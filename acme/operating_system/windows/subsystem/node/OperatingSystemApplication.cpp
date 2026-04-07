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
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "OperatingSystemApplication.h"

#include "acme/operating_system/windows/subsystem/_common_header.h"
//#include "remoting/remoting_common/thread/critical_section_lock.h"

namespace windows
{
   namespace subsystem
   {
      critical_section OperatingSystemApplication::m_MDLMutex;

      ::comparable_list_base<HWND> OperatingSystemApplication::m_modelessDialogList;

      OperatingSystemApplication::OperatingSystemApplication()
      :
        m_mainWindow(0)

      {
      }

      OperatingSystemApplication::~OperatingSystemApplication()
      {
      }

      void OperatingSystemApplication::initialize_operating_system_application(const ::scoped_string & scopedstrWindowClassName)
      {
         //::particle::initialize(pparticle);

         m_appInstance =(HINSTANCE)system()->m_hinstanceThis;


//           m_wstrWindowClassName(scopedstrwindowClassName)
  //          HINSTANCE appInstance,
    //                                         const ::scoped_string & scopedstrwindowClassName
      }
      void OperatingSystemApplication::run()
      {
         WNDCLASS wndClass;
         registerWindowClass(&wndClass);
         createWindow(wndClass.lpszClassName);
         try {
            m_iExitCode = processMessages();
         } catch (...) {
            m_iExitCode = 1;
         }
      }

      int OperatingSystemApplication::processMessages()
      {
         MSG msg;
         BOOL ret;
         while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0) {
            if (ret < 0) {
               return 1;
            }
            if (!processDialogMessage(&msg)) {
               TranslateMessage(&msg);
               DispatchMessage(&msg);
            }
         }

         return (int)msg.wParam;
      }

      void OperatingSystemApplication::createWindow(const ::scoped_string & scopedstrClassName)
      {
         m_mainWindow = CreateWindow(::wstring(scopedstrClassName),
                                     0, 0,
                                     0, 0, 0, 0,
                                     HWND_MESSAGE, 0,
                                     m_appInstance,
                                     0);
      }

      void OperatingSystemApplication::registerWindowClass(WNDCLASS *wndClass)
      {
         memset(wndClass, 0, sizeof(WNDCLASS));

         // Set default values. Derived classes can redefine this fields
         wndClass->lpfnWndProc = wndProc;
         wndClass->hInstance = m_appInstance;
         wndClass->lpszClassName = m_wstrWindowClassName;

         RegisterClass(wndClass);
      }

      void OperatingSystemApplication::shutdown()
      {
         PostMessage(m_mainWindow, WM_CLOSE, 0, 0);
      }

      void OperatingSystemApplication::postMessage(UINT scopedstrMessage, WPARAM wParam, LPARAM lParam)
      {
         PostMessage(m_mainWindow, scopedstrMessage, wParam, lParam);
      }

      void OperatingSystemApplication::addModelessDialog(HWND dialogWindow)
      {
         critical_section_lock l(&m_MDLMutex);

         m_modelessDialogList.add(dialogWindow);
      }

      void OperatingSystemApplication::removeModelessDialog(HWND dialogWindow)
      {
         critical_section_lock l(&m_MDLMutex);

         m_modelessDialogList.erase(dialogWindow);
      }

      bool OperatingSystemApplication::processDialogMessage(MSG *msg)
      {
         critical_section_lock l(&m_MDLMutex);
         for (::list_base<HWND>::iterator iter = m_modelessDialogList.begin();
              iter != m_modelessDialogList.end(); iter++) {
            if (IsDialogMessage(*iter, msg)) {
               return true;
            }
              }
         return false;
      }

      LRESULT CALLBACK OperatingSystemApplication::wndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
      {
         switch (msg) {
            case WM_CLOSE:
               DestroyWindow(hWnd);
               return 0;
            case WM_DESTROY:
               PostQuitMessage(0);
               return 0;
         }
         return DefWindowProc(hWnd, msg, wparam, lparam);
      }
   } // namespace subsystem
} //namespace windows

