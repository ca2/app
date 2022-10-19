#pragma once




//#include "_struct.h"




#include "angle.h"


#include "shift.h"


enum enum_orientation
{

   e_orientation_horizontal = -1,
   e_orientation_none = 0,
   e_orientation_vertical = 1,

};






inline auto left(const RECTANGLE_I32 & rectangle) { return rectangle.left; }
inline auto top(const RECTANGLE_I32 & rectangle) { return rectangle.top; }
inline auto left(const RECTANGLE_I64 & rectangle) { return rectangle.left; }
inline auto top(const RECTANGLE_I64 & rectangle) { return rectangle.top; }
inline auto left(const RECTANGLE_F32 & rectangle) { return rectangle.left; }
inline auto top(const RECTANGLE_F32 & rectangle) { return rectangle.top; }
inline auto left(const RECTANGLE_F64 & rectangle) { return rectangle.left; }
inline auto top(const RECTANGLE_F64 & rectangle) { return rectangle.top; }




template < typename TARGET, typename SOURCE >
inline TARGET & _001CopyRect(TARGET & prectTarget, const SOURCE & prectSource);


template < XYDim_rectangle XYWH, typename X, typename Y, typename W, typename H >
inline XYWH & set_dim(XYWH & rectTarget, X x, Y y, W w, H h)
{

   rectTarget.X = (decltype(rectTarget.X))x;
   rectTarget.Y = (decltype(rectTarget.Y))y;
   rectTarget.Width = (decltype(rectTarget.Width))w;
   rectTarget.Height = (decltype(rectTarget.Height))h;

   return rectTarget;

}


template < typename A, typename B >
void __swap(A & a, B & b)
{

   A aCopy = a;

   a = b;

   b = aCopy;

}


template < primitive_rectangle RECTANGLE_TYPE, typename X >
inline RECTANGLE_TYPE & x_offset_rect(RECTANGLE_TYPE & rectangle, X x)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left + x);

   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right + x);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, typename Y >
inline RECTANGLE_TYPE & y_offset_rect(RECTANGLE_TYPE & rectangle, Y y)
{

   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top + y);

   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom + y);

   return rectangle;

}



template < primitive_rectangle RECTANGLE_TYPE, typename X >
inline RECTANGLE_TYPE & x_subtract_rect(RECTANGLE_TYPE & rectangle, X x)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left - x);

   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right - x);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, typename Y >
inline RECTANGLE_TYPE & y_subtract_rect(RECTANGLE_TYPE & rectangle, Y y)
{

   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top - y);

   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom - y);

   return rectangle;

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & offset_rect(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   x_offset_rect(rectangle, x);

   y_offset_rect(rectangle, y);

   return rectangle;

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & subtract_rect(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   x_subtract_rect(rectangle, x);

   y_subtract_rect(rectangle, y);

   return rectangle;

}

template < typename RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & offset_rect(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return offset_rect(rectangle, point.x, point.y);

}



template < typename RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & subtract_rect(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return subtract_rect(rectangle, point.x, point.y);

}


template < typename RECTANGLE_TYPE, primitive_point POINT >
inline RECTANGLE_TYPE & rect_sub(RECTANGLE_TYPE & rectangle, const POINT & point) { return subtract_rect(rectangle, point); }



template < primitive_point POINT, typename X, typename Y >
inline POINT & offset_point(POINT & point, X x, Y y)
{

   point.x = (decltype(POINT::x))(point.x + x);
   point.y = (decltype(POINT::y))(point.y + y);

   return point;

}


template < primitive_point POINT, primitive_point POINT2 >
inline POINT & offset_point(POINT & point, const POINT2 & point2)
{

   return offset_point(point, point2.x, point2.y);

}


template < primitive_point POINT, primitive_point POINT2 >
inline POINT & point_add(POINT & point, const POINT2 & point2) { return offset_point(point, point2); }


template < primitive_point POINT_TYPE, typename X, typename Y >
inline POINT_TYPE & point_sub(POINT_TYPE & point, X x, Y y)
{

   point.x = (decltype(POINT_TYPE::x))(point.x - x);
   point.y = (decltype(POINT_TYPE::y))(point.y - y);

   return point;

}


template < primitive_point POINT_TYPE, typename POINT_TYPE2 >
inline POINT_TYPE & point_sub(POINT_TYPE & point, const POINT_TYPE2 & point2)
{

   return point_sub(point, point2.x, point2.y);

}


template < primitive_point POINT_TYPE, typename X, typename Y >
inline POINT_TYPE & subtract_point(POINT_TYPE & point, X x, Y y)
{

   point.x = (decltype(POINT_TYPE::x))(point.x - x);
   point.y = (decltype(POINT_TYPE::y))(point.y - y);

   return point;

}


template < primitive_point POINT_TYPE, primitive_point POINT_TYPE2 >
inline POINT_TYPE & subtract_point(POINT_TYPE & point, const POINT_TYPE2 & point2)
{

   return subtract_point(point, point2.x, point2.y);

}






template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle POINT_TYPE >
inline RECTANGLE_TYPE & rect_add(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point) { return offset_rect(rectangle, point); }



template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left, rect2.left);

   auto right = minimum(rect1.right, rect2.right);

   bool bIntersect = right > left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.left = left;

      rectangle.right = right;

   }

   return bIntersect;

}

template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left, rect2.left);

   auto right = minimum(rect1.right, rect2.right);

   return right > left;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top, rect2.top);

   auto bottom = minimum(rect1.bottom, rect2.bottom);

   bool bIntersect = bottom > top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.top = top;

      rectangle.bottom = bottom;

   }

   return bIntersect;

}



