// Created by camilo on 2025-04-17 09:37 <3ThomasBorregaardSorensen!!
#pragma once



#include "acme/prototype/string/string_base.h"
#include "acme/prototype/string/scoped_string_base.h"


//template < typename T >
//concept character_range_not_string = character_range<T> && !primitive_string<T>;
//
//
//template < typename T >
//concept character_range_not_string_neither_scoped_string = character_range<T> && !primitive_string<T> && !primitive_scoped_string<T>;


template < primitive_character CHARACTER, character_count n, typed_character_range < CHARACTER > TYPED_CHARACTER_RANGE >
const_string_range_static_array < const CHARACTER*, 2 > operator + (const CHARACTER(&s)[n], const TYPED_CHARACTER_RANGE& range)
{

   return { ::as_string_literal< CHARACTER, n>(s), range };

}






template < character_range RANGE, typed_character_range < typename RANGE::CHARACTER > TYPED_RANGE >
const_string_range_static_array < typename RANGE::const_iterator, 2 > operator + (const RANGE& range, const TYPED_RANGE& typedrange)
{

   return { range, typedrange };

}



template < character_range RANGE, has_as_string HAS_AS_STRING >
::string_base < typename RANGE::const_iterator > operator + (const RANGE& range, const HAS_AS_STRING& has_as_string)
{

   return ::transfer(::string_base < typename RANGE::const_iterator >(range) + has_as_string.as_string());

}



template < character_range RANGE, character_pointer CHARACTER_POINTER >
const_string_range_static_array < typename RANGE::const_iterator, 2 > operator + (const RANGE& range, CHARACTER_POINTER psz)
{

   return { { range }, { psz, psz + string_safe_length(psz), e_range_null_terminated } };

}


template < character_range RANGE, character_count n >
const_string_range_static_array < typename RANGE::const_iterator, 2 > operator + (const RANGE& range, const typename RANGE::CHARACTER(&s)[n])
{

   return { range, ::as_string_literal<typename RANGE::CHARACTER, n>(s) };

}






template < character_range RANGE, int t_size >
const_string_range_static_array < typename RANGE::const_iterator, t_size + 1 > operator + (const const_string_range_static_array < typename RANGE::const_iterator, t_size >& a, const RANGE& range)
{

   return { a, range };

}

template < character_range RANGE, primitive_character CHARACTER >
const_string_range_static_array < typename RANGE::const_iterator, 2 > operator + (const RANGE& range, const typename RANGE::CHARACTER ch)
{

   return { range, {&ch, &ch + 1, e_range_none} };

}


template < character_range RANGE >
inline const_string_range_static_array < const typename RANGE::CHARACTER *, 2 > operator +(const typename RANGE::CHARACTER & ch, const RANGE & range)
{

   return   { 
               ::range < const typename RANGE::CHARACTER *>(
                  (const typename RANGE::CHARACTER *) & ch,
                  ((const typename RANGE::CHARACTER *) (&ch)) + 1,
                  e_range_none
               ),
               range
            };

}


template < character_range RANGE >
inline string& operator <<(string& str, const RANGE& r)
{

   str.append(r);

   return str;

}


template<typename ITERATOR_TYPE>
inline string_base<ITERATOR_TYPE> const_string_range<ITERATOR_TYPE>::surrounded(const SCOPED_STRING& scopedstrLeft, const SCOPED_STRING& scopedstrRight) const
{

   return scopedstrLeft + *this + scopedstrRight;

}


template < character_range RANGE1, character_range RANGE2 >
::file::path operator / (const RANGE1& range1, const RANGE2& range2)
{

   return ::transfer(::file::path(range1).slashed_path(range2));

}



template < character_pointer CHARACTER_POINTER, character_range RANGE >
::file::path operator / (CHARACTER_POINTER p, const RANGE& range)
{

   return ::transfer(::file::path(p) / ::string(range));

}




template < character_range RANGE, character_count n >
::file::path operator / (const typename RANGE::CHARACTER(&sz)[n], const RANGE& range)
{

   return ::transfer(::file::path(sz) / ::string(range));

}



template < primitive_character ITERATOR_TYPE2, int t_size, character_range RANGE >
::file::path operator / (const const_string_range_static_array <ITERATOR_TYPE2, t_size >& a, const RANGE& range)
{

   return ::transfer(::file::path(a) / ::string(range));

}


template < character_range RANGE, character_pointer CHARACTER_POINTER >
::file::path operator / (const RANGE& range, CHARACTER_POINTER p)
{

   return ::transfer(::file::path(range) / ::file::path(p));

}


template < character_range RANGE, typename ITERATOR_TYPE2, int t_size >
::file::path operator / (const RANGE& range, const const_string_range_static_array <ITERATOR_TYPE2, t_size >& a)
{

   return ::transfer(::file::path(range) / ::file::path(a));

}




template < primitive_payload PAYLOAD, character_range RANGE >
::string operator + (const PAYLOAD& payload, const RANGE& range)
{

   return ::transfer(::string(payload) + ::string(range));

}


template < primitive_payload PAYLOAD, character_range RANGE >
PAYLOAD& operator += (PAYLOAD& payload, const RANGE& range)
{

   string str = payload.as_string() + ::string(range);

   payload = str;

   return payload;

}




template < character_range RANGE >
atom::atom(const RANGE& range) :
   m_str(range)
{

   m_etype = e_type_text;

}



