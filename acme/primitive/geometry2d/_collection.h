#pragma once


template<> inline uptr uptr_hash<point>(point key)
{

   return key.x | key.y;

}


template<> inline uptr uptr_hash<size>(size key)
{

   return key.cx | key.cy;

}


template<> inline uptr uptr_hash<rect>(rect key)
{

   return key.left | key.top | key.bottom | key.right;

}


template < >
inline uptr uptr_hash(const ::size& size)
{

   return size.cy << 16 | size.cx;

}


template < >
inline uptr uptr_hash(const ::point& point)
{

   return point.y << 16 | point.x;
   
}


template < >
inline uptr uptr_hash(const ::rect& rect)
{

   return rect.top << 24 | rect.left << 16 | rect.bottom << 8 | rect.right;

}


//using lines_shape = _shape < ::lines, e_shape_lines >;
using linesd_shape = _shape < ::linesd, e_shape_linesd >;
//using polygon_shape = _shape < ::polygon, e_shape_polygon >;
using polygond_shape = _shape < ::polygond, e_shape_polygond >;


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
//inline ___shape* __new_shape(const ::polygon& polygon)
//{
//
//   return new polygon_shape(polygon);
//
//}


template < >
inline ___shape* __new_shape(const ::polygond& polygon)
{

   return new polygond_shape(polygon);

}


#include "_collection_bounding_rect.h"


#include "_collection_contains.h"


#include "shape_array.h"



