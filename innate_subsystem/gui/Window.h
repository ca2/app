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
#include "subsystem/platform/Particle.h"
#include "acme/user/micro/elemental.h"

struct operating_ambient_window_t
{
   
   ::uptr m_u;
   
};

#define WIN32_WA_ACTIVE 1
#define WIN32_WA_CLICKACTIVE 2
#define WIN32_WA_INACTIVE 0
#define WIN32_SB_THUMBTRACK 1
#define WIN32_SB_THUMBPOSITION 2
#define WIN32_SB_LINEUP 3
#define WIN32_SB_LINEDOWN 4
#define WIN32_SB_PAGEUP 5
#define WIN32_SB_PAGEDOWN 6
#define WIN32_SB_LINELEFT 7
#define WIN32_SB_PAGELEFT 8
#define WIN32_SB_LINERIGHT 9
#define WIN32_SB_PAGERIGHT 10
    
namespace user{

enum enum_system_command{
   
   e_system_command_none,
   e_system_command_restore, // if ((wParam & 0xfff0) == SC_RESTORE) SC_RESTORE
   
};

} // namespace user

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
      virtual operating_ambient_window_t operating_ambient_window() const = 0;
      virtual void set_operating_ambient_window(operating_ambient_window_t operatingambientwindow) = 0;
      virtual void * _WNDPROC_default() const = 0;
      virtual ::operating_system::window operating_system_window() const = 0;
      virtual void set_operating_system_window(const ::operating_system::window & operatingsystemwindow) = 0;


      virtual WindowInterface * get_window_implementation() = 0;

      // createWindow()
      // Create window with windowName and setted style
      // other parameters can by changed
      virtual bool createWindow(const ::scoped_string & scopedstrWindowName, ::u32 style, const ::operating_system::window & operatingsystemwindowParent = 0,
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

      
      // Set resource name for the window
      virtual void setResourceName(const ::scoped_string & scopedstr) = 0;
      // Set resource id for the window
      virtual void setResourceId(::u32 uId) = 0;
      // Get resource name for the window
      virtual ::string getResourceName() = 0;
      // Get resource id for the window
      virtual ::u32 getResourceId() = 0;


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
      virtual bool setSize(const ::i32_size & size) = 0;
      virtual bool setPosition(const ::i32_point & point) = 0;
      virtual bool setPlacement(const ::i32_rectangle & rectangle) = 0;
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
      virtual void loadIcon(::u32 id) = 0;

      // setParent()
      // Making child window by changing parent of the window
      virtual void setParent(::innate_subsystem::WindowInterface * pwindowParent) = 0;
      virtual ::innate_subsystem::WindowInterface * getParent() = 0;


      virtual ::operating_system::window dialog_item_operating_system_window(int iDlgItem) = 0;


      virtual void subclassControlById(::Particle * pWindowControl, ::u32 id) = 0;
      virtual void subclassWindow(const ::operating_system::window & operatingsystemwindow) = 0;
      virtual void unsubclassWindow() = 0;


      // for changing registered class parameters of created window
      virtual void setClassStyle(::u32 style) = 0;
      virtual void setClassCursor(::innate_subsystem::CursorInterface * pcursor) = 0;
      virtual void setClassBackground(::innate_subsystem::BrushInterface * pbrush) = 0;
      virtual void setClassMenu(::innate_subsystem::MenuInterface * pmenu) = 0;

      // for changing or get style and exstyle of window
      virtual ::i64 getStyle() = 0;
      virtual void setStyle(::u32 style) = 0;
      virtual void addStyle(::u32 styleFlag) = 0;
      virtual void removeStyle(::u32 styleFlag) = 0;
      virtual bool isStyleEnabled(::u32 styleFlags) = 0;


      virtual ::i64 getExStyle() = 0;
      virtual void setExStyle(::u32 exstyle) = 0;
      virtual void addExStyle(::u32 styleFlag) = 0;
      virtual void removeExStyle(::u32 styleFlag) = 0;
      virtual bool isExStyleEnabled(::u32 styleFlag) = 0;



      // full redraw of window area
      virtual void redraw(const ::i32_rectangle &rcArea = {}) = 0;

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      virtual void setTimer(::uptr ident, ::u32 time) = 0;
      virtual void killTimer(::uptr ident) = 0;

      // set foreground window
      virtual void setForegroundWindow() = 0;

      // post message to this window
      virtual void postMessage(::u32 Msg, ::wparam wparam = 0, ::lparam lparam = 0) = 0;
      virtual void post(const ::procedure &procedure) = 0;

      virtual ::i32_rectangle getClientRect() = 0;
      virtual ::i32_rectangle getFullScreenRect() = 0;
      virtual ::i32_size getBorderSize() = 0;
      virtual ::i32_rectangle getScreenWorkArea() = 0;


      //virtual void setSizeFullScreenWindow() = 0;
      //virtual void doRestoreFromFullScreen() = 0;
      virtual void minimizeWindow() = 0;
      virtual void restoreWindow() = 0;


      virtual void doFullScreen() = 0;
      virtual void doUnFullScreen() = 0;

      virtual void adjustWindowSize() = 0;

      virtual void setMouseCursor(::enum_cursor ecursor) = 0;
   // private:
   //    // This function may be implement in child class.
   //    // Here is stub function, always returned false.
      virtual bool onCommand(::u32 controlID, ::u32 notificationID) = 0;
   //virtual bool onNotify(int idCtrl, LPNMHDR pnmh) = 0;
   //virtual bool onSysCommand(::wparam wparam, ::lparam lparam) = 0;
      virtual bool on_user_system_command(::user::enum_system_command esystemcommand) = 0;
   virtual bool onMessage(::user::enum_message emessage, ::wparam wparam, ::lparam lparam) = 0;
   virtual bool onMouseEx(::u32 uMessage, int iButtonMask, unsigned short wheelSpeed, const ::i32_point &point,
                          bool &bDoDefaultProcessing) = 0;

   virtual bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, const ::i32_point & position) = 0;
   virtual bool onKey(::user::enum_message eusermessage, ::user::enum_key euserkey) = 0;


   virtual bool onCreate(void * pCreateStruct) = 0;

   virtual bool on_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam) = 0;

      virtual void onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::i32_rectangle & rectangle) = 0;

      virtual void onBeforeFullScreen(bool bRestore) = 0;
      virtual void onAfterFullScreen(bool bRestore) = 0;
      virtual void onBeforeUnFullScreen(bool bMinimizing) = 0;
      virtual void onAfterUnFullScreen(bool bMinimizing) = 0;
      virtual bool onGetTooltip(int iControl, ::string & strTooltip) = 0;
      virtual bool onCalculateDefaultSize(::i32_rectangle & rectangleDefaultSize) = 0;
      virtual void onAdjustWindowSize() = 0;
      virtual void onSize() = 0;
      
      
