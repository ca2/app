// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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

//nclude "acme/subsystem/_common_header.h"
#include "innate_subsystem/gui/Window.h"
//#include "subsystem/::string.h"
//#include "acme/_operating_system.h"


namespace innate_subsystem
{
   enum VerticalAlignment
   {
      Left = 0x0,
      Center = 0x1,
      Right = 0x2
    };


      //
   // Base class to control windows control
   //

   class ControlInterface :
      virtual public ::Particle
   {
   public:


      //::pointer < Control > m_psubsystemcontrolThis;


      //ControlInterface();
      //Control(const ::operating_system::window & operatingsystemwindow);
      //virtual ~ControlInterface() = 0;

      //
      // Sets HWND associated with this control
      //





      //virtual void initialize_control(const ::operating_system::window & window) = 0;

      //virtual void setWindow(const ::operating_system::window & window) = 0;

      //
      // Changes enable state of this control
      //

      //virtual void setEnabled(bool enabled) = 0;

      //
      // Sets text associated with window
      //

      virtual void setText(const char *text) = 0;
      virtual void setSignedInt(int value) = 0;
      virtual void setUnsignedInt(unsigned int value) = 0;

      //
      // Sets text vertical alignment
      //

      virtual void setTextVerticalAlignment(VerticalAlignment align) = 0;

      // //
      // // Sets input focus to this control
      // //
      //
      // virtual void setFocus() = 0;
      //
      // //
      // // Return true if window has input focus
      // //
      //
      // virtual bool hasFocus() = 0;
      //
      // //
      // // Puts this control foreground and activates it
      // //
      //
      // virtual bool setForeground() = 0;

      //
      // Changes visible state of this control
      //

      virtual void setVisible(bool bVisible = true) = 0;

      // //
      // // Checks if this control is active (not disabled)
      // //
      //
      // virtual bool isEnabled() = 0;
      //
      // //
      // // Invalidates control
      // //
      //
      // virtual void invalidate() = 0;

      //
      // Gets text associated with window
      //

      //virtual ::string getText() = 0;

      //
      // Returns text vertical alignment
      //

      virtual VerticalAlignment getTextVerticalAlignment() = 0;

      //
      // Gets HWND associated with this control
      //

//      virtual ::operating_system::window operating_system_window() = 0;

      //void operator= (const ::operating_system::window& window)
      //{
      //   setWindow(window);
      //};

   //protected:

      //
      // Sets windows style for this control
      //

      //virtual void setStyle(unsigned int styleFlags) = 0;

      //
      // Gets windows style for this control
      //

      //virtual unsigned int getStyle() = 0;

      //
      // Adds style to this control
      //

      // virtual void addStyle(unsigned int styleFlag) = 0;
      //
      // //
      // // Removes style from this control
      // //
      //
      // virtual void removeStyle(unsigned int styleFlag) = 0;

      // //
      // // Returns true if styleFlags parameter is in
      // // this control's style
      // //
      //
      // virtual bool isStyleEnabled(unsigned int styleFlags) = 0;
      //
      // //
      // // Private methods for manipulation window extended styles
      // //
      //
      // virtual void setExStyle(unsigned int style) = 0;
      // virtual void addExStyle(unsigned int styleFlag) = 0;
      // virtual void removeExStyle(unsigned int styleFlag) = 0;
      //
      // virtual unsigned int getExStyle() = 0;
      // virtual bool isExStyleEnabled(unsigned int styleFlag) = 0;
      //
      //
      // Replaces default window proc with wndProc.
      //
      // This method must be called by child classes if needs to
      // override default window behavour.
      //

      //void replaceWindowProc(WNDPROC wndProc);

      //virtual void subclassWindow() = 0;

   // protected:
   //
   //    //
   //    // Handle of window
   //    //
   //
   //    HWND m_hwnd;
   //
   //    //
   //    // Pointer to default window procedure
   //    //
   //
   //    WNDPROC m_defWindowProc;
      //virtual void postUserMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam) = 0;
   };



