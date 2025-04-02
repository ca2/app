#pragma once


//#pragma pack(push, geometry2d_double, 1)


struct DOUBLE_SIZE
{

   double cx;
   double cy;

};


typedef const DOUBLE_SIZE * LPCDOUBLE_SIZE;

struct DOUBLE_POINT
{

   double x;
   double y;

};


typedef const DOUBLE_POINT * LPCDOUBLE_POINT;


struct DOUBLE_RECTANGLE
{

   double left;
   double top;
   double right;
   double bottom;

};


typedef const DOUBLE_RECTANGLE * LPCRECTANGE_F64;


//#pragma pack(pop, geometry2d_double)


