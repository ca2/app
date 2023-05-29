// From _initial_concepts.h by camilo on 2023-05-23 <3ThomasBorregaardSørensen!!
//
//  _numeric_concepts.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


template < typename NUMBER >
concept primitive_number =
   std::is_integral_v < ::std::decay_t < NUMBER > > ||
   std::is_enum_v < ::std::decay_t < NUMBER > > ||
   std::is_floating_point_v < ::std::decay_t < NUMBER > >;


template < typename POINT >
concept raw_primitive_point = requires(POINT point)
{
   {point.x}->primitive_number;
   {point.y}->primitive_number;
};




template < typename POINT >
concept primitive_point = requires(POINT point)
{
   {point.x()}->primitive_number;
   {point.y()}->primitive_number;
};



template < typename POLE >
concept primitive_pole = requires(POLE pole)
{
   {pole.x()}->primitive_number;
   {pole.y()}->primitive_number;
   {pole.z()}->primitive_number;
};




template < typename ORIGIN_SIZE >
concept origin_size = requires(ORIGIN_SIZE origin_size)
{

   { origin_size.origin } -> primitive_point;
   { origin_size.size } -> primitive_dim;

};



template < primitive_number NUMBER >
struct argument_of_struct < NUMBER >
{

   using type = NUMBER;

};



template < primitive_number NUMBER >
class point_type;


template < primitive_number NUMBER >
class size_type;


template < primitive_number NUMBER >
class rectangle_type;








template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline void copy(NUMBER1& number1, const NUMBER2& number2)
{

   number1 = (NUMBER1)number2;

}







template < primitive_XY POINT1, primitive_point POINT2 >
void copy(POINT1 point1, const POINT2& point2)
{

   point1.X = (decltype(POINT1::X))point2.x();
   point1.Y = (decltype(POINT1::Y))point2.y();

}


template < primitive_point POINT1, primitive_XY POINT2 >
void copy(POINT1& point1, const POINT2& point2)
{

   point1.x() = (decltype(POINT1::x))point2.X;
   point1.y() = (decltype(POINT1::y))point2.Y;

}


template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
void copy(XYDim& xydim, const RECTANGLE& rectangle)
{

   xydim.X = (decltype(XYDim::X))rectangle.left;
   xydim.Y = (decltype(XYDim::Y))rectangle.top;
   xydim.Width = (decltype(XYDim::Width))(rectangle.right - rectangle.left);
   xydim.Height = (decltype(XYDim::Height))(rectangle.bottom - rectangle.top);

}


template < primitive_xydim XYDIM, primitive_rectangle RECTANGLE >
void copy(XYDIM& xydim, const RECTANGLE& rectangle)
{

   xydim.x() = (decltype(XYDIM::X))rectangle.left;
   xydim.y() = (decltype(XYDIM::Y))rectangle.top;
   xydim.width = (decltype(XYDIM::Width))(rectangle.right - rectangle.left);
   xydim.height = (decltype(XYDIM::Height))(rectangle.bottom - rectangle.top);

}


template < primitive_XYDim XYDim1, primitive_XYDim XYDim2 >
void copy(XYDim1& xydim1, const XYDim2& xydim2)
{

   xydim1.X = (decltype(XYDim1::X))xydim2.X;
   xydim1.Y = (decltype(XYDim1::Y))xydim2.Y;
   xydim1.Width = (decltype(XYDim1::Width))xydim2.Width;
   xydim1.Height = (decltype(XYDim1::Height))xydim2.Height;

}


template < primitive_point POINT1, primitive_point POINT2 >
void copy(POINT1& point1, const POINT2& point2)
{

   point1.x() = (const ::std::decay_t <decltype(point1.x())>&)point2.x();
   point1.y() = (const ::std::decay_t <decltype(point1.y())>&)point2.y();

}


template < primitive_point POINT, primitive_size SIZE >
void copy(POINT& point, const SIZE& size)
{

   point.x() = (const ::std::decay_t <decltype(point.x())>&)size.cx();
   point.y() = (const ::std::decay_t <decltype(point.y()) > &)size.cy();

}


template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
void copy(SIZE_TYPE1& size1, const SIZE_TYPE2& size2)
{

   size1.cx() = (decltype(SIZE_TYPE1::cx))size2.cx();
   size1.cy() = (decltype(SIZE_TYPE1::cy))size2.cy();

}




template < primitive_rectangle RECTANGLE, origin_size ORIGIN_SIZE >
constexpr void copy(RECTANGLE& rectangle, const ORIGIN_SIZE& origin_size)
{

   rectangle.left = (decltype(rectangle.left))origin_size.origin.x();
   rectangle.top = (decltype(rectangle.top))origin_size.origin.y();
   rectangle.right = (decltype(rectangle.right))(origin_size.origin.x() + origin_size.size.width);
   rectangle.bottom = (decltype(rectangle.bottom))(origin_size.origin.y() + origin_size.size.height);

}


template < origin_size ORIGIN_SIZE, primitive_rectangle RECTANGLE >
constexpr void copy(ORIGIN_SIZE& origin_size, const RECTANGLE& rectangle)
{

   origin_size.origin.x() = (decltype(origin_size.origin.x()))rectangle.left;
   origin_size.origin.y() = (decltype(origin_size.origin.y()))rectangle.top;
   origin_size.size.width = (decltype(origin_size.size.width))(rectangle.right - rectangle.left);
   origin_size.size.height = (decltype(origin_size.size.height))(rectangle.bottom - rectangle.top);

}