   //using ControlInterface = ::particle_interface<ControlInterface, WindowInterface>;

   //
   // Base class to control windows control
   //

   class CLASS_DECL_INNATE_SUBSYSTEM ControlComposite :
      virtual public Composite < ControlInterface >
   {
   public:

      ImplementCompositeø(Control, control)

      ////::pointer < Control > m_psubsystemcontrolThis;


      //ControlComposite();
      ////Control(const ::operating_system::window & operatingsystemwindow);
      //~ControlComposite();


      //bool is_subsystem_implementation() const  override {return false;}
      //bool is_subsystem_composite() const  override {return true;}
      //
      // Sets HWND associated with this control
      //

       //void initialize_control(const ::operating_system::window & window);

       //void setWindow(const ::operating_system::window & window);

      //
      // Changes enable state of this control
      //

       //void setEnabled(bool enabled);

      //
      // Sets text associated with window
      //

       void setText(const char *text) { m_pcontrol->setText(text); }
       void setSignedInt(int value) { m_pcontrol->setSignedInt(value); }
       void setUnsignedInt(unsigned int value) { m_pcontrol->setUnsignedInt(value); }

      //
      // Sets text vertical alignment
      //

       void setTextVerticalAlignment(VerticalAlignment align) { m_pcontrol->setTextVerticalAlignment(align); }

      // //
      // // Sets input focus to this control
      // //
      //
      //  void setFocus();
      //
      // //
      // // Return true if window has input focus
      // //
      //
      //  bool hasFocus();
      //
      // //
      // // Puts this control foreground and activates it
      // //
      //
      //  bool setForeground();
      //
      //
      // Changes visible state of this control
      //

       void setVisible(bool visible) { m_pcontrol->setVisible(visible); }
      //
      // //
      // // Checks if this control is active (not disabled)
      // //
      //
      //  bool isEnabled();
      //
      // //
      // // Invalidates control
      // //
      //
      //  void invalidate();

      //
      // Gets text associated with window
      //

       //::string getText();

      //
      // Returns text vertical alignment
      //

       VerticalAlignment getTextVerticalAlignment() { return m_pcontrol->getTextVerticalAlignment(); }

      //
      // Gets HWND associated with this control
      //

       //::operating_system::window operating_system_window();

      //void operator= (const ::operating_system::window& window)
      //{
      //   setWindow(window);
      //};

   //protected:

      //
      // Sets windows style for this control
      //

       //void setStyle(unsigned int styleFlags);

      //
      // Gets windows style for this control
      //

       //unsigned int getStyle();

      //
      // Adds style to this control
      //

       //void addStyle(unsigned int styleFlag);

      //
      // Removes style from this control
      //

       //void removeStyle(unsigned int styleFlag);

      //
      // Returns true if styleFlags parameter is in
      // this control's style
      //

       ///bool isStyleEnabled(unsigned int styleFlags);

      //
      // Private methods for manipulation window extended styles
      //

       // void setExStyle(unsigned int style);
       // void addExStyle(unsigned int styleFlag);
       // void removeExStyle(unsigned int styleFlag);
       //
       // unsigned int getExStyle();
       // bool isExStyleEnabled(unsigned int styleFlag);

      //
      // Replaces default window proc with wndProc.
      //
      // This method must be called by child classes if needs to
      // override default window behavour.
      //

      //void replaceWindowProc(WNDPROC wndProc);


      //void subclassWindow();

   // protected:
   //
   //    //
   //    // Handle of window
   //    //
   //
   //    HWND m_hwnd;
   //
   //    //
   //    // Pointer to default window procedure
   //    //
   //
   //    WNDPROC m_defWindowProc;

      //void postUserMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam);
   };



   class CLASS_DECL_INNATE_SUBSYSTEM ControlAggregate :
      virtual public Aggregate<ControlComposite, WindowAggregate>
   {
   public:

      ImplementAggregateø(Control, Window)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM Control :
      virtual public Object<ControlAggregate>
   {
   public:

      ImplementObjectø(Control)

   };


} // namespace subsystem




