// Created by camilo on 2022-11-08 16:01 <3ThomasBorregaardSorensen!!
#pragma once


//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto width(RECTANGLE_TYPE & rectangle);

//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto height(RECTANGLE_TYPE & rectangle);

//template < typename W, typename H >
//constexpr H area(W w, H h);

//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto area(RECTANGLE_TYPE & rectangle);

//template < primitive_rectangle RECTANGLE_TYPE >
//bool is_null(const RECTANGLE_TYPE & rectangle);

//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto is_empty(RECTANGLE_TYPE & rectangle);

//template < primitive_rectangle RECTANGLE_TYPE >
//constexpr auto is_set(RECTANGLE_TYPE & rectangle);

//template < primitive_size SIZE_TYPE >
//bool is_null(const SIZE_TYPE & size);

//template < primitive_point POINT_TYPE >
//bool is_null(const POINT_TYPE & point);

//template < primitive_rectangle RECTANGLE_TYPE, typename X >
//inline RECTANGLE_TYPE & x_offset(RECTANGLE_TYPE & rectangle, X x);

//template < primitive_rectangle RECTANGLE_TYPE, typename Y >
//inline RECTANGLE_TYPE & y_offset(RECTANGLE_TYPE & rectangle, Y y);

//template < primitive_rectangle RECTANGLE_TYPE, typename X >
//inline RECTANGLE_TYPE & x_subtract(RECTANGLE_TYPE & rectangle, X x);

//template < primitive_rectangle RECTANGLE_TYPE, typename Y >
//inline RECTANGLE_TYPE & y_subtract(RECTANGLE_TYPE & rectangle, Y y);

//template < typename RECTANGLE_TYPE, typename X, typename Y >
//inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, X x, Y y);

//template < typename RECTANGLE_TYPE, typename X, typename Y >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, X x, Y y);

//template < typename RECTANGLE_TYPE, primitive_point POINT_TYPE >
//inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point);

//template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
//inline RECTANGLE1 & subtract(RECTANGLE1 & rectangle, const RECTANGLE2 & rectangle2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT & point) { return subtract(rectangle, point); }


//template < primitive_point POINT, typename X, typename Y >
//inline POINT & offset(POINT & point, X x, Y y);

//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & offset(POINT & point, const POINT2 & point2);

//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & add(POINT & point, const POINT2 & point2);

//template < primitive_point POINT_TYPE, typename X, typename Y >
//inline POINT_TYPE & subtract(POINT_TYPE & point, X x, Y y);

//template < primitive_point POINT_TYPE, primitive_point POINT_TYPE2 >
//inline POINT_TYPE & subtract(POINT_TYPE & point, const POINT_TYPE2 & point2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
//inline RECTANGLE_TYPE & add(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool x_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool y_top_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//bool top_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//RECTANGLE_TYPE & unite(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);


//template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
//RECT_TYPE1 & unite(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);


//template < typename X, typename Y >
//auto get_dimension(enum_orientation eorientation, X x, Y y);


//template < typename X, typename Y >
//auto get_normal_dimension(enum_orientation eorientation, X x, Y y);
//
//
//template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
//bool is_equal(const RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2, float epsilon = 0.0001);
//
//template < primitive_point POINT1, primitive_point POINT2 >
//bool is_equal(const POINT1 & point1, const POINT2 & point2, float epsilon = 0.0001);

//template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
//bool is_equal(const SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2, float epsilon = 0.0001);
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
//RECTANGLE_TYPE & assign(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b);
//
//
//template < primitive_rectangle RECTANGLE, primitive_number L, primitive_number T, primitive_number W, primitive_number H >
//RECTANGLE & set_dimension(RECTANGLE & rectangle, L l, T t, W w, H h);

//template < primitive_rectangle RECTANGLE,  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE &r, L l, T t, W w, H h) { return set_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(::rectangle_i64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(::rectangle_f32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(::rectangle_f64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }


//template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
//RECTANGLE & set_bottom_right(RECTANGLE & rectangle, const SIZE & size);
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
//RECTANGLE & assign(RECTANGLE & rectangle, const POINT & point, const SIZE & size);


