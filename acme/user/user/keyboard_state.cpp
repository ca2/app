// Created by camilo on 2023-11-14 14:37 <3ThomasBorregaardSorensen!!
// To keyboard_state.cpp by camilo on 2023-11-14 18:10 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "keyboard_state.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"


namespace user
{

   keyboard_state::keyboard_state() {} 


   keyboard_state::~keyboard_state() {}   


   void keyboard_state::initialize_keyboard_state()
   {

      defer_create_synchronization();

      //construct_newø(m_pmapKeyPressed);

   }


   void keyboard_state::destroy()
   {
      
      //m_pmapKeyPressed.release();

      ::particle::destroy();

   }


//    bool keyboard_state::is_key_pressed(const ::user::e_key & ekey) const
//    {
//
//       _synchronous_lock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       {
//
//          bool bPressed = false;
//
//          if (node()->is_key_pressed(&bPressed, ekey))
//          {
//
//             return bPressed;
//          }
//       }
//
//       _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       //if (!m_pmapKeyPressed)
//       //{
//
//       //   construct_newø(m_pmapKeyPressed);
//       //}
//
//       bool bPressed = false;
//
//       if (ekey == ::user::e_key_shift)
//       {
//
//
//          //m_pmapKeyPressed->find(::user::e_key_shift, bPressed);
//          if (m_estateaKey[::user::e_key_shift] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_left_shift, bPressed);
//          if (m_estateaKey[::user::e_key_left_shift] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_right_shift, bPressed);
//          if (m_estateaKey[::user::e_key_right_shift] != ::key::e_state_none)
//             return true;
//       }
//       else if (ekey == ::user::e_key_command
// #ifdef __APPLE__
//                || ekey == ::user::e_key_system_command
// #endif
//       )
//       {
//          //m_pmapKeyPressed->find(::user::e_key_command, bPressed);
//          if (m_estateaKey[::user::e_key_command] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_left_command, bPressed);
//          if (m_estateaKey[::user::e_key_left_command] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_right_command, bPressed);
//          if (m_estateaKey[::user::e_key_right_command] != ::key::e_state_none)
//             return true;
//       }
//       else if (ekey == ::user::e_key_control
// #ifndef __APPLE__
//                || ekey == ::user::e_key_system_command
// #endif
//       )
//       {
//          //m_pmapKeyPressed->find(::user::e_key_control, bPressed);
//          if (m_estateaKey[::user::e_key_control] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_left_control, bPressed);
//          if (m_estateaKey[::user::e_key_left_control] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_right_control, bPressed);
//          if (m_estateaKey[::user::e_key_right_control] != ::key::e_state_none)
//             return true;
//       }
//       else if (ekey == ::user::e_key_alt)
//       {
//          //m_pmapKeyPressed->find(::user::e_key_alt, bPressed);
//          if (m_estateaKey[::user::e_key_alt] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_left_alt, bPressed);
//          if (m_estateaKey[::user::e_key_left_alt] != ::key::e_state_none)
//             return true;
//          //m_pmapKeyPressed->find(::user::e_key_right_alt, bPressed);
//          if (m_estateaKey[::user::e_key_right_alt] != ::key::e_state_none)
//             return true;
//       }
//       else
//       {
//
//           bPressed = m_estateaKey[::user::e_key_right_shift] != ::key::e_state_none;
//          //m_pmapKeyPressed->find(ekey, bPressed);
//       }
//
//    ret:
//
//       return bPressed;
//    }


   // void keyboard_state::set_key_state(const ::user::e_key & ekey, ::key::enum_state e)
   // {
   //
   //    //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   //
   //    if (!m_pmapKeyPressed)
   //    {
   //
   //       construct_newø(m_pmapKeyPressed);
   //    }
   //
   //    (*m_pmapKeyPressed)[ekey] = bPressed;
   //
   //     if (b)
   //     return true
   //
   // }


   ::user::key_state keyboard_state::key_state() const
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::user::key_state keystate;

      if (is_key_pressed(::user::e_key_left_shift))
      {

         keystate.m_ekeystate |= ::user::e_key_state_left_shift;
      }

      if (is_key_pressed(::user::e_key_right_shift))
      {

         keystate.m_ekeystate |= ::user::e_key_state_right_shift;
      }

