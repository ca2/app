#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "axis/xml/_.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         list_view::list_view()
         {

            m_bKickActive = false;

            SetCacheInterface(&m_cache);

            m_pil = __new(::image_list);

            m_pil->create(16, 16, 0, 0, 0);

            m_iIconFolder = m_pil->add_matter_icon("mplite/vmskarlib_folder_normal.ico");

            m_iIconArtist = m_pil->add_matter_icon("mplite/vmskarlib_artist_normal.ico");

            m_iIconSong = m_pil->add_matter_icon("mplite/vmskarlib_song_normal.ico");

         }

         list_view::~list_view()
         {
         }

         void list_view::install_message_routing(::channel * pchannel)
         {
            simple_list_view::install_message_routing(pchannel);
            IGUI_MSG_LINK(WM_LBUTTONDBLCLK, pchannel, this, &list_view::_001OnLButtonDblClk);
//            //IGUI_MSG_LINK(WM_TIMER, pchannel, this, &list_view::_001OnTimer);
            IGUI_MSG_LINK(WM_SIZE, pchannel, this, &list_view::_001OnSize);
            IGUI_MSG_LINK(WM_CONTEXTMENU, pchannel, this, &list_view::_001OnContextMenu);
            IGUI_MSG_LINK(WM_ERASEBKGND, pchannel, this, &list_view::_001OnEraseBkgnd);
            IGUI_MSG_LINK(WM_USER + 1217, pchannel, this, &list_view::_001OnFillTaskResponse);

         }




         void list_view::assert_valid() const
         {
            simple_list_view::assert_valid();
         }

         void list_view::dump(dump_context & dumpcontext) const
         {
            simple_list_view::dump(dumpcontext);
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
               pcolumn->m_crSmallMask = RGB(255, 0, 255);
               pcolumn->m_pil = m_pil;
               */
               pcolumn->m_iWidth = 170;
               //      pcolumn->m_uiText = IDS_PLAYLIST_CODE;
               pcolumn->m_iSubItem = SubItemTitle;
               //      pcolumn->m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
               pcolumn->m_iSmallImageWidth = 16;
               pcolumn->m_crSmallMask = RGB(255, 0, 255);
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
               //ASSERT(FALSE);
               pitem->m_strText.Empty();
               break;
            }
            pitem->m_bOk = true;
         }

         void list_view::_001SearchGetItemText(::user::mesh_item * pitem)
         {
            return_(pitem->m_bOk, false);
         }


         void list_view::update(::update * pupdate)
         {

            simple_list_view::update(pupdate);

            //if(::is_null(pobject))
            {

              // _001UpdateColumns();

            }
            //else
            {

            }

         }


         void list_view::_001OnLButtonDblClk(::message::message * pmessage)
         {

            SCAST_PTR(::message::mouse, pmouse, pmessage);

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


         bool list_view::on_click(const ::user::item & item)
         {

            if(m_itema[item.item_index()]->IsFolder())
            {

               m_pserver->open_folder(m_itema[item.item_index()]->m_iFolder);

            }
            else
            {

               m_pserver->open_file(m_iParentFolder, m_itema[item.item_index()]->m_strFileName, m_itema[item.item_index()]->m_strExtension);

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

            strSql = "select id, title, artist, filename, filepath from album";

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


            /*            cslock sl(get_document()->m_pcsAlbum1);
                        get_document()->m_pdsAlbum1->query(strSql);*/

            m_cache._001Invalidate(this);

            set_need_redraw();

         }

         void list_view::PostFillTask(string & wstrFile, uptr uiTimer)
         {

            UNREFERENCED_PARAMETER(wstrFile);
            UNREFERENCED_PARAMETER(uiTimer);
            ASSERT(FALSE);

         }

         UINT c_cdecl list_view::ThreadProcFillTask(LPVOID pParameter)

         {
            UNREFERENCED_PARAMETER(pParameter);

            ASSERT(FALSE);

            /*FillTask * pobjectTask = (FillTask *) pParameter;


            pobjectTask->m_pview->KillTimer(1123);

            string & wstrPath = pobjectTask->m_wstrFile;
            MediaLibraryDoc * pdocument = pobjectTask->m_pview->get_document();
            __pointer(::sqlite::dataset) pds = pdocument->m_pdsAlbum;

            i32 iFind;
            if((iFind = pdocument->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
            {
            mediamanager::GetMediaManager()->album_build().add(wstrPath, pdocument->m_fileinfo.m_timeaAdd[iFind]);
            pdocument->m_fileinfo.m_wstraAdd.remove_at(iFind);
            pdocument->m_fileinfo.m_timeaAdd.remove_at(iFind);
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
            {
            mediamanager::GetMediaManager()->album_build().Update(wstrPath, pdocument->m_fileinfo.m_timeaUpdate[iFind]);
            pds->SetFieldValue("title", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrTitle));
            pds->SetFieldValue("filename", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrFileName));
            pdocument->m_fileinfo.m_iaUpdate.remove_at(iFind);
            pdocument->m_fileinfo.m_wstraUpdate.remove_at(iFind);
            pdocument->m_fileinfo.m_timeaUpdate.remove_at(iFind);
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
            {
            pdocument->m_fileinfo.m_iaRemove.remove_at(iFind);
            pdocument->m_fileinfo.m_wstraRemove.remove_at(iFind);
            pds->remove_row();
            }

            pobjectTask->m_pview->PostMessage(WM_USER + 1217, 0, (LPARAM) pobjectTask);*/




            return 0;
         }

         void list_view::_001OnTimer(::timer * ptimer)
         {
            simple_list_view::_001OnTimer(ptimer);
            if(ptimer->m_nIDEvent == 123654)
            {
               KillTimer(123654);
               m_bKickActive = false;

            }
            /*   if(nIDEvent == 1123)
            {
            KillTimer(1123);
            MediaLibraryDoc * pdocument = get_document();
            if(pdocument->m_bBuilt == true)
            {
            KillTimer(nIDEvent);
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

            i32 iRemove = MAX(30, m_buildhelper.m_iDisplayItemCount);

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
            PostFillTask(wstrPath, nIDEvent);
            break;
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
            {
            PostFillTask(wstrPath, nIDEvent);
            break;
            }
            else if((iFind = pdocument->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
            {
            iaRemove.add(pdocument->m_fileinfo.m_iaRemove[iFind]);
            pdocument->m_fileinfo.m_iaRemove.remove_at(iFind);
            pdocument->m_fileinfo.m_wstraRemove.remove_at(iFind);
            pds->remove_row();
            iRemove--;
            m_buildhelper.m_iStep--;
            if(iRemove < 0)
            break;
            }
            }
            mediamanager::GetMediaManager()->album_build().remove(iaRemove);
            }

            }
            else if(nIDEvent == 1124)
            {
            KillTimer(1124);
            MediaLibraryDoc * pdocument = get_document();
            __pointer(::sqlite::dataset) pds = pdocument->m_pdsAlbum;

            i32 iRemove = MAX(30, m_buildhelper.m_iDisplayItemCount);

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
            PostFillTask(pds->fv("filepath").get_asString(), nIDEvent);
            break;
            }
            else
            {
            ASSERT(FALSE);
            }

            }
            else if(iFind < pdocument->m_fileinfo.m_iaRemove.get_size())
            {
            fv = pdocument->m_fileinfo.m_iaRemove[iFind];
            if(pds->find_first("id", fv))
            {
            iaRemove.add(pdocument->m_fileinfo.m_iaRemove[iFind]);
            pdocument->m_fileinfo.m_iaRemove.remove_at(iFind);
            pdocument->m_fileinfo.m_wstraRemove.remove_at(iFind);
            pds->remove_row();
            iRemove--;
            m_buildhelper.m_iStep--;
            if(iRemove < 0)
            break;
            }
            else
            {
            ASSERT(FALSE);
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

         void list_view::_001OnSize(::message::message * pmessage)
         {
            UNREFERENCED_PARAMETER(pmessage);
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
         m_pview(pview),m_wstrFile(pcsz)

         {
         }*/

         void list_view::_001OnFillTaskResponse(::message::message * pmessage)
         {
            SCAST_PTR(::message::base, pbase, pmessage);
            m_bKickActive = true;
            if(pbase->m_wparam == 0)
            {

               m_cache._001Invalidate(this);

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
            else if(pbase->m_wparam == 1)
            {

               m_cache._001Invalidate(this);
               set_need_redraw();
            }
            else if(pbase->m_wparam == 2)
            {
               _001OnUpdateItemCount();
            }
            else if(pbase->m_wparam == 3)
            {
               m_cache._001Invalidate(this);
            }
         }

         void list_view::start_build(i32 iItem)
         {
            UNREFERENCED_PARAMETER(iItem);
            auto iTopIndex = m_iTopDisplayIndex;
            auto iDisplayItemCount = m_nDisplayCount;

            if(m_bKickActive &&
                  m_buildhelper.m_iTopIndex == iTopIndex &&
                  m_buildhelper.m_iDisplayItemCount == iDisplayItemCount)
               return;

            m_buildhelper.m_iTopIndex = iTopIndex;
            m_buildhelper.m_iDisplayItemCount = iDisplayItemCount;

            m_bKickActive = true;


            SetTimer(123654, 700, nullptr);

         }

         void list_view::_001OnContextMenu(::message::message * pmessage)
         {

            SCAST_PTR(::message::context_menu, pcontextmenu, pmessage);

            ::point point = pcontextmenu->GetPoint();

            _001ScreenToClient(point);

            /*    if(_001HitTest_(point, iItem))
            {
            SimpleMenu menu(BaseMenuCentral::GetMenuCentral(get_object()));
            if (menu.LoadMenu(IDR_POPUP_ALBUM_ITEM))
            {
            SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
            ASSERT(pPopup != nullptr);
            __pointer(::user::frame_window) pframe = GetParentFrame()->GetParentFrame();
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
            __pointer(::user::frame_window) pframe = GetParentFrame()->GetParentFrame();
            pPopup->track_popup_menu(
            point.x, point.y,
            (::user::interaction_impl *) pframe);
            }
            }*/
         }

         void list_view::parse(const char * pszSource)

         {
            m_itema.remove_all();
            _001OnUpdateItemCount(0);

            string str;

            xml::document doc;

            if(doc.load(pszSource))

            {
               str  = doc.get_xml();
            }
            else
            {
               System.message_box("error"); // simple parsing error check
               return;
            }


            m_iParentFolder = doc.root()->attribute("id");

            __pointer(::xml::node) pnodeFolder = doc.root()->get_child("folder");


            xml::node::array childs;

            string wstrType;
            Item item;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            index iNode = 0;
            for(i32 i = 0 ; i < pnodeFolder->get_children_count(); i++)
            {
               __pointer(::xml::node) pnodeItem = pnodeFolder->child_at(i);
               if(pnodeItem->get_name() == "folder")
               {
                  item.m_iParent = m_iParentFolder;
                  item.m_iFolder = pnodeItem->attribute("id");
                  item.m_strTitle = pnodeItem->attribute("name");

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
                                 ASSERT(FALSE);
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

            __pointer(::xml::node) pnodeFile = doc.get_child("file");

            for(i32 i = 0; i < pnodeFile->get_children_count(); i++)
            {
               __pointer(::xml::node) pnodeItem = pnodeFile->child_at(i);
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


         /*i32 ItemArray::FindAbsolute(const char * pszId)

         {
            for(i32 i = 0; i < this->get_size(); i++)
            {
               if(this->element_at(i).m_id == pszId)

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

         void list_view::_001OnEraseBkgnd(::message::message * pmessage)
         {
            SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pmessage);
            perasebkgnd->m_bRet = true;
            perasebkgnd->set_result(TRUE);
         }

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
