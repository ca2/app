//
//  ios_plane_system.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 03/10/17.
//

#include "framework.h"






//
//  app_system.cpp
//  app
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/05/14.
//  Copyright (c) 2014 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//


//plane_system * create_plane_system()
//{
//
//   return memory_new ::plane_system();
//
//}
//
//plane_system::plane_system()
//{
//
//   system() = ::get_context_system();
//
//   system()->m_pplanesystem = this;
//
//   system()->initialize_native_window1();
//
//}


//ui_window_ptr plane_system::plane_system_initialize(CGRect rectangle_i32)
//{
//
//   ::user::native_window_initialize initialize;
//
//   initialize.m_rectangle.left() = rectangle.origin.x();
//   initialize.m_rectangle.top() = rectangle.origin.y();
//   initialize.m_rectangle.right() = rectangle.origin.x() + rectangle.size.width;
//   initialize.m_rectangle.bottom() = rectangle.origin.x() + rectangle.size.height;
//
//   system()->m_possystemwindow->m_puserinteraction->initialize_native_window(&initialize);
//
//   ::ios::interaction_impl * pimpl = system()->m_possystemwindow->m_puserinteraction->m_pimpl.cast < ::ios::interaction_impl > ();
//
//   UIWindow * window = new_round_window(pimpl, rectangle);
//
//   pimpl->m_oswindow = oswindow_get(window);
//
//   pimpl->m_oswindow->set_user_interaction_impl(pimpl);
//
//   ::user::system createstruct;
//   pusersystem->m_createstruct.dwExStyle = 0;
//   pusersystem->m_createstruct.lpszClass = 0;
//   pusersystem->m_createstruct.lpszName = nullptr;
//   pusersystem->m_createstruct.style = 0;
//   pusersystem->m_createstruct.x() = 0;
//   pusersystem->m_createstruct.y() = 0;
//   pusersystem->m_createstruct.cx() = 0;
//   pusersystem->m_createstruct.cy() = 0;
//   //      pusersystem->m_createstruct.hwndParent = hWndParent;
//   //   pusersystem->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
//   pusersystem->m_createstruct.hMenu = nullptr;
//   //      pusersystem->m_createstruct.hInstance = ::acmeacmesystem()->m_hInstance;
//   pusersystem->m_createstruct.lpCreateParams = nullptr;
//
//   if(pimpl->m_puserinteraction != nullptr)
//   {
//
//      if(!pimpl->m_puserinteraction->pre_create_window(pusersystem))
//      {
//
//         pimpl->post_non_client_destroy();
//
//         return false;
//
//      }
//
//   }
//   else
//   {
//
//      if (!pimpl->pre_create_window(pusersystem))
//      {
//
//         pimpl->post_non_client_destroy();
//
//         return false;
//
//      }
//
//   }
//
//   if(pusersystem->m_createstruct.hwndParent == nullptr)
//   {
//
//      pusersystem->m_createstruct.style &= ~WS_CHILD;
//
//   }
//
//   //   puiimpl->m_puserinteraction->m_pthread = ::get_task();
//
//   pimpl->send_message(e_message_create, 0, (LPARAM) &cs);
//
//   ::rectangle_i32 rectangleMainScreen;
//
//   get_main_screen_rectangle(rectangleMainScreen);
//
//   pimpl->SetPlacement(rectangleMainScreen);
//
//   return window;
//
//}
//
//void plane_system::plane_system_begin()
//{
//
////   system()->m_XstrAppId = m_pmaindata->m_pmaindata->m_XstrAppId;
////
////   system()->startup_command(m_pmaindata->m_pmaindata);
////
////   if (!system()->pre_run())
////   {
////
////      return;
////
////   }
////
////
//   if (!system()->request(system()->m_pcommand))
//   {
//
//      return;
//
//   }
//
//
//}


