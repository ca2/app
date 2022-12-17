// Created by camilo on 2022-12-07 23:59 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/collection/array_range.h"
#include "acme/primitive/collection/comparable_eq_range.h"
#include "acme/primitive/collection/comparable_range.h"
#include "acme/primitive/collection/null_terminated_iterator.h"
#include "acme/primitive/collection/null_terminated_range.h"


template < typename ITERATOR_TYPE >
class string_range : 
   public ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >
{
public:
   

   using BASE_RANGE = ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >;

   using THIS_RANGE = ::string_range < ITERATOR_TYPE >;



   using this_iterator = BASE_RANGE::this_iterator;
   using iterator = BASE_RANGE::iterator;
   using const_iterator = BASE_RANGE::const_iterator;


   using THIS_RAW_RANGE = BASE_RANGE::THIS_RAW_RANGE;
   using RAW_RANGE = BASE_RANGE::RAW_RANGE;
   using CONST_RAW_RANGE = BASE_RANGE::CONST_RAW_RANGE;

   using ITEM_POINTER = get_type_item_pointer < this_iterator >::type;

   using ITEM = dereference < ITEM_POINTER >;

   
   template<::count count>
   constexpr string_range(const ITEM(&array)[count]) : range(array, array[count - 1] == 0 ? count - 1 : count){}
   template<primitive_integral INTEGRAL>
   constexpr string_range(const_iterator begin, INTEGRAL count) : BASE_RANGE((this_iterator)begin, (this_iterator)(begin + count)){}
   string_range(enum_no_initialize) : BASE_RANGE(e_no_initialize) {}
   string_range(nullptr_t) : BASE_RANGE(nullptr) {}
   string_range() {}
   template<typed_range<iterator> RANGE>
   string_range(const RANGE & range) : BASE_RANGE(range) {}
   template<typed_range<const_iterator> RANGE>
   string_range(const RANGE & range) : BASE_RANGE(range) {}
   explicit string_range(const THIS_RANGE & range) : BASE_RANGE(range) {}
   explicit string_range(THIS_RANGE && range) : BASE_RANGE(::move(range)) {}
   string_range(const_iterator begin, const_iterator end) : BASE_RANGE(begin, end) {}
   string_range(const_iterator begin) : BASE_RANGE(begin, span_zero_item(begin)) {}


   string_range & operator = (const string_range & string_range) { BASE_RANGE::operator=(string_range); return *this; }
   string_range & operator = (string_range && string_range) { BASE_RANGE::operator=(::move(string_range)); return *this; }


};


using ansi_range        = ::string_range < ::ansi_character * >;
using wd16_range        = ::string_range < ::wd16_character * >;
using wd32_range        = ::string_range < ::wd32_character * >;
using wide_range        = ::string_range < ::wide_character * >;
//using string_range      = ::ansi_range;
//using wstring_range     = ::wide_range;


using const_ansi_range     = ::string_range < const ::ansi_character * >;
using const_wd16_range     = ::string_range < const ::wd16_character * >;
using const_wd32_range     = ::string_range < const ::wd32_character * >;
using const_wide_range     = ::string_range < const ::wide_character * >;
//using const_string_range   = ::const_ansi_range;
//using const_wstring_range  = ::const_wide_range;

using const_ansi_raw_range     = ::range < const ::ansi_character * >;
using const_wd16_raw_range     = ::range < const ::wd16_character * >;
using const_wd32_raw_range     = ::range < const ::wd32_character * >;



template < primitive_character CHARACTER >
inline const CHARACTER * _unicode_scan(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
{

   auto p = block.data();

   auto pEnd = p + block.size();

   auto pBlock = blockBlock.data();

   auto pBlockEnd = pBlock + blockBlock.size();

   ::i32 len1;

   ::i32 len2;

   while (p < pEnd)
   {

      auto pBlockScan = pBlock;

      auto index = unicode_index_length(p, len1);

      do
      {

         if (index == unicode_index_length(pBlockScan, len2))
         {

            return true;

         }

         pBlockScan += len2;

      } while (pBlockScan < pBlockEnd);

      p += len1;

   }

   return p;

}


template < primitive_character CHARACTER >
inline const CHARACTER * unicode_scan(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
{

   CHARACTER * p;

   if (_string_scan_prefix(p, block, blockBlock))
   {

      return p;

   }

   return _unicode_scan(block, blockBlock);

}




template < primitive_character CHARACTER >
inline const CHARACTER * _unicode_rear_scan(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
{

   auto p = block.data();

   auto pEnd = p + block.size();

   auto pBlock = blockBlock.data();

   auto pBlockEnd = pBlock + blockBlock.size();

   ::i32 len1;

   ::i32 len2;

   while (pEnd < p)
   {

      auto pBlockScan = pBlock;

      auto pPrior = unicode_prior(pEnd, p);

      auto index = unicode_index(pPrior);

      do
      {

         if (index == unicode_index_length(pBlockScan, len2))
         {

            return true;

         }

         pBlockScan += len2;

      } while (pBlockScan < pBlockEnd);

      pEnd = pPrior;

   }

   return pEnd;

}


template < primitive_character CHARACTER >
inline const CHARACTER * unicode_rear_scan(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
{

   CHARACTER * p;

   if (_string_rear_scan_prefix(p, block, blockBlock))
   {

      return p;

   }

   return _unicode_rear_scan(block, blockBlock);

}







