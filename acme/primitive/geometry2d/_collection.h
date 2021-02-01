#pragma once


template<> inline uptr uptr_hash<point_i32>(point_i32 key)
{

   return key.x | key.y;

}


template<> inline uptr uptr_hash < ::size_i32 >(::size_i32 key)
{

   return key.cx | key.cy;

}


template<> inline uptr uptr_hash<rectangle_i32>(rectangle_i32 key)
{

   return key.left | key.top | key.bottom | key.right;

}


template < >
inline uptr uptr_hash(const ::size_i32& size)
{

   return size.cy << 16 | size.cx;

}


template < >
inline uptr uptr_hash(const ::point_i32& point)
{

   return point.y << 16 | point.x;
   
}


template < >
inline uptr uptr_hash(const ::rectangle_i32& rectangle)
{

   return rectangle.top << 24 | rectangle.left << 16 | rectangle.bottom << 8 | rectangle.right;

}


//using lines_shape = _shape < ::lines, e_shape_lines >;
using linesd_shape = _shape < ::linesd, e_shape_linesd >;
//using polygon_shape = _shape < ::polygon_i32, e_shape_polygon >;
using polygond_shape = _shape < ::polygon_f64, e_shape_polygond >;


//template < >
//inline ___shape* __new_shape(const ::lines& lines)
//{
//
//   return new lines_shape(lines);
//
//}


template < >
inline ___shape* __new_shape(const ::linesd& lines)
{

   return new linesd_shape(lines);

}


//template < >
//inline ___shape* __new_shape(const ::polygon_i32& polygon_i32)
//{
//
//   return new polygon_shape(polygon_i32);
//
//}


template < >
inline ___shape* __new_shape(const ::polygon_f64& polygon_i32)
{

   return new polygond_shape(polygon_i32);

}


#include "_collection_bounding_rect.h"


#include "_collection_contains.h"


#include "shape_array.h"



