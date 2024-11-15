#pragma once


namespace geometry2d
{


   class region;
   class item;


   class matrix;


} // namespace geometry2d


DECLARE_ENUMERATION(e_align, enum_align);


#include "_struct.h"


#include "__double.h"
#include "__float.h"
#include "__int.h"
#include "__huge_integer.h"


//template < typename TARGET, typename SOURCE >
//inline TARGET & _001CopyRect(TARGET & prectTarget, const SOURCE & prectSource);


//template < primitive_rectangle RECTANGLE_TYPE, typename X >
//inline RECTANGLE_TYPE & x_offset(RECTANGLE_TYPE & rectangle, X x)
//{
//
//   rectangle.left() = (decltype(RECTANGLE_TYPE::left))(rectangle.left() + x);
//
//   rectangle.right() = (decltype(RECTANGLE_TYPE::right))(rectangle.right() + x);
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
//   rectangle.top() = (decltype(RECTANGLE_TYPE::top))(rectangle.top() + y);
//
//   rectangle.bottom() = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom() + y);
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
//   rectangle.left() = (decltype(RECTANGLE_TYPE::left))(rectangle.left() - x);
//
//   rectangle.right() = (decltype(RECTANGLE_TYPE::right))(rectangle.right() - x);
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
//   rectangle.top() = (decltype(RECTANGLE_TYPE::top))(rectangle.top() - y);
//
//   rectangle.bottom() = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom() - y);
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
//   auto left = maximum(rect1.left(), rect2.left());
//
//   auto right = minimum(rect1.right(), rect2.right());
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
//      rectangle.left() = left;
//
//      rectangle.right() = right;
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
//   auto left = maximum(rect1.left(), rect2.left());
//
//   auto right = minimum(rect1.right(), rect2.right());
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
//   auto top = maximum(rect1.top(), rect2.top());
//
//   auto bottom = minimum(rect1.bottom(), rect2.bottom());
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
//      rectangle.top() = top;
//
//      rectangle.bottom() = bottom;
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
//   auto top = maximum(rect1.top(), rect2.top());
//
//   auto bottom = minimum(rect1.bottom(), rect2.bottom());
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
//   auto left = maximum(rect1.left(), rect2.left());
//
//   auto right = minimum(rect1.right(), rect2.right());
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
//      rectangle.left() = left;
//
//      rectangle.right() = right;
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
//   auto top = maximum(rect1.top(), rect2.top());
//
//   auto bottom = minimum(rect1.bottom(), rect2.bottom());
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
//      rectangle.top() = top;
//
//      rectangle.bottom() = bottom;
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
//   rectangle.left() = maximum(rect1.left(), rect2.left());
//
//   rectangle.right() = minimum(rect1.right(), rect2.right());
//
//   return rectangle.right() > rectangle.left() || (rectangle.right() == rectangle.left() && rect1.left() == rect2.left());
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_top_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
//{
//
//   rectangle.top() = maximum(rect1.top(), rect2.top());
//
//   rectangle.bottom() = minimum(rect1.bottom(), rect2.bottom());
//
//   return rectangle.top() < rectangle.bottom() || (rectangle.top() == rectangle.bottom() && rect1.top() == rect2.top());
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
//      rectangle.left() = (decltype(RECTANGLE_TYPE::left))minimum(rect1.left(), rect2.left());
//      rectangle.top() = (decltype(RECTANGLE_TYPE::top))minimum(rect1.top(), rect2.top());
//      rectangle.right() = (decltype(RECTANGLE_TYPE::right))maximum(rect1.right(), rect2.right());
//      rectangle.bottom() = (decltype(RECTANGLE_TYPE::bottom))maximum(rect1.bottom(), rect2.bottom());
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
//      rect1.left() = (decltype(RECT_TYPE1::left))minimum(rect1.left(), rect2.left());
//      rect1.top() = (decltype(RECT_TYPE1::top))minimum(rect1.top(), rect2.top());
//      rect1.right() = (decltype(RECT_TYPE1::right))maximum(rect1.right(), rect2.right());
//      rect1.bottom() = (decltype(RECT_TYPE1::bottom))maximum(rect1.bottom(), rect2.bottom());
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
//   rect1.left() = (decltype(RECT_TYPE1::left))rect2.left();
//   rect1.top() = (decltype(RECT_TYPE1::top))rect2.top();
//   rect1.right() = (decltype(RECT_TYPE1::right))rect2.right();
//   rect1.bottom() = (decltype(RECT_TYPE1::bottom))rect2.bottom();
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
//   rectangle.left() = (decltype(RECTANGLE::left))xydim.X;
//   rectangle.top() = (decltype(RECTANGLE::top))xydim.Y;
//   rectangle.right() = (decltype(RECTANGLE::right))(xydim.X + xydim.Width);
//   rectangle.bottom() = (decltype(RECTANGLE::bottom))(xydim.Y + xydim.Height);
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
//   rect1.left() = (decltype(RECTANGLE::left))xydim.x();
//   rect1.top() = (decltype(RECTANGLE::top))xydim.y();
//   rect1.right() = (decltype(RECTANGLE::right))(xydim.x() + xydim.width);
//   rect1.bottom() = (decltype(RECTANGLE::bottom))(xydim.y() + xydim.height);
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
//   xydim.X = (decltype(XYDim::X))rectangle.left();
//   xydim.Y = (decltype(XYDim::Y))rectangle.top();
//   xydim.Width = (decltype(XYDim::Width))(rectangle.right() - rectangle.left());
//   xydim.Height = (decltype(XYDim::Height))(rectangle.bottom() - rectangle.top());
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
//   xydim.x() = (decltype(XYDIM::X))rectangle.left();
//   xydim.y() = (decltype(XYDIM::Y))rectangle.top();
//   xydim.width = (decltype(XYDIM::Width))(rectangle.right() - rectangle.left());
//   xydim.height = (decltype(XYDIM::Height))(rectangle.bottom() - rectangle.top());
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
//   return rectangle1.left() == rectangle2.left() && rectangle1.top() == rectangle2.top()
//      && rectangle1.right() == rectangle2.right() && rectangle1.bottom() == rectangle2.bottom();
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
//   rectangle.left() = (decltype(RECTANGLE_TYPE::left))l;
//   rectangle.top() = (decltype(RECTANGLE_TYPE::top))t;
//   rectangle.right() = (decltype(RECTANGLE_TYPE::right))r;
//   rectangle.bottom() = (decltype(RECTANGLE_TYPE::bottom))b;
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
//   rectangle.left() = (decltype(RECTANGLE::left))l;
//   rectangle.top() = (decltype(RECTANGLE::top))t;
//   rectangle.right() = (decltype(RECTANGLE::right))(l + w);
//   rectangle.bottom() = (decltype(RECTANGLE::bottom))(t + h);
//
//   return rectangle;
//
//}
//
////template < primitive_rectangle RECTANGLE,  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(RECTANGLE &r, L l, T t, W w, H h) { return set_dim(p, l, t, w, h); }
////template <  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(::huge_integer_rectangle * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
////template <  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(::float_rectangle * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
////template <  typename L, typename T, typename W, typename H >
////inline auto _001SetRectDim(::double_rectangle * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
//RECTANGLE & set_bottom_right(RECTANGLE & rectangle, const SIZE & size)
//{
//
//   rectangle.right() = (decltype(RECTANGLE::right))(rectangle.left() + size.cx());
//   rectangle.bottom() = (decltype(RECTANGLE::bottom))(rectangle.top() + size.cy());
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
//   rectangle.left() = (decltype(RECTANGLE::left))point.x();
//   rectangle.top() = (decltype(RECTANGLE::top))point.y();
//   rectangle.right() = (decltype(RECTANGLE::right))(point.x() + size.cx());
//   rectangle.bottom() = (decltype(RECTANGLE::bottom))(point.y() + size.cy());
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
//constexpr auto width(RECTANGLE_TYPE & rectangle) { return rectangle.right() - rectangle.left(); }
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto height(RECTANGLE_TYPE & rectangle) { return rectangle.bottom() - rectangle.top(); }
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
//constexpr auto is_empty_rectangle(RECTANGLE_TYPE & rectangle) { return ::is_null(rectangle) || rectangle.right() <= rectangle.left() || rectangle.bottom() <= rectangle.top(); }
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//bool is_null_rectangle(const RECTANGLE_TYPE & rectangle)
//{
//
//   return rectangle.left() == (decltype(RECTANGLE_TYPE::left))0
//      && rectangle.top() == (decltype(RECTANGLE_TYPE::top))0
//      && rectangle.right() == (decltype(RECTANGLE_TYPE::right))0
//      && rectangle.bottom() == (decltype(RECTANGLE_TYPE::bottom))0;
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
//   return x >= rectangle.left() && x <= rectangle.right();
//
//}
//
//
//template < primitive_rectangle RECTANGLE, typename Y >
//inline bool contains_y(const RECTANGLE & rectangle, Y y)
//{
//
//   return y >= rectangle.top() && y <= rectangle.bottom();
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
//   rectangle.left() = (decltype(RECTANGLE_TYPE::left))(rectangle.left() - l);
//   rectangle.top() = (decltype(RECTANGLE_TYPE::top))(rectangle.top() - t);
//   rectangle.right() = (decltype(RECTANGLE_TYPE::right))(rectangle.right() + r);
//   rectangle.bottom() = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom() + b);
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
//   return rect_inflate(rectangle, rect2.left(), rect2.top(), rect2.right(), rect2.bottom());
//
//}
//
//
//template < primitive_rectangle RECTANGLE_TYPE, typename RECT_TYPE2 >
//inline RECTANGLE_TYPE & multiply_inline(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
//{
//
//   rectangle.left() *= rect2.left();
//   rectangle.top() *= rect2.top();
//   rectangle.right() *= rect2.right();
//   rectangle.bottom() *= rect2.bottom();
//
//   return rectangle;
//
//}
//
//template < primitive_rectangle RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
//{
//
//   rectangle.left() = (decltype(RECTANGLE_TYPE::left))(rectangle.left() + l);
//   rectangle.top() = (decltype(RECTANGLE_TYPE::top))(rectangle.top() + t);
//   rectangle.right() = (decltype(RECTANGLE_TYPE::right))(rectangle.right() - r);
//   rectangle.bottom() = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom() - b);
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
//   return deflate(rectangle, rect2.left(), rect2.top(), rect2.right(), rect2.bottom());
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
//inline RECTANGLE_TYPE & swap_left_right(RECTANGLE_TYPE & rectangle) { __swap(rectangle.left(), rectangle.right()); return rectangle; }
//
//
//
//template < primitive_point POINT1, primitive_point POINT2 >
//inline bool polygon_contains(const POINT1 * ppPolygon, int iCount, const POINT2 & point)
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
//inline int area(int cx, int cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
//inline huge_integer area(huge_integer cx, huge_integer cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
//inline double area(double cx, double cy) { return (cx < 0. && cy < 0. ? -1. : 1.) * cx * cy; }
//
//
//
//struct ::huge_integer_size;
//struct ::huge_integer_point;
//struct ::huge_integer_rectangle;
////::int_size;
////class huge_integer_size;
////class double_size;
////::int_point;
////class huge_integer_point;
////class double_point;
////::double_rectangle;
////::huge_integer_rectangle;
////::double_rectangle;
//
//typedef uchar      uch;
//
//struct ::huge_integer_point;
//struct ::huge_integer_size;
//struct ::huge_integer_rectangle;
//struct ::double_point;
//struct ::double_size;
//struct ::double_rectangle;
//
//
//
//using int_point = point_type < ::int_point, ::int_size, ::int_rectangle >;
//using huge_integer_point = point_type < ::huge_integer_point, ::huge_integer_size, ::huge_integer_rectangle >;
//using float_point = point_type < ::float_point, ::float_size, ::float_rectangle >;
//using double_point = point_type < ::double_point, ::double_size, ::double_rectangle >;
//
//
//using int_size = size_type < ::int_size, ::int_point, ::int_rectangle >;
//using huge_integer_size = size_type < ::huge_integer_size, ::huge_integer_point, ::huge_integer_rectangle >;
//using float_size = size_type < ::float_size, ::float_point, ::float_rectangle >;
//using double_size = size_type < ::double_size, ::double_point, ::double_rectangle >;
//
//
//using int_rectangle = rectangle_type < ::int_rectangle, ::int_point, ::int_size >;
//using huge_integer_rectangle = rectangle_type < ::huge_integer_rectangle, ::huge_integer_point, ::huge_integer_size >;
//using float_rectangle = rectangle_type < ::float_rectangle, ::float_point, ::float_size >;
//using double_rectangle = rectangle_type < ::double_rectangle, ::double_point, ::double_size >;
//
//
//using int_point_array = point_array_base < int_point >;
//using huge_integer_point_array = point_array_base < huge_integer_point >;
//using float_point_array = point_array_base < float_point >;
//using double_point_array = point_array_base < double_point >;
//
//
//using rectangle = ::double_rectangle;
//
//
////inline float i32muldiv(float f, int iNum, int iDen);
////inline double i32muldiv(double d, int iNum, int iDen);
////inline int i32muldiv(int i, int iNum, int iDen);
////#ifndef WINDOWS
////inline huge_integer MulDiv(huge_integer nNumber, int iNum, int iDen);
////#endif
////inline huge_integer i32muldiv(huge_integer i, huge_integer iNum, huge_integer iDen);
//
//
//template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3, primitive_integral INTEGRAL_RESULT = typename ::largest_type_of_3 < INTEGRAL1, INTEGRAL2, INTEGRAL3 >::type >
//inline INTEGRAL_RESULT muldiv(INTEGRAL1 i, INTEGRAL2 iNumerator, INTEGRAL3 iDenominator);
//
//
//template < primitive_rectangle RECTANGLE >
//inline auto width(const RECTANGLE & rectangle) { return rectangle.right() - rectangle.left(); }
//
//template < primitive_rectangle RECTANGLE >
//inline auto height(const RECTANGLE & rectangle) { return rectangle.bottom() - rectangle.top(); }
//
//template < primitive_rectangle RECTANGLE >
//inline auto area(const RECTANGLE & rectangle) { return maximum(width(rectangle), 0) * maximum(height(rectangle), 0); }
//
//
//template < primitive_rectangle RECTANGLE >
//inline auto left(const RECTANGLE & rectangle) { return rectangle.left(); }
//
//template < primitive_rectangle RECTANGLE >
//inline auto top(const RECTANGLE & rectangle) { return rectangle.top(); }
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
////   rectangle.left() = (decltype(rectangle.left())) xydim.X;
////   rectangle.top() = (decltype(rectangle.top())) xydim.Y;
////   rectangle.right() = (decltype(rectangle.right()))(xydim.X + xydim.Width);
////   rectangle.bottom() = (decltype(rectangle.bottom()))(xydim.Y + xydim.Height);
////
////}
////
////
////template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
////inline void copy(XYDim & xydim, const RECTANGLE & rectangle)
////{
////
////   xydim.X = (decltype(xydim.X)) rectangle.left();
////   xydim.Y = (decltype(xydim.Y)) rectangle.top();
////   xydim.Width = (decltype(xydim.Width))(rectangle.right() + rectangle.left());
////   xydim.Height = (decltype(xydim.Height))(rectangle.bottom() + rectangle.top());
////
////}
//
//
//
////inline bool contains(const ::int_rectangle &rectangle, const ::int_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::int_rectangle & null(::int_rectangle & rectDst) { return ::null_rect(rectDst); }
////inline bool is_equal(const ::int_rectangle &rect1, const ::int_rectangle &rect2) { return ::rect_equals(rect1, rect2); }
////inline ::int_rectangle & inflate(::int_rectangle & rectangle, int x, int y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::int_rectangle & deflate(::int_rectangle & rectangle, int x, int y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::int_rectangle & offset(::int_rectangle & rectangle, int x, int y) { return ::offset_rect(rectangle, x, y); }
////inline bool intersect(::int_rectangle & rectangle, const ::int_rectangle &rect1, const ::int_rectangle &rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::int_rectangle & unite(::int_rectangle & rectangle, const ::int_rectangle &rect1, const ::int_rectangle &rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline int width(const ::int_rectangle &rectangle) { return ::rect_width(rectangle); }
////inline int height(const ::int_rectangle &rectangle) { return ::rect_height(rectangle); }
////inline int area(const ::int_rectangle &rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::int_rectangle &rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::int_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }
//
////inline int width(const ::int_rectangle &rectangle) { return ::width(&rectangle); }
////inline int height(const ::int_rectangle &rectangle) { return ::height(&rectangle); }
////inline int area(const ::int_rectangle &rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::int_rectangle &rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::int_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//
//
////inline bool is_empty(::int_size & size) { return size.cx() <= 0 || size.cy() <= 0; }
////inline bool is_empty(::huge_integer_size & size) { return size.cx() <= 0 || size.cy() <= 0; }
////inline bool is_empty(::float_size & size) { return size.cx() <= 0.f || size.cy() <= 0.f; }
////inline bool is_empty(::double_size & size) { return size.cx() <= 0. || size.cy() <= 0.; }
//
//
//
//
//
//
//
//
////inline bool contains(const ::huge_integer_rectangle & rectangle, const ::int_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::huge_integer_rectangle & null(::huge_integer_rectangle & rectDst) { return ::null_rect(rectDst); }
////inline bool is_equal(const ::huge_integer_rectangle & rect1, const ::huge_integer_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
////inline ::huge_integer_rectangle & inflate(::huge_integer_rectangle & rectangle, huge_integer x, huge_integer y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::huge_integer_rectangle & deflate(::huge_integer_rectangle & rectangle, huge_integer x, huge_integer y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::huge_integer_rectangle & offset(::huge_integer_rectangle & rectangle, huge_integer x, huge_integer y) { return ::offset_rect(rectangle, x, y); }
////inline bool intersect(::huge_integer_rectangle & rectangle, const ::huge_integer_rectangle & rect1, const ::huge_integer_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::huge_integer_rectangle & unite(::huge_integer_rectangle & rectangle, const ::huge_integer_rectangle & rect1, const ::huge_integer_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline huge_integer width(const ::huge_integer_rectangle & rectangle) { return ::rect_width(rectangle); }
////inline huge_integer height(const ::huge_integer_rectangle & rectangle) { return ::rect_height(rectangle); }
////inline huge_integer area(const ::huge_integer_rectangle & rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::huge_integer_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::huge_integer_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }
//
////inline huge_integer width(const ::huge_integer_rectangle & rectangle) { return ::width(&rectangle); }
////inline huge_integer height(const ::huge_integer_rectangle & rectangle) { return ::height(&rectangle); }
////inline huge_integer area(const ::huge_integer_rectangle & rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::huge_integer_rectangle & rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::huge_integer_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//
//
//
//
////inline bool contains(const ::float_rectangle & rectangle, const ::float_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::float_rectangle & null(::float_rectangle & rect) { return ::null_rect(rect); }
////inline bool is_equal(const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
////inline ::float_rectangle & inflate(::float_rectangle & rectangle, float x, float y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::float_rectangle & deflate(::float_rectangle & rectangle, float x, float y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::float_rectangle & offset(::float_rectangle & rectangle, float x, float y) { return ::offset_rect(rectangle, x, y); }
////inline bool intersect(::float_rectangle & rectangle, const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::float_rectangle & unite(::float_rectangle & rectangle, const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline float width(const ::float_rectangle & rectangle) { return ::rect_width(rectangle); }
//////template < primitive_rectangle RECTANGLE > 
//////inline auto height(const RECTANGLE  & rectangle) { return ::rect_height(rectangle); }
//////template < primitive_rectangle RECTANGLE >
//////inline auto height(const RECTANGLE & rectangle) { return ::height(&rectangle); }
////inline float area(const ::float_rectangle & rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::float_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::float_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }
//
////inline float width(const ::float_rectangle& rectangle) { return ::width(&rectangle); }
//////inline float height(const ::float_rectangle& rectangle) { return ::height(&rectangle); }
////inline float area(const ::float_rectangle& rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::float_rectangle& rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::float_rectangle& rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//
//
//
////inline bool contains(const ::double_rectangle & rectangle, const ::double_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
////inline ::double_rectangle & null(::double_rectangle & rect) { return ::null_rect(rect); }
////inline bool is_equal(const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
////inline ::double_rectangle & inflate(::double_rectangle & rectangle, double x, double y) { return ::rect_inflate_point(rectangle, x, y); }
////inline ::double_rectangle & deflate(::double_rectangle & rectangle, double x, double y) { return ::rect_deflate_point(rectangle, x, y); }
////inline ::double_rectangle & offset(::double_rectangle & rectangle, double x, double y) { return ::offset_rect(rectangle, x, y); }
//
//template < primitive_rectangle RECTANGLE >
//inline RECTANGLE & rate_deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);
//
//
////inline bool intersect(::double_rectangle & rectangle, const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
////inline ::double_rectangle & unite(::double_rectangle & rectangle, const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
////inline double width(const ::double_rectangle & rectangle) { return ::rect_width(rectangle); }
//////inline double height(const ::double_rectangle  & rectangle) { return ::rect_height(rectangle); }
////inline double area(const ::double_rectangle & rectangle) { return ::rect_area(rectangle); }
////inline bool is_empty(const ::double_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
////inline void swap_left_right(::double_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }
//
////inline double width(const ::double_rectangle & rectangle) { return ::width(&rectangle); }
////inline double height(const ::double_rectangle& rectangle) { return ::height(&rectangle); }
////inline double area(const ::double_rectangle & rectangle) { return ::area(&rectangle); }
////inline bool is_empty(const ::double_rectangle & rectangle) { return ::is_empty(&rectangle); }
////inline void swap_left_right(::double_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator -= (POINT & point, const POINT2 & pointOffset) { ::subtract(point, pointOffset); return point; }
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator += (POINT & point, const POINT2 & pointOffset) { ::subtract(point, pointOffset); return point; }
//
////inline ::huge_integer_point & operator -= (::huge_integer_point & point, const ::huge_integer_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
////inline ::huge_integer_point & operator += (::huge_integer_point & point, const ::huge_integer_point & pointOffset) { ::point_add(point, pointOffset); return point; }
////inline ::float_point & operator -= (::float_point & point, const ::float_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
////inline ::float_point & operator += (::float_point & point, const ::float_point & pointOffset) { ::point_add(point, pointOffset); return point; }
////inline ::double_point & operator -= (::double_point & point, const ::double_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
////inline ::double_point & operator += (::double_point & point, const ::double_point & pointOffset) { ::point_add(point, pointOffset); return point; }
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator -= (RECTANGLE & rectangle, const POINT & point) { ::subtract(rectangle, point); return rectangle; }
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator += (RECTANGLE & rectangle, const POINT & point) { ::subtract(rectangle, point); return rectangle; }
//
////inline ::huge_integer_rectangle& operator -= (::huge_integer_rectangle& rectangle, const ::huge_integer_point& point) { ::rect_sub(rectangle, point); return rectangle; }
////inline ::huge_integer_rectangle& operator += (::huge_integer_rectangle& rectangle, const ::huge_integer_point& point) { ::rect_add(rectangle, point); return rectangle; }
////inline ::float_rectangle& operator -= (::float_rectangle& rectangle, const ::float_point& point) { ::rect_sub(rectangle, point); return rectangle; }
////inline ::float_rectangle& operator += (::float_rectangle& rectangle, const ::float_point& point) { ::rect_add(rectangle, point); return rectangle; }
////inline ::double_rectangle& operator -= (::double_rectangle& rectangle, const ::double_point& point) { ::rect_sub(rectangle, point); return rectangle; }
////inline ::double_rectangle& operator += (::double_rectangle& rectangle, const ::double_point& point) { ::rect_add(rectangle, point); return rectangle; }
//
////inline bool deflate(::int_rectangle  & rectangle, const ::int_rectangle & prectParam);
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
////void get_bounding_box(RECTANGLE_BASE_TYPE & rect, const POINT_BASE_TYPE * lppoint, ::collection::count count)
////{
////
////   if (count <= 0)
////   {
////
////      rect.left() = 0;
////      rect.top() = 0;
////      rect.right() = 0;
////      rect.bottom() = 0;
////
////   }
////   else
////   {
////      rect.left() = lppoint[0].x();
////      rect.top() = lppoint[0].y();
////      rect.right() = lppoint[0].x();
////      rect.bottom() = lppoint[0].y();
////
////      for (int i = 1; i < count; i++)
////      {
////         if (lppoint[i].x() < rect.left())
////            rect.left() = lppoint[i].x();
////         else if (lppoint[i].x() > rect.right())
////            rect.right() = lppoint[i].x();
////         if (lppoint[i].y() < rect.top())
////            rect.top() = lppoint[i].y();
////         else if (lppoint[i].y() > rect.bottom())
////            rect.bottom() = lppoint[i].y();
////      }
////
////   }
////
////}
//
//
////inline bool get_bounding_box(::int_rectangle & rectangleBounding, const ::int_rectangle &rectangle)
////{
////
////   copy(rectangleBounding, rectangle);
////
////   return true;
////
////}
//
//
////inline bool get_bounding_box(::double_rectangle & rectangleBounding, const ::int_rectangle &rectangle)
////{
////
////   copy(rectangleBounding, rectangle);
////
////   return true;
////
////}
////
////
////inline bool get_bounding_box(::int_rectangle & rectangleBounding, const ::double_rectangle & rectangle)
////{
////
////   copy(rectangleBounding, rectangle);
////
////   return true;
////
////}
////
////
////inline bool get_bounding_box(::double_rectangle & rectangleBounding, const ::double_rectangle & rectangle)
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
////void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > ::get_bounding_box(const POINT_BASE_TYPE * ppoint, ::collection::count count)
////{
////
////   ::get_bounding_box(*this, ppoint, count);
////
////}
////
////
////
////
////CLASS_DECL_ACME double d_distance(const int_point & point1, const int_point & point2);
////
////
////template < typename X, typename Y, typename W, typename H >
////inline int_rectangle int_rectangle_dimension(X x, Y y, W w, H h)
////{
////
////   return int_rectangle((int)(x), (int)(y), (int)(x + w), (int)(y + h));
////
////}
////
////
////template < typename X, typename Y, typename W, typename H >
////inline huge_integer_rectangle huge_integer_rectangle_dimension(X x, Y y, W w, H h)
////{
////
////   return huge_integer_rectangle((huge_integer)x, (huge_integer)y, (huge_integer)(x + w), (huge_integer)(y + h));
////
////}
////
////
////template < typename X, typename Y, typename W, typename H >
////inline float_rectangle float_rectangle_dimension(X x, Y y, W w, H h)
////{
////
////   return float_rectangle((float)x, (float)y, (float)(x + w), (float)(y + h));
////
////}
////
////
////template < typename X, typename Y, typename W, typename H >
////inline double_rectangle double_rectangle_dimension(X x, Y y, W w, H h)
////{
////
////   return double_rectangle((double)x, (double)y, (double)(x + w), (double)(y + h));
////
////}
//
//
//
////#ifdef UNIVERSAL_WINDOWS
////
////inline void copy(int_rectangle & rectDst, const ::winrt::Windows::Foundation::Rect * prectSrc)
////{
////   rectDst->left() = (int) prectSrc->X;
////   rectDst->top() = (int)prectSrc->Y;
////   rectDst->right() = (int) (prectSrc->X + prectSrc->Width);
////   rectDst->bottom() = (int) (prectSrc->Y + prectSrc->Height);
////}
////
////inline void copy(::winrt::Windows::Foundation::Rect& rectDst, int_rectangle* prectSrc)
////{
////   rectDst->X = (float) prectSrc->left();
////   rectDst->Y = (float) prectSrc->top();
////   rectDst->Width = (float) prectSrc->width();
////   rectDst->Height = (float) prectSrc->height();
////}
////
////#endif
//
//
////inline auto ::int_point(const ::lparam & lparam) noexcept { return ::int_point(lparam.x(), lparam.y()); }
////inline auto ::int_point(const unsigned int u) noexcept { return ::int_point((int)u32_x(u), (int)u32_y(u)); }
////inline auto ::int_point(const huge_natural u) noexcept { return ::int_point((int)u64_x(u), (int)u64_y(u)); }
////inline auto ::int_point(const ::int_size & size) noexcept { return ::int_point(size.cx(), size.cy()); }
////
////inline auto __point64(const ::lparam & lparam) noexcept { return ::huge_integer_point(lparam.x(), lparam.y()); }
////inline auto __point64(const unsigned int u) noexcept { return ::huge_integer_point((huge_integer)u32_x(u), (huge_integer)u32_y(u)); }
////inline auto __point64(const huge_natural u) noexcept { return ::huge_integer_point((huge_integer)u64_x(u), (huge_integer)u64_y(u)); }
////inline auto __point64(const ::huge_integer_size & size) noexcept { return ::huge_integer_point(size.cx(), size.cy()); }
////
////
////inline auto __pointf(const ::lparam & lparam) noexcept { return ::float_point((float)lparam.x(), (float)lparam.y()); }
////inline auto __pointf(const unsigned int u) noexcept { return ::float_point((float)u32_x(u), (float)u32_y(u)); }
////inline auto __pointf(const huge_natural u) noexcept { return ::float_point((float)u64_x(u), (float)u64_y(u)); }
////inline auto __pointf(const ::float_size & size) noexcept { return ::float_point(size.cx(), size.cy()); }
////
////
////inline auto __pointd(const ::lparam & lparam) noexcept { return ::double_point(lparam.x(), lparam.y()); }
////inline auto __pointd(const unsigned int u) noexcept { return ::double_point((double)u32_x(u), (double)u32_y(u)); }
////inline auto __pointd(const huge_natural u) noexcept { return ::double_point((double)u64_x(u), (double)u64_y(u)); }
////inline auto __pointd(const ::double_size & size) noexcept { return ::double_point(size.cx(), size.cy()); }
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
////      rectangle.left() = minimum((decltype(rectangle.left()))rectangle.left(), (decltype(rectangle.left()))r.left());
////      rectangle.right() = maximum((decltype(rectangle.right()))rectangle.right(), (decltype(rectangle.right()))r.right());
////      rectangle.top() = minimum((decltype(rectangle.top()))rectangle.top(), (decltype(rectangle.top()))r.top());
////      rectangle.bottom() = maximum((decltype(rectangle.bottom()))rectangle.bottom(), (decltype(rectangle.bottom()))r.bottom());
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
////      rectangle.left() = maximum((decltype(rectangle.left()))rectangle.left(), (decltype(rectangle.left()))r.left());
////      rectangle.right() = minimum((decltype(rectangle.right()))rectangle.right(), (decltype(rectangle.right()))r.right());
////      rectangle.top() = maximum((decltype(rectangle.top()))rectangle.top(), (decltype(rectangle.top()))r.top());
////      rectangle.bottom() = minimum((decltype(rectangle.bottom()))rectangle.bottom(), (decltype(rectangle.bottom()))r.bottom());
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
////inline int_point & top_left(const ::int_rectangle &rectangle) { return *(int_point *)&rectangle; }
////inline int_point & bottom_right(const ::int_rectangle &rectangle) { return *(int_point *)&rectangle.right(); }
//////inline int_point & top_left(const ::int_rectangle &rectangle) { return top_left(&rectangle); }
//////inline int_point & bottom_right(const ::int_rectangle &rectangle) { return bottom_right(&rectangle); }
////
////
////inline huge_integer_point & top_left(const ::huge_integer_rectangle & rectangle) { return *(huge_integer_point *)&rectangle; }
////inline huge_integer_point & bottom_right(const ::huge_integer_rectangle & rectangle) { return *(huge_integer_point *)&rectangle.right(); }
//////inline huge_integer_point & top_left(const ::huge_integer_rectangle & rectangle) { return top_left(&rectangle); }
//////inline huge_integer_point & bottom_right(const ::huge_integer_rectangle & rectangle) { return bottom_right(&rectangle); }
////
////
////inline double_point & top_left(const ::double_rectangle & rectangle) { return *(double_point *)&rectangle; }
////inline double_point & bottom_right(const ::double_rectangle & rectangle) { return *(double_point *)&rectangle.right(); }
//////inline double_point & top_left(const ::double_rectangle & rectangle) { return top_left(&rectangle); }
//////inline double_point & bottom_right(const ::double_rectangle & rectangle) { return bottom_right(&rectangle); }
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
////inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const POINT_TYPE & point) noexcept : size_type((size_type&)int_point) {}
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
////inline int __conv<int>(const ::string & str)
////{
////
////   return (int) ::atoi(str);
////
////}
////
////
////template <  >
////inline huge_integer __conv<huge_integer>(const ::string & str)
////{
////
////   return (int) ::atoi(str);
////
////}
////
////
////template <  >
////inline double __conv<double>(const ::string & str)
////{
////
////   return (int) ::atoi(str);
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
////inline string __xmlpri<int>()
////{
////
////   return "%" PRId32;
////
////}
////
////
////template < >
////inline string __xmlpri<huge_integer>()
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
////      rectangle.left() = range_rate(rectangle.left(), rectangle.right(), dLeftRate);
////
////      rectangle.right() = range_rate(rectangle.right(), rectangle.left(), dRightRate);
////
////      rectangle.top() = range_rate(rectangle.top(), rectangle.bottom(), dTopRate);
////
////      rectangle.bottom() = range_rate(rectangle.bottom(), rectangle.top(), dBottomRate);
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


