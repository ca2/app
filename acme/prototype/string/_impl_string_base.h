//
//  _string_base_impl.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 08/06/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#include "acme/prototype/string/_impl_string_base_allocation.h"


template < prototype_character CHARACTER, ::comparison::ordering < CHARACTER > ORDERING >
inline ::std::strong_ordering _sz_compare(const CHARACTER * pA, const CHARACTER * pB, ORDERING ordering) noexcept
{

   while (true)
   {

      auto order = ordering.order(*pA, *pB);

      if (order != 0 || !*pA || !*pB)
      {

         return order;

      }

      pA++;

      pB++;

   }

}


template < prototype_character CHARACTER >
constexpr ::std::strong_ordering _sz_compare(const CHARACTER * pA, const CHARACTER * pB) noexcept
{

   return _sz_compare(pA, pB, ::comparison::comparison<CHARACTER>());

}


template < prototype_character CHARACTER >
constexpr ::std::strong_ordering case_insensitive__sz_compare(const CHARACTER * pA, const CHARACTER * pB) noexcept
{

   return _sz_compare(pA, pB, ::comparison::case_insensitive < CHARACTER >());

}


template < prototype_character CHARACTER, ::comparison::ordering < CHARACTER > ORDERING >
inline ::std::strong_ordering _sz_count_compare(const CHARACTER * pA, const CHARACTER * pB, character_count sizeB, ORDERING ordering) noexcept
{

   auto pBEnd = pB + sizeB;

   while (true)
   {

      if (pB >= pBEnd)
      {

         return *pA <=> 0;

      }

      auto order = ordering.order(*pA, *pB);

      if (order != 0 || !*pA)
      {

         return order;

      }

      pA++;

      pB++;

   }

}


template < prototype_character CHARACTER >
constexpr ::std::strong_ordering _sz_count_compare(const CHARACTER * pA, const CHARACTER * pB, character_count sizeB) noexcept
{

   return _sz_count_compare(pA, pB, sizeB, ::comparison::comparison<CHARACTER>());

}


template < prototype_character CHARACTER >
constexpr ::std::strong_ordering case_insensitive__sz_count_compare(const CHARACTER * pA, const CHARACTER * pB, character_count sizeB) noexcept
{

   return _sz_count_compare(pA, pB, sizeB, ::comparison::case_insensitive < CHARACTER >());

}


template < prototype_character CHARACTER, ::comparison::ordering < CHARACTER > ORDERING >
inline ::std::strong_ordering _count_sz_compare(const CHARACTER * pA, character_count sizeA, const CHARACTER * pB, ORDERING ordering) noexcept
{

   auto pAEnd = pA + sizeA;

   while (true)
   {

      if (pA >= pAEnd)
      {

         return ordering.order({}, *pB);

      }

      auto order = ordering.order(*pA, *pB);

      if (order != 0 || !*pB)
      {

         return order;

      }

      pA++;

      pB++;

   }

}


template < prototype_character CHARACTER >
constexpr ::std::strong_ordering _count_sz_compare(const CHARACTER * pA, character_count sizeA, const CHARACTER * pB) noexcept
{

   return _count_sz_compare(pA, sizeA, pB, ::comparison::comparison<CHARACTER>());

}


template < prototype_character CHARACTER >
constexpr ::std::strong_ordering case_insensitive__count_sz_compare(const CHARACTER * pA, character_count sizeA, const CHARACTER * pB) noexcept
{

   return _count_sz_compare(pA, sizeA, pB, ::comparison::case_insensitive < CHARACTER >());

}



//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering case_insensitive__string_compare(const CHARACTER * pszA, character_count sizeA, const_char_pointer pszB, character_count sizeB) noexcept
//{
//
//   character_count lenCompare = minimum(sizeA, sizeB);
//
//   auto ordering = case_insensitive_string_count_compare(scopedstrA, pszB, lenCompare);
//
//   if (ordering != 0)
//   {
//
//      return ordering;
//
//   }
//
//   return sizeA <=> sizeB;
//
//}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering _scopedstr_collate(::scoped_string_base <  ITERATOR_TYPE > scopedstrA, ::scoped_string_base <  ITERATOR_TYPE > scopedstrB) noexcept
{

   character_count len = minimum(scopedstrA.size(), scopedstrB.size());

   auto order = string_count_collate(scopedstrA.begin(), scopedstrB.begin(), len);

   if (order != 0)
   {

      return order;

   }

   return scopedstrA.size() <=> scopedstrB.size();

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering _case_insensitive_scopedstr_collate(::scoped_string_base <  ITERATOR_TYPE > scopedstrA, ::scoped_string_base <  ITERATOR_TYPE > scopedstrB) noexcept
{

   character_count len = minimum(scopedstrA.size(), scopedstrB.size());

   auto order = case_insensitive_string_count_collate(scopedstrA.begin(), scopedstrB.begin(), len);

   if (order != 0)
   {

      return order;

   }

   return scopedstrA.size() <=> scopedstrB.size();

}


//template < typename ITERATOR_TYPE >
//inline int string_compare(const CHARACTER * pszA, character_count sizeA, const_char_pointer pszB, character_count sizeB) noexcept
//{
//
//   int iCompare;
//
//   if (string_compare_prefix(iCompare, pszA, pszB))
//   {
//
//      return iCompare;
//
//   }
//
//   return _string_compare(scopedstrA, sizeA, pszB, sizeB);
//
//}


//template < typename ITERATOR_TYPE >
//inline int case_insensitive_string_order(const array_scopedstr<CHARACTER> & scopedstrA, ) noexcept
//{
//
//   int iCompare;
//
//   if (string_compare_prefix(iCompare, pszA, pszB))
//   {
//
//      return iCompare;
//
//   }
//
//   return case_insensitive__string_compare(scopedstrA, sizeA, pszB, sizeB);
//
//}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering range_collate(::scoped_string_base <  ITERATOR_TYPE > scopedstrA, ::scoped_string_base <  ITERATOR_TYPE > scopedstrB) noexcept
{

   //::std::strong_ordering order(::std::strong_ordering::less);

   //if (scopedstrA._initialize_order(order, scopedstrA, scopedstrB))
   //{

   //   return order;

   //}

   return _string_collate(::string_base < ITERATOR_TYPE >(scopedstrA).c_str(), ::string_base < ITERATOR_TYPE >(scopedstrB).c_str());

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering case_insensitive_range_collate(::scoped_string_base <  ITERATOR_TYPE > scopedstrA, ::scoped_string_base <  ITERATOR_TYPE > scopedstrB) noexcept
{

   //::std::strong_ordering order(::std::strong_ordering::less);

   //if (scopedstrA._initialize_order(order, scopedstrA, scopedstrB))
   //{

   //   return order;

   //}

   return _case_insensitive_string_collate(::string_base < ITERATOR_TYPE >(scopedstrA).c_str(), ::string_base < ITERATOR_TYPE >(scopedstrB).c_str());

}


template < prototype_character CHARACTER >
inline ::std::strong_ordering _sz_count_collate(const CHARACTER * pszA, const CHARACTER * pszB, character_count sizeB) noexcept
{

   return range_collate<const CHARACTER>(pszA, { pszB, sizeB });

}


template < prototype_character CHARACTER >
inline ::std::strong_ordering _case_insensitive_sz_count_collate(const CHARACTER * pszA, const CHARACTER * pszB, character_count sizeB) noexcept
{

   return case_insensitive_range_collate<const CHARACTER>(pszA, { pszB, sizeB });

}


inline ::std::strong_ordering _count_sz_collate(const_char_pointer pszA, character_count sizeA, const_char_pointer pszB) noexcept
{

   return range_collate<const_char_pointer >({ pszA, sizeA }, pszB);

}


inline ::std::strong_ordering _case_insensitive_count_sz_collate(const_char_pointer pszA, character_count sizeA, const_char_pointer pszB) noexcept
{

   return case_insensitive_range_collate<const_char_pointer >({ pszA, sizeA }, pszB);

}


CLASS_DECL_ACME ::string string_formatf(const_char_pointer pszFormat, ...);





CLASS_DECL_ACME void foo123();


//template < typename ITERATOR_TYPE >
//inline void string_base < ITERATOR_TYPE >::construct1(const ITERATOR_TYPE p, character_count length)
//{
//
//   if (::is_null(p) || length <= 0)
//   {
//
//      default_construct();
//
//      return;
//
//   }
//
//   create_string(length);
//
//   memory_copy((void *) this->m_begin, p, length * sizeof(CHARACTER));
//
//   *(CHARACTER*)this->m_end = (CHARACTER)0;
//
//}


//template < typename ITERATOR_TYPE >
//template < int t_size >
//inline string_base < ITERATOR_TYPE >::string_base(const const_string_range_static_array < ITERATOR_TYPE, t_size >& a) :
//   ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
//{
//
//   auto new_len = a.size();
//
//   auto p = construct_string(new_len);
//
//   a.block_concatenate_to(p);
//
//   ASSERT(p <= this->m_end);
//
//   *p = CHARACTER{};
//
//}


//template < typename ITERATOR_TYPE >
//template < int t_size >
//string_base< ITERATOR_TYPE>& string_base< ITERATOR_TYPE>::append(const const_string_range_static_array < const CHARACTER *, t_size >& a)
//{
//
//   auto old_len = this->size();
//
//   auto add_len = a.size();
//
//   auto new_len = old_len + add_len;
//
//   auto p = get_buffer<true>(new_len);
//
//   p += old_len;
//
//   a.block_concatenate_to(p);
//
//   ASSERT(p <= this->m_end);
//
//   *(CHARACTER*)this->m_end = {};
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER, int t_size >
//string_base< ITERATOR_TYPE>& string_base< ITERATOR_TYPE>::append(const const_string_range_static_array < const OTHER_CHARACTER *, t_size >& a)
//{
//
//   auto old_len = this->size();
//
//   character_count iaLen[t_size];
//
//   character_count* plen = iaLen;
//
//   auto add_len = a.__utf_length(this->begin(), plen);
//
//   auto new_len = old_len + add_len;
//
//   auto p = get_buffer<true>(new_len);
//
//   p += old_len;
//
//   plen = iaLen;
//
//   a.__utf_concatenate_to(p, plen);
//
//   ASSERT(p <= this->m_end);
//
//   p[new_len] = {};
//
//   return *this;
//
//}


template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::construct2(const ::character_range < const CHARACTER * > & range)
{

   this->m_begin = range.m_begin;

   this->m_end = range.m_end;

   this->m_erange = range.m_erange;

   this->m_pbasedata = range.m_pbasedata;

   if (this->m_pbasedata)
   {

      ///auto pbasedata = this->base_data_from_data(this->m_begin);

      this->m_pbasedata->base_data_increment_reference_count();

   }

}


//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
//inline void string_base < ITERATOR_TYPE >::construct5(const OTHER_CHARACTER * p, character_count len)
//{
//
//   if (::is_null(p) || len <= 0)
//   {
//
//      default_construct();
//
//      return;
//
//   }
//
//   auto dstlen = utf_to_utf_length(this->begin(), p, len);
//
//   create_string(dstlen);
//
//   utf_to_utf((CHARACTER *)this->m_begin, p, len);
//
//   *(CHARACTER*)this->m_end = (CHARACTER)0;
//
//}
//

//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER, int t_size >
//inline string_base < ITERATOR_TYPE >::string_base(const const_string_range_static_array < const OTHER_CHARACTER *, t_size > & a)
//{
//
//   character_count iaLen[t_size];
//
//   character_count * plen = iaLen;
//
//   auto len = a.__utf_length(this->begin(), plen);
//
//   create_string(len);
//
//   auto p = (CHARACTER * ) this->m_begin;
//
//   plen = iaLen;
//
//   a.__utf_concatenate_to(p, plen);
//
//   *p = {};
//
//}


//template < typename ITERATOR_TYPE >
//void string_base< ITERATOR_TYPE >::construct1(const string_base& str)
//{
//
//   this->m_begin = str.m_begin;
//   this->m_end = str.m_end;
//   this->m_erange = str.m_erange;
//
//   auto pbasedata = string_base::NATURAL_META_DATA::from_data(this->m_begin);
//
//   pbasedata->natural_increment_reference_count();
//
//}


//template < typename ITERATOR_TYPE >
//template < typename RANGE >
//void string_base< ITERATOR_TYPE >::construct10(const RANGE& range)/* requires 
//::std::is_base_of_v < ::character_range < const typename string_base < ITERATOR_TYPE >::CHARACTER* >, RANGE >
//&& !
//(::std::is_base_of_v < string_base < ITERATOR_TYPE >, RANGE >
//   || ::std::is_same_v < string_base < ITERATOR_TYPE >, RANGE >)*/
//{
//
//   if (range.m_erange & e_range_string)
//   {
//
//      this->construct1(*(const string_base*)&range);
//
//   }
//   else
//   {
//
//      this->construct5(range.data(), range.size());
//
//   }
//
//}


//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
//inline void string_base < ITERATOR_TYPE >::construct20(const ::character_range < const OTHER_CHARACTER* > & range)
//{
//
//   character_count len = __utf_to_utf_length(this->m_begin, range.m_begin, range.size());
//
//   auto p = create_string(len);
//
//   auto plen = &len;
//
//   range.__utf_concatenate_to(p, plen);
//
//   *p = {};
//
//}


//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
//inline void string_base < ITERATOR_TYPE >::construct20(const OTHER_CHARACTER * start, character_count length, enum_range erange)
//{
//
//   if constexpr (sizeof(CHARACTER) == sizeof(CHARACTER2))
//   {
//
//      if(erange & e_range_string)
//      {
//
//         auto pbasedata = string_base::NATURAL_META_DATA::from_data(start);
//
//         pbasedata->natural_increment_reference_count();
//
//         this->m_begin = start;
//         this->m_end = start + length;
//         this->m_erange = erange;
//
//      }
//      else
//      {
//
//         this->construct1(start, length);
//
//      }
//
//   }
//   else
//   {
//
//      this->construct5(start, length);
//
//   }
//
//}


//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
//inline string_base < ITERATOR_TYPE >::string_base(OTHER_CHARACTER chSrc, character_count repeat) :
//   string_base(nullptr)
//{
//
//   if (repeat <= 0)
//   {
//
//      default_construct();
//
//      return;
//
//   }
//
//   auto lenUnit = utf_to_utf_length(this->begin(), &chSrc, 1);
//
//   auto len = lenUnit * repeat;
//
//   create_string(len);
//
//   CHARACTER sz[8];
//
//   utf_to_utf(sz, &chSrc, 1);
//
//   auto pTarget = (CHARACTER*) this->m_begin;
//
//   while (repeat > 0)
//   {
//
//      auto pSource = sz;
//
//      for (int j = 0; j < lenUnit; j++, pSource++)
//      {
//
//         *pTarget++ = *pSource;
//
//      }
//
//      repeat--;
//
//   }
//
//   *(CHARACTER *)this->m_end = (CHARACTER)0;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(::ansi_character ansich, character_count repeat)
//{
//
//   assign(ansich, repeat);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(::wd16_character wd16ch, character_count repeat)
//{
//
//   assign(wd16ch, repeat);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(::wd32_character wd32ch, character_count repeat)
//{
//
//   assign(wd32ch, repeat);
//
//}


template < typename ITERATOR_TYPE >
inline character_count const_string_range < ITERATOR_TYPE >::unichar_count() const
{

   return ::unichar_count(this->begin());

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const natural_ansistring & ansistrSrc)
//{
//
//   return assign(*this, ansistrSrc);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const natural_wd16string & wd16strSrc)
//{
//
//   return assign(*this, wd16strSrc);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const natural_wd32string & wd32strSrc)
//{
//
//   return assign(*this, wd32strSrc.begin());
//
//}


//template < typename ITERATOR_TYPE >
//template < prototype_character CHARACTER2 >
//string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const ::scoped_string_base <  const CHARACTER2 * > & scopedstr)
//{
//
//   assign(scopedstr);
//
//   return *this;
//
//}



//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const string_base & str)
//{
//
//   assign(scopedstr);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const wd16_string & wd16str)
//{
//
//   return assign(*this, wd16str.begin());
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const wd32_string & wd32str)
//{
//
//   return assign(*this, wd32str.begin());
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const_char_pointer pansichar)
//{
//
//   return assign(*this, pansichar);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const ::wd16_character * pwd16char)
//{
//
//   return assign(*this, pwd16char);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const ::wd32_character * pwd32char)
//{
//
//   return assign(*this, pwd32char);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(::ansi_character ansich)
//{
//
//   return assign(*this, ansich);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(::wd16_character wd16ch)
//{
//
//   return assign(*this, wd16ch);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(::wd32_character wd32ch)
//{
//
//   return assign(*this, wd32ch);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//template < int t_nSize >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator =(const static_string<CHARACTER, t_nSize > & ansistrSrc)
//{
//
//   assign(ansistrSrc);
//
//   return *this;
//
//}

