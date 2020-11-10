#pragma once


inline bool shape_contains(const ::arc* parc, const ::POINT32 & point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rect r;

   if (!get_bounding_rect(r, parc))
   {

      return false;

   }

   return r.contains(point);

}


inline bool shape_contains(const ::arc* parc, const ::POINTD& point)
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rect r;

   if (!get_bounding_rect(r, parc))
   {

      return false;

   }

   return r.contains(point);

}


inline bool shape_contains(const line* pline, const POINT32 & point)
{

   return false;

}


inline bool shape_contains(const line* pline, const POINTD& point)
{

   return false;

}


inline bool shape_contains(const lined* pline, const POINT32& point)
{

   return false;

}


inline bool shape_contains(const lined* pline, const POINTD& point)
{

   return false;

}


inline bool shape_contains(const RECT32* prect, const POINT32& point)
{

   return ::rect_contains(prect, point.x, point.y);

}


inline bool shape_contains(const RECT32* prect, const POINTD& point)
{

   return ::rect_contains(prect, point.x, point.y);

}


inline bool shape_contains(const RECTD* prect, const POINT32& point)
{

   return ::rect_contains(prect, point.x, point.y);

}


inline bool shape_contains(const RECTD* prect, const POINTD& point)
{

   return ::rect_contains(prect, point.x, point.y);

}