//template < primitive_rectangle RECTANGLE_TYPE >
//RECTANGLE_TYPE & null(RECTANGLE_TYPE & rectangle);
//
//
//template < primitive_rectangle RECTANGLE, primitive_number X >
//inline bool contains_x(const RECTANGLE & rectangle, X x);
//
//
//template < primitive_rectangle RECTANGLE, primitive_number Y >
//inline bool contains_y(const RECTANGLE & rectangle, Y y);
//
//template < typename RECTANGLE, primitive_number X, primitive_number Y >
//inline bool contains(const RECTANGLE & rectangle, X x, Y y);
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b);
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2);
//

//template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
//inline RECTANGLE_TYPE & multiply_inline(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2);
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b);
//
//template < typename RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2);
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, X x, Y y);
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, X x, Y y);
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
//inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, UNIT u);
//
//
//template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
//inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, UNIT u);
//
//
//template < primitive_rectangle RECTANGLE_TYPE >
//inline RECTANGLE_TYPE & swap_left_right(RECTANGLE_TYPE & rectangle);
//
//
//template < primitive_point POINT1, primitive_point POINT2 >
//inline bool polygon_contains_winding(const POINT1 * ppPolygon, int iCount, const POINT2 & point);
//
//template < primitive_point POINT1, primitive_point POINT2 >
//inline bool polygon_contains_alternate(const POINT1 * ppPolygon, int iCount, const POINT2 & point, bool bUseHoles, float epsilon = 0.00001f);
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator -= (POINT & point, const POINT2 & pointOffset);
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator += (POINT & point, const POINT2 & pointOffset);
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator -= (RECTANGLE & rectangle, const POINT & point);
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator += (RECTANGLE & rectangle, const POINT & point);
//
//
//CLASS_DECL_ACME double d_distance(const point_i32& point1, const point_i32& point2);


template < primitive_point POINT1, primitive_point POINT2 >
::f64 f64_distance(const POINT1 & point1, const POINT2 & point2)
{

   return sqrt((point2.x() - point1.x()) * (point2.x() - point1.x()) + (point2.y() - point1.y()) * (point2.y() - point1.y()));

}


template < typename X, typename Y >
inline auto get_dimension(enum_orientation eorientation, X x, Y y)
{

   if (eorientation == e_orientation_horizontal)
   {

      return x;

   }
   else if (eorientation == e_orientation_vertical)
   {

      return y;

   }
   else
   {

      throw ::exception(error_bad_argument, "invalid orientation");

   }

}


template < typename X, typename Y, typename Z >
inline auto get_dimension(enum_orientation eorientation, X x, Y y, Z z)
{

   if (eorientation == e_orientation_horizontal)
   {

      return x;

   }
   else if (eorientation == e_orientation_vertical)
   {

      return y;

   }
   else if (eorientation == e_orientation_z)
   {

      return z;

   }
   else
   {

      throw ::exception(error_bad_argument, "invalid orientation (2)");

   }

}


template < typename X, typename Y, typename Z, typename W >
inline auto get_dimension(enum_orientation eorientation, X x, Y y, Z z, W w)
{

   if (eorientation == e_orientation_horizontal)
   {

      return x;

   }
   else if (eorientation == e_orientation_vertical)
   {

      return y;

   }
   else if (eorientation == e_orientation_z)
   {

      return z;

   }
   else if (eorientation == e_orientation_w)
   {

      return w;

   }
   else
   {

      throw ::exception(error_bad_argument, "invalid orientation (3)");

   }

}


template < typename X, typename Y >
inline auto get_normal_dimension2(enum_orientation eorientation, X x, Y y)
{

   if (eorientation == e_orientation_horizontal)
   {

      return y;

   }
   else if (eorientation == e_orientation_vertical)
   {

      return x;

   }
   else
   {

      throw ::exception(error_bad_argument, "invalid orientation (4)");

   }

}




