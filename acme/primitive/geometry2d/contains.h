#pragma once


//template < primitive_number NUMBER, primitive_point POINT >
//inline bool shape_contains(const ::arc_type < NUMBER > & arc, const POINT & point)
//{
//
//   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL
//
//   ::rectangle_i32 rectangle;
//
//   if (!get_bounding_box(rectangle, arc))
//   {
//
//      return false;
//
//   }
//
//   return rectangle.contains(point);
//
//}

//
//template < primitive_number NUMBER, primitive_point POINT >
//inline bool shape_contains(const line_base < NUMBER > & line, const POINT & point)
//{
//
//   return false;
//
//}

//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline bool shape_contains(const RECTANGLE & rectangle, const POINT & point)
//{
//
//   return ::contains(rectangle, point.x(), point.y());
//
//}
//

// https://forums.codeguru.com/showthread.php?419763-Check-a-Point-lies-in-a-Line-segment


template < primitive_number NUMBER1, primitive_number NUMBER2, primitive_number NUMBER >
bool segment_contains(const ::point_type < NUMBER1 > & point1, const ::point_type < NUMBER2 > & point2, const ::point_type < NUMBER > & point, const float epsilon = 0.001f)
{

   double dx = point2.x() - point1.x();

   double dy = point2.y () - point1.y();

   return is_equal(((point.x() - point1.x()) * dy), ((point.y() - point1.y()) * dx), epsilon);

   //return false;
}


//
//template < primitive_number NUMBER1, primitive_number NUMBER2, primitive_number NUMBER >
//bool ellipse_contains(const ::point_type < NUMBER1 > & center, const ::size_type < NUMBER2 > & radius, const ::point_type < NUMBER > & point)
//{
//
//}
//
//


