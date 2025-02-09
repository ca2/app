#pragma once


#pragma pack(push, geometry2d_long_long, 1)


struct LONG_LONG_SIZE
{

   long long cx;
   long long cy;

};


typedef const LONG_LONG_SIZE * LPCLONG_LONG_SIZE;

struct LONG_LONG_POINT
{

   long long x;
   long long y;

};


typedef const LONG_LONG_POINT * LPCLONG_LONG_POINT;


struct LONG_LONG_RECTANGLE
{

   long long left;
   long long top;
   long long right;
   long long bottom;

};


typedef const LONG_LONG_RECTANGLE * LPCRECTANGE_I64;


#pragma pack(pop, geometry2d_long_long)


