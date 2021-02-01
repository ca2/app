#pragma once


#include "_rect_impl.h"
#include "_size_impl.h"


template < primitive_point POINT >
inline constexpr auto __horz(const POINT & point) { return point.x; }
template < primitive_point POINT >
inline constexpr auto __vert(const POINT & point) { return point.y; }
template < primitive_size SIZE >
inline constexpr auto __horz(const SIZE & size) { return size.cx; }
template < primitive_size SIZE >
inline constexpr auto __vert(const SIZE & size) { return size.cy; }

inline point_i32& top_left(const RECTANGLE_I32* prectangle) { return *(point_i32*)prectangle; }
inline point_i32& bottom_right(const RECTANGLE_I32* prectangle) { return *(point_i32*)& prectangle->right; }
inline point_i32& top_left(const RECTANGLE_I32& rectangle) { return top_left(&rectangle); }
inline point_i32& bottom_right(const RECTANGLE_I32& rectangle) { return bottom_right(&rectangle); }


inline point_i64& top_left(const RECTANGLE_I64* prectangle) { return *(point_i64*)prectangle; }
inline point_i64& bottom_right(const RECTANGLE_I64* prectangle) { return *(point_i64*)& prectangle->right; }
inline point_i64& top_left(const RECTANGLE_I64& rectangle) { return top_left(&rectangle); }
inline point_i64& bottom_right(const RECTANGLE_I64& rectangle) { return bottom_right(&rectangle); }


inline point_f64& top_left(const RECTANGLE_F64* prectangle) { return *(point_f64*)prectangle; }
inline point_f64& bottom_right(const RECTANGLE_F64* prectangle) { return *(point_f64*)& prectangle->right; }
inline point_f64& top_left(const RECTANGLE_F64& rectangle) { return top_left(&rectangle); }
inline point_f64& bottom_right(const RECTANGLE_F64& rectangle) { return bottom_right(&rectangle); }


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


//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
//inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECT_BASE_TYPE >::size_type(const POINT_TYPE & point) noexcept : size_type((size_type&)point_i32) {}
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
//inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECT_BASE_TYPE >::size_type(const RECT_TYPE & rectangle) noexcept : size_type(rectangle.width(), rectangle.height()) {}


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
bool _shape < SHAPE, ESHAPE >::expand_bounding_rect(RECTANGLE_F64* prectangle) const
      {

         ::RECTANGLE_F64 r;

         if (!this->get_bounding_rect(&r))
         {

            return false;

         }

         ::union_rect(prectangle, prectangle, &r);

         return true;

      }


template < typename SHAPE, enum_shape ESHAPE >
bool _shape < SHAPE, ESHAPE >::expand_bounding_rect(RECTANGLE_I32* prectangle) const
   {

      ::RECTANGLE_I32 r;

      if (!this->get_bounding_rect(&r))
      {

         return false;

      }

      ::union_rect(prectangle, prectangle, &r);

      return true;

   }





template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
inline void rect_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE >::normalize() noexcept
{
   
   __sort(this->left, this->right); 
   
   __sort(this->top, this->bottom); 

}
