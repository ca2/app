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

#include "subsystem/_common_header.h"

#include "innate_subsystem/gui/NotifyIconWindow.h"

#include "innate_subsystem/drawing/Icon.h"

//#include <shellapi.h>

namespace innate_subsystem
{

   // FIXME: Add documentation to class.
   class NotifyIconSlice
       : virtual public ::particle_base
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

   using NotifyIconInterface = particle_interface<NotifyIconSlice, NotifyIconWindowInterface>;

   // FIXME: Add documentation to class.
   class CLASS_DECL_INNATE_SUBSYSTEM NotifyIconComposite :
      virtual public composite<NotifyIconSlice, NotifyIconWindow>
   {
   public:


      implement_compositeø(NotifyIcon, NotifyIconWindow, notifyicon)

      //NotifyIcon();
      //~NotifyIcon() override;

      void initialize_notify_icon(bool showAfterCreation = true) override { m_pnotifyicon->initialize_notify_icon(showAfterCreation); }

      IconInterface *getIcon() override { return m_pnotifyicon->getIcon(); }
      bool isVisible() const override { return m_pnotifyicon->isVisible(); }

      void setIcon(IconInterface *icon) override { m_pnotifyicon->setIcon(icon); }
      void setText(const char *text) override { m_pnotifyicon->setText(text); }

      void showBalloon(const char *message, const char *caption, unsigned int timeoutMillis) override { m_pnotifyicon->showBalloon(message, caption, timeoutMillis); }

      void show() override { m_pnotifyicon->show(); }
      void hide() override { m_pnotifyicon->hide(); }

      //   protected:
      //    NOTIFYICONDATA m_nid;
      //  Icon *m_icon;
      //bool m_visible;
   };

   class CLASS_DECL_INNATE_SUBSYSTEM NotifyIcon :
      virtual public NotifyIconComposite,
   virtual public NotifyIconWindow
   {
   public:
   };
}// namespace innate_subsystem

//#endif


