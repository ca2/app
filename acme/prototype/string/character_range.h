// Created by camilo on 2025-04-17 09:37 <3ThomasBorregaardSorensen!!
#pragma once
#include <format>

#include "acme/prototype/collection/range.h"


template < typename ITERATOR_TYPE >
class character_range :
   public ::range < ITERATOR_TYPE >
{
public:

   using THIS_CHARACTER_RANGE = character_range < ITERATOR_TYPE >;
   using RAW_CHARACTER_RANGE = THIS_CHARACTER_RANGE;


   using BASE_RANGE = ::range < ITERATOR_TYPE >;
   using BASE_RAW_RANGE = character_range < ITERATOR_TYPE >;

   using this_iterator = typename BASE_RANGE::this_iterator;


   using BASE_RANGE::BASE_RANGE;

   character_range(const character_range& characterrange) :
      BASE_RANGE(characterrange) { }
   character_range(character_range&& characterrange) :
      BASE_RANGE(::transfer(characterrange)) {
   }

   template < typename TYPED_RANGE >
   character_range(const TYPED_RANGE& range) requires
      (typed_range<this_iterator>
         && !::std::is_convertible<TYPED_RANGE, character_range >::value) :
      base_array(range.begin(), range.end())
   {
   }


   character_range& operator=(const character_range& range)
   {
      BASE_RANGE::operator=(range);
      return *this;
   }


   character_range& operator=(character_range&& range) {
      BASE_RANGE::operator=(::transfer(range));
      return *this;
   }

};




template <typename ITERATOR_TYPE>
struct std::formatter<character_range<ITERATOR_TYPE>> : std::formatter<std::string_view>
{
   template <typename FormatContext>
   auto format(const character_range<ITERATOR_TYPE>& s, FormatContext& ctx) const
   {
      return std::formatter<std::string_view>::format(
         std::string_view(s.begin(), s.size()), ctx);
   }
};



