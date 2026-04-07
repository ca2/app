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
#include "acme/subsystem/node/SystemException.h"
#include "acme/subsystem/node/OperatingSystemHookListener.h"
#include "OperatingSystemHook.h"


namespace windows
{

   namespace subsystem
   {
      //HHOOK OperatingSystemHook::s_hooks = 0;
      //WindowsHookEventListener *OperatingSystemHook::s_pwindowshookeventlistener = nullptr;

      OperatingSystemHook::OperatingSystemHook()
      {

      }

      OperatingSystemHook::~OperatingSystemHook()
      {
         ///unregisterKeyboardHook(0);
         ///
         stopKeyboardHook();

      }


      LRESULT CALLBACK OperatingSystemHook::s_lowLevelKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
      {

         if (nCode < 0)
         {

            return CallNextHookEx(s_hhook, nCode, wParam, lParam);

         }

         ::lresult lresult = 0;

         if (!s_poperatingsystemhook->lowLevelKeyboardHook(lresult, nCode, wParam, lParam))
         {
            return lresult;
         }


         return CallNextHookEx(s_hhook, nCode, wParam, lParam);

      }


      bool OperatingSystemHook::lowLevelKeyboardHook(::lresult & lresult, int nCode, WPARAM wParam, LPARAM lParam)
      {

         KBDLLHOOKSTRUCT *str = (KBDLLHOOKSTRUCT*) lParam;
         // Ignoring of CapsLock, NumLock, ScrollLock, ::remoting::Window (Ctrl key), Menu (Alt key), Shift (shift key).
         // Set the repeat count for the current scopedstrMessage bits.
         ::lparam newLParam = 1;
         // Set the scan code bits.
         newLParam |= (str->scanCode & 0xf) << 16;
         // Set the extended key bit.
         newLParam |= (str->flags & LLKHF_EXTENDED) << 24;
         // Set the context code bit.
         newLParam |= ((str->flags & LLKHF_ALTDOWN) > 0) << 29;
         // Set the transition state bit.
         newLParam |= ((str->flags & LLKHF_UP) > 0) << 31;
         if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
         {
            if (operating_system_hook_on_keyboard_message(lresult, (::user::enum_message)wParam, str->vkCode, newLParam ))
            {

               return true;

            }
            //PostMessage(m_dsktWnd.getHWnd(), wParam, str->vkCode, newLParam);
         }
         else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
         {
            if (operating_system_hook_on_keyboard_message(lresult, (::user::enum_message)wParam, str->vkCode, newLParam ))
            {
               return true;

            }
            //PostMessage(m_dsktWnd.getHWnd(), wParam, str->vkCode, newLParam);
         }
         //       return true;
         //        } else {
         //           return false;
         //        }
         // }

         // if (s_pwindowshookeventlistener->onHookProc(nCode, wParam, lParam)) {
         //    // Processing is successful. Don't pass it to the next hook procedure.
         //    return true;
         // } else {
         // Calling the CallNextHookEx function to chain to the next hook procedure.

         return false;

      }


      void OperatingSystemHook::startKeyboardHook()
      {
         //stopKeyboardHook();

         if (s_hhook)
         {

            throw ::exception(error_wrong_state);

         }
         //s_pwindowshookeventlistener = hookEventListener;
         s_poperatingsystemhook = this;
#ifdef CUBE
         HINSTANCE hinst = GetModuleHandle(0);
#else
         HINSTANCE hinst = GetModuleHandle(L"acme.dll");
#endif
         s_hhook = SetWindowsHookEx(WH_KEYBOARD_LL, s_lowLevelKeyboardHook, hinst, 0);
         if (!s_hhook)
         {
            throw ::subsystem::SystemException("Unnable to set hooks");
         }
      }

      void OperatingSystemHook::stopKeyboardHook()
      {
         if (s_hhook) {
            UnhookWindowsHookEx(s_hhook);
         }
         s_hhook = nullptr;
         s_poperatingsystemhook = nullptr;
      }
   } // namespace subsystem

} // namespace windows


