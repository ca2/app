// From _string_base_impl.h by camilo on 2012-12-18 17:04 <3ThomasBorregaardSorensen!!
#pragma once



//template < typename ITERATOR_TYPE >
//constexpr ::std::strong_ordering const_string_range < ITERATOR_TYPE > ::order(const SCOPED_STRING & range) const noexcept
//{
//
//   return this->order(range, ::comparison::comparison < CHARACTER >());
//
//}
//

//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering const_string_range < ITERATOR_TYPE > ::case_insensitive_order(const SCOPED_STRING & range) const noexcept
//{
//
//   return this->order(range, ::comparison::case_insensitive < CHARACTER >());
//
//}
//

template < typename ITERATOR_TYPE >
inline ::std::strong_ordering const_string_range < ITERATOR_TYPE > ::collate(const SCOPED_STRING & range) const noexcept
{

   return range_collate<const CHARACTER *>(*this, range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering const_string_range < ITERATOR_TYPE > ::case_insensitive_collate(const SCOPED_STRING & range) const noexcept
{

   return case_insensitive_range_collate<const CHARACTER *>(*this, range);

}


//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::order(const SCOPED_STRING & range, character_count countRange) const noexcept
//{
//
//   return this->order(range.start_count(0, countRange));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_order(const SCOPED_STRING & range, character_count countRange) const noexcept
//{
//
//   return this->case_insensitive_order(range.start_count(0, countRange));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::collate(const SCOPED_STRING & range, character_count countRange) const noexcept
//{
//
//   return this->collate(range.start_count(0, countRange));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_collate(const SCOPED_STRING & range, character_count countRange) const noexcept
//{
//
//   return this->case_insensitive_collate(range.start_count(0, countRange));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::order(character_count start, character_count count, const SCOPED_STRING & range) const noexcept
//{
//
//   return this->start_count(start, count).order(range);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_order(character_count start, character_count count, const SCOPED_STRING & range) const noexcept
//{
//
//   return this->start_count(start, count).case_insensitive_order(range);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::collate(character_count start, character_count count, const SCOPED_STRING & range) const noexcept
//{
//
//   return this->start_count(start, count).collate(range);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_collate(character_count start, character_count count, const SCOPED_STRING & range) const noexcept
//{
//
//   return this->start_count(start, count).case_insensitive_collate(range);
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::order(character_count start, character_count count, const SCOPED_STRING & range, character_count startRange, character_count countRange) const noexcept
//{
//
//   return this->start_count(start, count).order(range.start_count(startRange, countRange));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_order(character_count start, character_count count, const SCOPED_STRING & range, character_count startRange, character_count countRange) const noexcept
//{
//
//   return this->start_count(start, count).case_insensitive_order(range.start_count(startRange, countRange));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::collate(character_count start, character_count count, const SCOPED_STRING & range, character_count startRange, character_count countRange) const noexcept
//{
//
//   return this->start_count(start, count).collate(range.start_count(startRange, countRange));
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_collate(character_count start, character_count count, const SCOPED_STRING & range, character_count startRange, character_count countRange) const noexcept
//{
//
//   return this->start_count(start, count).case_insensitive_collate(range.start_count(startRange, countRange));
//
//}






template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE > ::is_trimmed_empty() const
{

   auto p = this->m_begin;

   if (::is_null(p))
   {

      return true;

   }

   auto end = this->m_end;

   while (p < end)
   {

      if (!unicode_is_whitespace(p))
      {

         return false;

      }

      p = unicode_next(p);

   }

   return true;

}



template < typename ITERATOR_TYPE >
string_range < ITERATOR_TYPE > string_range < ITERATOR_TYPE > ::consume_token_until_any_character_in(const SCOPED_STRING& scopedstrCharacters, bool bReturnSeparator, bool bSkipAnyCharactersIn)
{

   auto p1 = this->find_first_character_in(scopedstrCharacters);

   if (!p1)
   {

      auto range = (*this)();

      if (this->m_begin != this->m_end)
      {

         this->m_begin = this->m_end;

         //this->m_erange = e_range_none;

         //this->m_erange = (enum_range)(this->m_erange & ~e_range_string);

      }

      return range;

   }

   if (bSkipAnyCharactersIn)
   {

      auto p2 = (*this)(p1).skip_any_character_in(scopedstrCharacters);

      if (bReturnSeparator)
      {

         auto range = string_range < ITERATOR_TYPE >(this->m_begin, p2);

         this->set_begin(p2);

         return range;

      }

      auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1);

      this->set_begin(p2);

      return range;

   }

   if (bReturnSeparator)
   {

      auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1 + 1);

      this->set_begin(p1 + 1);

      return range;

   }

   auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1);

   this->set_begin(p1 + 1);

   return range;

}
