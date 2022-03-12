#include "framework.h"
#include "aura/graphics/image/list.h"
#include "acme/platform/timer.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif

#include "aqua/xml.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         list_view::list_view()
         {

            m_bKickActive = false;

         }


         list_view::~list_view()
         {

         }


         void list_view::install_message_routing(::channel * pchannel)
         {
            simple_list_view::install_message_routing(pchannel);
            MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &list_view::on_message_left_button_double_click);
//            //MESSAGE_LINK(e_message_timer, pchannel, this, &list_view::_001OnTimer);
            MESSAGE_LINK(e_message_size, pchannel, this, &list_view::on_message_size);
#ifdef WINDOWS_DESKTOP
            MESSAGE_LINK(e_message_context_menu, pchannel, this, &list_view::on_message_context_menu);
#endif
            //MESSAGE_LINK(e_message_erase_background, pchannel, this, &list_view::_001OnEraseBkgnd);
            MESSAGE_LINK(WM_USER + 1217, pchannel, this, &list_view::_001OnFillTaskResponse);

         }




         void list_view::assert_ok() const
         {
            simple_list_view::assert_ok();
         }

         void list_view::dump(dump_context & dumpcontext) const
         {
            simple_list_view::dump(dumpcontext);
         }


         void list_view::on_message_create(::message::message* pmessage)
         {

            if (!pmessage->previous())
            {

               return;

            }

            //auto estatus = 
            
            __construct_new(m_puserlistcache);

            set_cache_interface(m_puserlistcache);

            m_pil = __create_new< ::image_list>();

            m_pil->create(16, 16, 0, 0, 0);

#ifdef WINDOWS

            //m_iIconFolder = m_pil->add(icon_payload("matter://mplite/vmskarlib_folder_normal.ico"));

            //m_iIconArtist = m_pil->add(icon_payload("matter://mplite/vmskarlib_artist_normal.ico"));

            //m_iIconSong = m_pil->add(icon_payload("matter://mplite/vmskarlib_song_normal.ico"));

            //m_iIconFolder = m_pil->add(icon_payload("matter://mplite/vmskarlib_folder_normal.ico"));

            //m_iIconArtist = m_pil->add(icon_payload("matter://mplite/vmskarlib_artist_normal.ico"));

            //m_iIconSong = m_pil->add(icon_payload("matter://mplite/vmskarlib_song_normal.ico"));
#endif

            m_iIconFolder = m_pil->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_folder_normal"));

            m_iIconArtist = m_pil->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_artist_normal"));

            m_iIconSong = m_pil->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_song_normal"));

            m_iIconFolder = m_pil->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_folder_normal"));

            m_iIconArtist = m_pil->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_artist_normal"));

            m_iIconSong = m_pil->add(icon_payload(this, "matter://app-veriwell/musical_player_lite/karaoke_library_song_normal"));

         }


         void list_view::_001InsertColumns()
         {

            {
               auto pcolumn = new_list_column();
               /*

               pcolumn->m_iWidth = 50;
               //      pcolumn->m_uiText = IDS_PLAYLIST_CODE;
               pcolumn->m_iSubItem = SubItemId;
               //      pcolumn->m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
               pcolumn->m_iSmallImageWidth = 16;
               pcolumn->m_colorSmallMask = rgb(255, 0, 255);
               pcolumn->m_pil = m_pil;
               */
               pcolumn->m_iWidth = 170;
               //      pcolumn->m_uiText = IDS_PLAYLIST_CODE;
               pcolumn->m_iSubItem = SubItemTitle;
               //      pcolumn->m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
               pcolumn->m_iSmallImageWidth = 16;
               pcolumn->m_colorSmallMask = rgb(255, 0, 255);
               pcolumn->m_pil = m_pil;


            }

            {

               auto pcolumn = new_list_column();
               //      pcolumn->m_uiText = IDS_PLAYLIST_SONG_NAME;
               pcolumn->m_iWidth = 200;
               pcolumn->m_iSubItem = SubItemArtist;


            }


            {
               auto pcolumn = new_list_column();

               //      pcolumn->m_uiText = IDS_PLAYLIST_SONG_NAME;
               pcolumn->m_iWidth = 400;
               pcolumn->m_iSubItem = SubItemFileName;


            }


            {

               auto pcolumn = new_list_column();

               pcolumn->m_iWidth = 400;
               pcolumn->m_iSubItem = SubItemFilePath;


            }


         }


         void list_view::_001GetItemImage(::user::mesh_item * pitem)
         {
            if(pitem->m_iItem < 0 || pitem->m_iItem >= m_itema.get_size())
            {
               pitem->m_bOk = false;
               return;
            }
            if(pitem->m_iSubItem == SubItemTitle)
            {
               pitem->m_bOk = true;
               switch(m_itema[pitem->m_iItem]->m_etype)
               {
               case ItemTypeFolder:
                  pitem->m_iImage = m_iIconFolder;
                  break;
               case ItemTypeArtist:
                  pitem->m_iImage = m_iIconArtist;
                  break;
               case ItemTypeSong:
                  pitem->m_iImage = m_iIconSong;
                  break;
               default:
                  pitem->m_bOk = false;
                  break;
               }
               return;
            }
            else
            {
               pitem->m_bOk = false;
               return;
            }

         }

         void list_view::_001GetItemText(::user::mesh_item * pitem)
         {
            if(pitem->m_iItem < 0 || pitem->m_iItem >= m_itema.get_size())
            {
               pitem->m_bOk = false;
               return;
            }
            switch(pitem->m_iSubItem)
            {
            case SubItemId:
               pitem->m_strText.Empty();
               break;
            case SubItemTitle:
               pitem->m_strText = m_itema[pitem->m_iItem]->m_strTitle;
               break;
            case SubItemArtist:
               pitem->m_strText.Empty();
               break;
            case SubItemFileName:
               pitem->m_strText.Empty();
               break;;
            case SubItemFilePath:
               pitem->m_strText.Empty();
               break;
            default:
               //ASSERT(false);
               pitem->m_strText.Empty();
               break;
            }
            pitem->m_bOk = true;
         }

         void list_view::_001SearchGetItemText(::user::mesh_item * pitem)
         {
            return_(pitem->m_bOk, false);
         }


         void list_view::handle(::topic * ptopic, ::context * pcontext)
         {

            simple_list_view::handle(ptopic, pcontext);

            //if(::is_null(pobject))
            {

              // _001UpdateColumns();

            }
            //else
            {

            }

         }


         void list_view::on_message_left_button_double_click(::message::message * pmessage)
         {

            auto pmouse = pmessage->m_union.m_pmouse;

            index iItem;

            if(_001HitTest_(pmouse->m_point, iItem))
            {

               if(m_itema[iItem]->IsFolder())
               {

                  m_pserver->open_folder(m_itema[iItem]->m_iFolder);

               }
               else
               {

                  m_pserver->open_file(m_iParentFolder, m_itema[iItem]->m_strFileName, m_itema[(::index) iItem]->m_strExtension);

               }

            }

         }


         bool list_view::on_click(::item * pitem)
         {

            if(m_itema[pitem->item_index()]->IsFolder())
            {

               m_pserver->open_folder(m_itema[pitem->item_index()]->m_iFolder);

            }
            else
            {

               m_pserver->open_file(m_iParentFolder, m_itema[pitem->item_index()]->m_strFileName, m_itema[pitem->item_index()]->m_strExtension);

            }

            return true;

         }


         bool list_view::GetSongPath(string &str, index iItem)
         {

            ::user::list_item item(this);
            item.m_iItem = iItem;
            item.m_iSubItem = SubItemFilePath;
            item.m_iListItem = -1;
            _001GetItemText(&item);
            if(!item.m_bOk)
               return false;
            str = item.m_strText;
            return true;
         }

         void list_view::_001OnSort()
         {
            string strSql;

            strSql = "select atom, title, artist, filename, filepath from album";

            if(m_sortinfo.m_itema.get_size() > 0)
            {
               strSql += " order by ";

               for(i32 i = 0; i < m_sortinfo.m_itema.get_size(); i++)
               {
                  CSortInfoItem & item = m_sortinfo.m_itema[i];
                  switch(item.m_iSubItem)
                  {
                  case SubItemId:
                     strSql += "id";
                     break;
                  case SubItemTitle:
                     strSql += "title";
                     break;
                  case SubItemArtist:
                     strSql += "artist";
                     break;
                  case SubItemFileName:
                     strSql += "filename";
                     break;
                  case SubItemFilePath:
                     strSql += "filepath";
                     break;
                  }
                  if(!item.m_bAscendent)
                  {
                     strSql += " desc";
                  }
                  if(i < m_sortinfo.m_itema.get_size() - 1)
                     strSql += ", ";
               }
            }
            strSql += ";";


            /*            critical_section_lock synchronouslock(get_document()->m_pcsAlbum1);
                        get_document()->m_pdsAlbum1->query(strSql);*/

            m_puserlistcache->_001Invalidate(this);

            set_need_redraw();

         }

         void list_view::PostFillTask(string & wstrFile, uptr uiTimer)
         {

            __UNREFERENCED_PARAMETER(wstrFile);
            __UNREFERENCED_PARAMETER(uiTimer);
            ASSERT(false);

         }


         void list_view::fill_task()
         {

            //__UNREFERENCED_PARAMETER(pParameter);

            ASSERT(false);

            /*FillTask * pobjectTask = (FillTask *) pParameter;


            pobjectTask->m_pimpact->KillTimer(1123);

            string & wstrPath = pobjectTask->m_wstrFile;
            MediaLibraryDoc * pdocument = pobjectTask->m_pimpact->get_document();
            __pointer(::sqlite::dataset) pds = pdocument->m_pdsAlbum;

            i32 iFind;
            if((iFind = pdocument->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
            {
            mediamanager::GetMediaManager()->album_build().add(wstrPath, pdocument->m_fileinfo.m_timeaAdd[iFind]);
            pdocument->m_fileinfo.m_wstraAdd.erase_at(iFind);
            pdocument->m_fileinfo.m_timeaAdd.erase_at(iFind);
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
            {
            mediamanager::GetMediaManager()->album_build().Update(wstrPath, pdocument->m_fileinfo.m_timeaUpdate[iFind]);
            pds->SetFieldValue("title", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrTitle));
            pds->SetFieldValue("filename", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrFileName));
            pdocument->m_fileinfo.m_iaUpdate.erase_at(iFind);
            pdocument->m_fileinfo.m_wstraUpdate.erase_at(iFind);
            pdocument->m_fileinfo.m_timeaUpdate.erase_at(iFind);
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
            {
            pdocument->m_fileinfo.m_iaRemove.erase_at(iFind);
            pdocument->m_fileinfo.m_wstraRemove.erase_at(iFind);
            pds->erase_row();
            }

            pobjectTask->m_pimpact->PostMessage(WM_USER + 1217, 0, (LPARAM) pobjectTask);*/




//            return 0;
         }

         void list_view::_001OnTimer(::timer * ptimer)
         {
            simple_list_view::_001OnTimer(ptimer);
            if(ptimer->m_uEvent == 123654)
            {
               KillTimer(123654);
               m_bKickActive = false;

            }
            /*   if(uEvent == 1123)
            {
            KillTimer(1123);
            MediaLibraryDoc * pdocument = get_document();
            if(pdocument->m_bBuilt == true)
            {
            KillTimer(uEvent);
            }
            else
            {
            KillTimer(1124);
            i32 iTopIndex = _001GetTopIndex();
            if(m_buildhelper.m_iTopIndex != iTopIndex)
            {
            m_buildhelper.m_iTopIndex = iTopIndex;
            m_buildhelper.m_iStep = 0;
            }
            i32 iItem;


            __pointer(::sqlite::dataset) pds = pdocument->m_pdsAlbum;

            i32 iRemove = maximum(30, m_buildhelper.m_iDisplayItemCount);

            int_array iaRemove;
            while(true)
            {
            iItem = m_buildhelper.m_iStep + m_buildhelper.m_iTopIndex;

            if(m_buildhelper.m_iStep >= m_buildhelper.m_iDisplayItemCount)
            {
            KillTimer(1123);
            SetTimer(1124, 50, nullptr);
            m_buildhelper.m_bActive = false;
            break;
            }

            m_buildhelper.m_iStep++;

            pds->seek(iItem);

            string wstrPath;
            wstrPath = pds->fv("filepath").get_asString();

            i32 iFind;
            if((iFind = pdocument->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
            {
            PostFillTask(wstrPath, uEvent);
            break;
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
            {
            PostFillTask(wstrPath, uEvent);
            break;
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
            {
            iaRemove.add(pdocument->m_fileinfo.m_iaRemove[iFind]);
            pdocument->m_fileinfo.m_iaRemove.erase_at(iFind);
            pdocument->m_fileinfo.m_wstraRemove.erase_at(iFind);
            pds->erase_row();
            iRemove--;
            m_buildhelper.m_iStep--;
            if(iRemove < 0)
            break;
            }
            }
            mediamanager::GetMediaManager()->album_build().erase(iaRemove);
            }

            }
            else if(uEvent == 1124)
            {
            KillTimer(1124);
            MediaLibraryDoc * pdocument = get_document();
            __pointer(::sqlite::dataset) pds = pdocument->m_pdsAlbum;

            i32 iRemove = maximum(30, m_buildhelper.m_iDisplayItemCount);

            int_array iaRemove;
            i32 iFind = 0;
            sqlite::CFieldValue fv;
            while(true)
            {
            if(iFind < pdocument->m_fileinfo.m_iaUpdate.get_size())
            {
            fv = pdocument->m_fileinfo.m_iaUpdate[iFind];
            if(pds->find_first("id", fv))
            {
            PostFillTask(pds->fv("filepath").get_asString(), uEvent);
            break;
            }
            else
            {
            ASSERT(false);
            }

            }
            else if(iFind < pdocument->m_fileinfo.m_iaRemove.get_size())
            {
            fv = pdocument->m_fileinfo.m_iaRemove[iFind];
            if(pds->find_first("id", fv))
            {
            iaRemove.add(pdocument->m_fileinfo.m_iaRemove[iFind]);
            pdocument->m_fileinfo.m_iaRemove.erase_at(iFind);
            pdocument->m_fileinfo.m_wstraRemove.erase_at(iFind);
            pds->erase_row();
            iRemove--;
            m_buildhelper.m_iStep--;
            if(iRemove < 0)
            break;
            }
            else
            {
            ASSERT(false);
            }
            }
            else
            {
            pdocument->m_bBuilt = true;
            break;
            }
            }
            }*/
         }


         list_view::BuildHelper::BuildHelper()
         {
            m_iTopIndex          = -1;
            m_bActive            = false;
            m_iStep              = -1;
            m_iDisplayItemCount  = -1;
         }

         void list_view::on_message_size(::message::message * pmessage)
         {
            __UNREFERENCED_PARAMETER(pmessage);
            //m_buildhelper.m_iDisplayItemCount = _001GetDisplayItemCount();

         }

         /*void list_view::KickBuildMachine(bool bDisplayOnly)
         {
         if(bDisplayOnly)
         {
         m_buildhelper.m_bActive = true;
         SetTimer(1123, 50, nullptr);
         }
         else
         {
         m_buildhelper.m_bActive = true;
         SetTimer(1124, 50, nullptr);
         }
         }*/

         /*list_view::FillTask::FillTask(__pointer(list_view) pview, LPWString pcsz)

         :
         m_pimpact(pview),m_wstrFile(pcsz)

         {
         }*/

         void list_view::_001OnFillTaskResponse(::message::message * pmessage)
         {
            __pointer(::user::message) pusermessage(pmessage);
            m_bKickActive = true;
            if(pusermessage->m_wparam == 0)
            {

               m_puserlistcache->_001Invalidate(this);

               _001OnUpdateItemCount();

               set_need_layout();

               set_need_redraw();

               //FillTask * pobjectTask = (FillTask *) lparam;


               //if(pobjectTask != nullptr)
               {
                  // SetTimer(pobjectTask->m_uiTimer, 50, nullptr);

                  //delete pobjectTask;
               }

            }
            else if(pusermessage->m_wparam == 1)
            {

               m_puserlistcache->_001Invalidate(this);

               set_need_redraw();

            }
            else if(pusermessage->m_wparam == 2)
            {
               
               _001OnUpdateItemCount();

            }
            else if(pusermessage->m_wparam == 3)
            {
               
               m_puserlistcache->_001Invalidate(this);

            }

         }

         void list_view::start_build(i32 iItem)
         {
            __UNREFERENCED_PARAMETER(iItem);
            auto iTopIndex = m_iTopDisplayIndex;
            auto iDisplayItemCount = m_nDisplayCount;

            if(m_bKickActive &&
                  m_buildhelper.m_iTopIndex == iTopIndex &&
                  m_buildhelper.m_iDisplayItemCount == iDisplayItemCount)
               return;

            m_buildhelper.m_iTopIndex = iTopIndex;
            m_buildhelper.m_iDisplayItemCount = iDisplayItemCount;

            m_bKickActive = true;


            SetTimer(123654, 700_ms, nullptr);

         }


         void list_view::on_message_context_menu(::message::message * pmessage)
         {

            __pointer(::message::context_menu) pcontextmenu(pmessage);

            ::point_i32 point = pcontextmenu->GetPoint();

            screen_to_client(point);

            /*    if(_001HitTest_(point, iItem))
            {
            SimpleMenu menu(BaseMenuCentral::GetMenuCentral(this));
            if (menu.LoadMenu(IDR_POPUP_ALBUM_ITEM))
            {
            SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
            ASSERT(pPopup != nullptr);
            __pointer(::user::frame_window) pframe = get_parent_frame()->get_parent_frame();
            pPopup->track_popup_menu(point.x, point.y,
            (::user::interaction_impl *) pframe);
            }
            }
            else
            {
            ::user::menu menu;
            if (menu.LoadMenu(IDR_POPUP_ALBUM))
            {
            ::user::menu* pPopup = menu.GetSubMenu(0);
            ASSERT(pPopup != nullptr);
            __pointer(::user::frame_window) pframe = get_parent_frame()->get_parent_frame();
            pPopup->track_popup_menu(
            point.x, point.y,
            (::user::interaction_impl *) pframe);
            }
            }*/
         }

         void list_view::parse(const ::string & pszSource)

         {
            m_itema.erase_all();
            _001OnUpdateItemCount(0);

            string str;

            auto pxmldocument = __create_new < xml::document >();

            if(pxmldocument->load(pszSource))
            {

               str  = pxmldocument->get_xml();

            }
            else
            {

               output_error_message("error"); // simple parsing error check

               return;

            }

            pxmldocument->root()->attribute("id").as(m_iParentFolder);

            auto pnodeFolder = pxmldocument->root()->get_child("folder");

            xml::node::array childs;

            string wstrType;
            Item item;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            index iNode = 0;
            for(i32 i = 0 ; i < pnodeFolder->get_children_count(); i++)
            {

               auto pnodeItem = pnodeFolder->child_at(i);

               if(pnodeItem->get_name() == "folder")
               {

                  item.m_iParent = m_iParentFolder;
                  pnodeItem->attribute("id").as(item.m_iFolder);
                  pnodeItem->attribute("name").as(item.m_strTitle);

                  /*            if(wstrType == "normal")
                              {
                                 item.m_etype = ItemTypeFolder;
                              }
                              else if(wstrType == "artist")
                              {
                                 item.m_etype = ItemTypeArtist;
                              }
                              else
                              {
                                 // unknown item type
                                 ASSERT(false);
                              }

                              switch(item.m_etype)
                              {
                              case ItemTypeFolder:
                                 item.m_iImage = m_iIconFolder;
                                 break;
                              case ItemTypeArtist:
                                 item.m_iImage = m_iIconArtist;
                                 break;
                              default:
                                 // unknown item type
                                 break;
                              }

                              */
                  m_itema.add(__new(Item(item)));
                  iNode++;
               }
            }

            auto pnodeFile = pxmldocument->get_child("file");

            for(i32 i = 0; i < pnodeFile->get_children_count(); i++)
            {
               auto pnodeItem = pnodeFile->child_at(i);
               if(pnodeItem->get_name() == "file")
               {
                  wstrType = pnodeItem->attribute("type");
                  item.m_iParent = m_iParentFolder;
                  item.m_iFolder = -1;
                  //               item.m_iId = atoi(pnode->get_child_value("songfileid"));
                  item.m_strTitle = pnodeItem->attribute("name");
                  item.m_strFileName = pnodeItem->attribute("name");
                  item.m_strExtension = pnodeItem->attribute("extension");

                  item.m_etype = ItemTypeSong;
                  item.m_iImage = m_iIconSong;


                  m_itema.add(__new(Item(item)));
                  iNode++;
               }
            }


            _001OnUpdateItemCount();
            iNode++;
         }


         /*i32 ItemArray::FindAbsolute(const ::string & pszId)

         {
            for(i32 i = 0; i < this->get_size(); i++)
            {
               if(this->element_at(i).m_atom == pszId)

                  return i;
            }
            return -1;
         }*/


         bool Item::IsFolder()
         {
            return m_iFolder >= 0;
//            return m_etype == ItemTypeFolder ||
            //             m_etype == ItemTypeArtist;
         }

         // void list_view::_001OnEraseBkgnd(::message::message * pmessage)
         // {
         //    __pointer(::message::erase_bkgnd) perasebkgnd(pmessage);
         //    perasebkgnd->m_bRet = true;
         //    perasebkgnd->set_result(true);
         // }

         ::count list_view::_001GetItemCount()
         {
            /*if(get_document() != nullptr)
            {
            return get_document()->GetSongCount();
            }
            else
            return 0;*/

            return m_itema.get_size();
         }

      } // namespace simple

   }  // namespace fs

}  // namespace filemanager
