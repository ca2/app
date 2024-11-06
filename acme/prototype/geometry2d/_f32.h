#pragma once


#pragma pack(push, geometry2d_f32, 1)


struct SIZE_F32
{

   float cx;
   float cy;

};


typedef const SIZE_F32 * LPCSIZE_F32;

struct POINT_F32
{

   float x;
   float y;

};


typedef const POINT_F32 * LPCPOINT_F32;


struct RECTANGLE_F32
{

   float left;
   float top;
   float right;
   float bottom;

};


typedef const RECTANGLE_F32 * LPCRECTANGE_F32;


#pragma pack(pop, geometry2d_f32)



