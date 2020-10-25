//
//  ios_plane_system.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 03/10/17.
//

#include "framework.h"






//
//  app_system.cpp
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 12/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//


//plane_system * create_plane_system()
//{
//
//   return new ::plane_system();
//
//}
//
//plane_system::plane_system()
//{
//
//   m_psystem = ::get_context_system();
//
//   m_psystem->m_pplanesystem = this;
//
//   m_psystem->initialize_native_window1();
//
//}


//ui_window_ptr plane_system::plane_system_initialize(CGRect rect)
//{
//
//   ::user::native_window_initialize initialize;
//
//   initialize.m_rect.left = rect.origin.x;
//   initialize.m_rect.top = rect.origin.y;
//   initialize.m_rect.right = rect.origin.x + rect.size.width;
//   initialize.m_rect.bottom = rect.origin.x + rect.size.height;
//
//   m_psystem->m_possystemwindow->m_puserinteraction->initialize_native_window(&initialize);
//
//   ::ios::interaction_impl * pimpl = m_psystem->m_possystemwindow->m_puserinteraction->m_pimpl.cast < ::ios::interaction_impl > ();
//
//   UIWindow * window = new_aura_window(pimpl, rect);
//
//   pimpl->m_oswindow = oswindow_get(window);
//
//   pimpl->m_oswindow->set_user_interaction_impl(pimpl);
//
//   ::user::create_struct createstruct;
//   cs.dwExStyle = 0;
//   cs.lpszClass = 0;
//   cs.lpszName = nullptr;
//   cs.style = 0;
//   cs.x = 0;
//   cs.y = 0;
//   cs.cx = 0;
//   cs.cy = 0;
//   //      cs.hwndParent = hWndParent;
//   //   cs.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
//   cs.hMenu = nullptr;
//   //      cs.hInstance = System.m_hInstance;
//   cs.lpCreateParams = nullptr;
//
//   if(pimpl->m_puserinteraction != nullptr)
//   {
//
//      if(!pimpl->m_puserinteraction->pre_create_window(cs))
//      {
//
//         pimpl->PostNcDestroy();
//
//         return FALSE;
//
//      }
//
//   }
//   else
//   {
//
//      if (!pimpl->pre_create_window(cs))
//      {
//
//         pimpl->PostNcDestroy();
//
//         return FALSE;
//
//      }
//
//   }
//
//   if(cs.hwndParent == nullptr)
//   {
//
//      cs.style &= ~WS_CHILD;
//
//   }
//
//   //   puiimpl->m_puserinteraction->m_pthread = ::get_task();
//
//   pimpl->send_message(e_message_create, 0, (LPARAM) &cs);
//
//   ::rect rectMainScreen;
//
//   GetMainScreenRect(rectMainScreen);
//
//   pimpl->SetPlacement(rectMainScreen);
//
//   return window;
//
//}
//
//void plane_system::plane_system_begin()
//{
//
////   m_psystem->m_strAppId = m_pmaindata->m_pmaindata->m_strAppId;
////
////   m_psystem->startup_command(m_pmaindata->m_pmaindata);
////
////   if (!m_psystem->pre_run())
////   {
////
////      return;
////
////   }
////
////
//   if (!m_psystem->request(m_psystem->m_pcommand))
//   {
//
//      return;
//
//   }
//
//
//}


