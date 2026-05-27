// Created by camilo on 2026-04-17 17:51 <3ThomasBorregaardSørensen!!
// Using HKL (Windows Keyboard Layout) code from Remoting.
#include "framework.h"
#include "KeyboardLayout.h"
#include "acme/constant/user_key.h"
// #ifndef _BASE_WINDOW_H_
// #define _BASE_WINDOW_H_


namespace innate_subsystem
{

	          keyboard_state_t::keyboard_state_t() :
       m_allowProcessCharEvent(false), m_allowProcessDoubleChar(false), m_doubleDeadCatched(false),
       m_leftMetaIsPressed(false), m_rightMetaIsPressed(false)
   {
   }

   void keyboard_state_t::clearKeyState()
   {
      memset(m_viewerKeyState, 0, sizeof(m_viewerKeyState));
      memset(m_serverKeyState, 0, sizeof(m_serverKeyState));
   }

   bool keyboard_state_t::isPressed(::user::enum_key ekey) { return (m_serverKeyState[ekey] & 128) != 0; }

   // void clearKeyState();
   ::i32 keyboard_state_t::GettingCharFromCtrlSymbol(::i32 ch)
   {
      bool ctrlPressed = isPressed(::user::e_key_left_control) || isPressed(::user::e_key_right_control);
      bool altPressed = isPressed(::user::e_key_left_alt) || isPressed(::user::e_key_right_alt);
      bool shiftPressed = isPressed(::user::e_key_left_shift) || isPressed(::user::e_key_right_shift);
      ::u32 oldCh = (::u32)ch;
      if (ctrlPressed && !altPressed && ch < 32)
      {
         if (ch >= 1 && ch <= 26 && !shiftPressed)
         {
            ch += 96;
         }
         else
         {
            ch += 64;
         }
         ::debugf("The %u ::i8 is a control symbol then"
                 " it will be increased to %u",
                 oldCh, (::u32)ch);
      }
      return ch;
   }




} // namespace innate_subsystem
