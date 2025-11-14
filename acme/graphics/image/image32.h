// Refactored by camilo on 2023-06-09 19:06 <3ThomasBorregaardSorensen!!
// Merge with _image32.cpp From pixmap.h by
// camilo on 2023-10-09 12:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/graphics/draw2d/color.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"



namespace image
{


   enum enum_copy_disposition
   {

      e_copy_disposition_none,
      e_copy_disposition_y_swap,

   };


} // namespace image


struct CLASS_DECL_ACME image32_t
{


   union
   {

      unsigned int    m_ui;
      unsigned char     m_ua[4];

   };


   constexpr image32_t() { m_ui = 0; }
   constexpr image32_t(::color::color color, color_indexes indexes);
   constexpr image32_t(const ::image32_t & image32) : m_ui(image32.m_ui) {}


   constexpr unsigned char byte_red(color_indexes indexes) const { return m_ua[indexes.red()]; }
   constexpr unsigned char byte_green(color_indexes indexes) const { return m_ua[indexes.green()]; }
   constexpr unsigned char byte_blue(color_indexes indexes) const { return m_ua[indexes.blue()]; }
   constexpr unsigned char byte_opacity(color_indexes indexes) const { return m_ua[indexes.opacity()]; }


   constexpr unsigned char & byte_red(color_indexes indexes) { return m_ua[indexes.red()]; }
   constexpr unsigned char & byte_green(color_indexes indexes) { return m_ua[indexes.green()]; }
   constexpr unsigned char & byte_blue(color_indexes indexes) { return m_ua[indexes.blue()]; }
   constexpr unsigned char & byte_opacity(color_indexes indexes) { return m_ua[indexes.opacity()]; }


   constexpr ::color::color color(color_indexes indexes) const;
   constexpr void assign(::color::color color, color_indexes indexes);

   constexpr ::color::color raw_color(color_indexes indexes) const;
   constexpr void raw_assign(::color::color color, color_indexes indexes);

   constexpr bool operator == (const image32_t & image) const { return m_ui == image.m_ui; }

   constexpr rgba_t rgb(color_indexes indexes) const { return { make_unsigned_int(byte_red(indexes), byte_green(indexes), byte_blue(indexes), 0) }; }



