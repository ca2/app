#pragma once


#pragma pack(push, geometry2d_i32, 1)


struct SIZE_I32
{

   int cx;
   int cy;
//
//   operator ::u32hash() const { return cx | cy << 16; }

};


typedef const SIZE_I32 * LPCSIZE_I32;

struct POINT_I32
{

   int x;
   int y;

};


typedef const POINT_I32 * LPCPOINT_I32;


struct RECTANGLE_I32
{

   int left;
   int top;
   int right;
   int bottom;

};

 


#pragma pack(pop, geometry2d_i32)

