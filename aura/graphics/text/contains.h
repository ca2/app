#pragma once


inline bool shape_contains(const ::text_out * ptextout, const POINT32 & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECT32 rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::text_out* ptextout, const POINTD& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTD rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::draw_text * ptextout, const POINT32& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECT32 rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::draw_text* ptextout, const POINTD& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTD rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return rectangle_contains(&rectBounding, point.x, point.y);

}



