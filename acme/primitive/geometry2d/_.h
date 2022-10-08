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






inline auto left(const RECTANGLE_I32 * prectangle) { return prectangle->left; }
inline auto top(const RECTANGLE_I32 * prectangle) { return prectangle->top; }
inline auto left(const RECTANGLE_I64 * prectangle) { return prectangle->left; }
inline auto top(const RECTANGLE_I64 * prectangle) { return prectangle->top; }
inline auto left(const RECTANGLE_F32 * prectangle) { return prectangle->left; }
inline auto top(const RECTANGLE_F32 * prectangle) { return prectangle->top; }
inline auto left(const RECTANGLE_F64 * prectangle) { return prectangle->left; }
inline auto top(const RECTANGLE_F64 * prectangle) { return prectangle->top; }




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


template < typename RECTANGLE_TYPE, typename X >
inline X x_offset_rect(RECTANGLE_TYPE * prectangle, X x)
{

   prectangle->left = (decltype(RECTANGLE_TYPE::left)) (prectangle->left + x);

   prectangle->right = (decltype(RECTANGLE_TYPE::right)) (prectangle->right + x);

   return x;

}


template < typename RECTANGLE_TYPE, typename Y >
inline Y y_offset_rect(RECTANGLE_TYPE * prectangle, Y y)
{

   prectangle->top = (decltype(RECTANGLE_TYPE::top)) (prectangle->top + y);

   prectangle->bottom = (decltype(RECTANGLE_TYPE::bottom)) (prectangle->bottom + y);

   return y;

}



template < typename RECTANGLE_TYPE, typename X >
inline X x_subtract_rect(RECTANGLE_TYPE* prectangle, X x)
{

   prectangle->left = (decltype(RECTANGLE_TYPE::left))(prectangle->left - x);

   prectangle->right = (decltype(RECTANGLE_TYPE::right))(prectangle->right - x);

   return x;

}


template < typename RECTANGLE_TYPE, typename Y >
inline Y y_subtract_rect(RECTANGLE_TYPE * prectangle, Y y)
{

   prectangle->top = (decltype(RECTANGLE_TYPE::top))(prectangle->top - y);

   prectangle->bottom = (decltype(RECTANGLE_TYPE::bottom))(prectangle->bottom - y);

   return y;

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE * offset_rect(RECTANGLE_TYPE * prectangle, X x, Y y)
{

   x_offset_rect(prectangle, x);

   y_offset_rect(prectangle, y);

   return prectangle;

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE* subtract_rect(RECTANGLE_TYPE* prectangle, X x, Y y)
{

   x_subtract_rect(prectangle, x);

   y_subtract_rect(prectangle, y);

   return prectangle;

}

template < typename RECTANGLE_TYPE, typename POINT_TYPE >
inline RECTANGLE_TYPE * offset_rect(RECTANGLE_TYPE * prectangle, const POINT_TYPE & point)
{

   return offset_rect(prectangle, point.x, point.y);

}



template < typename RECTANGLE_TYPE, typename POINT_TYPE >
inline RECTANGLE_TYPE* subtract_rect(RECTANGLE_TYPE* prectangle, const POINT_TYPE& point)
{

   return subtract_rect(prectangle, point.x, point.y);

}

template < typename RECTANGLE_TYPE, typename POINT_TYPE >
inline RECTANGLE_TYPE* rect_sub(RECTANGLE_TYPE* prectangle, const POINT_TYPE& point) { return subtract_rect(prectangle, point); }



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






template < typename RECTANGLE_TYPE, typename POINT_TYPE >
inline RECTANGLE_TYPE* rect_add(RECTANGLE_TYPE* prectangle, const POINT_TYPE& point) { return offset_rect(prectangle, point); }



template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool x_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   auto left   = maximum(prect1->left, prect2->left);

   auto right  = minimum(prect1->right, prect2->right);

   bool bIntersect = right > left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(prectangle))
   {

      prectangle->left = left;

      prectangle->right = right;

   }

   return bIntersect;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool y_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   auto top     = maximum(prect1->top,prect2->top);

   auto bottom  = minimum(prect1->bottom,prect2->bottom);

   bool bIntersect = bottom > top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(prectangle))
   {

      prectangle->top = top;

      prectangle->bottom = bottom;

   }

   return bIntersect;

}

