#pragma once


#include <limits.h>


template < primitive_integral INTEGRAL >
inline bool fits_i32(INTEGRAL i)
{

   if (::comparison::comparison2 < INTEGRAL, int >().order(i, I32_MAXIMUM) > 0)
   {

      return false;

   }

   if (::comparison::comparison2 < INTEGRAL, int >().order(i, I32_MINIMUM) < 0)
   {

      return false;

   }

   return true;

}



