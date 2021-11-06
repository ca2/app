#pragma once


//inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const lines* plines)
//{
//
//   plines->get_bounding_rectangle(prectangleBounding);
//
//   return true;
//}



inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const lines* plines)
{

//   ::RECTANGLE_I32 r;

  // plines->get_bounding_rectangle(&r);

   //copy(prectangleBounding, &r);
   
   plines->get_bounding_rectangle(prectangleBounding);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const lines* plines)
{

   ::RECTANGLE_F64 r;

   plines->get_bounding_rectangle(&r);

   copy(prectangleBounding, &r);

   return true;

}


//inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const lines* plines)
//{
//
//   plines->get_bounding_rectangle(prectangleBounding);
//
//   return true;
//
//}
//

inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const polygon_i32* ppolygon)
{

   ppolygon->get_bounding_rectangle(prectangleBounding);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const polygon_i32* ppolygon)
{

   ::RECTANGLE_I32 r;

   ppolygon->get_bounding_rectangle(&r);

   copy(prectangleBounding, &r);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32* prectangleBounding, const polygon_f64* ppolygon)
{

   ::RECTANGLE_F64 r;

   ppolygon->get_bounding_rectangle(&r);

   copy(prectangleBounding, &r);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64* prectangleBounding, const polygon_f64* ppolygon)
{

   ppolygon->get_bounding_rectangle(prectangleBounding);

   return true;

}



