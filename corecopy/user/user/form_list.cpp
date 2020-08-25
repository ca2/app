#include "framework.h"
#include "aura/update.h"
#include "aura/const/id.h"


namespace user
{


   form_list::form_list()
   {

      m_pcontrolEdit = nullptr;

      m_iClickCount    = 0;

   }


   form_list::~form_list()
   {

   }


   void form_list::_001GetSelection(::database::key & key,::database::selection &selection)
   {

      list::_001GetSelection(key,selection);

   }


   void form_list::install_message_routing(::channel *pchannel)
   {

      IGUI_MSG_LINK(WM_KEYDOWN,pchannel,this,&form_list::_001OnKeyDown);

      form_mesh::install_message_routing(pchannel);

      list::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_VSCROLL, pchannel, this, &form_list::_001OnVScroll);

      IGUI_MSG_LINK(WM_HSCROLL, pchannel, this, &form_list::_001OnHScroll);

   }




   bool form_list::on_right_click(const ::user::item & item)
   {

      if (!item)
      {


         _001HideEditingControls();

         return false;
      }

      __pointer(control) pinteraction = _001GetControl(item.item_index(), item.subitem_index());

      if (pinteraction != nullptr)
      {

         if (pinteraction->descriptor().has_function(::user::control_function_action))
         {

            if (pinteraction->descriptor().get_control_type() == ::user::control_type_button)
            {


               ::user::control_event ev;

               ev.m_puie = pinteraction;

               ev.m_eevent = ::user::event_button_clicked;

               m_itemControl = item;

               send_message(EVENT_MESSAGE, 0, (LPARAM)&ev);

            }

         }
         else if (m_columna.get_by_subitem(item.subitem_index())->m_bEditOnSecondClick)
         {

            if (m_itemClick == item)
            {

               m_iClickCount++;

            }
            else
            {

               m_iClickCount = 1;

            }

            m_itemClick = item;

            if (m_iClickCount == 2)
            {

               m_iClickCount = 0;

               _001PlaceControl(pinteraction, item);

            }

         }
         else
         {

            _001PlaceControl(pinteraction, item, true);

         }

      }
      else
      {

         // Click in subitem without editing controls.

         _001HideEditingControls();

      }

      return true;

   }





   bool form_list::on_click(const ::user::item & item)
   {

      if(!item)
      {

         _001HideEditingControls();

         return false;

      }

      __pointer(control) pinteraction = _001GetControl(item.item_index(), item.subitem_index());

      if (pinteraction != nullptr)
      {

         if (pinteraction->has_function(::user::control_function_action))
         {

            if (pinteraction->descriptor().get_control_type() == ::user::control_type_button)
            {

               ::user::control_event ev;

               ev.m_puie = pinteraction;

               ev.m_eevent = ::user::event_button_clicked;

               m_itemControl = item;

               send_message(EVENT_MESSAGE, 0, (LPARAM)& ev);

            }

         }
         else if (m_columna.get_by_subitem(item.subitem_index())->m_bEditOnSecondClick)
         {

            if (m_itemClick == item)
            {

               m_iClickCount++;

            }
            else
            {

               m_iClickCount = 1;

            }

            m_itemClick = item;

            if (m_iClickCount == 2)
            {

               m_iClickCount = 0;

               _001PlaceControl(pinteraction, item);

            }

         }
         else
         {

            _001PlaceControl(pinteraction, item, true);

         }

      }
      else
      {

         // Click in subitem without editing controls.

         _001HideEditingControls();

         __pointer(::user::list_column) pcolumn = m_columna.get_by_subitem(item.subitem_index());

         if (pcolumn.is_set() && pcolumn->m_iControl >= 0)
         {

            auto pdescriptor = m_controldescriptorset.sp_at((::index) pcolumn->m_iControl);

            if (pdescriptor.is_set())
            {

               if (pdescriptor->has_function(::user::control_function_check_box))
               {

                  ::enum_check echeck = _001GetSubItemCheck(item.item_index(), item.subitem_index());

                  if (echeck == ::check_checked)
                  {

                     echeck = ::check_unchecked;

                  }
                  else
                  {

                     echeck = ::check_checked;

                  }

                  _001SetSubItemCheck(item.item_index(), item.subitem_index(), echeck);

                  if (echeck == ::check_checked)
                  {

                     for (auto& pitem : m_controldescriptorset.ptra())
                     {

                        if (pitem->has_function(::user::control_function_duplicate_on_check_box))
                        {

                           if (pitem->m_iSubItemDuplicateCheckBox == item.subitem_index())
                           {

                              for (auto iSubItemTarget : pitem->m_iaSubItemDuplicate)
                              {

                                 ::user::mesh_item itemSource(this);

                                 itemSource.m_iItem = item.item_index();
                                 itemSource.m_iSubItem = pitem->subitem_index();

                                 _001GetItemText(&itemSource);

                                 if (itemSource.m_bOk)
                                 {

                                    ::user::mesh_item itemTarget(this);

                                    itemTarget.m_iItem = item.item_index();
                                    itemTarget.m_iSubItem = iSubItemTarget;
                                    itemTarget.m_strText = itemSource.m_strText;

                                    _001SetItemText(&itemTarget);

                                 }


                              }

                           }

                        }

                     }

                  }


                  return true;

               }

            }

         }
         else
         {

            //if (m_rangeSelection.has_item(iItem))
            //{

            //   m_rangeSelection.clear();

            //}
            //else
            //{

            //   m_rangeSelection.clear();

            //   ::user::item_range r;

            //   rect.m_iLowerBound = iItem;

            //   rect.m_iUpperBound = iItem;

            //   m_rangeSelection.add_item(rect);

            //}
            return ::user::list::on_click(item);

         }


      }

      return false;

      return false;

   }


   control * form_list::_001GetControl(index iItem, index iSubItem)
   {

      sync_lock sl(mutex());

      ::user::list_column * pcolumn = m_columna.get_by_subitem(iSubItem);

      if(pcolumn == nullptr
            || pcolumn->m_iControl < 0
            || pcolumn->m_iControl >= m_controldescriptorset.get_count())
      {

         return nullptr;

      }

      auto pdescriptor = m_controldescriptorset[pcolumn->m_iControl];

      if(pdescriptor.is_null())
      {

         return nullptr;

      }

      return pdescriptor->m_pusercontrol;

   }


   void form_list::_001OnShowControl(::user::interaction * pinteraction)
   {


   }


   index form_list::_001AddControl(class control_descriptor * pdescriptor)
   {

      m_controldescriptorset.add(pdescriptor);

      pdescriptor->m_puserinteractionParent = this;

      //if (pdescriptor->m_bTransparent)
      //{

      //   switch (pdescriptor->m_econtroltype)
      //   {
      //   case control_type_static:
      //   {
      //      /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pinteraction->m_id)->GetSafeoswindow_());
      //      if(pstatic == nullptr || !base_class < CTransparentStatic >::bases(pstatic))
      //      {
      //      pstatic = new CTransparentStatic;
      //      VERIFY(pstatic->subclass_window(pform->get_child_by_id(pinteraction->m_id)->GetSafeoswindow_()));
      //      }
      //      pinteraction->m_unionwndptr.m_pstatic = pstatic;*/
      //   }
      //   break;
      //   default:
      //      break;

      //   }
      //}

      if (pdescriptor->m_type)
      {

         if (pdescriptor->m_bCreated && pdescriptor->m_pusercontrol)
         {

            pdescriptor->m_bCreated = false;

            pdescriptor->m_pusercontrol.release();

         }


         if (pdescriptor->m_pusercontrol)
         {

         }
         else if (create_control(pdescriptor, m_controldescriptorset.get_upper_bound()))
         {

         }
         else
         {
            // Failed creation
            ASSERT(FALSE);
         }

      }

      return m_controldescriptorset.get_upper_bound();

   }


   void form_list::_001PlaceControl(::user::interaction * pinteraction, index iEditItem, bool bClick, bool bOnlySizeAndPosition)
   {

      bool bSameControl = false;

      bool bSameItemAndSubItem = false;

      if (_001GetEditControl() != nullptr)
      {

         if (_001GetEditControl()->m_pdescriptor->m_iSubItem != pinteraction->m_pdescriptor->m_iSubItem)
         {

            if (!bOnlySizeAndPosition && _001GetEditControl() != nullptr)
            {

               _001SaveEdit(_001GetEditControl());

            }

            if (!bOnlySizeAndPosition && pinteraction->m_pdescriptor->m_iSubItem)
            {

               _001HideEditingControls();

            }

         }
         else
         {

            bSameControl = true;

            _001SaveEdit(_001GetEditControl());

            if (iEditItem == _001GetEditControl()->m_iEditItem)
            {

               bSameItemAndSubItem = true;

            }

         }

      }

      _001SelectItem(iEditItem);

      draw_list_item item(this);

      m_iEditItem = iEditItem;

      pinteraction->m_iEditItem = iEditItem;

      item.m_iDisplayItem = _001DisplayToStrict(iEditItem);

      item.m_iItem = iEditItem;

      item.m_iColumn = pinteraction->m_pdescriptor->column_index();

      item.m_iSubItem = pinteraction->m_pdescriptor->subitem_index();

      item.m_pcolumn = m_columna.get_visible((::index) item.m_iColumn);

      if (!bOnlySizeAndPosition)
      {

         _001EnsureVisible(item.item_index());

      }

      item.m_iSubItem = pinteraction->descriptor().subitem_index();

      item.m_iOrder = _001MapSubItemToOrder(item.subitem_index());

      _001GetElementRect(&item,::user::mesh::element_text);

      if(item.m_bOk)
      {

         rectd rectControl(item.m_rectSubItem);

         auto pointViewport = get_viewport_offset();

         rectControl.offset(pointViewport);

         if (!bOnlySizeAndPosition)
         {

            _001Update(pinteraction);

         }

         pinteraction->order_top();

         pinteraction->place(rectControl);

         if (bOnlySizeAndPosition)
         {

            pinteraction->set_need_layout();

         }

         pinteraction->display();

         //SWP_SHOWWINDOW | (bOnlySizeAndPosition ? SWP_CHANGEVIEWPORTOFFSET : 0));

         if (!bOnlySizeAndPosition)
         {

            _001SetEditControl(pinteraction);

            if (_001IsSubItemEnabled(iEditItem, item.subitem_index()))
            {

               pinteraction->enable_window();

            }
            else
            {

               pinteraction->enable_window(false);

            }

            if (bClick)
            {

               __pointer(::user::combo_box) pcombobox = pinteraction;

               if (pcombobox.is_set() && !pcombobox->m_bEdit)
               {

                  if (bSameItemAndSubItem)
                  {

                     pcombobox->_001ToggleDropDown();

                  }
                  else if(pcombobox->m_plist != nullptr)
                  {

                     __keep(pcombobox->m_plist->m_bMovingComboBox);

                     pcombobox->_001ShowDropDown();

                  }
                  else
                  {

                     pcombobox->_001ShowDropDown();

                  }


                  goto break_click;

               }


               __pointer(::user::plain_edit) pedit = pinteraction;

               if (pedit.is_set())
               {

                  pinteraction->SetFocus();

                  pedit->_001SetSel(0, pedit->_001GetTextLength());

               }

            }
break_click:;

            _001OnShowControl(pinteraction);

         }

      }

   }

   bool form_list::_001OnUpdateItemCount(u32 dwFlags)
   {

      _001HideEditingControls();

      bool bOk = ::user::list::_001OnUpdateItemCount(dwFlags);

      for (auto & pitem : m_controldescriptorset.ptra())
      {

         if (pitem->has_function(::user::control_function_duplicate_on_check_box))
         {

            ::count iItemCount = _001GetItemCount();

            for(index iItem = 0; iItem < iItemCount; iItem++)
            {

               if (_001GetSubItemCheck(iItem, pitem->m_iSubItemDuplicateCheckBox) == ::check_checked)
               {

                  for (auto iSubItemTarget : pitem->m_iaSubItemDuplicate)
                  {

                     ::user::mesh_item itemSource(this);

                     itemSource.m_iItem = iItem;
                     itemSource.m_iSubItem= pitem->subitem_index();

                     _001GetItemText(&itemSource);

                     if (itemSource.m_bOk)
                     {

                        ::user::mesh_item itemTarget(this);

                        itemTarget.m_iItem= iItem;
                        itemTarget.m_iSubItem = iSubItemTarget;
                        itemTarget.m_strText = itemSource.m_strText;

                        _001SetItemText(&itemTarget);

                     }

                  }

               }

            }

         }

      }

      return bOk;

   }


   void form_list::_001UpdateEdit(::user::interaction * pinteraction)
   {
      ASSERT(pinteraction != nullptr);
      if (pinteraction == nullptr)
         return;

      __task_guard(m_bOnEditUpdate);

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_edit
             || pinteraction->descriptor().get_control_type() == control_type_edit_plain_text);

      __pointer(::user::plain_edit) pedit = pinteraction;

      //if (pedit.is_set())
      //{

      //   pedit->m_pfont = m_font;

      //}

      if (pinteraction->descriptor().has_function(control_function_vms_data_edit))
      {


         draw_list_item item(this);

         item.m_iItem = pinteraction->m_iEditItem;
         item.m_iSubItem = pinteraction->descriptor().subitem_index();

         _001GetItemText(&item);

         if (item.m_bOk)
         {

            pedit->_001SetText(item.m_strText, ::source_initialize);

         }

         //var var;
         //::database::selection selection;
         //_001GetSelection(pinteraction->descriptor().m_dataid, selection);
         //if (selection.get_item_count() > 0)
         //{
         //   ::database::selection_item & item = selection.get_item(0);
         //   __pointer(::user::edit_text) ptext = nullptr;
         //   if (get_child_by_id(pinteraction->m_id) != nullptr)
         //   {
         //      ptext = get_child_by_id(pinteraction->m_id);
         //   }
         //   if (ptext == nullptr && pinteraction != nullptr)
         //   {
         //      ptext = pinteraction;
         //   }
         //   if (ptext == nullptr)
         //      return;
         //   if (data_get(pinteraction->descriptor().m_dataid.m_id + "." + item.m_id.m_id, var))
         //   {
         //      switch (var.get_type())
         //      {
         //      case ::type_string:
         //      {
         //         string str;
         //         str = var.m_str;
         //         ptext->_001SetText(str, ::source_database);
         //      }
         //      break;
         //      case ::type_int32:
         //      {
         //         string str;
         //         str.Format("%d", var.i32());
         //         ptext->_001SetText(str, ::source_database);
         //      }
         //      break;
         //      default:
         //         ASSERT(FALSE);
         //         break;
         //      }
         //   }
         //}
      }

   }


   void form_list::_001UpdateComboBox(::user::interaction * pinteraction)
   {

      ASSERT(pinteraction != nullptr);

      if (pinteraction == nullptr)
         return;

      __task_guard(m_bOnEditUpdate);

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_combo_box);

      __pointer(::user::combo_box) pcombo = pinteraction;

      if (pinteraction->descriptor().has_function(control_function_data_selection))
      {

         draw_list_item item(this);

         item.m_iItem = pinteraction->m_iEditItem;

         item.m_iSubItem = pinteraction->descriptor().subitem_index();

         _001GetItemText(&item);

         if (item.m_bOk)
         {

            index iFind = pcombo->_001FindListText(item.m_strText);

            pcombo->set_current_item(iFind, ::source_sync);

         }

      }

   }


   bool form_list::_001SaveEdit(::user::interaction * pinteraction)
   {

      if (pinteraction == nullptr)
         return false;

      if (pinteraction->descriptor().get_control_type() == control_type_check_box)
      {

         __pointer(::user::check) pcheckbox = pinteraction;

         auto echeck = pcheckbox->echeck();

         draw_list_item item(this);

         item.m_iItem = pinteraction->m_iEditItem;

         item.m_iSubItem = pinteraction->descriptor().subitem_index();

         if (echeck == ::check_checked)
         {

            string str = pinteraction->descriptor().m_setValue[::check_checked];

            if(str.has_char())
            {

               item.m_strText = str;

            }
            else
            {

               item.m_strText = "true";

            }

         }
         else if (echeck == ::check_unchecked)
         {

            string str = pinteraction->descriptor().m_setValue[::check_unchecked];

            if (str.has_char())
            {

               item.m_strText = str;

            }
            else
            {

               item.m_strText = "false";

            }

         }
         else
         {

            string str = pinteraction->descriptor().m_setValue[::check_tristate];

            if (str.has_char())
            {

               item.m_strText = str;

            }
            else
            {

               item.m_strText = "";

            }

         }

         _001SetItemText(&item);

         auto pupdate = new_update();

         pupdate->m_id = id_control_saved;

         call_update(pupdate);

         return true;

      }

      ASSERT(pinteraction->descriptor().get_control_type() == control_type_edit || pinteraction->descriptor().get_control_type() == control_type_edit_plain_text
             || pinteraction->descriptor().get_control_type() == control_type_combo_box);

      auto pinteraction = get_child_by_id(pinteraction->m_id);

      if (!pinteraction)
      {

         pinteraction = pinteraction;

      }

      if (!pinteraction)
      {

         return false;

      }

      string str;

      pinteraction->_001GetText(str);

      if (!pinteraction->Validate(str))
      {

         // que tal um balão para indicar o erro

         return false;

      }

      var var;

      if (!pinteraction->get_data(pinteraction, var))
      {

         return false;

      }

      if (!_001Validate(pinteraction, var))
      {

         return false;

      }

      if (pinteraction->descriptor().has_function(control_function_vms_data_edit)
            || pinteraction->descriptor().has_function(control_function_data_selection))
      {

         draw_list_item item(this);

         item.m_iItem = pinteraction->m_iEditItem;

         item.m_iSubItem = pinteraction->descriptor().subitem_index();

         item.m_strText = var.get_string();

         _001SetItemText(&item);

         auto pupdate = new_update();

         pupdate->m_id = id_control_saved;

         call_update(pupdate);

         if (pinteraction->descriptor().has_function(::user::control_function_duplicate_on_check_box))
         {

            if (_001GetSubItemCheck(item.item_index(), pinteraction->descriptor().m_iSubItemDuplicateCheckBox) == ::check_checked)
            {

               for (auto iSubItemTarget : pinteraction->descriptor().m_iaSubItemDuplicate)
               {

                  ::user::mesh_item itemTarget(this);

                  itemTarget.m_iItem = item.item_index();
                  itemTarget.m_iSubItem = iSubItemTarget;
                  itemTarget.m_strText = item.m_strText;

                  _001SetItemText(&itemTarget);

                  //__pointer(::list::column) pcolumn = m_columna.get_by_subitem(iSubItemTarget);
                  //
                  //if (pcolumn.is_set() && m_controldescriptorset.bounds(pcolumn->m_iControl))
                  //{

                  //   __pointer(class ::user::control_descriptor) pdescriptorTarget = m_controldescriptorset.sp_at(pcolumn->m_iControl);

                  //   if (pdescriptorTarget.is_set())
                  //   {

                  //      on_update(nullptr, ::user::impact::update_control_saved, pinteraction);
                  //   }

                  //}

               }

            }

         }

      }

      return true;

   }



   void form_list::_001SetEditControl(::user::interaction * pinteraction)
   {

      if(pinteraction == nullptr)
      {
         if(m_pcontrolEdit != nullptr)
         {
            __pointer(class control) pcontrolEdit = m_pcontrolEdit;
            _001HideControl(pcontrolEdit);
            m_pcontrolEdit = nullptr;
         }
      }
      else
      {
         m_pcontrolEdit = pinteraction;
      }
   }


   control * form_list::_001GetEditControl()
   {

      return m_pcontrolEdit;

   }


   void form_list::_001OnVScroll(::message::message * pmessage)
   {
      //SCAST_PTR(::message::scroll, pscroll, pmessage);
      pmessage->previous();


      __pointer(control) pinteraction = _001GetEditControl();

      if(pinteraction != nullptr)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iEditItem, false, true);

      }

   }

   void form_list::_001OnHScroll(::message::message * pmessage)
   {
      pmessage->previous();
      if(pmessage->m_bRet)
         return;

      __pointer(control) pinteraction = _001GetEditControl();

      if(pinteraction != nullptr)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iEditItem, false, true);

      }

   }


   bool form_list::_001OnMouseActivate(::user::interaction_impl * pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult)
   {
      UNREFERENCED_PARAMETER(pDesktopWnd);
      UNREFERENCED_PARAMETER(nHitTest);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(iResult);
      return false;
   }

   void form_list::_001OnNotify(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void form_list::_001OnTimer(::timer * ptimer)
   {
      list::_001OnTimer(ptimer);
   }

   void form_list::_001OnMessageNotify(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      // linux na verdade revamp
      /*
      lresult = user::NotifyRetContinue;

      __pointer(control) pinteraction = m_controldescriptorset.get_control_by_id(wparam);

      if(pinteraction == nullptr)
      return true;

      user::Notify * pnotify = (user::Notify *) lparam;


      switch(pinteraction->descriptor().get_control_type())
      {
      case control_type_edit:
      switch(pnotify->m_uiCode)
      {
      case user::NotifyKeyDown:
      {
      user::NotifyKey * pkey = (user::NotifyKey *) pnotify;
      switch(pkey->m_uiVKey)
      {
      //             //  case VK_RETURN:
      _001SaveEdit(pinteraction);
      pinteraction->display(display_none);
      lresult &= ~user::NotifyRetContinue;
      return true;
      }
      }
      break;
      }
      break;
      }*/
      //return true;
   }

   void form_list::_001UpdateColumns()
   {

      _001RemoveControls();

      list::_001UpdateColumns();

   }

   //LRESULT form_list::_001BaseWndGetProperty(EProperty eprop,LPARAM lparam)

   //{
   //   switch(eprop)
   //   {
   //   case list::PropertyBaseWndInterface:
   //   case list::PropertyDrawBaseWndInterface:
   //   {
   //      const ::user::primitive ** ppinterface = (const ::user::primitive **) lparam;

   //      *ppinterface = (list *)this;
   //   }
   //   return 1;
   //   default:
   //      return 0;
   //   }
   //}


   void form_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      list::_001OnDraw(pgraphics);

   }

   void form_list::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      form_mesh::_001DrawChildren(pgraphics);

   }


   void form_list::_001HideEditingControls()
   {

      form_mesh::_001HideEditingControls();

      m_iEditItem = -1;

      //if(_001GetEditControl() != nullptr)
      //{
      //   _001SetEditControl(nullptr);
      //}
      //for(i32 i = 0; i < m_controldescriptorset.get_count(); i++)
      //{
      //   class ::user::control_descriptor & descriptor = m_controldescriptorset(i);
      //   if(control.m_etype == control_type_edit
      //      || control.m_etype == control_type_edit_plain_text)
      //   {
      //      if(control.m_pcontrol != nullptr)
      //      {
      //         control.m_pcontrol->display(display_none);
      //      }
      //   }
      //}
   }


   void form_list::_001HideControl(::user::interaction * pinteraction)
   {

      pinteraction->display(display_none);

   }


   void form_list::_001OnKeyDown(::message::message * pmessage)
   {
      SCAST_PTR(::message::key,pkey,pmessage);

      if(pkey->m_ekey == ::user::key_return)
      {
         _001SaveEdit(_001GetEditControl());
         _001HideEditingControls();
         pmessage->m_bRet = true;
         return;
      }
      pkey->previous();
   }



   bool form_list::_001IsEditing()
   {
      return m_pcontrolEdit != nullptr;
   }

   void form_list::_001OnAddColumn(list_column * pcolumn)
   {

      if (pcolumn->m_iControl >= 0)
      {

         m_controldescriptorset[pcolumn->m_iControl]->m_iSubItem = pcolumn->subitem_index();
         m_controldescriptorset[pcolumn->m_iControl]->m_iColumn = pcolumn->m_iColumn;

      }

   }


   bool form_list::_001IsPointInside(::user::interaction * pinteraction,point64 point)
   {

      if(pinteraction->m_pdescriptor != nullptr)
      {

         if(pinteraction->m_pdescriptor->m_econtroltype == control_type_edit
               || pinteraction->m_pdescriptor->m_econtroltype == control_type_edit_plain_text)
         {

            if(pinteraction == _001GetEditControl())
            {

               ::rect rectWindow;
               
               pinteraction->get_window_rect(rectWindow);

               return rectWindow.contains(point);

            }
            else
            {

               return false;

            }
         }
      }
      ::rect rectControl;
      ::rect rect;
      draw_list_item item(this);


      return m_itemControl && m_itemControl.subitem_index() == pinteraction->descriptor().subitem_index();

      //i32 iEditItem;
      //i32 iEditSubItem;

      //_001DisplayHitTest(point, iEditItem, iEditSubItem);

      //      item.m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
      //    item.item_index() = pinteraction->m_iEditItem;
//      item.m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
//
//      item.subitem_index() = pinteraction->descriptor().subitem_index();
//      item.m_iOrder = _001MapSubItemToOrder(item.subitem_index());
//      item.m_iListItem = -1;
//      //_001GetElementRect(&item, ::user::mesh::element_sub_item);
//      rectControl = item.m_rectSubItem;
//      _001ClientToScreen(rectControl);
//      rect64 rectForm;
//      get_window_rect(rectForm);
//      rect64 rectClient;
//      rectClient.top = rectForm.top;
//      rectClient.bottom = rectForm.bottom;
//      rectClient.left = rectControl.left;
//      rectClient.right = rectControl.right;
//      return rectClient.contains(point) != FALSE;
   }


   void form_list::_001OnColumnChange()
   {

      ::user::list::_001OnColumnChange();


      {

         sync_lock sl(mutex());

         for (index i = 0; i < m_columna.get_size(); i++)
         {

            if (m_columna[i]->m_iControl >= 0 && m_columna[(::index) i]->m_iControl < m_controldescriptorset.get_size())
            {
               
               auto pdescriptor = m_controldescriptorset.element_at((::index) m_columna[i]->m_iControl);

               if (pdescriptor != nullptr)
               {
                  if (m_columna[i]->subitem_index() >= 0)
                  {
                     pdescriptor->m_iSubItem = m_columna[i]->subitem_index();
                  }
                  else if (pdescriptor->subitem_index() >= 0)
                  {
                     m_columna[i]->m_iSubItem = pdescriptor->subitem_index();
                  }
               }
            }

         }

      }

      if (m_pcontrolEdit != nullptr && m_pcontrolEdit->is_window_visible())
      {

         _001PlaceControl(m_pcontrolEdit, m_pcontrolEdit->m_iEditItem);

      }

   }


   void form_list::_000OnMouse(::message::mouse * pmouse)
   {
      // must lock ::user::mutex_children() at top stack chain
// and only at top stack chain.

      auto point = pmouse->m_point;

      _001ScreenToClient(point);

      if (pmouse->m_id == WM_LBUTTONDOWN)
      {

         index iItem;

         index iSubItem;

         //::user::range range;

         //_001GetSelection(range);

         if (_001DisplayHitTest(point, iItem, iSubItem))
         {

            auto pdescriptor = m_controldescriptorset.get_by_sub_item((::index) iSubItem);

            if (pdescriptor
                  && pdescriptor->m_pusercontrol
                  && (pdescriptor->m_econtroltype == control_type_combo_box))
            {

               _001PlaceControl(pdescriptor->m_pusercontrol, (::index) iItem, true);

               //pinteraction->m_puserinteraction->message_handler(pmouse);

               pmouse->m_bRet = true;

               return;

            }
         }
      }
      if (pmouse->m_bRet)
      {

         return;

      }


      form_mesh::_000OnMouse(pmouse);

      if (pmouse->m_bRet)
      {

         return;

      }

      //else if(uiMessage == WM_LBUTTONUP)
      //{
      //i32 iItem;
      //i32 iSubItem;
      //::user::range range;
      //_001GetSelection(range);
      //if(_001DisplayHitTest(point, iItem, iSubItem))
      //{
      //class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
      //if(pinteraction != nullptr
      //&& pinteraction->m_pcontrol != nullptr
      //&& !pinteraction->m_pcontrol->is_window_visible()
      //&& (pinteraction->m_etype == type_edit
      //|| pinteraction->m_etype == type_edit_plain_text))
      //{
      //return false;
      //}
      //}
      //}*/
      //control_keep controlkeep(this,point);
      //__pointer(::user::interaction) pinteraction = top_child();
      //__pointer(::user::interaction) puiBefore = nullptr;
      //bool bError;
      //try
      //{
      //   while(pinteraction != nullptr)
      //   {
      //      bError = false;
      //      try
      //      {
      //         if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
      //         {
      //            pinteraction->_000OnMouse(pmouse);
      //            if(pmouse->m_bRet)
      //               return;
      //            pinteraction->send(pmouse);
      //            if(pmouse->get_lresult() != 0)
      //               return;
      //         }
      //      }
      //      catch(...)
      //      {
      //         bError = true;
      //         puiBefore = pinteraction;
      //      }
      //      pinteraction = under_sibling(pinteraction);
      //      if(bError)
      //      {
      //         m_uiptraChild.remove(puiBefore);
      //      }
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < ::message::message * > (pmouse->);
      //   if(pmouse->get_lresult() != 0)
      //      return;
      //}
      //catch(...)
      //{
      //}





      //::point point = pmouse->m_point;
      //_001ScreenToClient(point);
      ///*      if(uiMessage == WM_LBUTTONDOWN)
      //      {
      //      i32 iItem;
      //      i32 iSubItem;
      //      ::user::range range;
      //      _001GetSelection(range);
      //      if(_001DisplayHitTest(point, iItem, iSubItem))
      //      {
      //      class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
      //      if(pinteraction != nullptr
      //      && pinteraction->m_pcontrol != nullptr
      //      && (pinteraction->m_etype == type_edit
      //      || pinteraction->m_etype == type_edit_plain_text)
      //      && !range.has_sub_item(iItem, iSubItem))
      //      {
      //      _001HideEditingControls();
      //      return false;
      //      }
      //      }
      //      }
      //      else if(uiMessage == WM_LBUTTONUP)
      //      {
      //      i32 iItem;
      //      i32 iSubItem;
      //      ::user::range range;
      //      _001GetSelection(range);
      //      if(_001DisplayHitTest(point, iItem, iSubItem))
      //      {
      //      class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
      //      if(pinteraction != nullptr
      //      && pinteraction->m_pcontrol != nullptr
      //      && !pinteraction->m_pcontrol->is_window_visible()
      //      && (pinteraction->m_etype == type_edit
      //      || pinteraction->m_etype == type_edit_plain_text))
      //      {
      //      return false;
      //      }
      //      }
      //      }*/
      //control_keep controlkeep(this,point);
      //__pointer(::user::interaction) pinteraction = top_child();
      //__pointer(::user::interaction) puiBefore = nullptr;
      //bool bError;
      //try
      //{
      //   while(pinteraction != nullptr)
      //   {
      //      bError = false;
      //      try
      //      {
      //         if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
      //         {
      //            pinteraction->_000OnMouse(pmouse);
      //            if(pmouse->m_bRet)
      //               return;
      //            pinteraction->send(pmouse);
      //            if(pmouse->get_lresult() != 0)
      //               return;
      //         }
      //      }
      //      catch(...)
      //      {
      //         bError = true;
      //         puiBefore = pinteraction;
      //      }
      //      pinteraction = under_sibling(pinteraction);
      //      if(bError)
      //      {
      //         m_uiptraChild.remove(puiBefore);
      //      }
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <::message::message *> (pmouse->);
      //   if(pmouse->get_lresult() != 0)
      //      return;
      //}
      //catch(...)
      //{
      //}

   }


   void form_list::control_get_client_rect(::user::interaction * pinteraction,RECT * prect)

   {

      if(pinteraction == nullptr)
      {

         SetRectEmpty(prect);


         return;

      }

      ::rect rectControl;

      draw_list_item item(this);

      item.m_iDisplayItem = m_iDisplayItemHover;

      item.m_iItem = _001DisplayToStrict((::index) m_iDisplayItemHover);

      if(m_bGroup)
      {

         item.m_iGroupTopDisplayIndex = 0;

         for(item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
         {

            item.m_iGroupCount = _001GetGroupItemCount((::index) item.m_iGroup);

            if(item.item_index() >= item.m_iGroupTopDisplayIndex && item.item_index() < (item.m_iGroupTopDisplayIndex + item.m_iGroupCount))
            {

               break;

            }

         }

      }

      item.m_iSubItem = pinteraction->descriptor().subitem_index();

      item.m_iOrder = _001MapSubItemToOrder(item.subitem_index());

      item.m_iListItem = -1;

      _001GetElementRect(&item,::user::mesh::element_sub_item);

      rectControl = item.m_rectSubItem;

      ::rect rect(rectControl);

      *prect = rect;


   }


   void form_list::control_get_window_rect(::user::interaction * pinteraction,RECT * prect)

   {

      control_get_client_rect(pinteraction,prect);


      _001ClientToScreen(prect);


   }


   bool form_list::control_001DisplayHitTest(const ::point & point)
   {

      return _001DisplayHitTest(point,m_itemControl.m_iItem,m_itemControl.m_iSubItem);

   }


   bool form_list::_001PreviousEditableControl(index & iItem, index & iSubItem)
   {

      index iPreviousItem = iItem;

      ::count iColumnCount = _001GetColumnCount();

      index iSubItemColumn = _001MapSubItemToColumn(iSubItem);

      index iColumnPrevious = -1;

      for (index iColumn = iSubItemColumn - 1; iColumn >= 0; iColumn--)
      {

         if (m_columna.get_visible(iColumn)->m_iControl >= 0
               && _001GetControl(iItem, m_columna.get_visible(iColumn)->subitem_index()) != nullptr
               && _001IsSubItemEnabled(iItem, m_columna.get_visible(iColumn)->subitem_index()))
         {

            iColumnPrevious = iColumn;

            break;

         }

      }

      if (iColumnPrevious < 0)
      {

         iPreviousItem--;

         for (index iColumn = iColumnCount - 1; iColumn >= iSubItemColumn; iColumn--)
         {

            if (m_columna.get_visible(iColumn)->m_iControl >= 0
                  && _001GetControl(iItem, m_columna.get_visible(iColumn)->subitem_index()) != nullptr
                  && _001IsSubItemEnabled(iItem, m_columna.get_visible(iColumn)->subitem_index()))
            {

               iColumnPrevious = iColumn;

               break;

            }

         }

      }

      if (iColumnPrevious >= 0)
      {

         if (iPreviousItem < 0)
         {

            iPreviousItem = _001GetItemCount() - 1;

         }

         if (iPreviousItem < 0)
         {

            return false;

         }

         iItem = iPreviousItem;

         iSubItem = _001MapColumnToSubItem(iColumnPrevious);

         return true;

      }

      return false;

   }


   bool form_list::_001NextEditableControl(index & iItem, index & iSubItem)
   {

      index iNextItem = iItem;

      index iColumnCount = _001GetColumnCount();

      index iSubItemColumn = _001MapSubItemToColumn(iSubItem);

      index iColumnNext = -1;

      for (index iColumn = iSubItemColumn + 1; iColumn < iColumnCount; iColumn++)
      {

         if (m_columna.get_visible(iColumn)->m_iControl >= 0
               && _001GetControl(iItem, m_columna.get_visible(iColumn)->subitem_index()) != nullptr
               && _001IsSubItemEnabled(iItem, m_columna.get_visible(iColumn)->subitem_index()))
         {

            iColumnNext = iColumn;

            break;

         }

      }

      if (iColumnNext < 0)
      {

         iNextItem++;

         for (index iColumn = 0; iColumn <= iSubItemColumn; iColumn++)
         {

            if (m_columna.get_visible(iColumn)->m_iControl >= 0
                  && _001GetControl(iItem, m_columna.get_visible(iColumn)->subitem_index()) != nullptr
                  && _001IsSubItemEnabled(iItem, m_columna.get_visible(iColumn)->subitem_index()))
            {

               iColumnNext = iColumn;

               break;

            }

         }

      }

      if (iColumnNext >= 0)
      {

         if (iNextItem >= _001GetItemCount())
         {

            iNextItem = 0;

         }

         if (iNextItem >= _001GetItemCount())
         {

            return false;

         }

         iItem = iNextItem;

         iSubItem = _001MapColumnToOrder(iColumnNext);

         return true;

      }

      return false;

   }

   bool form_list::_001UpperEditableControl(index & iItem, index & iSubItem)
   {

      index iUpperItem = iItem - 1;

      for (; iUpperItem >= 0; iUpperItem--)
      {

         if (_001GetControl(iUpperItem, iSubItem) != nullptr && _001IsSubItemEnabled(iUpperItem, iSubItem))
         {

            iItem = iUpperItem;

            return true;

         }

      }

      for (iUpperItem = _001GetItemCount() - 1; iUpperItem >= iItem; iUpperItem--)
      {

         if (_001GetControl(iUpperItem, iSubItem) != nullptr && _001IsSubItemEnabled(iUpperItem, iSubItem))
         {

            iItem = iUpperItem;

            return true;

         }

      }

      iItem--;

      if (iItem < 0)
      {

         iItem = _001GetItemCount() - 1;

      }

      return _001PreviousEditableControl(iItem, iSubItem);

   }


   bool form_list::_001LowerEditableControl(index & iItem, index & iSubItem)
   {

      index iLowerItem = iItem + 1;

      for (; iLowerItem <  _001GetItemCount() - 1; iLowerItem++)
      {

         if (_001GetControl(iLowerItem, iSubItem) != nullptr && _001IsSubItemEnabled(iLowerItem, iSubItem))
         {

            iItem = iLowerItem;

            return true;

         }

      }

      for (iLowerItem = 0; iLowerItem <= iItem; iLowerItem++)
      {

         if (_001GetControl(iLowerItem, iSubItem) != nullptr && _001IsSubItemEnabled(iLowerItem, iSubItem))
         {

            iItem = iLowerItem;

            return true;

         }

      }

      iItem++;

      if (iItem >= _001GetItemCount())
      {

         iItem = 0;

      }

      return _001NextEditableControl(iItem, iSubItem);

   }



   void form_list::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_after_change_cur_sel)
      {

         if (m_pcontrolEdit == pevent->m_puie)
         {

            if (m_pcontrolEdit->descriptor().has_function(::user::control_function_data_selection))
            {

               _001SaveEdit(m_pcontrolEdit);

               pevent->m_bRet = true;

            }

         }

      }
      else if (pevent->m_eevent == ::user::event_enter_key)
      {

         if(m_pcontrolEdit != nullptr)
         {

            _001SaveEdit(m_pcontrolEdit);

            _001HideControl(m_pcontrolEdit);

            pevent->m_bRet = true;

         }

      }
      else if (pevent->m_eevent == ::user::event_tab_key)
      {

         index iItem = 0;

         index iSubItem = 0;

         if (m_pcontrolEdit != nullptr)
         {

            iItem = m_pcontrolEdit->m_iEditItem;

            iSubItem = m_pcontrolEdit->descriptor().subitem_index();

            _001SaveEdit(m_pcontrolEdit);

            _001HideControl(m_pcontrolEdit);

            pevent->m_bRet = true;

         }

         bool bOk;

         if (Session.is_key_pressed(::user::key_shift))
         {

            bOk = _001PreviousEditableControl(iItem, iSubItem);

         }
         else
         {

            bOk = _001NextEditableControl(iItem, iSubItem);

         }

         if(bOk)
         {

            __pointer(control) pinteraction = _001GetControl(iItem, iSubItem);

            _001PlaceControl(pinteraction, iItem);

            pevent->m_bRet = true;

         }

      }
      else if (pevent->m_eevent == ::user::event_key_down)
      {

         SCAST_PTR(::message::key, pkey, pevent->m_pmessage);

         if (pkey->m_ekey == key_down || pkey->m_ekey == key_up
               || pkey->m_ekey == key_left || pkey->m_ekey == key_right)
         {

            index iItem = 0;

            index iSubItem = 0;

            if (m_pcontrolEdit != nullptr)
            {

               __pointer(::user::plain_edit) pedit = m_pcontrolEdit;

               if (pedit.is_set())
               {

                  strsize iSel;

                  strsize iSelEnd;

                  pedit->_001GetSel(iSel, iSelEnd);

                  if (iSel != iSelEnd)
                  {

                     iSel = -1;

                  }

                  if (pkey->m_ekey == key_left && iSel != 0)
                  {

                     return;

                  }
                  else if (pkey->m_ekey == key_right)
                  {

                     strsize iLen = pedit->_001GetTextLength();

                     if (iSel != iLen)
                     {

                        return;

                     }

                  }

               }

               iItem = m_pcontrolEdit->m_iEditItem;

               iSubItem = m_pcontrolEdit->descriptor().subitem_index();

               _001SaveEdit(m_pcontrolEdit);
               _001HideControl(m_pcontrolEdit);

               pevent->m_bRet = true;

            }

            bool bOk = false;

            if (pkey->m_ekey == key_left)
            {

               bOk = _001PreviousEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == key_right)
            {

               bOk = _001NextEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == key_up)
            {

               bOk = _001UpperEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == key_down)
            {

               bOk = _001LowerEditableControl(iItem, iSubItem);

            }

            if (bOk)
            {

               __pointer(control) pinteraction = _001GetControl(iItem, iSubItem);

               _001PlaceControl(pinteraction, iItem);

               __pointer(::user::plain_edit) pedit = m_pcontrolEdit;

               if(pedit.is_set())
               {

                  if (pkey->m_ekey == key_left)
                  {

                     strsize iLen = pedit->_001GetTextLength();

                     pedit->_001SetSel(iLen, iLen);


                  }
                  else if (pkey->m_ekey == key_right)
                  {

                     pedit->_001SetSel(0, 0);


                  }

               }

               pevent->m_bRet = true;

            }

         }

      }

      if (pevent->m_bRet)
      {

         return;

      }

      return form_mesh::on_control_event(pevent);
   }


   bool form_list::_001HitTest_(const ::point & point,index &iItem,index &iSubItem)
   {

      return ::user::list::_001HitTest_(point,iItem,iSubItem);

   }


   void form_list::_001DrawSubItem(draw_list_item * pdrawitem)
   {

      if (pdrawitem->m_pcolumn->m_iControl >= 0)
      {

         auto rScreen = pdrawitem->m_rectSubItem;

         _001ClientToScreen(rScreen);

         if (rScreen.contains(Session.m_pointCursor))
         {

            auto pstyle = get_style(pdrawitem->m_pgraphics);

            auto crBackHover = get_color(pstyle, ::user::element_background, ::user::e_state_hover);

            if (!crBackHover)
            {

               crBackHover = ARGB(40, 0, 0, 0);

            }

            pdrawitem->m_pgraphics->fill_rect(pdrawitem->m_rectSubItem, crBackHover);

         }

         //if (pdrawitem->m_pcolumn->m_iControl >= 0 && pdrawitem->m_pcolumn->m_iControl < m_controldescriptorset.get_count())
         //{

         //   __pointer(class ::user::control_descriptor) pdescriptor = m_controldescriptorset.sp_at(pdrawitem->m_pcolumn->m_iControl);

         //   if (pdescriptor.is_set())
         //   {

         //      if (pdescriptor->has_function(::user::control_function_check_box))
         //      {

         //         _001GetElementRect(pdrawitem, ::user::mesh::element_text);

         //         if (pdrawitem->m_bOk)
         //         {

         //            rect r;

         //            rect.left = 0;
         //            rect.top = 0;
         //            rect.right = 15;
         //            rect.bottom = 15;

         //            rect.Align(::align_center, pdrawitem->m_rectSubItem);

         //            _001GetItemText(pdrawitem);

         //            ::enum_check echeck;

         //            if (pdrawitem->m_strText == pdescriptor->m_setValue[::check_checked])
         //            {

         //               echeck = ::check_checked;

         //            }
         //            else
         //            {

         //               echeck = ::check_unchecked;

         //            }

         //            if (m_puserstyle != nullptr)
         //            {

         //               m_puserstyle->_001DrawCheckBox(pdrawitem->m_pgraphics, r, echeck);

         //            }

         //         }

         //         return;

         //      }

         //   }

         //  }

      }

      ::user::list::_001DrawSubItem(pdrawitem);

      //if (pdrawitem->m_pcolumn->m_bCustomDraw)
      {

         __pointer(control) pinteraction = _001GetControl(pdrawitem->item_index(), pdrawitem->subitem_index());

         if (pinteraction != nullptr)
         {

            pdrawitem->m_rectClient = pdrawitem->m_rectSubItem;

            pdrawitem->m_rectWindow = pdrawitem->m_rectClient;

            _001ClientToScreen(pdrawitem->m_rectWindow);

            //::rect rectWindow;

            //pinteraction->get_window_rect(rectWindow);

            //_001ScreenToClient(rectWindow);

            //if (rectWindow != pdrawitem->m_rectClient)
            {

               // pinteraction->set_window_pos(0, pdrawitem->m_rectClient, SWP_HIDEWINDOW | SWP_NOZORDER);

            }

            if (!pinteraction->has_focus())
            {

               __pointer(::user::combo_box) pcombobox = pinteraction;

               if (pcombobox.is_set() && !pcombobox->m_bEdit)
               {

                  pdrawitem->m_bOk = false;

                  _001GetItemText(pdrawitem);

                  if (pdrawitem->m_bOk)
                  {

                     string strText;

                     pcombobox->_001GetText(strText);

                     if (pcombobox->get_current_item_string_value() != pdrawitem->m_strText)
                     {

                        pcombobox->set_current_item_by_string_value(pdrawitem->m_strText, ::source_sync);

                     }

                  }

                  goto ok_control;

               }

               __pointer(::user::plain_edit) pedit = pinteraction;

               if (pedit.is_set())
               {

                  pdrawitem->m_bOk = false;

                  _001GetItemText(pdrawitem);

                  if (pdrawitem->m_bOk)
                  {

                     string strText;

                     pedit->_001GetText(strText);

                     if (strText != pdrawitem->m_strText)
                     {

                        pedit->_001SetText(pdrawitem->m_strText, ::source_sync);

                     }

                  }


               }

            }
ok_control:;

            ::draw2d::savedc savedc(pdrawitem->m_pgraphics);

            on_viewport_offset(pdrawitem->m_pgraphics);
            pdrawitem->m_pgraphics->OffsetViewportOrg(pdrawitem->m_rectClient.left, pdrawitem->m_rectClient.top);

            __keep(pinteraction->m_pdrawcontext, pdrawitem);

            pinteraction->_001OnDraw(pdrawitem->m_pgraphics);

            //pinteraction->_003CallCustomDraw(pdrawitem->m_pgraphics,pdrawitem);
            //pdrawitem->m_pgraphics->SelectClipRgn(nullptr);
            //_001OnClip(pdrawitem->m_pgraphics);
         }
      }

      //::user::list::_001DrawSubItem(pdrawitem);

   }


   ::enum_check form_list::_001GetSubItemCheck(index iItem, index iSubItem)
   {

      __pointer(::user::list_column) pcolumn = m_columna.get_by_subitem(iSubItem);

      if (pcolumn.is_set() && pcolumn->m_iControl >= 0)
      {

         __pointer(class ::user::control_descriptor) pdescriptor = m_controldescriptorset.sp_at(pcolumn->m_iControl);

         if (pdescriptor.is_set())
         {

            if (pdescriptor->has_function(::user::control_function_check_box))
            {

               ::user::mesh_item item(this);

               item.m_iItem = iItem;

               item.m_iSubItem = iSubItem;

               _001GetItemText(&item);

               if (!item.m_bOk)
               {

                  return ::check_undefined;

               }

               //::enum_check echeck;

               if (item.m_strText == pdescriptor->m_setValue[::check_checked])
               {

                  return ::check_checked;

               }
               else
               {

                  return ::check_unchecked;

               }


            }

         }

      }

      return ::check_undefined;

   }


   bool form_list::_001SetSubItemCheck(index iItem, index iSubItem, ::enum_check echeck)
   {

      __pointer(::user::list_column) pcolumn = m_columna.get_by_subitem(iSubItem);

      if (pcolumn.is_set() && pcolumn->m_iControl >= 0)
      {

         __pointer(class ::user::control_descriptor) pdescriptor = m_controldescriptorset.sp_at(pcolumn->m_iControl);

         if (pdescriptor.is_set())
         {

            if (pdescriptor->has_function(::user::control_function_check_box))
            {

               ::user::mesh_item item(this);

               item.m_iItem = iItem;
               item.m_iSubItem = iSubItem;
               item.m_strText = pdescriptor->m_setValue[echeck];

               if (!item.m_strText.has_char())
               {

                  return false;

               }

               _001SetItemText(&item);

               return item.m_bOk;

            }

         }

      }

      return false;

   }


   bool form_list::_001IsSubItemEnabled(index iItem, index iSubItem)
   {

      __pointer(::user::list_column) pcolumn = m_columna.get_by_subitem(iSubItem);

      if (pcolumn.is_set() && pcolumn->m_iControl >= 0)
      {

         __pointer(class ::user::control_descriptor) pdescriptor = m_controldescriptorset.sp_at(pcolumn->m_iControl);

         if (pdescriptor.is_set())
         {

            if (pdescriptor->has_function(::user::control_function_disable_on_check_box))
            {

               if(_001GetSubItemCheck(iItem, pdescriptor->m_iSubItemDisableCheckBox) == ::check_checked)
               {

                  return false;

               }

            }

         }

      }

      return true;

   }




} // namespace user









