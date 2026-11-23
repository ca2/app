#include "core/platform.h"
#include "core/filesystem/filemanager/provider_path.h"
#include "acme/platform/system.h"
#include "acme/platform/application.h"
#include "apex/filesystem/fs/set.h"

namespace
{
   class test_application : public ::platform::application
   {
   public:
      ::file::path defer_process_path(::file::path path) override { return path; }
   };
   class provider : public ::fs::data, public ::file::image_info_provider
   {
   public:
      ::file::path root;
      bool duplicate = false;
      int enumerations = 0;
      bool get_file_image_info(const ::file::path & path, ::file::image_info & info) override
      {
         if (path == root / "pictures-id") info.m_strName = "Pictures";
         else if (path == root / "pictures-id/year-id") info.m_strName = "2026";
         else return false;
         info.m_bFolder = true;
         return true;
      }
      ::i32 is_dir(const ::file::path & path) override
      {
         return path == root || path == root / "pictures-id" || path == root / "documents-id"
            || path == root / "pictures-id/year-id" ? 1 : 0;
      }
      bool enumerate(::file::listing_base & listing) override
      {
         ++enumerations;
         if (!(listing.m_eflag & ::file::e_flag_folder)) return false;
         auto add = [&](const char * id, const char * name)
         {
            auto path = listing.m_pathUser / id;
            path.set_existent_folder();
            listing.defer_add(path);
            listing.m_straTitle.add(name);
         };
         if (listing.m_pathUser == root)
         {
            add("documents-id", "Documents");
            add("pictures-id", "Pictures");
            if (duplicate) add("another-id", "Pictures");
            return true;
         }
         if (listing.m_pathUser == root / "pictures-id")
         {
            add("year-id", "2026");
            return true;
         }
         return false;
      }
   };
}

int main()
{
   ::platform::system runtime;
   ::pointer<provider> filesystem(allocate_t{});
   ::pointer<test_application> app(allocate_t{});
   app->m_papplication = app;
   ::pointer<::fs::set> dispatcher(allocate_t{});
   dispatcher->m_papplication = app;
   for (auto root : {"google-drive://", "dropbox://", "dropbox-app://", "onedrive://"})
   {
      filesystem->root = root;
      dispatcher->fsmap().erase_all();
      dispatcher->fsmap()[root] = filesystem;
      filesystem->enumerations = 0;
      if (filemanager::provider_display_folder(*dispatcher, filesystem->root / "pictures-id") != filesystem->root / "Pictures") return 9;
      if (filemanager::provider_display_folder(*dispatcher, filesystem->root / "pictures-id/year-id") != filesystem->root / "Pictures/2026") return 10;
      using filemanager::resolve_provider_folder;
      if (resolve_provider_folder(*dispatcher, filesystem->root / "pictures-id") != filesystem->root / "pictures-id"
         || filesystem->enumerations != 0) return 1;
      try
      {
         if (resolve_provider_folder(*dispatcher, filesystem->root / "Pictures") != filesystem->root / "pictures-id") return 2;
      }
      catch (...) { return 8; }
      if (resolve_provider_folder(*dispatcher, filesystem->root / "pictures") != filesystem->root / "pictures-id") return 3;
      if (resolve_provider_folder(*dispatcher, filesystem->root / "Pictures/2026") != filesystem->root / "pictures-id/year-id") return 4;
      bool missing = false;
      try { resolve_provider_folder(*dispatcher, filesystem->root / "Missing"); }
      catch (const ::exception &) { missing = true; }
      if (!missing) return 5;
      filesystem->duplicate = true;
      bool ambiguous = false;
      try { resolve_provider_folder(*dispatcher, filesystem->root / "Pictures"); }
      catch (const ::exception &) { ambiguous = true; }
      filesystem->duplicate = false;
      if (!ambiguous) return 6;
   }
   if (filemanager::resolve_provider_folder(*dispatcher, "/local/Pictures") != "/local/Pictures") return 7;
   return 0;
}
