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


#include "innate_subsystem/gui/Window.h"
#include "subsystem/_common_header.h"


//#include "innate_subsystem/gui/WindowProcHolder.h"

namespace innate_subsystem
{


   class NotifyIconWindowInterface : virtual public ::particle_base
   {
   public:

      //NotifyIconWindow();
      //virtual ~NotifyIconWindowInterface() = 0;

      //virtual ::operating_system::window getWindow() = 0;

      //virtual void setWindowProcHolder(WindowProcHolder *wph) = 0;

      //protected:
      //  HWND m_window;
      //WindowProcHolder *m_wph;

      //friend class NotifyIcon;

      virtual void onNotifyIconRightButtonUp() = 0;
      virtual void onNotifyIconLeftButtonDown() = 0;
      virtual void onTaskBarCreated() = 0;



   };


   //using NotifyIconWindowInterface = particle_interface<NotifyIconWindowInterface, WindowInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM NotifyIconWindowComposite :
      virtual public composite<NotifyIconWindowInterface >
   {
   public:


      implement_compositeø(NotifyIconWindow, notifyiconwindow)

      //NotifyIconWindow();
      //~NotifyIconWindow() override;

      //::operating_system::window getWindow() override;

      //void setWindowProcHolder(WindowProcHolder *wph) override;

      //protected:
      //  HWND m_window;
      //WindowProcHolder *m_wph;

      virtual void onNotifyIconRightButtonUp() override { m_pnotifyiconwindow->onNotifyIconRightButtonUp(); }
      virtual void onNotifyIconLeftButtonDown() override { m_pnotifyiconwindow->onNotifyIconLeftButtonDown(); }
      virtual void onTaskBarCreated() override { m_pnotifyiconwindow->onTaskBarCreated(); }


      //friend class NotifyIcon;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM NotifyIconWindow :
   virtual public aggregate < NotifyIconWindowComposite, Window >
   {
   public:


      implement_aggregateø(NotifyIconWindow, Window)

   };



} // namespace innate_subsystem