//template < primitive_rectangle RECTANGLE, primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
//RECTANGLE & unite(RECTANGLE1 & rectangle, const RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
//{
//
//   if (is_empty(rectangle1))
//   {
//
//      if (is_empty(rectangle2))
//      {
//
//         null(rectangle);
//
//      }
//      else
//      {
//
//         copy(rectangle, rectangle2);
//
//      }
//
//   }
//   else if (is_empty(rectangle2))
//   {
//
//      copy(rectangle, rectangle1);
//
//   }
//   else
//   {
//
//      copy(rectangle, rectangle1);
//      
//      rectangle2.expand_bounding_box(rectangle.top_left(), rectangle.bottom_right());
//
//   }
//
//   return rectangle;
//
//}


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
RECTANGLE1 & unite(RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
{

   if (is_empty(rectangle1))
   {

      if (is_empty(rectangle2))
      {

         null(rectangle1);

      }
      else
      {

         copy(rectangle1, rectangle2);

      }

   }
   else if (is_set(rectangle2))
   {
      
      rectangle2.expand_bounding_box(rectangle1.top_left(), rectangle1.bottom_right());

   }

   return rectangle1;

}




template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto width(RECTANGLE_TYPE & rectangle) { return rectangle.right() - rectangle.left(); }


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto height(RECTANGLE_TYPE & rectangle) { return rectangle.bottom() - rectangle.top(); }


template < typename W, typename H >
constexpr H area(W w, H h) { return (w <= (W)0 || h <= (H)0) ? 0 : (H)(w * h); }


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto area(RECTANGLE_TYPE & rectangle) { return area(width(rectangle), height(rectangle)); }


template < primitive_rectangle RECTANGLE_TYPE >
bool is_null(const RECTANGLE_TYPE & rectangle)
{

   return rectangle.left() == (typename RECTANGLE_TYPE::UNIT_TYPE)0
      && rectangle.top() == (typename RECTANGLE_TYPE::UNIT_TYPE)0
      && rectangle.right() == (typename RECTANGLE_TYPE::UNIT_TYPE)0
      && rectangle.bottom() == (typename RECTANGLE_TYPE::UNIT_TYPE)0;

}


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto is_empty(RECTANGLE_TYPE & rectangle) { return ::is_null(rectangle) || rectangle.right() <= rectangle.left() || rectangle.bottom() <= rectangle.top(); }


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto is_set(RECTANGLE_TYPE & rectangle) { return !::is_empty(rectangle); }


template < primitive_size SIZE_TYPE >
bool is_null(const SIZE_TYPE & size)
{

   return size.cx() == (typename SIZE_TYPE::UNIT_TYPE)0
      && size.cy() == (typename SIZE_TYPE::UNIT_TYPE)0;

}


template < primitive_point POINT_TYPE >
bool is_null(const POINT_TYPE & point)
{

   return point.x() == (typename POINT_TYPE::UNIT_TYPE)0 && point.y() == (typename POINT_TYPE::UNIT_TYPE)0;

}





template < primitive_rectangle RECTANGLE_TYPE, typename X >
inline RECTANGLE_TYPE & x_offset(RECTANGLE_TYPE & rectangle, X x)
{

   rectangle.left() = (decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.left() + x);

   rectangle.right() = (decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.right() + x);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, typename Y >
inline RECTANGLE_TYPE & y_offset(RECTANGLE_TYPE & rectangle, Y y)
{

   rectangle.top() = (decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.top() + y);

   rectangle.bottom() = (decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.bottom() + y);

   return rectangle;

}



template < primitive_rectangle RECTANGLE_TYPE, primitive_number X >
inline RECTANGLE_TYPE & x_subtract(RECTANGLE_TYPE & rectangle, X x)
{

   rectangle.left() = (::decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.left() - x);

   rectangle.right() = (::decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.right() - x);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number Y >
inline RECTANGLE_TYPE & y_subtract(RECTANGLE_TYPE & rectangle, Y y)
{

   rectangle.top() = (::decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.top() - y);

   rectangle.bottom() = (::decay<typename RECTANGLE_TYPE::UNIT_TYPE>)(rectangle.bottom() - y);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   x_offset(rectangle, x);

   y_offset(rectangle, y);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   x_subtract(rectangle, x);

   y_subtract(rectangle, y);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return offset(rectangle, point.x(), point.y());

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return subtract(rectangle, point.x(), point.y());

}


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
inline RECTANGLE1 & subtract(RECTANGLE1 & rectangle, const RECTANGLE2 & rectangle2)
{

   rectangle.left() = (decay<typename RECTANGLE1::UNIT_TYPE>)(rectangle.left() - rectangle2.left());
   rectangle.top() = (decay<typename RECTANGLE1::UNIT_TYPE>)(rectangle.top() - rectangle2.top());
   rectangle.right() = (decay<typename RECTANGLE1::UNIT_TYPE>)(rectangle.right() - rectangle2.right());
   rectangle.bottom() = (decay<typename RECTANGLE1::UNIT_TYPE>)(rectangle.bottom() - rectangle2.bottom());

   return rectangle;

}


template < primitive_rectangle RECTANGLE, primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
inline RECTANGLE & subtract(RECTANGLE & rectangle, const RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
{

   rectangle.left() = (decay<typename RECTANGLE::UNIT_TYPE>)(rectangle1.left() - rectangle2.left());
   rectangle.top() = (decay<typename RECTANGLE::UNIT_TYPE>)(rectangle1.top() - rectangle2.top());
   rectangle.right() = (decay<typename RECTANGLE::UNIT_TYPE>)(rectangle1.right() - rectangle2.right());
   rectangle.bottom() = (decay<typename RECTANGLE::UNIT_TYPE>)(rectangle1.bottom() - rectangle2.bottom());

   return rectangle;

}


//template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT & point) { return subtract(rectangle, point); }


template < primitive_sequence2 SEQUENCE, primitive_number X, primitive_number Y >
inline SEQUENCE & offset(SEQUENCE & sequence, X x, Y y)
{

   sequence.a() = (const decay<typename SEQUENCE::UNIT_TYPE>&)(sequence.a() + x);
   sequence.b() = (const decay<typename SEQUENCE::UNIT_TYPE>&)(sequence.b() + y);

   return sequence;

}


template < primitive_sequence2 SEQUENCEA, primitive_sequence SEQUENCEB >
inline SEQUENCEA & offset(SEQUENCEA & sequencea, const SEQUENCEB & sequenceb)
{

   return offset(sequencea, sequenceb.a(), sequenceb.b());

}


template < primitive_sequence2 SEQUENCEA, primitive_sequence SEQUENCEB >
inline SEQUENCEA & add(SEQUENCEA & sequencea, const SEQUENCEB & sequenceb)
{

   return offset(sequencea, sequenceb);

}


template < primitive_sequence2 SEQUENCE, typename X, typename Y >
inline SEQUENCE & subtract(SEQUENCE & sequence, X x, Y y)
{

   sequence.a() = (const decay<typename SEQUENCE::UNIT_TYPE>&)(sequence.a() - x);
   sequence.b() = (const decay<typename SEQUENCE::UNIT_TYPE>&)(sequence.b() - y);

   return sequence;

}


template < primitive_sequence2 SEQUENCEA, primitive_sequence2 SEQUENCEB >
inline SEQUENCEA & subtract(SEQUENCEA & sequence, const SEQUENCEB & sequenceb)
{

   return subtract(sequence, sequenceb.x(), sequenceb.y());

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & add(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return offset(rectangle, point);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left(), rect2.left());

   auto right = minimum(rect1.right(), rect2.right());

   bool bIntersect = right > left;

   if (!bIntersect)
   {

      rectangle.left() = 0;

      rectangle.right() = 0;

   }
   else
   {
   //if (::is_set(rectangle))
   //{

      rectangle.left() = left;

      rectangle.right() = right;

   }

   return bIntersect;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{


   return rect1.left() < rect2.right() && rect1.right() > rect2.left();

   //auto left = maximum(rect1.left(), rect2.left());

   //auto right = minimum(rect1.right(), rect2.right());

   //return right > left;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top(), rect2.top());

   auto bottom = minimum(rect1.bottom(), rect2.bottom());

   bool bIntersect = bottom > top;

   if (!bIntersect)
   {

      rectangle.top() =0;

      rectangle.bottom() = 0;

   }
   else
   {
   //if (::is_set(rectangle))
   //{

      rectangle.top() = top;

      rectangle.bottom() = bottom;

   }

   return bIntersect;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   //auto top = maximum(rect1.top(), rect2.top());

   //auto bottom = minimum(rect1.bottom(), rect2.bottom());

   //return bottom > top;

   return rect1.top() < rect2.bottom() && rect1.bottom() > rect2.top();

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_intersect(rectangle, rect1, rect2) && y_intersect(rectangle, rect1, rect2))
   {

      return true;

   }

   //if (::is_set(rectangle))
   //{

      null(rectangle);

   //}

   return false;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   return x_intersects(rect1, rect2) && y_intersects(rect1, rect2);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left(), rect2.left());

   auto right = minimum(rect1.right(), rect2.right());

   bool bIntersect = right >= left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   //if (::is_set(rectangle))
   //{

      rectangle.left() = left;

      rectangle.right() = right;

   //}

   return bIntersect;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top(), rect2.top());

   auto bottom = minimum(rect1.bottom(), rect2.bottom());

   bool bIntersect = bottom >= top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   //if (::is_set(rectangle))
   //{

      rectangle.top() = top;

      rectangle.bottom() = bottom;

   //}

   return bIntersect;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_null_intersect(rectangle, rect1, rect2) && y_null_intersect(rectangle, rect1, rect2))
   {

      return true;

   }

   //if (::is_set(rectangle))
   //{

      null(rectangle);

   //}

   return false;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rectangle.left() = maximum(rect1.left(), rect2.left());

   rectangle.right() = minimum(rect1.right(), rect2.right());

   return rectangle.right() > rectangle.left() || (rectangle.right() == rectangle.left() && rect1.left() == rect2.left());

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_top_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rectangle.top() = maximum(rect1.top(), rect2.top());

   rectangle.bottom() = minimum(rect1.bottom(), rect2.bottom());

   return rectangle.top() < rectangle.bottom() || (rectangle.top() == rectangle.bottom() && rect1.top() == rect2.top());

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool top_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_left_null_intersect(rectangle, rect1, rect2) && y_top_null_intersect(rectangle, rect1, rect2))
   {

      return true;

   }
   else
   {

      null(rectangle);

      return false;

   }

}


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
bool is_equal(const RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2, largest_number < ::decay<typename RECTANGLE1::UNIT_TYPE>, ::decay<typename RECTANGLE2::UNIT_TYPE > > epsilon = default_epsilon < ::largest_number < ::decay < typename RECTANGLE1::UNIT_TYPE >, ::decay<typename RECTANGLE2::UNIT_TYPE > >>())
{

   return is_equal(rectangle1.left(), rectangle2.left(), epsilon)
      && is_equal(rectangle1.top(), rectangle2.top(), epsilon)
      && is_equal(rectangle1.right(), rectangle2.right(), epsilon)
      && is_equal(rectangle1.bottom(), rectangle2.bottom(), epsilon);

}


