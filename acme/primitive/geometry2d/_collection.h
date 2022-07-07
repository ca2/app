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


// template < >
// CLASS_DECL_ACME __pointer(___shape) __create_shape(const ::lines & lines);


// template < >
// CLASS_DECL_ACME __pointer(___shape) __create_shape(const ::polygon & polygon);


#include "_collection_bounding_rect.h"


#include "_collection_contains.h"


#include "shape_array.h"