//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const string_base & str)
//{
//
//   return append(scopedstr);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const ::const_ansi_range & scopedstr)
//{
//
//   return append(scopedstr);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const const_wd16_range & wd16scopedstr)
//{
//
//   return append(wd16scopedstr);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const const_wd32_range & wd32scopedstr)
//{
//
//   return append(wd32scopedstr);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const inline_number_string & inlinenumberstring)
//{
//
//   return append(inlinenumberstring);
//
//}



//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const_char_pointer pszSrc)
//{
//
//   return append(scopedstrSrc);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const ::wd16_character * pszSrc)
//{
//
//   return append(scopedstrSrc);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const ::wd32_character * pszSrc)
//{
//
//   return append(scopedstrSrc);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(::ansi_character ansich)
//{
//
//   return append(ansich);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(::wd16_character wd16ch)
//{
//
//   return append(wd16ch);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(::wd32_character wd32ch)
//{
//
//   return append(wd32ch);
//
//}


//template < typename ITERATOR_TYPE >
//template < int t_nSize >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator +=(const static_string<CHARACTER, t_nSize > & ansistrSrc)
//{
//
//   return append(ansistrSrc);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::wd16_character wd16ch) const
//{
//
//   string_base < ITERATOR_TYPE > ansistr;
//
//   ansistr.append(wd16ch);
//
//   return ansistr;
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::wd32_character wd32ch) const
//{
//
//   string_base < ITERATOR_TYPE > ansistr;
//
//   ansistr.append(wd32ch);
//
//   return ansistr;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const_char_pointer psz) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += psz;
//
//   return ::transfer(scopedstr);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const ::wd16_character * pwsz) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += pwsz;
//
//   return ::transfer(scopedstr);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const ::wd32_character * pwsz) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += pwsz;
//
//   return ::transfer(scopedstr);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const_ansi_range ansiscopedstr) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += ansiscopedstr;
//
//   return ::transfer(scopedstr);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const_wd16_range scopedstr) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += scopedstr;
//
//   return ::transfer(scopedstr);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const_wd32_range scopedstr) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += scopedstr;
//
//   return ::transfer(scopedstr);
//
//}



//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const inline_number_string & inlinenumberstring) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr.append(inlinenumberstring);
//
//   return ::transfer(scopedstr);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::ansi_character ansich) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += ansich;
//
//   return ::transfer(scopedstr);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::wd16_character wd16ch) const
//{
//
//   auto scopedstr(*this);
//
//   ansistr += wd16ch;
//
//   return ::transfer(scopedstr);
//
//}
//
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::wd32_character wd32ch) const
//{
//
//   auto scopedstr(*this);
//
//   scopedstr += wd32ch;
//
//   return ::transfer(scopedstr);
//
//}
//


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const string_base & str)
//{
//
//   NATURAL_POINTER::operator=(str);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(string_base && scopedstr)
//{
//
//   NATURAL_POINTER::operator=(::transfer(scopedstr));
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const ansi_string & strSrc)
//{
//
//   return assign(*this, strSrc.begin());
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const wd16_string & strSrc)
//{
//
//   return assign(*this, strSrc.begin());
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const wd32_string & strSrc)
//{
//
//   return assign(*this, strSrc.begin());
//
//}
//




//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const wd16_string & widestrSrc, character_count count)
//{
//
//   return assign(*this, widestrSrc.begin() + pos, count);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const wd32_string & widestrSrc, character_count count)
//{
//
//   return assign(*this, widestrSrc.begin() + pos, count);
//
//}

//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const_char_pointer pszSrc)
//{
//
//   return assign(*this, pszSrc);
//
//}
//


//template < typename ITERATOR_TYPE >
//template < prototype_character CHARACTER2 >
//inline typename string_range < ITERATOR_TYPE >::const_iterator string_range < ITERATOR_TYPE > ::start_count_length(character_count & start, character_count & count, const CHARACTER2 * pszSource)
//{
//
//   character_count len = -1;
//
//   if (start < 0)
//   {
//
//      start = 0;
//
//   }
//
//   if (count < 0)
//   {
//
//      len = string_safe_length(scopedstrSource);
//
//      count += (len - start) + 1;
//
//      if (count < 0)
//      {
//
//         count = 0;
//
//      }
//
//   }
//
//   if (len < 0)
//   {
//
//      len = string_safe_length(scopedstrSource, start + count);
//
//      if (len < 0)
//      {
//
//         return start + count;
//
//      }
//
//   }
//
//   if (count + start > len)
//   {
//
//      count = len - start;
//
//   }
//
//   return len;
//
//}


//template < typename ITERATOR_TYPE >
//inline void string_range < ITERATOR_TYPE >::start_count(character_count & start, character_count & count, character_count len)
//{
//
//   if (start < 0)
//   {
//
//      start = 0;
//
//   }
//
//   if (count < 0)
//   {
//
//      count += (len - start) + 1;
//
//      if (count < 0)
//      {
//
//         count = 0;
//
//      }
//
//   }
//
//   if (count + start > len)
//   {
//
//      count = len - start;
//
//   }
//
//}


//template < typename ITERATOR_TYPE >
//template < prototype_character CHARACTER2 >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const CHARACTER2 * pszSource)
//{
//
//   start_count_length(start, count, pszSource);
//
//   return _assign(scopedstrSource, start, count);
//
//}





template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::unichar_left(character_count count) const
{

   return { this->begin(), this->unichar_at(count) };

}



