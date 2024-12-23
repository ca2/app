// Created by camilo on 2022-06-25 09:59 <3ThomasBorregaardSorensen!!
#pragma once


#include "holdee.h"
#include "acme/prototype/geometry2d/shape.h"


template < >
inline ::pointer<___shape<::draw2d::region>> __create_shape(const ::double_rectangle & rectangle, holdee < ::draw2d::region >)
{

   return __allocate rectangle_shape<::draw2d::region> (rectangle);

}


template < >
inline ::pointer<___shape<::draw2d::region>> __create_shape(const ::double_ellipse & ellipse, holdee < ::draw2d::region >)
{

   return __allocate ellipse_shape <::draw2d::region> (ellipse);

}


/*  template < >
   inline ::pointer<___shape>__create_shape(const ::lines & lines, holdee < ::draw2d::region >)
   {

      return __allocate lines_shape<path> (lines);

   }*/


template < >
inline ::pointer<___shape<::draw2d::region>> __create_shape(const ::polygon & polygon, holdee < ::draw2d::region >)
{

   return __allocate polygon_shape<::draw2d::region> (polygon);

}


template < >
inline ::pointer<___shape<::draw2d::region>> __create_shape(const enum_shape & eshape, holdee < ::draw2d::region >)
{

   return ::__create_shape<::draw2d::region>(eshape);

}



