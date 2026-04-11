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
//#include "util/CommonHeader.h"
#include "Window.h"

//#include "acme/operating_system/windows/_.h"


namespace innate_subsystem
{
   Window::Window()
   // : m_hWnd(0),
   //   m_hicon(0),
   //   m_bWndCreated(false)
   {
   }

   Window::~Window()
   {
      // if (m_bWndCreated && m_hWnd) {
      //    DestroyWindow(m_hWnd);
      // }
      // if (m_hicon) {
      //    DeleteObject(m_hicon);
      // }
   }


   void Window::setClipboardViewerInterest()
   {

      m_pparticleThis->setClipboardViewerInterest();

   }


   bool Window::onDrawClipboard()
   {

      return false;

   }


   void Window::setClass(const ::scoped_string & scopedstrClassName)
   {
      m_pparticleThis->setClass(scopedstrClassName);
      //m_className = *className;
   }


   WindowInterface *Window::get_window_implementation()
   {

      return m_pparticleThis->get_window_implementation();

   }


   bool Window::createWindow(const scoped_string & scopedstrWindowName, unsigned int style,
                             const ::operating_system::window & operatingsystemwindowParent,
                             int xPos, int yPos, int width, int height)
   {

           return m_pparticleThis->createWindow(scopedstrWindowName,style, operatingsystemwindowParent, xPos, yPos, width, height);
      // if (m_hWnd) {
      //    return false;
      // }
      // m_windowName = *windowName;
      // m_hWnd = CreateWindow(m_className.getString(),
      //                       m_windowName.getString(),
      //                       style,
      //                       xPos, yPos,
      //                       width, height,
      //                       hWndParent,
      //                       0,
      //                       GetModuleHandle(0),
      //                       reinterpret_cast<LPVOID>(this));
      // m_bWndCreated = (m_hWnd == 0 ? false : true);
      // if (m_bWndCreated) {
      //    SetWindowLongPtr(m_hWnd,
      //                     GWLP_USERDATA,
      //                     reinterpret_cast<LONG_PTR>(this));
      // }
      // return true;
   }

   void Window::loadIcon(unsigned int id)
   {

      m_pparticleThis ->loadIcon(id);
      // if (m_hicon) {
      //    DeleteObject(m_hicon);
      //    m_hicon = 0;
      // }
      // if (IS_INTRESOURCE(id)) {
      //    m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
      //    SetClassLongPtr(m_hWnd, GCLP_HICON, reinterpret_cast<LONG_PTR>(m_hicon));
      // } else {
      //    SetClassLongPtr(m_hWnd, GCLP_HICON, static_cast<LONG_PTR>(id));
      // }
   }

   void Window::enableWindow(bool bEnable)
   {
      m_pparticleThis ->enableWindow(bEnable);
      // _ASSERT(m_hWnd != 0);
      // EnableWindow(m_hWnd, bEnable);
   }

   void Window::setEnabled(bool bEnable)
   {
      m_pparticleThis ->setEnabled(bEnable);
   }

   bool Window::destroyWindow()
   {
      return m_pparticleThis->destroyWindow();
      // if (m_hWnd) {
      //    DestroyWindow(m_hWnd);
      //    return true;
      // }
      //return false;
   }


   void Window::setShowCursor(bool bShowCursor)
   {

      m_pparticleThis->setShowCursor(bShowCursor);

   }


   bool Window::shouldShowCursor()
   {

      return m_pparticleThis->shouldShowCursor();

   }


   void Window::setDoubleBuffering(bool bDoubleBuffering)
   {

      m_pparticleThis->setDoubleBuffering(bDoubleBuffering);

   }


   bool Window::isDoubleBuffering()
   {

      return m_pparticleThis->isDoubleBuffering();

   }

   void Window::show()
   {
      m_pparticleThis->show();
      // _ASSERT(m_hWnd != 0);
      // ShowWindow(m_hWnd, SW_SHOW);
   }

   void Window::hide()
   {
      //_ASSERT(m_hWnd != 0);
      //ShowWindow(m_hWnd, SW_HIDE);
      m_pparticleThis->hide();
   }

   bool Window::setSize(const ::int_size & size)
   {
      // _ASSERT(m_hWnd != 0);
      // return !!SetWindowPos(m_hWnd, 0, 0, 0, width, height,
      //                       SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
      return m_pparticleThis->setSize(size);
   }

   bool Window::setPosition(int xPos, int yPos)
   {
      // _ASSERT(m_hWnd != 0);
      // return !!SetWindowPos(m_hWnd, 0, xPos, yPos, 0, 0,
      //                       SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
      return m_pparticleThis->setPosition(xPos, yPos);
   }

   void Window::setParent(const ::operating_system::window & operatingsystemwindow)
   {
      // _ASSERT(m_hWnd != 0);
      // SetParent(m_hWnd, hwnd);

      m_pparticleThis->setParent(operatingsystemwindow);
   }


