// Created by camilo on 2022-03-18 19:55 <3ThomasBorregaardSorensen!! (Thomas likes number 5!!)!!
#include "framework.h"

#include "appearance.h"
#include "aura/user/user/interaction.h"


namespace appearance
{


   appearance::appearance()
   {

      m_bUsePreferredSize = true;
      m_pmessage = nullptr;

   }


   appearance::~appearance()
   {


   }


   void appearance::set_user_interaction(::user::interaction * puserinteraction)
   {

      m_puserinteraction = puserinteraction;

   }


   bool appearance::call_click()
   {

      return false;

   }


   bool appearance::call_check(::enum_check echeck)
   {

      return false;

   }


   ::int_size appearance::preferred_size(::draw2d::graphics_pointer & pgraphics)
   {

      return {};

   }


   void appearance::perform_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void appearance::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void appearance::on_mouse_enter(const ::int_point & point, const ::user::e_key & ekeyModifiers)
   {


   }


   void appearance::on_mouse_leave()
   {


   }

   
   bool appearance::on_button_down(::user::e_key ekeyButton, const ::int_point & point, const ::user::e_key & ekeyModifiers, bool bDoubleClick)
   {

      return false;

   }


   bool appearance::on_button_up(::user::e_key ekeyButton, const ::int_point & point, const ::user::e_key & ekeyModifiers)
   {

      return false;

   }


   bool appearance::on_mouse_move(const ::int_point & point, bool bDown, const ::user::e_key & ekeyModifiers)
   {

      return false;

   }


   //bool appearance::on_mouse_drag(const ::int_point & point, const ::user::e_key & ekeyModifiers)
   //{

   //   return false;

   //}


   bool appearance::on_scroll_event(const ::int_point & point, double x, double y)
   {

      return false;

   }

   
   bool appearance::on_key_down(::user::enum_key ekey, long long scancode, const ::user::e_key & ekeyModifiers, const ::scoped_string & scopedstrText)
   {

      return false;

   }


   bool appearance::on_key_up(::user::enum_key ekey, long long scancode, const ::user::e_key & ekeyModifiers)
   {

      return false;

   }


   void appearance::on_character(int iCharacter)
   {

   }


} // namespace appearance



