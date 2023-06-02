#pragma once


#include "lines.h"


#include "bounding_box.h"


template < primitive_number RECTANGLE_NUMBER, primitive_number LINES_NUMBER >
inline bool expand_bounding_box(::rectangle_type < RECTANGLE_NUMBER > & rectangleBounding, const lines_base < LINES_NUMBER > & lines)
{

   ::get_bounding_box(rectangleBounding, lines.data(), lines.size());

   return true;

}


//inline bool get_bounding_box(::rectangle_i32 & rectangleBounding, const lines & lines)
//{
//
//   ::get_bounding_box(rectangleBounding, lines.data(), lines.size());
//
//   return true;
//
//}


//template < primitive_number RECTANGLE_NUMBER, primitive_number POLYGON_NUMBER >
//inline bool expand_bounding_box(::rectangle_type < RECTANGLE_NUMBER > & rectangleBounding, const polygon_base < POLYGON_NUMBER > & polygon)
//{
//
//   ::get_bounding_box(rectangleBounding, polygon.data(), polygon.size());
//
//   return true;
//
//}


//inline bool get_bounding_box(::rectangle_f64 & rectangleBounding, const polygon_i32 & polygon)
//{
//
//   ::get_bounding_box(rectangleBounding, polygon.data(), polygon.size());
//
//   return true;
//
//}
//
//
//inline bool get_bounding_box(::rectangle_i32 & rectangleBounding, const polygon_f64 & polygon)
//{
//
//   ::get_bounding_box(rectangleBounding, polygon.data(), polygon.size());
//
//   return true;
//
//}
//
//
//inline bool get_bounding_box(::rectangle_f64 & rectangleBounding, const polygon_f64 & polygon)
//{
//
//   ::get_bounding_box(rectangleBounding, polygon.data(), polygon.size());
//
//   return true;
//
//}



template < primitive_number NUMBER1, primitive_number NUMBER2 >
void expand_bounding_box(::rectangle_type < NUMBER1 > & rectangle, const ::polygon_base < NUMBER2 > & polygon)
{

   for (auto & point : polygon)
   {

      ::expand_bounding_box(rectangle, point);

   }

}



template < primitive_number NUMBER1, primitive_number NUMBER2 >
void expand_bounding_box(::rectangle_type < NUMBER1 > & rectangle, const ::poly_polygon_type < NUMBER2 > & polypolygon)
{

   for (auto & ppolygon : polypolygon)
   {

      ::expand_bounding_box(rectangle, *ppolygon);

   }

}





