#pragma once


enum e_orientation
{

   orientation_horizontal = -1,
   orientation_none = 0,
   orientation_vertical = 1,

};


inline auto left(const RECT * prect) { return prect->left; }
inline auto top(const RECT * prect) { return prect->top; }
inline auto left(const RECT64 * prect) { return prect->left; }
inline auto top(const RECT64 * prect) { return prect->top; }
inline auto left(const RECTF * prect) { return prect->left; }
inline auto top(const RECTF * prect) { return prect->top; }
inline auto left(const RECTD * prect) { return prect->left; }
inline auto top(const RECTD * prect) { return prect->top; }



template < typename TARGET, typename SOURCE >
inline TARGET * _001CopyRect(TARGET * prectTarget, const SOURCE * prectSource);


template < typename XYWH, typename X, typename Y, typename W, typename H >
inline auto set_XYWH_dim(XYWH * prectTarget, X x, Y y, W w, H h)
{

   prectTarget->X = (decltype(prectTarget->X)) x;
   prectTarget->Y = (decltype(prectTarget->Y)) y;
   prectTarget->Width = (decltype(prectTarget->Width)) w;
   prectTarget->Height = (decltype(prectTarget->Height)) h;

   return prectTarget;

}


template < typename A, typename B >
void __swap(A& a, B& b)
{

   A aCopy = a;

   a = b;

   b = aCopy;

}


template < typename RECT_TYPE, typename X >
inline X x_offset_rect(RECT_TYPE * prect, X x)
{

   prect->left = (decltype(RECT_TYPE::left)) (prect->left + x);

   prect->right = (decltype(RECT_TYPE::right)) (prect->right + x);

   return x;

}


template < typename RECT_TYPE, typename Y >
inline Y y_offset_rect(RECT_TYPE * prect, Y y)
{

   prect->top = (decltype(RECT_TYPE::top)) (prect->top + y);

   prect->bottom = (decltype(RECT_TYPE::bottom)) (prect->bottom + y);

   return y;

}



template < typename RECT_TYPE, typename X >
inline X x_subtract_rect(RECT_TYPE* prect, X x)
{

   prect->left = (decltype(RECT_TYPE::left))(prect->left - x);

   prect->right = (decltype(RECT_TYPE::right))(prect->right - x);

   return x;

}


template < typename RECT_TYPE, typename Y >
inline Y y_subtract_rect(RECT_TYPE * prect, Y y)
{

   prect->top = (decltype(RECT_TYPE::top))(prect->top - y);

   prect->bottom = (decltype(RECT_TYPE::bottom))(prect->bottom - y);

   return y;

}


template < typename RECT_TYPE, typename X, typename Y >
inline RECT_TYPE * offset_rect(RECT_TYPE * prect, X x, Y y)
{

   x_offset_rect(prect, x);

   y_offset_rect(prect, y);

   return prect;

}


template < typename RECT_TYPE, typename X, typename Y >
inline RECT_TYPE* subtract_rect(RECT_TYPE* prect, X x, Y y)
{

   x_subtract_rect(prect, x);

   y_subtract_rect(prect, y);

   return prect;

}

template < typename RECT_TYPE, typename POINT_TYPE >
inline RECT_TYPE * offset_rect(RECT_TYPE * prect, const POINT_TYPE & point)
{

   return offset_rect(prect, point.x, point.y);

}



template < typename RECT_TYPE, typename POINT_TYPE >
inline RECT_TYPE* subtract_rect(RECT_TYPE* prect, const POINT_TYPE& point)
{

   return subtract_rect(prect, point.x, point.y);

}

template < typename RECT_TYPE, typename POINT_TYPE >
inline RECT_TYPE* rect_sub(RECT_TYPE* prect, const POINT_TYPE& point) { return subtract_rect(prect, point); }



template < typename POINT_TYPE, typename X, typename Y >
inline POINT_TYPE * offset_point(POINT_TYPE* ppoint, X x, Y y)
{

   ppoint->x = (decltype(POINT_TYPE::x))(ppoint->x + x);
   ppoint->y = (decltype(POINT_TYPE::y))(ppoint->y + y);

   return ppoint;

}


template < typename POINT_TYPE, typename POINT_TYPE2 >
inline POINT_TYPE* offset_point(POINT_TYPE* ppoint, const POINT_TYPE2& point2)
{

   return offset_point(ppoint, point2.x, point2.y);

}


template < typename POINT_TYPE, typename POINT_TYPE2 >
inline POINT_TYPE* point_add(POINT_TYPE* ppoint, const POINT_TYPE2& point) { return offset_point(ppoint, point); }


template < typename POINT_TYPE, typename X, typename Y >
inline POINT_TYPE * point_sub(POINT_TYPE * ppoint, X x, Y y)
{

   ppoint->x = (decltype(POINT_TYPE::x))(ppoint->x - x);
   ppoint->y = (decltype(POINT_TYPE::y))(ppoint->y - y);

   return ppoint;

}


