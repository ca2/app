// Created by camilo on 2023-08-12 20:42 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "list2.h"
#include "acme/constant/user_message.h"
#include "acme/user/user/content.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/message/user.h"
#include "aura/user/user/still.h"
#include "axis/user/user/line_layout.h"
#include "core/user/user/list_column.h"
#include "core/user/user/mesh_item.h"


namespace user
{



   list2::list2()
   {

      m_bDefaultClickHandling = true;

   }

   list2::~list2()
   {

   }



   void list2::install_message_routing(::channel * psender)
   {

      ::user::scroll_base::install_message_routing(psender);

      MESSAGE_LINK(::user::e_message_create, psender, this, &list2::on_message_create);

      // add_command_handler("generate_and_copy_button", { this, &form_001::_001OnGenerateAndCopyButton });
      //add_command_handler("clear_button", { this, &form_001::_001OnClearButton });

   }


   void list2::on_message_create(::message::message * pmessage)
   {

      ::pointer < ::message::create > pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

    /*  fork([this]()
         {

            update_data();

         });*/


      //auto puser = øcreate_new <user>();

      //puser->m_strEmail = "aaa@aaa.com";

      //m_pitema->add(puser);


      //plabelTitle->set_font(pfont);

      //øconstruct_new(m_pstill);

      //øconstruct_new(m_pedit);

      //øconstruct_new(m_pbuttonClear);

      //øconstruct_new(m_pbuttonGenerateAndCopy);

      //øconstruct_new(m_pstillKey);

      //øconstruct_new(m_peditKey);

      //øconstruct_new(m_pstillTrial);

      //øconstruct_new(m_pcheckboxTrial);

      //øconstruct_new(m_pstillDays);

      //øconstruct_new(m_peditDays);

      //øconstruct_new(m_pstillYear);

      //øconstruct_new(m_peditYear);
      //
      //øconstruct_new(m_pstillMonth);
      //
      //øconstruct_new(m_peditMonth);

      //øconstruct_new(m_pstillDay);

      //øconstruct_new(m_peditDay);

      //m_pstill->create_control(this, "still");

      //m_pedit->create_control(this, "edit");

      //m_pedit->add_handler(this);

      //m_pstillTrial->create_control(this, "still_trial");

      //m_pstillTrial->m_ealignText = e_align_right_center;

      //m_pstillTrial->set_window_text("Trial");

      //m_pcheckboxTrial->create_control(this, "check_box_trial");

      //m_pcheckboxTrial->add_handler(this);

      //m_pstillDays->create_control(this, "still_days");

      //m_pstillDays->m_ealignText = e_align_right_center;

      //m_pstillDays->set_window_text("Days");

      //m_peditDays->create_control(this, "edit_days");

      //m_peditDays->add_handler(this);

      //m_pstillYear->create_control(this, "still_year");

      //m_pstillYear->m_ealignText = e_align_right_center;

      //m_pstillYear->set_window_text("Year");

      //m_peditYear->create_control(this, "edit_year");

      //m_peditYear->add_handler(this);

      //m_pstillMonth->create_control(this, "still_month");

      //m_pstillMonth->m_ealignText = e_align_right_center;

      //m_pstillMonth->set_window_text("Month");

      //m_peditMonth->create_control(this, "edit_month");

      //m_peditMonth->add_handler(this);

      //m_pstillDay->create_control(this, "still_day");

      //m_pstillDay->m_ealignText = e_align_right_center;

      //m_pstillDay->set_window_text("Day");

      //m_peditDay->create_control(this, "edit_day");

      //m_peditDay->add_handler(this);

      //m_pbuttonClear->create_control(this, "clear_button");

      //m_pbuttonClear->add_handler(this);

      //m_pbuttonGenerateAndCopy->create_control(this, "generate_and_copy_button");

      //m_pbuttonGenerateAndCopy->add_handler(this);

      //m_pstill->set_window_text("Hardware Id");

      //m_pstill->m_ealignText = e_align_right_center;


      //m_pstillKey->create_control(this, "still_key");

      //m_pstillKey->m_ealignText = e_align_right_center;

      //m_pstillKey->set_window_text("Key");

      //m_peditKey->create_control(this, "edit_key");

      //m_peditKey->set_window_text("(Waiting to receive...)");

      ////m_pedit->m_strEmtpyText = "Enter New Text Here";

      //string strInitialText;

      //auto papp = get_app();

      //papp->datastream()->get("last_text", strInitialText);

      //m_pedit->set_text(strInitialText, ::e_source_initialize);

      //m_pbuttonClear->set_window_text("Clear");

      //m_pbuttonGenerateAndCopy->set_window_text("Generate & Copy");

   }


