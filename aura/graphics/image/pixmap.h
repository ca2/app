#pragma once


#include "header.h"
#include "acme/graphics/draw2d/image32.h"
#include "acme/graphics/image/_configuration.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/primitive/primitive/concrete.h"


namespace draw2d
{


   inline ::color::color get_pixel(const ::image32_t* pdata, color_indexes indexes, int iScan, int iHeight, int x, int y);


} // namespace draw2d


#define __sizeof(TYPE) ((memsize)sizeof(TYPE))


#pragma pack(push, pixmap)

// POD

#ifdef __cplusplus
struct CLASS_DECL_AURA pixmap :
   public image_header
#else
struct pixmap
#endif
{


#ifndef __cplusplus
   struct image_header           m_header;
#endif

   i32                           m_iRedLower;
   i32                           m_iScan;
   ::image32_t *                 m_pimage32;
   ::point_i32                   m_point;
   ::image32_t *                 m_pimage32Raw;
   ::size_i32                    m_sizeRaw;
   ::color_indexes               m_colorindexes = common_system_image_color_indexes();
   mutable bool                  m_bTrans; // optionally used by implementation
   mutable bool                  m_bMapped; // optionally used by implementation
   bool                          m_bReduced; // optionally used by implementation


#ifdef __cplusplus

   pixmap()
   {

#if defined(FREEBSD) || (defined(UNIVERSAL_WINDOWS) && OSBIT == 32)
      m_iRedLower = 0;
#else
      m_iRedLower = 1;
#endif
      m_iScan = 0;
      m_pimage32 = nullptr;
      m_pimage32Raw = nullptr;
      m_bMapped = false;
      m_bReduced = false;
      m_bTrans = false;
      
   }


   void clear()
   {

      reset();

      m_iScan = 0;
      m_pimage32 = nullptr;
      m_pimage32Raw = nullptr;

   }


   void init(const ::size_i32 & size, ::image32_t * pimage32, i32 iScan)
   {

      m_size = size;

      m_sizeRaw = size;

      m_pimage32Raw = pimage32;

      m_iScan = iScan;

      m_point.Null();

      map();

   }



   int scan_size() const { return m_iScan; }

   inline ::image32_t * image32() { return m_pimage32; }
   inline ::image32_t * image32() const { return m_pimage32; }

   inline operator pixmap * () { return this; }
   inline operator const pixmap * () const { return this; }


   inline bool is_ok() const { return ::is_set(this) && area() > 0; }

   inline ::rectangle_i32 rectangle() const { return ::rectangle_i32(m_point, m_size); }

   inline ::rectangle_i32 rectangle(const ::point_i32 & point) const { return ::rectangle_i32(point, m_size); }

   inline ::point_i32 top_left() const noexcept { return m_point; }
   inline ::point_i32 origin() const noexcept { return top_left(); }
   //inline concrete < ::size_i32 > size() const noexcept { return m_size; }
   inline ::size_i32 size() const noexcept { return m_size;  }
   inline int width() const noexcept { return m_size.cx(); }
   inline int height() const noexcept { return m_size.cy(); }
   inline int area() const noexcept { return m_size.area(); }
   inline int scan_area() const noexcept { return height() * scan_size(); }


   inline ::color::color get_pixel(int x, int y) const
   {

      return ::draw2d::get_pixel(image32(), m_colorindexes, scan_size(), height(), x, y);

   }


   inline ::color::color get_pixel(const ::point_i32 & point) const { return get_pixel(point.x(), point.y()); }

   inline pixmap & operator =(const pixmap & pixmap);
   inline pixmap & operator =(const ::rectangle_i32 & rectangle) { map(rectangle);  return *this; }



   void map(const ::rectangle_i32 & rectangle)
   {

      m_point = rectangle.origin();

      m_size = rectangle.size();

      map();

   }

   void map() const
   {

      if (::is_set(m_pimage32Raw))
      {

         ((pixmap *)this)->m_pimage32 = m_pimage32Raw + (m_point.x() + m_iScan * m_point.y());

      }

   }

   void unmap()
   {

      m_pimage32 = m_pimage32Raw;
      m_size = m_sizeRaw;

   }


};



   //class CLASS_DECL_AURA pixmap :
   //   public bitmap
   //{
   //public:
   //
   //
   //   ::bitmap          m_bitmapMap;
   //   ::bitmap *        m_pbitmapMap;
   //
   //   pixmap()
   //   {
   //      reset();
   //   }
   //
   //
   //   ::rectangle_i32 map(::rectangle_i32 rectangleNew)
   //   {
   //
   //      auto rectanglePrevious = rectangle_i32();
   //
   //      operator =(rectangleNew);
   //
   //      return rectanglePrevious;
   //
   //   }
   //
   //
   //   void unmap(::rectangle_i32 rectanglePrevious)
   //   {
   //
   //      operator =(rectanglePrevious);
   //
   //   }
   //
   //   inline ::image32_t* image32() { return m_pbitmapMap->image32(); }
   //   inline const ::image32_t* image32() const { return m_pbitmapMap->image32(); }
   //
   //   inline operator bitmap* () { return m_pbitmapMap; }
   //   inline operator const bitmap* () const { return m_pbitmapMap; }
   //
   //   inline ::color::color get_pixel(int x, int y) { m_pbitmapMap->get_pixel(x, y); }
   //   inline ::color::color get_pixel(const ::point_i32& point) { m_pbitmapMap->get_pixel(point); }
   //
   //
   //   inline bool is_ok() const { return m_pbitmapMap->is_ok(); }
   //
   //
   //   inline ::rectangle_i32 rectangle() const { return m_pbitmapMap->rectangle(); }
   //
   //
   //   pixmap& operator = (const ::rectangle_i32& rectangle) { m_point = rectangle.origin(); m_size = rectangle.size(); return *this; }
   //
   //
   //   inline ::rectangle_i32 rectangle(const point_i32 & point = {}) const { return m_pbitmapMap->rectangle(point); }
   //
   //   pixmap& operator =(const pixmap& pixmap);
   //
   //   inline ::rectangle_i32 rectangle() const { return m_pbitmapMap->rectangle(); }
   //
   //
   //   inline ::point_i32 top_left() const noexcept { return m_pbitmapMap->top_left(); }
   //   inline ::point_i32 origin() const noexcept { return m_pbitmapMap->top_left(); }
   //   inline ::size_i32 size() const noexcept { return m_pbitmapMap->size(); }
   //   inline int width() const noexcept { return m_pbitmapMap->width(); }
   //   inline int height() const noexcept { return m_pbitmapMap->height(); }
   //   inline int area() const noexcept { return m_pbitmapMap->area(); }
   //
   //   void reset() { m_pbitmapMap = this; }
   //
   //
   //};



   class pixmap_lock
   {
   public:


      pixmap * m_pbitmap;
      ::rectangle_i32      m_rectanglePrevious;
      bool        m_bMapped;


      pixmap_lock() { }


      pixmap_lock(pixmap * pmap, rectangle_i32 rectangle) :
         m_pbitmap(pmap)
      {

         map(rectangle);

      }


      pixmap_lock(pixmap * pmap) :
         m_pbitmap(pmap)
      {

      }


      ~pixmap_lock()
      {

         unmap();

      }

      bool map(::rectangle_i32 rectangleMap)
      {

         if (m_bMapped)
         {

            return false;

         }

         m_rectanglePrevious = m_pbitmap->rectangle();

         m_pbitmap->map(rectangleMap);

         m_bMapped = true;

         return true;

      }


      bool unmap()
      {

         if (!m_bMapped)
         {

            return false;

         }

         m_pbitmap->map(m_rectanglePrevious);

         m_bMapped = false;

         return true;

      }

#endif

};

