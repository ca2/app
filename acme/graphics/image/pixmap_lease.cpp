// Created by camilo on 2026-07-23 01:24 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "pixmap.h"
#include "pixmap_lease.h"


pixmap_lease::pixmap_lease()
{

}


pixmap_lease::pixmap_lease(::pixmap *ppixmap, const ::i32_rectangle & rectangle) :
   ::pointer< ::pixmap >(ppixmap),
   m_rectangle({ppixmap->m_point, ppixmap->m_size })
{

   ppixmap->_map(rectangle);

}
   

// pixmap_lease::pixmap_lease(::pixmap* ppixmap, const ::i32_rectangle & rectangle) :
//    ::pointer< ::pixmap >(ppixmap),
//    m_bRectangleMap(true),
//    m_rectangleBefore(ppixmap->rectangle())
// {
//
//    ppixmap->_map(rectangle);
//
//    memory_copy(this, (::pixmap_t*)ppixmap, sizeof(pixmap_t));
//
// }


pixmap_lease::pixmap_lease(pixmap_lease &&pixmaplease) :
   ::pointer< ::pixmap >(::transfer(pixmaplease)),
   m_rectangle(pixmaplease.m_rectangle)
{



}



   
pixmap_lease::~pixmap_lease()
{

   if (!m_p)
   {

      return;

   }

   m_p->_unmap(m_rectangle);

   // if (m_bRectangleMap)
   // {
   //
   //    if (m_rectangleBefore.is_set())
   //    {
   //
   //       m_p->pixmap_map(m_rectangleBefore);
   //
   //    }
   //
   // }
   //
   // //clear();

}



pixmap_lease &pixmap_lease::operator=(pixmap_lease &&pixmaplease)
{

   if (this != &pixmaplease)
   {

      ::pointer < ::pixmap>::operator=(::transfer(pixmaplease));

      m_rectangle = pixmaplease.m_rectangle;

   }

   return *this;
}
