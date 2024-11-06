// Refactored form _opengl.h by camilo on 2023-06-09 20:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/graphics/image/image32.h"


namespace opengl
{



   inline void color(unsigned char u8Red, unsigned char u8Green, unsigned char u8Blue, unsigned char u8Opacity)
   {

      //auto fr = (float)r * (float)a / 65355.f;
      //auto fg = (float)g * (float)a / 65355.f;
      //auto fb = (float)b * (float)a / 65355.f;
      //auto f32Red = (float)(u8Red * u8Opacity) / (255.f * 255.f);
      //auto f32Green = (float)(u8Green * u8Opacity) / (255.f * 255.f);
      //auto f32Blue = (float)(u8Blue * u8Opacity) / (255.f * 255.f);
      auto f32Red = (float)(u8Red) / (255.f);
      auto f32Green = (float)(u8Green) / (255.f);
      auto f32Blue = (float)(u8Blue) / (255.f);
      auto f32Opacity = (float)u8Opacity / 255.f;

      ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);

   }



   inline void color(const ::color::color & color)
   {

      ::opengl::color(
         color.m_u8Red,
         color.m_u8Green,
         color.m_u8Blue,
         color.m_u8Opacity);

   }


} // namespace opengl


inline void opengl_color(::color::color color)
{

   ::opengl::color(
      color.u8_red(),
      color.u8_green(),
      color.u8_blue(),
      color.u8_opacity());

}



