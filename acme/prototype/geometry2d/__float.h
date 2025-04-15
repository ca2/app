#pragma once


//#pragma pack(push, geometry2d_float, 1)


struct FLOAT_SIZE
{

   float cx;
   float cy;

};


typedef const FLOAT_SIZE * LPCFLOAT_SIZE;

struct FLOAT_POINT
{

   float x;
   float y;

};


typedef const FLOAT_POINT * LPCFLOAT_POINT;


struct FLOAT_RECTANGLE
{

   float left;
   float top;
   float right;
   float bottom;

};


typedef const FLOAT_RECTANGLE * LPCRECTANGE_F32;


//#pragma pack(pop, geometry2d_float)



