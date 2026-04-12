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

#include "innate_subsystem/_common_header.h"
#define WINDOW_WIDTH_USE_DEFAULT       ((int)0x80000000)
#include "acme/prototype/geometry2d/rectangle.h"
#include "subsystem/particle.h"


namespace innate_subsystem
{


   enum enum_mouse
   {

      e_mouse_left         = 1,
      e_mouse_middle       = 2,
      e_mouse_right        = 4,
      e_mouse_wheel_up     = 8,
      e_mouse_wheel_down   = 16,

   };


   class WindowInterface :
      virtual public ::subsystem::particle_interface<WindowInterface>,
      virtual public notification_handler
   {
   public:


      //Window();
      //virtual  ~WindowInterface() = 0;

      // getWindow()
      // Get a handle of the window
      virtual void * _HWND() const = 0;
      virtual void _setHWND(void *) = 0;
      virtual void * _WNDPROC_default() const = 0;
      virtual ::operating_system::window operating_system_window() const = 0;
      virtual void set_operating_system_window(const ::operating_system::window & operatingsystemwindow) = 0;


      virtual WindowInterface * get_window_implementation() = 0;

      // createWindow()
      // Create window with windowName and setted style
      // other parameters can by changed
      virtual bool createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent = 0,
                        int xPos = WINDOW_WIDTH_USE_DEFAULT, int yPos = WINDOW_WIDTH_USE_DEFAULT,
                        int width = WINDOW_WIDTH_USE_DEFAULT, int height = WINDOW_WIDTH_USE_DEFAULT) = 0;
      virtual bool destroyWindow() = 0;

      virtual void setClipboardViewerInterest() = 0;
      virtual bool onDrawClipboard() = 0;
      // setClass()
      // Set a class name only to the new window created by createWindow
      virtual void setClass(const ::scoped_string  & scopedstrWindowClassName) = 0;

      // We want WM_KEYDOWN scopedstrMessage when enter is pressed
      virtual bool we_want_WM_KEYDOWN_when_enter_is_pressed() const {return false;}


      virtual void setShowCursor(bool bShowCursor) = 0;
      virtual bool shouldShowCursor() = 0;

      virtual void setDoubleBuffering(bool bDoubleBuffering) = 0;
      virtual bool isDoubleBuffering() = 0;

      // basic window manipulation procedures
      virtual void show() = 0;
      virtual void hide() = 0;
      virtual void enableWindow(bool bEnable) = 0;
      virtual void setEnabled(bool bEnable) = 0;
      virtual void updateWindow() = 0;
      virtual bool setSize(const ::int_size & size) = 0;
      virtual bool setPosition(const ::int_point & point) = 0;
      virtual bool setPlacement(const ::int_rectangle & rectangle) = 0;
      virtual void setWindowText(const ::scoped_string  & scopedstrText) = 0;

      //
      // Sets input focus to this control
      //

      virtual void setFocus() = 0;

      //
      // Return true if window has input focus
      //

      virtual bool hasFocus() = 0;

      //
      // Puts this control foreground and activates it
      //

      virtual bool setForeground() = 0;

      // //
      // // Changes visible state of this control
      // //
      //
      // virtual void setVisible(bool visible) = 0;

      //
      // Checks if this control is active (not disabled)
      //

      virtual bool isEnabled() = 0;


      virtual bool isWindow() = 0;


      virtual bool isVisible() = 0;


      virtual bool isIconic() = 0;


      virtual bool isMinimized() = 0;


      virtual bool isFullScreen() = 0;

      //
      // Invalidates control
      //

      virtual void invalidate() = 0;

      //
      // Gets text associated with window
      //

      virtual ::string getText() = 0;


      // loadIcon()
      // Set the icon of application where id can be from resource or handle HICON
      virtual void loadIcon(unsigned int id) = 0;

      // setParent()
      // Making child window by changing parent of the window
      virtual void setParent(const ::operating_system::window & operatingsystemwindow) = 0;


      virtual ::operating_system::window dialog_item_operating_system_window(int iDlgItem) = 0;


      // for changing registered class parameters of created window
      virtual void setClassStyle(unsigned int style) = 0;
      virtual void setClassCursor(::innate_subsystem::CursorInterface * pcursor) = 0;
      virtual void setClassBackground(::innate_subsystem::BrushInterface * pbrush) = 0;
      virtual void setClassMenu(::innate_subsystem::MenuInterface * pmenu) = 0;

