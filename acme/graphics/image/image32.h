// Refactored by camilo on 2023-06-09 19:06 <3ThomasBorregaardSorensen!!
// Merge with _image32.cpp From pixmap.h by
// camilo on 2023-10-09 12:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/graphics/draw2d/color.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"



struct CLASS_DECL_ACME image32_t
{


   union
   {

      unsigned int    m_u32;
      unsigned char     m_ua[4];

   };


   constexpr image32_t() { m_u32 = 0; }
   constexpr image32_t(::color::color color, color_indexes indexes);
   constexpr image32_t(const ::image32_t & image32) : m_u32(image32.m_u32) {}


   constexpr unsigned char u8_red(color_indexes indexes) const { return m_ua[indexes.red()]; }
   constexpr unsigned char u8_green(color_indexes indexes) const { return m_ua[indexes.green()]; }
   constexpr unsigned char u8_blue(color_indexes indexes) const { return m_ua[indexes.blue()]; }
   constexpr unsigned char u8_opacity(color_indexes indexes) const { return m_ua[indexes.opacity()]; }


   constexpr unsigned char & u8_red(color_indexes indexes) { return m_ua[indexes.red()]; }
   constexpr unsigned char & u8_green(color_indexes indexes) { return m_ua[indexes.green()]; }
   constexpr unsigned char & u8_blue(color_indexes indexes) { return m_ua[indexes.blue()]; }
   constexpr unsigned char & u8_opacity(color_indexes indexes) { return m_ua[indexes.opacity()]; }


   constexpr ::color::color color(color_indexes indexes) const;
   constexpr void assign(::color::color color, color_indexes indexes);

   constexpr bool operator == (const image32_t & image) const { return m_u32 == image.m_u32; }

   constexpr rgba_t rgb(color_indexes indexes) const { return { make_u32(u8_red(indexes), u8_green(indexes), u8_blue(indexes), 0) }; }



   inline ::color::color get_pixel(color_indexes indexes, int iScan, int iHeight, int x, int y);
   void vertical_swap_copy( int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
   inline void vertical_swap_copy(const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
   {
      vertical_swap_copy(size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
   }
   ::image32_t * offset(int x, int y, int iStrideDst)
   {
      return (::image32_t *)((unsigned char *)this + x * sizeof(::image32_t) + y * iStrideDst);

   }
   void copy(int x, int y, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
   {
      return offset(x, y, iStrideDst)->copy(cx, cy, iStrideDst, pimage32Src, iStrideSrc);
   }
   void copy(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
   inline void copy(const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
   {
      copy(size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
   }

   //void vertical_swap_copy(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   void vertical_swap_copy_swap_red_blue(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   inline void vertical_swap_copy_swap_red_blue(const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1)
   {
      vertical_swap_copy_swap_red_blue(size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
   }
   //void copy(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   //void copy(int x, int y, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   //void copy(const size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   inline void copy(const ::point_i32 & point, const size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1)
   {
      copy(point.x(), point.y(), size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
   }
   inline void copy(const ::rectangle_i32 & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1)
   {
      copy(rectangle.top_left(), rectangle.size(), iStrideDst, pimage32Src, iStrideSrc);
   }
   void copy_swap_red_blue(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   void _001ProperCopyColorref(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);

   inline void copy(const ::size_i32 & size, int iStrideDst, const ::pixmap * ppixmapSrc);


};


//
//#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD) || defined(OPENBSD)
//
//
//constexpr unsigned int argb_image32_u32(unsigned char u8Opacity, unsigned char u8Red, unsigned char u8Green, unsigned char u8Blue)
//{
//
//   return u8Blue
//      | ((unsigned short)(u8Green) << 8)
//      | (((unsigned int)(u8Red)) << 16)
//      | (((unsigned int)(u8Opacity)) << 24);
//
//}
//
//
////constexpr unsigned char image32_t::u8_red() const { return lower_u8(m_u32 >> 16); }
////constexpr unsigned char image32_t::u8_green() const { return lower_u8(m_u32 >> 8); }
////constexpr unsigned char image32_t::u8_blue()  const { return lower_u8(m_u32); }
////constexpr unsigned char image32_t::u8_opacity() const { return lower_u8(m_u32 >> 24); }
////
//
//#else
//
//
//constexpr unsigned int argb_image32_u32(unsigned char u8Opacity, unsigned char u8Red, unsigned char u8Green, unsigned char u8Blue)
//{
//
//   return u8Red
//      | (((unsigned short)u8Green) << 8)
//      | (((unsigned int)u8Blue) << 16)
//      | (((unsigned int)u8Opacity) << 24);
//
//}
//
////
////constexpr unsigned char image32_t::u8_red() const { return lower_u8(m_u32); }
////constexpr unsigned char image32_t::u8_green() const { return lower_u8(m_u32>>8)); }
////constexpr unsigned char image32_t::u8_blue()  const { return lower_u8(m_u32>>16)); }
////constexpr unsigned char image32_t::u8_opacity() const { return lower_u8(m_u32>>24)); }
//
//
//#endif


constexpr image32_t::image32_t(::color::color color, color_indexes indexes)
{

   assign(color, indexes);

}


constexpr ::color::color image32_t::color(color_indexes indexes) const
{

   return u8_opacity(indexes) == 0 ? ::color::transparent : rgba(u8_red(indexes) * 255 / u8_opacity(indexes), u8_green(indexes) * 255 / u8_opacity(indexes), u8_blue(indexes) * 255 / u8_opacity(indexes), u8_opacity(indexes));

}


constexpr void image32_t::assign(::color::color color, color_indexes indexes)
{

   u8_red(indexes) = color.m_u8Red * color.m_u8Opacity / 255;
   u8_green(indexes) = color.m_u8Green * color.m_u8Opacity / 255;
   u8_blue(indexes) = color.m_u8Blue * color.m_u8Opacity / 255;
   u8_opacity(indexes) = color.m_u8Opacity;

}










class color_array;


CLASS_DECL_ACME void colora_from_quada(color_array & colora, WINRGBQUAD * prgbquad, int iCount);


CLASS_DECL_ACME void vertical_swap(pixmap * ppixmap);



namespace draw2d
{


   CLASS_DECL_ACME void image_copy(::image::image *imagethis, ::image::image *pimage);
   CLASS_DECL_ACME void image_create(::particle * pparticle, ::image::image *& image);
   CLASS_DECL_ACME void image_create_image(::image::image *pimage, const size_i32 & size);
   CLASS_DECL_ACME unsigned int * image_get_data(::image::image *pimage);
   CLASS_DECL_ACME graphics * image_get_graphics(::image::image *pimage);


} // namespace draw2d


inline ::color::color image32_get_pixel(const ::image32_t * pdata, color_indexes indexes, int iScan, int iHeight, int x, int y)
{

   ::color::color color;

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((unsigned char*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   color = ((::image32_t *)&((unsigned char *)pdata)[iScan * y])[x].color(indexes);
   //
   //#endif

   return color;

}




//CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::point_i32 & point, const size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
//CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::rectangle_i32 & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);


//inline void copy_image32(::image32_t * pimage32Dst, const ::size_i32 & size, int iStrideDst, const ::pixmap * ppixmapSrc);



