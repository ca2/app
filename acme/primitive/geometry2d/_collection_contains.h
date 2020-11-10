#pragma once


inline bool shape_contains(const ::lines* plines, const POINT32& point)
{

   return false;

}


inline bool shape_contains(const ::lines* plines, const ::POINTD& point)
{

   return false;

}


inline bool shape_contains(const ::linesd* plines, const POINT32& point)
{

   return false;

}


inline bool shape_contains(const ::linesd* plines, const ::POINTD& point)
{

   return false;

}


inline bool shape_contains(const ::polygon* ppolygon, const POINT32 & point)
{

   return ppolygon->polygon_contains(point);

}
  

inline bool shape_contains(const ::polygon* ppolygon, const ::POINTD & point)
{

   return ppolygon->polygon_contains(point);

}


inline bool shape_contains(const ::polygond* ppolygon, const POINT32& point)
{

   return ppolygon->polygon_contains(point);

}


inline bool shape_contains(const ::polygond* ppolygon, const ::POINTD& point)
{

   return ppolygon->polygon_contains(point);

}