template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top, rect2.top);

   auto bottom = minimum(rect1.bottom, rect2.bottom);

   return bottom > top;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_intersect_rect(rectangle, rect1, rect2) && y_intersect_rect(rectangle, rect1, rect2))
   {

      return true;

   }

   if (::is_set(rectangle))
   {

      null(rectangle);

   }

   return false;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   return x_intersects(rect1, rect2) && y_intersects(rect1, rect2);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_null_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left, rect2.left);

   auto right = minimum(rect1.right, rect2.right);

   bool bIntersect = right >= left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.left = left;

      rectangle.right = right;

   }

   return bIntersect;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_null_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top, rect2.top);

   auto bottom = minimum(rect1.bottom, rect2.bottom);

   bool bIntersect = bottom >= top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.top = top;

      rectangle.bottom = bottom;

   }

   return bIntersect;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool null_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_null_intersect_rect(rectangle, rect1, rect2) && y_null_intersect_rect(rectangle, rect1, rect2))
   {

      return true;

   }

   if (::is_set(rectangle))
   {

      null(rectangle);

   }

   return false;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_left_null_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rectangle.left = maximum(rect1.left, rect2.left);

   rectangle.right = minimum(rect1.right, rect2.right);

   return rectangle.right > rectangle.left || (rectangle.right == rectangle.left && rect1.left == rect2.left);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_top_null_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rectangle.top = maximum(rect1.top, rect2.top);

   rectangle.bottom = minimum(rect1.bottom, rect2.bottom);

   return rectangle.top < rectangle.bottom || (rectangle.top == rectangle.bottom && rect1.top == rect2.top);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool top_left_null_intersect_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_left_null_intersect_rect(rectangle, rect1, rect2) && y_top_null_intersect_rect(rectangle, rect1, rect2))
   {

      return true;

   }
   else
   {

      null(rectangle);

      return false;

   }

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECTANGLE_TYPE & union_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (is_rect_empty(rect1))
   {

      if (is_rect_empty(rect2))
      {

         null_rect(rectangle);

      }
      else
      {

         copy(rectangle, rect2);

      }

   }
   else if (is_rect_empty(rect1))
   {

      copy(rectangle, rect1);

   }
   else
   {

      rectangle.left = (decltype(RECTANGLE_TYPE::left))minimum(rect1.left, rect2.left);
      rectangle.top = (decltype(RECTANGLE_TYPE::top))minimum(rect1.top, rect2.top);
      rectangle.right = (decltype(RECTANGLE_TYPE::right))maximum(rect1.right, rect2.right);
      rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))maximum(rect1.bottom, rect2.bottom);

   }

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECTANGLE_TYPE & subtract_rect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{


   rectangle.left = (decltype(RECT_TYPE1::left))minimum(rect1.left, rect2.left);
   rectangle.top = (decltype(RECT_TYPE1::top))minimum(rect1.top, rect2.top);
   rectangle.right = (decltype(RECT_TYPE1::right))maximum(rect1.right, rect2.right);
   rectangle.bottom = (decltype(RECT_TYPE1::bottom))maximum(rect1.bottom, rect2.bottom);

   return rectangle;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 & copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rect1.left = (decltype(RECT_TYPE1::left))rect2.left;
   rect1.top = (decltype(RECT_TYPE1::top))rect2.top;
   rect1.right = (decltype(RECT_TYPE1::right))rect2.right;
   rect1.bottom = (decltype(RECT_TYPE1::bottom))rect2.bottom;

   return rect1;

}


template < primitive_rectangle RECT_TYPE1, XYDim_rectangle RECT_TYPE2 >
RECT_TYPE1 & copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rect1.left = (decltype(RECT_TYPE1::left))rect2.X;
   rect1.top = (decltype(RECT_TYPE1::top))rect2.Y;
   rect1.right = (decltype(RECT_TYPE1::right))(rect2.X + rect2.Width);
   rect1.bottom = (decltype(RECT_TYPE1::bottom))(rect2.Y + rect2.Height);

   return rect1;

}


template < primitive_rectangle RECT_TYPE1, xydim_rectangle RECT_TYPE2 >
RECT_TYPE1 & copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rect1.left = (decltype(RECT_TYPE1::left))rect2.x;
   rect1.top = (decltype(RECT_TYPE1::top))rect2.y;
   rect1.right = (decltype(RECT_TYPE1::right))(rect2.x + rect2.width);
   rect1.bottom = (decltype(RECT_TYPE1::bottom))(rect2.y + rect2.height);

   return rect1;

}


template < XY_point POINT1, primitive_point POINT2 >
POINT1 & copy(POINT1 & point1, const POINT2 & point2)
{

   point1.X = (decltype(POINT1::X))point2.x;
   point1.Y = (decltype(POINT1::Y))point2.y;

   return point1;

}


template < primitive_point POINT1, XY_point POINT2 >
POINT1 & copy(POINT1 & point1, const POINT2 & point2)
{

   point1.x = (decltype(POINT1::x))point2.X;
   point1.y = (decltype(POINT1::y))point2.Y;

   return point1;

}


template < XYDim_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 & copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rect1.X = (decltype(RECT_TYPE1::X))rect2.left;
   rect1.Y = (decltype(RECT_TYPE1::Y))rect2.top;
   rect1.Width = (decltype(RECT_TYPE1::Width))(rect2.right - rect2.left);
   rect1.Height = (decltype(RECT_TYPE1::Height))(rect2.bottom - rect2.top);

   return rect1;

}


template < xydim_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 & copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rect1.x = (decltype(RECT_TYPE1::X))rect2.left;
   rect1.y = (decltype(RECT_TYPE1::Y))rect2.top;
   rect1.width = (decltype(RECT_TYPE1::Width))(rect2.right - rect2.left);
   rect1.height = (decltype(RECT_TYPE1::Height))(rect2.bottom - rect2.top);

   return rect1;

}


template < XYDim_rectangle RECT_TYPE1, XYDim_rectangle RECT_TYPE2 >
RECT_TYPE1 & copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rect1.X = (decltype(RECT_TYPE1::X))rect2.X;
   rect1.Y = (decltype(RECT_TYPE1::Y))rect2.Y;
   rect1.Width = (decltype(RECT_TYPE1::Width))rect2.Width;
   rect1.Height = (decltype(RECT_TYPE1::Height))rect2.Height;

   return rect1;

}


