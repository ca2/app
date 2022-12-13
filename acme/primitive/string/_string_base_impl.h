//
//  _string_base_impl.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


//#include "acme/exception/debug.h"
////#include "acme/primitive/primitive/range.h"
//#include "simple_string_base.h"



template < primitive_character CHARACTER, ::comparison::ordering < CHARACTER > ORDERING >
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


template < primitive_character CHARACTER >
constexpr ::std::strong_ordering _sz_compare(const CHARACTER * pA, const CHARACTER * pB) noexcept
{

   return _sz_compare(pA, pB, ::comparison::comparison<CHARACTER>());

}


template < primitive_character CHARACTER >
constexpr ::std::strong_ordering _sz_compare_ci(const CHARACTER * pA, const CHARACTER * pB) noexcept
{

   return _sz_compare(pA, pB, ::comparison::case_insensitive < CHARACTER >());

}


template < primitive_character CHARACTER, ::comparison::ordering < CHARACTER > ORDERING >
inline ::std::strong_ordering _sz_count_compare(const CHARACTER * pA, const CHARACTER * pB, strsize sizeB, ORDERING ordering) noexcept
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


template < primitive_character CHARACTER >
constexpr ::std::strong_ordering _sz_count_compare(const CHARACTER * pA, const CHARACTER * pB, strsize sizeB) noexcept
{

   return _sz_count_compare(pA, pB, sizeB, ::comparison::comparison<CHARACTER>());

}


template < primitive_character CHARACTER >
constexpr ::std::strong_ordering _sz_count_compare_ci(const CHARACTER * pA, const CHARACTER * pB, strsize sizeB) noexcept
{

   return _sz_count_compare(pA, pB, sizeB, ::comparison::case_insensitive < CHARACTER >());

}


template < primitive_character CHARACTER, ::comparison::ordering < CHARACTER > ORDERING >
inline ::std::strong_ordering _count_sz_compare(const CHARACTER * pA, strsize sizeA, const CHARACTER * pB, ORDERING ordering) noexcept
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


template < primitive_character CHARACTER >
constexpr ::std::strong_ordering _count_sz_compare(const CHARACTER * pA, strsize sizeA, const CHARACTER * pB) noexcept
{

   return _count_sz_compare(pA, sizeA, pB, ::comparison::comparison<CHARACTER>());

}


template < primitive_character CHARACTER >
constexpr ::std::strong_ordering _count_sz_compare_ci(const CHARACTER * pA, strsize sizeA, const CHARACTER * pB) noexcept
{

   return _count_sz_compare(pA, sizeA, pB, ::comparison::case_insensitive < CHARACTER >());

}



//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering _string_compare_ci(const CHARACTER * pszA, strsize sizeA, const ::ansi_character * pszB, strsize sizeB) noexcept
//{
//
//   strsize lenCompare = minimum(sizeA, sizeB);
//
//   auto ordering = string_count_compare_ci(pszA, pszB, lenCompare);
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
inline ::std::strong_ordering _range_collate(::string_range < ITERATOR_TYPE > rangeA, ::string_range < ITERATOR_TYPE > rangeB) noexcept
{

   strsize len = minimum(rangeA.size(), rangeB.size());

   auto order = string_count_collate(rangeA.begin(), rangeB.begin(), len);

   if (order != 0)
   {

      return order;

   }

   return rangeA.size() <=> rangeB.size();

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering _case_insensitive_range_collate(::string_range < ITERATOR_TYPE > rangeA, ::string_range < ITERATOR_TYPE > rangeB) noexcept
{

   strsize len = minimum(rangeA.size(), rangeB.size());

   auto order = case_insensitive_string_count_collate(rangeA.begin(), rangeB.begin(), len);

   if (order != 0)
   {

      return order;

   }

   return rangeA.size() <=> rangeB.size();

}


//template < typename ITERATOR_TYPE >
//inline i32 string_compare(const CHARACTER * pszA, strsize sizeA, const ::ansi_character * pszB, strsize sizeB) noexcept
//{
//
//   ::i32 iCompare;
//
//   if (string_compare_prefix(iCompare, pszA, pszB))
//   {
//
//      return iCompare;
//
//   }
//
//   return _string_compare(pszA, sizeA, pszB, sizeB);
//
//}


//template < typename ITERATOR_TYPE >
//inline i32 case_insensitive_string_order(const array_range<CHARACTER> & rangeA, ) noexcept
//{
//
//   ::i32 iCompare;
//
//   if (string_compare_prefix(iCompare, pszA, pszB))
//   {
//
//      return iCompare;
//
//   }
//
//   return _string_compare_ci(pszA, sizeA, pszB, sizeB);
//
//}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering range_collate(::string_range < ITERATOR_TYPE > rangeA, ::string_range < ITERATOR_TYPE > rangeB) noexcept
{

   ::std::strong_ordering order(::std::strong_ordering::less);

   if (rangeA._initialize_order(order, rangeA, rangeB))
   {

      return order;

   }

   return _range_collate(rangeA, rangeB);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering case_insensitive_range_collate(::string_range < ITERATOR_TYPE > rangeA, ::string_range < ITERATOR_TYPE > rangeB) noexcept
{

   ::std::strong_ordering order(::std::strong_ordering::less);

   if (rangeA._initialize_order(order, rangeA, rangeB))
   {

      return order;

   }

   return _case_insensitive_range_collate(rangeA, rangeB);

}


template < primitive_character CHARACTER >
inline ::std::strong_ordering _sz_count_collate(const CHARACTER * pszA, const CHARACTER * pszB, strsize sizeB) noexcept
{

   return range_collate<const CHARACTER>(pszA, { pszB, sizeB });

}


template < primitive_character CHARACTER >
inline ::std::strong_ordering _case_insensitive_sz_count_collate(const CHARACTER * pszA, const CHARACTER * pszB, strsize sizeB) noexcept
{

   return case_insensitive_range_collate<const CHARACTER>(pszA, { pszB, sizeB });

}


inline ::std::strong_ordering _count_sz_collate(const ::ansi_character * pszA, strsize sizeA, const ::ansi_character * pszB) noexcept
{

   return range_collate<const ::ansi_character *>({ pszA, sizeA }, pszB);

}


inline ::std::strong_ordering _case_insensitive_count_sz_collate(const ::ansi_character * pszA, strsize sizeA, const ::ansi_character * pszB) noexcept
{

   return case_insensitive_range_collate<const ::ansi_character * >({ pszA, sizeA }, pszB);

}





CLASS_DECL_ACME::string string_format(const char * pszFormat, ...);


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline string_base < ITERATOR_TYPE >::string_base(const CHARACTER2 * pszSource, strsize start, strsize count) :
   string_base(e_no_initialize)
{

   start_count_length(start, count, pszSource);

   auto dstlen = utf_to_utf_length(this->begin(), pszSource + start, count);

   if (dstlen <= 0)
   {

      default_construct();

   }
   else
   {

      auto pszTarget = create_string(dstlen);

      utf_to_utf(pszTarget, pszSource, count);

      this->release_string_buffer(dstlen);

   }

}



//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(RANGE range, strsize start, strsize count) :
//   string_base(e_no_initialize)
//{
//
//   auto lenSource = range.size();
//
//   start_count(start, count, lenSource);
//
//   if (count <= 0)
//   {
//
//      default_construct();
//
//   }
//   else
//   {
//
//      auto dstlen = utf_to_utf_length(this->begin(), range.begin() + start, count);
//
//      auto pszTarget = create_string(dstlen);
//
//      utf_to_utf(pszTarget, range.begin() + start, count);
//
//      this->release_string_buffer(dstlen);
//
//   }
//
//}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline void string_base < ITERATOR_TYPE >::construct2(const ::range < const CHARACTER2 * > & range)
{

   this->construct2(range, range.size());

}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline void string_base < ITERATOR_TYPE >::construct2(const ::range < const CHARACTER2 * > & range, strsize count)
{

   this->construct2(range, 0, count);

}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline void string_base < ITERATOR_TYPE >::construct2(const ::range < const CHARACTER2 * > & range, strsize start, strsize count)
{

   auto rangeStartCount = _start_count_range(range, start, count);

   if (rangeStartCount.is_empty())
   {

      default_construct();

      return;

   }

   if constexpr (sizeof(CHARACTER) == sizeof(CHARACTER2))
   {

      if (range.is_natural_pointer() && rangeStartCount.begin() == range.begin() && rangeStartCount.end() == range.end())
      {

         this->create_assign_natural_meta_data(NATURAL_META_DATA::from_data(range.begin()));

         this->m_erange = e_range_natural_pointer;

      }
      else
      {

         RANGE::operator =(rangeStartCount);

         this->m_erange -= e_range_natural_pointer;

         this->m_erange -= e_range_null_terminated;

      }

      return;

   }

   auto dstlen = utf_to_utf_length(this->begin(), range.begin(), range.size());

   auto pszTarget = create_string(dstlen);

   utf_to_utf(pszTarget, range.begin(), range.size());

   this->release_string_buffer(dstlen);

   this->m_erange = e_range_natural_pointer | e_range_null_terminated;

}


//template < typename ITERATOR_TYPE >
//template < primitive_character CHARACTER2 >
//inline string_base < ITERATOR_TYPE >::string_base(const ::string_range < const CHARACTER2 * > & range, strsize start, strsize count)
//{
//
//   auto lenSource = range.size();
//
//   start_count(start, count, lenSource);
//
//   if (count <= 0)
//   {
//
//      default_construct();
//
//   }
//   //else if (sizeof(CHARACTER) == sizeof(CHARACTER2) && start == 0 && count == lenSource)
//   //{
//
//   //   this->create_assign_natural_meta_data((natural_meta_data < string_meta_data < CHARACTER > > *)strSource.metadata());
//
//   //}
//   else
//   {
//
//      auto dstlen = utf_to_utf_length(this->begin(), range.begin() + start, count);
//
//      auto pszTarget = create_string(dstlen);
//
//      utf_to_utf(pszTarget, range.begin() + start, count);
//
//      this->release_string_buffer(dstlen);
//
//   }
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const string_base & str) :
//   string_base(e_no_initialize)
//{
//
//   auto pmetadata = str.metadata();
//
//   this->create_assign_natural_meta_data(pmetadata);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//template < primitive_character CHARACTER2 >
//inline string_base < ITERATOR_TYPE >::string_base(CHARACTER2 chSrc, strsize repeat) :
//   string_base(e_no_initialize)
//{
//
//   if (repeat > 0)
//   {
//
//      auto lenUnit = utf_to_utf_length(this->begin(), &chSrc, 1);
//
//      auto len = lenUnit * repeat;
//
//      auto psz = create_string(len);
//
//      CHARACTER sz[8];
//
//      utf_to_utf(sz, &chSrc, 1);
//
//      auto pTarget = psz;
//
//      while (repeat > 0)
//      {
//
//         auto pSource = sz;
//
//         for (int j = 0; j < lenUnit; j++, pSource++)
//         {
//
//            *pTarget++ = *pSource;
//
//         }
//
//         repeat--;
//
//      }
//
//      release_string_buffer(len);
//
//   }
//   else
//   {
//
//      default_construct();
//
//   }
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(::ansi_character ansich, strsize repeat)
//{
//
//   assign(ansich, repeat);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(::wd16_character wd16ch, strsize repeat)
//{
//
//   assign(wd16ch, repeat);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(::wd32_character wd32ch, strsize repeat)
//{
//
//   assign(wd32ch, repeat);
//
//}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE >::unichar_count() const
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
//template < primitive_character CHARACTER2 >
//string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const ::string_range < const CHARACTER2 * > & range)
//{
//
//   assign(range);
//
//   return *this;
//
//}



//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (RANGE range)
//{
//
//   assign(range);
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
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator=(const ::ansi_character * pansichar)
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
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(RANGE range)
//{
//
//   return append(range);
//
//}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const string_base & str)
{

   return append(str);

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const const_wd16_raw_range & wd16range)
//{
//
//   return append(wd16range);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const const_wd32_raw_range & wd32range)
//{
//
//   return append(wd32range);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const inline_number_string & inlinenumberstring)
//{
//
//   return append(inlinenumberstring);
//
//}



//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const ::ansi_character * pszSrc)
//{
//
//   return append(pszSrc);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const ::wd16_character * pszSrc)
//{
//
//   return append(pszSrc);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const ::wd32_character * pszSrc)
//{
//
//   return append(pszSrc);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(::ansi_character ansich)
//{
//
//   return append(ansich);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(::wd16_character wd16ch)
//{
//
//   return append(wd16ch);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(::wd32_character wd32ch)
//{
//
//   return append(wd32ch);
//
//}


//template < typename ITERATOR_TYPE >
//template < int t_nSize >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator+=(const static_string<CHARACTER, t_nSize > & ansistrSrc)
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
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const ::ansi_character * psz) const
//{
//
//   auto str(*this);
//
//   str += psz;
//
//   return ::move(str);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const ::wd16_character * pwsz) const
//{
//
//   auto str(*this);
//
//   str += pwsz;
//
//   return ::move(str);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const ::wd32_character * pwsz) const
//{
//
//   auto str(*this);
//
//   str += pwsz;
//
//   return ::move(str);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const_ansi_range ansirange) const
//{
//
//   auto str(*this);
//
//   str += ansirange;
//
//   return ::move(str);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const_wd16_range range) const
//{
//
//   auto str(*this);
//
//   str += range;
//
//   return ::move(str);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const_wd32_range range) const
//{
//
//   auto str(*this);
//
//   str += range;
//
//   return ::move(str);
//
//}



