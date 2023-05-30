// Created by camilo on 2022-11-08 16:17 <3ThomasBorregaardSørensen!!
#pragma once


//
//
//using line = ::line_f64;
//
//
//
//
//
//
//using line = ::line_f64;
//using rectangle = ::rectangle_f64;
//using ellipse = ::ellipse_f64;



#include "_function.h"


#include "_angle.h"
#include "_line.h"
#include "_point.h"
#include "_arc.h"
#include "_rectangle.h"
#include "_size.h"
#include "_shift.h"
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



//template < raw_primitive_point RAW_PRIMITIVE_POINT, primitive_point PRIMITIVE_POINT >
//inline void copy(RAW_PRIMITIVE_POINT& rawprimitivepoint, const PRIMITIVE_POINT & primitivepoint)
//{
//
//   rawprimitivepoint.x = (decltype(rawprimitivepoint.x))primitivepoint.x();
//   rawprimitivepoint.y = (decltype(rawprimitivepoint.y))primitivepoint.y();
//
//}





