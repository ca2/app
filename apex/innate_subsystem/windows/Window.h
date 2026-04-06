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

#pragma once


//#include "util/CommonHeader.h"


namespace  windows
{
   namespace innate_subsystem
   {

      class Window
      {
      public:
         Window();

         virtual ~Window();

         // getWindow()
         // Get a handle of the window
         ::operating_system::window get_operating_system_window() const;
         void setHWnd(const ::operating_system::window & operatingsystemwindow);

         // createWindow()
         // Create window with windowName and setted style
         // other parameters can by changed
         bool createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent = 0,
                           int xPos = WINDOW_WIDTH_USE_DEFAULT, int yPos = WINDOW_WIDTH_USE_DEFAULT,
                           int width = WINDOW_WIDTH_USE_DEFAULT, int height = WINDOW_WIDTH_USE_DEFAULT);
         bool destroyWindow();

         // setClass()
         // Set a class name only to the new window created by createWindow
         void setClass(const ::scoped_string  & scopedstrWindowClassName);

         // basic window manipulation procedures
         void show();
         void hide();
         void enableWindow(bool bEnable);
         void updateWindow();
         bool setSize(int width, int height);
         bool setPosition(int xPos, int yPos);
         void setWindowText(const ::scoped_string  & scopedstrText);

         // loadIcon()
         // Set the icon of application where id can be from resource or handle HICON
         void loadIcon(unsigned int id);

         // setParent()
         // Making child window by changing parent of the window
         void setParent(const ::operating_system::window & operatingsystemwindow);

         // for changing registered class parameters of created window
         void setClassStyle(unsigned int style);
         void setClassCursor(::innate_subsystem::Cursor * pcursor);
         void setClassBackground(::innate_subsystem::Brush * pbrush);
         void setClassMenu(long long menu);

         // for changing or get style and exstyle of window
         long long getStyle();
         void setStyle(unsigned int style);
         long long getExStyle();
         void setExStyle(unsigned int exstyle);

         // full redraw of window area
         void redraw(const ::int_rectangle &rcArea = 0);

         // set or kill timer, with identifactor ident
         // and time in milliseconds
         void setTimer(::uptr ident, unsigned int time);
         void killTimer(::uptr ident);

         // set foreground window
         void setForegroundWindow();

         // post message to this window
         void postMessage(unsigned int Msg, ::wparam wparam = 0, ::lparam lparam = 0);

         void getClientRect(::int_rectangle &rc);
         void getBorderSize(int *width, int *height);

         virtual bool wndProc(unsigned int message, ::wparam wparam, ::lparam lparam);

         static const int MOUSE_LDOWN  = 1;
         static const int MOUSE_MDOWN  = 2;
         static const int MOUSE_RDOWN  = 4;
         static const int MOUSE_WUP    = 8;
         static const int MOUSE_WDOWN  = 16;

         // private:
         // This function may be implement in child class.
         // Here is stub function, always returned false.
         virtual bool onCommand(::wparam wparam, ::lparam lparam);
         virtual bool onNotify(int idCtrl, LPNMHDR pnmh);
         virtual bool onSysCommand(::wparam wparam, ::lparam lparam);
         virtual bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam);
         virtual bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, POINT position);

      protected:
         HWND m_hWnd;
         StringStorage m_className;
         StringStorage m_windowName;
         HICON m_hicon;

         bool m_bWndCreated;
      };

      //#endif
   } //  namespace innate_subsystem
} // namespace  windows

