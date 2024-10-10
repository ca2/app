// From pixmap.h by camilo on 2024-09-27 19:36 <3ThomasBorregaardSorensen!!
#pragma once


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


};



