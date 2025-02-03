#include "framework.h"
#include "context_menu.h"
#include "data.h"
#include "document.h"
#include "file_list.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/platform/timer.h"
#include "acme/prototype/collection/_array_binary_stream.h"
#include "acme/prototype/collection/_container.h"
#include "apex/database/_binary_stream.h"
#include "apex/filesystem/fs/data.h"
#include "apex/filesystem/fs/set.h"
#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"

#include "aura/graphics/image/list.h"
#include "aura/message/user.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/copydesk.h"
#include "aura/user/user/button.h"
#include "aura/user/user/plain_edit.h"
#include "aura/user/user/interaction_array.h"
#include "aura/user/user/shell.h"
#include "aura/user/menu/command.h"
#include "base/user/menu/item.h"
#include "base/user/menu/item_ptra.h"
#include "base/user/menu/menu.h"
#include "core/filesystem/userfs/list_data.h"
#include "core/filesystem/userfs/list_item.h"
#include "core/filesystem/userfs/list_item_array.h"
#include "core/user/user/user.h"
#include "core/user/user/list_column.h"
#include "core/platform/application.h"
#include "core/platform/session.h"


namespace filemanager
{


   file_list::file_list()
   {

      m_bStatic = false;
      m_bFileSize = false;
      m_bShow = false;
      m_bHoverSelect2 = true;

   }


   file_list::~file_list()
   {

   }


   void file_list::initialize_impact(::user::document * pdocument)
   {

      ::filemanager_show < ::userfs::list >::initialize_impact(pdocument);

   }


   void file_list::install_message_routing(::channel * pchannel)
   {

      impact::install_message_routing(pchannel);

      ::user::form_list::install_message_routing(pchannel);

      ::userfs::list::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_scroll_x, pchannel, this, &file_list::on_message_scroll_x);
      MESSAGE_LINK(e_message_scroll_y, pchannel, this, &file_list::on_message_scroll_y);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &file_list::on_message_context_menu);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &file_list::on_message_show_window);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &file_list::on_message_set_focus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &file_list::on_message_kill_focus);

      add_command_prober("edit_copy", { this,  &file_list::_001OnUpdateEditCopy });
      add_command_handler("edit_copy", { this,  &file_list::_001OnEditCopy });
      add_command_prober("trash_that_is_not_trash", { this,  &file_list::_001OnUpdateTrashThatIsNotTrash });
      add_command_handler("trash_that_is_not_trash", { this,  &file_list::_001OnTrashThatIsNotTrash });
      add_command_prober("open_with", { this,  &file_list::_001OnUpdateOpenWith });
      //add_command_prober("spafy", &file_list::_001OnUpdateSpafy);
      //add_command_handler("spafy", &file_list::_001OnSpafy);
      //add_command_prober("spafy2", &file_list::_001OnUpdateSpafy2);
      //add_command_handler("spafy2", &file_list::_001OnSpafy2);
      add_command_prober("file_rename", { this,  &file_list::_001OnUpdateFileRename });
      add_command_handler("file_rename", { this,  &file_list::_001OnFileRename });
      add_command_handler("file_open", { this,  &file_list::_001OnFileOpen });

   }


//   void file_list::assert_ok() const
////   {
////
////      ::user::impact::assert_ok();
////
////   }
////
////
////   void file_list::dump(dump_context & dumpcontext) const
////   {
////
////      ::user::impact::dump(dumpcontext);
////
////   }


   bool file_list::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      if (::is_item(pitem, m_iNameSubItem) ||
         ((m_eview == impact_list || m_eview == impact_report)))
         //&& subitem_less_than(pitem, 0)))
      {

         if (!_017OpenSelected(true, ::e_source_user))
         {

            ::collection::index iStrict = pitem->m_item.m_iItem;

            auto pitem = fs_list_item(iStrict);

            _017OpenItem(pitem, true, ::e_source_user);

         }

      }

      return ::user::list::on_click(pitem, pmouse);

   }


   bool file_list::on_right_click(::item * pitem, ::user::mouse * pmouse)
   {

      if(::is_set(pitem))
      {

         _017OpenContextMenuSelected(::e_source_user);

      }
      else
      {

         _017OpenContextMenu(::e_source_user);

      }

      return true;

   }


   void file_list::RenameFile(int iLine, string &wstrNameNew, const ::action_context & context)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization());

      ::file::path filepath = fs_list_item(iLine)->final_path();

      ::file::path filepathNew = filepath.folder() / wstrNameNew;

      // auto pcontext = get_context();

      file()->rename(filepathNew, filepath);

      browse_sync(context);

   }


   void file_list::on_message_context_menu(::message::message * pmessage)
   {

      ::pointer<::message::mouse>pcontextmenu(pmessage);

      synchronous_lock synchronouslock(fs_list()->synchronization());

      ::collection::index iItem;

      auto point = pcontextmenu->m_pointHost;

      ::user::list::host_to_client()(point);

      if (_001HitTest_(point, iItem))
      {

         if (fs_list_item((::collection::index) iItem)->IsFolder())
         {

            _017OpenContextMenuFolder(fs_list_item((::collection::index) iItem), ::e_source_user);

         }
         else
         {

            auto pcontext = m_papplication;
            
            auto psession = pcontext->m_psession;
            
            auto puser = psession->m_puser;

            auto pointCursor = pcontextmenu->m_pointHost;
            
            auto r = ::int_rectangle::square_with_center_and_apothem(point, 8);

//            host_to_client()(point);
            
            auto pusermenu = user()->menu_from_xml(this, filemanager_data()->m_strXmlPopup);
            
            auto ptrackpopup = ___new ::menu::track_popup(
                                                             pusermenu,
                                                             this,
                                                             this,
                                                             pointCursor,
                                                             r);

            puser->track_popup_menu(ptrackpopup);

         }

      }
      else
      {

         auto pcontext = m_papplication;
         
         auto psession = pcontext->m_psession;
         
         auto puser = psession->m_puser;

         auto pointCursor = pcontextmenu->m_pointHost;

         auto r = ::int_rectangle::square_with_center_and_apothem(point, 8);
         
         auto pmenu = puser->menu_from_xml(this, filemanager_data()->m_strXmlPopup);
         
         auto ptrackpopup = __initialize_new ::menu::track_popup(
                                                             pmenu,
                                                             this,
                                                             this,
                                                               pointCursor,
                                                             r);

         puser->track_popup_menu(ptrackpopup);

      }

   }


   bool file_list::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP



