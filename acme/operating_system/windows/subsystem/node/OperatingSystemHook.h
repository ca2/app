// Copyright (C) 2013 GlavSoft LLC.
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


#include "acme/subsystem/node/OperatingSystemHook.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"


namespace windows
{

namespace subsystem
   {
   // Class for intercepting keyboard on low level.
   class CLASS_DECL_ACME OperatingSystemHook :
   virtual  public ::subsystem::implementation<::subsystem::OperatingSystemHookInterface>
   {
   public:
      OperatingSystemHook();
      ~OperatingSystemHook() override;


      virtual bool lowLevelKeyboardHook(::lresult & lresult, int nCode,
                                             WPARAM wParam,
                                             LPARAM lParam);

      // Hook procedure.
      static LRESULT CALLBACK s_lowLevelKeyboardHook(int nCode,
                                                   WPARAM wParam,
                                                   LPARAM lParam);

      // Registration of keyboard hook.
      //static void registerKeyboardHook(WindowsHookEventListener *hookEventListener);

      // Unregistration of keyboard hook.
      //static void unregisterKeyboardHook(WindowsHookEventListener *hookEventListener);

      void startKeyboardHook() override;

      void stopKeyboardHook() override;

      //private:
      // Hook object.
      static HHOOK s_hhook;
      static OperatingSystemHook * s_poperatingsystemhook;
      // Handler to the processing hooks function.
      //static
   };


   } // namespace subsystem
} // namespace windows
