#pragma once

//
//#include "arc.h"
//#include "line.h"




//template < primitive_rectangle RECTANGLE, primitive_number NUMBER >
//inline bool expand_bounding_box(RECTANGLE & rectangleBounding, const ::arc_type < NUMBER > & arc)
//{
//
//   rectangleBounding.left = (decltype(rectangleBounding.left)) (arc.m_pointCenter.x() - arc.m_sizeRadius.cx());
//   rectangleBounding.right = (decltype(rectangleBounding.right))(arc.m_pointCenter.x() + arc.m_sizeRadius.cx());
//   rectangleBounding.top = (decltype(rectangleBounding.top))(arc.m_pointCenter.y() - arc.m_sizeRadius.cy());
//   rectangleBounding.bottom = (decltype(rectangleBounding.bottom))(arc.m_pointCenter.y() + arc.m_sizeRadius.cy());
//
//   return true;
//
//}


//template < primitive_rectangle RECTANGLE >
//inline void expand_bounding_box(RECTANGLE & rectangle, ::point_f64 * p, ::count c)
//{
//
//   for (::index i = 0; i < c; i++)
//   {
//
//      expand_bounding_box(rectangle, *p);
//
//      p++;
//
//   }
//
//}



//inline bool get_bounding_box(::rectangle_f64 * prectangleBounding, const ::arc * parc)
//{
//
//   rectangleBounding.left = arc.m_pointCenter.x() - arc.m_sizeRadius.cx();
//   rectangleBounding.right = arc.m_pointCenter.x() + arc.m_sizeRadius.cx();
//   rectangleBounding.top = arc.m_pointCenter.y() - arc.m_sizeRadius.cy();
//   rectangleBounding.bottom = arc.m_pointCenter.y() + arc.m_sizeRadius.cy();
//
//   return true;
//
//}



//inline bool get_bounding_box(::rectangle_f64* prectangleBounding, const line* pline)
//{
//
//   rectangleBounding.left = minimum(line.m_p1.x(), line.m_p2.x());
//   rectangleBounding.top = minimum(line.m_p1.y(), line.m_p2.y());
//   rectangleBounding.right = maximum(line.m_p1.x(), line.m_p2.x());
//   rectangleBounding.bottom = maximum(line.m_p1.y(), line.m_p2.y());
//
//   return true;
//
//}


//inline bool get_bounding_box(::rectangle_i32* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = (::i32)minimum(line.m_p1.x(), line.m_p2.x());
//   rectangleBounding.top = (::i32)minimum(line.m_p1.y(), line.m_p2.y());
//   rectangleBounding.right = (::i32)maximum(line.m_p1.x(), line.m_p2.x());
//   rectangleBounding.bottom = (::i32)maximum(line.m_p1.y(), line.m_p2.y());
//
//   return true;
//
//}


//inline bool get_bounding_box(::rectangle_f64* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = minimum(line.m_p1.x(), line.m_p2.x());
//   rectangleBounding.top = minimum(line.m_p1.y(), line.m_p2.y());
//   rectangleBounding.right = maximum(line.m_p1.x(), line.m_p2.x());
//   rectangleBounding.bottom = maximum(line.m_p1.y(), line.m_p2.y());
//
//   return true;
//
//}

//
//template < primitive_rectangle RECTANGLE, primitive_number NUMBER >
//inline bool get_bounding_box(RECTANGLE & rectangleBounding, const ellipse_base < NUMBER > & ellipse)
//{
//
//   copy(rectangleBounding, ellipse);
//
//   return true;
//
//}


//inline bool get_bounding_box(::rectangle_f64* prectangleBounding, const ellipse * pellipse)
//{
//
//   copy(prectangleBounding, pellipse);
//
//   return true;
//
//}


//inline bool get_bounding_box(::rectangle_i32* prectangleBounding, const ellipse* poval)
//{
//
//   copy(prectangleBounding, poval);
//
//   return true;
//
//}


//inline bool get_bounding_box(::rectangle_f64* prectangleBounding, const ellipse* prectangle)
//{
//
//   copy(prectangleBounding, prectangle);
//
//   return true;
//
//}
//
//


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
inline bool get_bounding_box(RECTANGLE1 & rectangleBounding, const RECTANGLE2 & rectangle)
{

   copy(rectangleBounding, rectangle);

   return true;

}