   ::operating_system::window Window::dialog_item_operating_system_window(int iDlgItem)
   {

      return m_pparticleThis->dialog_item_operating_system_window(iDlgItem);
      // auto hwndDlgItem = ::GetDlgItem(m_hWnd, iDlgItem);
      //
      // auto operatingsystemwindow = as_operating_system_window(hwndDlgItem);
      //
      // return operatingsystemwindow;

   }

   void Window::setClassStyle(unsigned int style)
   {
      // _ASSERT(m_hWnd != 0);
      // SetClassLong(m_hWnd, GCL_STYLE, style);
      m_pparticleThis->setClassStyle(style);
   }

   // void Window::setClassCursor(HCURSOR hcursor)
   // {
   //    // _ASSERT(m_hWnd != 0);
   //    // SetClassLongPtr(m_hWnd, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(hcursor));
   //
   //    m_pparticleThis->setClassCursor(hcursor);
   // }
   //
   // void Window::setClassBackground(HBRUSH hbrush)
   // {
   //    //_ASSERT(m_hWnd != 0);
   //    //SetClassLongPtr(m_hWnd, GCLP_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(hbrush));
   //    m_pparticleThis->setClassCursor(hcursor);
   // }

   // void Window::setClassMenu(long long menu)
   // {
   //    // _ASSERT(m_hWnd != 0);
   //    // SetClassLongPtr(m_hWnd, GCLP_MENUNAME, menu);
   // }


   bool Window::we_want_WM_KEYDOWN_when_enter_is_pressed() const
   {

      return m_pparticleThis->we_want_WM_KEYDOWN_when_enter_is_pressed();

   }

   long long Window::getStyle()
   {
      // _ASSERT(m_hWnd != 0);
      // return GetWindowLong(m_hWnd, GWL_STYLE);
      return m_pparticleThis->getStyle();
   }

   void Window::setStyle(unsigned int style)
   {
      //_ASSERT(m_hWnd != 0);
      //SetWindowLong(m_hWnd, GWL_STYLE, style);
      m_pparticleThis->setStyle(style);
   }

   long long Window::getExStyle()
   {
      //_ASSERT(m_hWnd != 0);
      //return GetWindowLong(m_hWnd, GWL_EXSTYLE);
      return m_pparticleThis->getExStyle();
   }

   void Window::setExStyle(unsigned int exstyle)
   {
      //_ASSERT(m_hWnd != 0);
      //SetWindowLong(m_hWnd, GWL_EXSTYLE, exstyle);
      m_pparticleThis->setExStyle(exstyle);
   }

   void Window::updateWindow()
   {
      //_ASSERT(m_hWnd != 0);
      //UpdateWindow(m_hWnd);
      m_pparticleThis->updateWindow();
   }

   void Window::setTimer(::uptr u, unsigned int time)
   {
      //_ASSERT(m_hWnd != 0);
      //SetTimer(m_hWnd, ident, time, 0);

      m_pparticleThis->setTimer(u, time);
   }

   void Window::killTimer(::uptr u)
   {
      // _ASSERT(m_hWnd != 0);
      // KillTimer(m_hWnd, ident);

      m_pparticleThis->killTimer(u);
   }

   bool Window::onCommand(::wparam wparam, ::lparam lparam)
   {
      return m_pparticleThis->onCommand(wparam, lparam);
   }

   // bool Window::onNotify(int idCtrl, LPNMHDR pnmh)
   // {
   //    return false;
   // }

