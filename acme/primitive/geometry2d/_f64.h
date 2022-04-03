#pragma once


#pragma pack(push, geometry2d_f64, 1)


struct SIZE_F64
{

   ::f64 cx;
   ::f64 cy;

};


typedef const SIZE_F64 * LPCSIZE_F64;

struct POINT_F64
{

   ::f64 x;
   ::f64 y;

};


typedef const POINT_F64 * LPCPOINT_F64;


struct RECTANGLE_F64
{

   ::f64 left;
   ::f64 top;
   ::f64 right;
   ::f64 bottom;

};


typedef const RECTANGLE_F64 * LPCRECTANGE_F64;


#pragma pack(pop, geometry2d_f64)


inline bool is_same(const POINT_F64 & p1, const POINT_F64 & p2, double dTolerance)
{
   
   return is_same(p1.x, p2.x, dTolerance) && is_same(p1.y, p2.y, dTolerance);
   
}


inline bool is_different(const POINT_F64 & p1, const POINT_F64 & p2, double dTolerance)
{
   
   return !is_same(p1, p2, dTolerance);
   
}
