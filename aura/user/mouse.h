//
//  user_mouse.hpp
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 14/08/17.
//
//
#pragma once


namespace user
{


   class CLASS_DECL_AURA mouse
   {
   public:


      uptr                                m_nFlags;
      point_i32                           m_point;
      point_i32                           m_pointDesired;
      bool                                m_bTranslated;
      //enum_cursor                       m_ecursor;
      __pointer(::windowing::cursor)      m_pcursor;


      virtual unsigned int get_message()
      {
         return 0;
      }

      bool is_left_button_pressed() const { return m_nFlags & 1; }
      bool is_right_button_pressed() const { return m_nFlags & 2; }
      bool is_shift_pressed() const { return m_nFlags & 4; }
      bool is_control_pressed() const { return m_nFlags & 8; }
      bool is_middle_button_pressed() const { return m_nFlags & 16; }
      bool is_x1_button_pressed() const { return m_nFlags & 32; }
      bool is_x2_button_pressed() const { return m_nFlags & 64; }


   };


} // namespace user