using int_point = point_type < int >;
using huge_integer_point = point_type < huge_integer >;
using float_point = point_type < float >;
using double_point = point_type < double >;


using int_size = size_type < int >;
using huge_integer_size = size_type < huge_integer >;
using float_size = size_type < float >;
using double_size = size_type < double >;


using int_rectangle = rectangle_type < int >;
using huge_integer_rectangle = rectangle_type < huge_integer >;
using float_rectangle = rectangle_type < float >;
using double_rectangle = rectangle_type < double >;


using int_ellipse = ellipse_type < int >;
using huge_integer_ellipse = ellipse_type < huge_integer >;
using float_ellipse = ellipse_type < float >;
using double_ellipse = ellipse_type < double >;


using int_line = line_type < int >;
using huge_integer_line = line_type < huge_integer >;
using float_line = line_type < float >;
using double_line = line_type < double >;


using int_arc = arc_type < int >;
using huge_integer_arc = arc_type < huge_integer >;
using float_arc = arc_type < float >;
using double_arc = arc_type < double >;


using int_point_array = point_array_base < int >;
using huge_integer_point_array = point_array_base < huge_integer >;
using float_point_array = point_array_base < float >;
using double_point_array = point_array_base < double >;


using int_polygon = polygon_type < int >;
using huge_integer_polygon = polygon_type < huge_integer >;
using float_polygon = polygon_type < float >;
using double_polygon = polygon_type < double >;


