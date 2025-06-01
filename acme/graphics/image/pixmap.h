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

   int                           m_iRedLower;
   int                           m_iScan;
   ::image32_t * m_pimage32;
   ::int_point                   m_point;
   ::image32_t * m_pimage32Raw;
   ::int_size                    m_sizeRaw;
   ::color_indexes               m_colorindexes = common_system_image_color_indexes();
   mutable bool                  m_bTrans; // optionally used by implementation
   mutable bool                  m_bMapped; // optionally used by implementation
   bool                          m_bReduced; // optionally used by implementation

   static int                    g_iRedLowerDefault;

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


   void initialize(const ::int_size & size, ::image32_t * pimage32, int iScan)
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


   inline ::image32_t * data() { return m_pimage32; }
   inline ::image32_t * data() const { return m_pimage32; }


   inline operator pixmap * () { return this; }
   inline operator const pixmap * () const { return this; }


   inline bool is_ok() const { return ::is_set(this) && area() > 0; }

   inline bool nok() const { return !is_ok(); }

   bool create(::memory& memory, const ::int_size& size, int stride = -1);

   inline ::int_rectangle rectangle() const { return ::int_rectangle(m_point, m_size); }

   inline ::int_rectangle rectangle(const ::int_point & point) const { return ::int_rectangle(point, m_size); }

   inline ::int_point top_left() const noexcept { return m_point; }
   inline ::int_point origin() const noexcept { return top_left(); }
   //inline concrete < ::int_size > size() const noexcept { return m_size; }
   inline ::int_size size() const noexcept { return m_size; }
   inline int width() const noexcept { return m_size.cx(); }
   inline int height() const noexcept { return m_size.cy(); }
   inline int area() const noexcept { return m_size.area(); }
   inline int scan_area() const noexcept { return height() * scan_size(); }


   inline ::color::color get_pixel(int x, int y) const
   {

      return ::image32_get_pixel(image32(), m_colorindexes, scan_size(), height(), x, y);

   }

   inline void set_pixel(int x, int y, ::color::color color) 
   {

      return ::image32_set_pixel(image32(), m_colorindexes, scan_size(), height(), x, y, color);

   }

   inline ::color::color raw_pixel(int x, int y) const
   {

      return ::image32_raw_pixel(image32(), m_colorindexes, scan_size(), height(), x, y);

   }

   inline void set_raw_pixel(int x, int y, ::color::color color)
   {

      return ::image32_set_raw_pixel(image32(), m_colorindexes, scan_size(), height(), x, y, color);

   }

   inline ::color::color get_pixel(const ::int_point & point) const { return get_pixel(point.x(), point.y()); }

   inline pixmap & operator =(const pixmap & pixmap);
   inline pixmap & operator =(const ::int_rectangle & rectangle) { map(rectangle);  return *this; }

   void reference(const pixmap& pixmap);

   void map(const ::int_rectangle & rectangle)
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

   void mult_alpha();


   void vertical_swap();


   void copy(const ::int_size & size, const ::pixmap * ppixmapSrc);

   void copy(const ::pixmap * ppixmapSrc);


   ::color::color average_color();

#endif

};

//#pragma pack(pop, pixmap)





inline void image32_t::copy(const ::int_size & size, int iStrideDst, const ::pixmap * ppixmapSrc)
{
   
   copy(size.minimum(ppixmapSrc->size()), iStrideDst, ppixmapSrc->m_pimage32, ppixmapSrc->m_iScan);

}
