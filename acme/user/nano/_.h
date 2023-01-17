//
// Created by camilo on 2022-10-24 08:45 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace nano
{


   class display;


} // namespace nano


class nano_device;
class nano_child;


class nano_window;


class nano_window_implementation;


class nano_brush;
class nano_pen;
class nano_font;


class nano_button;
class nano_still;


namespace nano
{


   CLASS_DECL_ACME ::pointer<nano_brush>create_solid_brush(::particle * pparticle, color32_t color);
   CLASS_DECL_ACME ::pointer<nano_font>create_point_font(::particle * pparticle, int iPoint, enum_font efont, bool bBold = false);
   CLASS_DECL_ACME ::pointer<nano_pen>create_pen(::particle * pparticle, int iWidth, color32_t color);


} // namespace nano



