#pragma once


namespace comparison
{


   template < typename T >
   inline T abs(const T& t)
   {

      return t >= (T)0 ? t : -t;

   }


} // namespace comparison



