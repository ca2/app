// Created by camilo on 2025-04-21 19:55 <3ThomasBorregaardSørensen!!
#pragma once


//template < typename ITERATOR_TYPE >
//inline void string_base < ITERATOR_TYPE >::construct_from_string(const ITERATOR_TYPE p, character_count length)
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
//   fork_string<false, false>(length);
//
//   memory_copy((void*)this->m_begin, p, length * sizeof(CHARACTER));
//
//   *(CHARACTER*)this->m_end = (CHARACTER)0;
//
//}


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

   auto p = this->construct_string(len);

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
template < primitive_character CHARACTER2 >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE > ::assign(const CHARACTER2 * start, const CHARACTER2 * end)
{

   return assign(start, end - start);

}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline ::string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(const CHARACTER2 * start, character_count len)
{

   _assign(start, len);

   return *this;

}


template < typename ITERATOR_TYPE >
template < primitive_character SAME_SIZE_CHARACTER >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::_assign(const SAME_SIZE_CHARACTER * pszSource, character_count len)
requires (sizeof(SAME_SIZE_CHARACTER) == sizeof(CHARACTER))
{

   // auto dstlen = utf_to_utf_length(this->begin(), pszSource, len);
   //
   // if (dstlen <= 0)
   // {
   //
   //    this->empty();
   //
   // }
   // else
   // {
   //
   //    auto pszTarget = this->get_buffer(dstlen);
   //
   //    utf_to_utf(pszTarget, pszSource, len);
   //
   //    this->release_buffer(dstlen);
   //
   // }
   //
   // return *this;

   // if ((::range<const CHARACTER *> *)(this) == (::range<const CHARACTER *> *)(&range))
   // {
   //
   //    return *this;
   //
   // }

   typename BASE_DATA::base_data * pdataThis;

   if(this->m_erange & e_range_string)
   {

      pdataThis = BASE_DATA::base_data_from_data(this->m_begin);

   }
   else
   {

      pdataThis = nullptr;

   }

   if (::is_null(pszSource) || len <= 0)
   {

      this->default_construct();

   }
   else
   {
      auto lengthNew = len;

      if (((ITERATOR_TYPE) pszSource == this->m_begin)
         ||
         (
            ::is_set(pdataThis) &&
            !pdataThis->base_data_is_shared() &&
            lengthNew <= pdataThis->storage_character_count()
         )
         )
      {

         pdataThis = nullptr;

      }
      else
      {

         this->m_begin = create_string_data(len);

      }

      ::memory_transfer((void*) this->m_begin, pszSource, lengthNew);

      this->m_end = this->m_begin + lengthNew;

      this->m_erange = e_range_string;

      *((CHARACTER*)this->m_end) = CHARACTER{};

   }

   if (pdataThis)
   {

      this->base_data_release(pdataThis);

   }

   return *this;

}