template < primitive_point POINT1, primitive_point POINT2 >
POINT1 & copy(POINT1 & point1, const POINT2 & point2)
{

   point1.x = (decltype(POINT1::x))point2.x;
   point1.y = (decltype(POINT1::y))point2.y;

   return point1;

}


template < primitive_point POINT, primitive_size SIZE >
POINT & copy(POINT & point, const SIZE & size)
{

   point.x = (decltype(POINT::x))size.cx;
   point.y = (decltype(POINT::y))size.cy;

   return point;

}


template < typename SIZE_TYPE1, typename SIZE_TYPE2 >
SIZE_TYPE1 & copy_size(SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2)
{

   size1.cx = (decltype(SIZE_TYPE1::cx))size2.cx;
   size1.cy = (decltype(SIZE_TYPE1::cy))size2.cy;

   return size1;

}


template < typename X, typename Y >
auto get_dimension(enum_orientation eorientation, X x, Y y);


template < typename X, typename Y >
auto get_normal_dimension(enum_orientation eorientation, X x, Y y);



template < typename RECTANGLE_TYPE >
bool rect_equals(const RECTANGLE_TYPE & rect1, const RECTANGLE_TYPE & rect2)
{

   return rect1.left == rect2.left && rect1.top == rect2.top
      && rect1.right == rect2.right && rect1.bottom == rect2.bottom;

}


template < typename POINT_TYPE >
bool point_equals(const POINT_TYPE * ppoint1, const POINT_TYPE * ppoint2)
{

   return ppoint1->x == ppoint2->x && ppoint1->y == ppoint2->y;

}


template < typename SIZE_TYPE >
bool size_equals(const SIZE_TYPE & size1, const SIZE_TYPE & size2)
{

   return size1.x == size2.x && size1.y == size2.y;

}

template < typename RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
RECTANGLE_TYPE & set_rect(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))l;
   rectangle.top = (decltype(RECTANGLE_TYPE::top))t;
   rectangle.right = (decltype(RECTANGLE_TYPE::right))r;
   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))b;

   return rectangle;

}





template < primitive_rectangle RECTANGLE, typename L, typename T, typename W, typename H >
RECTANGLE & set_dim(RECTANGLE & rectangle, L l, T t, W w, H h)
{

   rectangle.left = (decltype(RECTANGLE::left))l;
   rectangle.top = (decltype(RECTANGLE::top))t;
   rectangle.right = (decltype(RECTANGLE::right))(l + w);
   rectangle.bottom = (decltype(RECTANGLE::bottom))(t + h);

   return rectangle;

}

//template < primitive_rectangle RECTANGLE,  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE &r, L l, T t, W w, H h) { return set_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_I64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_F32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_F64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }


template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & set_rect_size_bottom_right(RECTANGLE & rectangle, const SIZE & size)
{

   rectangle.right = (decltype(RECTANGLE::right))(rectangle.left + size.cx);
   rectangle.bottom = (decltype(RECTANGLE::bottom))(rectangle.top + size.cy);

   return rectangle;

}



template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & set_rect_point_size(RECTANGLE & rectangle, const POINT & point, const SIZE & size)
{

   rectangle.left = (decltype(RECTANGLE::left))point.x;
   rectangle.top = (decltype(RECTANGLE::top))point.y;
   rectangle.right = (decltype(RECTANGLE::right))(point.x + size.cx);
   rectangle.bottom = (decltype(RECTANGLE::bottom))(point.y + size.cy);

   return rectangle;

}


template < typename RECTANGLE_TYPE >
RECTANGLE_TYPE & null_rect(RECTANGLE_TYPE & rectangle)
{

   return ::set_rect(rectangle, 0, 0, 0, 0);

}


template < typename RECTANGLE_TYPE >
constexpr auto rect_width(RECTANGLE_TYPE & rectangle) { return rectangle.right - rectangle.left; }


template < typename RECTANGLE_TYPE >
constexpr auto rect_height(RECTANGLE_TYPE & rectangle) { return rectangle.bottom - rectangle.top; }


template < typename W, typename H >
constexpr H rect_area(W w, H h) { return (w <= (W)0 || h <= (H)0) ? 0 : (H)(w * h); }


template < typename RECTANGLE_TYPE >
constexpr auto rect_area(RECTANGLE_TYPE & rectangle) { return rect_area(rect_width(rectangle), rect_height(rectangle)); }


template < typename RECTANGLE_TYPE >
constexpr auto is_rect_empty(RECTANGLE_TYPE & rectangle) { return ::is_null(rectangle) || rectangle.right <= rectangle.left || rectangle.bottom <= rectangle.top; }

template < typename RECTANGLE_TYPE >
bool is_rect_null(const RECTANGLE_TYPE & rectangle)
{

   return rectangle.left == (decltype(RECTANGLE_TYPE::left))0
      && rectangle.top == (decltype(RECTANGLE_TYPE::top))0
      && rectangle.right == (decltype(RECTANGLE_TYPE::right))0
      && rectangle.bottom == (decltype(RECTANGLE_TYPE::bottom))0;

}


template < typename SIZE_TYPE >
bool is_size_null(const SIZE_TYPE & size)
{

   return size.cx == (decltype(SIZE_TYPE::cx))0
      && size.cy == (decltype(SIZE_TYPE::cy))0;

}


template < typename POINT_TYPE >
bool is_point_null(const POINT_TYPE & point)
{

   return point.x == (decltype(POINT_TYPE::cx))0
      && point.y == (decltype(POINT_TYPE::cy))0;

}



template < primitive_rectangle RECTANGLE, typename X >
inline bool rectangle_contains_x(const RECTANGLE & rectangle, X x)
{

   return x >= rectangle.left && x <= rectangle.right;

}


template < primitive_rectangle RECTANGLE, typename Y >
inline bool rectangle_contains_y(const RECTANGLE & rectangle, Y y)
{

   return y >= rectangle.top && y <= rectangle.bottom;

}


