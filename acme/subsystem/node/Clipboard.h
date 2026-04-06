// Copyright (C) 2012 GlavSoft LLC.
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

#pragma once


#include "acme/subsystem/_common_header.h"
#include "acme/operating_system/window.h"


namespace subsystem
{
   class CLASS_DECL_ACME Clipboard :
   virtual public ::subsystem::particle
   {
   public:

      //ClipboardInterface(HWND hwnd);
      Clipboard();
      ~Clipboard() override;


      virtual void initialize_clipboard(const ::operating_system::window & operatingsystemwindow) = 0;

      virtual void setHWnd(const ::operating_system::window & operatingsystemwindow) = 0;

      // get string from windows clipboard
      virtual bool getString(::string & str) = 0;

      // update windows clipboard
      virtual bool setString(const ::scoped_string & scopedstr) = 0;

      // //protected:
      // static const char CR = '\r';
      // static const char LF = '\n';

      //protected:
      // function removed CR before LF
      virtual ::string removeCR(const ::scoped_string & scopedstr) = 0;

      // function replaced LF to CR+LF. If before LF already is CR, this not added second
      virtual ::string addCR(const ::scoped_string & scopedstr) = 0;

      // HANDLE m_hndClipboard;
      // HWND m_hwnd;
   };

   // class CLASS_DECL_ACME Clipboard :
   // virtual public ::subsystem::composite< ClipboardInterface>
   // {
   // public:
   //
   //    Clipboard(const ::operating_system::window & operatingsystemwindow);
   //     ~Clipboard() override;
   //
   //
   //    void initialize_clipboard(const ::operating_system::window & operatingsystemwindow) override;
   //
   //    void setHWnd(const ::operating_system::window & operatingsystemwindow) override;
   //
   //    // get string from windows clipboard
   //    bool getString(::string & str) override;
   //
   //    // update windows clipboard
   //    bool setString(const ::scoped_string & scopedstr) override;
   //
   //    // //protected:
   //    // static const char CR = '\r';
   //    // static const char LF = '\n';
   //
   //    //protected:
   //    // function removed CR before LF
   //    ::string removeCR(const ::scoped_string & scopedstr)override;
   //
   //    // function replaced LF to CR+LF. If before LF already is CR, this not added second
   //    ::string addCR(const ::scoped_string & scopedstr) override;
   //
   //    // HANDLE m_hndClipboard;
   //    // HWND m_hwnd;
   // };
} // namespace subsystem


