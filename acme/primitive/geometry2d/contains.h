#pragma once


template < primitive_number NUMBER, primitive_point POINT >
inline bool shape_contains(const ::arc_type < NUMBER > & arc, const POINT & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_i32 rectangle;

   if (!get_bounding_rectangle(rectangle, arc))
   {

      return false;

   }

   return rectangle.contains(point);

}


template < primitive_number NUMBER, primitive_point POINT >
inline bool shape_contains(const line_base < NUMBER > & line, const POINT & point)
{

   return false;

}


template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline bool shape_contains(const RECTANGLE & rectangle, const POINT & point)
{

   return ::contains(rectangle, point.x(), point.y());

}



