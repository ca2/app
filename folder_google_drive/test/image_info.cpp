#include "folder_google_drive/platform.h"
#include "folder_google_drive/folder.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/file_context.h"

namespace
{
   class cached_files : public ::file_system
   {
   public:
      bool m_bContent = false;
      filesize m_iSize = 12;
      bool exists(const ::file::path & path) override { return path.ends(".json") || m_bContent; }
      filesize size(const ::file::path &) override { return m_iSize; }
   };
   class cached_metadata : public ::file_context
   {
   public:
      ::string m_strJson;
      ::string as_string(const ::payload &) override { return m_strJson; }
   };
   class cached_application : public ::platform::application
   {
   public:
      ::pointer < cached_files > m_files;
      ::pointer < cached_metadata > m_metadata;
      ::file_system * file_system() override { return m_files; }
      ::file_context * file() override { return m_metadata; }
   };
}

int main()
{
   ::platform::system testSystem;
   ::pointer < cached_application > app(allocate_t{});
   app->m_papplication = app;
   app->m_files = ::pointer < cached_files >(allocate_t{});
   app->m_metadata = ::pointer < cached_metadata >(allocate_t{});
   ::folder_google_drive::folder drive;
   drive.m_papplication = app;
   drive.m_pathMetadata = "meta";
   drive.m_pathContent = "cache";
   app->m_metadata->m_strJson = R"({"name":"photo.webp","mimeType":"image/webp","version":"42","size":"12"})";
   ::file::image_info info;
   if (!drive.get_file_image_info("google-drive://image-id", info) || info.m_bFolder
      || info.m_strName != "photo.webp" || info.m_strLocalThumbnailPath.has_character()) return 1;
   app->m_files->m_bContent = true;
   if (!drive.get_file_image_info("google-drive://image-id", info)
      || info.m_strLocalThumbnailPath != "cache/image-id/42") return 2;
   app->m_files->m_iSize = 11;
   if (!drive.get_file_image_info("google-drive://image-id", info)
      || info.m_strLocalThumbnailPath.has_character()) return 3;
   app->m_metadata->m_strJson = R"({"name":"Photos","mimeType":"application/vnd.google-apps.folder"})";
   if (!drive.get_file_image_info("google-drive://folder-id", info) || !info.m_bFolder
      || info.m_strLocalThumbnailPath.has_character()) return 4;
   if (drive.get_file_image_info("google-drive://", info)) return 5;
   // No api_client is initialized: all of these requests must be cache-only.
   if (drive.m_papiclient) return 6;
   return 0;
}
