// Created by camilo on 2022-06-25 22:27 <3ThomasBorregaardS�rensen!!
#pragma once


#include "acme/primitive/geometry2d/_enhanced.h"
#include "acme/primitive/geometry2d/shape_array.h"
#include "acme/primitive/geometry2d/lines.h"


template < >
inline ::pointer<___shape<::draw2d::path>> __create_shape(const ::line & line, holdee < ::draw2d::path >)
{

   return __new(line_shape< ::draw2d::path >(line));

}


template < >
inline ::pointer<___shape<::draw2d::path>> __create_shape(const ::rectangle & rectangle, holdee < ::draw2d::path >)
{

   return __new(rectangle_shape<::draw2d::path>(rectangle));

}


template < >
inline ::pointer<___shape<::draw2d::path>> __create_shape(const ::ellipse & ellipse, holdee < ::draw2d::path >)
{

   return __new(ellipse_shape <::draw2d::path>(ellipse));

}


template < >
inline ::pointer<___shape<::draw2d::path>> __create_shape(const ::lines & lines, holdee < ::draw2d::path >)
{

   return __new(lines_shape<::draw2d::path>(lines));

}


template < >
inline ::pointer<___shape<::draw2d::path>> __create_shape(const ::polygon & polygon, holdee < ::draw2d::path >)
{

   return __new(polygon_shape<::draw2d::path>(polygon));

}


template < >
inline ::pointer<___shape<::draw2d::path>> __create_shape(const enum_shape & eshape, holdee < ::draw2d::path >)
{

   return ::__create_shape<::draw2d::path>(eshape);

}



