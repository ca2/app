// Refactored by camilo on 2023-06-09 19:06 <3ThomasBorregaardSorensen!!
#pragma once


#include "color.h"


struct image32_t
{


   union
   {

      ::u32    m_u32;
      ::u8     m_ua[4];

   };


   constexpr image32_t() { m_u32 = 0; }
   constexpr image32_t(::color::color color, color_indexes indexes);
   constexpr image32_t(const ::image32_t & image32) : m_u32(image32.m_u32) {}


   constexpr ::u8 u8_red(color_indexes indexes) const { return m_ua[indexes.red()]; }
   constexpr ::u8 u8_green(color_indexes indexes) const { return m_ua[indexes.green()]; }
   constexpr ::u8 u8_blue(color_indexes indexes) const { return m_ua[indexes.blue()]; }
   constexpr ::u8 u8_opacity(color_indexes indexes) const { return m_ua[indexes.opacity()]; }


   constexpr ::u8 & u8_red(color_indexes indexes) { return m_ua[indexes.red()]; }
   constexpr ::u8 & u8_green(color_indexes indexes) { return m_ua[indexes.green()]; }
   constexpr ::u8 & u8_blue(color_indexes indexes) { return m_ua[indexes.blue()]; }
   constexpr ::u8 & u8_opacity(color_indexes indexes) { return m_ua[indexes.opacity()]; }


   constexpr ::color::color color(color_indexes indexes) const;
   constexpr void assign(::color::color color, color_indexes indexes);

   constexpr bool operator == (const image32_t & image) const { return m_u32 == image.m_u32; }

   constexpr rgba_t rgb(color_indexes indexes) const { return { make_u32(u8_red(indexes), u8_green(indexes), u8_blue(indexes), 0) }; }

};

//
//#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD)
//
//
//constexpr ::u32 argb_image32_u32(::u8 u8Opacity, ::u8 u8Red, ::u8 u8Green, ::u8 u8Blue)
//{
//
//   return u8Blue
//      | ((::u16)(u8Green) << 8)
//      | (((::u32)(u8Red)) << 16)
//      | (((::u32)(u8Opacity)) << 24);
//
//}
//
//
////constexpr ::u8 image32_t::u8_red() const { return lower_u8(m_u32 >> 16); }
////constexpr ::u8 image32_t::u8_green() const { return lower_u8(m_u32 >> 8); }
////constexpr ::u8 image32_t::u8_blue()  const { return lower_u8(m_u32); }
////constexpr ::u8 image32_t::u8_opacity() const { return lower_u8(m_u32 >> 24); }
////
//
//#else
//
//
//constexpr ::u32 argb_image32_u32(::u8 u8Opacity, ::u8 u8Red, ::u8 u8Green, ::u8 u8Blue)
//{
//
//   return u8Red
//      | (((::u16)u8Green) << 8)
//      | (((::u32)u8Blue) << 16)
//      | (((::u32)u8Opacity) << 24);
//
//}
//
////
////constexpr ::u8 image32_t::u8_red() const { return lower_u8(m_u32); }
////constexpr ::u8 image32_t::u8_green() const { return lower_u8(m_u32>>8)); }
////constexpr ::u8 image32_t::u8_blue()  const { return lower_u8(m_u32>>16)); }
////constexpr ::u8 image32_t::u8_opacity() const { return lower_u8(m_u32>>24)); }
//
//
//#endif


constexpr image32_t::image32_t(::color::color color, color_indexes indexes)
{

   assign(color, indexes);

}


constexpr ::color::color  image32_t::color(color_indexes indexes) const
{

   return rgba(u8_red(indexes), u8_green(indexes), u8_blue(indexes), u8_opacity(indexes));

}


constexpr void image32_t::assign(::color::color color, color_indexes indexes)
{

   u8_red(indexes) = color.m_u8Red;
   u8_green(indexes) = color.m_u8Green;
   u8_blue(indexes) = color.m_u8Blue;
   u8_opacity(indexes) = color.m_u8Opacity;

}



