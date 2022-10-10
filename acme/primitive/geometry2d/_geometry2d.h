// Created by camilo on 2021-09-06 10:36 BRT Ten days to <3ThomasBS_!! Birthday!!
#pragma once


#include "shape.h"

#include "bounding_rect.h"

#include "contains.h"


//#include "shape_array.h"


template < typename HOLDEE >
inline ::pointer<___shape<HOLDEE >> __create_shape(const enum_shape & eshape)
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
      throw ::exception(error_not_implemented, "memory_new geometry processor or not a geometry processor?");
      return nullptr;
   }

}



///#include "_impl.h"