template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::unichar_mid(character_count iFirst) const
{

   return { this->unichar_at(iFirst), this->end() };

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::unichar_mid(character_count iStart, character_count iCount) const
{

   return { this->unichar_at(iStart), this->unichar_at(iStart + iCount) };

}


template < prototype_character CHARACTER >
inline bool operator>(const CHARACTER * psz, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr)
{

   return string_compare(scopedstr, string_safe_length(scopedstr), scopedstr.begin(), scopedstr.size()) > 0;

}


template < prototype_character CHARACTER >
inline bool operator > (CHARACTER ch, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr)
{

   return string_compare(&ch, 1, scopedstr.begin(), scopedstr.size()) > 0;

}


template < prototype_character CHARACTER >
inline bool operator > (::wide_character ch, const typename ::GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr)
{

   return wide_string(ch) > scopedstr;

}


template < prototype_character CHARACTER >
inline bool operator>(int i, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr)
{

   return ::string_base<CHARACTER>(i) > scopedstr;

}


template < prototype_character CHARACTER >
inline bool operator<(const CHARACTER * psz, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr)
{

   return string_compare(scopedstr, string_save_length(scopedstr), scopedstr.begin(), scopedstr.size()) < 0;

}


template < prototype_character CHARACTER >
inline bool operator<(CHARACTER ch, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr)
{

   return string_compare(&ch, 1, scopedstr.begin(), scopedstr.size()) < 0;

}


template < prototype_character CHARACTER >
inline bool operator<(int i, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr)
{

   return ::string_base <CHARACTER>(i) < scopedstr;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::lower() const
{

   return string_base < ITERATOR_TYPE >(*this).make_lower();

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::upper() const
{

   return string_base < ITERATOR_TYPE >(*this).make_upper();

}


template < prototype_character CHARACTER >
inline const CHARACTER * FormatArgument(const typename GET_BLOCK_TYPE<CHARACTER>::TYPE & scopedstr) noexcept
{

   return scopedstr.begin();

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const SCOPED_STRING & scopedstr) :
//   string_base((const_char_pointer )scopedstr.data(), (character_count)scopedstr.size())
//{
//
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const ansi_string & ansistr)
//{
//
//   assign(ansistr.begin());
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const wd16_string & wd16str)
//{
//
//   assign(wd16str.begin());
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const wd32_string & wd32str)
//{
//
//   assign(wd32str.begin());
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const simple_ansistring & ansistr) :
//   string_base(ansistr.begin())
//{
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const simple_wd16string & wd16str) :
//   string_base(wd16str.begin())
//{
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const simple_wd32string & wd32str) :
//   string_base(wd32str.begin())
//{
//
//}


template < typename ITERATOR_TYPE >
template < prototype_array A_STRING_ARRAY >
bool const_string_range < ITERATOR_TYPE >::contains_any(const A_STRING_ARRAY & stra) const
{

   for (auto & scopedstr : stra)
   {

      if (contains(scopedstr))
      {

         return true;

      }

   }

   return false;

}


template < typename ITERATOR_TYPE >
template < prototype_array A_STRING_ARRAY >
bool const_string_range < ITERATOR_TYPE >::contains_all(const A_STRING_ARRAY & stra) const
{

   for (auto & scopedstr : stra)
   {

      if (!contains(scopedstr))
      {

         return false;

      }

   }

   return true;

}




template < typename ITERATOR_TYPE >
template < prototype_array A_STRING_ARRAY >
bool const_string_range < ITERATOR_TYPE >::case_insensitive_contains_at_least_one_of(const A_STRING_ARRAY & stra) const
{

   for (auto & scopedstr : stra)
   {

      if (case_insensitive_contains(scopedstr))
      {

         return true;

      }

   }

   return false;

}


template < typename ITERATOR_TYPE >
template < prototype_array A_STRING_ARRAY >
bool const_string_range < ITERATOR_TYPE >::case_insensitive_contains_all(const A_STRING_ARRAY & stra) const
{

   for (auto & scopedstr : stra)
   {

      if (!case_insensitive_contains(scopedstr))
      {

         return false;

      }

   }

   return true;

}


template < typename ITERATOR_TYPE >
template < prototype_array A_STRING_ARRAY >
bool const_string_range < ITERATOR_TYPE >::unicode_case_insensitive_contains_at_least_one_of(const A_STRING_ARRAY & stra) const
{

   for (auto & scopedstr : stra)
   {

      if (unicode_case_insensitive_contains(scopedstr))
      {

         return true;

      }

   }

   return false;

}


template < typename ITERATOR_TYPE >
template < prototype_array A_STRING_ARRAY >
bool const_string_range < ITERATOR_TYPE >::unicode_case_insensitive_contains_all(const A_STRING_ARRAY & stra) const
{

   for (auto & scopedstr : stra)
   {

      if (!unicode_case_insensitive_contains(scopedstr))
      {

         return false;

      }

   }

   return true;

}



template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::Tokenize(const SCOPED_STRING & scopedstrTokens, character_count & start) const
{
   ASSERT(start >= 0);

   if (start < 0)
      throw_exception(error_bad_argument);

   if (scopedstrTokens.is_empty())
   {
      if (start < this->size())
      {
         return(string_base < ITERATOR_TYPE >(this->begin() + start));
      }
   }
   else
   {
      const CHARACTER * pszPlace = this->begin() + start;
      const CHARACTER * pszEnd = this->begin() + this->size();
      if (pszPlace < pszEnd)
      {
         character_count nIncluding = string_skip_any_character_in(pszPlace,
            scopedstrTokens);

         if ((pszPlace + nIncluding) < pszEnd)
         {
            pszPlace += nIncluding;
            character_count nExcluding = string_find_first_character_in(pszPlace, scopedstrTokens);

            character_count iFrom = start + nIncluding;
            character_count nUntil = nExcluding;
            start = iFrom + nUntil + 1;

            return this->substr(iFrom, nUntil);

         }

      }

   }

   // return is_empty string_base < ITERATOR_TYPE >, done tokenizing
   start = -1;

   return(string_base < ITERATOR_TYPE >());

}




template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::intersection(const SCOPED_STRING & scopedstrFind) const
{

   string_base < ITERATOR_TYPE > scopedstr;

   for (character_count i = 0; i < this->size(); i++)
   {

      auto ch = this->operator[](i);

      if (scopedstrFind.contains(ch))
      {

         scopedstr += ch;

      }


   }

   return scopedstr;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::concatenate_with_separator(const SCOPED_STRING & scopedstrSeparator, const SCOPED_STRING & scopedstr)
{

   if (this->has_character())
   {
      
      if (scopedstr.has_character())
      {

         this->append(scopedstrSeparator + scopedstr);

      }

   }
   else if (scopedstr.has_character())
   {

      this->assign(scopedstr);

   }

   return *this;

}



template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::get_string(CHARACTER * psz) const noexcept
{

   string_count_copy(psz, this->begin(), this->length());

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::release_buffer(character_count characterCount)
{

   if (characterCount < 0)
   {

      characterCount = string_safe_length(this->begin()) + characterCount + 1;

   }

   //this->NATURAL_POINTER::metadata()->set_character_count(characterCount);

   this->m_end = this->m_begin + characterCount;

   *(CHARACTER *)this->m_end = (CHARACTER) 0;

   return *this;

}


//template < typename ITERATOR_TYPE >
//inline character_count string_base < ITERATOR_TYPE >::storage_character_count() const { return this->NATURAL_POINTER::metadata()->storage_character_count(); }


// template < typename ITERATOR_TYPE >
// inline memsize string_base < ITERATOR_TYPE >::character_count_in_bytes() const { return this->size() * sizeof(CHARACTER); }
//
//
// template < typename ITERATOR_TYPE >
// inline memsize string_base < ITERATOR_TYPE >::null_terminated_character_count_in_bytes() const { return (this->size() +1)* sizeof(CHARACTER); }


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::resize(character_count n, CHARACTER c)
{

   character_count nOldSize = this->length();

   if (n < nOldSize)
   {

      this->truncate(n);

   }
   else
   {

      auto psz = this->get_buffer<true>(n);

      flood_characters(psz + nOldSize, c, n - nOldSize);

      this->release_buffer(n);

   }

}


template < typename ITERATOR_TYPE >
inline typename string_base < ITERATOR_TYPE >::this_iterator string_base < ITERATOR_TYPE >::truncate_on_find_character(CHARACTER ch)
{

   auto p = this->find_first_character(ch);

   if (::is_null(p))
   {

      return nullptr;

   }

   return truncate(p);

}


template < typename ITERATOR_TYPE >
inline typename string_base < ITERATOR_TYPE >::this_iterator & string_base < ITERATOR_TYPE >::truncate(this_iterator p)
{
   
   if(p <= this->begin())
   {
      
      empty();
      
   }
   else if(p < this->end())
   {

      auto pbasedata = this->m_pbasedata;

      if (pbasedata->base_data_is_shared())
      {

         this->assign(this->m_begin, p);

      }
      else
      {

         auto characterCount = p - this->begin();

         //pbasedata->set_character_count(characterCount);

         this->m_end = this->m_begin + characterCount;

         *(CHARACTER *)this->m_end = (CHARACTER) 0;

      }

   }

   return this->end();

}


template < typename ITERATOR_TYPE >
inline typename string_base < ITERATOR_TYPE >::this_iterator & string_base < ITERATOR_TYPE >::erase_beginning(this_iterator p)
{

   //p = minimum_maximum(p, , size());

   assign(p, this->m_end - p);

   return this->m_begin;

}



template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::set_at(character_count iChar, CHARACTER ch)
{

   defer_set_size<true>(maximum(this->size(), iChar + 1));

   //auto p = this->NATURAL_POINTER::metadata();

   //if (iChar >= p->character_count())
   //{

   //   throw ::exception(error_index_out_of_bounds);

   //}

   //if (p->base_data_is_shared())
   //{

   //   fork_string(maximum(p->character_count(), iChar + 1), true);

   //}

   ((CHARACTER *)this->m_begin)[iChar] = ch;

}

template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::contains(const SCOPED_STRING & scopedstr) const
{

   return ::is_set(find(scopedstr));

}


template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::case_insensitive_contains(const SCOPED_STRING & scopedstr) const
{

   return ::is_set(case_insensitive_find(scopedstr));

}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto pFind = find(scopedstr, start, count, ppszEnd);
//
//   if (::is_null(pFind))
//   {
//
//      return false;
//
//   }
//
//   if (ppszBeg)
//   {
//
//      *ppszBeg = psz + iFind;
//
//   }
//
//   return true;
//
//}
//
//
//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto pFind = case_insensitive_find(scopedstr, start, count, ppszEnd);
//
//   if (::is_null(pFind))
//   {
//
//      return false;
//
//   }
//
//   if (ppszBeg)
//   {
//
//      *ppszBeg = psz + iFind;
//
//   }
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(CHARACTER ch) const
//{
//
//   return find(ch, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(::wide_character wch) const
//{
//
//   return find_w(unicode_to_utf8(wch), start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(int i) const // utf8 CHARACTER index
//{
//
//   return find_w(unicode_to_utf8(i), start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(const CHARACTER* psz) const
//{
//
//   return find(scopedstr, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(const SCOPED_STRING & scopedstr) const
//{
//
//   return find(scopedstr, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(CHARACTER ch) const
//{
//
//   return find(ch, start, count) >= 0;
//
//}
//
//
//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(CHARACTER ch) const
//{
//
//   return case_insensitive_find(ch, start, count) >= 0;
//
//}

//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(CHARACTER ch, const CHARACTER ** ppszBeg) const
//{
//
//   auto find = this->find(ch, start, count);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->begin() + find;
//
//   }
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(CHARACTER ch, const CHARACTER ** ppszBeg) const
//{
//
//   auto find = case_insensitive_find(ch, start, count);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->begin() + find;
//
//   }
//
//   return true;
//
//}
//
//
//
//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(::wide_character wch) const
//{
//
//   return unicode_case_insensitive_find(unicode_to_utf8(wch), start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(int i) const// utf8 CHARACTER index
//{
//
//   return unicode_case_insensitive_find(unicode_to_utf8(i), start, count) >= 0;
//
//}

//
//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(const CHARACTER* psz) const
//{
//
//   return case_insensitive_find(scopedstr, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(const SCOPED_STRING & scopedstr) const
//{
//
//   return case_insensitive_find(scopedstr, start, count) >= 0;
//
//}


template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   auto pFind = this->find(scopedstr);

   if (::is_null(pFind))
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = pFind;

   }

   if (::is_set(ppszEnd))
   {

      *ppszEnd = pFind + scopedstr.size();

   }

   return true;

}


