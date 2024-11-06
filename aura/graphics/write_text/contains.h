#pragma once


inline bool shape_contains(const ::write_text::text_out & textout, const ::int_point & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::int_rectangle rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}


inline bool shape_contains(const ::write_text::text_out & textout, const ::double_point& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::double_rectangle rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}


inline bool shape_contains(const ::write_text::draw_text & textout, const ::int_point& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::int_rectangle rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}


inline bool shape_contains(const ::write_text::draw_text & textout, const ::double_point& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::double_rectangle rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}



