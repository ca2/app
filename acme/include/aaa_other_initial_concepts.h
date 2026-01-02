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
concept prototype_number =
   prototype_integral < NUMBER > ||
   prototype_floating < NUMBER > ||
   prototype_enum < NUMBER >;


template < typename POINT >
concept raw_primitive_point = requires(POINT point)
{
   {point.x}->prototype_number;
   {point.y}->prototype_number;
};


template < typename POINT >
concept prototype_point = requires(POINT point)
{
   {point.x}->prototype_number;
   {point.y}->prototype_number;
};


template < typename POLE >
concept prototype_pole = requires(POLE pole)
{
   {pole.x}->prototype_number;
   {pole.y}->prototype_number;
   {pole.z}->prototype_number;
};


template < typename POINT >
concept prototype_XY = requires(POINT point)
{
   point.X;
   point.Y;
};


template < typename SIZE >
concept prototype_size = requires(SIZE size)
{
   size.cx;
   size.cy;
};


template < typename Dimension >
concept prototype_Dimension = requires(Dimension dimension)
{
   dimension.Width;
   dimension.Height;
};


template < typename DIMENSION >
concept prototype_dimension = requires(DIMENSION dimension)
{
   dimension.width;
   dimension.height;
};


template < typename RECTANGLE >
concept prototype_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.left;
   rectangle.top;
   rectangle.right;
   rectangle.bottom;
};


template < typename RECTANGLE >
concept prototype_XYDim = requires(RECTANGLE rectangle)
{
   rectangle.X;
   rectangle.Y;
   rectangle.Width;
   rectangle.Height;
};


template < typename RECTANGLE >
concept prototype_xydim = requires(RECTANGLE rectangle)
{
   rectangle.x;
   rectangle.y;
   rectangle.width;
   rectangle.height;
};


template < typename RECTANGLE >
concept prototype_origin_size = requires(RECTANGLE rectangle)
{
   {rectangle.origin}->raw_primitive_point;
   {rectangle.size}->prototype_dimension;
};


//template < typename ORIGIN_SIZE >
//concept origin_size = requires(ORIGIN_SIZE origin_size)
//{
//
//   { origin_size.origin } -> prototype_point;
//   { origin_size.size } -> prototype_dim;
//
//};



template < prototype_number NUMBER >
struct argument_of_struct < NUMBER >
{

   using type = NUMBER;

};



template < prototype_number NUMBER >
class point_type;


template < prototype_number NUMBER >
class size_type;


template < prototype_number NUMBER >
class rectangle_type;






//
//
//template < prototype_number NUMBER1, prototype_number NUMBER2 >
//inline void copy(NUMBER1& number1, const NUMBER2& number2)
//{
//
//   number1 = (NUMBER1)number2;
//
//}
//









