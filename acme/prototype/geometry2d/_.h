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


using int_point = point_type < int >;
using long_long_point = point_type < long long >;
using float_point = point_type < float >;
using double_point = point_type < double >;


using int_size = size_type < int >;
using long_long_size = size_type < long long >;
using float_size = size_type < float >;
using double_size = size_type < double >;


using int_rectangle = rectangle_type < int >;
using long_long_rectangle = rectangle_type < long long >;
using float_rectangle = rectangle_type < float >;
using double_rectangle = rectangle_type < double >;


using int_ellipse = ellipse_type < int >;
using long_long_ellipse = ellipse_type < long long >;
using float_ellipse = ellipse_type < float >;
using double_ellipse = ellipse_type < double >;


using int_line = line_type < int >;
using long_long_line = line_type < long long >;
using float_line = line_type < float >;
using double_line = line_type < double >;


using int_arc = arc_type < int >;
using long_long_arc = arc_type < long long >;
using float_arc = arc_type < float >;
using double_arc = arc_type < double >;


using int_point_array_base = point_array_base < int >;
using long_long_point_array_base = point_array_base < long long >;
using float_point_array_base = point_array_base < float >;
using double_point_array_base = point_array_base < double >;


using int_point_array = ::array_particle < int_point_array_base >;
using long_long_point_array = ::array_particle < long_long_point_array_base >;
using float_point_array= ::array_particle < float_point_array_base >;
using double_point_array = ::array_particle < double_point_array_base >;


using int_polygon_base = polygon_base < int >;
using long_long_polygon_base = polygon_base < long long >;
using float_polygon_base = polygon_base < float >;
using double_polygon_base = polygon_base < double >;


using int_polygon = ::array_particle < int_polygon_base >;
using long_long_polygon = ::array_particle < long_long_polygon_base >;
using float_polygon = ::array_particle < float_polygon_base >;
using double_polygon = ::array_particle < double_polygon_base >;


using int_poly_polygon_base = poly_polygon_base < int >;
using long_long_poly_polygon_base = poly_polygon_base < long long >;
using float_poly_polygon_base = poly_polygon_base < float >;
using double_poly_polygon_base = poly_polygon_base < double >;


using int_poly_polygon = ::array_particle < int_poly_polygon_base >;
using long_long_poly_polygon = ::array_particle < long_long_poly_polygon_base >;
using float_poly_polygon = ::array_particle < float_poly_polygon_base >;
using double_poly_polygon = ::array_particle < double_poly_polygon_base >;


using int_point_array_base = point_array_base < int >;
using long_long_point_array_base = point_array_base < long long >;
using float_point_array_base = point_array_base < float >;
using double_point_array_base = point_array_base < double >;


using int_point_array = ::array_particle < int_point_array_base >;
using long_long_point_array = ::array_particle < long_long_point_array_base >;
using float_point_array = ::array_particle < float_point_array_base >;
using double_point_array = ::array_particle < double_point_array_base >;


using int_size_array_base = size_array_base < int >;
using long_long_size_array_base = size_array_base < long long >;
using float_size_array_base = size_array_base < float >;
using double_size_array_base = size_array_base < double >;


using int_size_array = ::array_particle < int_size_array_base >;
using long_long_size_array = ::array_particle < long_long_size_array_base >;
using float_size_array = ::array_particle < float_size_array_base >;
using double_size_array = ::array_particle < double_size_array_base >;


using int_rectangle_array_base = rectangle_array_base < int >;
using long_long_rectangle_array_base = rectangle_array_base < long long >;
using float_rectangle_array_base = rectangle_array_base < float >;
using double_rectangle_array_base = rectangle_array_base < double >;


using int_rectangle_array = ::array_particle < int_rectangle_array_base >;
using long_long_rectangle_array = ::array_particle < long_long_rectangle_array_base >;
using float_rectangle_array = ::array_particle < float_rectangle_array_base >;
using double_rectangle_array = ::array_particle < double_rectangle_array_base >;

using int_lines_base = lines_base < int >;
using long_long_lines_base = lines_base < long long >;
using float_lines_base = lines_base < float >;
using double_lines_base = lines_base < double >;

using int_lines = ::array_particle < int_lines_base >;
using long_long_lines = ::array_particle < long_long_lines_base >;
using float_lines = ::array_particle < float_lines_base >;
using double_lines = ::array_particle < double_lines_base >;

template < struct_rectangle RECTANGLE1, prototype_rectangle RECTANGLE2 >
inline void copy(RECTANGLE1 * prectangle1, const RECTANGLE2 * prectangle2)
{

   prectangle1->left = (decltype(prectangle1->left))prectangle2->left;
   prectangle1->top = (decltype(prectangle1->top))prectangle2->top;
   prectangle1->right = (decltype(prectangle1->right))prectangle2->right;
   prectangle1->bottom = (decltype(prectangle1->bottom))prectangle2->bottom;

}



