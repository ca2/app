//
//  user_mouse.hpp
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 14/08/17.
//
//
#pragma once



namespace user
{


   class CLASS_DECL_ACME mouse :
      virtual public element
   {
   public:


      uptr                                m_nFlags;
      point_i32                           m_point;
      point_i32                           m_pointDesired;
      bool                                m_bTranslated;
      __pointer(::windowing::cursor)      m_pcursor;
      __pointer(::user::interaction)      m_puserinteractionHit;


      virtual unsigned int get_message()
      {
         return 0;
      }

      bool is_left_button_pressed() const       { return m_nFlags & (int) ::user::e_button_state_left; }
      bool is_right_button_pressed() const      { return m_nFlags & (int)::user::e_button_state_right; }
      bool is_shift_pressed() const             { return m_nFlags & (int)::user::e_button_state_shift; }
      bool is_control_pressed() const           { return m_nFlags & (int)::user::e_button_state_control; }
      bool is_middle_button_pressed() const     { return m_nFlags & (int)::user::e_button_state_middle; }
      bool is_x1_button_pressed() const         { return m_nFlags & (int)::user::e_button_state_x1; }
      bool is_x2_button_pressed() const         { return m_nFlags & (int)::user::e_button_state_x2; }

      void set_left_button_pressed()   { m_nFlags |= (int)::user::e_button_state_left;
      }
      void set_right_button_pressed() { m_nFlags |= (int)::user::e_button_state_right; }
      void set_shift_pressed() { m_nFlags |= (int)::user::e_button_state_shift; }
      void set_control_pressed() { m_nFlags |= (int)::user::e_button_state_control; }
      void set_middle_button_pressed() { m_nFlags |= (int)::user::e_button_state_middle; }
      void set_x1_button_pressed() { m_nFlags |= (int)::user::e_button_state_x1; }
      void set_x2_button_pressed() { m_nFlags |= (int)::user::e_button_state_x2; }

      void clear_left_button_pressed()    { m_nFlags &= (int)::user::e_button_state_left;
      }
      void clear_right_button_pressed() { m_nFlags &= (int)::user::e_button_state_right; }
      void clear_shift_pressed() { m_nFlags &= (int)::user::e_button_state_shift; }
      void clear_control_pressed() { m_nFlags &= (int)::user::e_button_state_control; }
      void clear_middle_button_pressed() { m_nFlags &= (int)::user::e_button_state_middle; }
      void clear_x1_button_pressed() { m_nFlags &= (int)::user::e_button_state_x1; }
      void clear_x2_button_pressed() { m_nFlags &= (int)::user::e_button_state_x2; }

   };


} // namespace user

