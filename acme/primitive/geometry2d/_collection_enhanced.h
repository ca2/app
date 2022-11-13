#pragma once


#include "acme/primitive/primitive/_u32hash.h"


//template<> inline u32hash u32_hash<point_i32>(point_i32 key)
//{
//
//   return key.x | key.y;
//
//}
//
//
//template<> inline u32hash u32_hash < ::size_i32 >(::size_i32 key)
//{
//
//   return key.cx | key.cy;
//
//}
//
//
//template<> inline u32hash u32_hash<rectangle_i32>(rectangle_i32 key)
//{
//
//   return key.left | key.top | key.bottom | key.right;
//
//}
//
//
//template < >
//inline u32hash u32_hash(const ::size_i32& size)
//{
//
//   return size.cy << 16 | size.cx;
//
//}
//
//
//template < >
//inline u32hash u32_hash(const ::point_i32& point)
//{
//
//   return point.y << 16 | point.x;
//   
//}
//
//
//template < >
//inline u32hash u32_hash(const ::rectangle_i32& rectangle)
//{
//
//   return rectangle.top << 24 | rectangle.left << 16 | rectangle.bottom << 8 | rectangle.right;
//
//}


// template < >
// CLASS_DECL_ACME ::pointer<___shape>__create_shape(const ::lines & lines);


// template < >
// CLASS_DECL_ACME ::pointer<___shape>__create_shape(const ::polygon & polygon);


#include "_collection_bounding_rect.h"


#include "_collection_contains.h"


#include "shape_array.h"



