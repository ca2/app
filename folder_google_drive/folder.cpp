#include "platform.h"
#include "folder.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/prototype/url.h"
#include "apex/platform/api.h"
#include "acme/platform/scoped_restore.h"

namespace folder_google_drive
{
   folder::~folder()
   {
      // api_client and api hold each other; the provider owns their lifetime.
      if (m_papiclient && m_papiclient->m_papi)
         m_papiclient->m_papi->m_papiclient.release();
      if (m_papiclientWrite && m_papiclientWrite->m_papi)
         m_papiclientWrite->m_papi->m_papiclient.release();
   }

   void folder::initialize(::particle * pparticle)
   {
      ::folder::initialize(pparticle);
      defer_create_synchronization();
      m_pathContent = directory_system()->home() / "folder/google_drive";
      m_pathMetadata = directory_system()->home() / "folder/.google_drive";
      // A separate profile prevents reusing a token granted only cloud-platform scope.
      m_papiclient = create_newø < ::api_client >();
      m_papiclient->initialize_api_client("google", "", "", m_pathMetadata / "profile");
      m_papiclient->m_papi = m_papiclient->create_api("google", "");
      m_papiclient->m_papi->m_strScope = "https://www.googleapis.com/auth/drive.readonly";
   }

   ::string folder::file_id(const ::file::path & path)
   {
      ::string str(path);
      if (!str.case_insensitive_begins_eat("google-drive://"))
         throw ::exception(error_bad_argument, "Expected google-drive:// URI");
      str.trim_right("/");
      if (str.is_empty()) return "root";
      ::string strId = ::file::path(str).name();
      // IDs are opaque and never used as arbitrary local paths or query expressions.
      for (auto ch : strId)
         if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
            || (ch >= '0' && ch <= '9') || ch == '_' || ch == '-'))
            throw ::exception(error_bad_argument, "Invalid Google Drive file ID");
      return strId;
   }

   ::payload folder::request(const ::scoped_string & scopedstrUrl)
   {
      ::property_set set;
      return api_request(m_papiclient, scopedstrUrl, set);
   }

   ::payload folder::api_request(::api_client * pclient, const ::scoped_string & scopedstrUrl, ::property_set & set)
   {
      pclient->defer_api();
      ::string str;
      pclient->m_papi->_api_get(str, scopedstrUrl, set);
      auto status = set["http_status_code"].as_i32();
      ::payload result;
      bool bParsed = false;
      try { result.parse_network_payload(str); bParsed = true; } catch (...) {}
      if (status < 200 || status >= 300 || result.has_property("error"))
      {
         auto strMessage = result["error"]["message"].as_string();
         throw ::exception(error_failed, "Google Drive request failed (HTTP " + ::as_string(status) + "): " + strMessage);
      }
      if (!bParsed)
         throw ::exception(error_failed, "Google Drive returned an invalid response. Refresh the folder before trying again.");
      return result;
   }

   ::file::path folder::create_folder(const ::file::path & pathParent, const ::scoped_string & scopedstrName)
   {
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      ::string strName(scopedstrName);
      strName.trim();
      if (strName.is_empty() || strName == "." || strName == ".." || strName.contains("/") || strName.contains("\\"))
         throw ::exception(error_bad_argument, "Enter a folder name without path separators");
      auto strParentId = file_id(pathParent);
      if (metadata(pathParent)["mimeType"].as_string() != "application/vnd.google-apps.folder")
         throw ::exception(error_bad_argument, "The parent must be a Google Drive folder");
      write_api();
      ::property_set set;
      set["http_method"] = "POST";
      auto & body = set["post"]["network_payload"];
      body["name"] = strName;
      body["mimeType"] = "application/vnd.google-apps.folder";
      body["parents"].string_array_reference().add(strParentId);
      auto result = api_request(m_papiclientWrite,
         "https://www.googleapis.com/drive/v3/files?supportsAllDrives=true&fields=id,name,mimeType,version", set);
      auto strId = result["id"].as_string();
      if (strId.is_empty()) throw ::exception(error_failed, "Google Drive did not return the new folder ID");
      ::file::path pathCreated = pathParent / strId;
      file_id(pathCreated);
      try
      {
         directory_system()->create(m_pathMetadata / "files");
         file()->put_text(m_pathMetadata / "files" / (strId + ".json"), result.get_network_payload());
      }
      catch (...) { warning() << "The folder was created, but its local metadata could not be cached"; }
      return pathCreated;
   }

   ::api_client * folder::write_api()
   {
      // Request write permission only for an explicit mutation.
      // A separate profile cannot accidentally reuse the read-only token.
      if (!m_papiclientWrite)
      {
         m_papiclientWrite = create_newø < ::api_client >();
         m_papiclientWrite->initialize_api_client("google", "", "", m_pathMetadata / "profile_write");
         m_papiclientWrite->m_papi = m_papiclientWrite->create_api("google", "");
         m_papiclientWrite->m_papi->m_strScope = "https://www.googleapis.com/auth/drive";
      }
      return m_papiclientWrite;
   }

   ::file::path folder::import_file(const ::file::path & destination, const ::file::path & source,
      const ::function<bool(::f64)> & progress)
   {
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      auto notify = [&](::f64 rate)
      {
         if (progress && !progress(rate)) throw ::exception(error_cancelled, "Paste cancelled");
      };
      notify(0.0);
      auto parentId = file_id(destination);
      auto input = file()->get_reader(source);
      if (!input) throw ::exception(error_file_not_found, "Could not open the file to upload");
      const auto length = input->size();
      // The existing HTTP PUT transport currently uses a signed 32-bit content length.
      if (length > 0x7fffffff) throw ::exception(error_not_supported, "Files larger than 2 GB are not supported by this upload transport yet");
      if (metadata(destination)["mimeType"].as_string() != "application/vnd.google-apps.folder")
         throw ::exception(error_bad_argument, "The paste destination must be a Google Drive folder");
      auto client = write_api();
      ::property_set start;
      start["http_method"] = "POST";
      auto & body = start["post"]["network_payload"];
      body["name"] = source.name();
      body["parents"].string_array_reference().add(parentId);
      start["headers"]["X-Upload-Content-Type"] = "application/octet-stream";
      start["headers"]["X-Upload-Content-Length"] = ::as_string(length);
      ::string response;
      client->defer_api();
      client->m_papi->_api_get(response,
         "https://www.googleapis.com/upload/drive/v3/files?uploadType=resumable&supportsAllDrives=true&fields=id,name,mimeType,size,version,modifiedTime,parents", start);
      const auto status = start["http_status_code"].as_i32();
      auto sessionUrl = start["get_headers"]["location"].as_string();
      if (status < 200 || status >= 300)
         throw ::exception(error_failed, "Could not start Google Drive upload (HTTP " + ::as_string(status) + "): " + response);
      if (!sessionUrl.begins("https://www.googleapis.com/upload/drive/"))
         throw ::exception(error_failed, "Google Drive returned an invalid upload session");
      notify(0.0);
      ::property_set upload;
      upload["http_method"] = "PUT";
      upload["put"] = input;
      upload["headers"]["Content-Type"] = "application/octet-stream";
      transfer_progress_function callback = [&](::f64 rate, filesize, filesize) { notify(rate * 0.99); };
      upload["transfer_progress_function"] = callback;
      auto result = api_request(client, sessionUrl, upload);
      auto id = result["id"].as_string();
      if (id.is_empty() || result["size"].as_i64() != length)
         throw ::exception(error_failed, "Google Drive did not confirm the complete uploaded file");
      auto created = destination / id;
      file_id(created);
      try
      {
         directory_system()->create(m_pathMetadata / "files");
         file()->put_text(m_pathMetadata / "files" / (id + ".json"), result.get_network_payload());
      }
      catch (...) { warning() << "The file was uploaded, but its local metadata could not be cached"; }
      // Once committed, report success even if cancellation was requested during the response.
      if (progress) progress(1.0);
      return created;
   }

   ::payload folder::metadata(const ::file::path & path)
   {
      auto strId = file_id(path);
      auto result = request("https://www.googleapis.com/drive/v3/files/" + strId
         + "?supportsAllDrives=true&fields=id,name,mimeType,size,version,modifiedTime,trashed");
      if (result["trashed"].as_bool())
         throw ::exception(error_file_not_found);
      directory_system()->create(m_pathMetadata / "files");
      file()->put_text(m_pathMetadata / "files" / (strId + ".json"), result.get_network_payload());
      return result;
   }

   ::file::listing_base & folder::root_ones(::file::listing_base & listing)
   {
      ::file::path path("google-drive://");
      path.set_existent_folder();
      listing.defer_add(path);
      listing.m_straTitle.add("Google Drive");
      return listing;
   }

   bool folder::get_file_image_info(const ::file::path & path, ::file::image_info & info)
   {
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      auto strId = file_id(path);
      if (strId == "root") return false; // Preserve the root's custom icon.
      auto pathMetadata = m_pathMetadata / "files" / (strId + ".json");
      if (!file_system()->exists(pathMetadata)) return false;
      ::payload entry;
      entry.parse_network_payload(file()->as_string(pathMetadata));
      info = {};
      info.m_bFolder = entry["mimeType"].as_string() == "application/vnd.google-apps.folder";
      info.m_strName = entry["name"].as_string();
      auto strVersion = entry["version"].as_string();
      bool bVersionValid = strVersion.has_character();
      for (auto ch : strVersion) if (ch < '0' || ch > '9') bVersionValid = false;
      if (!info.m_bFolder && entry["mimeType"].as_string().begins("image/") && bVersionValid)
      {
         
         auto pathContent = m_pathContent / strId / strVersion;

         if (file_system()->exists(pathContent) && file_system()->size(pathContent) == entry["size"].as_i64())
         {
            
            info.m_strLocalThumbnailPath = pathContent;

         }
         else
         {

            background_download_add(path, info.m_particleaNotify);

         }

      }

      return true;
   }

   bool folder::enumerate(::file::listing_base & listing)
   {
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      if (listing.m_bRecursive || listing.m_edepth > 0)
         throw ::exception(error_not_supported, "Recursive Google Drive enumeration is not implemented");
      auto pathBase = listing.m_pathUser;
      auto strId = file_id(pathBase);
      ::string strPage;
      ::string_array_base straPages;
      auto straPatterns = listing.m_straPattern;
      auto restorePatterns = create_scoped_restore(listing.m_straPattern);
      listing.m_straPattern.erase_all();
      int iPage = 0;
      do
      {
         auto strQuery = "'" + strId + "' in parents and trashed = false";
         auto strUrl = "https://www.googleapis.com/drive/v3/files?q=" + ::url::encode(strQuery)
            + "&pageSize=1000&supportsAllDrives=true&includeItemsFromAllDrives=true"
              "&fields=nextPageToken,files(id,name,mimeType,size,version,modifiedTime)";
         if (strPage.has_character()) strUrl += "&pageToken=" + ::url::encode(strPage);
         auto result = request(strUrl);
         append_listing_page(listing, result, straPatterns);
         // Keep icon metadata available without another API call or login.
         directory_system()->create(m_pathMetadata / "files");
         for (auto & entry : result["files"].payload_array_reference())
         {
            auto pathEntry = pathBase / entry["id"].as_string();
            auto strEntryId = file_id(pathEntry);
            file()->put_text(m_pathMetadata / "files" / (strEntryId + ".json"), entry.get_network_payload());
         }
         auto pathListing = m_pathMetadata / "listings" / strId;
         directory_system()->create(pathListing);
         file()->put_text(pathListing / (::as_string(iPage++) + ".json"),
            result.get_network_payload());
         strPage = result["nextPageToken"].as_string();
         if (strPage.has_character() && straPages.contains(strPage))
            throw ::exception(error_failed, "Google Drive returned a repeated page token");
         straPages.add(strPage);
      } while (strPage.has_character());
      listing.m_pathFinal = pathBase;
      return true;
   }

   void folder::append_listing_page(::file::listing_base & listing, ::payload & result,
      const ::string_array_base & straPatterns)
   {
      auto pathBase = listing.m_pathUser;
      for (auto & entry : result["files"].payload_array_reference())
      {
         auto strName = entry["name"].as_string();
         if (!case_insensitive_matches_wildcard_criteria(straPatterns, strName)) continue;
         bool bFolder = entry["mimeType"].as_string() == "application/vnd.google-apps.folder";
         if ((bFolder && !listing.m_bDir) || (!bFolder && !listing.m_bFile)) continue;
         ::file::path path = pathBase / entry["id"].as_string();
         if (bFolder) path.set_existent_folder(); else path.set_existent_file();
         path.m_iSize = entry["size"].as_i64();
         auto count = listing.size();
         listing.defer_add(path);
         if (listing.size() > count) listing.m_straTitle.add(entry["name"].as_string());
      }
   }

   ::file::e_type folder::file_type(const ::file::path & path)
   {
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      if (file_id(path) == "root") return ::file::e_type_existent_folder;
      auto entry = metadata(path);
      return entry["mimeType"].as_string() == "application/vnd.google-apps.folder"
         ? ::file::e_type_existent_folder : ::file::e_type_existent_file;
   }

   ::i32 folder::is_dir(const ::file::path & path) { return file_type(path) == ::file::e_type_existent_folder ? 1 : 0; }
   bool folder::file_exists(const ::file::path & path) { return file_type(path) == ::file::e_type_existent_file; }
   ::payload folder::file_length(const ::file::path & path)
   {
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      return metadata(path)["size"];
   }
   bool folder::has_subdir(const ::file::path & path)
   {
      ::file::listing_base listing;
      listing.m_pathUser = path;
      listing.m_bFile = false;
      enumerate(listing);
      return listing.has_element();
   }
   // Remote directory probing is deferred to the actual expansion.
   bool folder::fast_has_subdir(const ::file::path & path)
   {
      if (path.is_folder() || file_id(path) == "root") return true;
      if (path.is_file()) return false;
      ::file::image_info info;
      return get_file_image_info(path, info) && info.m_bFolder;
   }
   bool folder::locate_file(const ::file::path & path)
   {
      if (!file_exists(path)) return false;
      m_strCurrent = path; m_etypeCurrent = ::file::e_type_existent_file;
      return true;
   }
   bool folder::locate_folder(const ::file::path & path)
   {
      if (is_dir(path) != 1) return false;
      m_strCurrent = path; m_etypeCurrent = ::file::e_type_existent_folder;
      return true;
   }
   bool folder::has_sub_folder(const ::file::path & path) { return has_subdir(path.has_character() ? path : ::file::path(m_strCurrent)); }
   bool folder::is_compressed(const ::file::path &) { return false; }
   ::file_pointer folder::get_file(const ::file::path & path)
   {
      return get_file(::payload(path), ::file::e_open_read | ::file::e_open_binary);
   }
   ::file_pointer folder::get_file() { return get_file(::file::path(m_strCurrent)); }

   ::file_pointer folder::get_file(const ::payload & payloadFile, ::file::e_open eopen,
      ::pointer < ::file::exception > * pexception)
   {
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      if (eopen & (::file::e_open_write | ::file::e_open_create | ::file::e_open_truncate))
         throw ::exception(error_not_supported, "Google Drive browsing is read-only");
      auto path = payloadFile.as_file_path();
      auto entry = metadata(path);
      auto strMime = entry["mimeType"].as_string();
      if (strMime.begins("application/vnd.google-apps."))
         throw ::exception(error_not_supported, "Google Workspace documents require export; folders and shortcuts cannot be downloaded");
      auto strId = file_id(path);
      
      auto strVersion = entry["version"].as_string();
      if (strVersion.is_empty()) throw ::exception(error_failed, "Google Drive did not return a file version");
      for (auto ch : strVersion)
         if (ch < '0' || ch > '9') throw ::exception(error_failed, "Invalid Google Drive file version");
      // Versioned files do not overwrite an older valid download on failure.
      ::file::path pathContent = m_pathContent / strId / strVersion;
      if (!file_system()->exists(pathContent) || file_system()->size(pathContent) != entry["size"].as_i64())
      {
         ::property_set set;
         auto memory = m_papiclient->api_memory("https://www.googleapis.com/drive/v3/files/" + strId
            + "?alt=media&supportsAllDrives=true", set);
         auto status = set["http_status_code"].as_i32();
         if (status < 200 || status >= 300) throw ::exception(error_failed, "Google Drive download failed");
         if (memory.size() != entry["size"].as_i64()
            || metadata(path)["version"].as_string() != strVersion)
            throw ::exception(error_failed, "Google Drive file changed during download; please retry");
         directory_system()->create(pathContent.folder());
         file()->put_memory(pathContent, memory);
      }
      return file()->get_file(pathContent, eopen, pexception);
   }

   void folder::extract(::memory & memory, const ::file::path & path)
   {
      auto pfile = path.has_character() ? get_file(path) : get_file();
      memory = file()->as_memory(pfile);
   }
}