//
//template < primitive_number NUMBER1, primitive_number NUMBER2 >
//void expand_bounding_box(::rectangle_type < NUMBER1 > & rectangle, ::point_type < NUMBER2 > & point)
//{
//
//   if (point.x < (NUMBER1) rectangle.left)
//   {
//
//      rectangle.left = (NUMBER1) point.x;
//
//   }
//   else if (pointVertex.x > (NUMBER1) rectangle.right)
//   {
//
//      rectangle.right = (NUMBER1) point.x;
//
//   }
//
//   if (point.y < (NUMBER1)rectangle.top)
//   {
//
//      rectangle.top = (NUMBER1)point.y;
//
//   }
//   else if (point.y > (NUMBER1) rectangle.bottom)
//   {
//
//      rectangle.bottom = (NUMBER1)point.y;
//
//   }
//
//}


template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline void expand_bounding_box_x(::rectangle_type < NUMBER1 > & rectangle, NUMBER2 x)
{

   if ((NUMBER1) x < rectangle.left)
   {

      rectangle.left = (NUMBER1)x;

   }
   else if ((NUMBER1) x > rectangle.right)
   {

      rectangle.right = (NUMBER1)x;

   }

}


template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline void expand_bounding_box_y(::rectangle_type < NUMBER1 > & rectangle, NUMBER2 y)
{

   if ((NUMBER1)y < rectangle.top)
   {

      rectangle.top = (NUMBER1)y;

   }
   else if ((NUMBER1)y > rectangle.bottom)
   {

      rectangle.bottom = (NUMBER1)y;

   }

}


template < primitive_number NUMBER1, primitive_number NUMBER2 >
void expand_bounding_box(::rectangle_type < NUMBER1 > & rectangle, const ::point_type < NUMBER2 > & point)
{

   expand_bounding_box_x(rectangle, point.x());

   expand_bounding_box_y(rectangle, point.y());

}


template < primitive_number NUMBER1, primitive_number NUMBER2 >
void expand_bounding_box(::rectangle_type < NUMBER1 > & rectangle, const ::rectangle_type < NUMBER2 > & rectangle2)
{

   expand_bounding_box_x(rectangle, rectangle2.left);

   expand_bounding_box_y(rectangle, rectangle2.top);

   expand_bounding_box_x(rectangle, rectangle2.right);

   expand_bounding_box_y(rectangle, rectangle2.bottom);

}


template < primitive_number NUMBER1, primitive_number NUMBER2 >
void expand_bounding_box(::rectangle_type < NUMBER1 > & rectangle, const ::ellipse_type < NUMBER2 > & ellipse2)
{

   expand_bounding_box_x(rectangle, ellipse2.left);

   expand_bounding_box_y(rectangle, ellipse2.top);

   expand_bounding_box_x(rectangle, ellipse2.right);

   expand_bounding_box_y(rectangle, ellipse2.bottom);

}





template < primitive_rectangle RECTANGLE, primitive_number NUMBER >
inline void expand_bounding_box(RECTANGLE & rectangleBounding, const ::line_type < NUMBER > & line)
{

   expand_bounding_box(rectangleBounding, line.m_p1);
   expand_bounding_box(rectangleBounding, line.m_p2);

}



template < primitive_rectangle RECTANGLE, typename TYPE >
inline bool get_bounding_box(RECTANGLE & rectangleBounding, const TYPE & t)
{

   rectangleBounding.maximum_minimum();

   expand_bounding_box(rectangleBounding, t);

   //rectangleBounding.left = (decltype(rectangleBounding.left))minimum(line.m_p1.x(), line.m_p2.x());
   //rectangleBounding.top = (decltype(rectangleBounding.top))minimum(line.m_p1.y(), line.m_p2.y());
   //rectangleBounding.right = (decltype(rectangleBounding.right))maximum(line.m_p1.x(), line.m_p2.x());
   //rectangleBounding.bottom = (decltype(rectangleBounding.bottom))maximum(line.m_p1.y(), line.m_p2.y());

   return rectangleBounding.is_set();

}
