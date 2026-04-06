// Copyright (C) 2011,2012 GlavSoft LLC.
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
#include "util/CommonHeader.h"
#include "Window.h"

namespace innate_subsystem
{
   Window::Window()
   : m_hWnd(0),
     m_hicon(0),
     m_bWndCreated(false)
   {
   }

   Window::~Window()
   {
      if (m_bWndCreated && m_hWnd) {
         DestroyWindow(m_hWnd);
      }
      if (m_hicon) {
         DeleteObject(m_hicon);
      }
   }

   void Window::setClass(const StringStorage *className)
   {
      m_className = *className;
   }

   bool Window::createWindow(const StringStorage *windowName, DWORD style, HWND hWndParent,
                                 int xPos, int yPos, int width, int height)
   {
      if (m_hWnd) {
         return false;
      }
      m_windowName = *windowName;
      m_hWnd = CreateWindow(m_className.getString(),
                            m_windowName.getString(),
                            style,
                            xPos, yPos,
                            width, height,
                            hWndParent,
                            0,
                            GetModuleHandle(0),
                            reinterpret_cast<LPVOID>(this));
      m_bWndCreated = (m_hWnd == 0 ? false : true);
      if (m_bWndCreated) {
         SetWindowLongPtr(m_hWnd,
                          GWLP_USERDATA,
                          reinterpret_cast<LONG_PTR>(this));
      }
      return true;
   }

   void Window::loadIcon(DWORD id)
   {
      if (m_hicon) {
         DeleteObject(m_hicon);
         m_hicon = 0;
      }
      if (IS_INTRESOURCE(id)) {
         m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
         SetClassLongPtr(m_hWnd, GCLP_HICON, reinterpret_cast<LONG_PTR>(m_hicon));
      } else {
         SetClassLongPtr(m_hWnd, GCLP_HICON, static_cast<LONG_PTR>(id));
      }
   }

   void Window::enableWindow(bool bEnable)
   {
      _ASSERT(m_hWnd != 0);
      EnableWindow(m_hWnd, bEnable);
   }

   bool Window::destroyWindow()
   {
      if (m_hWnd) {
         DestroyWindow(m_hWnd);
         return true;
      }
      return false;
   }

   void Window::show()
   {
      _ASSERT(m_hWnd != 0);
      ShowWindow(m_hWnd, SW_SHOW);
   }

   void Window::hide()
   {
      _ASSERT(m_hWnd != 0);
      ShowWindow(m_hWnd, SW_HIDE);
   }

