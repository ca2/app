#pragma once


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const lines & lines)
{

   lines.get_bounding_rectangle(rectangleBounding);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const lines & lines)
{

   ::RECTANGLE_F64 r;

   lines.get_bounding_rectangle(r);

   copy(rectangleBounding, r);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const polygon_i32 & polygon)
{

   polygon.get_bounding_rectangle(rectangleBounding);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const polygon_i32 & polygon)
{

   ::RECTANGLE_I32 r;

   polygon.get_bounding_rectangle(r);

   copy(rectangleBounding, r);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_I32 & rectangleBounding, const polygon_f64 & polygon)
{

   ::RECTANGLE_F64 r;

   polygon.get_bounding_rectangle(r);

   copy(rectangleBounding, r);

   return true;

}


inline bool get_bounding_rectangle(RECTANGLE_F64 & rectangleBounding, const polygon_f64 & polygon)
{

   polygon.get_bounding_rectangle(rectangleBounding);

   return true;

}



