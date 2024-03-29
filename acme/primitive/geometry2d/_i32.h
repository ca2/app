#pragma once


#pragma pack(push, geometry2d_i32, 1)


struct SIZE_I32
{

   ::i32 cx;
   ::i32 cy;
//
//   operator ::u32hash() const { return cx | cy << 16; }

};


typedef const SIZE_I32 * LPCSIZE_I32;

struct POINT_I32
{

   ::i32 x;
   ::i32 y;

};


typedef const POINT_I32 * LPCPOINT_I32;


struct RECTANGLE_I32
{

   ::i32 left;
   ::i32 top;
   ::i32 right;
   ::i32 bottom;

};

 


#pragma pack(pop, geometry2d_i32)

