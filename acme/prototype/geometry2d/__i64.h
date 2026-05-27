#pragma once


//#pragma pack(push, geometry2d_i64, 1)


struct LONG_LONG_SIZE
{

   ::i64 cx;
   ::i64 cy;

};


typedef const LONG_LONG_SIZE * LPCLONG_LONG_SIZE;

struct LONG_LONG_POINT
{

   ::i64 x;
   ::i64 y;

};


typedef const LONG_LONG_POINT * LPCLONG_LONG_POINT;


struct LONG_LONG_RECTANGLE
{

   ::i64 left;
   ::i64 top;
   ::i64 right;
   ::i64 bottom;

};


typedef const LONG_LONG_RECTANGLE * LPCRECTANGE_I64;


//#pragma pack(pop, geometry2d_i64)


