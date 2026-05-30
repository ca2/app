/// Created by camilo on 2026-05-28 12:34 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/constant/key_state.h"


namespace user
{


   class CLASS_DECL_ACME key_state
   {
   public:

      ::user::e_key_state m_ekeystate;

      
      key_state();
      key_state(const ::user::e_key_state &ekeystate);
      key_state(const ::user::key_state &keystate);
      key_state(const ::user::key_state * pkeystate);
      ~key_state();


       key_state & operator = (const ::user::key_state &keystate);
       key_state & operator = (const ::user::key_state * pkeystate);


      virtual bool is_mouse_state(const ::user::e_key_state &ekeystate) const;
      virtual ::i32_boolean has_mouse_state(const ::user::e_key_state &ekeystate) const;


      const ::user::e_key_state &operator() ()const {return m_ekeystate; }


      ::i32_boolean is_left_button_pressed() const { return m_ekeystate & ::user::e_key_state_left_button; }
      ::i32_boolean is_right_button_pressed() const { return m_ekeystate & ::user::e_key_state_right_button; }
      ::i32_boolean is_shift_pressed() const { return m_ekeystate & ::user::e_key_state_shift; }
      ::i32_boolean is_control_pressed() const { return m_ekeystate & ::user::e_key_state_control; }
      ::i32_boolean is_middle_button_pressed() const { return m_ekeystate & ::user::e_key_state_middle_button; }
      ::i32_boolean is_x1_button_pressed() const { return m_ekeystate & ::user::e_key_state_x1_button; }
      ::i32_boolean is_x2_button_pressed() const { return m_ekeystate & ::user::e_key_state_x2_button; }



      void set_left_button_pressed() { m_ekeystate |= ::user::e_key_state_left_button; }
      void set_right_button_pressed() { m_ekeystate |= ::user::e_key_state_right_button; }
      void set_shift_pressed() { m_ekeystate |= ::user::e_key_state_shift; }
      void set_control_pressed() { m_ekeystate |= ::user::e_key_state_control; }
      void set_middle_button_pressed() { m_ekeystate |= ::user::e_key_state_middle_button; }
      void set_x1_button_pressed() { m_ekeystate |= ::user::e_key_state_x1_button; }
      void set_x2_button_pressed() { m_ekeystate |= ::user::e_key_state_x2_button; }



      void clear_left_button_pressed() { m_ekeystate -= ::user::e_key_state_left_button; }
      void clear_right_button_pressed() { m_ekeystate -=    ::user::e_key_state_right_button; }
      void clear_shift_pressed() { m_ekeystate -= ::user::e_key_state_shift; }
      void clear_control_pressed() { m_ekeystate -= ::user::e_key_state_control; }
      void clear_middle_button_pressed() { m_ekeystate -= ::user::e_key_state_middle_button; }
      void clear_x1_button_pressed() { m_ekeystate -= ::user::e_key_state_x1_button; }
      void clear_x2_button_pressed() { m_ekeystate -= ::user::e_key_state_x2_button; }


   };


} // namespace user