template < primitive_point POINT1, primitive_point POINT2 >
bool is_equal(const POINT1 & point1, const POINT2 & point2, largest_number < ::decay<typename POINT1::UNIT_TYPE>, ::decay<typename POINT2::UNIT_TYPE> > epsilon = default_epsilon<largest_number < ::decay<typename POINT1::UNIT_TYPE>, ::decay<typename POINT2::UNIT_TYPE> >>())
{

   return is_equal(point1.x(), point2.x(), epsilon) && is_equal(point1.y(), point2.y(), epsilon);

}


template < primitive_size SIZE1, primitive_size SIZE2 >
bool is_equal(const SIZE1 & size1, const SIZE2 & size2, largest_number < ::decay<typename SIZE1::UNIT_TYPE>, ::decay<typename SIZE2::UNIT_TYPE> > epsilon = default_epsilon<largest_number < ::decay<typename SIZE1::UNIT_TYPE>, ::decay<typename SIZE2::UNIT_TYPE > >>())
{

   return is_equal(size1.cx(), size2.cx(), epsilon) && is_equal(size1.cy(), size2.cy(), epsilon);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
RECTANGLE_TYPE & assign(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left() = (typename RECTANGLE_TYPE::UNIT_TYPE)l;
   rectangle.top() = (typename RECTANGLE_TYPE::UNIT_TYPE)t;
   rectangle.right() = (typename RECTANGLE_TYPE::UNIT_TYPE)r;
   rectangle.bottom() = (typename RECTANGLE_TYPE::UNIT_TYPE)b;

   return rectangle;

}


template < primitive_rectangle RECTANGLE, primitive_number L, primitive_number T, primitive_number W, primitive_number H >
RECTANGLE & set_dimension(RECTANGLE & rectangle, L l, T t, W w, H h)
{

   rectangle.left() = (typename RECTANGLE::UNIT_TYPE)l;
   rectangle.top() = (typename RECTANGLE::UNIT_TYPE)t;
   rectangle.right() = (typename RECTANGLE::UNIT_TYPE)(l + w);
   rectangle.bottom() = (typename RECTANGLE::UNIT_TYPE)(t + h);

   return rectangle;

}

//template < primitive_rectangle RECTANGLE,  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE &r, L l, T t, W w, H h) { return set_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(::rectangle_i64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(::rectangle_f32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(::rectangle_f64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }


template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & set_bottom_right(RECTANGLE & rectangle, const SIZE & size)
{

   rectangle.right() = (typename RECTANGLE::UNIT_TYPE)(rectangle.left() + size.cx());
   rectangle.bottom() = (typename RECTANGLE::UNIT_TYPE)(rectangle.top() + size.cy());

   return rectangle;

}


template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & assign(RECTANGLE & rectangle, const POINT & point, const SIZE & size)
{

   rectangle.left() = (typename RECTANGLE::UNIT_TYPE)point.x();
   rectangle.top() = (typename RECTANGLE::UNIT_TYPE)point.y();
   rectangle.right() = (typename RECTANGLE::UNIT_TYPE)(point.x() + size.cx());
   rectangle.bottom() = (typename RECTANGLE::UNIT_TYPE)(point.y() + size.cy());

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE >
RECTANGLE_TYPE & null(RECTANGLE_TYPE & rectangle)
{

   return ::assign(rectangle, 0, 0, 0, 0);

}



template < primitive_rectangle RECTANGLE, primitive_number X >
inline bool contains_x(const RECTANGLE & rectangle, X x)
{

   return x >= rectangle.left() && x <= rectangle.right();

}


template < primitive_rectangle RECTANGLE, primitive_number Y >
inline bool contains_y(const RECTANGLE & rectangle, Y y)
{

   return y >= rectangle.top() && y <= rectangle.bottom();

}


template < typename RECTANGLE, primitive_number X, primitive_number Y >
inline bool contains(const RECTANGLE & rectangle, X x, Y y)
{

   return contains_x(rectangle, x) && contains_y(rectangle, y);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.left() - l);
   rectangle.top() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.top() - t);
   rectangle.right() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.right() + r);
   rectangle.bottom() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.bottom() + b);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   return inflate(rectangle, rect2.left(), rect2.top(), rect2.right(), rect2.bottom());

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & multiply_inline(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   rectangle.left() *= rect2.left();
   rectangle.top() *= rect2.top();
   rectangle.right() *= rect2.right();
   rectangle.bottom() *= rect2.bottom();

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.left() + l);
   rectangle.top() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.top() + t);
   rectangle.right() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.right() - r);
   rectangle.bottom() = (typename RECTANGLE_TYPE::UNIT_TYPE)(rectangle.bottom() - b);

   return rectangle;

}


