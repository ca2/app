#pragma once


inline bool shape_contains(const ::text_out * ptextout, const POINT_I32 & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_I32 rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::text_out* ptextout, const POINT_F64& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_F64 rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::draw_text * ptextout, const POINT_I32& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_I32 rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::draw_text* ptextout, const POINT_F64& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_F64 rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return rectangle_contains(&rectBounding, point.x, point.y);

}



