// Created by camilo on 2022-10-19 22:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "_geometry2d.h"


template < typename POINT_TYPE >
class polygon_base;

template < typename POINT_TYPE >
class point_array_base;

template < typename _SIZE_TYPE >
class size_array_base;

template < typename RECTANGLE_TYPE >
class rectangle_array_base;


template < typename POINT_TYPE >
class point_array_base;

template < typename POINT_TYPE >
class lines_base;

using lines_i32 = lines_base < point_i32 >;
using lines_i64 = lines_base < point_i64 >;
using lines_f32 = lines_base < point_f32 >;
using lines_f64 = lines_base < point_f64 >;




using lines = lines_f64;



using polygon_i32 = polygon_base < point_i32 >;
using polygon_i64 = polygon_base < point_i64 >;
using polygon_f32 = polygon_base < point_f32 >;
using polygon_f64 = polygon_base < point_f64 >;


using polygon = polygon_f64;



using point_i32_array = point_array_base < point_i32 >;
using point_i64_array = point_array_base < point_i64 >;
using point_f32_array = point_array_base < point_f32 >;
using point_f64_array = point_array_base < point_f64 >;


using size_i32_array = size_array_base < size_i32 >;
using size_i64_array = size_array_base < size_i64 >;
using size_f32_array = size_array_base < size_f32 >;
using size_f64_array = size_array_base < size_f64 >;



using rectangle_i32_array = rectangle_array_base < rectangle_i32 >;
using rectangle_i64_array = rectangle_array_base < rectangle_i64 >;
using rectangle_f32_array = rectangle_array_base < rectangle_f32 >;
using rectangle_f64_array = rectangle_array_base < rectangle_f64 >;


using lines = ::lines_f64;
using polygon = ::polygon_f64;



#include "_polygon.h"
#include "_lines.h"




#include "acme/primitive/geometry2d/point_array.h"
#include "acme/primitive/geometry2d/size_array.h"
#include "acme/primitive/geometry2d/rectangle_array.h"


using point_i32_array = point_array_base < point_i32 >;
using point_i64_array = point_array_base < point_i64 >;
using point_f32_array = point_array_base < point_f32 >;
using point_f64_array = point_array_base < point_f64 >;




#include "acme/primitive/geometry2d/_polygon.h"



