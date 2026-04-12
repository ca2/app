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

#include "subsystem/_common_header.h"
#include "subsystem/node/OperatingSystemHookListener.h"


namespace subsystem
{


   // Class for intercepting keyboard on low level.
   class CLASS_DECL_SUBSYSTEM OperatingSystemHookInterface :
   virtual public ::subsystem::particle_interface<OperatingSystemHookInterface>,
   virtual public ::subsystem::OperatingSystemHookListener
   {
   public:

      ::pointer_array < ::subsystem::OperatingSystemHookListener > m_listenera;

      OperatingSystemHookInterface();
      virtual ~OperatingSystemHookInterface();


      bool operating_system_hook_on_keyboard_message(::lresult & lresult, ::user::enum_message emessage, int iVkCode, ::lparam lparam) override;

   //    // Hook procedure.
   //    static LRESULT CALLBACK lowLevelKeyboardHook(int nCode,
   //                                                 WPARAM wParam,
   //                                                 LPARAM lParam);
   //
   //    // Registration of keyboard hook.
   virtual void registerKeyboardHook(::subsystem::OperatingSystemHookListener *phooklistener);
   //
   //    // Unregistration of keyboard hook.
   virtual void unregisterKeyboardHook(::subsystem::OperatingSystemHookListener *phooklistener);

      virtual void startKeyboardHook() = 0;
      virtual void stopKeyboardHook() = 0;
   //
   // private:
   //    // Hook object.
   //    static HHOOK s_hooks;
   //
   //    // Handler to the processing hooks function.
   //    static HookEventListener *s_eventListener;
   };


   // Class for intercepting keyboard on low level.
   class CLASS_DECL_SUBSYSTEM OperatingSystemHook :
   virtual public ::subsystem::composite< OperatingSystemHookInterface >
   {
   public:

      //WinHooks();
      OperatingSystemHook();
      ~OperatingSystemHook() override;

      //bool operating_system_hook_on_keyboard_message(::lresult & lresult, ::user::enum_message emessage, int iVkCode) override;

      //    // Hook procedure.
      //    static LRESULT CALLBACK lowLevelKeyboardHook(int nCode,
      //                                                 WPARAM wParam,
      //                                                 LPARAM lParam);
      //
      //    // Registration of keyboard hook.
      void startKeyboardHook() override;
      //
      //    // Unregistration of keyboard hook.
      void stopKeyboardHook() override;
      //
      // private:
      //    // Hook object.
      //    static HHOOK s_hooks;
      //
      //    // Handler to the processing hooks function.
      //    static HookEventListener *s_eventListener;
   };
} // namespace subsystem