template < typename RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   return deflate(rectangle, rect2.left(), rect2.top(), rect2.right(), rect2.bottom());

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   return inflate(rectangle, x, y, x, y);

}

template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   return deflate(rectangle, x, y, x, y);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, UNIT u)
{

   return inflate(rectangle, u, u);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, UNIT u)
{

   return deflate(rectangle, u, u);

}


template < primitive_rectangle RECTANGLE_TYPE >
inline RECTANGLE_TYPE & swap_left_right(RECTANGLE_TYPE & rectangle) { __swap(rectangle.left(), rectangle.right()); return rectangle; }


template < primitive_point POINT1, primitive_point POINT2 >
inline bool polygon_contains_winding(const POINT1 * ppPolygon, int iCount, const POINT2 & point)
{

   int i, j = iCount - 1;

   auto x = point.x();

   auto y = point.y();

   bool oddNodes = false;

   for (i = 0; i < iCount; i++)
   {

      if (((ppPolygon[i].y() < y && ppPolygon[j].y() >= y) || (ppPolygon[j].y() < y && ppPolygon[i].y() >= y)) && (ppPolygon[i].x() <= x || ppPolygon[j].x() <= x))
      {

         oddNodes ^= (ppPolygon[i].x() + (y - ppPolygon[i].y()) / (ppPolygon[j].y() - ppPolygon[i].y()) * (ppPolygon[j].x() - ppPolygon[i].x()) < x);

      }

      j = i;

   }

   return oddNodes;

}



