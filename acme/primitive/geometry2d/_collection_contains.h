#pragma once


inline bool shape_contains(const ::lines* plines, const POINT_I32& point)
{

   return false;

}


inline bool shape_contains(const ::lines* plines, const ::POINT_F64& point)
{

   return false;

}


inline bool shape_contains(const ::linesd* plines, const POINT_I32& point)
{

   return false;

}


inline bool shape_contains(const ::linesd* plines, const ::POINT_F64& point)
{

   return false;

}


inline bool shape_contains(const ::polygon_i32* ppolygon, const POINT_I32 & point)
{

   return ppolygon->polygon_contains(point);

}
  

inline bool shape_contains(const ::polygon_i32* ppolygon, const ::POINT_F64 & point)
{

   return ppolygon->polygon_contains(point);

}


inline bool shape_contains(const ::polygon_f64* ppolygon, const POINT_I32& point)
{

   return ppolygon->polygon_contains(point);

}


inline bool shape_contains(const ::polygon_f64* ppolygon, const ::POINT_F64& point)
{

   return ppolygon->polygon_contains(point);

}



