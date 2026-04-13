// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "NotifyIconWindow.h"

namespace innate_subsystem
{


   NotifyIconWindow::NotifyIconWindow()
   //: m_wph(0)
   {
      // //
      // // Register window class
      // //
      //
      // WNDCLASS wc;
      //
      // wc.style = 0;
      // wc.lpfnWndProc = WindowProcHolder::defWindowProc;
      // wc.cbClsExtra = 0;
      // wc.cbWndExtra = 0;
      // wc.hInstance = GetModuleHandle(0);
      // wc.hIcon = NULL;
      // wc.hCursor = NULL;
      // wc.hbrBackground = NULL;
      // wc.lpszMenuName = NULL;
      // wc.lpszClassName = _T("NotifyIconWindowClass");
      //
      // ATOM atom = RegisterClass(&wc);
      //
      // //
      // // Create window
      // //
      //
      // m_window = CreateWindow((LPCTSTR)atom,
      //                         (LPCTSTR)_T("NotifyIconWindowTitle"),
      //                         WS_OVERLAPPED,
      //                         CW_USEDEFAULT, CW_USEDEFAULT,
      //                         CW_USEDEFAULT, CW_USEDEFAULT,
      //                         NULL, NULL, GetModuleHandle(0), NULL);
      //
      // SetWindowLongPtr(m_window, GWLP_USERDATA, (LONG_PTR)m_wph);
   }

   NotifyIconWindow::~NotifyIconWindow()
   {
      //setWindowProcHolder(NULL);

      //DestroyWindow(m_window);
   }
   //
   // ::operating_system::window NotifyIconWindow::getWindow()
   // {
   //    //return m_window;
   //    return m_pparticleThis->getWindow();
   // // }
   //
   //
   // bool NotifyIconWindow::on_window_procedure(lresult &lresult, unsigned int message, wparam wparam, lparam lparam)
   // {
   //
   //    // Make sure to reset it back to false before leaving this function for any
   //    // reason (check all return statements, exceptions should not happen here).
   //    //m_inWindowProc = true;
   //
   //    switch (message) {
   //       case WM_USER + 1:
   //          switch (lparam.m_lparam) {
   //          case ::user::e_message_right_button_up:
   //                onNotifyIconRightButtonUp();
   //                break;
   //          case ::user::e_message_left_button_down:
   //                onNotifyIconLeftButtonDown();
   //                break;
   //          } // switch (lParam)
   //          break;
   //       default:
   //          if (message == WM_USER_TASKBAR) {
   //             onTaskBarCreate();
   //    }
   //
   //    return 0;
   // }


   void NotifyIconWindow::onNotifyIconRightButtonUp()
   {



   }



   void NotifyIconWindow::onNotifyIconLeftButtonDown()
   {



   }



   void NotifyIconWindow::onTaskBarCreated()
   {



   }





   // void NotifyIconWindow::setWindowProcHolder(WindowProcHolder *wph)
   // {
   //    //m_wph = wph;
   //
   //    //SetWindowLongPtr(m_window, GWLP_USERDATA, (LONG_PTR)m_wph);
   //
   //    m_pparticleThis->setWindowProcHolder(wph);
   // }
} // namespace innate_subsystem