// there are degenerated cases for this ray-casting method for even odd rule (use holes)
//https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon


/* intersection function */
template < primitive_point POINT1, primitive_point POINT2 >
inline bool polygon_contains_alternate(const POINT1 * ppPolygon, int iCount, const POINT2 & point, const bool use_holes, largest_number < ::decay<typename POINT1::UNIT_TYPE>, ::decay<typename POINT2::UNIT_TYPE>> epsilon = default_epsilon<largest_number < ::decay < typename POINT1::UNIT_TYPE >, ::decay < typename POINT2::UNIT_TYPE > > > ())
{

   using UNIT_TYPE = largest_number < ::decay <typename  POINT1::UNIT_TYPE >, ::decay<typename POINT2::UNIT_TYPE > >;

   /* we do the angle rule, define that all added angles should be about zero or (2 * PI) */
   UNIT_TYPE angletot{};
   //float fp1[2], fp2[2];
   //unsigned int i;
   //const float * p1, * p2;

   auto * p1 = &ppPolygon[iCount - 1];

   const POINT1 * p2 = nullptr;

   /* first vector */
   POINT1 fp1 = *p1 - point;

   for (int i = 0; i < iCount; i++)
   {
      
      p2 = &ppPolygon[i];

      /* second vector */
      POINT1 fp2 = *p2 - point;

      /* dot and angle and cross */
      angletot += fp1.angle(fp2);

      /* circulate */
      fp1 = fp2;

      p1 = p2;

   }

   angletot = (UNIT_TYPE) fabs(angletot);
   
   if (use_holes)
   {
   
      auto nested = (UNIT_TYPE) (floor((double) (angletot / (UNIT_TYPE)(MATH_PI * 2.0)) + (double) epsilon));

      angletot -= nested * (UNIT_TYPE)(MATH_PI * 2.0);

      return (angletot > 4.0f) != ((int)nested % 2);

   }
   else
   {

      return (angletot > 4.0f);

   }

}


