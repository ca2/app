// From string_range.h by camilo on 2023-02-20 20:25 <3ThomasBorregaardSorensen!!
#pragma once


#include "string_range.h"


template<typename ITERATOR_TYPE>
class mutable_string_range :
        //public ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >
        //public ::array_range < ::range < ITERATOR_TYPE > > >
public ::const_string_range<ITERATOR_TYPE> {
public:
   
   
   //using BASE_RANGE = ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >;
   
   using BASE_RANGE = ::const_string_range<ITERATOR_TYPE>;
   
   using THIS_RANGE = ::mutable_string_range<ITERATOR_TYPE>;
   
   using STRING_RANGE = ::string_range < BASE_RANGE >;
   
   using ITEM_POINTER = get_type_item_pointer<ITERATOR_TYPE>;
   using ITEM = non_const<dereference<ITEM_POINTER> >;
   using CHARACTER = ITEM;
   
   
   using this_iterator = typename BASE_RANGE::this_iterator;
   using iterator = typename BASE_RANGE::iterator;
   using const_iterator = typename BASE_RANGE::const_iterator;
   
   using STRING_BASE = ::string_base< const_iterator >;
   

   using THIS_RAW_RANGE = typename BASE_RANGE::THIS_RAW_RANGE;
   using RAW_RANGE = typename BASE_RANGE::RAW_RANGE;
   using CONST_RAW_RANGE = typename BASE_RANGE::CONST_RAW_RANGE;
   
   //using ITEM_POINTER =  typename get_type_item_pointer < this_iterator >::type;
   
   //using ITEM = non_const < dereference < ITEM_POINTER > >;
   
   using SCOPED_STRING = scoped_string_base<ITERATOR_TYPE>;
   
   
   using ARG_ITEM = typename BASE_RANGE::ARG_ITEM;
   
   
   template<::std::size_t count>
   constexpr mutable_string_range(const ITEM(&array)[count]) : BASE_RANGE(array, array[count - 1] == 0 ? count - 1 : count) {}
   
   template<primitive_integral INTEGRAL>
   constexpr mutable_string_range(const_iterator begin, INTEGRAL count) : BASE_RANGE((this_iterator) begin,
                                                                             (this_iterator) (begin + count)) {}
   
   mutable_string_range(no_initialize_t) : BASE_RANGE(no_initialize_t{}) {}
   
   mutable_string_range(nullptr_t) : BASE_RANGE(nullptr) {}
   
   mutable_string_range() {}
   
   template<typed_range<iterator> RANGE>
   explicit mutable_string_range(const RANGE &range) : BASE_RANGE(range) {}
   
   template<typed_range<const_iterator> RANGE>
   explicit mutable_string_range(const RANGE &range) : BASE_RANGE(range) {}
   
   mutable_string_range(THIS_RANGE &range) : BASE_RANGE(range) {}
   
   mutable_string_range(THIS_RANGE &&range) : BASE_RANGE(::transfer(range)) {}
   
   mutable_string_range(this_iterator begin, this_iterator end) : BASE_RANGE(begin, end) {}
   
   explicit mutable_string_range(const ::block &block);
   
   explicit mutable_string_range(ITERATOR_TYPE psz) : STRING_RANGE(psz, 0, string_safe_length(psz)) {}
   
   mutable_string_range(ITERATOR_TYPE psz, character_count len) : STRING_RANGE(psz, 0, len) {}
   
   //string_range(const CHARACTER * start, const CHARACTER * end) : BASE_RANGE(start, end) {}
   
   mutable_string_range(ITERATOR_TYPE psz, character_count start, character_count count) : STRING_RANGE(
                                                                                   ::_start_count_string_range(psz, start, count)) {}
   
   
   
   
      ///
   /// similar with _tcscpy with escape process
   /// /p escape - will be escape character
   /// Return :
   /// Coder    Date                      Desc
   /// bro      2002-10-29
   void escape_copy(char escape, const ::const_ansi_range & rangeSource);

   
};












using mutable_ansi_range = ::mutable_string_range< ::ansi_character *>;
using mutable_wd16_range = ::mutable_string_range< ::wd16_character *>;
using mutable_wd32_range = ::mutable_string_range< ::wd32_character *>;
using mutable_wide_range = ::mutable_string_range< ::wide_character *>;


template<primitive_character CHARACTER>
inline const CHARACTER *
_unicode_find_first_character_in(const ::range<CHARACTER> &block, const ::range<CHARACTER> &blockBlock) noexcept {

   auto p = block.data();

   auto pEnd = p + block.size();

   auto pBlock = blockBlock.data();

   auto pBlockEnd = pBlock + blockBlock.size();

   int len1;

   int len2;

   while (p < pEnd) {

      auto pBlockScan = pBlock;

      auto index = unicode_index_length(p, len1);

      do {

         if (index == unicode_index_length(pBlockScan, len2)) {

            return true;

         }

         pBlockScan += len2;

      } while (pBlockScan < pBlockEnd);

      p += len1;

   }

   return p;

}


