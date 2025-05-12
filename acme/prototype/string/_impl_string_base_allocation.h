// Created by camilo on 2025-04-21 19:55 <3ThomasBorregaardSørensen!!
#pragma once


template < typename ITERATOR_TYPE >
inline void string_base < ITERATOR_TYPE >::construct1(const ITERATOR_TYPE p, character_count length)
{

   if (::is_null(p) || length <= 0)
   {

      default_construct();

      return;

   }

   fork_string<false, false>(length);

   memory_copy((void*)this->m_begin, p, length * sizeof(CHARACTER));

   *(CHARACTER*)this->m_end = (CHARACTER)0;

}


//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
//inline void string_base < ITERATOR_TYPE >::construct5(const OTHER_CHARACTER* p, character_count len)
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
//   utf_to_utf((CHARACTER*)this->m_begin, p, len);
//
//   *(CHARACTER*)this->m_end = (CHARACTER)0;
//
//}


template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename ::string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
template < typename OTHER_CHARACTER >
inline void string_base < ITERATOR_TYPE >::construct20(const ::range < const OTHER_CHARACTER* >& range)
requires other_primitive_character < OTHER_CHARACTER, CHARACTER >
{

   auto len = utf_to_utf_length(this->m_begin, range.m_begin, range.size());

   auto p = construct_string(len);

   auto plen = &len;

   range.__utf_concatenate_to(p, plen);

   *p = {};

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >::string_base(CHARACTER chSrc, character_count repeat) :
   ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
{

   if (repeat <= 0)
   {

      default_construct();

      return;

   }

   auto len = repeat;

   auto p = construct_string(len);

   while (repeat > 0)
   {

      *p++ = chSrc;

      repeat--;

   }

   *p = CHARACTER{};

}


template < typename ITERATOR_TYPE >
template < typename OTHER_CHARACTER >
inline string_base < ITERATOR_TYPE >::string_base(OTHER_CHARACTER chSrc, character_count repeat)
requires other_primitive_character < OTHER_CHARACTER, CHARACTER > :
::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
{

   if (repeat <= 0)
   {

      default_construct();

      return;

   }

   auto lenUnit = utf_to_utf_length(this->begin(), &chSrc, 1);

   auto len = lenUnit * repeat;

   auto p = construct_string(len);

   CHARACTER sz[8];

   utf_to_utf(sz, &chSrc, 1);

   //auto pTarget = (CHARACTER*)this->m_begin;

   while (repeat > 0)
   {

      auto pSource = sz;

      auto j = lenUnit;

      while(j > 0)
      {

         *p++ = *pSource++;

         j--;

      }

      repeat--;

   }

   *(CHARACTER*)this->m_end = CHARACTER {};

}





//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER, int t_size >
//inline string_base < ITERATOR_TYPE >::string_base(const const_string_range_static_array < const OTHER_CHARACTER*, t_size >& a) :
//   ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
//{
//
//   character_count iaLen[t_size];
//
//   character_count* plen = iaLen;
//
//   auto len = a.__utf_length(this->begin(), plen);
//
//   auto p = construct_string(len);
//
//   plen = iaLen;
//
//   a.__utf_concatenate_to(p, plen);
//
//   *p = {};
//
//}


template < typename ITERATOR_TYPE >
void string_base< ITERATOR_TYPE >::construct1(const string_base& str)
{

   this->m_begin = str.m_begin;
   this->m_end = str.m_end;
   this->m_erange = (str.m_erange & ~e_range_scoped_ownership);

   if (this->m_erange & e_range_string)
   {

      auto pbasedata = this->base_data_from_data(this->m_begin);

      pbasedata->base_data_increment_reference_count();

   }

}


template < typename ITERATOR_TYPE >
inline void string_base< ITERATOR_TYPE >::construct5(ITERATOR_TYPE pSrc, character_count len)
{

   if (::is_null(pSrc) || len <= 0)
   {

      default_construct();

      return;

   }

   auto p = construct_string(len);

   string_count_copy(p, pSrc, len);

   p[len] = CHARACTER{};

}




template < typename ITERATOR_TYPE >
template < typename OTHER_CHARACTER_POINTER >
inline void string_base< ITERATOR_TYPE >::construct5(OTHER_CHARACTER_POINTER pSrc, character_count src_len)
requires other_character_pointer < OTHER_CHARACTER_POINTER, ITERATOR_TYPE >
{

   if (::is_null(pSrc) || src_len <= 0)
   {

      default_construct();

      return;

   }

   auto dst_len = utf_to_utf_length(this->begin(), pSrc, src_len);

   auto p = construct_string(dst_len);

   utf_to_utf(p, pSrc, src_len);

   p[dst_len] = CHARACTER{};

}


template < typename ITERATOR_TYPE >
template < character_pointer CHARACTER_POINTER >
string_base< ITERATOR_TYPE >::string_base(CHARACTER_POINTER s1, CHARACTER_POINTER e1, CHARACTER_POINTER s2, CHARACTER_POINTER e2) : 
   string_base(::range < ITERATOR_TYPE >(s1, e1) + ::range < ITERATOR_TYPE >(s2, e2)) 
{


}


template < typename ITERATOR_TYPE >
template < typename RANGE1, typename RANGE2 >
void string_base< ITERATOR_TYPE >::construct40(const RANGE1& range1, const RANGE2& range2)
{

   if (range1.is_empty())
   {

      if (range2.is_empty())
      {

         default_construct();

      }
      else
      {
      
         construct10(range2);
      
      }

      return;

   }
   else if (range2.is_empty())
   {

      construct10(range1);

      return;

   }

   auto len1 = range1.size();

   auto len2 = range2.size();

   auto len = len1 + len2;

   auto p = construct_string(len);

   string_count_copy(p, range1.m_begin, len1);

   string_count_copy(p + len1, range2.m_begin, len2);

   p[len] = CHARACTER{};

}