template < typename POINT_TYPE, typename POINT_TYPE2 >
inline POINT_TYPE * point_sub(POINT_TYPE * ppoint, const POINT_TYPE2 & point2)
{

   return point_sub(ppoint, point2.x, point2.y);

}


template < typename POINT_TYPE, typename X, typename Y >
inline POINT_TYPE* subtract_point(POINT_TYPE* ppoint, X x, Y y)
{

   ppoint->x = (decltype(POINT_TYPE::x))(ppoint->x - x);
   ppoint->y = (decltype(POINT_TYPE::y))(ppoint->y - y);

   return ppoint;

}


template < typename POINT_TYPE, typename POINT_TYPE2 >
inline POINT_TYPE * subtract_point(POINT_TYPE * ppoint, const POINT_TYPE2 & point2)
{

   return subtract_point(ppoint, point2.x, point2.y);

}






template < typename RECT_TYPE, typename POINT_TYPE >
inline RECT_TYPE* rect_add(RECT_TYPE* prect, const POINT_TYPE& point) { return offset_rect(prect, point); }



template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool x_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   auto left   = MAX(prect1->left, prect2->left);

   auto right  = MIN(prect1->right, prect2->right);

   bool bIntersect = right > left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(prect))
   {

      prect->left = left;

      prect->right = right;

   }

   return bIntersect;

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool y_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   auto top     = MAX(prect1->top,prect2->top);

   auto bottom  = MIN(prect1->bottom,prect2->bottom);

   bool bIntersect = bottom > top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(prect))
   {

      prect->top = top;

      prect->bottom = bottom;

   }

   return bIntersect;

}

template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if (x_intersect_rect(prect, prect1, prect2) && y_intersect_rect(prect, prect1, prect2))
   {

      return true;

   }

   if (::is_set(prect))
   {

      null(prect);

   }

   return false;

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool x_null_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   auto left = MAX(prect1->left, prect2->left);

   auto right = MIN(prect1->right, prect2->right);

   bool bIntersect = right >= left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(prect))
   {

      prect->left = left;

      prect->right = right;

   }

   return bIntersect;

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool y_null_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   auto top = MAX(prect1->top, prect2->top);

   auto bottom = MIN(prect1->bottom, prect2->bottom);

   bool bIntersect = bottom >= top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(prect))
   {

      prect->top = top;

      prect->bottom = bottom;

   }

   return bIntersect;

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool null_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if(x_null_intersect_rect(prect, prect1, prect2) && y_null_intersect_rect(prect, prect1, prect2))
   {

      return true;

   }

   if(::is_set(prect))
   {

      null(prect);

   }

   return false;

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool x_left_null_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   prect->left    = MAX(prect1->left,prect2->left);

   prect->right   = MIN(prect1->right,prect2->right);

   return prect->right > prect->left || (prect->right == prect->left && prect1->left == prect2->left);

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool y_top_null_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   prect->top     = MAX(prect1->top, prect2->top);

   prect->bottom  = MIN(prect1->bottom, prect2->bottom);

   return prect->top < prect->bottom || (prect->top == prect->bottom && prect1->top == prect2->top);

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool top_left_null_intersect_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if(x_left_null_intersect_rect(prect,prect1,prect2) && y_top_null_intersect_rect(prect,prect1,prect2))
   {

      return true;

   }
   else
   {

      null(prect);

      return false;

   }

}


template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
RECT_TYPE * union_rect(RECT_TYPE * prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if (is_rect_empty(prect1))
   {

      if (is_rect_empty(prect2))
      {

         null_rect(prect);

      }
      else
      {

         copy_rect(prect, prect2);

      }

   }
   else if (is_rect_empty(prect1))
   {

      copy_rect(prect, prect1);

   }
   else
   {

      prect->left = (decltype(RECT_TYPE::left))MIN(prect1->left, prect2->left);
      prect->top = (decltype(RECT_TYPE::top))MIN(prect1->top, prect2->top);
      prect->right = (decltype(RECT_TYPE::right))MAX(prect1->right, prect2->right);
      prect->bottom = (decltype(RECT_TYPE::bottom))MAX(prect1->bottom, prect2->bottom);

   }

   return prect;

}