#pragma pack(pop, pixmap)











CLASS_DECL_AURA void vertical_swap_copy_image32(::image32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, int x, int y, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);


CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);





CLASS_DECL_AURA void colora_from_quada(color_array & colora, WINRGBQUAD * prgbquad, int iCount);


CLASS_DECL_AURA void vertical_swap(pixmap * ppixmap);
CLASS_DECL_AURA void vertical_swap_copy_image32(::image32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void vertical_swap_copy_image32_swap_red_blue(::image32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, int x, int y, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::point_i32 & point, const size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::rectangle_i32 & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void copy_image32_swap_red_blue(::image32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);
CLASS_DECL_AURA void _001ProperCopyColorref(::image32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc = -1);



namespace draw2d
{


   CLASS_DECL_AURA void image_copy(::image * imagethis, ::image * pimage);
   CLASS_DECL_AURA void image_create(::particle * pparticle, ::image *& image);
   CLASS_DECL_AURA void image_create_image(::image * pimage, const size_i32 & size);
   CLASS_DECL_AURA unsigned int * image_get_data(::image * pimage);
   CLASS_DECL_AURA graphics * image_get_graphics(::image * pimage);


} // namespace draw2d


CLASS_DECL_AURA enum_rotate_flip exif_orientation_rotate_flip(int orientation);


CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::point_i32 & point, const size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);
CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::rectangle_i32 & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc);


namespace draw2d
{


   inline ::color::color get_pixel(const ::image32_t* pdata, color_indexes indexes, int iScan, int iHeight, int x, int y)
   {

      ::color::color color;

//#ifdef __APPLE__
//
//      color = ((::image32_t*)&((u8*)pdata)[iScan * (iHeight - y - 1)])[x];
//
//#else
//
      color = ((::image32_t *)&((u8*)pdata)[iScan * y])[x].color(indexes);
//
//#endif

      return color;

   }


} // namespace draw2d


#ifdef __cplusplus


inline void copy_image32(::image32_t* pimage32Dst, const ::size_i32& size, int iStrideDst, const ::pixmap* ppixmapSrc)
{

   copy_image32(pimage32Dst, size, iStrideDst, ppixmapSrc->image32(), ppixmapSrc->scan_size());

}


inline void copy_image32(::pixmap* ppixmapDst, const ::size_i32& size, const ::pixmap* ppixmapSrc)
{

   copy_image32(ppixmapDst->image32(), size, ppixmapDst->scan_size(), ppixmapSrc);

}


inline void copy_image32(::pixmap* ppixmapDst, const ::pixmap* ppixmapSrc)
{

   copy_image32(ppixmapDst, ppixmapDst->size().minimum(ppixmapSrc->size()), ppixmapSrc);

}


inline pixmap& pixmap::operator =(const pixmap& pixmap) { if (this != &pixmap) ::copy_image32(this, pixmap); return *this; }


#endif
