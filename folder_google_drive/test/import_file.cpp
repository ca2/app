#include "folder_google_drive/platform.h"
#include "folder_google_drive/folder.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "apex/platform/api.h"

namespace
{
   class test_directories : public ::directory_system
   {
   public:
      void create(const ::file::path &) override {}
   };
   class test_system : public ::platform::system
   {
   public:
      ::pointer<test_directories> m_directories;
      ::directory_system * directory_system() const override { return m_directories; }
   };
   class test_files : public ::file_context
   {
   public:
      ::file_pointer get_reader(const ::payload &, ::file::e_open) override
      {
         return ::pointer<::memory_file>(allocate_t{}, "abc", 3);
      }
      void put_text(const ::payload &, const ::scoped_string &) override {}
   };
   class test_app : public ::platform::application
   {
   public:
      ::pointer<test_files> m_files;
      ::file_context * file() override { return m_files; }
   };
   class recording_api : public ::api
   {
   public:
      ::string get_name_for_profile() override { return "test"; }
      int m_starts = 0;
      int m_uploads = 0;
      bool m_badSession = false;
      bool m_failUpload = false;
      ::string m_parent;
      ::string m_name;
      void _api_get(::string & response, const ::scoped_string & url, ::property_set & set) override
      {
         set["http_status_code"] = 200;
         if (set["http_method"] == "POST")
         {
            ++m_starts;
            m_parent = set["post"]["network_payload"]["parents"].as_string_array()[0];
            m_name = set["post"]["network_payload"]["name"].as_string();
            set["get_headers"]["location"] = m_badSession ? "https://other.example/upload" : "https://www.googleapis.com/upload/drive/v3/files?upload_id=test";
            response = "";
         }
         else if (set["http_method"] == "PUT")
         {
            ++m_uploads;
            auto input = set["put"].cast<::file::file>();
            if (!input || input->size() != 3) throw ::exception(error_failed);
            transfer_progress_function progress = set["transfer_progress_function"];
            progress(0.5, 1, 3);
            if (m_failUpload) { set["http_status_code"] = 403; response = R"({"error":{"message":"No upload permission"}})"; }
            else response = R"({"id":"new-file-id","name":"photo.png","mimeType":"image/png","size":"3","version":"1"})";
         }
         else response = R"({"id":"pictures-id","mimeType":"application/vnd.google-apps.folder"})";
      }
   };
}
int main()
{
   test_system runtime;
   runtime.m_directories = ::pointer<test_directories>(allocate_t{});
   ::pointer<test_app> app(allocate_t{});
   app->m_papplication = app;
   app->m_files = ::pointer<test_files>(allocate_t{});
   ::folder_google_drive::folder drive;
   drive.m_papplication = app;
   drive.m_pathMetadata = "metadata";
   drive.defer_create_synchronization();
   ::pointer<recording_api> api(allocate_t{});
   api->m_bAuthenticated = true;
   drive.m_papiclient = ::pointer<::api_client>(allocate_t{});
   drive.m_papiclientWrite = ::pointer<::api_client>(allocate_t{});
   drive.m_papiclient->m_papi = api;
   drive.m_papiclientWrite->m_papi = api;
   int progressCalls = 0;
   ::file::folder_importer & importer = drive;
   auto result = importer.import_file("google-drive://pictures-id", "local/photo.png", [&](::f64) { ++progressCalls; return true; });
   if (result != "google-drive://pictures-id/new-file-id" || api->m_starts != 1 || api->m_uploads != 1
      || api->m_parent != "pictures-id" || api->m_name != "photo.png" || progressCalls < 3) return 1;
   try { importer.import_file("google-drive://pictures-id", "local/photo.png", [](::f64) { return false; }); return 2; }
   catch (const ::exception & error) { if (error.m_estatus != error_cancelled) return 3; }
   if (api->m_starts != 1) return 4;
   api->m_badSession = true;
   try { importer.import_file("google-drive://pictures-id", "local/photo.png", {}); return 5; }
   catch (const ::exception &) {}
   if (api->m_uploads != 1) return 6;
   api->m_badSession = false;
   api->m_failUpload = true;
   try { importer.import_file("google-drive://pictures-id", "local/photo.png", {}); return 7; }
   catch (const ::exception & error) { if (!error.get_message().contains("No upload permission")) return 8; }
   return 0;
}
