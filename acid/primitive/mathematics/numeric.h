//
// as numeric Created by camilo on 2022-10-23 09:16 <3ThomasBorregaardSorensen!!
//
// as numerics Created by camilo on 2023-06-14 20:45 <3ThomasBorregaardSorensen!!
#pragma once


#include "numeric_info.h"


namespace numeric // (?acid or acid, when I am going to introduce acid, on in the minimum insertion acid static library)
{


   template <typename T>
   constexpr int sign(T val)
   {

      return ((val > ::numeric_info < T >::null()) ? 1 : 0)
         - ((val < ::numeric_info < T >::null()) ? 1 : 0);

   }


   template <typename T>
   int non_zero_sign(T val)
   {
      // val < 0 -> -1
      // val >= 0 -> 1
      return (::numeric_info < T >::null() <= val) - (val < ::numeric_info < T >::null());
   }


   template <typename T>
   T& set_maximum(T& payload)
   {

      return payload = ::numeric_info < T >::maximum();

   }

   template <typename T>
   T& set_minimum(T& payload)
   {

      return payload = ::numeric_info < T >::minimum();

   }


   template <typename T>
   T& set_null(T& payload)
   {

      return payload = ::numeric_info < T >::null();

   }


   template <typename T>
   T& set_unitary(T& payload)
   {

      return payload = ::numeric_info < T >::unitary();

   }


   template <typename T>
   bool is_maximum(const T& payload)
   {

      return payload == ::numeric_info < T >::maximum();

   }

   template <typename T>
   bool is_minimum(const T& payload)
   {

      return payload == ::numeric_info < T >::minimum();

   }


   template <typename T>
   bool is_null(const T& payload)
   {

      return payload == ::numeric_info < T >::null();

   }


   template <typename T>
   bool is_unitary(const T& payload)
   {

      return payload == ::numeric_info < T >::unitary();

   }


   inline ::f64 floor(::f64 f)
   {

      return ::floor(f);

   }


   inline ::f32 floor(::f32 f)
   {

      return ::floorf(f);

   }


   inline ::f64 ceil(::f64 f)
   {

      return ::ceil(f);

   }


   inline ::f32 ceil(::f32 f)
   {

      return ::ceilf(f);

   }


} // namespace numeric



