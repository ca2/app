// Created by camilo on 2022-12-07 23:59 <3ThomasBorregaardSorensen!!
#pragma once


#include "const_string_range.h"


template < typename ITERATOR_TYPE >
class string_range :
   //public ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >
   //public ::array_range < ::range < ITERATOR_TYPE > > >
   public ::const_string_range < ITERATOR_TYPE >
{
public:


   //using BASE_RANGE = ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >;

   using BASE_RANGE = ::const_string_range < ITERATOR_TYPE >;

   using THIS_RANGE = ::string_range < ITERATOR_TYPE >;

   using STRING_RANGE = ::string_range < ITERATOR_TYPE >;

   using STRING_BASE = ::string_base < ITERATOR_TYPE >;

   using ITEM_POINTER = get_type_item_pointer<ITERATOR_TYPE>;
   using ITEM = non_const<dereference<ITEM_POINTER> >;
   using CHARACTER = ITEM;


   using this_iterator = typename BASE_RANGE::this_iterator;
   using iterator = typename BASE_RANGE::iterator;
   using const_iterator = typename BASE_RANGE::const_iterator;


   using THIS_RAW_RANGE = typename BASE_RANGE::THIS_RAW_RANGE;
   using RAW_RANGE = typename BASE_RANGE::RAW_RANGE;
   using CONST_RAW_RANGE = typename BASE_RANGE::CONST_RAW_RANGE;

   //using ITEM_POINTER =  typename get_type_item_pointer < this_iterator >::type;

   //using ITEM = non_const < dereference < ITEM_POINTER > >;

   using SCOPED_STRING = scoped_string_base<ITERATOR_TYPE>;


   using ARG_ITEM = typename BASE_RANGE::ARG_ITEM;


   template<::std::size_t count>
   constexpr string_range(const ITEM(&array)[count]) : BASE_RANGE(array, array[count - 1] == 0 ? count - 1 : count) {}

   template<primitive_integral INTEGRAL>
   constexpr string_range(const_iterator begin, INTEGRAL count) : BASE_RANGE((this_iterator)begin,
                                                                             (this_iterator)(begin + count)) {}

   string_range(no_initialize_t) : BASE_RANGE(no_initialize_t{}) {}

   string_range(nullptr_t) : BASE_RANGE(nullptr) {}

   string_range() {}

   template<typed_range<iterator> RANGE>
   explicit string_range(const RANGE & range) : BASE_RANGE(range) {}

   template<typed_range<const_iterator> RANGE>
   explicit string_range(const RANGE & range) : BASE_RANGE(range) {}

   string_range(const THIS_RANGE & range) : BASE_RANGE(range) {}

   string_range(THIS_RANGE && range) : BASE_RANGE(::transfer(range)) {}

   string_range(this_iterator begin, this_iterator end) : BASE_RANGE(begin, end) {}
   string_range(this_iterator begin, this_iterator end, enum_range erange) : BASE_RANGE(begin, end, erange) {}

   //explicit string_range(const ::atom & atom);

   template < character_count n >
   string_range(const CHARACTER(&s)[n]) : BASE_RANGE(s) {}


   template < typed_character_pointer < typename ::string_range<ITERATOR_TYPE>::CHARACTER > CHARACTER_POINTER >
   string_range(CHARACTER_POINTER start, CHARACTER_POINTER end, e_range erange) :
      BASE_RANGE(start, end, erange) { }


   template < primitive_block BLOCK >
   string_range(const BLOCK & block);


   template < character_pointer CHARACTER_POINTER >
   string_range(CHARACTER_POINTER start) : BASE_RANGE(start, start + string_safe_length(start), e_range_null_terminated) {}

   //explicit string_range(ITERATOR_TYPE psz) : string_range(scopedstr, 0, string_safe_length(scopedstr)) {}

   string_range(ITERATOR_TYPE psz, character_count len) : string_range(psz, 0, len) {}

   //string_range(const CHARACTER * start, const CHARACTER * end) : BASE_RANGE(start, end) {}

   string_range(ITERATOR_TYPE psz, character_count start, character_count count) : string_range(
           ::_start_count_string_range(psz, start, count)) {}


   //auto this_range() const {return *this;}

   //auto subrange(character_count start, character_count count) const { auto range = *this; ::_start_count_range(range, start, count); return range; }

   using BASE_RANGE::last;
   auto & last() { return ::get(this->end() - 1); }
   //    auto & last() const { return (const CHARACTER &) ::get(this->end() - 1); }


   //    THIS_RANGE operator()(character_count start, character_count count) const {
   //
   //       return ::_start_count_range(*this, start, count);
   //
   //    }
   //
   //    THIS_RANGE operator()(character_count start, const_iterator end) const {
   //
   //       return ::_start_end_range(*this, start, end);
   //
   //    }
   //
   //
   //    THIS_RANGE operator()(const_iterator start) const {
   //
   //       return THIS_RANGE(start, this->end());
   //
   //    }
   //
   //
   //    template < primitive_integral START >
   //    THIS_RANGE operator()(START start) const {
   //
   //       return THIS_RANGE(this->begin() + start, this->end());
   //
   //    }
   //
   //
   //    THIS_RANGE operator()() const {
   //
   //       return THIS_RANGE(*this);
   //
   //    }
   //
   //
   //    bool has_character() const { return !this->is_empty(); }

   //    inline bool is_empty() const noexcept { return this->m_end <= this->m_begin || *this->m_begin == '\0'; }
   //    inline memsize length_in_bytes() const{return this->size() * sizeof(CHARACTER);}
   //
   //    //inline bool has_character() const noexcept { return !this->is_empty(); }
   //    inline character_count get_upper_bound(character_count i = -1) const noexcept { return this->size() + i; }
   //
   //    operator ::block() const { return {(unsigned char *) c_str(), this->length_in_bytes()}; }
   //
   //    inline CHARACTER character_at(character_count i) const { return this->data()[i]; }

   using BASE_RANGE::data;

   inline CHARACTER * data() { return (CHARACTER *)this->begin(); }


   void clear()
   {
      this->m_begin = nullptr;
      this->m_end = nullptr;
      this->m_erange = e_range_none;
   }
   string_range& assign(const_iterator s, const_iterator e, enum_range erange)
   {
      this->m_begin = s;
      this->m_end = e;
      this->m_erange = erange;
      return *this;
   }

   string_range& assign(const_iterator s, const_iterator e)
   {
      if (s != this->m_begin)
      {

         if (e != this->m_end)
         {

            this->m_erange = e_range_none;

         }
         else
         {

            this->m_erange =(enum_range) ( this->m_erange & ~e_range_string);
         }

      }
      else if(e != this->m_end)
      {
         this->m_erange = (enum_range)(this->m_erange & ~e_range_null_terminated);

      }
      this->m_begin = s;
      this->m_end = e;
      return *this;
   }
   template < primitive_integral INTEGRAL >
   string_range& assign(const_iterator s, INTEGRAL n)
   {

      return assign(s, s + n);

   }
   //    inline const CHARACTER *data() const { return this->begin(); }
   //
   //    inline const CHARACTER *c_str() const { return this->data(); }
   //
   //    inline const CHARACTER *c_str_for_printf() const { return this->data(); }
   //
   //    inline operator const CHARACTER *() const { return this->data(); }
   //           using BASE_RANGE::operator CHARACTER *;
   inline operator CHARACTER * () { return this->data(); }

   //using BASE_RANGE::ptr_at;
   //inline const CHARACTER * ptr_at(::collection::index i) { return this->data() + i; }

   //    inline const CHARACTER *ptr_at(::collection::index i) const { return this->data() + i; }

   //using BASE_RANGE::rear_ptr;
   //inline const CHARACTER * rear_ptr(::collection::index i) { return this->data() + this->size() + i; }

   //    inline const CHARACTER *reverse_ptr(::collection::index i) const { return this->data() + this->size() + i; }
   //
   //    inline const CHARACTER &operator[](::collection::index i) const { return this->data()[i]; }
   //
   //    character_count offset_of(const CHARACTER *p) const { return ::offset_of(p, data()); }


   string_range & operator=(const THIS_RANGE & range)
   {
      BASE_RANGE::operator=(range);
      return *this;
   }

   string_range & operator=(string_range && range) {
      BASE_RANGE::operator=(::transfer(range));
      return *this;
   }

   //string_range & operator=(const atom & atom);

   string_range & operator=(const block & block);



   //    //::std::strong_ordering order(const string_range &range) const noexcept;
   //    //using NATURAL_POINTER::order;
   //
   //    //::std::strong_ordering order(const SCOPED_STRING &range) const noexcept;
   //    ::std::strong_ordering case_insensitive_order(const SCOPED_STRING &range) const noexcept;
   //
   //    ::std::strong_ordering collate(const SCOPED_STRING &range) const noexcept;
   //
   //    ::std::strong_ordering case_insensitive_collate(const SCOPED_STRING &range) const noexcept;
   //
   //    //::std::strong_ordering order(const SCOPED_STRING &range, character_count n) const noexcept;
   //
   //    //::std::strong_ordering case_insensitive_order(const SCOPED_STRING &range, character_count n) const noexcept;
   //
   //    //::std::strong_ordering collate(const SCOPED_STRING &range, character_count n) const noexcept;
   //
   //    //::std::strong_ordering case_insensitive_collate(const SCOPED_STRING &range, character_count n) const noexcept;
   //
   //    //::std::strong_ordering order(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;
   //
   //    //::std::strong_ordering case_insensitive_order(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;
   //
   //    //::std::strong_ordering collate(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;
   //
   //    //::std::strong_ordering
   //    //case_insensitive_collate(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;
   //
   //    //::std::strong_ordering
   //    //order(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2, character_count iCount2) const noexcept;
   //
   //    //::std::strong_ordering
   //    //case_insensitive_order(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2,
   //    //                       character_count iCount2) const noexcept;
   //
   //    //::std::strong_ordering
   //    //collate(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2, character_count iCount2) const noexcept;
   //
   //    //::std::strong_ordering
   //    //case_insensitive_collate(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2,
   //    //                         character_count iCount2) const noexcept;
   //
   //    //inline int operator<=>(const string_range &range) const { return order(range); }
   //    //inline bool operator==(const string_range &range) const { return size() != range.size() ? false : !order(range); }
   //    //inline bool operator>(const string_range &range) const { return order(ansistr) > 0; }
   //    //inline bool operator<(const string_range &range) const { return order(ansistr) < 0; }
   //    //inline bool operator!=(const string_range &range) const { return !operator ==(ansistr); }
   //    //inline bool operator>=(const string_range &range) const { return !operator <(ansistr); }
   //    //inline bool operator<=(const string_range &range) const { return !operator >(ansistr); }
   //
   //
   //    //inline bool operator==(const string_range &range) const { return order(ansistr) == 0; }
   //    //inline bool operator>(const string_range &range) const { return order(ansistr) > 0; }
   //    //inline bool operator<(const string_range &range) const { return order(ansistr) < 0; }
   //    //inline bool operator!=(const string_range &range) const { return !operator ==(ansistr); }
   //    //inline bool operator>=(const string_range &range) const { return !operator <(ansistr); }
   //    //inline bool operator<=(const string_range &range) const { return !operator >(ansistr); }
   //
   //    inline bool operator==(const THIS_RANGE &range) const { return this->equals(range); }
   //    //inline ::std::strong_ordering operator<=>(const SCOPED_STRING &range) const { return this->order(range); }
   //
   //
   //
   //
   //    using BASE_RANGE::_order;
   //
   //    constexpr ::std::strong_ordering _order(const SCOPED_STRING &range) const {
   //
   //       return _order(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::order;
   //
   //    constexpr ::std::strong_ordering order(const SCOPED_STRING &range) const noexcept;
   //
   //
   //    constexpr ::std::strong_ordering operator<=>(const SCOPED_STRING &range) const {
   //
   //       return this->order(range);
   //
   //    }
   //
   //
   //    using BASE_RANGE::_equals;
   //
   //    constexpr bool _equals(const SCOPED_STRING &range) const {
   //
   //       return this->_equals(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::equals;
   //
   //    constexpr bool equals(const SCOPED_STRING &range) const {
   //
   //       return this->equals(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //    constexpr bool case_insensitive_equals(const SCOPED_STRING &range) const noexcept {
   //
   //       return this->equals(range, ::comparison::case_insensitive<ITEM>());
   //
   //    }
   //
   //    //bool equals(const SCOPED_STRING &range, character_count n) const noexcept {
   //
   //    //   return this->equals_start_count(range, 0, n, ::comparison::comparison<ITEM>());
   //
   //    //}
   //
   //    //bool case_insensitive_equals(const SCOPED_STRING &range, character_count n) const noexcept {
   //
   //    //   return this->equals_start_count(range, 0, n, ::comparison::case_insensitive<ITEM>());
   //
   //    //}
   //
   //    //bool equals(character_count start, character_count count, const SCOPED_STRING &range) const noexcept {
   //
   //    //   return this->equals_start_count(range, start, count, ::comparison::comparison<ITEM>());
   //
   //    //}
   //
   //    //bool case_insensitive_equals(character_count start, character_count count, const SCOPED_STRING &range) const noexcept {
   //
   //    //   return this->equals_start_count(range, start, count, ::comparison::case_insensitive<ITEM>());
   //
   //    //}
   //
   //    //bool
   //    //equals(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2, character_count iCount2) const noexcept {
   //
   //    //   return this->equals_start_count(range.start_count(iStart2, iCount2), start, count,
   //    //                                   ::comparison::comparison<ITEM>());
   //
   //    //}
   //
   //    //bool case_insensitive_equals(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2,
   //    //                             character_count iCount2) const noexcept {
   //
   //    //   return this->equals_start_count(range.start_count(iStart2, iCount2), start, count,
   //    //                                   ::comparison::case_insensitive<ITEM>());
   //
   //    //}
   //
   //
   //
   ////   using BASE_RANGE::_equals_start;
   ////
   ////   constexpr bool _equals_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->_equals_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::equals_start;
   ////
   ////   constexpr bool equals_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->equals_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_equals_start_count;
   ////
   ////   constexpr bool _equals_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_equals_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::equals_start_count;
   ////
   ////   constexpr bool equals_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->equals_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   //
   //    using BASE_RANGE::_find;
   //
   //    constexpr const_iterator _find(const SCOPED_STRING &range) const {
   //
   //       return this->_find(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::find;
   //
   //    constexpr const_iterator find(const SCOPED_STRING &range) const {
   //
   //       return this->find(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //    constexpr character_count find_index(const SCOPED_STRING & range, character_count start = 0) const {
   //
   //       return this->offset_of(start <= 0 ? this->find(range) : (*this)(start).find(range));
   //
   //    }
   //    constexpr character_count find_index(CHARACTER ch, character_count start = 0) const {
   //
   //       return this->offset_of(start <= 0 ? this->find(ch) : (*this)(start).find(ch));
   //
   //    }
   //
   //
   ////   using BASE_RANGE::_find_start;
   ////
   ////   constexpr const_iterator _find_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->_find_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::find_start;
   ////
   ////   constexpr const_iterator find_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->find_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_find_start_count;
   ////
   ////   constexpr const_iterator _find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::find_start_count;
   ////
   ////   constexpr const_iterator find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //
   //    using BASE_RANGE::_rear_find;
   //
   //    constexpr const_iterator _rear_find(const SCOPED_STRING &range, const_iterator end = nullptr) const
   //    {
   //
   //       return (*this)(0, ::is_null(end) ? this->end() : end)._rear_find(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::rear_find;
   //
   //    constexpr const_iterator rear_find(const SCOPED_STRING &range, const_iterator end = nullptr) const
   //    {
   //
   //       return (*this)(0, ::is_null(end) ? this->end() : end).rear_find(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //    constexpr character_count _rear_find_index(const SCOPED_STRING & range, character_count end = -1) const
   //    {
   //
   //       return this->offset_of((*this)(0, end >= 0 ? end : this->size() + end + 1)._rear_find(range));
   //
   //    }
   //
   //
   //    constexpr character_count rear_find_index(const SCOPED_STRING & range, character_count end = -1) const
   //    {
   //
   //       return this->offset_of((*this)(0, end >= 0 ? end : this->size() + end + 1).rear_find(range));
   //
   //    }
   //
   //
   //    constexpr const_iterator _rear_find(CHARACTER character, const_iterator end = nullptr) const
   //    {
   //
   //       return (*this)(0, ::is_null(end) ? this->end() : end).rear_find(character, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    constexpr const_iterator rear_find(CHARACTER character, const_iterator end = nullptr) const
   //    {
   //
   //       return (*this)(0, ::is_null(end) ? this->end() : end).rear_find(character, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    constexpr character_count _rear_find_index(CHARACTER character, character_count end = -1) const
   //    {
   //
   //       return this->offset_of((*this)(0, end >= 0 ? end : this->size() + end + 1)._rear_find(character));
   //
   //    }
   //
   //
   //    constexpr character_count rear_find_index(CHARACTER character, character_count end = -1) const
   //    {
   //
   //       return this->offset_of((*this)(0, end >= 0 ? end : this->size() + end + 1).rear_find(character));
   //
   //    }
   //
   //
   //    const_iterator case_insensitive_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW
   //    {
   //
   //       return this->find(scopedstr, ::comparison::case_insensitive<ITEM>());
   //
   //    }
   //
   //
   //    character_count case_insensitive_find_index(const SCOPED_STRING & scopedstr) const RELEASENOTHROW
   //    {
   //
   //       return this->offset_of(case_insensitive_find(scopedstr));
   //
   //    }
   //
   //
   //    character_count case_insensitive_find_index(const SCOPED_STRING & scopedstr, character_count start) const RELEASENOTHROW { return this->offset_of((*this)(start).case_insensitive_find(scopedstr)); }
   //
   //
   //    constexpr const_iterator _case_insensitive_rear_find(const SCOPED_STRING & scopedstr) const
   //    {
   //
   //       return this->_rear_find(scopedstr, ::comparison::case_insensitive<ITEM>());
   //
   //    }
   //
   //
   //    character_count _case_insensitive_rear_find_index(const SCOPED_STRING & scopedstr, character_count end = -1) const RELEASENOTHROW
   //    {
   //
   //       return this->offset_of((*this)(0, end >= 0 ? end : this->size() + end + 1)._case_insensitive_rear_find(scopedstr));
   //
   //    }
   //
   //
   //    constexpr const_iterator case_insensitive_rear_find(const SCOPED_STRING & scopedstr) const
   //    {
   //
   //       return this->rear_find(scopedstr, ::comparison::case_insensitive<ITEM>());
   //
   //    }
   //
   //
   //    character_count case_insensitive_rear_find_index(const SCOPED_STRING & scopedstr, character_count end = -1) const RELEASENOTHROW
   //    {
   //
   //
   //       return this->offset_of((*this)(0, end >= 0 ? end : this->size() + end + 1).case_insensitive_rear_find(scopedstr));
   //
   //    }
   //
   //
   ////   using BASE_RANGE::_rear_find_start;
   ////
   ////   constexpr const_iterator _rear_find_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->_rear_find_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::rear_find_start;
   ////
   ////   constexpr const_iterator rear_find_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->rear_find_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_rear_find_start_count;
   ////
   ////   constexpr const_iterator _rear_find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::rear_find_start_count;
   ////
   ////   constexpr const_iterator rear_find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //
   //    using BASE_RANGE::_find_first_character_in;
   //
   //    constexpr const_iterator _find_first_character_in(const SCOPED_STRING &range) const {
   //
   //       return this->_find_first_character_in(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //    constexpr character_count _find_first_character_in_index(const SCOPED_STRING & range) const {
   //       return this->offset_of(_find_first_character_in(range));
   //    }
   //
   //    using BASE_RANGE::find_first_character_in;
   //
   //    constexpr const_iterator find_first_character_in(const SCOPED_STRING &range) const {
   //
   //       return this->find_first_character_in(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //    constexpr character_count find_first_character_in_index(const SCOPED_STRING & range, ::character_count start = 0) const {
   //       return this->offset_of((*this)(start).find_first_character_in(range));
   //    }
   //
   //
   //    // Convert the string_base < ITERATOR_TYPE > to lowercase
   //    //template < typename ITERATOR_TYPE >
   //    string_base < ITERATOR_TYPE > lowered() const;
   //
   //
   ////   using BASE_RANGE::_find_first_character_in_start;
   ////
   ////   constexpr const_iterator _find_first_character_in_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->_find_first_character_in_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::find_first_character_in_start;
   ////
   ////   constexpr const_iterator find_first_character_in_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->find_first_character_in_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_find_first_character_in_start_count;
   ////
   ////   constexpr const_iterator _find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::find_first_character_in_start_count;
   ////
   ////   constexpr const_iterator find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //
   //
   //    using BASE_RANGE::_skip_any_character_in;
   //
   //    constexpr const_iterator skip_any_character_in(const SCOPED_STRING &range) const {
   //
   //       return this->_skip_any_character_in(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    constexpr character_count skip_any_character_in_index(const SCOPED_STRING & range, ::character_count start = 0) const {
   //       return this->offset_of((*this)(start).skip_any_character_in(range));
   //    }
   //
   //
   //    using BASE_RANGE::skip_any_character_in;
   //
   ////    constexpr const_iterator skip_any_character_in(const SCOPED_STRING &range) const {
   ////
   ////       return this->skip_any_character_in(range, ::comparison::comparison<ITEM>());
   ////
   ////    }
   //
   //
   ////   using BASE_RANGE::_skip_any_character_in_start;
   ////
   ////   constexpr const_iterator _skip_any_character_in_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->_skip_any_character_in_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::skip_any_character_in_start;
   ////
   ////   constexpr const_iterator skip_any_character_in_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->skip_any_character_in_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_skip_any_character_in_start_count;
   ////
   ////   constexpr const_iterator _skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::skip_any_character_in_start_count;
   ////
   ////   constexpr const_iterator skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //
   //    using BASE_RANGE::_rear_skip_any_character_in;
   //
   //    constexpr const_iterator _rear_skip_any_character_in(const SCOPED_STRING &range) const noexcept {
   //
   //       return this->_rear_skip_any_character_in(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::rear_skip_any_character_in;
   //
   //    constexpr const_iterator rear_skip_any_character_in(const SCOPED_STRING &range) const noexcept {
   //
   //       return this->rear_skip_any_character_in(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   ////   using BASE_RANGE::rear_skip_any_character_in_start;
   ////
   ////   constexpr const_iterator rear_skip_any_character_in_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->rear_skip_any_character_in_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_rear_skip_any_character_in_start_count;
   ////
   ////   constexpr const_iterator _rear_skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_rear_skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::rear_skip_any_character_in_start_count;
   ////
   ////   constexpr const_iterator rear_skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->rear_skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //    using BASE_RANGE::_skip;
   //
   //    constexpr const_iterator _skip(CHARACTER item) const {
   //
   //       return this->_skip(item, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::skip;
   //
   //    constexpr const_iterator skip(CHARACTER item) const {
   //
   //       return this->skip(item, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   ////   using BASE_RANGE::_skip_start;
   ////
   ////   constexpr const_iterator _skip_start(const ITEM & item, memsize start) const
   ////   {
   ////
   ////      return this->_skip_start(item, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::skip_start;
   ////
   ////   constexpr const_iterator skip_start(const ITEM & item, memsize start) const
   ////   {
   ////
   ////      return this->skip_start(item, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_skip_start_count;
   ////
   ////   constexpr const_iterator _skip_start_count(const ITEM & item, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_skip_start_count(item, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::skip_start_count;
   ////
   ////   constexpr const_iterator skip_start_count(const ITEM & item, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->skip_start_count(item, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //
   //
   //
   //    //using BASE_RANGE::_rear_find;
   //
   //    //constexpr const_iterator _rear_find(ARG_ITEM item) const {
   //
   //    //   return this->_rear_find(item, ::comparison::comparison<ITEM>());
   //
   //    //}
   //
   //
   //    //using BASE_RANGE::rear_find;
   //
   //    //constexpr const_iterator rear_find(ARG_ITEM item) const {
   //
   //    //   return this->rear_find(item, ::comparison::comparison<ITEM>());
   //
   //    //}
   //
   //    //constexpr character_count _rear_find_index(ARG_ITEM item) const {
   //
   //    //   return this->offset_of(this->_rear_find(item));
   //
   //    //}
   //
   //
   //    //constexpr character_count rear_find_index(ARG_ITEM item) const {
   //
   //    //   return this->offset_of(this->rear_find(item));
   //
   //    //}
   //
   //
   ////   using BASE_RANGE::_rear_find_item_start;
   ////
   ////   constexpr const_iterator _rear_find_item_start(const ITEM & item, memsize start) const
   ////   {
   ////
   ////      return this->_rear_find_item_start(item, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::rear_find_item_start;
   ////
   ////   constexpr const_iterator rear_find_item_start(const ITEM & item, memsize start) const
   ////   {
   ////
   ////      return this->rear_find_item_start(item, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_rear_find_item_start_count;
   ////
   ////   constexpr const_iterator _rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::rear_find_item_start_count;
   ////
   ////   constexpr const_iterator rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //
   //
   //    using BASE_RANGE::_rear_find_first_character_in;
   //
   //    constexpr const_iterator _rear_find_first_character_in(const SCOPED_STRING &range) const noexcept {
   //
   //       return this->_rear_find_first_character_in(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::rear_find_first_character_in;
   //
   //    constexpr const_iterator rear_find_first_character_in(const SCOPED_STRING &range) const noexcept {
   //
   //       return this->rear_find_first_character_in(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   ////   using BASE_RANGE::rear_find_first_character_in_start;
   ////
   ////   constexpr const_iterator rear_find_first_character_in_start(const SCOPED_STRING & range, memsize start) const
   ////   {
   ////
   ////      return this->rear_find_first_character_in_start(range, start, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::_rear_find_first_character_in_start_count;
   ////
   ////   constexpr const_iterator _rear_find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->_rear_find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   ////
   ////
   ////   using BASE_RANGE::rear_find_first_character_in_start_count;
   ////
   ////   constexpr const_iterator rear_find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   ////   {
   ////
   ////      return this->rear_find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   ////
   ////   }
   //
   //
   //    using BASE_RANGE::_begins;
   //
   //    constexpr bool _begins(const SCOPED_STRING &range) const {
   //
   //       return this->_begins(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::begins;
   //
   //    constexpr bool begins(const SCOPED_STRING &range) const {
   //
   //       return this->begins(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    ::collection::count begins_count(bool(*character_is_function)(CHARACTER character))
   //    {
   //
   //       ::collection::count c = 0;
   //
   //       while (character_is_function(this->begin()[c])) c++;
   //
   //       return c;
   //
   //    }




   //   using BASE_RANGE::_begins_start;
   //
   //   constexpr bool _begins_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->_begins_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::begins_start;
   //
   //   constexpr bool begins_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->begins_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_begins_start_count;
   //
   //   constexpr bool _begins_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_begins_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::begins_start_count;
   //
   //   constexpr bool begins_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->begins_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }



   //    using BASE_RANGE::_ends;
   //
   //    constexpr bool _ends(const SCOPED_STRING &range) const {
   //
   //       return this->_ends(range, ::comparison::comparison<ITEM>());
   //
   //    }
   //
   //
   //    using BASE_RANGE::ends;
   //
   //    constexpr bool ends(const SCOPED_STRING &range) const {
   //
   //       return this->ends(range, ::comparison::comparison<ITEM>());
   //
   //    }


   //   using BASE_RANGE::_ends_start;
   //
   //   constexpr bool _ends_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->_ends_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::ends_start;
   //
   //   constexpr bool ends_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->ends_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_ends_start_count;
   //
   //   constexpr bool _ends_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_ends_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::ends_start_count;
   //
   //   constexpr bool ends_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->ends_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }


   //
   //
   //    template<typename PRED>
   //    bool is_every_char(PRED pred) {
   //
   //       for (::collection::index i = 0; i < this->length(); i++) {
   //
   //          if (!pred(this->operator[](i))) {
   //
   //             return false;
   //
   //          }
   //
   //       }
   //
   //       return true;
   //
   //    }
   //
   //
   //    template<typename NUMBER>
   //    NUMBER &translate_index(NUMBER &number) {
   //
   //       if (number < 0) {
   //
   //          number += this->size() + 1;
   //
   //          if (number < 0) {
   //
   //             number = 0;
   //
   //          }
   //
   //       } else if (number > this->size()) {
   //
   //          number = this->size();
   //
   //       }
   //
   //       return number;
   //
   //    }

   //
   //    //inline bool contains(CHARACTER ch = 0) const;
   //    inline bool contains(const SCOPED_STRING &scopedstr = 0) const;
   //
   //    //inline bool contains(const string_base &str = 0) const;
   //    inline bool contains(CHARACTER ch) const { return ::is_set(find(ch)); }
   //
   //    inline bool
   //    contains(const SCOPED_STRING &scopedstr, const CHARACTER **ppszBeg, const CHARACTER **ppszEnd = nullptr) const;
   //    //inline bool contains(const string_base &str, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;
   //
   //    template<primitive_array STRING_ARRAY>
   //    inline bool contains_any(const STRING_ARRAY &stra) const;
   //
   //    template<primitive_array STRING_ARRAY>
   //    inline bool contains_all(const STRING_ARRAY &stra) const;
   //
   //    //inline bool case_insensitive_contains(CHARACTER ch = 0) const;
   //    inline bool case_insensitive_contains(const SCOPED_STRING &scopedstr = 0) const;
   //
   //    //inline bool case_insensitive_contains(const string_base &str = 0) const;
   //    //inline bool case_insensitive_contains(CHARACTER ch, const CHARACTER ** ppszBeg) const;
   //    inline bool
   //    case_insensitive_contains(const SCOPED_STRING &scopedstr, const CHARACTER **ppszBeg, const CHARACTER **ppszEnd = nullptr) const;
   //    //inline bool case_insensitive_contains(const string_base &str, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;
   //
   //    template<primitive_array STRING_ARRAY>
   //    inline bool case_insensitive_contains_at_least_one_of(const STRING_ARRAY &stra) const;
   //
   //    template<primitive_array STRING_ARRAY>
   //    inline bool case_insensitive_contains_all(const STRING_ARRAY &stra) const;
   //
   //
   //    //inline bool unicode_case_insensitive_contains(CHARACTER ch = 0) const;
   //    inline bool unicode_case_insensitive_contains(const SCOPED_STRING &scopedstr = 0) const;
   //
   //    //inline bool unicode_case_insensitive_contains(const string_base &str = 0) const;
   //    //inline bool unicode_case_insensitive_contains(CHARACTER ch, const CONST_STRING_RANGE &* ppszBeg) const;
   //    inline bool
   //    unicode_case_insensitive_contains(const SCOPED_STRING &scopedstr, const CHARACTER **ppszBeg, const CHARACTER **ppszEnd = nullptr) const;
   //    //inline bool unicode_case_insensitive_contains(const string_base &str, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;
   //
   //    template<primitive_array STRING_ARRAY>
   //    inline bool unicode_case_insensitive_contains_at_least_one_of(const STRING_ARRAY &stra) const;
   //
   //    template<primitive_array STRING_ARRAY>
   //    inline bool unicode_case_insensitive_contains_all(const STRING_ARRAY &stra) const;
   //
   //
   //    template<::comparison::equality<CHARACTER> EQUALITY>
   //    ::collection::count _occurrence_count_of(const SCOPED_STRING &scopedstr, EQUALITY equality) {
   //
   //       character_count nLen = scopedstr.size();
   //
   //       character_count count = 0;
   //
   //       auto range = (*this)();
   //
   //       while ((range.begin(range.find(scopedstr, equality))) != nullptr) {
   //
   //          count++;
   //
   //          range.begin() += nLen;
   //
   //       }
   //
   //       return count;
   //
   //    }
   //
   //
   //    ::collection::count occurrence_count_of(const SCOPED_STRING &scopedstr = 0) {
   //
   //       return _occurrence_count_of(scopedstr, ::comparison::comparison<CHARACTER>());
   //
   //    }
   //
   //
   //    ::collection::count case_insensitive_occurrence_count_of(const SCOPED_STRING &scopedstr = 0) {
   //
   //       return _occurrence_count_of(scopedstr, ::comparison::case_insensitive<CHARACTER>());
   //
   //    }
   //

   //
   //    // find routines
   //
   //    // find the first occurrence of character 'ch', starting at index 'iStart'
   //    const_iterator find(CHARACTER ch) const RELEASENOTHROW;
   //
   ////   character_count find(CHARACTER ch) const RELEASENOTHROW;
   ////   character_count find(CHARACTER ch) const RELEASENOTHROW;
   //    const_iterator case_insensitive_find(CHARACTER ch) const RELEASENOTHROW;
   //
   //    // find routines
   //
   //// find the first occurrence of character 'ch', starting at index 'iStart'
   //    //character_count find_index(CHARACTER ch) const RELEASENOTHROW { return this->offset_of(this->find(ch)); }
   //
   //    //   character_count find(CHARACTER ch) const RELEASENOTHROW;
   //    //   character_count find(CHARACTER ch) const RELEASENOTHROW;
   //    character_count case_insensitive_find_index(CHARACTER ch) const RELEASENOTHROW { return this->offset_of(case_insensitive_find(ch)); }
   //    character_count case_insensitive_find_index(CHARACTER ch, character_count start) const RELEASENOTHROW { return this->offset_of((*this)(start).case_insensitive_find(ch)); }
   //
   //    const_iterator find_skip_or_end(CHARACTER ch = 0) const RELEASENOTHROW
   //    {
   //
   //       auto p = this->begin();
   //
   //       while (p < this->end()) {
   //
   //          if (*p == ch) {
   //
   //             p++;
   //
   //             return p;
   //
   //          }
   //
   //          p++;
   //
   //       }
   //
   //       return p;
   //
   //    }
   //


       //inline bool begins(const SCOPED_STRING & scopedstrPrefix) const;
       //inline bool ends(const SCOPED_STRING & scopedstrSuffix) const;

   //    inline bool case_insensitive_begins(const SCOPED_STRING &scopedstrPrefix) const;
   //
   //    inline bool case_insensitive_ends(const SCOPED_STRING &scopedstrSuffix) const;


       // look for a specific sub-string_base

       //bool _find_prefix(character_count & i, const string_base &str, character_count & start, character_count & blockLen, character_count & nEndPosition, const CHARACTER ** ppszTail) const RELEASENOTHROW;

       // find the first occurrence of string_base 'block', starting at index 'iStart'
       //const_iterator find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;



   //    const_iterator unicode_find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
   //
   //    const_iterator unicode_case_insensitive_find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
   //    ::collection::index unicode_case_insensitive_find_index(const SCOPED_STRING & scopedstr, character_count start = 0) const RELEASENOTHROW
   //    {
   //
   //       return this->offset_of(this->operator()(start).unicode_case_insensitive_find(scopedstr));
   //
   //    }
   //
   //    // find the first occurrence of string_base 'block', starting at index 'iStart', if found returns the index of first character after the end of the found string_base
   //    //const_iterator rear_find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
   //
   //    const_iterator unicode_rear_find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
   //
   //    const_iterator unicode_case_insensitive_rear_find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
   //
   //    // find the first occurrence of any of the characters in string_base 'pszCharSet'
   //    //const_iterator find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //    //const_iterator find_first_character_in(const SCOPED_STRING & scopedstrCharacters) const RELEASENOTHROW;
   //    //character_count find_first_character_in(const CHARACTER * blockCharacters, character_count iStart = 0) const RELEASENOTHROW;
   //
   //    //const_iterator _find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //    //const_iterator _find_first_character_in(const SCOPED_STRING & scopedstrCharacters) const RELEASENOTHROW;
   //    ///character_count _find_first_character_in(const CHARACTER * blockCharacters, character_count iStart = 0) const RELEASENOTHROW;
   //
   //    const_iterator find_first(CHARACTER chSeparator) const RELEASENOTHROW;
   //
   //    //character_count find_first_in(const string_base &str) const RELEASENOTHROW;
   //    //character_count find_first_in(const string_base &str) const RELEASENOTHROW;
   //    ////character_count find_first_in(const string_base &str) const RELEASENOTHROW;
   //    //character_count find_first_in(CHARACTER ca) const RELEASENOTHROW;
   //
   //    //const_iterator skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //
   //    //const_iterator skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //
   //    //character_count skip_any_character_in(const CHARACTER * pszCharacters) const RELEASENOTHROW;
   //    // const_iterator skip(CHARACTER chSkip) const RELEASENOTHROW;
   //
   //    //const_iterator
   //    //_skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //
   //    //const_iterator _skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //
   //    //character_count _skip_any_character_in(const CHARACTER * pszCharacters) const RELEASENOTHROW;
   //    //const_iterator _skip(CHARACTER chSkip) const RELEASENOTHROW;
   //
   //
   ////character_count find_last_not_in(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
   //    //character_count find_last_not_in(const string_base &str) const RELEASENOTHROW;
   //    ////character_count find_last_not_in(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
   //    //character_count find_last_not_in(CHARACTER ca, character_count pos = -1) const RELEASENOTHROW;
   //
   ////    const_iterator rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   ////
   ////    const_iterator rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters, character_count iStart,
   ////                                                character_count n) const RELEASENOTHROW;
   //    //character_count rear_find_first_character_in(const CHARACTER * blockCharacters) const RELEASENOTHROW;
   //
   ////    const_iterator _rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   ////
   ////    const_iterator _rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters, character_count iStart,
   ////                                                 character_count n) const RELEASENOTHROW;
   //    //character_count _rear_find_first_character_in(const CHARACTER * blockCharacters) const RELEASENOTHROW;
   //
   //    //character_count find_first_of(const string_base &str) const RELEASENOTHROW;
   //    //character_count find_first_of(const string_base &str) const RELEASENOTHROW;
   //    //character_count find_first_of(const CHARACTER * pszCharacters) const RELEASENOTHROW;
   //    //character_count find_first_of(CHARACTER ca) const RELEASENOTHROW;
   //    //character_count find_first_of(CHARACTER ca, character_count pos) const RELEASENOTHROW;
   //
   //    //character_count find_first_not_of(const string_base &str) const RELEASENOTHROW;
   //    //character_count find_first_not_of(const string_base &str) const RELEASENOTHROW;
   //    //character_count find_first_not_of(const string_base &str) const RELEASENOTHROW;
   //    //character_count find_first_not_of(CHARACTER ca) const RELEASENOTHROW;
   //
   //    //const_iterator rear_skip_any_character_in(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
   //    //const_iterator rear_skip_any_character_in(const SCOPED_STRING & scopedstr) const RELEASENOTHROW;
   //    //character_count rear_skip_any_character_in(const CHARACTER * psz, character_count pos = -1) const RELEASENOTHROW;
   //
   //    //const_iterator rear_skip(CHARACTER ca) const RELEASENOTHROW;
   //    //const_iterator rear_skip(CHARACTER ca) const RELEASENOTHROW;
   //
   //
   //    //const_iterator _rear_skip_any_character_in(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
   //    //const_iterator _rear_skip_any_character_in(const SCOPED_STRING & scopedstr) const RELEASENOTHROW;
   //
   //
   //    using BASE_RANGE::_rear_skip;
   //
   //
   //    //const_iterator _rear_skip_any_character_in(CHARACTER ca) const RELEASENOTHROW;
   //    const_iterator _rear_skip(CHARACTER ca) const RELEASENOTHROW
   //    {
   //
   //       return this->_rear_skip(ca, ::comparison::comparison < CHARACTER >());
   //
   //    }
   //
   //    using BASE_RANGE::rear_skip;
   //
   //    //character_count _rear_skip_any_character_in(const CHARACTER * psz, character_count pos = -1) const RELEASENOTHROW;
   //    const_iterator rear_skip(CHARACTER ca) const RELEASENOTHROW
   //    {
   //
   //       return this->rear_skip(ca, ::comparison::comparison < CHARACTER> ());
   //
   //    }
   //
   //    //character_count find_last_of(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
   //    //character_count find_last_of(const string_base &str) const RELEASENOTHROW;
   //    ////character_count find_last_of(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
   //    //character_count find_last_of(CHARACTER ca, character_count pos = -1) const RELEASENOTHROW;
   //
   //    // find the last occurrence of character 'ch'
   //    //const_iterator rear_find(CHARACTER ch) const RELEASENOTHROW;
   //
   //    // find the last occurrence of string_base 'sz'
   //    //const_iterator rear_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW;
   //
   //
   //
   //    CHARACTER last_char(character_count count = -1) const;
   //
   //
   //    inline character_count unichar_count() const;
   //
   //    inline const_iterator unichar_at(character_count iUnicharIndex) const;
   //
   //
   //    //const_iterator __replace(const_iterator start, const_iterator end, const SCOPED_STRING & scopedstr)
   //    //{
   //
   //    //   ::memory_transfer((void *)start, start + scopedstr.size(), this->end() - end);
   //
   //    //   string_count_copy(start, scopedstr.begin(), scopedstr.size());
   //
   //    //}
   //
   //
   //    //bool equals(const string_base &str) const;
   //    //bool case_insensitive_equals(const string_base &str) const;
   //           inline bool operator==(const ::ansi_string &str) const;
   //
   //           inline bool operator==(const ::wd16_string &str) const;
   //
   //           inline bool operator==(const ::wd32_string &str) const;
   //
   //    //inline bool operator ==(const SCOPED_STRING & scopedstr) const { return this->equals(scopedstr); }
   //    inline bool operator==(const_char_pointer psz) const { return this->equals(scopedstr); }
   //
   //    inline bool operator==(const ::wd16_character *psz) const { return this->equals(scopedstr); }
   //
   //    inline bool operator==(const ::wd32_character *psz) const { return this->equals(scopedstr); }
   //
   //    inline bool operator==(const ::inline_number_string &inline_number_string) const {
   //       return this->equals((const SCOPED_STRING &) inline_number_string);
   //    }
   //
   //    //inline ::std::strong_ordering operator<=>(const string_base & range) const { return this->order(range); }
   //    //inline ::std::strong_ordering operator<=>(const SCOPED_STRING &scopedstr) const { return this->order(scopedstr); }
   //    //inline ::std::strong_ordering operator<=>(const CHARACTER * psz) const { return *this <=> ((const SCOPED_STRING &)psz); }
   //    //inline int operator<=>(CHARACTER ch) const;
   //    //inline bool operator==(CHARACTER ch) const;
   //    //inline bool operator==(CHARACTER ch) const;
   //    //inline bool operator>(const string_base &str2) const;
   //    //inline bool operator>(CHARACTER ch) const;
   //    //inline bool operator<(const string_base &str2) const;
   //    //inline bool operator<(CHARACTER ch) const;
   //    //inline bool operator!=(const string_base &str) const { return !operator ==(scopedstr); }
   //    //inline bool operator!=(CHARACTER ch) const { return !operator ==(ch); }
   //    //inline bool operator>=(const string_base &str) const { return !operator <(scopedstr); }
   //    //inline bool operator>=(CHARACTER ch) const { return !operator <(ch); }
   //    //inline bool operator<=(const CHARACTER * psz) const { return !operator >(scopedstr); }
   //    //inline bool operator<=(CHARACTER ch) const { return !operator >(ch); }
   //
   //
   //
   //    //character_count rear_find(CHARACTER ch) const RELEASENOTHROW
   //    //{
   //    //   return rear_find(ch, iStart);
   //    //};
   //    //character_count rear_find(const string_base &str) const RELEASENOTHROW
   //    //{
   //    //   return rear_find(sz, iStart);
   //    //};
   //


     //
     //    const_iterator find_first_whitespace() const RELEASENOTHROW { return this->find_first_character_in("\t\r\n "); }
     //
     //    const_iterator skip_whitespace() const RELEASENOTHROW { return this->skip_any_character_in("\t\r\n "); }
     //
     //    ::character_count count_left(const SCOPED_STRING& range = "\t\r\n ") const RELEASENOTHROW { return this->skip_any_character_in(range) - this->begin(); }


   void add_to_begin(::character_count size)
   {

      if(size)
      {

         this->m_begin += size;

         this->m_erange = (enum_range)(this->m_erange & ~e_range_string);

      }

   }


   void add_to_end(::character_count size)
   {

      if(size)
      {

         this->m_end += size;

         this->m_erange = (enum_range)(this->m_erange & ~(e_range_string | e_range_null_terminated));

      }

   }


   void set_begin(ITERATOR_TYPE p)
   {

      if(this->m_begin != p)
      {

         this->m_begin = p;

         this->m_erange = (enum_range) (this->m_erange  & ~e_range_string);

      }

   }


   void set_end(ITERATOR_TYPE p)
   {

      if(this->m_end != p)
      {

         this->m_end = p;

         this->m_erange = (enum_range)(this->m_erange & ~(e_range_string | e_range_null_terminated));

      }

   }


   string_range & trim_left(const SCOPED_STRING & range) RELEASENOTHROW { add_to_begin(this->count_left(range));
         return *this; }

   //    const_iterator rear_find_first_whitespace() const RELEASENOTHROW { return this->rear_find_first_character_in("\t\r\n "); }
   //
   //    const_iterator rear_skip_whitespace() const RELEASENOTHROW { return this->rear_skip_any_character_in("\t\r\n "); }
   //
   //    ::character_count count_right(const SCOPED_STRING& range = "\t\r\n ") const RELEASENOTHROW { return this->m_end - this->rear_skip_any_character_in(range); }

   string_range & trim_right(const SCOPED_STRING & range) RELEASENOTHROW { add_to_end(-this->count_right(range)); return *this; }

   //    ::character_count count_left_and_right(const SCOPED_STRING& range = "\t\r\n ") const RELEASENOTHROW { ::character_count c; return ((c = count_left(range)) == this->size()) ? c : c + count_right(range); }

   string_range & trim(const SCOPED_STRING & range) RELEASENOTHROW { trim_left(range); trim_right(range); return *this; }

   bool paired_trim(CHARACTER character1, CHARACTER character2)
   {

      if (this->size() < 2)
      {

         return false;

      }

      if (this->first() != character1 || this->last() != character2)
      {

         return false;

      }

      this->add_to_begin(1);

      this->add_to_end(-1);

      return true;

   }


   string_range& pair_trim_quotes()
   {

      while (paired_trim('\"', '\"') || paired_trim('\'', '\''));

      return *this;

   }


   bool begins_eat(CHARACTER character)
   {

      if (this->size() <= 0)
      {

         return false;

      }

      if (this->first() != character)
      {

         return false;

      }

      this->begin()++;

      return true;

   }


   bool defer_consume_character(CHARACTER & character)
   {

      if (this->size() <= 0)
      {

         return false;

      }

      character = this->first();

      this->begin()++;

      return true;

   }


   int defer_consume_digit(int iBase)
   {

      CHARACTER character;

      if (!defer_consume_character(character))
      {

         return -1;

      }

      if (character >= '0' && character <= ('0' + minimum(iBase - 1, 9)))
      {

         return character - '0';

      }

      if (iBase <= 10)
      {

         return -1;

      }

      if (character >= 'a' && character <= ('a' + minimum(iBase - 11, 'z')))
      {

         return character - 'a';

      }
      else if (character >= 'A' && character <= ('A' + minimum(iBase - 11, 'Z')))
      {

         return character - 'A';

      }

      return -1;

   }


   ::collection::count consume(bool(*character_is_function)(CHARACTER character), character_count minimum_count);


   ::collection::count consume_spaces(character_count minimum_count = 0)
   {

      return consume(&character_isspace, minimum_count);

   }


   bool consume_line(string_range & range)
   {

      if (this->is_empty())
      {

         return false;

      }

      auto p = this->find_first_character_in("\r\n");

      range.m_begin = this->m_begin;

      range.m_erange = e_range_none;

      if (p)
      {

         range.m_end = p;

         if (*p == '\r' && *(p + 1) == '\n')
         {

            p += 2;

         }
         else
         {

            p++;

         }

         this->m_begin = p;

      }
      else
      {

         range.m_end = this->m_end;

         this->m_begin = this->m_end;

      }

      return range;

   }


   string_range consume_line()
   {

      string_range range(no_initialize_t{});

      if (!consume_line(range))
      {

         return {};

      }

      return range;

   }


   string_base<ITERATOR_TYPE > consume_quoted_value();

   bool defer_consume_quoted_value(string_base<ITERATOR_TYPE > & str);

   bool defer_consume(const SCOPED_STRING & scopedstr)
   {

      if (!this->begins(scopedstr))
      {

         return false;

      }

      this->begin() += scopedstr.size();

      return true;

   }

   string_range consume_word(const SCOPED_STRING & scopedstrCharacters = " ")
   {

      return this->consume_token_until_any_character_in(scopedstrCharacters);

   }


   bool begins_consume(const ::scoped_string & scopedstr);
   bool begins_consume(ansi_character ansich) { return (*this->m_begin == ansich) ? (static_cast<void>(this->m_begin++), true) : false; }
   bool begins_consume(::ansi_character & characterReturn, ansi_character ansich) { return (bool)(*this->m_begin == ansich) ? (static_cast<void>(characterReturn = ansich), static_cast<void>(this->m_begin++), true) : false; }
   bool begins_eat(const ::scoped_string & scopedstr);
   bool ends_eat(const ::scoped_string & scopedstr);
   bool case_insensitive_begins_eat(const ::scoped_string & scopedstr);
   bool case_insensitive_ends_eat(const ::scoped_string & scopedstr);
   void consume(const_char_pointer pszToConsume);
   //static void consume(::const_ansi_range & range, const_char_pointer psz);
   void consume(const ::scoped_string & scopedstr);
   //void consume_spaces(::collection::count iMinimumCount = 1);
   unsigned long long consume_natural(unsigned long long uiMax = ((unsigned long long)-1), unsigned long long uiMin = 0);
   //unsigned long long consume_natural(string & str, unsigned long long uiMax = ((unsigned long long)-1), unsigned long long uiMin = 0);
   string_range consume_hex();
   //void consume_spaces(::const_ansi_range & range, ::collection::count iMinimumCount);
   string_range consume_non_spaces();
   //::string_base < ITERATOR_TYPE > consume_non_spaces(::const_ansi_range & range);
   string_range consume_nc_name();
   //  ::string_base < ITERATOR_TYPE > consume_quoted_value(const_char_pointer &pszParse);
   //static void no_escape_consume_quoted_value(::const_ansi_range & range, ::ansi_character ** ppsz, character_count & iBufferSize);
   string_base<ITERATOR_TYPE> no_escape_consume_quoted_value();
   void no_escape_skip_quoted_value();

   //template < typename ITERATOR_TYPE >
   //static string_base < ITERATOR_TYPE > consume_quoted_value(::string_range<BASE_TYPE> & range);


   string_base<ITERATOR_TYPE> consume_quoted_value_ex();
   void skip_quoted_value_ex();
   //static ::string_base < ITERATOR_TYPE > consume_spaced_value(string & str);
   //::string_base < ITERATOR_TYPE > consume_spaced_value(const_char_pointer &pszParse);
   string_range consume_spaced_value();
   //static ::string_base < ITERATOR_TYPE > consume_command_line_argument(string & str);
   //::string_base < ITERATOR_TYPE > consume_command_line_argument(const_char_pointer &pszParse);
   string_base<ITERATOR_TYPE> consume_command_line_argument();
   void consume_until_any_character_in(const ::scoped_string & scopedstr);
   //static bool begins_consume(::const_ansi_range & range, const ::scoped_string & scopedstr);

   string_range xml_consume_comment();

   string_base < ITERATOR_TYPE > consume_c_quoted_value();

   template < bool bWriteOutput >
   void _consume_quoted_value_ex(string_base<ITERATOR_TYPE>* pstrOut);

   string_range consume_utf8_char();





   ///
   /// Name   : _tcsechr
   /// Desc   : similar with strchr with escape process
   /// Param  : escape - will be escape character
   //; Return :
   ///--------------------------------------------------------
   /// Coder    Date                      Desc
   /// bro      2002-10-29
   ///========================================================

   void escape_skip_to_character(int ch, int escape);

   ///========================================================
   /// Name   : _tcsepbrk
   /// Desc   : similar with ansi_scan with escape process
   /// Param  : escape - will be escape character
   /// Return :
   ///--------------------------------------------------------
   /// Coder    Date                      Desc
   /// bro      2002-10-29
   ///========================================================
   void escape_skip_to_first_character_in(const_char_pointer chset, int escape);


   ///========================================================
   /// Name   : _tcsenistr
   /// Desc   : similar with _tcsistr with escape process
   /// Param  : escape - will be escape character
   /// Return :
   ///--------------------------------------------------------
   /// Coder    Date                      Desc
   /// bro      2002-10-29
   ///========================================================
   void escape_case_insensitive_skip_to(const ::scoped_string & scopedstr, int escape);
   
   THIS_RANGE& trim_left()
   {

      return *this = this->trimmed_left();

   }


   THIS_RANGE& trim_right()
   {

      return *this = this->trimmed_right();

   }


   THIS_RANGE& trim()
   {

      return *this = this->trimmed_right().trimmed_left();

   }


   inline ::collection::count _count_parts_from_beginning(::collection::count cPathMaxPartCount, CHARACTER chPartSeparator)
   {

      this->m_begin = this->__count_parts_from_beginning(cPathMaxPartCount, chPartSeparator);

      return cPathMaxPartCount;

   }


   inline ::collection::count count_parts_from_beginning(::collection::count  cPathPartCountToConsume, CHARACTER chSeparator)
   {

      if (cPathPartCountToConsume <= 0)
      {

         return cPathPartCountToConsume;

      }

      return this->_count_parts_from_beginning(cPathPartCountToConsume, chSeparator);

   }


   
   string_range consume_token_until_any_character_in(const SCOPED_STRING& scopedstrCharacters, bool bReturnSeparator = false, bool bSkipAnyCharactersIn = true);


};















using ansi_range = ::string_range< const_char_pointer >;
using wd16_range = ::string_range< const ::wd16_character *>;
using wd32_range = ::string_range< const ::wd32_character *>;
using wide_range = ::string_range< const ::wide_character *>;


//using ansi_string_range = ::string_range<::ansi_string>;
//using wd16_string_range = ::string_range<::wd16_string>;
//using wd32_string_range = ::string_range<::wd32_string>;
//using wide_string_range = ::string_range<::wide_string>;


template < primitive_character CHARACTER, primitive_integral INTEGRAL >
::string_range < const CHARACTER* > as_string_range(const CHARACTER* p, INTEGRAL n)
{

   return {
      p,
      p + n,
      p[n] == CHARACTER{} ?
      e_range_null_terminated : e_range_none
   };

}

