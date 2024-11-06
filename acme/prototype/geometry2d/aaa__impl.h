#pragma once

//
//#include "_rect_impl.h"
//#include "_size_impl.h"
//

//template < primitive_point POINT >
//inline constexpr auto __horz(const POINT & point) { return point.x(); }
//template < primitive_point POINT >
//inline constexpr auto __vert(const POINT & point) { return point.y(); }
//template < primitive_size SIZE >
//inline constexpr auto __horz(const SIZE & size) { return size.cx(); }
//template < primitive_size SIZE >
//inline constexpr auto __vert(const SIZE & size) { return size.cy(); }
//
//inline point_i32& top_left(const ::rectangle_i32* prectangle) { return *(point_i32*)prectangle; }
//inline point_i32& bottom_right(const ::rectangle_i32* prectangle) { return *(point_i32*)& prectangle->right(); }
//inline point_i32& top_left(const ::rectangle_i32& rectangle) { return top_left(&rectangle); }
//inline point_i32& bottom_right(const ::rectangle_i32& rectangle) { return bottom_right(&rectangle); }
//
//
//inline point_i64& top_left(const ::rectangle_i64* prectangle) { return *(point_i64*)prectangle; }
//inline point_i64& bottom_right(const ::rectangle_i64* prectangle) { return *(point_i64*)& prectangle->right(); }
//inline point_i64& top_left(const ::rectangle_i64& rectangle) { return top_left(&rectangle); }
//inline point_i64& bottom_right(const ::rectangle_i64& rectangle) { return bottom_right(&rectangle); }
//
//
//inline point_f64& top_left(const ::rectangle_f64* prectangle) { return *(point_f64*)prectangle; }
//inline point_f64& bottom_right(const ::rectangle_f64* prectangle) { return *(point_f64*)& prectangle->right(); }
//inline point_f64& top_left(const ::rectangle_f64& rectangle) { return top_left(&rectangle); }
//inline point_f64& bottom_right(const ::rectangle_f64& rectangle) { return bottom_right(&rectangle); }


//template < typename X, typename Y >
//inline auto get_dimension(enum_orientation eorientation, X x, Y y)
//{
//
//   if (eorientation == e_orientation_horizontal)
//   {
//
//      return x;
//
//   }
//   else if (eorientation == e_orientation_vertical)
//   {
//
//      return y;
//
//   }
//   else
//   {
//
//      throw ::exception(error_bad_argument, "invalid orientation");
//
//   }
//
//}
//
//
//template < typename X, typename Y >
//inline auto get_normal_dimension(enum_orientation eorientation, X x, Y y)
//{
//
//   if (eorientation == e_orientation_vertical)
//   {
//
//      return x;
//
//   }
//   else if (eorientation == e_orientation_horizontal)
//   {
//
//      return y;
//
//   }
//   else
//   {
//
//      throw ::exception(error_bad_argument, "invalid orientation");
//
//   }
//
//}
//
//
////template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
////inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const POINT_TYPE & point) noexcept : size_type((size_type&)point_i32) {}
////
////
////template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
////inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const RECTANGLE_TYPE & rectangle) noexcept : size_type(rectangle.width(), rectangle.height()) {}
//
//
//template < typename UNIT_TYPE >
//inline UNIT_TYPE __conv(const ::string & str)
//{
//
//   return (UNIT_TYPE) str;
//
//}
//
//
//template <  >
//inline int __conv<int>(const ::string & str)
//{
//
//   return (int) ::atoi(str);
//
//}
//
//
//template <  >
//inline i64 __conv<i64>(const ::string & str)
//{
//
//   return (int) ::atoi(str);
//
//}
//
//
//template <  >
//inline double __conv<double>(const ::string & str)
//{
//
//   return (int) ::atoi(str);
//
//}
//
//
//template < typename TYPE >
//inline string __xmlpri()
//{
//
//   return "%";
//
//}
//
//
//template < >
//inline string __xmlpri<int>()
//{
//
//   return "%" PRId32;
//
//}
//
//
//template < >
//inline string __xmlpri<i64>()
//{
//
//   return "%" PRId64;
//
//}
//
//
//template < >
//inline string __xmlpri<double>()
//{
//
//   return "%f";
//
//}
//
//
//template < typename HOLDEE >
//inline ::pointer<___shape<HOLDEE >> __create_shape(const enum_shape& eshape)
//{
//
//   switch (eshape)
//   {
//   case e_shape_none:
//      return nullptr;
//   case e_shape_begin_clip:
//      return __allocate begin_clip_shape<HOLDEE> ();
//   case e_shape_intersect_clip:
//      return __allocate intersect_clip_shape<HOLDEE> ();
//   case e_shape_begin_figure:
//      return __allocate begin_figure_shape<HOLDEE> ();
//   case e_shape_close_figure:
//      return __allocate close_figure_shape<HOLDEE> ();
//   case e_shape_end_figure:
//      return __allocate end_figure_shape<HOLDEE> ();
//   default:
//      throw ::exception(error_not_implemented, "aaa_primitive_new geometry processor or not a geometry processor?");
//      return nullptr;
//   }
//
//}
//
//
//
//
//namespace geometry
//{
//
//   //////////////////////////////////////////////////////////////////////
//   //
//   // Function Name: deflate
//   //
//   // Purpose:
//   // Change rectangle dimension using its dimensions and the specified
//   // rates. For example, the dLeftRate machine the left position of the
//   // rectangle. If 0.0, it remains the same as the original left.
//   // If 1.0, it turns as the original right. If 0.4, it will be 40%
//   // of the width from left to right.
//   //
//   // Output:
//   // -1 if the creation of the ::user::impact failed.
//   // 0 if the creation of the ::user::impact succeeded.
//   //
//   // Author:
//   // Vanessa Testoni
//   //
//   //
//   //////////////////////////////////////////////////////////////////////
//   template < primitive_rectangle RECTANGLE >
//   inline void deflate(RECTANGLE* prectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate)
//   {
//
//      auto rectangle = *prectangle;
//
//      prectangle->left() = range_rate(rectangle.left(), rectangle.right(), dLeftRate);
//
//      prectangle->right() = range_rate(rectangle.right(), rectangle.left(), dRightRate);
//
//      prectangle->top() = range_rate(rectangle.top(), rectangle.bottom(), dTopRate);
//
//      prectangle->bottom() = range_rate(rectangle.bottom(), rectangle.top(), dBottomRate);
//
//   }
//
//
//} // namespace geometry
//
//
//template < primitive_point POINT >
//inline ::string as_string(const POINT & point)
//{
//
//   str = as_string(point.x()) + ", " + as_string(point.y());
//
//}
//
//
//template < primitive_size SIZE >
//inline ::string as_string(const SIZE & size)
//{
//
//   str = as_string(size.cx()) + ", " + as_string(size.cy());
//
//}
