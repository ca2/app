#pragma once


#include "_rect_impl.h"
#include "_size_impl.h"


inline constexpr auto __horz(const ::point & point) { return point.x; }
inline constexpr auto __vert(const ::point & point) { return point.y; }
inline constexpr auto __horz(const ::size & size) { return size.cx; }
inline constexpr auto __vert(const ::size & size) { return size.cy; }

inline point& top_left(const RECT32* prect) { return *(point*)prect; }
inline point& bottom_right(const RECT32* prect) { return *(point*)& prect->right; }
inline point& top_left(const RECT32& rect) { return top_left(&rect); }
inline point& bottom_right(const RECT32& rect) { return bottom_right(&rect); }


inline point64& top_left(const RECT64* prect) { return *(point64*)prect; }
inline point64& bottom_right(const RECT64* prect) { return *(point64*)& prect->right; }
inline point64& top_left(const RECT64& rect) { return top_left(&rect); }
inline point64& bottom_right(const RECT64& rect) { return bottom_right(&rect); }


inline pointd& top_left(const RECTD* prect) { return *(pointd*)prect; }
inline pointd& bottom_right(const RECTD* prect) { return *(pointd*)& prect->right; }
inline pointd& top_left(const RECTD& rect) { return top_left(&rect); }
inline pointd& bottom_right(const RECTD& rect) { return bottom_right(&rect); }


template < typename X, typename Y >
inline auto get_dimension(e_orientation eorientation, X x, Y y)
{

   if (eorientation == orientation_horizontal)
   {

      return x;

   }
   else if (eorientation == orientation_vertical)
   {

      return y;

   }
   else
   {

      __throw(invalid_argument_exception("invalid orientation"));

   }

}


template < typename X, typename Y >
inline auto get_normal_dimension(e_orientation eorientation, X x, Y y)
{

   if (eorientation == orientation_vertical)
   {

      return x;

   }
   else if (eorientation == orientation_horizontal)
   {

      return y;

   }
   else
   {

      __throw(invalid_argument_exception("invalid orientation"));

   }

}


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECT_BASE_TYPE >::size_type(const POINT_TYPE & point) noexcept : size_type((size_type&)point) {}


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECT_BASE_TYPE >::size_type(const RECT_TYPE & rect) noexcept : size_type(rect.width(), rect.height()) {}


template < typename UNIT_TYPE >
inline UNIT_TYPE __conv(const string & str)
{

   return (UNIT_TYPE) str;

}


template <  >
inline ::i32 __conv<::i32>(const string & str)
{

   return (::i32) ::atoi(str);

}


template <  >
inline i64 __conv<i64>(const string & str)
{

   return (::i32) ::atoi(str);

}


template <  >
inline double __conv<double>(const string & str)
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


template < >
inline ___shape* __new_shape(const enum_shape& eshape)
{

   switch (eshape)
   {
   case e_shape_none:
      return nullptr;
   case e_shape_begin_clip:
      return new begin_clip_shape;
   case e_shape_intersect_clip:
      return new intersect_clip_shape;
   case e_shape_begin_figure:
      return new begin_figure_shape;
   case e_shape_close_figure:
      return new close_figure_shape;
   default:
      __throw(not_implemented("new geometry processor or not a geometry processor?"));
      return nullptr;
   }

}


template < typename GEOMETRY >
inline ___shape* __new_shape(const GEOMETRY& geometry)
{

   __throw(not_implemented("unimplemented geometry"));

   return nullptr;

}


template < typename SHAPE, enum_shape ESHAPE >
bool _shape < SHAPE, ESHAPE >::expand_bounding_rect(RECTD* prect) const
      {

         ::RECTD r;

         if (!this->get_bounding_rect(&r))
         {

            return false;

         }

         ::union_rect(prect, prect, &r);

         return true;

      }


template < typename SHAPE, enum_shape ESHAPE >
bool _shape < SHAPE, ESHAPE >::expand_bounding_rect(RECT32* prect) const
   {

      ::RECT32 r;

      if (!this->get_bounding_rect(&r))
      {

         return false;

      }

      ::union_rect(prect, prect, &r);

      return true;

   }




