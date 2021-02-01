#pragma once


#include <limits.h>


template < primitive_integral INTEGRAL >
inline bool fits_i32(INTEGRAL i)
{

   if (__gt(i, MAXI32))
   {

      return false;

   }


   if (__lt(i, MINI32))
   {

      return false;

   }

   return true;

}



