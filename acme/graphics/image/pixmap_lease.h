// Created by camilo on 2026-07-23 01:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap_t.h"


class CLASS_DECL_ACME pixmap_lease : 
   public pixmap_t
{
protected:


   ::pointer<::pixmap> m_ppixmap;


public:


   pixmap_lease();
   pixmap_lease(::pixmap *ppixmap, bool bApplyTransform = true);
   pixmap_lease(pixmap_lease &&pixmaplease);
   ~pixmap_lease();


   pixmap_lease &operator=(pixmap_lease &&pixmaplease);


};



