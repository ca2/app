//
// Created by camilo on 2022-10-24 08:45 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/reference_referer.h"





namespace nano
{

namespace user
{

class user;


class device;
class child;


class window;


class window_implementation;



class button;
class still;

   class display;

class brush;
class pen;
class font;



   CLASS_DECL_ACME ::pointer<brush>create_solid_brush(::particle * pparticle, color32_t color);
   CLASS_DECL_ACME ::pointer<font>create_point_font(::particle * pparticle, int iPoint, enum_font efont, bool bBold = false);
   CLASS_DECL_ACME ::pointer<pen>create_pen(::particle * pparticle, int iWidth, color32_t color);


} //namespace user

} // namespace nano




enum enum_display_type
{

   e_display_type_none,
   e_display_type_system = 100,
#ifdef WITH_X11
   e_display_type_x11 = 1000,
#endif
#ifdef WITH_XCB
   e_display_type_xcb = 2000,
#endif
#ifdef HAS_WAYLAND
   e_display_type_wayland = 3000,
#endif

};


enum_display_type get_display_type();