template < typename RECT_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
RECT_TYPE* subtract_rect(RECT_TYPE* prect, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{


   prect->left = (decltype(RECT_TYPE1::left))MIN(prect1->left, prect2->left);
   prect->top = (decltype(RECT_TYPE1::top))MIN(prect1->top, prect2->top);
   prect->right = (decltype(RECT_TYPE1::right))MAX(prect1->right, prect2->right);
   prect->bottom = (decltype(RECT_TYPE1::bottom))MAX(prect1->bottom, prect2->bottom);

   return prect;

}


template < typename RECT_TYPE1, typename RECT_TYPE2 >
RECT_TYPE1 * copy_rect(RECT_TYPE1 * prect1, const RECT_TYPE2* prect2)
{

   prect1->left = (decltype(RECT_TYPE1::left)) prect2->left;
   prect1->top = (decltype(RECT_TYPE1::top)) prect2->top;
   prect1->right = (decltype(RECT_TYPE1::right)) prect2->right;
   prect1->bottom = (decltype(RECT_TYPE1::bottom)) prect2->bottom;

   return prect1;

}


template < typename POINT_TYPE1, typename POINT_TYPE2 >
POINT_TYPE1 * copy_point(POINT_TYPE1 * ppoint1, const POINT_TYPE2 * ppoint2)
{

   ppoint1->x = (decltype(POINT_TYPE1::x))ppoint2->x;
   ppoint1->y = (decltype(POINT_TYPE1::y))ppoint2->y;

   return ppoint1;

}


template < typename SIZE_TYPE1, typename SIZE_TYPE2 >
SIZE_TYPE1 * copy_size(SIZE_TYPE1 * psize1, const SIZE_TYPE2 * psize2)
{

   psize1->cx = (decltype(SIZE_TYPE1::cx))psize2->cx;
   psize1->cy = (decltype(SIZE_TYPE1::cy))psize2->cy;

   return psize1;

}


template < typename X, typename Y >
auto get_dimension(e_orientation eorientation, X x, Y y);


template < typename X, typename Y >
auto get_normal_dimension(e_orientation eorientation, X x, Y y);



template < typename RECT_TYPE >
bool rect_equals(const RECT_TYPE* prect1, const RECT_TYPE* prect2)
{

   return prect1->left == prect2->left && prect1->top == prect2->top
      && prect1->right == prect2->right && prect1->bottom == prect2->bottom;

}


template < typename POINT_TYPE >
bool point_equals(const POINT_TYPE* ppoint1, const POINT_TYPE* ppoint2)
{

   return ppoint1->x == ppoint2->x && ppoint1->y == ppoint2->y;

}


template < typename SIZE_TYPE >
bool size_equals(const SIZE_TYPE* psize1, const SIZE_TYPE* psize2)
{

   return psize1->x == psize2->x && psize1->y == psize2->y;

}

template < typename RECT_TYPE, typename L, typename T, typename R, typename B >
RECT_TYPE * set_rect(RECT_TYPE* prect, L l, T t, R r, B b)
{

   prect->left = (decltype(RECT_TYPE::left))l;
   prect->top = (decltype(RECT_TYPE::top))t;
   prect->right = (decltype(RECT_TYPE::right))r;
   prect->bottom = (decltype(RECT_TYPE::bottom))b;

   return prect;

}





template < typename RECT_TYPE, typename L, typename T, typename W, typename H >
RECT_TYPE * set_rect_dim(RECT_TYPE* prect, L l, T t, W w, H h)
{

   prect->left = (decltype(RECT_TYPE::left))l;
   prect->top = (decltype(RECT_TYPE::top))t;
   prect->right = (decltype(RECT_TYPE::right))(l+w);
   prect->bottom = (decltype(RECT_TYPE::bottom))(t+h);

   return prect;

}

template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECT * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECT64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECTF * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECTD * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }


template < typename RECT_TYPE, typename POINT_TYPE, typename SIZE_TYPE >
RECT_TYPE* set_rect_point_size(RECT_TYPE* prect, const POINT_TYPE & point, const SIZE_TYPE & size)
{

   prect->left = (decltype(RECT_TYPE::left))point.x;
   prect->top = (decltype(RECT_TYPE::top))point.y;
   prect->right = (decltype(RECT_TYPE::right))(point.x + size.cx);
   prect->bottom = (decltype(RECT_TYPE::bottom))(point.y + size.cy);

   return prect;

}


template < typename RECT_TYPE >
RECT_TYPE * null_rect(RECT_TYPE* prect)
{

   return ::set_rect(prect, 0, 0, 0, 0);

}


template < typename RECT_TYPE >
constexpr auto rect_width(RECT_TYPE* prect) { return prect->right - prect->left; }


template < typename RECT_TYPE >
constexpr auto rect_height(RECT_TYPE* prect) { return prect->bottom - prect->top; }


template < typename W, typename H >
constexpr H rect_area(W w, H h) { return (w <= (W) 0 || h <= (H) 0) ? 0 : (H) (w * h); }


template < typename RECT_TYPE >
constexpr auto rect_area(RECT_TYPE* prect) { return rect_area(rect_width(prect), rect_height(prect)); }


template < typename RECT_TYPE >
constexpr auto is_rect_empty(RECT_TYPE * prect) { return ::is_null(prect) || prect->right <= prect->left || prect->bottom <= prect->top; }