//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(const inline_number_string & inlinenumberstring) const
//{
//
//   auto str(*this);
//
//   str.append(inlinenumberstring);
//
//   return ::move(str);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::ansi_character ansich) const
//{
//
//   auto str(*this);
//
//   str += ansich;
//
//   return ::move(str);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::wd16_character wd16ch) const
//{
//
//   auto str(*this);
//
//   ansistr += wd16ch;
//
//   return ::move(str);
//
//}
//
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::operator +(::wd32_character wd32ch) const
//{
//
//   auto str(*this);
//
//   str += wd32ch;
//
//   return ::move(str);
//
//}
//


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const string_base & str)
{

   NATURAL_POINTER::operator=(str);

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(string_base && str)
{

   NATURAL_POINTER::operator=(::move(str));

   return *this;

}


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
//template < primitive_character CHARACTER2 >
//inline ::string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const ::string_base < CHARACTER2 > & strSource, strsize start, strsize count)
//{
//
//   start_count(start, count, strSource.size());
//
//   if(sizeof(CHARACTER) != sizeof(CHARACTER2) || start != 0 || count != strSource.size())
//   {
//
//      assign(strSource.begin(), start, count);
//
//   }
//   else
//   {
//
//      assign(strSource.begin());
//
//   }
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const wd16_string & widestrSrc, strsize pos, strsize count)
//{
//
//   return assign(*this, widestrSrc.begin() + pos, count);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const wd32_string & widestrSrc, strsize pos, strsize count)
//{
//
//   return assign(*this, widestrSrc.begin() + pos, count);
//
//}

//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const ::ansi_character * pszSrc)
//{
//
//   return assign(*this, pszSrc);
//
//}
//


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline strsize string_base < ITERATOR_TYPE > ::start_count_length(strsize & start, strsize & count, const CHARACTER2 * pszSource)
{

   strsize len = -1;

   if (start < 0)
   {

      start = 0;

   }

   if (count < 0)
   {

      len = string_safe_length(pszSource);

      count += (len - start) + 1;

      if (count < 0)
      {

         count = 0;

      }

   }

   if (len < 0)
   {

      len = string_safe_length(pszSource, start + count);

      if (len < 0)
      {

         return start + count;

      }

   }

   if (count + start > len)
   {

      count = len - start;

   }

   return len;

}


template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::start_count(strsize & start, strsize & count, strsize len)
{

   if (start < 0)
   {

      start = 0;

   }

   if (count < 0)
   {

      count += (len - start) + 1;

      if (count < 0)
      {

         count = 0;

      }

   }

   if (count + start > len)
   {

      count = len - start;

   }

}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const CHARACTER2 * pszSource, strsize start, strsize count)
{

   start_count_length(start, count, pszSource);

   return _assign(pszSource, start, count);

}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::_assign(const CHARACTER2 * pszSource, strsize start, strsize len)
{

   auto dstlen = utf_to_utf_length(this->begin(), pszSource + start, len);

   if (dstlen <= 0)
   {

      this->Empty();

   }
   else
   {

      auto pszTarget = this->get_string_buffer(dstlen);

      utf_to_utf(pszTarget, pszSource + start, len);

      this->release_string_buffer(dstlen);

   }

   return *this;

}

//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const ::wd16_character * pwd16sz)
//{
//
//   return assign(*this, pwd16sz);
//
//}
//

//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const ::wd16_character * pwd16sz, strsize len)
//{
//
//   return assign(*this, pwd16sz, len);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const ::wd32_character * pwd32sz)
//{
//
//   return assign(*this, pwd32sz);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const ::wd32_character * pwd32sz, strsize len)
//{
//
//   return assign(*this, pwd32sz, len);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(::ansi_character ansich)
//{
//
//   return assign(*this, &ansich, 1);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(::wd16_character wd16ch)
//{
//
//   return assign(*this, &wd16ch, 1);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(::wd32_character wd32ch)
//{
//
//   return assign(*this, &wd32ch, 1);
//
//}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(CHARACTER2 chSrc, strsize repeat)
{

   if (repeat > 0)
   {

      auto lenUnit = utf_to_utf_length(this->begin(), &chSrc, 1);

      auto len = lenUnit * repeat;

      auto psz = get_string_buffer(len);

      CHARACTER sz[8];

      utf_to_utf(sz, &chSrc, 1);

      auto pTarget = psz;

      while (repeat > 0)
      {

         auto pSource = sz;

         for (index j = 0; j < lenUnit; j++)
         {

            *pTarget++ = *pSource;

         }

         repeat--;

      }

      release_string_buffer(len);

   }
   else
   {

      this->Empty();

   }

   return *this;

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(::wd16_character wd16ch, strsize repeat)
//{
//
//   if (repeat > 0)
//   {
//
//      auto lenUnit = utf_to_utf_length(this->begin(), &wd16ch, 1);
//
//      auto len = lenUnit * repeat;
//
//      auto psz = get_string_buffer(len);
//
//      CHARACTER sz[8];
//
//      utf_to_utf(sz, &wd16ch, 1);
//
//      for (index i = 0; i < len; i += lenUnit)
//      {
//
//         memcpy(psz, sz, lenUnit * sizeof(CHARACTER));
//
//         psz += lenUnit;
//
//      }
//
//      release_string_buffer(len);
//
//   }
//   else
//   {
//
//      this->natural_release();
//
//   }
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(::wd32_character wd32ch, strsize repeat)
//{
//
//   if (repeat > 0)
//   {
//
//      auto lenUnit = utf_to_utf_length(this->begin(), &wd32ch, 1);
//
//      auto len = lenUnit * repeat;
//
//      auto psz = get_string_buffer(len);
//
//      CHARACTER sz[8];
//
//      utf_to_utf(sz, &wd32ch, 1);
//
//      for (index i = 0; i < len; i += lenUnit)
//      {
//
//         memcpy(psz, sz, lenUnit * sizeof(CHARACTER));
//
//         psz += lenUnit;
//
//      }
//
//      release_string_buffer(len);
//
//   }
//   else
//   {
//
//      this->natural_release();
//
//   }
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//template < int t_nSize >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const static_string<CHARACTER, t_nSize > & ansistrSrc)
//{
//
//   return assign(ansistrSrc.begin(), ansistrSrc.length());
//
//}
//


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::const_ansi_raw_range & ansirange)
{

   return append(ansirange.begin(), ansirange.size());

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::const_wd16_raw_range & wd16range)
{

   return append(wd16range.begin(), wd16range.size());

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::const_wd32_raw_range & wd32range)
{

   return append(wd32range.begin(), wd32range.size());

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const wd16_string & wd16strSrc)
//{
//
//   return append(wd16strSrc.begin(), wd16strSrc.size());
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const wd32_string & wd32strSrc)
//{
//
//   return append(wd32strSrc.begin(), wd32strSrc.size());
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::ansi_character * pszSrc)
//{
//
//   return append(pszSrc, string_safe_length(pszSrc));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::wd16_character * pwszSrc)
//{
//
//   return append(pwszSrc, string_safe_length(pwszSrc));
//
//}
//