   inline ::color::color get_pixel(color_indexes indexes, int iScan, int iHeight, int x, int y);
   void vertical_swap_copy( int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
   inline void vertical_swap_copy(const ::int_size & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
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
   inline void copy(const ::int_size & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
   {
      copy(size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
   }

   //void vertical_swap_copy(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   void vertical_swap_copy_swap_red_blue(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   inline void vertical_swap_copy_swap_red_blue(const ::int_size & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1)
   {
      vertical_swap_copy_swap_red_blue(size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
   }
   //void copy(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   //void copy(int x, int y, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   //void copy(const int_size & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   inline void copy(const ::int_point & point, const int_size & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1)
   {
      copy(point.x, point.y, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
   }
   inline void copy(const ::int_rectangle & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1)
   {
      copy(rectangle.top_left(), rectangle.size(), iStrideDst, pimage32Src, iStrideSrc);
   }
   inline void copy(const ::pixmap* p);
   void copy_swap_red_blue(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
   void _001ProperCopyColorref(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);

   inline void copy(const ::int_size & size, int iStrideDst, const ::pixmap * ppixmapSrc);

   void set_rectangle(int x, int y, int w, int h, int s, const ::image32_t & source);
   void blend_rectangle(int x, int y, int w, int h, int s, const ::image32_t & source);


};


//
//#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD) || defined(OPENBSD)
//
//
//constexpr unsigned int argb_image32_unsigned_int(unsigned char u8Opacity, unsigned char u8Red, unsigned char u8Green, unsigned char u8Blue)
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
////constexpr unsigned char image32_t::byte_red() const { return lower_byte(m_ui >> 16); }
////constexpr unsigned char image32_t::byte_green() const { return lower_byte(m_ui >> 8); }
////constexpr unsigned char image32_t::byte_blue()  const { return lower_byte(m_ui); }
////constexpr unsigned char image32_t::byte_opacity() const { return lower_byte(m_ui >> 24); }
////
//
//#else
//
//
//constexpr unsigned int argb_image32_unsigned_int(unsigned char u8Opacity, unsigned char u8Red, unsigned char u8Green, unsigned char u8Blue)
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
////constexpr unsigned char image32_t::byte_red() const { return lower_byte(m_ui); }
////constexpr unsigned char image32_t::byte_green() const { return lower_byte(m_ui>>8)); }
////constexpr unsigned char image32_t::byte_blue()  const { return lower_byte(m_ui>>16)); }
////constexpr unsigned char image32_t::byte_opacity() const { return lower_byte(m_ui>>24)); }
//
//
//#endif


constexpr image32_t::image32_t(::color::color color, color_indexes indexes)
{

   assign(color, indexes);

}


constexpr ::color::color image32_t::color(color_indexes indexes) const
{

   return byte_opacity(indexes) == 0 ? ::color::transparent : rgba(byte_red(indexes) * 255 / byte_opacity(indexes), byte_green(indexes) * 255 / byte_opacity(indexes), byte_blue(indexes) * 255 / byte_opacity(indexes), byte_opacity(indexes));

}


constexpr void image32_t::assign(::color::color color, color_indexes indexes)
{

   byte_red(indexes) = color.m_uchRed * color.m_uchOpacity / 255;
   byte_green(indexes) = color.m_uchGreen * color.m_uchOpacity / 255;
   byte_blue(indexes) = color.m_uchBlue * color.m_uchOpacity / 255;
   byte_opacity(indexes) = color.m_uchOpacity;

}


constexpr ::color::color image32_t::raw_color(color_indexes indexes) const
{

   return rgba(byte_red(indexes), byte_green(indexes), byte_blue(indexes), byte_opacity(indexes));

}


constexpr void image32_t::raw_assign(::color::color color, color_indexes indexes)
{

   byte_red(indexes) = color.m_uchRed;
   byte_green(indexes) = color.m_uchGreen;
   byte_blue(indexes) = color.m_uchBlue;
   byte_opacity(indexes) = color.m_uchOpacity;

}










class color_array;


CLASS_DECL_ACME void colora_from_quada(color_array & colora, WINRGBQUAD * prgbquad, int iCount);


CLASS_DECL_ACME void vertical_swap(pixmap * ppixmap);



namespace draw2d
{


   CLASS_DECL_ACME void image_copy(::image::image *imagethis, ::image::image *pimage);
   CLASS_DECL_ACME void image_create(::particle * pparticle, ::image::image *& image);
   CLASS_DECL_ACME void image_create_image(::image::image *pimage, const int_size & size);
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

inline void image32_set_pixel(const ::image32_t * pdata, color_indexes indexes, int iScan, int iHeight, int x, int y, ::color::color color)
{

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((unsigned char*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   ((::image32_t *)&((unsigned char *)pdata)[iScan * y])[x].assign(color, indexes);
   //
   //#endif


}


inline ::color::color image32_raw_pixel(const ::image32_t * pdata, color_indexes indexes, int iScan, int iHeight, int x, int y)
{

   ::color::color color;

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((unsigned char*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   color = ((::image32_t *)&((unsigned char *)pdata)[iScan * y])[x].raw_color(indexes);
   //
   //#endif

   return color;

}

inline void image32_set_raw_pixel(const ::image32_t * pdata, color_indexes indexes, int iScan, int iHeight, int x, int y, ::color::color color)
{

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((unsigned char*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   ((::image32_t *)&((unsigned char *)pdata)[iScan * y])[x].raw_assign(color, indexes);
   //
   //#endif


}

//CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::int_point & point, const int_size & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
//CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::int_rectangle & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);


//inline void copy_image32(::image32_t * pimage32Dst, const ::int_size & size, int iStrideDst, const ::pixmap * ppixmapSrc);


using image32_callback = ::function< void(const ::image32_t*, int, int, int) >;