template < typename RECT_TYPE >
bool is_rect_null(const RECT_TYPE* prect)
{

   return prect->left == (decltype(RECT_TYPE::left))0
      && prect->top == (decltype(RECT_TYPE::top))0
      && prect->right == (decltype(RECT_TYPE::right))0
      && prect->bottom == (decltype(RECT_TYPE::bottom))0;

}


template < typename SIZE_TYPE >
bool is_size_null(const SIZE_TYPE* psize)
{

   return psize->cx == (decltype(SIZE_TYPE::cx))0
      && psize->cy == (decltype(SIZE_TYPE::cy))0;

}


template < typename POINT_TYPE >
bool is_point_null(const POINT_TYPE* ppoint)
{

   return ppoint->x == (decltype(POINT_TYPE::cx))0
      && ppoint->y == (decltype(POINT_TYPE::cy))0;

}



template < typename RECT_BASE_TYPE, typename X >
inline bool rect_contains_x(const RECT_BASE_TYPE * prect, X x)
{

   return x >= prect->left && x <= prect->right;

}


template < typename RECT_BASE_TYPE, typename Y >
inline bool rect_contains_y(const RECT_BASE_TYPE * prect, Y y)
{

   return y >= prect->top && y <= prect->bottom;

}


template < typename RECT_BASE_TYPE, typename X, typename Y >
inline bool rect_contains(const RECT_BASE_TYPE * prect, X x, Y y)
{

   return rect_contains_x(prect, x) && rect_contains_y(prect, y);

}


template < typename RECT_TYPE, typename L, typename T, typename R, typename B >
inline RECT_TYPE* rect_inflate(RECT_TYPE* prect, L l, T t, R r, B b)
{

   prect->left = (decltype(RECT_TYPE::left))(prect->left - l);
   prect->top = (decltype(RECT_TYPE::top))(prect->top - t);
   prect->right = (decltype(RECT_TYPE::right))(prect->right + r);
   prect->bottom = (decltype(RECT_TYPE::bottom))(prect->bottom + b);

   return prect;

}


template < typename RECT_TYPE, typename RECT_TYPE2 >
inline RECT_TYPE* rect_inflate(RECT_TYPE* prect, const RECT_TYPE2* prect2)
{

   return rect_inflate(prect, prect2->left, prect2->top, prect2->right, prect2->bottom);

}


template < typename RECT_TYPE, typename RECT_TYPE2 >
inline RECT_TYPE* rect_multiply_inline(RECT_TYPE* prect, const RECT_TYPE2* prect2)
{

   prect->left *= prect2->left;
   prect->top *= prect2->top;
   prect->right *= prect2->right;
   prect->bottom *= prect2->bottom;

   return prect;

}

template < typename RECT_TYPE, typename L, typename T, typename R, typename B >
inline RECT_TYPE* rect_deflate(RECT_TYPE* prect, L l, T t, R r, B b)
{

   prect->left = (decltype(RECT_TYPE::left))(prect->left + l);
   prect->top = (decltype(RECT_TYPE::top))(prect->top + t);
   prect->right = (decltype(RECT_TYPE::right))(prect->right - r);
   prect->bottom = (decltype(RECT_TYPE::bottom))(prect->bottom - b);

   return prect;

}


template < typename RECT_TYPE, typename RECT_TYPE2 >
inline RECT_TYPE* rect_deflate(RECT_TYPE* prect, const RECT_TYPE2* prect2)
{

   return rect_deflate(prect, prect2->left, prect2->top, prect2->right, prect2->bottom);

}


template < typename RECT_TYPE, typename X, typename Y >
inline RECT_TYPE* rect_inflate_point(RECT_TYPE* prect, X x, Y y)
{

   return rect_inflate(prect, x, y, x, y);

}

template < typename RECT_TYPE, typename X, typename Y >
inline RECT_TYPE* rect_deflate_point(RECT_TYPE* prect, X x, Y y)
{

   return rect_deflate(prect, x, y, x, y);

}


template < typename RECT_TYPE, typename UNIT >
inline RECT_TYPE* rect_inflate_unit(RECT_TYPE* prect, UNIT u)
{

   return rect_inflate_point(prect, u, u);

}


template < typename RECT_TYPE, typename UNIT >
inline RECT_TYPE* rect_deflate_unit(RECT_TYPE* prect, UNIT u)
{

   return rect_deflate_point(prect, u, u);

}


template < typename RECT_TYPE >
inline RECT_TYPE* swap_rect_left_right(RECT_TYPE* prect) { __swap(prect->left, prect->right); return prect; }



template < typename POINT_TYPE >
inline bool polygon_contains_point(const POINT_TYPE * ppPolygon, i32 iCount, const POINT_TYPE & point)
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




template < typename SIZE_BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
class size_type;

template < typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE, typename RECT_BASE_TYPE >
class point_type;

template < typename RECT_BASE_TYPE, typename POINT_TYPE, typename SIZE_TYPE >
class rect_type;

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


