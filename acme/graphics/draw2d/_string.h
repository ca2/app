// Created by camilo on 2022-10-23 01:38 <3ThomasBorregaardSorensen!!
#pragma once


inline string hex_color(const ::color::color & color)
{

   string str;

   str.format("%02x%02x%02x", color.u8_red(), color.u8_green(), color.u8_blue());

   return str;

}


string _hex_color(const ::color::color & color)
{

   return "#" + ::hex_color(color);

}


//string hex_color(const ::hex_color & color)
//{
//
//   return ::hex_color(color);
//
//}
//

inline ::string as_string(const ::color::color & color)
{

   return ::string_format("%f %f %f %f", color.f32_red(), color.f32_green(), color.f32_blue(), color.f32_opacity());

}


CLASS_DECL_ACME::color::color as_color(const ::scoped_string& scopedstr);


inline void from_string(::color::color& color, const ::scoped_string& scopedstr)
{

   color = ::as_color(scopedstr);

}


