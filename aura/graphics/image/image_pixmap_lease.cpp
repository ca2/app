// From pixmap_lease by camilo on 2026-08-18 22:48 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// Created by camilo on 2026-07-23 01:24 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "image.h"
#include "image_pixmap_lease.h"


image_pixmap_lease::image_pixmap_lease()
{

}


image_pixmap_lease::image_pixmap_lease(::image::image * pimage, ::pixmap * ppixmap) :
   ::pixmap_lease(ppixmap, {pimage->m_point, pimage->m_size}),
   m_pimage(pimage)
{
   m_pimage = pimage;
   m_pimage->m_pimagepixmaplease = this;

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


image_pixmap_lease::image_pixmap_lease(image_pixmap_lease &&imagepixmaplease) :
   ::pixmap_lease(::transfer(imagepixmaplease)),
   m_pimage(imagepixmaplease.m_pimage)
{
   m_pimage->m_pimagepixmaplease = this;
   imagepixmaplease.m_pimage = nullptr;

}

   
image_pixmap_lease::~image_pixmap_lease()
{

   if (!m_p || !m_pimage)
   {

      return;

   }

   m_pimage->_unmap(this);

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

      m_pimage = imagepixmaplease.m_pimage;

      imagepixmaplease.m_pimage = nullptr;

   }

   return *this;
}



