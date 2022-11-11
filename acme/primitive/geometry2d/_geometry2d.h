// Created by camilo on 2022-11-08 16:17 <3ThomasBorregaardSorensen!!
#pragma once

template < typename BASE_TYPE, typename SIZE_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class point_type;

template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class size_type;

template < typename POINT_TYPE >
class line_base;

template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
class rectangle_type;

template < typename RECTANGLE_TYPE >
class ellipse_base;


class arc;




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
#include "_arc.h"
#include "_line.h"
#include "_point.h"
#include "_rectangle.h"
#include "_size.h"
#include "_shift.h"
#include "_polygon.h"
#include "_ellipse.h"


#include "_function_impl.h"