//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::wd32_character * pwszSrc)
//{
//
//   return append(pwszSrc, string_safe_length(pwszSrc));
//
//}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const CHARACTER2 * pszSrc, strsize nLength)
{

   auto nOldLength = this->length();

   if (nOldLength < 0)
   {

      nOldLength = 0;

   }

   strsize nNewLength = nOldLength + utf_to_utf_length(this->begin(), pszSrc, nLength);

   auto pszBuffer = get_string_buffer(nNewLength);

   utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);

   release_string_buffer(nNewLength);

   return *this;

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::wd16_character * pszSrc, strsize nLength)
//{
//
//   auto nOldLength = this->length();
//
//   if (nOldLength < 0)
//   {
//
//      nOldLength = 0;
//
//   }
//
//   strsize nNewLength = nOldLength + utf_to_utf_length(this->begin(), pszSrc, nLength);
//
//   auto pszBuffer = get_string_buffer(nNewLength);
//
//   utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);
//
//   release_string_buffer(nNewLength);
//
//   return *this;
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::wd32_character * pszSrc, strsize nLength)
//{
//
//   auto nOldLength = this->length();
//
//   if (nOldLength < 0)
//   {
//
//      nOldLength = 0;
//
//   }
//
//   strsize nNewLength = nOldLength + utf_to_utf_length(this->begin(), pszSrc, nLength);
//
//   auto pszBuffer = get_string_buffer(nNewLength);
//
//   utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);
//
//   release_string_buffer(nNewLength);
//
//   return *this;
//
//}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append_character(::ansi_character ch)
{

   return append(&ch, 1);

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append_character(::wd16_character wch)
{

   return append(&wch, 1);

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append_character(::wd32_character wch)
{

   return append(&wch, 1);

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(strsize len, CHARACTER ch)
{

   if (len > 0)
   {

      strsize nOldLength = this->size();

      strsize nNewLength = nOldLength + len;

      CHARACTER * pszBuffer = this->get_string_buffer(nNewLength);

      auto pch = pszBuffer + nOldLength;

      auto p = pch + len - 1;

      while (p >= pch)
      {

         *p = ch;

         p--;

      }

      this->release_string_buffer(nNewLength);

   }

   return *this;

}

//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(strsize len, ::ansi_character ch)
//{
//
//   if (len > 0)
//   {
//
//      strsize nOldLength = this->size();
//
//      strsize nNewLength = nOldLength + len;
//
//      CHARACTER * pszBuffer = this->get_string_buffer(nNewLength);
//
//      CHARACTER
//
//         auto pch = pszBuffer + nOldLength;
//
//      auto p = pch + len - 1;
//
//      while (p >= pch)
//      {
//
//         *p = ch;
//
//         p--;
//
//      }
//
//      this->release_string_buffer(nNewLength);
//
//   }
//
//   return *this;
//
//}



//template < typename ITERATOR_TYPE >
//template < typename STATIC_TYPE_CHAR, int t_nSize >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const static_string<STATIC_TYPE_CHAR, t_nSize > & ansistrSrc)
//{
//
//   return append(ansistrSrc.begin(), ansistrSrc.length());
//
//}


//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::order(RANGE range) const noexcept
//{
//
//   return this->order(range, compare_const_reference <const CHARACTER>);
//
//}
//

template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_order(RANGE range) const noexcept
{

   return NATURAL_POINTER::order(range, ::comparison::case_insensitive < CHARACTER >());

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::collate(RANGE range) const noexcept
{

   return range_collate<const CHARACTER *>(*this, range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_collate(RANGE range) const noexcept
{

   return case_insensitive_range_collate<const CHARACTER *>(*this, range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::order(RANGE range, strsize len) const noexcept
{

   return ::string_range < const CHARACTER * >(*this).order({ range.begin(), minimum(range.size(), len) });

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_order(RANGE range, strsize len) const noexcept
{

   return ::string_range < const CHARACTER * >(*this).order({ range.begin(), minimum(range.size(), len) }, ::comparison::case_insensitive<const CHARACTER >());

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::collate(RANGE range, strsize len) const noexcept
{

   return string_collate(this->begin(), this->size(), range.begin(), minimum(range.size(), len));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_collate(RANGE range, strsize len) const noexcept
{

   return case_insensitive_string_collate(this->begin(), this->size(), range.begin(), minimum(range.size(), len));

}


// TODO strncmpn(const ::ansi_character * psz1, strsize len1, const ::ansi_character * psz2, strsize len2);
// TODO wcsncmpn(const ::wide_character * psz1, strsize len1, const ::wide_character * psz2, strsize len2);


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::order(strsize start, strsize iCount, RANGE range) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   return string_compare(this->begin() + start, iCount, range.begin(), range.size());

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_order(strsize start, strsize iCount, RANGE range) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   return case_insensitive_string_order(this->begin() + start, iCount, range.begin(), range.size());

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::collate(strsize start, strsize iCount, RANGE range) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   return string_collate(this->begin() + start, iCount, range.begin(), range.size());

}



template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_collate(strsize start, strsize iCount, RANGE range) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   return case_insensitive_string_collate(this->begin() + start, iCount, range.begin(), range.size());

}



template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::order(strsize start, strsize iCount, RANGE range, strsize iStart2, strsize iCount2) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   if (iStart2 + iCount2 > range.size())
   {

      throw ::exception(error_bad_argument);

   }

   return string_compare(this->begin() + start, iCount, range.begin() + iStart2, iCount2);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_order(strsize start, strsize iCount, RANGE range, strsize iStart2, strsize iCount2) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   if (iStart2 + iCount2 > range.size())
   {

      throw ::exception(error_bad_argument);

   }

   return case_insensitive_string_order(this->begin() + start, iCount, range.begin() + iStart2, iCount2);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::collate(strsize start, strsize iCount, RANGE range, strsize iStart2, strsize iCount2) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   if (iStart2 + iCount2 > range.size())
   {

      throw ::exception(error_bad_argument);

   }

   return string_collate(this->begin() + start, iCount, range.begin() + iStart2, iCount2);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_base < ITERATOR_TYPE > ::case_insensitive_collate(strsize start, strsize iCount, RANGE range, strsize iStart2, strsize iCount2) const noexcept
{

   if (start + iCount > size())
   {

      throw ::exception(error_bad_argument);

   }

   if (iStart2 + iCount2 > range.size())
   {

      throw ::exception(error_bad_argument);

   }

   return case_insensitive_string_collate(this->begin() + start, iCount, range.begin() + iStart2, iCount2);

}


//template < typename ITERATOR_TYPE >
//inline int string_base < ITERATOR_TYPE >::operator<=>(RANGE range) const { return order(range); }
////template < typename ITERATOR_TYPE >
////inline int string_base < ITERATOR_TYPE >::operator<=>(CHARACTER ch) const { return order((RANGE) (ch)); }
//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE >::operator==(RANGE range) const { return !order(range); }
//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE >::operator==(CHARACTER ch) const { return !order((RANGE) string_base(ch)); }
//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE >::operator>(RANGE range) const { return order(psz) > 0; }
//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE >::operator>(CHARACTER wch) const { return order(string_base(wch)) > 0; }
//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE >::operator<(RANGE range) const { return order(psz) < 0; }
//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE >::operator<(CHARACTER ch) const { return order(string_base(ch)) < 0; }


template < typename ITERATOR_TYPE >
template < class InputIterator >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::assign(InputIterator first, InputIterator last)
{

   this->Empty();

   for (auto it = first; it <= last; it++)
   {

      *this += *it;

   }

   return *this;

}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::find_first_in(RANGE range, strsize pos) const RELEASENOTHROW
//{
//
//   return find_first_of(range, pos);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::find_first_in(RANGE range, strsize pos, strsize n) const RELEASENOTHROW
//{
//
//   return find_first_of(range, pos, n);
//
//}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::find_first_in(RANGE range, strsize pos) const RELEASENOTHROW
//{
//
//   return find_first_of(s, pos);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::find_first_in(CHARACTER ca, strsize pos) const RELEASENOTHROW
//{
//
//   return find_first_of(ca, pos);
//
//}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::scan(RANGE rangeSeparators, strsize pos) const RELEASENOTHROW
{

   return offset_of(::string_range <ITERATOR_TYPE>({ this->begin() + pos, size() - pos }).scan(rangeSeparators));

}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::get_token(RANGE rangeSeparators, strsize pos, strsize n) const RELEASENOTHROW
//{
//
//   auto psz = ::string_token({ this->begin() + pos, n }, rangeSeparators);
//
//   return ::is_set(psz) ? (::strsize)psz - this->begin() : -1;
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::get_token(const CHARACTER * pszSeparators, strsize pos) const RELEASENOTHROW
//{
//
//   return ::string_token(this->begin() + pos, pszSeparators);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::get_token(CHARACTER chSeparator, strsize pos) const RELEASENOTHROW
//{
//
//   return ::string_find_character(ca, pos);
//
//}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::span(RANGE range, strsize pos) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >(this->begin() + pos, size() - pos).span(range));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::span(RANGE range, strsize pos, strsize n) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >(this->begin() + pos, n).span(range));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::span(const CHARACTER * psz, strsize pos) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >(this->begin() + pos, size() - pos).span(psz));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::skip(CHARACTER chSkip, strsize pos) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >(this->begin() + pos, size() - pos).skip(chSkip));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::_span(RANGE range, strsize pos) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >({ this->begin() + pos, size() - pos })._span(range));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::_span(RANGE range, strsize pos, strsize n) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >({ this->begin() + pos, n })._span(range));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::_span(const CHARACTER * psz, strsize pos) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >(this->begin() + pos)._span(psz));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::_skip(CHARACTER chSkip, strsize pos) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * >(this->begin() + pos)._skip(chSkip));

}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::find_last_not_in(RANGE range, strsize pos) const RELEASENOTHROW
//{
//
//   return find_last_not_of(range, pos);
//
//}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::find_last_not_in(CHARACTER ca, strsize pos) const RELEASENOTHROW
//{
//
//   return find_last_not_of(ca, pos);
//
//}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::rear_scan(RANGE range, strsize start) const RELEASENOTHROW
{

   return offset_of(NATURAL_POINTER::rear_scan_start(range, start));

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::rear_scan(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   return offset_of(NATURAL_POINTER::rear_scan_start_count(range, start, count));

}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::rear_scan(const CHARACTER * psz, strsize count) const RELEASENOTHROW
//{
//
//   return offset_of(::string_rear_scan({this->begin(), size() + count + 1}, {psz, ::string_safe_length(psz)}));
//
//}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::_rear_scan(RANGE range, strsize start) const RELEASENOTHROW
{

   return offset_of(NATURAL_POINTER::_rear_scan_start(range, start));

}



template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::_rear_scan(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   return offset_of(NATURAL_POINTER::_rear_scan_start_count(range, start, count));

}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::_rear_scan(const CHARACTER * psz, strsize count) const RELEASENOTHROW
//{
//
//   return offset_of(::_string_rear_scan({this->begin(), size() + count + 1}, {psz, ::string_safe_length(psz)}));
//
//}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE > ::rear_find(CHARACTER ch, strsize count) const RELEASENOTHROW
{

   return offset_of(::string_range < const CHARACTER * > (this->begin(), size() + count + 1).rear_find_item(ch));

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::unichar_left(strsize count) const
{

   return Left(char_type_count(count));

}



template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::unichar_mid(strsize iFirst) const
{

   return Mid(char_type_count(iFirst));

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >  string_base < ITERATOR_TYPE > ::unichar_mid(strsize iFirst, strsize count) const
{

   strsize iBeg = char_type_count(iFirst);

   strsize iEnd = char_type_count(iFirst + count);

   return Mid(iFirst, iEnd - iBeg);

}


//template < typename ITERATOR_TYPE >
//inline strsize string_base < ITERATOR_TYPE > ::erase(strsize iIndex, strsize count)
//{
//
//   return Delete(iIndex, count);
//
//}


template < primitive_character CHARACTER >
inline bool operator>(const CHARACTER * psz, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & range)
{

   return string_compare(psz, string_safe_length(psz), range.begin(), range.size()) > 0;

}


template < primitive_character CHARACTER >
inline bool operator > (CHARACTER ch, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & range)
{

   return string_compare(&ch, 1, range.begin(), range.size()) > 0;

}


template < primitive_character CHARACTER >
inline bool operator > (::wide_character ch, const typename ::GET_BLOCK_TYPE<CHARACTER>::TYPE & range)
{

   return wide_string(ch) > range;

}


template < primitive_character CHARACTER >
inline bool operator>(i32 i, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & range)
{

   return ::string_base<CHARACTER>(i) > range;

}


template < primitive_character CHARACTER >
inline bool operator<(const CHARACTER * psz, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & range)
{

   return string_compare(psz, string_save_length(psz), range.begin(), range.size()) < 0;

}


template < primitive_character CHARACTER >
inline bool operator<(CHARACTER ch, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & range)
{

   return string_compare(&ch, 1, range.begin(), range.size()) < 0;

}


template < primitive_character CHARACTER >
inline bool operator<(i32 i, const typename::GET_BLOCK_TYPE<CHARACTER>::TYPE & range)
{

   return ::string_base <CHARACTER>(i) < range;

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


template < primitive_character CHARACTER >
inline const CHARACTER * FormatArgument(const typename GET_BLOCK_TYPE<CHARACTER>::TYPE & range) noexcept
{

   return range.begin();

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(RANGE range) :
//   string_base((const ::ansi_character *)range.data(), (strsize)range.size())
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
template < primitive_array STRING_ARRAY >
bool string_base < ITERATOR_TYPE >::contains_any(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (contains(str))
      {

         return true;

      }

   }

   return false;

}


template < typename ITERATOR_TYPE >
template < primitive_array STRING_ARRAY >
bool string_base < ITERATOR_TYPE >::contains_all(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (!contains(str))
      {

         return false;

      }

   }

   return true;

}




template < typename ITERATOR_TYPE >
template < primitive_array STRING_ARRAY >
bool string_base < ITERATOR_TYPE >::contains_any_ci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (contains_ci(str))
      {

         return true;

      }

   }

   return false;

}


template < typename ITERATOR_TYPE >
template < primitive_array STRING_ARRAY >
bool string_base < ITERATOR_TYPE >::contains_all_ci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (!contains_ci(str))
      {

         return false;

      }

   }

   return true;

}


template < typename ITERATOR_TYPE >
template < primitive_array STRING_ARRAY >
bool string_base < ITERATOR_TYPE >::contains_any_wci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (contains_wci(str))
      {

         return true;

      }

   }

   return false;

}


template < typename ITERATOR_TYPE >
template < primitive_array STRING_ARRAY >
bool string_base < ITERATOR_TYPE >::contains_all_wci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (!contains_wci(str))
      {

         return false;

      }

   }

   return true;

}



template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::Tokenize(RANGE rangeTokens, strsize & start) const
{
   ASSERT(start >= 0);

   if (start < 0)
      throw_exception(error_bad_argument);

   if ((rangeTokens == nullptr) || (*rangeTokens == (char)0))
   {
      if (start < size())
      {
         return(string_base < ITERATOR_TYPE >(this->begin() + start));
      }
   }
   else
   {
      const CHARACTER * pszPlace = this->begin() + start;
      const CHARACTER * pszEnd = this->begin() + size();
      if (pszPlace < pszEnd)
      {
         strsize nIncluding = string_span_including(pszPlace,
            rangeTokens);

         if ((pszPlace + nIncluding) < pszEnd)
         {
            pszPlace += nIncluding;
            strsize nExcluding = string_span_excluding(pszPlace, rangeTokens);

            strsize iFrom = start + nIncluding;
            strsize nUntil = nExcluding;
            start = iFrom + nUntil + 1;

            return(Mid(iFrom, nUntil));
         }
      }
   }

   // return is_empty string_base < ITERATOR_TYPE >, done tokenizing
   start = -1;

   return(string_base < ITERATOR_TYPE >());

}




template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::intersection(RANGE find) const
{

   string_base < ITERATOR_TYPE > str;

   for (strsize i = 0; i < size(); i++)
   {

      auto ch = operator[](i);

      if (find.contains(ch))
      {

         str += ch;

      }


   }

   return str;

}






template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::get_string(CHARACTER * psz) const noexcept
{

   copy_chars(psz, this->begin(), length());

}


template < typename ITERATOR_TYPE >
typename string_base < ITERATOR_TYPE >::CHARACTER * string_base < ITERATOR_TYPE >::create_string(strsize strsize)
{

   auto memsize = char_length_to_byte_length(this->begin(), strsize + 1);

   auto pNew = this->create_meta_data(memsize);

   pNew->set_length(strsize);

   this->create_assign_natural_meta_data(pNew);

   return (CHARACTER *) pNew->begin();

}


template < typename ITERATOR_TYPE >
typename string_base < ITERATOR_TYPE >::CHARACTER * string_base < ITERATOR_TYPE >::fork_string(strsize strsize)
{

   auto pOld = this->NATURAL_POINTER::metadata();

   ASSERT(pOld->m_countReference >= 1);

   auto memsize = char_length_to_byte_length(this->begin(), strsize + 1);

   auto pNew = this->create_meta_data(memsize);

   if (::is_set(pOld))
   {

      auto memsizeOld = pOld->memsize();

      if (memsizeOld > 0)
      {

         auto memsizeCopy = minimum(memsizeOld, memsize);

         memcpy_dup((void *) pNew->begin(), pOld->begin(), memsizeCopy);

      }

   }

   pNew->set_length(strsize);

   this->assign_natural_meta_data(pNew);

   //pNew->natural_dec_ref();

   return (CHARACTER *) pNew->begin();

}




template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::release_string_buffer(strsize nNewLength)
{

   if (nNewLength == -1)
   {

      nNewLength = string_safe_length(this->begin());

   }

   this->NATURAL_POINTER::metadata()->set_length(nNewLength);

   return *this;

}


template < typename ITERATOR_TYPE >
inline strsize string_base < ITERATOR_TYPE >::get_storage_length() { return (::strsize)byte_length_to_char_length(this->begin(), this->get_storage_size_in_bytes()); }


template < typename ITERATOR_TYPE >
inline memsize string_base < ITERATOR_TYPE >::length_in_bytes() const { return char_length_to_byte_length(this->begin(), (strsize)(this->NATURAL_POINTER::metadata()->m_datasize)); }


template < typename ITERATOR_TYPE >
inline memsize string_base < ITERATOR_TYPE >::length_in_bytes_with_null_terminator() const { return char_length_to_byte_length(this->begin(), (strsize)(this->NATURAL_POINTER::metadata()->m_datasize + 1)); }


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::resize(strsize n, CHARACTER c)
{

   strsize nOldSize = length();

   if (n < nOldSize)
   {

      this->truncate(n);

   }
   else
   {

      auto psz = this->get_string_buffer(n);

      flood_characters(psz + nOldSize, c, n - nOldSize);

      this->release_string_buffer(n);

   }

}





template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::truncate(strsize nNewLength)
{

   if (nNewLength >= this->length())
   {

      return;

   }

   if (nNewLength <= 0)
   {

      Empty();

      return;

   }

   get_string_buffer(nNewLength);

   release_string_buffer(nNewLength);

}


template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::erase_beginning(strsize i)
{

   i = minimum_maximum(i, 0, size());

   assign(this->begin() + i, size() - i);

}



template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::set_at(strsize iChar, CHARACTER ch)
{

   auto p = this->NATURAL_POINTER::metadata();

   if (p->natural_is_shared() || iChar >= p->length())
   {

      fork_string(maximum(p->length(), iChar + 1));

   }

   ((CHARACTER *)this->m_begin)[iChar] = ch;

}






//template < typename ITERATOR_TYPE >
//void string_base < ITERATOR_TYPE >::construct() noexcept
//{
//
//   NATURAL_POINTER::natural_release();
//
//}


//#ifdef WINDOWS
//
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >::string_base(const USHORT* pshSrc)
//{
//
//   *this = pshSrc;
//
//}
//
//
//#endif


//#ifdef _UWP
//
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >::string_base(Array <byte >^ a)
//{
//
//   *this = string_base < ITERATOR_TYPE >((const ::ansi_character *) a->begin(), a->Length);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >::string_base(Object^ o)
//{
//
//   *this = o->ToString()->Begin();
//
//}
//
//
//
//
//
//#endif



//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >::string_base(strsize nLength, CHARACTER ch)
//{
//
//   ASSERT(nLength >= 0);
//
//   if (nLength > 0)
//   {
//
//      CHARACTER* pszBuffer = get_string_buffer(nLength);
//
//      flood_characters(ch, nLength, pszBuffer);
//
//      release_string_buffer(nLength);
//
//   }
//
//}



//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(const CHARACTER* pszSrc)
//{
//
//   string_base < ITERATOR_TYPE >::operator=(pszSrc);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(string_base < ITERATOR_TYPE >&& str)
//{
//   this->begin()->Release();
//   this->begin() = str.begin();
//   str.begin() = nullptr;
//   return *this;
//
//}

//#ifdef WINDOWS
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(const USHORT* pshSrc)
//{
//
//   return operator=((const ::wide_character*)pshSrc);
//
//}
//
//#endif


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(const ::wide_character* pszSrc)
//{
//
//   strsize nDestLength = (pszSrc != nullptr) ? get_char_length(pszSrc) : 0;
//
//   if (nDestLength > 0)
//   {
//
//      CHARACTER* pszBuffer = get_string_buffer(nDestLength);
//
//      ConvertTochar(pszBuffer, nDestLength, pszSrc);
//
//      release_string_buffer(nDestLength);
//
//   }
//   else
//   {
//
//      Empty();
//
//   }
//
//   return *this;
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(const ::wd32_character* pszSrc)
//{
//   // nDestLength is in XCHARs
//   strsize nDestLength = (pszSrc != nullptr) ? wd32_to_wd16_len(pszSrc) : 0;
//   if (nDestLength > 0)
//   {
//      CHARACTER* pszBuffer = get_string_buffer(nDestLength);
//      wd32_to_ansi(pszBuffer, pszSrc, nDestLength);
//      release_string_buffer(nDestLength);
//   }
//   else
//   {
//      Empty();
//   }
//
//   return *this;
//}
//

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(const uchar* pszSrc)
//{
//   return(operator=(reinterpret_cast<const CHARACTER*>(pszSrc)));
//}
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(CHARACTER ch)
//{
//   CHARACTER ach[2] = { ch,0 };
//
//   return(operator=(ach));
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator=(::wide_character ch)
//{
//   ::wide_character ach[2] = { ch,0 };
//
//   return(operator=(ach));
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator+=(const string_base < ITERATOR_TYPE >& str)
//{
//   append(str);
//
//   return *this;
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator+=(const CHARACTER* pszSrc)
//{
//   string_base < ITERATOR_TYPE >::operator+=(pszSrc);
//
//   return *this;
//}

//#ifdef WINDOWS
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator+=(const USHORT* pshSrc)
//{
//
//   string_base < ITERATOR_TYPE > str(pshSrc);
//
//   return operator+=(str);
//
//}
//
//#endif

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator+=(const ::wide_character* pszSrc)
//{
//   string_base < ITERATOR_TYPE > str(pszSrc, GetManager());
//
//   return(operator+=(str));
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator+=(CHARACTER ch)
//{
//
//   append_char((CHARACTER)ch);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator+=(uchar ch)
//{
//
//   append_char((CHARACTER)ch);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator+=(::wide_character ch)
//{
//
//   append_char((CHARACTER)ch);
//
//   return *this;
//
//}

//// Override from acme class
//template < typename ITERATOR_TYPE >
//string_manager* string_base < ITERATOR_TYPE >::GetManager() const noexcept
//{
//   string_manager* pstringmanager = string_base < ITERATOR_TYPE >::GetManager();
//   if (pstringmanager) { return pstringmanager; }
//
//   pstringmanager = GetDefaultManager();
//   return pstringmanager->Clone();
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(const string_base < ITERATOR_TYPE >& str)
//{
//   return operator = (str);
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(const string_base < ITERATOR_TYPE >& str, strsize pos, strsize n)
//{
//   return operator = (str.substr(pos, n));
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(const CHARACTER* s, strsize n)
//{
//   return operator = (string_base < ITERATOR_TYPE >(s, n));
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(const CHARACTER* s)
//{
//   return operator = (s);
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(strsize n, CHARACTER ca)
//{
//   return operator = (string_base < ITERATOR_TYPE >(ca, n));
//}

//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(i32 n, i32 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(i64 n, i64 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(u32 n, u32 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::assign(u64 n, u64 ca)
//{
//   string_base < ITERATOR_TYPE > strChar = unicode_to_utf8(ca);
//   while (n > 0)
//   {
//      *this += strChar;
//   }
//   return *this;
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator =(const ::ansi_character * pansichar)
//{
//
//   assign(pansichar);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator =(const ::wd16_character * pwd16char)
//{
//
//   assign(pwd16char);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator =(const ::wd32_character * pwd32char)
//{
//
//   assign(pwd32char);
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::order(const CHARACTER* psz) const noexcept
//{
//   return NATURAL_POINTER::string_compare(this->begin(), psz);
//}

//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_order(const CHARACTER* psz) const noexcept
//{
//   return NATURAL_POINTER::case_insensitive_string_order(this->begin(), psz);
//}

//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::collate(const CHARACTER* psz) const noexcept
//{
//   return NATURAL_POINTER::string_collate(this->begin(), psz);
//}

//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_collate(const CHARACTER* psz) const noexcept
//{
//   return NATURAL_POINTER::case_insensitive_string_collate(this->begin(), psz);
//}

//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::order(RANGE range, strsize n) const
//{
//   return NATURAL_POINTER::string_count_compare(this->begin(), psz, n);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_order(RANGE range) const noexcept
//{
//  return NATURAL_POINTER::string_count_compare_ci(this->begin(), psz, n);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::collate(RANGE range) const noexcept
//{
//  return NATURAL_POINTER::string_n_collate(this->begin(), psz, n);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_collate(RANGE range) const noexcept
//{
//  return NATURAL_POINTER::string_n_collate_ci(this->begin(), psz, n);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::order(strsize start, strsize count, const CHARACTER* psz) const
//{
//   return substr(start, count).order(psz);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_order(strsize start, strsize count, const CHARACTER* psz) const
//{
//   return substr(start, count).case_insensitive_order(psz);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::collate(strsize start, strsize count, const CHARACTER* psz) const
//{
//   return substr(start, count).collate(psz);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_collate(strsize start, strsize count, const CHARACTER* psz) const
//{
//   return substr(start, count).case_insensitive_order(psz);
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::order(strsize start, strsize count, const CHARACTER* psz, strsize start2, strsize count2) const
//{
//
//   return substr(start, count).order(string_base < ITERATOR_TYPE >(psz).substr(start2, count2));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_order(strsize start, strsize count, const CHARACTER* psz, strsize start2, strsize count2) const
//{
//
//   return substr(start, count).case_insensitive_order(string_base < ITERATOR_TYPE >(psz).substr(start2, count2));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::collate(strsize start, strsize count, const CHARACTER* psz, strsize start2, strsize count2) const
//{
//
//   return substr(start, count).collate(string_base < ITERATOR_TYPE >(psz).substr(start2, count2));
//
//}
//
//template < typename ITERATOR_TYPE >
//i32 string_base < ITERATOR_TYPE >::case_insensitive_collate(strsize start, strsize count, const CHARACTER* psz, strsize start2, strsize count2) const
//{
//
//   return substr(start, count).case_insensitive_collate(string_base < ITERATOR_TYPE >(psz).substr(start2, count2));
//
//}

template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains(RANGE range, strsize start, strsize count) const
{

   return find(range, start, count) >= 0;

}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains_ci(RANGE range, strsize start, strsize count) const
{

   return case_insensitive_find(range, start, count) >= 0;

}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   strsize iFind = find(psz, start, count, ppszEnd);
//
//   if (iFind < 0)
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
//bool string_base < ITERATOR_TYPE >::contains_ci(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   strsize iFind = case_insensitive_find(psz, start, count, ppszEnd);
//
//   if (iFind < 0)
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
//bool string_base < ITERATOR_TYPE >::contains(CHARACTER ch, strsize start, strsize count) const
//{
//
//   return find(ch, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(::wide_character wch, strsize start, strsize count) const
//{
//
//   return find_w(unicode_to_utf8(wch), start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(i32 i, strsize start, strsize count) const // utf8 CHARACTER index
//{
//
//   return find_w(unicode_to_utf8(i), start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(const CHARACTER* psz, strsize start, strsize count) const
//{
//
//   return find(psz, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains(RANGE range, strsize start, strsize count) const
//{
//
//   return find(range, start, count) >= 0;
//
//}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains(CHARACTER ch, strsize start, strsize count) const
{

   return find(ch, start, count) >= 0;

}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains_ci(CHARACTER ch, strsize start, strsize count) const
{

   return case_insensitive_find(ch, start, count) >= 0;

}

template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains(CHARACTER ch, strsize start, strsize count, const CHARACTER ** ppszBeg) const
{

   auto find = this->find(ch, start, count);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->begin() + find;

   }

   return true;

}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains_ci(CHARACTER ch, strsize start, strsize count, const CHARACTER ** ppszBeg) const
{

   auto find = case_insensitive_find(ch, start, count);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->begin() + find;

   }

   return true;

}



//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains_ci(::wide_character wch, strsize start, strsize count) const
//{
//
//   return find_wci(unicode_to_utf8(wch), start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains_ci(i32 i, strsize start, strsize count) const// utf8 CHARACTER index
//{
//
//   return find_wci(unicode_to_utf8(i), start, count) >= 0;
//
//}

//
//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains_ci(const CHARACTER* psz, strsize start, strsize count) const
//{
//
//   return case_insensitive_find(psz, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains_ci(RANGE range, strsize start, strsize count) const
//{
//
//   return case_insensitive_find(range, start, count) >= 0;
//
//}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   auto find = this->find(range, start, count);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->begin() + find;

   }

   if (::is_set(ppszEnd))
   {

      *ppszEnd = this->begin() + find + range.size();

   }

   return true;

}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains_ci(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   auto find = this->case_insensitive_find(range, start, count);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->begin() + find;

   }

   if (::is_set(ppszEnd))
   {

      *ppszEnd = this->begin() + find + range.size();

   }

   return true;

}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains_wci(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   auto find = this->find_wci(range, start, count);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->begin() + find;

   }

   if (::is_set(ppszEnd))
   {

      *ppszEnd = this->begin() + find + range.size();

   }

   return true;

}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains_wci(CHARACTER ch, strsize start, strsize count, const CHARACTER ** ppszBeg) const
//{
//
//   auto find = find_wci(ch, start, count);
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
//bool string_base < ITERATOR_TYPE >::contains(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto find = this->find(range, start, count, ppszEnd);
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
//bool string_base < ITERATOR_TYPE >::contains_ci(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto find = case_insensitive_find(range, start, count, ppszEnd);
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
//bool string_base < ITERATOR_TYPE >::contains_wci(RANGE range, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
//{
//
//   auto find = find_wci(range, start, count, ppszEnd);
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
//bool string_base < ITERATOR_TYPE >::contains_wci(CHARACTER wch, strsize start, strsize count) const
//{
//
//   return find_wci(wch, start, count) >= 0;
//
//}

