// Created by camilo on 2022-10-23 01:38 <3ThomasBorregaardSørensen!!
#pragma once


inline string hex_color(const ::color::color & color)
{

   string str;

   str.format("%02x%02x%02x", color.red, color.green, color.blue);

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

   return ::string_format("%f %f %f %f", color.fr(), color.fg(), color.fb(), color.fa());

}


CLASS_DECL_ACME::color::color as_color(const ::scoped_string& scopedstr);


inline void from_string(::color::color& color, const ::scoped_string& scopedstr)
{

   color = ::as_color(scopedstr);

}


