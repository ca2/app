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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "acme/subsystem/node/SystemException.h"
#include "acme/subsystem/io/InputStream.h"
#include "acme/subsystem/node/InputInjector.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"


namespace windows
{
   namespace subsystem
   {
      /**
       * Wrapper of WinAPI methods that can inject input events into system
       * (mouse, keyboard etc) and get information about input device states.
       */
      class CLASS_DECL_ACME InputInjector :
            virtual public ::subsystem::InputInjector
      {
      public:

         InputInjector();
         ~InputInjector();


         virtual void initialize_input_injector(bool ctrlAltDelEnabled, ::subsystem::LogWriter *log) override;

         // Toggles off all modifiers including the Delete key.
         void resetModifiers() override;

         /**
          * Syntezises key pressed event.
          * @param vkCode virtual code of key.
          * @throws SystemException on fail.
          */
         void injectKeyPress(unsigned char vkCode) override;

         /**
          * Syntezises key released event.
          * @param vkCode virtual code of key.
          * @throws SystemException on fail.
          */
         void injectKeyRelease(unsigned char vkCode) override;

         /**
          * Syntezises key event (press or release).
          * @param vkCode virtual code of key.
          * @param release if true then sybtezises release event, otherwise, press.
          * @throws SystemException on fail.
          */
         void injectKeyEvent(unsigned char vkCode, bool release, bool extended = false) override;

         /**
          * Syntezises char press or release event.
          * @param ch target unicode character.
          * @param release if set to true then release event will be emulated, otherwise,
          * press event.
          * @remark method must be used only for locale dependent keys ('a', 'b', 'c', 'd' etc),
          * not for extended and auxilary keys like LEFT, RIGHT, INSERT etc.
          * @throws SystemException on fail.
          */
         void injectCharEvent(int ch, bool release) override;

         //private:
         // Return true if CapsLock toggled on.
         bool capsToggled() override;

         // Returns true if the vkCode value is a dead key in keyboardLayout layout.
         virtual bool _isDeadKey(SHORT scanResult, HKL keyboardLayout);

         // Returns true if the printed char can get by one key event sending.
         // Else returns false e.g. for uppercase french e with ogonek that may be get
         // only by a sequence keyevenst with a dead char, but the lower case
         // e can be get by one pressing of the "7" key.
         virtual bool _isOneKeyEventChar(WCHAR ch, SHORT scanResult, HKL keyboardLayout);

         // Returns true if characters differs when the modifier state is on and off.
         virtual bool _isDifferentWith(BYTE modifier, BYTE modStateValueOfOn,
                              BYTE virtKey, HKL keyboardLayout);

         // Return true if key generates the same symbol with pressed the Shift key
         // and without.
         virtual bool _isInvariantToShift(BYTE virtKey, HKL keyboardLayout);

         // Return true if the char is the same with the CAPS or without.
         virtual bool _isResistantToCaps(BYTE virtKey, HKL keyboardLayout);

         // Returns true if the ch symbol is a ascii symbol.
         bool isAscii(int ch) override;

         // Returns current kbd layout of an active window.
         // Throws ::remoting::Exception on an error.
         virtual HKL getCurrentKbdLayout();

         // Searches virtual code in available keyboard layouts and returns the code
         // if found. If virtual code has not been found throws an ::remoting::Exception.
         // Puts current kbd layout to the *hklCurrent argument (if no throwing).
         virtual SHORT _searchVirtKey(WCHAR ch, HKL hklCurrent);

         /**
          * Array of extended virtual codes.
          */
         static const BYTE EXTENDED_KEYS[];

         bool m_controlIsPressed;
         bool m_menuIsPressed;
         bool m_deleteIsPressed;
         bool m_shiftIsPressed;
         bool m_winIsPressed;
         bool m_ctrlAltDelEnabled;

         ::subsystem::LogWriter *m_log;
      };
   }// namespace subsystem
} // namespace windows
