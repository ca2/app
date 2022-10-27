//
// Created by camilo on 2022-10-23 09:16 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "numeric_info.h"


namespace numeric // (?acme or ace, when I am going to introduce ace, on in the minimum insertion ace static library)
{


   template <typename T>
   int sgn(T val)
   {

      return (::numeric_info < T >::null() < val) - (val < ::numeric_info < T >::null());

   }


   template <typename T>
   int nzsgn(T val)
   {
      // val < 0 -> -1
      // val >= 0 -> 1
      return (::numeric_info < T >::null() <= val) - (val < ::numeric_info < T >::null());
   }


   template <typename T>
   T & set_maximum(T & payload)
   {

      return payload = ::numeric_info < T >::maximum();

   }

   template <typename T>
   T & set_minimum(T & payload)
   {

      return payload = ::numeric_info < T >::minimum();

   }


   template <typename T>
   T & set_null(T & payload)
   {

      return payload = ::numeric_info < T >::null();

   }


   template <typename T>
   T & set_unitary(T & payload)
   {

      return payload = ::numeric_info < T >::unitary();

   }


   template <typename T>
   bool is_maximum(const T & payload)
   {

      return payload == ::numeric_info < T >::maximum();

   }

   template <typename T>
   bool is_minimum(const T & payload)
   {

      return payload == ::numeric_info < T >::minimum();

   }


   template <typename T>
   bool is_null(const T & payload)
   {

      return payload == ::numeric_info < T >::null();

   }


   template <typename T>
   bool is_unitary(const T & payload)
   {

      return payload == ::numeric_info < T >::unitary();

   }


} // namespace numeric



