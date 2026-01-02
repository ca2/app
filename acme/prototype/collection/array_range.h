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


   constexpr bool array_range_ok() const { return true; }


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


   inline const TYPE *ptr_at(::collection::index nIndex) const { return this->m_begin + nIndex; }
   inline TYPE *ptr_at(::collection::index nIndex) { return this->m_begin + nIndex; }

   inline const TYPE &element_at(::collection::index nIndex) const;
   inline TYPE &element_at(::collection::index nIndex);

   inline TYPE &first(::collection::index n = 0);
   inline const TYPE &first(::collection::index n = 0) const;

   inline TYPE &last(::collection::index n = -1);
   inline const TYPE &last(::collection::index n = -1) const;

   inline TYPE &middle(::collection::index n = 0);
   inline const TYPE &middle(::collection::index n = 0) const;


   TYPE &operator[](::collection::index i) { return this->m_begin[i]; }
   const TYPE &operator[](::collection::index i) const { return this->m_begin[i]; }


};
//

//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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


//template < prototype_character CHARACTER >
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


//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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
//template < prototype_character CHARACTER >
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


 template<typename TYPE, typename ARG_TYPE>
inline const TYPE &array_range<TYPE, ARG_TYPE>::element_at(::collection::index nIndex) const
{

    ASSERT(nIndex >= 0 && nIndex < this->size());

    return this->m_begin[nIndex];

 }


 template<typename TYPE, typename ARG_TYPE>
 inline TYPE &array_range<TYPE, ARG_TYPE>::element_at(::collection::index nIndex)
 {

    ASSERT(nIndex >= 0 && nIndex < this->size());

    return this->m_begin[nIndex];

 }


template<typename TYPE, typename ARG_TYPE>
inline const TYPE &array_range<TYPE, ARG_TYPE>::first(::collection::index nIndex) const
{

   return this->element_at(nIndex);
}


template<typename TYPE, typename ARG_TYPE>
inline TYPE &array_range<TYPE, ARG_TYPE>::first(::collection::index nIndex)
{

   return this->element_at(nIndex);
}


template<typename TYPE, typename ARG_TYPE>
inline const TYPE &array_range<TYPE, ARG_TYPE>::last(::collection::index i) const
{

   return element_at(this->get_upper_bound(i));
}


template<typename TYPE, typename ARG_TYPE>
inline TYPE &array_range<TYPE, ARG_TYPE>::last(::collection::index i)
{

   return element_at(this->get_upper_bound(i));
}


template<typename TYPE, typename ARG_TYPE>
inline const TYPE &array_range<TYPE, ARG_TYPE>::middle(::collection::index i) const
{

   return element_at(this->get_middle_index(i));
}


template<typename TYPE, typename ARG_TYPE>
inline TYPE &array_range<TYPE, ARG_TYPE>::middle(::collection::index i)
{

   return element_at(this->get_middle_index(i));
}
