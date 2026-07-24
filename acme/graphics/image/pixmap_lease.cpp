// Created by camilo on 2026-07-23 01:24 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "pixmap.h"
#include "pixmap_lease.h"


pixmap_lease::pixmap_lease()
{


}

pixmap_lease::pixmap_lease(::pixmap *ppixmap, bool bApplyTransform) :
   m_ppixmap(ppixmap) 
{

   ppixmap->_map(bApplyTransform);

   memory_copy(this, (::pixmap_t*) ppixmap, sizeof(pixmap_t));

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

   m_ppixmap->unmap();

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
