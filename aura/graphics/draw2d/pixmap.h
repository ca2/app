#pragma once


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
   struct image_header        m_header;
#endif

   i32                           m_iScan;
   ::color32_t *                 m_pcolorref1;
   ::point_i32                   m_point;
   ::color32_t *                 m_pcolorrefRaw;
   ::size_i32                    m_sizeRaw;
   mutable bool                  m_bTrans; // optionally used by implementation
   mutable bool                  m_bMapped; // optionally used by implementation
   bool                          m_bReduced; // optionally used by implementation


#ifdef __cplusplus

      pixmap()
      {

         m_iScan = 0;
         m_pcolorref1 = nullptr;
         m_pcolorrefRaw = nullptr;
         m_bMapped = false;
         m_bReduced = false;
         m_bTrans = false;
      }


      void clear()
      {

         reset();

         m_iScan = 0;
         m_pcolorref1 = nullptr;
         m_pcolorrefRaw = nullptr;

      }


      void init(const ::size_i32 & size, ::color32_t * pcolorref, i32 iScan)
      {

         m_size = size;

         m_sizeRaw = size;

         m_pcolorrefRaw = pcolorref;

         m_iScan = iScan;

         m_point.Null();

         map();

      }



      int scan_size() const { return m_iScan; }

      inline ::color32_t * colorref() { return m_pcolorref1; }
      inline ::color32_t * colorref() const { return m_pcolorref1; }

      inline operator pixmap * () { return this; }
      inline operator const pixmap * () const { return this; }


      inline bool is_ok() const { return ::is_set(this) && area() > 0; }

      inline ::rectangle_i32 rectangle() const { return ::rectangle_i32(m_point, m_size); }

      inline ::rectangle_i32 rectangle(const ::point_i32 & point) const { return ::rectangle_i32(point, m_size); }

      inline ::point_i32 top_left() const noexcept { return m_point; }
      inline ::point_i32 origin() const noexcept { return top_left(); }
      inline concrete < ::size_i32 > size() const noexcept { return m_size; }
      inline int width() const noexcept { return m_size.cx; }
      inline int height() const noexcept { return m_size.cy; }
      inline int area() const noexcept { return m_size.area(); }
      inline int scan_area() const noexcept { return height() * scan_size(); }


      inline ::color::color get_pixel(int x, int y) const;
      inline ::color::color get_pixel(const ::point_i32 & point) const { return get_pixel(point.x, point.y); }

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

         if (::is_set(m_pcolorrefRaw))
         {

            ((pixmap *)this)->m_pcolorref1 = m_pcolorrefRaw + (m_point.x + m_iScan * m_point.y);

         }

      }

      void unmap()
      {

         m_pcolorref1 = m_pcolorrefRaw;
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
   //   inline ::color32_t* colorref() { return m_pbitmapMap->colorref(); }
   //   inline const ::color32_t* colorref() const { return m_pbitmapMap->colorref(); }
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
   //   inline ::rectangle_i32 rectangle(const point_i32& point = nullptr) const { return m_pbitmapMap->rectangle(point); }
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


#ifdef __cplusplus


inline void copy_colorref(::color32_t * pcolorrefDst, const ::size_i32 & size, int iStrideDst, const ::pixmap * ppixmapSrc)
{

   copy_colorref(pcolorrefDst, size, iStrideDst, ppixmapSrc->colorref(), ppixmapSrc->scan_size());

}


inline void copy_colorref(::pixmap * ppixmapDst, const ::size_i32 & size, const ::pixmap * ppixmapSrc)
{

   copy_colorref(ppixmapDst->colorref(), size, ppixmapDst->scan_size(), ppixmapSrc);

}


inline void copy_colorref(::pixmap * ppixmapDst, const ::pixmap * ppixmapSrc)
{

   copy_colorref(ppixmapDst, ppixmapDst->size().minimum(ppixmapSrc->size()), ppixmapSrc);

}


inline pixmap & pixmap::operator =(const pixmap & pixmap) { if (this != &pixmap) ::copy_colorref(this, pixmap); return *this; }


#endif






