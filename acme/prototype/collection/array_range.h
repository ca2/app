// Created by camilo on 2022-12-05 18:28 <3ThomasBorregaardSorensen!!
#pragma once


#include "iterator.h"
#include "range.h"
//#include "array_range.h"
#include "acme/prototype/mathematics/numeric.h"

//
///// consecutive items arranged as array of ITEM
template < typename TYPE, typename ARG_TYPE >
class array_range :
   public ::range < TYPE * >
{
public:

   
   using BASE_RANGE = ::range<TYPE *>;
   using RAW_BASE_ARRAY = array_range;
   using BASE_RAW_RANGE = ::range<TYPE *>;
   using BASE_TYPE = TYPE;


   using BASE_RANGE::BASE_RANGE;


   ::collection::count size() const { return this->m_end - this->m_begin; }
   ::collection::count get_count() const { return this->size(); }


   inline ::collection::index get_lower_bound(::collection::index i = 0) const;
   inline ::collection::index get_middle_index(::collection::index i = 0) const;
   inline ::collection::index get_upper_bound(::collection::index i = -1) const;
   inline ::collection::index lower_bound(::collection::index i = 0) const { return this->get_lower_bound(i); }
   inline ::collection::index upper_bound(::collection::index i = -1) const { return this->get_upper_bound(i); }
   inline ::collection::index first_index(::collection::index i = 0) const { return this->lower_bound(i); }
   inline ::collection::index middle_index(::collection::index i = 0) const { return this->get_middle_index(i); }
   inline ::collection::index last_index(::collection::index i = -1) const { return this->get_upper_bound(i); }
   inline bool bounds(::collection::index i) const;
   inline bool contains_index(::collection::index i) const { return bounds(i); }


   inline bool prepare_first_last(::collection::index& first, ::collection::index& last) const;
   inline bool prepare_first_in_count_last_out(::collection::index& first, ::collection::count& inCountLastOut) const;


   //
//
//   using BASE_RANGE = RANGE_TYPE;
//
//   using THIS_RANGE = ::array_range < BASE_RANGE >;
//
//
//   using CONST_RAW_RANGE = typename RANGE_TYPE::CONST_RAW_RANGE;
//
//
//   using iterator = typename RANGE_TYPE::iterator;
//   using const_iterator = typename RANGE_TYPE::const_iterator;
//
//
//   using RAW_RANGE = ::range < iterator >;
//
//
//   using ITEM_POINTER = typename get_type_item_pointer<iterator>::type;
//
//
//   using ITEM = dereference <ITEM_POINTER>;
//
//   //using BASE_RANGE::BASE_RANGE;
//
//   array_range(no_initialize_t):BASE_RANGE(no_initialize_t{}){}
//   array_range(nullptr_t):BASE_RANGE(nullptr){}
//   array_range():BASE_RANGE(){}
//   array_range(const array_range & array_range) : BASE_RANGE(array_range) {}
//   array_range(array_range && array_range) : BASE_RANGE(::transfer(array_range)) {}
//   template<typed_range<iterator> RANGE>
//   array_range(const RANGE &range) : BASE_RANGE(range) {}
//   template<typed_range<const_iterator> RANGE>
//   array_range(const RANGE &range) : BASE_RANGE(range) {}
//   template < primitive_integral INTEGRAL >
//   constexpr array_range(const_iterator data, INTEGRAL count) : BASE_RANGE(data, count) { }
//   constexpr array_range(const_iterator begin, const_iterator end) : BASE_RANGE(begin, end) {}
//   template < primitive_block BLOCK_TYPE >
//   array_range(enum_as_block, const BLOCK_TYPE & block) :
//      BASE_RANGE(no_initialize_t{})
//   {
//      assign_block(block);
//   }
//   template < typed_block < ITEM > TYPED_BLOCK >
//   array_range(enum_as_typed_block, const TYPED_BLOCK & block) :
//      BASE_RANGE(no_initialize_t{})
//   {
//      
//      assign_typed_block(block);
//
//   }
//
//
// 
//   array_range & operator = (const array_range & array_range) { RANGE_TYPE::operator=(array_range); return *this; }
//   array_range & operator = (array_range && range) { BASE_RANGE::operator=(::transfer(range)); return *this; }
//
//
//   //array_range(const ITEM * data) :range(data) { }
//   //array_range(const ITEM * begin, const ITEM * end, bool bNullTerminated = false) : range(begin, end, bNullTerminated) { }
//   //template < primitive_integral INTEGRAL >
//   //array_range(ITEM * data, INTEGRAL count, bool bNullTerminated = false) :
//   //   range(data, count, bNullTerminated) { }
//   //template <std::size_t c>
//   //array_range(const ITEM(&begin)[c]) : range(begin, begin + c, false) {}
//
//   memsize length_in_bytes() const { return ::is_set(this->begin()) ? maximum(0, (const unsigned char *)(const ITEM * )this->end() - (const unsigned char *)(const ITEM *)this->begin()) : 0; }
//
//
//
//   template < primitive_block BLOCK_TYPE >
//   void assign_block(const BLOCK_TYPE & block)
//   {
//
//      ASSERT(block.length_in_bytes() % this->item_size() == 0);
//
//      this->m_begin = (iterator)block.begin();
//
//      this->m_end = (iterator)((unsigned char *)this->begin() + block.length_in_bytes() / this->item_size());
//
//
//   }
//
//   template < typed_block < ITEM > TYPED_BLOCK >
//   void assign_typed_block(TYPED_BLOCK & block)
//   {
//
//      this->m_begin = block.data();
//      this->m_end = this->m_end + block.size();
//
//   }
//
//   auto data() { return this->begin(); }
//   auto data() const { return this->begin(); }
//
//   constexpr ::collection::count _size() const { return this->end() - this->begin(); }
//
//
//   bool contains_data(const ITEM * p) const
//   {
//
//      return p >= this->begin() && p < this->end();
//
//   }
//
//   constexpr bool is_end(iterator iterator) const
//   {
//
//      return iterator >= this->m_end;
//
//   }
//
//   constexpr bool is_end() const
//   {
//
//      return this->m_begin >= this->m_end;
//
//   }
//
//   constexpr bool is_ok(iterator iterator) const
//   {
//
//      return iterator < this->m_end;
//
//   }
//
//
//   constexpr bool is_ok() const
//   {
//
//      return this->m_begin < this->m_end;
//
//   }
//
//

constexpr bool array_range_ok() const { return true; }


   TYPE &element_at(::collection::index i) { return this->m_begin[i]; }
   const TYPE &element_at(::collection::index i) const { return this->m_begin[i]; }
   TYPE &operator[](::collection::index i) { return this->m_begin[i]; }
   const TYPE &operator[](::collection::index i) const { return this->m_begin[i]; }



};
//