/* math lib */

//static float dot_v2v2(const float a[2], const float b[2])
//{
//   return a[0] * b[0] + a[1] * b[1];
//}


//static void copy_v2_v2(float r[2], const float a[2])
//{
//   r[0] = a[0];
//   r[1] = a[1];
//}

//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator -= (POINT & point, const POINT2 & pointOffset) { ::subtract(point, pointOffset); return point; }
//
//template < primitive_point POINT, primitive_point POINT2 >
//inline POINT & operator += (POINT & point, const POINT2 & pointOffset) { ::add(point, pointOffset); return point; }
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator -= (RECTANGLE & rectangle, const POINT & point) { ::subtract(rectangle, point); return rectangle; }
//
//template < primitive_rectangle RECTANGLE, primitive_point POINT >
//inline RECTANGLE & operator += (RECTANGLE & rectangle, const POINT & point) { ::add(rectangle, point); return rectangle; }






template < typename RECT1, typename RECT2 >
inline void expand_rect(RECT1& rectangle, const RECT2& r)
{

   if (::is_null(rectangle))
   {

      copy(rectangle, r);

   }
   else
   {

      rectangle.left() = minimum((typename RECT1::UNIT_TYPE)rectangle.left(), (typename RECT1::UNIT_TYPE)r.left());
      rectangle.right() = maximum((typename RECT1::UNIT_TYPE)rectangle.right(), (typename RECT1::UNIT_TYPE)r.right());
      rectangle.top() = minimum((typename RECT1::UNIT_TYPE)rectangle.top(), (typename RECT1::UNIT_TYPE)r.top());
      rectangle.bottom() = maximum((typename RECT1::UNIT_TYPE)rectangle.bottom(), (typename RECT1::UNIT_TYPE)r.bottom());

   }

}


template < typename RECT1, typename RECT2 >
inline void collapse_rect(RECT1& rectangle, const RECT2& r)
{

   if (::is_null(rectangle))
   {

      copy(rectangle, r);

   }
   else
   {

      rectangle.left() = maximum((typename RECT1::UNIT_TYPE)rectangle.left(), (typename RECT1::UNIT_TYPE)r.left());
      rectangle.right() = minimum((typename RECT1::UNIT_TYPE)rectangle.right(), (typename RECT1::UNIT_TYPE)r.right());
      rectangle.top() = maximum((typename RECT1::UNIT_TYPE)rectangle.top(), (typename RECT1::UNIT_TYPE)r.top());
      rectangle.bottom() = minimum((typename RECT1::UNIT_TYPE)rectangle.bottom(), (typename RECT1::UNIT_TYPE)r.bottom());

      if (::width(rectangle) == 0 || height(rectangle) == 0)
      {

         ::null(rectangle);

      }

   }

}


template < primitive_point POINT >
inline constexpr auto __horz(const POINT& point) { return point.x(); }
template < primitive_point POINT >
inline constexpr auto __vert(const POINT& point) { return point.y(); }
template < primitive_size SIZE >
inline constexpr auto __horz(const SIZE& size) { return size.cx(); }
template < primitive_size SIZE >
inline constexpr auto __vert(const SIZE& size) { return size.cy(); }


