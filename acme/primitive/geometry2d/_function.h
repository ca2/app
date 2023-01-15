// Created by camilo on 2022-11-08 16:01 <3ThomasBorregaardSørensen!!
#pragma once


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto width(RECTANGLE_TYPE & rectangle);

template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto height(RECTANGLE_TYPE & rectangle);

template < typename W, typename H >
constexpr H area(W w, H h);

template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto area(RECTANGLE_TYPE & rectangle);

template < primitive_rectangle RECTANGLE_TYPE >
bool is_null(const RECTANGLE_TYPE & rectangle);

template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto is_empty(RECTANGLE_TYPE & rectangle);

template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto is_set(RECTANGLE_TYPE & rectangle);

template < primitive_size SIZE_TYPE >
bool is_null(const SIZE_TYPE & size);

template < primitive_point POINT_TYPE >
bool is_null(const POINT_TYPE & point);

template < primitive_rectangle RECTANGLE_TYPE, typename X >
inline RECTANGLE_TYPE & x_offset(RECTANGLE_TYPE & rectangle, X x);

template < primitive_rectangle RECTANGLE_TYPE, typename Y >
inline RECTANGLE_TYPE & y_offset(RECTANGLE_TYPE & rectangle, Y y);

template < primitive_rectangle RECTANGLE_TYPE, typename X >
inline RECTANGLE_TYPE & x_subtract(RECTANGLE_TYPE & rectangle, X x);

template < primitive_rectangle RECTANGLE_TYPE, typename Y >
inline RECTANGLE_TYPE & y_subtract(RECTANGLE_TYPE & rectangle, Y y);

template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, X x, Y y);

template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, X x, Y y);

template < typename RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point);

template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point);

template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
inline RECTANGLE1 & subtract(RECTANGLE1 & rectangle, const RECTANGLE2 & rectangle2);

//template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT & point) { return subtract(rectangle, point); }


template < primitive_point POINT, typename X, typename Y >
inline POINT & offset(POINT & point, X x, Y y);

template < primitive_point POINT, primitive_point POINT2 >
inline POINT & offset(POINT & point, const POINT2 & point2);

template < primitive_point POINT, primitive_point POINT2 >
inline POINT & add(POINT & point, const POINT2 & point2);

template < primitive_point POINT_TYPE, typename X, typename Y >
inline POINT_TYPE & subtract(POINT_TYPE & point, X x, Y y);

template < primitive_point POINT_TYPE, primitive_point POINT_TYPE2 >
inline POINT_TYPE & subtract(POINT_TYPE & point, const POINT_TYPE2 & point2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & add(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_top_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool top_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECTANGLE_TYPE & unite(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 & unite(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2);


template < typename X, typename Y >
auto get_dimension(enum_orientation eorientation, X x, Y y);


template < typename X, typename Y >
auto get_normal_dimension(enum_orientation eorientation, X x, Y y);


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
bool is_equal(const RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2);

template < primitive_point POINT1, primitive_point POINT2 >
bool is_equal(const POINT1 & point1, const POINT2 & point2);

template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
bool is_equal(const SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2);

template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
RECTANGLE_TYPE & assign(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b);


template < primitive_rectangle RECTANGLE, primitive_number L, primitive_number T, primitive_number W, primitive_number H >
RECTANGLE & set_dimension(RECTANGLE & rectangle, L l, T t, W w, H h);

//template < primitive_rectangle RECTANGLE,  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE &r, L l, T t, W w, H h) { return set_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_I64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_F32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_F64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }


template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & set_bottom_right(RECTANGLE & rectangle, const SIZE & size);

template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & assign(RECTANGLE & rectangle, const POINT & point, const SIZE & size);


template < primitive_rectangle RECTANGLE_TYPE >
RECTANGLE_TYPE & null(RECTANGLE_TYPE & rectangle);


template < primitive_rectangle RECTANGLE, primitive_number X >
inline bool contains_x(const RECTANGLE & rectangle, X x);


template < primitive_rectangle RECTANGLE, primitive_number Y >
inline bool contains_y(const RECTANGLE & rectangle, Y y);

template < typename RECTANGLE, primitive_number X, primitive_number Y >
inline bool contains(const RECTANGLE & rectangle, X x, Y y);

template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b);

template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2);


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & multiply_inline(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2);


template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b);

template < typename RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2);


template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, X x, Y y);

template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, X x, Y y);


template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, UNIT u);


template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, UNIT u);


template < primitive_rectangle RECTANGLE_TYPE >
inline RECTANGLE_TYPE & swap_left_right(RECTANGLE_TYPE & rectangle);


template < primitive_point POINT1, primitive_point POINT2 >
inline bool polygon_contains(const POINT1 * ppPolygon, i32 iCount, const POINT2 & point);

template < primitive_point POINT, primitive_point POINT2 >
inline POINT & operator -= (POINT & point, const POINT2 & pointOffset);

template < primitive_point POINT, primitive_point POINT2 >
inline POINT & operator += (POINT & point, const POINT2 & pointOffset);

template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline RECTANGLE & operator -= (RECTANGLE & rectangle, const POINT & point);

template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline RECTANGLE & operator += (RECTANGLE & rectangle, const POINT & point);


CLASS_DECL_ACME double d_distance(const point_i32& point1, const point_i32& point2);