template < primitive_rectangle RECTANGLE, typename X, typename Y >
inline bool rectangle_contains(const RECTANGLE & rectangle, X x, Y y)
{

   return rectangle_contains_x(rectangle, x) && rectangle_contains_y(rectangle, y);

}


template < typename RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
inline RECTANGLE_TYPE & rect_inflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left - l);
   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top - t);
   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right + r);
   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom + b);

   return rectangle;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE2 >
inline RECTANGLE_TYPE & rect_inflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   return rect_inflate(rectangle, rect2.left, rect2.top, rect2.right, rect2.bottom);

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE2 >
inline RECTANGLE_TYPE & rect_multiply_inline(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   rectangle.left *= rect2.left;
   rectangle.top *= rect2.top;
   rectangle.right *= rect2.right;
   rectangle.bottom *= rect2.bottom;

   return rectangle;

}

template < typename RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
inline RECTANGLE_TYPE & rect_deflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left + l);
   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top + t);
   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right - r);
   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom - b);

   return rectangle;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE2 >
inline RECTANGLE_TYPE & rect_deflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   return rect_deflate(rectangle, rect2.left, rect2.top, rect2.right, rect2.bottom);

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & rect_inflate_point(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   return rect_inflate(rectangle, x, y, x, y);

}

template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & rect_deflate_point(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   return rect_deflate(rectangle, x, y, x, y);

}


template < typename RECTANGLE_TYPE, typename UNIT >
inline RECTANGLE_TYPE & rect_inflate_unit(RECTANGLE_TYPE & rectangle, UNIT u)
{

   return rect_inflate_point(rectangle, u, u);

}


template < typename RECTANGLE_TYPE, typename UNIT >
inline RECTANGLE_TYPE & rect_deflate_unit(RECTANGLE_TYPE & rectangle, UNIT u)
{

   return rect_deflate_point(rectangle, u, u);

}


template < typename RECTANGLE_TYPE >
inline RECTANGLE_TYPE & swap_rect_left_right(RECTANGLE_TYPE & rectangle) { __swap(rectangle.left, rectangle.right); return rectangle; }



template < primitive_point POINT1, primitive_point POINT2 >
inline bool polygon_contains_point(const POINT1 * ppPolygon, i32 iCount, const POINT2 & point)
{

   int i, j = iCount - 1;
   auto x = point.x;

   auto y = point.y;

   bool oddNodes = false;

   for (i = 0; i < iCount; i++)
   {
      if (((ppPolygon[i].y < y && ppPolygon[j].y >= y) || (ppPolygon[j].y < y && ppPolygon[i].y >= y)) && (ppPolygon[i].x <= x || ppPolygon[j].x <= x))

      {
         oddNodes ^= (ppPolygon[i].x + (y - ppPolygon[i].y) / (ppPolygon[j].y - ppPolygon[i].y) * (ppPolygon[j].x - ppPolygon[i].x) < x);

      }
      j = i;
   }

   return oddNodes;

}




template < typename SIZE_BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class size_type;

template < typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class point_type;

template < typename RECTANGLE_BASE_TYPE, typename POINT_TYPE, typename SIZE_TYPE >
class rectangle_type;

template < typename POINT_TYPE >
class point_array_base;


namespace design
{

   enum e_fit
   {

      fit_width = -1,
      fit_match = 0,
      fit_height = 1,

   };



   enum e_match
   {

      match_width = -1,
      match_none = 0,
      match_height = 1,

   };


} // namespace design



#include "align.h"


DECLARE_ENUMERATION(e_align, enum_align);