using int_poly_polygon = poly_polygon_type < int >;
using huge_integer_poly_polygon = poly_polygon_type < huge_integer >;
using float_poly_polygon = poly_polygon_type < float >;
using double_poly_polygon = poly_polygon_type < double >;


using int_point_array = point_array_base < int >;
using huge_integer_point_array = point_array_base < huge_integer >;
using float_point_array = point_array_base < float >;
using double_point_array = point_array_base < double >;


using int_size_array = size_array_base < int >;
using huge_integer_size_array = size_array_base < huge_integer >;
using float_size_array = size_array_base < float >;
using double_size_array = size_array_base < double >;


using int_rectangle_array = rectangle_array_base < int >;
using huge_integer_rectangle_array = rectangle_array_base < huge_integer >;
using float_rectangle_array = rectangle_array_base < float >;
using double_rectangle_array = rectangle_array_base < double >;


using int_lines = lines_base < int >;
using huge_integer_lines = lines_base < huge_integer >;
using float_lines = lines_base < float >;
using double_lines = lines_base < double >;


template < struct_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
inline void copy(RECTANGLE1 * prectangle1, const RECTANGLE2 * prectangle2)
{

   prectangle1->left = (decltype(prectangle1->left))prectangle2->left();
   prectangle1->top = (decltype(prectangle1->top))prectangle2->top();
   prectangle1->right = (decltype(prectangle1->right))prectangle2->right();
   prectangle1->bottom = (decltype(prectangle1->bottom))prectangle2->bottom();

}



