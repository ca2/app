#pragma once


#include "angle.h"


//#include "_geometry2d.h"


#include "_concept.h"


// inline auto left(const ::rectangle_i32 &rectangle) { return rectangle.left; }
// inline auto top(const ::rectangle_i32 &rectangle) { return rectangle.top; }
// inline auto left(const ::rectangle_i64 & rectangle) { return rectangle.left; }
// inline auto top(const ::rectangle_i64 & rectangle) { return rectangle.top; }
// inline auto left(const ::rectangle_f32 & rectangle) { return rectangle.left; }
// inline auto top(const ::rectangle_f32 & rectangle) { return rectangle.top; }
// inline auto left(const ::rectangle_f64 & rectangle) { return rectangle.left; }
// inline auto top(const ::rectangle_f64 & rectangle) { return rectangle.top; }


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






inline ::i32 area(::i32 cx, ::i32 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline i64 area(i64 cx, i64 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline double area(double cx, double cy) { return (cx < 0. && cy < 0. ? -1. : 1.) * cx * cy; }



struct ::size_i64;
struct ::point_i64;
struct ::rectangle_i64;
//::size_i32;
//class size_i64;
//class size_f64;
//::point_i32;
//class point_i64;
//class point_f64;
//::rectangle_f64;
//::rectangle_i64;
//::rectangle_f64;

typedef uchar      byte;

struct ::point_i64;
struct ::size_i64;
struct ::rectangle_i64;
struct ::point_f64;
struct ::size_f64;
struct ::rectangle_f64;




//inline float i32muldiv(float f, i32 iNum, i32 iDen);
//inline double i32muldiv(double d, i32 iNum, i32 iDen);
//inline i32 i32muldiv(i32 i, i32 iNum, i32 iDen);
//#ifndef WINDOWS
//inline i64 MulDiv(i64 nNumber, i32 iNum, i32 iDen);
//#endif
//inline i64 i32muldiv(i64 i, i64 iNum, i64 iDen);


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3, primitive_integral INTEGRAL_RESULT = typename ::largest_type_of_3 < INTEGRAL1, INTEGRAL2, INTEGRAL3 >::type >
inline INTEGRAL_RESULT muldiv(INTEGRAL1 i, INTEGRAL2 iNumerator, INTEGRAL3 iDenominator);


template < primitive_rectangle RECTANGLE >
inline auto width(const RECTANGLE & rectangle) { return rectangle.right - rectangle.left; }

template < primitive_rectangle RECTANGLE >
inline auto height(const RECTANGLE & rectangle) { return rectangle.bottom - rectangle.top; }

template < primitive_rectangle RECTANGLE >
inline auto area(const RECTANGLE & rectangle) { return maximum(width(rectangle), 0) * maximum(height(rectangle), 0); }


template < primitive_rectangle RECTANGLE >
inline auto left(const RECTANGLE & rectangle) { return rectangle.left; }

template < primitive_rectangle RECTANGLE >
inline auto top(const RECTANGLE & rectangle) { return rectangle.top; }



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
//   rectangle.left = (decltype(rectangle.left)) xydim.X;
//   rectangle.top = (decltype(rectangle.top)) xydim.Y;
//   rectangle.right = (decltype(rectangle.right))(xydim.X + xydim.Width);
//   rectangle.bottom = (decltype(rectangle.bottom))(xydim.Y + xydim.Height);
//
//}
//
//
//template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
//inline void copy(XYDim & xydim, const RECTANGLE & rectangle)
//{
//
//   xydim.X = (decltype(xydim.X)) rectangle.left;
//   xydim.Y = (decltype(xydim.Y)) rectangle.top;
//   xydim.Width = (decltype(xydim.Width))(rectangle.right + rectangle.left);
//   xydim.Height = (decltype(xydim.Height))(rectangle.bottom + rectangle.top);
//
//}



//inline bool contains(const ::rectangle_i32 &rectangle, const ::point_i32 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::rectangle_i32 & null(::rectangle_i32 & rectDst) { return ::null_rect(rectDst); }
//inline bool is_equal(const ::rectangle_i32 &rect1, const ::rectangle_i32 &rect2) { return ::rect_equals(rect1, rect2); }
//inline ::rectangle_i32 & inflate(::rectangle_i32 & rectangle, ::i32 x, ::i32 y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::rectangle_i32 & deflate(::rectangle_i32 & rectangle, ::i32 x, ::i32 y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::rectangle_i32 & offset(::rectangle_i32 & rectangle, ::i32 x, ::i32 y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::rectangle_i32 & rectangle, const ::rectangle_i32 &rect1, const ::rectangle_i32 &rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::rectangle_i32 & unite(::rectangle_i32 & rectangle, const ::rectangle_i32 &rect1, const ::rectangle_i32 &rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline ::i32 width(const ::rectangle_i32 &rectangle) { return ::rect_width(rectangle); }
//inline ::i32 height(const ::rectangle_i32 &rectangle) { return ::rect_height(rectangle); }
//inline ::i32 area(const ::rectangle_i32 &rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::rectangle_i32 &rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::rectangle_i32 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline ::i32 width(const ::rectangle_i32 &rectangle) { return ::width(&rectangle); }
//inline ::i32 height(const ::rectangle_i32 &rectangle) { return ::height(&rectangle); }
//inline ::i32 area(const ::rectangle_i32 &rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::rectangle_i32 &rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::rectangle_i32 & rectangle) noexcept { ::swap_left_right(&rectangle); }



//inline bool is_empty(::size_i32 & size) { return size.cx() <= 0 || size.cy() <= 0; }
//inline bool is_empty(::size_i64 & size) { return size.cx() <= 0 || size.cy() <= 0; }
//inline bool is_empty(::size_f32 & size) { return size.cx() <= 0.f || size.cy() <= 0.f; }
//inline bool is_empty(::size_f64 & size) { return size.cx() <= 0. || size.cy() <= 0.; }








//inline bool contains(const ::rectangle_i64 & rectangle, const ::point_i32 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::rectangle_i64 & null(::rectangle_i64 & rectDst) { return ::null_rect(rectDst); }
//inline bool is_equal(const ::rectangle_i64 & rect1, const ::rectangle_i64 & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::rectangle_i64 & inflate(::rectangle_i64 & rectangle, i64 x, i64 y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::rectangle_i64 & deflate(::rectangle_i64 & rectangle, i64 x, i64 y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::rectangle_i64 & offset(::rectangle_i64 & rectangle, i64 x, i64 y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::rectangle_i64 & rectangle, const ::rectangle_i64 & rect1, const ::rectangle_i64 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::rectangle_i64 & unite(::rectangle_i64 & rectangle, const ::rectangle_i64 & rect1, const ::rectangle_i64 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline i64 width(const ::rectangle_i64 & rectangle) { return ::rect_width(rectangle); }
//inline i64 height(const ::rectangle_i64 & rectangle) { return ::rect_height(rectangle); }
//inline i64 area(const ::rectangle_i64 & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::rectangle_i64 & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::rectangle_i64 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline i64 width(const ::rectangle_i64 & rectangle) { return ::width(&rectangle); }
//inline i64 height(const ::rectangle_i64 & rectangle) { return ::height(&rectangle); }
//inline i64 area(const ::rectangle_i64 & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::rectangle_i64 & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::rectangle_i64 & rectangle) noexcept { ::swap_left_right(&rectangle); }





//inline bool contains(const ::rectangle_f32 & rectangle, const ::point_f32 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::rectangle_f32 & null(::rectangle_f32 & rect) { return ::null_rect(rect); }
//inline bool is_equal(const ::rectangle_f32 & rect1, const ::rectangle_f32 & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::rectangle_f32 & inflate(::rectangle_f32 & rectangle, float x, float y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::rectangle_f32 & deflate(::rectangle_f32 & rectangle, float x, float y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::rectangle_f32 & offset(::rectangle_f32 & rectangle, float x, float y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::rectangle_f32 & rectangle, const ::rectangle_f32 & rect1, const ::rectangle_f32 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::rectangle_f32 & unite(::rectangle_f32 & rectangle, const ::rectangle_f32 & rect1, const ::rectangle_f32 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline float width(const ::rectangle_f32 & rectangle) { return ::rect_width(rectangle); }
////template < primitive_rectangle RECTANGLE > 
////inline auto height(const RECTANGLE  & rectangle) { return ::rect_height(rectangle); }
////template < primitive_rectangle RECTANGLE >
////inline auto height(const RECTANGLE & rectangle) { return ::height(&rectangle); }
//inline float area(const ::rectangle_f32 & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::rectangle_f32 & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::rectangle_f32 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline float width(const ::rectangle_f32& rectangle) { return ::width(&rectangle); }
////inline float height(const ::rectangle_f32& rectangle) { return ::height(&rectangle); }
//inline float area(const ::rectangle_f32& rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::rectangle_f32& rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::rectangle_f32& rectangle) noexcept { ::swap_left_right(&rectangle); }




//inline bool contains(const ::rectangle_f64 & rectangle, const ::point_f64 & point) { return ::rectangle_contains(rectangle, point.x(), point.y()); }
//inline ::rectangle_f64 & null(::rectangle_f64 & rect) { return ::null_rect(rect); }
//inline bool is_equal(const ::rectangle_f64 & rect1, const ::rectangle_f64 & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::rectangle_f64 & inflate(::rectangle_f64 & rectangle, double x, double y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::rectangle_f64 & deflate(::rectangle_f64 & rectangle, double x, double y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::rectangle_f64 & offset(::rectangle_f64 & rectangle, double x, double y) { return ::offset_rect(rectangle, x, y); }

template < primitive_rectangle RECTANGLE >
inline RECTANGLE & rate_deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);


//inline bool intersect(::rectangle_f64 & rectangle, const ::rectangle_f64 & rect1, const ::rectangle_f64 & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::rectangle_f64 & unite(::rectangle_f64 & rectangle, const ::rectangle_f64 & rect1, const ::rectangle_f64 & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline double width(const ::rectangle_f64 & rectangle) { return ::rect_width(rectangle); }
////inline double height(const ::rectangle_f64  & rectangle) { return ::rect_height(rectangle); }
//inline double area(const ::rectangle_f64 & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::rectangle_f64 & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::rectangle_f64 & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline double width(const ::rectangle_f64 & rectangle) { return ::width(&rectangle); }
//inline double height(const ::rectangle_f64& rectangle) { return ::height(&rectangle); }
//inline double area(const ::rectangle_f64 & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::rectangle_f64 & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::rectangle_f64 & rectangle) noexcept { ::swap_left_right(&rectangle); }

//inline ::point_i64 & operator -= (::point_i64 & point, const ::point_i64 & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::point_i64 & operator += (::point_i64 & point, const ::point_i64 & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline ::point_f32 & operator -= (::point_f32 & point, const ::point_f32 & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::point_f32 & operator += (::point_f32 & point, const ::point_f32 & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline ::point_f64 & operator -= (::point_f64 & point, const ::point_f64 & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::point_f64 & operator += (::point_f64 & point, const ::point_f64 & pointOffset) { ::point_add(point, pointOffset); return point; }



//inline ::rectangle_i64& operator -= (::rectangle_i64& rectangle, const ::point_i64& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::rectangle_i64& operator += (::rectangle_i64& rectangle, const ::point_i64& point) { ::rect_add(rectangle, point); return rectangle; }
//inline ::rectangle_f32& operator -= (::rectangle_f32& rectangle, const ::point_f32& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::rectangle_f32& operator += (::rectangle_f32& rectangle, const ::point_f32& point) { ::rect_add(rectangle, point); return rectangle; }
//inline ::rectangle_f64& operator -= (::rectangle_f64& rectangle, const ::point_f64& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::rectangle_f64& operator += (::rectangle_f64& rectangle, const ::point_f64& point) { ::rect_add(rectangle, point); return rectangle; }

//inline bool deflate(::rectangle_i32  & rectangle, const ::rectangle_i32 & prectParam);


#include "_point.h"
#include "_size.h"
#include "_rectangle.h"



#include "types.h"





//inline bool get_bounding_rectangle(::rectangle_f64 & rectangleBounding, const ::rectangle_i32 &rectangle)
//{
//
//   copy(rectangleBounding, rectangle);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(::rectangle_i32 & rectangleBounding, const ::rectangle_f64 & rectangle)
//{
//
//   copy(rectangleBounding, rectangle);
//
//   return true;
//
//}


//inline bool get_bounding_rectangle(::rectangle_f64 & rectangleBounding, const ::rectangle_f64 & rectangle)
//{
//
//   copy(rectangleBounding, rectangle);
//
//   return true;
//
//}








//#ifdef UNIVERSAL_WINDOWS
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
//inline auto ::point_i32(const ::size_i32 & size) noexcept { return ::point_i32(size.cx(), size.cy()); }
//inline auto __point64(const ::size_i64 & size) noexcept { return ::point_i64(size.cx(), size.cy()); }
//inline auto __pointf(const ::size_f32 & size) noexcept { return ::point_f32(size.cx(), size.cy()); }
//inline auto __pointd(const ::size_f64 & size) noexcept { return ::point_f64(size.cx(), size.cy()); }
//





