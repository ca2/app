#include "framework.h"
#include "core/user/user/_user.h"


namespace user
{


   form_mesh::form_mesh()
   {

      m_pcontrolEdit = nullptr;

      m_iClickCount    = 0;

   }

   form_mesh::~form_mesh()
   {

   }

   void form_mesh::_001GetSelection(::database::key & key,::database::selection &selection)
   {

      //mesh::_001GetSelection(key,selection);

   }

   void form_mesh::install_message_routing(::channel * pchannel)
   {
      MESSAGE_LINK(e_message_key_down, pchannel, this,&form_mesh::_001OnKeyDown);

      form::install_message_routing(pchannel);
      mesh::install_message_routing(pchannel);

   }

   bool form_mesh::_001HitTest_(const ::point_i32 & point,index &iItem,index &iSubItem)
   {

      return false;

   }


   bool form_mesh::on_click(const ::user::item & item)
   {
      
      if (!item.is_set())
      {

         return false;

      }

      ::user::interaction * pinteraction = _001GetControl(item.item_index(), item.subitem_index());

      if(pinteraction != nullptr)
      {
         if(pinteraction->has_function(::user::e_control_function_action))
         {
            if(pinteraction->get_control_type() == ::user::e_control_type_button)
            {


               ::user::control_event ev;
               ev.m_puie                  = pinteraction;
               ev.m_eevent                = ::user::e_event_button_clicked;

               m_itemControl              = item;

               send_message(e_message_event,0,(lparam)&ev);

            }
         }
         else
         {

            _001PlaceControl(pinteraction, item, true);

         }

      }

      return true;

   }


   ::user::interaction * form_mesh::_001GetControl(index iItem, index iSubItem)
   {

      return nullptr;

   }






   void form_mesh::_001PlaceControl(::user::interaction * pinteraction, index iEditItem, bool bClick, bool bOnlySizeAndPosition)
   {

      ::rectangle_i32 rectangle;

      draw_mesh_item item(this);

      item.m_iDisplayItem = _001StrictToDisplay(pinteraction->m_iItem);
      item.m_iItem = pinteraction->m_iItem;
      item.m_iSubItem = pinteraction->m_iSubItem;
      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
      item.m_iListItem = -1;
      _001GetElementRect(&item,::user::mesh::e_element_text);
      if(item.m_bOk)
      {
         
         _001Update(pinteraction);

         pinteraction->order_top();
         
         pinteraction->place(rectangle);

         pinteraction->display();

         _001SetEditControl(pinteraction);

         pinteraction->set_keyboard_focus();

      }

   }


   void form_mesh::_001SetEditControl(::user::interaction * pinteraction)
   {

      if(!pinteraction)
      {

         if(m_pcontrolEdit)
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


   ::user::interaction * form_mesh::_001GetEditControl()
   {

      return m_pcontrolEdit;

   }


   void form_mesh::_001OnVScroll(::message::message * pmessage)
   {

      pmessage->previous();

      ::user::interaction * pinteraction = _001GetEditControl();

      if(pinteraction != nullptr)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iItem);

      }

   }


