// Created by camilo on 2022-08-28 18:47 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/geometry2d/shape.h"


#include "acme/primitive/geometry2d/shape_array.h"


template < typename HOLDEE >
inline __pointer(___shape<HOLDEE >) __create_shape(const enum_shape & eshape)
{

   switch (eshape)
   {
   case e_shape_none:
      return nullptr;
   case e_shape_begin_clip:
      return __new(begin_clip_shape<HOLDEE>);
   case e_shape_intersect_clip:
      return __new(intersect_clip_shape<HOLDEE>);
   case e_shape_begin_figure:
      return __new(begin_figure_shape<HOLDEE>);
   case e_shape_close_figure:
      return __new(close_figure_shape<HOLDEE>);
   case e_shape_end_figure:
      return __new(end_figure_shape<HOLDEE>);
   default:
      throw ::exception(error_not_implemented, "new geometry processor or not a geometry processor?");
      return nullptr;
   }

}



