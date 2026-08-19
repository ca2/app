// From pixmap_lease by camilo on 2026-08-18 22:48 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// Created by camilo on 2026-07-23 01:24 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "pixmap.h"
#include "pixmap_lease.h"


image_pixmap_lease::image_pixmap_lease()
{

}


image_pixmap_lease::image_pixmap_lease(::image::image * pimage, ::pixmap * ppixmap, const ::i32_rectangle & rectangle) :
   ::pixmap_lease(ppixmap, rectangle),
   m_pimage(pimage),
   m_rectangle({pimage->m_point, pimage->m_size})
{

   m_pimage = pimage;

   m_pimagepixmaplease->m_ppixmap->m_point = m_point;

   m_pimagepixmaplease->m_ppixmap->m_size = m_size;

   m_pimagepixmaplease->m_ppixmap->m_size = m_size;

   m_pimagepixmaplease->m_ppixmap->pixmap_map();

   ppixmap->_map({pimage->m_point, pimage->m_size});

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


image_pixmap_lease::image_pixmap_lease(pixmap_lease &&pixmaplease) :
   ::pointer< ::pixmap >(::transfer(pixmaplease)),
   m_rectangle(pixmaplease.m_rectangle)
{



}



   
image_pixmap_lease::~image_pixmap_lease()
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



image_pixmap_lease &image_pixmap_lease::operator=(image_pixmap_lease &&imagepixmaplease)
{

   if (this != &imagepixmaplease)
   {

      ::pointer < ::pixmap>::operator=(::transfer(imagepixmaplease));

      m_rectangle = pixmaplease.m_rectangle;

   }

   return *this;
}
