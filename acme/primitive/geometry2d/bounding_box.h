#pragma once


#include "arc.h"
#include "line.h"




template < primitive_rectangle RECTANGLE, primitive_number NUMBER >
inline bool expand_bounding_box(RECTANGLE & rectangleBounding, const ::arc_type < NUMBER > & arc)
{

   rectangleBounding.left = (decltype(rectangleBounding.left)) (arc.m_pointCenter.x() - arc.m_sizeRadius.cx());
   rectangleBounding.right = (decltype(rectangleBounding.right))(arc.m_pointCenter.x() + arc.m_sizeRadius.cx());
   rectangleBounding.top = (decltype(rectangleBounding.top))(arc.m_pointCenter.y() - arc.m_sizeRadius.cy());
   rectangleBounding.bottom = (decltype(rectangleBounding.bottom))(arc.m_pointCenter.y() + arc.m_sizeRadius.cy());

   return true;

}


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


template < primitive_rectangle RECTANGLE, primitive_number NUMBER >
inline bool get_bounding_box(RECTANGLE & rectangleBounding, const ellipse_base < NUMBER > & ellipse)
{

   copy(rectangleBounding, ellipse);

   return true;

}


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

template < primitive_rectangle RECTANGLE_BASE_TYPE, primitive_point POINT_BASE_TYPE >
void get_bounding_box(RECTANGLE_BASE_TYPE & rect, const POINT_BASE_TYPE * lppoint, ::count count)
{

   if (count <= 0)
   {

      rect.left = 0;
      rect.top = 0;
      rect.right = 0;
      rect.bottom = 0;

   }
   else
   {

      rect.left =(decltype(rect.left))lppoint[0].x();
      rect.top = (decltype(rect.top))lppoint[0].y();
      rect.right = (decltype(rect.right))lppoint[0].x();
      rect.bottom = (decltype(rect.bottom))lppoint[0].y();

      for (i32 i = 1; i < count; i++)
      {
         if (lppoint[i].x() < rect.left)
            rect.left = (decltype(rect.left))lppoint[i].x();
         else if (lppoint[i].x() > rect.right)
            rect.right = (decltype(rect.right))lppoint[i].x();
         if (lppoint[i].y() < rect.top)
            rect.top = (decltype(rect.top))lppoint[i].y();
         else if (lppoint[i].y() > rect.bottom)
            rect.bottom = (decltype(rect.bottom))lppoint[i].y();
      }

   }

}


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
void expand_bounding_box(::rectangle_type < NUMBER1 > & rectangle, const ::ellipse_base < NUMBER2 > & ellipse2)
{

   expand_bounding_box_x(rectangle, ellipse2.left);

   expand_bounding_box_y(rectangle, ellipse2.top);

   expand_bounding_box_x(rectangle, ellipse2.right);

   expand_bounding_box_y(rectangle, ellipse2.bottom);

}





template < primitive_rectangle RECTANGLE, primitive_number NUMBER >
inline void expand_bounding_box(RECTANGLE & rectangleBounding, const ::line_base < NUMBER > & line)
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
