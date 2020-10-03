#pragma once



template<> inline uptr uptr_hash<point>(point key)
{

   return key.x | key.y;

}


template<> inline uptr uptr_hash<size>(size key)
{

   return key.cx | key.cy;

}


template<> inline uptr uptr_hash<rect>(rect key)
{

   return key.left | key.top | key.bottom | key.right;

}





template < >
inline uptr uptr_hash(const ::size& size)
{
   return size.cy << 16 | size.cx;
}


template < >
inline uptr uptr_hash(const ::point& point)
{
   return point.y << 16 | point.x;
}


template < >
inline uptr uptr_hash(const ::rect& rect)
{
   return rect.top << 24 | rect.left << 16 | rect.bottom << 8 | rect.right;
}


#include "shape.h"