inline ::i32 area(::i32 cx, ::i32 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline i64 area(i64 cx, i64 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline double area(double cx, double cy) { return (cx < 0. && cy < 0. ? -1. : 1.) * cx * cy; }



struct SIZE_I64;
struct POINT_I64;
struct RECTANGLE_I64;
//::size_i32;
//class size_i64;
//class size_f64;
//::point_i32;
//class point_i64;
//class point_f64;
//::rectangle;
//::rectangle_i64;
//::rectangle_f64;

typedef uchar      byte;

struct POINT_I64;
struct SIZE_I64;
struct RECTANGLE_I64;
struct POINT_F64;
struct SIZE_F64;
struct RECTANGLE_F64;



using point_i32 = point_type < POINT_I32, SIZE_I32, RECTANGLE_I32 >;
using point_i64 = point_type < POINT_I64, SIZE_I64, RECTANGLE_I64 >;
using point_f32 = point_type < POINT_F32, SIZE_F32, RECTANGLE_F32 >;
using point_f64 = point_type < POINT_F64, SIZE_F64, RECTANGLE_F64 >;


using size_i32 = size_type < SIZE_I32, POINT_I32, RECTANGLE_I32 >;
using size_i64 = size_type < SIZE_I64, POINT_I64, RECTANGLE_I64 >;
using size_f32 = size_type < SIZE_F32, POINT_F32, RECTANGLE_F32 >;
using size_f64 = size_type < SIZE_F64, POINT_F64, RECTANGLE_F64 >;


using rectangle_i32 = rectangle_type < RECTANGLE_I32, POINT_I32, SIZE_I32 >;
using rectangle_i64 = rectangle_type < RECTANGLE_I64, POINT_I64, SIZE_I64 >;
using rectangle_f32 = rectangle_type < RECTANGLE_F32, POINT_F32, SIZE_F32 >;
using rectangle_f64 = rectangle_type < RECTANGLE_F64, POINT_F64, SIZE_F64 >;


using point_i32_array = point_array_base < point_i32 >;
using point_i64_array = point_array_base < point_i64 >;
using point_f32_array = point_array_base < point_f32 >;
using point_f64_array = point_array_base < point_f64 >;


using rectangle = ::rectangle_f64;


//inline float i32muldiv(float f, i32 iNum, i32 iDen);
//inline double i32muldiv(double d, i32 iNum, i32 iDen);
//inline i32 i32muldiv(i32 i, i32 iNum, i32 iDen);
//#ifndef WINDOWS
//inline i64 MulDiv(i64 nNumber, i32 iNum, i32 iDen);
//#endif
//inline i64 i32muldiv(i64 i, i64 iNum, i64 iDen);


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3, primitive_integral INTEGRAL_RESULT = typename ::largest_type_of_3 < INTEGRAL1, INTEGRAL2, INTEGRAL3 >::type >
inline INTEGRAL_RESULT muldiv(INTEGRAL1 i, INTEGRAL2 iNumerator, INTEGRAL3 iDenominator);










inline bool contains(const RECTANGLE_I32 & rectangle, const POINT_I32 & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
inline RECTANGLE_I32 & null(RECTANGLE_I32 & rectDst) { return ::null_rect(rectDst); }
inline bool is_equal(const RECTANGLE_I32 & rect1, const RECTANGLE_I32 & rect2) { return ::rect_equals(rect1, rect2); }
inline RECTANGLE_I32 & inflate(RECTANGLE_I32 & rectangle, ::i32 x, ::i32 y) { return ::rect_inflate_point(rectangle, x, y); }
inline RECTANGLE_I32 & deflate(RECTANGLE_I32 & rectangle, ::i32 x, ::i32 y) { return ::rect_deflate_point(rectangle, x, y); }
inline RECTANGLE_I32 & offset(RECTANGLE_I32 & rectangle, ::i32 x, ::i32 y) { return ::offset_rect(rectangle, x, y); }
inline bool intersect(RECTANGLE_I32 & rectangle, const RECTANGLE_I32 & rect1, const RECTANGLE_I32 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
inline RECTANGLE_I32 & unite(RECTANGLE_I32 & rectangle, const RECTANGLE_I32 & rect1, const RECTANGLE_I32 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
inline ::i32 width(const RECTANGLE_I32 & rectangle) { return ::rect_width(rectangle); }
inline ::i32 height(const RECTANGLE_I32 & rectangle) { return ::rect_height(rectangle); }
inline ::i32 area(const RECTANGLE_I32 & rectangle) { return ::rect_area(rectangle); }
inline bool is_empty(const RECTANGLE_I32 & rectangle) { return ::is_rect_empty(rectangle); }
inline void swap_left_right(RECTANGLE_I32 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline ::i32 width(const RECTANGLE_I32 & rectangle) { return ::width(&rectangle); }
//inline ::i32 height(const RECTANGLE_I32 & rectangle) { return ::height(&rectangle); }
//inline ::i32 area(const RECTANGLE_I32 & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const RECTANGLE_I32 & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(RECTANGLE_I32 & rectangle) noexcept { ::swap_left_right(&rectangle); }



inline bool is_empty(SIZE_I32 & size) { return size.cx <= 0 || size.cy <= 0; }
inline bool is_empty(SIZE_I64 & size) { return size.cx <= 0 || size.cy <= 0; }
inline bool is_empty(SIZE_F32 & size) { return size.cx <= 0.f || size.cy <= 0.f; }
inline bool is_empty(SIZE_F64 & size) { return size.cx <= 0. || size.cy <= 0.; }








inline bool contains(const RECTANGLE_I64 & rectangle, const POINT_I32 & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
inline RECTANGLE_I64 & null(RECTANGLE_I64 & rectDst) { return ::null_rect(rectDst); }
inline bool is_equal(const RECTANGLE_I64 & rect1, const RECTANGLE_I64 & rect2) { return ::rect_equals(rect1, rect2); }
inline RECTANGLE_I64 & inflate(RECTANGLE_I64 & rectangle, i64 x, i64 y) { return ::rect_inflate_point(rectangle, x, y); }
inline RECTANGLE_I64 & deflate(RECTANGLE_I64 & rectangle, i64 x, i64 y) { return ::rect_deflate_point(rectangle, x, y); }
inline RECTANGLE_I64 & offset(RECTANGLE_I64 & rectangle, i64 x, i64 y) { return ::offset_rect(rectangle, x, y); }
inline bool intersect(RECTANGLE_I64 & rectangle, const RECTANGLE_I64 & rect1, const RECTANGLE_I64 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
inline RECTANGLE_I64 & unite(RECTANGLE_I64 & rectangle, const RECTANGLE_I64 & rect1, const RECTANGLE_I64 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
inline i64 width(const RECTANGLE_I64 & rectangle) { return ::rect_width(rectangle); }
inline i64 height(const RECTANGLE_I64 & rectangle) { return ::rect_height(rectangle); }
inline i64 area(const RECTANGLE_I64 & rectangle) { return ::rect_area(rectangle); }
inline bool is_empty(const RECTANGLE_I64 & rectangle) { return ::is_rect_empty(rectangle); }
inline void swap_left_right(RECTANGLE_I64 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline i64 width(const RECTANGLE_I64 & rectangle) { return ::width(&rectangle); }
//inline i64 height(const RECTANGLE_I64 & rectangle) { return ::height(&rectangle); }
//inline i64 area(const RECTANGLE_I64 & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const RECTANGLE_I64 & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(RECTANGLE_I64 & rectangle) noexcept { ::swap_left_right(&rectangle); }





inline bool contains(const RECTANGLE_F32 & rectangle, const POINT_F32 & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
inline RECTANGLE_F32 & null(RECTANGLE_F32 & rect) { return ::null_rect(rect); }
inline bool is_equal(const RECTANGLE_F32 & rect1, const RECTANGLE_F32 & rect2) { return ::rect_equals(rect1, rect2); }
inline RECTANGLE_F32 & inflate(RECTANGLE_F32 & rectangle, float x, float y) { return ::rect_inflate_point(rectangle, x, y); }
inline RECTANGLE_F32 & deflate(RECTANGLE_F32 & rectangle, float x, float y) { return ::rect_deflate_point(rectangle, x, y); }
inline RECTANGLE_F32 & offset(RECTANGLE_F32 & rectangle, float x, float y) { return ::offset_rect(rectangle, x, y); }
inline bool intersect(RECTANGLE_F32 & rectangle, const RECTANGLE_F32 & rect1, const RECTANGLE_F32 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
inline RECTANGLE_F32 & unite(RECTANGLE_F32 & rectangle, const RECTANGLE_F32 & rect1, const RECTANGLE_F32 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
inline float width(const RECTANGLE_F32 & rectangle) { return ::rect_width(rectangle); }
//template < primitive_rectangle RECTANGLE > 
//inline auto height(const RECTANGLE  & rectangle) { return ::rect_height(rectangle); }
//template < primitive_rectangle RECTANGLE >
//inline auto height(const RECTANGLE & rectangle) { return ::height(&rectangle); }
inline float area(const RECTANGLE_F32 & rectangle) { return ::rect_area(rectangle); }
inline bool is_empty(const RECTANGLE_F32 & rectangle) { return ::is_rect_empty(rectangle); }
inline void swap_left_right(RECTANGLE_F32 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline float width(const RECTANGLE_F32& rectangle) { return ::width(&rectangle); }
////inline float height(const RECTANGLE_F32& rectangle) { return ::height(&rectangle); }
//inline float area(const RECTANGLE_F32& rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const RECTANGLE_F32& rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(RECTANGLE_F32& rectangle) noexcept { ::swap_left_right(&rectangle); }




inline bool contains(const RECTANGLE_F64 & rectangle, const POINT_F64 & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
inline RECTANGLE_F64 & null(RECTANGLE_F64 & rect) { return ::null_rect(rect); }
inline bool is_equal(const RECTANGLE_F64 & rect1, const RECTANGLE_F64 & rect2) { return ::rect_equals(rect1, rect2); }
inline RECTANGLE_F64 & inflate(RECTANGLE_F64 & rectangle, double x, double y) { return ::rect_inflate_point(rectangle, x, y); }
inline RECTANGLE_F64 & deflate(RECTANGLE_F64 & rectangle, double x, double y) { return ::rect_deflate_point(rectangle, x, y); }
inline RECTANGLE_F64 & offset(RECTANGLE_F64 & rectangle, double x, double y) { return ::offset_rect(rectangle, x, y); }

namespace geometry
{

   template < primitive_rectangle RECTANGLE >
   inline void deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);

} // namespace geometry


inline bool intersect(RECTANGLE_F64 & rectangle, const RECTANGLE_F64 & rect1, const RECTANGLE_F64 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
inline RECTANGLE_F64 & unite(RECTANGLE_F64 & rectangle, const RECTANGLE_F64 & rect1, const RECTANGLE_F64 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
inline double width(const RECTANGLE_F64 & rectangle) { return ::rect_width(rectangle); }
//inline double height(const RECTANGLE_F64  & rectangle) { return ::rect_height(rectangle); }
inline double area(const RECTANGLE_F64 & rectangle) { return ::rect_area(rectangle); }
inline bool is_empty(const RECTANGLE_F64 & rectangle) { return ::is_rect_empty(rectangle); }
inline void swap_left_right(RECTANGLE_F64 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline double width(const RECTANGLE_F64 & rectangle) { return ::width(&rectangle); }
//inline double height(const RECTANGLE_F64& rectangle) { return ::height(&rectangle); }
//inline double area(const RECTANGLE_F64 & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const RECTANGLE_F64 & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(RECTANGLE_F64 & rectangle) noexcept { ::swap_left_right(&rectangle); }

template < primitive_point POINT, primitive_point POINT2 >
inline POINT & operator -= (POINT & point, const POINT2 & pointOffset) { ::point_sub(point, pointOffset); return point; }

template < primitive_point POINT, primitive_point POINT2 >
inline POINT & operator += (POINT & point, const POINT2 & pointOffset) { ::point_add(point, pointOffset); return point; }

//inline POINT_I64 & operator -= (POINT_I64 & point, const ::point_i64 & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline POINT_I64 & operator += (POINT_I64 & point, const ::point_i64 & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline POINT_F32 & operator -= (POINT_F32 & point, const ::point_f32 & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline POINT_F32 & operator += (POINT_F32 & point, const ::point_f32 & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline POINT_F64 & operator -= (POINT_F64 & point, const ::point_f64 & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline POINT_F64 & operator += (POINT_F64 & point, const ::point_f64 & pointOffset) { ::point_add(point, pointOffset); return point; }

template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline RECTANGLE & operator -= (RECTANGLE & rectangle, const POINT & point) { ::rect_sub(rectangle, point); return rectangle; }

template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline RECTANGLE & operator += (RECTANGLE & rectangle, const POINT & point) { ::rect_add(rectangle, point); return rectangle; }

//inline RECTANGLE_I64& operator -= (RECTANGLE_I64& rectangle, const ::point_i64& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline RECTANGLE_I64& operator += (RECTANGLE_I64& rectangle, const ::point_i64& point) { ::rect_add(rectangle, point); return rectangle; }
//inline RECTANGLE_F32& operator -= (RECTANGLE_F32& rectangle, const ::point_f32& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline RECTANGLE_F32& operator += (RECTANGLE_F32& rectangle, const ::point_f32& point) { ::rect_add(rectangle, point); return rectangle; }
//inline RECTANGLE_F64& operator -= (RECTANGLE_F64& rectangle, const ::point_f64& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline RECTANGLE_F64& operator += (RECTANGLE_F64& rectangle, const ::point_f64& point) { ::rect_add(rectangle, point); return rectangle; }

//inline bool deflate(RECTANGLE_I32  & rectangle, const ::rectangle_i32 & prectParam);


#include "point.h"
#include "size.h"
#include "rectangle.h"



#include "types.h"


template < typename RECTANGLE_BASE_TYPE, typename POINT_BASE_TYPE >
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
      rect.left = lppoint[0].x;
      rect.top = lppoint[0].y;
      rect.right = lppoint[0].x;
      rect.bottom = lppoint[0].y;

      for (i32 i = 1; i < count; i++)
      {
         if (lppoint[i].x < rect.left)
            rect.left = lppoint[i].x;
         else if (lppoint[i].x > rect.right)
            rect.right = lppoint[i].x;
         if (lppoint[i].y < rect.top)
            rect.top = lppoint[i].y;
         else if (lppoint[i].y > rect.bottom)
            rect.bottom = lppoint[i].y;
      }

   }

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const RECTANGLE_I32 & rectangle)
{

   copy(rectangleBounding, rectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const RECTANGLE_I32 & rectangle)
{

   copy(rectangleBounding, rectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const RECTANGLE_F64 & rectangle)
{

   copy(rectangleBounding, rectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const RECTANGLE_F64 & rectangle)
{

   copy(rectangleBounding, rectangle);

   return true;

}


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > ::get_bounding_rectangle(const POINT_BASE_TYPE * ppoint, ::count count)
{

   ::get_bounding_rectangle(*this, ppoint, count);

}




CLASS_DECL_ACME double d_distance(const point_i32 & point1, const point_i32 & point2);


template < typename X, typename Y, typename W, typename H >
inline rectangle_i32 rectangle_i32_dimension(X x, Y y, W w, H h)
{

   return rectangle_i32((i32)(x), (i32)(y), (i32)(x + w), (i32)(y + h));

}


template < typename X, typename Y, typename W, typename H >
inline rectangle_i64 rectangle_i64_dimension(X x, Y y, W w, H h)
{

   return rectangle_i64((i64)x, (i64)y, (i64)(x + w), (i64)(y + h));

}


template < typename X, typename Y, typename W, typename H >
inline rectangle_f32 rectangle_f32_dimension(X x, Y y, W w, H h)
{

   return rectangle_f32((f32)x, (f32)y, (f32)(x + w), (f32)(y + h));

}


template < typename X, typename Y, typename W, typename H >
inline rectangle_f64 rectangle_f64_dimension(X x, Y y, W w, H h)
{

   return rectangle_f64((f64)x, (f64)y, (f64)(x + w), (f64)(y + h));

}



//#ifdef _UWP
//
//inline void copy(rectangle_i32 & rectDst, const ::winrt::Windows::Foundation::Rect * prectSrc)
//{
//   rectDst->left = (::i32) prectSrc->X;
//   rectDst->top = (::i32)prectSrc->Y;
//   rectDst->right = (::i32) (prectSrc->X + prectSrc->Width);
//   rectDst->bottom = (::i32) (prectSrc->Y + prectSrc->Height);
//}
//
//inline void copy(::winrt::Windows::Foundation::Rect& rectDst, rectangle_i32* prectSrc)
//{
//   rectDst->X = (float) prectSrc->left;
//   rectDst->Y = (float) prectSrc->top;
//   rectDst->Width = (float) prectSrc->width();
//   rectDst->Height = (float) prectSrc->height();
//}
//
//#endif


inline auto __point(const ::lparam & lparam) noexcept { return ::point_i32(lparam.x(), lparam.y()); }
inline auto __point(const ::u32 u) noexcept { return ::point_i32((::i32)__u32x(u), (::i32)__u32y(u)); }
inline auto __point(const ::u64 u) noexcept { return ::point_i32((::i32)__u64x(u), (::i32)__u64y(u)); }
inline auto __point(const ::size_i32 & size) noexcept { return ::point_i32(size.cx, size.cy); }

inline auto __point64(const ::lparam & lparam) noexcept { return ::point_i64(lparam.x(), lparam.y()); }
inline auto __point64(const ::u32 u) noexcept { return ::point_i64((i64)__u32x(u), (i64)__u32y(u)); }
inline auto __point64(const ::u64 u) noexcept { return ::point_i64((i64)__u64x(u), (i64)__u64y(u)); }
inline auto __point64(const ::size_i64 & size) noexcept { return ::point_i64(size.cx, size.cy); }


inline auto __pointf(const ::lparam & lparam) noexcept { return ::point_f32((float)lparam.x(), (float)lparam.y()); }
inline auto __pointf(const ::u32 u) noexcept { return ::point_f32((float)__u32x(u), (float)__u32y(u)); }
inline auto __pointf(const ::u64 u) noexcept { return ::point_f32((float)__u64x(u), (float)__u64y(u)); }
inline auto __pointf(const ::size_f32 & size) noexcept { return ::point_f32(size.cx, size.cy); }


inline auto __pointd(const ::lparam & lparam) noexcept { return ::point_f64(lparam.x(), lparam.y()); }
inline auto __pointd(const ::u32 u) noexcept { return ::point_f64((double)__u32x(u), (double)__u32y(u)); }
inline auto __pointd(const ::u64 u) noexcept { return ::point_f64((double)__u64x(u), (double)__u64y(u)); }
inline auto __pointd(const ::size_f64 & size) noexcept { return ::point_f64(size.cx, size.cy); }

//#ifdef _UWP
//
//inline ::winrt::Windows::Foundation::Rect ScaleRect(::winrt::Windows::Foundation::Rect rectangle, double scale)
//{
//
//   rectangle.X = (float)(rectangle.X*scale);
//   rectangle.Y = (float)(rectangle.Y* scale);
//   rectangle.Width = (float)(rectangle.Width * scale);
//   rectangle.Height = (float)(rectangle.Height*scale);
//
//   return rectangle;
//
//}
//
//
//#endif





template < typename RECT1, typename RECT2 >
inline void expand_rect(RECT1 & rectangle, const RECT2 & r)
{

   if (::is_rect_null(rectangle))
   {

      copy(rectangle, r);

   }
   else
   {

      rectangle.left = minimum((decltype(rectangle.left))rectangle.left, (decltype(rectangle.left))r.left);
      rectangle.right = maximum((decltype(rectangle.right))rectangle.right, (decltype(rectangle.right))r.right);
      rectangle.top = minimum((decltype(rectangle.top))rectangle.top, (decltype(rectangle.top))r.top);
      rectangle.bottom = maximum((decltype(rectangle.bottom))rectangle.bottom, (decltype(rectangle.bottom))r.bottom);

   }

}


template < typename RECT1, typename RECT2 >
inline void collapse_rect(RECT1 & rectangle, const RECT2 & r)
{

   if (::is_rect_null(rectangle))
   {

      copy(rectangle, r);

   }
   else
   {

      rectangle.left = maximum((decltype(rectangle.left))rectangle.left, (decltype(rectangle.left))r.left);
      rectangle.right = minimum((decltype(rectangle.right))rectangle.right, (decltype(rectangle.right))r.right);
      rectangle.top = maximum((decltype(rectangle.top))rectangle.top, (decltype(rectangle.top))r.top);
      rectangle.bottom = minimum((decltype(rectangle.bottom))rectangle.bottom, (decltype(rectangle.bottom))r.bottom);

      if (::width(rectangle) == 0 || height(rectangle) == 0)
      {

         ::null_rect(rectangle);

      }

   }

}


template < primitive_point POINT >
inline constexpr auto __horz(const POINT & point) { return point.x; }
template < primitive_point POINT >
inline constexpr auto __vert(const POINT & point) { return point.y; }
template < primitive_size SIZE >
inline constexpr auto __horz(const SIZE & size) { return size.cx; }
template < primitive_size SIZE >
inline constexpr auto __vert(const SIZE & size) { return size.cy; }

inline point_i32 & top_left(const RECTANGLE_I32 & rectangle) { return *(point_i32 *)&rectangle; }
inline point_i32 & bottom_right(const RECTANGLE_I32 & rectangle) { return *(point_i32 *)&rectangle.right; }
//inline point_i32 & top_left(const RECTANGLE_I32 & rectangle) { return top_left(&rectangle); }
//inline point_i32 & bottom_right(const RECTANGLE_I32 & rectangle) { return bottom_right(&rectangle); }


inline point_i64 & top_left(const RECTANGLE_I64 & rectangle) { return *(point_i64 *)&rectangle; }
inline point_i64 & bottom_right(const RECTANGLE_I64 & rectangle) { return *(point_i64 *)&rectangle.right; }
//inline point_i64 & top_left(const RECTANGLE_I64 & rectangle) { return top_left(&rectangle); }
//inline point_i64 & bottom_right(const RECTANGLE_I64 & rectangle) { return bottom_right(&rectangle); }


inline point_f64 & top_left(const RECTANGLE_F64 & rectangle) { return *(point_f64 *)&rectangle; }
inline point_f64 & bottom_right(const RECTANGLE_F64 & rectangle) { return *(point_f64 *)&rectangle.right; }
//inline point_f64 & top_left(const RECTANGLE_F64 & rectangle) { return top_left(&rectangle); }
//inline point_f64 & bottom_right(const RECTANGLE_F64 & rectangle) { return bottom_right(&rectangle); }


template < typename X, typename Y >
inline auto get_dimension(enum_orientation eorientation, X x, Y y)
{

   if (eorientation == e_orientation_horizontal)
   {

      return x;

   }
   else if (eorientation == e_orientation_vertical)
   {

      return y;

   }
   else
   {

      throw ::exception(error_bad_argument, "invalid orientation");

   }

}


template < typename X, typename Y >
inline auto get_normal_dimension(enum_orientation eorientation, X x, Y y)
{

   if (eorientation == e_orientation_vertical)
   {

      return x;

   }
   else if (eorientation == e_orientation_horizontal)
   {

      return y;

   }
   else
   {

      throw ::exception(error_bad_argument, "invalid orientation");

   }

}


//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const POINT_TYPE & point) noexcept : size_type((size_type&)point_i32) {}
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const RECTANGLE_TYPE & rectangle) noexcept : size_type(rectangle.width(), rectangle.height()) {}


template < typename UNIT_TYPE >
inline UNIT_TYPE __conv(const ::string & str)
{

   return (UNIT_TYPE)str;

}


template <  >
inline ::i32 __conv<::i32>(const ::string & str)
{

   return (::i32) ::atoi(str);

}


template <  >
inline i64 __conv<i64>(const ::string & str)
{

   return (::i32) ::atoi(str);

}


template <  >
inline double __conv<double>(const ::string & str)
{

   return (::i32) ::atoi(str);

}


template < typename TYPE >
inline string __xmlpri()
{

   return "%";

}


template < >
inline string __xmlpri<::i32>()
{

   return "%" PRId32;

}


template < >
inline string __xmlpri<i64>()
{

   return "%" PRId64;

}


template < >
inline string __xmlpri<double>()
{

   return "%f";

}





namespace geometry
{

   //////////////////////////////////////////////////////////////////////
   //
   // Function Name: deflate
   //
   // Purpose:
   // Change rectangle dimension using its dimensions and the specified
   // rates. For example, the dLeftRate machine the left position of the
   // rectangle. If 0.0, it remains the same as the original left.
   // If 1.0, it turns as the original right. If 0.4, it will be 40%
   // of the width from left to right.
   //
   // Output:
   // -1 if the creation of the ::user::impact failed.
   // 0 if the creation of the ::user::impact succeeded.
   //
   // Author:
   // Vanessa Testoni
   //
   //
   //////////////////////////////////////////////////////////////////////
   template < primitive_rectangle RECTANGLE >
   inline void deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate)
   {

      rectangle.left = range_rate(rectangle.left, rectangle.right, dLeftRate);

      rectangle.right = range_rate(rectangle.right, rectangle.left, dRightRate);

      rectangle.top = range_rate(rectangle.top, rectangle.bottom, dTopRate);

      rectangle.bottom = range_rate(rectangle.bottom, rectangle.top, dBottomRate);

   }


} // namespace geometry


template < primitive_point POINT >
inline ::string __string(const POINT & point)
{

   return __string(point.x) + ", " + __string(point.y);

}


template < primitive_size SIZE >
inline ::string __string(const SIZE & size)
{

   return __string(size.cx) + ", " + __string(size.cy);

}


#include "arc.h"

#include "line.h"

#include "lines.h"

#include "ellipse.h"


template < primitive_point POINT >
inline ::string __string(const POINT & point);


template < primitive_size SIZE >
inline ::string __string(const SIZE & size);







