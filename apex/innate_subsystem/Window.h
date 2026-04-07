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
//#ifndef _BASE_WINDOW_H_
//#define _BASE_WINDOW_H_

//#include "util/CommonHeader.h"

#define WINDOW_WIDTH_USE_DEFAULT       ((int)0x80000000)
#include "acme/prototype/geometry2d/rectangle.h"

namespace innate_subsystem
{

   class CLASS_DECL_APEX Window :
      virtual public ::subsystem::particle<Window>
   {
   public:


      Window();
      virtual ~Window();

      // getWindow()
      // Get a handle of the window
      virtual ::operating_system::window get_operating_system_window() const;
      virtual void setHWnd(const ::operating_system::window & operatingsystemwindow);

      // createWindow()
      // Create window with windowName and setted style
      // other parameters can by changed
      virtual bool createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent = 0,
                        int xPos = WINDOW_WIDTH_USE_DEFAULT, int yPos = WINDOW_WIDTH_USE_DEFAULT,
                        int width = WINDOW_WIDTH_USE_DEFAULT, int height = WINDOW_WIDTH_USE_DEFAULT);
      virtual bool destroyWindow();

      // setClass()
      // Set a class name only to the new window created by createWindow
      virtual void setClass(const ::scoped_string  & scopedstrWindowClassName);

      // basic window manipulation procedures
      virtual void show();
      virtual void hide();
      virtual void enableWindow(bool bEnable);
      virtual void updateWindow();
      virtual bool setSize(int width, int height);
      virtual bool setPosition(int xPos, int yPos);
      virtual void setWindowText(const ::scoped_string  & scopedstrText);

      // loadIcon()
      // Set the icon of application where id can be from resource or handle HICON
      virtual void loadIcon(unsigned int id);

      // setParent()
      // Making child window by changing parent of the window
      virtual void setParent(const ::operating_system::window & operatingsystemwindow);

      // for changing registered class parameters of created window
      virtual void setClassStyle(unsigned int style);
      virtual void setClassCursor(::innate_subsystem::Cursor * pcursor);
      virtual void setClassBackground(::innate_subsystem::Brush * pbrush);
      virtual void setClassMenu(long long menu);

      // for changing or get style and exstyle of window
      virtual long long getStyle();
      virtual void setStyle(unsigned int style);
      virtual void addStyle(unsigned int styleFlag);
      virtual void removeStyle(unsigned int styleFlag);
      virtual bool isStyleEnabled(unsigned int styleFlags);


      virtual long long getExStyle();
      virtual void setExStyle(unsigned int exstyle);
      virtual void addExStyle(unsigned int styleFlag);
      virtual void removeExStyle(unsigned int styleFlag);
      virtual bool isExStyleEnabled(unsigned int styleFlag);



      // full redraw of window area
      virtual void redraw(const ::int_rectangle &rcArea = {});

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      virtual void setTimer(::uptr ident, unsigned int time);
      virtual void killTimer(::uptr ident);

      // set foreground window
      virtual void setForegroundWindow();

      // post message to this window
      virtual void postMessage(unsigned int Msg, ::wparam wparam = 0, ::lparam lparam = 0);

      virtual void getClientRect(::int_rectangle &rc);
      virtual void getBorderSize(int *width, int *height);

      virtual bool wndProc(unsigned int message, ::wparam wparam, ::lparam lparam);

      static const int MOUSE_LDOWN  = 1;
      static const int MOUSE_MDOWN  = 2;
      static const int MOUSE_RDOWN  = 4;
      static const int MOUSE_WUP    = 8;
      static const int MOUSE_WDOWN  = 16;

   // private:
   //    // This function may be implement in child class.
   //    // Here is stub function, always returned false.
   //    virtual bool onCommand(::wparam wparam, ::lparam lparam);
   //    virtual bool onNotify(int idCtrl, LPNMHDR pnmh);
   //    virtual bool onSysCommand(::wparam wparam, ::lparam lparam);
   //    virtual bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam);
   //    virtual bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, POINT position);

