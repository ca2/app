#include "platform.h"
#include "context_menu.h"
#include "data.h"
#include "document.h"
#include "file_list.h"
#include "acme/constant/id.h"
#include "acme/constant/timer.h"
#include "acme/constant/user_message.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/user/interface/message_box.h"
//#include "acme/platform/timer.h"
#include "acme/prototype/collection/_array_binary_stream.h"
#include "acme/prototype/collection/_container.h"
#include "apex/database/_binary_stream.h"
#include "apex/filesystem/fs/data.h"
#include "apex/filesystem/fs/set.h"
#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"

#include "aura/graphics/image/list.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/copydesk.h"
#include "aura/user/user/button.h"
#include "aura/user/user/plain_edit.h"
#include "aura/user/user/interaction_array.h"
#include "aura/user/user/shell.h"
#include "aura/user/menu/command.h"
#include "berg/user/menu/item.h"
#include "berg/user/menu/item_ptra.h"
#include "berg/user/menu/menu.h"
#include "core/filesystem/userfs/list_data.h"
#include "core/filesystem/userfs/list_item.h"
#include "core/filesystem/userfs/list_item_array.h"
#include "core/user/user/user.h"
#include "core/user/user/list_column.h"
#include "core/platform/application.h"
#include "core/platform/session.h"


namespace filemanager
{
   constexpr ::enum_timer e_timer_folder_loading = (::enum_timer)0x67646c;


   file_list::file_list()
   {

      m_bStatic = false;
      m_bFileSize = false;
      m_bShow = false;
      m_bHoverSelect2 = true;
      m_iLeftMargin = 24;
      m_iRightMargin = 24;

   }


   file_list::~file_list()
   {

      set_inplace_watch_suppressed(false);

   }


   void file_list::initialize_impact(::user::document * pdocument)
   {

      ::filemanager_show < ::userfs::list >::initialize_impact(pdocument);

   }


