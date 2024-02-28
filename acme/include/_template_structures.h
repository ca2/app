// Created by camilo on 2022-11-11 21:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/u32hash.h"


namespace comparison
{

constexpr int get_bool_int( bool b){return b? 1:0;}

   template < typename TYPE >
   class comparison
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;


      constexpr bool equals(const TYPE & a, const TYPE & b) const { return a == b; }
      constexpr ::std::strong_ordering order(const TYPE & a, const TYPE & b) const { return a <=> b; }


   };

template <  >
class comparison < bool >
{
public:


   using EQUALITY = for_type < bool >;
   using ORDERING = for_type < bool >;


   constexpr bool equals(bool a, bool b) const { return get_bool_int(a) == get_bool_int(b); }
   constexpr ::std::strong_ordering order(bool a, bool b) const { return get_bool_int(a) <=> get_bool_int(b); }


};


   template < primitive_fundamental TYPE >
   class comparison < TYPE >
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;


      constexpr bool equals(TYPE a, TYPE b) const { return a == b; }
      constexpr ::std::strong_ordering order(TYPE a, TYPE b) const { return a <=> b; }


   };


   //template < primitive_character CHARACTER >
   //class comparison :
   //   public comparison < CHARACTER >
   //{
   //public:
   //
   //
   //   //using EQUALITY_TRAITS = EQUALITY_TRAITS_TAG;
   //   //using COMPARISON_TRAITS = COMPARISON_TRAITS_TAG;
   //
   //
   //   //constexpr bool equals(CHARACTER a, CHARACTER b) const { return a == b; }
   //   //constexpr ::std::strong_ordering compare(CHARACTER a, CHARACTER b) const { return a <=> b; }
   //
   //
   //};




} // namespace comparison