template < primitive_rectangle RECTANGLE >
inline auto & top_left(const RECTANGLE & rectangle) { return *(typename RECTANGLE::POINT_TYPE*)&rectangle; }
template < primitive_rectangle RECTANGLE >
inline auto & bottom_right(const RECTANGLE& rectangle) { return *(typename RECTANGLE::POINT_TYPE*)&rectangle.right(); }


//inline point_i64& top_left(const rectangle_i64& rectangle) { return *(point_i64*)&rectangle; }
//inline point_i64& bottom_right(const rectangle_i64& rectangle) { return *(point_i64*)&rectangle.right(); }


//inline point_f32& top_left(const rectangle_f32& rectangle) { return *(point_f32*)&rectangle; }
//inline point_f32& bottom_right(const rectangle_f32& rectangle) { return *(point_f32*)&rectangle.right(); }


//inline point_f64& top_left(const rectangle_f64& rectangle) { return *(point_f64*)&rectangle; }
//inline point_f64& bottom_right(const rectangle_f64& rectangle) { return *(point_f64*)&rectangle.right(); }


//inline point_i32 & top_left(const ::rectangle_i32 &rectangle) { return *(point_i32 *)&rectangle; }
//inline point_i32 & bottom_right(const ::rectangle_i32 &rectangle) { return *(point_i32 *)&rectangle.right(); }
//inline point_i32 & top_left(const ::rectangle_i32 &rectangle) { return top_left(&rectangle); }
//inline point_i32 & bottom_right(const ::rectangle_i32 &rectangle) { return bottom_right(&rectangle); }


//inline point_i64 & top_left(const ::rectangle_i64 & rectangle) { return *(point_i64 *)&rectangle; }
//inline point_i64 & bottom_right(const ::rectangle_i64 & rectangle) { return *(point_i64 *)&rectangle.right(); }
//inline point_i64 & top_left(const ::rectangle_i64 & rectangle) { return top_left(&rectangle); }
//inline point_i64 & bottom_right(const ::rectangle_i64 & rectangle) { return bottom_right(&rectangle); }


//inline point_f64 & top_left(const ::rectangle_f64 & rectangle) { return *(point_f64 *)&rectangle; }
//inline point_f64 & bottom_right(const ::rectangle_f64 & rectangle) { return *(point_f64 *)&rectangle.right(); }
//inline point_f64 & top_left(const ::rectangle_f64 & rectangle) { return top_left(&rectangle); }
//inline point_f64 & bottom_right(const ::rectangle_f64 & rectangle) { return bottom_right(&rectangle); }




//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const POINT_TYPE & point) noexcept : size_type((size_type&)point_i32) {}
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >::size_type(const RECTANGLE_TYPE & rectangle) noexcept : size_type(rectangle.width(), rectangle.height()) {}

//
//template < typename UNIT_TYPE >
//inline UNIT_TYPE __conv(const ::string & str)
//{
//
//   return (UNIT_TYPE)str;
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
//





namespace geometry
{

   //////////////////////////////////////////////////////////////////////
   //
   // Function Name: deflate
   //
   // Purpose:
   // Change rectangle dimension using its dimensions and the specified
   // rates. For example, the dLeftRate machine the left position of the
   // rectangle. If 0.0, it remains the same as the original left.
   // If 1.0, it turns as the original right. If 0.4, it will be 40%
   // of the width from left to right.
   //
   // Output:
   // -1 if the creation of the ::user::impact failed.
   // 0 if the creation of the ::user::impact succeeded.
   //
   // Author:
   // Vanessa Testoni
   //
   //
   //////////////////////////////////////////////////////////////////////
   template < primitive_rectangle RECTANGLE >
   inline void deflate(RECTANGLE& rectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate)
   {

      rectangle.left() = range_rate(rectangle.left(), rectangle.right(), dLeftRate);

      rectangle.right() = range_rate(rectangle.right(), rectangle.left(), dRightRate);

      rectangle.top() = range_rate(rectangle.top(), rectangle.bottom(), dTopRate);

      rectangle.bottom() = range_rate(rectangle.bottom(), rectangle.top(), dBottomRate);

   }


} // namespace geometry


//template < primitive_point POINT >
//inline ::string as_string(const POINT & point)
//{
//
//   return as_string(point.x()) + ", " + as_string(point.y());
//
//}
//
//
//template < primitive_size SIZE >
//inline ::string as_string(const SIZE & size)
//{
//
//   return as_string(size.cx()) + ", " + as_string(size.cy());
//
//}
