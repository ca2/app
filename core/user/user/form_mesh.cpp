#include "framework.h"
#include "form_mesh.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"
#include "core/user/user/mesh_item.h"


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


   void form_mesh::get_selection(const ::scoped_string & scopedstrDataKey, ::string_array & straDataKey)
   {

      //mesh::get_selection(key,selection);

   }


   void form_mesh::install_message_routing(::channel * pchannel)
   {
      MESSAGE_LINK(e_message_key_down, pchannel, this,&form_mesh::on_message_key_down);

      form::install_message_routing(pchannel);
      mesh::install_message_routing(pchannel);

   }

   bool form_mesh::_001HitTest_(const ::int_point & point, ::collection::index &iItem, ::collection::index &iSubItem)
   {

      return false;

   }


   bool form_mesh::on_click(::item * pitem, ::user::mouse * pmouse)
   {
      
      if (!::is_set(pitem))
      {

         return false;

      }

      ///::user::interaction * pinteraction = _001GetControl(pitem->m_item.m_iItem, pitem->m_item.m_iSubItem);
      ::user::interaction * pinteraction = _001GetControl(pitem->m_item.m_iItem, pitem->m_item.m_iSubItem);

      if(pinteraction != nullptr)
      {

         if(pinteraction->has_function(::user::e_control_function_action))
         {

            if(pinteraction->get_control_type() == ::user::e_control_type_button)
            {

               auto pextendedtopic = __allocate ::extended_topic(::id_click);

               pextendedtopic->m_puserelement         = pinteraction;

               m_pitemControl                         = pitem;

               send_message(e_message_subject,0, pextendedtopic);

            }

         }
         else
         {

            _001PlaceControl(pinteraction, pitem->m_item.m_iItem, true);

         }

      }

      return true;

   }


   ::user::interaction * form_mesh::_001GetControl(::collection::index iItem, ::collection::index iSubItem)
   {

      return nullptr;

   }






   void form_mesh::_001PlaceControl(::user::interaction * pinteraction, ::collection::index iEditItem, bool bClick, bool bOnlySizeAndPosition)
   {

      ::int_rectangle rectangle;

      auto psubitem = get_subitem(pinteraction->m_iEditItem, pinteraction->m_iEditSubItem);

      psubitem->m_pitem->m_iDisplayItem = strict_to_display(pinteraction->m_iEditItem);
      
      psubitem->m_iOrder = sub_item_to_order(psubitem->m_iSubItem);
      
      //psubitem.m_iListItem = -1;
      
      index_element_rectangle(*psubitem,::user::mesh::e_element_text);

      if(psubitem->m_bOk)
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


   void form_mesh::on_message_scroll_y(::message::message * pmessage)
   {

      pmessage->previous();

      ::user::interaction * pinteraction = _001GetEditControl();

      if(pinteraction != nullptr)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iEditItem);

      }

   }


   void form_mesh::on_message_scroll_x(::message::message * pmessage)
   {

      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      ::user::interaction * pinteraction = _001GetEditControl();

      if(pinteraction != nullptr)
      {

         _001PlaceControl(pinteraction, pinteraction->m_iEditItem);

      }

   }


   bool form_mesh::_001OnMouseActivate(::windowing::window * pDesktopWnd,unsigned int nHitTest,const ::atom & atom, lresult & iResult)
   {
      __UNREFERENCED_PARAMETER(pDesktopWnd);
      __UNREFERENCED_PARAMETER(nHitTest);
      __UNREFERENCED_PARAMETER(atom);
      __UNREFERENCED_PARAMETER(iResult);
      return false;
   }

   void form_mesh::_001OnNotify(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void form_mesh::on_timer(::timer * ptimer)
   {
      mesh::on_timer(ptimer);
   }

   void form_mesh::_001OnMessageNotify(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
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
   //      const ::user::interaction_base ** ppinterface = (const ::user::interaction_base **) lparam;

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

      synchronous_lock synchronouslock(this->synchronization());

      if(_001GetEditControl() != nullptr)
      {

         _001SetEditControl(nullptr);

      }

      for_user_interaction_children(pinteraction, this)
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


   void form_mesh::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if(pkey->m_ekey == ::user::e_key_return)
      {

         _001SaveEdit(_001GetEditControl());

         _001HideEditingControls();

         pmessage->m_bRet = true;

         return;

      }

      pkey->previous();

   }


   void form_mesh::_001DrawSubItem(draw_mesh_subitem * psubitem)
   {
      ::user::mesh::_001DrawSubItem(psubitem);
      //if(pdrawitem->m_pcolumn->m_bCustomDraw)
      //{
      //   ::user::interaction * pinteraction = _001GetControlBySubItem(pdrawitem->m_iSubItem);
      //   if(pinteraction != nullptr)
      //   {
      //      pdrawitem->m_rectangleX = pdrawitem.m_rectangleSubItem;
      //      pdrawitem->m_rectangleWindow = pdrawitem.m_rectangleX;
      //      client_to_screen(pdrawitem->m_rectangleWindow);
      //      control_keep controlkeep(this,pdrawitem->m_iItem,pdrawitem->m_iSubItem);
      //      pinteraction->_003CallCustomDraw(pdrawitem->m_pgraphics,pdrawitem);
      //   }
      //}
   }


   bool form_mesh::_001IsEditing()
   {

      return m_pcontrolEdit != nullptr;

   }


   bool form_mesh::_001IsPointInside(::user::interaction * pinteraction, const huge_integer_point & point)
   {

      if(pinteraction != nullptr)
      {

         if(pinteraction->m_econtroltype == e_control_type_edit
               || pinteraction->m_econtroltype == e_control_type_edit_plain_text)
         {

            if(pinteraction == _001GetEditControl())
            {
               
               ::int_rectangle rectangleWindow;
               
               pinteraction->window_rectangle(rectangleWindow);

               return rectangleWindow.contains(point);

            }
            else
            {
               return false;
            }

         }

      }

      ::int_rectangle rectangleControl;

      ::int_rectangle rectangle;

      draw_mesh_item item;

      item.initialize_mesh_item(this);

      throw ::exception(error_failed);

      return false;

      //return ::is_set(m_pitemControl)
        // && m_pitemControl->m_item.m_iSubItem == pinteraction->m_iEditSubItem;

      //int iEditItem;
      //int iEditSubItem;

      //_001DisplayHitTest(point, iEditItem, iEditSubItem);

      //      item.m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
      //    item.m_iItem = pinteraction->m_iEditItem;
//      item.m_iDisplayItem = DisplayToStrict(pinteraction->m_iEditItem);
//
//      item.m_iSubItem = pinteraction->m_iSubItem;
//      item.m_iOrder = sub_item_to_order(item.m_iSubItem);
//      item.m_iListItem = -1;
//      //index_element_rectangle(&item, ::user::mesh::element_sub_item);
//      rectangleControl = item.m_rectangleSubItem;
//      client_to_screen(rectangleControl);
//      huge_integer_rectangle rectangleForm;
//      window_rectangle(rectangleForm);
//      huge_integer_rectangle rectangleX;
//      rectangleX.top() = rectangleForm.top();
//      rectangleX.bottom() = rectangleForm.bottom();
//      rectangleX.left() = rectangleControl.left();
//      rectangleX.right() = rectangleControl.right();
//      return rectangleX.contains(point) != false;
   }

   //void form_mesh::_001OnColumnChange()
   //{
   //   ::user::mesh::_001OnColumnChange();
   //   for(int i = 0; i < m_columna.get_size(); i++)
   //   {
   //      if(m_columna[i]->m_iControl >= 0 && m_columna[i]->m_iControl < m_controldescriptorset.get_size())
   //      {
   //         ::user::interaction * pinteractionParent, const ::atom & atom = m_controldescriptorset.element_at(m_columna[i]->m_iControl);
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

   //   //::int_point point = pmouse->m_point;

   //   //screen_to_client()(point);

   //   //if(pmouse->m_emessage == e_message_left_button_down)
   //   //{
   //   //
   //   //   int iItem;
   //   //
   //   //   int iSubItem;
   //   //
   //   //   ::user::range range;
   //   //
   //   //   get_selection(range);
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
   //   //int iItem;
   //   //int iSubItem;
   //   //::user::range range;
   //   //get_selection(range);
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
   //   //control_keep controlkeep(this,int_point);
   //   //::pointer<::user::interaction>pinteraction = top_child();
   //   //::pointer<::user::interaction>puiBefore = nullptr;
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


   void form_mesh::control_get_client_rect(::user::interaction * pinteraction, ::int_rectangle  & rectangle)
   {

      if(pinteraction == nullptr)
      {

         ::null(rectangle);

         return;

      }

      //::int_rectangle rectangleControl;

      //auto iItem = display_to_strict(m_iDisplayItemHover);

      //auto psubitem = get_subitem(iItem, pinteraction->m_iSubItem);

      //psubitem->m_pitem->m_iDisplayItem = m_iDisplayItemHover;

      //psubitem->m_iOrder = sub_item_to_order(psubitem->m_iSubItem);

      //index_element_rectangle(*psubitem,::user::mesh::e_element_sub_item);

      //rectangleControl = psubitem->m_pdrawmeshsubitem->m_rectangleSubItem;

      //copy(rectangle, rectangleControl);

   }


   void form_mesh::control_get_window_rect(::user::interaction * pinteraction,::int_rectangle & rectangle)
   {

      control_get_client_rect(pinteraction,rectangle);

      client_to_screen()(rectangle);

   }


   bool form_mesh::control_001DisplayHitTest(const ::int_point & point)
   {

      //return _001DisplayHitTest(point, m_pitemControl->m_item.m_iItem, m_pitemControl->m_item.m_iSubItem);

      throw ::exception(todo);

      return false;

   }


   void form_mesh::handle(::topic * ptopic, ::context * pcontext)
   {

      return form::handle(ptopic, pcontext);

   }


   bool form_mesh::_001OnSetItemText(::user::interaction * pinteraction, ::collection::index iItem, ::collection::index iSubItem)
   {

      return true;

   }


   bool form_mesh::_001OnControlSetFocus(::user::interaction * pinteraction)
   {

      synchronous_lock synchronouslock(this->synchronization());

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

      synchronous_lock synchronouslock(this->synchronization());

      //index iItem;

      //index iSubItem;

      /*if(m_controldescriptorset.find_control(pinteraction,iItem,iSubItem))
      {

         ::pointer<::user::plain_edit>pedit = pinteraction;

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
