#pragma once


#pragma pack(push, geometry2d_huge_integer, 1)


struct LONG_LONG_SIZE
{

   huge_integer cx;
   huge_integer cy;

};


typedef const LONG_LONG_SIZE * LPCLONG_LONG_SIZE;

struct LONG_LONG_POINT
{

   huge_integer x;
   huge_integer y;

};


typedef const LONG_LONG_POINT * LPCLONG_LONG_POINT;


struct LONG_LONG_RECTANGLE
{

   huge_integer left;
   huge_integer top;
   huge_integer right;
   huge_integer bottom;

};


typedef const LONG_LONG_RECTANGLE * LPCRECTANGE_I64;


#pragma pack(pop, geometry2d_huge_integer)


