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


   enum enum_window_class
   {

      e_window_class_none = 0,
      e_window_class_viewer = 1,

   };


   class WindowInterface :
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
      virtual void setOnDrawInterest() = 0;
      virtual bool onDrawClipboard() = 0;
      // setClass()
      // Set a class name only to the new window created by createWindow
      //virtual void setClass(const ::scoped_string  & scopedstrWindowClassName) = 0;

      virtual void setClass(enum_window_class ewindowclass) = 0;

      // We want WM_KEYDOWN scopedstrMessage when enter is pressed
      virtual bool we_want_WM_KEYDOWN_when_enter_is_pressed() const {return false;}


      virtual void setCursor(enum_cursor ecursor) = 0;
      virtual enum_cursor getCursor() = 0;

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
      virtual void setParent(::innate_subsystem::WindowInterface * pwindowParent) = 0;


      virtual ::operating_system::window dialog_item_operating_system_window(int iDlgItem) = 0;


      virtual void subclassControlById(::Particle * pWindowControl, unsigned int id) = 0;
      virtual void subclassWindow(const ::operating_system::window & operatingsystemwindow) = 0;
      virtual void unsubclassWindow() = 0;


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
      virtual bool onCommand(unsigned int controlID, bool bAccelerator, unsigned int notificationID) = 0;
   //virtual bool onNotify(int idCtrl, LPNMHDR pnmh) = 0;
   virtual bool onSysCommand(::wparam wparam, ::lparam lparam) = 0;
   virtual bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam) = 0;
   virtual bool onMouseEx(unsigned int uMessage, int iButtonMask, unsigned short wheelSpeed, const ::int_point &point,
                          bool &bDoDefaultProcessing) = 0;

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
      virtual void onSize() = 0;
   // protected:
   //    HWND m_hWnd;
   //    ::string m_className;
   //    ::string m_windowName;
   //    HICON m_hicon;
   //
   //    bool m_bWndCreated;
   };

      class CLASS_DECL_INNATE_SUBSYSTEM WindowCallback : virtual public Callback<WindowInterface>
   {
   public:

      ImplementCallbackø(Window, window)
   };

   class CLASS_DECL_INNATE_SUBSYSTEM WindowComposite :
      virtual public Composite<WindowInterface>
   {
   public:

      ImplementCompositeWithCallbackø(Window, window)

      // Window();
      //
      //  ~Window() override;

      // getWindow()
      // Get a handle of the window
      void * _HWND() const override {return m_pwindow->_HWND();}
      void _setHWND(void *p) override{return m_pwindow->_setHWND(p);}
      void * _WNDPROC_default() const override{return m_pwindow->_WNDPROC_default();}
      ::operating_system::window operating_system_window() const override {return m_pwindow->operating_system_window();}
      void set_operating_system_window(const ::operating_system::window & operatingsystemwindow) override
      {

         m_pwindow->set_operating_system_window(operatingsystemwindow);
      }

      WindowInterface*get_window_implementation() override {return m_pwindow->get_window_implementation();}
      // createWindow()
      // Create window with windowName and setted style
      // other parameters can by changed
      bool createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent = {},
                        int xPos = WINDOW_WIDTH_USE_DEFAULT, int yPos = WINDOW_WIDTH_USE_DEFAULT,
                        int width = WINDOW_WIDTH_USE_DEFAULT, int height = WINDOW_WIDTH_USE_DEFAULT) override
      {
         return m_pwindow->createWindow(scopedstrWindowName, style, operatingsystemwindowParent, xPos, yPos, width, height);

      }
      bool destroyWindow() override
      {

         return m_pwindow->destroyWindow();
      }

      void setClipboardViewerInterest() override
      {

         m_pwindow->setClipboardViewerInterest();
      }
      void setOnDrawInterest() override { m_pwindow->setOnDrawInterest(); }
      bool onDrawClipboard() override
      {

         return m_pwindow->onDrawClipboard();
      }

      // setClass()
      // Set a class name only to the new window created by createWindow
      //void setClass(const ::scoped_string  & scopedstrWindowClassName) override
      void setClass(enum_window_class ewindowclass)
      {

         m_pwindow->setClass(ewindowclass);
         //m_pwindow->setClass(scopedstrWindowClassName);
      }


      void setCursor(enum_cursor ecursor) override { m_pwindow->setCursor(ecursor); }
      enum_cursor getCursor() override { return m_pwindow->getCursor(); }

      virtual void setDoubleBuffering(bool bDoubleBuffering) override { m_pwindow->setDoubleBuffering(bDoubleBuffering); }
      virtual bool isDoubleBuffering() override { return m_pwindow->isDoubleBuffering(); }


      // basic window manipulation procedures
      void show() override { m_pwindow->show(); }
      void hide() override { m_pwindow->hide(); }
      void enableWindow(bool bEnable) override { m_pwindow->enableWindow(bEnable); }
      void setEnabled(bool bEnable) override { m_pwindow->setEnabled(bEnable); }
      void updateWindow() override { m_pwindow->updateWindow(); }
      bool setSize(const ::int_size & size) override { return m_pwindow->setSize(size); }
      bool setPosition(const ::int_point & point) override { return m_pwindow->setPosition(point); }
      bool setPlacement(const ::int_rectangle & rectangle) override { return m_pwindow->setPlacement(rectangle); }
      void setWindowText(const ::scoped_string  & scopedstrText) override { m_pwindow->setWindowText(scopedstrText); }




      //
      // Sets input focus to this control
      //

      void setFocus() override { m_pwindow->setFocus(); }

      //
      // Return true if window has input focus
      //

      bool hasFocus() override { return m_pwindow->hasFocus(); }

      //
      // Puts this control foreground and activates it
      //

      bool setForeground() override { return m_pwindow->setForeground(); }

      // //
      // // Changes visible state of this control
      // //
      //
      // void setVisible(bool visible) override;

      //
      // Checks if this control is active (not disabled)
      //

      bool isEnabled() override { return m_pwindow->isEnabled(); }

      bool isWindow() override { return m_pwindow->isWindow(); }

      bool isVisible() override { return m_pwindow->isVisible(); }

      bool isIconic() override { return m_pwindow->isIconic(); }

      bool isMinimized() override { return m_pwindow->isMinimized(); }

      bool isFullScreen() override { return m_pwindow->isFullScreen(); }

      //
      // Invalidates control
      //

      void invalidate() override { m_pwindow->invalidate(); }

      //
      // Gets text associated with window
      //

      ::string getText() override { return m_pwindow->getText(); }

      // loadIcon()
      // Set the icon of application where id can be from resource or handle HICON
      void loadIcon(unsigned int id) override { m_pwindow->loadIcon(id); }

      // setParent()
      // Making child window by changing parent of the window
      void setParent(::innate_subsystem::WindowInterface * pwindowParent) override { m_pwindow->setParent(pwindowParent); }


      ::operating_system::window dialog_item_operating_system_window(int iDlgItem) override { return m_pwindow->dialog_item_operating_system_window(iDlgItem); }
      void subclassControlById(::Particle * pWindowControl, unsigned int id) override { m_pwindow->subclassControlById(pWindowControl, id); }
      void subclassWindow(const ::operating_system::window & operatingsystemwindow)override { m_pwindow->subclassWindow(operatingsystemwindow); }
      void unsubclassWindow() override { m_pwindow->unsubclassWindow(); }

      // for changing registered class parameters of created window
      void setClassStyle(unsigned int style) override { m_pwindow->setClassStyle(style); }
      void setClassCursor(::innate_subsystem::CursorInterface * pcursor) override { m_pwindow->setClassCursor(pcursor); }
      void setClassBackground(::innate_subsystem::BrushInterface * pbrush) override { m_pwindow->setClassBackground(pbrush); }
      void setClassMenu(::innate_subsystem::MenuInterface * pmenu) override { m_pwindow->setClassMenu(pmenu); }


      bool we_want_WM_KEYDOWN_when_enter_is_pressed() const override { return false; }

      // for changing or get style and exstyle of window
      long long getStyle() override { return m_pwindow->getStyle(); }
      void setStyle(unsigned int style) override { m_pwindow->setStyle(style); }
      void addStyle(unsigned int styleFlag) override { m_pwindow->addStyle(styleFlag); }
      void removeStyle(unsigned int styleFlag) override { m_pwindow->removeStyle(styleFlag); }
      bool isStyleEnabled(unsigned int styleFlags) override { return m_pwindow->isStyleEnabled(styleFlags); }


      long long getExStyle() override { return m_pwindow->getExStyle(); }
      void setExStyle(unsigned int exstyle) override { m_pwindow->setExStyle(exstyle); }
      void addExStyle(unsigned int styleFlag) override { m_pwindow->addExStyle(styleFlag); }
      void removeExStyle(unsigned int styleFlag) override { m_pwindow->removeExStyle(styleFlag); }
      bool isExStyleEnabled(unsigned int styleFlag) override { return m_pwindow->isExStyleEnabled(styleFlag); }

      // full redraw of window area
      void redraw(const ::int_rectangle &rcArea ={}) override { m_pwindow->redraw(rcArea); }

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      void setTimer(::uptr ident, unsigned int time) override { m_pwindow->setTimer(ident, time); }
      void killTimer(::uptr ident) override { m_pwindow->killTimer(ident); }

      // set foreground window
      void setForegroundWindow() override { m_pwindow->setForegroundWindow(); }

      // post message to this window
      void postMessage(unsigned int Msg, ::wparam wparam =0, ::lparam lparam =0) override { m_pwindow->postMessage(Msg, wparam, lparam); }

      ::int_rectangle getClientRect() override { return m_pwindow->getClientRect(); }
      ::int_rectangle getFullScreenRect() override { return m_pwindow->getFullScreenRect(); }
      ::int_size getBorderSize() override { return m_pwindow->getBorderSize(); }
      ::int_rectangle getScreenWorkArea() override { return m_pwindow->getScreenWorkArea(); }

      //void setSizeFullScreenWindow() override;
      //void doRestoreFromFullScreen() override;
      void minimizeWindow() override { m_pwindow->minimizeWindow(); }
      void restoreWindow() override { m_pwindow->restoreWindow(); }


      void doFullScreen() override { m_pwindow->doFullScreen(); }
      void doUnFullScreen() override { m_pwindow->doUnFullScreen(); }


      void adjustWindowSize() override { m_pwindow->adjustWindowSize(); }


      //bool wndProc(unsigned int message, ::wparam wparam, ::lparam lparam) override;

      // static const int MOUSE_LDOWN  = 1;
      // static const int MOUSE_MDOWN  = 2;
      // static const int MOUSE_RDOWN  = 4;
      // static const int MOUSE_WUP    = 8;
      // static const int MOUSE_WDOWN  = 16;

   // private:
   //    // This function may be implement in child class.
   //    // Here is stub function, always returned false.
      bool onCommand(unsigned int controlID, bool bAccelerator, unsigned int notificationID) override { return false; }
   //    bool onNotify(int idCtrl, LPNMHDR pnmh) override;
      bool onSysCommand(::wparam wparam, ::lparam lparam) override { return false; }
      bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam) override { return false; }
      bool onMouseEx(unsigned int uMessage, int iButtonMask, unsigned short wheelSpeed,
          const ::int_point& point, bool & bDoDefaultProcessing) override

      {
          return false;

      }

      bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, const ::int_point &position) override
      {
         return false;
      }

      bool onCreate(void * pCreateStruct) override { return false; }

      bool on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam) override 
      { 
      return false;
      }


      void onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::int_rectangle & rectangle) override {  }


      void onBeforeFullScreen(bool bRestore) override {  }
      void onAfterFullScreen(bool bRestore) override {  }
      void onBeforeUnFullScreen(bool bMinimizing) override {  }
      void onAfterUnFullScreen(bool bMinimizing) override {  }
      bool onGetTooltip(int iControl, ::string & strTooltip) override { return false; }
      bool onCalculateDefaultSize(::int_rectangle &rectangleDefaultSize) override { return false; }
      void onAdjustWindowSize() override { }
      void onSize() override {  }

   // protected:
   //    HWND m_hWnd;
   //    ::string m_className;
   //    ::string m_windowName;
   //    HICON m_hicon;
   //
   //    bool m_bWndCreated;
   };

   class CLASS_DECL_INNATE_SUBSYSTEM WindowAggregate :
   virtual public Aggregate < WindowComposite >
   {
   public:

      ImplementBaseø(Window)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM Window :
virtual public Object<WindowAggregate>
   {
   public:

       ImplementObjectø(Window)

   };


} // namespace innate_subsystem