   //void list2::_001InsertColumns()
   //{

   //   {
   //      auto pcolumn = new_list_column();
   //      /*

   //      pcolumn->m_iWidth = 50;
   //      //      pcolumn->m_uiText = IDS_PLAYLIST_CODE;
   //      pcolumn->m_iSubItem = SubItemId;
   //      //      pcolumn->m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
   //      pcolumn->m_iSmallImageWidth = 16;
   //      pcolumn->m_colorSmallMask = rgb(255, 0, 255);
   //      pcolumn->m_pimagelist = m_pimagelist;
   //      */
   //      pcolumn->m_iWidth = 170;
   //      //      pcolumn->m_uiText = IDS_PLAYLIST_CODE;
   //      pcolumn->m_iSubItem = SubItemEmail;
   //      //      pcolumn->m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
   //      pcolumn->m_iSmallImageWidth = 16;
   //      pcolumn->m_colorSmallMask = rgb(255, 0, 255);
   //      //pcolumn->m_pimagelist = m_pimagelist;


   //   }

   //   //{

   //   //   auto pcolumn = new_list_column();
   //   //   //      pcolumn->m_uiText = IDS_PLAYLIST_SONG_NAME;
   //   //   pcolumn->m_iWidth = 200;
   //   //   pcolumn->m_iSubItem = SubItemArtist;


   //   //}


   //   //{
   //   //   auto pcolumn = new_list_column();

   //   //   //      pcolumn->m_uiText = IDS_PLAYLIST_SONG_NAME;
   //   //   pcolumn->m_iWidth = 400;
   //   //   pcolumn->m_iSubItem = SubItemFileName;


   //   //}


   //   //{

   //   //   auto pcolumn = new_list_column();

   //   //   pcolumn->m_iWidth = 400;
   //   //   pcolumn->m_iSubItem = SubItemFilePath;


   //   //}


   //}


   //void list2::_001GetSubItemImage(::user::mesh_subitem* psubitem)
   //{

   //   if (psubitem->m_pitem->m_iItem < 0 || psubitem->m_pitem->m_iItem >= m_useritema.get_size())
   //   {

   //      psubitem->m_bOk = false;

   //      return;

   //   }

   //   if (psubitem->m_iSubItem == SubItemEmail)
   //   {

   //      psubitem->m_bOk = true;

   //         psubitem->m_iImage =0;
   //         
   //      return;
   //   }
   //   else
   //   {
   //      psubitem->m_bOk = false;
   //      return;
   //   }

   //}


   //void list2::_001GetSubItemText(::user::mesh_subitem* psubitem)
   //{

   //   if (psubitem->m_pitem->m_iItem < 0 || psubitem->m_pitem->m_iItem >= m_useritema.get_size())
   //   {

   //      psubitem->m_bOk = false;

   //      return;

   //   }

   //   switch (psubitem->m_iSubItem)
   //   {
   //   case SubItemEmail:
   //      psubitem->m_strText = m_useritema[psubitem->m_pitem->m_iItem]->m_strEmail;
   //      break;
   //   default:
   //      //ASSERT(false);
   //      psubitem->m_strText.empty();
   //      break;
   //   }
   //   psubitem->m_bOk = true;
   //}


   //void list2::_001SearchGetSubItemText(::user::mesh_subitem* psubitem)
   //{

