// Created by camilo on 2022-10-23 01:38 <3ThomasBorregaardSørensen!!
#pragma once


inline string hex_color(const COLOR32 & c)
{

   string str;

   str.format("%02x%02x%02x", c.red, c.green, c.blue);

   return str;

}


inline string _hex_color(const COLOR32 & c)
{

   return "#" + hex_color(c);

}


string _hex_color(const ::color::color & color)
{

   return ::_hex_color(color);

}


string hex_color(const ::hex_color & color)
{

   return ::hex_color(color);

}