      // for changing or get style and exstyle of window
      virtual long long getStyle() = 0;
      virtual void setStyle(unsigned int style) = 0;
      virtual void addStyle(unsigned int styleFlag) = 0;
      virtual void removeStyle(unsigned int styleFlag) = 0;
      virtual bool isStyleEnabled(unsigned int styleFlags) = 0;


      virtual long long getExStyle() = 0;
      virtual void setExStyle(unsigned int exstyle) = 0;
      virtual void addExStyle(unsigned int styleFlag) = 0;
      virtual void removeExStyle(unsigned int styleFlag) = 0;
      virtual bool isExStyleEnabled(unsigned int styleFlag) = 0;



      // full redraw of window area
      virtual void redraw(const ::int_rectangle &rcArea = {}) = 0;

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      virtual void setTimer(::uptr ident, unsigned int time) = 0;
      virtual void killTimer(::uptr ident) = 0;

      // set foreground window
      virtual void setForegroundWindow() = 0;

      // post message to this window
      virtual void postMessage(unsigned int Msg, ::wparam wparam = 0, ::lparam lparam = 0) = 0;

      virtual ::int_rectangle getClientRect() = 0;
      virtual ::int_rectangle getFullScreenRect() = 0;
      virtual ::int_size getBorderSize() = 0;
      virtual ::int_rectangle getScreenWorkArea() = 0;


      //virtual void setSizeFullScreenWindow() = 0;
      //virtual void doRestoreFromFullScreen() = 0;
      virtual void minimizeWindow() = 0;
      virtual void restoreWindow() = 0;


      virtual void doFullScreen() = 0;
      virtual void doUnFullScreen() = 0;

      virtual void adjustWindowSize() = 0;


