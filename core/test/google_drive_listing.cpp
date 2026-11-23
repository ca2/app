#include "core/platform.h"
#include "core/filesystem/userfs/data.h"
#include "core/filesystem/userfs/list_data.h"
#include "core/filesystem/userfs/list_item_array.h"
#include "apex/filesystem/fs/set.h"
#include "folder_google_drive/_.h"
#include "folder_google_drive/folder.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/listing.h"

int main()
{
   ::platform::system testSystem;
   ::pointer < ::platform::application > papplication(allocate_t{});
   papplication->m_papplication = papplication;
   ::pointer < ::folder_google_drive::folder > pdrive(allocate_t{});
   ::pointer < ::fs::set > pfilesystem(allocate_t{});
   pfilesystem->m_papplication = papplication;
   pfilesystem->fsa().add(pdrive);
   ::file::listing_base roots;
   pfilesystem->root_ones(roots);
   if (roots.size() != 1) return 11;
   if (roots[0] != "google-drive://") return 12;
   if (roots.m_straTitle.size() != 1) return 13;
   if (roots.m_straTitle[0] != "Google Drive") return 14;
   if (pfilesystem->path_data("google-drive://") != pdrive.get()
      || pfilesystem->is_dir("google-drive://") != 1) return 2;

   ::pointer < ::userfs::data > pdata(allocate_t{});
   pdata->m_pfsset = pfilesystem;
   ::file::path path("google-drive://folder-id");
   path.set_existent_folder();
   pdata->m_listingUser2.defer_add(path);
   pdata->m_listingUser2.m_straTitle.add("Project invoices");
   pdata->m_listingFinal2.defer_add(path);
   ::pointer < ::userfs::list_data > plist(allocate_t{});
   plist->m_papplication = papplication;
   plist->update(pdata);
   if (plist->item(0)->m_strName != "Project invoices") return 3;
   if (plist->item(0)->user_path() != path) return 4;

   pdata->m_listingUser2.m_straTitle.erase_all();
   plist->update(pdata);
   if (plist->item(0)->m_strName != "folder-id") return 5;

   ::payload page;
   page.parse_network_payload(R"({"files":[
      {"id":"child-folder","name":"Pictures","mimeType":"application/vnd.google-apps.folder"},
      {"id":"child-file","name":"invoice.pdf","mimeType":"application/pdf","size":"12345"}
   ]})");
   ::file::listing_base children;
   children.set_listing("google-drive://folder-id", e_depth_none, ::file::e_flag_file_or_folder);
   ::string_array_base patterns;
   pdrive->append_listing_page(children, page, patterns);
   if (children.size() != 2 || !children[0].is_folder() || !children[1].is_file()) return 6;
   if (children[0] != "google-drive://folder-id/child-folder"
      || children[1] != "google-drive://folder-id/child-file") return 7;
   if (children[1].m_iSize != 12345) return 8;
   pdata->m_listingUser2 = children;
   pdata->m_listingFinal2 = children;
   plist->update(pdata);
   if (plist->item(0)->m_strName != "Pictures" || !plist->item(0)->is_folder()
      || plist->item(1)->m_strName != "invoice.pdf" || plist->item(1)->is_folder()) return 9;

   ::file::listing_base folders;
   folders.set_listing("google-drive://folder-id", e_depth_none, ::file::e_flag_folder);
   folders.m_bFile = false;
   pdrive->append_listing_page(folders, page, patterns);
   if (folders.size() != 1 || folders.m_straTitle[0] != "Pictures") return 10;
   return 0;
}
