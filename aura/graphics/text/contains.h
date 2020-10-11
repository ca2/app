#pragma once


inline bool shape_contains(const ::text_out * ptextout, const POINT & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECT rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rect_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::text_out* ptextout, const POINTD& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTD rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rect_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::draw_text * ptextout, const POINT& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECT rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return ::rect_contains(&rectBounding, point.x, point.y);

}


inline bool shape_contains(const ::draw_text* ptextout, const POINTD& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTD rectBounding;

   if (!::get_bounding_rect(&rectBounding, ptextout))
   {

      return false;

   }

   return rect_contains(&rectBounding, point.x, point.y);

}