   // protected:
   //    HWND m_hWnd;
   //    StringStorage m_className;
   //    StringStorage m_windowName;
   //    HICON m_hicon;
   //
   //    bool m_bWndCreated;
   };


   //    class CLASS_DECL_APEX Window :
   // virtual public ::subsystem::Window
   // {
   // public:
   //    Window();
   //
   //     ~Window() override;
   //
   //    // getWindow()
   //    // Get a handle of the window
   //    ::operating_system::window get_operating_system_window() const override;
   //    void setHWnd(const ::operating_system::window & operatingsystemwindow) override;
   //
   //    // createWindow()
   //    // Create window with windowName and setted style
   //    // other parameters can by changed
   //    bool createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent = {},
   //                      int xPos = WINDOW_WIDTH_USE_DEFAULT, int yPos = WINDOW_WIDTH_USE_DEFAULT,
   //                      int width = WINDOW_WIDTH_USE_DEFAULT, int height = WINDOW_WIDTH_USE_DEFAULT) override;
   //    bool destroyWindow() override;
   //
   //    // setClass()
   //    // Set a class name only to the new window created by createWindow
   //    void setClass(const ::scoped_string  & scopedstrWindowClassName) override;
   //
   //    // basic window manipulation procedures
   //    void show() override;
   //    void hide() override;
   //    void enableWindow(bool bEnable) override;
   //    void updateWindow() override;
   //    bool setSize(int width, int height) override;
   //    bool setPosition(int xPos, int yPos) override;
   //    void setWindowText(const ::scoped_string  & scopedstrText) override;
   //
   //    // loadIcon()
   //    // Set the icon of application where id can be from resource or handle HICON
   //    void loadIcon(unsigned int id) override;
   //
   //    // setParent()
   //    // Making child window by changing parent of the window
   //    void setParent(const ::operating_system::window & operatingsystemwindow) override;
   //
   //    // for changing registered class parameters of created window
   //    void setClassStyle(unsigned int style) override;
   //    void setClassCursor(::innate_subsystem::Cursor * pcursor) override;
   //    void setClassBackground(::innate_subsystem::Brush * pbrush) override;
   //    void setClassMenu(long long menu) override;
   //
   //    // for changing or get style and exstyle of window
   //    long long getStyle() override;
   //    void setStyle(unsigned int style) override;
   //    void addStyle(unsigned int styleFlag) override;
   //    void removeStyle(unsigned int styleFlag) override;
   //    bool isStyleEnabled(unsigned int styleFlags) override;
   //
   //
   //    long long getExStyle() override;
   //    void setExStyle(unsigned int exstyle) override;
   //    void addExStyle(unsigned int styleFlag) override;
   //    void removeExStyle(unsigned int styleFlag) override;
   //    bool isExStyleEnabled(unsigned int styleFlag) override;
   //
   //    // full redraw of window area
   //    void redraw(const ::int_rectangle &rcArea ={}) override;
   //
   //    // set or kill timer, with identifactor ident
   //    // and time in milliseconds
   //    void setTimer(::uptr ident, unsigned int time) override;
   //    void killTimer(::uptr ident) override;
   //
   //    // set foreground window
   //    void setForegroundWindow() override;
   //
   //    // post message to this window
   //    void postMessage(unsigned int Msg, ::wparam wparam =0, ::lparam lparam =0) override;
   //
   //    void getClientRect(::int_rectangle &rc) override;
   //    void getBorderSize(int *width, int *height) override;
   //
   //    bool wndProc(unsigned int message, ::wparam wparam, ::lparam lparam) override;
   //
   //    static const int MOUSE_LDOWN  = 1;
   //    static const int MOUSE_MDOWN  = 2;
   //    static const int MOUSE_RDOWN  = 4;
   //    static const int MOUSE_WUP    = 8;
   //    static const int MOUSE_WDOWN  = 16;
   //
   // // private:
   // //    // This function may be implement in child class.
   // //    // Here is stub function, always returned false.
   // //    bool onCommand(::wparam wparam, ::lparam lparam);
   // //    bool onNotify(int idCtrl, LPNMHDR pnmh);
   // //    bool onSysCommand(::wparam wparam, ::lparam lparam);
   // //    bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam);
   // //    bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, POINT position);
   //
   // // protected:
   // //    HWND m_hWnd;
   // //    StringStorage m_className;
   // //    StringStorage m_windowName;
   // //    HICON m_hicon;
   // //
   // //    bool m_bWndCreated;
   // };

} // namespace innate_subsystem