//template < primitive_character CHARACTER >
//inline bool _string_scan_prefix(const CHARACTER *& p, const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
//{
//
//   if (block.is_empty())
//   {
//
//      p = block.data();
//
//      return true;
//
//   }
//
//   if(blockBlock.is_empty())
//   {
//
//      p = block.data();
//
//      return true;
//
//   }
//
//   return false;
//
//}

//
//template < primitive_character CHARACTER >
//inline bool _string_rear_scan_prefix(const CHARACTER *& p, const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
//{
//
//   if (block.is_empty())
//   {
//
//      p = block.data() + block.size();
//
//      return true;
//
//   }
//
//   if (blockBlock.is_empty())
//   {
//
//      p = block.data() + block.size();
//
//      return true;
//
//   }
//
//   return false;
//
//}



//
//template < primitive_character CHARACTER >
//inline const CHARACTER * _string_rear_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
//{
//
//   auto p = block.data();
//
//   auto pEnd = p + block.size();
//
//   auto pBlock = blockBlock.data();
//
//   auto pBlockEnd = pBlock + blockBlock.size();
//
//   while (pEnd > p)
//   {
//
//      auto pBlockScan = pBlock;
//
//      do
//      {
//
//         if (*pEnd == *pBlockScan)
//         {
//
//            return pEnd;
//
//         }
//
//         pBlockScan++;
//
//      } while (pBlockScan < pBlockEnd);
//
//      pEnd--;
//
//   }
//
//   return pEnd;
//
//}

//
//template < primitive_character CHARACTER >
//inline const CHARACTER * string_rear_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockBlock) noexcept
//{
//
//   CHARACTER * p;
//
//   if (_string_rear_scan_prefix(p, block, blockBlock))
//   {
//
//      return p;
//
//   }
//
//   return _string_rear_scan(block, blockBlock);
//
//}


//template < primitive_character CHARACTER >
//inline const CHARACTER * _unicode_find_first_character_in(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockSeparators)
//{
//
//   auto p = block.data();
//
//   auto pEndExclusive = p + block.size();
//
//   auto pSeparators = blockSeparators.data();
//
//   auto pSeparatorsEndExclusive = pSeparators + blockSeparators.size();
//
//   int len1;
//
//   int len2;
//
//   while (p < pEndExclusive)
//   {
//
//      auto index = unicode_index_length(p, len1);
//
//      auto pSeparatorsScan = pSeparators;
//
//      do
//      {
//
//         if (index == unicode_index_length(pSeparatorsScan, len2))
//         {
//
//            return p;
//
//         }
//
//         pSeparatorsScan += len2;
//
//      } while (pSeparatorsScan < pSeparatorsEndExclusive);
//
//      p += len1;
//
//   }
//
//   return p;
//
//}


