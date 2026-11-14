#include "platform.h"
#include "path_impact.h"
#include "document.h"
#include "data.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "apex/filesystem/fs/set.h"
#include "aura/message/user.h"

namespace filemanager
{
   path_impact::path_impact()
   {
      m_bVoidSync = false;
      m_bMultiLine = false;
   }

   void path_impact::install_message_routing(::channel * pchannel)
   {
      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::plain_edit::install_message_routing(pchannel);
      USER_MESSAGE_LINK(::user::e_message_key_down, pchannel, this, &path_impact::on_message_key_down);
      USER_MESSAGE_LINK(::user::e_message_kill_focus, pchannel, this, &path_impact::on_message_kill_focus);
   }

   void path_impact::browse_sync(const ::action_context &)
   {
      if (m_bVoidSync || !filemanager_document()) return;
      auto pitem = filemanager_item();
      if (!pitem) return;
      auto strPath = pitem->user_path();
      if (get_text() != strPath) set_text(strPath, ::e_source_sync);
   }

   ::file::path path_impact::resolve_folder(const ::scoped_string & scopedstrText, bool bFindParent)
   {
      ::string str(scopedstrText);
      str.trim();
      if (str.length() >= 2 && str.begins("\"") && str.ends("\""))
         str = str.substr(1, str.length() - 2);
      if (str.is_empty() || !filemanager_document() || !filemanager_item()) return {};
      ::file::path path;
      if (str == "~") path = directory_system()->home();
      else if (str.begins_eat("~/") || str.begins_eat("~\\")) path = directory_system()->home() / str;
      else path = str;
      if (path.is_relative() && !path.contains("://"))
      {
         if (!bFindParent) return {};
         path = filemanager_item()->user_path() / path;
      }
      auto pfsdata = filemanager_data()->fs_data();
      while (path.has_character())
      {
         try
         {
            auto pathToProcess = path;
            pathToProcess.flags() += ::file::e_flag_resolve_alias;
            auto pathFinal = application()->defer_process_path(pathToProcess);
            // is_dir returns -1 for an unknown provider, which is not a directory.
            if (pathFinal.has_character() && pfsdata->is_dir(pathFinal) > 0) return path;
         }
         catch (...) {}
         if (!bFindParent) break;
         auto pathParent = path.folder();
         if (pathParent == path) break;
         path = pathParent;
      }
      return {};
   }

   bool path_impact::browse_typed_path(bool bFindParent)
   {
      auto path = resolve_folder(get_text(), bFindParent);
      if (path.is_empty()) return false;
      auto pitem = filemanager_item();
      if (!pitem || pitem->user_path() != path)
      {
         try { filemanager_document()->browse(path, ::e_source_user); }
         catch (...) { return false; }
      }
      if (bFindParent && get_text() != path) set_text(path, ::e_source_sync);
      return true;
   }

   void path_impact::on_message_key_down(::message::message * pmessage)
   {
      auto pkey = pmessage->m_union.m_pkey;
      if (pkey && pkey->m_ekey == ::user::e_key_return)
      {
         m_bVoidSync = false;
         if (!browse_typed_path(true)) browse_sync(::e_source_sync);
         pmessage->m_bRet = true;
         pmessage->m_lresult = 1;
         return;
      }
      pmessage->previous();
   }

   void path_impact::on_message_kill_focus(::message::message * pmessage)
   {
      pmessage->previous();
      m_bVoidSync = false;
      browse_sync(::e_source_sync);
   }

   void path_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      ::user::plain_edit::_001OnDraw(pgraphics);
   }

   void path_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {
      ::filemanager_impact_base::handle(ptopic, pcontext);
      ::user::plain_edit::handle(ptopic, pcontext);
      if (ptopic->id() == id_initialize || ptopic->id() == id_browse)
         browse_sync(ptopic->m_actioncontext);
      else if (ptopic->id() == id_after_change_text && ptopic->m_actioncontext.is_user_source())
      {
         // Do not let a queued browse completion overwrite newer in-progress input.
         m_bVoidSync = true;
         browse_typed_path(false);
      }
   }
}
