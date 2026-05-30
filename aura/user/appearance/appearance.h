// Created by camilo on 2022-03-18 19:47 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"


namespace appearance
{


   class CLASS_DECL_AURA appearance :
      virtual public object
   {
   public:


      bool                                   m_bUsePreferredSize;
      ::pointer<::user::interaction>         m_puserinteraction;
      ::i32_point                            m_pointMouseLast;
      ::i32_point                            m_pointLastCursor;
      ::message::message*                    m_pmessage;


      appearance();
      ~appearance() override;


      virtual void set_user_interaction(::user::interaction * puserinteraction);


      virtual bool call_click();
      virtual bool call_check(::enum_check echeck);

      virtual ::i32_size preferred_size(::draw2d::graphics_pointer & pointer);

      virtual void perform_layout(::draw2d::graphics_pointer & pointer);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_mouse_enter(const ::i32_point & point, bool bEnter);
      virtual void on_mouse_leave();

      virtual bool on_button_down(::user::e_key euserkeyMouseButton, const ::i32_point & point, bool bDoubleClick);
      virtual bool on_button_up(::user::e_key euserkeyMouseButton, const ::i32_point &point);

      virtual bool on_mouse_move(const ::i32_point & point);
      //virtual bool on_mouse_drag(const ::i32_point & point, const ::user::keyboard_state & keyboardstate);

      virtual bool on_scroll_event(const ::i32_point & point, ::f64 x, ::f64 y);

      virtual bool on_key_down(const ::user::e_key & ekey, ::i64 scancode, const ::scoped_string & scopedstrText);
      virtual bool on_key_up(const ::user::e_key & ekey, ::i64 scancode);

      virtual void on_character(::i32 iCharacter);


   };


} // namespace appearance



