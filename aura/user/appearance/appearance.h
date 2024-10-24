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
      ::point_i32                            m_pointMouseLast;
      ::point_i32                            m_pointLastCursor;
      ::message::message*                    m_pmessage;


      appearance();
      ~appearance() override;


      virtual void set_user_interaction(::user::interaction * puserinteraction);


      virtual bool call_click();
      virtual bool call_check(::enum_check echeck);

      virtual ::size_i32 preferred_size(::draw2d::graphics_pointer & pointer);

      virtual void perform_layout(::draw2d::graphics_pointer & pointer);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_mouse_enter(const ::point_i32 & point, const ::user::e_key & ekeyModifiers);
      virtual void on_mouse_leave();

      virtual bool on_button_down(::user::e_key ekeyButton, const ::point_i32 & point, const ::user::e_key & ekeyModifiers, bool bDoubleClick);
      virtual bool on_button_up(::user::e_key ekeyButton, const ::point_i32 & point, const ::user::e_key & ekeyModifiers);

      virtual bool on_mouse_move(const ::point_i32 & point, bool bDown, const ::user::e_key & ekeyModifiers);
      //virtual bool on_mouse_drag(const ::point_i32 & point, const ::user::e_key & ekeyModifiers);

      virtual bool on_scroll_event(const ::point_i32 & point, double x, double y);

      virtual bool on_key_down(::user::enum_key ekey, ::i64 scancode, const ::user::e_key & ekeyModifiers, const ::string & strText);
      virtual bool on_key_up(::user::enum_key ekey, ::i64 scancode, const ::user::e_key & ekeyModifiers);

      virtual void on_character(int iCharacter);


   };


} // namespace appearance