//
//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains_wci(i32 i, strsize start, strsize count) const// utf8 CHARACTER index
//{
//
//   return find_wci(unicode_to_utf8(i), start, count) >= 0;
//
//}


template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::contains_wci(RANGE range, strsize start, strsize count) const
{

   return find_wci(range, start, count) >= 0;

}


//template < typename ITERATOR_TYPE >
//bool string_base < ITERATOR_TYPE >::contains_wci(RANGE range, strsize start, strsize count) const
//{
//
//   return find_wci(str, start, count) >= 0;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::erase(strsize start, strsize strsize)
//{
//
//   if (start < 0)
//   {
//
//      strsize = 0;
//
//   }
//
//   if (strsize < 0)
//   {
//
//      strsize = size();
//
//   }
//
//   Delete(start, strsize);
//
//   return *this;
//
//}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::erase(strsize iIndex, strsize count)
{

   strsize nLength = size();

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

      strsize nNewLength = nLength - count;

      strsize nCopy = nLength - (iIndex + count) + 1;

      CHARACTER * pszBuffer = get_string_buffer();

      memmove(pszBuffer + iIndex, pszBuffer + iIndex + count, (size_t)nCopy);

      release_string_buffer(nNewLength);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::Insert(strsize iIndex, CHARACTER ch)
{

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (iIndex > size())
   {

      iIndex = size();

   }

   strsize nNewLength = size() + 1;

   CHARACTER * pszBuffer = get_string_buffer(nNewLength);

   memmove(pszBuffer + iIndex + 1, pszBuffer + iIndex, nNewLength - iIndex);

   pszBuffer[iIndex] = ch;

   release_string_buffer(nNewLength);

   return nNewLength;

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::Insert(strsize iIndex, RANGE range)
{

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (iIndex > size())
   {

      iIndex = size();

   }

   // nInsertLength and nNewLength are in XCHARs

   strsize nInsertLength = range.size();

   strsize nNewLength = size();

   if (nInsertLength > 0)
   {

      nNewLength += nInsertLength;

      CHARACTER * pszBuffer = get_string_buffer(nNewLength);
      // move existing bytes down
      memmove(pszBuffer + iIndex + nInsertLength, pszBuffer + iIndex, (nNewLength - iIndex - nInsertLength + 1) * sizeof(CHARACTER));
      memcpy(pszBuffer + iIndex, range.begin(), nInsertLength * sizeof(CHARACTER));
      release_string_buffer(nNewLength);
   }

   return(nNewLength);
}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::replace_character(CHARACTER charNew, CHARACTER charOld, strsize start)
{
   strsize count = 0;

   // i16-circuit the nop case
   if (charOld != charNew)
   {
      // otherwise modify each character that matches in the string_base < ITERATOR_TYPE >
      bool bCopied = false;
      CHARACTER * pszBuffer = const_cast<CHARACTER *>(this->begin() + start);  // We don't actually write to pszBuffer until we've called get_string_buffer().

      strsize nLength = size();
      strsize iChar = 0;
      while (iChar < nLength)
      {
         // replace instances of the specified character only
         if (pszBuffer[iChar] == charOld)
         {
            if (!bCopied)
            {
               bCopied = true;
               pszBuffer = get_string_buffer(nLength);
            }
            pszBuffer[iChar] = charNew;
            count++;
         }
         iChar = strsize((pszBuffer + iChar + 1) - pszBuffer);
      }
      if (bCopied)
      {
         release_string_buffer(nLength);
      }
   }

   return(count);
}

//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::xxx_replace(CHARACTER charOld, CHARACTER charNew, strsize start)
//{
//
//   return replace_with(charNew, charOld, start);
//
//}


template < typename ITERATOR_TYPE >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
strsize string_base < ITERATOR_TYPE >::replace_with(RANGE rangeNew, RANGE rangeOld, strsize start)
{
   // can't have is_empty or nullptr pszOld


   // nSourceLen is in XCHARs
   strsize nSourceLen = rangeOld.size();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = rangeNew.size();

   // loop once to figure out the size_i32 of the result string_base < ITERATOR_TYPE >
   strsize count = 0;
   {
      const CHARACTER * pszStart = this->begin() + start;
      //      const CHARACTER * pszEnd = pszStart+size();
      const CHARACTER * pszTarget;
      while ((pszTarget = RANGE(pszStart).find(rangeOld)) != nullptr)
      {
         count++;
         pszStart = pszTarget + nSourceLen;
      }
   }

   // if any changes were made, make them
   if (count > 0)
   {
      // if the buffer is too small, just
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = size();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * count;

      CHARACTER * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      //CHARACTER * pszStart = pszBuffer + start;
      //CHARACTER * pszEnd = pszBuffer + nOldLength;
      RANGE range(pszBuffer + start, pszBuffer + nOldLength);

      // loop again to actually do the work
      while (range.begin() < range.end())
      {
         CHARACTER * pszTarget;
         while ((pszTarget = (CHARACTER *) range.find(rangeOld)) != nullptr)
         {
            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);
            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER));
            memcpy(pszTarget, rangeNew.begin(), nReplacementLen * sizeof(CHARACTER));

            range.m_begin = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);
         }
         range.m_begin += string_safe_length(range.m_begin) + 1;
      }
      ASSERT(pszBuffer[nNewLength] == 0);
      release_string_buffer(nNewLength);
   }

   return(count);
}