inline LONG area(LONG cx, LONG cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline i64 area(i64 cx, i64 cy) { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
inline double area(double cx, double cy) { return (cx < 0. && cy < 0. ? -1. : 1.) * cx * cy; }



struct SIZE64;
struct POINT64;
struct RECT64;
//::size;
//class size64;
//class sized;
//::point;
//class point64;
//class pointd;
//::prect;
//::rect64;
//::rectd;

typedef uchar      byte;

struct POINT64;
struct SIZE64;
struct RECT64;
struct POINTD;
struct SIZED;
struct RECTD;



using point = point_type < POINT, SIZE, RECT >;
using point64 = point_type < POINT64, SIZE64, RECT64 >;
using pointf = point_type < POINTF, SIZEF, RECTF >;
using pointd = point_type < POINTD, SIZED, RECTD >;


using size = size_type < SIZE, POINT, RECT >;
using size64 = size_type < SIZE64, POINT64, RECT64 >;
using sizef = size_type < SIZEF, POINTF, RECTF >;
using sized = size_type < SIZED, POINTD, RECTD >;


using rect = rect_type < RECT, POINT, SIZE >;
using rect64 = rect_type < RECT64, POINT64, SIZE64 >;
using rectf = rect_type < RECTF, POINTF, SIZEF >;
using rectd = rect_type < RECTD, POINTD, SIZED >;

using point_array = point_array_base < point >;
using point64_array = point_array_base < point64 >;
using pointf_array = point_array_base < pointf >;
using pointd_array = point_array_base < pointd >;


inline float i32muldiv(float f, i32 iNum, i32 iDen);
inline double i32muldiv(double d, i32 iNum, i32 iDen);
inline i32 i32muldiv(i32 i, i32 iNum, i32 iDen);
#ifndef WINDOWS
inline i64 MulDiv(i64 nNumber, i32 iNum, i32 iDen);
#endif
inline i64 i32muldiv(i64 i, i32 iNum, i32 iDen);


inline void copy(POINT* ppointDst, const POINT* ppointSrc) { *ppointDst = *ppointSrc; }
inline void copy(POINT* ppointDst, const POINT64* ppointSrc) { ::copy_point(ppointDst, ppointSrc);}
inline void copy(POINT* ppointDst, const POINTF* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINT* ppointDst, const POINTD* ppointSrc) { ::copy_point(ppointDst, ppointSrc ); }
inline void copy(POINT64* ppointDst, const POINT* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINT64* ppointDst, const POINT64* ppointSrc) { *ppointDst = *ppointSrc; }
inline void copy(POINT64* ppointDst, const POINTF* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINT64* ppointDst, const POINTD* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINTF* ppointDst, const POINT* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINTF* ppointDst, const POINT64* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINTF* ppointDst, const POINTF* ppointSrc) { *ppointDst = *ppointSrc; }
inline void copy(POINTF* ppointDst, const POINTD* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINTD* ppointDst, const POINT* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINTD* ppointDst, const POINT64* ppointSrc) { ::copy_point(ppointDst, ppointSrc); }
inline void copy(POINTD* ppointDst, const POINTD* ppointSrc) { *ppointDst=*ppointSrc; }

inline void copy(SIZE* psizeDst, const SIZE* psizeSrc) { *psizeDst = *psizeSrc; }
inline void copy(SIZE* psizeDst, const SIZE64* psizeSrc) { ::copy_size(psizeDst, psizeSrc ); }
inline void copy(SIZE* psizeDst, const SIZEF* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZE* psizeDst, const SIZED* psizeSrc) { ::copy_size(psizeDst, psizeSrc ); }
inline void copy(SIZE64* psizeDst, const SIZE* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZE64* psizeDst, const SIZE64* psizeSrc) { *psizeDst = *psizeSrc; }
inline void copy(SIZE64* psizeDst, const SIZEF* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZE64* psizeDst, const SIZED* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZEF* psizeDst, const SIZE* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZEF* psizeDst, const SIZE64* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZEF* psizeDst, const SIZEF* psizeSrc) { *psizeDst = *psizeSrc; }
inline void copy(SIZEF* psizeDst, const SIZED* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZED* psizeDst, const SIZE* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZED* psizeDst, const SIZE64* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZED* psizeDst, const SIZEF* psizeSrc) { ::copy_size(psizeDst, psizeSrc); }
inline void copy(SIZED* psizeDst, const SIZED* psizeSrc) { *psizeDst = *psizeSrc; }

inline void copy(RECT* prectDst, const RECT* prectSrc) { *prectDst=*prectSrc; }
inline void copy(RECT* prectDst, const RECT64* prectSrc) { ::copy_rect(prectDst, prectSrc ); }
inline void copy(RECT* prectDst, const RECTF* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECT* prectDst, const RECTD* prectSrc) { ::copy_rect(prectDst, prectSrc ); }
inline void copy(RECT64* prectDst, const RECT* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECT64* prectDst, const RECT64* prectSrc) { *prectDst = *prectSrc; }
inline void copy(RECT64* prectDst, const RECTF* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECT64* prectDst, const RECTD* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECTF* prectDst, const RECT* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECTF* prectDst, const RECT64* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECTF* prectDst, const RECTF* prectSrc) { *prectDst = *prectSrc; }
inline void copy(RECTF* prectDst, const RECTD* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECTD* prectDst, const RECT* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECTD* prectDst, const RECT64* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECTD* prectDst, const RECTF* prectSrc) { ::copy_rect(prectDst, prectSrc); }
inline void copy(RECTD* prectDst, const RECTD* prectSrc) { *prectDst = *prectSrc; }










inline bool contains(const RECT* prect, const POINT& point) { return ::rect_contains(prect, point.x, point.y); }
inline RECT* null(RECT* prectDst) { return ::null_rect(prectDst); }
inline bool is_equal(const RECT* prect1, const RECT* prect2) { return ::rect_equals(prect1, prect2); }
inline RECT* inflate(RECT * prect, LONG x, LONG y) { return ::rect_inflate_point(prect, x, y); }
inline RECT* deflate(RECT * prect, LONG x, LONG y) { return ::rect_deflate_point(prect, x, y); }
inline RECT* offset(RECT * prect, LONG x, LONG y) { return ::offset_rect(prect, x, y); }
inline bool intersect(RECT * prect, const RECT * prect1, const RECT * prect2) { return ::intersect_rect(prect, prect1, prect2); }
inline bool unite(RECT * prect, const RECT * prect1, const RECT * prect2) { return ::union_rect(prect, prect1, prect2); }
inline LONG width(const RECT * prect) { return ::rect_width(prect); }
inline LONG height(const RECT * prect) { return ::rect_height(prect); }
inline LONG area(const RECT * prect) { return ::rect_area(prect); }
inline bool is_empty(const RECT * prect) { return ::is_rect_empty(prect); }
inline void swap_left_right(RECT * prect) noexcept { ::__swap(prect->left, prect->right); }

inline LONG width(const RECT & rect) { return ::width(&rect); }
inline LONG height(const RECT & rect) { return ::height(&rect); }
inline LONG area(const RECT & rect) { return ::area(&rect); }
inline bool is_empty(const RECT & rect) { return ::is_empty(&rect); }
inline void swap_left_right(RECT & rect) noexcept { ::swap_left_right(&rect); }



inline bool is_empty(SIZE* psize){ return psize->cx <= 0 || psize->cy <= 0; }
inline bool is_empty(SIZE64* psize) { return psize->cx <= 0 || psize->cy <= 0; }
inline bool is_empty(SIZEF* psize) { return psize->cx <= 0.f || psize->cy <= 0.f; }
inline bool is_empty(SIZED* psize) { return psize->cx <= 0. || psize->cy <= 0.; }








inline bool contains(const RECT64* prect, const POINT& point) { return ::rect_contains(prect, point.x, point.y); }
inline RECT64* null(RECT64* prectDst) { return ::null_rect(prectDst); }
inline bool is_equal(const RECT64* prect1, const RECT64* prect2) { return ::rect_equals(prect1, prect2); }
inline RECT64* inflate(RECT64 * prect, i64 x, i64 y) { return ::rect_inflate_point(prect, x, y); }
inline RECT64* deflate(RECT64 * prect, i64 x, i64 y) { return ::rect_deflate_point(prect, x, y); }
inline RECT64* offset(RECT64 * prect, i64 x, i64 y) { return ::offset_rect(prect, x, y); }
inline bool intersect(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2) { return ::intersect_rect(prect, prect1, prect2); }
inline bool unite(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2) { return ::union_rect(prect, prect1, prect2); }
inline i64 width(const RECT64 * prect) { return ::rect_width(prect); }
inline i64 height(const RECT64 * prect) { return ::rect_height(prect); }
inline i64 area(const RECT64 * prect) { return ::rect_area(prect); }
inline bool is_empty(const RECT64 * prect) { return ::is_rect_empty(prect); }
inline void swap_left_right(RECT64 * prect) noexcept { ::__swap(prect->left, prect->right); }

inline i64 width(const RECT64 & rect) { return ::width(&rect); }
inline i64 height(const RECT64 & rect) { return ::height(&rect); }
inline i64 area(const RECT64 & rect) { return ::area(&rect); }
inline bool is_empty(const RECT64 & rect) { return ::is_empty(&rect); }
inline void swap_left_right(RECT64 & rect) noexcept { ::swap_left_right(&rect); }





inline bool contains(const RECTF* prect, const POINTF& point) { return ::rect_contains(prect, point.x, point.y); }
inline RECTF* null(RECTF* prectFst) { return ::null_rect(prectFst); }
inline bool is_equal(const RECTF* prect1, const RECTF* prect2) { return ::rect_equals(prect1, prect2); }
inline RECTF* inflate(RECTF* prect, float x, float y) { return ::rect_inflate_point(prect, x, y); }
inline RECTF* deflate(RECTF* prect, float x, float y) { return ::rect_deflate_point(prect, x, y); }
inline RECTF* offset(RECTF* prect, float x, float y) { return ::offset_rect(prect, x, y); }
inline bool intersect(RECTF* prect, const RECTF* prect1, const RECTF* prect2) { return ::intersect_rect(prect, prect1, prect2); }
inline bool unite(RECTF* prect, const RECTF* prect1, const RECTF* prect2) { return ::union_rect(prect, prect1, prect2); }
inline float width(const RECTF* prect) { return ::rect_width(prect); }
inline float height(const RECTF* prect) { return ::rect_height(prect); }
inline float area(const RECTF* prect) { return ::rect_area(prect); }
inline bool is_empty(const RECTF* prect) { return ::is_rect_empty(prect); }
inline void swap_left_right(RECTF* prect) noexcept { ::__swap(prect->left, prect->right); }

inline float width(const RECTF& rect) { return ::width(&rect); }
inline float height(const RECTF& rect) { return ::height(&rect); }
inline float area(const RECTF& rect) { return ::area(&rect); }
inline bool is_empty(const RECTF& rect) { return ::is_empty(&rect); }
inline void swap_left_right(RECTF& rect) noexcept { ::swap_left_right(&rect); }




inline bool contains(const RECTD * prect, const POINTD & point) { return ::rect_contains(prect, point.x, point.y); }
inline RECTD* null(RECTD* prectDst) { return ::null_rect(prectDst); }
inline bool is_equal(const RECTD* prect1, const RECTD* prect2) { return ::rect_equals(prect1, prect2); }
inline RECTD* inflate(RECTD* prect, double x, double y) { return ::rect_inflate_point(prect, x, y); }
inline RECTD* deflate(RECTD* prect, double x, double y) { return ::rect_deflate_point(prect, x, y); }
inline RECTD* offset(RECTD* prect, double x, double y) { return ::offset_rect(prect, x, y); }
inline bool intersect(RECTD* prect, const RECTD* prect1, const RECTD* prect2) { return ::intersect_rect(prect, prect1, prect2); }
inline bool unite(RECTD * prect, const RECTD * prect1, const RECTD * prect2) { return ::union_rect(prect, prect1, prect2); }
inline double width(const RECTD * prect) { return ::rect_width(prect); }
inline double height(const RECTD * prect) { return ::rect_height(prect); }
inline double area(const RECTD * prect) { return ::rect_area(prect); }
inline bool is_empty(const RECTD* prect) { return ::is_rect_empty(prect); }
inline void swap_left_right(RECTD * prect) noexcept { ::__swap(prect->left, prect->right); }

inline double width(const RECTD & rect) { return ::width(&rect); }
inline double height(const RECTD& rect) { return ::height(&rect); }
inline double area(const RECTD & rect) { return ::area(&rect); }
inline bool is_empty(const RECTD & rect) { return ::is_empty(&rect); }
inline void swap_left_right(RECTD & rect) noexcept { ::swap_left_right(&rect); }

inline POINT & operator -= (POINT & point, const ::point & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINT & operator += (POINT & point, const ::point & pointOffset) { ::point_add(&point, pointOffset); return point; }
inline POINT64 & operator -= (POINT64 & point, const ::point64 & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINT64 & operator += (POINT64 & point, const ::point64 & pointOffset) { ::point_add(&point, pointOffset); return point; }
inline POINTF & operator -= (POINTF & point, const ::pointf & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINTF & operator += (POINTF & point, const ::pointf & pointOffset) { ::point_add(&point, pointOffset); return point; }
inline POINTD & operator -= (POINTD & point, const ::pointd & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINTD & operator += (POINTD & point, const ::pointd & pointOffset) { ::point_add(&point, pointOffset); return point; }


inline RECT& operator -= (RECT& rect, const ::point& point) { ::rect_sub(&rect, point); return rect; }
inline RECT& operator += (RECT& rect, const ::point& point) { ::rect_add(&rect, point); return rect; }
inline RECT64& operator -= (RECT64& rect, const ::point64& point) { ::rect_sub(&rect, point); return rect; }
inline RECT64& operator += (RECT64& rect, const ::point64& point) { ::rect_add(&rect, point); return rect; }
inline RECTF& operator -= (RECTF& rect, const ::pointf& point) { ::rect_sub(&rect, point); return rect; }
inline RECTF& operator += (RECTF& rect, const ::pointf& point) { ::rect_add(&rect, point); return rect; }
inline RECTD& operator -= (RECTD& rect, const ::pointd& point) { ::rect_sub(&rect, point); return rect; }
inline RECTD& operator += (RECTD& rect, const ::pointd& point) { ::rect_add(&rect, point); return rect; }

//inline bool deflate(RECT * prect, const ::rect & prectParam);


#include "point.h"
#include "size.h"
#include "rect.h"


inline void copy(::rect* prectDst, const ::rect* prectSrc) { *prectDst=*prectSrc; }
inline void copy(::rect64* prectDst, const ::rect64* prectSrc) { *prectDst=*prectSrc; }
inline void copy(::rectf* prectDst, const ::rectf* prectSrc) { *prectDst=*prectSrc; }
inline void copy(::rectd* prectDst, const ::rectd* prectSrc) { *prectDst=*prectSrc; }





#include "types.h"



CLASS_DECL_AURA double d_distance(const point & point1, const point & point2);


inline CLASS_DECL_AURA rect rect_dim(LONG x, LONG y, LONG cx, LONG cy)
{

   return rect(x, y, x + cx, y + cy);

}





template < typename X, typename Y, typename W, typename H >
inline rectd rectd_dim(X x, Y y, W w, H h)
{

   return rectd(x, y, x + w, y + h);

}

#ifdef APPLEOS

void copy(CGRect * prectTarget, const RECT * prectSource);
void copy(RECT * prectTarget, const CGRect * prectSource);
void copy(CGRect * prectTarget, const RECTD * prectSource);
void copy(RECTD * prectTarget, const CGRect * prectSource);
void window_copy(CGRect * prectTarget, const RECT * prectSource);
void window_copy(RECT * prectTarget, const CGRect * prectSource);


void copy(CGPoint * ppointTarget, const POINT * ppointSource);
void copy(POINT * ppointTarget, const CGPoint * ppointSource);
void copy(CGPoint * ppointTarget, const POINTD * ppointSource);
void copy(POINTD * ppointTarget, const CGPoint * ppointSource);

#endif

#ifdef WINDOWS

inline void copy(RECTF* prectDst, const D2D1_RECT_F* prectSrc) { ::copy_rect(prectDst, prectSrc); }

#endif

#ifdef _UWP

inline void copy(rect * prectDst, const Windows::Foundation::Rect * prectSrc)
{
   prectDst->left = (LONG) prectSrc->X;
   prectDst->top = (LONG)prectSrc->Y;
   prectDst->right = (LONG) (prectSrc->X + prectSrc->Width);
   prectDst->bottom = (LONG) (prectSrc->Y + prectSrc->Height);
}

inline void copy(Windows::Foundation::Rect* prectDst, rect* prectSrc)
{
   prectDst->X = (float) prectSrc->left;
   prectDst->Y = (float) prectSrc->top;
   prectDst->Width = (float) prectSrc->width();
   prectDst->Height = (float) prectSrc->height();
}

#endif


inline auto __point(const ::lparam & lparam) noexcept { return ::point(lparam.x(), lparam.y()); }
inline auto __point(const ::u32 u) noexcept { return ::point((LONG)__u32x(u), (LONG)__u32y(u)); }
inline auto __point(const ::u64 u) noexcept { return ::point((LONG)__u64x(u), (LONG)__u64y(u)); }
inline auto __point(const ::size & size) noexcept { return ::point(size.cx, size.cy); }

inline auto __point64(const ::lparam & lparam) noexcept { return ::point64(lparam.x(), lparam.y()); }
inline auto __point64(const ::u32 u) noexcept { return ::point64((i64)__u32x(u), (i64)__u32y(u)); }
inline auto __point64(const ::u64 u) noexcept { return ::point64((i64)__u64x(u), (i64)__u64y(u)); }
inline auto __point64(const ::size64 & size) noexcept { return ::point64(size.cx, size.cy); }


inline auto __pointf(const ::lparam & lparam) noexcept { return ::pointf((float)lparam.x(), (float)lparam.y()); }
inline auto __pointf(const ::u32 u) noexcept { return ::pointf((float)__u32x(u), (float)__u32y(u)); }
inline auto __pointf(const ::u64 u) noexcept { return ::pointf((float)__u64x(u), (float)__u64y(u)); }
inline auto __pointf(const ::sizef & size) noexcept { return ::pointf(size.cx, size.cy); }


inline auto __pointd(const ::lparam & lparam) noexcept { return ::pointd(lparam.x(), lparam.y()); }
inline auto __pointd(const ::u32 u) noexcept { return ::pointd((double)__u32x(u), (double)__u32y(u)); }
inline auto __pointd(const ::u64 u) noexcept { return ::pointd((double)__u64x(u), (double)__u64y(u)); }
inline auto __pointd(const ::sized & size) noexcept { return ::pointd(size.cx, size.cy); }

#ifdef _UWP

inline ::Windows::Foundation::Rect ScaleRect(::Windows::Foundation::Rect rect, double scale)
{

   rect.X = (float)(rect.X*scale);
   rect.Y = (float)(rect.Y* scale);
   rect.Width = (float)(rect.Width * scale);
   rect.Height = (float)(rect.Height*scale);

   return rect;

}


#endif



