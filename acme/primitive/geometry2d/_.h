#pragma once


namespace geometry2d
{


   class region;
   class item;


} // namespace geometry2d


DECLARE_ENUMERATION(e_align, enum_align);


#include "_struct.h"


#include "_i32.h"
#include "_i64.h"
#include "_f32.h"
#include "_f64.h"


//template < typename TARGET, typename SOURCE >
//inline TARGET & _001CopyRect(TARGET & prectTarget, const SOURCE & prectSource);


//template < primitive_rectangle RECTANGLE_TYPE, typename X >
//inline RECTANGLE_TYPE & x_offset(RECTANGLE_TYPE & rectangle, X x)
//{
//
//   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left + x);
//
//   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right + x);
//
//   return rectangle;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename Y >
//inline RECTANGLE_TYPE & y_offset(RECTANGLE_TYPE & rectangle, Y y)
//{
//
//   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top + y);
//
//   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom + y);
//
//   return rectangle;
//
//}
//
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename X >
//inline RECTANGLE_TYPE & x_subtract(RECTANGLE_TYPE & rectangle, X x)
//{
//
//   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left - x);
//
//   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right - x);
//
//   return rectangle;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename Y >
//inline RECTANGLE_TYPE & y_subtract(RECTANGLE_TYPE & rectangle, Y y)
//{
//
//   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top - y);
//
//   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom - y);
//
//   return rectangle;
//
//}
//
//
//template < typename RECTANGLE_TYPE, typename X, typename Y >
//inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, X x, Y y)
//{
//
//   x_offset(rectangle, x);
//
//   y_offset(rectangle, y);
//
//   return rectangle;
//
//}
//
//
//template < typename RECTANGLE_TYPE, typename X, typename Y >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, X x, Y y)
//{
//
//   x_subtract(rectangle, x);
//
//   y_subtract(rectangle, y);
//
//   return rectangle;
//
//}
//
//
//template < typename RECTANGLE_TYPE, primitive_point POINT_TYPE >
//inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
//{
//
//   return offset(rectangle, point.x(), point.y());
//
//}
//
//
//template < typename RECTANGLE_TYPE, primitive_point POINT_TYPE >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
//{
//
//   return subtract(rectangle, point.x(), point.y());
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT & point) { return subtract(rectangle, point); }
//
//
//template < primitive_point POINT, typename X, typename Y >
//inline POINT & offset(POINT & point, X x, Y y)
//{
//
//   point.x() = (decltype(POINT::x))(point.x() + x);
//   point.y() = (decltype(POINT::y))(point.y() + y);
//
//   return point;
//
//}
//
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & offset(POINT & point, const POINT2 & point2)
//{
//
//   return offset(point, point2.x(), point2.y());
//
//}
//
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & add(POINT & point, const POINT2 & point2) { return offset(point, point2); }
//
//
//template < primitive_point POINT_TYPE, typename X, typename Y >
//inline POINT_TYPE & subtract(POINT_TYPE & point, X x, Y y)
//{
//
//   point.x() = (decltype(POINT_TYPE::x))(point.x() - x);
//   point.y() = (decltype(POINT_TYPE::y))(point.y() - y);
//
//   return point;
//
//}
//
//
//template < primitive_point POINT_TYPE, primitive_point POINT_TYPE2 >
//inline POINT_TYPE & subtract(POINT_TYPE & point, const POINT_TYPE2 & point2)
//{
//
//   return subtract(point, point2.x(), point2.y());
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle POINT_TYPE >
//inline RECTANGLE_TYPE & add(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
//{ 
//   
//   return offset(rectangle, point); 
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   auto left = maximum(rect1.left, rect2.left);
//
//   auto right = minimum(rect1.right, rect2.right);
//
//   bool bIntersect = right > left;
//
//   if (!bIntersect)
//   {
//
//      left = 0; right = 0;
//
//   }
//
//   if (::is_set(rectangle))
//   {
//
//      rectangle.left = left;
//
//      rectangle.right = right;
//
//   }
//
//   return bIntersect;
//
//}
//
//
//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   auto left = maximum(rect1.left, rect2.left);
//
//   auto right = minimum(rect1.right, rect2.right);
//
//   return right > left;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   auto top = maximum(rect1.top, rect2.top);
//
//   auto bottom = minimum(rect1.bottom, rect2.bottom);
//
//   bool bIntersect = bottom > top;
//
//   if (!bIntersect)
//   {
//
//      top = 0; bottom = 0;
//
//   }
//
//   if (::is_set(rectangle))
//   {
//
//      rectangle.top = top;
//
//      rectangle.bottom = bottom;
//
//   }
//
//   return bIntersect;
//
//}
//
//
//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   auto top = maximum(rect1.top, rect2.top);
//
//   auto bottom = minimum(rect1.bottom, rect2.bottom);
//
//   return bottom > top;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   if (x_intersect(rectangle, rect1, rect2) && y_intersect(rectangle, rect1, rect2))
//   {
//
//      return true;
//
//   }
//
//   if (::is_set(rectangle))
//   {
//
//      null(rectangle);
//
//   }
//
//   return false;
//
//}
//
//
//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   return x_intersects(rect1, rect2) && y_intersects(rect1, rect2);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   auto left = maximum(rect1.left, rect2.left);
//
//   auto right = minimum(rect1.right, rect2.right);
//
//   bool bIntersect = right >= left;
//
//   if (!bIntersect)
//   {
//
//      left = 0; right = 0;
//
//   }
//
//   if (::is_set(rectangle))
//   {
//
//      rectangle.left = left;
//
//      rectangle.right = right;
//
//   }
//
//   return bIntersect;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   auto top = maximum(rect1.top, rect2.top);
//
//   auto bottom = minimum(rect1.bottom, rect2.bottom);
//
//   bool bIntersect = bottom >= top;
//
//   if (!bIntersect)
//   {
//
//      top = 0; bottom = 0;
//
//   }
//
//   if (::is_set(rectangle))
//   {
//
//      rectangle.top = top;
//
//      rectangle.bottom = bottom;
//
//   }
//
//   return bIntersect;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   if (x_null_intersect_rect(rectangle, rect1, rect2) && y_null_intersect_rect(rectangle, rect1, rect2))
//   {
//
//      return true;
//
//   }
//
//   if (::is_set(rectangle))
//   {
//
//      null(rectangle);
//
//   }
//
//   return false;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   rectangle.left = maximum(rect1.left, rect2.left);
//
//   rectangle.right = minimum(rect1.right, rect2.right);
//
//   return rectangle.right > rectangle.left || (rectangle.right == rectangle.left && rect1.left == rect2.left);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_top_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   rectangle.top = maximum(rect1.top, rect2.top);
//
//   rectangle.bottom = minimum(rect1.bottom, rect2.bottom);
//
//   return rectangle.top < rectangle.bottom || (rectangle.top == rectangle.bottom && rect1.top == rect2.top);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool top_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   if (x_left_null_intersect(rectangle, rect1, rect2) && y_top_null_intersect(rectangle, rect1, rect2))
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      null(rectangle);
//
//      return false;
//
//   }
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//RECTANGLE_TYPE & unite(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   if (is_empty_rectangle(rect1))
//   {
//
//      if (is_empty_rectangle(rect2))
//      {
//
//         null(rectangle);
//
//      }
//      else
//      {
//
//         copy(rectangle, rect2);
//
//      }
//
//   }
//   else if (is_empty_rectangle(rect1))
//   {
//
//      copy(rectangle, rect1);
//
//   }
//   else
//   {
//
//      rectangle.left = (decltype(RECTANGLE_TYPE::left))minimum(rect1.left, rect2.left);
//      rectangle.top = (decltype(RECTANGLE_TYPE::top))minimum(rect1.top, rect2.top);
//      rectangle.right = (decltype(RECTANGLE_TYPE::right))maximum(rect1.right, rect2.right);
//      rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))maximum(rect1.bottom, rect2.bottom);
//
//   }
//
//   return rectangle;
//
//}
//
//
//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//RECT_TYPE1 & unite(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   if (is_empty_rectangle(rect1))
//   {
//
//      if (is_empty_rectangle(rect2))
//      {
//
//         null(rect1);
//
//      }
//      else
//      {
//
//         copy(rect1, rect2);
//
//      }
//
//   }
//   else if (!is_empty_rectangle(rect2))
//   {
//
//      rect1.left = (decltype(RECT_TYPE1::left))minimum(rect1.left, rect2.left);
//      rect1.top = (decltype(RECT_TYPE1::top))minimum(rect1.top, rect2.top);
//      rect1.right = (decltype(RECT_TYPE1::right))maximum(rect1.right, rect2.right);
//      rect1.bottom = (decltype(RECT_TYPE1::bottom))maximum(rect1.bottom, rect2.bottom);
//
//   }
//
//   return rect1;
//
//}
//