template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::case_insensitive_contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   auto pFind = this->case_insensitive_find(scopedstr);

   if (::is_null(pFind))
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = pFind;

   }

   if (::is_set(ppszEnd))
   {

      *ppszEnd = pFind + scopedstr.size();

   }

   return true;

}


template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::unicode_case_insensitive_contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   auto pFind = this->unicode_case_insensitive_find(scopedstr);

   if (::is_null(pFind))
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = pFind;

   }

   if (::is_set(ppszEnd))
   {

      *ppszEnd = pFind + scopedstr.size();

   }

   return true;

}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::unicode_case_insensitive_contains(CHARACTER ch, const CHARACTER ** ppszBeg) const
//{
//
//   auto find = unicode_case_insensitive_find(ch, start, count);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->begin() + find;
//
//   }
//
//   return true;
//
//}

//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto find = this->find(scopedstr, start, count, ppszEnd);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->begin() + find;
//
//   }
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::case_insensitive_contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto find = case_insensitive_find(scopedstr, start, count, ppszEnd);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->begin() + find;
//
//   }
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::unicode_case_insensitive_contains(const SCOPED_STRING & scopedstr, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto find = unicode_case_insensitive_find(scopedstr, start, count, ppszEnd);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->begin() + find;
//
//   }
//
//   return true;
//
//}

//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::unicode_case_insensitive_contains(CHARACTER wch) const
//{
//
//   return unicode_case_insensitive_find(wch, start, count) >= 0;
//
//}

//
//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::unicode_case_insensitive_contains(int i) const// utf8 CHARACTER index
//{
//
//   return unicode_case_insensitive_find(unicode_to_utf8(i), start, count) >= 0;
//
//}


template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::unicode_case_insensitive_contains(const SCOPED_STRING & scopedstr) const
{

   return ::is_set(unicode_case_insensitive_find(scopedstr));

}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::unicode_case_insensitive_contains(const SCOPED_STRING & scopedstr) const
//{
//
//   return unicode_case_insensitive_find(scopedstr, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::erase(character_count start, character_count character_count)
//{
//
//   if (start < 0)
//   {
//
//      character_count = 0;
//
//   }
//
//   if (character_count < 0)
//   {
//
//      character_count = this->size();
//
//   }
//
//   Delete(start, character_count);
//
//   return *this;
//
//}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::erase(character_count iIndex, character_count count)
{

   character_count nLength = this->size();

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (count < 0)
   {

      count = nLength;

   }

   if (count + iIndex > nLength)
   {

      count = nLength - iIndex;

   }

   if (count < 0)
   {

      return *this;

   }

   if (count + iIndex > nLength)
   {

      count = nLength - iIndex;

   }

   if (count > 0)
   {

      character_count nNewLength = nLength - count;

      character_count nCopy = nLength - (iIndex + count) + 1;

      CHARACTER * pszBuffer = get_buffer<true>();

      memory_transfer(pszBuffer + iIndex, pszBuffer + iIndex + count, (size_t)nCopy);

      release_buffer(nNewLength);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline ::collection::count string_base < ITERATOR_TYPE >::insert(character_count i, CHARACTER ch)
{

   if (i < 0)
   {

      i = 0;

   }

   if (i > this->size())
   {

      i = this->size();

   }

   character_count nNewLength = this->size() + 1;

   CHARACTER * pszBuffer = get_buffer<true>(nNewLength);

   memory_transfer(pszBuffer + i + 1, pszBuffer + i, nNewLength - i);

   pszBuffer[i] = ch;

   release_buffer(nNewLength);

   return nNewLength;

}


template < typename ITERATOR_TYPE >
inline ::collection::count string_base < ITERATOR_TYPE >::insert(character_count i, const string_base & str)
{

   if (i < 0)
   {

      i = 0;

   }

   if (i > this->size())
   {

      i = this->size();

   }

   character_count nInsertLength = str.size();

   character_count nNewLength = this->size();

   if (nInsertLength > 0)
   {

      nNewLength += nInsertLength;

      CHARACTER * pszBuffer = get_buffer<true>(nNewLength);

      memory_transfer(pszBuffer + i + nInsertLength, pszBuffer + i, (nNewLength - i - nInsertLength + 1) * sizeof(CHARACTER));

      memory_copy(pszBuffer + i, str.begin(), nInsertLength * sizeof(CHARACTER));

      release_buffer(nNewLength);

   }

   return nNewLength;

}


template < typename ITERATOR_TYPE >
inline ::collection::count string_base < ITERATOR_TYPE >::replace_with(CHARACTER charNew, CHARACTER charOld, character_count start)
{

   character_count count = 0;

   // short-circuit the nop case
   if (charOld != charNew)
   {
      // otherwise modify each character that matches in the string_base < ITERATOR_TYPE >
      bool bCopied = false;
      CHARACTER * pszBuffer = const_cast<CHARACTER *>(this->begin() + start);  // We don't actually write to pszBuffer until we've called get_buffer().

      character_count nLength = this->size();
      character_count iChar = 0;
      while (iChar < nLength)
      {
         // replace instances of the specified character only
         if (pszBuffer[iChar] == charOld)
         {
            if (!bCopied)
            {
               bCopied = true;
               pszBuffer = get_buffer<true>(nLength);
            }
            pszBuffer[iChar] = charNew;
            count++;
         }
         iChar = character_count((pszBuffer + iChar + 1) - pszBuffer);
      }
      if (bCopied)
      {
         release_buffer(nLength);
      }
   }

   return count;
}



template < typename ITERATOR_TYPE >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
::collection::count string_base < ITERATOR_TYPE >::replace_with_count(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count start)
{
   // can't have is_empty or nullptr pszOld


   ::collection::count c = 0;

   // nSourceLen is in XCHARs
   character_count nSourceLen = scopedstrOld.size();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   character_count nReplacementLen = scopedstrNew.size();

   // loop once to figure out the int_size of the result string_base < ITERATOR_TYPE >
   character_count count = 0;

   {

      const CHARACTER * pszStart = this->begin() + start;
      //      const CHARACTER * pszEnd = pszStart+this->size();
      const CHARACTER * pszTarget;

      while ((pszTarget = string_find_string(pszStart, scopedstrOld)) != nullptr)
      {

         count++;

         pszStart = pszTarget + nSourceLen;

         c++;

      }

   }

   // if any changes were made, make them
   if (count > 0)
   {
      // if the buffer is too small, just
      //   allocate a ___new buffer(slow but sure)
      character_count nOldLength = this->size();
      character_count nNewLength = nOldLength + (nReplacementLen - nSourceLen) * count;

      CHARACTER * pszBuffer = get_buffer<true>(maximum(nNewLength, nOldLength));

      const CHARACTER * pszStart = pszBuffer + start;
      const CHARACTER * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHARACTER * pszTarget;

         while ((pszTarget = (CHARACTER *)string_find_string(pszStart, scopedstrOld)) != nullptr)
         {

            character_count nBalance = nOldLength - character_count(pszTarget - pszBuffer + nSourceLen);

            memory_transfer((void *)(pszTarget + nReplacementLen), pszTarget + nSourceLen, nBalance * sizeof(CHARACTER));

            ::memory_copy((void *)pszTarget, scopedstrNew, nReplacementLen * sizeof(CHARACTER));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_buffer(nNewLength);

   }

   return c;

}


template < typename ITERATOR_TYPE >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
::collection::count string_base < ITERATOR_TYPE >::replace_with_ci_count(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count start)
{
   // can't have is_empty or nullptr pszOld


   ::collection::count c = 0;

   // nSourceLen is in XCHARs
   character_count nSourceLen = scopedstrOld.size();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   character_count nReplacementLen = scopedstrOld.size();

   // loop once to figure out the int_size of the result string_base < ITERATOR_TYPE >
   character_count count = 0;
   {
      const CHARACTER * pszStart = this->begin() + start;
      //      const CHARACTER * pszEnd = pszStart+this->size();
      const CHARACTER * pszTarget;
      while ((pszTarget = case_insensitive_string_find_string(pszStart, scopedstrOld)) != nullptr)
      {
         count++;
         pszStart = pszTarget + nSourceLen;
         c++;
      }
   }

   // if any changes were made, make them
   if (count > 0)
   {
      // if the buffer is too small, just
      //   allocate a ___new buffer(slow but sure)
      character_count nOldLength = this->size();
      character_count nNewLength = nOldLength + (nReplacementLen - nSourceLen) * count;

      CHARACTER * pszBuffer = get_buffer<true>(maximum(nNewLength, nOldLength));

      CHARACTER * pszStart = pszBuffer + start;
      CHARACTER * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHARACTER * pszTarget;

         while ((pszTarget = (CHARACTER *)case_insensitive_string_find_string(pszStart, scopedstrOld)) != nullptr)
         {

            character_count nBalance = nOldLength - character_count(pszTarget - pszBuffer + nSourceLen);

            memory_transfer(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER));

            ::memory_copy(pszTarget, scopedstrNew, nReplacementLen * sizeof(CHARACTER));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_buffer(nNewLength);

   }

   return c;

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::replace(const_iterator pszStart, const_iterator pszEnd, const SCOPED_STRING & scopedstr)
{

   auto finalLen = this->size() + scopedstr.size() - (pszEnd - pszStart);

   string str;

   auto psz = str.get_buffer(finalLen);

   memory_copy(psz, this->begin(), pszStart - this->begin());

   memory_copy(psz + (pszStart - this->begin()), scopedstr.begin(), scopedstr.size());

   memory_copy(psz + (pszStart - this->begin()) + scopedstr.size(), pszEnd, this->end() - pszEnd);

   str.release_buffer(finalLen);

   *this = ::transfer(str);

   return *this;

}


template < typename ITERATOR_TYPE >
inline ::collection::count string_base < ITERATOR_TYPE >::erase_character(CHARACTER chRemove)
{

   character_count nLength = this->size();

   CHARACTER * pszBuffer = get_buffer<true>(nLength);

   CHARACTER * pszSource = pszBuffer;

   CHARACTER * pszDest = pszBuffer;

   CHARACTER * pszEnd = pszBuffer + nLength;

   while (pszSource < pszEnd)
   {
      CHARACTER * pszNewSource = pszSource + 1;
      if (*pszSource != chRemove)
      {
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         size_t NewSourceGap = (pszNewSource - pszSource);
         CHARACTER * pszNewDest = pszDest + NewSourceGap;
         size_t i = 0;
         for (i = 0; pszDest != pszNewDest && i < NewSourceGap; i++)
         {
            *pszDest = *pszSource;
            pszSource++;
            pszDest++;
         }
      }
      pszSource = pszNewSource;
   }
   *pszDest = 0;
   character_count count = character_count(pszSource - pszDest);
   release_buffer(nLength - count);

   return(count);

}


template < typename ITERATOR_TYPE >
inline ::collection::count string_base < ITERATOR_TYPE >::erase_any_character_in(const SCOPED_STRING & scopedstrCharacters)
{

      character_count nLength = this->size();

      CHARACTER * pszBuffer = get_buffer<true>(nLength);

      CHARACTER * pszSource = pszBuffer;

      CHARACTER * pszDest = pszBuffer;

      CHARACTER * pszEnd = pszBuffer + nLength;

      while (pszSource < pszEnd)
      {
         CHARACTER * pszNewSource = pszSource + 1;
         if (!scopedstrCharacters.contains(*pszSource))
         {
            // copy the source to the destination.  Remember to copy all bytes of an MBCS character
            // copy the source to the destination.  Remember to copy all bytes of an MBCS character
            size_t NewSourceGap = (pszNewSource - pszSource);
            CHARACTER * pszNewDest = pszDest + NewSourceGap;
            size_t i = 0;
            for (i = 0; pszDest != pszNewDest && i < NewSourceGap; i++)
            {
               *pszDest = *pszSource;
               pszSource++;
               pszDest++;
            }
         }
         pszSource = pszNewSource;
      }
   *pszDest = 0;
   character_count count = character_count(pszSource - pszDest);
   release_buffer(nLength - count);

      return(count);


}

// find the first occurrence of character 'ch', starting at character_count 'start'
template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::find(CHARACTER ch) const RELEASENOTHROW
{

   return this->find_first(ch);

}


// find the first occurrence of character 'ch', starting at character_count 'start'
template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::case_insensitive_find(CHARACTER ch) const RELEASENOTHROW
{
   // start is in XCHARs
   //ASSERT(start >= 0);

   // nLength is in XCHARs
   //character_count nLength = this->size();
//   if (start < 0 || start >= nLength)
//   {
//      return(-1);
//   }

//if(nLength <= 0)
//{
//
//   return -1;
//
//}
//
//   if (count < 0)
//      count = nLength;
//
//   if (count + start > nLength)
//      count = nLength - start;
//
//   if (count < 0)
//      return -1;

   auto psz = this->begin();

   while(psz < this->end())
   {

      if (character_tolower(*psz) == character_tolower(ch))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}



template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::find_first(CHARACTER ch, ::character_count start) const RELEASENOTHROW
{
   
   return ::string_find_character(this->begin() + start, this->end(), ch);

}



// find the first occurrence of string_base < ITERATOR_TYPE > 'scopedstr', starting at character_count 'start'
template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::unicode_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW
{

   const_iterator p;

   auto rangeScope = *this;

   if (this->_initialize_find(p, scopedstr, rangeScope))
   {

      return p;

   }

   auto psz = (const CHARACTER * ) p;

   auto pszBlock = (const CHARACTER * ) scopedstr.begin();

   auto pszBlockEnd = (const CHARACTER *)scopedstr.end();

   for (; psz < rangeScope.m_end; psz++)
   {
      
      auto psz2 = psz;

      auto pszBlock2 = pszBlock;

      int len1;

      int len2;

      do
      {

         if (unicode_index_length(psz2, len1) != unicode_index_length(pszBlock2, len2))
         {

            break;

         }

         psz2 += len1;
         
         pszBlock2 += len2;

      }
      while (pszBlock2 < pszBlockEnd);

      if (pszBlock2 >= pszBlockEnd)
      {
         
         //if (ppszTail)
         //{

         //   *ppszTail = pszBlock2;

         //}
 
         return psz;

      }

      psz = ::unicode_next(psz);

   }

   return nullptr;

}


// find the first occurrence of string_base < ITERATOR_TYPE > 'scopedstr', starting at character_count 'start'
template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::unicode_case_insensitive_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW
{

   const_iterator p;

   auto rangeScope = *this;

   if (this->_initialize_find(p, scopedstr, rangeScope))
   {

      return p;

   }

   auto psz = (const CHARACTER *)p;

//   auto pszBlock = (const CHARACTER *)scopedstr.begin();
//
//   auto pszBlockEnd = (const CHARACTER *)scopedstr.end();

   for (; psz < rangeScope.m_end; psz++)
   {

      bool bFound = true;

      const CHARACTER * psz2 = psz;

      const CHARACTER * pszSub2 = scopedstr;

      int len1;

      int len2;

      while (*psz2 != '\0' && *pszSub2 != '\0') 
      {

         if (unicode_to_lower_case(unicode_index_length(psz2, len1)) !=
            unicode_to_lower_case(unicode_index_length(pszSub2, len2)))
         {

            bFound = false;

            break;

         }

         psz2 += len1;

         psz2 += len2;

      }

      if (bFound)
      {

         if (*pszSub2 == '\0')
         {

        /*    if (ppszTail)
            {

               *ppszTail = psz2;

            }*/

            return psz;

         }
         else
         {

            return nullptr;

         }

      }

      //psz++;

   }

   return nullptr;

}


//template < typename ITERATOR_TYPE >
//inline typename string_range < ITERATOR_TYPE >::const_iterator string_range < ITERATOR_TYPE >::rear_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW
//{
//
//   return rear_find(scopedstr, ::comparison::comparison < CHARACTER >());
//
//}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator += (const SCOPED_STRING & scopedstr)
{

   append(scopedstr);

   return *this;

}


inline string & operator <<(string & str, const_char_pointer psz)
{

   str += psz;

   return str;

}


template < prototype_integral INTEGRAL >
inline string & operator <<(string & str, INTEGRAL i)
{

   str += ::as_string(i);

   return str;

}


template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::unicode_rear_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW
{

   auto psz = (const CHARACTER *)this->begin();

   auto pszEnd = (const CHARACTER *)this->end();
   
   pszEnd = unicode_prior(pszEnd, psz);

   auto pszBlock = (const CHARACTER *)scopedstr.begin();

   auto pszBlockEnd = (const CHARACTER *)scopedstr.end();

   pszBlockEnd = unicode_prior(pszBlockEnd, pszBlock);

   if (::is_null(pszBlockEnd))
   {

      return pszEnd;

   }

   while(::is_set(pszEnd))
   {

      //bool bFound = true;

      const CHARACTER * pszSub2 = pszBlockEnd;

      const CHARACTER * psz2 = pszEnd;

      while (true)
      {

         if (unicode_index(pszBlockEnd) != unicode_index(psz2))
         {

            break;

         }

         pszSub2 = (const CHARACTER *)unicode_prior(pszSub2, pszBlock);

         if (::is_null(pszSub2))
         {
            
            // End of searching block parsing reached.
            // Every unicode character so far is identical.
            // Found matching string.

            return psz;

         }

         psz2 = (const CHARACTER *)unicode_prior(psz2, psz);

         if (is_null(psz2))
         {

            // Premature end of searched string
            // Didn't find matching block.
            // Return nullptr (not found).

            return nullptr;

         }

      }

      pszEnd = (const CHARACTER *)unicode_prior(pszEnd, psz);

   }

   // End of searched string
   // Didn't find matching block.
   // Return nullptr (not found).

   return nullptr;

}


template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::unicode_case_insensitive_rear_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW
{

   auto psz = (const CHARACTER *)this->begin();

   auto pszEnd = (const CHARACTER *)this->end();

   pszEnd = unicode_prior(pszEnd, psz);

   auto pszBlock = (const CHARACTER *)scopedstr.begin();

   auto pszBlockEnd = (const CHARACTER *)scopedstr.end();

   pszBlockEnd = unicode_prior(pszBlockEnd, pszBlock);

   if (::is_null(pszBlockEnd))
   {

      return pszEnd;

   }

   while (::is_set(pszEnd))
   {

      //bool bFound = true;

      const CHARACTER * pszSub2 = pszBlockEnd;

      const CHARACTER * psz2 = pszEnd;

      while (true)
      {

         if (unicode_to_lower_case(unicode_index(pszBlockEnd)) != unicode_to_lower_case(unicode_index(psz2)))
         {

            break;

         }

         pszSub2 = (const CHARACTER *)unicode_prior(pszSub2, pszBlock);

         if (::is_null(pszSub2))
         {

            // End of searching block parsing reached.
            // Every unicode character so far is case-insensitive equivalent.
            // Found matching string.

            return psz;

         }

         psz2 = (const CHARACTER *)unicode_prior(psz2, psz);

         if (is_null(psz2))
         {

            // Premature end of searched string
            // Didn't find matching block.
            // Return nullptr (not found).

            return nullptr;

         }

      }

      pszEnd = (const CHARACTER *)unicode_prior(pszEnd, psz);

   }

   // End of searched string
   // Didn't find matching block.
   // Return nullptr (not found).

   return nullptr;

}


template < typename ITERATOR_TYPE >
typename const_string_range < ITERATOR_TYPE >::CHARACTER const_string_range < ITERATOR_TYPE >::last_char(character_count count) const
{

   return *(this->end() + count);
}



// Convert the string_base < ITERATOR_TYPE > to uppercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::make_upper()
{
   character_count nLength = this->size();
   CHARACTER * pszBuffer = get_buffer<true>(nLength);
   string_uppercase(pszBuffer, nLength + 1);
   release_buffer(nLength);

   return *this;
}

// Convert the string_base < ITERATOR_TYPE > to lowercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::make_lower()
{
   character_count nLength = this->size();
   CHARACTER * pszBuffer = get_buffer<true>(nLength);
   string_lowercase(pszBuffer, nLength + 1);
   release_buffer(nLength);

   return *this;
}

// Reverse the string_base < ITERATOR_TYPE >
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::MakeReverse()
{
   character_count nLength = this->size();
   CHARACTER * pszBuffer = get_buffer<true>(nLength);
   string_reverse(pszBuffer);
   release_buffer(nLength);

   return *this;
}

// trimming

// erase all trailing whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_right()
{

   return trim_right(" \t\r\n");


   //const CHARACTER * pszLast = nullptr;
   //const CHARACTER * pszMax = this->begin() + this->size();
   //auto psz = pszMax;

   //if (scopedstr != nullptr)
   //{

   //   while (true)
   //   {

   //      psz = unicode_prior(scopedstr, this->begin());

   //      if (scopedstr < this->begin())
   //      {

   //         break;

   //      }

   //      if (!unicode_is_whitespace(scopedstr))
   //      {

   //         pszLast = unicode_next(scopedstr);

   //         break;

   //      }

   //   }

   //}

   //if (scopedstrLast != nullptr && pszLast < pszMax)
   //{

   //   // truncate at trailing space start

   //   character_count iLast = character_count(scopedstrLast - this->begin());

   //   truncate(iLast);

   //}

   //return *this;

}

// erase all leading whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_left()
{
   // find first non-space character

   return trim_left(" \t\r\n");

   //auto i = skip_whitespace();

   //if (i > 0)
   //{

   //   erase_beginning(i);

   //}

   //return *this;

   ////auto psz = this->begin();

   ////character_count iHere;

   ////while (unicode_is_whitespace(scopedstr))
   ////{

   ////   unicode_increment(psz);

   ////   iHere = (character_count)(scopedstr - this->begin());

   ////   if (iHere >= size())
   ////   {

   ////      if (iHere == size())
   ////      {

   ////         break;

   ////      }
   ////      else
   ////      {

   ////         return *this;

   ////      }


   ////   }

   ////}


   ////if (scopedstr != this->begin())
   ////{
   ////   // fix up begin and length
   ////   character_count iFirst = character_count(scopedstr - this->begin());

   ////   CHARACTER * pszBuffer = get_buffer<true>(size());

   ////   psz = pszBuffer + iFirst;

   ////   character_count nDataLength = this->size() - iFirst;

   ////   memory_transfer(scopedstrBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER));

   ////   release_buffer(nDataLength);

   ////}

   ////return *this;
}

// erase all leading and trailing whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim()
{
   return(trim_right().trim_left());
}

// erase all leading and trailing occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim(CHARACTER chTarget)
{
   return(trim_right(chTarget).trim_left(chTarget));
}

// erase all leading and trailing occurrences of any of the characters in the string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim(const SCOPED_STRING & scopedstrTargets)
{
   return trim_right(scopedstrTargets).trim_left(scopedstrTargets);
}

// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_right(CHARACTER chTarget)
{

   auto iterator = this->rear_skip(chTarget);

   if (iterator)
   {

      truncate(iterator);

   }

   return *this;

   //// find beginning of trailing matches
   //// by starting at beginning (DBCS aware)

   //auto psz = this->begin();
   //const CHARACTER * pszLast = nullptr;

   //while (*psz != 0)
   //{
   //   if (*psz == chTarget)
   //   {
   //      if (scopedstrLast == nullptr)
   //      {
   //         pszLast = psz;
   //      }
   //   }
   //   else
   //   {
   //      pszLast = nullptr;
   //   }

   //   unicode_increment(psz);

   //}

   //if (scopedstrLast != nullptr)
   //{
   //   // truncate at left-most matching character
   //   character_count iLast = character_count(scopedstrLast - this->begin());
   //   truncate(iLast);
   //}

   //return *this;

}


// erase all trailing occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_right(const SCOPED_STRING & scopedstrCharacters)
//template < pointer_castable < CHARACTER > PCHAR>
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::trim_right(PCHAR szTargets)
{

   auto p = this->rear_skip_any_character_in(scopedstrCharacters);

   if (p < this->end())
   {

      truncate(p);

   }

   return *this;

   //auto pszTargets = scopedstrzTargets.begin();

   //// if we're not trimming anything, we're not doing any work
   //if ((scopedstrTargets == nullptr) || (*pszTargets == 0))
   //{
   //   return *this;
   //}

   //// find beginning of trailing matches
   //// by starting at beginning (DBCS aware)

   //auto psz = this->begin();
   //const CHARACTER * pszStart = psz;
   //const CHARACTER * pszLast = nullptr;

   //while (!::is_null(scopedstr, 1024) && *psz != 0)
   //{
   //   if (string_find_char(scopedstrTargets, *psz) != nullptr)
   //   {
   //      if (scopedstrLast == nullptr)
   //      {
   //         pszLast = psz;
   //      }
   //   }
   //   else
   //   {
   //      pszLast = nullptr;
   //   }

   //   unicode_increment(psz);

   //}

   //if (scopedstrLast != nullptr)
   //{
   //   // truncate at left-most matching character
   //   character_count iLast = character_count(scopedstrLast - pszStart);
   //   truncate(iLast);
   //}

   //return *this;

}


// erase all leading occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_left(CHARACTER chTarget)
{

   auto p = this->skip(chTarget);

   if (::is_set(p) && p > this->begin())
   {

      erase_beginning(p);

   }

   //// find first non-matching character
   //auto psz = this->begin();

   //while (chTarget == *psz)
   //{

   //   unicode_increment(psz);

   //}

   //if (scopedstr != this->begin())
   //{
   //   // fix up begin and length
   //   character_count iFirst = character_count(scopedstr - this->begin());
   //   CHARACTER * pszBuffer = get_buffer<true>(size());
   //   psz = pszBuffer + iFirst;
   //   character_count nDataLength = this->size() - iFirst;
   //   memory_transfer(scopedstrBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER));
   //   release_buffer(nDataLength);
   //}

   return *this;

}


// erase all leading occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_left(const SCOPED_STRING & scopedstrCharacters)
//template < pointer_castable < CHARACTER > PCHAR >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::trim_left(PCHAR szTargets)
{

   auto p = this->skip_any_character_in(scopedstrCharacters);

   if (p > this->begin())
   {

      this->erase_beginning(p);

   }

   return *this;

   //const CHARACTER * pszTargets = szTargets;

   //// if we're not trimming anything, we're not doing any work
   //if ((scopedstrTargets == nullptr) || (*pszTargets == 0))
   //{
   //   return *this;
   //}

   //auto psz = this->begin();
   //while ((*psz != 0) && (string_find_char(scopedstrTargets, *psz) != nullptr))
   //{
   //   unicode_increment(psz);
   //}

   //if (scopedstr != this->begin())
   //{
   //   // fix up begin and length
   //   character_count iFirst = character_count(scopedstr - this->begin());
   //   CHARACTER * pszBuffer = get_buffer<true>(size());
   //   psz = pszBuffer + iFirst;
   //   character_count nDataLength = this->size() - iFirst;
   //   memory_transfer(scopedstrBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER));
   //   release_buffer(nDataLength);
   //}

   //return *this;
}


// erase all trailing whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::right_trimmed() const
{

   string_base < ITERATOR_TYPE > scopedstr(*this);

   scopedstr.trim_right();

   return scopedstr;

}


// erase all leading whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::left_trimmed() const
{

   string_base < ITERATOR_TYPE > scopedstr(*this);

   scopedstr.trim_left();

   return scopedstr;

}


// erase all leading and trailing whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::trimmed() const
{

   string_base < ITERATOR_TYPE > scopedstr(*this);

   scopedstr.trim();

   return scopedstr;

}


// erase all leading and trailing occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::trimmed(CHARACTER chTarget) const
{

   string_base < ITERATOR_TYPE > scopedstr(*this);

   scopedstr.trim(chTarget);

   return scopedstr;

}


// erase all leading and trailing occurrences of any of the characters in the string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::trimmed(const SCOPED_STRING & scopedstrCharacters) const
{

   auto scopedstr(*this);

   scopedstr.trim(scopedstrCharacters);

   return ::transfer(scopedstr);

}


// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::right_trimmed(CHARACTER chTarget) const
{

   auto scopedstr(*this);

   scopedstr.trim_right(chTarget);

   return ::transfer(scopedstr);

}


// erase all trailing occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::right_trimmed(const SCOPED_STRING & scopedstrCharacters) const
{

   auto scopedstr(*this);

   scopedstr.trim_right(scopedstrCharacters);

   return ::transfer(scopedstr);

}


// erase all leading occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::left_trimmed(CHARACTER chTarget) const
{

   string_base < ITERATOR_TYPE > scopedstr(*this);

   scopedstr.trim_left(chTarget);

   return scopedstr;

}


// erase all leading occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::left_trimmed(const SCOPED_STRING & scopedstrCharacters) const
{

   auto scopedstr(*this);

   scopedstr.trim_left(scopedstrCharacters);

   return ::transfer(scopedstr);

}


template < typename ITERATOR_TYPE >
const_string_range < ITERATOR_TYPE > const_string_range < ITERATOR_TYPE >::subrange(character_count start) const
{

   return subrange(start, -1);

}


template < typename ITERATOR_TYPE >
template < prototype_integral START, prototype_integral COUNT >
const_string_range < ITERATOR_TYPE > const_string_range < ITERATOR_TYPE >::subrange(START start, COUNT count) const
{

   character_count length = this->size();

   if (start < 0)
   {

      start = 0;

   }
   else if ((::character_count)start >= length)
   {

      return {};

   }

   character_count end;

   if (count < 0)
   {

      end = length + count + 1;

   }
   else
   {

      end = start + count;

   }

   if (end > length)
   {

      end = length;

   }

   if (end <= (::character_count)start)
   {

      return {};

   }

   return { this->begin() + start, (::character_count)(end - start) };

}


//template < typename ITERATOR_TYPE >
//template < prototype_integral START >
//typename string_base < ITERATOR_TYPE >::BASE_RANGE string_base < ITERATOR_TYPE >::substr(START start) const
//{
//   
//   return substr(start, -1);
//
//}


//template < typename ITERATOR_TYPE >
//template < prototype_integral START, prototype_integral COUNT >
//typename string_base < ITERATOR_TYPE >::BASE_RANGE string_base < ITERATOR_TYPE >::substr(START start, COUNT count) const
//{
//
// /*  character_count length = this->size();
//
//   if (start < 0)
//   {
//
//      start = 0;
//
//   }
//   else if ((::character_count)start >= length)
//   {
//
//      return {};
//
//   }
//
//   character_count end;
//
//   if (count < 0)
//   {
//
//      
//
//   }
//
//   if (end > length)
//   {
//
//      end = length;
//
//   }
//
//   if (end <= (::character_count) start)
//   {
//
//      return {};
//
//   }*/
//
//   auto sizeThis = this->size();
//
//   auto start = this->begin() + minimum(start, sizeThis);
//
//   auto end = minimum(count < 0 ? length + count + 1 : start + count, sizeThis);
//
//   return start == 0 && end == sizeThis
//   ?
//   *this :
//   {
//      this->m_begin + start,
//      this->m_begin + end,
//      !(*this->end) ? e_range_null_terminated : e_range_none
//   };
//
//}
//

template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::clear()
{

   empty();

}



template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append_formatf_arguments(const CHARACTER * pszFormat, va_list args)
{

   ASSERT(is_string_ok(pszFormat));

   character_count nCurrentLength = this->size();

   va_list argsForCount;

   va_copy(argsForCount, args);

   character_count nAppendLength = get_formatted_length(pszFormat, argsForCount);

   va_end(argsForCount);

   auto p = get_buffer<true>(nCurrentLength + nAppendLength);

   _string_format(p + nCurrentLength, nAppendLength + 1, pszFormat, args);

   release_buffer(nCurrentLength + nAppendLength);

   return *this;

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::formatf_arguments(const CHARACTER * pszFormat, va_list args)
{

   ASSERT(is_string_ok(pszFormat));

   if (pszFormat == nullptr)
   {

      throw_exception(error_bad_argument);

   }

   va_list ptr1;

   va_copy(ptr1, args);

   character_count nLength = get_formatted_length(pszFormat, ptr1);

   if (nLength < 0)
   {

      throw ::exception(error_failed);

   }

   va_end(ptr1);

   CHARACTER * pszBuffer = get_buffer(nLength);

   va_list ptr2;

   va_copy(ptr2, args);

   _string_format(pszBuffer, nLength + 1, pszFormat, ptr2);

   va_end(ptr2);

   release_buffer(nLength);

   return *this;

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::formatf(const CHARACTER * pszFormat, ...)
{

   ASSERT(is_string_ok(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   formatf_arguments(pszFormat, argList);

   va_end(argList);

   return *this;

}


// append formatted begin using format string_base < ITERATOR_TYPE > 'pszFormat'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append_formatf(const CHARACTER * pszFormat, ...)
{

   ASSERT(is_string_ok(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   append_formatf_arguments(pszFormat, argList);

   va_end(argList);

   return *this;

}


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::reserve(character_count res_arg)
{
   get_buffer<true>(res_arg + 1);
}



// Convert the string_base < ITERATOR_TYPE > to uppercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::uppered() const
{

   return string_base < ITERATOR_TYPE >(*this).make_upper();

}


// Convert the string_base < ITERATOR_TYPE > to lowercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::reversed() const
{

   return string_base < ITERATOR_TYPE >(*this).MakeReverse();

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::unichar_substr(character_count iFirst) const
{

   return unichar_substr(iFirst, -1);

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::unichar_substr(character_count iFirst, character_count count) const
{

   const CHARACTER * pchStart = *this;

   if (pchStart == nullptr)
      return "";

   ::collection::count iUtf8Len = this->unichar_count();

   if (iFirst < 0)
      iFirst = iUtf8Len + iFirst;

   if (count < 0)
      count = iUtf8Len - iFirst + count + 1;

   if (iFirst + count > iUtf8Len)
      count = iUtf8Len - iFirst;

   if (count <= 0)
      return "";

   ::collection::count ca = 0;

   while (ca < iFirst && *pchStart != '\0')
   {

      pchStart = unicode_next(pchStart);

      ca++;

   }

   if (*pchStart == '\0')
      return "";

   const CHARACTER * pchEnd = pchStart;

   ca = 0;

   while (ca < count && *pchEnd != '\0')
   {

      pchEnd = unicode_next(pchEnd);

      ca++;

   }

   return string_base < ITERATOR_TYPE >(pchStart, pchEnd - pchStart);


}

//template < typename ITERATOR_TYPE >
//::collection::count string_base < ITERATOR_TYPE >::unichar_count() const
//{
//
//   const CHARACTER* pch = *this;
//
//   if (pch == nullptr)
//      return 0;
//
//   ::collection::count cCharCount = 0;
//
//   while (pch != nullptr && *pch != '\0')
//   {
//
//      pch = __utf8_inc(pch);
//
//      cCharCount++;
//
//   }
//
//   return cCharCount;
//
//}


template < typename ITERATOR_TYPE >
inline typename const_string_range < ITERATOR_TYPE >::const_iterator const_string_range < ITERATOR_TYPE >::unichar_at(character_count iUnicharIndex) const
{

   auto p = this->begin();

   while (p < this->end() && iUnicharIndex > 0)
   {

      auto iLen = unicode_len(p);

      p += iLen;

   }

   return p;

}



template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::eat_before(string_base < ITERATOR_TYPE > & strBefore, const SCOPED_STRING & scopedstrSeparator, bool bEatEverythingIfNotFound)
{

   ASSERT(this != &strBefore);

   if (this == &strBefore)
   {

      return false;

   }

   auto pFind = this->find(scopedstrSeparator);

   if (::is_null(pFind))
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = *this;

         this->empty();

      }

      return false;

   }

   strBefore = (*this)(0, pFind);

   *this = (*this)(pFind + scopedstrSeparator.size());

   return true;

}



template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::eat_before_let_separator(string_base < ITERATOR_TYPE > & strBefore, const SCOPED_STRING & scopedstrSeparator, bool bEatEverythingIfNotFound)
{

   ASSERT(this != &strBefore);

   if (this == &strBefore)
   {

      return false;

   }

   auto pFind = this->find(scopedstrSeparator);

   if (::is_null(pFind))
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = *this;

         *this = scopedstrSeparator;

      }

      return false;

   }

   strBefore = (*this)(0, pFind);

   *this = (*this)(pFind);

   return true;

}


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::add(CHARACTER ch)
{

   operator += (ch);

}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator = (const ::string_stream& scopedstr)
//{
//
//   return this->operator =(scopedstr.operator const SCOPED_STRING & scopedstr ());
//
//}
//















//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::begins(const SCOPED_STRING & scopedstr) const
//{
//
//   return string_range_begins<CHARACTER>(*this,scopedstr);
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::ends(const SCOPED_STRING & scopedstr) const
//{
//
//   return string_range_ends<CHARACTER>(*this, scopedstr);
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::begins(const SCOPED_STRING & scopedstr) const
//{
//
//   return BASE_RANGE::begins(scopedstr, ::comparison::comparison < CHARACTER >());
//
//}
//
//
//
//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::ends(const SCOPED_STRING & scopedstr) const
//{
//
//   return BASE_RANGE::ends(scopedstr, ::comparison::comparison < CHARACTER >());
//
//}



template < typename ITERATOR_TYPE >
inline bool const_string_range < ITERATOR_TYPE > ::case_insensitive_begins(const SCOPED_STRING & scopedstr) const
{

   return this->begins(scopedstr, ::comparison::case_insensitive < CHARACTER >());

}



template < typename ITERATOR_TYPE >
inline bool const_string_range < ITERATOR_TYPE > ::case_insensitive_ends(const SCOPED_STRING & scopedstr) const
{

   return this->ends(scopedstr, ::comparison::case_insensitive < CHARACTER >());

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::begins_eat(const SCOPED_STRING & scopedstrPrefix)
{

   if (!this->begins(scopedstrPrefix))
   {

      return false;

   }

   assign(this->begin() + scopedstrPrefix.size(), this->size() - scopedstrPrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::ends_eat(const SCOPED_STRING & scopedstrSuffix)
{

   if (!this->ends(scopedstrSuffix))
   {

      return false;

   }

   assign(this->begin(), this->size() - scopedstrSuffix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins_eat(const SCOPED_STRING & scopedstrPrefix)
{

   if (!this->case_insensitive_begins(scopedstrPrefix))
   {

      return false;

   }

   assign(this->begin() + scopedstrPrefix.size(), this->size() - scopedstrPrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends_eat(const SCOPED_STRING & scopedstrSuffix)
{

   if (!this->case_insensitive_ends(scopedstrSuffix))
   {

      return false;

   }

   assign(this->begin(), this->size() - scopedstrSuffix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::begins_replace(const SCOPED_STRING & scopedstrNewPrefix, const SCOPED_STRING & scopedstrPrefix)
{

   if(!begins_eat(scopedstrPrefix))
   {

      return false;

   }

   *this = scopedstrNewPrefix + *this;

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins_replace(const SCOPED_STRING & scopedstrNewPrefix, const SCOPED_STRING & scopedstrPrefix)
{

   if(!this->case_insensitive_begins_eat(scopedstrPrefix))
   {

      return false;

   }

   *this = scopedstrNewPrefix + *this;

   return true;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_prefix(const SCOPED_STRING & scopedstrPrefix)
{

   if (!this->begins(scopedstrPrefix))
   {

      operator =(scopedstrPrefix + *this);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::case_insensitive_ensure_prefix(const SCOPED_STRING & scopedstrPrefix)
{

   if (!this->case_insensitive_begins(scopedstrPrefix))
   {

      operator =(scopedstrPrefix + *this);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_suffix(const SCOPED_STRING & scopedstrSuffix)
{

   if (!this->ends(scopedstrSuffix))
   {

      operator =(*this + scopedstrSuffix);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::case_insensitive_ensure_suffix(const SCOPED_STRING & scopedstrSuffix)
{

   if (!this->case_insensitive_ends(scopedstrSuffix))
   {

      operator =(*this + scopedstrSuffix);

   }

   return *this;

}



template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::defer_prefixed(const SCOPED_STRING & scopedstrPrefix) const
{

   if (!this->begins(scopedstrPrefix))
   {

      return scopedstrPrefix + *this;

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::case_insensitive_defer_prefixed(const SCOPED_STRING & scopedstrPrefix) const
{

   if (!this->case_insensitive_begins(scopedstrPrefix))
   {

      return scopedstrPrefix + *this;

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::defer_suffixed(const SCOPED_STRING & scopedstrSuffix) const
{

   if (!this->ends(scopedstrSuffix))
   {

      return *this + scopedstrSuffix;

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::case_insensitive_defer_suffixed(const SCOPED_STRING & scopedstrSuffix) const
{

   if (!this->case_insensitive_ends(scopedstrSuffix))
   {

      return *this + scopedstrSuffix;

   }

   return *this;

}

//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::begins(const CHARACTER * pszPrefix) const
//{
//
//   auto psz = this->begin();
//
//   while (*psz && *pszPrefix)
//   {
//
//      if (*psz != *pszPrefix)
//      {
//
//         return false;
//
//      }
//
//      psz++;
//
//      pszPrefix++;
//
//   }
//
//   return !*pszPrefix;
//
//}
//

//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::begins(const SCOPED_STRING & scopedstrPrefix) const
//{
//
//   auto psz = this->begin();
//
//   auto pszPrefix = scopedstrPrefix.begin();
//
//   auto pszPrefixEnd = scopedstrPrefix.end();
//
//   while (*psz && pszPrefix < pszPrefixEnd)
//   {
//
//      if (*psz != *pszPrefix)
//      {
//
//         return false;
//
//      }
//
//      psz++;
//
//      pszPrefix++;
//
//   }
//
//   return pszPrefix == pszPrefixEnd;
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::ends(const SCOPED_STRING & scopedstrSuffix) const
//{
//
//   return string_ends(this->begin(), this->size(), scopedstrSuffix, scopedstrSuffix.size());
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins(const SCOPED_STRING & scopedstrPrefix) const
//{
//
//   auto psz = this->begin();
//
//   auto pszPrefix = scopedstrPrefix.begin();
//
//   auto pszPrefixEnd = scopedstrPrefix.end();
//
//   while (*psz && pszPrefix < pszPrefixEnd)
//   {
//
//      if (character_tolower(*psz) != character_tolower(*pszPrefix))
//      {
//
//         return false;
//
//      }
//
//      psz++;
//
//      pszPrefix++;
//
//   }
//
//   return pszPrefix == pszPrefixEnd;
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends(const SCOPED_STRING & scopedstrSuffix) const
//{
//
//   return case_insensitive_string_ends(this->begin(), this->size(), scopedstrSuffix, scopedstrSuffix.size());
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::begins_eat(const SCOPED_STRING & scopedstrPrefix)
//{
//
//   character_count lenPrefix;
//
//   if (!_string_begins(this->begin(), this->size(), scopedstrPrefix, lenPrefix))
//   {
//
//      return false;
//
//   }
//
//   assign(this->begin() + lenPrefix, this->size() - lenPrefix);
//
//   return true;
//
//}
//

//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::ends_eat(const SCOPED_STRING & scopedstrSuffix)
//{
//
//   character_count lenSuffix;
//
//   if (!_string_ends(this->begin(), this->size(), scopedstrSuffix, lenSuffix))
//   {
//
//      return false;
//
//   }
//
//   truncate(this->size() - lenSuffix);
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins_eat(const SCOPED_STRING & scopedstrPrefix)
//{
//
//   character_count lenPrefix;
//
//   if (!case_insensitive__string_begins(this->begin(), this->size(), scopedstrPrefix, lenPrefix))
//   {
//
//      return false;
//
//   }
//
//   assign(this->begin() + lenPrefix, this->size() - lenPrefix);
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends_eat(const SCOPED_STRING & scopedstrSuffix)
//{
//
//   character_count lenSuffix;
//
//   if (!case_insensitive__string_ends(this->begin(), this->size(), scopedstrSuffix, lenSuffix))
//   {
//
//      return false;
//
//   }
//
//   truncate(this->size() - lenSuffix);
//
//   return true;
//
//}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::begins_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstrPrefix) const
{

   if (!this->begins(scopedstrPrefix))
   {

      return false;

   }

   strRemainder.assign(this->begin() + scopedstrPrefix.size(), this->size() - scopedstrPrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::ends_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstrSuffix) const
{

   if (!this->ends(scopedstrSuffix))
   {

      return false;

   }

   strRemainder.assign(this->begin(), this->size() - scopedstrSuffix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstrPrefix) const
{

   if (!this->case_insensitive_begins(scopedstrPrefix))
   {

      return false;

   }

   strRemainder.assign(this->begin() + scopedstrPrefix.size(), this->size() - scopedstrPrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstrSuffix) const
{

   if (!this->case_insensitive_ends(scopedstrSuffix))
   {

      return false;

   }

   strRemainder.assign(this->begin(), this->size() - scopedstrSuffix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::begins_bitten(const SCOPED_STRING & scopedstrPrefix) const
{

   if (!this->begins(scopedstrPrefix))
   {

      return *this;

   }

   return { this->begin() + scopedstrPrefix.size(), this->size() - scopedstrPrefix.size() };

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::ends_bitten(const SCOPED_STRING & scopedstrSuffix) const
{

   if (!this->ends(scopedstrSuffix))
   {

      return *this;

   }

   return { this->begin(), this->size() - scopedstrSuffix.size()};

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::case_insensitive_begins_bitten(const SCOPED_STRING & scopedstrPrefix) const
{

   if (!this->case_insensitive_begins(scopedstrPrefix))
   {

      return *this;

   }

   return { this->begin() + scopedstrPrefix.size(), this->size() - scopedstrPrefix.size()};

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::case_insensitive_ends_bitten(const SCOPED_STRING & scopedstrSuffix) const
{

   if (!this->case_insensitive_ends(scopedstrSuffix))
   {

      return *this;

   }

   return { this->begin(), this->size() - scopedstrSuffix.size()};

}



template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::begins_erase_get_erased(string_base & strErased, const SCOPED_STRING & scopedstrPrefix)
{

   if (!this->case_insensitive_begins(scopedstrPrefix))
   {

      return false;

   }

   strErased.assign(this->begin(), scopedstrPrefix.size());

   assign(this->begin() + scopedstrPrefix.size(), this->size() - scopedstrPrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::ends_erase_get_erased(string_base & strErased, const SCOPED_STRING & scopedstrSuffix)
{

   if (!this->case_insensitive_ends(scopedstrSuffix))
   {

      return false;

   }

   strErased.assign(this->begin() + this->length() - scopedstrSuffix.size(), scopedstrSuffix.size());

   assign(this->begin(), this->size() - scopedstrSuffix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::case_insensitive_begins_eaten(const SCOPED_STRING & scopedstrPrefix) const
{

   if (!this->case_insensitive_begins(scopedstrPrefix))
   {

      return {};

   }

   return { this->begin(), scopedstrPrefix.size() };

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE > ::case_insensitive_ends_eaten(const SCOPED_STRING & scopedstrSuffix) const
{

   if (!this->case_insensitive_ends(scopedstrSuffix))
   {

      return {};

   }

   return { this->begin() + this->length() - scopedstrSuffix.size(), scopedstrSuffix.size() };

}


template < typename ITERATOR_TYPE >
// replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
template < typename EQUALITY >
inline ::collection::count string_base < ITERATOR_TYPE > ::_replace_with(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count start, EQUALITY equality)
{

   // nSourceLen is in XCHARs
   character_count nReplacedLen = scopedstrOld.size();

   if (nReplacedLen == 0)
   {

      return 0;

   }

   // nReplacementLen is in XCHARs
   character_count nReplacementLen = scopedstrNew.size();

   // loop once to figure out the int_size of the result string_base < ITERATOR_TYPE >
   auto count = (*this)(start)._occurrence_count_of(scopedstrOld, equality);

   // if any changes were made, make them
   if (count <= 0) 
   {

      return 0;

   }

   // if the buffer is too small, just
   //   allocate a ___new buffer(slow but sure)

   character_count nNewLength = this->size() + (nReplacementLen - nReplacedLen) * count;

   string_base < ITERATOR_TYPE > str;

   CHARACTER * pszBuffer = str.get_buffer(nNewLength);

   CHARACTER * pLastNewEnd = pszBuffer;

   BASE_RANGE rangeOld = *this;

   memory_copy(pLastNewEnd, rangeOld.begin(), start * sizeof(CHARACTER));

   rangeOld.begin() += start;

   pLastNewEnd += start;

   CHARACTER * pszTarget;

   while ((pszTarget = (CHARACTER *)rangeOld.find(scopedstrOld, equality)) != nullptr)
   {

      auto offset = pszTarget - rangeOld.begin();

      memory_copy(pLastNewEnd,rangeOld.begin(), offset * sizeof(CHARACTER));

      pLastNewEnd += offset;

      memory_copy(pLastNewEnd, scopedstrNew.begin(), nReplacementLen * sizeof(CHARACTER));

      rangeOld.m_begin = pszTarget + nReplacedLen;

      pLastNewEnd += nReplacementLen;

   }

   memory_copy(pLastNewEnd,rangeOld.begin(), (rangeOld.end() - rangeOld.begin()) * sizeof(CHARACTER));

   str.release_buffer(nNewLength);

   *this = ::transfer(str);

   return count;

}





template < prototype_character CHARACTER >
void CopyCharsOverlapped(CHARACTER * pchDest, const CHARACTER * pchSrc, character_count nChars) noexcept
{

   memory_transfer(pchDest, pchSrc, nChars * sizeof(CHARACTER));

}


template < prototype_character CHARACTER >
void CopyCharsOverlapped(CHARACTER * pchDest, size_t nDestLen, const CHARACTER * pchSrc, character_count nChars) noexcept
{

   memory_transfer(pchDest, pchSrc, nChars * sizeof(CHARACTER));

}



template < typename STRING >
inline STRING & string_concatenate(STRING & scopedstr, const typename STRING::CHARACTER * psz1, character_count nLength1, const typename STRING::CHARACTER * psz2, character_count nLength2)
{

   character_count nNewLength = nLength1 + nLength2;

   typename STRING::CHARACTER * pszBuffer = scopedstr.get_buffer(nNewLength);

   string_count_copy(pszBuffer, psz1, nLength1);

   string_count_copy(pszBuffer + nLength1, psz2, nLength2);

   scopedstr.release_buffer(nNewLength);

   return scopedstr;

}


template < typename STRING >
inline bool string_ends_eat(STRING & ansistr, const STRING & scopedstrSuffix)
{

   auto lenSuffix = scopedstrSuffix.length();

   if (lenSuffix > ansistr.length())
   {

      return false;

   }

   if (STRING::string_count_compare(ansistr.reverse_ptr_at(lenSuffix), scopedstrSuffix, lenSuffix) != 0)
   {

      return false;

   }

   ansistr.reverse_truncate(lenSuffix);

   return true;

}



int get_mem_free_available_kb();


template < prototype_character CHARACTER >
::wd32_character unicode_iterator < CHARACTER > ::operator *() { return unicode_index(m_psz); }


template < prototype_character CHARACTER >
unicode_iterator < CHARACTER > & unicode_iterator < CHARACTER > ::operator ++()
{

   unicode_increment(m_psz);

   return *this;

}


template < prototype_character CHARACTER >
unicode_iterator < CHARACTER > unicode_iterator < CHARACTER > ::operator ++(int)
{

   auto psz = m_psz;

   unicode_increment(m_psz);

   return psz;

}



template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > operator +(const scoped_string_base < ITERATOR_TYPE > & scopedstr, const inline_number_string & inlinenumberstring)
{

   string_base < ITERATOR_TYPE > str(scopedstr);

   string_base < ITERATOR_TYPE > strNumber(inlinenumberstring);

   str.append(strNumber);

   return ::transfer(scopedstr);

}


template < character_count n >
inline ::string_base < const_char_pointer >operator +(const char (&s)[n], const inline_number_string& inlinenumberstring)
{

   return { ::as_string_literal<char, n>(s), inlinenumberstring };

}


//template < character_count m_sizeMaximumLength >
//inline ::string operator +(const ::scoped_string & scopedstr, const ::inline_string < char, m_sizeMaximumLength > & inlinestring)
//{
//
//   return str + ::string(inlinestring);
//
//}
//
//
//template < ::collection::count c >
//inline ::string operator +(const ::scoped_string & scopedstr, const char(&sz)[c])
//{
//
//   return str + ::string(sz);
//
//}







//template < ::collection::count c, character_count m_sizeMaximumLength >
//inline ::string operator +(const char(&sz)[c], const ::inline_string < char, m_sizeMaximumLength > & inlinestring)
//{
//
//   return ::transfer(::string(sz) + ::string(inlinestring));
//
//}
//
//
//
//template < ::collection::count c, character_count m_sizeMaximumLength >
//inline ::string operator +(const ::inline_string < char, m_sizeMaximumLength > & inlinestring, const char(&sz)[c])
//{
//
//   return ::transfer(::string(inlinestring) + ::string(sz));
//
//}


//inline ::string operator + (const ::scoped_string & scopedstr, char ch)
//{
//
//   return str + ::string(ch);
//
//}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >::string_base(const ::atom& atom) :
   string_base(atom.as_string())
{


}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE >::string_base(const ::payload & payload) :
   string_base(payload.as_string())
{


}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >::string_base(const property & property) :
   string_base(property.as_string())
{


}




//
//
//
//template < typename ITERATOR_TYPE >
//inline string_base< ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_ansi_string & ansistr) { assign_range(ansistr); return *this; }
//
//template < typename ITERATOR_TYPE >
//inline string_base< ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_wd16_string & wd16str) { assign_range(wd16str); return *this; }
//
//template < typename ITERATOR_TYPE >
//inline string_base< ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_wd32_string & wd32str) { assign_range(wd32str); return *this; }
//


template < typename ITERATOR_TYPE >
inline typename scoped_string_base < ITERATOR_TYPE >::STRING scoped_string_base < ITERATOR_TYPE > ::as_string() const
{

   return *this;

}


template < typename ITERATOR_TYPE >
inline typename scoped_string_base < ITERATOR_TYPE >::BASE_RANGE scoped_string_base < ITERATOR_TYPE > ::rear_word(CHARACTER ch) const
{

   auto p = this->rear_find(ch);

   if (!p)
   {

      return {};

   }

   return {::unicode_next(p), this->m_end};

}


template < typename ITERATOR_TYPE >
inline typename scoped_string_base < ITERATOR_TYPE >::BASE_RANGE scoped_string_base < ITERATOR_TYPE > ::rear_prefix(CHARACTER ch) const
{

   auto p = this->rear_find(ch);

   if (!p)
   {

      return {};

   }

   return {this->m_begin, p};

}


#include "acme/prototype/string/c_string.h"


template < typename ITERATOR_TYPE >
string_base<ITERATOR_TYPE>::string_base(const ::c::string & cstring) :
   string_base(cstring.m_psz)
{


}





template<typename ITERATOR_TYPE>
inline const ::block string_base<ITERATOR_TYPE>::block_with_null_terminator() const
{

   return {(const void *) this->data(), this->size_in_bytes_with_null_terminator()};

}
