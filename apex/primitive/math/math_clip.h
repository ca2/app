#pragma once


template < typename T1, typename T2 >
inline bool clip_convert(T1 & t1, const T2 & t2)
{

   if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
   {

      t1 = ::numeric_info < T1 >::get_maximum_value();

      output_debug_string("\nclip::assign max clipped");

      return false;

   }

   if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
   {

      t1 = ::numeric_info < T1 >::get_minimum_value();

      output_debug_string("\nclip::assign min clipped");

      return false;

   }

   t1 = (T1)t2;

   return true;

}


template < typename T1, typename T2 >
inline T1 clip_convert(const T2 & t2)
{

   if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
   {

      output_debug_string("\nclip::convert max clipped");

      return ::numeric_info < T1 >::get_maximum_value();

   }

   if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
   {

      output_debug_string("\nclip::convert min clipped");

      return ::numeric_info < T1 >::get_minimum_value();

   }

   return (T1) t2;

}


template < typename T1, typename T2 >
inline bool clip_convert_add(T1 & t1, const T2 & t2)
{

   auto t = t1 + t2;

   if (!convert(t1, t))
   {

      output_debug_string(" (convert_add)");

   }

   return true;

}


template < typename T1, typename T2 >
inline bool clip_convert_difference(T1 & t1, const T2 & t2)
{

   auto t = t1 - t2;

   return clip_convert(t1, t);

}


template < typename T1, typename T2 >
inline bool clip_convert_multiply(T1 & t1, const T2 & t2)
{

   auto t = t2 * t1;

   if (!clip_convert(t1, t))
   {

      output_debug_string(" (convert_multiply)");

   }

   return true;

}


// division by zero protection isn't this function's current responsability and maybe never should be
template < typename T1, typename T2 >
inline bool clip_convert_divide(T1 & t1, const T2 & t2)
{

   auto t = t1 / t2;

   if (!clip_convert(t1, t))
   {

      output_debug_string(" (convert_divide)");

   }

   return true;

}


template < typename TMIN, typename TMAX, typename T  >
inline T & clip(const TMIN & min, const TMAX & max, T & t)
{
   if (t < min)
   {

      t = (T) min;

   }
   else if (t > max)
   {

      t = (T)max;

   }

   return t;

}