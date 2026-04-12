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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
//#include "acme/_operating_system.h"
#include "OperatingSystemApplication.h"

#include "subsystem/_common_header.h"
////#include "remoting/remoting_common/thread/AutoLock.h"

namespace subsystem
{
   //LocalMutex OperatingSystemApplication::m_MDLMutex;

   //::comparable_list_base<HWND> OperatingSystemApplication::m_modelessDialogList;


   //    OperatingSystemApplication::OperatingSystemApplication(::hinstance appInstance,
   //                                        const ::scoped_string & scopedstrwindowClassName)
   // : m_appInstance(appInstance),
   //   m_mainWindow(0),
   //   m_wstrWindowClassName(scopedstrwindowClassName)
   // {
   // }
   OperatingSystemApplication::OperatingSystemApplication()
   {
   }

   OperatingSystemApplication::~OperatingSystemApplication()
   {
   }


   void OperatingSystemApplication::initialize_operating_system_application(const ::scoped_string & scopedstrwindowClassName)
   // : m_appInstance(appInstance),
   //   m_mainWindow(0),
   //   m_wstrWindowClassName(scopedstrwindowClassName)
   {
      m_pparticleThis->initialize_operating_system_application(scopedstrwindowClassName);
   }

   void OperatingSystemApplication::run()
   {
      m_pparticleThis->run();
      //}
      // WNDCLASS wndClass;
      // registerWindowClass(&wndClass);
      // createWindow(wndClass.lpszClassName);
      // try {
      //   m_iExitCode = processMessages();
      // } catch (...) {
      //  m_iExitCode = 1;
      // }
   }

   // int OperatingSystemApplication::processMessages()
   // {
   //
   //    return m_pparticleThis->processMessages();
   //    //   MSG msg;
   //    //   BOOL ret;
   //    //   while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0) {
   //    //     if (ret < 0) {
   //    //       return 1;
   //    //     }
   //    //     if (!processDialogMessage(&msg)) {
   //    //       TranslateMessage(&msg);
   //    //       DispatchMessage(&msg);
   //    //     }
   //    //   }
   //    //
   //    //   return (int)msg.wParam;
   // }

   // void OperatingSystemApplication::createWindow(const ::scoped_string & scopedstrClassName)
   // {
   // //   // m_mainWindow = CreateWindow(::wstring(scopedstrClassName),
   // //   //                             0, 0,
   // //   //                             0, 0, 0, 0,
   // //   //                             HWND_MESSAGE, 0,
   // //   //                             m_appInstance,
   // //   //                             0);
   //
   //    m_pparticleThis->createWindow(scopedstrClassName);
   // }


   void OperatingSystemApplication::createApplicationMainTask()
   {
      //   // m_mainWindow = CreateWindow(::wstring(scopedstrClassName),
      //   //                             0, 0,
      //   //                             0, 0, 0, 0,
      //   //                             HWND_MESSAGE, 0,
      //   //                             m_appInstance,
      //   //                             0);

      m_pparticleThis->createApplicationMainTask();
   }



   void OperatingSystemApplication::postMainThreadMessage(int iMainThreadMessage)
   {
      //   // m_mainWindow = CreateWindow(::wstring(scopedstrClassName),
      //   //                             0, 0,
      //   //                             0, 0, 0, 0,
      //   //                             HWND_MESSAGE, 0,
      //   //                             m_appInstance,
      //   //                             0);

      m_pparticleThis->postMainThreadMessage(iMainThreadMessage);
   }



   // void OperatingSystemApplication::registerWindowClass(WNDCLASS *wndClass)
   // {
   //   memset(wndClass, 0, sizeof(WNDCLASS));
   //
   //   // Set default values. Derived classes can redefine this fields
   //   wndClass->lpfnWndProc = wndProc;
   //   wndClass->hInstance = m_appInstance;
   //   wndClass->lpszClassName = m_wstrWindowClassName;
   //
   //   RegisterClass(wndClass);
   // }

   void OperatingSystemApplication::shutdown()
   {
      //PostMessage(m_mainWindow, WM_CLOSE, 0, 0);
      m_pparticleThis->shutdown();
   }

   void OperatingSystemApplication::postMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam)
   {
      //PostMessage(m_mainWindow, scopedstrMessage, wParam, lParam);
      m_pparticleThis->postMessage(uMessage, wparam, lparam);
   }

   void OperatingSystemApplication::addModelessDialog(const ::operating_system::window & operatingsystemwindow)
   {
      //AutoLock l(&m_MDLMutex);

      //m_modelessDialogList.add(dialogWindow);
      m_pparticleThis->addModelessDialog(operatingsystemwindow);
   }

   void OperatingSystemApplication::removeModelessDialog(const ::operating_system::window & operatingsystemwindow)
   {
      //AutoLock l(&m_MDLMutex);

      //m_modelessDialogList.erase(dialogWindow);

      m_pparticleThis->removeModelessDialog(operatingsystemwindow);
   }

   // bool OperatingSystemApplication::processDialogMessage(MSG *msg)
   // {
   //   // AutoLock l(&m_MDLMutex);
   //   // for (::list_base<HWND>::iterator iter = m_modelessDialogList.begin();
   //   //      iter != m_modelessDialogList.end(); iter++) {
   //   //   if (IsDialogMessage(*iter, msg)) {
   //   //     return true;
   //   //   }
   //   // }
   //   return m_pparticleThis->pro;
   // }

   // LRESULT CALLBACK OperatingSystemApplication::wndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
   // {
   //   switch (msg) {
   //   case WM_CLOSE:
   //     DestroyWindow(hWnd);
   //     return 0;
   //   case WM_DESTROY:
   //     PostQuitMessage(0);
   //     return 0;
   //   }
   //   return DefWindowProc(hWnd, msg, wparam, lparam);
   // }

    int OperatingSystemApplication::getExitCode()
   {

      return m_pparticleThis->getExitCode();

   }


   void OperatingSystemApplication::onMainThreadMessage(int iMainThreadMessage)
   {


   }
} // namespace subsystem

