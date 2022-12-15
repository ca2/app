// Created by camilo on 2022-12-05 18:28 <3ThomasBorregaardSorensen!!
#pragma once


#include "iterator.h"
#include "range.h"
#include "array_range.h"
#include "acme/primitive/mathematics/numeric.h"


/// consecutive items arranged as array of ITEM
template < typename RANGE_TYPE >
class array_range :
   public RANGE_TYPE
{
public:


   using BASE_RANGE = RANGE_TYPE;

   using THIS_RANGE = ::array_range < BASE_RANGE >;


   using CONST_RAW_RANGE = RANGE_TYPE::CONST_RAW_RANGE;


   using iterator = RANGE_TYPE::iterator;
   using const_iterator = RANGE_TYPE::const_iterator;


   using RAW_RANGE = ::range < iterator >;


   using ITEM_POINTER = get_type_item_pointer<iterator>::type;


   using ITEM = dereference <ITEM_POINTER>;

   //using BASE_RANGE::BASE_RANGE;

   array_range(enum_no_initialize):BASE_RANGE(e_no_initialize){}
   array_range(nullptr_t):BASE_RANGE(nullptr){}
   array_range():BASE_RANGE(){}
   array_range(const array_range & array_range) : BASE_RANGE(array_range) {}
   array_range(array_range && array_range) : BASE_RANGE(::move(array_range)) {}
   template<typed_range<iterator> RANGE>
   array_range(const RANGE &range) : BASE_RANGE(range) {}
   template<typed_range<const_iterator> RANGE>
   array_range(const RANGE &range) : BASE_RANGE(range) {}
   template < primitive_integral INTEGRAL >
   array_range(const_iterator data, INTEGRAL count) : BASE_RANGE(data, count) { }
   array_range(const_iterator begin, const_iterator end) : BASE_RANGE(begin, end) {}
   template < primitive_block BLOCK_TYPE >
   array_range(enum_as_block, const BLOCK_TYPE & block) :
      BASE_RANGE(e_no_initialize)
   {
      assign_block(block);
   }
   template < typed_block < ITEM > TYPED_BLOCK >
   array_range(enum_as_typed_block, const TYPED_BLOCK & block) :
      BASE_RANGE(e_no_initialize)
   {
      
      assign_typed_block(block);

   }


 
   array_range & operator = (const array_range & array_range) { RANGE_TYPE::operator=(array_range); return *this; }
   array_range & operator = (array_range && range) { BASE_RANGE::operator=(::move(range)); return *this; }


   //array_range(const ITEM * data) :range(data) { }
   //array_range(const ITEM * begin, const ITEM * end, bool bNullTerminated = false) : range(begin, end, bNullTerminated) { }
   //template < primitive_integral INTEGRAL >
   //array_range(ITEM * data, INTEGRAL count, bool bNullTerminated = false) :
   //   range(data, count, bNullTerminated) { }
   //template <std::size_t c>
   //array_range(const ITEM(&begin)[c]) : range(begin, begin + c, false) {}

   memsize length_in_bytes() const { return ::is_set(this->begin()) ? maximum(0, (const ::byte *)(const ITEM * )this->end() - (const ::byte *)(const ITEM *)this->begin()) : 0; }



   template < primitive_block BLOCK_TYPE >
   void assign_block(const BLOCK_TYPE & block)
   {

      ASSERT(block.length_in_bytes() % this->item_size() == 0);

      this->m_begin = (iterator)block.begin();

      this->m_end = (iterator)((::byte *)this->begin() + block.length_in_bytes() / this->item_size());


   }

   template < typed_block < ITEM > TYPED_BLOCK >
   void assign_typed_block(TYPED_BLOCK & block)
   {

      this->m_begin = block.data();
      this->m_end = this->m_end + block.size();

   }

   auto data() { return this->begin(); }
   auto data() const { return this->begin(); }

   constexpr ::count _size() const { return this->end() - this->begin(); }


   bool contains_data(const ITEM * p) const
   {

      return p >= this->begin() && p < this->end();

   }

   constexpr bool is_end(iterator iterator) const
   {

      return iterator >= this->m_end;

   }

   constexpr bool is_end() const
   {

      return this->m_begin >= this->m_end;

   }

   constexpr bool is_ok(iterator iterator) const
   {

      return iterator < this->m_end;

   }


   constexpr bool is_ok() const
   {

      return this->m_begin < this->m_end;

   }


};


//template < primitive_character CHARACTER >
//inline bool _string_scan_prefix(const CHARACTER *& p, const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
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
//inline bool _string_rear_scan_prefix(const CHARACTER *& p, const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
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
//inline const CHARACTER * _string_rear_scan(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
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
//inline const CHARACTER * string_rear_scan(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockBlock) noexcept
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
//inline const CHARACTER * _unicode_span_excluding(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockSeparators)
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
//   ::i32 len1;
//
//   ::i32 len2;
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
//const CHARACTER * unicode_token(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockSeparators)
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
//inline const CHARACTER * _string_span_excluding(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockSeparators)
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
//const CHARACTER * string_token(const ::string_range < CHARACTER > & block, const ::string_range < CHARACTER > & blockSeparators)
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
//inline const CHARACTER * _block_rear_find_character(const ::string_range < CHARACTER > & block, CHARACTER ch) noexcept
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
//bool _string_compare_prefix(int & iCompare, const ::string_range < CHARACTER > & blockA, const ::string_range < CHARACTER > & blockB)
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
//const CHARACTER * _string_compare(const ::string_range < CHARACTER > & blockA, const ::string_range < CHARACTER > & blockB)
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
//const CHARACTER * string_compare(const CHARACTER * pA, strsize sizeA, const CHARACTER * pB, strsize sizeB)
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