   void file_list::install_message_routing(::channel * pchannel)
   {

      // The list overrides filemanager_show's routing setup, so install the
      // File Manager commands explicitly (in particular edit_paste).
      ::filemanager_impact_base::install_message_routing(pchannel);

      ::user::form_list::install_message_routing(pchannel);

      ::userfs::list::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_scroll_x, pchannel, this, &file_list::on_message_scroll_x);
      USER_MESSAGE_LINK(::user::e_message_scroll_y, pchannel, this, &file_list::on_message_scroll_y);
      USER_MESSAGE_LINK(::user::e_message_right_button_up, pchannel, this, &file_list::on_message_context_menu);
      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &file_list::on_message_show_window);
      USER_MESSAGE_LINK(::user::e_message_set_focus, pchannel, this, &file_list::on_message_set_focus);
      USER_MESSAGE_LINK(::user::e_message_kill_focus, pchannel, this, &file_list::on_message_kill_focus);

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
      add_command_prober("new_folder_inplace", { this,  &file_list::_001OnUpdateNewFolderInPlace });
      add_command_handler("new_folder_inplace", { this,  &file_list::_001OnNewFolderInPlace });
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


   void file_list::RenameFile(::i32 iLine, string &wstrNameNew, const ::action_context & context)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::file::path filepath = fs_list_item(iLine)->final_path();

      ::file::path filepathNew = filepath.folder() / wstrNameNew;

      // auto pcontext = get_context();

      path_system()->rename(filepathNew, filepath);

      browse_sync(context);

   }


   void file_list::on_message_context_menu(::message::message * pmessage)
   {

      ::pointer<::message::mouse>pcontextmenu(pmessage);

      if (_001IsEditing())
      {

         if (!_001SaveEdit(_001GetEditControl()))
         {

            pmessage->m_bRet = true;

            return;

         }

         _001HideEditingControls();

      }

      ::collection::index iItem = -1;

      auto point = pcontextmenu->m_pointHost;

      ::user::list::host_to_client()(point);

      m_pointContextMenuClient = point;

      m_bHasContextMenuRenamePoint = false;

      m_iContextMenuRenameItem = -1;

      auto pointCursor = pcontextmenu->m_pointAbsolute;

      auto r = ::i32_rectangle::square_with_center_and_apothem(pointCursor, 8);

      const char * pszItemMenuXml =
         "<menubar id=\"popup\">"
         "   <item id=\"file_open\">Open</item>"
         "   <item id=\"edit_copy\">Copy</item>"
         "   <item id=\"edit_paste\">Paste</item>"
         "   <item id=\"file_rename\">Rename</item>"
         "</menubar>";

      const char * pszEmptyAreaMenuXml =
         "<menubar id=\"popup\">"
         "   <menubar id=\"new_menu\" title=\"New\">"
         "      <item id=\"new_folder_inplace\">Folder</item>"
         "   </menubar>"
         "   <item id=\"edit_paste\">Paste</item>"
         "</menubar>";

      bool bHitItem = false;
      bool bIsFolder = false;
      ::pointer<::file::item> pfolderItem;
      ::string strXmlPopup;

      {

         synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         bHitItem = _001HitTest_(point, iItem)
            && iItem >= 0
            && iItem < fs_list()->m_pitema->get_size();

         if (bHitItem)
         {

            m_bHasContextMenuRenamePoint = true;

            m_iContextMenuRenameItem = iItem;

            ::user::range range;

            get_selection(range);

            if (!range.has_item(iItem))
            {

               _001SelectItem(iItem);

            }

            pfolderItem = fs_list_item(iItem);

            bIsFolder = pfolderItem && pfolderItem->is_folder();

         }

         strXmlPopup = filemanager_data()->m_strXmlPopup;

      }

      ::pointer<file_list> plist = this;

      // Menu window creation uses user_send -> main_send; run off the Qt/GTK main thread to avoid deadlocking.
      user_post([plist, bHitItem, bIsFolder, pfolderItem, strXmlPopup, pointCursor, r, pszItemMenuXml, pszEmptyAreaMenuXml]()
      {

         auto puser = plist->user();

         auto trackXmlMenu = [&](const ::scoped_string & strXml)
         {
            auto pmenu = puser->menu_from_xml(plist, strXml);
            if (!pmenu) return false;
             REFDBG_POINTER(plist);
            auto ptrackpopup = __initialize_pointer_with(plist) new ::menu::track_popup(
               pmenu,
               plist,
               plist,
               pointCursor,
               r);
            puser->track_popup_menu(ptrackpopup);
            return true;
         };

         if (bHitItem)
         {

            if (bIsFolder && pfolderItem)
            {

               string_array_base straCommand;

               string_array_base straCommandTitle;

               plist->filemanager_document()->on_file_manager_open_context_menu_folder(
                  pfolderItem, straCommand, straCommandTitle, ::e_source_user);

               if (straCommand.get_size() > 0)
               {

                  if (!straCommand.contains("file_rename"))
                  {

                     straCommand.add("file_rename");

                     straCommandTitle.add("Rename");

                  }
REFDBG_POINTER(plist);
                  auto pmenu = plist->create_newø < ::user::menu >();

                  if (pmenu->create_menu(straCommand, straCommandTitle))
                  {

                     auto ptrackpopup = __initialize_pointer_with(plist) new ::menu::track_popup(
                        pmenu,
                        plist,
                        plist,
                        pointCursor,
                        r);

                     puser->track_popup_menu(ptrackpopup);

                     return;

                  }

               }

               trackXmlMenu(pszItemMenuXml);

            }
            else
            {

               trackXmlMenu(pszItemMenuXml);

            }

         }
         else
         {

            trackXmlMenu(pszEmptyAreaMenuXml);

         }

      });

      pmessage->m_bRet = true;

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

   //   ::i32 i;

   //   while (::task_get_run())
   //   {

   //      i = 0;

   //      while (i < fs_list()->m_pitema->get_count() || is_window_visible())
   //      {

   //         ::i64 i64Size;

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


   void file_list::operator()(::timer * ptimer)
   {

      ::userfs::list::operator()(ptimer);
      if (ptimer->m_etimer == e_timer_folder_loading)
      {
         if (!m_bFolderLoading) { ptimer->cancel(); return; }
         m_iLoadingDots = (m_iLoadingDots + 1) % 4;
         post_redraw();
         return;
      }

      if (ptimer->m_etimer == e_timer_update_bergedge_topic_file)
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

               psession->m_varTopicFile = (const string_array_base &) patha;

            }

         }
         else
         {
            //kill_timer(888888);
            ptimer->cancel();
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

      synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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

      string_array_base straCommand;

      string_array_base straCommandTitle;

      filemanager_document()->on_file_manager_open_context_menu_folder(item, straCommand, straCommandTitle, context);

      if (straCommand.get_size() > 0)
      {

         auto pmenu = create_newø < ::user::menu >();

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


   void file_list::set_inplace_watch_suppressed(bool bSuppress)
   {

      if (m_bInPlaceWatchSuppressed == bSuppress)
      {

         return;

      }

      auto pdocument = filemanager_document();

      if (pdocument)
      {

         if (bSuppress)
         {

            pdocument->m_iWatchRefreshSuppress.fetch_add(1, std::memory_order_relaxed);

         }
         else
         {

            pdocument->m_iWatchRefreshSuppress.fetch_sub(1, std::memory_order_relaxed);

         }

      }

      m_bInPlaceWatchSuppressed = bSuppress;

   }


   ::collection::index file_list::calculate_insert_index_for_point(const ::i32_point & point)
   {

      auto iCount = fs_list()->m_pitema->get_size();

      if (iCount <= 0)
      {

         return 0;

      }

      auto pointOffset = get_context_offset();

      auto rectangleX = this->rectangle();

      ::collection::index iInsert = iCount;

      if (m_eview == impact_report)
      {

         ::f64 iy = point.y + pointOffset.y - (m_bHeaderCtrl ? m_dItemHeight : 0.0)
            - (m_bTopText ? m_rectangleTopText.height() : 0.0);

         if (m_dItemHeight > 0.0)
         {

            iInsert = (::collection::index)(iy / m_dItemHeight);

         }

      }
      else if (m_eview == impact_list)
      {

         auto rectContent = rectangleX;

         if (m_bTopText) rectContent.top += m_rectangleTopText.height();

         if (m_bHeaderCtrl) rectContent.top += (::i32)m_dItemHeight;

         if (m_dItemHeight > 0.0 && m_iItemWidth > 0)
         {

            ::i32 iRows = maximum<::i32>(1, (::i32)(rectContent.height() / m_dItemHeight));

            ::i32 iCol = maximum<::i32>(0, (::i32)((point.x + pointOffset.x - m_iLeftMargin) / m_iItemWidth));

            ::i32 iRow = maximum<::i32>(0, (::i32)((point.y + pointOffset.y - rectContent.top) / m_dItemHeight));

            iInsert = iCol * iRows + iRow;

         }

      }
      else if (m_eview == impact_icon)
      {

         auto sizeIconItem = get_list_icon_item_size();

         auto iTop = m_bTopText ? m_rectangleTopText.height() : 0;

         auto iAvailableWidth = maximum<::i32>(sizeIconItem.cx, rectangleX.width() - m_iLeftMargin - m_iRightMargin);

         auto iCols = maximum<::i32>(1, iAvailableWidth / sizeIconItem.cx);

         ::i32 ix = maximum<::i32>(0, minimum<::i32>(iCols - 1, (::i32)((point.x + pointOffset.x - m_iLeftMargin) / sizeIconItem.cx)));

         ::i32 iy = maximum<::i32>(0, (::i32)((point.y + pointOffset.y - iTop) / sizeIconItem.cy));

         iInsert = iy * iCols + ix;

      }

      if (iInsert < 0) iInsert = 0;

      if (iInsert > iCount) iInsert = iCount;

      return iInsert;

   }


   void file_list::_001OnUpdateNewFolderInPlace(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      auto pitem = filemanager_item();

      pcommand->enable(pitem && pitem->user_path().has_character());

      pmessage->m_bRet = true;

   }


   void file_list::_001OnNewFolderInPlace(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      auto pdirItem = filemanager_item();

      if (!pdirItem || pdirItem->user_path().is_empty())
      {

         return;

      }

      if (_001IsEditing())
      {

         _001CancelEdit(_001GetEditControl());

         _001HideEditingControls();

      }

      ::collection::index iInsert = 0;

      {

         synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         iInsert = calculate_insert_index_for_point(m_pointContextMenuClient);

         auto pnewitem = create_newø<::userfs::list_item>();

         pnewitem->m_strName = "";

         // Use an existing regular folder path for final_path so the shell icon
         // lookup resolves the regular folder icon instead of "unknown file type"
         // for a not-yet-created path.
         ::file::path pathFolderIcon;

         for (::collection::index i = 0; i < fs_list()->m_pitema->get_size(); i++)
         {

            auto pexisting = fs_list_item(i);

            if (pexisting && pexisting->is_folder() && pexisting->final_path().has_character())
            {

               pathFolderIcon = pexisting->final_path();

               break;

            }

         }

         if (pathFolderIcon.is_empty())
         {

            pathFolderIcon = pdirItem->final_path().has_character() ? pdirItem->final_path() : ::file::path("/tmp");

         }

         pnewitem->user_path_reference() = pdirItem->user_path() / "New Folder";

         pnewitem->final_path_reference() = pathFolderIcon;

         pnewitem->m_flags = ::file::e_flag_folder;

         pnewitem->m_iImage = -1;

         pnewitem->m_iImageSelected = -1;

         fs_list()->m_pitema->insert_at(iInsert, pnewitem);

      }

      set_inplace_watch_suppressed(true);

      on_update_item_count();

      m_bCreatingNewFolderInPlace = true;

      m_iInPlaceEditItem = iInsert;

      ::user::interaction * pinteraction = _001GetControl(iInsert, m_iNameSubItem);

      if (pinteraction)
      {

         _001PlaceControl(pinteraction, iInsert, true);

      }
      else
      {

         _001CancelEdit(nullptr);

      }

   }


   void file_list::_001OnFileRename(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      if (_001IsEditing())
      {

         _001CancelEdit(_001GetEditControl());

         _001HideEditingControls();

      }

      ::collection::index iEditItem = -1;

      if (m_iContextMenuRenameItem >= 0)
      {

         iEditItem = m_iContextMenuRenameItem;

         m_iContextMenuRenameItem = -1;

      }
      else
      {

         ::user::range range;

         get_selection(range);

         if (range.get_item_count() == 1 && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound())
         {

            iEditItem = range.ItemAt(0).get_lower_bound();

         }

      }

      if (iEditItem >= 0)
      {

         if (iEditItem >= fs_list()->m_pitema->get_size())
         {

            m_bHasContextMenuRenamePoint = false;

            return;

         }

         _001SelectItem(iEditItem);

         m_bCreatingNewFolderInPlace = false;

         m_iInPlaceEditItem = iEditItem;

         set_inplace_watch_suppressed(true);

         ::user::interaction * pinteraction = _001GetControl(iEditItem, m_iNameSubItem);

         if (pinteraction)
         {

            bool bPlaceCaretAtClick = m_bHasContextMenuRenamePoint;

            ::i32_point pointClickClient = m_pointContextMenuClient;

            m_bHasContextMenuRenamePoint = false;

            _001PlaceControl(pinteraction, iEditItem, true);

            if (bPlaceCaretAtClick)
            {

               ::pointer<::user::plain_edit> pedit = pinteraction;

               if (pedit.is_set())
               {

                  ::i32_point pointInEdit = pointClickClient - pedit->const_layout().sketch().origin();

                  ::pointer<file_list> plistHold = this;

                  pedit->queue_graphics_call([plistHold, pedit, pointInEdit](::draw2d::graphics_pointer & pdraw2dgraphics)
                  {

                     if (plistHold->_001GetEditControl() != pedit.m_p)
                     {

                        return;

                     }

                     pedit->plain_edit_update(pdraw2dgraphics, true, -1);

                     character_count iHit = pedit->plain_edit_line_char_hit_test(pdraw2dgraphics, pointInEdit.x, 0);

                     character_count iLen = pedit->get_text_length();

                     if (iHit < 0)
                     {

                        iHit = 0;

                     }
                     else if (iHit > iLen)
                     {

                        iHit = iLen;

                     }

                     pedit->set_text_selection(iHit, iHit, e_source_user);

                     pedit->plain_edit_sel_to_column_x(pdraw2dgraphics, iHit, pedit->m_iColumnX);

                     pedit->set_need_redraw();

                     pedit->post_redraw();

                  });

               }

            }

         }
         else
         {

            m_iInPlaceEditItem = -1;

            set_inplace_watch_suppressed(false);

         }

      }

   }


   void file_list::_001OnShowControl(::user::interaction * pinteraction)
   {

      ::userfs::list::_001OnShowControl(pinteraction);

      if (!pinteraction || pinteraction->m_item.m_iSubItem != m_iNameSubItem)
      {

         return;

      }

      ::collection::index iItem = pinteraction->m_item.m_iItem;

      if (iItem < 0)
      {

         return;

      }

      m_iInPlaceEditItem = iItem;

      set_inplace_watch_suppressed(true);

      if (!m_bCreatingNewFolderInPlace)
      {

         ::pointer<::user::plain_edit> pedit = pinteraction;

         if (pedit.is_set())
         {

            bool bIsFolder = false;

            ::string strName;

            {

               synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

               if (iItem < fs_list()->m_pitema->get_size())
               {

                  auto pitem = fs_list_item(iItem);

                  if (pitem)
                  {

                     bIsFolder = pitem->is_folder();

                     strName = pitem->m_strName;

                  }

               }

            }

            character_count iCaretPos = strName.length();

            if (!bIsFolder)
            {

               auto iDot = strName.rear_find_index('.');

               if (iDot > 0)
               {

                  iCaretPos = iDot;

               }

            }

            pedit->set_text_selection(iCaretPos, iCaretPos, e_source_user);

         }

      }

   }


   bool file_list::_001Validate(::user::interaction * pinteraction, ::payload & payload)
   {

      if (m_iInPlaceEditItem < 0)
      {

         return ::userfs::list::_001Validate(pinteraction, payload);

      }

      if (m_bValidationDialogOpen)
      {

         return false;

      }

      ::string strName = payload.as_string();

      strName.trim();

      bool bNewFolder = m_bCreatingNewFolderInPlace;

      ::collection::index iEditItem = m_iInPlaceEditItem;

      ::string strOldName;

      bool bIsFolder = bNewFolder;

      {

         synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         if (iEditItem >= 0 && iEditItem < fs_list()->m_pitema->get_size())
         {

            auto pitem = fs_list_item(iEditItem);

            if (pitem)
            {

               strOldName = pitem->m_strName;

               bIsFolder = pitem->is_folder();

            }

         }

      }

      if (!bNewFolder && strName == strOldName)
      {

         payload = strName;

         return true;

      }

      bool bExternalFocusLoss = m_bSavingOnExternalFocusLoss;

      auto showValidationError = [&](const ::scoped_string & strReason)
      {

         m_bValidationDialogOpen = true;

         ::pointer<file_list> plist = this;

         ::pointer<::user::plain_edit> pedit = pinteraction;

         auto pmsg = create_newø<::user_interface::message_box>();

         ::string strMsg;

         if (bExternalFocusLoss)
         {

            if (bNewFolder)
            {

               if (strName.has_character())
               {

                  strMsg = "Couldn't create folder \"" + strName + "\" because: " + ::string(strReason);

               }
               else
               {

                  strMsg = "Couldn't create folder because: " + ::string(strReason);

               }

            }
            else
            {

               if (strName.has_character())
               {

                  strMsg = "Couldn't rename \"" + strOldName + "\" to \"" + strName + "\" because: " + ::string(strReason);

               }
               else
               {

                  strMsg = "Couldn't rename \"" + strOldName + "\" because: " + ::string(strReason);

               }

            }

            pmsg->initialize_message_box(
               strMsg,
               bNewFolder ? "New Folder" : "Rename",
               ::user::e_message_box_icon_exclamation);

            pmsg->add_button("OK", e_dialog_result_ok, 'o');

            pmsg->message_box_response_callback() = [plist](::user_interface::message_box * pmessagebox)
            {

               __UNREFERENCED_PARAMETER(pmessagebox);

               plist->user_post([plist]()
               {

                  plist->m_bValidationDialogOpen = false;

               });

            };

         }
         else
         {

            if (bNewFolder)
            {

               if (strName.has_character())
               {

                  strMsg = "Cannot create folder \"" + strName + "\" because: " + ::string(strReason)
                     + "\n\nChoose Edit to modify the name, or Cancel to exit.";

               }
               else
               {

                  strMsg = "Cannot create folder because: " + ::string(strReason)
                     + "\n\nChoose Edit to enter a name, or Cancel to exit.";

               }

            }
            else
            {

               if (strName.has_character())
               {

                  strMsg = "Cannot rename \"" + strOldName + "\" to \"" + strName + "\" because: " + ::string(strReason)
                     + "\n\nChoose Edit to modify the name, Restore to restore the original name, or Cancel to exit rename mode.";

               }
               else
               {

                  strMsg = "Cannot rename \"" + strOldName + "\" because: " + ::string(strReason)
                     + "\n\nChoose Edit to enter a name, Restore to restore the original name, or Cancel to exit rename mode.";

               }

            }

            pmsg->initialize_message_box(
               strMsg,
               bNewFolder ? "New Folder" : "Rename",
               ::user::e_message_box_icon_exclamation);

            pmsg->add_button("Edit", e_dialog_result_retry, 'e');

            if (!bNewFolder)
            {

               pmsg->add_button("Restore", e_dialog_result_yes, 'r');

            }

            pmsg->add_button("Cancel", e_dialog_result_cancel, 'c');

            pmsg->message_box_response_callback() = [plist, pedit, bNewFolder, bIsFolder, strOldName](::user_interface::message_box * pmessagebox)
            {

               auto payloadResponse = pmessagebox->get_dialog_response();

               plist->user_post([plist, pedit, bNewFolder, bIsFolder, strOldName, payloadResponse]()
               {

                  plist->m_bValidationDialogOpen = false;

                  if (payloadResponse == e_dialog_result_cancel)
                  {

                     plist->_001CancelEdit(pedit);

                     plist->_001HideEditingControls();

                  }
                  else if (payloadResponse == e_dialog_result_yes && !bNewFolder)
                  {

                     if (pedit.is_set() && plist->_001GetEditControl() == pedit.m_p)
                     {

                        pedit->set_text(strOldName, e_source_user);

                        pedit->set_keyboard_focus();

                        character_count iSelEnd = strOldName.length();

                        if (!bIsFolder)
                        {

                           auto iDot = strOldName.rear_find_index('.');

                           if (iDot > 0)
                           {

                              iSelEnd = iDot;

                           }

                        }

                        pedit->set_text_selection(iSelEnd, iSelEnd, e_source_user);

                        pedit->set_need_redraw();

                        pedit->post_redraw();

                     }

                  }
                  else
                  {

                     if (pedit.is_set() && plist->_001GetEditControl() == pedit.m_p)
                     {

                        character_count iBeg = 0;

                        character_count iEnd = 0;

                        pedit->get_text_selection(iBeg, iEnd);

                        pedit->set_keyboard_focus();

                        pedit->set_text_selection(iBeg, iEnd, e_source_user);

                        pedit->set_need_redraw();

                        pedit->post_redraw();

                     }

                  }

               });

            };

         }

         user_post([pmsg]()
         {

            pmsg->display(e_display_normal, {});

         });

      };

      if (strName.is_empty())
      {

         showValidationError("the name cannot be empty.");

         return false;

      }

      if (strName == "." || strName == "..")
      {

         showValidationError("\"" + strName + "\" is a reserved name.");

         return false;

      }

      if (strName.contains("/") || strName.contains("\\") || strName.contains(":")
         || strName.contains("*") || strName.contains("?") || strName.contains("\"")
         || strName.contains("<") || strName.contains(">") || strName.contains("|"))
      {

         showValidationError("the name contains invalid characters (/, \\, :, *, ?, \", <, >, |).");

         return false;

      }

      {

         synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         auto iCount = fs_list()->m_pitema->get_size();

         for (::collection::index i = 0; i < iCount; i++)
         {

            if (i == iEditItem) continue;

            auto pexisting = fs_list_item(i);

            if (pexisting && pexisting->m_strName == strName)
            {

               showValidationError("an item named \"" + strName + "\" already exists in this folder.");

               return false;

            }

         }

      }

      payload = strName;

      return true;

   }


   void file_list::_001SetSubItemText(::user::mesh_subitem * psubitem)
   {

      if (!psubitem || psubitem->m_iSubItem != m_iNameSubItem || m_iInPlaceEditItem < 0)
      {

         ::userfs::list::_001SetSubItemText(psubitem);

         return;

      }

      bool bNewFolder = m_bCreatingNewFolderInPlace;

      ::collection::index iItem = m_iInPlaceEditItem;

      ::string strNewName = psubitem->m_strText;

      strNewName.trim();

      m_bCreatingNewFolderInPlace = false;

      m_iInPlaceEditItem = -1;

      if (bNewFolder)
      {

         {

            synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            if (iItem >= 0 && iItem < fs_list()->m_pitema->get_size())
            {

               fs_list_item(iItem)->m_strName = strNewName;

            }

         }

         auto pdirItem = filemanager_item();

         if (!pdirItem || pdirItem->user_path().is_empty())
         {

            return;

         }

         ::file::path pathParent = pdirItem->user_path();

         ::pointer<file_list> plist = this;

         ::pointer<::filemanager::document> pdocument = filemanager_document();

         pdocument->fork([plist, pdocument, pathParent, strNewName]()
         {

            ::string strError;

            try
            {

               pdocument->filemanager_data()->fs_data()->create_folder(pathParent, strNewName);

            }
            catch (const ::exception & exception)
            {

               strError = exception.get_message();

            }
            catch (...)
            {

               strError = "Could not create the folder.";

            }

            plist->user_post([plist, pdocument, strError]()
            {

               if (strError.has_character())
               {

                   REFDBG_POINTER(plist);

                  auto pmsg = plist->create_newø<::user_interface::message_box>();

                  pmsg->initialize_message_box(strError, "New Folder");

                  pmsg->display(e_display_normal, {});

               }

               pdocument->_001Refresh();

            });

         });

      }
      else
      {

         ::file::path filepathOld;

         ::string strOldName;

         {

            synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            if (iItem < 0 || iItem >= fs_list()->m_pitema->get_size())
            {

               return;

            }

            auto pitem = fs_list_item(iItem);

            strOldName = pitem->m_strName;

            filepathOld = pitem->final_path();

         }

         if (strNewName == strOldName)
         {

            return;

         }

         if (filepathOld.case_insensitive_begins("google-drive://"))
         {

            {

               synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

               if (iItem >= 0 && iItem < fs_list()->m_pitema->get_size())
               {

                  auto pitem = fs_list_item(iItem);

                  if (pitem)
                  {

                     pitem->m_strName = strNewName;

                  }

               }

            }

            set_need_redraw();

            post_redraw();

            ::pointer<file_list> plist = this;

            ::pointer<::filemanager::document> pdocument = filemanager_document();

            auto & pfactory = system()->factory("folder", "google_drive");

            auto pfolder = createø<::folder>(pfactory);

            pdocument->fork([plist, pfolder, filepathOld, strOldName, strNewName]()
            {

               ::string strError;

               try
               {

                  pfolder->rename_item(filepathOld, strNewName);

               }
               catch (const ::exception & exception)
               {

                  strError = exception.get_message();

               }
               catch (...)
               {

                  strError = "Could not rename the item on Google Drive.";

               }

               if (strError.has_character())
               {

                  plist->user_post([plist, filepathOld, strOldName, strError]()
                  {

                     {

                        synchronous_lock synchronouslock(plist->fs_list()->synchronization(), plist.m_p, __FILE__, __LINE__);

                        for (::collection::index i = 0; i < plist->fs_list()->m_pitema->get_size(); i++)
                        {

                           auto pitem = plist->fs_list_item(i);

                           if (pitem && pitem->final_path() == filepathOld)
                           {

                              pitem->m_strName = strOldName;

                              break;

                           }

                        }

                     }

                     plist->set_need_redraw();

                     plist->post_redraw();

                     REFDBG_POINTER(plist);

                     auto pmsg = plist->create_newø<::user_interface::message_box>();

                     pmsg->initialize_message_box(strError, "Rename");

                     pmsg->display(e_display_normal, {});

                  });

               }

            });

            return;

         }

         try
         {

            ::file::path filepathNew = filepathOld.folder() / strNewName;

            path_system()->rename(filepathNew, filepathOld);

            {

               synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

               if (iItem >= 0 && iItem < fs_list()->m_pitema->get_size())
               {

                  auto pitem = fs_list_item(iItem);

                  if (pitem)
                  {

                     pitem->m_strName = strNewName;

                     pitem->set_user_path(pitem->user_path().folder() / strNewName);

                     filepathNew.flags() |= ::file::e_flag_final_path;

                     filepathNew.m_etype = filepathOld.m_etype;

                     pitem->set_final_path(filepathNew);

                  }

               }

            }

            set_need_redraw();

            post_redraw();

         }
         catch (const ::exception & exception)
         {

            auto pmsg = create_newø<::user_interface::message_box>();

            pmsg->initialize_message_box(exception.get_message(), "Rename");

            user_post([pmsg]()
            {

               pmsg->display(e_display_normal, {});

            });

         }
         catch (...)
         {

            auto pmsg = create_newø<::user_interface::message_box>();

            pmsg->initialize_message_box("Could not rename the item.", "Rename");

            user_post([pmsg]()
            {

               pmsg->display(e_display_normal, {});

            });

         }

      }

   }


   void file_list::_001HideEditingControls()
   {

      ::userfs::list::_001HideEditingControls();

      m_iInPlaceEditItem = -1;

      set_inplace_watch_suppressed(false);

   }


   void file_list::_001CancelEdit(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      bool bNewFolder = m_bCreatingNewFolderInPlace;

      ::collection::index iItem = m_iInPlaceEditItem;

      m_bCreatingNewFolderInPlace = false;

      m_iInPlaceEditItem = -1;

      set_inplace_watch_suppressed(false);

      if (bNewFolder && iItem >= 0)
      {

         {

            synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            if (iItem < fs_list()->m_pitema->get_size())
            {

               fs_list()->m_pitema->erase_at(iItem);

            }

         }

         on_update_item_count();

         set_need_redraw();

         post_redraw();

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

      information() << "File Manager Copy: " << patha.size() << " selected files";
      auto pcopydesk = copydesk();

      if (patha.is_empty() || !pcopydesk->set_filea(patha, ::user::copydesk::e_op_copy))
      {
         auto message = create_newø<::user_interface::message_box>();
         message->initialize_message_box(patha.is_empty() ? "Select files to copy." : "Could not put the selected files on the clipboard.", "Copy files");
         message->display(e_display_normal, {});
      }

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

         string_array_base stra;

         // auto pcontext = get_context();

         node()->file_extension_get_open_with_list_keys(stra, strExt);

         m_straOpenWith = stra;

         ::collection::count iCount = stra.get_size();

         string str;

         for (::i32 i = 0; i < iCount; i++)
         {

            auto pmenuitem = create_newø < ::menu::item > ();

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

      ::i32 iPos = -1;

      for (::i32 i = 0; i < m_straOpenWith.get_size(); i++)
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

      ::i32 iPos = -1;

      for (::i32 i = 0; i < m_straOpenWith.get_size(); i++)
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

   //   string_array_base stra;

   //   ::file::listing_base straSub;

   //   string strFileList;
   //   string strFileCheck;
   //   for (::i32 i = 0; i < itema.get_size(); i++)
   //   {

   //      if (directory()->is(itema[i]->m_filepathFinal) && strcmp(itema[i]->m_filepathFinal.name(), ".svn"))
   //      {

   //         straSub.rls(itema[i]->m_filepathFinal);

   //         for (::i32 j = 0; j < straSub.get_size(); j++)
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

   //   synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //   ::pointer<::userfs::list_data>pdata = fs_list();
   //
   //   __UNREFERENCED_PARAMETER(pmessage);
   //
   //   string_array_base stra;
   //
   //   ::file::listing_base straSub(get_context());

   //   string strFileList;

   //   string strFileCheck;

   //   for (::i32 i = 0; i < pdata->m_pitema->get_count(); i++)
   //   {

   //      if (fs_data()->is_dir(pdata->item(i)->m_filepathFinal)
   //            && strcmp(pdata->item(i)->m_filepathFinal.name(), ".svn"))
   //      {

   //         straSub.rls(pdata->item(i)->m_filepathFinal);

   //         for (::i32 j = 0; j < straSub.get_size(); j++)
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


   //void file_list::schedule_file_size(const ::scoped_string & scopedstr)
   //{

   //   __UNREFERENCED_PARAMETER(scopedstr);

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

         string_array_base stra;

         auto papp = ::filemanager_impact_base::get_app();

         ::cast < ::database::client > pdatabaseclient = papp;

         pdatabaseclient->datastream()->get(filemanager_data()->m_strDataKeyStatic, stra);

         synchronous_lock lock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         fs_list()->m_pitema->erase_all();

         for (::i32 i = 0; i < stra.get_size(); i++)
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

         set_timer(e_timer_update_bergedge_topic_file, 230_ms, nullptr);

      }

      set_context_offset({0,0});

      string_array_base straStrictOrder;

//      papp->datastream()->get(data_get_current_sort_id() + "." +  data_get_current_list_layout_id() + ".straStrictOrder", straStrictOrder);

      index_biunique iaDisplayToStrict;

      ::pointer<icon_layout>piconlayout;

      construct_newø(piconlayout);

//      papp->datastream()->get(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), piconlayout);

      iaDisplayToStrict = piconlayout->m_iaDisplayToStrict;

      index_biunique iaDisplayToStrictNew;

      ::userfs::list_item item;

      string strParent = filemanager_path();

      ::file::path pathParentEx = filemanager_item()->user_path();

      pathParentEx = filemanager_path();

      //::i32 iMaxSize;

      //iMaxSize = 1000;

      //::i32 iSize;

      //iSize = 0;

      m_pathaStrictOrder.erase_all();

      update_impact();

      // auto pcontext = get_context();

      {

         auto pparticleSynchronization = fs_list()->synchronization();

         synchronous_lock lock(pparticleSynchronization, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         ::file::listing_base & listingUser = filemanager_data()->m_listingUser2;

         ::file::listing_base & listingFinal = filemanager_data()->m_listingFinal2;

         auto cItem = listingUser.get_size();

         fs_list()->m_pitema->set_size(cItem);

         m_pathaStrictOrder = listingUser;

         for (::i32 i = 0; i < cItem; i++)
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

            if (pathFinal.is_folder())
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

         fs_list()->m_pitema->arrange(::fs::arrange_by_name);
         m_pathaStrictOrder.erase_all();
         for (auto & pitem : *fs_list()->m_pitema)
         {

            m_pathaStrictOrder.add(pitem->user_path());

         }

      }

      update_impact();

      {

         synchronous_lock lock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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
      /*   for(::i32 i = 0; i < m_pitema->get_item_count(); i++)
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

      //queue_graphics_call([this](::draw2d::graphics_pointer & pdraw2dgraphics)
        // {

           // set_context_offset(pdraw2dgraphics, 0, 0);

      //set_context_offset(pdraw2dgraphics, 0, 0);

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

      ::i32 iCount = 0;

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

            auto pinteraction = create_newø <  user::button > ();
            pinteraction->m_bTransparent = true;
            //pinteraction->set_control_type(user::e_control_type_button);
            //pinteraction->m_type = ::type<::user::button>();
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

      if (filemanager_data()->m_bListSelection && m_eview != impact_icon)
      {

         ::i32 iIconSize = maximum(get_document()->m_iIconSize, filemanager_data()->m_iIconSize);

         m_iSelectionSubItem = i;
         m_iIconSubItem = m_iSelectionSubItem;
         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = iIconSize + 8;
         //pcolumn->m_bIcon                = true;
         pcolumn->m_sizeIcon.cx = iIconSize;
         pcolumn->m_sizeIcon.cy = iIconSize;
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

      bool bRenameEdit = true;

      {

         ::pointer<::user::list_column> pcolumn;

         if (bRenameEdit)
         {

            auto pinteraction = create_newø < ::user::plain_edit > ();
            pinteraction->m_econtroltype = ::user::e_control_type_edit_plain_text;
            pinteraction->m_strDataKey20 = "FILE_MANAGER_ID_FILE_NAME";
            pinteraction->set_data_type(user::e_control_data_type_string);
            pinteraction->add_function(user::e_control_function_vms_data_edit);
            pinteraction->m_type = ::type<::user::plain_edit>();
            pinteraction->id() = 1000 + i;
            pinteraction->display(e_display_none);
            pcolumn = new_list_column_with_control(pinteraction);

         }
         else
         {

            pcolumn = new_list_column();

         }



         m_iNameSubItem = i;
         if (m_iSelectionSubItem < 0)
         {
            m_iIconSubItem = m_iNameSubItem;
         }
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
         pcolumn->m_sizeIcon.cx = get_document()->m_iIconSize;
         pcolumn->m_sizeIcon.cy = get_document()->m_iIconSize;
         pcolumn->m_text = pcontext->__text("text://file/Name");
         pcolumn->m_strDataKey = "FILE_MANAGER_ID_FILE_NAME";
         pcolumn->m_bEditOnSecondClick = false;
         ::i32 iIconSize = get_document()->m_iIconSize;

         auto pcontext = m_papplication;
         
         auto psession = pcontext->m_psession;
         
         auto puser = psession->m_puser;

         if (m_iSelectionSubItem < 0)
         {
            pcolumn->m_pimagelist = puser->shell()->GetImageList(iIconSize);

            pcolumn->m_pimagelistHover = puser->shell()->GetImageListHover(iIconSize);
         }
         else
         {
            pcolumn->m_pimagelist = nullptr;

            pcolumn->m_pimagelistHover = nullptr;
         }

      }

      i++;

      if (filemanager_data()->m_bFileSize)
      {

         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 100;

         pcolumn->m_iSubItem = i;

         m_iSizeSubItem = i;

         fs_list()->m_iSizeSubItem = m_iSizeSubItem;

         pcolumn->m_text = pcontext->__text("text://file/Size");

         pcolumn->m_sizeIcon.cx = 0;

         pcolumn->m_sizeIcon.cy = 0;

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


   void file_list::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      if (!m_bFolderLoading && !m_bFolderLoadFailed)
         ::user::form_list::_001OnDraw(pdraw2dgraphics);
      if (m_bFolderLoading || m_bFolderLoadFailed)
      {
         ::string str = m_bFolderLoading ? "Loading" : "Could not load this folder.";
         if (m_bFolderLoading) for (int i = 0; i < m_iLoadingDots; ++i) str += ".";
         else
         {
            auto detail = payload("filemanager_browse_error").as_string();
            if (detail.has_character()) str += "\n" + detail;
         }
         auto rectangle = this->rectangle();
         rectangle.top += 40;
         auto pstyle = get_style(pdraw2dgraphics);
         pdraw2dgraphics->set_solid_color(get_color(pstyle, ::e_element_text));
         pdraw2dgraphics->set_font(this);
         pdraw2dgraphics->draw_text(str, rectangle, e_align_center);
      }

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

      synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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

            if (fs_list_item(iStrict)->is_folder())
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

         pbutton->set_button_style(::user::e_button_style_list);

         pcallback->InitializeActionButton(pinteraction->id().as_i32() - 1000, pbutton);

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

   //   synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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


   bool file_list::add_fs_item(::file::path pathUser, ::file::path pathFinal, const ::scoped_string & scopedstrName)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::userfs::list_item item;

      item.set_user_path(pathUser);

      item.set_final_path(pathFinal);

      item.m_strName = scopedstrName;

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

   //   for (::i32 i = 0; i < fs_list()->m_pitema->get_count(); i++)
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

      synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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
            return fs_list_item(iStrict)->is_folder();

         }

      }

      return false;

   }


   bool file_list::do_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag)
   {

      synchronous_lock synchronouslock(fs_list()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::collection::index strict = display_to_strict(iDisplayDrop);

      ::collection::index strictDrag = display_to_strict(iDisplayDrag);

      // auto pcontext = get_context();

      if (strict >= 0 && fs_list_item(strict)->is_folder())
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

      pmessage->previous();
      if (auto frame = parent_frame()) frame->set_active_impact(this);

   }


   void file_list::on_message_kill_focus(::message::message * pmessage)
   {

      informationf("filemanager::file_list::on_message_kill_focus");

   }


   void file_list::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (!m_bStatic && ptopic->id() == "filemanager_browse_started")
      {
         if (_001IsEditing())
         {
            auto pcontrol = _001GetEditControl();
            m_bSavingOnExternalFocusLoss = true;
            if (!_001SaveEdit(pcontrol))
            {
               _001CancelEdit(pcontrol);
            }
            m_bSavingOnExternalFocusLoss = false;
            _001HideEditingControls();
         }
         m_bFolderLoading = true;
         m_bFolderLoadFailed = false;
         payload("filemanager_browse_error") = "";
         m_iLoadingDots = 1;
         clear_selection();
         auto pdata = fs_list();
         if (pdata)
         {
            synchronous_lock lock(pdata->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
            if (pdata->m_pitema) pdata->m_pitema->erase_all();
         }
         update_impact();
         set_timer(e_timer_folder_loading, 300_ms);
         post_redraw();
         return;
      }
      if (ptopic->id() == "filemanager_browse_failed" || ptopic->id() == id_browse)
      {
         m_bFolderLoading = false;
         m_bFolderLoadFailed = ptopic->id() == "filemanager_browse_failed";
         payload("filemanager_browse_error") = m_bFolderLoadFailed ? ptopic->payload("error_message").as_string() : ::string("");
         kill_timer(e_timer_folder_loading);
         post_redraw();
         if (m_bFolderLoadFailed)
         {
            if (!m_bStatic && ptopic->m_actioncontext.is_user_source())
            {
               set_keyboard_focus();
            }
            return;
         }
      }
      ::filemanager_impact_base::handle(ptopic, phandlercontext);

      ::userfs::list::handle(ptopic, phandlercontext);

      ::user::form_list::handle(ptopic, phandlercontext);

      if (ptopic->m_bRet)
      {

         return;

      }

      auto papp = get_app();

      if (m_bStatic && ptopic->id() == id_add_location)
      {

         ::file::path_array_base filepatha;

         ::cast < ::database::client > pdatabaseclient = application();

         pdatabaseclient->datastream()->get(filemanager_data()->m_strDataKeyStatic, filepatha);

         //filepatha.add().stra());

         ::file::path filepath = filemanager_item()->user_path();

         filepath.trim();

         if (filepath.has_character() && fs_data()->is_dir(filepath))
         {

            if (filepatha.add_unique(filepath) >= 0)
            {

               string_array_base stra;

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

         //      synchronous_lock synchronouslock(mutex_draw(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         //      if (filemanager_data()->m_pholderFileList->m_puserinteractionpointeraChild->has_interaction())
         //      {

         //         filemanager_data()->m_pholderFileList->m_puserinteractionpointeraChild->interaction_at(0)->display(e_display_none);

         //      }

         //   }

         //   filemanager_data()->m_pholderFileList->place_hold(this);

         //   filemanager_data()->m_pholderFileList->set_need_layout();

         //}

         information() << "file_list handle id_browse";

         browse_sync(ptopic->m_actioncontext + ::e_source_sync);

         data_get_DisplayToStrict();

         update_impact();

         post_redraw();

         if (ptopic->m_actioncontext.is_user_source())
         {
            set_keyboard_focus();
         }

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

               ::file::path pathFolder = filemanager_item()->user_path() / ptopic->payload(id_folder).as_string();

               // auto pcontext = get_context();

               directory()->create(pathFolder);

               ptopic->m_bRet = true;

            }

         }

      }

   }


} // namespace filemanager



