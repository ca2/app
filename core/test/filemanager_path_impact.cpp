#include "core/platform.h"
#include "core/filesystem/filemanager/path_impact.h"
#include "core/filesystem/filemanager/document.h"
#include "core/filesystem/filemanager/data.h"
#include "apex/filesystem/fs/set.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/filesystem/file/item.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "aura/message/user.h"

namespace
{
   class path_application : public ::platform::application
   {
   public:
      ::file::path defer_process_path(::file::path path) override { return path; }
   };

   class path_filesystem : public ::fs::set
   {
   public:
      ::i32 is_dir(const ::file::path & path) override
      {
         return path == "test://root" || path == "test://root/child"
            || path == "image://" || path == "google-drive://" || path == "google-drive://folder-id" ? 1 : -1;
      }
   };

   class path_document : public ::filemanager::document
   {
   public:
      int m_iBrowses = 0;
      void browse(const ::file::path & path, const ::action_context &) override
      {
         ++m_iBrowses;
         auto finalPath = path;
         finalPath.flags() += ::file::e_flag_final_path;
         m_pfilemanagerdata->m_pitem = ::pointer < ::file::item >(allocate_t{}, path, finalPath);
      }
   };

   class path_edit : public ::filemanager::path_impact
   {
   public:
      path_document * m_pdocumentTest = nullptr;
      ::string m_strEdit;
      ::filemanager::document * filemanager_document() override { return m_pdocumentTest; }
      ::string get_text() const override { return m_strEdit; }
      void set_text(const ::scoped_string & text, const ::action_context &) override { m_strEdit = text; }
   };
}

int main()
{
   ::platform::system testSystem;
   ::pointer < path_application > papplication(allocate_t{});
   papplication->m_papplication = papplication;
   ::pointer < path_filesystem > pfilesystem(allocate_t{});
   ::pointer < ::filemanager::data > pdata(allocate_t{});
   pdata->m_pfsset = pfilesystem;
   ::file::path finalRoot("test://root");
   finalRoot.flags() += ::file::e_flag_final_path;
   pdata->m_pitem = ::pointer < ::file::item >(allocate_t{}, "test://root", finalRoot);
   ::pointer < path_document > pdocument(allocate_t{});
   pdocument->m_pfilemanagerdata = pdata;
   ::pointer < path_edit > pedit(allocate_t{});
   pedit->m_papplication = papplication;
   pedit->m_pdocumentTest = pdocument;

   ::topic browsed(id_browse);
   pedit->handle(&browsed, nullptr);
   if (pedit->m_strEdit != "test://root") return 1;

   pedit->m_strEdit = "test://root/child";
   if (!pedit->browse_typed_path(false) || pdocument->m_iBrowses != 1
      || pdata->m_pitem->user_path() != "test://root/child") return 2;

   pedit->m_strEdit = "unknown://invalid";
   if (pedit->browse_typed_path(false) || pdocument->m_iBrowses != 1) return 3;
   ::message::message blur;
   blur.m_iRouteIndex = 0;
   pedit->on_message_kill_focus(&blur);
   if (pedit->m_strEdit != "test://root/child") return 4;

   ::message::key enter;
   enter.m_union.m_pkey = &enter;
   enter.m_ekey = ::user::e_key_return;
   pedit->m_strEdit = "test://root/child/missing/file";
   pedit->on_message_key_down(&enter);
   if (!enter.m_bRet || pedit->m_strEdit != "test://root/child") return 5;

   pedit->m_strEdit = "unknown://invalid";
   pedit->on_message_key_down(&enter);
   if (pedit->m_strEdit != "test://root/child") return 6;

   pdocument->browse("test://root", ::e_source_sync);
   pedit->m_strEdit = "child";
   if (pedit->browse_typed_path(false)) return 7; // Relative input waits for Enter.
   pedit->on_message_key_down(&enter);
   if (pdata->m_pitem->user_path() != "test://root/child" || pedit->m_strEdit != "test://root/child") return 8;

   if (pedit->resolve_folder("  \"test://root\"  ", true) != "test://root") return 9;
   pedit->m_bVoidSync = true;
   pedit->m_strEdit = "test://root/child/in-progress";
   pdocument->browse("test://root", ::e_source_sync);
   pedit->handle(&browsed, nullptr);
   if (pedit->m_strEdit != "test://root/child/in-progress") return 10;
   blur.m_iRouteIndex = 0;
   pedit->on_message_kill_focus(&blur);
   if (pedit->m_strEdit != "test://root") return 11;
   // Friendly root titles must never replace editable, reusable provider URIs.
   pdata->m_listingRoot2.add_get("image://").set_existent_folder();
   pdata->m_listingRoot2.m_straTitle.add("Image");
   pdata->m_listingRoot2.add_get("google-drive://").set_existent_folder();
   pdata->m_listingRoot2.m_straTitle.add("Google Drive");
   for (auto uri : {"image://", "google-drive://folder-id"})
   {
      pdocument->browse(uri, ::e_source_sync);
      pedit->browse_sync(::e_source_sync);
      if (pedit->get_text() != uri) return 12;
   }
   pedit->m_strEdit = "image://";
   auto beforeTyping = pdocument->m_iBrowses;
   ::topic changed(id_after_change_text);
   changed.m_actioncontext = ::e_source_user;
   pedit->handle(&changed, nullptr);
   if (pdocument->m_iBrowses != beforeTyping) return 13;
   pedit->on_message_key_down(&enter);
   if (pdata->m_pitem->user_path() != "image://" || pedit->get_text() != "image://") return 14;
   pedit->m_strEdit = "google-drive://folder-id";
   pedit->handle(&changed, nullptr);
   pedit->on_message_key_down(&enter);
   if (pdata->m_pitem->user_path() != "google-drive://folder-id") return 15;
   if (pedit->resolve_folder("google-drive://Pictures", true) != "google-drive://Pictures") return 16;
   // Enter on the current address still goes through browse completion/focus.
   auto beforeSameAddress = pdocument->m_iBrowses;
   pedit->on_message_key_down(&enter);
   if (pdocument->m_iBrowses != beforeSameAddress + 1) return 17;
   pedit->destroy();
   return 0;
}
