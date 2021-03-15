#include "framework.h"
#include "base/user/experience/_experience.h"


namespace experience
{


   menu_manager::menu_manager()
   {

      m_enumState = e_state_initial;

   }


   menu_manager::~menu_manager()
   {

   }


   ::e_status menu_manager::initialize_menu_manager(frame_window* pframewindow)
   {

      auto estatus = ::object::initialize(pframewindow);

      if (!estatus)
      {

         return estatus;

      }

      m_pframewindow = pframewindow;

      return estatus;

   }


   void menu_manager::relay_event(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      if (m_pframewindow == nullptr || pusermessage->userinteraction() != m_pframewindow)
      {

         return;

      }

      if(pusermessage->m_id == e_message_right_button_down)
      {
         m_enumState = StateMBDown;
      }
      else if(pusermessage->m_id == e_message_right_button_up)
      {
         if(m_enumState == StateMBDown)
         {
            //               auto pframewindow = m_pframewindow;

            /*            ::user::menu * pmenu = pframewindow->GetSystemMenu(false);
                     if(pmenu != nullptr)
                     {
                     pmenu->track_popup_menu(
                     pMsg->point.x, lpMsg->point.y,

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

      switch(pusermessage->m_id)
      {
      case e_message_left_button_double_click:
      {
                              auto point = __point(pusermessage->m_lparam);
                              if(OnLButtonDblClk((::u32)pusermessage->m_wparam, point))
                              {

                                 pusermessage->m_lresult = 0;

                                 pusermessage->m_bRet = true;

                                 return;

                              }
                              break;
      }
      }

      if(pusermessage->m_id == e_message_right_button_down)
      {
         m_enumState = StateMBDown;
      }
      if(pusermessage->m_id == e_message_right_button_down)
      {
         m_enumState = StateMBDown;
      }
      else if(pusermessage->m_id == e_message_right_button_up)
      {
         if(m_enumState == StateMBDown)
         {
            //               auto pframewindow = m_pframewindow;

            /*            ::user::menu * pmenu = pframewindow->GetSystemMenu(false);
                     if(pmenu != nullptr)
                     {
                     const ::point_i32 & point(LOWORD(lparam), HIWORD(lparam));

                     pframewindow->_001ClientToScreen(&point);
                     pmenu->track_popup_menu(
                     point.x, point.y,
                     pframewindow);
                     }*/
            pusermessage->m_bRet = true;
            return;
         }
         m_enumState = e_state_initial;
      }
   }

   bool menu_manager::OnLButtonDblClk(::u32 nFlags, const ::point_i32 & point)
   {

      UNREFERENCED_PARAMETER(nFlags);

      UNREFERENCED_PARAMETER(point);

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



