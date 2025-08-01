// Created by camilo on 2025-04-17 09:37 <3ThomasBorregaardSorensen!!
#pragma once



#include "acme/prototype/string/string_base.h"
#include "acme/prototype/string/string_base.h"


//template < typename T >
//concept character_range_not_string = character_range<T> && !primitive_string<T>;
//
//
//template < typename T >
//concept character_range_not_string_neither_scoped_string = character_range<T> && !primitive_string<T> && !primitive_scoped_string<T>;


//template < primitive_character CHARACTER, character_count n, typed_character_range < CHARACTER > TYPED_CHARACTER_RANGE >
//const_string_range_static_array < const CHARACTER*, 2 > operator + (const CHARACTER(&s)[n], const TYPED_CHARACTER_RANGE& range)
//{
//
//   //return { ::as_string_literal< CHARACTER, n>(s), range };
//    return { s, range };
//
//}






template < character_range RANGE, typed_character_range < typename RANGE::CHARACTER > TYPED_RANGE >
::string_base < typename RANGE::const_iterator > operator + (const RANGE& range, const TYPED_RANGE& typedrange)
{

   return { range, typedrange };

}


template < character_range RANGE, has_as_string HAS_AS_STRING >
::string_base < typename RANGE::const_iterator > operator + (const RANGE& range, const HAS_AS_STRING& has_as_string)
{

   return ::transfer(::string_base < typename RANGE::const_iterator >(range) + has_as_string.as_string());

}



//template < character_count n >
//const_string_range_static_array < const_char_pointer , 2 > operator + (const ::range < const_char_pointer  > & range, const ansi_string_literal<n> & literal)
//{
//
//   //return { range, ::as_string_literal<typename RANGE::CHARACTER, n>(s) };
//    return { range, literal };
//
//}






//template < character_range RANGE, int t_size >
//const_string_range_static_array < typename RANGE::const_iterator, t_size + 1 > operator + (const const_string_range_static_array < typename RANGE::const_iterator, t_size >& a, const RANGE& range)
//{
//
//   return { a, range };
//
//}

template < character_range RANGE, primitive_character CHARACTER >
::string_base < typename RANGE::const_iterator > operator + (const RANGE& range, const typename RANGE::CHARACTER ch)
{

   return { range, {&ch, &ch + 1, e_range_none} };

}


template < character_range RANGE >
inline ::string_base < const typename RANGE::CHARACTER * > operator +(const typename RANGE::CHARACTER & ch, const RANGE & range)
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
inline string_base<ITERATOR_TYPE> const_string_range<ITERATOR_TYPE>::surrounded(const SCOPED_STRING& strLeft, const SCOPED_STRING& strRight) const
{

   return strLeft + *this + strRight;

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



