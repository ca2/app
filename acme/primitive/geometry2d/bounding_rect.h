#pragma once


#include "_arc.h"
#include "_line.h"


template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const ::arc & arc)
{

   rectangleBounding.left = (decltype(rectangleBounding.left)) (arc.m_pointCenter.x - arc.m_sizeRadius.cx);
   rectangleBounding.right = (decltype(rectangleBounding.right))(arc.m_pointCenter.x + arc.m_sizeRadius.cx);
   rectangleBounding.top = (decltype(rectangleBounding.top))(arc.m_pointCenter.y - arc.m_sizeRadius.cy);
   rectangleBounding.bottom = (decltype(rectangleBounding.bottom))(arc.m_pointCenter.y + arc.m_sizeRadius.cy);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64 * prectangleBounding, const ::arc * parc)
//{
//
//   rectangleBounding.left = arc.m_pointCenter.x - arc.m_sizeRadius.cx;
//   rectangleBounding.right = arc.m_pointCenter.x + arc.m_sizeRadius.cx;
//   rectangleBounding.top = arc.m_pointCenter.y - arc.m_sizeRadius.cy;
//   rectangleBounding.bottom = arc.m_pointCenter.y + arc.m_sizeRadius.cy;
//
//   return true;
//
//}

template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const line & line)
{

   rectangleBounding.left = (decltype(rectangleBounding.left)) minimum(line.m_p1.x, line.m_p2.x);
   rectangleBounding.top = (decltype(rectangleBounding.top)) minimum(line.m_p1.y, line.m_p2.y);
   rectangleBounding.right = (decltype(rectangleBounding.right)) maximum(line.m_p1.x, line.m_p2.x);
   rectangleBounding.bottom = (decltype(rectangleBounding.bottom)) maximum(line.m_p1.y, line.m_p2.y);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line* pline)
//{
//
//   rectangleBounding.left = minimum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.top = minimum(line.m_p1.y, line.m_p2.y);
//   rectangleBounding.right = maximum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.bottom = maximum(line.m_p1.y, line.m_p2.y);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = (::i32)minimum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.top = (::i32)minimum(line.m_p1.y, line.m_p2.y);
//   rectangleBounding.right = (::i32)maximum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.bottom = (::i32)maximum(line.m_p1.y, line.m_p2.y);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const line * pline)
//{
//
//   rectangleBounding.left = minimum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.top = minimum(line.m_p1.y, line.m_p2.y);
//   rectangleBounding.right = maximum(line.m_p1.x, line.m_p2.x);
//   rectangleBounding.bottom = maximum(line.m_p1.y, line.m_p2.y);
//
//   return true;
//
//}


template < primitive_rectangle RECTANGLE >
inline bool get_bounding_rectangle(RECTANGLE & rectangleBounding, const ellipse & ellipse)
{

   copy(rectangleBounding, ellipse);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const ellipse * pellipse)
//{
//
//   copy(prectangleBounding, pellipse);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const ellipse* poval)
//{
//
//   copy(prectangleBounding, poval);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const ellipse* prectangle)
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
void get_bounding_rectangle(RECTANGLE_BASE_TYPE & rect, const POINT_BASE_TYPE * lppoint, ::count count)
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

      rect.left =(decltype(rect.left))lppoint[0].x;
      rect.top = (decltype(rect.top))lppoint[0].y;
      rect.right = (decltype(rect.right))lppoint[0].x;
      rect.bottom = (decltype(rect.bottom))lppoint[0].y;

      for (i32 i = 1; i < count; i++)
      {
         if (lppoint[i].x < rect.left)
            rect.left = (decltype(rect.left))lppoint[i].x;
         else if (lppoint[i].x > rect.right)
            rect.right = (decltype(rect.right))lppoint[i].x;
         if (lppoint[i].y < rect.top)
            rect.top = (decltype(rect.top))lppoint[i].y;
         else if (lppoint[i].y > rect.bottom)
            rect.bottom = (decltype(rect.bottom))lppoint[i].y;
      }

   }

}


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
inline bool get_bounding_rectangle(RECTANGLE1 & rectangleBounding, const RECTANGLE2 & rectangle)
{

   copy(rectangleBounding, rectangle);

   return true;

}




