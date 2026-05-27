#pragma once


#include "acme/graphics/image/header.h"
#include "acme/graphics/image/image32.h"
#include "acme/graphics/image/_configuration.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/prototype/concrete.h"


#define __sizeof(TYPE) ((memsize)sizeof(TYPE))


//#pragma pack(push, pixmap)

// POD

#ifdef __cplusplus
struct CLASS_DECL_ACME pixmap :
   public image_header
#else
struct pixmap
#endif
{


#ifndef __cplusplus
   struct image_header           m_header;
#endif

   ::i32                           m_iRedLower;
   ::i32                           m_iScan;
   ::image32_t * m_pimage32;
   ::i32_point                   m_point;
   ::image32_t * m_pimage32Raw;
   ::i32_size                    m_sizeRaw;
   ::color_indexes               m_colorindexes = common_system_image_color_indexes();
   mutable bool                  m_bTrans; // optionally used by implementation
   mutable bool                  m_bMapped; // optionally used by implementation
   bool                          m_bReduced; // optionally used by implementation

   static ::i32                    g_iRedLowerDefault;

#ifdef __cplusplus

   pixmap()
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


   void initialize(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan)
   {

      m_size = size;

      m_sizeRaw = size;

      m_pimage32Raw = pimage32;

      m_iScan = iScan;

      m_point.clear();

      map();

   }



   ::i32 scan_size() const { return m_iScan; }

   inline ::image32_t * image32() { return m_pimage32; }
   inline ::image32_t * image32() const { return m_pimage32; }


   inline ::image32_t * data() { return m_pimage32; }
   inline ::image32_t * data() const { return m_pimage32; }


   inline operator pixmap * () { return this; }
   inline operator const pixmap * () const { return this; }


   inline bool is_ok() const { return ::is_set(this) && area() > 0; }

   inline bool nok() const { return !is_ok(); }

   bool create(::memory& memory, const ::i32_size& size, ::i32 stride = -1);

   inline ::i32_rectangle rectangle() const { return ::i32_rectangle(m_point, m_size); }

   inline ::i32_rectangle rectangle(const ::i32_point & point) const { return ::i32_rectangle(point, m_size); }

   inline ::i32_point top_left() const noexcept { return m_point; }
   inline ::i32_point origin() const noexcept { return top_left(); }
   //inline concrete < ::i32_size > size() const noexcept { return m_size; }
   inline ::i32_size size() const noexcept { return m_size; }
   inline ::i32 width() const noexcept { return m_size.cx; }
   inline ::i32 height() const noexcept { return m_size.cy; }
   inline ::i32 area() const noexcept { return m_size.area(); }
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

   inline ::color::color get_pixel(const ::i32_point & point) const { return get_pixel(point.x, point.y); }

   inline pixmap & operator =(const pixmap & pixmap);
   inline pixmap & operator =(const ::i32_rectangle & rectangle) { map(rectangle);  return *this; }

   void reference(const pixmap& pixmap);

   void map(const ::i32_rectangle & rectangle)
   {

      m_point = rectangle.origin();

      m_size = rectangle.size();

      map();

   }

   void map() const
   {

      if (::is_set(m_pimage32Raw))
      {

         ((pixmap *)this)->m_pimage32 = m_pimage32Raw + (m_point.x + m_iScan * m_point.y);

      }

   }

   void unmap()
   {

      m_pimage32 = m_pimage32Raw;
      m_size = m_sizeRaw;

   }

   void mult_alpha();


   void vertical_swap();


   void copy(const ::i32_size & size, const ::pixmap * ppixmapSrc);

   void y_swap_copy(const ::i32_size& size, const ::pixmap* ppixmapSrc);

   void copy(const ::pixmap * ppixmapSrc);

   void copy(const ::pixmap* ppixmapSrc, const ::image::enum_copy_disposition & ecopydisposition);

   void y_swap_copy(const ::pixmap* ppixmapSrc);

   ::color::color average_color();

#endif

};

//#pragma pack(pop, pixmap)





inline void image32_t::copy(const ::i32_size & size, ::i32 iStrideDst, const ::pixmap * ppixmapSrc)
{
   
   copy(size.minimum(ppixmapSrc->size()), iStrideDst, ppixmapSrc->m_pimage32, ppixmapSrc->m_iScan);

}



inline void image32_t::copy(const ::pixmap* p)
{
   copy(::i32_point(), p->size(), p->width() * 4, p->image32(), p->m_iScan);
}
