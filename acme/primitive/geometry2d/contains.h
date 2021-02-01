#pragma once


template < primitive_point POINT >
inline bool shape_contains(const ::arc* parc, const POINT & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_i32 r;

   if (!get_bounding_rect(r, parc))
   {

      return false;

   }

   return r.contains(point);

}


template < primitive_point POINT >
inline bool shape_contains(const lined* pline, const POINT & point)
{

   return false;

}


template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline bool shape_contains(const RECTANGLE * prectangle, const POINT & point)
{

   return ::rectangle_contains(prectangle, point.x, point.y);

}