   bool Window::setSize(int width, int height)
   {
      _ASSERT(m_hWnd != 0);
      return !!SetWindowPos(m_hWnd, 0, 0, 0, width, height,
                            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
   }

   bool Window::setPosition(int xPos, int yPos)
   {
      _ASSERT(m_hWnd != 0);
      return !!SetWindowPos(m_hWnd, 0, xPos, yPos, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
   }

   void Window::setParent(HWND hwnd)
   {
      _ASSERT(m_hWnd != 0);
      SetParent(m_hWnd, hwnd);
   }

   void Window::setClassStyle(DWORD style)
   {
      _ASSERT(m_hWnd != 0);
      SetClassLong(m_hWnd, GCL_STYLE, style);
   }

   void Window::setClassCursor(HCURSOR hcursor)
   {
      _ASSERT(m_hWnd != 0);
      SetClassLongPtr(m_hWnd, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(hcursor));
   }

   void Window::setClassBackground(HBRUSH hbrush)
   {
      _ASSERT(m_hWnd != 0);
      SetClassLongPtr(m_hWnd, GCLP_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(hbrush));
   }

   void Window::setClassMenu(LONG menu)
   {
      _ASSERT(m_hWnd != 0);
      SetClassLongPtr(m_hWnd, GCLP_MENUNAME, menu);
   }

   LONG Window::getStyle()
   {
      _ASSERT(m_hWnd != 0);
      return GetWindowLong(m_hWnd, GWL_STYLE);
   }

   void Window::setStyle(DWORD style)
   {
      _ASSERT(m_hWnd != 0);
      SetWindowLong(m_hWnd, GWL_STYLE, style);
   }

   LONG Window::getExStyle()
   {
      _ASSERT(m_hWnd != 0);
      return GetWindowLong(m_hWnd, GWL_EXSTYLE);
   }

   void Window::setExStyle(DWORD exstyle)
   {
      _ASSERT(m_hWnd != 0);
      SetWindowLong(m_hWnd, GWL_EXSTYLE, exstyle);
   }

   void Window::updateWindow()
   {
      _ASSERT(m_hWnd != 0);
      UpdateWindow(m_hWnd);
   }

   void Window::setTimer(unsigned int_PTR ident, unsigned int time)
   {
      _ASSERT(m_hWnd != 0);
      SetTimer(m_hWnd, ident, time, 0);
   }

   void Window::killTimer(unsigned int_PTR ident)
   {
      _ASSERT(m_hWnd != 0);
      KillTimer(m_hWnd, ident);
   }

   bool Window::onCommand(::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   bool Window::onNotify(int idCtrl, LPNMHDR pnmh)
   {
      return false;
   }

   bool Window::onSysCommand(::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   bool Window::onMessage(unsigned int message, ::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   bool Window::wndProc(unsigned int message, ::wparam wparam, ::lparam lparam)
   {
      switch (message) {
         case WM_COMMAND:
            return onCommand(::wparam, ::lparam);
         case WM_NOTIFY:
            return onNotify((int)::wparam, (LPNMHDR)::lparam);
         case WM_SYSCOMMAND:
            return onSysCommand(::wparam, ::lparam);
         case WM_LBUTTONDOWN:
         case WM_LBUTTONUP:
         case WM_MBUTTONDOWN:
         case WM_MBUTTONUP:
         case WM_RBUTTONDOWN:
         case WM_RBUTTONUP:
         case WM_MOUSEWHEEL:
         case WM_MOUSEMOVE:
         {
            unsigned char mouseButtons = 0;

            mouseButtons |= LOWORD(::wparam) & MK_RBUTTON ? MOUSE_RDOWN : 0;
            mouseButtons |= LOWORD(::wparam) & MK_MBUTTON ? MOUSE_MDOWN : 0;
            mouseButtons |= LOWORD(::wparam) & MK_LBUTTON ? MOUSE_LDOWN : 0;

            // Translate position from ::lparam to POINT.
            POINTS points = MAKEPOINTS(::lparam);
            POINT point;
            point.x = points.x;
            point.y = points.y;

            unsigned short wheelSpeed = 0;
            if (message == WM_MOUSEWHEEL) {
               // Get speed wheel and set mouse button.
               signed short wheelSignedSpeed = static_cast<signed short>(HIWORD(::wparam));
               if (wheelSignedSpeed < 0) {
                  mouseButtons |= MOUSE_WDOWN;
                  wheelSpeed = - wheelSignedSpeed / WHEEL_DELTA;
               } else {
                  mouseButtons |= MOUSE_WUP;
                  wheelSpeed = wheelSignedSpeed / WHEEL_DELTA;
               }

               // In some cases wheelSignedSpeed can be smaller than the WHEEL_DELTA,
               // then wheelSpeed set to 1, but not 0.
               if (wheelSpeed == 0) {
                  wheelSpeed = 1;
               }

               // If windows-message is WHEEL, then need to translate screen coordinate to client.
               if (!ScreenToClient(getHWnd(), &point)) {
                  point.x = -1;
                  point.y = -1;
               }
            }

            // Notify window about mouse-event.
            return onMouse(mouseButtons, static_cast<unsigned short>(wheelSpeed), point);
         }
      }
      return onMessage(message, ::wparam, ::lparam);
   }

   void Window::setHWnd(HWND hwnd)
   {
      m_hWnd = hwnd;
   }

   HWND Window::getHWnd() const
   {
      return m_hWnd;
   }

   void Window::setWindowText(const StringStorage *text)
   {
      _ASSERT(m_hWnd != 0);
      SetWindowText(m_hWnd, text->getString());
   }

   void Window::redraw(const ::int_rectangle &rcArea)
   {
      _ASSERT(m_hWnd != 0);

      if (rcArea == 0) {
         InvalidateRect(m_hWnd, NULL, TRUE);
      } else {
         InvalidateRect(m_hWnd, rcArea, FALSE);
      }
   }

   bool Window::onMouse(unsigned char msg, unsigned short wspeed, POINT pt)
   {
      return false;
   }

   void Window::setForegroundWindow()
   {
      _ASSERT(m_hWnd != 0);

      SetForegroundWindow(m_hWnd);
   }

   void Window::postMessage(unsigned int Msg, ::wparam wparam, ::lparam lparam)
   {
      _ASSERT(m_hWnd != 0);

      PostMessage(m_hWnd, Msg, ::wparam, ::lparam);
   }

   void Window::getClientRect(::int_rectangle &rc)
   {
      _ASSERT(m_hWnd != 0 && rc);

      GetClientRect(m_hWnd, rc);
   }

   void Window::getBorderSize(int *width, int *height)
   {
      _ASSERT(m_hWnd != 0);

      *width = 2 * GetSystemMetrics(SM_CXSIZEFRAME);
      *height = GetSystemMetrics(SM_CYSIZE) +
                2 * GetSystemMetrics(SM_CYSIZEFRAME);
   }
} // namespace innate_subsystem


