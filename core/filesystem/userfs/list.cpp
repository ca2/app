#include "framework.h"
#include "aura/user/shell.h"
#include "_userfs.h"


namespace userfs
{


   list::list()
   {

      m_iSelectionSubItem = -1;
      m_iNameSubItem = -1;
      m_iIconSubItem = -1;

      m_rectMargin.left = 0;
      m_rectMargin.top = 0;
      m_rectMargin.bottom = 0;
      m_rectMargin.right = 0;

      //create_int(::user::int_list_item_draw_text_flags, e_align_left_center | DT_SINGLELINE | DT_PATH_ELLIPSIS);

   }


   list::~list()
   {

   }


   void list::install_message_routing(::channel * pchannel)
   {

      ::user::form_list_view::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_hscroll, pchannel, this, &list::_001OnHScroll);
      MESSAGE_LINK(e_message_vscroll, pchannel, this, &list::_001OnVScroll);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &list::_001OnShowWindow);
      MESSAGE_LINK(e_message_create, pchannel, this, &list::on_message_create);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &list::_001OnLButtonDblClk);
//#ifdef WINDOWS_DESKTOP
//      MESSAGE_LINK(WM_CANCELMODE, pchannel, this, &list::_001OnCancelMode);
//#endif

   }


   void list::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      if(pmessage->m_bRet)
         return;

      //puser->shell()->on_update_sizes_interest();

      set_impact_title("File Manager");
      
      auto pframe = get_parent_frame();

      pframe->set_frame_title("File Manager");

      if (get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = this;

      }

   }


   void list::_001OnTimer(::timer * ptimer)
   {
//      UNREFERENCED_PARAMETER(pmessage);

      ::user::form_list_view::_001OnTimer(ptimer);

   }


   bool list::on_click(const ::user::item & item)
   {

      ::user::range range;

      _001GetSelection(range);

      if(range.get_item_count() > 0)
      {
         list_data * pdata = fs_list();
         auto & itemrange = range.ItemAt(0);
         index iLItem = itemrange.get_lower_bound();
         index iUItem = itemrange.get_upper_bound();
         if(iUItem < iLItem)
         {
            iUItem = pdata->m_itema.get_upper_bound();
         }
         if(iLItem < 0)
            return false;
         if(iLItem >= pdata->m_itema.get_size())
            return false;
         if(iUItem >= pdata->m_itema.get_size())
            iUItem = pdata->m_itema.get_upper_bound();
         ::payload varFile;
         ::payload varQuery;
         if(iUItem == iLItem)
         {

            varFile = fs_list_item(iLItem)->get_user_path();

         }
         else
         {

            string_array stra;

            for(index iItem = iLItem; iItem < iLItem; iItem++)
            {

               stra.add(pdata->item(iItem)->get_user_path());

            }

            varFile = stra;

         }

         //get_document()->request_file(varFile, varQuery);

      }

      return true;

   }


   void list::assert_valid() const
   {

      ::user::form_list_view::assert_valid();

   }


   void list::dump(dump_context & dumpcontext) const
   {

      ::user::form_list_view::dump(dumpcontext);

   }


   void list::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {


   }

   void list::_001OnLButtonDblClk(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      __pointer(::message::mouse) pmouse(pmessage);
      /*         index iItem;
            list_data * pdata = fslist();
            if(_001HitTest_(pmouse->m_point, iItem))
            {
               ::file::item item;
               item.m_strPath         = pdata->m_foldera.GetFolder(iItem).m_strPath;
               get_filemanager_template()->get_filemanager_data()->OnFileManagerOpenFolder(item);
            }*/
   }

   void list::_001OnCancelMode(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      // trans   ::user::impact::OnCancelMode();

      // TODO: add your message handler code here

   }

   
   bool list::pre_create_window(::user::system * pusersystem)
   {


#ifdef WINDOWS_DESKTOP

#endif

      return ::user::form_list_view::pre_create_window(pusersystem);

   }


   void list::_001InsertColumns()
   {

      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth = 200;
         pcolumn->m_iSubItem = 0;

         

      }

      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth = 300;
         pcolumn->m_iSubItem = 1;

         

      }

      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth = 100;
         pcolumn->m_iSubItem = 2;

         

      }

   }


   bool list::_001OnUpdateItemCount(u32 dwFlags)
   {
      return ::user::list::_001OnUpdateItemCount(dwFlags);
   }


   void list::get_selected_user_path(::file::patha & patha)
   {

      patha.erase_all();

      auto itema = get_selected_items();

      for (auto & item : itema.ptra())
      {

         patha.add(item->m_filepathUser);

      }

   }


   void list::get_selected_final_path(::file::patha & patha)
   {

      patha.erase_all();

      auto itema = get_selected_items();

      for (auto & pitem : itema.ptra())
      {

         patha.add(pitem->m_filepathFinal);

      }

   }


   void list::get_selected_items(::file::item_array & itema)
   {

      ::user::range range;

      _001GetSelection(range);

      string str;

      for (index i = 0; i < range.get_item_count(); i++)
      {

         auto & itemrange = range.ItemAt(i);

         for (index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            index iStrict = _001DisplayToStrict(iItem);

            __pointer(::userfs::list_item) pitem = fs_list_item(iStrict);

            itema.add(pitem);

         }

      }

   }


   ::file::patha list::get_selected_user_path()
   {

      ::file::patha patha;

      get_selected_user_path(patha);

      return patha;

   }


   ::file::patha list::get_selected_final_path()
   {

      ::file::patha patha;

      get_selected_final_path(patha);

      return patha;

   }


   ::file::item_array list::get_selected_items()
   {

      ::file::item_array itema;

      get_selected_items(itema);

      return itema;

   }


   __pointer(::file::item) list::get_first_selected_item()
   {

      auto itema = get_selected_items();

      if (itema.is_empty())
      {

         return nullptr;

      }

      return itema.first_pointer();

   }


   void list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_list_view::_001OnDraw(pgraphics);

   }


   //void list::StartAnimation()
   //{
   //   //         m_iAnimate = 1;
   //}

   
   void list::_017OpenItem(__pointer(::file::item) pitem, bool bOpenFile, const ::action_context & action_context)
   {

      if (pitem->IsFolder())
      {

         _017OpenFolder(pitem, action_context);

      }
      else if (bOpenFile)
      {

         ::file::item_array itema;

         itema.add(pitem);

         _017OpenFile(itema, action_context);

      }

   }


   bool list::_017OpenSelected(bool bOpenFile, const ::action_context & context)
   {

      auto itema = get_selected_items();

      if (itema.is_empty())
      {

         return false;

      }

      if (itema.get_count() == 1)
      {

         _017OpenItem(itema.first_pointer(), bOpenFile, context + ::e_source_selection);

      }
      else if (bOpenFile)
      {

         _017OpenFile(itema, context + ::e_source_selection);

      }

      //_001ClearSelection();

      return true;

   }


   void list::_017OpenContextMenuSelected(const ::action_context & context)
   {

      list_data * pdata = fs_list();

      ::file::item_array itema;
      index iItemRange, iItem;
      ::user::range range;
      _001GetSelection(range);
      for (iItemRange = 0;
            iItemRange < range.get_item_count();
            iItemRange++)
      {
         auto & itemrange = range.ItemAt(iItemRange);
         for (iItem = itemrange.get_lower_bound();
               iItem <= itemrange.get_upper_bound();
               iItem++)
         {
            if (iItem < 0)
               continue;
            if (iItem >= pdata->m_itema.get_count())
               continue;

            index iStrict = _001DisplayToStrict(iItem);

            __pointer(::userfs::list_item) pitem = pdata->item(iStrict);

            if (pitem->IsFolder())
            {

               _017OpenContextMenuFolder(pitem, context);

               break;

            }
            else
            {

               itema.add(pitem);

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

      _001ClearSelection();

   }


   void list::_017OpenContextMenuFolder(__pointer(::file::item) item, const ::action_context & context)
   {

      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(context);

   }


   void list::_017OpenContextMenuFile(const ::file::item_array &itema, const ::action_context & context)
   {

      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(context);

   }


   void list::_017OpenContextMenu(const ::action_context & context)
   {

      UNREFERENCED_PARAMETER(context);

   }


   void list::_017OpenFolder(__pointer(::file::item) item, const ::action_context & context)
   {

      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(context);
      ASSERT(false);

   }


   //void list::_017OpenFolder(const ::userfs::list_item &item, const ::action_context & context)
   //{

   //   UNREFERENCED_PARAMETER(item);
   //   UNREFERENCED_PARAMETER(context);
   //   ASSERT(false);

   //}

   void list::_017OpenFile(const ::file::item_array &itema, const ::action_context & context)
   {
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(context);
      ASSERT(false);
   }

   void list::_001OnInitializeForm(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if (pinteraction == nullptr)
         return;

      /*      filemanager::file_list_callback * pcallback =
      get_filemanager_template()->get_filemanager_template()->m_pfilelistcallback;

      __pointer(::user::button) pbutton =  (pinteraction);
      if(pcallback != nullptr && pbutton != nullptr)
      {
      pcallback->InitializeActionButton(((i32) pinteraction->m_id) - 1000, pbutton);
      } */
   }

   void list::_001OnButtonAction(::user::interaction * pinteraction)
   {
      UNREFERENCED_PARAMETER(pinteraction);
      //      list_data * pdata = fslist();
      /* filemanager::file_list_callback * pcallback =
      get_filemanager_template()->get_filemanager_template()->m_pfilelistcallback;

      if(pcallback != nullptr)
      {
      ::file::item item;
      i32 iItem = pinteraction->GetEditItem();
      i32 iStrict;
      if(m_eview == impact_icon)
      {
      iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
      }
      else
      {
      iStrict = m_meshlayout.m_iaDisplayToStrict[iItem];
      }
      item.m_strPath         = pdata->item(iStrict).m_strPath;
      item.m_strExtra        = pdata->item(iStrict).m_strExtra;
      pcallback->OnButtonAction((i32) pinteraction->m_id - 1000, item);
      } */
   }

   //void list::GetSelected(::file::item_array &itema)
   //{
   //   list_data * pdata = fslist();
   //   index iItemRange, iItem;
   //   ::user::range range;
   //   _001GetSelection(range);
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
   //         ::file::item item;
   //         if (iItem < pdata->m_itema.get_count() && !iaItem.contains(iItem))
   //         {
   //            iaItem.add(iItem);
   //            index iStrict;
   //            if (m_eview == impact_icon)
   //            {
   //               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
   //            }
   //            else
   //            {
   //               if(iItem >= m_meshlayout.m_iaDisplayToStrict.get_count())
   //                  continue;
   //               iStrict = m_meshlayout.m_iaDisplayToStrict[iItem];
   //            }
   //            itema.add(__new(::file::item(pdata->item(iStrict))));
   //         }
   //      }
   //   }
   //}

   void list::_001OnVScroll(::message::message * pmessage)
   {
      //      __pointer(::message::scroll) pscroll(pmessage);
      //m_iCreateImageListStep = pscroll->m_nPos;
      //m_bRestartCreateImageList = true;
      pmessage->m_bRet = false;
   }

   void list::_001OnHScroll(::message::message * pmessage)
   {
      pmessage->m_bRet = false;
   }


   ::count list::_001GetItemCount()
   {

      return fs_list()->m_itema.get_count();

   }


   void list::add_fs_item(::file::path pathUser, ::file::path pathFinal, string strName)
   {

      list_item item;

      item.m_filepathUser = pathUser;

      item.m_filepathFinal = pathFinal;

      item.m_strName = strName;

      if (fs_data()->is_dir(item.get_final_path()))
      {

         item.m_flags.add(::file::e_flag_folder);

      }

      fs_list()->m_itema.add_fs_item(item);

      _001OnUpdateItemCount();

   }


   __pointer(::image_list) list::GetActionButtonImageList(index i)
   {

      if (i == 0)
      {

         auto puser = user();

         return puser->shell()->GetImageList(16);

      }

      return nullptr;

   }


   void list::_001OnFileRename(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::user::range range;

      _001GetSelection(range);

      if (range.get_item_count() == 1 && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound())
      {

         auto iEditItem = range.ItemAt(0).get_lower_bound();

         ::user::interaction * pinteraction = _001GetControl(iEditItem, fs_list()->m_iNameSubItem);

         _001PlaceControl(pinteraction, iEditItem);

      }

   }


   void list::_001OnUpdateFileRename(::message::message * pmessage)
   {
      __pointer(::message::command) pcommand(pmessage);
      ::user::range range;
      _001GetSelection(range);
      pcommand->enable(
      range.get_item_count() == 1
      && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound());
      pmessage->m_bRet = true;
   }

   void list::_001OnShowWindow(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //      __pointer(::message::show_window) pshow(pmessage);

      //db_server * pcentral = dynamic_cast < db_server * > (psystem->m_psimpledb->db());
      //if (pcentral == nullptr)
      //   return;
      //DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
      /*if(pshow->m_bShow)
      {
      for(i32 i = 0; i < m_itema.get_item_count(); i++)
      {
      pset->m_table.add_request(item(i).m_strPath);
      }
      }
      else
      {
      for(i32 i = 0; i < m_itema.get_item_count(); i++)
      {
      pset->m_table.erase_request(item(i).m_strPath);
      }
      }*/
   }


   void list::_001InitializeFormPreData()
   {
      /*      ::filemanager::data * pdata = get_filemanager_template()->get_filemanager_data();
      pdata->m_pcallback->OnFileManagerInitializeFormPreData(
      pdata,
      GetDlgCtrlId(),
      this);*/
   }


   bool list::query_drop(index iDisplayDrop, index iDisplayDrag)
   {

      list_data * pdata = fs_list();

      if (iDisplayDrag < 0)
      {

         return false;

      }

      if (iDisplayDrop < 0)
      {

         return false;

      }

      if (iDisplayDrag != iDisplayDrop)
      {

         index iStrict = _001DisplayToStrict(iDisplayDrop);

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
            return pdata->item(iStrict)->IsFolder();

         }

      }

      return false;

   }


   bool list::do_drop(index iDisplayDrop, index iDisplayDrag)
   {

      list_data * pdata = fs_list();

      index iStrictDrop = m_piconlayout->m_iaDisplayToStrict[iDisplayDrop];

      index iStrictDrag = m_piconlayout->m_iaDisplayToStrict[iDisplayDrag];

      if (iStrictDrop >= 0 && pdata->item(iStrictDrop)->IsFolder())
      {

         ::file::path strPath = pdata->item(iStrictDrag)->m_filepathFinal;

         string strName = strPath.name();

         fs_data()->file_move(pdata->item(iStrictDrop)->m_filepathFinal, strPath);

      }
      else
      {

         ::user::list::do_drop(iDisplayDrop, iDisplayDrag);

      }

      return true;

   }


   //color32_t list::get_background_color()
   //{

   //   return rgb(255, 255, 255);

   //}


   list_data * list::fs_list()
   {

      return m_pmeshdata.cast < list_data > ();

   }


   __pointer(::user::mesh_data) list::create_mesh_data()
   {

      return __new(list_data);

   }


   __pointer(::fs::data) list::fs_data()
   {

      return get_document()->fs_data();

   }


   __pointer(::file::item) list::fs_list_item(index iIndex)
   {

      return fs_list()->m_itema[iIndex];

   }


   __pointer(::userfs::document) list::get_document()
   {

      return ::user::form_list_view::get_document();

   }


   void list::_001GetItemText(::user::mesh_item * pitem)
   {

      return ::user::form_list_view::_001GetItemText(pitem);

   }


   void list::_001GetItemImage(::user::mesh_item * pitem)
   {

      if (pitem->m_iSubItem == m_iSelectionSubItem || pitem->m_iSubItem == m_iNameSubItem)
      {

         if (pitem->m_iSubItem == m_iIconSubItem)
         {

            list_data * pdata = fs_list();

            if (::is_null(pdata))
            {

               return;

            }

            if (get_document().is_null())
            {

               return;

            }

            __pointer(::fs::set) pset = fs_data();

            if (pset.is_null())
            {

               return;

            }

            if (pitem->m_iItem < 0 || pitem->m_iItem >= pdata->m_itema.get_count())
            {

               return;

            }

            auto pfsitem = pdata->item((::index) pitem->m_iItem);

            __pointer(::core::session) psession = get_session();

            auto puser = psession->user();

            pitem->m_iImage = puser->shell()->get_file_image(
                              pfsitem->m_filepathFinal,
                              pset->is_dir(pfsitem->m_filepathFinal) ? ::user::shell::file_attribute_directory : ::user::shell::file_attribute_normal,
                              ::user::shell::icon_normal);

            if (pitem->m_iImage >= 0)
            {

               pitem->m_bOk = true;

            }

         }
         else
         {

            pitem->m_iImage = -1;

            pitem->m_bOk = false;

         }

         return;

      }


      return ::user::form_list_view::_001GetItemImage(pitem);

   }


} // namespace userfs

