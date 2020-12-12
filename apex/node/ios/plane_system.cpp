//
//  ios_plane_system.cpp
//  ios_apex
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
//   UIWindow * window = new_round_window(pimpl, rect);
//
//   pimpl->m_oswindow = oswindow_get(window);
//
//   pimpl->m_oswindow->set_user_interaction_impl(pimpl);
//
//   ::user::create_struct createstruct;
//   pcreatestruct->m_createstruct.dwExStyle = 0;
//   pcreatestruct->m_createstruct.lpszClass = 0;
//   pcreatestruct->m_createstruct.lpszName = nullptr;
//   pcreatestruct->m_createstruct.style = 0;
//   pcreatestruct->m_createstruct.x = 0;
//   pcreatestruct->m_createstruct.y = 0;
//   pcreatestruct->m_createstruct.cx = 0;
//   pcreatestruct->m_createstruct.cy = 0;
//   //      pcreatestruct->m_createstruct.hwndParent = hWndParent;
//   //   pcreatestruct->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
//   pcreatestruct->m_createstruct.hMenu = nullptr;
//   //      pcreatestruct->m_createstruct.hInstance = System.m_hInstance;
//   pcreatestruct->m_createstruct.lpCreateParams = nullptr;
//
//   if(pimpl->m_puserinteraction != nullptr)
//   {
//
//      if(!pimpl->m_puserinteraction->pre_create_window(pcreatestruct))
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
//      if (!pimpl->pre_create_window(pcreatestruct))
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
//   if(pcreatestruct->m_createstruct.hwndParent == nullptr)
//   {
//
//      pcreatestruct->m_createstruct.style &= ~WS_CHILD;
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


