// From _string_base_impl.h by camilo on 2012-12-18 17:04 <3ThomasBorregaardSorensen!!
#pragma once



template < typename ITERATOR_TYPE >
constexpr ::std::strong_ordering string_range < ITERATOR_TYPE > ::order(const SCOPED_STRING & range) const noexcept
{

   return this->order(range, ::comparison::comparison < CHARACTER >());

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_order(const SCOPED_STRING & range) const noexcept
{

   return this->order(range, ::comparison::case_insensitive < CHARACTER >());

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::collate(const SCOPED_STRING & range) const noexcept
{

   return range_collate<const CHARACTER *>(*this, range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_collate(const SCOPED_STRING & range) const noexcept
{

   return case_insensitive_range_collate<const CHARACTER *>(*this, range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::order(const SCOPED_STRING & range, strsize countRange) const noexcept
{

   return this->order(range.start_count(0, countRange));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_order(const SCOPED_STRING & range, strsize countRange) const noexcept
{

   return this->case_insensitive_order(range.start_count(0, countRange));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::collate(const SCOPED_STRING & range, strsize countRange) const noexcept
{

   return this->collate(range.start_count(0, countRange));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_collate(const SCOPED_STRING & range, strsize countRange) const noexcept
{

   return this->case_insensitive_collate(range.start_count(0, countRange));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::order(strsize start, strsize count, const SCOPED_STRING & range) const noexcept
{

   return this->start_count(start, count).order(range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_order(strsize start, strsize count, const SCOPED_STRING & range) const noexcept
{

   return this->start_count(start, count).case_insensitive_order(range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::collate(strsize start, strsize count, const SCOPED_STRING & range) const noexcept
{

   return this->start_count(start, count).collate(range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_collate(strsize start, strsize count, const SCOPED_STRING & range) const noexcept
{

   return this->start_count(start, count).case_insensitive_collate(range);

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::order(strsize start, strsize count, const SCOPED_STRING & range, strsize startRange, strsize countRange) const noexcept
{

   return this->start_count(start, count).order(range.start_count(startRange, countRange));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_order(strsize start, strsize count, const SCOPED_STRING & range, strsize startRange, strsize countRange) const noexcept
{

   return this->start_count(start, count).case_insensitive_order(range.start_count(startRange, countRange));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::collate(strsize start, strsize count, const SCOPED_STRING & range, strsize startRange, strsize countRange) const noexcept
{

   return this->start_count(start, count).collate(range.start_count(startRange, countRange));

}


template < typename ITERATOR_TYPE >
inline ::std::strong_ordering string_range < ITERATOR_TYPE > ::case_insensitive_collate(strsize start, strsize count, const SCOPED_STRING & range, strsize startRange, strsize countRange) const noexcept
{

   return this->start_count(start, count).case_insensitive_collate(range.start_count(startRange, countRange));

}




