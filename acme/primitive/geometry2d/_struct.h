#pragma once


template < typename POINT >
concept primitive_point = requires(POINT point)
{
   point.x;
   point.y;
};


template < typename POINT >
concept XY_point = requires(POINT point)
{
   point.X;
   point.Y;
};


template < typename SIZE >
concept primitive_size = requires(SIZE size)
{
   size.cx;
   size.cy;
};


template < typename SIZE >
concept Dim_size = requires(SIZE size)
{
   size.Width;
   size.Height;
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
concept XYDim_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.X;
   rectangle.Y;
   rectangle.Width;
   rectangle.Height;
};


#include "_i32.h"
#include "_i64.h"
#include "_f32.h"
#include "_f64.h"