//      virtual void on_set_cursor_rectangles() = 0;
//      virtual void invalidate_cursor_rectangles() = 0;
//      virtual void add_cursor_rectangle(const ::i32_rectangle & rectangle, ::enum_cursor ecursor) = 0;
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
      virtual public Composite<WindowInterface>,
      virtual public ::micro::elemental
   {
   public:

      ImplementCompositeWithCallbackø(Window, window)

      // Window();
      //
      //  ~Window() override;

      // getWindow()
      // Get a handle of the window
      
      operating_ambient_window_t operating_ambient_window() const override {return m_pwindow->operating_ambient_window();}
      void set_operating_ambient_window(operating_ambient_window_t operatingambientwindow) override{return m_pwindow->set_operating_ambient_window(operatingambientwindow);}

      
      
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
      bool createWindow(const ::scoped_string & scopedstrWindowName, ::u32 style, const ::operating_system::window & operatingsystemwindowParent = {},
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
      void setClass(enum_window_class ewindowclass) override
      {

         m_pwindow->setClass(ewindowclass);
         //m_pwindow->setClass(scopedstrWindowClassName);
      }

      
      
      // Set resource name for the window
      void setResourceName(const ::scoped_string & scopedstr)  override
      {
         
         m_pwindow->setResourceName(scopedstr);
         
      }
      // Set resource id for the window
      void setResourceId(::u32 uId)  override
      {
         
         m_pwindow->setResourceId(uId);
         
      }
      // Get resource name for the window
      ::string getResourceName()  override
      {
         
         return m_pwindow->getResourceName();
         
      }
      // Get resource id for the window
      ::u32 getResourceId()  override
      {
         
         return m_pwindow->getResourceId();
      
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
      bool setSize(const ::i32_size & size) override { return m_pwindow->setSize(size); }
      bool setPosition(const ::i32_point & point) override { return m_pwindow->setPosition(point); }
      bool setPlacement(const ::i32_rectangle & rectangle) override { return m_pwindow->setPlacement(rectangle); }
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
      void loadIcon(::u32 id) override { m_pwindow->loadIcon(id); }

      // setParent()
      // Making child window by changing parent of the window
      void setParent(::innate_subsystem::WindowInterface * pwindowParent) override { m_pwindow->setParent(pwindowParent); }
      ::innate_subsystem::WindowInterface*getParent() override {return m_pwindow->getParent();}


      ::operating_system::window dialog_item_operating_system_window(int iDlgItem) override { return m_pwindow->dialog_item_operating_system_window(iDlgItem); }
      void subclassControlById(::Particle * pWindowControl, ::u32 id) override { m_pwindow->subclassControlById(pWindowControl, id); }
      void subclassWindow(const ::operating_system::window & operatingsystemwindow)override { m_pwindow->subclassWindow(operatingsystemwindow); }
      void unsubclassWindow() override { m_pwindow->unsubclassWindow(); }

      // for changing registered class parameters of created window
      void setClassStyle(::u32 style) override { m_pwindow->setClassStyle(style); }
      void setClassCursor(::innate_subsystem::CursorInterface * pcursor) override { m_pwindow->setClassCursor(pcursor); }
      void setClassBackground(::innate_subsystem::BrushInterface * pbrush) override { m_pwindow->setClassBackground(pbrush); }
      void setClassMenu(::innate_subsystem::MenuInterface * pmenu) override { m_pwindow->setClassMenu(pmenu); }


      bool we_want_WM_KEYDOWN_when_enter_is_pressed() const override { return false; }

      // for changing or get style and exstyle of window
      ::i64 getStyle() override { return m_pwindow->getStyle(); }
      void setStyle(::u32 style) override { m_pwindow->setStyle(style); }
      void addStyle(::u32 styleFlag) override { m_pwindow->addStyle(styleFlag); }
      void removeStyle(::u32 styleFlag) override { m_pwindow->removeStyle(styleFlag); }
      bool isStyleEnabled(::u32 styleFlags) override { return m_pwindow->isStyleEnabled(styleFlags); }


      ::i64 getExStyle() override { return m_pwindow->getExStyle(); }
      void setExStyle(::u32 exstyle) override { m_pwindow->setExStyle(exstyle); }
      void addExStyle(::u32 styleFlag) override { m_pwindow->addExStyle(styleFlag); }
      void removeExStyle(::u32 styleFlag) override { m_pwindow->removeExStyle(styleFlag); }
      bool isExStyleEnabled(::u32 styleFlag) override { return m_pwindow->isExStyleEnabled(styleFlag); }

      // full redraw of window area
      void redraw(const ::i32_rectangle &rcArea ={}) override { m_pwindow->redraw(rcArea); }

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      void setTimer(::uptr ident, ::u32 time) override { m_pwindow->setTimer(ident, time); }
      void killTimer(::uptr ident) override { m_pwindow->killTimer(ident); }

      // set foreground window
      void setForegroundWindow() override { m_pwindow->setForegroundWindow(); }

      // post message to this window
      void postMessage(::u32 Msg, ::wparam wparam =0, ::lparam lparam =0) override { m_pwindow->postMessage(Msg, wparam, lparam); }
      void post(const ::procedure &procedure) override { m_pwindow->post(procedure); }

      ::i32_rectangle getClientRect() override { return m_pwindow->getClientRect(); }
      ::i32_rectangle getFullScreenRect() override { return m_pwindow->getFullScreenRect(); }
      ::i32_size getBorderSize() override { return m_pwindow->getBorderSize(); }
      ::i32_rectangle getScreenWorkArea() override { return m_pwindow->getScreenWorkArea(); }

      //void setSizeFullScreenWindow() override;
      //void doRestoreFromFullScreen() override;
      void minimizeWindow() override { m_pwindow->minimizeWindow(); }
      void restoreWindow() override { m_pwindow->restoreWindow(); }


      void doFullScreen() override { m_pwindow->doFullScreen(); }
      void doUnFullScreen() override { m_pwindow->doUnFullScreen(); }


      void adjustWindowSize() override { m_pwindow->adjustWindowSize(); }

      
      void setMouseCursor(::enum_cursor ecursor) override{
         m_pwindow->setMouseCursor(ecursor);
      }

//      void invalidate_cursor_rectangles() override {m_pwindow->invalidate_cursor_rectangles();}
//      void add_cursor_rectangle(const ::i32_rectangle & rectangle, ::enum_cursor ecursor) override {m_pwindow->add_cursor_rectangle(rectangle, ecursor);}
      //bool wndProc(::u32 message, ::wparam wparam, ::lparam lparam) override;

      // static const int MOUSE_LDOWN  = 1;
      // static const int MOUSE_MDOWN  = 2;
      // static const int MOUSE_RDOWN  = 4;
      // static const int MOUSE_WUP    = 8;
      // static const int MOUSE_WDOWN  = 16;

   // private:
   //    // This function may be implement in child class.
   //    // Here is stub function, always returned false.
      bool onCommand(::u32 controlID, ::u32 notificationID) override { return false; }
   //    bool onNotify(int idCtrl, LPNMHDR pnmh) override;
      //bool onSysCommand(::wparam wparam, ::lparam lparam) override { return false; }
      
      bool on_user_system_command(::user::enum_system_command esystemcommand) override { return false;}
      bool onMessage(::user::enum_message emessage, ::wparam wparam, ::lparam lparam) override { return false; }
      bool onMouseEx(::u32 uMessage, int iButtonMask, unsigned short wheelSpeed,
          const ::i32_point& point, bool & bDoDefaultProcessing) override

      {
          return false;

      }

      bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, const ::i32_point &position) override
      {
         return false;
      }
      bool onKey(::user::enum_message emessage, ::user::enum_key euserkey) override
      {
         return false;
      }

      bool onCreate(void * pCreateStruct) override { return false; }

      bool on_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam) override 
      { 
      return false;
      }


      void onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::i32_rectangle & rectangle) override {  }


      void onBeforeFullScreen(bool bRestore) override {  }
      void onAfterFullScreen(bool bRestore) override {  }
      void onBeforeUnFullScreen(bool bMinimizing) override {  }
      void onAfterUnFullScreen(bool bMinimizing) override {  }
      bool onGetTooltip(int iControl, ::string & strTooltip) override { return false; }
      bool onCalculateDefaultSize(::i32_rectangle &rectangleDefaultSize) override { return false; }
      void onAdjustWindowSize() override { }
      void onSize() override {  }
      //void on_set_cursor_rectangles() override { }

      void back_on_mouse_move(::user::mouse * pmouse) override;
      void back_on_left_button_down(::user::mouse * pmouse) override;
      void back_on_left_button_up(::user::mouse * pmouse) override;
      void back_on_right_button_down(::user::mouse * pmouse) override;
      void back_on_right_button_up(::user::mouse * pmouse) override;
      void on_create() override;
      void on_key_down(::user::key * pkey) override;
      void on_key_up(::user::key * pkey) override;

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