#endif

      return ::user::impact::pre_create_window(pusersystem);

   }


   //void file_list::FileSize()
   //{

   //   if (m_bFileSize)
   //   {

   //      return;

   //   }

   //   m_bFileSize = true;

   //   db_server * pcentral = dynamic_cast <db_server *> (psystem->m_psimpledb->db());

   //   if (pcentral == nullptr)
   //   {

   //      return;

   //   }

   //   DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;

   //   int i;

   //   while (::task_get_run())
   //   {

   //      i = 0;

   //      while (i < fs_list()->m_pitema->get_count() || is_window_visible())
   //      {

   //         huge_integer i64Size;

   //         bool bPendingSize;

   //         single_lock lock(get_app()->mutex());

   //         if (!lock.lock(::time(2000)))
   //         {

   //            break;

   //         }

   //         if (i >= fs_list()->m_pitema->get_count())
   //         {

   //            i = 0;

   //         }

   //         bPendingSize = false;

   //         try
   //         {

   //            pset->get_fs_size(i64Size, fs_list_item(i)->get_user_path(), bPendingSize);

   //         }
   //         catch (...)
   //         {

   //         }

   //         lock.unlock();

   //         i++;

   //         sleep(23_ms);

   //      }

   //      sleep(100_ms);

   //   }

   //   m_bFileSize = false;

   //}


   void file_list::on_timer(::timer * ptimer)
   {

      ::userfs::list::on_timer(ptimer);

      if (ptimer->m_uTimer == 888888)
      {

         auto psession = session();

         if (filemanager_data()->m_bSetBergedgeTopicFile)
         {

            auto patha = get_selected_user_path();

            if (patha.is_empty())
            {

               psession->m_varTopicFile.unset();

            }
            else if (patha.get_count() == 1)
            {

               psession->m_varTopicFile = patha[0];

            }
            else
            {

               psession->m_varTopicFile = (const string_array &) patha;

            }

         }
         else
         {
            KillTimer(888888);
         }
      }

   }


   void file_list::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      auto itema = get_selected_items();

      if (filemanager_document()->HandleDefaultFileManagerItemCmdMsg(pcommand, itema))
      {

         pcommand->m_bRet = true;

         return;

      }

      ::user::impact::route_command(pcommand);

   }


   void file_list::_001OnShellCommand(::message::message * pmessage)
   {
      ::pointer<::user::message>pcommand(pmessage);
      m_pcontextmenu->OnCommand(pcommand->GetId());
   }

   void file_list::_001OnFileManagerItemCommand(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      ::file::item_array itema;

      ::collection::index iItemRange, iItem;

      ::user::range range;

      get_selection(range);

      for (iItemRange = 0;
            iItemRange < range.get_item_count();
            iItemRange++)
      {

         auto & itemrange = range.ItemAt(iItemRange);

         for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            itema.add(fs_list_item(iItem));

         }

      }

      filemanager_document()->on_file_manager_item_command(pcommand->command_id(), itema);

   }


   void file_list::_001OnFileManagerItemUpdate(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      synchronous_lock synchronouslock(fs_list()->synchronization());

      ::file::item_array itema;

      ::collection::index iItemRange, iItem;

      ::user::range range;

      get_selection(range);

      for (iItemRange = 0; iItemRange < range.get_item_count(); iItemRange++)
      {

         auto & itemrange = range.ItemAt(iItemRange);

         for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            itema.add(fs_list_item(iItem));

         }

      }

      filemanager_document()->on_file_manager_item_update(pcommand, itema);

      pmessage->m_bRet = true;

   }


   void file_list::_017OpenContextMenuFolder(::pointer<::file::item> item, const ::action_context & context)
   {

      string_array straCommand;

      string_array straCommandTitle;

      filemanager_document()->on_file_manager_open_context_menu_folder(item, straCommand, straCommandTitle, context);

      if (straCommand.get_size() > 0)
      {

         auto pmenu = __create_new < ::user::menu >();

         if (pmenu->create_menu(straCommand, straCommandTitle))
         {
            
            auto ptrackpopup = __initialize_new ::menu::track_popup(
                                                             pmenu,
                                                             this,
                                                             this);

            //pmenu->track_popup_menu(parent_frame());
            
            ptrackpopup->track([](){});

         }

      }

   }


   void file_list::_017OpenContextMenuFile(const ::file::item_array & itema, const ::action_context & context)
   {

      filemanager_document()->on_file_manager_open_context_menu_file(itema, context);

   }


   void file_list::_017OpenContextMenu(const ::action_context & context)
   {

      filemanager_document()->on_file_manager_open_context_menu(context);

   }


   //void file_list::_017OpenFolder(::pointer<::file::item>pitem, const ::action_context & context)
   //{

   //   filemanager_data()->browse(pitem, context);

   //}


   void file_list::_017OpenFile(const ::file::item_array & itema, const ::action_context & context)
   {

      filemanager_document()->on_file_manager_open(itema, context);

   }


   void file_list::_001OnFileRename(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      ::user::range range;

      get_selection(range);

      if (range.get_item_count() == 1 && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound())
      {

         ::collection::index iEditItem = range.ItemAt(0).get_lower_bound();

         ::user::interaction * pinteraction = _001GetControl(iEditItem, m_iNameSubItem);

         _001PlaceControl(pinteraction, iEditItem);

      }

   }


   void file_list::_001OnFileOpen(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      _017OpenSelected(true, ::e_source_user);

   }


   void file_list::_001OnUpdateFileRename(::message::message * pmessage)
   {
      //      ::pointer<::message::command>pcommand(pmessage);
      //    pcommand->enable(_001GetSelectedItemCount() == 1);
      //  pmessage->m_bRet = true;

      ::pointer<::message::command>pcommand(pmessage);
      ::user::range range;
      get_selection(range);
      pcommand->enable(
      range.get_item_count() == 1
      && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound());
      pmessage->m_bRet = true;

   }


   void file_list::_001OnUpdateEditCopy(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      ::user::range range;

      get_selection(range);

      pcommand->enable(range.get_item_count() > 0);

      pmessage->m_bRet = true;

   }


   void file_list::_001OnEditCopy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto patha = get_selected_final_path();

      auto pcopydesk = copydesk();

      pcopydesk->set_filea(patha, ::user::copydesk::e_op_copy);

      pmessage->m_bRet = true;

   }


   void file_list::_001OnUpdateTrashThatIsNotTrash(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      ::user::range range;

      get_selection(range);

      pcommand->enable(range.get_item_count() > 0);

      pmessage->m_bRet = true;

   }


   void file_list::_001OnTrashThatIsNotTrash(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto patha = get_selected_final_path();

      // auto pcontext = get_context();

      file()->trash_that_is_not_trash(patha);

      _001Refresh();

      pmessage->m_bRet = true;

   }


   void file_list::_001OnUpdateOpenWith(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      ::pointer<::menu::command>pmenucommandui(pcommand);

      if (pmenucommandui)
      {

         auto pitema = pmenucommandui->m_pitema;

         auto pmenu = pitema->element_at(pmenucommandui->m_iIndex)->m_pmenu;

         pitema->erase_at(pcommand->m_iIndex);

         ::collection::index iStartIndex = pcommand->m_iIndex;

         ::collection::index iIndex = iStartIndex;

         auto patha = get_selected_final_path();

         ::file::path strPath = patha.first();

         string strExt = strPath.final_extension();

         string_array stra;

         // auto pcontext = get_context();

         node()->file_extension_get_open_with_list_keys(stra, strExt);

         m_straOpenWith = stra;

         ::collection::count iCount = stra.get_size();

         string str;

         for (int i = 0; i < iCount; i++)
         {

            auto pmenuitem = __create_new < ::menu::item > ();

            pmenuitem->id() = "open with" + stra[i];

            if (pmenuitem->m_puserinteraction != nullptr)
            {

               pmenuitem->m_puserinteraction->set_window_text(stra[i]);

            }

            pmenuitem->m_iLevel = pitema->m_pitemParent != nullptr ? pitema->m_pitemParent->m_iLevel + 1 : 0;

            pmenuitem->m_pmenu = pmenu;

            pitema->insert_at(iIndex, pmenuitem);

            iIndex++;

         }

         pcommand->m_iIndex = iStartIndex;

         pcommand->m_iCount += iCount - 1;

         ::collection::index iNewIndex = iStartIndex + iCount - 1;

         pmenucommandui->m_iIndex = iNewIndex;

         pmenu->set_need_layout();

      }

      pmessage->m_bRet = true;

   }


   void file_list::on_command_probe(::message::command * pcommand)
   {

      int iPos = -1;

      for (int i = 0; i < m_straOpenWith.get_size(); i++)
      {

         string strId = "open with" + m_straOpenWith[i];

         if (pcommand->command_id() == strId)
         {

            iPos = i;

            break;

         }

      }

      if (iPos >= 0)
      {

         pcommand->enable(true);

         pcommand->m_bRet = true;

         return;

      }

      ::user::impact::on_command_probe(pcommand);

   }


   void file_list::on_command(::message::command * pcommand)
   {

      if (pcommand->command_id() == "1000")
      {

         //      _017OpenSelected(true, ::e_source_user);

         pcommand->m_bRet = true;

         return;

      }

      int iPos = -1;

      for (int i = 0; i < m_straOpenWith.get_size(); i++)
      {

         string strId = "open with" + m_straOpenWith[i];

         if (pcommand->command_id() == strId)
         {

            iPos = i;

            break;

         }

      }

      if (iPos >= 0)
      {

         auto patha = get_selected_final_path();

         ::file::path pathUser = patha.first();

         // auto pcontext = get_context();

         node()->file_open(pathUser);

         pcommand->m_bRet = true;

         return;

      }

      ::user::impact::on_command(pcommand);

   }


   //void file_list::_001OnUpdateSpafy(::message::message * pmessage)
   //{
   //   ::pointer<::message::command>pcommand(pmessage);
   //   ::user::range range;
   //   get_selection(range);
   //   pcommand->enable(range.get_item_count() > 0);
   //   pmessage->m_bRet = true;
   //}


   //void file_list::_001OnSpafy(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //   auto itema = get_selected_items();

   //   string_array stra;

   //   ::file::listing straSub;

   //   string strFileList;
   //   string strFileCheck;
   //   for (int i = 0; i < itema.get_size(); i++)
   //   {

   //      if (directory()->is(itema[i]->m_filepathFinal) && strcmp(itema[i]->m_filepathFinal.name(), ".svn"))
   //      {

   //         straSub.rls(itema[i]->m_filepathFinal);

   //         for (int j = 0; j < straSub.get_size(); j++)
   //         {
   //            if (!directory()->is(straSub[j]) && straSub[j].find(".svn") < 0)
   //            {
   //               strFileList += straSub[j] + "\n";
   //               strFileCheck += straSub[j] + ",";
   //               strFileCheck += file()->length(straSub[j]).get_string() + ",";
   //               strFileCheck += file()->md5(straSub[j]) + "\n";
   //            }
   //         }
   //      }
   //      else
   //      {
   //         strFileList += itema[i]->m_filepathUser + "\n";
   //         strFileCheck += itema[i]->m_filepathUser + ",";
   //         strFileCheck += file()->length(itema[i]->m_filepathFinal).get_string() + ",";
   //         strFileCheck += file()->md5(itema[i]->m_filepathFinal) + "\n";
   //      }
   //   }

   //   ::earth::time time = ::earth::time::now();

   //   string strTime;

   //   strTime.formatf("%04d-%02d-%02d %02d-%02d",
   //                  time.GetYear(),
   //                  time.GetMonth(),
   //                  time.GetDay(),
   //                  time.GetHour(),
   //                  time.GetMinute());

   //   string strBase = filemanager_item()->m_filepathUser / "spafy_";

   //   string strList = strBase + "list_" + strTime + ".txt";
   //   string strCheck = strBase + "check_" + strTime + ".txt";


   //   file()->put_contents(strList, strFileList);
   //   file()->put_contents(strCheck, strFileCheck);

   //}

   //void file_list::_001OnUpdateSpafy2(::message::message * pmessage)
   //{
   //   ::pointer<::message::command>pcommand(pmessage);
   //   pcommand->enable(true);
   //   pmessage->m_bRet = true;
   //}


   //void file_list::_001OnSpafy2(::message::message * pmessage)
   //{

   //   synchronous_lock synchronouslock(fs_list()->synchronization());

   //   ::pointer<::userfs::list_data>pdata = fs_list();
   //
   //   __UNREFERENCED_PARAMETER(pmessage);
   //
   //   string_array stra;
   //
   //   ::file::listing straSub(get_context());

   //   string strFileList;

   //   string strFileCheck;

   //   for (int i = 0; i < pdata->m_pitema->get_count(); i++)
   //   {

   //      if (fs_data()->is_dir(pdata->item(i)->m_filepathFinal)
   //            && strcmp(pdata->item(i)->m_filepathFinal.name(), ".svn"))
   //      {

   //         straSub.rls(pdata->item(i)->m_filepathFinal);

   //         for (int j = 0; j < straSub.get_size(); j++)
   //         {

   //            string strExtension = straSub[j].extension();

   //            if (!directory()->is(straSub[j])
   //                  && (strExtension == "exe" || strExtension == "dll" || strExtension == "dll.manifest"
   //                      || strExtension == "exe.manifest"))
   //            {

   //               strFileList += straSub[j] + "\n";
   //               strFileCheck += straSub[j] + ",";
   //               strFileCheck += file()->length(straSub[j]).get_string() + ",";
   //               strFileCheck += file()->md5(straSub[j]) + "\n";

   //            }

   //         }
   //      }
   //      else
   //      {

   //         string strExtension = pdata->item(i)->m_filepathUser.extension();

   //         if (strExtension == "exe" || strExtension == "dll" || strExtension == "dll.manifest"
   //               || strExtension == "exe.manifest")
   //         {

   //            strFileList += pdata->item(i)->m_filepathUser + "\n";
   //            strFileCheck += pdata->item(i)->m_filepathUser + ",";
   //            strFileCheck += file()->length(pdata->item(i)->m_filepathFinal).get_string() + ",";
   //            strFileCheck += file()->md5(pdata->item(i)->m_filepathFinal) + "\n";

   //         }

   //      }

   //   }

   //   ::earth::time time = ::earth::time::now();

   //   string strTime;

   //   strTime.formatf("%04d-%02d-%02d %02d-%02d",
   //                  time.GetYear(),
   //                  time.GetMonth(),
   //                  time.GetDay(),
   //                  time.GetHour(),
   //                  time.GetMinute());

   //   string strBase = filemanager_item()->m_filepathUser / "spafy_";

   //   string strList = strBase + "list_" + strTime + ".txt";

   //   string strCheck = strBase + "check_" + strTime + ".txt";

   //   file()->put_contents(strList, strFileList);

   //   file()->put_contents(strCheck, strFileCheck);

   //}


   void file_list::_001OnAfterSort()
   {

      data_set_DisplayToStrict();

   }


   //::pointer<::fs::data>file_list::fs_data()
   //{

   //   return ::userfs::list::fs_data();

   //}


   //void file_list::schedule_file_size(const ::string & psz)
   //{

   //   __UNREFERENCED_PARAMETER(psz);

   //   if (!is_window_visible())
   //   {

   //      return;

   //   }

   //}


   void file_list::on_message_show_window(::message::message * pmessage)
   {

      //::pointer<::message::show_window>pshowwindow(pmessage);

      __UNREFERENCED_PARAMETER(pmessage);

   }


   atom file_list::data_get_current_list_layout_id()
   {

      return filemanager_item()->user_path();

   }


   void file_list::browse_sync(const ::action_context & context)
   {

      if (m_bStatic)
      {

         ::userfs::list_item item;

         string_array stra;

         auto papp = ::filemanager_impact_base::get_app();

         ::cast < ::database::client > pdatabaseclient = papp;

         pdatabaseclient->datastream()->get(filemanager_data()->m_strDataKeyStatic, stra);

         synchronous_lock lock(fs_list()->synchronization());

         fs_list()->m_pitema->erase_all();

         for (int i = 0; i < stra.get_size(); i++)
         {

            item.m_flags.clear();

            ::file::path pathItem = stra[i];

            if (directory()->is(pathItem))
            {

               item.m_flags.add(::file::e_flag_folder);

            }

            ::file::path strPath = stra[i];

            string strName = strPath.name();

            item.set_user_path(strPath);

            item.set_final_path(m_papplication->defer_process_matter_path(strPath));

            item.m_strName = strName;

            fs_list()->m_pitema->add_fs_item(item);

         }

         update_impact();

         return;

      }

      if (filemanager_data()->m_bSetBergedgeTopicFile)
      {

         SetTimer(888888, 230_ms, nullptr);

      }

      set_context_offset({0,0});

      string_array straStrictOrder;

//      papp->datastream()->get(data_get_current_sort_id() + "." +  data_get_current_list_layout_id() + ".straStrictOrder", straStrictOrder);

      index_biunique iaDisplayToStrict;

      ::pointer<icon_layout>piconlayout;

      __construct_new(piconlayout);

//      papp->datastream()->get(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), piconlayout);

      iaDisplayToStrict = piconlayout->m_iaDisplayToStrict;

      index_biunique iaDisplayToStrictNew;

      ::userfs::list_item item;

      string strParent = filemanager_path();

      ::file::path pathParentEx = filemanager_item()->user_path();

      pathParentEx = filemanager_path();

      //int iMaxSize;

      //iMaxSize = 1000;

      //int iSize;

      //iSize = 0;

      m_pathaStrictOrder.erase_all();

      update_impact();

      // auto pcontext = get_context();

      {

         auto pparticleSynchronization = fs_list()->synchronization();

         synchronous_lock lock(pparticleSynchronization);

         ::file::listing & listingUser = filemanager_data()->m_listingUser2;

         ::file::listing & listingFinal = filemanager_data()->m_listingFinal2;

         auto cItem = listingUser.get_size();

         fs_list()->m_pitema->set_size(cItem);

         m_pathaStrictOrder = listingUser;

         for (int i = 0; i < cItem; i++)
         {

            auto & spitem = (*fs_list()->m_pitema)[i];

            spitem.create_new(this);

            ::file::path pathFinal = listingFinal[i];

            pathFinal = m_papplication->defer_process_matter_path(pathFinal);

            pathFinal.set_type(listingFinal[i].type());

            if (pathFinal.not_file_or_folder())
            {

               pathFinal.set_type(fs_data()->file_type(pathFinal));

            }

            if (pathFinal.set_existent_folder())
            {

               spitem->m_flags.add(::file::e_flag_folder);

            }

            spitem->set_user_path(listingUser[i]);

            spitem->set_final_path(pathFinal);

            spitem->m_strName = listingUser.name(i);

            //if (spitem->m_strName.case_insensitive_contains("aaa."))
            //{

            //   informationf("test filemanager file_list");

            //}

         }

      }

      update_impact();

      {

         synchronous_lock lock(fs_list()->synchronization());

         if (m_eview == impact_icon)
         {
            /*   // primeiro, todos System arquivos que foram removidos
            // ou seja, que existem no array antigo,
            // mas nao existe no novo.
            for(index strictOld = 0; strictOld < straStrictOrder.get_count(); strictOld++)
            {
            string str = straStrictOrder[strictOld];
            ::collection::index find = m_pathaStrictOrder.find_first(str);
            if(find < 0)
            {
            iaDisplayToStrictNew.erase_b(strictOld);
            }
            }*/
            // segundo, reordena conforme a
            // ordem que a listagem de arquivos fornecida pelo
            // sistema operacional pode ser fornecida.
            for (::collection::index strictNew = 0; strictNew < m_pathaStrictOrder.get_count(); strictNew++)
            {
               string str = m_pathaStrictOrder[strictNew];
               ::collection::index strictOld = straStrictOrder.find_first(str);
               if (strictOld >= 0)
               {
                  ::collection::index iDisplay = iaDisplayToStrict.get_a(strictOld);
                  iaDisplayToStrictNew.set(iDisplay, strictNew);
               }
            }
            // terceiro, adiciona System novos arquivos nos primeiros espacos
            // vazios
            for (::collection::index strictNew = 0; strictNew < m_pathaStrictOrder.get_count(); strictNew++)
            {
               string str = m_pathaStrictOrder[strictNew];
               ::collection::index strictOld = straStrictOrder.find_first(str);
               if (strictOld < 0)
               {
                  iaDisplayToStrictNew.add_b_in_first_free_a(strictNew);
               }
            }
            m_piconlayout->m_iaDisplayToStrict = iaDisplayToStrictNew;
         }
         else
         {
            fs_list()->m_pitema->arrange(::fs::arrange_by_name);
         }

      }

      ///      _001CreateImageList();

      //file_size_add_request(true);
      /*   for(int i = 0; i < m_pitema->get_item_count(); i++)
      {
      pset->m_table.add_request(item(i)->m_strPath);
      }*/
      //if (m_eview == impact_icon)
      //{
         //papp->datastream()->set(data_get_current_sort_id() + "." + data_get_current_list_layout_id() + ".straStrictOrder", m_pathaStrictOrder);
         //m_piconlayout->m_iaDisplayToStrict = iaDisplayToStrictNew;
         //data_set_DisplayToStrict();
      //}

      clear_selection();

      //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
        // {

           // set_context_offset(pgraphics, 0, 0);

      //set_context_offset(pgraphics, 0, 0);

      set_context_offset({});

         //});

      set_need_layout();

      set_need_redraw();

   }


   void file_list::on_insert_columns()
   {

      if (filemanager_document() == nullptr)
      {

         return;

      }

      auto pcontext = m_papplication;

      if (filemanager_data()->m_bIconImpact)
      {

         m_eview = impact_icon;

      }

      int iCount = 0;

      file_list_callback * pcallback = filemanager_data()->m_pfilelistcallback;

      if (pcallback != nullptr)
      {

         iCount = pcallback->GetActionButtonCount();

      }

      ::collection::index i;

      for (i = 0; i < iCount; i++)
      {

         //index iControl;

         ::atom atom = 1000 + i;

         {

            auto pinteraction = __create_new <  user::button > ();
            pinteraction->m_bTransparent = true;
            //pinteraction->set_control_type(user::e_control_type_button);
            //pinteraction->m_type = ::type < ::user::button >();
            pinteraction->id() = atom;
            pinteraction->add_function(user::e_control_function_action);
            _001AddControl(pinteraction);

         }

         {

            auto pcolumn = new_list_column();

            pcolumn->m_iWidth = 18;
            pcolumn->m_iSubItem = i;
            pcolumn->id() = atom;
            pcolumn->m_bCustomDraw = true;
            pcolumn->m_bEditOnSecondClick = true;
            pcolumn->m_pimagelist = pcallback->GetActionButtonImageList(i);

         }

      }

      if (filemanager_data()->m_bListSelection)
      {

         m_iSelectionSubItem = i;
         m_iIconSubItem = m_iSelectionSubItem;
         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = filemanager_data()->m_iIconSize;
         //pcolumn->m_bIcon                = true;
         pcolumn->m_sizeIcon.cx() = filemanager_data()->m_iIconSize;
         pcolumn->m_sizeIcon.cy() = filemanager_data()->m_iIconSize;
         //pcolumn->m_iControl = -1;
         pcolumn->m_strDataKey = "FILE_MANAGER_ID_FILE_NAME";
         pcolumn->m_bEditOnSecondClick = false;

         auto pcontext = m_papplication;
         
         auto psession = pcontext->m_psession;
         
         auto puser = psession->m_puser;

         pcolumn->m_pimagelist = puser->shell()->GetImageList(get_document()->m_iIconSize);
         pcolumn->m_pimagelistHover = puser->shell()->GetImageListHover(get_document()->m_iIconSize);
         pcolumn->m_iSubItem = m_iSelectionSubItem;
         i++;
      }
      else
      {
         m_iSelectionSubItem = -1;
      }

      bool bRenameEdit = false;

      {

         auto pcolumn = new_list_column();

         if (bRenameEdit)
         {

            auto pinteraction = __create_new <  user::plain_edit > ();
            //pinteraction->set_control_type(user::e_control_type_edit_plain_text);
            pinteraction->m_strDataKey20 = "FILE_MANAGER_ID_FILE_NAME";
            //pinteraction->id() = _vms::FILE_MANAGER_ID_FILE_NAME;
            pinteraction->set_data_type(user::e_control_data_type_string);
            pinteraction->add_function(user::e_control_function_vms_data_edit);
            pinteraction->m_typeatom = ::type < ::user::plain_edit >();
            //pinteraction->m_iSubItem = i;
            pinteraction->id() = 1000 + i;
            ::collection::index iControl = _001AddControl(pinteraction);
            pcolumn->id() = pinteraction->id();

         }



         m_iNameSubItem = i;
         m_iIconSubItem = m_iNameSubItem;
         pcolumn->m_iSubItem = m_iNameSubItem;
         if (filemanager_data()->m_bListText)
         {
            m_iNameSubItemText = i;
            pcolumn->m_iWidth = 500;
         }
         else
         {
            m_iNameSubItemText = i;
            pcolumn->m_iWidth = get_document()->m_iIconSize;
         }
         auto plistdata = fs_list();
         plistdata->m_iNameSubItemText = m_iNameSubItemText;
         //pcolumn->m_bIcon                = true;
         pcolumn->m_sizeIcon.cx() = get_document()->m_iIconSize;
         pcolumn->m_sizeIcon.cy() = get_document()->m_iIconSize;
         pcolumn->m_text = pcontext->__text("file:Name");
         pcolumn->m_strDataKey = "FILE_MANAGER_ID_FILE_NAME";
         pcolumn->m_bEditOnSecondClick = true;
         int iIconSize = get_document()->m_iIconSize;

         auto pcontext = m_papplication;
         
         auto psession = pcontext->m_psession;
         
         auto puser = psession->m_puser;

         pcolumn->m_pimagelist = puser->shell()->GetImageList(iIconSize);

         pcolumn->m_pimagelistHover = puser->shell()->GetImageListHover(iIconSize);

      }

      i++;

      if (filemanager_data()->m_bFileSize)
      {

         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 100;

         pcolumn->m_iSubItem = i;

         m_iSizeSubItem = i;

         fs_list()->m_iSizeSubItem = m_iSizeSubItem;

         pcolumn->m_text = pcontext->__text("file:Size");

         pcolumn->m_sizeIcon.cx() = 0;

         pcolumn->m_sizeIcon.cy() = 0;

         pcolumn->m_pimagelistHover = nullptr;

         pcolumn->m_pimagelist = nullptr;


      }

   }


   void file_list::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      if (m_bStatic)
      {

         return ::user::list::_001GetSubItemText(psubitem);

      }

      return ::userfs::list::_001GetSubItemText(psubitem);

   }


   void file_list::_001GetSubItemImage(::user::mesh_subitem * psubitem)
   {

      return ::userfs::list::_001GetSubItemImage(psubitem);

   }



   //void file_list::_001OnMainPostMessage(::message::message * pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //   switch (pusermessage->m_wparam)
   //   {
   //   case MessageMainPostCreateImageListItemStepSetRedraw:
   //   {
   //      ::time tickNow= ::time::now();
   //      if (tickNow - m_timeLastRedraw > 784)
   //      {
   //         m_timeLastRedraw = tickNow;
   //         set_need_redraw();
   //      }
   //   }
   //   break;
   //   case MessageMainPostCreateImageListItemRedraw:
   //   {
   //      set_need_redraw();
   //   }
   //   break;
   //   }

   //   pusermessage->set_lresult(0);

   //   pusermessage->m_bRet = true;

   //}


   void file_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_list::_001OnDraw(pgraphics);

   }


   //void file_list::TakeAnimationSnapshot()
   //{

   //}


   //void file_list::_017OpenSelected(bool bOpenFile, const ::action_context & context)
   //{

   //   ::file::item_array itema;

   //   index iItemRange, iItem;

   //   ::user::range range;

   //   get_selection(range);

   //   for (iItemRange = 0; iItemRange < range.get_item_count(); iItemRange++)
   //   {

   //      auto & itemrange = range.ItemAt(iItemRange);

   //      for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
   //      {

   //         if (iItem < 0)
   //         {

   //            continue;

   //         }

   //         if (iItem >= _001GetItemCount())
   //         {

   //            continue;

   //         }

   //         index iStrict;

   //         if (m_eview == impact_icon)
   //         {

   //            iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);

   //         }
   //         else
   //         {

   //            iStrict = m_meshlayout.m_iaDisplayToStrict[iItem];

   //         }

   //         ::pointer<::userfs::list_item>pitem = fs_list_item(iStrict);

   //         if (pitem->IsFolder())
   //         {

   //            _017OpenFolder(pitem, context) + ::e_source_selection;

   //            break;

   //         }
   //         else
   //         {

   //            itema.add(pitem);

   //         }

   //      }

   //   }

   //   if (bOpenFile && itema.get_size() > 0)
   //   {

   //      _017OpenFile(itema, context) + ::e_source_selection;

   //   }

   //   clear_selection();

   //}


   void file_list::_017OpenContextMenuSelected(const ::action_context & context)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization());

      ::file::item_array itema;

      ::collection::index iItemRange, iItem;

      ::user::range range;

      get_selection(range);

      for (iItemRange = 0; iItemRange < range.get_item_count(); iItemRange++)
      {

         auto & itemrange = range.ItemAt(iItemRange);

         for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            if (iItem < 0)
            {

               continue;

            }

            if (iItem >= fs_list()->m_pitema->get_count())
            {

               continue;

            }

            ::collection::index iStrict = display_to_strict(iItem);

            if (fs_list_item(iStrict)->IsFolder())
            {

               _017OpenContextMenuFolder(fs_list_item(iStrict), context);

               break;

            }
            else
            {

               itema.add(fs_list_item(iStrict));

            }

         }

      }

      if (itema.get_size() > 0)
      {
         _017OpenContextMenuFile(itema, context);
      }
      else
      {
         _017OpenContextMenu(context);
      }
      clear_selection();
   }


   void file_list::_001OnInitializeForm(::user::interaction * pinteraction)
   {

      ASSERT(pinteraction != nullptr);

      if (pinteraction == nullptr)
      {

         return;

      }

      file_list_callback * pcallback = filemanager_data()->m_pfilelistcallback;

      ::pointer<::user::button>pbutton = pinteraction;

      if (pcallback != nullptr && pbutton != nullptr)
      {

         pbutton->set_button_style(::user::button::e_style_list);

         pcallback->InitializeActionButton(pinteraction->id().as_int() - 1000, pbutton);

      }

   }


   void file_list::_001OnButtonAction(::user::interaction * pinteraction)
   {

      file_list_callback * pcallback = filemanager_data()->m_pfilelistcallback;

      if (::is_set(pcallback))
      {

         ::file::item item;

         ::collection::index iItem = pinteraction->m_item.m_iItem;

         ::collection::index iStrict = display_to_strict(iItem);

         pcallback->OnButtonAction(pinteraction->id(), fs_list_item(iStrict));

      }

   }


   //void file_list::GetSelected(::file::item_array &itema)
   //{

   //   synchronous_lock synchronouslock(fs_list()->synchronization());

   //   index iItemRange, iItem;
   //   ::user::range range;
   //   get_selection(range);
   //   index_array iaItem;
   //   for (iItemRange = 0;
   //         iItemRange < range.get_item_count();
   //         iItemRange++)
   //   {
   //      auto & itemrange = range.ItemAt(iItemRange);
   //      for (iItem = maximum(0, itemrange.get_lower_bound());
   //            iItem <= itemrange.get_upper_bound();
   //            iItem++)
   //      {

   //         if (iItem < fs_list()->m_pitema->get_count() && !iaItem.contains(iItem))
   //         {

   //            iaItem.add(iItem);

   //            index iStrict = display_to_strict(iItem);

   //            itema.add(fs_list_item(iStrict));

   //         }

   //      }

   //   }

   //}


   void file_list::on_message_scroll_y(::message::message * pmessage)
   {

      //::pointer<::message::scroll>pscroll(pmessage);

      //m_iCreateImageListStep = pscroll->m_nPos;

      //m_bRestartCreateImageList = true;

      pmessage->m_bRet = false;

   }


   void file_list::on_message_scroll_x(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   ::collection::count file_list::_001GetItemCount()
   {

      return fs_list()->m_pitema->get_count();

   }


   bool file_list::add_fs_item(::file::path pathUser, ::file::path pathFinal, string strName)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization());

      ::userfs::list_item item;

      item.set_user_path(pathUser);

      item.set_final_path(pathFinal);

      item.m_strName = strName;

      // auto pcontext = get_context();

      if (directory()->is(pathFinal))
      {

         item.m_flags.add(::file::e_flag_folder);

      }

      fs_list()->m_pitema->add_fs_item(item);

      update_impact();

      return true;

   }


   ::image::image_list * file_list::GetActionButtonImageList(::collection::index i)
   {

      if (i == 0)
      {

         auto pcontext = m_papplication;
         
         auto psession = pcontext->m_psession;
         
         auto puser = psession->m_puser;

         return puser->shell()->GetImageList(get_document()->m_iIconSize);

      }

      return nullptr;

   }


   //void file_list::file_size_add_request(bool bClear)
   //{

   //   __UNREFERENCED_PARAMETER(bClear);

   //   db_server * pcentral = dynamic_cast <db_server *> (psystem->m_psimpledb->db());

   //   if (pcentral == nullptr)
   //   {

   //      return;

   //   }

   //   DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;

   //   single_lock synchronouslock(pset->m_table.mutex(), true);

   //   for (int i = 0; i < fs_list()->m_pitema->get_count(); i++)
   //   {

   //      //pset->get_cache_fs_size(iSize, item(i)->m_strPath, bPending);

   //   }

   //}


   void file_list::_001InitializeFormPreData()
   {

      auto pfilemanagerdata = filemanager_data();

      pfilemanagerdata->m_pfilemanagercallback->on_file_manager_initialize_form_pre_data(pfilemanagerdata, GetDlgCtrlId(), this);

   }


   bool file_list::query_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization());

      if (iDisplayDrag < 0)
         return false;
      if (iDisplayDrop < 0)
         return false;
      if (iDisplayDrag != iDisplayDrop)
      {

         ::collection::index iStrict = display_to_strict(iDisplayDrop);

         if (iStrict <= -1)
         {

            return true; // can drop in is_empty place

         }
         else if (iStrict >= _001GetItemCount())
         {

            return true; // can drop if destination is invalid

         }
         else
         {

            // can drop if destination is folder
            return fs_list_item(iStrict)->IsFolder();

         }

      }

      return false;

   }


   bool file_list::do_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization());

      ::collection::index strict = display_to_strict(iDisplayDrop);

      ::collection::index strictDrag = display_to_strict(iDisplayDrag);

      // auto pcontext = get_context();

      if (strict >= 0 && fs_list_item(strict)->IsFolder())
      {

         ::file::path strPath = fs_list_item(strictDrag)->final_path();

         string strName = strPath.name();

         file()->transfer(fs_list_item(strict)->final_path(), strPath);

      }
      else
      {

         ::user::list::do_drop(iDisplayDrop, iDisplayDrag);

      }

      return true;

   }


   //::color::color file_list::get_background_color()
   //{

   //   if (get_document() != nullptr && get_document()->is_topic())
   //   {
   //      return argb(255, 255, 255, 255);
   //      //::color32_t color32;
   //      //if (filemanager_data()->m_emode == document::mode_saving)
   //      //{

   //      //   color32 = argb(255, 255, 210, 180);

   //      //}
   //      //else if (filemanager_data()->m_emode == document::mode_import)
   //      //{

   //      //   color32 = argb(255, 180, 210, 255);

   //      //}
   //      //else if (filemanager_data()->m_emode == document::mode_export)
   //      //{

   //      //   color32 = argb(255, 255, 250, 210);

   //      //}
   //      //else
   //      //{

   //      //   color32 = argb(190, 210, 255, 180);

   //      //}
   //      //return color32;
   //   }
   //   else
   //   {

   //      return argb(255, 255, 255, 255);

   //   }

   //}


   void file_list::on_message_set_focus(::message::message * pmessage)
   {

      informationf("filemanager::file_list::on_message_set_focus");

   }


   void file_list::on_message_kill_focus(::message::message * pmessage)
   {

      informationf("filemanager::file_list::on_message_kill_focus");

   }


   void file_list::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      ::userfs::list::handle(ptopic, pcontext);

      auto papp = get_app();

      if (m_bStatic && ptopic->id() == id_add_location)
      {

         ::file::path_array filepatha;

         ::cast < ::database::client > pdatabaseclient = application();

         pdatabaseclient->datastream()->get(filemanager_data()->m_strDataKeyStatic, filepatha);

         //filepatha.add().stra());

         ::file::path filepath = filemanager_item()->user_path();

         filepath.trim();

         if (filepath.has_character() && fs_data()->is_dir(filepath))
         {

            if (filepatha.add_unique(filepath) >= 0)
            {

               string_array stra;

               ::generic::container::copy(stra, filepatha);

               pdatabaseclient->datastream()->set(filemanager_data()->m_strDataKeyStatic, stra);

               add_fs_item(filemanager_item()->user_path(),
                  filemanager_item()->final_path(), filemanager_item()->user_path().name());

               update_impact();

            }

         }

      }
      else if (ptopic->id() == id_impact_list)
      {

         _001SetImpact(impact_list);

      }
      else if (ptopic->id() == id_impact_report)
      {

         _001SetImpact(impact_report);

      }
      else if (ptopic->id() == id_impact_icon)
      {

         _001SetImpact(impact_icon);

      }

      if (ptopic->id() == id_initialize)
      {

         if (filemanager_data()->m_bPassBk)
         {

            ::user::list::m_bBackgroundBypass = true;

         }

         set_pending_column_update();

         update_impact();

      }
      else if (!m_bStatic && ptopic->id() == id_browse)
      {

         //if (ptopic->_extended_topic()->m_pfileitem->user_path() != filemanager_item()->user_path())
         //{

         //   return;

         //}

         //if (filemanager_data()->m_pholderFileList != nullptr)
         //{

         //   {

         //      synchronous_lock synchronouslock(mutex_draw());

         //      if (filemanager_data()->m_pholderFileList->m_puserinteractionpointeraChild->has_interaction())
         //      {

         //         filemanager_data()->m_pholderFileList->m_puserinteractionpointeraChild->interaction_at(0)->display(e_display_none);

         //      }

         //   }

         //   filemanager_data()->m_pholderFileList->place_hold(this);

         //   filemanager_data()->m_pholderFileList->set_need_layout();

         //}

         information() << "file_list handle id_browse";

         data_get_DisplayToStrict();

         update_impact();

         post_redraw();

      }
      else if (ptopic->id() == id_filter)
      {

         if (ptopic->payload(id_filter).is_empty())
         {

            FilterClose();

         }
         else
         {

            FilterBegin();

            Filter1(ptopic->payload(id_filter));

         }

      }
      else if (ptopic->id() == id_get_active_impact_selection)
      {

         if (parent_frame()->get_active_impact() == (this))
         {

            get_selected_items(*ptopic->cast <::file::item_array>(id_selected));

         }

      }
      else if (ptopic->id() == id_after_browse)
      {

         if (ptopic->payload(id_after_browse) == "filemanager\\replace_name_in_file_system.xhtml")
         {

            //html::matter * pelemental = dynamic_cast < html::matter * > (pupdate->m_pformview->get_html_data()->get_element_by_name("encontrar"));

            //html::impl::input_text * pinput = dynamic_cast < html::impl::input_text * > (pelemental->m_pimpl);

            ::pointer<::user::interaction>puserinteractionParent = ptopic->m_puserelement;

            auto pinteraction = puserinteractionParent->get_child_by_id("encontrar");

            auto pitem = get_first_selected_item();

            if (pitem)
            {

               pinteraction->set_text(ptopic->payload(id_name), ptopic->m_actioncontext);

            }

         }

         if (ptopic->id() == id_replace_name)
         {

            if (ptopic->payload(id_find).has_character())
            {

               // auto pcontext = get_context();

               ::file::path pathFolder = filemanager_item()->user_path();

               file()->replace_with(pathFolder, ptopic->payload(id_replace), ptopic->payload(id_find));

            }

         }
         else if (ptopic->id() == id_new_folder)
         {

            if (ptopic->payload(id_folder).has_character())
            {

               ::file::path pathFolder = filemanager_item()->user_path() / ptopic->payload(id_folder);

               // auto pcontext = get_context();

               directory()->create(pathFolder);

               ptopic->m_bRet = true;

            }

         }

      }

   }


} // namespace filemanager