template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if (x_intersect_rect(prectangle, prect1, prect2) && y_intersect_rect(prectangle, prect1, prect2))
   {

      return true;

   }

   if (::is_set(prectangle))
   {

      null(prectangle);

   }

   return false;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool x_null_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   auto left = maximum(prect1->left, prect2->left);

   auto right = minimum(prect1->right, prect2->right);

   bool bIntersect = right >= left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(prectangle))
   {

      prectangle->left = left;

      prectangle->right = right;

   }

   return bIntersect;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool y_null_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   auto top = maximum(prect1->top, prect2->top);

   auto bottom = minimum(prect1->bottom, prect2->bottom);

   bool bIntersect = bottom >= top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(prectangle))
   {

      prectangle->top = top;

      prectangle->bottom = bottom;

   }

   return bIntersect;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool null_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if(x_null_intersect_rect(prectangle, prect1, prect2) && y_null_intersect_rect(prectangle, prect1, prect2))
   {

      return true;

   }

   if(::is_set(prectangle))
   {

      null(prectangle);

   }

   return false;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool x_left_null_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   prectangle->left    = maximum(prect1->left,prect2->left);

   prectangle->right   = minimum(prect1->right,prect2->right);

   return prectangle->right > prectangle->left || (prectangle->right == prectangle->left && prect1->left == prect2->left);

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool y_top_null_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   prectangle->top     = maximum(prect1->top, prect2->top);

   prectangle->bottom  = minimum(prect1->bottom, prect2->bottom);

   return prectangle->top < prectangle->bottom || (prectangle->top == prectangle->bottom && prect1->top == prect2->top);

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
bool top_left_null_intersect_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if(x_left_null_intersect_rect(prectangle,prect1,prect2) && y_top_null_intersect_rect(prectangle,prect1,prect2))
   {

      return true;

   }
   else
   {

      null(prectangle);

      return false;

   }

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
RECTANGLE_TYPE * union_rect(RECTANGLE_TYPE * prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{

   if (is_rect_empty(prect1))
   {

      if (is_rect_empty(prect2))
      {

         null_rect(prectangle);

      }
      else
      {

         copy(prectangle, prect2);

      }

   }
   else if (is_rect_empty(prect1))
   {

      copy(prectangle, prect1);

   }
   else
   {

      prectangle->left = (decltype(RECTANGLE_TYPE::left))minimum(prect1->left, prect2->left);
      prectangle->top = (decltype(RECTANGLE_TYPE::top))minimum(prect1->top, prect2->top);
      prectangle->right = (decltype(RECTANGLE_TYPE::right))maximum(prect1->right, prect2->right);
      prectangle->bottom = (decltype(RECTANGLE_TYPE::bottom))maximum(prect1->bottom, prect2->bottom);

   }

   return prectangle;

}

template < typename RECTANGLE_TYPE, typename RECT_TYPE1, typename RECT_TYPE2 >
RECTANGLE_TYPE* subtract_rect(RECTANGLE_TYPE* prectangle, const RECT_TYPE1* prect1, const RECT_TYPE2* prect2)
{


   prectangle->left = (decltype(RECT_TYPE1::left))minimum(prect1->left, prect2->left);
   prectangle->top = (decltype(RECT_TYPE1::top))minimum(prect1->top, prect2->top);
   prectangle->right = (decltype(RECT_TYPE1::right))maximum(prect1->right, prect2->right);
   prectangle->bottom = (decltype(RECT_TYPE1::bottom))maximum(prect1->bottom, prect2->bottom);

   return prectangle;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 * copy(RECT_TYPE1 * prect1, const RECT_TYPE2* prect2)
{

   prect1->left = (decltype(RECT_TYPE1::left)) prect2->left;
   prect1->top = (decltype(RECT_TYPE1::top)) prect2->top;
   prect1->right = (decltype(RECT_TYPE1::right)) prect2->right;
   prect1->bottom = (decltype(RECT_TYPE1::bottom)) prect2->bottom;

   return prect1;

}


template < primitive_rectangle RECT_TYPE1, XYDim_rectangle RECT_TYPE2 >
RECT_TYPE1 * copy(RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   prect1->left = (decltype(RECT_TYPE1::left))prect2->X;
   prect1->top = (decltype(RECT_TYPE1::top))prect2->Y;
   prect1->right = (decltype(RECT_TYPE1::right))(prect2->X + prect2->Width);
   prect1->bottom = (decltype(RECT_TYPE1::bottom))(prect2->Y + prect2->Height);

   return prect1;

}


template < primitive_rectangle RECT_TYPE1, xydim_rectangle RECT_TYPE2 >
RECT_TYPE1 * copy(RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   prect1->left = (decltype(RECT_TYPE1::left))prect2->x;
   prect1->top = (decltype(RECT_TYPE1::top))prect2->y;
   prect1->right = (decltype(RECT_TYPE1::right))(prect2->x + prect2->width);
   prect1->bottom = (decltype(RECT_TYPE1::bottom))(prect2->y + prect2->height);

   return prect1;

}


template < XY_point POINT1, primitive_point POINT2 >
POINT1 * copy(POINT1 * ppoint1, const POINT2 * ppoint2)
{

   ppoint1->X = (decltype(POINT1::X))ppoint2->x;
   ppoint1->Y = (decltype(POINT1::Y))ppoint2->y;

   return ppoint1;

}


template < primitive_point POINT1, XY_point POINT2 >
POINT1 * copy(POINT1 * ppoint1, const POINT2 * ppoint2)
{

   ppoint1->x = (decltype(POINT1::x))ppoint2->X;
   ppoint1->y = (decltype(POINT1::y))ppoint2->Y;


   return ppoint1;
}


template < XYDim_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 * copy(RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   prect1->X = (decltype(RECT_TYPE1::X))prect2->left;
   prect1->Y = (decltype(RECT_TYPE1::Y))prect2->top;
   prect1->Width = (decltype(RECT_TYPE1::Width))(prect2->right - prect2->left);
   prect1->Height = (decltype(RECT_TYPE1::Height))(prect2->bottom - prect2->top);

   return prect1;

}


template < xydim_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 * copy(RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   prect1->x = (decltype(RECT_TYPE1::X))prect2->left;
   prect1->y = (decltype(RECT_TYPE1::Y))prect2->top;
   prect1->width = (decltype(RECT_TYPE1::Width))(prect2->right - prect2->left);
   prect1->height = (decltype(RECT_TYPE1::Height))(prect2->bottom - prect2->top);

   return prect1;

}


template < XYDim_rectangle RECT_TYPE1, XYDim_rectangle RECT_TYPE2 >
RECT_TYPE1 * copy(RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   prect1->X = (decltype(RECT_TYPE1::X))prect2->X;
   prect1->Y = (decltype(RECT_TYPE1::Y))prect2->Y;
   prect1->Width = (decltype(RECT_TYPE1::Width))prect2->Width;
   prect1->Height = (decltype(RECT_TYPE1::Height))prect2->Height;

   return prect1;

}


template < primitive_point POINT1, primitive_point POINT2 >
POINT1 * copy(POINT1 * ppoint1, const POINT2 * ppoint2)
{

   ppoint1->x = (decltype(POINT1::x))ppoint2->x;
   ppoint1->y = (decltype(POINT1::y))ppoint2->y;

   return ppoint1;

}


template < primitive_point POINT, primitive_size SIZE >
POINT * copy(POINT * ppoint, const SIZE * psize)
{

   ppoint->x = (decltype(POINT::x))psize->cx;
   ppoint->y = (decltype(POINT::y))psize->cy;

   return ppoint;

}


template < typename SIZE_TYPE1, typename SIZE_TYPE2 >
SIZE_TYPE1 * copy_size(SIZE_TYPE1 * psize1, const SIZE_TYPE2 * psize2)
{

   psize1->cx = (decltype(SIZE_TYPE1::cx))psize2->cx;
   psize1->cy = (decltype(SIZE_TYPE1::cy))psize2->cy;

   return psize1;

}


template < typename X, typename Y >
auto get_dimension(enum_orientation eorientation, X x, Y y);


template < typename X, typename Y >
auto get_normal_dimension(enum_orientation eorientation, X x, Y y);



template < typename RECTANGLE_TYPE >
bool rect_equals(const RECTANGLE_TYPE* prect1, const RECTANGLE_TYPE* prect2)
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

template < typename RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
RECTANGLE_TYPE * set_rect(RECTANGLE_TYPE* prectangle, L l, T t, R r, B b)
{

   prectangle->left = (decltype(RECTANGLE_TYPE::left))l;
   prectangle->top = (decltype(RECTANGLE_TYPE::top))t;
   prectangle->right = (decltype(RECTANGLE_TYPE::right))r;
   prectangle->bottom = (decltype(RECTANGLE_TYPE::bottom))b;

   return prectangle;

}





template < typename RECTANGLE_TYPE, typename L, typename T, typename W, typename H >
RECTANGLE_TYPE * set_rect_dim(RECTANGLE_TYPE* prectangle, L l, T t, W w, H h)
{

   prectangle->left = (decltype(RECTANGLE_TYPE::left))l;
   prectangle->top = (decltype(RECTANGLE_TYPE::top))t;
   prectangle->right = (decltype(RECTANGLE_TYPE::right))(l+w);
   prectangle->bottom = (decltype(RECTANGLE_TYPE::bottom))(t+h);

   return prectangle;

}

template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECTANGLE_I32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECTANGLE_I64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECTANGLE_F32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RECTANGLE_F64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }


template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE * set_rect_size_bottom_right(RECTANGLE * prectangle, const SIZE & size)
{

   prectangle->right = (decltype(RECTANGLE::right))(prectangle->left + size.cx);
   prectangle->bottom = (decltype(RECTANGLE::bottom))(prectangle->top + size.cy);

   return prectangle;

}



template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE * set_rect_point_size(RECTANGLE * prectangle, const POINT & point, const SIZE & size)
{

   prectangle->left = (decltype(RECTANGLE::left))point.x;
   prectangle->top = (decltype(RECTANGLE::top))point.y;
   prectangle->right = (decltype(RECTANGLE::right))(point.x + size.cx);
   prectangle->bottom = (decltype(RECTANGLE::bottom))(point.y + size.cy);

   return prectangle;

}


template < typename RECTANGLE_TYPE >
RECTANGLE_TYPE * null_rect(RECTANGLE_TYPE* prectangle)
{

   return ::set_rect(prectangle, 0, 0, 0, 0);

}


template < typename RECTANGLE_TYPE >
constexpr auto rect_width(RECTANGLE_TYPE* prectangle) { return prectangle->right - prectangle->left; }


template < typename RECTANGLE_TYPE >
constexpr auto rect_height(RECTANGLE_TYPE* prectangle) { return prectangle->bottom - prectangle->top; }


template < typename W, typename H >
constexpr H rect_area(W w, H h) { return (w <= (W) 0 || h <= (H) 0) ? 0 : (H) (w * h); }


template < typename RECTANGLE_TYPE >
constexpr auto rect_area(RECTANGLE_TYPE* prectangle) { return rect_area(rect_width(prectangle), rect_height(prectangle)); }


template < typename RECTANGLE_TYPE >
constexpr auto is_rect_empty(RECTANGLE_TYPE * prectangle) { return ::is_null(prectangle) || prectangle->right <= prectangle->left || prectangle->bottom <= prectangle->top; }

template < typename RECTANGLE_TYPE >
bool is_rect_null(const RECTANGLE_TYPE* prectangle)
{

   return prectangle->left == (decltype(RECTANGLE_TYPE::left))0
      && prectangle->top == (decltype(RECTANGLE_TYPE::top))0
      && prectangle->right == (decltype(RECTANGLE_TYPE::right))0
      && prectangle->bottom == (decltype(RECTANGLE_TYPE::bottom))0;

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



template < primitive_rectangle RECTANGLE, typename X >
inline bool rectangle_contains_x(const RECTANGLE * prectangle, X x)
{

   return x >= prectangle->left && x <= prectangle->right;

}


template < primitive_rectangle RECTANGLE, typename Y >
inline bool rectangle_contains_y(const RECTANGLE * prectangle, Y y)
{

   return y >= prectangle->top && y <= prectangle->bottom;

}


template < primitive_rectangle RECTANGLE, typename X, typename Y >
inline bool rectangle_contains(const RECTANGLE * prectangle, X x, Y y)
{

   return rectangle_contains_x(prectangle, x) && rectangle_contains_y(prectangle, y);

}


template < typename RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
inline RECTANGLE_TYPE* rect_inflate(RECTANGLE_TYPE* prectangle, L l, T t, R r, B b)
{

   prectangle->left = (decltype(RECTANGLE_TYPE::left))(prectangle->left - l);
   prectangle->top = (decltype(RECTANGLE_TYPE::top))(prectangle->top - t);
   prectangle->right = (decltype(RECTANGLE_TYPE::right))(prectangle->right + r);
   prectangle->bottom = (decltype(RECTANGLE_TYPE::bottom))(prectangle->bottom + b);

   return prectangle;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE2 >
inline RECTANGLE_TYPE* rect_inflate(RECTANGLE_TYPE* prectangle, const RECT_TYPE2* prect2)
{

   return rect_inflate(prectangle, prect2->left, prect2->top, prect2->right, prect2->bottom);

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE2 >
inline RECTANGLE_TYPE* rect_multiply_inline(RECTANGLE_TYPE* prectangle, const RECT_TYPE2* prect2)
{

   prectangle->left *= prect2->left;
   prectangle->top *= prect2->top;
   prectangle->right *= prect2->right;
   prectangle->bottom *= prect2->bottom;

   return prectangle;

}

template < typename RECTANGLE_TYPE, typename L, typename T, typename R, typename B >
inline RECTANGLE_TYPE* rect_deflate(RECTANGLE_TYPE* prectangle, L l, T t, R r, B b)
{

   prectangle->left = (decltype(RECTANGLE_TYPE::left))(prectangle->left + l);
   prectangle->top = (decltype(RECTANGLE_TYPE::top))(prectangle->top + t);
   prectangle->right = (decltype(RECTANGLE_TYPE::right))(prectangle->right - r);
   prectangle->bottom = (decltype(RECTANGLE_TYPE::bottom))(prectangle->bottom - b);

   return prectangle;

}


template < typename RECTANGLE_TYPE, typename RECT_TYPE2 >
inline RECTANGLE_TYPE* rect_deflate(RECTANGLE_TYPE* prectangle, const RECT_TYPE2* prect2)
{

   return rect_deflate(prectangle, prect2->left, prect2->top, prect2->right, prect2->bottom);

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE* rect_inflate_point(RECTANGLE_TYPE* prectangle, X x, Y y)
{

   return rect_inflate(prectangle, x, y, x, y);

}

template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE* rect_deflate_point(RECTANGLE_TYPE* prectangle, X x, Y y)
{

   return rect_deflate(prectangle, x, y, x, y);

}


template < typename RECTANGLE_TYPE, typename UNIT >
inline RECTANGLE_TYPE* rect_inflate_unit(RECTANGLE_TYPE* prectangle, UNIT u)
{

   return rect_inflate_point(prectangle, u, u);

}


template < typename RECTANGLE_TYPE, typename UNIT >
inline RECTANGLE_TYPE* rect_deflate_unit(RECTANGLE_TYPE* prectangle, UNIT u)
{

   return rect_deflate_point(prectangle, u, u);

}


template < typename RECTANGLE_TYPE >
inline RECTANGLE_TYPE* swap_rect_left_right(RECTANGLE_TYPE* prectangle) { __swap(prectangle->left, prectangle->right); return prectangle; }



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
//::prectangle;
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










inline bool contains(const RECTANGLE_I32* prectangle, const POINT_I32& point) { return ::rectangle_contains(prectangle, point.x, point.y); }
inline RECTANGLE_I32* null(RECTANGLE_I32* prectDst) { return ::null_rect(prectDst); }
inline bool is_equal(const RECTANGLE_I32* prect1, const RECTANGLE_I32* prect2) { return ::rect_equals(prect1, prect2); }
inline RECTANGLE_I32* inflate(RECTANGLE_I32 * prectangle, ::i32 x, ::i32 y) { return ::rect_inflate_point(prectangle, x, y); }
inline RECTANGLE_I32* deflate(RECTANGLE_I32 * prectangle, ::i32 x, ::i32 y) { return ::rect_deflate_point(prectangle, x, y); }
inline RECTANGLE_I32* offset(RECTANGLE_I32 * prectangle, ::i32 x, ::i32 y) { return ::offset_rect(prectangle, x, y); }
inline bool intersect(RECTANGLE_I32 * prectangle, const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2) { return ::intersect_rect(prectangle, prect1, prect2); }
inline bool unite(RECTANGLE_I32 * prectangle, const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2) { return ::union_rect(prectangle, prect1, prect2); }
inline ::i32 width(const RECTANGLE_I32 * prectangle) { return ::rect_width(prectangle); }
inline ::i32 height(const RECTANGLE_I32 * prectangle) { return ::rect_height(prectangle); }
inline ::i32 area(const RECTANGLE_I32 * prectangle) { return ::rect_area(prectangle); }
inline bool is_empty(const RECTANGLE_I32 * prectangle) { return ::is_rect_empty(prectangle); }
inline void swap_left_right(RECTANGLE_I32 * prectangle) noexcept { ::__swap(prectangle->left, prectangle->right); }

inline ::i32 width(const RECTANGLE_I32 & rectangle) { return ::width(&rectangle); }
inline ::i32 height(const RECTANGLE_I32 & rectangle) { return ::height(&rectangle); }
inline ::i32 area(const RECTANGLE_I32 & rectangle) { return ::area(&rectangle); }
inline bool is_empty(const RECTANGLE_I32 & rectangle) { return ::is_empty(&rectangle); }
inline void swap_left_right(RECTANGLE_I32 & rectangle) noexcept { ::swap_left_right(&rectangle); }



inline bool is_empty(SIZE_I32* psize){ return psize->cx <= 0 || psize->cy <= 0; }
inline bool is_empty(SIZE_I64* psize) { return psize->cx <= 0 || psize->cy <= 0; }
inline bool is_empty(SIZE_F32* psize) { return psize->cx <= 0.f || psize->cy <= 0.f; }
inline bool is_empty(SIZE_F64* psize) { return psize->cx <= 0. || psize->cy <= 0.; }








inline bool contains(const RECTANGLE_I64* prectangle, const POINT_I32& point) { return ::rectangle_contains(prectangle, point.x, point.y); }
inline RECTANGLE_I64* null(RECTANGLE_I64* prectDst) { return ::null_rect(prectDst); }
inline bool is_equal(const RECTANGLE_I64* prect1, const RECTANGLE_I64* prect2) { return ::rect_equals(prect1, prect2); }
inline RECTANGLE_I64* inflate(RECTANGLE_I64 * prectangle, i64 x, i64 y) { return ::rect_inflate_point(prectangle, x, y); }
inline RECTANGLE_I64* deflate(RECTANGLE_I64 * prectangle, i64 x, i64 y) { return ::rect_deflate_point(prectangle, x, y); }
inline RECTANGLE_I64* offset(RECTANGLE_I64 * prectangle, i64 x, i64 y) { return ::offset_rect(prectangle, x, y); }
inline bool intersect(RECTANGLE_I64 * prectangle, const RECTANGLE_I64 * prect1, const RECTANGLE_I64 * prect2) { return ::intersect_rect(prectangle, prect1, prect2); }
inline bool unite(RECTANGLE_I64 * prectangle, const RECTANGLE_I64 * prect1, const RECTANGLE_I64 * prect2) { return ::union_rect(prectangle, prect1, prect2); }
inline i64 width(const RECTANGLE_I64 * prectangle) { return ::rect_width(prectangle); }
inline i64 height(const RECTANGLE_I64 * prectangle) { return ::rect_height(prectangle); }
inline i64 area(const RECTANGLE_I64 * prectangle) { return ::rect_area(prectangle); }
inline bool is_empty(const RECTANGLE_I64 * prectangle) { return ::is_rect_empty(prectangle); }
inline void swap_left_right(RECTANGLE_I64 * prectangle) noexcept { ::__swap(prectangle->left, prectangle->right); }

inline i64 width(const RECTANGLE_I64 & rectangle) { return ::width(&rectangle); }
inline i64 height(const RECTANGLE_I64 & rectangle) { return ::height(&rectangle); }
inline i64 area(const RECTANGLE_I64 & rectangle) { return ::area(&rectangle); }
inline bool is_empty(const RECTANGLE_I64 & rectangle) { return ::is_empty(&rectangle); }
inline void swap_left_right(RECTANGLE_I64 & rectangle) noexcept { ::swap_left_right(&rectangle); }





inline bool contains(const RECTANGLE_F32* prectangle, const POINT_F32& point) { return ::rectangle_contains(prectangle, point.x, point.y); }
inline RECTANGLE_F32* null(RECTANGLE_F32* prectFst) { return ::null_rect(prectFst); }
inline bool is_equal(const RECTANGLE_F32* prect1, const RECTANGLE_F32* prect2) { return ::rect_equals(prect1, prect2); }
inline RECTANGLE_F32* inflate(RECTANGLE_F32* prectangle, float x, float y) { return ::rect_inflate_point(prectangle, x, y); }
inline RECTANGLE_F32* deflate(RECTANGLE_F32* prectangle, float x, float y) { return ::rect_deflate_point(prectangle, x, y); }
inline RECTANGLE_F32* offset(RECTANGLE_F32* prectangle, float x, float y) { return ::offset_rect(prectangle, x, y); }
inline bool intersect(RECTANGLE_F32* prectangle, const RECTANGLE_F32* prect1, const RECTANGLE_F32* prect2) { return ::intersect_rect(prectangle, prect1, prect2); }
inline bool unite(RECTANGLE_F32* prectangle, const RECTANGLE_F32* prect1, const RECTANGLE_F32* prect2) { return ::union_rect(prectangle, prect1, prect2); }
inline float width(const RECTANGLE_F32* prectangle) { return ::rect_width(prectangle); }
template < primitive_rectangle RECTANGLE > 
inline auto height(const RECTANGLE * prectangle) { return ::rect_height(prectangle); }
template < primitive_rectangle RECTANGLE >
inline auto height(const RECTANGLE & rectangle) { return ::height(&rectangle); }
inline float area(const RECTANGLE_F32* prectangle) { return ::rect_area(prectangle); }
inline bool is_empty(const RECTANGLE_F32* prectangle) { return ::is_rect_empty(prectangle); }
inline void swap_left_right(RECTANGLE_F32* prectangle) noexcept { ::__swap(prectangle->left, prectangle->right); }

inline float width(const RECTANGLE_F32& rectangle) { return ::width(&rectangle); }
//inline float height(const RECTANGLE_F32& rectangle) { return ::height(&rectangle); }
inline float area(const RECTANGLE_F32& rectangle) { return ::area(&rectangle); }
inline bool is_empty(const RECTANGLE_F32& rectangle) { return ::is_empty(&rectangle); }
inline void swap_left_right(RECTANGLE_F32& rectangle) noexcept { ::swap_left_right(&rectangle); }




inline bool contains(const RECTANGLE_F64 * prectangle, const POINT_F64 & point) { return ::rectangle_contains(prectangle, point.x, point.y); }
inline RECTANGLE_F64* null(RECTANGLE_F64* prectDst) { return ::null_rect(prectDst); }
inline bool is_equal(const RECTANGLE_F64* prect1, const RECTANGLE_F64* prect2) { return ::rect_equals(prect1, prect2); }
inline RECTANGLE_F64* inflate(RECTANGLE_F64* prectangle, double x, double y) { return ::rect_inflate_point(prectangle, x, y); }
inline RECTANGLE_F64* deflate(RECTANGLE_F64* prectangle, double x, double y) { return ::rect_deflate_point(prectangle, x, y); }
inline RECTANGLE_F64* offset(RECTANGLE_F64* prectangle, double x, double y) { return ::offset_rect(prectangle, x, y); }

namespace geometry
{

   template < primitive_rectangle RECTANGLE >
   inline void deflate(RECTANGLE* prectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);

} // namespace geometry


inline bool intersect(RECTANGLE_F64* prectangle, const RECTANGLE_F64* prect1, const RECTANGLE_F64* prect2) { return ::intersect_rect(prectangle, prect1, prect2); }
inline bool unite(RECTANGLE_F64 * prectangle, const RECTANGLE_F64 * prect1, const RECTANGLE_F64 * prect2) { return ::union_rect(prectangle, prect1, prect2); }
inline double width(const RECTANGLE_F64 * prectangle) { return ::rect_width(prectangle); }
//inline double height(const RECTANGLE_F64 * prectangle) { return ::rect_height(prectangle); }
inline double area(const RECTANGLE_F64 * prectangle) { return ::rect_area(prectangle); }
inline bool is_empty(const RECTANGLE_F64* prectangle) { return ::is_rect_empty(prectangle); }
inline void swap_left_right(RECTANGLE_F64 * prectangle) noexcept { ::__swap(prectangle->left, prectangle->right); }

inline double width(const RECTANGLE_F64 & rectangle) { return ::width(&rectangle); }
//inline double height(const RECTANGLE_F64& rectangle) { return ::height(&rectangle); }
inline double area(const RECTANGLE_F64 & rectangle) { return ::area(&rectangle); }
inline bool is_empty(const RECTANGLE_F64 & rectangle) { return ::is_empty(&rectangle); }
inline void swap_left_right(RECTANGLE_F64 & rectangle) noexcept { ::swap_left_right(&rectangle); }

inline POINT_I32 & operator -= (POINT_I32 & point, const ::point_i32 & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINT_I32 & operator += (POINT_I32 & point, const ::point_i32 & pointOffset) { ::point_add(&point, pointOffset); return point; }
inline POINT_I64 & operator -= (POINT_I64 & point, const ::point_i64 & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINT_I64 & operator += (POINT_I64 & point, const ::point_i64 & pointOffset) { ::point_add(&point, pointOffset); return point; }
inline POINT_F32 & operator -= (POINT_F32 & point, const ::point_f32 & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINT_F32 & operator += (POINT_F32 & point, const ::point_f32 & pointOffset) { ::point_add(&point, pointOffset); return point; }
inline POINT_F64 & operator -= (POINT_F64 & point, const ::point_f64 & pointOffset) { ::point_sub(&point, pointOffset); return point; }
inline POINT_F64 & operator += (POINT_F64 & point, const ::point_f64 & pointOffset) { ::point_add(&point, pointOffset); return point; }


inline RECTANGLE_I32& operator -= (RECTANGLE_I32& rectangle, const ::point_i32& point) { ::rect_sub(&rectangle, point); return rectangle; }
inline RECTANGLE_I32& operator += (RECTANGLE_I32& rectangle, const ::point_i32& point) { ::rect_add(&rectangle, point); return rectangle; }
inline RECTANGLE_I64& operator -= (RECTANGLE_I64& rectangle, const ::point_i64& point) { ::rect_sub(&rectangle, point); return rectangle; }
inline RECTANGLE_I64& operator += (RECTANGLE_I64& rectangle, const ::point_i64& point) { ::rect_add(&rectangle, point); return rectangle; }
inline RECTANGLE_F32& operator -= (RECTANGLE_F32& rectangle, const ::point_f32& point) { ::rect_sub(&rectangle, point); return rectangle; }
inline RECTANGLE_F32& operator += (RECTANGLE_F32& rectangle, const ::point_f32& point) { ::rect_add(&rectangle, point); return rectangle; }
inline RECTANGLE_F64& operator -= (RECTANGLE_F64& rectangle, const ::point_f64& point) { ::rect_sub(&rectangle, point); return rectangle; }
inline RECTANGLE_F64& operator += (RECTANGLE_F64& rectangle, const ::point_f64& point) { ::rect_add(&rectangle, point); return rectangle; }

//inline bool deflate(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & prectParam);


#include "point.h"
#include "size.h"
#include "rectangle.h"



#include "types.h"


template < typename RECTANGLE_BASE_TYPE, typename POINT_BASE_TYPE >
void get_bounding_rectangle(RECTANGLE_BASE_TYPE * lprect, const POINT_BASE_TYPE * lppoint, ::count count)
{

   if (count <= 0)
   {

      lprect->left = 0;
      lprect->top = 0;
      lprect->right = 0;
      lprect->bottom = 0;

   }
   else
   {
      lprect->left = lppoint[0].x;
      lprect->top = lppoint[0].y;
      lprect->right = lppoint[0].x;
      lprect->bottom = lppoint[0].y;

      for (i32 i = 1; i < count; i++)
      {
         if (lppoint[i].x < lprect->left)
            lprect->left = lppoint[i].x;
         else if (lppoint[i].x > lprect->right)
            lprect->right = lppoint[i].x;
         if (lppoint[i].y < lprect->top)
            lprect->top = lppoint[i].y;
         else if (lppoint[i].y > lprect->bottom)
            lprect->bottom = lppoint[i].y;
      }

   }

}


inline bool get_bounding_rectangle(RECTANGLE_I32 * prectangleBounding, const RECTANGLE_I32 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const RECTANGLE_I32 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const RECTANGLE_F64 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const RECTANGLE_F64 * prectangle)
{

   copy(prectangleBounding, prectangle);

   return true;

}


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > ::get_bounding_rectangle(const POINT_BASE_TYPE * ppoint, ::count count)
{

   ::get_bounding_rectangle(this, ppoint, count);

}




CLASS_DECL_ACME double d_distance(const point_i32 & point1, const point_i32 & point2);


template < typename X, typename Y, typename W, typename H >
inline rectangle_i32 rectangle_i32_dimension(X x, Y y, W w, H h)
{

   return rectangle_i32((i32) (x), (i32) (y), (i32) (x + w), (i32) (y + h));

}


template < typename X, typename Y, typename W, typename H >
inline rectangle_i64 rectangle_i64_dimension(X x, Y y, W w, H h)
{

   return rectangle_i64((i64) x, (i64)y, (i64) (x + w), (i64) (y + h));

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
//inline void copy(rectangle_i32 * prectDst, const ::winrt::Windows::Foundation::Rect * prectSrc)
//{
//   prectDst->left = (::i32) prectSrc->X;
//   prectDst->top = (::i32)prectSrc->Y;
//   prectDst->right = (::i32) (prectSrc->X + prectSrc->Width);
//   prectDst->bottom = (::i32) (prectSrc->Y + prectSrc->Height);
//}
//
//inline void copy(::winrt::Windows::Foundation::Rect* prectDst, rectangle_i32* prectSrc)
//{
//   prectDst->X = (float) prectSrc->left;
//   prectDst->Y = (float) prectSrc->top;
//   prectDst->Width = (float) prectSrc->width();
//   prectDst->Height = (float) prectSrc->height();
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
inline void expand_rect(RECT1* prectangle, const RECT2& r)
{

   if (::is_rect_null(prectangle))
   {

      __copy(prectangle, r);

   }
   else
   {

      prectangle->left = minimum((decltype(prectangle->left))prectangle->left, (decltype(prectangle->left))r.left);
      prectangle->right = maximum((decltype(prectangle->right))prectangle->right, (decltype(prectangle->right))r.right);
      prectangle->top = minimum((decltype(prectangle->top))prectangle->top, (decltype(prectangle->top))r.top);
      prectangle->bottom = maximum((decltype(prectangle->bottom))prectangle->bottom, (decltype(prectangle->bottom))r.bottom);

   }

}


template < typename RECT1, typename RECT2 >
inline void collapse_rect(RECT1 * prectangle, const RECT2 & r)
{

   if (::is_rect_null(prectangle))
   {

      __copy(prectangle, r);

   }
   else
   {

      prectangle->left = maximum((decltype(prectangle->left))prectangle->left, (decltype(prectangle->left))r.left);
      prectangle->right = minimum((decltype(prectangle->right))prectangle->right, (decltype(prectangle->right))r.right);
      prectangle->top = maximum((decltype(prectangle->top))prectangle->top, (decltype(prectangle->top))r.top);
      prectangle->bottom = minimum((decltype(prectangle->bottom))prectangle->bottom, (decltype(prectangle->bottom))r.bottom);

      if (::width(prectangle) == 0 || height(prectangle) == 0)
      {

         ::null_rect(prectangle);

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

inline point_i32 & top_left(const RECTANGLE_I32 * prectangle) { return *(point_i32 *)prectangle; }
inline point_i32 & bottom_right(const RECTANGLE_I32 * prectangle) { return *(point_i32 *)&prectangle->right; }
inline point_i32 & top_left(const RECTANGLE_I32 & rectangle) { return top_left(&rectangle); }
inline point_i32 & bottom_right(const RECTANGLE_I32 & rectangle) { return bottom_right(&rectangle); }


inline point_i64 & top_left(const RECTANGLE_I64 * prectangle) { return *(point_i64 *)prectangle; }
inline point_i64 & bottom_right(const RECTANGLE_I64 * prectangle) { return *(point_i64 *)&prectangle->right; }
inline point_i64 & top_left(const RECTANGLE_I64 & rectangle) { return top_left(&rectangle); }
inline point_i64 & bottom_right(const RECTANGLE_I64 & rectangle) { return bottom_right(&rectangle); }


inline point_f64 & top_left(const RECTANGLE_F64 * prectangle) { return *(point_f64 *)prectangle; }
inline point_f64 & bottom_right(const RECTANGLE_F64 * prectangle) { return *(point_f64 *)&prectangle->right; }
inline point_f64 & top_left(const RECTANGLE_F64 & rectangle) { return top_left(&rectangle); }
inline point_f64 & bottom_right(const RECTANGLE_F64 & rectangle) { return bottom_right(&rectangle); }


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
   inline void deflate(RECTANGLE * prectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate)
   {

      auto rectangle = *prectangle;

      prectangle->left = range_rate(rectangle.left, rectangle.right, dLeftRate);

      prectangle->right = range_rate(rectangle.right, rectangle.left, dRightRate);

      prectangle->top = range_rate(rectangle.top, rectangle.bottom, dTopRate);

      prectangle->bottom = range_rate(rectangle.bottom, rectangle.top, dBottomRate);

   }


} // namespace geometry


template < primitive_point POINT >
inline ::string __string(const POINT & point)
{

   str = __string(point.x) + ", " + __string(point.y);

}


template < primitive_size SIZE >
inline ::string __string(const SIZE & size)
{

   str = __string(size.cx) + ", " + __string(size.cy);

}




#include "arc.h"

#include "line.h"

#include "lines.h"

#include "ellipse.h"


template < primitive_point POINT >
inline ::string __string(const POINT & point);


template < primitive_size SIZE >
inline ::string __string(const SIZE & size);







