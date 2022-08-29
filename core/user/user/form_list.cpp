#include "framework.h"
#include "core/user/user/_component.h"
#include "axis/user/user/validate.h"
#include "acme/id.h"
#include "form_list.h"
#include "list_column.h"
#include "list_column_array.h"
#include "list_item.h"
#include "axis/user/user/combo_box.h"
#include "axis/user/user/list_box.h"
#include "aura/message/user.h"
#include "core/platform/session.h"


namespace user
{


   form_list::form_list()
   {

      m_econtroltype = e_control_type_list;

      m_pcontrolEdit = nullptr;

      m_iClickCount = 0;

   }


   form_list::~form_list()
   {

   }


   void form_list::_001GetSelection(::database::key & key, ::database::selection & selection)
   {

      list::_001GetSelection(key, selection);

   }


   void form_list::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_key_down, pchannel, this, &form_list::on_message_key_down);

      form_mesh::install_message_routing(pchannel);

      list::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_vscroll, pchannel, this, &form_list::_001OnVScroll);

      MESSAGE_LINK(e_message_hscroll, pchannel, this, &form_list::_001OnHScroll);

   }




   bool form_list::on_right_click(::item * pitem)
   {

      if (!::is_set(pitem))
      {


         _001HideEditingControls();

         return false;

      }

      auto pinteraction = _001GetControl(pitem->item_index(), pitem->subitem_index());

      if (pinteraction)
      {

         if (pinteraction->has_function(::user::e_control_function_action))
         {

            if (pinteraction->get_control_type() == ::user::e_control_type_button)
            {

               auto pextendedtopic = __new(::extended_topic(id_click));

               pextendedtopic->m_puserelement = pinteraction;

               m_pitemControl = pitem;

               send_message(e_message_subject, 0, pextendedtopic);

            }

         }
         else if (m_pcolumna->get_by_subitem(pitem->subitem_index())->m_bEditOnSecondClick)
         {

            if (m_pitemClick == pitem)
            {

               m_iClickCount++;

            }
            else
            {

               m_iClickCount = 1;

            }

            m_pitemClick = pitem;

            if (m_iClickCount == 2)
            {

               m_iClickCount = 0;

               _001PlaceControl(pinteraction, pitem->item_index());

            }

         }
         else
         {

            _001PlaceControl(pinteraction, pitem->item_index(), true);

         }

      }
      else
      {

         // Click in subitem without editing controls.

         _001HideEditingControls();

      }

      return true;

   }





   bool form_list::on_click(::item * pitem)
   {

      if (!::is_set(pitem))
      {

         _001HideEditingControls();

         return false;

      }

      auto pinteraction = _001GetControl(pitem->item_index(), pitem->subitem_index());

      if (pinteraction)
      {

         if (pinteraction->has_function(::user::e_control_function_action))
         {

            if (pinteraction->get_control_type() == ::user::e_control_type_button)
            {

               auto pextendedtopic = __new(::extended_topic(::id_click));

               pextendedtopic->m_puserelement = pinteraction;

               pextendedtopic->m_atom = ::id_click;

               m_pitemControl = pitem;

               send_message(e_message_subject, 0, pextendedtopic);

            }

         }
         else if (m_pcolumna->get_by_subitem(pitem->subitem_index())->m_bEditOnSecondClick)
         {

            if (m_pitemClick == pitem)
            {

               m_iClickCount++;

            }
            else
            {

               m_iClickCount = 1;

            }

            m_pitemClick = pitem;

            if (m_iClickCount == 2)
            {

               m_iClickCount = 0;

               _001PlaceControl(pinteraction, pitem->item_index());

            }

         }
         else
         {

            _001PlaceControl(pinteraction, pitem->item_index(), true);

         }

      }
      else
      {

         // Click in subitem without editing controls.

         _001HideEditingControls();

         __pointer(::user::list_column) pcolumn = m_pcolumna->get_by_subitem(pitem->subitem_index());

         if (pcolumn.is_set() && pcolumn->m_atom)
         {

            auto pinteraction = get_child_by_id(pcolumn->m_atom);

            if (pinteraction)
            {

               if (pinteraction->has_function(::user::e_control_function_check_box))
               {

                  ::enum_check echeck = _001GetSubItemCheck(pitem->item_index(), pitem->subitem_index());

                  if (echeck == ::e_check_checked)
                  {

                     echeck = ::e_check_unchecked;

                  }
                  else
                  {

                     echeck = ::e_check_checked;

                  }

                  _001SetSubItemCheck(pitem->item_index(), pitem->subitem_index(), echeck);

                  if (echeck == ::e_check_checked)
                  {

                     for (auto pinteraction : proper_children())
                     {

                        if (pinteraction->has_function(::user::e_control_function_duplicate_on_check_box))
                        {

                           if (pinteraction->m_iSubItemDuplicateCheckBox == pitem->subitem_index())
                           {

                              for (auto iSubItemTarget : pinteraction->m_iaSubItemDuplicate)
                              {

                                 auto psubitem = get_subitem(pitem->item_index(), pinteraction->m_iSubItem);

                                 //itemSource.initialize_mesh_item(this);

                                 //itemSource.m_iItem = 

                                 //itemSource.m_iSubItem = 

                                 _001GetSubItemText(psubitem);

                                 if (psubitem->m_bOk)
                                 {

                                    auto psubitemTarget = get_subitem(pitem->item_index(), iSubItemTarget);

                                    psubitemTarget->m_strText = psubitem->m_strText;

                                    _001SetSubItemText(psubitemTarget);

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

            //   rectangle.m_iLowerBound = iItem;

            //   rectangle.m_iUpperBound = iItem;

            //   m_rangeSelection.add_item(rectangle);

            //}
            return ::user::list::on_click(pitem);

         }


      }

      return false;

   }


   interaction * form_list::_001GetControl(index iItem, index iSubItem)
   {

      //synchronous_lock synchronouslock(mutex());

      ::user::list_column * pcolumn = m_pcolumna->get_by_subitem(iSubItem);

      if (!pcolumn || pcolumn->m_atom.is_empty())
      {

         return nullptr;

      }

      auto pcontrol = get_control(pcolumn, iItem);

      return pcontrol;

   }


   interaction * form_list::_001GetControl(draw_list_subitem * psubitem)
   {

      //synchronous_lock synchronouslock(mutex());

      ::user::list_column * pcolumn = psubitem->m_pcolumn;

      if (!pcolumn || pcolumn->m_atom.is_empty())
      {

         return nullptr;

      }

      auto pcontrol = get_control(pcolumn, psubitem->m_pitem->m_iItem);

      return pcontrol;

   }



   void form_list::_001OnShowControl(::user::interaction * pinteraction)
   {


   }


   bool form_list::_001AddControl(::user::interaction * pinteraction)
   {

      if (pinteraction->set_parent(this))
      {

         return false;

      }

      return true;

   }


   void form_list::_001PlaceControl(::user::interaction * pinteraction, index iEditItem, bool bClick, bool bOnlySizeAndPosition)
   {

      bool bSameControl = false;

      bool bSameItemAndSubItem = false;

      if (_001GetEditControl() != nullptr)
      {

         if (_001GetEditControl()->m_iSubItem != pinteraction->m_iSubItem)
         {

            if (!bOnlySizeAndPosition && _001GetEditControl() != nullptr)
            {

               _001SaveEdit(_001GetEditControl());

            }

            if (!bOnlySizeAndPosition && pinteraction->m_iSubItem)
            {

               _001HideEditingControls();

            }

         }
         else
         {

            bSameControl = true;

            _001SaveEdit(_001GetEditControl());

            if (iEditItem == _001GetEditControl()->m_iItem)
            {

               bSameItemAndSubItem = true;

            }

         }

      }

      _001SelectItem(iEditItem);

      auto psubitem = get_subitem(iEditItem, pinteraction->m_iSubItem);

      m_iItem = iEditItem;

      pinteraction->m_iItem = iEditItem;

      psubitem->m_pitem->m_iDisplayItem = _001DisplayToStrict(iEditItem);

      //psubitem->m_iItem = iEditItem;

      //psubitem->m_iColumn = pinteraction->m_iColumn;

      //pitem->m_iSubItem = ;

      psubitem->m_pcolumn = m_pcolumna->get_visible((::index)pinteraction->m_iColumn);

      if (!bOnlySizeAndPosition)
      {

         _001EnsureVisible(psubitem->m_pitem->item_index());

      }

      //psubitem->m_iSubItem = pinteraction->m_iSubItem;

      psubitem->m_iOrder = _001MapSubItemToOrder(psubitem->m_iSubItem);

      _001GetElementRect(*psubitem, ::user::mesh::e_element_text);

      if (psubitem->m_bOk)
      {

         rectangle_f64 rectangleControl(psubitem->m_pdrawmeshsubitem->m_rectangleSubItem);

         auto pointContext = get_context_offset();

         rectangleControl.offset(pointContext);

         if (!bOnlySizeAndPosition)
         {

            _001Update(pinteraction);

         }

         pinteraction->order_top();

         pinteraction->place(rectangleControl);

         if (bOnlySizeAndPosition)
         {

            pinteraction->set_need_layout();

         }

         pinteraction->display();

         //SWP_SHOWWINDOW | (bOnlySizeAndPosition ? SWP_CHANGEVIEWPORTOFFSET : 0));

         if (!bOnlySizeAndPosition)
         {

            _001SetEditControl(pinteraction);

            if (_001IsSubItemEnabled(iEditItem, psubitem->m_iSubItem))
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
                  else if (pcombobox->m_plistbox != nullptr)
                  {

                     __keep(pcombobox->m_plistbox->m_bMovingComboBox);

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

                  pinteraction->set_keyboard_focus();

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

      for (auto pinteraction : proper_children())
      {

         if (pinteraction->has_function(::user::e_control_function_duplicate_on_check_box))
         {

            ::count iItemCount = _001GetItemCount();

            for (index iItem = 0; iItem < iItemCount; iItem++)
            {

               if (_001GetSubItemCheck(iItem, pinteraction->m_iSubItemDuplicateCheckBox) == ::e_check_checked)
               {

                  for (auto iSubItemTarget : pinteraction->m_iaSubItemDuplicate)
                  {

                     auto psubitem = get_subitem(iItem, pinteraction->m_iSubItem);

                     _001GetSubItemText(psubitem);

                     if (psubitem->m_bOk)
                     {

                        auto psubitemTarget = get_subitem(iItem, iSubItemTarget);

                        psubitemTarget->m_strText = psubitem->m_strText;

                        _001SetSubItemText(psubitemTarget);

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

      ASSERT(pinteraction->get_control_type() == e_control_type_edit
         || pinteraction->get_control_type() == e_control_type_edit_plain_text);

      __pointer(::user::plain_edit) pedit = pinteraction;

      //if (pedit.is_set())
      //{

      //   pedit->m_pfont = m_pfont;

      //}

      if (pinteraction->has_function(e_control_function_vms_data_edit))
      {

         auto psubitem = get_subitem(pinteraction->m_iItem, pinteraction->m_iSubItem);

         _001GetSubItemText(psubitem);

         if (psubitem->m_bOk)
         {

            pedit->_001SetText(psubitem->m_strText, ::e_source_initialize);

         }

         //::payload payload;
         //::database::selection selection;
         //_001GetSelection(pinteraction->m_dataid, selection);
         //if (selection.get_item_count() > 0)
         //{
         //   ::database::selection_item & item = selection.get_item(0);
         //   __pointer(::user::edit_text) ptext = nullptr;
         //   if (get_child_by_id(pinteraction->m_atom) != nullptr)
         //   {
         //      ptext = get_child_by_id(pinteraction->m_atom);
         //   }
         //   if (ptext == nullptr && pinteraction != nullptr)
         //   {
         //      ptext = pinteraction;
         //   }
         //   if (ptext == nullptr)
         //      return;
         //   if (data_get(pinteraction->m_dataid.m_atom + "." + pitem->m_atom.m_atom, payload))
         //   {
         //      switch (payload.get_type())
         //      {
         //      case ::e_type_string:
         //      {
         //         string str;
         //         str = payload.m_str;
         //         ptext->_001SetText(str, ::e_source_database);
         //      }
         //      break;
         //      case ::type_int32:
         //      {
         //         string str;
         //         str.format("%d", payload.i32());
         //         ptext->_001SetText(str, ::e_source_database);
         //      }
         //      break;
         //      default:
         //         ASSERT(false);
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

      ASSERT(pinteraction->get_control_type() == e_control_type_combo_box);

      __pointer(::user::combo_box) pcombo = pinteraction;

      if (pinteraction->has_function(e_control_function_data_selection))
      {

         auto psubitem = get_subitem(pinteraction->m_iItem, pinteraction->m_iSubItem);

         _001GetSubItemText(psubitem);

         if (psubitem->m_bOk)
         {

            index iFind = pcombo->_001FindListText(psubitem->m_strText);

            pcombo->set_current_item(__new(::item(::e_element_item, iFind)), ::e_source_sync);

         }

      }

   }


   bool form_list::_001SaveEdit(::user::interaction * pinteraction)
   {

      if (pinteraction == nullptr)
         return false;

      if (pinteraction->get_control_type() == e_control_type_check_box)
      {

         __pointer(::user::check) pcheckbox = pinteraction;

         auto echeck = pcheckbox->echeck();

         auto psubitem = get_subitem(pinteraction->m_iItem, pinteraction->m_iSubItem);

         if (echeck == ::e_check_checked)
         {

            string str(pinteraction->m_setValue[::e_check_checked].get_string());

            if (str.has_char())
            {

               psubitem->m_strText = str;

            }
            else
            {

               psubitem->m_strText = "true";

            }

         }
         else if (echeck == ::e_check_unchecked)
         {

            string str(pinteraction->m_setValue[::e_check_unchecked].get_string());

            if (str.has_char())
            {

               psubitem->m_strText = str;

            }
            else
            {

               psubitem->m_strText = "false";

            }

         }
         else
         {

            string str(pinteraction->m_setValue[::e_check_tristate].get_string());

            if (str.has_char())
            {

               psubitem->m_strText = str;

            }
            else
            {

               psubitem->m_strText = "";

            }

         }

         _001SetSubItemText(psubitem);

         //auto pformlist = this;

         auto ptopic = create_topic(id_control_saved);

         ptopic->m_puserelement = pinteraction;

         route(ptopic);

         //pformlist->handle_subject(ptopic);

         return true;

      }

      ASSERT(pinteraction->get_control_type() == e_control_type_edit || pinteraction->get_control_type() == e_control_type_edit_plain_text
         || pinteraction->get_control_type() == e_control_type_combo_box);

      //auto pinteraction = get_child_by_id(pinteraction->m_atom);

      //if (!pinteraction)
      //{

      //   pinteraction = pinteraction;

      //}

      if (!pinteraction)
      {

         return false;

      }

      string str;

      pinteraction->_001GetText(str);

      ::user::validate validate;

      try
      {

         validate.Validate(str, pinteraction);

      }
      catch (...)
      {

         return false;

      }

      //if (!validate.Validate(str, pinteraction))
      //{

      //   // que tal um balão para indicar o erro

      //   return false;

      //}

      ::payload payload;

      if (!pinteraction->get_data(pinteraction, payload))
      {

         return false;

      }

      if (!_001Validate(pinteraction, payload))
      {

         return false;

      }

      if (pinteraction->has_function(e_control_function_vms_data_edit)
         || pinteraction->has_function(e_control_function_data_selection))
      {

         auto psubitem = get_subitem(pinteraction->m_iItem, pinteraction->m_iSubItem);

         psubitem->m_strText = payload.string();

         _001SetSubItemText(psubitem);

         //auto pformlist = this;

         auto ptopic = create_topic(id_control_saved);

         ptopic->m_puserelement = pinteraction;

         route(ptopic);

         //pformlist->handle_subject(ptopic);

         if (pinteraction->has_function(::user::e_control_function_duplicate_on_check_box))
         {

            if (_001GetSubItemCheck(psubitem->m_pitem->m_iItem, pinteraction->m_iSubItemDuplicateCheckBox) == ::e_check_checked)
            {

               for (auto iSubItemTarget : pinteraction->m_iaSubItemDuplicate)
               {

                  auto psubitemTarget = get_subitem(psubitem->m_pitem->m_iItem, iSubItemTarget);
                  //itemTarget.m_iItem = pitem->item_index();
                  //itemTarget.m_iSubItem = iSubItemTarget;
                  psubitemTarget->m_strText = psubitem->m_strText;

                  _001SetSubItemText(psubitemTarget);

                  //__pointer(::list::column) pcolumn = m_pcolumna->get_by_subitem(iSubItemTarget);
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

      if (!pinteraction)
      {

         if (m_pcontrolEdit)
         {

            _001HideControl(m_pcontrolEdit);

            m_pcontrolEdit = nullptr;

         }

      }
      else
      {

         m_pcontrolEdit = pinteraction;

      }

   }


   interaction * form_list::_001GetEditControl()
   {

      return m_pcontrolEdit;

   }


   void form_list::_001OnVScroll(::message::message * pmessage)
   {

      pmessage->previous();

      auto pinteraction = _001GetEditControl();

      if (pinteraction)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iItem, false, true);

      }

   }


   void form_list::_001OnHScroll(::message::message * pmessage)
   {

      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      auto pinteraction = _001GetEditControl();

      if (pinteraction)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iItem, false, true);

      }

   }


   bool form_list::_001OnMouseActivate(::user::interaction_impl * pDesktopWnd, ::u32 nHitTest, const ::atom & atom, lresult & iResult)
   {

      __UNREFERENCED_PARAMETER(pDesktopWnd);
      __UNREFERENCED_PARAMETER(nHitTest);
      __UNREFERENCED_PARAMETER(atom);
      __UNREFERENCED_PARAMETER(iResult);
      return false;
   }

   void form_list::_001OnNotify(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void form_list::_001OnTimer(::timer * ptimer)
   {
      list::_001OnTimer(ptimer);
   }

   void form_list::_001OnMessageNotify(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      // linux na verdade revamp
      /*
      lresult = user::NotifyRetContinue;

      __pointer(control) pinteraction = m_controldescriptorset.get_control_by_id(wparam);

      if(pinteraction == nullptr)
      return true;

      user::Notify * pnotify = (user::Notify *) lparam;


      switch(pinteraction->get_control_type())
      {
      case e_control_type_edit:
      switch(pnotify->m_uiCode)
      {
      case user::NotifyKeyDown:
      {
      user::NotifyKey * pkey = (user::NotifyKey *) pnotify;
      switch(pkey->m_uiVKey)
      {
      //             //  case VK_RETURN:
      _001SaveEdit(pinteraction);
      pinteraction->display(e_display_none);
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

      //_001RemoveControls();

      list::_001UpdateColumns();

   }

   //LRESULT form_list::_001BaseWndGetProperty(EProperty eprop,lparam lparam)

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

      m_iItem = -1;

      //if(_001GetEditControl() != nullptr)
      //{
      //   _001SetEditControl(nullptr);
      //}
      //for(i32 i = 0; i < m_controldescriptorset.get_count(); i++)
      //{
      //   class ::user::control_descriptor & descriptor = m_controldescriptorset(i);
      //   if(control.m_etype == e_control_type_edit
      //      || control.m_etype == e_control_type_edit_plain_text)
      //   {
      //      if(control.m_pcontrol != nullptr)
      //      {
      //         control.m_pcontrol->display(e_display_none);
      //      }
      //   }
      //}
   }


   void form_list::_001HideControl(::user::interaction * pinteraction)
   {

      pinteraction->display(e_display_none);

   }


   void form_list::on_message_key_down(::message::message * pmessage)
   {
      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_return)
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

      //if (pcolumn->M-atom >= 0)
      //{

      //   m_controldescriptorset[pcolumn->m_iControl]->m_iSubItem = pcolumn->subitem_index();
      //   m_controldescriptorset[pcolumn->m_iControl]->m_iColumn = pcolumn->m_iColumn;

      //}

   }


   bool form_list::_001IsPointInside(::user::interaction * pinteraction, point_i64 point)
   {

      if (pinteraction != nullptr)
      {

         if (pinteraction->m_econtroltype == e_control_type_edit
            || pinteraction->m_econtroltype == e_control_type_edit_plain_text)
         {

            if (pinteraction == _001GetEditControl())
            {

               ::rectangle_i32 rectangleWindow;

               pinteraction->get_window_rect(rectangleWindow);

               return rectangleWindow.contains(point);

            }
            else
            {

               return false;

            }
         }
      }

      ::rectangle_i32 rectangleControl;

      ::rectangle_i32 rectangle;

      //auto pitem = __new(draw_list_item(this));

      return ::is_subitem(m_pitemControl, pinteraction->m_iSubItem);

      //i32 iEditItem;
      //i32 iEditSubItem;

      //_001DisplayHitTest(point, iEditItem, iEditSubItem);

      //      pitem->m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
      //    pitem->item_index() = pinteraction->m_iEditItem;
//      pitem->m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
//
//      pitem->subitem_index() = pinteraction->subitem_index();
//      pitem->m_iOrder = _001MapSubItemToOrder(pitem->subitem_index());
//      pitem->m_iListItem = -1;
//      //_001GetElementRect(&item, ::user::mesh::element_sub_item);
//      rectangleControl = pitem->m_rectangleSubItem;
//      client_to_screen(rectangleControl);
//      rectangle_i64 rectangleForm;
//      get_window_rect(rectangleForm);
//      rectangle_i64 rectangleClient;
//      rectangleClient.top = rectangleForm.top;
//      rectangleClient.bottom = rectangleForm.bottom;
//      rectangleClient.left = rectangleControl.left;
//      rectangleClient.right = rectangleControl.right;
//      return rectangleClient.contains(point) != false;
   }


   void form_list::_001OnColumnChange()
   {

      ::user::list::_001OnColumnChange();


      {

         synchronous_lock synchronouslock(mutex());

         for (index i = 0; i < m_pcolumna->get_size(); i++)
         {

            auto pdescriptor = get_child_by_id((*m_pcolumna)[i]->m_atom);

            if (pdescriptor != nullptr)
            {

               if ((*m_pcolumna)[i]->subitem_index() >= 0)
               {

                  pdescriptor->m_iSubItem = (*m_pcolumna)[i]->subitem_index();

               }
               else if (pdescriptor->m_iSubItem >= 0)
               {

                  (*m_pcolumna)[i]->m_iSubItem = pdescriptor->m_iSubItem;

               }

            }

         }

      }

      if (m_pcontrolEdit != nullptr && m_pcontrolEdit->is_window_visible())
      {

         _001PlaceControl(m_pcontrolEdit, m_pcontrolEdit->m_iItem);

      }

   }


   //   void form_list::_000OnMouse(::message::mouse * pmouse)
   //   {
   //      // must lock ::user::mutex_children() at top stack chain
   //// and only at top stack chain.
   //
   //      auto point = pmouse->m_point;
   //
   //      screen_to_client()(point);
   //
   //      if (pmouse->m_atom == e_message_left_button_down)
   //      {
   //
   //         index iItem;
   //
   //         index iSubItem;
   //
   //         //::user::range range;
   //
   //         //_001GetSelection(range);
   //
   //         if (_001DisplayHitTest(point, iItem, iSubItem))
   //         {
   //
   //            auto pinteraction = get_subitem_control(iSubItem);
   //
   //            if (pinteraction 
   //                  && pinteraction->m_econtroltype == e_control_type_combo_box)
   //            {
   //
   //               _001PlaceControl(pinteraction, (::index) iItem, true);
   //
   //               //pinteraction->m_puserinteraction->message_handler(pmouse);
   //
   //               pmouse->m_bRet = true;
   //
   //               return;
   //
   //            }
   //         }
   //      }
   //      if (pmouse->m_bRet)
   //      {
   //
   //         return;
   //
   //      }
   //
   //
   //      form_mesh::_000OnMouse(pmouse);
   //
   //      if (pmouse->m_bRet)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      //else if(emessage == e_message_left_button_up)
   //      //{
   //      //i32 iItem;
   //      //i32 iSubItem;
   //      //::user::range range;
   //      //_001GetSelection(range);
   //      //if(_001DisplayHitTest(point, iItem, iSubItem))
   //      //{
   //      //class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
   //      //if(pinteraction != nullptr
   //      //&& pinteraction->m_pcontrol != nullptr
   //      //&& !pinteraction->m_pcontrol->is_window_visible()
   //      //&& (pinteraction->m_etype == type_edit
   //      //|| pinteraction->m_etype == type_edit_plain_text))
   //      //{
   //      //return false;
   //      //}
   //      //}
   //      //}*/
   //      //control_keep controlkeep(this,point_i32);
   //      //__pointer(::user::interaction) pinteraction = top_child();
   //      //__pointer(::user::interaction) puiBefore = nullptr;
   //      //bool bError;
   //      //try
   //      //{
   //      //   while(pinteraction != nullptr)
   //      //   {
   //      //      bError = false;
   //      //      try
   //      //      {
   //      //         if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
   //      //         {
   //      //            pinteraction->_000OnMouse(pmouse);
   //      //            if(pmouse->m_bRet)
   //      //               return;
   //      //            pinteraction->send(pmouse);
   //      //            if(pmouse->get_lresult() != 0)
   //      //               return;
   //      //         }
   //      //      }
   //      //      catch(...)
   //      //      {
   //      //         bError = true;
   //      //         puiBefore = pinteraction;
   //      //      }
   //      //      pinteraction = under_sibling(pinteraction);
   //      //      if(bError)
   //      //      {
   //      //         m_uiptraChild.erase(puiBefore);
   //      //      }
   //      //   }
   //      //}
   //      //catch(...)
   //      //{
   //      //}
   //      //try
   //      //{
   //      //   (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < ::message::message * > (pmouse->);
   //      //   if(pmouse->get_lresult() != 0)
   //      //      return;
   //      //}
   //      //catch(...)
   //      //{
   //      //}
   //
   //
   //
   //
   //
   //      //::point_i32 point = pmouse->m_point;
   //      //screen_to_client()(point);
   //      ///*      if(emessage == e_message_left_button_down)
   //      //      {
   //      //      i32 iItem;
   //      //      i32 iSubItem;
   //      //      ::user::range range;
   //      //      _001GetSelection(range);
   //      //      if(_001DisplayHitTest(point, iItem, iSubItem))
   //      //      {
   //      //      class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
   //      //      if(pinteraction != nullptr
   //      //      && pinteraction->m_pcontrol != nullptr
   //      //      && (pinteraction->m_etype == type_edit
   //      //      || pinteraction->m_etype == type_edit_plain_text)
   //      //      && !range.has_sub_item(iItem, iSubItem))
   //      //      {
   //      //      _001HideEditingControls();
   //      //      return false;
   //      //      }
   //      //      }
   //      //      }
   //      //      else if(emessage == e_message_left_button_up)
   //      //      {
   //      //      i32 iItem;
   //      //      i32 iSubItem;
   //      //      ::user::range range;
   //      //      _001GetSelection(range);
   //      //      if(_001DisplayHitTest(point, iItem, iSubItem))
   //      //      {
   //      //      class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
   //      //      if(pinteraction != nullptr
   //      //      && pinteraction->m_pcontrol != nullptr
   //      //      && !pinteraction->m_pcontrol->is_window_visible()
   //      //      && (pinteraction->m_etype == type_edit
   //      //      || pinteraction->m_etype == type_edit_plain_text))
   //      //      {
   //      //      return false;
   //      //      }
   //      //      }
   //      //      }*/
   //      //control_keep controlkeep(this,point_i32);
   //      //__pointer(::user::interaction) pinteraction = top_child();
   //      //__pointer(::user::interaction) puiBefore = nullptr;
   //      //bool bError;
   //      //try
   //      //{
   //      //   while(pinteraction != nullptr)
   //      //   {
   //      //      bError = false;
   //      //      try
   //      //      {
   //      //         if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
   //      //         {
   //      //            pinteraction->_000OnMouse(pmouse);
   //      //            if(pmouse->m_bRet)
   //      //               return;
   //      //            pinteraction->send(pmouse);
   //      //            if(pmouse->get_lresult() != 0)
   //      //               return;
   //      //         }
   //      //      }
   //      //      catch(...)
   //      //      {
   //      //         bError = true;
   //      //         puiBefore = pinteraction;
   //      //      }
   //      //      pinteraction = under_sibling(pinteraction);
   //      //      if(bError)
   //      //      {
   //      //         m_uiptraChild.erase(puiBefore);
   //      //      }
   //      //   }
   //      //}
   //      //catch(...)
   //      //{
   //      //}
   //      //try
   //      //{
   //      //   (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <::message::message *> (pmouse->);
   //      //   if(pmouse->get_lresult() != 0)
   //      //      return;
   //      //}
   //      //catch(...)
   //      //{
   //      //}
   //
   //   }


   void form_list::control_get_client_rect(::user::interaction * pinteraction, RECTANGLE_I32 * prectangle)

   {

      if (pinteraction == nullptr)
      {

         ::null(prectangle);

         return;

      }

      ::rectangle_i32 rectangleControl;

      auto iItem = _001DisplayToStrict((::index)m_iDisplayItemHover);

      auto psubitem = get_subitem(iItem, pinteraction->m_iSubItem);

      psubitem->m_pitem->m_iDisplayItem = m_iDisplayItemHover;

      //pitem->m_iItem = 

      //if(m_bGroup)
      //{

      //   psubitem->m_pitem->m_iGroupTopDisplayIndex = 0;

      //   for(psubitem->m_pitem->m_iGroup = 0; psubitem->m_pitem->m_iGroup < m_nGroupCount; psubitem->m_pitem->m_iGroup++)
      //   {

      //      psubitem->m_pitem->m_iGroupCount = _001GetGroupItemCount((::index)psubitem->m_pitem->m_iGroup);

      //      if(psubitem->m_pitem->item_index() >= psubitem->m_pitem->m_iGroupTopDisplayIndex && psubitem->m_pitem->item_index() < (psubitem->m_pitem->m_iGroupTopDisplayIndex + psubitem->m_pitem->m_iGroupCount))
      //      {

      //         break;

      //      }

      //   }

      //}

      //pitem->m_iSubItem = pinteraction->m_iSubItem;

      psubitem->m_iOrder = _001MapSubItemToOrder(psubitem->m_iSubItem);

      //pitem->m_iListItem = -1;

      _001GetElementRect(*psubitem, ::user::mesh::e_element_sub_item);

      rectangleControl = psubitem->m_pdrawmeshsubitem->m_rectangleSubItem;

      ::rectangle_i32 rectangle(rectangleControl);

      *prectangle = rectangle;


   }


   void form_list::control_get_window_rect(::user::interaction * pinteraction, RECTANGLE_I32 * prectangle)

   {

      control_get_client_rect(pinteraction, prectangle);


      client_to_screen()(*prectangle);


   }


   bool form_list::control_001DisplayHitTest(const ::point_i32 & point)
   {

      return _001DisplayHitTest(point, m_pitemControl->m_iItem, m_pitemControl->m_iSubItem);

   }


   bool form_list::_001PreviousEditableControl(index & iItem, index & iSubItem)
   {

      index iPreviousItem = iItem;

      ::count iColumnCount = _001GetColumnCount();

      index iSubItemColumn = _001MapSubItemToColumn(iSubItem);

      index iColumnPrevious = -1;

      for (index iColumn = iSubItemColumn - 1; iColumn >= 0; iColumn--)
      {

         auto pcolumn = m_pcolumna->get_visible(iColumn);

         auto puserinteraction = get_control(pcolumn, iItem);

         if (pcolumn->m_atom
            && puserinteraction != nullptr
            && _001IsSubItemEnabled(iItem, pcolumn->m_iSubItem))
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

            auto pcolumn = m_pcolumna->get_visible(iColumn);

            auto puserinteraction = get_control(pcolumn, iItem);

            if (puserinteraction != nullptr && _001IsSubItemEnabled(iItem, pcolumn->m_iSubItem))
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

         auto pcolumn = m_pcolumna->get_visible(iColumn);

         auto puserinteraction = get_control(pcolumn, iItem);

         if (puserinteraction != nullptr && _001IsSubItemEnabled(iItem, pcolumn->m_iSubItem))
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

            auto pcolumn = m_pcolumna->get_visible(iColumn);

            auto puserinteraction = get_control(pcolumn, iItem);

            if (puserinteraction != nullptr && _001IsSubItemEnabled(iItem, pcolumn->m_iSubItem))
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

      for (; iLowerItem < _001GetItemCount() - 1; iLowerItem++)
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



   void form_list::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == ::id_set_check)
      {

         auto puserinteraction = ptopic->user_interaction();

         auto iSubItem = puserinteraction->m_iSubItem;

         auto pcolumn = m_pcolumna->get_by_subitem(iSubItem);

         if (::is_set(pcolumn))
         {

            on_check_save(puserinteraction);

         }

      }
      else if (ptopic->m_atom == ::id_after_change_cur_sel)
      {

         if (m_pcontrolEdit == ptopic->user_interaction())
         {

            if (m_pcontrolEdit->has_function(::user::e_control_function_data_selection))
            {

               _001SaveEdit(m_pcontrolEdit);

               ptopic->m_bRet = true;

            }

         }

      }
      else if (ptopic->m_atom == ::id_enter_key)
      {

         if (m_pcontrolEdit != nullptr)
         {

            _001SaveEdit(m_pcontrolEdit);

            _001HideControl(m_pcontrolEdit);

            ptopic->m_bRet = true;

         }

      }
      else if (ptopic->m_atom == ::id_tab_key)
      {

         index iItem = 0;

         index iSubItem = 0;

         if (m_pcontrolEdit != nullptr)
         {

            iItem = m_pcontrolEdit->m_iItem;

            iSubItem = m_pcontrolEdit->m_iSubItem;

            _001SaveEdit(m_pcontrolEdit);

            _001HideControl(m_pcontrolEdit);

            ptopic->m_bRet = true;

         }

         bool bOk;

         auto psession = get_session();

         if (psession->is_key_pressed(::user::e_key_shift))
         {

            bOk = _001PreviousEditableControl(iItem, iSubItem);

         }
         else
         {

            bOk = _001NextEditableControl(iItem, iSubItem);

         }

         if (bOk)
         {

            auto pinteraction = _001GetControl(iItem, iSubItem);

            _001PlaceControl(pinteraction, iItem);

            ptopic->m_bRet = true;

         }

      }
      else if (ptopic->m_atom == ::id_key_down)
      {

         SCAST_PTR(::message::key, pkey, ptopic->m_actioncontext.m_pmessage.m_p);

         if (pkey->m_ekey == e_key_down || pkey->m_ekey == e_key_up
            || pkey->m_ekey == e_key_left || pkey->m_ekey == e_key_right)
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

                  if (pkey->m_ekey == e_key_left && iSel != 0)
                  {

                     return;

                  }
                  else if (pkey->m_ekey == e_key_right)
                  {

                     strsize iLen = pedit->_001GetTextLength();

                     if (iSel != iLen)
                     {

                        return;

                     }

                  }

               }

               iItem = m_pcontrolEdit->m_iItem;

               iSubItem = m_pcontrolEdit->m_iSubItem;

               _001SaveEdit(m_pcontrolEdit);
               _001HideControl(m_pcontrolEdit);

               ptopic->m_bRet = true;

            }

            bool bOk = false;

            if (pkey->m_ekey == e_key_left)
            {

               bOk = _001PreviousEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == e_key_right)
            {

               bOk = _001NextEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == e_key_up)
            {

               bOk = _001UpperEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == e_key_down)
            {

               bOk = _001LowerEditableControl(iItem, iSubItem);

            }

            if (bOk)
            {

               auto pinteraction = _001GetControl(iItem, iSubItem);

               _001PlaceControl(pinteraction, iItem);

               __pointer(::user::plain_edit) pedit = m_pcontrolEdit;

               if (pedit.is_set())
               {

                  if (pkey->m_ekey == e_key_left)
                  {

                     strsize iLen = pedit->_001GetTextLength();

                     pedit->_001SetSel(iLen, iLen);


                  }
                  else if (pkey->m_ekey == e_key_right)
                  {

                     pedit->_001SetSel(0, 0);


                  }

               }

               ptopic->m_bRet = true;

            }

         }

      }

      if (ptopic->m_bRet)
      {

         return;

      }

      return form_mesh::handle(ptopic, pcontext);
   }


   bool form_list::_001HitTest_(const ::point_i32 & point, index & iItem, index & iSubItem)
   {

      return ::user::list::_001HitTest_(point, iItem, iSubItem);

   }


   ::user::interaction * form_list::get_control(::user::list_column * pcolumn, ::index iItem)
   {

      if (!pcolumn->m_puserinteractionTemplate)
      {

         return nullptr;

      }

      auto puserinteractiona = pcolumn->m_puserinteractiona;

      ::index iIndex = iItem - m_iTopDisplayIndex;

      auto & pinteraction = puserinteractiona->interactiona().element_at_grow(iIndex);

      if (!pinteraction)
      {

         auto pinteractionTemplate = pcolumn->m_puserinteractionTemplate;

         if (::is_null(pinteractionTemplate))
         {

            return nullptr;

         }

         pinteraction = ::clone(pinteractionTemplate);

         if (::is_set(pinteraction))
         {

            pinteraction->initialize(this);

            pinteraction->create_child(this);

            pinteraction->add_handler(this);

            pinteraction->m_flagsfunction = pinteractionTemplate->m_flagsfunction;

         }

      }

      pinteraction->m_atom = pcolumn->m_atom;

      pinteraction->m_iItem = iItem;

      pinteraction->m_iSubItem = pcolumn->m_iSubItem;

      return pinteraction;

   }


   void form_list::on_check_save(::user::interaction * puserinteraction)
   {

   }


   void form_list::on_check_load(::user::interaction * puserinteraction)
   {


   }


   void form_list::_001DrawSubItem(::draw2d::graphics_pointer & pgraphics, draw_list_subitem * pdrawlistsubitem)
   {

      //if (psubitem->m_pcolumn->m_atom)
      //{

      //   auto rScreen = psubitem->m_rectangleSubItem;

      //   client_to_screen(rScreen);

      //   auto psession = get_session();

      //   if (rScreen.contains(psession->m_pointCursor))
      //   {

      //      auto pstyle = get_style(psubitem->m_pitem->m_pdrawmeshitem->m_pgraphics);

      //      auto crBackHover = get_color(pstyle, ::e_element_background, ::user::e_state_hover);

      //      if (!crBackHover.is_ok())
      //      {

      //         crBackHover = argb(40, 0, 0, 0);

      //      }

      //      psubitem->m_pitem->m_pdrawmeshitem->m_pgraphics->fill_rectangle(psubitem->m_pdrawmeshsubitem->m_rectangleSubItem, crBackHover);

      //   }

      //   //if (pdrawitem->m_pcolumn->m_iControl >= 0 && pdrawitem->m_pcolumn->m_iControl < m_controldescriptorset.get_count())
      //   //{

      //   //   __pointer(class ::user::control_descriptor) pdescriptor = m_controldescriptorset.sp_at(pdrawitem->m_pcolumn->m_iControl);

      //   //   if (pdescriptor.is_set())
      //   //   {

      //   //      if (pdescriptor->has_function(::user::e_control_function_check_box))
      //   //      {

      //   //         _001GetElementRect(pdrawitem, ::user::mesh::e_element_text);

      //   //         if (pdrawitem->m_bOk)
      //   //         {

      //   //            rectangle_i32 r;

      //   //            rectangle.left = 0;
      //   //            rectangle.top = 0;
      //   //            rectangle.right = 15;
      //   //            rectangle.bottom = 15;

      //   //            rectangle.Align(::e_align_center, pdrawitem->m_rectangleSubItem);

      //   //            _001GetItemText(pdrawitem);

      //   //            ::enum_check echeck;

      //   //            if (pdrawitem->m_strText == pdescriptor->m_setValue[::e_check_checked])
      //   //            {

      //   //               echeck = ::e_check_checked;

      //   //            }
      //   //            else
      //   //            {

      //   //               echeck = ::e_check_unchecked;

      //   //            }

      //   //            if (m_puserstyle != nullptr)
      //   //            {

      //   //               m_puserstyle->_001DrawCheckBox(pdrawitem->m_pgraphics, r, echeck);

      //   //            }

      //   //         }

      //   //         return;

      //   //      }

      //   //   }

      //   //  }

      //}

      ::user::list::_001DrawSubItem(pgraphics, pdrawlistsubitem);

      //if (pdrawitem->m_pcolumn->m_bCustomDraw)
      {
         //
               // trigger control creation
         auto pinteraction = _001GetControl(pdrawlistsubitem);

         if (pinteraction)
         {
            //
            //            //pdrawitem->m_rectangleClient = pdrawitem->m_rectangleSubItem;
            //
            //            //pdrawitem->m_rectangleWindow = pdrawitem->m_rectangleClient;
            //
            pinteraction->place(pdrawlistsubitem->m_pdrawmeshsubitem->m_rectangleSubItem);

            pinteraction->display();

            //
                        //client_to_screen(pdrawitem->m_rectangleWindow);

                        //::rectangle_i32 rectangleWindow;

                        //pinteraction->get_window_rect(rectangleWindow);

                        //screen_to_client(rectangleWindow);

                        //if (rectangleWindow != pdrawitem->m_rectangleClient)
            {

               // pinteraction->set_window_position(0, pdrawitem->m_rectangleClient, SWP_HIDEWINDOW | SWP_NOZORDER);

            }

            if (pinteraction->has_function(::user::e_control_function_check_box))
            {

               on_check_load(pinteraction);

            }

            if (!pinteraction->has_keyboard_focus())
            {

               __pointer(::user::combo_box) pcombobox = pinteraction;

               if (pcombobox.is_set() && !pcombobox->m_bEdit)
               {

                  pdrawlistsubitem->m_bOk = false;

                  _001GetSubItemText(pdrawlistsubitem);

                  if (pdrawlistsubitem->m_bOk)
                  {

                     string strText;

                     pcombobox->_001GetText(strText);

                     if (pcombobox->get_current_item_string_value() != pdrawlistsubitem->m_strText)
                     {

                        pcombobox->set_current_item_by_string_value(pdrawlistsubitem->m_strText, ::e_source_sync);

                     }

                  }

                  goto ok_control;

               }

               __pointer(::user::plain_edit) pedit = pinteraction;

               if (pedit.is_set())
               {

                  pdrawlistsubitem->m_bOk = false;

                  _001GetSubItemText(pdrawlistsubitem);

                  if (pdrawlistsubitem->m_bOk)
                  {

                     string strText;

                     pedit->_001GetText(strText);

                     if (strText != pdrawlistsubitem->m_strText)
                     {

                        pedit->_001SetText(pdrawlistsubitem->m_strText, ::e_source_sync);

                     }

                  }


               }

            }
         ok_control:;
            //
            //            ::draw2d::savedc savedc(pdrawitem->m_pgraphics);
            //
            //            on_context_offset(pdrawitem->m_pgraphics);
            //
            //            __keep(pinteraction->m_pdrawcontext, pdrawitem);
            //
            //            pinteraction->_001OnDraw(pdrawitem->m_pgraphics);
            //
            //            //pinteraction->_003CallCustomDraw(pdrawitem->m_pgraphics,pdrawitem);
            //            //pdrawitem->m_pgraphics->SelectClipRgn(nullptr);
            //            //_001OnClip(pdrawitem->m_pgraphics);
         }
      }

      //::user::list::_001DrawSubItem(pdrawitem);

   }


   ::enum_check form_list::_001GetSubItemCheck(index iItem, index iSubItem)
   {

      __pointer(::user::list_column) pcolumn = m_pcolumna->get_by_subitem(iSubItem);

      if (pcolumn.is_set() && pcolumn->m_atom)
      {

         auto pinteraction = get_child_by_id(pcolumn->m_atom);

         if (pinteraction->has_function(::user::e_control_function_check_box))
         {

            auto psubitem = get_subitem(iItem, iSubItem);

            //pitem->m_iItem = iItem;

            //pitem->m_iSubItem = iSubItem;

            _001GetSubItemText(psubitem);

            if (!psubitem->m_bOk)
            {

               return ::e_check_undefined;

            }

            if (psubitem->m_strText == pinteraction->m_setValue[::e_check_checked])
            {

               return ::e_check_checked;

            }
            else
            {

               return ::e_check_unchecked;

            }

         }

      }

      return ::e_check_undefined;

   }


   bool form_list::_001SetSubItemCheck(index iItem, index iSubItem, ::enum_check echeck)
   {

      __pointer(::user::list_column) pcolumn = m_pcolumna->get_by_subitem(iSubItem);

      if (pcolumn.is_set() && pcolumn->m_atom)
      {

         auto pinteraction = get_child_by_id(pcolumn->m_atom);

         if (pinteraction)
         {

            if (pinteraction->has_function(::user::e_control_function_check_box))
            {

               auto psubitem = get_subitem(iItem, iSubItem);

               //pitem->m_iItem = iItem;
               //pitem->m_iSubItem = iSubItem;
               psubitem->m_strText = pinteraction->m_setValue[echeck];

               if (!psubitem->m_strText.has_char())
               {

                  return false;

               }

               _001SetSubItemText(psubitem);

               return psubitem->m_bOk;

            }

         }

      }

      return false;

   }


   bool form_list::_001IsSubItemEnabled(index iItem, index iSubItem)
   {

      __pointer(::user::list_column) pcolumn = m_pcolumna->get_by_subitem(iSubItem);

      if (pcolumn.is_set() && pcolumn->m_atom)
      {

         auto pinteraction = get_child_by_id(pcolumn->m_atom);

         if (pinteraction)
         {

            if (pinteraction->has_function(::user::e_control_function_disable_on_check_box))
            {

               if (_001GetSubItemCheck(iItem, pinteraction->m_iSubItemDisableCheckBox) == ::e_check_checked)
               {

                  return false;

               }

            }

         }

      }

      return true;

   }


} // namespace user









