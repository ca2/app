// Created by camilo on 2022-03-18 19:55 <3ThomasBorregaardS�rensen!! (Thomas likes number 5!!)!!
#include "framework.h"


namespace appearance
{


   appearance::appearance()
   {

      m_bUsePreferredSize = true;

   }


   appearance::~appearance()
   {


   }


   bool appearance::call_click()
   {

      return false;

   }


   bool appearance::call_check(::enum_check echeck)
   {

      return false;

   }


   ::size_i32 appearance::preferred_size(::draw2d::graphics_pointer & pgraphics)
   {

      return {};

   }


   void appearance::perform_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void appearance::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void appearance::on_mouse_enter(const ::point_i32 & point)
   {


   }


   void appearance::on_mouse_leave()
   {


   }

   
   bool appearance::on_button_down(const ::point_i32 & point)
   {

      return false;

   }


   bool appearance::on_button_up(const ::point_i32 & point)
   {

      return false;

   }


   bool appearance::on_mouse_move(const ::point_i32 & point)
   {

      return false;

   }


   bool appearance::on_mouse_drag(const ::point_i32 & point)
   {

      return false;

   }

   
   bool appearance::on_key_down(::user::enum_key ekey)
   {

      return false;

   }


   bool appearance::on_key_up(::user::enum_key ekey)
   {

      return false;

   }


} // namespace appearance