   void form_mesh::_001OnHScroll(::message::message * pmessage)
   {

      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      ::user::interaction * pinteraction = _001GetEditControl();

      if(pinteraction != nullptr)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iItem);

      }

   }


   bool form_mesh::_001OnMouseActivate(::user::interaction_impl * pDesktopWnd,::u32 nHitTest,const ::id & id, lresult & iResult)
   {
      UNREFERENCED_PARAMETER(pDesktopWnd);
      UNREFERENCED_PARAMETER(nHitTest);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(iResult);
      return false;
   }

   void form_mesh::_001OnNotify(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void form_mesh::_001OnTimer(::timer * ptimer)
   {
      mesh::_001OnTimer(ptimer);
   }

   void form_mesh::_001OnMessageNotify(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      // linux na verdade revamp
      /*
      lresult = user::NotifyRetContinue;

      ::user::interaction * pinteraction = m_controldescriptorset.get_control_by_id(wparam);

      if(pinteraction == nullptr)
      return true;

      user::Notify * pnotify = (user::Notify *) lparam;


      switch(pinteraction->get_type())
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

   //void form_mesh::_001UpdateColumns()
   //{
   //   _001RemoveControls();
   //   mesh::_001UpdateColumns();
   //}

   //LRESULT form_mesh::_001BaseWndGetProperty(EProperty eprop,lparam lparam)

   //{
   //   switch(eprop)
   //   {
   //   case mesh::PropertyBaseWndInterface:
   //   case mesh::PropertyDrawBaseWndInterface:
   //   {
   //      const ::user::primitive ** ppinterface = (const ::user::primitive **) lparam;

   //      *ppinterface = (mesh *)this;
   //   }
   //   return 1;
   //   default:
   //      return 0;
   //   }
   //}


   void form_mesh::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      mesh::_001OnDraw(pgraphics);

   }


   void form_mesh::_001HideEditingControls()
   {

      synchronous_lock synchronouslock(mutex());

      if(_001GetEditControl() != nullptr)
      {

         _001SetEditControl(nullptr);

      }

      for(auto pinteraction : proper_children())
      {

         if(pinteraction->m_econtroltype == e_control_type_edit  || pinteraction->m_econtroltype == e_control_type_edit_plain_text)
         {

            pinteraction->display(e_display_none);

         }

      }

   }


   void form_mesh::_001HideControl(::user::interaction * pinteraction)
   {

      pinteraction->display(e_display_none);

   }


   void form_mesh::_001OnKeyDown(::message::message * pmessage)
   {

      __pointer(::message::key) pkey(pmessage);

      if(pkey->m_ekey == ::user::e_key_return)
      {

         _001SaveEdit(_001GetEditControl());

         _001HideEditingControls();

         pmessage->m_bRet = true;

         return;

      }

      pkey->previous();

   }


   void form_mesh::_001DrawSubItem(draw_mesh_item * pdrawitem)
   {
      ::user::mesh::_001DrawSubItem(pdrawitem);
      //if(pdrawitem->m_pcolumn->m_bCustomDraw)
      //{
      //   ::user::interaction * pinteraction = _001GetControlBySubItem(pdrawitem->m_iSubItem);
      //   if(pinteraction != nullptr)
      //   {
      //      pdrawitem->m_rectangleClient = pdrawitem.m_rectSubItem;
      //      pdrawitem->m_rectangleWindow = pdrawitem.m_rectangleClient;
      //      _001ClientToScreen(pdrawitem->m_rectangleWindow);
      //      control_keep controlkeep(this,pdrawitem->m_iItem,pdrawitem->m_iSubItem);
      //      pinteraction->_003CallCustomDraw(pdrawitem->m_pgraphics,pdrawitem);
      //   }
      //}
   }


   bool form_mesh::_001IsEditing()
   {

      return m_pcontrolEdit != nullptr;

   }


   bool form_mesh::_001IsPointInside(::user::interaction * pinteraction,point_i64 point)
   {

      if(pinteraction != nullptr)
      {

         if(pinteraction->m_econtroltype == e_control_type_edit
               || pinteraction->m_econtroltype == e_control_type_edit_plain_text)
         {

            if(pinteraction == _001GetEditControl())
            {
               
               ::rectangle_i32 rectWindow;
               
               pinteraction->get_window_rect(rectWindow);

               return rectWindow.contains(point);

            }
            else
            {
               return false;
            }

         }

      }

      ::rectangle_i32 rectControl;

      ::rectangle_i32 rectangle;

      draw_mesh_item item(this);

      return m_itemControl.is_set()
         && m_itemControl.m_iSubItem == pinteraction->m_iSubItem;

      //i32 iEditItem;
      //i32 iEditSubItem;

      //_001DisplayHitTest(point, iEditItem, iEditSubItem);

      //      item.m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
      //    item.m_iItem = pinteraction->m_iEditItem;
//      item.m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
//
//      item.m_iSubItem = pinteraction->m_iSubItem;
//      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
//      item.m_iListItem = -1;
//      //_001GetElementRect(&item, ::user::mesh::element_sub_item);
//      rectControl = item.m_rectSubItem;
//      _001ClientToScreen(rectControl);
//      rectangle_i64 rectForm;
//      get_window_rect(rectForm);
//      rectangle_i64 rectangleClient;
//      rectangleClient.top = rectForm.top;
//      rectangleClient.bottom = rectForm.bottom;
//      rectangleClient.left = rectControl.left;
//      rectangleClient.right = rectControl.right;
//      return rectangleClient.contains(point) != false;
   }

   //void form_mesh::_001OnColumnChange()
   //{
   //   ::user::mesh::_001OnColumnChange();
   //   for(i32 i = 0; i < m_columna.get_size(); i++)
   //   {
   //      if(m_columna[i]->m_iControl >= 0 && m_columna[i]->m_iControl < m_controldescriptorset.get_size())
   //      {
   //         ::user::interaction * pinteractionParent, const ::id & id = m_controldescriptorset.element_at(m_columna[i]->m_iControl);
   //         if(pdescriptor != nullptr)
   //         {
   //            if(m_columna[i]->m_iSubItem >= 0)
   //            {
   //               pdescriptor->m_iSubItem = m_columna[i]->m_iSubItem;
   //            }
   //            else if(pdescriptor->m_iSubItem >= 0)
   //            {
   //               m_columna[i]->m_iSubItem = pdescriptor->m_iSubItem;
   //            }
   //         }
   //      }
   //   }
   //}

   //void form_mesh::_000OnMouse(::message::mouse * pmouse)
   //{

   //   ::user::interaction::_000OnMouse(pmouse);

   //   //if (pmouse->m_bRet)
   //   //{

   //   //   return;

   //   //}

   //   //::point_i32 point = pmouse->m_point;

   //   //_001ScreenToClient(point);

   //   //if(pmouse->m_id == e_message_left_button_down)
   //   //{
   //   //
   //   //   i32 iItem;
   //   //
   //   //   i32 iSubItem;
   //   //
   //   //   ::user::range range;
   //   //
   //   //   _001GetSelection(range);
   //   //
   //   //   if(_001DisplayHitTest(point, iItem, iSubItem))
   //   //   {
   //   //
   //   //      class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
   //   //
   //   //      if(pinteraction != nullptr
   //   //      && pinteraction->m_pcontrol != nullptr
   //   //      && (pinteraction->m_etype == type_edit
   //   //      || pinteraction->m_etype == type_edit_plain_text)
   //   //&& !range.has_sub_item(iItem, iSubItem))
   //   //{
   //   //_001HideEditingControls();
   //   //return false;
   //   //}
   //   //}
   //   //}
   //   //else if(emessage == e_message_left_button_up)
   //   //{
   //   //i32 iItem;
   //   //i32 iSubItem;
   //   //::user::range range;
   //   //_001GetSelection(range);
   //   //if(_001DisplayHitTest(point, iItem, iSubItem))
   //   //{
   //   //class ::user::control_descriptor * pinteraction = m_controldescriptorset.get_by_sub_item(iSubItem);
   //   //if(pinteraction != nullptr
   //   //&& pinteraction->m_pcontrol != nullptr
   //   //&& !pinteraction->m_pcontrol->is_window_visible()
   //   //&& (pinteraction->m_etype == type_edit
   //   //|| pinteraction->m_etype == type_edit_plain_text))
   //   //{
   //   //return false;
   //   //}
   //   //}
   //   //}*/
   //   //control_keep controlkeep(this,point_i32);
   //   //__pointer(::user::interaction) pinteraction = top_child();
   //   //__pointer(::user::interaction) puiBefore = nullptr;
   //   //bool bError;
   //   //try
   //   //{
   //   //   while(pinteraction != nullptr)
   //   //   {
   //   //      bError = false;
   //   //      try
   //   //      {
   //   //         if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
   //   //         {
   //   //            pinteraction->_000OnMouse(pmouse);
   //   //            if(pmouse->m_bRet)
   //   //               return;
   //   //            pinteraction->send(pmouse);
   //   //            if(pmouse->get_lresult() != 0)
   //   //               return;
   //   //         }
   //   //      }
   //   //      catch(...)
   //   //      {
   //   //         bError = true;
   //   //         puiBefore = pinteraction;
   //   //      }
   //   //      pinteraction = under_sibling(pinteraction);
   //   //      if(bError)
   //   //      {
   //   //         m_uiptraChild.erase(puiBefore);
   //   //      }
   //   //   }
   //   //}
   //   //catch(...)
   //   //{
   //   //}
   //   //try
   //   //{
   //   //   (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < ::message::message * > (pmouse->);
   //   //   if(pmouse->get_lresult() != 0)
   //   //      return;
   //   //}
   //   //catch(...)
   //   //{
   //   //}

   //}


   void form_mesh::control_get_client_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle)

   {

      if(pinteraction == nullptr)
      {

         ::null(prectangle);

         return;

      }

      ::rectangle_i32 rectControl;

      draw_mesh_item item(this);

      item.m_iDisplayItem = m_iDisplayItemHover;

      item.m_iItem = _001DisplayToStrict(m_iDisplayItemHover);

      if(m_bGroup)
      {

         item.m_iGroupTopDisplayIndex = 0;

         for(item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
         {

            item.m_iGroupCount = _001GetGroupItemCount(item.m_iGroup);

            if(item.m_iItem >= item.m_iGroupTopDisplayIndex && item.m_iItem < (item.m_iGroupTopDisplayIndex + item.m_iGroupCount))
            {

               break;

            }

         }

      }

      item.m_iSubItem = pinteraction->m_iSubItem;

      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);

      item.m_iListItem = -1;

      _001GetElementRect(&item,::user::mesh::element_sub_item);

      rectControl = item.m_rectSubItem;

      ::rectangle_i32 rectangle(rectControl);

      *prectangle = rectangle;


   }


   void form_mesh::control_get_window_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle)

   {
      control_get_client_rect(pinteraction,prectangle);

      _001ClientToScreen(prectangle);

   }


   bool form_mesh::control_001DisplayHitTest(const ::point_i32 & point)
   {

      return _001DisplayHitTest(point,m_itemControl.m_iItem, m_itemControl.m_iSubItem);

   }


   void form_mesh::on_control_event(::user::control_event * pevent)
   {


      //if(pdescriptor != nullptr)
      //{
      ///pdescriptor->m_pcontrol->m_iEditItem = m_iControlItem;
      //}
      return form::on_control_event(pevent);
   }


   bool form_mesh::_001OnSetItemText(::user::interaction * pinteraction, index iItem, index iSubItem)
   {

      return true;

   }


   bool form_mesh::_001OnControlSetFocus(::user::interaction * pinteraction)
   {

      synchronous_lock synchronouslock(mutex());

      //index iItem;

      //index iSubItem;

      //if(find_control(pinteraction,iItem,iSubItem))
      //{

      //   pinteraction->order(e_zorder_top);
      //   
      //   pinteraction->display();
      //   //, nullptr, SWP_NOSIZE | SWP_NOMOVE);

      //}

      return true;

   }



   bool form_mesh::_001OnControlKillFocus(::user::interaction * pinteraction)
   {

      synchronous_lock synchronouslock(mutex());

      //index iItem;

      //index iSubItem;

      /*if(m_controldescriptorset.find_control(pinteraction,iItem,iSubItem))
      {

         __pointer(::user::plain_edit) pedit = pinteraction;

         if(pedit.is_set())
         {

            if(!_001OnSetItemText(pinteraction,iItem,iSubItem))
            {

               return false;

            }

         }

      }*/

      return true;

   }







} // namespace user
