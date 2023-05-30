#pragma once


template < primitive_number LINES_NUMBER, primitive_number POINT_NUMBER >
inline bool shape_contains(const ::lines_base < LINES_NUMBER > & lines, const ::point_type < POINT_NUMBER > & point)
{

   return false;

}


//inline bool shape_contains(const ::lines & lines, const ::point_f64& point)
//{
//
//   return false;
//
//}
//

//inline bool shape_contains(const ::linesd* plines, const ::point_i32& point)
//{
//
//   return false;
//
//}
//
//
//inline bool shape_contains(const ::linesd* plines, const ::point_f64& point)
//{
//
//   return false;
//
//}


inline bool shape_contains(const ::polygon_i32 & polygon, const ::point_i32 & point)
{

   return polygon.polygon_contains(point);

}
  

inline bool shape_contains(const ::polygon_i32 & polygon, const ::point_f64 & point)
{

   return polygon.polygon_contains(point);

}


inline bool shape_contains(const ::polygon_f64 & polygon, const ::point_i32& point)
{

   return polygon.polygon_contains(point);

}


inline bool shape_contains(const ::polygon_f64 & polygon, const ::point_f64& point)
{

   return polygon.polygon_contains(point);

}



