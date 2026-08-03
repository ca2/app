// Created by camilo on 2026-07-23 01:24 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "pixmap.h"
#include "pixmap_lease.h"


pixmap_lease::pixmap_lease()
{

   m_bRectangleMap = false;

}

pixmap_lease::pixmap_lease(::pixmap *ppixmap, bool bApplyTransform) :
   m_ppixmap(ppixmap),
   m_bRectangleMap(false)
{

   ppixmap->_map(bApplyTransform);

   memory_copy(this, (::pixmap_t*) ppixmap, sizeof(pixmap_t));

}
   

pixmap_lease::pixmap_lease(::pixmap* ppixmap, const ::i32_rectangle & rectangle) :
   m_ppixmap(ppixmap),
   m_bRectangleMap(true)
{

   ppixmap->_map(true);

   m_rectangleBefore = ppixmap->rectangle();

   ppixmap->pixmap_map(rectangle);

   memory_copy(this, (::pixmap_t*)ppixmap, sizeof(pixmap_t));

}


pixmap_lease::pixmap_lease(pixmap_lease &&pixmaplease) :
   m_ppixmap(::transfer(pixmaplease.m_ppixmap))
{

   memory_copy(this, (::pixmap_t *)&pixmaplease, sizeof(pixmap_t));

}



   
pixmap_lease::~pixmap_lease()
{

   if (!m_ppixmap)
   {

      return;

   }

   m_ppixmap->_unmap();

   if (m_bRectangleMap)
   {

      if (m_rectangleBefore.is_set())
      {

         m_ppixmap->pixmap_map(m_rectangleBefore);

      }

   }

   clear();

}



pixmap_lease &pixmap_lease::operator=(pixmap_lease &&pixmaplease)
{

   if (this != &pixmaplease)
   {
      m_ppixmap = ::transfer(pixmaplease.m_ppixmap);
      memory_copy(this, (::pixmap_t *)&pixmaplease, sizeof(pixmap_t));
   }

   return *this;
}
