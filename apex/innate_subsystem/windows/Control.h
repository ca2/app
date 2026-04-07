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

#include "apex/innate_subsystem/Control.h"


namespace windows
{
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

      class Control :
         virtual public ::subsystem::implementation<::innate_subsystem::Control
      {
      public:


         //::pointer < Control > m_psubsystemcontrolThis;


         Control();
         //Control(HWND hwnd);
         ~Control()override;

         //
         // Sets HWND associated with this control
         //





         virtual void initialize_control(const ::operating_system::window & window) = 0;

         virtual void setWindow(const ::operating_system::window & window) = 0;

         //
         // Changes enable state of this control
         //

         virtual void setEnabled(bool enabled) = 0;

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

         //
         // Changes visible state of this control
         //

         virtual void setVisible(bool visible) = 0;

         //
         // Checks if this control is active (not disabled)
         //

         virtual bool isEnabled() = 0;

         //
         // Invalidates control
         //

         virtual void invalidate() = 0;

         //
         // Gets text associated with window
         //

         virtual ::string getText() = 0;

         //
         // Returns text vertical alignment
         //

         virtual VerticalAlignment getTextVerticalAlignment() = 0;

         //
         // Gets HWND associated with this control
         //

         virtual ::operating_system::window getWindow() = 0;

         void operator= (const ::operating_system::window& window)
         {
            setWindow(window);
         };

         //protected:

         //
         // Sets windows style for this control
         //

         virtual void setStyle(unsigned int styleFlags) = 0;

         //
         // Gets windows style for this control
         //

         virtual unsigned int getStyle() = 0;

         //
         // Adds style to this control
         //

         virtual void addStyle(unsigned int styleFlag) = 0;

         //
         // Removes style from this control
         //

         virtual void removeStyle(unsigned int styleFlag) = 0;

         //
         // Returns true if styleFlags parameter is in
         // this control's style
         //

         virtual bool isStyleEnabled(unsigned int styleFlags) = 0;

         //
         // Private methods for manipulation window extended styles
         //

         virtual void setExStyle(unsigned int style) = 0;
         virtual void addExStyle(unsigned int styleFlag) = 0;
         virtual void removeExStyle(unsigned int styleFlag) = 0;

         virtual unsigned int getExStyle() = 0;
         virtual bool isExStyleEnabled(unsigned int styleFlag) = 0;

         //
         // Replaces default window proc with wndProc.
         //
         // This method must be called by child classes if needs to
         // override default window behavour.
         //

         //void replaceWindowProc(WNDPROC wndProc);

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
         virtual void postUserMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam) = 0;
      };

      //
      // Base class to control windows control
      //

      class Control :
          public ::subsystem::composite < ControlInterface >
      {
      public:


         //::pointer < Control > m_psubsystemcontrolThis;


         Control();
         //Control(HWND hwnd);
         ~Control() override;


         //
         // Sets HWND associated with this control
         //

         void initialize_control(const ::operating_system::window & window) override;

         void setWindow(const ::operating_system::window & window) override;

         //
         // Changes enable state of this control
         //

         void setEnabled(bool enabled) override;

         //
         // Sets text associated with window
         //

         void setText(const char *text) override;
         void setSignedInt(int value) override;
         void setUnsignedInt(unsigned int value) override;

         //
         // Sets text vertical alignment
         //

         void setTextVerticalAlignment(VerticalAlignment align) override;

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

         //
         // Changes visible state of this control
         //

         void setVisible(bool visible) override;

         //
         // Checks if this control is active (not disabled)
         //

         bool isEnabled() override;

         //
         // Invalidates control
         //

         void invalidate() override;

         //
         // Gets text associated with window
         //

         ::string getText() override;

         //
         // Returns text vertical alignment
         //

         VerticalAlignment getTextVerticalAlignment() override;

         //
         // Gets HWND associated with this control
         //

         ::operating_system::window getWindow() override;

         void operator= (const ::operating_system::window& window)
         {
            setWindow(window);
         };

         //protected:

         //
         // Sets windows style for this control
         //

         void setStyle(unsigned int styleFlags) override;

         //
         // Gets windows style for this control
         //

         unsigned int getStyle() override;

         //
         // Adds style to this control
         //

         void addStyle(unsigned int styleFlag) override;

         //
         // Removes style from this control
         //

         void removeStyle(unsigned int styleFlag) override;

         //
         // Returns true if styleFlags parameter is in
         // this control's style
         //

         bool isStyleEnabled(unsigned int styleFlags) override;

         //
         // Private methods for manipulation window extended styles
         //

         void setExStyle(unsigned int style) override;
         void addExStyle(unsigned int styleFlag) override;
         void removeExStyle(unsigned int styleFlag) override;

         unsigned int getExStyle() override;
         bool isExStyleEnabled(unsigned int styleFlag) override;

         //
         // Replaces default window proc with wndProc.
         //
         // This method must be called by child classes if needs to
         // override default window behavour.
         //

         //void replaceWindowProc(WNDPROC wndProc);

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

         void postUserMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam) override;
      };

      //#endif
   } // namespace subsystem
} // namespace windows