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

   constexpr ::color::color raw_color(color_indexes indexes) const;
   constexpr void raw_assign(::color::color color, color_indexes indexes);

   constexpr bool operator == (const image32_t & image) const { return m_u32 == image.m_u32; }

   constexpr rgba_t rgb(color_indexes indexes) const { return { make_u32(u8_red(indexes), u8_green(indexes), u8_blue(indexes), 0) }; }



   inline ::color::color get_pixel(color_indexes indexes, ::i32 iScan, ::i32 iHeight, ::i32 x, ::i32 y);
   void vertical_swap_copy( ::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc);
   inline void vertical_swap_copy(const ::i32_size & size, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc)
   {
      vertical_swap_copy(size.cx, size.cy, iStrideDst, pimage32Src, iStrideSrc);
   }
   ::image32_t * offset(::i32 x, ::i32 y, ::i32 iStrideDst)
   {
      return (::image32_t *)((::u8 *)this + x * sizeof(::image32_t) + y * iStrideDst);

   }
   void copy(::i32 x, ::i32 y, ::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc)
   {
      return offset(x, y, iStrideDst)->copy(cx, cy, iStrideDst, pimage32Src, iStrideSrc);
   }
   void copy(::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc);
   inline void copy(const ::i32_size & size, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc)
   {
      copy(size.cx, size.cy, iStrideDst, pimage32Src, iStrideSrc);
   }

   //void vertical_swap_copy(::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1);
   void vertical_swap_copy_swap_red_blue(::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1);
   inline void vertical_swap_copy_swap_red_blue(const ::i32_size & size, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1)
   {
      vertical_swap_copy_swap_red_blue(size.cx, size.cy, iStrideDst, pimage32Src, iStrideSrc);
   }
   //void copy(::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1);
   //void copy(::i32 x, ::i32 y, ::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1);
   //void copy(const i32_size & size, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1);
   inline void copy(const ::i32_point & point, const i32_size & size, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1)
   {
      copy(point.x, point.y, size.cx, size.cy, iStrideDst, pimage32Src, iStrideSrc);
   }
   inline void copy(const ::i32_rectangle & rectangle, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1)
   {
      copy(rectangle.top_left(), rectangle.size(), iStrideDst, pimage32Src, iStrideSrc);
   }
   inline void copy(const ::pixmap_t *p);
   void copy_swap_red_blue(::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1);
   void swap_red_blue(::i32 cx, ::i32 cy, ::i32 iStride = 0);
   void _001ProperCopyColorref(::i32 cx, ::i32 cy, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc = -1);

   inline void copy(const ::i32_size &size, ::i32 iStrideDst, const ::pixmap_t *ppixmapSrc);

   void set_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, ::i32 s, const ::image32_t & source);
   void blend_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, ::i32 s, const ::image32_t & source);


   void copy_3_channel_data(const ::i32_size & size, ::i32 stride, const void * pdata, ::i32 inputStride);

   void copy_1_channel_data(const ::i32_size & size, ::i32 stride, const void * pdata, ::i32 inputStride);


   static image32_t * create_copy_of(
      ::memory &memoryAllocation, 
      const i32_size & size, 
      ::i32 stride,
      const void *pdata, 
      ::i32 channels, 
      ::i32 inputStride = -1);


};


//
//#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD) || defined(OPENBSD)
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
////constexpr ::u8 image32_t::u8_red() const { return lower_byte(m_u32 >> 16); }
////constexpr ::u8 image32_t::u8_green() const { return lower_byte(m_u32 >> 8); }
////constexpr ::u8 image32_t::u8_blue()  const { return lower_byte(m_u32); }
////constexpr ::u8 image32_t::u8_opacity() const { return lower_byte(m_u32 >> 24); }
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
////constexpr ::u8 image32_t::u8_red() const { return lower_byte(m_u32); }
////constexpr ::u8 image32_t::u8_green() const { return lower_byte(m_u32>>8)); }
////constexpr ::u8 image32_t::u8_blue()  const { return lower_byte(m_u32>>16)); }
////constexpr ::u8 image32_t::u8_opacity() const { return lower_byte(m_u32>>24)); }
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


constexpr ::color::color image32_t::raw_color(color_indexes indexes) const
{

   return rgba(u8_red(indexes), u8_green(indexes), u8_blue(indexes), u8_opacity(indexes));

}


constexpr void image32_t::raw_assign(::color::color color, color_indexes indexes)
{

   u8_red(indexes) = color.m_u8Red;
   u8_green(indexes) = color.m_u8Green;
   u8_blue(indexes) = color.m_u8Blue;
   u8_opacity(indexes) = color.m_u8Opacity;

}










class color_array;


CLASS_DECL_ACME void colora_from_quada(color_array & colora, WINRGBQUAD * prgbquad, ::i32 iCount);


CLASS_DECL_ACME void vertical_swap(pixmap_t *ppixmap);



namespace draw2d
{


   CLASS_DECL_ACME void image_copy(::image::image *imagethis, ::image::image *pimage);
   CLASS_DECL_ACME void image_create(::particle * pparticle, ::image::image *& image);
   CLASS_DECL_ACME void image_create_image(::image::image *pimage, const i32_size & size);
   CLASS_DECL_ACME ::u32 * image_get_data(::image::image *pimage);
   CLASS_DECL_ACME graphics * image_get_graphics(::image::image *pimage);


} // namespace draw2d


inline ::color::color image32_get_pixel(const ::image32_t * pdata, color_indexes indexes, ::i32 iScan, ::i32 iHeight, ::i32 x, ::i32 y)
{

   ::color::color color;

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((::u8*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   color = ((::image32_t *)&((::u8 *)pdata)[iScan * y])[x].color(indexes);
   //
   //#endif

   return color;

}

inline void image32_set_pixel(const ::image32_t * pdata, color_indexes indexes, ::i32 iScan, ::i32 iHeight, ::i32 x, ::i32 y, ::color::color color)
{

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((::u8*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   ((::image32_t *)&((::u8 *)pdata)[iScan * y])[x].assign(color, indexes);
   //
   //#endif


}


inline ::color::color image32_raw_pixel(const ::image32_t * pdata, color_indexes indexes, ::i32 iScan, ::i32 iHeight, ::i32 x, ::i32 y)
{

   ::color::color color;

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((::u8*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   color = ((::image32_t *)&((::u8 *)pdata)[iScan * y])[x].raw_color(indexes);
   //
   //#endif

   return color;

}

inline void image32_set_raw_pixel(const ::image32_t * pdata, color_indexes indexes, ::i32 iScan, ::i32 iHeight, ::i32 x, ::i32 y, ::color::color color)
{

   //#ifdef __APPLE__
   //
   //      color = ((::image32_t*)&((::u8*)pdata)[iScan * (iHeight - y - 1)])[x];
   //
   //#else
   //
   ((::image32_t *)&((::u8 *)pdata)[iScan * y])[x].raw_assign(color, indexes);
   //
   //#endif


}

//CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::i32_point & point, const i32_size & size, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc);
//CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::i32_rectangle & rectangle, ::i32 iStrideDst, const ::image32_t * pimage32Src, ::i32 iStrideSrc);


//inline void copy_image32(::image32_t * pimage32Dst, const ::i32_size & size, ::i32 iStrideDst, const ::pixmap * ppixmapSrc);


using image32_callback = ::function< void(const ::image32_t*, ::i32, ::i32, ::i32) >;