   // private:
   //    // This function may be implement in child class.
   //    // Here is stub function, always returned false.
   virtual bool onCommand(::wparam wparam, ::lparam lparam) = 0;
   //virtual bool onNotify(int idCtrl, LPNMHDR pnmh) = 0;
   virtual bool onSysCommand(::wparam wparam, ::lparam lparam) = 0;
   virtual bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam) = 0;
   virtual bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, const ::int_point & position) = 0;


   virtual bool onCreate(void * pCreateStruct) = 0;

   virtual bool on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam) = 0;

      virtual void onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::int_rectangle & rectangle) = 0;

      virtual void onBeforeFullScreen(bool bRestore) = 0;
      virtual void onAfterFullScreen(bool bRestore) = 0;
      virtual void onBeforeUnFullScreen(bool bMinimizing) = 0;
      virtual void onAfterUnFullScreen(bool bMinimizing) = 0;
      virtual bool onGetTooltip(int iControl, ::string & strTooltip) = 0;
      virtual bool onCalculateDefaultSize(::int_rectangle & rectangleDefaultSize) = 0;
      virtual void onAdjustWindowSize() = 0;
   // protected:
   //    HWND m_hWnd;
   //    ::string m_className;
   //    ::string m_windowName;
   //    HICON m_hicon;
   //
   //    bool m_bWndCreated;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM Window :
      virtual public ::subsystem::composite<WindowInterface>
   {
   public:

      Window();

       ~Window() override;

      // getWindow()
      // Get a handle of the window
      void * _HWND() const override;
      void _setHWND(void *) override;
      void * _WNDPROC_default() const override;
      ::operating_system::window operating_system_window() const override;
      void set_operating_system_window(const ::operating_system::window & operatingsystemwindow) override;

      WindowInterface*get_window_implementation() override;
      // createWindow()
      // Create window with windowName and setted style
      // other parameters can by changed
      bool createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent = {},
                        int xPos = WINDOW_WIDTH_USE_DEFAULT, int yPos = WINDOW_WIDTH_USE_DEFAULT,
                        int width = WINDOW_WIDTH_USE_DEFAULT, int height = WINDOW_WIDTH_USE_DEFAULT) override;
      bool destroyWindow() override;

      void setClipboardViewerInterest() override;
      bool onDrawClipboard() override;

      // setClass()
      // Set a class name only to the new window created by createWindow
      void setClass(const ::scoped_string  & scopedstrWindowClassName) override;


      void setShowCursor(bool bShowCursor) override;
      bool shouldShowCursor() override;

      virtual void setDoubleBuffering(bool bDoubleBuffering) override;
      virtual bool isDoubleBuffering() override;


      // basic window manipulation procedures
      void show() override;
      void hide() override;
      void enableWindow(bool bEnable) override;
      void setEnabled(bool bEnable) override;
      void updateWindow() override;
      bool setSize(const ::int_size & size) override;
      bool setPosition(const ::int_point & point) override;
      bool setPlacement(const ::int_rectangle & rectangle) override;
      void setWindowText(const ::scoped_string  & scopedstrText) override;




      //
      // Sets input focus to this control
      //

      void setFocus() override;

      //
      // Return true if window has input focus
      //

      bool hasFocus() override;

      //
      // Puts this control foreground and activates it
      //

      bool setForeground() override;

      // //
      // // Changes visible state of this control
      // //
      //
      // void setVisible(bool visible) override;

      //
      // Checks if this control is active (not disabled)
      //

      bool isEnabled() override;

      bool isWindow() override;

      bool isVisible() override;

      bool isIconic() override;

      bool isMinimized() override;

      bool isFullScreen() override;

      //
      // Invalidates control
      //

      void invalidate() override;

      //
      // Gets text associated with window
      //

      ::string getText() override;

      // loadIcon()
      // Set the icon of application where id can be from resource or handle HICON
      void loadIcon(unsigned int id) override;

      // setParent()
      // Making child window by changing parent of the window
      void setParent(const ::operating_system::window & operatingsystemwindow) override;


      ::operating_system::window dialog_item_operating_system_window(int iDlgItem) override;


      // for changing registered class parameters of created window
      void setClassStyle(unsigned int style) override;
      void setClassCursor(::innate_subsystem::CursorInterface * pcursor) override;
      void setClassBackground(::innate_subsystem::BrushInterface * pbrush) override;
      void setClassMenu(::innate_subsystem::MenuInterface * pmenu) override;


      bool we_want_WM_KEYDOWN_when_enter_is_pressed() const override;

      // for changing or get style and exstyle of window
      long long getStyle() override;
      void setStyle(unsigned int style) override;
      void addStyle(unsigned int styleFlag) override;
      void removeStyle(unsigned int styleFlag) override;
      bool isStyleEnabled(unsigned int styleFlags) override;


      long long getExStyle() override;
      void setExStyle(unsigned int exstyle) override;
      void addExStyle(unsigned int styleFlag) override;
      void removeExStyle(unsigned int styleFlag) override;
      bool isExStyleEnabled(unsigned int styleFlag) override;

      // full redraw of window area
      void redraw(const ::int_rectangle &rcArea ={}) override;

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      void setTimer(::uptr ident, unsigned int time) override;
      void killTimer(::uptr ident) override;

      // set foreground window
      void setForegroundWindow() override;

      // post message to this window
      void postMessage(unsigned int Msg, ::wparam wparam =0, ::lparam lparam =0) override;

      ::int_rectangle getClientRect() override;
      ::int_rectangle getFullScreenRect() override;
      ::int_size getBorderSize() override;
      ::int_rectangle getScreenWorkArea() override;

      //void setSizeFullScreenWindow() override;
      //void doRestoreFromFullScreen() override;
      void minimizeWindow() override;
      void restoreWindow() override;


      void doFullScreen() override;
      void doUnFullScreen() override;


      void adjustWindowSize() override;


      //bool wndProc(unsigned int message, ::wparam wparam, ::lparam lparam) override;

      // static const int MOUSE_LDOWN  = 1;
      // static const int MOUSE_MDOWN  = 2;
      // static const int MOUSE_RDOWN  = 4;
      // static const int MOUSE_WUP    = 8;
      // static const int MOUSE_WDOWN  = 16;

   // private:
   //    // This function may be implement in child class.
   //    // Here is stub function, always returned false.
       bool onCommand(::wparam wparam, ::lparam lparam) override;
   //    bool onNotify(int idCtrl, LPNMHDR pnmh) override;
       bool onSysCommand(::wparam wparam, ::lparam lparam) override;
       bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam) override;
       bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, const ::int_point & position) override;

      bool onCreate(void * pCreateStruct) override;

      bool on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam) override;


      void onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::int_rectangle & rectangle) override;


      void onBeforeFullScreen(bool bRestore) override;
      void onAfterFullScreen(bool bRestore) override;
      void onBeforeUnFullScreen(bool bMinimizing) override;
      void onAfterUnFullScreen(bool bMinimizing) override;
      bool onGetTooltip(int iControl, ::string & strTooltip) override;
      bool onCalculateDefaultSize(::int_rectangle & rectangleDefaultSize) override;
      void onAdjustWindowSize() override;

   // protected:
   //    HWND m_hWnd;
   //    ::string m_className;
   //    ::string m_windowName;
   //    HICON m_hicon;
   //
   //    bool m_bWndCreated;
   };

} // namespace innate_subsystem