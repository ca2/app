#pragma once


#include "angle.h"


//#include "_geometry2d.h"


#include "_concept.h"


// inline auto left(const ::int_rectangle &rectangle) { return rectangle.left(); }
// inline auto top(const ::int_rectangle &rectangle) { return rectangle.top(); }
// inline auto left(const ::huge_integer_rectangle & rectangle) { return rectangle.left(); }
// inline auto top(const ::huge_integer_rectangle & rectangle) { return rectangle.top(); }
// inline auto left(const ::float_rectangle & rectangle) { return rectangle.left(); }
// inline auto top(const ::float_rectangle & rectangle) { return rectangle.top(); }
// inline auto left(const ::double_rectangle & rectangle) { return rectangle.left(); }
// inline auto top(const ::double_rectangle & rectangle) { return rectangle.top(); }


//template < typename TARGET, typename SOURCE >
//inline TARGET & _001CopyRect(TARGET & prectTarget, const SOURCE & prectSource);




template < typename SIZE_BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class size_type;

template < typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class point_type;

template < typename RECTANGLE_BASE_TYPE, typename POINT_TYPE, typename SIZE_TYPE >
class rectangle_type;

template < typename POINT_TYPE >
class point_array_base;






inline int area(int cx, int cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline huge_integer area(huge_integer cx, huge_integer cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline double area(double cx, double cy) { return (cx < 0. && cy < 0. ? -1. : 1.) * cx * cy; }



struct ::huge_integer_size;
struct ::huge_integer_point;
struct ::huge_integer_rectangle;
//::int_size;
//class huge_integer_size;
//class double_size;
//::int_point;
//class huge_integer_point;
//class double_point;
//::double_rectangle;
//::huge_integer_rectangle;
//::double_rectangle;

typedef uchar      uch;

struct ::huge_integer_point;
struct ::huge_integer_size;
struct ::huge_integer_rectangle;
struct ::double_point;
struct ::double_size;
struct ::double_rectangle;




//inline float i32muldiv(float f, int iNum, int iDen);
//inline double i32muldiv(double d, int iNum, int iDen);
//inline int i32muldiv(int i, int iNum, int iDen);
//#ifndef WINDOWS
//inline huge_integer MulDiv(huge_integer nNumber, int iNum, int iDen);
//#endif
//inline huge_integer i32muldiv(huge_integer i, huge_integer iNum, huge_integer iDen);


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3, primitive_integral INTEGRAL_RESULT = typename ::largest_type_of_3 < INTEGRAL1, INTEGRAL2, INTEGRAL3 >::type >
inline INTEGRAL_RESULT muldiv(INTEGRAL1 i, INTEGRAL2 iNumerator, INTEGRAL3 iDenominator);


template < primitive_rectangle RECTANGLE >
inline auto width(const RECTANGLE & rectangle) { return rectangle.right() - rectangle.left(); }

template < primitive_rectangle RECTANGLE >
inline auto height(const RECTANGLE & rectangle) { return rectangle.bottom() - rectangle.top(); }

template < primitive_rectangle RECTANGLE >
inline auto area(const RECTANGLE & rectangle) { return maximum(width(rectangle), 0) * maximum(height(rectangle), 0); }


template < primitive_rectangle RECTANGLE >
inline auto left(const RECTANGLE & rectangle) { return rectangle.left(); }

template < primitive_rectangle RECTANGLE >
inline auto top(const RECTANGLE & rectangle) { return rectangle.top(); }



template < primitive_XYDim XYDim >
inline auto width(const XYDim & rectangle) { return rectangle.Width; }

template < primitive_XYDim XYDim >
inline auto height(const XYDim & rectangle) { return rectangle.Height; }

template < primitive_XYDim XYDim >
inline auto area(const XYDim & rectangle) { return maximum(rectangle.Width, 0) * maximum(rectangle.Height, 0); }


template < primitive_XYDim XYDim >
inline auto left(const XYDim & rectangle) { return rectangle.X; }

template < primitive_XYDim XYDim >
inline auto top(const XYDim & rectangle) { return rectangle.Y; }


//template < primitive_rectangle RECTANGLE, primitive_XYDim XYDim >
//inline void copy(RECTANGLE & rectangle, const XYDim & xydim)
//{
//
//   rectangle.left() = (decltype(rectangle.left())) xydim.X;
//   rectangle.top() = (decltype(rectangle.top())) xydim.Y;
//   rectangle.right() = (decltype(rectangle.right()))(xydim.X + xydim.Width);
//   rectangle.bottom() = (decltype(rectangle.bottom()))(xydim.Y + xydim.Height);
//
//}
//
//
//template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
//inline void copy(XYDim & xydim, const RECTANGLE & rectangle)
//{
//
//   xydim.X = (decltype(xydim.X)) rectangle.left();
//   xydim.Y = (decltype(xydim.Y)) rectangle.top();
//   xydim.Width = (decltype(xydim.Width))(rectangle.right() + rectangle.left());
//   xydim.Height = (decltype(xydim.Height))(rectangle.bottom() + rectangle.top());
//
//}



//inline bool contains(const ::int_rectangle &rectangle, const ::int_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::int_rectangle & null(::int_rectangle & rectDst) { return ::null_rect(rectDst); }
//inline bool is_equal(const ::int_rectangle &rect1, const ::int_rectangle &rect2) { return ::rect_equals(rect1, rect2); }
//inline ::int_rectangle & inflate(::int_rectangle & rectangle, int x, int y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::int_rectangle & deflate(::int_rectangle & rectangle, int x, int y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::int_rectangle & offset(::int_rectangle & rectangle, int x, int y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::int_rectangle & rectangle, const ::int_rectangle &rect1, const ::int_rectangle &rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::int_rectangle & unite(::int_rectangle & rectangle, const ::int_rectangle &rect1, const ::int_rectangle &rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline int width(const ::int_rectangle &rectangle) { return ::rect_width(rectangle); }
//inline int height(const ::int_rectangle &rectangle) { return ::rect_height(rectangle); }
//inline int area(const ::int_rectangle &rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::int_rectangle &rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::int_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }

//inline int width(const ::int_rectangle &rectangle) { return ::width(&rectangle); }
//inline int height(const ::int_rectangle &rectangle) { return ::height(&rectangle); }
//inline int area(const ::int_rectangle &rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::int_rectangle &rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::int_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }



//inline bool is_empty(::int_size & size) { return size.cx() <= 0 || size.cy() <= 0; }
//inline bool is_empty(::huge_integer_size & size) { return size.cx() <= 0 || size.cy() <= 0; }
//inline bool is_empty(::float_size & size) { return size.cx() <= 0.f || size.cy() <= 0.f; }
//inline bool is_empty(::double_size & size) { return size.cx() <= 0. || size.cy() <= 0.; }








//inline bool contains(const ::huge_integer_rectangle & rectangle, const ::int_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::huge_integer_rectangle & null(::huge_integer_rectangle & rectDst) { return ::null_rect(rectDst); }
//inline bool is_equal(const ::huge_integer_rectangle & rect1, const ::huge_integer_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::huge_integer_rectangle & inflate(::huge_integer_rectangle & rectangle, huge_integer x, huge_integer y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::huge_integer_rectangle & deflate(::huge_integer_rectangle & rectangle, huge_integer x, huge_integer y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::huge_integer_rectangle & offset(::huge_integer_rectangle & rectangle, huge_integer x, huge_integer y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::huge_integer_rectangle & rectangle, const ::huge_integer_rectangle & rect1, const ::huge_integer_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::huge_integer_rectangle & unite(::huge_integer_rectangle & rectangle, const ::huge_integer_rectangle & rect1, const ::huge_integer_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline huge_integer width(const ::huge_integer_rectangle & rectangle) { return ::rect_width(rectangle); }
//inline huge_integer height(const ::huge_integer_rectangle & rectangle) { return ::rect_height(rectangle); }
//inline huge_integer area(const ::huge_integer_rectangle & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::huge_integer_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::huge_integer_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }

//inline huge_integer width(const ::huge_integer_rectangle & rectangle) { return ::width(&rectangle); }
//inline huge_integer height(const ::huge_integer_rectangle & rectangle) { return ::height(&rectangle); }
//inline huge_integer area(const ::huge_integer_rectangle & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::huge_integer_rectangle & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::huge_integer_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }





//inline bool contains(const ::float_rectangle & rectangle, const ::float_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::float_rectangle & null(::float_rectangle & rect) { return ::null_rect(rect); }
//inline bool is_equal(const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::float_rectangle & inflate(::float_rectangle & rectangle, float x, float y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::float_rectangle & deflate(::float_rectangle & rectangle, float x, float y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::float_rectangle & offset(::float_rectangle & rectangle, float x, float y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::float_rectangle & rectangle, const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::float_rectangle & unite(::float_rectangle & rectangle, const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline float width(const ::float_rectangle & rectangle) { return ::rect_width(rectangle); }
////template < primitive_rectangle RECTANGLE > 
////inline auto height(const RECTANGLE  & rectangle) { return ::rect_height(rectangle); }
////template < primitive_rectangle RECTANGLE >
////inline auto height(const RECTANGLE & rectangle) { return ::height(&rectangle); }
//inline float area(const ::float_rectangle & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::float_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::float_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }

//inline float width(const ::float_rectangle& rectangle) { return ::width(&rectangle); }
////inline float height(const ::float_rectangle& rectangle) { return ::height(&rectangle); }
//inline float area(const ::float_rectangle& rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::float_rectangle& rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::float_rectangle& rectangle) noexcept { ::swap_left_right(&rectangle); }




//inline bool contains(const ::double_rectangle & rectangle, const ::double_point & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::double_rectangle & null(::double_rectangle & rect) { return ::null_rect(rect); }
//inline bool is_equal(const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::double_rectangle & inflate(::double_rectangle & rectangle, double x, double y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::double_rectangle & deflate(::double_rectangle & rectangle, double x, double y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::double_rectangle & offset(::double_rectangle & rectangle, double x, double y) { return ::offset_rect(rectangle, x, y); }

template < primitive_rectangle RECTANGLE >
inline RECTANGLE & rate_deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);


//inline bool intersect(::double_rectangle & rectangle, const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::double_rectangle & unite(::double_rectangle & rectangle, const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline double width(const ::double_rectangle & rectangle) { return ::rect_width(rectangle); }
////inline double height(const ::double_rectangle  & rectangle) { return ::rect_height(rectangle); }
//inline double area(const ::double_rectangle & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::double_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::double_rectangle & rectangle) noexcept { ::__swap(rectangle.left(), rectangle.right()); }

//inline double width(const ::double_rectangle & rectangle) { return ::width(&rectangle); }
//inline double height(const ::double_rectangle& rectangle) { return ::height(&rectangle); }
//inline double area(const ::double_rectangle & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::double_rectangle & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::double_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }

//inline ::huge_integer_point & operator -= (::huge_integer_point & point, const ::huge_integer_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::huge_integer_point & operator += (::huge_integer_point & point, const ::huge_integer_point & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline ::float_point & operator -= (::float_point & point, const ::float_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::float_point & operator += (::float_point & point, const ::float_point & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline ::double_point & operator -= (::double_point & point, const ::double_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::double_point & operator += (::double_point & point, const ::double_point & pointOffset) { ::point_add(point, pointOffset); return point; }



//inline ::huge_integer_rectangle& operator -= (::huge_integer_rectangle& rectangle, const ::huge_integer_point& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::huge_integer_rectangle& operator += (::huge_integer_rectangle& rectangle, const ::huge_integer_point& point) { ::rect_add(rectangle, point); return rectangle; }
//inline ::float_rectangle& operator -= (::float_rectangle& rectangle, const ::float_point& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::float_rectangle& operator += (::float_rectangle& rectangle, const ::float_point& point) { ::rect_add(rectangle, point); return rectangle; }
//inline ::double_rectangle& operator -= (::double_rectangle& rectangle, const ::double_point& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::double_rectangle& operator += (::double_rectangle& rectangle, const ::double_point& point) { ::rect_add(rectangle, point); return rectangle; }

//inline bool deflate(::int_rectangle  & rectangle, const ::int_rectangle & prectParam);


#include "_point.h"
#include "_size.h"
#include "_rectangle.h"



#include "types.h"





//inline bool get_bounding_box(::double_rectangle & rectangleBounding, const ::int_rectangle &rectangle)
//{
//
//   copy(rectangleBounding, rectangle);
//
//   return true;
//
//}


//inline bool get_bounding_box(::int_rectangle & rectangleBounding, const ::double_rectangle & rectangle)
//{
//
//   copy(rectangleBounding, rectangle);
//
//   return true;
//
//}


//inline bool get_bounding_box(::double_rectangle & rectangleBounding, const ::double_rectangle & rectangle)
//{
//
//   copy(rectangleBounding, rectangle);
//
//   return true;
//
//}








//#ifdef UNIVERSAL_WINDOWS
//
//inline void copy(int_rectangle & rectDst, const ::winrt::Windows::Foundation::Rect * prectSrc)
//{
//   rectDst->left() = (int) prectSrc->X;
//   rectDst->top() = (int)prectSrc->Y;
//   rectDst->right() = (int) (prectSrc->X + prectSrc->Width);
//   rectDst->bottom() = (int) (prectSrc->Y + prectSrc->Height);
//}
//
//inline void copy(::winrt::Windows::Foundation::Rect& rectDst, int_rectangle* prectSrc)
//{
//   rectDst->X = (float) prectSrc->left();
//   rectDst->Y = (float) prectSrc->top();
//   rectDst->Width = (float) prectSrc->width();
//   rectDst->Height = (float) prectSrc->height();
//}
//
//#endif



//#ifdef UNIVERSAL_WINDOWS
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






#include "arc.h"

#include "_line.h"

#include "lines.h"

#include "ellipse.h"


//template < primitive_point POINT >
//inline ::string as_string(const POINT & point);
//
//
//template < primitive_size SIZE >
//inline ::string as_string(const SIZE & size);
//
//
//
//
//



//
//inline auto ::int_point(const ::int_size & size) noexcept { return ::int_point(size.cx(), size.cy()); }
//inline auto __point64(const ::huge_integer_size & size) noexcept { return ::huge_integer_point(size.cx(), size.cy()); }
//inline auto __pointf(const ::float_size & size) noexcept { return ::float_point(size.cx(), size.cy()); }
//inline auto __pointd(const ::double_size & size) noexcept { return ::double_point(size.cx(), size.cy()); }
//