template<primitive_character CHARACTER>
inline const CHARACTER *
unicode_find_first_character_in(const ::range<CHARACTER> &block, const ::range<CHARACTER> &blockBlock) noexcept {

   CHARACTER *p;

   if (_string_find_first_character_in_prefix(p, block, blockBlock)) {

      return p;

   }

   return _unicode_find_first_character_in(block, blockBlock);

}


template<primitive_character CHARACTER>
inline const CHARACTER *
_unicode_rear_find_first_character_in(const ::range<CHARACTER> &block, const ::range<CHARACTER> &blockBlock) noexcept {

   auto p = block.data();

   auto pEnd = p + block.size();

   auto pBlock = blockBlock.data();

   auto pBlockEnd = pBlock + blockBlock.size();

   //int len1;

   int len2;

   while (pEnd < p) {

      auto pBlockScan = pBlock;

      auto pPrior = unicode_prior(pEnd, p);

      auto index = unicode_index(pPrior);

      do {

         if (index == unicode_index_length(pBlockScan, len2)) {

            return true;

         }

         pBlockScan += len2;

      } while (pBlockScan < pBlockEnd);

      pEnd = pPrior;

   }

   return pEnd;

}


template<primitive_character CHARACTER>
inline const CHARACTER *
unicode_rear_find_first_character_in(const ::range<CHARACTER> &block, const ::range<CHARACTER> &blockBlock) noexcept {

   CHARACTER *p;

   if (_string_rear_find_first_character_in_prefix(p, block, blockBlock)) {

      return p;

   }

   return _unicode_rear_find_first_character_in(block, blockBlock);

}


using ansi_range = ::string_range< const ::ansi_character * >;
using wd16_range = ::string_range< const ::wd16_character * >;
using wd32_range = ::string_range< const ::wd32_character * >;


template<primitive_character CHARACTER>
inline ::hash32 _string_range_unsigned_int_hash(::string_range<const CHARACTER *> range) {

   if (range.is_empty()) {

      return {0};

   }

   unsigned int uHash = 0;

   while (range.m_begin < range.m_end) uHash = (uHash << 5) + *(range.m_begin++);

   return {uHash};

}


//inline ::hash32 as_hash32(const_ansi_range range)
//{
//
//   return _string_range_unsigned_int_hash((::string_range<const ::ansi_character *>) range);
//
//}
//
//
//inline ::hash32 as_hash32(const_wd16_range range)
//{
//
//   return _string_range_unsigned_int_hash((::string_range<const ::wd16_character *>) range);
//
//}
//
//
//inline ::hash32 as_hash32(const_wd32_range range)
//{
//
//   return _string_range_unsigned_int_hash<::wd32_character>((::string_range<const ::wd32_character *>) range);
//
//}


template<primitive_character CHARACTER>
constexpr ::string_range<const CHARACTER *> _string_range(const CHARACTER *psz) {

   return {psz, psz + string_safe_length(psz)};

}


template<primitive_character CHARACTER>
constexpr ::string_range<const CHARACTER *>
_start_count_string_range(const CHARACTER *psz, memsize start, memsize count) {

   auto pend = psz + string_safe_length(psz);

   return {
           ::clipped_add(psz, start, psz, pend),
           ((count >= 0) ? ::clipped_add(psz, start + count, psz, pend) :
            ::clipped_add(pend, count, psz, pend))};

}




template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE > ::STRING_RANGE const_string_range < ITERATOR_TYPE > ::operator()(character_count start, character_count count) const {

   return ::_start_count_range(STRING_RANGE(*this), start, count);

}

template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE > ::STRING_RANGE const_string_range < ITERATOR_TYPE > ::operator()(character_count start, const_iterator end) const {

   return ::_start_end_range(STRING_RANGE(*this), start, end);

}


template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE > ::STRING_RANGE const_string_range < ITERATOR_TYPE > ::operator()(const_iterator start) const {

   return STRING_RANGE(start, this->end());

}


template < typename ITERATOR_TYPE >
template < primitive_integral START >
inline typename const_string_range < ITERATOR_TYPE > ::STRING_RANGE const_string_range < ITERATOR_TYPE > ::operator()(START start) const {

   return STRING_RANGE(this->begin() + start, this->end());

}


template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE > ::STRING_RANGE const_string_range < ITERATOR_TYPE > ::operator()() const {

   return STRING_RANGE(*this);

}