   //   return_(psubitem->m_bOk, false);

   //}


   void list2::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::scroll_base::handle(ptopic, phandlercontext);

      //if(::is_null(pparticle))
      {

         // _001UpdateColumns();

      }
      //else
      {

      }

   }


   //void list2::on_message_left_button_double_click(::message::message* pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   index iItem;

   //   if (_001HitTest_(pmouse->m_point, iItem))
   //   {

   //      //if (m_useritema[iItem]->IsFolder())
   //      //{

   //      //   m_pserver->open_folder(m_useritema[iItem]->m_iFolder);

   //      //}
   //      //else
   //      //{

   //      //   m_pserver->open_file(m_iParentFolder, m_useritema[iItem]->m_strFileName, m_useritema[(::collection::index)iItem]->m_strExtension);

   //      //}

   //   }

   //}


   //bool list2::on_click(::item* pitem)
   //{

   //   //if (m_useritema[pitem->item_index()]->IsFolder())
   //   //{

   //   //   m_pserver->open_folder(m_useritema[pitem->item_index()]->m_iFolder);

   //   //}
   //   //else
   //   //{

   //   //   m_pserver->open_file(m_iParentFolder, m_useritema[pitem->item_index()]->m_strFileName, m_useritema[pitem->item_index()]->m_strExtension);

   //   //}

   //   return true;

   //}


   //bool list2::GetSongPath(string& str, ::collection::index iItem)
   //{

   //   auto& pdrawlistsubitem = get_subitem(iItem, SubItemFilePath);

   //   _001GetSubItemText(pdrawlistsubitem);

   //   if (!pdrawlistsubitem->m_bOk)
   //   {

   //      return false;

   //   }

   //   str = pdrawlistsubitem->m_strText;

   //   return true;

   //}


   //void list2::_001OnSort()
   //{
   //   string strSql;

   //   strSql = "select atom, title, artist, filename, filepath from album";

   //   if (m_sortinfo.m_useritema.get_size() > 0)
   //   {
   //      strSql += " order by ";

   //      for (int i = 0; i < m_sortinfo.m_useritema.get_size(); i++)
   //      {
   //         CSortInfoItem& item = m_sortinfo.m_useritema[i];
   //         switch (item.m_iSubItem)
   //         {
   //         case SubItemId:
   //            strSql += "id";
   //            break;
   //         case SubItemTitle:
   //            strSql += "title";
   //            break;
   //         case SubItemArtist:
   //            strSql += "artist";
   //            break;
   //         case SubItemFileName:
   //            strSql += "filename";
   //            break;
   //         case SubItemFilePath:
   //            strSql += "filepath";
   //            break;
   //         }
   //         if (!item.m_bAscendent)
   //         {
   //            strSql += " desc";
   //         }
   //         if (i < m_sortinfo.m_useritema.get_size() - 1)
   //            strSql += ", ";
   //      }
   //   }
   //   strSql += ";";


   //   /*            critical_section_lock synchronouslock(get_document()->m_pcsAlbum1);
   //               get_document()->m_pdsAlbum1->query(strSql);*/

   //   m_puserlistcache->_001Invalidate(this);

   //   set_need_redraw();

   //}

   //void list2::PostFillTask(string& wstrFile, uptr uiTimer)
   //{

   //   __UNREFERENCED_PARAMETER(wstrFile);
   //   __UNREFERENCED_PARAMETER(uiTimer);
   //   ASSERT(false);

   //}


   //void list2::fill_task()
   //{

   //   //__UNREFERENCED_PARAMETER(pParameter);

   //   ASSERT(false);

   //   /*FillTask * pobjectTask = (FillTask *) pParameter;


   //   pobjectTask->m_pimpact->kill_timer(1123);

   //   string & wstrPath = pobjectTask->m_wstrFile;
   //   MediaLibraryDoc * pdocument = pobjectTask->m_pimpact->get_document();
   //   ::pointer<::sqlite::dataset>pds = pdocument->m_pdsAlbum;

   //   int iFind;
   //   if((iFind = pdocument->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
   //   {
   //   mediamanager::GetMediaManager()->album_build().add(wstrPath, pdocument->m_fileinfo.m_timeaAdd[iFind]);
   //   pdocument->m_fileinfo.m_wstraAdd.erase_at(iFind);
   //   pdocument->m_fileinfo.m_timeaAdd.erase_at(iFind);
   //   }
   //   else if((iFind = pdocument->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
   //   {
   //   mediamanager::GetMediaManager()->album_build().Update(wstrPath, pdocument->m_fileinfo.m_timeaUpdate[iFind]);
   //   pds->SetFieldValue("title", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrTitle));
   //   pds->SetFieldValue("filename", sqlite::CFieldValue(mediamanager::GetMediaManager()->album_build().album_record().m_wstrFileName));
   //   pdocument->m_fileinfo.m_iaUpdate.erase_at(iFind);
   //   pdocument->m_fileinfo.m_wstraUpdate.erase_at(iFind);
   //   pdocument->m_fileinfo.m_timeaUpdate.erase_at(iFind);
   //   }
   //   else if((iFind = pdocument->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
   //   {
   //   pdocument->m_fileinfo.m_iaRemove.erase_at(iFind);
   //   pdocument->m_fileinfo.m_wstraRemove.erase_at(iFind);
   //   pds->erase_row();
   //   }

   //   pobjectTask->m_pimpact->PostMessage(WM_USER + 1217, 0, (LPARAM) pobjectTask);*/




   //   //            return 0;
   //}

   //void list2::on_timer(::timer* ptimer)
   //{
   //   simple_user_list::on_timer(ptimer);
   //   if (ptimer->m_uTimer == 123654)
   //   {
   //      kill_timer(123654);
   //      m_bKickActive = false;

   //   }
   //   /*   if(uEvent == 1123)
   //   {
   //   kill_timer(1123);
   //   MediaLibraryDoc * pdocument = get_document();
   //   if(pdocument->m_bBuilt == true)
   //   {
   //   kill_timer(uEvent);
   //   }
   //   else
   //   {
   //   kill_timer(1124);
   //   int iTopIndex = _001GetTopIndex();
   //   if(m_buildhelper.m_iTopIndex != iTopIndex)
   //   {
   //   m_buildhelper.m_iTopIndex = iTopIndex;
   //   m_buildhelper.m_iStep = 0;
   //   }
   //   int iItem;


   //   ::pointer<::sqlite::dataset>pds = pdocument->m_pdsAlbum;

   //   int iRemove = maximum(30, m_buildhelper.m_iDisplayItemCount);

   //   ::int_array_base iaRemove;
   //   while(true)
   //   {
   //   iItem = m_buildhelper.m_iStep + m_buildhelper.m_iTopIndex;

   //   if(m_buildhelper.m_iStep >= m_buildhelper.m_iDisplayItemCount)
   //   {
   //   kill_timer(1123);
   //   set_timer(1124, 50, nullptr);
   //   m_buildhelper.m_bActive = false;
   //   break;
   //   }

   //   m_buildhelper.m_iStep++;

   //   pds->seek(iItem);

   //   string wstrPath;
   //   wstrPath = pds->fv("filepath").get_asString();

   //   int iFind;
   //   if((iFind = pdocument->m_fileinfo.m_wstraAdd.FindFirst(wstrPath)) >= 0)
   //   {
   //   PostFillTask(wstrPath, uEvent);
   //   break;
   //   }
   //   else if((iFind = pdocument->m_fileinfo.m_wstraUpdate.FindFirst(wstrPath)) >= 0)
   //   {
   //   PostFillTask(wstrPath, uEvent);
   //   break;
   //   }
   //   else if((iFind = pdocument->m_fileinfo.m_wstraRemove.FindFirst(wstrPath)) >= 0)
   //   {
   //   iaRemove.add(pdocument->m_fileinfo.m_iaRemove[iFind]);
   //   pdocument->m_fileinfo.m_iaRemove.erase_at(iFind);
   //   pdocument->m_fileinfo.m_wstraRemove.erase_at(iFind);
   //   pds->erase_row();
   //   iRemove--;
   //   m_buildhelper.m_iStep--;
   //   if(iRemove < 0)
   //   break;
   //   }
   //   }
   //   mediamanager::GetMediaManager()->album_build().erase(iaRemove);
   //   }

   //   }
   //   else if(uEvent == 1124)
   //   {
   //   kill_timer(1124);
   //   MediaLibraryDoc * pdocument = get_document();
   //   ::pointer<::sqlite::dataset>pds = pdocument->m_pdsAlbum;

   //   int iRemove = maximum(30, m_buildhelper.m_iDisplayItemCount);

   //   ::int_array_base iaRemove;
   //   auto pFind = 0;
   //   sqlite::CFieldValue fv;
   //   while(true)
   //   {
   //   if(iFind < pdocument->m_fileinfo.m_iaUpdate.get_size())
   //   {
   //   fv = pdocument->m_fileinfo.m_iaUpdate[iFind];
   //   if(pds->find_first("id", fv))
   //   {
   //   PostFillTask(pds->fv("filepath").get_asString(), uEvent);
   //   break;
   //   }
   //   else
   //   {
   //   ASSERT(false);
   //   }

   //   }
   //   else if(iFind < pdocument->m_fileinfo.m_iaRemove.get_size())
   //   {
   //   fv = pdocument->m_fileinfo.m_iaRemove[iFind];
   //   if(pds->find_first("id", fv))
   //   {
   //   iaRemove.add(pdocument->m_fileinfo.m_iaRemove[iFind]);
   //   pdocument->m_fileinfo.m_iaRemove.erase_at(iFind);
   //   pdocument->m_fileinfo.m_wstraRemove.erase_at(iFind);
   //   pds->erase_row();
   //   iRemove--;
   //   m_buildhelper.m_iStep--;
   //   if(iRemove < 0)
   //   break;
   //   }
   //   else
   //   {
   //   ASSERT(false);
   //   }
   //   }
   //   else
   //   {
   //   pdocument->m_bBuilt = true;
   //   break;
   //   }
   //   }
   //   }*/
   //}


   //void list2::on_message_size(::message::message* pmessage)
   //{
   //   __UNREFERENCED_PARAMETER(pmessage);
   //   //m_buildhelper.m_iDisplayItemCount = _001GetDisplayItemCount();

   //}

   /*void list2::KickBuildMachine(bool bDisplayOnly)
   {
   if(bDisplayOnly)
   {
   m_buildhelper.m_bActive = true;
   set_timer(1123, 50, nullptr);
   }
   else
   {
   m_buildhelper.m_bActive = true;
   set_timer(1124, 50, nullptr);
   }
   }*/

   /*list2::FillTask::FillTask(::pointer<list2>pimpact, LPWString pcsz)

   :
   m_pimpact(pimpact),m_wstrFile(pcsz)

   {
   }*/

   //void list2::_001OnFillTaskResponse(::message::message* pmessage)
   //{
   //   ::pointer<::user::message>pusermessage(pmessage);
   //   m_bKickActive = true;
   //   if (pusermessage->m_wparam == 0)
   //   {

   //      m_puserlistcache->_001Invalidate(this);

   //      _001OnUpdateItemCount();

   //      set_need_layout();

   //      set_need_redraw();

   //      //FillTask * pobjectTask = (FillTask *) lparam;


   //      //if(pobjectTask != nullptr)
   //      {
   //         // set_timer(pobjectTask->m_uiTimer, 50, nullptr);

   //         //delete pobjectTask;
   //      }

   //   }
   //   else if (pusermessage->m_wparam == 1)
   //   {

   //      m_puserlistcache->_001Invalidate(this);

   //      set_need_redraw();

   //   }
   //   else if (pusermessage->m_wparam == 2)
   //   {

   //      _001OnUpdateItemCount();

   //   }
   //   else if (pusermessage->m_wparam == 3)
   //   {

   //      m_puserlistcache->_001Invalidate(this);

   //   }

   //}

   //void list2::start_build(int iItem)
   //{
   //   __UNREFERENCED_PARAMETER(iItem);
   //   auto iTopIndex = m_iTopDisplayIndex;
   //   auto iDisplayItemCount = m_nDisplayCount;

   //   if (m_bKickActive &&
   //      m_buildhelper.m_iTopIndex == iTopIndex &&
   //      m_buildhelper.m_iDisplayItemCount == iDisplayItemCount)
   //      return;

   //   m_buildhelper.m_iTopIndex = iTopIndex;
   //   m_buildhelper.m_iDisplayItemCount = iDisplayItemCount;

   //   m_bKickActive = true;


   //   set_timer(123654, 700_ms, nullptr);

   //}


   //void list2::on_message_context_menu(::message::message* pmessage)
   //{

   //   ::pointer<::message::context_menu>pcontextmenu(pmessage);

   //   ::int_point point = pcontextmenu->GetPoint();

   //   screen_to_client()(point);

   //   /*    if(_001HitTest_(point, iItem))
   //   {
   //   SimpleMenu menu(BaseMenuCentral::GetMenuCentral(this));
   //   if (menu.LoadMenu(IDR_POPUP_ALBUM_ITEM))
   //   {
   //   SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
   //   ASSERT(pPopup != nullptr);
   //   ::pointer<::user::frame_window>pframe = get_parent_frame()->get_parent_frame();
   //   pPopup->track_popup_menu(point.x(), point.y(),
   //   (::windowing::window *) pframe);
   //   }
   //   }
   //   else
   //   {
   //   ::user::menu menu;
   //   if (menu.LoadMenu(IDR_POPUP_ALBUM))
   //   {
   //   ::user::menu* pPopup = menu.GetSubMenu(0);
   //   ASSERT(pPopup != nullptr);
   //   ::pointer<::user::frame_window>pframe = get_parent_frame()->get_parent_frame();
   //   pPopup->track_popup_menu(
   //   point.x(), point.y(),
   //   (::windowing::window *) pframe);
   //   }
   //   }*/
   //}


   //void list2::parse(const ::scoped_string & scopedstrXml)
   //{

   //   m_useritema.erase_all();

   //   _001OnUpdateItemCount(0);

   //   auto pxmldocument = øcreate_new < xml::document >();

   //   pxmldocument->load(strXml);

   //   m_iParentFolder = pxmldocument->root()->attribute("id").as_int();

   //   auto pnodeFolder = pxmldocument->root()->get_child("folder");

   //   xml::node::array childs;

   //   string wstrType;
   //   Item item;
   //   // method 3: Selected Childs with GetChilds()
   //   // Result: Person, Person, Person
   //   index iNode = 0;
   //   for (int i = 0; i < pnodeFolder->get_children_count(); i++)
   //   {

   //      auto pnodeItem = pnodeFolder->child_at(i);

   //      if (pnodeItem->get_name() == "folder")
   //      {

   //         item.m_iParent = m_iParentFolder;
   //         item.m_iFolder = pnodeItem->attribute("id");
   //         item.m_strTitle = pnodeItem->attribute("name");

   //         /*            if(wstrType == "normal")
   //                     {
   //                        item.m_etype = ItemTypeFolder;
   //                     }
   //                     else if(wstrType == "artist")
   //                     {
   //                        item.m_etype = ItemTypeArtist;
   //                     }
   //                     else
   //                     {
   //                        // unknown item type
   //                        ASSERT(false);
   //                     }

   //                     switch(item.m_etype)
   //                     {
   //                     case ItemTypeFolder:
   //                        item.m_iImage = m_iIconFolder;
   //                        break;
   //                     case ItemTypeArtist:
   //                        item.m_iImage = m_iIconArtist;
   //                        break;
   //                     default:
   //                        // unknown item type
   //                        break;
   //                     }

   //                     */
   //         m_useritema.add(øallocate Item(item));
   //         iNode++;
   //      }
   //   }

   //   auto pnodeFile = pxmldocument->get_child("file");

   //   for (int i = 0; i < pnodeFile->get_children_count(); i++)
   //   {
   //      auto pnodeItem = pnodeFile->child_at(i);
   //      if (pnodeItem->get_name() == "file")
   //      {
   //         wstrType = pnodeItem->attribute("type");
   //         item.m_iParent = m_iParentFolder;
   //         item.m_iFolder = -1;
   //         //               item.m_iId = atoi(pnode->get_child_value("songfileid"));
   //         item.m_strTitle = pnodeItem->attribute("name");
   //         item.m_strFileName = pnodeItem->attribute("name");
   //         item.m_strExtension = pnodeItem->attribute("extension");

   //         item.m_etype = ItemTypeSong;
   //         item.m_iImage = m_iIconSong;


   //         m_useritema.add(øallocate Item(item));
   //         iNode++;
   //      }
   //   }


   //   _001OnUpdateItemCount();
   //   iNode++;
   //}


   /*int ItemArray::FindAbsolute(const ::scoped_string & scopedstrId)

   {
      for(int i = 0; i < this->get_size(); i++)
      {
         if(this->element_at(i).id() == pszId)

            return i;
      }
      return -1;
   }*/


   //bool Item::IsFolder()
   //{
   //   return m_iFolder >= 0;
   //   //            return m_etype == ItemTypeFolder ||
   //               //             m_etype == ItemTypeArtist;
   //}

   // void list2::_001OnEraseBkgnd(::message::message * pmessage)
   // {
   //    ::pointer<::message::erase_bkgnd>perasebkgnd(pmessage);
   //    perasebkgnd->m_bRet = true;
   //    perasebkgnd->set_result(true);
   // }


   void list2::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      int x = 5;
      int y = 5;

      auto rectangleX = this->rectangle();

      auto pstyle = get_style(pgraphics);

      auto pfont = øcreate < ::write_text::font >();

      pfont->create_font(e_font_sans_ui, 12_pt);

      pgraphics->set(pfont);

      pfont->defer_update(pgraphics, 0);

      auto iLineHeight = pfont->get_height(pgraphics);

      iLineHeight *= 1.25;

      for (::collection::index i = 0; i < main_content().m_pitema->size(); i++)
      {

         auto pitem = main_content().m_pitema->element_at(i);

         auto puseritembase = user_item_base(pitem);

         auto puseritem = puseritembase->m_puseritem;

         puseritem->m_rectangle2.left() = 0;
         puseritem->m_rectangle2.right() = rectangleX.width();
         puseritem->m_rectangle2.top() = y;
         puseritem->m_rectangle2.bottom() = (int) (y + iLineHeight);

         ::user::enum_state estate = ::user::e_state_none;

         if (pitem == m_pitemHover)
         {

            estate = estate | ::user::e_state_hover;

         }

         auto color = get_color(pstyle, ::e_element_item_text, estate);

         pgraphics->set_text_color(color);

         pgraphics->text_out(x, (int) y, pitem->get_item_text(puseritembase));

         y = (int) (y + iLineHeight);

      }

   }


   //void list2::update_data()
   //{

   //   m_pitema->clear();

   //   auto puser = øcreate_new <user>();

   //   puser->m_strEmail = "Loading...";

   //   m_pitema->add(puser);

   //   set_need_redraw();

   //   post_redraw();

   //   string strUrl = "https://ppp.reddotlogics.com/list2";

   //   string str;

   //   ::property_set set;

   //   //auto purl = system()->url();

   //   //strGetUrl = "https://api.ca2.network/account/openweather?request=" + ::url::encode(strUrl);

   //   //auto pcontext = m_papplication;

   //   auto payload = api_get(strUrl, set);

   //   auto pitema = øcreate_new < pointer_array < ::item > >();

   //   for (auto & row : payload.payload_array_reference())
   //   {

   //      auto puser = øcreate_new <user>();

   //      puser->m_strEmail = row[0];

   //      pitema->add(puser);

   //      //         m_pitema->add(pitem);

   //   }

   //   //str = http()->get(strGetUrl, set);

   //   //auto iHttpStatusCode = set["http_status_code"].as_int();

   //   //synchronous_lock synchronouslock(this->synchronization());

   //   //if (str.is_empty() || iHttpStatusCode != 200)
   //   //{

   //   //   m_strLastError = "Failed to fetch updated weather information from server.";

   //   //   set_need_redraw();

   //   //   return false;

   //   //}

   //   //m_strLastError.empty();

   //   ////::payload payload;

   //   ////payload.parse_network_payload(strResponse);

   //   //m_payload = payload;

   //   //m_bSunrise = payload["sys"]["sunrise"].has_character();

   //   //m_zonetimeSunrise = { payload["sys"]["sunrise"].as_posix_time(), m_timeshiftZone };

   //   //m_bSunset = payload["sys"]["sunset"].has_character();

   //   //m_zonetimeSunset = { payload["sys"]["sunset"].as_posix_time(), m_timeshiftZone };

   //   //string strSunrise(m_zonetimeSunrise.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

   //   //string strSunset(m_zonetimeSunset.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

   //   //m_datetimeLastStatus = payload["dt"].as_posix_time();

   //   //information(strCity + ":sunrise:" + strSunrise + "\n");

   //   //information(strCity + ":sunset:" + strSunset + "\n");

   //   m_pitema = pitema;

   //   set_need_redraw();

   //   post_redraw();


   //}


   //void list2::add_user(const ::scoped_string & scopedstrEmail)
   //{

   //   string strUrl = "https://ppp.reddotlogics.com/add_user?email=" + scopedstrEmail;

   //   string str;

   //   ::property_set set;

   //   //auto purl = system()->url();

   //   //strGetUrl = "https://api.ca2.network/account/openweather?request=" + ::url::encode(strUrl);

   //   //auto pcontext = m_papplication;

   //   auto payload = api_get(strUrl, set);

   //   update_data();

   //   //auto pitema = øcreate_new < pointer_array < ::item > >();

   //   //for (auto& row : payload.payload_array_reference())
   //   //{

   //   //   auto puser = øcreate_new <user>();

   //   //   puser->m_strEmail = row[0];

   //   //   pitema->add(puser);

   //   //   //         m_pitema->add(pitem);

   //   //}

   //}


   //void list2::erase_user(const ::scoped_string & scopedstrEmail)
   //{

   //   string strUrl = "https://ppp.reddotlogics.com/erase_user?email=" + scopedstrEmail;

   //   string str;

   //   ::property_set set;

   //   //auto purl = system()->url();

   //   //strGetUrl = "https://api.ca2.network/account/openweather?request=" + ::url::encode(strUrl);

   //   //auto pcontext = m_papplication;

   //   auto payload = api_get(strUrl, set);

   //   update_data();

   //   //auto pitema = øcreate_new < pointer_array < ::item > >();

   //   //for (auto& row : payload.payload_array_reference())
   //   //{

   //   //   auto puser = øcreate_new <user>();

   //   //   puser->m_strEmail = row[0];

   //   //   pitema->add(puser);

   //   //   //         m_pitema->add(pitem);

   //   //}

   //}


   //bool list2::on_click(::item * pitem)
   //{

   //   if (::is_null(pitem))
   //   {

   //      return false;

   //   }

   //   ::pointer < user > puser = pitem;

   //   if (!puser)
   //   {

   //      return false;

   //   }

   //   m_pmainimpact->m_ptabimpact->set_current_tab_by_id("user_form");

   //   m_pmainimpact->m_ptabimpact->m_puserformmainimpact->m_puserform->set_user(puser);

   //   return true;

   //}


} // namespace user



