#include "core/platform.h"
#include "core/filesystem/userfs/data.h"
#include "core/filesystem/userfs/document.h"
#include "core/filesystem/userfs/list.h"
#include "core/filesystem/userfs/list_data.h"
#include "core/filesystem/userfs/list_item_array.h"
#include "core/user/user/user.h"
#include "core/user/user/mesh_item.h"
#include "aura/user/user/shell.h"
#include "apex/filesystem/fs/set.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/handler/topic.h"
#include "acme/constant/id.h"

namespace
{
   class test_application : public ::platform::application
   {
   public:
      ::file::path defer_process_path(::file::path path) override { return path; }
   };
   class test_document : public ::userfs::document
   {
   public:
      int m_iCompleted = 0;
      int m_iFailed = 0;
      void on_update_data(::data::data *, ::topic * topic, const ::action_context &) override
      {
         if (topic->id() == id_browse) ++m_iCompleted;
      }
      void update_all_impacts(::topic * topic) override
      {
         if (topic->id() == "filemanager_browse_failed") ++m_iFailed;
      }
   };
   class test_provider : public ::fs::data, public ::file::image_info_provider
   {
   public:
      bool get_file_image_info(const ::file::path &, ::file::image_info & info) override
      {
         info.m_strName = "photo.webp";
         info.m_bFolder = false;
         return true;
      }
   };
   class test_shell : public ::user::shell
   {
   public:
      image_key m_key;
      ::i32 get_file_image(const image_key & key) override { m_key = key; return 17; }
   };
   class test_user : public ::core::user
   {
   public:
      test_shell * m_shell = nullptr;
      ::user::shell * shell() override { return m_shell; }
   };
   class test_list : public ::userfs::list
   {
   public:
      test_user * m_user = nullptr;
      ::pointer < ::userfs::list_data > m_data;
      ::user::user * user() override { return m_user; }
      ::userfs::list_data * fs_list() override { return m_data; }
   };
}

int main()
{
   ::platform::system runtime;
   ::pointer < test_application > app(allocate_t{});
   app->m_papplication = app;
   ::pointer < ::userfs::data > data(allocate_t{});
   data->m_papplication = app;
   ::pointer < test_document > document(allocate_t{});
   document->m_puserfsdata = data;
   data->m_pusercontroller = document;
   ::pointer < ::fs::set > fs(allocate_t{});
   fs->m_papplication = app;
   data->m_pfsset = fs;
   ::pointer < test_provider > provider(allocate_t{});
   fs->fsmap()["test://"] = provider;
   ::pointer < ::file::item > folder(allocate_t{}, "test://folder", "test://folder");
   ::file::listing_base listing;
   listing.set_listing("test://folder", e_depth_none, ::file::e_flag_file_or_folder);
   ::file::path photo("test://folder/image-id");
   photo.set_existent_file();
   photo.m_iSize = 1234;
   listing.defer_add(photo);
   listing.m_straTitle.add("photo.webp");
   listing.m_pathFinal = "test://folder";
   ::file::listing_base copied(listing);
   if (copied.m_pathFinal != listing.m_pathFinal || copied.m_straTitle.size() != 1
      || copied.m_eflag != listing.m_eflag) return 15;
   ::file::listing_base moved(::transfer(copied));
   if (moved.m_pathFinal != listing.m_pathFinal || moved.m_straTitle.size() != 1) return 16;
   data->m_uBrowseRequest = 2;
   data->complete_browse(1, folder, ::e_source_user, listing, {});
   if (document->m_iCompleted || data->m_listingUser2.has_element()) return 1;
   data->complete_browse(2, folder, ::e_source_user, listing, {});
   if (data->m_listingUser2.m_straTitle.is_empty()) return 14;
   if (document->m_iCompleted != 1 || data->m_listingUser2.size() != 1
      || data->m_listingUser2.m_straTitle[0] != "photo.webp" || data->m_listingFinal2[0].m_iSize != 1234) return 2;
   data->browse_failed(1, ::e_source_user);
   if (document->m_iFailed) return 3;
   data->browse_failed(2, ::e_source_user);
   if (document->m_iFailed != 1) return 4;

   ::pointer < test_shell > shell(allocate_t{});
   ::pointer < test_user > user(allocate_t{});
   user->m_shell = shell;
   ::pointer < test_list > list(allocate_t{});
   list->m_papplication = app;
   list->m_user = user;
   list->m_pdocument = document;
   list->m_data = ::pointer < ::userfs::list_data >(allocate_t{});
   list->m_data->m_papplication = app;
   list->m_data->update(data);
   list->m_iNameSubItem = 0;
   list->m_iIconSubItem = 0;
   ::user::mesh_subitem subitem;
   subitem.m_pitem = ::pointer < ::user::mesh_item >(allocate_t{});
   subitem.m_pitem->m_iItem = 0;
   subitem.m_iSubItem = 0;
   subitem.m_iImage = -1;
   list->_001GetSubItemImage(&subitem);
   if (!subitem.m_bOk || subitem.m_iImage != 17 || !shell->m_key.m_bProviderImage
      || shell->m_key.m_strExtension != "webp") return 5;
   data->m_pusercontroller.release();
   document->m_puserfsdata.release();
   return 0;
}
