// Created by camilo on 2025-11-13 22:44 <3ThomasBorregaardSørensen!!
#pragma once


namespace geometry
{


   template < typename TYPE >
   inline TYPE clamp(TYPE n, TYPE nMin, TYPE nMax)
   {

      if (n < nMin)
         return nMin;

      if (n > nMax)
         return nMax;

      return n;

   }


} // namespace geometry


constexpr long double degrees_to_radians(long double degrees)
{ 
   
   return degrees * πl / 180.0l; 

}


constexpr double degrees_to_radians(double degrees)
{
   
   return degrees * π / 180.0; 

}


constexpr float degrees_to_radians(float degrees)
{ 
   
   return degrees * πf / 180.0f; 

}


constexpr long double radians_to_degrees(long double radians)
{
   
   return radians * 180.0l / πl;  

}


constexpr double radians_to_degrees(double radians)
{
   
   return radians * 180.0 / π; 

}


constexpr float radians_to_degrees(float radians)
{
   
   return radians * 180.0f / πf; 

}



