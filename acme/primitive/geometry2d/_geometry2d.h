// Created by camilo on 2022-11-08 16:17 <3ThomasBorregaardSørensen!!
#pragma once

template < primitive_number NUMBER >
class point_type;

template < primitive_number NUMBER >
class size_type;

template < typename POINT_TYPE >
class line_base;

template < primitive_number NUMBER >
class rectangle_type;

template < typename RECTANGLE_TYPE >
class ellipse_base;


class arc;



using point_i32 = point_type < ::i32 >;
using point_i64 = point_type < ::i64 >;
using point_f32 = point_type < ::f32 >;
using point_f64 = point_type < ::f64 >;





using size_i32 = size_type < ::i32 >;
using size_i64 = size_type < ::i64 >;
using size_f32 = size_type < ::f32 >;
using size_f64 = size_type < ::f64 >;





using rectangle_i32 = rectangle_type < ::i32 >;
using rectangle_i64 = rectangle_type < ::i64 >;
using rectangle_f32 = rectangle_type < ::f32 >;
using rectangle_f64 = rectangle_type < ::f64 >;


using ellipse_i32 = ellipse_base < rectangle_i32 >;
using ellipse_i64 = ellipse_base < rectangle_i64 >;
using ellipse_f32 = ellipse_base < rectangle_f32 >;
using ellipse_f64 = ellipse_base < rectangle_f64 >;



using line_i32 = line_base < ::point_i32 >;
using line_i64 = line_base < ::point_i64 >;
using line_f32 = line_base < ::point_f32 >;
using line_f64 = line_base < ::point_f64 >;




using line = ::line_f64;






using line = ::line_f64;
using rectangle = ::rectangle_f64;
using ellipse = ::ellipse_f64;



#include "_function.h"


#include "_angle.h"
#include "_line.h"
#include "_point.h"
#include "_arc.h"
#include "_rectangle.h"
#include "_size.h"
#include "_shift.h"
#include "_polygon.h"
#include "_ellipse.h"


#include "_function_impl.h"





inline auto left(const ::rectangle_i32& rectangle) { return rectangle.left; }
inline auto top(const ::rectangle_i32& rectangle) { return rectangle.top; }
inline auto left(const ::rectangle_i64& rectangle) { return rectangle.left; }
inline auto top(const ::rectangle_i64& rectangle) { return rectangle.top; }
inline auto left(const ::rectangle_f32& rectangle) { return rectangle.left; }
inline auto top(const ::rectangle_f32& rectangle) { return rectangle.top; }
inline auto left(const ::rectangle_f64& rectangle) { return rectangle.left; }
inline auto top(const ::rectangle_f64& rectangle) { return rectangle.top; }



template < raw_primitive_point RAW_PRIMITIVE_POINT, primitive_point PRIMITIVE_POINT >
inline void copy(RAW_PRIMITIVE_POINT& rawprimitivepoint, const PRIMITIVE_POINT & primitivepoint)
{

   rawprimitivepoint.x = (decltype(rawprimitivepoint.x))primitivepoint.x();
   rawprimitivepoint.y = (decltype(rawprimitivepoint.y))primitivepoint.y();

}





