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


constexpr ::f128 degrees_to_radians(::f128 degrees)
{ 
   
   return degrees * πl / 180.0l; 

}


constexpr ::f64 degrees_to_radians(::f64 degrees)
{
   
   return degrees * π / 180.0; 

}


constexpr ::f32 degrees_to_radians(::f32 degrees)
{ 
   
   return degrees * πf / 180.0f; 

}


constexpr ::f128 radians_to_degrees(::f128 radians)
{
   
   return radians * 180.0l / πl;  

}


constexpr ::f64 radians_to_degrees(::f64 radians)
{
   
   return radians * 180.0 / π; 

}


constexpr ::f32 radians_to_degrees(::f32 radians)
{
   
   return radians * 180.0f / πf; 

}