//template < primitive_character CHARACTER >
//const CHARACTER * unicode_token(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockSeparators)
//{
//
//   if (block.is_empty())
//   {
//
//      return block.data();
//
//   }
//
//   if (blockSeparators.is_empty())
//   {
//
//      return block.data();
//
//   }
//
//   return _unicode_token(block, blockSeparators);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline const CHARACTER * _string_find_first_character_in(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockSeparators)
//{
//
//   auto p = block.data();
//
//   auto pEndExclusive = p + block.size();
//
//   auto pSeparators = blockSeparators.data();
//
//   auto pSeparatorsEndExclusive = pSeparators + blockSeparators.size();
//
//   while (p < pEndExclusive)
//   {
//
//      auto ch = *p;
//
//      auto pSeparatorsScan = pSeparators;
//
//      do
//      {
//
//         if (ch == *pSeparatorsScan)
//         {
//
//            return p;
//
//         }
//
//         pSeparatorsScan++;
//
//      } while (pSeparatorsScan < pSeparatorsEndExclusive);
//
//      p++;
//
//   }
//
//   return p;
//
//}
//
//
//template < primitive_character CHARACTER >
//const CHARACTER * string_token(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockSeparators)
//{
//
//   if (block.is_empty())
//   {
//
//      return block.data();
//
//   }
//
//   if (blockSeparators.is_empty())
//   {
//
//      return block.data();
//
//   }
//
//   return _string_token(block, blockSeparators);
//
//}


//
//template < primitive_character CHARACTER >
//inline const CHARACTER * _block_rear_find_character(const ::range < CHARACTER > & block, CHARACTER ch) noexcept
//{
//
//   auto pBegin = block.begin();
//
//   auto pEnd = block.end() - 1;
//
//   while (pEnd >= pBegin)
//   {
//
//      if (*pEnd == ch)
//      {
//
//         return pEnd;
//
//      }
//
//   }
//
//   return nullptr;
//
//}

//
//template < primitive_character CHARACTER >
//bool _string_compare_prefix(int & iCompare, const ::range < CHARACTER > & blockA, const ::range < CHARACTER > & blockB)
//{
//
//   if (blockA.is_empty())
//   {
//
//      if (blockB.is_empty())
//      {
//
//         iCompare = 0;
//
//         return true;
//
//      }
//      else
//      {
//
//         iCompare = 1;
//
//         return true;
//
//      }
//
//   }
//   else if (blockB.is_empty())
//   {
//
//      iCompare = -1;
//
//      return true;
//
//   }
//
//   return false;
//
//}

//
//template < primitive_character CHARACTER >
//const CHARACTER * _string_compare(const ::range < CHARACTER > & blockA, const ::range < CHARACTER > & blockB)
//{
//
//   auto pA = blockA.begin();
//
//   auto pAEnd = blockA.end();
//
//   auto pB = blockB.begin();
//
//   auto pBEnd = blockB.end();
//
//   int iCompare;
//
//   while (pA < pAEnd && pB < pBEnd)
//   {
//
//      iCompare = *pA - *pB;
//
//   }
//
//
//}

//
//template < primitive_character CHARACTER >
//const CHARACTER * string_compare(const CHARACTER * pA, character_count sizeA, const CHARACTER * pB, character_count sizeB)
//{
//
//   int iCompare;
//
//   if (_string_compare_prefix(iCompare, blockA, blockB))
//   {
//
//      return iCompare;
//
//   }
//
//   return _string_compare(blockA, blockB);
//
//}
//
//
//






template<typename TYPE, typename ARG_TYPE>
inline ::collection::index array_range<TYPE, ARG_TYPE>::get_lower_bound(::collection::index i) const
{
   return i < this->size() ? i : -1;
}

template<typename TYPE, typename ARG_TYPE>
inline ::collection::index
array_range<TYPE, ARG_TYPE>::get_middle_index(::collection::index iIndex) const
{
   return this->size() / 2 + iIndex;
}


template<typename TYPE, typename ARG_TYPE>
inline ::collection::index
array_range<TYPE, ARG_TYPE>::get_upper_bound(::collection::index iIndex) const
{
   return this->size() + iIndex;
}

template<typename TYPE, typename ARG_TYPE>
inline bool array_range<TYPE, ARG_TYPE>::bounds(::collection::index i) const
{
   return i >= 0 && i < this->size();
}



template<typename TYPE, typename ARG_TYPE>
bool array_range<TYPE, ARG_TYPE>::prepare_first_last(::collection::index& first,
   ::collection::index& last) const
{

   if (first < 0)
   {

      first += this->array_get_count();

   }

   if (last < 0)
   {

      last += this->array_get_count();

   }

   return last >= first;
}


template<typename TYPE, typename ARG_TYPE>
bool array_range<TYPE, ARG_TYPE >::prepare_first_in_count_last_out(
   ::collection::index& first, ::collection::count& in_count_out_last) const
{

   if (first < 0)
   {

      first += this->array_get_count();

   }

   if (first < 0)
   {

      first = 0;

   }

   if (in_count_out_last < 0)
   {

      in_count_out_last += this->array_get_count();

   }
   else
   {

      in_count_out_last = first + in_count_out_last - 1;

   }

   return in_count_out_last >= first;

}