template < typename ITERATOR_TYPE >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
strsize string_base < ITERATOR_TYPE >::replace_with_ci(RANGE rangeNew, RANGE rangeOld, strsize start)
{

   // can't have is_empty or nullptr pszOld
   // nSourceLen is in XCHARs
   strsize nSourceLen = rangeOld.size();

   if (nSourceLen == 0)
   {

      return(0);

   }

   // nReplacementLen is in XCHARs
   strsize nReplacementLen = rangeNew.size();

   // loop once to figure out the size_i32 of the result string_base < ITERATOR_TYPE >
   strsize count = 0;

   {

      strsize i = start;

      strsize iFind;

      while ((iFind = case_insensitive_find(rangeOld, i, -1)) >= 0)
      {

         count++;

         i = iFind + nSourceLen;

      }

   }

   // if any changes were made, make them
   if (count > 0)
   {

      // if the buffer is too small, just
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = size();

      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * count;

      CHARACTER * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      strsize i = start;

      strsize nEnd = nNewLength;

      strsize iFind;

      // loop again to actually do the work
      while (i < nEnd)
      {
         
         while ((iFind = case_insensitive_find(rangeOld, i, -1)) >= 0)
         {

            auto pszTarget = pszBuffer + iFind;

            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER));

            memcpy(pszTarget, rangeOld.begin(), nReplacementLen * sizeof(CHARACTER));

            i += nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         i += string_safe_length(pszBuffer + 1) + 1;

      }
      
      ASSERT(pszBuffer[nNewLength] == 0);

      release_string_buffer(nNewLength);

   }

   return(count);

}


template < typename ITERATOR_TYPE >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
::count string_base < ITERATOR_TYPE >::replace_with_count(RANGE rangeNew, RANGE rangeOld, strsize start)
{
   // can't have is_empty or nullptr pszOld


   ::count c = 0;

   // nSourceLen is in XCHARs
   strsize nSourceLen = rangeOld.size();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = rangeNew.size();

   // loop once to figure out the size_i32 of the result string_base < ITERATOR_TYPE >
   strsize count = 0;
   {
      const CHARACTER * pszStart = this->begin() + start;
      //      const CHARACTER * pszEnd = pszStart+size();
      const CHARACTER * pszTarget;
      while ((pszTarget = string_find_string(pszStart, rangeOld)) != nullptr)
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
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = size();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * count;

      CHARACTER * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      const CHARACTER * pszStart = pszBuffer + start;
      const CHARACTER * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHARACTER * pszTarget;

         while ((pszTarget = (CHARACTER *)string_find_string(pszStart, rangeOld)) != nullptr)
         {

            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

            memmove((void *)(pszTarget + nReplacementLen), pszTarget + nSourceLen, nBalance * sizeof(CHARACTER));

            memcpy((void *)pszTarget, rangeNew, nReplacementLen * sizeof(CHARACTER));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_string_buffer(nNewLength);

   }

   return c;

}


template < typename ITERATOR_TYPE >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
::count string_base < ITERATOR_TYPE >::replace_with_ci_count(RANGE rangeNew, RANGE rangeOld, strsize start)
{
   // can't have is_empty or nullptr pszOld


   ::count c = 0;

   // nSourceLen is in XCHARs
   strsize nSourceLen = rangeOld.size();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = rangeOld.size();

   // loop once to figure out the size_i32 of the result string_base < ITERATOR_TYPE >
   strsize count = 0;
   {
      const CHARACTER * pszStart = this->begin() + start;
      //      const CHARACTER * pszEnd = pszStart+size();
      const CHARACTER * pszTarget;
      while ((pszTarget = string_find_string_ci(pszStart, rangeOld)) != nullptr)
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
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = size();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * count;

      CHARACTER * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      CHARACTER * pszStart = pszBuffer + start;
      CHARACTER * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHARACTER * pszTarget;

         while ((pszTarget = (CHARACTER *)string_find_string_ci(pszStart, rangeOld)) != nullptr)
         {

            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER));

            memcpy(pszTarget, rangeNew, nReplacementLen * sizeof(CHARACTER));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_string_buffer(nNewLength);

   }

   return c;

}

