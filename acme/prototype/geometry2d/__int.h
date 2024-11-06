#pragma once


#pragma pack(push, geometry2d_int, 1)


struct INT_SIZE
{

   int cx;
   int cy;
//
//   operator ::u32hash() const { return cx | cy << 16; }

};


typedef const INT_SIZE * LPCINT_SIZE;

struct INT_POINT
{

   int x;
   int y;

};


typedef const INT_POINT * LPCINT_POINT;


struct INT_RECTANGLE
{

   int left;
   int top;
   int right;
   int bottom;

};

 


#pragma pack(pop, geometry2d_int)

