#pragma once


#pragma pack(push, geometry2d_f32, 1)


struct SIZE_F32
{

   ::f32 cx;
   ::f32 cy;

};


typedef const SIZE_F32 * LPCSIZE_F32;

struct POINT_F32
{

   ::f32 x;
   ::f32 y;

};


typedef const POINT_F32 * LPCPOINT_F32;


struct RECTANGLE_F32
{

   ::f32 left;
   ::f32 top;
   ::f32 right;
   ::f32 bottom;

};


typedef const RECTANGLE_F32 * LPCRECTANGE_F32;


#pragma pack(pop, geometry2d_f32)



