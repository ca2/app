#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif


namespace experience
{


   menu_manager::menu_manager(frame_window * pframewindow) :
      ::object(pframewindow)
   {

      m_pframewindow = pframewindow;
      m_enumState = state_initial;

   }


   menu_manager::~menu_manager()
   {

   }


   void menu_manager::relay_event(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (m_pframewindow == nullptr || pbase->userinteraction() != m_pframewindow)
      {

         return;

      }

      if(pbase->m_id == WM_RBUTTONDOWN)
      {
         m_enumState = StateMBDown;
      }
      else if(pbase->m_id == WM_RBUTTONUP)
      {
         if(m_enumState == StateMBDown)
         {
            //               auto pframewindow = m_pframewindow;

            /*            ::user::menu * pmenu = pframewindow->GetSystemMenu(FALSE);
                     if(pmenu != nullptr)
                     {
                     pmenu->track_popup_menu(
                     pMsg->point.x, lpMsg->point.y,

                     pframewindow);
                     }*/
            //pbase->m_bRet = true;
            //return;
         }
         m_enumState = state_initial;
      }
   }

   void menu_manager::message_handler(::user::interaction * pframewindow, ::message::base * pbase)
   {

      switch(pbase->m_id)
      {
      case WM_LBUTTONDBLCLK:
      {
                              auto point = __point(pbase->m_lparam);
                              if(OnLButtonDblClk((UINT)pbase->m_wparam, point))
                              {

                                 pbase->m_lresult = 0;

                                 pbase->m_bRet = true;

                                 return;

                              }
                              break;
      }
      }

      if(pbase->m_id == WM_RBUTTONDOWN)
      {
         m_enumState = StateMBDown;
      }
      if(pbase->m_id == WM_RBUTTONDOWN)
      {
         m_enumState = StateMBDown;
      }
      else if(pbase->m_id == WM_RBUTTONUP)
      {
         if(m_enumState == StateMBDown)
         {
            //               auto pframewindow = m_pframewindow;

            /*            ::user::menu * pmenu = pframewindow->GetSystemMenu(FALSE);
                     if(pmenu != nullptr)
                     {
                     const ::point & point(LOWORD(lparam), HIWORD(lparam));

                     pframewindow->_001ClientToScreen(&point);
                     pmenu->track_popup_menu(
                     point.x, point.y,
                     pframewindow);
                     }*/
            pbase->m_bRet = true;
            return;
         }
         m_enumState = state_initial;
      }
   }

   bool menu_manager::OnLButtonDblClk(UINT nFlags, const ::point & point)
   {

      UNREFERENCED_PARAMETER(nFlags);

      UNREFERENCED_PARAMETER(point);

      if (m_pframewindow == nullptr)
      {

         return false;

      }
      /*xxx client::e_element eelement;
      if(m_pframewindow->m_pappearance->_001HitTest(point, eelement))
      {
      if(eelement == client::ElementTopLeftIcon)
      {
      m_pframewindow->WindowClose();
      return true;
      }
      }*/
      return false;

   }

   bool menu_manager::set_frame_window(frame_window * pframewindow)
   {
      m_pframewindow = pframewindow;
      return true;
   }




} // namespace experience



