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
#include "framework.h"
#include "acme/_operating_system.h"
#include "OperatingSystemHook.h"
#include "subsystem/node/SystemException.h"


namespace subsystem
{
   //HHOOK WinHooks::s_hooks = 0;
   //HookEventListener *WinHooks::s_eventListener = 0;


   OperatingSystemHookInterface::OperatingSystemHookInterface()
   {

   }


   OperatingSystemHookInterface::~OperatingSystemHookInterface()
   {
      //unregisterKeyboardHook(0);
   }


   bool OperatingSystemHookInterface::operating_system_hook_on_keyboard_message(::lresult & lresult, ::user::enum_message emessage, int iVkCode, ::lparam lparam)
   {

      for (auto plistener : m_listenera)
      {

         if (plistener->operating_system_hook_on_keyboard_message(lresult, emessage, iVkCode, lparam))
         {

            return true;

         }

      }

      return false;
   }

   //    // Registration of keyboard hook.
   void OperatingSystemHookInterface::registerKeyboardHook(::subsystem::OperatingSystemHookListener *phooklistener)
   {

      if (::is_null(phooklistener))
      {

         throw ::exception(error_bad_argument);

      }

      if (m_listenera.is_empty())
      {

         startKeyboardHook();

      }

      m_listenera.add_unique(phooklistener);

   }
   //
   //    // Unregistration of keyboard hook.
   void OperatingSystemHookInterface::unregisterKeyboardHook(::subsystem::OperatingSystemHookListener *phooklistener)
   {

      if (::is_null(phooklistener))
      {

         throw ::exception(error_bad_argument);

      }


      m_listenera.add_unique(phooklistener);

      if (m_listenera.is_empty())
      {

         stopKeyboardHook();

      }

   }


   OperatingSystemHook::OperatingSystemHook()
   {

   }


   OperatingSystemHook::~OperatingSystemHook()
   {
      //unregisterKeyboardHook(0);
   }


   void OperatingSystemHook::startKeyboardHook()
   {

      m_pparticleThis->startKeyboardHook();

   }


   void OperatingSystemHook::stopKeyboardHook()
   {

      m_pparticleThis->stopKeyboardHook();

   }


   // }
   // LRESULT CALLBACK WinHooks::lowLevelKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
   // {
   //   if (nCode < 0) {
   //     return CallNextHookEx(s_hooks, nCode, wParam, lParam);
   //   }
   //   if (s_eventListener->onHookProc(nCode, wParam, lParam)) {
   //     // Processing is successful. Don't pass it to the next hook procedure.
   //     return true;
   //   } else {
   //     // Calling the CallNextHookEx function to chain to the next hook procedure.
   //     return CallNextHookEx(s_hooks, nCode, wParam, lParam);
   //   }
   // }
   //
   // void WinHooks::registerKeyboardHook(HookEventListener *hookEventListener)
   // {
   //   unregisterKeyboardHook(0);
   //   s_eventListener = hookEventListener;
   //   HINSTANCE hinst = GetModuleHandle(0);
   //   s_hooks = SetWindowsHookEx(WH_KEYBOARD_LL, lowLevelKeyboardHook, hinst, 0);
   //   if (s_hooks == NULL) {
   //     throw SystemException("Unnable to set hooks");
   //   }
   // }
   //
   // void WinHooks::unregisterKeyboardHook(HookEventListener *hookEventListener)
   // {
   //   if (s_hooks != 0) {
   //     UnhookWindowsHookEx(s_hooks);
   //   }
   //   s_hooks = 0;
   //   s_eventListener = 0;
   // }
} // nanamespace subsystem
