#pragma once


inline bool shape_contains(const ::lines & lines, const POINT_I32& point)
{

   return false;

}


inline bool shape_contains(const ::lines & lines, const ::POINT_F64& point)
{

   return false;

}


//inline bool shape_contains(const ::linesd* plines, const POINT_I32& point)
//{
//
//   return false;
//
//}
//
//
//inline bool shape_contains(const ::linesd* plines, const ::POINT_F64& point)
//{
//
//   return false;
//
//}


inline bool shape_contains(const ::polygon_i32 & polygon, const POINT_I32 & point)
{

   return polygon.polygon_contains(point);

}
  

inline bool shape_contains(const ::polygon_i32 & polygon, const ::POINT_F64 & point)
{

   return polygon.polygon_contains(point);

}


inline bool shape_contains(const ::polygon_f64 & polygon, const POINT_I32& point)
{

   return polygon.polygon_contains(point);

}


inline bool shape_contains(const ::polygon_f64 & polygon, const ::POINT_F64& point)
{

   return polygon.polygon_contains(point);

}



