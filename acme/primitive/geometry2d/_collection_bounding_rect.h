#pragma once


#include "_lines.h"


#include "bounding_rect.h"


template < primitive_number RECTANGLE_NUMBER, primitive_number LINES_NUMBER >
inline bool get_bounding_rectangle(::rectangle_type < RECTANGLE_NUMBER > & rectangleBounding, const lines_base < LINES_NUMBER > & lines)
{

   ::get_bounding_rectangle(rectangleBounding, lines.data(), lines.size());

   return true;

}


//inline bool get_bounding_rectangle(::rectangle_i32 & rectangleBounding, const lines & lines)
//{
//
//   ::get_bounding_rectangle(rectangleBounding, lines.data(), lines.size());
//
//   return true;
//
//}

template < primitive_number RECTANGLE_NUMBER, primitive_number POLYGON_NUMBER >
inline bool get_bounding_rectangle(::rectangle_type < RECTANGLE_NUMBER > & rectangleBounding, const polygon_base < POLYGON_NUMBER > & polygon)
{

   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());

   return true;

}


//inline bool get_bounding_rectangle(::rectangle_f64 & rectangleBounding, const polygon_i32 & polygon)
//{
//
//   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());
//
//   return true;
//
//}
//
//
//inline bool get_bounding_rectangle(::rectangle_i32 & rectangleBounding, const polygon_f64 & polygon)
//{
//
//   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());
//
//   return true;
//
//}
//
//
//inline bool get_bounding_rectangle(::rectangle_f64 & rectangleBounding, const polygon_f64 & polygon)
//{
//
//   ::get_bounding_rectangle(rectangleBounding, polygon.data(), polygon.size());
//
//   return true;
//
//}



