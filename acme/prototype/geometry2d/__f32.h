#pragma once


//#pragma pack(push, geometry2d_f32, 1)


struct FLOAT_SIZE
{

   ::f32 cx;
   ::f32 cy;

};


typedef const FLOAT_SIZE * LPCFLOAT_SIZE;

struct FLOAT_POINT
{

   ::f32 x;
   ::f32 y;

};


typedef const FLOAT_POINT * LPCFLOAT_POINT;


struct FLOAT_RECTANGLE
{

   ::f32 left;
   ::f32 top;
   ::f32 right;
   ::f32 bottom;

};


typedef const FLOAT_RECTANGLE * LPCRECTANGE_F32;


//#pragma pack(pop, geometry2d_f32)



