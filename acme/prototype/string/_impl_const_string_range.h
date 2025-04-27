// Created by camilo on 2025-04-24 18:57 <3ThomasBorregaardSorensen!!
#pragma once




template < primitive_character CHARACTER >
::string_base < const CHARACTER* > operator + (
   const ::range < const CHARACTER* >& range1,
   const ::range < const CHARACTER* >& range2)
{

   return { range1, range2 };

}



template < primitive_character CHARACTER, character_count n >
::string_base < const CHARACTER* > operator + (
   const ::range < const CHARACTER* >& range1,
   const CHARACTER(&s)[n])
{

   return { range1, ::as_string_literal <CHARACTER,n>(s) };

}


template < typename ITERATOR_TYPE >
const_string_range < ITERATOR_TYPE >::THIS_RANGE const_string_range < ITERATOR_TYPE >::right(character_count count) const
{

   if (count < 0)
   {

      count = 0;

   }

   character_count nLength = this->size();

   if (count >= nLength)
   {

      return *this;

   }

   return _begin_set(this->begin() + nLength - count);

}


// Return the substring consisting of the leftmost 'count' characters
template < typename ITERATOR_TYPE >
const_string_range < ITERATOR_TYPE > const_string_range < ITERATOR_TYPE >::left(character_count count) const
{

   // count is in XCHARs
   if (count < 0)
   {

      count = 0;

   }

   character_count nLength = this->size();

   if (count >= nLength)
   {

      return *this;

   }

   return _end_set(this->begin() + count);

}


// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
template < typename ITERATOR_TYPE >
const_string_range < ITERATOR_TYPE > const_string_range < ITERATOR_TYPE >::left_including_any_character_in(const SCOPED_STRING& scopedstrCharacters) const
{

   auto pbegin = this->skip_any_character_in(scopedstrCharacters);

   return _begin_set(pbegin);

}


// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
template < typename ITERATOR_TYPE >
const_string_range < ITERATOR_TYPE > const_string_range < ITERATOR_TYPE >::left_skipping_any_character_in(const SCOPED_STRING& scopedstrCharacters) const
{

   auto pbegin = this->skip_any_character_in(scopedstrCharacters);

   return _begin_set(pbegin);

}


//template < typename ITERATOR_TYPE >
//typename ::const_string_range < ITERATOR_TYPE >::THIS_RANGE const_string_range < ITERATOR_TYPE > ::consume_token_until_any_character_in(const SCOPED_STRING& scopedstrCharacters, bool bReturnSeparator, bool bSkipAnyCharactersIn) const
//{
//
//   auto p1 = this->find_first_character_in(scopedstrCharacters);
//
//   if (!p1)
//   {
//
//      return *this;
//      //auto range = (*this)();
//
//      //if (this->m_begin != this->m_end)
//      //{
//
//      //   this->m_begin = this->m_end;
//
//      //   this->m_erange = ;
//
//      //}
//
//      //return { this->m_end, this->m_end, (enum_range)(this->m_erange & ~e_range_string) };
//
//   }
//
//   if (bSkipAnyCharactersIn)
//   {
//
//      auto p2 = (*this)(p1).skip_any_character_in(scopedstrCharacters);
//
//      if (bReturnSeparator)
//      {
//
//         auto range = const_string_range < ITERATOR_TYPE >(this->m_begin, p2);
//
//         this->set_begin(p2);
//
//         return range;
//
//      }
//
//      auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1);
//
//      this->set_begin(p2);
//
//      return range;
//
//   }
//
//   if (bReturnSeparator)
//   {
//
//      auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1 + 1);
//
//      this->set_begin(p1 + 1);
//
//      return range;
//
//   }
//
//   auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1);
//
//   this->set_begin(p1 + 1);
//
//   return range;
//
//}


template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::xml_is_comment() const
{

   return this->size() > 3 && this->m_begin[0] == '<' && this->m_begin[1] == '!' && this->m_begin[2] == '-';

}



//========================================================
// Name   : _tcsenicmp
// Desc   : similar with case_insensitive_ansi_count_compare with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
template < typename ITERATOR_TYPE >
::std::strong_ordering const_string_range < ITERATOR_TYPE >::escape_case_insensitive_count_order(const ::scoped_string& scopedstr, int escape) const
{

   auto rangeCompare = scopedstr();

   ::std::strong_ordering order = ::std::strong_ordering::equal;

   const CHARACTER* prev_escape = nullptr;

   auto r = (*this)();

   while (r.has_character() && *r.m_begin && rangeCompare.has_character())
   {

      if (escape != 0 && *r.m_begin == escape && prev_escape == nullptr)
      {

         prev_escape = r.m_begin;

      }
      else
      {

         prev_escape = nullptr;

         order = unicode_to_lower_case(unicode_index(r.m_begin)) <=> unicode_to_lower_case(unicode_index(rangeCompare.m_begin));

         if (order != 0)
         {

            break;

         }

         rangeCompare.m_begin++;

      }

      r.m_begin++;

   }

   return order;

}


template < typename ITERATOR_TYPE >
typename const_string_range < ITERATOR_TYPE >::THIS_RANGE const_string_range < ITERATOR_TYPE >::get_utf8_char() const
{

   auto pszStart = this->m_begin;

   auto pszNext = unicode_next(pszStart);

   return { pszStart, minimum(pszNext, this->m_end) };

}