template < typename ITERATOR_TYPE >
template < primitive_character OTHER_SIZE_CHARACTER >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::_assign(const OTHER_SIZE_CHARACTER * pszSource, character_count len)
requires (sizeof(OTHER_SIZE_CHARACTER) != sizeof(CHARACTER))
{

   ASSERT((void * )(pszSource + len) < (void*)this->m_begin
      || (void * )pszSource > (void*)(this->m_end))

   // auto dstlen = utf_to_utf_length(this->begin(), pszSource, len);
   //
   // if (dstlen <= 0)
   // {
   //
   //    this->empty();
   //
   // }
   // else
   // {
   //
   //    auto pszTarget = this->get_buffer(dstlen);
   //
   //    utf_to_utf(pszTarget, pszSource, len);
   //
   //    this->release_buffer(dstlen);
   //
   // }
   //
   // return *this;

   // if ((::range<const CHARACTER *> *)(this) == (::range<const CHARACTER *> *)(&range))
   // {
   //
   //    return *this;
   //
   // }

   typename BASE_DATA::base_data * pdataThis;

   if(this->m_erange & e_range_string)
   {

      pdataThis = BASE_DATA::base_data_from_data(this->m_begin);

   }
   else
   {

      pdataThis = nullptr;

   }

   if (::is_null(pszSource) || len <= 0)
   {

      this->default_construct();

   }
   else
   {

      auto lengthNew = utf_to_utf_length(this->begin(), pszSource, len);

      if ((::is_null(pdataThis) &&
         !pdataThis->base_data_is_shared() &&
         lengthNew <= pdataThis->storage_character_count()))
      {

         pdataThis = nullptr;

      }
      else
      {

         this->m_begin = create_string_data(len);

      }

      utf_to_utf((CHARACTER*)  this->m_begin, pszSource, lengthNew);

      this->m_end = this->m_begin + lengthNew;

      this->m_erange = e_range_string;

      *((CHARACTER*)this->m_end) = CHARACTER{};

   }

   if (pdataThis)
   {

      this->base_data_release(pdataThis);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER2 >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::assign(CHARACTER2 chSrc, character_count repeat)
{

   if (repeat > 0)
   {

      auto lenUnit = utf_to_utf_length(this->begin(), &chSrc, 1);

      auto len = lenUnit * repeat;

      auto psz = get_buffer(len);

      CHARACTER sz[8];

      utf_to_utf(sz, &chSrc, 1);

      auto pTarget = psz;

      while (repeat > 0)
      {

         auto pSource = sz;

         for (::collection::index j = 0; j < lenUnit; j++)
         {

            *pTarget++ = *pSource;

         }

         repeat--;

      }

      release_buffer(len);

   }
   else
   {

      this->empty();

   }

   return *this;

}




template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::_append(const CHARACTER * pszSrc, character_count count)
{

   auto old_len = this->length();

   if (old_len < 0)
   {

      old_len = 0;

   }

   auto add_len = utf_to_utf_length(this->m_begin, pszSrc, count);

   auto new_len = old_len + add_len;

   auto p = get_buffer<true>(new_len);

   utf_to_utf(p + old_len, pszSrc, count);

   //release_buffer(nNewLength);

   p[new_len] = CHARACTER{};

   return *this;

}


template < typename ITERATOR_TYPE >
template < typename OTHER_CHARACTER >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::_append(const OTHER_CHARACTER * pszSrc, character_count count)
requires other_primitive_character < OTHER_CHARACTER, CHARACTER >
{

   auto old_len = this->length();

   if (old_len < 0)
   {

      old_len = 0;

   }

   auto add_len = utf_to_utf_length(this->m_begin, pszSrc, count);

   auto new_len = old_len + add_len;

   auto p = get_buffer<true>(new_len);

   p += old_len;

   utf_to_utf(p, pszSrc, count);

   ASSERT(p <= this->m_end);

   p[new_len] = CHARACTER{};

   return *this;

}



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
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(character_count len, CHARACTER ch)
{

   if (len > 0)
   {

      character_count nOldLength = this->size();

      character_count nNewLength = nOldLength + len;

      auto p = this->get_buffer<true>(nNewLength);

      auto padd = p + len - 1;

      while (padd >= p)
      {

         *padd = ch;

         padd--;

      }

      this->release_buffer(nNewLength);

   }

   return *this;

}


template < typename ITERATOR_TYPE >
void string_base< ITERATOR_TYPE >::construct_from_string(const string_base& str)
{

   this->m_begin = str.m_begin;
   this->m_end = str.m_end;
   this->m_erange = str.m_erange;

   if (this->m_erange & e_range_string)
   {

      auto pbasedata = this->base_data_from_data(this->m_begin);

      pbasedata->base_data_increment_reference_count();

   }

}


template < typename ITERATOR_TYPE >
inline void string_base< ITERATOR_TYPE >::construct_from_range(ITERATOR_TYPE pSrc, character_count len)
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
inline void string_base< ITERATOR_TYPE >::construct_from_range(OTHER_CHARACTER_POINTER pSrc, character_count src_len)
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
void string_base< ITERATOR_TYPE >::construct_from_two_ranges_concatenation(const RANGE1& range1, const RANGE2& range2)
{

   if (range1.is_empty())
   {

      if (range2.is_empty())
      {

         default_construct();

      }
      else
      {
      
         construct_from_a_range(range2);
      
      }

      return;

   }
   else if (range2.is_empty())
   {

      construct_from_a_range(range1);

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


template < typename ITERATOR_TYPE >
inline ITERATOR_TYPE character_range_defer_increment_reference_count(ITERATOR_TYPE piterator, enum_range erange)
{

   if (erange & e_range_string)
   {

      string_base_increment_reference_count(piterator);

   }

   return piterator;

}


template < typename RANGE >
inline RANGE & character_range_defer_increment_reference_count(RANGE & range)
{

   character_range_defer_increment_reference_count(range.m_begin, range.m_erange);

   return range;

}


template < typename RANGE >
inline RANGE & character_range_defer_release(RANGE & range)
{

   if (range.m_erange & e_range_string)
   {

      string_base_release(range.m_begin);

   }

   return range;

}




template < typename ITERATOR_TYPE >
inline void string_base_increment_reference_count(ITERATOR_TYPE piterator)
{

   ::string_base< ITERATOR_TYPE >::string_data_increment_reference_count(piterator);

}


template < typename ITERATOR_TYPE >
inline void string_base_release(ITERATOR_TYPE piterator)
{

   ::string_base< ITERATOR_TYPE >::string_data_release(piterator);

}



