// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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


#include "acme/subsystem/_common_header.h"


#include "apex/innate_subsystem/WindowProcHolder.h"

namespace innate_subsystem
{
   class NotifyIconWindowInterface :
   virtual public ::subsystem::particle_interface
   {
   public:

      //NotifyIconWindow();
      virtual ~NotifyIconWindowInterface() = 0;

      virtual ::operating_system::window getWindow() = 0;

      virtual void setWindowProcHolder(WindowProcHolder *wph) = 0;

      //protected:
      //  HWND m_window;
      //WindowProcHolder *m_wph;

      //friend class NotifyIcon;
   };

   class NotifyIconWindow :
      virtual public ::subsystem::composite<NotifyIconWindow
   {
   public:

      NotifyIconWindow();
       ~NotifyIconWindow() override;

      ::operating_system::window getWindow() override;

      void setWindowProcHolder(WindowProcHolder *wph) override;

      //protected:
      //  HWND m_window;
      //WindowProcHolder *m_wph;

      //friend class NotifyIcon;
   };

} // namespace innate_subsystem