   bool Window::onSysCommand(::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   bool Window::onMessage(unsigned int message, ::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   // bool Window::wndProc(unsigned int message, ::wparam wparam, ::lparam lparam)
   // {
   //    switch (message) {
   //       case WM_COMMAND:
   //          return onCommand(::wparam, ::lparam);
   //       case WM_NOTIFY:
   //          return onNotify((int)::wparam, (LPNMHDR)::lparam);
   //       case WM_SYSCOMMAND:
   //          return onSysCommand(::wparam, ::lparam);
   //       case WM_LBUTTONDOWN:
   //       case WM_LBUTTONUP:
   //       case WM_MBUTTONDOWN:
   //       case WM_MBUTTONUP:
   //       case WM_RBUTTONDOWN:
   //       case WM_RBUTTONUP:
   //       case WM_MOUSEWHEEL:
   //       case WM_MOUSEMOVE:
   //       {
   //          unsigned char mouseButtons = 0;
   //
   //          mouseButtons |= LOWORD(::wparam) & MK_RBUTTON ? MOUSE_RDOWN : 0;
   //          mouseButtons |= LOWORD(::wparam) & MK_MBUTTON ? MOUSE_MDOWN : 0;
   //          mouseButtons |= LOWORD(::wparam) & MK_LBUTTON ? MOUSE_LDOWN : 0;
   //
   //          // Translate position from ::lparam to POINT.
   //          POINTS points = MAKEPOINTS(::lparam);
   //          POINT point;
   //          point.x = points.x;
   //          point.y = points.y;
   //
   //          unsigned short wheelSpeed = 0;
   //          if (message == WM_MOUSEWHEEL) {
   //             // Get speed wheel and set mouse button.
   //             signed short wheelSignedSpeed = static_cast<signed short>(HIWORD(::wparam));
   //             if (wheelSignedSpeed < 0) {
   //                mouseButtons |= MOUSE_WDOWN;
   //                wheelSpeed = - wheelSignedSpeed / WHEEL_DELTA;
   //             } else {
   //                mouseButtons |= MOUSE_WUP;
   //                wheelSpeed = wheelSignedSpeed / WHEEL_DELTA;
   //             }
   //
   //             // In some cases wheelSignedSpeed can be smaller than the WHEEL_DELTA,
   //             // then wheelSpeed set to 1, but not 0.
   //             if (wheelSpeed == 0) {
   //                wheelSpeed = 1;
   //             }
   //
   //             // If windows-message is WHEEL, then need to translate screen coordinate to client.
   //             if (!ScreenToClient(getHWnd(), &point)) {
   //                point.x = -1;
   //                point.y = -1;
   //             }
   //          }
   //
   //          // Notify window about mouse-event.
   //          return onMouse(mouseButtons, static_cast<unsigned short>(wheelSpeed), point);
   //       }
   //    }
   //    return onMessage(message, ::wparam, ::lparam);
   // }


   void *Window::_HWND() const
   {

      return m_pparticleThis->_HWND();

   }


   void Window::_setHWND(void *p)
   {

      m_pparticleThis->_setHWND(p);

   }


   void * Window::_WNDPROC_default() const
   {

      return m_pparticleThis->_WNDPROC_default();

   }


   ::operating_system::window Window::operating_system_window() const
   {
      return m_pparticleThis->operating_system_window();
   }



   void Window::set_operating_system_window(const ::operating_system::window & operatingsystemwindow)
   {
      //m_hWnd = hwnd;
      m_pparticleThis->set_operating_system_window(operatingsystemwindow);
   }

   void Window::setWindowText(const ::scoped_string & scopedstr)
   {
      // _ASSERT(m_hWnd != 0);
      // SetWindowText(m_hWnd, text->getString());
      m_pparticleThis->setWindowText(scopedstr);
   }

   void Window::setFocus()
   {
      //::SetFocus(m_hwnd);
      m_pparticleThis->setFocus();
   }

   bool Window::hasFocus()
   {
      ///return (::GetFocus() == m_hwnd) || (GetForegroundWindow() == m_hwnd);
      return m_pparticleThis->hasFocus();
   }

   bool Window::setForeground()
   {
      //return SetForegroundWindow(getWindow()) != 0;

      return m_pparticleThis->setForeground();
   }

   // void Window::setVisible(bool visible)
   // {
   //    //ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
   //    m_pparticleThis->setVisible(visible);
   // }

   bool Window::isEnabled()
   {
      ///return (!isStyleEnabled(WS_DISABLED));
      return m_pparticleThis->isEnabled();
   }

   bool Window::isIconic()
   {
      ///return (!isStyleEnabled(WS_DISABLED));
      return m_pparticleThis->isEnabled();
   }

   void Window::invalidate()
   {
      //InvalidateRect(m_hwnd, NULL, TRUE);
      m_pparticleThis->invalidate();
   }

   void Window::redraw(const ::int_rectangle &rcArea)
   {
      m_pparticleThis->redraw(rcArea);
      // _ASSERT(m_hWnd != 0);
      //
      // if (rcArea == 0) {
      //    InvalidateRect(m_hWnd, NULL, TRUE);
      // } else {
      //    InvalidateRect(m_hWnd, rcArea, FALSE);
      // }
   }

   bool Window::onMouse(unsigned char msg, unsigned short wspeed, const ::int_point & point)
   {

      m_pparticleThis->onMouse(msg, wspeed, point);
      return false;
   }

   void Window::setForegroundWindow()
   {
      // _ASSERT(m_hWnd != 0);
      //
      // SetForegroundWindow(m_hWnd);
      m_pparticleThis->setForegroundWindow();
   }

   void Window::postMessage(unsigned int Msg, ::wparam wparam, ::lparam lparam)
   {
      // _ASSERT(m_hWnd != 0);
      //
      // PostMessage(m_hWnd, Msg, ::wparam, ::lparam);
      m_pparticleThis->postMessage(Msg, wparam, lparam);
   }

   void Window::getClientRect(::int_rectangle &rc)
   {
      // _ASSERT(m_hWnd != 0 && rc);
      //
      // GetClientRect(m_hWnd, rc);
      m_pparticleThis->getClientRect(rc);
   }

   ::int_size Window::getBorderSize()
   {
      // _ASSERT(m_hWnd != 0);
      //
      // *width = 2 * GetSystemMetrics(SM_CXSIZEFRAME);
      // *height = GetSystemMetrics(SM_CYSIZE) +
      //           2 * GetSystemMetrics(SM_CYSIZEFRAME);

      return m_pparticleThis->getBorderSize();
   }


   bool Window::onCreate(void * pCreateStruct)
   {

      return false;

   }


   bool Window::on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {

      return false;

   }


   void Window::onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::int_rectangle & rectangle)
   {


   }
   

} // namespace innate_subsystem


