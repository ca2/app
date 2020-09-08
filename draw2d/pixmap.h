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

   i32                        m_iScan;
   COLORREF *                 m_pcolorref1;
   ::point                    m_point;
   COLORREF *                 m_pcolorrefRaw;
   ::size                     m_sizeRaw;


#ifdef __cplusplus

      pixmap()
      {

         m_iScan = 0;
         m_pcolorref1 = nullptr;
         m_pcolorrefRaw = nullptr;

      }


      void clear()
      {

         reset();

         m_iScan = 0;
         m_pcolorref1 = nullptr;
         m_pcolorrefRaw = nullptr;

      }


      void init(const ::size & size, COLORREF * pcolorref, i32 iScan)
      {

         m_size = size;

         m_sizeRaw = size;

         m_pcolorrefRaw = pcolorref;

         m_iScan = iScan;

         m_point.Null();

         map();

      }


      int scan_size() const { return m_iScan; }

      inline COLORREF * colorref() { return m_pcolorref1; }
      inline COLORREF * colorref() const { return m_pcolorref1; }

      inline operator pixmap * () { return this; }
      inline operator const pixmap * () const { return this; }


      inline bool is_ok() const { return ::is_set(this) && area() > 0; }

      inline ::rect rect() const { return ::rect(m_point, m_size); }

      inline ::rect rect(const ::point & point) const { return ::rect(point, m_size); }

      inline ::point top_left() const noexcept { return m_point; }
      inline ::point origin() const noexcept { return top_left(); }
      inline ::size size() const noexcept { return m_size; }
      inline int width() const noexcept { return m_size.cx; }
      inline int height() const noexcept { return m_size.cy; }
      inline int area() const noexcept { return m_size.area(); }
      inline int scan_area() const noexcept { return height() * scan_size(); }


      inline COLORREF get_pixel(int x, int y) const;
      inline COLORREF get_pixel(const ::point & point) const { return get_pixel(point.x, point.y); }

      inline pixmap & operator =(const pixmap & pixmap);
      inline pixmap & operator =(const ::rect & rect) { map(rect);  return *this; }

#ifdef WINDOWS_DESKTOP
      HBITMAP update_windows_dib(const ::size & size);
#endif

      void map(const ::rect & rect)
      {

         m_point = rect.origin();

         m_size = rect.size();

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
   //   ::rect map(::rect rectNew)
   //   {
   //
   //      auto rectPrevious = rect();
   //
   //      operator =(rectNew);
   //
   //      return rectPrevious;
   //
   //   }
   //
   //
   //   void unmap(::rect rectPrevious)
   //   {
   //
   //      operator =(rectPrevious);
   //
   //   }
   //
   //   inline COLORREF* colorref() { return m_pbitmapMap->colorref(); }
   //   inline const COLORREF* colorref() const { return m_pbitmapMap->colorref(); }
   //
   //   inline operator bitmap* () { return m_pbitmapMap; }
   //   inline operator const bitmap* () const { return m_pbitmapMap; }
   //
   //   inline COLORREF get_pixel(int x, int y) { m_pbitmapMap->get_pixel(x, y); }
   //   inline COLORREF get_pixel(const ::point& point) { m_pbitmapMap->get_pixel(point); }
   //
   //
   //   inline bool is_ok() const { return m_pbitmapMap->is_ok(); }
   //
   //
   //   inline ::rect rect() const { return m_pbitmapMap->rect(); }
   //
   //
   //   pixmap& operator = (const ::rect& rect) { m_point = rect.origin(); m_size = rect.size(); return *this; }
   //
   //
   //   inline ::rect rect(const point& point = nullptr) const { return m_pbitmapMap->rect(point); }
   //
   //   pixmap& operator =(const pixmap& pixmap);
   //
   //   inline ::rect rect() const { return m_pbitmapMap->rect(); }
   //
   //
   //   inline ::point top_left() const noexcept { return m_pbitmapMap->top_left(); }
   //   inline ::point origin() const noexcept { return m_pbitmapMap->top_left(); }
   //   inline ::size size() const noexcept { return m_pbitmapMap->size(); }
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
      ::rect      m_rectPrevious;
      bool        m_bMapped;


      pixmap_lock() { }


      pixmap_lock(pixmap * pmap, rect rect) :
         m_pbitmap(pmap)
      {

         map(rect);

      }


      pixmap_lock(pixmap * pmap) :
         m_pbitmap(pmap)
      {

      }


      ~pixmap_lock()
      {

         unmap();

      }

      bool map(::rect rectMap)
      {

         if (m_bMapped)
         {

            return false;

         }

         m_rectPrevious = m_pbitmap->rect();

         m_pbitmap->map(rectMap);

         m_bMapped = true;

         return true;

      }


      bool unmap()
      {

         if (!m_bMapped)
         {

            return false;

         }

         m_pbitmap->map(m_rectPrevious);

         m_bMapped = false;

         return true;

      }

#endif

};

#pragma pack(pop, pixmap)


#ifdef __cplusplus


inline void copy_colorref(COLORREF * pcolorrefDst, const ::size & size, int iStrideDst, const ::pixmap * ppixmapSrc)
{

   copy_colorref(pcolorrefDst, size, iStrideDst, ppixmapSrc->colorref(), ppixmapSrc->scan_size());

}


inline void copy_colorref(::pixmap * ppixmapDst, const ::size & size, const ::pixmap * ppixmapSrc)
{

   copy_colorref(ppixmapDst->colorref(), size, ppixmapDst->scan_size(), ppixmapSrc);

}


inline void copy_colorref(::pixmap * ppixmapDst, const ::pixmap * ppixmapSrc)
{

   copy_colorref(ppixmapDst, ppixmapDst->size().min(ppixmapSrc->size()), ppixmapSrc);

}


inline pixmap & pixmap::operator =(const pixmap & pixmap) { if (this != &pixmap) ::copy_colorref(this, pixmap); return *this; }


#endif






