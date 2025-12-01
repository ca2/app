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
   std::is_integral_v < ::std::decay_t < NUMBER > > ||
   std::is_enum_v < ::std::decay_t < NUMBER > > ||
   std::is_floating_point_v < ::std::decay_t < NUMBER > >;


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








template < prototype_number NUMBER1, prototype_number NUMBER2 >
inline void copy(NUMBER1& number1, const NUMBER2& number2)
{

   number1 = (NUMBER1)number2;

}







template < prototype_XY POINT1, prototype_point POINT2 >
void copy(POINT1 point1, const POINT2& point2)
{

   point1.X = (decltype(POINT1::X))point2.x;
   point1.Y = (decltype(POINT1::Y))point2.y;

}


template < prototype_point POINT1, prototype_XY POINT2 >
void copy(POINT1& point1, const POINT2& point2)
{

   point1.x = (decltype(POINT1::x))point2.X;
   point1.y = (decltype(POINT1::y))point2.Y;

}


template < prototype_rectangle RECTANGLE1, prototype_rectangle RECTANGLE2 >
inline void copy(RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
{

   rectangle1.left = (::decay<decltype(rectangle1.left)>)rectangle2.left;
   rectangle1.top = (::decay<decltype(rectangle1.top)>)rectangle2.top;
   rectangle1.right = (::decay<decltype(rectangle1.right)>)rectangle2.right;
   rectangle1.bottom = (::decay<decltype(rectangle1.bottom)>)rectangle2.bottom;

}


template < prototype_XYDim XYDim, prototype_rectangle RECTANGLE >
void copy(XYDim& xydim, const RECTANGLE& rectangle)
{

   xydim.X = (decltype(XYDim::X))rectangle.left;
   xydim.Y = (decltype(XYDim::Y))rectangle.top;
   xydim.Width = (decltype(XYDim::Width))(rectangle.right - rectangle.left);
   xydim.Height = (decltype(XYDim::Height))(rectangle.bottom - rectangle.top);

}


template < prototype_xydim XYDIM, prototype_rectangle RECTANGLE >
void copy(XYDIM& xydim, const RECTANGLE& rectangle)
{

   xydim.x = (decltype(XYDIM::X))rectangle.left;
   xydim.y = (decltype(XYDIM::Y))rectangle.top;
   xydim.width = (decltype(XYDIM::Width))(rectangle.right - rectangle.left);
   xydim.height = (decltype(XYDIM::Height))(rectangle.bottom - rectangle.top);

}


template < prototype_XYDim XYDim1, prototype_XYDim XYDim2 >
void copy(XYDim1& xydim1, const XYDim2& xydim2)
{

   xydim1.X = (decltype(XYDim1::X))xydim2.X;
   xydim1.Y = (decltype(XYDim1::Y))xydim2.Y;
   xydim1.Width = (decltype(XYDim1::Width))xydim2.Width;
   xydim1.Height = (decltype(XYDim1::Height))xydim2.Height;

}


template < prototype_point POINT1, prototype_point POINT2 >
void copy(POINT1& point1, const POINT2& point2)
{

   point1.x = (const ::std::decay_t <decltype(point1.x)>&)point2.x;
   point1.y = (const ::std::decay_t <decltype(point1.y)>&)point2.y;

}


template < prototype_point POINT1, raw_primitive_point POINT2 >
void copy(POINT1& point1, const POINT2& point2)
{

   point1.x = (const ::std::decay_t <decltype(point1.x)>&)point2.x;
   point1.y = (const ::std::decay_t <decltype(point1.y)>&)point2.y;
   
}

template < raw_primitive_point POINT1, prototype_point POINT2 >
void copy(POINT1& point1, const POINT2& point2)
{

   point1.x = (const ::std::decay_t <decltype(point1.x)>&)point2.x;
   point1.y = (const ::std::decay_t <decltype(point1.y)>&)point2.y;

}


template < prototype_point POINT, prototype_size SIZE >
void copy(POINT& point, const SIZE& size)
{

   point.x = (const ::std::decay_t <decltype(point.x)>&)size.cx;
   point.y = (const ::std::decay_t <decltype(point.y) > &)size.cy;

}


template < prototype_size SIZE_TYPE1, prototype_size SIZE_TYPE2 >
void copy(SIZE_TYPE1& size1, const SIZE_TYPE2& size2)
{

   size1.cx = (decltype(SIZE_TYPE1::cx))size2.cx;
   size1.cy = (decltype(SIZE_TYPE1::cy))size2.cy;

}






