// From _initial_concepts.h by camilo on 2023-05-23 <3ThomasBorregaardSorensen!!
//
//  _numeric_concepts.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/22.
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


template < typename NUMBER >
concept primitive_number =
   primitive_integral < NUMBER > ||
   primitive_floating < NUMBER > ||
   primitive_enum < NUMBER >;


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


template < typename POINT >
concept primitive_XY = requires(POINT point)
{
   point.X;
   point.Y;
};


template < typename SIZE >
concept primitive_size = requires(SIZE size)
{
   size.cx();
   size.cy();
};


template < typename Dimension >
concept primitive_Dimension = requires(Dimension dimension)
{
   dimension.Width;
   dimension.Height;
};


template < typename DIMENSION >
concept primitive_dimension = requires(DIMENSION dimension)
{
   dimension.width;
   dimension.height;
};


template < typename RECTANGLE >
concept primitive_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.left;
   rectangle.top;
   rectangle.right;
   rectangle.bottom;
};


template < typename RECTANGLE >
concept primitive_XYDim = requires(RECTANGLE rectangle)
{
   rectangle.X;
   rectangle.Y;
   rectangle.Width;
   rectangle.Height;
};


template < typename RECTANGLE >
concept primitive_xydim = requires(RECTANGLE rectangle)
{
   rectangle.x;
   rectangle.y;
   rectangle.width;
   rectangle.height;
};


template < typename RECTANGLE >
concept primitive_origin_size = requires(RECTANGLE rectangle)
{
   {rectangle.origin}->raw_primitive_point;
   {rectangle.size}->primitive_dimension;
};


//template < typename ORIGIN_SIZE >
//concept origin_size = requires(ORIGIN_SIZE origin_size)
//{
//
//   { origin_size.origin } -> primitive_point;
//   { origin_size.size } -> primitive_dim;
//
//};



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






//
//
//template < primitive_number NUMBER1, primitive_number NUMBER2 >
//inline void copy(NUMBER1& number1, const NUMBER2& number2)
//{
//
//   number1 = (NUMBER1)number2;
//
//}
//









