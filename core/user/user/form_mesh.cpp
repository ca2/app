#include "framework.h"


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
      IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this,&form_mesh::_001OnKeyDown);

      form::install_message_routing(pchannel);
      mesh::install_message_routing(pchannel);

   }

   bool form_mesh::_001HitTest_(const ::point & point,index &iItem,index &iSubItem)
   {

      return false;

   }


   bool form_mesh::on_click(const ::user::item & item)
   {
      
      if (!item)
      {

         return false;

      }

      ::user::control * pcontrol = _001GetControl(item.item_index(), item.subitem_index());

      if(pcontrol != nullptr)
      {
         if(pcontrol->descriptor().has_function(::user::control_function_action))
         {
            if(pcontrol->descriptor().get_control_type() == ::user::control_type_button)
            {


               ::user::control_event ev;
               ev.m_puie                  = pcontrol;
               ev.m_eevent                = ::user::event_button_clicked;

               m_itemControl              = item;

               send_message(EVENT_MESSAGE,0,(LPARAM)&ev);

            }
         }
         else
         {

            _001PlaceControl(pcontrol, item, true);

         }

      }

      return true;

   }


   control * form_mesh::_001GetControl(index iItem, index iSubItem)
   {

      return nullptr;

   }






   void form_mesh::_001PlaceControl(::user::control * pcontrol, index iEditItem, bool bClick, bool bOnlySizeAndPosition)
   {

      ::rect rect;

      draw_mesh_item item(this);

      item.m_iDisplayItem = _001DisplayToStrict(pcontrol->m_iEditItem);
      item.m_iItem = pcontrol->m_iEditItem;
      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;
      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
      item.m_iListItem = -1;
      _001GetElementRect(&item,::user::mesh::element_text);
      if(item.m_bOk)
      {
         
         _001Update(pcontrol);

         pcontrol->order_top();
         
         pcontrol->place(rect);

         pcontrol->display();

         _001SetEditControl(pcontrol);

         pcontrol->SetFocus();

      }

   }


   void form_mesh::_001SetEditControl(::user::control * pcontrol)
   {

      if(pcontrol == nullptr)
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
         m_pcontrolEdit = pcontrol;
      }
   }

   ::user::control * form_mesh::_001GetEditControl()
   {
      return m_pcontrolEdit;
   }


   void form_mesh::_001OnVScroll(::message::message * pmessage)
   {

      pmessage->previous();

      ::user::control * pcontrol = _001GetEditControl();

      if(pcontrol != nullptr)
      {

         _001PlaceControl(pcontrol, pcontrol->m_iEditItem);

      }

   }


   void form_mesh::_001OnHScroll(::message::message * pmessage)
   {

      pmessage->previous();

      if(pmessage->m_bRet)
         return;

      ::user::control * pcontrol = _001GetEditControl();

      if(pcontrol != nullptr)
      {

         _001PlaceControl(pcontrol, pcontrol->m_iEditItem);

      }

   }


   bool form_mesh::_001OnMouseActivate(::user::interaction_impl * pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult)
   {
      UNREFERENCED_PARAMETER(pDesktopWnd);
      UNREFERENCED_PARAMETER(nHitTest);
      UNREFERENCED_PARAMETER(message);
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

      ::user::control * pcontrol = m_controldescriptorset.get_control_by_id(wparam);

      if(pcontrol == nullptr)
      return true;

      user::Notify * pnotify = (user::Notify *) lparam;


      switch(pcontrol->descriptor().get_type())
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
      _001SaveEdit(pcontrol);
      pcontrol->display(display_none);
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

   //LRESULT form_mesh::_001BaseWndGetProperty(EProperty eprop,LPARAM lparam)

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

      sync_lock sl(mutex());

      if(_001GetEditControl() != nullptr)
      {

         _001SetEditControl(nullptr);

      }

      for(i32 i = 0; i < m_controldescriptorset.get_count(); i++)
      {

         class ::user::control_descriptor & descriptor = m_controldescriptorset(i);

         if(descriptor.m_econtroltype == control_type_edit  || descriptor.m_econtroltype == control_type_edit_plain_text)
         {

            for(auto pair : descriptor.m_controlmap)
            {

               if(pair.element2().is_set())
               {

                  pair.element2()->display(display_none);

               }

            }

         }

      }

   }


   void form_mesh::_001HideControl(::user::control * pcontrol)
   {
      pcontrol->display(display_none);
   }


   void form_mesh::_001OnKeyDown(::message::message * pmessage)
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

   void form_mesh::_001DrawSubItem(draw_mesh_item * pdrawitem)
   {
      ::user::mesh::_001DrawSubItem(pdrawitem);
      //if(pdrawitem->m_pcolumn->m_bCustomDraw)
      //{
      //   ::user::control * pcontrol = _001GetControlBySubItem(pdrawitem->m_iSubItem);
      //   if(pcontrol != nullptr)
      //   {
      //      pdrawitem->m_rectClient = pdrawitem.m_rectSubItem;
      //      pdrawitem->m_rectWindow = pdrawitem.m_rectClient;
      //      _001ClientToScreen(pdrawitem->m_rectWindow);
      //      control_keep controlkeep(this,pdrawitem->m_iItem,pdrawitem->m_iSubItem);
      //      pcontrol->_003CallCustomDraw(pdrawitem->m_pgraphics,pdrawitem);
      //   }
      //}
   }


   bool form_mesh::_001IsEditing()
   {

      return m_pcontrolEdit != nullptr;

   }


   bool form_mesh::_001IsPointInside(::user::control * pcontrol,point64 point)
   {

      if(pcontrol->m_pdescriptor != nullptr)
      {

         if(pcontrol->m_pdescriptor->m_econtroltype == control_type_edit
               || pcontrol->m_pdescriptor->m_econtroltype == control_type_edit_plain_text)
         {

            if(pcontrol == _001GetEditControl())
            {
               
               ::rect rectWindow;
               
               pcontrol->get_window_rect(rectWindow);

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

      draw_mesh_item item(this);

      return m_itemControl 
         && m_itemControl.m_iSubItem == pcontrol->descriptor().m_iSubItem;

      //i32 iEditItem;
      //i32 iEditSubItem;

      //_001DisplayHitTest(point, iEditItem, iEditSubItem);

      //      item.m_iDisplayItem = DisplayToStrict(pcontrol->m_iEditItem);
      //    item.m_iItem = pcontrol->m_iEditItem;
//      item.m_iDisplayItem = DisplayToStrict(pcontrol->m_iEditItem);
//
//      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;
//      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
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

   //void form_mesh::_001OnColumnChange()
   //{
   //   ::user::mesh::_001OnColumnChange();
   //   for(i32 i = 0; i < m_columna.get_size(); i++)
   //   {
   //      if(m_columna[i]->m_iControl >= 0 && m_columna[i]->m_iControl < m_controldescriptorset.get_size())
   //      {
   //         class control_descriptor * pdescriptor = m_controldescriptorset.element_at(m_columna[i]->m_iControl);
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

   void form_mesh::_000OnMouse(::message::mouse * pmouse)
   {

      ::user::control::_000OnMouse(pmouse);

      //if (pmouse->m_bRet)
      //{

      //   return;

      //}

      //::point point = pmouse->m_point;

      //_001ScreenToClient(point);

      //if(pmouse->m_id == WM_LBUTTONDOWN)
      //{
      //
      //   i32 iItem;
      //
      //   i32 iSubItem;
      //
      //   ::user::range range;
      //
      //   _001GetSelection(range);
      //
      //   if(_001DisplayHitTest(point, iItem, iSubItem))
      //   {
      //
      //      class ::user::control_descriptor * pcontrol = m_controldescriptorset.get_by_sub_item(iSubItem);
      //
      //      if(pcontrol != nullptr
      //      && pcontrol->m_pcontrol != nullptr
      //      && (pcontrol->m_etype == type_edit
      //      || pcontrol->m_etype == type_edit_plain_text)
      //&& !range.has_sub_item(iItem, iSubItem))
      //{
      //_001HideEditingControls();
      //return false;
      //}
      //}
      //}
      //else if(uiMessage == WM_LBUTTONUP)
      //{
      //i32 iItem;
      //i32 iSubItem;
      //::user::range range;
      //_001GetSelection(range);
      //if(_001DisplayHitTest(point, iItem, iSubItem))
      //{
      //class ::user::control_descriptor * pcontrol = m_controldescriptorset.get_by_sub_item(iSubItem);
      //if(pcontrol != nullptr
      //&& pcontrol->m_pcontrol != nullptr
      //&& !pcontrol->m_pcontrol->is_window_visible()
      //&& (pcontrol->m_etype == type_edit
      //|| pcontrol->m_etype == type_edit_plain_text))
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

   }


   void form_mesh::control_get_client_rect(::user::control * pcontrol,RECT * prect)

   {

      if(pcontrol == nullptr)
      {

         SetRectEmpty(prect);


         return;

      }

      ::rect rectControl;

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

      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;

      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);

      item.m_iListItem = -1;

      _001GetElementRect(&item,::user::mesh::element_sub_item);

      rectControl = item.m_rectSubItem;

      ::rect rect(rectControl);

      *prect = rect;


   }


   void form_mesh::control_get_window_rect(::user::control * pcontrol,RECT * prect)

   {
      control_get_client_rect(pcontrol,prect);

      _001ClientToScreen(prect);

   }


   bool form_mesh::control_001DisplayHitTest(const ::point & point)
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

      sync_lock sl(mutex());

      index iItem;

      index iSubItem;

      if(m_controldescriptorset.find_control(pinteraction,iItem,iSubItem))
      {

         pinteraction->order(zorder_top);
         
         pinteraction->display();
         //, nullptr, SWP_NOSIZE | SWP_NOMOVE);

      }

      return true;

   }



   bool form_mesh::_001OnControlKillFocus(::user::interaction * pinteraction)
   {

      sync_lock sl(mutex());

      index iItem;

      index iSubItem;

      if(m_controldescriptorset.find_control(pinteraction,iItem,iSubItem))
      {

         __pointer(::user::plain_edit) pedit = pinteraction;

         if(pedit.is_set())
         {

            if(!_001OnSetItemText(pinteraction,iItem,iSubItem))
            {

               return false;

            }

         }

      }

      return true;

   }







} // namespace user
