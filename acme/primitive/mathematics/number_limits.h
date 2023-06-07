#pragma once


#include <limits.h>


template < primitive_integral INTEGRAL >
inline bool fits_i32(INTEGRAL i)
{

   if (::comparison::comparison2 < INTEGRAL, int >().order(i, MAXI32) > 0)
   {

      return false;

   }

   if (::comparison::comparison2 < INTEGRAL, int >().order(i, MINI32) < 0)
   {

      return false;

   }

   return true;

}



