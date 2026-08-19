// Created by camilo on 2026-07-23 01:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap_t.h"


class CLASS_DECL_ACME pixmap_lease :
public ::pointer < ::pixmap >
{
protected:


   ::i32_rectangle       m_rectangle;
   

public:


   pixmap_lease();
   pixmap_lease(::pixmap* ppixmap, const ::i32_rectangle & rectangle = {});
   pixmap_lease(pixmap_lease &&pixmaplease);
   ~pixmap_lease();


   pixmap_lease &operator=(pixmap_lease &&pixmaplease);



};



