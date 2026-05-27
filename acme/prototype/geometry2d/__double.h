#pragma once


//#pragma pack(push, geometry2d_double, 1)


struct DOUBLE_SIZE
{

   ::f64 cx;
   ::f64 cy;

};


typedef const DOUBLE_SIZE * LPCDOUBLE_SIZE;

struct DOUBLE_POINT
{

   ::f64 x;
   ::f64 y;

};


typedef const DOUBLE_POINT * LPCDOUBLE_POINT;


struct DOUBLE_RECTANGLE
{

   ::f64 left;
   ::f64 top;
   ::f64 right;
   ::f64 bottom;

};


typedef const DOUBLE_RECTANGLE * LPCRECTANGE_F64;


//#pragma pack(pop, geometry2d_double)