//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//RECT_TYPE1 & copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   rect1.left = (decltype(RECT_TYPE1::left))rect2.left;
//   rect1.top = (decltype(RECT_TYPE1::top))rect2.top;
//   rect1.right = (decltype(RECT_TYPE1::right))rect2.right;
//   rect1.bottom = (decltype(RECT_TYPE1::bottom))rect2.bottom;
//
//   return rect1;
//
//}
//
//
//template < primitive_rectangle RECTANGLE, primitive_XYDim XYDim >
//RECTANGLE & copy(RECTANGLE & rectangle, const XYDim & xydim)
//{
//
//   rectangle.left = (decltype(RECTANGLE::left))xydim.X;
//   rectangle.top = (decltype(RECTANGLE::top))xydim.Y;
//   rectangle.right = (decltype(RECTANGLE::right))(xydim.X + xydim.Width);
//   rectangle.bottom = (decltype(RECTANGLE::bottom))(xydim.Y + xydim.Height);
//
//   return rectangle;
//
//}
//
//
//template < primitive_rectangle RECTANGLE, primitive_xydim XYDIM >
//RECTANGLE & copy(RECTANGLE & rect1, const XYDIM & xydim)
//{
//
//   rect1.left = (decltype(RECTANGLE::left))xydim.x();
//   rect1.top = (decltype(RECTANGLE::top))xydim.y();
//   rect1.right = (decltype(RECTANGLE::right))(xydim.x() + xydim.width);
//   rect1.bottom = (decltype(RECTANGLE::bottom))(xydim.y() + xydim.height);
//
//   return rect1;
//
//}
//
//
//template < primitive_XY POINT1, primitive_point POINT2 >
//POINT1 & copy(POINT1 & point1, const POINT2 & point2)
//{
//
//   point1.X = (decltype(POINT1::X))point2.x();
//   point1.Y = (decltype(POINT1::Y))point2.y();
//
//   return point1;
//
//}
//
//
//template < primitive_point POINT1, primitive_XY POINT2 >
//POINT1 & copy(POINT1 & point1, const POINT2 & point2)
//{
//
//   point1.x() = (decltype(POINT1::x))point2.X;
//   point1.y() = (decltype(POINT1::y))point2.Y;
//
//   return point1;
//
//}
//
//
//template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
//XYDim & copy(XYDim & xydim, const RECTANGLE & rectangle)
//{
//
//   xydim.X = (decltype(XYDim::X))rectangle.left;
//   xydim.Y = (decltype(XYDim::Y))rectangle.top;
//   xydim.Width = (decltype(XYDim::Width))(rectangle.right - rectangle.left);
//   xydim.Height = (decltype(XYDim::Height))(rectangle.bottom - rectangle.top);
//
//   return xydim;
//
//}
//
//
//template < primitive_xydim XYDIM, primitive_rectangle RECTANGLE >
//XYDIM & copy(XYDIM & xydim, const RECTANGLE & rectangle)
//{
//
//   xydim.x() = (decltype(XYDIM::X))rectangle.left;
//   xydim.y() = (decltype(XYDIM::Y))rectangle.top;
//   xydim.width = (decltype(XYDIM::Width))(rectangle.right - rectangle.left);
//   xydim.height = (decltype(XYDIM::Height))(rectangle.bottom - rectangle.top);
//
//   return xydim;
//
//}
//
//
//template < primitive_XYDim XYDim1, primitive_XYDim XYDim2 >
//XYDim1 & copy(XYDim1 & xydim1, const XYDim2 & xydim2)
//{
//
//   xydim1.X = (decltype(XYDim1::X))xydim2.X;
//   xydim1.Y = (decltype(XYDim1::Y))xydim2.Y;
//   xydim1.Width = (decltype(XYDim1::Width))xydim2.Width;
//   xydim1.Height = (decltype(XYDim1::Height))xydim2.Height;
//
//   return xydim1;
//
//}
//
//
//template < primitive_point POINT1, primitive_point POINT2 >
//POINT1 & copy(POINT1 & point1, const POINT2 & point2)
//{
//
//   point1.x() = (decltype(POINT1::x))point2.x();
//   point1.y() = (decltype(POINT1::y))point2.y();
//
//   return point1;
//
//}
//
//
//template < primitive_point POINT, primitive_size SIZE >
//POINT & copy(POINT & point, const SIZE & size)
//{
//
//   point.x() = (decltype(POINT::x))size.cx();
//   point.y() = (decltype(POINT::y))size.cy();
//
//   return point;
//
//}
//
//
//template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
//SIZE_TYPE1 & copy_size(SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2)
//{
//
//   size1.cx() = (decltype(SIZE_TYPE1::cx))size2.cx();
//   size1.cy() = (decltype(SIZE_TYPE1::cy))size2.cy();
//
//   return size1;
//
//}
//
//
//template < typename X, typename Y >
//auto get_dimension(enum_orientation eorientation, X x, Y y);
//
//
//template < typename X, typename Y >
//auto get_normal_dimension(enum_orientation eorientation, X x, Y y);
//
//
//template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
//bool is_equal(const RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
//{
//
//   return rectangle1.left == rectangle2.left && rectangle1.top == rectangle2.top
//      && rectangle1.right == rectangle2.right && rectangle1.bottom == rectangle2.bottom;
//
//}
//
//
//template < primitive_point POINT1, primitive_point POINT2 >
//bool is_equal(const POINT1 & point1, const POINT2 & point2)
//{
//
//   return point1.x() == point2.x() && point1.y() == point2.y();
//
//}
//
//
//template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
//bool is_equal(const SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2)
//{
//
//   return size1.cx() == size2.cx() && size1.cy() == size2.cy();
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
//RECTANGLE_TYPE & set_rectangle(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
//{
//
//   rectangle.left = (decltype(RECTANGLE_TYPE::left))l;
//   rectangle.top = (decltype(RECTANGLE_TYPE::top))t;
//   rectangle.right = (decltype(RECTANGLE_TYPE::right))r;
//   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))b;
//
//   return rectangle;
//
//}
//
//
//template < primitive_rectangle RECTANGLE, typename L, typename T, typename W, typename H >
//RECTANGLE & set_dim(RECTANGLE & rectangle, L l, T t, W w, H h)
//{
//
//   rectangle.left = (decltype(RECTANGLE::left))l;
//   rectangle.top = (decltype(RECTANGLE::top))t;
//   rectangle.right = (decltype(RECTANGLE::right))(l + w);
//   rectangle.bottom = (decltype(RECTANGLE::bottom))(t + h);
//
//   return rectangle;
//
//}
//
////template < primitive_rectangle RECTANGLE,  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(RECTANGLE &r, L l, T t, W w, H h) { return set_dim(p, l, t, w, h); }
////template <  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(::rectangle_i64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
////template <  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(::rectangle_f32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
////template <  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(::rectangle_f64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
//RECTANGLE & set_bottom_right(RECTANGLE & rectangle, const SIZE & size)
//{
//
//   rectangle.right = (decltype(RECTANGLE::right))(rectangle.left + size.cx());
//   rectangle.bottom = (decltype(RECTANGLE::bottom))(rectangle.top + size.cy());
//
//   return rectangle;
//
//}
//
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
//RECTANGLE & assign(RECTANGLE & rectangle, const POINT & point, const SIZE & size)
//{
//
//   rectangle.left = (decltype(RECTANGLE::left))point.x();
//   rectangle.top = (decltype(RECTANGLE::top))point.y();
//   rectangle.right = (decltype(RECTANGLE::right))(point.x() + size.cx());
//   rectangle.bottom = (decltype(RECTANGLE::bottom))(point.y() + size.cy());
//
//   return rectangle;
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//RECTANGLE_TYPE & null(RECTANGLE_TYPE & rectangle)
//{
//
//   return ::set_rectangle(rectangle, 0, 0, 0, 0);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto width(RECTANGLE_TYPE & rectangle) { return rectangle.right - rectangle.left; }
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto height(RECTANGLE_TYPE & rectangle) { return rectangle.bottom - rectangle.top; }
//
//
//template < typename W, typename H >
//constexpr H area(W w, H h) { return (w <= (W)0 || h <= (H)0) ? 0 : (H)(w * h); }
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto area(RECTANGLE_TYPE & rectangle) { return area(width(rectangle), height(rectangle)); }
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto is_empty_rectangle(RECTANGLE_TYPE & rectangle) { return ::is_null(rectangle) || rectangle.right <= rectangle.left || rectangle.bottom <= rectangle.top; }
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//bool is_null_rectangle(const RECTANGLE_TYPE & rectangle)
//{
//
//   return rectangle.left == (decltype(RECTANGLE_TYPE::left))0
//      && rectangle.top == (decltype(RECTANGLE_TYPE::top))0
//      && rectangle.right == (decltype(RECTANGLE_TYPE::right))0
//      && rectangle.bottom == (decltype(RECTANGLE_TYPE::bottom))0;
//
//}
//
//
//template < primitive_size SIZE_TYPE >
//bool is_null(const SIZE_TYPE & size)
//{
//
//   return size.cx() == (decltype(SIZE_TYPE::cx))0
//      && size.cy() == (decltype(SIZE_TYPE::cy))0;
//
//}
//
//
//template < primitive_point POINT_TYPE >
//bool is_null(const POINT_TYPE & point)
//{
//
//   return point.x() == (decltype(POINT_TYPE::cx))0 && point.y() == (decltype(POINT_TYPE::cy))0;
//
//}
//
//
//template < primitive_rectangle RECTANGLE, typename X >
//inline bool contains_x(const RECTANGLE & rectangle, X x)
//{
//
//   return x >= rectangle.left && x <= rectangle.right;
//
//}
//
//
//template < primitive_rectangle RECTANGLE, typename Y >
//inline bool contains_y(const RECTANGLE & rectangle, Y y)
//{
//
//   return y >= rectangle.top && y <= rectangle.bottom;
//
//}
//
//
//template < typename RECTANGLE, typename X, typename Y >
//inline bool contains(const RECTANGLE & rectangle, X x, Y y)
//{
//
//   return contains_x(rectangle, x) && contains_y(rectangle, y);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
//{
//
//   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left - l);
//   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top - t);
//   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right + r);
//   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom + b);
//
//   return rectangle;
//
//}
//
//
//template < typename RECTANGLE_TYPE, typename RECT_TYPE2 >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
//{
//
//   return rect_inflate(rectangle, rect2.left, rect2.top, rect2.right, rect2.bottom);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename RECT_TYPE2 >
//inline RECTANGLE_TYPE & multiply_inline(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
//{
//
//   rectangle.left *= rect2.left;
//   rectangle.top *= rect2.top;
//   rectangle.right *= rect2.right;
//   rectangle.bottom *= rect2.bottom;
//
//   return rectangle;
//
//}
//
//template < primitive_rectangle RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
//{
//
//   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left + l);
//   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top + t);
//   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right - r);
//   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom - b);
//
//   return rectangle;
//
//}
//
//
//template < typename RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
//{
//
//   return deflate(rectangle, rect2.left, rect2.top, rect2.right, rect2.bottom);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename X, typename Y >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, X x, Y y)
//{
//
//   return inflate(rectangle, x, y, x, y);
//
//}
//
//template < primitive_rectangle RECTANGLE_TYPE, typename X, typename Y >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, X x, Y y)
//{
//
//   return deflate(rectangle, x, y, x, y);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename UNIT >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, UNIT u)
//{
//
//   return inflate(rectangle, u, u);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename UNIT >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, UNIT u)
//{
//
//   return deflate(rectangle, u, u);
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//inline RECTANGLE_TYPE & swap_left_right(RECTANGLE_TYPE & rectangle) { __swap(rectangle.left, rectangle.right); return rectangle; }
//
//
//
//template < primitive_point POINT1, primitive_point POINT2 >
//inline bool polygon_contains(const POINT1 * ppPolygon, i32 iCount, const POINT2 & point)
//{
//
//   int i, j = iCount - 1;
//
//   auto x = point.x();
//
//   auto y = point.y();
//
//   bool oddNodes = false;
//
//   for (i = 0; i < iCount; i++)
//   {
//
//      if (((ppPolygon[i].y() < y && ppPolygon[j].y() >= y) || (ppPolygon[j].y() < y && ppPolygon[i].y() >= y)) && (ppPolygon[i].x() <= x || ppPolygon[j].x() <= x))
//      {
//         
//         oddNodes ^= (ppPolygon[i].x() + (y - ppPolygon[i].y()) / (ppPolygon[j].y() - ppPolygon[i].y()) * (ppPolygon[j].x() - ppPolygon[i].x()) < x);
//
//      }
//
//      j = i;
//
//   }
//
//   return oddNodes;
//
//}
//
//
//template < typename SIZE_BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//class size_type;
//
//template < typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//class point_type;
//
//template < typename RECTANGLE_BASE_TYPE, typename POINT_TYPE, typename SIZE_TYPE >
//class rectangle_type;
//
//template < typename POINT_TYPE >
//class point_array_base;
//
//
//namespace design
//{
//
//   enum e_fit
//   {
//
//      fit_width = -1,
//      fit_match = 0,
//      fit_height = 1,
//
//   };
//
//
//
//   enum e_match
//   {
//
//      match_width = -1,
//      match_none = 0,
//      match_height = 1,
//
//   };
//
//
//} // namespace design
//
//
//
//#include "align.h"
//
//
//DECLARE_ENUMERATION(e_align, enum_align);
//
//
//inline ::i32 area(::i32 cx, ::i32 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
//inline i64 area(i64 cx, i64 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
//inline double area(double cx, double cy) { return (cx < 0. && cy < 0. ? -1. : 1.) * cx * cy; }
//
//
//
//struct ::size_i64;
//struct ::point_i64;
//struct ::rectangle_i64;
////::size_i32;
////class size_i64;
////class size_f64;
////::point_i32;
////class point_i64;
////class point_f64;
////::rectangle_f64;
////::rectangle_i64;
////::rectangle_f64;
//
//typedef uchar      byte;
//
//struct ::point_i64;
//struct ::size_i64;
//struct ::rectangle_i64;
//struct ::point_f64;
//struct ::size_f64;
//struct ::rectangle_f64;
//
//
//
//using point_i32 = point_type < ::point_i32, ::size_i32, ::rectangle_i32 >;
//using point_i64 = point_type < ::point_i64, ::size_i64, ::rectangle_i64 >;
//using point_f32 = point_type < ::point_f32, ::size_f32, ::rectangle_f32 >;
//using point_f64 = point_type < ::point_f64, ::size_f64, ::rectangle_f64 >;
//
//
//using size_i32 = size_type < ::size_i32, ::point_i32, ::rectangle_i32 >;
//using size_i64 = size_type < ::size_i64, ::point_i64, ::rectangle_i64 >;
//using size_f32 = size_type < ::size_f32, ::point_f32, ::rectangle_f32 >;
//using size_f64 = size_type < ::size_f64, ::point_f64, ::rectangle_f64 >;
//
//
//using rectangle_i32 = rectangle_type < ::rectangle_i32, ::point_i32, ::size_i32 >;
//using rectangle_i64 = rectangle_type < ::rectangle_i64, ::point_i64, ::size_i64 >;
//using rectangle_f32 = rectangle_type < ::rectangle_f32, ::point_f32, ::size_f32 >;
//using rectangle_f64 = rectangle_type < ::rectangle_f64, ::point_f64, ::size_f64 >;
//
//
//using point_i32_array = point_array_base < point_i32 >;
//using point_i64_array = point_array_base < point_i64 >;
//using point_f32_array = point_array_base < point_f32 >;
//using point_f64_array = point_array_base < point_f64 >;
//
//
//using rectangle = ::rectangle_f64;
//
//
////inline float i32muldiv(float f, i32 iNum, i32 iDen);
////inline double i32muldiv(double d, i32 iNum, i32 iDen);
////inline i32 i32muldiv(i32 i, i32 iNum, i32 iDen);
////#ifndef WINDOWS
////inline i64 MulDiv(i64 nNumber, i32 iNum, i32 iDen);
////#endif
////inline i64 i32muldiv(i64 i, i64 iNum, i64 iDen);
//
//
//template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3, primitive_integral INTEGRAL_RESULT = typename ::largest_type_of_3 < INTEGRAL1, INTEGRAL2, INTEGRAL3 >::type >
//inline INTEGRAL_RESULT muldiv(INTEGRAL1 i, INTEGRAL2 iNumerator, INTEGRAL3 iDenominator);
//
//
//template < primitive_rectangle RECTANGLE >
//inline auto width(const RECTANGLE & rectangle) { return rectangle.right - rectangle.left; }
//
//template < primitive_rectangle RECTANGLE >
//inline auto height(const RECTANGLE & rectangle) { return rectangle.bottom - rectangle.top; }
//
//template < primitive_rectangle RECTANGLE >
//inline auto area(const RECTANGLE & rectangle) { return maximum(width(rectangle), 0) * maximum(height(rectangle), 0); }
//
//
//template < primitive_rectangle RECTANGLE >
//inline auto left(const RECTANGLE & rectangle) { return rectangle.left; }
//
//template < primitive_rectangle RECTANGLE >
//inline auto top(const RECTANGLE & rectangle) { return rectangle.top; }
//
//
//
//template < primitive_XYDim XYDim >
//inline auto width(const XYDim & rectangle) { return rectangle.Width; }
//
//template < primitive_XYDim XYDim >
//inline auto height(const XYDim & rectangle) { return rectangle.Height; }
//
//template < primitive_XYDim XYDim >
//inline auto area(const XYDim & rectangle) { return maximum(rectangle.Width, 0) * maximum(rectangle.Height, 0); }
//
//
//template < primitive_XYDim XYDim >
//inline auto left(const XYDim & rectangle) { return rectangle.X; }
//
//template < primitive_XYDim XYDim >
//inline auto top(const XYDim & rectangle) { return rectangle.Y; }
//
//
////template < primitive_rectangle RECTANGLE, primitive_XYDim XYDim >
////inline void copy(RECTANGLE & rectangle, const XYDim & xydim)
////{
////
////   rectangle.left = (decltype(rectangle.left)) xydim.X;
////   rectangle.top = (decltype(rectangle.top)) xydim.Y;
////   rectangle.right = (decltype(rectangle.right))(xydim.X + xydim.Width);
////   rectangle.bottom = (decltype(rectangle.bottom))(xydim.Y + xydim.Height);
////
////}
////
////
////template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
////inline void copy(XYDim & xydim, const RECTANGLE & rectangle)
////{
////
////   xydim.X = (decltype(xydim.X)) rectangle.left;
////   xydim.Y = (decltype(xydim.Y)) rectangle.top;
////   xydim.Width = (decltype(xydim.Width))(rectangle.right + rectangle.left);
////   xydim.Height = (decltype(xydim.Height))(rectangle.bottom + rectangle.top);
////
////}
//
//
//
////inline bool contains(const ::rectangle_i32 &rectangle, const ::point_i32 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::rectangle_i32 & null(::rectangle_i32 & rectDst) { return ::null_rect(rectDst); }
////inline bool is_equal(const ::rectangle_i32 &rect1, const ::rectangle_i32 &rect2) { return ::rect_equals(rect1, rect2); }
////inline ::rectangle_i32 & inflate(::rectangle_i32 & rectangle, ::i32 x, ::i32 y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::rectangle_i32 & deflate(::rectangle_i32 & rectangle, ::i32 x, ::i32 y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::rectangle_i32 & offset(::rectangle_i32 & rectangle, ::i32 x, ::i32 y) { return ::offset_rect(rectangle, x, y); }
////inline bool intersect(::rectangle_i32 & rectangle, const ::rectangle_i32 &rect1, const ::rectangle_i32 &rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::rectangle_i32 & unite(::rectangle_i32 & rectangle, const ::rectangle_i32 &rect1, const ::rectangle_i32 &rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline ::i32 width(const ::rectangle_i32 &rectangle) { return ::rect_width(rectangle); }
////inline ::i32 height(const ::rectangle_i32 &rectangle) { return ::rect_height(rectangle); }
////inline ::i32 area(const ::rectangle_i32 &rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::rectangle_i32 &rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::rectangle_i32 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }
//
////inline ::i32 width(const ::rectangle_i32 &rectangle) { return ::width(&rectangle); }
////inline ::i32 height(const ::rectangle_i32 &rectangle) { return ::height(&rectangle); }
////inline ::i32 area(const ::rectangle_i32 &rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::rectangle_i32 &rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::rectangle_i32 & rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//
//
////inline bool is_empty(::size_i32 & size) { return size.cx() <= 0 || size.cy() <= 0; }
////inline bool is_empty(::size_i64 & size) { return size.cx() <= 0 || size.cy() <= 0; }
////inline bool is_empty(::size_f32 & size) { return size.cx() <= 0.f || size.cy() <= 0.f; }
////inline bool is_empty(::size_f64 & size) { return size.cx() <= 0. || size.cy() <= 0.; }
//
//
//
//
//
//
//
//
////inline bool contains(const ::rectangle_i64 & rectangle, const ::point_i32 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::rectangle_i64 & null(::rectangle_i64 & rectDst) { return ::null_rect(rectDst); }
////inline bool is_equal(const ::rectangle_i64 & rect1, const ::rectangle_i64 & rect2) { return ::rect_equals(rect1, rect2); }
////inline ::rectangle_i64 & inflate(::rectangle_i64 & rectangle, i64 x, i64 y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::rectangle_i64 & deflate(::rectangle_i64 & rectangle, i64 x, i64 y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::rectangle_i64 & offset(::rectangle_i64 & rectangle, i64 x, i64 y) { return ::offset_rect(rectangle, x, y); }
////inline bool intersect(::rectangle_i64 & rectangle, const ::rectangle_i64 & rect1, const ::rectangle_i64 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::rectangle_i64 & unite(::rectangle_i64 & rectangle, const ::rectangle_i64 & rect1, const ::rectangle_i64 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline i64 width(const ::rectangle_i64 & rectangle) { return ::rect_width(rectangle); }
////inline i64 height(const ::rectangle_i64 & rectangle) { return ::rect_height(rectangle); }
////inline i64 area(const ::rectangle_i64 & rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::rectangle_i64 & rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::rectangle_i64 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }
//
////inline i64 width(const ::rectangle_i64 & rectangle) { return ::width(&rectangle); }
////inline i64 height(const ::rectangle_i64 & rectangle) { return ::height(&rectangle); }
////inline i64 area(const ::rectangle_i64 & rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::rectangle_i64 & rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::rectangle_i64 & rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//
//
//
//
////inline bool contains(const ::rectangle_f32 & rectangle, const ::point_f32 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::rectangle_f32 & null(::rectangle_f32 & rect) { return ::null_rect(rect); }
////inline bool is_equal(const ::rectangle_f32 & rect1, const ::rectangle_f32 & rect2) { return ::rect_equals(rect1, rect2); }
////inline ::rectangle_f32 & inflate(::rectangle_f32 & rectangle, float x, float y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::rectangle_f32 & deflate(::rectangle_f32 & rectangle, float x, float y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::rectangle_f32 & offset(::rectangle_f32 & rectangle, float x, float y) { return ::offset_rect(rectangle, x, y); }
////inline bool intersect(::rectangle_f32 & rectangle, const ::rectangle_f32 & rect1, const ::rectangle_f32 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::rectangle_f32 & unite(::rectangle_f32 & rectangle, const ::rectangle_f32 & rect1, const ::rectangle_f32 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline float width(const ::rectangle_f32 & rectangle) { return ::rect_width(rectangle); }
//////template < primitive_rectangle RECTANGLE > 
//////inline auto height(const RECTANGLE  & rectangle) { return ::rect_height(rectangle); }
//////template < primitive_rectangle RECTANGLE >
//////inline auto height(const RECTANGLE & rectangle) { return ::height(&rectangle); }
////inline float area(const ::rectangle_f32 & rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::rectangle_f32 & rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::rectangle_f32 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }
//
////inline float width(const ::rectangle_f32& rectangle) { return ::width(&rectangle); }
//////inline float height(const ::rectangle_f32& rectangle) { return ::height(&rectangle); }
////inline float area(const ::rectangle_f32& rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::rectangle_f32& rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::rectangle_f32& rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//
//
//
////inline bool contains(const ::rectangle_f64 & rectangle, const ::point_f64 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::rectangle_f64 & null(::rectangle_f64 & rect) { return ::null_rect(rect); }
////inline bool is_equal(const ::rectangle_f64 & rect1, const ::rectangle_f64 & rect2) { return ::rect_equals(rect1, rect2); }
////inline ::rectangle_f64 & inflate(::rectangle_f64 & rectangle, double x, double y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::rectangle_f64 & deflate(::rectangle_f64 & rectangle, double x, double y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::rectangle_f64 & offset(::rectangle_f64 & rectangle, double x, double y) { return ::offset_rect(rectangle, x, y); }
//
//template < primitive_rectangle RECTANGLE >
//inline RECTANGLE & rate_deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);
//
//
////inline bool intersect(::rectangle_f64 & rectangle, const ::rectangle_f64 & rect1, const ::rectangle_f64 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::rectangle_f64 & unite(::rectangle_f64 & rectangle, const ::rectangle_f64 & rect1, const ::rectangle_f64 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline double width(const ::rectangle_f64 & rectangle) { return ::rect_width(rectangle); }
//////inline double height(const ::rectangle_f64  & rectangle) { return ::rect_height(rectangle); }
////inline double area(const ::rectangle_f64 & rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::rectangle_f64 & rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::rectangle_f64 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }
//
////inline double width(const ::rectangle_f64 & rectangle) { return ::width(&rectangle); }
////inline double height(const ::rectangle_f64& rectangle) { return ::height(&rectangle); }
////inline double area(const ::rectangle_f64 & rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::rectangle_f64 & rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::rectangle_f64 & rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator -= (POINT & point, const POINT2 & pointOffset) { ::subtract(point, pointOffset); return point; }
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator += (POINT & point, const POINT2 & pointOffset) { ::subtract(point, pointOffset); return point; }
//
////inline ::point_i64 & operator -= (::point_i64 & point, const ::point_i64 & pointOffset) { ::point_sub(point, pointOffset); return point; }
////inline ::point_i64 & operator += (::point_i64 & point, const ::point_i64 & pointOffset) { ::point_add(point, pointOffset); return point; }
////inline ::point_f32 & operator -= (::point_f32 & point, const ::point_f32 & pointOffset) { ::point_sub(point, pointOffset); return point; }
////inline ::point_f32 & operator += (::point_f32 & point, const ::point_f32 & pointOffset) { ::point_add(point, pointOffset); return point; }
////inline ::point_f64 & operator -= (::point_f64 & point, const ::point_f64 & pointOffset) { ::point_sub(point, pointOffset); return point; }
////inline ::point_f64 & operator += (::point_f64 & point, const ::point_f64 & pointOffset) { ::point_add(point, pointOffset); return point; }
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator -= (RECTANGLE & rectangle, const POINT & point) { ::subtract(rectangle, point); return rectangle; }
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator += (RECTANGLE & rectangle, const POINT & point) { ::subtract(rectangle, point); return rectangle; }
//
////inline ::rectangle_i64& operator -= (::rectangle_i64& rectangle, const ::point_i64& point) { ::rect_sub(rectangle, point); return rectangle; }
////inline ::rectangle_i64& operator += (::rectangle_i64& rectangle, const ::point_i64& point) { ::rect_add(rectangle, point); return rectangle; }
////inline ::rectangle_f32& operator -= (::rectangle_f32& rectangle, const ::point_f32& point) { ::rect_sub(rectangle, point); return rectangle; }
////inline ::rectangle_f32& operator += (::rectangle_f32& rectangle, const ::point_f32& point) { ::rect_add(rectangle, point); return rectangle; }
////inline ::rectangle_f64& operator -= (::rectangle_f64& rectangle, const ::point_f64& point) { ::rect_sub(rectangle, point); return rectangle; }
////inline ::rectangle_f64& operator += (::rectangle_f64& rectangle, const ::point_f64& point) { ::rect_add(rectangle, point); return rectangle; }
//
////inline bool deflate(::rectangle_i32  & rectangle, const ::rectangle_i32 & prectParam);
//
//
////#include "point.h"
////#include "size.h"
////#include "rectangle.h"
//
//
//
//#include "types.h"
//
//
////template < typename RECTANGLE_BASE_TYPE, typename POINT_BASE_TYPE >
////void get_bounding_box(RECTANGLE_BASE_TYPE & rect, const POINT_BASE_TYPE * lppoint, ::count count)
////{
////
////   if (count <= 0)
////   {
////
////      rect.left = 0;
////      rect.top = 0;
////      rect.right = 0;
////      rect.bottom = 0;
////
////   }
////   else
////   {
////      rect.left = lppoint[0].x();
////      rect.top = lppoint[0].y();
////      rect.right = lppoint[0].x();
////      rect.bottom = lppoint[0].y();
////
////      for (i32 i = 1; i < count; i++)
////      {
////         if (lppoint[i].x() < rect.left)
////            rect.left = lppoint[i].x();
////         else if (lppoint[i].x() > rect.right)
////            rect.right = lppoint[i].x();
////         if (lppoint[i].y() < rect.top)
////            rect.top = lppoint[i].y();
////         else if (lppoint[i].y() > rect.bottom)
////            rect.bottom = lppoint[i].y();
////      }
////
////   }
////
////}
//
//
////inline bool get_bounding_box(::rectangle_i32 & rectangleBounding, const ::rectangle_i32 &rectangle)
////{
////
////   copy(rectangleBounding, rectangle);
////
////   return true;
////
////}
//
//
////inline bool get_bounding_box(::rectangle_f64 & rectangleBounding, const ::rectangle_i32 &rectangle)
////{
////
////   copy(rectangleBounding, rectangle);
////
////   return true;
////
////}
////
////
////inline bool get_bounding_box(::rectangle_i32 & rectangleBounding, const ::rectangle_f64 & rectangle)
////{
////
////   copy(rectangleBounding, rectangle);
////
////   return true;
////
////}
////
////
////inline bool get_bounding_box(::rectangle_f64 & rectangleBounding, const ::rectangle_f64 & rectangle)
////{
////
////   copy(rectangleBounding, rectangle);
////
////   return true;
////
////}
////
////
////template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
////void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > ::get_bounding_box(const POINT_BASE_TYPE * ppoint, ::count count)
////{
////
////   ::get_bounding_box(*this, ppoint, count);
////
////}
////
////
////
////
////CLASS_DECL_ACME double d_distance(const point_i32 & point1, const point_i32 & point2);
////
////
////template < typename X, typename Y, typename W, typename H >
////inline rectangle_i32 rectangle_i32_dimension(X x, Y y, W w, H h)
////{
////
////   return rectangle_i32((i32)(x), (i32)(y), (i32)(x + w), (i32)(y + h));
////
////}
////
////
////template < typename X, typename Y, typename W, typename H >
////inline rectangle_i64 rectangle_i64_dimension(X x, Y y, W w, H h)
////{
////
////   return rectangle_i64((i64)x, (i64)y, (i64)(x + w), (i64)(y + h));
////
////}
////
////
////template < typename X, typename Y, typename W, typename H >
////inline rectangle_f32 rectangle_f32_dimension(X x, Y y, W w, H h)
////{
////
////   return rectangle_f32((f32)x, (f32)y, (f32)(x + w), (f32)(y + h));
////
////}
////
////
////template < typename X, typename Y, typename W, typename H >
////inline rectangle_f64 rectangle_f64_dimension(X x, Y y, W w, H h)
////{
////
////   return rectangle_f64((f64)x, (f64)y, (f64)(x + w), (f64)(y + h));
////
////}
//
//
//
////#ifdef UNIVERSAL_WINDOWS
////
////inline void copy(rectangle_i32 & rectDst, const ::winrt::Windows::Foundation::Rect * prectSrc)
////{
////   rectDst->left = (::i32) prectSrc->X;
////   rectDst->top = (::i32)prectSrc->Y;
////   rectDst->right = (::i32) (prectSrc->X + prectSrc->Width);
////   rectDst->bottom = (::i32) (prectSrc->Y + prectSrc->Height);
////}
////
////inline void copy(::winrt::Windows::Foundation::Rect& rectDst, rectangle_i32* prectSrc)
////{
////   rectDst->X = (float) prectSrc->left;
////   rectDst->Y = (float) prectSrc->top;
////   rectDst->Width = (float) prectSrc->width();
////   rectDst->Height = (float) prectSrc->height();
////}
////
////#endif
//
//
////inline auto ::point_i32(const ::lparam & lparam) noexcept { return ::point_i32(lparam.x(), lparam.y()); }
////inline auto ::point_i32(const ::u32 u) noexcept { return ::point_i32((::i32)__u32x(u), (::i32)__u32y(u)); }
////inline auto ::point_i32(const ::u64 u) noexcept { return ::point_i32((::i32)__u64x(u), (::i32)__u64y(u)); }
////inline auto ::point_i32(const ::size_i32 & size) noexcept { return ::point_i32(size.cx(), size.cy()); }
////
////inline auto __point64(const ::lparam & lparam) noexcept { return ::point_i64(lparam.x(), lparam.y()); }
////inline auto __point64(const ::u32 u) noexcept { return ::point_i64((i64)__u32x(u), (i64)__u32y(u)); }
////inline auto __point64(const ::u64 u) noexcept { return ::point_i64((i64)__u64x(u), (i64)__u64y(u)); }
////inline auto __point64(const ::size_i64 & size) noexcept { return ::point_i64(size.cx(), size.cy()); }
////
////
////inline auto __pointf(const ::lparam & lparam) noexcept { return ::point_f32((float)lparam.x(), (float)lparam.y()); }
////inline auto __pointf(const ::u32 u) noexcept { return ::point_f32((float)__u32x(u), (float)__u32y(u)); }
////inline auto __pointf(const ::u64 u) noexcept { return ::point_f32((float)__u64x(u), (float)__u64y(u)); }
////inline auto __pointf(const ::size_f32 & size) noexcept { return ::point_f32(size.cx(), size.cy()); }
////
////
////inline auto __pointd(const ::lparam & lparam) noexcept { return ::point_f64(lparam.x(), lparam.y()); }
////inline auto __pointd(const ::u32 u) noexcept { return ::point_f64((double)__u32x(u), (double)__u32y(u)); }
////inline auto __pointd(const ::u64 u) noexcept { return ::point_f64((double)__u64x(u), (double)__u64y(u)); }
////inline auto __pointd(const ::size_f64 & size) noexcept { return ::point_f64(size.cx(), size.cy()); }
//
////#ifdef UNIVERSAL_WINDOWS
////
////inline ::winrt::Windows::Foundation::Rect ScaleRect(::winrt::Windows::Foundation::Rect rectangle, double scale)
////{
////
////   rectangle.X = (float)(rectangle.X*scale);
////   rectangle.Y = (float)(rectangle.Y* scale);
////   rectangle.Width = (float)(rectangle.Width * scale);
////   rectangle.Height = (float)(rectangle.Height*scale);
////
////   return rectangle;
////
////}
////
////
////#endif
//
//
//
//
//
////template < typename RECT1, typename RECT2 >
////inline void expand_rect(RECT1 & rectangle, const RECT2 & r)
////{
////
////   if (::is_null(rectangle))
////   {
////
////      copy(rectangle, r);
////
////   }
////   else
////   {
////
////      rectangle.left = minimum((decltype(rectangle.left))rectangle.left, (decltype(rectangle.left))r.left);
////      rectangle.right = maximum((decltype(rectangle.right))rectangle.right, (decltype(rectangle.right))r.right);
////      rectangle.top = minimum((decltype(rectangle.top))rectangle.top, (decltype(rectangle.top))r.top);
////      rectangle.bottom = maximum((decltype(rectangle.bottom))rectangle.bottom, (decltype(rectangle.bottom))r.bottom);
////
////   }
////
////}
////
////
////template < typename RECT1, typename RECT2 >
////inline void collapse_rect(RECT1 & rectangle, const RECT2 & r)
////{
////
////   if (::is_rect_null(rectangle))
////   {
////
////      copy(rectangle, r);
////
////   }
////   else
////   {
////
////      rectangle.left = maximum((decltype(rectangle.left))rectangle.left, (decltype(rectangle.left))r.left);
////      rectangle.right = minimum((decltype(rectangle.right))rectangle.right, (decltype(rectangle.right))r.right);
////      rectangle.top = maximum((decltype(rectangle.top))rectangle.top, (decltype(rectangle.top))r.top);
////      rectangle.bottom = minimum((decltype(rectangle.bottom))rectangle.bottom, (decltype(rectangle.bottom))r.bottom);
////
////      if (::width(rectangle) == 0 || height(rectangle) == 0)
////      {
////
////         ::null_rect(rectangle);
////
////      }
////
////   }
////
////}
////
////
////template < primitive_point POINT >
////inline constexpr auto __horz(const POINT & point) { return point.x(); }
////template < primitive_point POINT >
////inline constexpr auto __vert(const POINT & point) { return point.y(); }
////template < primitive_size SIZE >
////inline constexpr auto __horz(const SIZE & size) { return size.cx(); }
////template < primitive_size SIZE >
////inline constexpr auto __vert(const SIZE & size) { return size.cy(); }
////
////inline point_i32 & top_left(const ::rectangle_i32 &rectangle) { return *(point_i32 *)&rectangle; }
////inline point_i32 & bottom_right(const ::rectangle_i32 &rectangle) { return *(point_i32 *)&rectangle.right; }
//////inline point_i32 & top_left(const ::rectangle_i32 &rectangle) { return top_left(&rectangle); }
//////inline point_i32 & bottom_right(const ::rectangle_i32 &rectangle) { return bottom_right(&rectangle); }
////
////
////inline point_i64 & top_left(const ::rectangle_i64 & rectangle) { return *(point_i64 *)&rectangle; }
////inline point_i64 & bottom_right(const ::rectangle_i64 & rectangle) { return *(point_i64 *)&rectangle.right; }
//////inline point_i64 & top_left(const ::rectangle_i64 & rectangle) { return top_left(&rectangle); }
//////inline point_i64 & bottom_right(const ::rectangle_i64 & rectangle) { return bottom_right(&rectangle); }
////
////
////inline point_f64 & top_left(const ::rectangle_f64 & rectangle) { return *(point_f64 *)&rectangle; }
////inline point_f64 & bottom_right(const ::rectangle_f64 & rectangle) { return *(point_f64 *)&rectangle.right; }
//////inline point_f64 & top_left(const ::rectangle_f64 & rectangle) { return top_left(&rectangle); }
//////inline point_f64 & bottom_right(const ::rectangle_f64 & rectangle) { return bottom_right(&rectangle); }
//
//
////template < typename X, typename Y >
////inline auto get_dimension(enum_orientation eorientation, X x, Y y)
////{
////
////   if (eorientation == e_orientation_horizontal)
////   {
////
////      return x;
////
////   }
////   else if (eorientation == e_orientation_vertical)
////   {
////
////      return y;
////
////   }
////   else
////   {
////
////      throw ::exception(error_bad_argument, "invalid orientation");
////
////   }
////
////}
////
////
////template < typename X, typename Y >
////inline auto get_normal_dimension(enum_orientation eorientation, X x, Y y)
////{
////
////   if (eorientation == e_orientation_vertical)
////   {
////
////      return x;
////
////   }
////   else if (eorientation == e_orientation_horizontal)
////   {
////
////      return y;
////
////   }
////   else
////   {
////
////      throw ::exception(error_bad_argument, "invalid orientation");
////
////   }
////
////}
//
//
////template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
////inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const POINT_TYPE & point) noexcept : size_type((size_type&)point_i32) {}
////
////
////template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
////inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const RECTANGLE_TYPE & rectangle) noexcept : size_type(rectangle.width(), rectangle.height()) {}
//
//
////template < typename UNIT_TYPE >
////inline UNIT_TYPE __conv(const ::string & str)
////{
////
////   return (UNIT_TYPE)str;
////
////}
////
////
////template <  >
////inline ::i32 __conv<::i32>(const ::string & str)
////{
////
////   return (::i32) ::atoi(str);
////
////}
////
////
////template <  >
////inline i64 __conv<i64>(const ::string & str)
////{
////
////   return (::i32) ::atoi(str);
////
////}
////
////
////template <  >
////inline double __conv<double>(const ::string & str)
////{
////
////   return (::i32) ::atoi(str);
////
////}
////
////
////template < typename TYPE >
////inline string __xmlpri()
////{
////
////   return "%";
////
////}
////
////
////template < >
////inline string __xmlpri<::i32>()
////{
////
////   return "%" PRId32;
////
////}
////
////
////template < >
////inline string __xmlpri<i64>()
////{
////
////   return "%" PRId64;
////
////}
////
////
////template < >
////inline string __xmlpri<double>()
////{
////
////   return "%f";
////
////}
////
//
//
//
////
////namespace geometry
////{
////
////   //////////////////////////////////////////////////////////////////////
////   //
////   // Function Name: deflate
////   //
////   // Purpose:
////   // Change rectangle dimension using its dimensions and the specified
////   // rates. For example, the dLeftRate machine the left position of the
////   // rectangle. If 0.0, it remains the same as the original left.
////   // If 1.0, it turns as the original right. If 0.4, it will be 40%
////   // of the width from left to right.
////   //
////   // Output:
////   // -1 if the creation of the ::user::impact failed.
////   // 0 if the creation of the ::user::impact succeeded.
////   //
////   // Author:
////   // Vanessa Testoni
////   //
////   //
////   //////////////////////////////////////////////////////////////////////
////   template < primitive_rectangle RECTANGLE >
////   inline void deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate)
////   {
////
////      rectangle.left = range_rate(rectangle.left, rectangle.right, dLeftRate);
////
////      rectangle.right = range_rate(rectangle.right, rectangle.left, dRightRate);
////
////      rectangle.top = range_rate(rectangle.top, rectangle.bottom, dTopRate);
////
////      rectangle.bottom = range_rate(rectangle.bottom, rectangle.top, dBottomRate);
////
////   }
////
////
////} // namespace geometry
////
////
////template < primitive_point POINT >
////inline ::string as_string(const POINT & point)
////{
////
////   return as_string(point.x()) + ", " + as_string(point.y());
////
////}
////
////
////template < primitive_size SIZE >
////inline ::string as_string(const SIZE & size)
////{
////
////   return as_string(size.cx()) + ", " + as_string(size.cy());
////
////}
////
////
////#include "arc.h"
////
////#include "line.h"
////
////#include "lines.h"
////
////#include "ellipse.h"
////
////
////template < primitive_point POINT >
////inline ::string as_string(const POINT & point);
////
////
////template < primitive_size SIZE >
////inline ::string as_string(const SIZE & size);
////
////
////
////
////
//
//


