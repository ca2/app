// From pixmap.h by camilo on 2026-07-24 01:46 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/_configuration.h"
#include "acme/graphics/image/header.h"
#include "acme/graphics/image/image32.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/prototype/concrete.h"


#define __sizeof(TYPE) ((memsize)sizeof(TYPE))


// #pragma pack(push, pixmap)

// POD

#ifdef __cplusplus
struct CLASS_DECL_ACME pixmap_t : public image_header
#else
struct pixmap_t
#endif
{


#ifndef __cplusplus
   struct image_header m_header;
#endif

   ::i32 m_iRedLower;
   ::i32 m_iScan;
   ::image32_t *m_pimage32;
   ::i32_point m_point;
   ::image32_t *m_pimage32Raw;
   ::i32_size m_sizeRaw;
   ::color_indexes m_colorindexes = common_system_image_color_indexes();
   mutable bool m_bTrans; // optionally used by implementation
   mutable bool m_bMapped; // optionally used by implementation
   bool m_bReduced; // optionally used by implementation

   static ::i32 g_iRedLowerDefault;

#ifdef __cplusplus

   pixmap_t()
   {
      m_iRedLower = g_iRedLowerDefault;
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


   void initialize_pixmap(const ::i32_size &size, ::image32_t *pimage32, ::i32 iScan)
   {

      m_size = size;

      m_sizeRaw = size;

      m_iScan = iScan;

      m_point.clear();

      m_bMapped = false;

      if (::is_set(pimage32))
      {

         m_pimage32Raw = pimage32;

         map();
      }
      else
      {

         m_pimage32Raw = nullptr;

         m_pimage32 = nullptr;
      }
   }


   const ::color_indexes &color_indexes() const { return m_colorindexes; }
   ::color_indexes &color_indexes() { return m_colorindexes; }


   //   inline ::u64 area() const
   //{

   //   if (::is_null(this))
   //   {

   //      return 0;
   //   }

   //   return m_size.area();
   //}


   // inline ::i32 scan_size() const
   //{

   //   if (::is_null(this))
   //   {

   //      return 0;
   //   }

   //   return m_iScan;
   //}


   // inline ::i32 width() const
   //{

   //   if (::is_null(this))
   //   {

   //      return 0;
   //   }

   //   return m_size.cx;
   //}


   // inline ::i32 height() const
   //{

   //   if (::is_null(this))
   //   {

   //      return 0;
   //   }

   //   return m_size.cy;
   //}


   inline bool is_null() const { return ::is_null(this) || m_size.area() <= 0; }


   inline bool is_set() const { return !is_null(); }


   inline bool is_empty() const { return is_null(); }


   inline ::image32_t *image32() { return m_pimage32; }


   inline const ::image32_t *image32() const { return m_pimage32; }


   inline operator ::image32_t *() { return image32(); }


   inline operator const ::image32_t *() const { return image32(); }


   inline ::pixmap_t *pixmap() { return this; }


   inline const ::pixmap_t *pixmap() const { return this; }


   inline operator ::pixmap_t *() { return this; }


   inline operator const ::pixmap_t *() const { return this; }


   // inline ::image32_t * image32() { return m_pimage32; }
   // inline ::image32_t * image32() const { return m_pimage32; }


   inline ::image32_t *data() { return m_pimage32; }
   inline ::image32_t *data() const { return m_pimage32; }


   
   ::image32_t * line_data(::i32 iLine) { return (::image32_t *)(((::u8 *)data()) + (iLine * m_iScan)); }



   // inline operator pixmap_t *() { return this; }
   // inline operator const pixmap_t *() const { return this; }


   inline bool is_ok() const { return ::is_set(this) && area() > 0; }

   inline bool nok() const { return !is_ok(); }

   bool create(::memory &memory, const ::i32_size &size, ::i32 stride = -1);

   inline ::i32_rectangle rectangle() const { return ::i32_rectangle(m_point, m_size); }

   inline ::i32_rectangle rectangle(const ::i32_point &point) const { return ::i32_rectangle(point, m_size); }

   inline ::i32_point top_left() const noexcept { return m_point; }
   inline ::i32_point origin() const noexcept { return top_left(); }
   // inline concrete < ::i32_size > size() const noexcept { return m_size; }
   inline ::i32_size size() const noexcept { return m_size; };
   inline ::i32 width() const noexcept { return m_size.cx; }
   inline ::i32 height() const noexcept { return m_size.cy; }
   inline ::i32 area() const noexcept { return m_size.area(); }
   inline ::i32 scan_size() const noexcept { return m_iScan; }
   inline ::i32 scan_area() const noexcept { return height() * scan_size(); }


   inline ::color::color get_pixel(::i32 x, ::i32 y) const
   {

      return ::image32_get_pixel(image32(), m_colorindexes, scan_size(), height(), x, y);
   }

   inline void set_pixel(::i32 x, ::i32 y, ::color::color color)
   {

      return ::image32_set_pixel(image32(), m_colorindexes, scan_size(), height(), x, y, color);
   }

   inline ::color::color raw_pixel(::i32 x, ::i32 y) const
   {

      return ::image32_raw_pixel(image32(), m_colorindexes, scan_size(), height(), x, y);
   }

   inline void set_raw_pixel(::i32 x, ::i32 y, ::color::color color)
   {

      return ::image32_set_raw_pixel(image32(), m_colorindexes, scan_size(), height(), x, y, color);
   }

   inline ::color::color get_pixel(const ::i32_point &point) const { return get_pixel(point.x, point.y); }

   inline pixmap_t &operator=(const pixmap_t &pixmap);
   inline pixmap_t &operator=(const ::i32_rectangle &rectangle)
   {
      map(rectangle);
      return *this;
   }

   void reference(const pixmap_t &pixmap);

   void map(const ::i32_rectangle &rectangle)
   {

      m_point = rectangle.origin();

      m_size = rectangle.size();

      map();
   }

   void map() const
   {

      if (::is_set(m_pimage32Raw))
      {

         ((pixmap_t *)this)->m_pimage32 = m_pimage32Raw + (m_point.x + m_iScan * m_point.y);
      }
   }

   void unmap()
   {

      m_pimage32 = m_pimage32Raw;
      m_size = m_sizeRaw;
   }

   void mult_alpha();


   void vertical_swap();


   void copy(const ::i32_size &size, const ::pixmap_t *ppixmapSrc);

   void copy(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan);

   void y_swap_copy(const ::i32_size &size, const ::pixmap_t *ppixmapSrc);

   void copy(const ::pixmap_t *ppixmapSrc);

   void copy(const ::pixmap_t *ppixmapSrc, const ::image::enum_copy_disposition &ecopydisposition);

   void y_swap_copy(const ::pixmap_t *ppixmapSrc);

   ::color::color average_color();

#endif
};



