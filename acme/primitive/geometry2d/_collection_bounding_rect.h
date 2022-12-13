#pragma once


#include "_lines.h"


#include "bounding_rect.h"


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const lines & lines)
{

   ::get_bounding_rectangle(rectangleBounding, lines.data(), lines.size());

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const lines & lines)
{

   ::get_bounding_rectangle(rectangleBounding, lines.data(), lines.size());

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const polygon_i32 & polygon)
{

   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const polygon_i32 & polygon)
{

   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const polygon_f64 & polygon)
{

   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const polygon_f64 & polygon)
{

   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());

   return true;

}