template < primitive_number NUMBER >
class point_type;

template < primitive_number NUMBER >
class size_type;

template < primitive_number NUMBER >
class line_type;

template < primitive_number NUMBER >
class rectangle_type;

template < primitive_number NUMBER >
class ellipse_type;

template < primitive_number NUMBER >
class arc_type;

template < primitive_number NUMBER >
class point_array_base;

template < primitive_number NUMBER >
class polygon_type;

template < primitive_number NUMBER >
class poly_polygon_type;

template < primitive_number NUMBER >
class point_array_base;

template < primitive_number NUMBER >
class size_array_base;

template < primitive_number NUMBER >
class rectangle_array_base;

template < primitive_number NUMBER >
class lines_base;


using point_i32 = point_type < ::i32 >;
using point_i64 = point_type < ::i64 >;
using point_f32 = point_type < ::f32 >;
using point_f64 = point_type < ::f64 >;


using size_i32 = size_type < ::i32 >;
using size_i64 = size_type < ::i64 >;
using size_f32 = size_type < ::f32 >;
using size_f64 = size_type < ::f64 >;


using rectangle_i32 = rectangle_type < ::i32 >;
using rectangle_i64 = rectangle_type < ::i64 >;
using rectangle_f32 = rectangle_type < ::f32 >;
using rectangle_f64 = rectangle_type < ::f64 >;


