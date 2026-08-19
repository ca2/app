// From pixmap_lease by camilo on 2026-08-18 22:47 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// Created by camilo on 2026-07-23 01:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap_lease.h"


class CLASS_DECL_AURA image_pixmap_lease :
   public ::pixmap_lease
{
protected:


   friend class ::image::image;


   ::image::image *        m_pimage;


public:

   image_pixmap_lease();
   image_pixmap_lease(::image::image * pimage, ::pixmap * ppixmap);
   image_pixmap_lease(image_pixmap_lease &&imagepixmaplease);
   ~image_pixmap_lease();


   image_pixmap_lease &operator=(image_pixmap_lease &&imagepixmaplease);



};



