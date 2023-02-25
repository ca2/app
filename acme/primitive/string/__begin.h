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


constexpr int_bool utf16_is_1st_surrogate(::wd16_character _1stSurrogateCandidate) { return (_1stSurrogateCandidate & 0xfc00) == 0xd800; } // Sober Surrogay (Told Hi)
constexpr int_bool utf16_is_2nd_surrogate(::wd16_character _2ndSurrogateCandidate) { return (_2ndSurrogateCandidate & 0xfc00) == 0xdc00; } // Marginal Surro-G (Told Lo, but much more drunk)
constexpr int_bool utf16_is_surrogate(::wd16_character uc) { return utf16_is_1st_surrogate(uc) || utf16_is_2nd_surrogate(uc); }
constexpr int_bool utf32_is_surrogated(u32 character) { return 0x10000 <= character && character <= 0x10FFFF; }
constexpr u32 decode_utf16_pair(u16* units)
{
   u32 code;
   ASSERT(utf16_is_1st_surrogate(units[0]));
   ASSERT(utf16_is_2nd_surrogate(units[1]));
   code = 0x10000;
   code += (units[0] & 0x03FF) << 10;
   code += (units[1] & 0x03FF);
   return code;
}
constexpr ::wd32_character utf16_surrogate_to_utf32(::wd16_character _1stSurrogateCandidate, ::wd16_character _2ndSurrogateCandidate) { return (_1stSurrogateCandidate << 10) + _2ndSurrogateCandidate - 0x35fdc00; }