template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::replace(strsize start, strsize count, RANGE range)
{

   if (count < 0)
   {

      auto len = start + range.size();

      auto psz = get_string_buffer(len);

      string_count_copy(psz + start, range.begin(), range.size());

      release_string_buffer(len);

      return *this;

   }
   else
   {

      auto len = start + range.size() + (size() - (start + count));

      auto psz = get_string_buffer(len);

      memmove(psz + start + range.size(), psz + start + count);

      string_count_copy(psz + start, range.begin(), range.size());

      release_string_buffer(len);

      return *this;

   }

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::replace(strsize start, strsize count, RANGE range, strsize nSubLen)
{

   nSubLen = minimum_maximum(nSubLen, 0, range.size());

   if (count < 0)
   {

      auto len = start + nSubLen;

      auto psz = get_string_buffer(len);

      string_count_copy(psz + start, range.begin(), nSubLen);

      release_string_buffer(len);

      return *this;

   }
   else
   {

      auto len = start + nSubLen + (size() - (start + count));

      auto psz = get_string_buffer(len);

      memmove(psz + start + nSubLen, psz + start + count);

      string_count_copy(psz + start, range.begin(), nSubLen);

      release_string_buffer(len);

      return *this;

   }

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::erase_character(CHARACTER chRemove)
{

   strsize nLength = size();

   CHARACTER * pszBuffer = get_string_buffer(nLength);

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
   strsize count = strsize(pszSource - pszDest);
   release_string_buffer(nLength - count);

   return(count);

}

// find the first occurrence of character 'ch', starting at strsize 'start'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::find(CHARACTER ch) const RELEASENOTHROW
{

   auto psz = string_find_character(this->begin(), ch);

   if (!psz)
   {

      return -1;

   }

   return psz - this->begin();

}



template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::find(CHARACTER ch, strsize start) const RELEASENOTHROW
{

   auto psz = string_find_character(this->begin() + start, ch);

   if (!psz)
   {

      return -1;

   }

   return psz - this->begin();

}

// find routines

// find the first occurrence of character 'ch', starting at strsize 'start'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::find(CHARACTER ch, strsize start, strsize count) const RELEASENOTHROW
{
   // start is in XCHARs
   ASSERT(start >= 0);

   // nLength is in XCHARs
   strsize nLength = size();
   if (start < 0 || start >= nLength)
   {
      return -1;
   }

   if (count < 0)
      count = nLength;

   if (count + start > nLength)
      count = nLength - start;

   if (count < 0)
      return -1;

   auto psz = this->begin() + start;

   for (i32 i = 0; i < count; i++)
   {

      if (psz[i] == ch)
      {

         return start + i;

      }

   }

   return -1;

}

// find the first occurrence of character 'ch', starting at strsize 'start'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::case_insensitive_find(CHARACTER ch, strsize start, strsize count) const RELEASENOTHROW
{
   // start is in XCHARs
   ASSERT(start >= 0);

   // nLength is in XCHARs
   strsize nLength = size();
   if (start < 0 || start >= nLength)
   {
      return(-1);
   }

   if (count < 0)
      count = nLength;

   if (count + start > nLength)
      count = nLength - start;

   if (count < 0)
      return -1;

   auto psz = this->begin() + start;

   for (i32 i = 0; i < count; i++)
   {

      if (character_tolower(psz[i]) == character_tolower(ch))
      {

         return start + i;

      }

   }


   return -1;
}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::scan_whitespace(strsize start) const RELEASENOTHROW
{

   return scan("\t\n\r ", start);

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::span_whitespace(strsize start) const RELEASENOTHROW
{

   return span("\t\n\r ", start);

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::find_first(CHARACTER ch, strsize start) const RELEASENOTHROW
{
   
   return ::string_find_character(this->begin()+start, ch);

}



// iconic prime good doxygen comment



///
/// @brief Find the first occurrence of \p range, starting at \p start position and up 
/// to \p count characters from \p start.
/// Optionally returns at \p ppszTail the address immediately after
/// where \p range was found in the string.
/// 
/// @param range [in] range to search for.
/// @param start [in] position where to start the start.
/// @param iCount [in] amount of characters since \p start 
///    to continue searching for \p range
/// @param ppszTail [out,opt] address immediately after where \p range 
///    was found in the string.
/// @return position where \p range was found respecting \p start 
///    and \p iCount or -1 if not found.
/// 
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::find(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   return offset_of(RANGE(this->begin() + start, count).find(range));


   //strsize rangeLen;

   //strsize nEndExclusive;

   //strsize i;

   //if (_find_prefix(i, range, start, count, rangeLen, nEndExclusive))
   //{

   //   return i;

   //}

   //auto psz = this->begin();

   //auto pszBlock = range.begin();

   //for (; i < nEndExclusive; i++)
   //{

   //   bool bFound = true;

   //   auto j = i;

   //   for (; j < rangeLen; j++)
   //   {

   //      if (psz[j] != pszBlock[j])
   //      {

   //         bFound = false;

   //         break;

   //      }

   //   }

   //   if (bFound)
   //   {

   //      if (::is_set(ppszTail))
   //      {

   //         *ppszTail = psz + j;

   //      }

   //      return i;

   //   }

   //   psz++;

   //}

   //return -1;

}


/// @brief find the first occurrence of a range
/// string_base < ITERATOR_TYPE > 'range', starting at strsize 'start'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::case_insensitive_find(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   return offset_of(RANGE(this->begin() + start, count).find(range, ::comparison::case_insensitive < CHARACTER >()));

   //strsize rangeLen;

   //strsize nEndExclusive;

   //strsize i;

   //if (_find_prefix(i, range, start, count, rangeLen, nEndExclusive))
   //{

   //   return i;

   //}

   //auto psz = this->begin();

   //auto pszBlock = range.begin();

   //for (; i < nEndExclusive; i++)
   //{

   //   bool bFound = true;

   //   auto j = i;

   //   for (; j < rangeLen; j++)
   //   {

   //      if (character_tolower(psz[j]) != character_tolower(pszBlock[j]))
   //      {

   //         bFound = false;

   //         break;

   //      }

   //   }

   //   if (bFound)
   //   {

   //      if (::is_set(ppszTail))
   //      {

   //         *ppszTail = psz + j;

   //      }

   //      return i;

   //   }

   //   psz++;

   //}

   //return -1;

}


// find the first occurrence of string_base < ITERATOR_TYPE > 'range', starting at strsize 'start'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::unicode_find(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   const_iterator p;

   RANGE rangeScope{ this->begin() + start, count };

   if (_find_prefix(p, range, rangeScope))
   {

      return offset_if(p);

   }

   auto psz = (const CHARACTER * ) p;

   auto pszBlock = (const CHARACTER * ) range.begin();

   auto pszBlockEnd = (const CHARACTER *)range.end();

   for (; psz < rangeScope.m_end; psz++)
   {
      
      auto psz2 = psz;

      auto pszBlock2 = pszBlock;

      ::i32 len1;

      ::i32 len2;

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
 
         return offset_of(psz);

      }

      ::unicode_increment(psz);

   }

   return -1;

}


// find the first occurrence of string_base < ITERATOR_TYPE > 'range', starting at strsize 'start'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::case_insensitive_unicode_find(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   const_iterator p;

   RANGE rangeScope{ this->begin() + start, count };

   if (_find_prefix(p, range, rangeScope))
   {

      return offset_if(p);

   }

   auto psz = (const CHARACTER *)p;

   auto pszBlock = (const CHARACTER *)range.begin();

   auto pszBlockEnd = (const CHARACTER *)range.end();

   for (; psz < rangeScope.m_end; psz++)
   {

      bool bFound = true;

      const CHARACTER * psz2 = psz;

      const CHARACTER * pszSub2 = range;

      ::i32 len1;

      ::i32 len2;

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

            return offset_of(psz);

         }
         else
         {

            return -1;

         }

      }

      psz++;

   }

   return -1;

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_find(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   const CHARACTER * p;

   if (::is_null(p = find(range, start, count)))
   {

      return -1;

   }

   return offset_of(p + range.size());

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_unicode_find(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   const CHARACTER * p;

   if (::is_null(p = find_w(range, start, count)))
   {

      return -1;

   }

   return offset_of(p + range.size());

}


template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_case_insensitive_unicode_find(RANGE range, strsize start, strsize count) const RELEASENOTHROW
{

   const CHARACTER * p;

   if (::is_null(p = find_unicode_ci(range, start, count)))
   {

      return -1;

   }

   return offset_of(p + range.size());

}


// find the first occurrence of any of the characters in string_base < ITERATOR_TYPE > 'pszCharSet'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::scan(RANGE rangeCharacters, strsize start, strsize n) const RELEASENOTHROW
{

   auto p = string_scan({ this->begin() + start, size() - start }, rangeCharacters);

   return ::is_set(p) ? offset_of(p) : -1;

}



// find the first occurrence of any of the characters in string_base < ITERATOR_TYPE > 'pszCharSet'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::scan(const CHARACTER * pszCharacters, strsize start) const RELEASENOTHROW
{

   auto p = string_pbrk(this->begin() + start, pszCharacters);

   return ::is_set(p) ? offset_of(p) : -1;

}


//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::scan(RANGE rangeCharacters, strsize start) const RELEASENOTHROW
//{
//
//   return scan(rangeCharacters, start);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::scan(RANGE rangeCharacters, strsize start, strsize n) const RELEASENOTHROW
//{
//
//   return scan(rangeCharacters, start, n);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::scan(const CHARACTER * pszCharacters, strsize pos) const RELEASENOTHROW
//{
//
//   return find_one_of(pszCharacters, pos);
//
//}
//
//
////template < typename ITERATOR_TYPE >
////strsize string_base < ITERATOR_TYPE >::find_first_of(CHARACTER ch, strsize pos) const RELEASENOTHROW
////{
////
////   return ::string_find_character(this->begin() + pos, ch);
////
////}


//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::find_first_of(CHARACTER ch, strsize pos, strsize count) const RELEASENOTHROW
//{
//
//   return ::string_find_character(this->begin() + pos, ch, count);
//
//}


//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::span(RANGE range, strsize pos) const RELEASENOTHROW
//{
//   
//   return find_first_not_of(range, pos, size());
//
//}
//
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::span(const CHARACTER * psz, strsize pos) const
//RELEASENOTHROW
//{
//
//   return ::string_find_first_not_of(, pos);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::span(CHARACTER ca, strsize pos) const
//RELEASENOTHROW
//{
//   strsize nLength = size();
//
//   if (pos < 0 || pos >= nLength)
//      return -1;
//   RANGE range = &this->begin()[pos];
//   while (*psz != '\0' && *psz == ca)
//   {
//      psz++;
//   }
//   if (*psz == '\0')
//      return -1;
//   else
//      return psz - this->begin();
//}
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::span(RANGE range, strsize pos, strsize n) const
//RELEASENOTHROW
//{
//   string_base < ITERATOR_TYPE > strChars(s, n);
//
//   strsize nLength = size();
//
//   if (pos < 0 || pos >= nLength)
//      return -1;
//   RANGE range = &this->begin()[pos];
//   while (*psz != '\0' && strChars.contains(*psz))
//   {
//      psz++;
//   }
//   if (*psz == '\0')
//      return -1;
//   else
//      return psz - this->begin();
//}


// find the first occurrence of any of the characters in string_base < ITERATOR_TYPE > 'pszCharSet'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_skip(CHARACTER ch, strsize start) const RELEASENOTHROW
{

   return offset_of(NATURAL_POINTER::rear_skip_start(ch, start));

   //strsize nLength = size();
   //// nLength is in XCHARs
   //if (pos < 0)
   //   pos = nLength - 1;
   //if (pos < 0 || pos >= nLength)
   //{
   //   return(-1);
   //}
   //auto psz = this->begin();
   //while (pos >= 0 && psz[pos] != ca)
   //{
   //   pos--;
   //}
   //return pos;
}

//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::rear_scan(const CHARACTER * pszCharSet, strsize start) const RELEASENOTHROW
//{
//   return find_last_of(pszCharSet, start, -1);
//}
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::rear_scan(const CHARACTER * pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
//{
//   strsize nLength = size();
//   // nLength is in XCHARs
//   if (pos < 0)
//      pos = nLength - 1;
//   if (pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   string_base < ITERATOR_TYPE > strChars(pszCharSet, n);
//   auto psz = this->begin();
//   while (pos >= 0 && !strChars.contains(psz[pos]))
//   {
//      pos--;
//   }
//   return pos;
//}
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::rear_scan(RANGE range strCharSet, strsize pos) const RELEASENOTHROW
//{
//   return find_last_of(strCharSet, pos, strCharSet.size());
//}
//
//
//// find the first occurrence of any of the characters in string_base < ITERATOR_TYPE > 'pszCharSet'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_skip(CHARACTER ch, strsize start, strsize count) const RELEASENOTHROW
{

   return offset_of(NATURAL_POINTER::rear_skip_start_count(ch, start, count));

}
//   strsize nLength = size();
//   // nLength is in XCHARs
//   if (pos < 0)
//      pos = nLength - 1;
//   if (pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   auto psz = this->begin();
//   while (pos >= 0 && psz[pos] == ca)
//   {
//      pos--;
//   }
//   return pos;
//}
//
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_span(RANGE rangeCharacters, strsize start) const RELEASENOTHROW
{
   return offset_of(NATURAL_POINTER::rear_span_start(rangeCharacters, start));
}
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_span(RANGE rangeCharacters, strsize start, strsize count) const RELEASENOTHROW
{
   return offset_of(NATURAL_POINTER::rear_span_start_count(rangeCharacters, start, count));
}
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::rear_span(const CHARACTER * pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
//{
//   strsize nLength = size();
//   // nLength is in XCHARs
//   if (pos < 0)
//      pos = nLength - 1;
//   if (pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   string_base < ITERATOR_TYPE > strChars(pszCharSet, n);
//   auto psz = this->begin();
//   while (pos >= 0 && strChars.contains(psz[pos]))
//   {
//      pos--;
//   }
//   return pos;
//}
//
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::rear_span(RANGE range strCharSet, strsize pos) const RELEASENOTHROW
//{
//   return find_last_not_of(strCharSet, pos, strCharSet.size());
//}


//// find the last occurrence of character 'ch'
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::rear_find(CHARACTER ch, strsize count) const RELEASENOTHROW
//{
//   // find last single character
//   auto psz = string_rear_find_character({ this->begin(), size() + count + 1}, ch);
//
//   // return -1 if not found, distance from beginning otherwise
//   return ::is_set(psz) ? strsize(psz - this->begin()) : -1;
//
//}
//

template < typename ITERATOR_TYPE >
typename string_base < ITERATOR_TYPE >::CHARACTER string_base < ITERATOR_TYPE >::last_char(strsize count) const
{

   return *(this->begin() + length() + count);
}

// find the last occurrence of character 'ch'
template < typename ITERATOR_TYPE >
strsize string_base < ITERATOR_TYPE >::rear_find(RANGE range, strsize start) const RELEASENOTHROW
{
   return offset_of(NATURAL_POINTER::rear_find_start(range, start));
}

// manipulation


//// find the last occurrence of character 'ch'
//template < typename ITERATOR_TYPE >
//strsize string_base < ITERATOR_TYPE >::rear_find(const CHARACTER * ch, strsize start) const RELEASENOTHROW
//{
//   // find last single character
//   RANGE range = string_find_string_reverse(this->begin(), ch, start);
//
//   // return -1 if not found, distance from beginning otherwise
//   return((psz == nullptr) ? -1 : strsize(psz - this->begin()));
//}
//
//// manipulation

// Convert the string_base < ITERATOR_TYPE > to uppercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::make_upper()
{
   strsize nLength = size();
   CHARACTER * pszBuffer = get_string_buffer(nLength);
   string_uppercase(pszBuffer, nLength + 1);
   release_string_buffer(nLength);

   return *this;
}

// Convert the string_base < ITERATOR_TYPE > to lowercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::make_lower()
{
   strsize nLength = size();
   CHARACTER * pszBuffer = get_string_buffer(nLength);
   string_lowercase(pszBuffer, nLength + 1);
   release_string_buffer(nLength);

   return *this;
}

// Reverse the string_base < ITERATOR_TYPE >
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::MakeReverse()
{
   strsize nLength = size();
   CHARACTER * pszBuffer = get_string_buffer(nLength);
   string_reverse(pszBuffer);
   release_string_buffer(nLength);

   return *this;
}

// trimming

// erase all trailing whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_right()
{

   const CHARACTER * pszLast = nullptr;
   const CHARACTER * pszMax = this->begin() + size();
   auto psz = pszMax;

   if (psz != nullptr)
   {

      while (true)
      {

         psz = unicode_prior(psz, this->begin());

         if (psz < this->begin())
         {

            break;

         }

         if (!unicode_is_whitespace(psz))
         {

            pszLast = unicode_next(psz);

            break;

         }

      }

   }

   if (pszLast != nullptr && pszLast < pszMax)
   {

      // truncate at trailing space start

      strsize iLast = strsize(pszLast - this->begin());

      truncate(iLast);

   }

   return *this;

}

// erase all leading whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_left()
{
   // find first non-space character

   auto i = span_whitespace();

   if (i > 0)
   {

      erase_beginning(i);

   }

   return *this;

   //auto psz = this->begin();

   //strsize iHere;

   //while (unicode_is_whitespace(psz))
   //{

   //   unicode_increment(psz);

   //   iHere = (strsize)(psz - this->begin());

   //   if (iHere >= size())
   //   {

   //      if (iHere == size())
   //      {

   //         break;

   //      }
   //      else
   //      {

   //         return *this;

   //      }


   //   }

   //}


   //if (psz != this->begin())
   //{
   //   // fix up begin and length
   //   strsize iFirst = strsize(psz - this->begin());

   //   CHARACTER * pszBuffer = get_string_buffer(size());

   //   psz = pszBuffer + iFirst;

   //   strsize nDataLength = size() - iFirst;

   //   memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER));

   //   release_string_buffer(nDataLength);

   //}

   //return *this;
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
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim(RANGE rangeTargets)
{
   return trim_right(rangeTargets).trim_left(rangeTargets);
}

// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_right(CHARACTER chTarget)
{
   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   auto psz = this->begin();
   const CHARACTER * pszLast = nullptr;

   while (*psz != 0)
   {
      if (*psz == chTarget)
      {
         if (pszLast == nullptr)
         {
            pszLast = psz;
         }
      }
      else
      {
         pszLast = nullptr;
      }

      unicode_increment(psz);

   }

   if (pszLast != nullptr)
   {
      // truncate at left-most matching character
      strsize iLast = strsize(pszLast - this->begin());
      truncate(iLast);
   }

   return *this;

}


// erase all trailing occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_right(RANGE rangeCharacters)
//template < pointer_castable < CHARACTER > PCHAR>
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::trim_right(PCHAR szTargets)
{

   auto i = rear_scan(rangeCharacters);

   if (i >= 0 && i < size())
   {

      truncate(i);

   }

   return *this;

   //auto pszTargets = rangezTargets.begin();

   //// if we're not trimming anything, we're not doing any work
   //if ((pszTargets == nullptr) || (*pszTargets == 0))
   //{
   //   return *this;
   //}

   //// find beginning of trailing matches
   //// by starting at beginning (DBCS aware)

   //auto psz = this->begin();
   //const CHARACTER * pszStart = psz;
   //const CHARACTER * pszLast = nullptr;

   //while (!::is_null(psz, 1024) && *psz != 0)
   //{
   //   if (string_find_char(pszTargets, *psz) != nullptr)
   //   {
   //      if (pszLast == nullptr)
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

   //if (pszLast != nullptr)
   //{
   //   // truncate at left-most matching character
   //   strsize iLast = strsize(pszLast - pszStart);
   //   truncate(iLast);
   //}

   //return *this;

}


// erase all leading occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_left(CHARACTER chTarget)
{

   auto i = skip(chTarget);

   if (i > 0)
   {

      operator =(this->begin() + i);

   }

   //// find first non-matching character
   //auto psz = this->begin();

   //while (chTarget == *psz)
   //{

   //   unicode_increment(psz);

   //}

   //if (psz != this->begin())
   //{
   //   // fix up begin and length
   //   strsize iFirst = strsize(psz - this->begin());
   //   CHARACTER * pszBuffer = get_string_buffer(size());
   //   psz = pszBuffer + iFirst;
   //   strsize nDataLength = size() - iFirst;
   //   memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER));
   //   release_string_buffer(nDataLength);
   //}

   return *this;

}


// erase all leading occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::trim_left(RANGE rangeCharacters)
//template < pointer_castable < CHARACTER > PCHAR >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::trim_left(PCHAR szTargets)
{

   auto i = span(rangeCharacters);

   if (i > 0)
   {

      assign(this->begin() + i, size() - i);

   }

   return *this;

   //const CHARACTER * pszTargets = szTargets;

   //// if we're not trimming anything, we're not doing any work
   //if ((pszTargets == nullptr) || (*pszTargets == 0))
   //{
   //   return *this;
   //}

   //auto psz = this->begin();
   //while ((*psz != 0) && (string_find_char(pszTargets, *psz) != nullptr))
   //{
   //   unicode_increment(psz);
   //}

   //if (psz != this->begin())
   //{
   //   // fix up begin and length
   //   strsize iFirst = strsize(psz - this->begin());
   //   CHARACTER * pszBuffer = get_string_buffer(size());
   //   psz = pszBuffer + iFirst;
   //   strsize nDataLength = size() - iFirst;
   //   memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER));
   //   release_string_buffer(nDataLength);
   //}

   //return *this;
}


// erase all trailing whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::right_trimmed() const
{

   string_base < ITERATOR_TYPE > str(*this);

   str.trim_right();

   return str;

}


// erase all leading whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::left_trimmed() const
{

   string_base < ITERATOR_TYPE > str(*this);

   str.trim_left();

   return str;

}


// erase all leading and trailing whitespace
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::trimmed() const
{

   string_base < ITERATOR_TYPE > str(*this);

   str.trim();

   return str;

}


// erase all leading and trailing occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::trimmed(CHARACTER chTarget) const
{

   string_base < ITERATOR_TYPE > str(*this);

   str.trim(chTarget);

   return str;

}


// erase all leading and trailing occurrences of any of the characters in the string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::trimmed(RANGE rangeCharacters) const
{

   auto str(*this);

   str.trim(rangeCharacters);

   return ::move(str);

}


// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::right_trimmed(CHARACTER chTarget) const
{

   auto str(*this);

   str.trim_right(chTarget);

   return ::move(str);

}


// erase all trailing occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::right_trimmed(RANGE rangeCharacters) const
{

   auto str(*this);

   str.trim_right(rangeCharacters);

   return ::move(str);

}


// erase all leading occurrences of character 'chTarget'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::left_trimmed(CHARACTER chTarget) const
{

   string_base < ITERATOR_TYPE > str(*this);

   str.trim_left(chTarget);

   return str;

}


// erase all leading occurrences of any of the characters in string_base < ITERATOR_TYPE > 'pszTargets'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::left_trimmed(RANGE rangeCharacters) const
{

   auto str(*this);

   str.trim_left(rangeCharacters);

   return ::move(str);

}

//CLASS_DECL_ACME void __throw_what_exclamation_exclamation(const char * ::payload);


// Convert the string_base < ITERATOR_TYPE > to the OEM character set
template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::AnsiToOem()
{
   throw_exception(error_what_exclamation_exclamation, "AnsiToOem WTF AnsiToOem ANSI is already WTF, Oem is very WTF, and what to say about ANSItoOEM");
   //strsize nLength = size();
   //CHARACTER* pszBuffer = get_string_buffer(nLength);
   //ConvertToOem(pszBuffer, nLength + 1);
   //release_string_buffer(nLength);
}

// Convert the string_base < ITERATOR_TYPE > to the ANSI character set
template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::OemToAnsi()
{
   throw_exception(error_what_exclamation_exclamation, "AnsiToOem WTF AnsiToOem ANSI is already WTF, Oem is very WTF, and what to say about ANSItoOEM Ah?!?! :/ OEMtoANSI, now a bit lesser (or more?) WTF, WHAT?! WTF Power 10!!");
   //strsize nLength = size();
   //CHARACTER* pszBuffer = get_string_buffer(nLength);
   //convert_to_ansi(pszBuffer, nLength + 1);
   //release_string_buffer(nLength);
}

// Very simple sub-string_base < ITERATOR_TYPE > extraction

// Return the substring starting at strsize 'iFirst'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::Mid(strsize iFirst) const
{
   return Mid(iFirst, -1);
}

template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::substr(strsize iFirst) const
{
   return Mid(iFirst);
}

// Return the substring starting at strsize 'iFirst', with length 'count'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::Mid(strsize iFirst, strsize count) const
{
   // count is in XCHARs

   // out-of-bounds requests return sensible things

   strsize nLength = size();

   if (iFirst < 0)
      iFirst = 0;

   if (count < 0)
      count = nLength + count + 1;

   if (count + iFirst > nLength)
      count = nLength - iFirst;

   if (count < 0)
      return "";

   if (iFirst + count > size())
   {

      count = size() - iFirst;

   }

   if (iFirst > size())
   {
      count = 0;
   }

   ASSERT((count == 0) || ((iFirst + count) <= size()));

   // optimize case of returning entire string_base < ITERATOR_TYPE >
   if ((iFirst == 0) && ((iFirst + count) == size()))
   {
      return *this;
   }

   return(string_base < ITERATOR_TYPE >(this->begin() + iFirst, count));

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::substr(strsize iFirst, strsize count) const
{

   return Mid(iFirst, count);

}


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::clear()
{

   Empty();

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::Right(strsize count) const
{

   if (count < 0)
   {

      count = 0;

   }

   strsize nLength = size();

   if (count >= nLength)
   {

      return *this;

   }

   return(string_base < ITERATOR_TYPE >(this->begin() + nLength - count, count));

}


// Return the substring consisting of the leftmost 'count' characters
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::Left(strsize count) const
{

   // count is in XCHARs
   if (count < 0)
   {

      count = 0;

   }

   strsize nLength = size();

   if (count >= nLength)
   {

      return *this;

   }

   return(string_base < ITERATOR_TYPE >(this->begin(), count));

}


// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::scan_including(RANGE rangeCharacters, strsize start, strsize iCount) const
{

   auto i = scan(rangeCharacters, start, iCount);

   if (i <= 0)
   {

      return {};

   }
   else
   {

      return { this->begin() + i, ::minimum(iCount, size() - i) };

   }

}


// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::span_excluding(RANGE rangeCharacters, strsize start, strsize iCount) const
{

   auto i = span(rangeCharacters, start, iCount);

   if (i <= 0)
   {

      return {};

   }
   else
   {

      return { this->begin() + i, ::minimum(iCount, size() - i) };

   }

}


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::append_format_arguments(const CHARACTER * pszFormat, va_list args)
{

   ASSERT(__is_valid_string(pszFormat));

   strsize nCurrentLength = size();

   va_list argsForCount;

   va_copy(argsForCount, args);

   strsize nAppendLength = get_formatted_length(pszFormat, argsForCount);

   va_end(argsForCount);

   CHARACTER * pszBuffer = get_string_buffer(nCurrentLength + nAppendLength);

   string_format(pszBuffer + nCurrentLength, nAppendLength + 1, pszFormat, args);

   release_string_buffer(nCurrentLength + nAppendLength);

}


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::format_arguments(const CHARACTER * pszFormat, va_list args)
{

   ASSERT(__is_valid_string(pszFormat));

   if (pszFormat == nullptr)
   {

      throw_exception(error_bad_argument);

   }

   va_list ptr1;

   va_copy(ptr1, args);

   strsize nLength = get_formatted_length(pszFormat, ptr1);

   va_end(ptr1);

   CHARACTER * pszBuffer = get_string_buffer(nLength);

   va_list ptr2;

   va_copy(ptr2, args);

   ansistring_format(pszBuffer, nLength + 1, pszFormat, ptr2);

   va_end(ptr2);

   release_string_buffer(nLength);

}


// set the string_base < ITERATOR_TYPE > to the value of environment ::payload 'pszVar'
// template < typename ITERATOR_TYPE >
// bool string_base < ITERATOR_TYPE >::xxxget_environment_variable(const CHARACTER* pszVar)
// {

//    u32 nLength = xxxget_environment_variable(pszVar, nullptr, 0);

//    bool bRetVal = false;

//    if (nLength == 0)
//    {

//       Empty();

//    }
//    else
//    {

//       CHARACTER* pszBuffer = get_string_buffer(nLength);

//       xxxget_environment_variable(pszVar, pszBuffer, nLength);

//       release_string_buffer();

//       bRetVal = true;

//    }

//    return(bRetVal);

// }


// template < typename ITERATOR_TYPE >
// bool string_base < ITERATOR_TYPE >::xxxgetenv(const CHARACTER* pszVar)
// {

//    return xxxget_environment_variable(pszVar);

// }



template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::format(const CHARACTER * pszFormat, ...)
{

   ASSERT(__is_valid_string(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   format_arguments(pszFormat, argList);

   va_end(argList);

}


// append formatted begin using format string_base < ITERATOR_TYPE > 'pszFormat'
template < typename ITERATOR_TYPE >
void __cdecl string_base < ITERATOR_TYPE >::append_format(const CHARACTER * pszFormat, ...)
{

   ASSERT(__is_valid_string(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   append_format_arguments(pszFormat, argList);

   va_end(argList);

}


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::reserve(strsize res_arg)
{
   get_string_buffer(res_arg + 1);
}



// Convert the string_base < ITERATOR_TYPE > to uppercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::uppered() const
{

   return string_base < ITERATOR_TYPE >(*this).make_upper();

}

// Convert the string_base < ITERATOR_TYPE > to lowercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::lowered() const
{

   return string_base < ITERATOR_TYPE >(*this).make_lower();

}

// Convert the string_base < ITERATOR_TYPE > to lowercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::reversed() const
{

   return string_base < ITERATOR_TYPE >(*this).MakeReverse();

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::unichar_substr(strsize iFirst) const
{

   return unichar_substr(iFirst, -1);

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > string_base < ITERATOR_TYPE >::unichar_substr(strsize iFirst, strsize count) const
{

   const CHARACTER * pchStart = *this;

   if (pchStart == nullptr)
      return "";

   ::count iUtf8Len = unichar_count();

   if (iFirst < 0)
      iFirst = iUtf8Len + iFirst;

   if (count < 0)
      count = iUtf8Len - iFirst + count + 1;

   if (iFirst + count > iUtf8Len)
      count = iUtf8Len - iFirst;

   if (count <= 0)
      return "";

   ::count ca = 0;

   while (ca < iFirst && *pchStart != '\0')
   {

      pchStart = unicode_increment(pchStart);

      ca++;

   }

   if (*pchStart == '\0')
      return "";

   const CHARACTER * pchEnd = pchStart;

   ca = 0;

   while (ca < count && *pchEnd != '\0')
   {

      pchEnd = unicode_increment(pchEnd);

      ca++;

   }

   return string_base < ITERATOR_TYPE >(pchStart, pchEnd - pchStart);


}

//template < typename ITERATOR_TYPE >
//::count string_base < ITERATOR_TYPE >::unichar_count() const
//{
//
//   const CHARACTER* pch = *this;
//
//   if (pch == nullptr)
//      return 0;
//
//   ::count cCharCount = 0;
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
strsize string_base < ITERATOR_TYPE >::char_type_count(strsize iUnicharCount) const
{

   strsize iFinalLen = 0;

   auto psz = operator const CHARACTER * ();

   strsize cMaxLen = size();

   while (iUnicharCount > 0)
   {

      auto iLen = unicode_len(psz);

      psz += iLen;

      iFinalLen += iLen;

      if (iFinalLen >= cMaxLen)
      {

         return cMaxLen;

      }

      iUnicharCount--;

   }

   return iFinalLen;

}



template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::eat_before(string_base < ITERATOR_TYPE > & strBefore, RANGE rangeSeparator, bool bEatEverythingIfNotFound)
{

   ASSERT(this != &strBefore);

   if (this == &strBefore)
   {

      return false;

   }

   index iFind = this->find(rangeSeparator);

   if (iFind < 0)
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = *this;

         this->Empty();

      }

      return false;

   }

   strBefore = this->Left(iFind);

   *this = this->Mid(iFind + rangeSeparator.size());

   return true;

}



template < typename ITERATOR_TYPE >
bool string_base < ITERATOR_TYPE >::eat_before_let_separator(string_base < ITERATOR_TYPE > & strBefore, RANGE rangeSeparator, bool bEatEverythingIfNotFound)
{

   ASSERT(this != &strBefore);

   if (this == &strBefore)
   {

      return false;

   }

   index iFind = this->find(rangeSeparator);

   if (iFind < 0)
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = *this;

         *this = rangeSeparator;

      }

      return false;

   }

   strBefore = this->Left(iFind);

   *this = this->Mid(iFind);

   return true;

}


template < typename ITERATOR_TYPE >
void string_base < ITERATOR_TYPE >::push_back(CHARACTER ch)
{

   operator += (ch);

}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE >& string_base < ITERATOR_TYPE >::operator = (const ::string_stream& str)
//{
//
//   return this->operator =(str.operator RANGE range ());
//
//}
//















//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::begins(RANGE range) const
//{
//
//   return string_range_begins<CHARACTER>(*this,range);
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::ends(RANGE range) const
//{
//
//   return string_range_ends<CHARACTER>(*this, range);
//
//}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins(RANGE range) const
{

   return NATURAL_POINTER::begins(range, ::comparison::case_insensitive < CHARACTER >());

}



template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends(RANGE range) const
{

   return NATURAL_POINTER::ends(range, ::comparison::case_insensitive < CHARACTER >());

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::begins_eat(RANGE rangePrefix)
{

   if (!this->begins(rangePrefix))
   {

      return false;

   }

   assign(this->begin() + rangePrefix.size(), size() - rangePrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::ends_eat(RANGE rangeSuffix)
{

   if (!this->ends(rangeSuffix))
   {

      return false;

   }

   assign(this->begin(), size() - rangeSuffix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins_eat(RANGE rangePrefix)
{

   if (!case_insensitive_begins(rangePrefix))
   {

      return false;

   }

   assign(this->begin() + rangePrefix.size(), size() - rangePrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends_eat(RANGE rangeSuffix)
{

   if (!case_insensitive_ends(rangeSuffix))
   {

      return false;

   }

   assign(this->begin(), size() - rangeSuffix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_begins(RANGE rangePrefix)
{

   if (!begins(rangePrefix))
   {

      operator =(rangePrefix + *this);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_begins_ci(RANGE rangePrefix)
{

   if (!case_insensitive_begins(rangePrefix))
   {

      operator =(rangePrefix + *this);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_ends(RANGE rangeSuffix)
{

   if (!ends(rangeSuffix))
   {

      operator =(*this + rangeSuffix);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_ends_ci(RANGE rangeSuffix)
{

   if (!case_insensitive_ends(rangeSuffix))
   {

      operator =(*this + rangeSuffix);

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
//inline bool string_base < ITERATOR_TYPE > ::begins(RANGE rangePrefix) const
//{
//
//   auto psz = this->begin();
//
//   auto pszPrefix = rangePrefix.begin();
//
//   auto pszPrefixEnd = rangePrefix.end();
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
//inline bool string_base < ITERATOR_TYPE > ::ends(RANGE rangeSuffix) const
//{
//
//   return string_ends(this->begin(), size(), rangeSuffix, rangeSuffix.size());
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins(RANGE rangePrefix) const
//{
//
//   auto psz = this->begin();
//
//   auto pszPrefix = rangePrefix.begin();
//
//   auto pszPrefixEnd = rangePrefix.end();
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
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends(RANGE rangeSuffix) const
//{
//
//   return string_ends_ci(this->begin(), size(), rangeSuffix, rangeSuffix.size());
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::begins_eat(RANGE rangePrefix)
//{
//
//   strsize lenPrefix;
//
//   if (!_string_begins(this->begin(), size(), rangePrefix, lenPrefix))
//   {
//
//      return false;
//
//   }
//
//   assign(this->begin() + lenPrefix, size() - lenPrefix);
//
//   return true;
//
//}
//

//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::ends_eat(RANGE rangeSuffix)
//{
//
//   strsize lenSuffix;
//
//   if (!_string_ends(this->begin(), size(), rangeSuffix, lenSuffix))
//   {
//
//      return false;
//
//   }
//
//   truncate(size() - lenSuffix);
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins_eat(RANGE rangePrefix)
//{
//
//   strsize lenPrefix;
//
//   if (!_string_begins_ci(this->begin(), size(), rangePrefix, lenPrefix))
//   {
//
//      return false;
//
//   }
//
//   assign(this->begin() + lenPrefix, size() - lenPrefix);
//
//   return true;
//
//}


//template < typename ITERATOR_TYPE >
//inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends_eat(RANGE rangeSuffix)
//{
//
//   strsize lenSuffix;
//
//   if (!_string_ends_ci(this->begin(), size(), rangeSuffix, lenSuffix))
//   {
//
//      return false;
//
//   }
//
//   truncate(size() - lenSuffix);
//
//   return true;
//
//}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::begins_eat(string_base & strRest, RANGE rangePrefix) const
{

   strsize lenPrefix;

   if (!_string_begins(this->begin(), size(), rangePrefix, lenPrefix))
   {

      return false;

   }

   strRest.assign(this->begin() + lenPrefix, size() - lenPrefix);

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::ends_eat(string_base & strRest, RANGE rangeSuffix) const
{

   strsize lenSuffix;

   if (!_string_ends(this->begin(), size(), rangeSuffix, lenSuffix))
   {

      return false;

   }

   strRest.assign(this->begin(), size() - lenSuffix);

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_begins_eat(string_base & strRest, RANGE rangePrefix) const
{

   if (!string_begins_ci<const CHARACTER>(*this, rangePrefix))
   {

      return false;

   }

   strRest.assign(this->begin() + rangePrefix.size(), size() - rangePrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::case_insensitive_ends_eat(string_base & strRest, RANGE rangeSuffix) const
{

   if (!string_ends_ci<const CHARACTER>(*this, rangeSuffix))
   {

      return false;

   }

   strRest.assign(this->begin(), size() - rangeSuffix.size());

   return true;

}



template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::begins_eaten_ci(string_base & strEaten, RANGE rangePrefix) const
{

   if (!string_begins_ci<const CHARACTER>(*this, rangePrefix))
   {

      return false;

   }

   strEaten.assign(this->begin(), rangePrefix.size());

   return true;

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE > ::ends_eaten_ci(string_base & strEaten, RANGE rangeSuffix) const
{

   if (!_string_ends_ci<const CHARACTER>(*this, rangeSuffix))
   {

      return false;

   }

   strEaten.assign(this->begin() + length() - rangeSuffix.size(), rangeSuffix.size());

   return true;

}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_begins(RANGE rangePrefix)
//{
//
//   if (!begins(rangePrefix))
//   {
//
//      operator =(string_base(rangePrefix) + *this);
//
//   }
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_begins_ci(RANGE range)
//{
//
//   if (!case_insensitive_begins(psz))
//   {
//
//      operator =(string_base(psz) + *this);
//
//   }
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_ends(RANGE rangeSuffix)
//{
//
//   if (!ends(rangeSuffix))
//   {
//
//      operator =(*this + rangeSuffix);
//
//   }
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::ensure_ends_ci(RANGE rangeSuffix)
//{
//
//   if (!case_insensitive_ends(rangeSuffix))
//   {
//
//      operator =(*this + rangeSuffix);
//
//   }
//
//   return *this;
//
//}













template < primitive_character CHARACTER >
void CopyCharsOverlapped(CHARACTER * pchDest, const CHARACTER * pchSrc, strsize nChars) noexcept
{

   __memmov(pchDest, pchSrc, nChars * sizeof(CHARACTER));

}


template < primitive_character CHARACTER >
void CopyCharsOverlapped(CHARACTER * pchDest, size_t nDestLen, const CHARACTER * pchSrc, strsize nChars) noexcept
{

   __memmov(pchDest, pchSrc, nChars * sizeof(CHARACTER));

}



template < typename STRING >
inline STRING & string_concatenate(STRING & str, const typename STRING::CHARACTER * psz1, strsize nLength1, const typename STRING::CHARACTER * psz2, strsize nLength2)
{

   strsize nNewLength = nLength1 + nLength2;

   typename STRING::CHARACTER * pszBuffer = str.get_string_buffer(nNewLength);

   copy_chars(pszBuffer, psz1, nLength1);

   copy_chars(pszBuffer + nLength1, psz2, nLength2);

   str.release_string_buffer(nNewLength);

   return str;

}


template < typename STRING >
inline bool string_ends_eat(STRING & ansistr, const STRING & strSuffix)
{

   auto lenSuffix = strSuffix.length();

   if (lenSuffix > ansistr.length())
   {

      return false;

   }

   if (STRING::string_count_compare(ansistr.reverse_ptr_at(lenSuffix), strSuffix, lenSuffix) != 0)
   {

      return false;

   }

   ansistr.reverse_truncate(lenSuffix);

   return true;

}

//
//
//
//inline ::string operator+(const char * psz, const ::string & str);
//template < primitive_atom ATOM >
//inline ::string operator+(const char * psz, const ATOM & atom);
////{
////   return ::string(psz) + atom.string();
////
////}
//template < primitive_payload PAYLOAD >
//inline ::string operator+(const char * psz, const PAYLOAD & payload);
////{
////   return ::string(psz) + payload.get_string();
////}
////inline ::string operator+(const char * psz, const ::property & property);
//




template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE >::equals(RANGE range) const noexcept
{

   return ::string_range < const CHARACTER * >(*this).equals(range, ::comparison::comparison < CHARACTER >());

}


template < typename ITERATOR_TYPE >
inline bool string_base < ITERATOR_TYPE >::case_insensitive_equals(RANGE range) const noexcept
{

   return ::string_range < const CHARACTER * >(*this).equals(range, ::comparison::case_insensitive< CHARACTER >());

}


//// find the first occurrence of character 'ch', starting at strsize 'start'
//inline strsize string::find(::ansi_character ch) const RELEASENOTHROW
//{
//
//   const ::ansi_character * psz = strchr(m_psz, ch);
//
//   return psz == nullptr ? -1 : psz - m_psz;
//
//}
//

//// find the first occurrence of character 'ch', starting at strsize 'start'
//inline strsize string::find(::ansi_character ch, strsize start) const RELEASENOTHROW
//{
//
//   const ::ansi_character * psz = strchr(&m_psz[start], ch);
//
//   return psz == nullptr ? -1 : psz - m_psz;
//
//}


int get_mem_free_available_kb();


template < primitive_character CHARACTER >
inline void string_meta_data < CHARACTER > ::set_length(::strsize strsize)
{

   if (this->natural_is_shared())
   {

      throw_exception(error_wrong_state, "invalid state");

   }

   auto strsizeStorage = this->memsize_in_chars();

   if (strsize >= strsizeStorage)
   {

      throw_exception(error_bad_argument);

   }

   this->m_datasize = strsize;

   this->begin()[strsize] = (CHARACTER)0;

   this->begin()[strsizeStorage - 1] = (CHARACTER)0;

}



template < primitive_character CHARACTER >
inline void string_meta_data < CHARACTER > ::set_data_length(::strsize strsize)
{

   if (this->natural_is_shared())
   {

      throw_exception(error_wrong_state, "invalid state");

   }

   auto strsizeStorage = this->memsize_in_chars();

   if (strsize >= strsizeStorage)
   {

      throw_exception(error_bad_argument);

   }

   this->m_datasize = strsize;

}



template < primitive_character CHARACTER >
inline ::strsize string_meta_data < CHARACTER>::memsize_in_chars() const
{

   return (::strsize)byte_length_to_char_length(&this->begin()[0], (::strsize)this->m_memsize);

}


template < primitive_character CHARACTER >
inline ::memsize string_meta_data < CHARACTER>::length_in_bytes() const
{

   return char_length_to_byte_length(&this->begin()[0], this->m_datasize);

}



template < primitive_character CHARACTER >
::wd32_character unicode_iterator < CHARACTER > ::operator *() { return unicode_index(m_psz); }


template < primitive_character CHARACTER >
unicode_iterator < CHARACTER > & unicode_iterator < CHARACTER > ::operator ++()
{

   unicode_increment(m_psz);

   return *this;

}


template < primitive_character CHARACTER >
unicode_iterator < CHARACTER > unicode_iterator < CHARACTER > ::operator ++(int)
{

   auto psz = m_psz;

   unicode_increment(m_psz);

   return psz;

}



