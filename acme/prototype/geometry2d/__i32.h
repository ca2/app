#pragma once


//#pragma pack(push, geometry2d_int, 1)


struct INT_SIZE
{

   ::i32 cx;
   ::i32 cy;
//
//   operator ::hash32() const { return cx | cy << 16; }

};


typedef const INT_SIZE * LPCINT_SIZE;

struct INT_POINT
{

   ::i32 x;
   ::i32 y;

};


typedef const INT_POINT * LPCINT_POINT;


struct INT_RECTANGLE
{

   ::i32 left;
   ::i32 top;
   ::i32 right;
   ::i32 bottom;

};

 


//#pragma pack(pop, geometry2d_int)

