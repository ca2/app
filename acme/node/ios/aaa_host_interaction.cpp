//
//  ui_interaction.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//
#include "framework.h"
#include "_ios.h"


namespace ios
{


   host_interaction::host_interaction()
   {

      

   }


   host_interaction::~host_interaction()
   {


   }


   void host_interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      //return ::user::interaction::_001DrawThis(pgraphics);
      
      //pgraphics->fill_solid_rect_dim(10, 10, 100, 100, argb(255, 0, 0, 255));
      

   }


   void host_interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

//      pgraphics->fill_solid_rect_dim(10, 110, 100, 100, argb(255, 100, 155, 255));
//
//      pgraphics->fill_solid_rect_dim(10, 210, 100, 100, argb(255, 200, 225, 255));

      ::user::interaction::_001DrawChildren(pgraphics);
      

   }


   void host_interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_000OnDraw(pgraphics);

   }


   void host_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void host_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


   bool host_interaction::is_this_visible()
   {

      return true;

   }


   ::user::interaction * create_host_window()
   {
      
      return new host_interaction();
      
   }


} // namespace ios



