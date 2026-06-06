//
// Created by camilo on 2022-10-24 08:45 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/reference_referer.h"



//
// enum enum_display_type
// {
//
//    e_display_type_none,
//    e_display_type_system = 100,
// #ifdef WITH_X11
//    e_display_type_x11 = 1000,
// #endif
// #ifdef WITH_XCB
//    e_display_type_xcb = 2000,
// #endif
// #ifdef HAS_WAYLAND
//    e_display_type_wayland = 3000,
// #endif
//
// };


namespace nano
{

namespace graphics
{





enum enum_pen
{
   e_pen_solid = 0, //PS_SOLID;
   e_pen_dashed = 1, //PS_DASH;
   e_pen_null =5, // PS_NULL;
};


      enum enum_line_cap
{

   e_line_cap_none,
   e_line_cap_round,

};



class graphics;


class context;
//class child;


  // class interchange;

//class window;


//class window_implementation;


class icon;
//class button;
//class still;

  // class display;

class brush;
class pen;
class font_family;
class font;

class image;

class path;

   //CLASS_DECL_ACME ::pointer<brush>create_solid_brush(::particle * pparticle, color32_t color);
   //CLASS_DECL_ACME ::pointer<font>create_point_font(::particle * pparticle, ::i32 iPoint, enum_font efont, bool bBold = false);
   


      //::enum_display_type get_display_type();

   enum enum_blend_mode
   {

      e_blend_mode_blend,
      e_blend_mode_copy,

   };

   enum enum_smoothing_mode
   {

      e_smoothing_mode_none,
      e_smoothing_mode_high_quality,

   };

   enum enum_text_rendering_hint
   {

      e_text_rendering_hint_none,
      e_text_rendering_hint_clear_type_grid_fit,

   };


   } //namespace graphics


} // namespace nano



