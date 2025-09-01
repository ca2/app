#include "framework.h"
#include "menu_manager.h"
#include "frame_window.h"
#include "acme/constant/user_message.h"
#include "aura/message/user.h"


namespace experience
{


   menu_manager::menu_manager()
   {

      m_enumState = e_state_initial;

   }


   menu_manager::~menu_manager()
   {

   }


   void menu_manager::initialize_menu_manager(frame_window* pframewindow)
   {

      //auto estatus = 
      
      ::object::initialize(pframewindow);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pframewindow = pframewindow;

      //return estatus;

   }


   void menu_manager::relay_event(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      if (!pusermessage)
      {

         return;

      }

      //throw todo;

      //if (m_pframewindow == nullptr || ::user::message_user_interaction(pusermessage) != m_pframewindow)
      //{

      //   return;

      //}

      if(pusermessage->m_emessage == ::user::e_message_right_button_down)
      {

         m_enumState = StateMBDown;

      }
      else if(pusermessage->m_emessage == ::user::e_message_right_button_up)
      {

         if(m_enumState == StateMBDown)
         {
            //               auto pframewindow = m_pframewindow;

            /*            ::user::menu * pmenu = pframewindow->GetSystemMenu(false);
                     if(pmenu != nullptr)
                     {
                     pmenu->track_popup_menu(
                     pMsg->point.x(), lpMsg->point.y(),

                     pframewindow);
                     }*/
            //pusermessage->m_bRet = true;
            //return;
         }
         m_enumState = e_state_initial;
      }
   }

   void menu_manager::message_handler(::user::interaction * pframewindow, ::user::message * pusermessage)
   {

      switch(pusermessage->m_emessage)
      {
      case ::user::e_message_left_button_double_click:
      {
                              auto point = pusermessage->m_lparam.point();
                              if(OnLButtonDblClk((unsigned int)pusermessage->m_wparam, point))
                              {

                                 pusermessage->m_lresult = 0;

                                 pusermessage->m_bRet = true;

                                 return;

                              }
                              break;
      }
         default:
            break;
      }

      if(pusermessage->m_emessage == ::user::e_message_right_button_down)
      {
         m_enumState = StateMBDown;
      }
      if(pusermessage->m_emessage == ::user::e_message_right_button_down)
      {
         m_enumState = StateMBDown;
      }
      else if(pusermessage->m_emessage == ::user::e_message_right_button_up)
      {
         if(m_enumState == StateMBDown)
         {
            //               auto pframewindow = m_pframewindow;

            /*            ::user::menu * pmenu = pframewindow->GetSystemMenu(false);
                     if(pmenu != nullptr)
                     {
                     const ::int_point & point(LOWORD(lparam), HIWORD(lparam));

                     pframewindow->client_to_screen(&point);
                     pmenu->track_popup_menu(
                     point.x(), point.y(),
                     pframewindow);
                     }*/
            pusermessage->m_bRet = true;
            return;
         }
         m_enumState = e_state_initial;
      }
   }

   bool menu_manager::OnLButtonDblClk(unsigned int nFlags, const ::int_point & point)
   {

      __UNREFERENCED_PARAMETER(nFlags);

      __UNREFERENCED_PARAMETER(point);

      if (m_pframewindow == nullptr)
      {

         return false;

      }

      return false;

   }

   bool menu_manager::set_frame_window(frame_window * pframewindow)
   {
      m_pframewindow = pframewindow;
      return true;
   }




} // namespace experience



