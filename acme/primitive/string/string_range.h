// Created by camilo on 2022-12-07 23:59 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/collection/array_range.h"
#include "acme/primitive/collection/comparable_eq_range.h"
#include "acme/primitive/collection/comparable_range.h"
#include "acme/primitive/collection/null_terminated_iterator.h"
#include "acme/primitive/collection/null_terminated_range.h"



template < typename ITERATOR_TYPE >
class string_range : 
   //public ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >
   //public ::array_range < ::range < ITERATOR_TYPE > > >
   public ::range < ITERATOR_TYPE >
{
public:
   

   //using BASE_RANGE = ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >;

   using BASE_RANGE = ::range < ITERATOR_TYPE >;

   using THIS_RANGE = ::string_range < ITERATOR_TYPE >;



   using this_iterator = typename BASE_RANGE::this_iterator;
   using iterator =  typename BASE_RANGE::iterator;
   using const_iterator = typename  BASE_RANGE::const_iterator;


   using THIS_RAW_RANGE =  typename BASE_RANGE::THIS_RAW_RANGE;
   using RAW_RANGE =  typename BASE_RANGE::RAW_RANGE;
   using CONST_RAW_RANGE =  typename BASE_RANGE::CONST_RAW_RANGE;

   using ITEM_POINTER =  typename get_type_item_pointer < this_iterator >::type;

   using ITEM = non_const < dereference < ITEM_POINTER > >;

   
   template<::std::size_t count>
   constexpr string_range(const ITEM(&array)[count]) : BASE_RANGE(array, array[count - 1] == 0 ? count - 1 : count){}
   template<primitive_integral INTEGRAL>
   constexpr string_range(const_iterator begin, INTEGRAL count) : BASE_RANGE((this_iterator)begin, (this_iterator)(begin + count)){}
   string_range(enum_no_initialize) : BASE_RANGE(e_no_initialize) {}
   string_range(nullptr_t) : BASE_RANGE(nullptr) {}
   string_range() {}
   template<typed_range<iterator> RANGE>
   string_range(const RANGE & range) : BASE_RANGE(range) {}
   template<typed_range<const_iterator> RANGE>
   string_range(const RANGE & range) : BASE_RANGE(range) {}
   string_range(const THIS_RANGE & range) : BASE_RANGE(range) {}
   string_range(THIS_RANGE && range) : BASE_RANGE(::move(range)) {}
   string_range(const_iterator begin, const_iterator end) : BASE_RANGE(begin, end) {}
   string_range(const ITEM * & begin) : BASE_RANGE(begin, span_zero_item(begin)) {}
   string_range(const ::atom & atom);


   string_range & operator = (const string_range & range) { BASE_RANGE::operator=(range); return *this; }
   string_range & operator = (string_range && range) { BASE_RANGE::operator=(::move(range)); return *this; }
   string_range & operator = (const atom & atom);



   using BASE_RANGE::_order;

   constexpr ::std::strong_ordering _order(THIS_RANGE range) const
   {

      return _order(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::order;

   constexpr ::std::strong_ordering order(THIS_RANGE range) const
   {

      return BASE_RANGE::order(range, ::comparison::comparison < ITEM >());

   }


   constexpr ::std::strong_ordering operator<=>(THIS_RANGE range) const
   {

      return this->order(range);

   }


   using BASE_RANGE::_equals;

   constexpr bool _equals(const THIS_RANGE & range) const
   {

      return this->_equals(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::equals;

   constexpr bool equals(const THIS_RANGE & range) const
   {

      return this->equals(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_equals_start;

   constexpr bool _equals_start(const THIS_RANGE & range, memsize start) const
   {

      return this->_equals_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::equals_start;

   constexpr bool equals_start(const THIS_RANGE & range, memsize start) const
   {

      return this->equals_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_equals_start_count;

   constexpr bool _equals_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_equals_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::equals_start_count;

   constexpr bool equals_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->equals_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   bool operator == (const THIS_RANGE & range) const
   {

      return this->equals(range);

   }

   using BASE_RANGE::_find;

   constexpr const_iterator _find(const THIS_RANGE & range) const
   {

      return this->_find(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::find;

   constexpr const_iterator find(const THIS_RANGE & range) const
   {

      return this->find(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_find_start;

   constexpr const_iterator _find_start(const THIS_RANGE & range, memsize start) const
   {

      return this->_find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::find_start;

   constexpr const_iterator find_start(const THIS_RANGE & range, memsize start) const
   {

      return this->find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_find_start_count;

   constexpr const_iterator _find_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::find_start_count;

   constexpr const_iterator find_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_find;

   constexpr const_iterator _rear_find(const THIS_RANGE & range) const
   {

      return this->_rear_find(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_find;

   constexpr const_iterator rear_find(const THIS_RANGE & range) const
   {

      return this->rear_find(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_find_start;

   constexpr const_iterator _rear_find_start(const THIS_RANGE & range, memsize start) const
   {

      return this->_rear_find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_find_start;

   constexpr const_iterator rear_find_start(const THIS_RANGE & range, memsize start) const
   {

      return this->rear_find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_find_start_count;

   constexpr const_iterator _rear_find_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_find_start_count;

   constexpr const_iterator rear_find_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_scan;

   constexpr const_iterator _scan(const THIS_RANGE & range) const
   {

      return this->_scan(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::scan;

   constexpr const_iterator scan(const THIS_RANGE & range) const
   {

      return this->scan(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_scan_start;

   constexpr const_iterator _scan_start(const THIS_RANGE & range, memsize start) const
   {

      return this->_scan_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::scan_start;

   constexpr const_iterator scan_start(const THIS_RANGE & range, memsize start) const
   {

      return this->scan_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_scan_start_count;

   constexpr const_iterator _scan_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::scan_start_count;

   constexpr const_iterator scan_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }



   using BASE_RANGE::_span;

   constexpr const_iterator _span(const THIS_RANGE & range) const
   {

      return this->_span(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::span;

   constexpr const_iterator span(const THIS_RANGE & range) const
   {

      return this->span(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_span_start;

   constexpr const_iterator _span_start(const THIS_RANGE & range, memsize start) const
   {

      return this->_span_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::span_start;

   constexpr const_iterator span_start(const THIS_RANGE & range, memsize start) const
   {

      return this->span_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_span_start_count;

   constexpr const_iterator _span_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_span_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::span_start_count;

   constexpr const_iterator span_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->span_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_span;

   constexpr const_iterator _rear_span(const THIS_RANGE & range) const noexcept
   {

      return this->_rear_span(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_span;

   constexpr const_iterator rear_span(const THIS_RANGE & range) const noexcept
   {

      return this->rear_span(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_span_start;

   constexpr const_iterator rear_span_start(const THIS_RANGE & range, memsize start) const
   {

      return this->rear_span_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_span_start_count;

   constexpr const_iterator _rear_span_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_rear_span_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_span_start_count;

   constexpr const_iterator rear_span_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->rear_span_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }

   using BASE_RANGE::_skip;

   constexpr const_iterator _skip(const ITEM & item) const
   {

      return this->_skip(item, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::skip;

   constexpr const_iterator skip(const ITEM & item) const
   {

      return this->skip(item, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_skip_start;

   constexpr const_iterator _skip_start(const ITEM & item, memsize start) const
   {

      return this->_skip_start(item, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::skip_start;

   constexpr const_iterator skip_start(const ITEM & item, memsize start) const
   {

      return this->skip_start(item, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_skip_start_count;

   constexpr const_iterator _skip_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->_skip_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::skip_start_count;

   constexpr const_iterator skip_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->skip_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }




   using BASE_RANGE::_rear_find_item;

   constexpr const_iterator _rear_find_item(const ITEM & item) const
   {

      return this->_rear_find_item(item, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_find_item;

   constexpr const_iterator rear_find_item(const ITEM & item) const
   {

      return this->rear_find_item(item, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_find_item_start;

   constexpr const_iterator _rear_find_item_start(const ITEM & item, memsize start) const
   {

      return this->_rear_find_item_start(item, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_find_item_start;

   constexpr const_iterator rear_find_item_start(const ITEM & item, memsize start) const
   {

      return this->rear_find_item_start(item, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_find_item_start_count;

   constexpr const_iterator _rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->_rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_find_item_start_count;

   constexpr const_iterator rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }



   using BASE_RANGE::_rear_scan;

   constexpr const_iterator _rear_scan(const THIS_RANGE & range) const noexcept
   {

      return this->_rear_scan(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_scan;

   constexpr const_iterator rear_scan(const THIS_RANGE & range) const noexcept
   {

      return this->rear_scan(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_scan_start;

   constexpr const_iterator rear_scan_start(const THIS_RANGE & range, memsize start) const
   {

      return this->rear_scan_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_rear_scan_start_count;

   constexpr const_iterator _rear_scan_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_rear_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::rear_scan_start_count;

   constexpr const_iterator rear_scan_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->rear_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_begins;

   constexpr bool _begins(const THIS_RANGE & range) const
   {

      return this->_begins(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::begins;

   constexpr bool begins(const THIS_RANGE & range) const
   {

      return this->begins(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_begins_start;

   constexpr bool _begins_start(const THIS_RANGE & range, memsize start) const
   {

      return this->_begins_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::begins_start;

   constexpr bool begins_start(const THIS_RANGE & range, memsize start) const
   {

      return this->begins_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_begins_start_count;

   constexpr bool _begins_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_begins_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::begins_start_count;

   constexpr bool begins_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->begins_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }



   using BASE_RANGE::_ends;

   constexpr bool _ends(const THIS_RANGE & range) const
   {

      return this->_ends(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::ends;

   constexpr bool ends(const THIS_RANGE & range) const
   {

      return this->ends(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_ends_start;

   constexpr bool _ends_start(const THIS_RANGE & range, memsize start) const
   {

      return this->_ends_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::ends_start;

   constexpr bool ends_start(const THIS_RANGE & range, memsize start) const
   {

      return this->ends_start(range, start, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::_ends_start_count;

   constexpr bool _ends_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->_ends_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::ends_start_count;

   constexpr bool ends_start_count(const THIS_RANGE & range, memsize start, memsize count) const
   {

      return this->ends_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }



};


using ansi_range        = ::range < ::ansi_character * >;
using wd16_range        = ::range < ::wd16_character * >;
using wd32_range        = ::range < ::wd32_character * >;
using wide_range        = ::range < ::wide_character * >;
//using range      = ::ansi_range;
//using wstring_range     = ::wide_range;


using const_ansi_range     = ::string_range < const ::ansi_character * >;
using const_wd16_range     = ::string_range < const ::wd16_character * >;
using const_wd32_range     = ::string_range < const ::wd32_character * >;
using const_wide_range     = ::string_range < const ::wide_character * >;
//using const_string_range   = ::const_ansi_range;
//using const_wstring_range  = ::const_wide_range;

//using const_ansi_range     = ::string_range < const ::ansi_character * >;
//using const_wd16_range     = ::string_range < const ::wd16_character * >;
//using const_wd32_range     = ::string_range < const ::wd32_character * >;



template < primitive_character CHARACTER >
inline const CHARACTER * _unicode_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
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
inline const CHARACTER * unicode_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
{

   CHARACTER * p;

   if (_string_scan_prefix(p, block, blockBlock))
   {

      return p;

   }

   return _unicode_scan(block, blockBlock);

}




template < primitive_character CHARACTER >
inline const CHARACTER * _unicode_rear_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
{

   auto p = block.data();

   auto pEnd = p + block.size();

   auto pBlock = blockBlock.data();

   auto pBlockEnd = pBlock + blockBlock.size();

   //::i32 len1;

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
inline const CHARACTER * unicode_rear_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
{

   CHARACTER * p;

   if (_string_rear_scan_prefix(p, block, blockBlock))
   {

      return p;

   }

   return _unicode_rear_scan(block, blockBlock);

}








using const_ansi_range = ::string_range < const ::ansi_character * >;
using const_wd16_range = ::string_range < const ::wd16_character * >;
using const_wd32_range = ::string_range < const ::wd32_character * >;


template < primitive_character CHARACTER >
inline u32hash _string_range_u32_hash(::string_range < const CHARACTER * > range)
{

   if (range.is_empty())
   {

      return { 0 };

   }

   u32 uHash = 0;

   while (range.m_begin < range.m_end) uHash = (uHash << 5) + *(range.m_begin++);

   return { uHash };

}


template < >
inline u32hash u32_hash < const_ansi_range >(const_ansi_range range)
{

   return _string_range_u32_hash<::ansi_character>(range);

}


template < >
inline u32hash u32_hash < const_wd16_range >(const_wd16_range range)
{

   return _string_range_u32_hash<::wd16_character>(range);

}


template < >
inline u32hash u32_hash < const_wd32_range >(const_wd32_range range)
{

   return _string_range_u32_hash<::wd32_character>(range);

}


