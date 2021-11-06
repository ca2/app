#pragma once




template < typename T >
inline c_number < T > & c_number < T >::from(const ::string & str)
{

   ::from_string(m_number, str);

   return *this;

}



template < typename TYPE >
inline TYPE* __random_bytes(TYPE* p, memsize s)
{
   generate_random_bytes(p, s);
   return p;
}


template < typename TYPE >
inline TYPE& __random(TYPE& t)
{

   return *__random_bytes(&t, sizeof(TYPE));

}


template < typename TYPE >
inline TYPE __random()
{

   TYPE t;

   __random(t);

   return t;

}



template < primitive_floating FLOATING1, primitive_floating FLOATING2, primitive_floating FLOATING_RESULT >
inline FLOATING_RESULT __random(FLOATING1 f1, FLOATING2 f2)
{

   if (f1 == f2) return f1;

   auto fMin = minimum(f1, f2);

   auto fMax = maximum(f1, f2);

   FLOATING_RESULT dRange = fMax - fMin;

   u64 u;

   __random(u);

   return (FLOATING_RESULT)(((FLOATING_RESULT)u * dRange) / (FLOATING_RESULT)MAXU64) + fMin;

}


//inline double __random(double d1, double d2)
//{
//
//   if (d1 == d2) return d1;
//
//   auto dMin = minimum(d1, d2);
//
//   auto dMax = maximum(d1, d2);
//
//   auto dRange = dMax - dMin;
//
//   u64 u;
//
//   __random(u);
//
//   return (((double)u * dRange) / (double)MAXU64) + dMin;
//
//}


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3 >
INTEGRAL3 __random(INTEGRAL1 i1, INTEGRAL2 i2)
{

   if (i1 == i2) return i1;

   auto iMin = minimum(i1, i2);

   auto iMax = maximum(i1, i2);

   auto iRange = iMax - iMin;

   u64 u;

   __random(u);

   return (INTEGRAL3)((u % ((INTEGRAL3)iRange + 1)) + (INTEGRAL3)iMin);

}


//inline i64 __random(i64 i1, i64 i2)
//{
//   return __random_int(i1, i2);
//}


//inline i32 __random(i32 i1, i32 i2)
//{
//   return __random_int(i1, i2);
//}



//inline i64 __random(i32 i1, i64 i2)
//{
//   return __random_int((i64) i1, i2);
//}


//inline i64 __random(i64 i1, i32 i2)
//{
//   return __random_int(i1, (i64)i2);
//}






template < typename T1, typename T2 >
inline bool clip_convert(T1& t1, const T2& t2)
{

   if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
   {

      t1 = ::numeric_info < T1 >::get_maximum_value();

      output_debug_string("\nclip::assign maximum clipped");

      return false;

   }

   if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
   {

      t1 = ::numeric_info < T1 >::get_minimum_value();

      output_debug_string("\nclip::assign minimum clipped");

      return false;

   }

   t1 = (T1)t2;

   return true;

}


template < typename T1, typename T2 >
inline T1 clip_convert(const T2& t2)
{

   if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
   {

      output_debug_string("\nclip::convert maximum clipped");

      return ::numeric_info < T1 >::get_maximum_value();

   }

   if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
   {

      output_debug_string("\nclip::convert minimum clipped");

      return ::numeric_info < T1 >::get_minimum_value();

   }

   return (T1)t2;

}


template < typename T1, typename T2 >
inline bool clip_convert_add(T1& t1, const T2& t2)
{

   auto t = t1 + t2;

   if (!convert(t1, t))
   {

      output_debug_string(" (convert_add)");

   }

   return true;

}


template < typename T1, typename T2 >
inline bool clip_convert_difference(T1& t1, const T2& t2)
{

   auto t = t1 - t2;

   return clip_convert(t1, t);

}


template < typename T1, typename T2 >
inline bool clip_convert_multiply(T1& t1, const T2& t2)
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
inline bool clip_convert_divide(T1& t1, const T2& t2)
{

   auto t = t1 / t2;

   if (!clip_convert(t1, t))
   {

      output_debug_string(" (convert_divide)");

   }

   return true;

}


template < typename TMIN, typename TMAX, typename T  >
inline T& clip(const TMIN& minimum, const TMAX& maximum, T& t)
{
   if (t < minimum)
   {

      t = (T)minimum;

   }
   else if (t > maximum)
   {

      t = (T)maximum;

   }

   return t;

}