using ellipse_i32 = ellipse_type < ::i32 >;
using ellipse_i64 = ellipse_type < ::i64 >;
using ellipse_f32 = ellipse_type < ::f32 >;
using ellipse_f64 = ellipse_type < ::f64 >;


using line_i32 = line_type < ::i32 >;
using line_i64 = line_type < ::i64 >;
using line_f32 = line_type < ::f32 >;
using line_f64 = line_type < ::f64 >;


using arc_i32 = arc_type < ::i32 >;
using arc_i64 = arc_type < ::i64 >;
using arc_f32 = arc_type < ::f32 >;
using arc_f64 = arc_type < ::f64 >;


using point_i32_array = point_array_base < ::i32 >;
using point_i64_array = point_array_base < ::i64 >;
using point_f32_array = point_array_base < ::f32 >;
using point_f64_array = point_array_base < ::f64 >;


using polygon_i32 = polygon_type < ::i32 >;
using polygon_i64 = polygon_type < ::i64 >;
using polygon_f32 = polygon_type < ::f32 >;
using polygon_f64 = polygon_type < ::f64 >;


using poly_polygon_i32 = poly_polygon_type < ::i32 >;
using poly_polygon_i64 = poly_polygon_type < ::i64 >;
using poly_polygon_f32 = poly_polygon_type < ::f32 >;
using poly_polygon_f64 = poly_polygon_type < ::f64 >;


using point_i32_array = point_array_base < ::i32 >;
using point_i64_array = point_array_base < ::i64 >;
using point_f32_array = point_array_base < ::f32 >;
using point_f64_array = point_array_base < ::f64 >;


using size_i32_array = size_array_base < ::i32 >;
using size_i64_array = size_array_base < ::i64 >;
using size_f32_array = size_array_base < ::f32 >;
using size_f64_array = size_array_base < ::f64 >;


using rectangle_i32_array = rectangle_array_base < ::i32 >;
using rectangle_i64_array = rectangle_array_base < ::i64 >;
using rectangle_f32_array = rectangle_array_base < ::f32 >;
using rectangle_f64_array = rectangle_array_base < ::f64 >;


using lines_i32 = lines_base < ::i32 >;
using lines_i64 = lines_base < ::i64 >;
using lines_f32 = lines_base < ::f32 >;
using lines_f64 = lines_base < ::f64 >;



