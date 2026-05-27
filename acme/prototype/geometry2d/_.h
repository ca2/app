#pragma once


namespace geometry2d
{


   class region;
   class item;


   class matrix;


} // namespace geometry2d


DECLARE_ENUMERATION(e_align, enum_align);


#include "_struct.h"


template < prototype_number NUMBER >
class point_type;

template < prototype_number NUMBER >
class size_type;

template < prototype_number NUMBER >
class line_type;

template < prototype_number NUMBER >
class rectangle_type;

template < prototype_number NUMBER >
class ellipse_type;

template < prototype_number NUMBER >
class arc_type;

template < prototype_number NUMBER >
class point_array_base;

template < prototype_number NUMBER >
class polygon_base;

template < prototype_number NUMBER >
class poly_polygon_base;

template < prototype_number NUMBER >
class point_array_base;

template < prototype_number NUMBER >
class size_array_base;

template < prototype_number NUMBER >
class rectangle_array_base;

template < prototype_number NUMBER >
class lines_base;


using i32_point = point_type < ::i32 >;
using i64_point = point_type < ::i64 >;
using f32_point = point_type < ::f32 >;
using f64_point = point_type < ::f64 >;


using i32_size = size_type < ::i32 >;
using i64_size = size_type < ::i64 >;
using f32_size = size_type < ::f32 >;
using f64_size = size_type < ::f64 >;


using i32_rectangle = rectangle_type < ::i32 >;
using i64_rectangle = rectangle_type < ::i64 >;
using f32_rectangle = rectangle_type < ::f32 >;
using f64_rectangle = rectangle_type < ::f64 >;


using i32_ellipse = ellipse_type < ::i32 >;
using i64_ellipse = ellipse_type < ::i64 >;
using f32_ellipse = ellipse_type < ::f32 >;
using f64_ellipse = ellipse_type < ::f64 >;


using i32_line = line_type < ::i32 >;
using i64_line = line_type < ::i64 >;
using f32_line = line_type < ::f32 >;
using f64_line = line_type < ::f64 >;


using i32_arc = arc_type < ::i32 >;
using i64_arc = arc_type < ::i64 >;
using f32_arc = arc_type < ::f32 >;
using f64_arc = arc_type < ::f64 >;


using i32_point_array_base = point_array_base < ::i32 >;
using i64_point_array_base = point_array_base < ::i64 >;
using f32_point_array_base = point_array_base < ::f32 >;
using f64_point_array_base = point_array_base < ::f64 >;


using i32_point_array = ::array_particle < i32_point_array_base >;
using i64_point_array = ::array_particle < i64_point_array_base >;
using f32_point_array = ::array_particle < f32_point_array_base >;
using f64_point_array = ::array_particle < f64_point_array_base >;


using i32_polygon_base = polygon_base < ::i32 >;
using i64_polygon_base = polygon_base < ::i64 >;
using f32_polygon_base = polygon_base < ::f32 >;
using f64_polygon_base = polygon_base < ::f64 >;


using i32_polygon = ::array_particle < i32_polygon_base >;
using i64_polygon = ::array_particle < i64_polygon_base >;
using f32_polygon = ::array_particle < f32_polygon_base >;
using f64_polygon = ::array_particle < f64_polygon_base >;


using i32_poly_polygon_base = poly_polygon_base < ::i32 >;
using i64_poly_polygon_base = poly_polygon_base < ::i64 >;
using f32_poly_polygon_base = poly_polygon_base < ::f32 >;
using f64_poly_polygon_base = poly_polygon_base < ::f64 >;


using i32_poly_polygon = ::array_particle < i32_poly_polygon_base >;
using i64_poly_polygon = ::array_particle < i64_poly_polygon_base >;
using f32_poly_polygon = ::array_particle < f32_poly_polygon_base >;
using f64_poly_polygon = ::array_particle < f64_poly_polygon_base >;


using i32_point_array_base = point_array_base < ::i32 >;
using i64_point_array_base = point_array_base < ::i64 >;
using f32_point_array_base = point_array_base < ::f32 >;
using f64_point_array_base = point_array_base < ::f64 >;


using i32_point_array = ::array_particle < i32_point_array_base >;
using i64_point_array = ::array_particle < i64_point_array_base >;
using f32_point_array = ::array_particle < f32_point_array_base >;
using f64_point_array = ::array_particle < f64_point_array_base >;


using i32_size_array_base = size_array_base < ::i32 >;
using i64_size_array_base = size_array_base < ::i64 >;
using f32_size_array_base = size_array_base < ::f32 >;
using f64_size_array_base = size_array_base < ::f64 >;


using i32_size_array = ::array_particle < i32_size_array_base >;
using i64_size_array = ::array_particle < i64_size_array_base >;
using f32_size_array = ::array_particle < f32_size_array_base >;
using f64_size_array = ::array_particle < f64_size_array_base >;


using i32_rectangle_array_base = rectangle_array_base < ::i32 >;
using i64_rectangle_array_base = rectangle_array_base < ::i64 >;
using f32_rectangle_array_base = rectangle_array_base < ::f32 >;
using f64_rectangle_array_base = rectangle_array_base < ::f64 >;


using i32_rectangle_array = ::array_particle < i32_rectangle_array_base >;
using i64_rectangle_array = ::array_particle < i64_rectangle_array_base >;
using f32_rectangle_array = ::array_particle < f32_rectangle_array_base >;
using f64_rectangle_array = ::array_particle < f64_rectangle_array_base >;

using i32_lines_base = lines_base < ::i32 >;
using i64_lines_base = lines_base < ::i64 >;
using f32_lines_base = lines_base < ::f32 >;
using f64_lines_base = lines_base < ::f64 >;

using i32_lines = ::array_particle < i32_lines_base >;
using i64_lines = ::array_particle < i64_lines_base >;
using f32_lines = ::array_particle < f32_lines_base >;
using f64_lines = ::array_particle < f64_lines_base >;

template < struct_rectangle RECTANGLE1, prototype_rectangle RECTANGLE2 >
inline void copy(RECTANGLE1 * prectangle1, const RECTANGLE2 * prectangle2)
{

   prectangle1->left = (decltype(prectangle1->left))prectangle2->left;
   prectangle1->top = (decltype(prectangle1->top))prectangle2->top;
   prectangle1->right = (decltype(prectangle1->right))prectangle2->right;
   prectangle1->bottom = (decltype(prectangle1->bottom))prectangle2->bottom;

}



