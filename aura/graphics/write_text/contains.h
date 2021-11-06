﻿#pragma once


inline bool shape_contains(const ::write_text::text_out * ptextout, const POINT_I32 & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_I32 rectangleBounding;

   if (!::get_bounding_rectangle(&rectangleBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectangleBounding, point.x, point.y);

}


inline bool shape_contains(const ::write_text::text_out* ptextout, const POINT_F64& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_F64 rectangleBounding;

   if (!::get_bounding_rectangle(&rectangleBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectangleBounding, point.x, point.y);

}


inline bool shape_contains(const ::write_text::draw_text * ptextout, const POINT_I32& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_I32 rectangleBounding;

   if (!::get_bounding_rectangle(&rectangleBounding, ptextout))
   {

      return false;

   }

   return ::rectangle_contains(&rectangleBounding, point.x, point.y);

}


inline bool shape_contains(const ::write_text::draw_text* ptextout, const POINT_F64& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::RECTANGLE_F64 rectangleBounding;

   if (!::get_bounding_rectangle(&rectangleBounding, ptextout))
   {

      return false;

   }

   return rectangle_contains(&rectangleBounding, point.x, point.y);

}



