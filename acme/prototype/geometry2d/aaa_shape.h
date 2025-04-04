//
// Created by camilo on 28/08/2022 19:00 BRT <3ThomasBorregaardSorensen!!
//
#pragma once


#include "shape.h"


#include "shape_array.h"


template < typename HOLDEE >
inline ::pointer<___shape<HOLDEE >> __create_shape(const enum_shape & eshape)
{

   switch (eshape)
   {
   case e_shape_none:
      return nullptr;
   case e_shape_begin_clip:
      return __allocate begin_clip_shape<HOLDEE> ();
   case e_shape_intersect_clip:
      return __allocate intersect_clip_shape<HOLDEE> ();
   case e_shape_begin_figure:
      return __allocate begin_figure_shape<HOLDEE> ();
   case e_shape_close_figure:
      return __allocate close_figure_shape<HOLDEE> ();
   case e_shape_end_figure:
      return __allocate end_figure_shape<HOLDEE> ();
   default:
      throw ::exception(error_not_implemented, "aaa_primitive_new geometry processor or not a geometry processor?");
      return nullptr;
   }

}



