// Created by camilo on 2023-11-14 14:37 <3ThomasBorregaardSorensen!!
// To keyboard_state.h by camilo on 2023-11-14 18:10 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/constant/user_key.h"
#include "acme/user/key/state.h"
#include "acme/user/user/key_state.h"


namespace user
{


   class CLASS_DECL_ACME keyboard_state :
      virtual public ::particle,
      virtual public ::user::key_state
   {
   public:


      //::pointer<::map<::user::enum_key, bool>> m_pmapKeyPressed;

      ::key::enum_state       m_estateaKey[::user::e_key_count];


      keyboard_state();
      keyboard_state(const keyboard_state & keyboardstate) = delete;
      ~keyboard_state() override;


      keyboard_state & operator = (const keyboard_state &keyboardstate) = delete;


      virtual void initialize_keyboard_state();

      void destroy() override;


      //virtual bool is_key_pressed(const ::user::e_key & ekey) const;
      virtual ::user::key_state key_state() const;
#if defined(WINDOWS_DESKTOP)
      virtual ::user::key_state key_state_with_wm_mouse_wparam(::wparam wparam) const;
#endif

      //virtual void set_key_pressed(const ::user::e_key & ekey, bool bPressed);
      void set_key_state(const ::user::e_key & ekey, ::key::enum_state estate) {
         m_estateaKey[(::i32) ekey] = estate;
      }
      void set_key_pressed(const ::user::e_key & ekey, bool bPressed) {
         if (bPressed)
            set_key_state(ekey, ::key::e_state_pressed);
         else
            set_key_state(ekey,::key::e_state_none);
      }
      ::key::enum_state _key_state(const ::user::e_key & ekey) const {
         return m_estateaKey[(::i32) ekey];
      }
      bool is_key_pressed(const ::user::e_key & ekey) const
   {

      // _synchronous_lock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      //
      // {
      //
      //    bool bPressed = false;
      //
      //    if (node()->is_key_pressed(&bPressed, ekey))
      //    {
      //
      //       return bPressed;
      //    }
      // }
      //
      // _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //if (!m_pmapKeyPressed)
      //{

      //   construct_newø(m_pmapKeyPressed);
      //}

      //bool bPressed = false;

      if (ekey == ::user::e_key_shift)
      {


         //m_pmapKeyPressed->find(::user::e_key_shift, bPressed);
         if (m_estateaKey[::user::e_key_shift] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_left_shift, bPressed);
         if (m_estateaKey[::user::e_key_left_shift] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_right_shift, bPressed);
         if (m_estateaKey[::user::e_key_right_shift] != ::key::e_state_none)
            return true;
         return false;
      }
      else if (ekey == ::user::e_key_command
#ifdef __APPLE__
               || ekey == ::user::e_key_system_command
#endif
      )
      {
         //m_pmapKeyPressed->find(::user::e_key_command, bPressed);
         if (m_estateaKey[::user::e_key_command] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_left_command, bPressed);
         if (m_estateaKey[::user::e_key_left_command] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_right_command, bPressed);
         if (m_estateaKey[::user::e_key_right_command] != ::key::e_state_none)
            return true;
         return false;
      }
      else if (ekey == ::user::e_key_control
#ifndef __APPLE__
               || ekey == ::user::e_key_system_command
#endif
      )
      {
         //m_pmapKeyPressed->find(::user::e_key_control, bPressed);
         if (m_estateaKey[::user::e_key_control] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_left_control, bPressed);
         if (m_estateaKey[::user::e_key_left_control] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_right_control, bPressed);
         if (m_estateaKey[::user::e_key_right_control] != ::key::e_state_none)
            return true;
         return false;
      }
      else if (ekey == ::user::e_key_alt)
      {
         //m_pmapKeyPressed->find(::user::e_key_alt, bPressed);
         if (m_estateaKey[::user::e_key_alt] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_left_alt, bPressed);
         if (m_estateaKey[::user::e_key_left_alt] != ::key::e_state_none)
            return true;
         //m_pmapKeyPressed->find(::user::e_key_right_alt, bPressed);
         if (m_estateaKey[::user::e_key_right_alt] != ::key::e_state_none)
            return true;
         return false;
      }
      else
      {

          return m_estateaKey[(::i32) ekey] != ::key::e_state_none;
         //m_pmapKeyPressed->find(ekey, bPressed);
      }

   //ret:

     // return bPressed;
   }


   };


} // namespace user



