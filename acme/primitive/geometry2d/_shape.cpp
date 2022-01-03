//
// Created by camilo on 30/12/2021 19:53 BRT <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_geometry2d.h"
#include "_shape.h"
#include "_defer.h"
#include "acme/_defer.h"


template < >
CLASS_DECL_ACME __pointer(___shape) __create_shape(const ::lines & lines)
{

   return __new(lines_shape(lines));

}


template < >
CLASS_DECL_ACME __pointer(___shape) __create_shape(const ::polygon & polygon)
{

   return __new(polygon_shape(polygon));

}



