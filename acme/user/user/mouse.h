//
//  user_mouse.hpp
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 14/08/17.
//
//
#pragma once



#include "acme/platform/message.h"
#include "acme/prototype/geometry2d/point.h"


namespace user
{


   class CLASS_DECL_ACME mouse :
      virtual public ::acme::message
   {
   protected:
      friend class ::user::interaction;
      ::pointer<::windowing::cursor>        m_pwindowingcursor;
   public:


      ::user::e_button_state                m_ebuttonstate;
      int_point                             m_pointHost;
      int_point                             m_pointAbsolute;
      int_point                             m_pointDesired;
      //bool                                m_bTranslated;
      ::pointer<::user::interaction>        m_puserinteractionHit;
      void *                                 m_pOsMouseDataOkIfOnStack = nullptr;

#ifdef _DEBUG

      huge_integer increment_reference_count() override;
      huge_integer decrement_reference_count() override;
      
#endif


      virtual unsigned int get_message()
      {
         return 0;
      }

      //bool has_screen_coordinates() const
      //{
      //   return m_pointScreen.x() != I32_MINIMUM
      //      && m_pointScreen.y() != I32_MINIMUM;

      //}

      bool is_left_button_pressed() const       { return m_ebuttonstate & (int) ::user::e_button_state_left; }
      bool is_right_button_pressed() const      { return m_ebuttonstate & (int)::user::e_button_state_right; }
      bool is_shift_pressed() const             { return m_ebuttonstate & (int)::user::e_button_state_shift; }
      bool is_control_pressed() const           { return m_ebuttonstate & (int)::user::e_button_state_control; }
      bool is_middle_button_pressed() const     { return m_ebuttonstate & (int)::user::e_button_state_middle; }
      bool is_x1_button_pressed() const         { return m_ebuttonstate & (int)::user::e_button_state_x1; }
      bool is_x2_button_pressed() const         { return m_ebuttonstate & (int)::user::e_button_state_x2; }

      void set_left_button_pressed()   { m_ebuttonstate |= ::user::e_button_state_left;
      }
      void set_right_button_pressed() { m_ebuttonstate |= ::user::e_button_state_right; }
      void set_shift_pressed() { m_ebuttonstate |= ::user::e_button_state_shift; }
      void set_control_pressed() { m_ebuttonstate |= ::user::e_button_state_control; }
      void set_middle_button_pressed() { m_ebuttonstate |= ::user::e_button_state_middle; }
      void set_x1_button_pressed() { m_ebuttonstate |= ::user::e_button_state_x1; }
      void set_x2_button_pressed() { m_ebuttonstate |= ::user::e_button_state_x2; }

      void clear_left_button_pressed()    { m_ebuttonstate &= ::user::e_button_state_left;
      }
      void clear_right_button_pressed() { m_ebuttonstate &= ::user::e_button_state_right; }
      void clear_shift_pressed() { m_ebuttonstate &= ::user::e_button_state_shift; }
      void clear_control_pressed() { m_ebuttonstate &= ::user::e_button_state_control; }
      void clear_middle_button_pressed() { m_ebuttonstate &= ::user::e_button_state_middle; }
      void clear_x1_button_pressed() { m_ebuttonstate &= ::user::e_button_state_x1; }
      void clear_x2_button_pressed() { m_ebuttonstate &= ::user::e_button_state_x2; }

      
      ::user::mouse & operator = (const ::user::mouse & mouse);


   };


} // namespace user

