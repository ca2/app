#pragma once


#pragma pack(push, geometry2d_i64, 1)


struct SIZE_I64
{

   ::i64 cx;
   ::i64 cy;

};


typedef const SIZE_I64 * LPCSIZE_I64;

struct POINT_I64
{

   ::i64 x;
   ::i64 y;

};


typedef const POINT_I64 * LPCPOINT_I64;


struct RECTANGLE_I64
{

   ::i64 left;
   ::i64 top;
   ::i64 right;
   ::i64 bottom;

};


typedef const RECTANGLE_I64 * LPCRECTANGE_I64;


#pragma pack(pop, geometry2d_i64)


