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

#include "apex/innate_subsystem/NotifyIconWindow.h"

#include "apex/innate_subsystem/drawing/Icon.h"

//#include <shellapi.h>

namespace innate_subsystem
{

   // FIXME: Add documentation to class.
   class NotifyIconInterface :
      virtual public ::subsystem::particle_interface<NotifyIconInterface>,
   virtual public NotifyIconWindow
   {
   public:
      
      
      //NotifyIcon();
      //virtual ~NotifyIconInterface() = 0;

      virtual void initialize_notify_icon(bool showAfterCreation = true) = 0;

      virtual IconInterface *getIcon() = 0;
      virtual bool isVisible() const = 0;

      virtual void setIcon(IconInterface *icon) = 0;
      virtual void setText(const char *text) = 0;

      virtual void showBalloon(const char *message, const char *caption, unsigned int timeoutMillis) = 0;

      virtual void show() = 0;
      virtual void hide() = 0;

//   protected:
  //    NOTIFYICONDATA m_nid;
    //  Icon *m_icon;
      //bool m_visible;
   };


   // FIXME: Add documentation to class.
   class CLASS_DECL_APEX NotifyIcon :
      virtual public ::subsystem::composite<NotifyIconInterface>
   {
   public:


      NotifyIcon();
      ~NotifyIcon() override;

      void initialize_notify_icon(bool showAfterCreation = true) override;

      IconInterface *getIcon() override;
      bool isVisible() const override;

      void setIcon(IconInterface *icon) override;
      void setText(const char *text) override;

      void showBalloon(const char *message, const char *caption, unsigned int timeoutMillis) override;

      void show() override;
      void hide() override;

      //   protected:
      //    NOTIFYICONDATA m_nid;
      //  Icon *m_icon;
      //bool m_visible;
   };


}// namespace innate_subsystem

//#endif


