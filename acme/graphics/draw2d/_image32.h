// Refactored by camilo on 2023-06-09 19:06 <3ThomasBorregaardSorensen!!
#pragma once


#include "color.h"


struct image32_t
{


   ::u32 m_u32;


   constexpr image32_t() { m_u32 = 0; }
   constexpr image32_t(const ::color::color & color);
   constexpr image32_t(const ::image32_t & image32) : m_u32(image32.m_u32) {}


   constexpr ::u8 u8_red() const;
   constexpr ::u8 u8_green() const;
   constexpr ::u8 u8_blue() const;
   constexpr ::u8 u8_opacity() const;

   constexpr operator ::color::color() const;

   constexpr bool operator==(const image32_t & image32) const { return m_u32 == image32.m_u32; }

   constexpr ::u32 rgb() const { return make_u32(u8_red(), u8_green(), u8_blue(), 255); }

};


#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD)


constexpr ::u32 argb_image32_u32(::u8 u8Opacity, ::u8 u8Red, ::u8 u8Green, ::u8 u8Blue)
{

   return u8Blue
      | ((::u16)(u8Green) << 8)
      | (((::u32)(u8Red)) << 16)
      | (((::u32)(u8Opacity)) << 24);

}


constexpr ::u8 image32_t::u8_red() const { return lower_u8(m_u32 >> 16); }
constexpr ::u8 image32_t::u8_green() const { return lower_u8(m_u32 >> 8); }
constexpr ::u8 image32_t::u8_blue()  const { return lower_u8(m_u32); }
constexpr ::u8 image32_t::u8_opacity() const { return lower_u8(m_u32 >> 24); }


#else


constexpr ::u32 argb_image32_u32(::u8 u8Opacity, ::u8 u8Red, ::u8 u8Green, ::u8 u8Blue)
{

   return u8Red
      | (((::u16)u8Green) << 8)
      | (((::u32)u8Blue) << 16)
      | (((::u32)u8Opacity) << 24);

}


constexpr ::u8 image32_t::u8_red() const { return lower_u8(m_u32); }
constexpr ::u8 image32_t::u8_green() const { return lower_u8(m_u32>>8)); }
constexpr ::u8 image32_t::u8_blue()  const { return lower_u8(m_u32>>16)); }
constexpr ::u8 image32_t::u8_opacity() const { return lower_u8(m_u32>>24)); }


#endif


constexpr image32_t::image32_t(const ::color::color & color)
{

   m_u32 = argb_image32_u32(color.m_u8Opacity, color.m_u8Red, color.m_u8Green, color.m_u8Blue);

}


constexpr image32_t::operator ::color::color() const
{

   return rgba(u8_red(), u8_green(), u8_blue(), u8_opacity());

}