      if (is_key_pressed(::user::e_key_left_control))
      {

         keystate.m_ekeystate |= ::user::e_key_state_left_control;

         // #if !defined(__APPLE__)
         //
         //          ekeystate |= ::user::e_key_system_left_command;
         //
         // #endif
      }

      if (is_key_pressed(::user::e_key_right_control))
      {

         keystate.m_ekeystate |= ::user::e_key_state_right_control;

         // #if !defined(__APPLE__)
         //
         //          ekeystate |= ::user::e_key_system_right_command;
         //
         // #endif
      }

      if (is_key_pressed(::user::e_key_left_alt))
      {

         keystate.m_ekeystate |= ::user::e_key_state_left_alt;
      }

      if (is_key_pressed(::user::e_key_right_alt))
      {

         keystate.m_ekeystate |= ::user::e_key_state_right_alt;
      }

      if (is_key_pressed(::user::e_key_left_command))
      {

         keystate.m_ekeystate |= ::user::e_key_state_left_command;

#if defined(__APPLE__)

         ekeystate |= ::user::e_key_state_system_left_command;

#endif
      }

      if (is_key_pressed(::user::e_key_right_command))
      {

         keystate.m_ekeystate |= ::user::e_key_state_right_command;

#if defined(__APPLE__)

         keystate.m_ekeystate |= ::user::e_key_state_system_right_command;

#endif
      }

      if (is_key_pressed(::user::e_key_left_button))
      {

         keystate.m_ekeystate |= ::user::e_key_state_left_button;
      }

      if (is_key_pressed(::user::e_key_middle_button))
      {

         keystate.m_ekeystate |= ::user::e_key_state_middle_button;
      }

      if (is_key_pressed(::user::e_key_right_button))
      {

         keystate.m_ekeystate |= ::user::e_key_state_right_button;

      }

      return keystate;

   }


   // CLASS_DECL_ACME::user::e_key_state wm_mouse_wparam_to_user_key_state(::wparam wparam)
   ::user::key_state keyboard_state::key_state_with_wm_mouse_wparam(::wparam wparam) const
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      using namespace ::user;

      ::user::key_state keystate;

      if (wparam & MK_LBUTTON)
      {

         keystate.m_ekeystate |=  e_key_state_left_button;
      }

      if (wparam & MK_RBUTTON)
      {

         keystate.m_ekeystate |=  e_key_state_right_button;
      }

      if (wparam & MK_SHIFT)
      {

         keystate.m_ekeystate |=  e_key_state_shift;

         if (is_key_pressed(::user::e_key_left_shift))
         {

            keystate.m_ekeystate |=  e_key_state_left_shift;
         }

         if (is_key_pressed(::user::e_key_right_shift))
         {

            keystate.m_ekeystate |=  e_key_state_right_shift;
         }
      }

      if (wparam & MK_CONTROL)
      {

         keystate.m_ekeystate |=  e_key_state_control;

         if (is_key_pressed(::user::e_key_left_control))
         {

            keystate.m_ekeystate |=  e_key_state_left_control;
         }

         if (is_key_pressed(::user::e_key_right_control))
         {

            keystate.m_ekeystate |=  e_key_state_right_control;
         }
      }

      if (wparam & MK_MBUTTON)
      {

         keystate.m_ekeystate |=  e_key_state_middle_button;
      }

#ifdef MK_XBUTTON1
      if (wparam & MK_XBUTTON1)
      {

         keystate.m_ekeystate |=  e_key_state_x1_button;
      }
#endif

#ifdef MK_XBUTTON2
      if (wparam & MK_XBUTTON2)
      {

         keystate.m_ekeystate |=  e_key_state_x2_button;
      }
#endif

      if (is_key_pressed(::user::e_key_left_alt))
      {

         keystate.m_ekeystate |=  e_key_state_left_alt;
      }

      if (is_key_pressed(::user::e_key_right_alt))
      {

         keystate.m_ekeystate |=  e_key_state_right_alt;
      }

#ifdef VK_LWIN
      if (is_key_pressed(::user::e_key_left_command))
      {

         keystate.m_ekeystate |=  e_key_state_left_command;
      }
#endif

#ifdef VK_RWIN
      if (is_key_pressed(::user::e_key_right_command))
      {

         keystate.m_ekeystate |=  e_key_state_right_command;
      }
#endif

      return keystate;

   }




} // namespace user


