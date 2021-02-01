#pragma once


inline bool get_bounding_rect(RECTANGLE_I32* prectBounding, const lines* plines)
{

   plines->get_bounding_rect(prectBounding);

   return true;
}



inline bool get_bounding_rect(RECTANGLE_F64* prectBounding, const lines* plines)
{

   ::RECTANGLE_I32 r;

   plines->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_I32* prectBounding, const linesd* plines)
{

   ::RECTANGLE_F64 r;

   plines->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_F64* prectBounding, const linesd* plines)
{

   plines->get_bounding_rect(prectBounding);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_I32* prectBounding, const polygon_i32* ppolygon)
{

   ppolygon->get_bounding_rect(prectBounding);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_F64* prectBounding, const polygon_i32* ppolygon)
{

   ::RECTANGLE_I32 r;

   ppolygon->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_I32* prectBounding, const polygon_f64* ppolygon)
{

   ::RECTANGLE_F64 r;

   ppolygon->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECTANGLE_F64* prectBounding, const polygon_f64* ppolygon)
{

   ppolygon->get_bounding_rect(prectBounding);

   return true;

}



