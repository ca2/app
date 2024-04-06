#pragma once


inline bool shape_contains(const ::write_text::text_out & textout, const ::point_i32 & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_i32 rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}


inline bool shape_contains(const ::write_text::text_out & textout, const ::point_f64& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_f64 rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}


inline bool shape_contains(const ::write_text::draw_text & textout, const ::point_i32& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_i32 rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}


inline bool shape_contains(const ::write_text::draw_text & textout, const ::point_f64& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_f64 rectangleBounding;

   if (!::get_bounding_box(rectangleBounding, textout))
   {

      return false;

   }

   return rectangleBounding.contains(point);

}



