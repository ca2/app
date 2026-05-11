#pragma once


#include "angle.h"


//#include "_geometry2d.h"


#include "_concept.h"


// inline auto left(const ::i32_rectangle &rectangle) { return rectangle.left; }
// inline auto top(const ::i32_rectangle &rectangle) { return rectangle.top; }
// inline auto left(const ::i64_rectangle & rectangle) { return rectangle.left; }
// inline auto top(const ::i64_rectangle & rectangle) { return rectangle.top; }
// inline auto left(const ::float_rectangle & rectangle) { return rectangle.left; }
// inline auto top(const ::float_rectangle & rectangle) { return rectangle.top; }
// inline auto left(const ::double_rectangle & rectangle) { return rectangle.left; }
// inline auto top(const ::double_rectangle & rectangle) { return rectangle.top; }


//template < typename TARGET, typename SOURCE >
//inline TARGET & _001CopyRect(TARGET & prectTarget, const SOURCE & prectSource);




template < typename SIZE_BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class size_type;

template < typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class point_type;

template < typename RECTANGLE_BASE_TYPE, typename POINT_TYPE, typename SIZE_TYPE >
class rectangle_type;

template < typename POINT_TYPE >
class poi32_array_base;






inline int area(int cx, int cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline ::i64 area(::i64 cx, ::i64 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline double area(double cx, double cy) { return (cx < 0. && cy < 0. ? -1. : 1.) * cx * cy; }



struct ::i64_size;
struct ::i64_point;
struct ::i64_rectangle;
//::i32_size;
//class i64_size;
//class double_size;
//::i32_point;
//class i64_point;
//class double_point;
//::double_rectangle;
//::i64_rectangle;
//::double_rectangle;

typedef uchar      uch;

struct ::i64_point;
struct ::i64_size;
struct ::i64_rectangle;
struct ::double_point;
struct ::double_size;
struct ::double_rectangle;




//inline float i32muldiv(float f, int iNum, int iDen);
//inline double i32muldiv(double d, int iNum, int iDen);
//inline int i32muldiv(int i, int iNum, int iDen);
//#ifndef WINDOWS
//inline ::i64 MulDiv(::i64 nNumber, int iNum, int iDen);
//#endif
//inline ::i64 i32muldiv(::i64 i, ::i64 iNum, ::i64 iDen);


template < prototype_integral INTEGRAL1, prototype_integral INTEGRAL2, prototype_integral INTEGRAL3, prototype_integral INTEGRAL_RESULT = typename ::largest_type_of_3 < INTEGRAL1, INTEGRAL2, INTEGRAL3 >::type >
inline INTEGRAL_RESULT muldiv(INTEGRAL1 i, INTEGRAL2 iNumerator, INTEGRAL3 iDenominator);


template < prototype_rectangle RECTANGLE >
inline auto width(const RECTANGLE & rectangle) { return rectangle.right - rectangle.left; }

template < prototype_rectangle RECTANGLE >
inline auto height(const RECTANGLE & rectangle) { return rectangle.bottom - rectangle.top; }

template < prototype_rectangle RECTANGLE >
inline auto area(const RECTANGLE & rectangle) { return maximum(width(rectangle), 0) * maximum(height(rectangle), 0); }


template < prototype_rectangle RECTANGLE >
inline auto left(const RECTANGLE & rectangle) { return rectangle.left; }

template < prototype_rectangle RECTANGLE >
inline auto top(const RECTANGLE & rectangle) { return rectangle.top; }



template < prototype_XYDim XYDim >
inline auto width(const XYDim & rectangle) { return rectangle.Width; }

template < prototype_XYDim XYDim >
inline auto height(const XYDim & rectangle) { return rectangle.Height; }

template < prototype_XYDim XYDim >
inline auto area(const XYDim & rectangle) { return maximum(rectangle.Width, 0) * maximum(rectangle.Height, 0); }


template < prototype_XYDim XYDim >
inline auto left(const XYDim & rectangle) { return rectangle.X; }

template < prototype_XYDim XYDim >
inline auto top(const XYDim & rectangle) { return rectangle.Y; }


//template < prototype_rectangle RECTANGLE, prototype_XYDim XYDim >
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
//template < prototype_XYDim XYDim, prototype_rectangle RECTANGLE >
//inline void copy(XYDim & xydim, const RECTANGLE & rectangle)
//{
//
//   xydim.X = (decltype(xydim.X)) rectangle.left;
//   xydim.Y = (decltype(xydim.Y)) rectangle.top;
//   xydim.Width = (decltype(xydim.Width))(rectangle.right + rectangle.left);
//   xydim.Height = (decltype(xydim.Height))(rectangle.bottom + rectangle.top);
//
//}



//inline bool contains(const ::i32_rectangle &rectangle, const ::i32_point & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
//inline ::i32_rectangle & null(::i32_rectangle & rectDst) { return ::null_rect(rectDst); }
//inline bool is_equal(const ::i32_rectangle &rect1, const ::i32_rectangle &rect2) { return ::rect_equals(rect1, rect2); }
//inline ::i32_rectangle & inflate(::i32_rectangle & rectangle, int x, int y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::i32_rectangle & deflate(::i32_rectangle & rectangle, int x, int y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::i32_rectangle & offset(::i32_rectangle & rectangle, int x, int y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::i32_rectangle & rectangle, const ::i32_rectangle &rect1, const ::i32_rectangle &rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::i32_rectangle & unite(::i32_rectangle & rectangle, const ::i32_rectangle &rect1, const ::i32_rectangle &rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline int width(const ::i32_rectangle &rectangle) { return ::rect_width(rectangle); }
//inline int height(const ::i32_rectangle &rectangle) { return ::rect_height(rectangle); }
//inline int area(const ::i32_rectangle &rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::i32_rectangle &rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::i32_rectangle & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline int width(const ::i32_rectangle &rectangle) { return ::width(&rectangle); }
//inline int height(const ::i32_rectangle &rectangle) { return ::height(&rectangle); }
//inline int area(const ::i32_rectangle &rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::i32_rectangle &rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::i32_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }



//inline bool is_empty(::i32_size & size) { return size.cx <= 0 || size.cy <= 0; }
//inline bool is_empty(::i64_size & size) { return size.cx <= 0 || size.cy <= 0; }
//inline bool is_empty(::float_size & size) { return size.cx <= 0.f || size.cy <= 0.f; }
//inline bool is_empty(::double_size & size) { return size.cx <= 0. || size.cy <= 0.; }








//inline bool contains(const ::i64_rectangle & rectangle, const ::i32_point & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
//inline ::i64_rectangle & null(::i64_rectangle & rectDst) { return ::null_rect(rectDst); }
//inline bool is_equal(const ::i64_rectangle & rect1, const ::i64_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::i64_rectangle & inflate(::i64_rectangle & rectangle, ::i64 x, ::i64 y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::i64_rectangle & deflate(::i64_rectangle & rectangle, ::i64 x, ::i64 y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::i64_rectangle & offset(::i64_rectangle & rectangle, ::i64 x, ::i64 y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::i64_rectangle & rectangle, const ::i64_rectangle & rect1, const ::i64_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::i64_rectangle & unite(::i64_rectangle & rectangle, const ::i64_rectangle & rect1, const ::i64_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline ::i64 width(const ::i64_rectangle & rectangle) { return ::rect_width(rectangle); }
//inline ::i64 height(const ::i64_rectangle & rectangle) { return ::rect_height(rectangle); }
//inline ::i64 area(const ::i64_rectangle & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::i64_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::i64_rectangle & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline ::i64 width(const ::i64_rectangle & rectangle) { return ::width(&rectangle); }
//inline ::i64 height(const ::i64_rectangle & rectangle) { return ::height(&rectangle); }
//inline ::i64 area(const ::i64_rectangle & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::i64_rectangle & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::i64_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }





//inline bool contains(const ::float_rectangle & rectangle, const ::float_point & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
//inline ::float_rectangle & null(::float_rectangle & rect) { return ::null_rect(rect); }
//inline bool is_equal(const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::float_rectangle & inflate(::float_rectangle & rectangle, float x, float y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::float_rectangle & deflate(::float_rectangle & rectangle, float x, float y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::float_rectangle & offset(::float_rectangle & rectangle, float x, float y) { return ::offset_rect(rectangle, x, y); }
//inline bool intersect(::float_rectangle & rectangle, const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::float_rectangle & unite(::float_rectangle & rectangle, const ::float_rectangle & rect1, const ::float_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline float width(const ::float_rectangle & rectangle) { return ::rect_width(rectangle); }
////template < prototype_rectangle RECTANGLE > 
////inline auto height(const RECTANGLE  & rectangle) { return ::rect_height(rectangle); }
////template < prototype_rectangle RECTANGLE >
////inline auto height(const RECTANGLE & rectangle) { return ::height(&rectangle); }
//inline float area(const ::float_rectangle & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::float_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::float_rectangle & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline float width(const ::float_rectangle& rectangle) { return ::width(&rectangle); }
////inline float height(const ::float_rectangle& rectangle) { return ::height(&rectangle); }
//inline float area(const ::float_rectangle& rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::float_rectangle& rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::float_rectangle& rectangle) noexcept { ::swap_left_right(&rectangle); }




//inline bool contains(const ::double_rectangle & rectangle, const ::double_point & point) { return ::rectangle_contains(rectangle, point.x, point.y); }
//inline ::double_rectangle & null(::double_rectangle & rect) { return ::null_rect(rect); }
//inline bool is_equal(const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::rect_equals(rect1, rect2); }
//inline ::double_rectangle & inflate(::double_rectangle & rectangle, double x, double y) { return ::rect_inflate_point(rectangle, x, y); }
//inline ::double_rectangle & deflate(::double_rectangle & rectangle, double x, double y) { return ::rect_deflate_point(rectangle, x, y); }
//inline ::double_rectangle & offset(::double_rectangle & rectangle, double x, double y) { return ::offset_rect(rectangle, x, y); }

template < prototype_rectangle RECTANGLE >
inline RECTANGLE & rate_deflate(RECTANGLE & rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);


//inline bool intersect(::double_rectangle & rectangle, const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::intersect_rect(rectangle, rect1, rect2); }
//inline ::double_rectangle & unite(::double_rectangle & rectangle, const ::double_rectangle & rect1, const ::double_rectangle & rect2) { return ::union_rect(rectangle, rect1, rect2); }
//inline double width(const ::double_rectangle & rectangle) { return ::rect_width(rectangle); }
////inline double height(const ::double_rectangle  & rectangle) { return ::rect_height(rectangle); }
//inline double area(const ::double_rectangle & rectangle) { return ::rect_area(rectangle); }
//inline bool is_empty(const ::double_rectangle & rectangle) { return ::is_rect_empty(rectangle); }
//inline void swap_left_right(::double_rectangle & rectangle) noexcept { ::__swap(rectangle.left, rectangle.right); }

//inline double width(const ::double_rectangle & rectangle) { return ::width(&rectangle); }
//inline double height(const ::double_rectangle& rectangle) { return ::height(&rectangle); }
//inline double area(const ::double_rectangle & rectangle) { return ::area(&rectangle); }
//inline bool is_empty(const ::double_rectangle & rectangle) { return ::is_empty(&rectangle); }
//inline void swap_left_right(::double_rectangle & rectangle) noexcept { ::swap_left_right(&rectangle); }

//inline ::i64_point & operator -= (::i64_point & point, const ::i64_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::i64_point & operator += (::i64_point & point, const ::i64_point & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline ::float_point & operator -= (::float_point & point, const ::float_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::float_point & operator += (::float_point & point, const ::float_point & pointOffset) { ::point_add(point, pointOffset); return point; }
//inline ::double_point & operator -= (::double_point & point, const ::double_point & pointOffset) { ::point_sub(point, pointOffset); return point; }
//inline ::double_point & operator += (::double_point & point, const ::double_point & pointOffset) { ::point_add(point, pointOffset); return point; }



//inline ::i64_rectangle& operator -= (::i64_rectangle& rectangle, const ::i64_point& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::i64_rectangle& operator += (::i64_rectangle& rectangle, const ::i64_point& point) { ::rect_add(rectangle, point); return rectangle; }
//inline ::float_rectangle& operator -= (::float_rectangle& rectangle, const ::float_point& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::float_rectangle& operator += (::float_rectangle& rectangle, const ::float_point& point) { ::rect_add(rectangle, point); return rectangle; }
//inline ::double_rectangle& operator -= (::double_rectangle& rectangle, const ::double_point& point) { ::rect_sub(rectangle, point); return rectangle; }
//inline ::double_rectangle& operator += (::double_rectangle& rectangle, const ::double_point& point) { ::rect_add(rectangle, point); return rectangle; }

//inline bool deflate(::i32_rectangle  & rectangle, const ::i32_rectangle & prectParam);


#include "_point.h"
#include "_size.h"
#include "_rectangle.h"



#include "types.h"





//inline bool get_bounding_box(::double_rectangle & rectangleBounding, const ::i32_rectangle &rectangle)
//{
//
//   copy(rectangleBounding, rectangle);
//
//   return true;
//
//}


//inline bool get_bounding_box(::i32_rectangle & rectangleBounding, const ::double_rectangle & rectangle)
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
//inline void copy(i32_rectangle & rectDst, const ::winrt::Windows::Foundation::Rect * prectSrc)
//{
//   rectDst->left = (int) prectSrc->X;
//   rectDst->top = (int)prectSrc->Y;
//   rectDst->right = (int) (prectSrc->X + prectSrc->Width);
//   rectDst->bottom = (int) (prectSrc->Y + prectSrc->Height);
//}
//
//inline void copy(::winrt::Windows::Foundation::Rect& rectDst, i32_rectangle* prectSrc)
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


//template < prototype_point POINT >
//inline ::string as_string(const POINT & point);
//
//
//template < prototype_size SIZE >
//inline ::string as_string(const SIZE & size);
//



//
//inline auto ::i32_point(const ::i32_size & size) noexcept { return ::i32_point(size.cx, size.cy); }
//inline auto __point64(const ::i64_size & size) noexcept { return ::i64_point(size.cx, size.cy); }
//inline auto __pointf(const ::float_size & size) noexcept { return ::float_point(size.cx, size.cy); }
//inline auto __pointd(const ::double_size & size) noexcept { return ::double_point(size.cx, size.cy); }
//





