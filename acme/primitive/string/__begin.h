#pragma once


#include "c/_.h"
#include "sz/_.h"
//#include <assert.h>

namespace comparison
{


   template < typename TYPE >
   class case_insensitive
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;

      constexpr bool equals(const TYPE & a, const TYPE & b) const { return a.case_insensitive_equals(b); }
      constexpr ::std::strong_ordering order(const TYPE & a, const TYPE & b) const { return a.case_insensitive_order(b); }


   };


   template < primitive_character CHARACTER >
   class case_insensitive < CHARACTER >
   {
   public:


      using EQUALITY = for_type < CHARACTER >;
      using ORDERING = for_type < CHARACTER >;

      constexpr bool equals(CHARACTER a, CHARACTER b) const { return character_tolower(a) == character_tolower(b); }
      constexpr ::std::strong_ordering order(CHARACTER a, CHARACTER b) const { return character_tolower(a) <=> character_tolower(b); }


   };


} // namespace comparison



//template < primitive_character CHARACTER >
//constexpr bool ::comparison::comparison(CHARACTER a, CHARACTER b)
//{
//
//   return a == b;
//
//}



//template < primitive_character CHARACTER >
//constexpr ::std::strong_ordering compare_character(CHARACTER a, CHARACTER b)
//{
//
//   return a <=> b;
//
//}

//
//template < primitive_character CHARACTER >
//constexpr bool equals_character_ci(CHARACTER a, CHARACTER b)
//{
//
//   return character_tolower(a) == character_tolower(b);
//
//}
//
//
//
//template < primitive_character CHARACTER >
//constexpr ::std::strong_ordering compare_character_ci(CHARACTER a, CHARACTER b)
//{ 
//   
//   return character_tolower(a) <=> character_tolower(b); 
//
//}



constexpr char __digit(int digit)
{

   return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[digit];

}


constexpr u32 decode_utf16_pair(u16 * units);




