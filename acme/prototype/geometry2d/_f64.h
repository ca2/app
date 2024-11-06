#pragma once


#pragma pack(push, geometry2d_f64, 1)


struct SIZE_F64
{

   double cx;
   double cy;

};


typedef const SIZE_F64 * LPCSIZE_F64;

struct POINT_F64
{

   double x;
   double y;

};


typedef const POINT_F64 * LPCPOINT_F64;


struct RECTANGLE_F64
{

   double left;
   double top;
   double right;
   double bottom;

};


typedef const RECTANGLE_F64 * LPCRECTANGE_F64;


#pragma pack(pop, geometry2d_f64)


