// From string_range.h by camilo on 2023-02-20 20:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/string/character_range.h"


#include <algorithm>


#define IMPLEMENT_TYPED_STRING_LITERAL(NAME, LITERAL) \
template < typename T > consteval auto typed_##NAME() { throw "interface only for typed_" #NAME; return nullptr; } \
template < > consteval auto typed_##NAME<char>() { return LITERAL; } \
template < > consteval auto typed_##NAME<wchar_t>() { return L##LITERAL; } \
template < > consteval auto typed_##NAME<char16_t>() { return u##LITERAL; } \
template < > consteval auto typed_##NAME<char32_t>() { return U##LITERAL; }


template<primitive_character CHARACTER>
constexpr ::range<const CHARACTER *>
inline _start_count_string_range(const CHARACTER *psz, memsize start, memsize count);

//
//template < typename T >
//consteval auto typed_whitespace() { throw "interface onlye"; return nullptr; }
//
//template < >
//consteval auto typed_whitespace<char>() { return "/t/r/n "; }
//template < >
//consteval auto typed_whitespace<wchar_t>() { return L"/t/r/n "; }
//template < >
//consteval auto typed_whitespace<char16_t>() { return u"/t/r/n "; }
//template < >
//consteval auto typed_whitespace<char32_t>() { return U"/t/r/n "; }
IMPLEMENT_TYPED_STRING_LITERAL(whitespace, "\t\r\n ")


#include "acme/prototype/collection/array_range.h"
#include "acme/prototype/collection/comparable_eq_range.h"
#include "acme/prototype/collection/comparable_range.h"
#include "acme/prototype/collection/null_terminated_iterator.h"
#include "acme/prototype/collection/null_terminated_range.h"


template<typename ITERATOR_TYPE>
class string_range;



template < typename CHAR_POINTER >
struct end_of_line_and_next_line
{

   CHAR_POINTER end_of_line;
   CHAR_POINTER next_line;

};


//template < typename ITERATOR_TYPE >
//class scoped_string_base;






/// <summary>
/// class of operations on a range of characters
/// that are not changed. m_begin, m_end or m_erange should
/// only be changed in the returning object.
/// After construction, m_begin, m_end and m_erange members
/// should never be changed.
/// Contents should never be changed and null
/// termination is not set.
/// So ITERATOR_TYPE can be actually be const or not.
/// </summary>
/// <typeparam name="ITERATOR_TYPE"></typeparam>
template<typename ITERATOR_TYPE>
class const_string_range :
   //public ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >
   //public ::array_range < ::range < ITERATOR_TYPE > > >
   public ::character_range<ITERATOR_TYPE> {
public:

   using BASE_RANGE = ::character_range<ITERATOR_TYPE>;
   using RAW_CHARACTER_RANGE = typename BASE_RANGE::RAW_CHARACTER_RANGE;

   using BASE_RANGE = ::character_range<ITERATOR_TYPE>;
   using RAW_CHARACTER_RANGE = typename BASE_RANGE::RAW_CHARACTER_RANGE;


   //using BASE_RANGE = ::comparable_range < ::comparable_eq_range < ::array_range < ::range < ITERATOR_TYPE > > > >;

   using THIS_RANGE = ::const_string_range<ITERATOR_TYPE>;

   using STRING_RANGE = ::string_range<ITERATOR_TYPE>;


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

   using STRING = string_base < ITERATOR_TYPE >;

   using STRING_ARRAY = ::string_base_array < STRING, STRING, e_type_string_array >;


   //template<character_count n>
   //constexpr const_string_range(const CHARACTER(&s)[n]) :
   //   BASE_RANGE(no_initialize_t{})
   //{

   //   if constexpr (n >= 1)
   //   {

   //      if (s[n - 1] == CHARACTER{})
   //      {

   //         this->m_begin = s;
   //         this->m_end = s + n - 1;
   //         this->m_erange = e_range_null_terminated
   //            | e_range_string_literal;

   //         return;

   //      }

   //   }

   //   this->m_begin = s;
   //   this->m_end = s + n;
   //   this->m_erange = e_range_none | e_range_string_literal;

   //}


   template<primitive_integral INTEGRAL>
   constexpr const_string_range(const_iterator begin, INTEGRAL count) : BASE_RANGE((this_iterator)begin,
      (this_iterator)(begin + count)) {
   }

   const_string_range(no_initialize_t) : BASE_RANGE(no_initialize_t{}) {}

   const_string_range(nullptr_t) : BASE_RANGE(nullptr) {}

   const_string_range() {}

   template < typed_range < iterator > TYPED_RANGE >
   constexpr const_string_range(const TYPED_RANGE & range) 
      requires(!::std::is_same_v < TYPED_RANGE, THIS_RANGE >) :
      BASE_RANGE(range.m_begin, range.m_end, range.m_erange) { }

   constexpr const_string_range(const const_string_range & range) :
      BASE_RANGE(range.m_begin, range.m_end, range.m_erange) { }

   constexpr const_string_range(const_string_range && range) :
      BASE_RANGE(::transfer(range)) { }

   constexpr const_string_range(this_iterator begin, this_iterator end, enum_range erange = e_range_none) :
      BASE_RANGE(begin, end, erange) { }

   //explicit const_string_range(const ::atom& atom);

   const_string_range(const ::block& block);

   const_string_range(ITERATOR_TYPE psz) : 
      const_string_range(psz, string_safe_length(psz)) {}


   const_string_range start_count(character_count start, character_count count = -1)
   {

      if (start > this->size())
      {

         return {};

      }

      character_count end;

      if (count < 0)
      {

         end = this->size() + count + 1;

      }
      else
      {

         end = start + count;

      }

      if (end >= this->size())
      {

         return {};

      }

      auto erange = this->m_erange;

      if (start != 0)
      {

         if (end != 0)
         {

            erange = e_range_none;

         }
         else
         {

            erange = erange & ~e_range_string;

         }

      }
      else if (end != 0)
      {

         erange = e_range_none;

      }

      return {
         this->m_begin + start,
         this->m_begin + end,
      erange};

   }


   ::collection::count length() const {return this->size();}


   const_string_range & assign_bounded(ITERATOR_TYPE psz, character_count start, character_count count)
   {

      *this = ::_start_count_string_range(psz, start, count);

      return *this;

   }

   const_string_range subrange(character_count iFirst) const;

   const_string_range subrange(const_iterator p) const { return ::transfer(subrange(p, -1)); }
   const_string_range subrange(const_iterator p, character_count count) const { return ::transfer(subrange(p - this->begin(), count)); }



   template < primitive_integral START, primitive_integral COUNT >
   const_string_range subrange(START start, COUNT count) const;
   template < primitive_integral START >
   const_string_range subrange(START start, const_iterator p) const { return subrange(start, (p - this->m_begin) - start); }

   //auto this_range() const {return *this;}

   //auto subrange(character_count start, character_count count) const { auto range = *this; ::_start_count_range(range, start, count); return range; }

   template<int cCount, int wCount, int u16Count, int u32Count>
   static consteval auto typed_str_literal(const char(&c)[cCount], const wchar_t(&w)[wCount], const char16_t(&u16)[u16Count], const char32_t(&u32)[u32Count])
   {
      if constexpr (std::is_same_v<CHARACTER, char>)
         return c;
      else if constexpr (std::is_same_v<CHARACTER, wchar_t>)
         return w;
      else if constexpr (std::is_same_v<CHARACTER, char16_t>)
         return u16;
      else if constexpr (std::is_same_v<CHARACTER, char32_t>)
         return u32;
      else
         static_assert(sizeof(CHARACTER) == 0, "Unsupported character type");
   }


   //auto & last() { return ::get(this->end() - 1); }
   auto& last() const { return (const CHARACTER&) ::get(this->end() - 1); }

   auto& last(::collection::index i) const { return (const CHARACTER&) ::get(this->end() - 1 - i); }

   auto last_index() const { return this->size() - 1; }

   auto last_index(::collection::index i) const { return this->size() - 1 - i; }

   bool is_trimmed_empty() const;

   //void clear()
   //{
   //this->m_begin=nullptr;
   //this->m_end = nullptr;
   //this->m_erange = e_range_none;
   //}


   constexpr THIS_RANGE _begin_set(ITERATOR_TYPE pbegin) const
   {

      return pbegin == this->m_begin ?
         *this :
         THIS_RANGE{
            pbegin,
            this->m_end,
            (enum_range)this->m_erange & ~e_range_string
      }
      ;

   }


   constexpr THIS_RANGE begin_set(ITERATOR_TYPE pbegin) const
   {

      if (pbegin < this->m_begin)
      {

         throw "pbegin < this->m_begin";

      }
      else if (pbegin > this->m_end)
      {

         throw "pbegin > this->m_end";

      }

      return _begin_set(pbegin);

   }


   constexpr THIS_RANGE _end_set(ITERATOR_TYPE pend) const
   {

      return pend == this->m_end ?
         *this :
         THIS_RANGE{
            this->m_begin,
               pend,
               e_range_none
      }
      ;

   }


   constexpr THIS_RANGE end_set(ITERATOR_TYPE pend) const
   {

      if (pend < this->m_begin)
      {

         throw "pend < this->m_begin";

      }
      else if (pend > this->m_end)
      {

         throw "pend > this->m_end";

      }

      return _end_set(pend);

   }


   template < primitive_integral START, primitive_integral COUNT>
   STRING_RANGE operator()(START start, COUNT count) const;
   template < primitive_integral START, typed_character_pointer < const_string_range < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   STRING_RANGE operator()(START start, CHARACTER_POINTER end) const
   {
      return ::_start_end_range(STRING_RANGE(*this), start, end);
   }
   template < typed_character_pointer < typename const_string_range < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   STRING_RANGE operator()(CHARACTER_POINTER start) const
   {
       return STRING_RANGE(start, this->end());
   }
   template < primitive_integral START >
   STRING_RANGE operator()(START start) const;
   STRING_RANGE operator()() const;

   template < primitive_integral START, primitive_integral COUNT>
   auto substr(START start, COUNT count) const { return this->operator()(start, count); }
   template < primitive_integral START, typed_character_pointer < typename const_string_range < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   auto substr(START start, CHARACTER_POINTER end) const { return this->operator()(start, end); }
   template < typed_character_pointer < typename const_string_range < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   auto substr(CHARACTER_POINTER start) const { return this->operator()(start); }
   template < primitive_integral START >
   auto substr(START start) const { return this->operator()(start); }
   //STRING_RANGE operator()() const;

   ::end_of_line_and_next_line < const CHARACTER* > end_of_line_and_next_line() const
   {

      ::end_of_line_and_next_line < const CHARACTER* > pair;

      pair.end_of_line = this->find_first_character_in("\r\n\0");

      pair.next_line = pair.end_of_line;

      if (!*pair.next_line)
      {

         pair.next_line = nullptr;

      }
      else if (*pair.next_line == '\r')
      {

         pair.next_line++;

         if (*pair.next_line == '\n')
         {

            pair.next_line++;

         }

      }
      else if (*pair.next_line == '\n')
      {

         pair.next_line++;

      }
      else
      {

         throw_exception(error_failed);

      }

      return pair;

   }


   bool has_character() const { return !this->is_empty(); }

   inline bool is_empty() const noexcept { return ::is_null(this->m_begin) || ::is_null(this->m_end) || this->m_end <= this->m_begin || *this->m_begin == '\0'; }
   inline memsize length_in_bytes() const { return this->size() * sizeof(CHARACTER); }

   //inline bool has_character() const noexcept { return !this->is_empty(); }
   inline character_count get_upper_bound(character_count i = -1) const noexcept { return this->size() + i; }

   operator ::block() const { return { (unsigned char*)this->m_begin, this->length_in_bytes() }; }

   inline CHARACTER character_at(character_count i) const { return this->data()[i]; }





   //inline CHARACTER *data() { return (CHARACTER *) this->begin(); }

   inline const CHARACTER* data() const { return this->begin(); }

   inline operator const CHARACTER* () const { return this->data(); }

   //inline operator CHARACTER *() { return this->data(); }

   //inline const CHARACTER *ptr_at(::collection::index i) { return this->data() + i; }

   inline const CHARACTER* address_at(::collection::index i) const { return this->data() + i; }

   //inline const CHARACTER *reverse_ptr(::collection::index i) { return this->data() + this->size() + i; }

   inline const CHARACTER* rear_address(::collection::index i) const { return this->end() + i; }

   inline const CHARACTER& operator[](::collection::index i) const { return this->data()[i]; }

   character_count index_of(const CHARACTER* p) const { return ::index_of(p, data()); }


   const_string_range trimmed_left() const
   {

      return _begin_set(skip_any_character_in(typed_whitespace<CHARACTER>()));

   }


   const_string_range trimmed_right() const
   {

      return _end_set(rear_skip_any_character_in(typed_whitespace<CHARACTER>()));

   }


   const_string_range trimmed() const
   {

      return trimmed_right().trimmed_left();

   }



   //    string_range &operator=(const THIS_RANGE &range)
   //    {
   //       BASE_RANGE::operator=(range);
   //       return *this;
   //    }
   //
   //    string_range &operator=(string_range &&range) {
   //       BASE_RANGE::operator=(::transfer(range));
   //       return *this;
   //    }

   //    string_range &operator=(const atom &atom);
   //
   //    string_range &operator=(const block &block);
   //

   THIS_RANGE get_utf8_char() const;


   //::std::strong_ordering order(const string_range &range) const noexcept;
   //using NATURAL_POINTER::order;

   //::std::strong_ordering order(const SCOPED_STRING &range) const noexcept;
   //::std::strong_ordering case_insensitive_order(const SCOPED_STRING& range) const noexcept;

   ::std::strong_ordering collate(const SCOPED_STRING& range) const noexcept;

   ::std::strong_ordering case_insensitive_collate(const SCOPED_STRING& range) const noexcept;

   //::std::strong_ordering order(const SCOPED_STRING &range, character_count n) const noexcept;

   //::std::strong_ordering case_insensitive_order(const SCOPED_STRING &range, character_count n) const noexcept;

   //::std::strong_ordering collate(const SCOPED_STRING &range, character_count n) const noexcept;

   //::std::strong_ordering case_insensitive_collate(const SCOPED_STRING &range, character_count n) const noexcept;

   //::std::strong_ordering order(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;

   //::std::strong_ordering case_insensitive_order(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;

   //::std::strong_ordering collate(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;

   //::std::strong_ordering
   //case_insensitive_collate(character_count start, character_count count, const SCOPED_STRING &range) const noexcept;

   //::std::strong_ordering
   //order(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2, character_count iCount2) const noexcept;

   //::std::strong_ordering
   //case_insensitive_order(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2,
   //                       character_count iCount2) const noexcept;

   //::std::strong_ordering
   //collate(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2, character_count iCount2) const noexcept;

   //::std::strong_ordering
   //case_insensitive_collate(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2,
   //                         character_count iCount2) const noexcept;

   //inline int operator<=>(const string_range &range) const { return order(range); }
   //inline bool operator==(const string_range &range) const { return size() != range.size() ? false : !order(range); }
   //inline bool operator>(const string_range &range) const { return order(ansistr) > 0; }
   //inline bool operator<(const string_range &range) const { return order(ansistr) < 0; }
   //inline bool operator!=(const string_range &range) const { return !operator ==(ansistr); }
   //inline bool operator>=(const string_range &range) const { return !operator <(ansistr); }
   //inline bool operator<=(const string_range &range) const { return !operator >(ansistr); }


   //inline bool operator==(const string_range &range) const { return order(ansistr) == 0; }
   //inline bool operator>(const string_range &range) const { return order(ansistr) > 0; }
   //inline bool operator<(const string_range &range) const { return order(ansistr) < 0; }
   //inline bool operator!=(const string_range &range) const { return !operator ==(ansistr); }
   //inline bool operator>=(const string_range &range) const { return !operator <(ansistr); }
   //inline bool operator<=(const string_range &range) const { return !operator >(ansistr); }

   inline bool operator==(const THIS_RANGE& range) const { return this->equals(range); }
   //inline ::std::strong_ordering operator<=>(const SCOPED_STRING &range) const { return this->order(range); }




   using BASE_RANGE::_order;

   constexpr ::std::strong_ordering _order(const SCOPED_STRING& range) const
   {

      return _order(range, ::comparison::comparison<ITEM>());

   }


   using BASE_RANGE::order;

   //constexpr ::std::strong_ordering order(const SCOPED_STRING& range) const noexcept;


   constexpr ::std::strong_ordering operator<=>(const SCOPED_STRING& range) const {

      return this->order(range);

   }


   template < typed_character_range < CHARACTER > CHARACTER_RANGE >
   constexpr bool equals(const CHARACTER_RANGE& range) const
   {

      auto sizeRange = this->size();

      return sizeRange != range.size() ? false :
         (sizeRange <= 0 ?
            true :
            _string_count_compare(this->m_begin, range.m_begin, sizeRange) == 0
            );

   }


   template < typed_character_pointer < CHARACTER > CHARACTER_POINTER >
   constexpr bool equals(CHARACTER_POINTER psz) const
   {

      auto sizeThis = this->size();

      return _string_count_compare(this->m_begin, psz, sizeThis) == 0
         && psz[sizeThis] == CHARACTER{};

   }


   constexpr bool equals(const SCOPED_STRING& scopedstr) const
   {

      auto sizeRange = this->size();

      return sizeRange != scopedstr.size() ? false :
         (sizeRange <= 0 ?
            true :
            _string_count_compare(this->m_begin, scopedstr.m_begin, sizeRange) == 0
            );

   }


   template < typed_character_range < CHARACTER > CHARACTER_RANGE >
   constexpr bool case_insensitive_equals(const CHARACTER_RANGE& range) const
   {

      auto sizeRange = this->size();

      return sizeRange != range.size() ? false :
         (sizeRange <= 0 ?
            true :
            _case_insensitive_string_count_compare(this->m_begin, range.m_begin, sizeRange) == 0
            );

   }


   template < typed_character_pointer < CHARACTER > CHARACTER_POINTER >
   constexpr bool case_insensitive_equals(CHARACTER_POINTER psz) const
   {

      auto sizeThis = this->size();

      return this->is_empty()?
         (::is_empty(psz) ? true :
         false) :
         (::is_empty(psz) ? false :
            (_case_insensitive_string_count_compare(this->m_begin, psz, sizeThis) == 0
            && psz[sizeThis] == CHARACTER{})
               );

   }


   constexpr bool case_insensitive_equals(const SCOPED_STRING& scopedstr) const
   {

      auto sizeRange = this->size();

      return sizeRange != scopedstr.size() ? false :
         (sizeRange <= 0 ?
            true :
            _case_insensitive_string_count_compare(this->m_begin, scopedstr.m_begin, sizeRange) == 0
            );

   }



   template < typed_character_range < CHARACTER > CHARACTER_RANGE >
   constexpr ::std::strong_ordering order(const CHARACTER_RANGE& range) const
   {

      auto sizeThis = this->size();

      ::std::strong_ordering ordering(1<=>1);

      return this->is_empty() ?
         (range.is_empty() ? ::std::strong_ordering::equal :
            ::std::strong_ordering::less) :
         (range.is_empty() ? ::std::strong_ordering::greater : 
            ((ordering = _string_count_compare(this->m_begin, range.begin(), sizeThis)) == 0 ?
               sizeThis <=> range.size() : ordering));

   }


   template < typed_character_pointer < CHARACTER > CHARACTER_POINTER >
   constexpr ::std::strong_ordering order(CHARACTER_POINTER psz) const
   {

      auto sizeThis = this->size();

      ::std::strong_ordering ordering(1<=>1);

      return this->is_empty() ?
         (::is_empty(psz) ? ::std::strong_ordering::equal :
            ::std::strong_ordering::less) :
         (::is_empty(psz) ? ::std::strong_ordering::greater :
            ((ordering = _string_count_compare(this->m_begin, psz, sizeThis)) == 0 ?
               (psz[sizeThis] == CHARACTER{} ?
                  ::std::strong_ordering::equal :
                  ::std::strong_ordering::less)
               : ordering));
   }


   constexpr ::std::strong_ordering order(const SCOPED_STRING& scopedstr) const
   {

      auto sizeThis = this->size();

      ::std::strong_ordering ordering(1<=>1);

      return this->is_empty() ?
         (scopedstr.is_empty() ? ::std::strong_ordering::equal :
            ::std::strong_ordering::less) :
         (scopedstr.is_empty() ? ::std::strong_ordering::greater : 
            ((ordering = _string_count_compare(this->m_begin, scopedstr.m_begin, sizeThis)) == 0 ?
               sizeThis <=> scopedstr.size() : ordering));

   }


   template < typed_character_range < CHARACTER > CHARACTER_RANGE >
   constexpr ::std::strong_ordering case_insensitive_order(const CHARACTER_RANGE& range) const
   {

      auto sizeThis = this->size();

      ::std::strong_ordering ordering(1<=>1);

      return this->is_empty() ?
         (range.is_empty() ? ::std::strong_ordering::equal :
            ::std::strong_ordering::less) :
         (range.is_empty() ? ::std::strong_ordering::greater :
            ((ordering = _case_insensitive_string_count_compare(this->m_begin, range.begin(), sizeThis)) == 0 ?
               sizeThis <=> range.size() : ordering));

   }


   template < typed_character_pointer < CHARACTER > CHARACTER_POINTER >
   constexpr ::std::strong_ordering case_insensitive_order(CHARACTER_POINTER psz) const
   {

      auto sizeThis = this->size();

      ::std::strong_ordering ordering(1<=>1);

      return this->is_empty() ?
         (::is_empty(psz) ? ::std::strong_ordering::equal :
            ::std::strong_ordering::less) :
         (::is_empty(psz) ? ::std::strong_ordering::greater :
            ((ordering = _case_insensitive_string_count_compare(this->m_begin, psz, sizeThis)) == 0 ?
               (psz[sizeThis] == CHARACTER{}?
                  ::std::strong_ordering::equal :
                  ::std::strong_ordering::less)
               : ordering));

   }


   constexpr ::std::strong_ordering case_insensitive_order(const SCOPED_STRING& scopedstr) const
   {

      auto sizeThis = this->size();

      ::std::strong_ordering ordering(1<=>1);

      return this->is_empty() ?
         (scopedstr.is_empty() ? ::std::strong_ordering::equal :
            ::std::strong_ordering::less) :
         (scopedstr.is_empty() ? ::std::strong_ordering::greater :
            ((ordering = _case_insensitive_string_count_compare(this->m_begin, scopedstr.m_begin, sizeThis)) == 0 ?
               sizeThis <=> scopedstr.size() : ordering));

   }



   //using BASE_RANGE::_equals;

   //constexpr bool _equals(const SCOPED_STRING& range) const {

   //   return this->binary_equals(range);

   //}


   //using BASE_RANGE::equals;

   //constexpr bool equals(const SCOPED_STRING& range) const {

   //   return this->binary_equals(range);

   //}

   //constexpr bool case_insensitive_equals(const SCOPED_STRING& range) const noexcept {

   //   return this->equals(range, ::comparison::case_insensitive<ITEM>());

   //}

   //bool equals(const SCOPED_STRING &range, character_count n) const noexcept {

   //   return this->equals_start_count(range, 0, n, ::comparison::comparison<ITEM>());

   //}

   //bool case_insensitive_equals(const SCOPED_STRING &range, character_count n) const noexcept {

   //   return this->equals_start_count(range, 0, n, ::comparison::case_insensitive<ITEM>());

   //}

   //bool equals(character_count start, character_count count, const SCOPED_STRING &range) const noexcept {

   //   return this->equals_start_count(range, start, count, ::comparison::comparison<ITEM>());

   //}

   //bool case_insensitive_equals(character_count start, character_count count, const SCOPED_STRING &range) const noexcept {

   //   return this->equals_start_count(range, start, count, ::comparison::case_insensitive<ITEM>());

   //}

   //bool
   //equals(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2, character_count iCount2) const noexcept {

   //   return this->equals_start_count(range.start_count(iStart2, iCount2), start, count,
   //                                   ::comparison::comparison<ITEM>());

   //}

   //bool case_insensitive_equals(character_count start, character_count count, const SCOPED_STRING &range, character_count iStart2,
   //                             character_count iCount2) const noexcept {

   //   return this->equals_start_count(range.start_count(iStart2, iCount2), start, count,
   //                                   ::comparison::case_insensitive<ITEM>());

   //}



//   using BASE_RANGE::_equals_start;
//
//   constexpr bool _equals_start(const SCOPED_STRING & range, memsize start) const
//   {
//
//      return this->_equals_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::equals_start;
//
//   constexpr bool equals_start(const SCOPED_STRING & range, memsize start) const
//   {
//
//      return this->equals_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_equals_start_count;
//
//   constexpr bool _equals_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
//   {
//
//      return this->_equals_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::equals_start_count;
//
//   constexpr bool equals_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
//   {
//
//      return this->equals_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//

   using BASE_RANGE::_find;

   constexpr const_iterator _find(const SCOPED_STRING& range) const {

      return this->_find(range, ::comparison::comparison<ITEM>());

   }


   using BASE_RANGE::find;

   constexpr const_iterator find(const SCOPED_STRING& range) const {

      return this->find(range, ::comparison::comparison<ITEM>());

   }
   constexpr character_count find_index(const SCOPED_STRING& range, character_count start = 0) const
   {

      return this->index_of(start <= 0 ? this->find(range) : (*this)(start).find(range));

   }
   constexpr character_count find_index(CHARACTER ch, character_count start = 0) const
   {

      return this->index_of(start <= 0 ? this->find(ch) : (*this)(start).find(ch));

   }


   //   using BASE_RANGE::_find_start;
   //
   //   constexpr const_iterator _find_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->_find_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::find_start;
   //
   //   constexpr const_iterator find_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->find_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_find_start_count;
   //
   //   constexpr const_iterator _find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::find_start_count;
   //
   //   constexpr const_iterator find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }


   using BASE_RANGE::_rear_find;

   constexpr const_iterator _rear_find(const SCOPED_STRING& range, const_iterator end = nullptr) const
   {

      return (*this)(0, ::is_null(end) ? this->end() : end)._rear_find(range, ::comparison::comparison<ITEM>());

   }


   using BASE_RANGE::rear_find;

   constexpr const_iterator rear_find(const SCOPED_STRING& range, const_iterator end = nullptr) const
   {

      return (*this)(0, ::is_null(end) ? this->end() : end).rear_find(range, ::comparison::comparison<ITEM>());

   }

   constexpr character_count _rear_find_index(const SCOPED_STRING& range, character_count end = -1) const
   {

      return this->index_of((*this)(0, end >= 0 ? end : this->size() + end + 1)._rear_find(range));

   }


   constexpr character_count rear_find_index(const SCOPED_STRING& range, character_count end = -1) const
   {

      return this->index_of((*this)(0, end >= 0 ? end : this->size() + end + 1).rear_find(range));

   }


   constexpr const_iterator _rear_find(CHARACTER character, const_iterator end = nullptr) const
   {

      return (*this)(0, ::is_null(end) ? this->end() : end).rear_find(character, ::comparison::comparison<ITEM>());

   }


   constexpr const_iterator rear_find(CHARACTER character, const_iterator end = nullptr) const
   {

      return (*this)(0, ::is_null(end) ? this->end() : end).rear_find(character, ::comparison::comparison<ITEM>());

   }


   constexpr character_count _rear_find_index(CHARACTER character, character_count end = -1) const
   {

      return this->index_of((*this)(0, end >= 0 ? end : this->size() + end + 1)._rear_find(character));

   }


   constexpr character_count rear_find_index(CHARACTER character, character_count end = -1) const
   {

      return this->index_of((*this)(0, end >= 0 ? end : this->size() + end + 1).rear_find(character));

   }


   const_iterator case_insensitive_find(const SCOPED_STRING& scopedstr) const RELEASENOTHROW
   {

      return this->find(scopedstr, ::comparison::case_insensitive<ITEM>());

   }


   character_count case_insensitive_find_index(const SCOPED_STRING& scopedstr) const RELEASENOTHROW
   {

      return this->index_of(case_insensitive_find(scopedstr));

   }


   character_count case_insensitive_find_index(const SCOPED_STRING& scopedstr, character_count start) const RELEASENOTHROW { return this->index_of((*this)(start).case_insensitive_find(scopedstr)); }


   constexpr const_iterator _case_insensitive_rear_find(const SCOPED_STRING& scopedstr) const
   {

      return this->_rear_find(scopedstr, ::comparison::case_insensitive<ITEM>());

   }


   character_count _case_insensitive_rear_find_index(const SCOPED_STRING& scopedstr, character_count end = -1) const RELEASENOTHROW
   {

      return this->index_of((*this)(0, end >= 0 ? end : this->size() + end + 1)._case_insensitive_rear_find(scopedstr));

   }


   constexpr const_iterator case_insensitive_rear_find(const SCOPED_STRING& scopedstr) const
   {

      return this->rear_find(scopedstr, ::comparison::case_insensitive<ITEM>());

   }


   character_count case_insensitive_rear_find_index(const SCOPED_STRING& scopedstr, character_count end = -1) const RELEASENOTHROW
   {


      return this->index_of((*this)(0, end >= 0 ? end : this->size() + end + 1).case_insensitive_rear_find(scopedstr));

   }


   //   using BASE_RANGE::_rear_find_start;
   //
   //   constexpr const_iterator _rear_find_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->_rear_find_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::rear_find_start;
   //
   //   constexpr const_iterator rear_find_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->rear_find_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_rear_find_start_count;
   //
   //   constexpr const_iterator _rear_find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::rear_find_start_count;
   //
   //   constexpr const_iterator rear_find_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }


   using BASE_RANGE::_find_first_character_in;

   constexpr const_iterator _find_first_character_in(const SCOPED_STRING& range) const {

      return this->_find_first_character_in(range, ::comparison::comparison<ITEM>());

   }

   constexpr character_count _find_first_character_in_index(const SCOPED_STRING& range) const {
      return this->index_of(_find_first_character_in(range));
   }

   using BASE_RANGE::find_first_character_in;

   constexpr const_iterator find_first_character_in(const SCOPED_STRING& range) const {

      return this->find_first_character_in(range, ::comparison::comparison<ITEM>());

   }
   constexpr character_count find_first_character_in_index(const SCOPED_STRING& range, ::character_count start = 0) const {
      return this->index_of((*this)(start).find_first_character_in(range));
   }


   // Convert the string_base < ITERATOR_TYPE > to lowercase
   //template < typename ITERATOR_TYPE >
   string_base < ITERATOR_TYPE > lowered() const;
   string_base < ITERATOR_TYPE > uppered() const;


   //   using BASE_RANGE::_find_first_character_in_start;
   //
   //   constexpr const_iterator _find_first_character_in_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->_find_first_character_in_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::find_first_character_in_start;
   //
   //   constexpr const_iterator find_first_character_in_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->find_first_character_in_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_find_first_character_in_start_count;
   //
   //   constexpr const_iterator _find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::find_first_character_in_start_count;
   //
   //   constexpr const_iterator find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }


   //constexpr ITERATOR_TYPE skip_any_character_in(const SCOPED_STRING& range) const 
   //{

   //   return this->_skip_any_character_in(range, ::comparison::comparison<ITEM>());

   //}


   //constexpr character_count skip_any_character_in_index(const SCOPED_STRING& range, ::character_count start = 0) const 
   //{

   //   return this->index_of((*this)(start).skip_any_character_in(range).begin());

   //}


   //using BASE_RANGE::skip_any_character_in;

   //static constexpr bool
   //   _static_initialize_skip_any_character_in(THIS_RANGE & rangeRetur, const THIS_RANGE& range, const THIS_RANGE& rangeBlock) noexcept
   //{



   //   return false;

   //}


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr ITERATOR_TYPE
      _static_skip_any_character_in(THIS_RANGE range, const THIS_RANGE& rangeBlock, EQUALITY equality) noexcept
   {

      ITERATOR_TYPE pbegin = range.m_begin;

      do
      {

         auto pBlockScan = rangeBlock.begin();

         while (true)
         {

            if (equality.equals(*pbegin, *pBlockScan))
            {

               // found a matching item...
               // continue skip_any_character_inning...

               break;

            }

            pBlockScan++;

            if (rangeBlock.is_end(pBlockScan))
            {

               // Iterated through all pBlock items
               // and didn't find any that match *p

               // so p is the end of the skip_any_character_in for matching items...

               return pbegin;

            }

         };

         pbegin++;

      } while (!range.is_end(pbegin));

      // reached end of the skip_any_character_inning range...
      // each skip_any_character_inned item matched some item in range...
      // return address immediately after end of skip_any_character_inning...

      return pbegin;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr ITERATOR_TYPE
      static_skip_any_character_in(const THIS_RANGE& range, const THIS_RANGE& rangeBlock, EQUALITY equality) noexcept
   {

      if (range.is_empty())
      {

         return range.m_begin;

      }

      if (rangeBlock.is_empty())
      {

         return range.m_end;

      }

      return _static_skip_any_character_in(range, rangeBlock, equality);

   }


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr THIS_RAW_RANGE _skip_any_character_in(const THIS_RAW_RANGE& rangeBlock, EQUALITY equality) const
   //{

   //   return _static_skip_any_character_in(*this, rangeBlock, equality);

   //}


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr const_iterator skip_any_character_in(const THIS_RAW_RANGE& rangeBlock, EQUALITY equality) const
   //{

   //   return static_skip_any_character_in(*this, rangeBlock, equality);

   //}

   template<::comparison::equality<ITEM> EQUALITY>
   constexpr ITERATOR_TYPE _skip_any_character_in(const THIS_RANGE& rangeBlock, EQUALITY equality) const
   {

      return static_skip_any_character_in(*this, rangeBlock, equality);

   }


   constexpr ITERATOR_TYPE skip_any_character_in(const SCOPED_STRING& range) const {

      return this->_skip_any_character_in(range, ::comparison::comparison<ITEM>());

   }


   //   using BASE_RANGE::_skip_any_character_in_start;
   //
   //   constexpr const_iterator _skip_any_character_in_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->_skip_any_character_in_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::skip_any_character_in_start;
   //
   //   constexpr const_iterator skip_any_character_in_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->skip_any_character_in_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_skip_any_character_in_start_count;
   //
   //   constexpr const_iterator _skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::skip_any_character_in_start_count;
   //
   //   constexpr const_iterator skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }


   //using BASE_RANGE::_rear_skip_any_character_in;

   constexpr ITERATOR_TYPE rear_skip_any_character_in(const THIS_RANGE& range) const noexcept
   {

      return static_rear_skip_any_character_in(*this, range, ::comparison::comparison<ITEM>());

   }


   //constexpr THIS_RANGE rear_skip_any_character_in(const SCOPED_STRING& range) const noexcept {

   //   return this->rear_skip_any_character_in(range, ::comparison::comparison<ITEM>());

   //}


   //static constexpr bool
   //   _initialize_rear_skip_any_character_in(const_iterator& p, const THIS_RAW_RANGE& range, const THIS_RAW_RANGE& rangeBlock) noexcept
   //{

   //   if (range.is_empty())
   //   {

   //      p = range.end() - 1;

   //      return true;

   //   }

   //   if (range.is_empty())
   //   {

   //      p = range.end() - 1;

   //      return true;

   //   }

   //   return false;

   //}


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr ITERATOR_TYPE
      _static_rear_skip_any_character_in(THIS_RANGE range, const THIS_RANGE& rangeBlock, EQUALITY equality) noexcept
   {

      ITERATOR_TYPE pend = range.m_end;

      pend--;

      do
      {

         auto pBlockScan = rangeBlock.begin();

         while (true)
         {

            if (equality.equals(*pend, *pBlockScan))
            {

               // found a matching item...
               // continue skip_any_character_inning...

               break;

            }

            pBlockScan++;

            if (rangeBlock.is_end(pBlockScan))
            {

               // Iterated through all pBlock items
               // and didn't find any that match *p

               // so p is the end of the skip_any_character_in for matching items...

               return pend + 1;

            }

         };

         pend--;

      } while (!range.is_before_begin(pend));

      // reached end of the skip_any_character_inning range...
      // each skip_any_character_inned item matched some item in range...
      // return address immediately after end of skip_any_character_inning...

      return pend + 1;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr ITERATOR_TYPE
      static_rear_skip_any_character_in(THIS_RANGE range, const THIS_RANGE& rangeBlock, EQUALITY equality) noexcept
   {

      //const_iterator p;

      //if (_initialize_rear_skip_any_character_in(p, range, rangeBlock))
      //{

      //   return p;

      //}

      if (range.is_empty())
      {

         //p = range.end() - 1;

         //return true;

         return range.m_end;

      }

      if (rangeBlock.is_empty())
      {

         //p = range.end() - 1;

         return range.m_begin;

      }

      return _static_rear_skip_any_character_in(range, rangeBlock, equality);

   }


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr ITERATOR_TYPE _rear_skip_any_character_in(const THIS_RAW_RANGE& rangeBlock, EQUALITY equality) const
   //{

   //   return _static_rear_skip_any_character_in(*this, rangeBlock, equality);

   //}


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr ITERATOR_TYPE rear_skip_any_character_in(const THIS_RANGE& rangeBlock, EQUALITY equality) const
   //{

   //   return static_rear_skip_any_character_in(*this, rangeBlock, equality);

   //}


   //   using BASE_RANGE::rear_skip_any_character_in_start;
   //
   //   constexpr const_iterator rear_skip_any_character_in_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->rear_skip_any_character_in_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_rear_skip_any_character_in_start_count;
   //
   //   constexpr const_iterator _rear_skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_rear_skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::rear_skip_any_character_in_start_count;
   //
   //   constexpr const_iterator rear_skip_any_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->rear_skip_any_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }

   using BASE_RANGE::_skip;

   constexpr const_iterator _skip(CHARACTER item) const {

      return this->_skip(item, ::comparison::comparison<ITEM>());

   }


   using BASE_RANGE::skip;

   constexpr const_iterator skip(CHARACTER item) const {

      return this->skip(item, ::comparison::comparison<ITEM>());

   }


   //   using BASE_RANGE::_skip_start;
   //
   //   constexpr const_iterator _skip_start(const ITEM & item, memsize start) const
   //   {
   //
   //      return this->_skip_start(item, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::skip_start;
   //
   //   constexpr const_iterator skip_start(const ITEM & item, memsize start) const
   //   {
   //
   //      return this->skip_start(item, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_skip_start_count;
   //
   //   constexpr const_iterator _skip_start_count(const ITEM & item, memsize start, memsize count) const
   //   {
   //
   //      return this->_skip_start_count(item, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::skip_start_count;
   //
   //   constexpr const_iterator skip_start_count(const ITEM & item, memsize start, memsize count) const
   //   {
   //
   //      return this->skip_start_count(item, start, count, ::comparison::comparison < ITEM >());
   //
   //   }




       //using BASE_RANGE::_rear_find;

       //constexpr const_iterator _rear_find(ARG_ITEM item) const {

       //   return this->_rear_find(item, ::comparison::comparison<ITEM>());

       //}


       //using BASE_RANGE::rear_find;

       //constexpr const_iterator rear_find(ARG_ITEM item) const {

       //   return this->rear_find(item, ::comparison::comparison<ITEM>());

       //}

       //constexpr character_count _rear_find_index(ARG_ITEM item) const {

       //   return this->index_of(this->_rear_find(item));

       //}


       //constexpr character_count rear_find_index(ARG_ITEM item) const {

       //   return this->index_of(this->rear_find(item));

       //}


   //   using BASE_RANGE::_rear_find_item_start;
   //
   //   constexpr const_iterator _rear_find_item_start(const ITEM & item, memsize start) const
   //   {
   //
   //      return this->_rear_find_item_start(item, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::rear_find_item_start;
   //
   //   constexpr const_iterator rear_find_item_start(const ITEM & item, memsize start) const
   //   {
   //
   //      return this->rear_find_item_start(item, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_rear_find_item_start_count;
   //
   //   constexpr const_iterator _rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   //   {
   //
   //      return this->_rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::rear_find_item_start_count;
   //
   //   constexpr const_iterator rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   //   {
   //
   //      return this->rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());
   //
   //   }



   using BASE_RANGE::_rear_find_first_character_in;

   constexpr const_iterator _rear_find_first_character_in(const SCOPED_STRING& range) const noexcept {

      return this->_rear_find_first_character_in(range, ::comparison::comparison<ITEM>());

   }


   using BASE_RANGE::rear_find_first_character_in;

   constexpr const_iterator rear_find_first_character_in(const SCOPED_STRING& range) const noexcept {

      return this->rear_find_first_character_in(range, ::comparison::comparison<ITEM>());

   }


   //   using BASE_RANGE::rear_find_first_character_in_start;
   //
   //   constexpr const_iterator rear_find_first_character_in_start(const SCOPED_STRING & range, memsize start) const
   //   {
   //
   //      return this->rear_find_first_character_in_start(range, start, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::_rear_find_first_character_in_start_count;
   //
   //   constexpr const_iterator _rear_find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->_rear_find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }
   //
   //
   //   using BASE_RANGE::rear_find_first_character_in_start_count;
   //
   //   constexpr const_iterator rear_find_first_character_in_start_count(const SCOPED_STRING & range, memsize start, memsize count) const
   //   {
   //
   //      return this->rear_find_first_character_in_start_count(range, start, count, ::comparison::comparison < ITEM >());
   //
   //   }


   using BASE_RANGE::_begins;

   constexpr bool _begins(const SCOPED_STRING& range) const {

      return this->_begins(range, ::comparison::comparison<ITEM>());

   }


   using BASE_RANGE::begins;

   constexpr bool begins(const SCOPED_STRING& range) const {

      return this->begins(range, ::comparison::comparison<ITEM>());

   }


   ::collection::count begins_count(bool(*character_is_function)(CHARACTER character)) const
   {

      ::collection::count c = 0;

      while (character_is_function(this->begin()[c])) c++;

      return c;

   }


   //    ::collection::count consume(bool(*character_is_function)(CHARACTER character), character_count minimum_count);


   //    ::collection::count consume_spaces(character_count minimum_count = 0)
   //    {
   //
   //       return consume(&character_isspace, minimum_count);
   //
   //    }


   //   ::string_base < ITERATOR_TYPE > consume_quoted_value();
   //
   //   ::string_base < ITERATOR_TYPE > consume_token_until_any_character_in(const SCOPED_STRING & scopedstrCharacters = 0, bool bReturnSeparator = false, bool bSkipAnyCharactersIn = true);
   //
   //    bool defer_consume(const SCOPED_STRING & range)
   //    {
   //
   //       if (!this->begins(range))
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       this->begin() += range.size();
   //
   //       return true;
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



   using BASE_RANGE::_ends;

   constexpr bool _ends(const SCOPED_STRING& range) const {

      return this->_ends(range, ::comparison::comparison<ITEM>());

   }


   using BASE_RANGE::ends;

   constexpr bool ends(const SCOPED_STRING& range) const {

      return this->ends(range, ::comparison::comparison<ITEM>());

   }


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




   template<typename PRED>
   bool is_every_char(PRED pred) const {

      for (::collection::index i = 0; i < this->length(); i++) {

         if (!pred(this->operator[](i))) {

            return false;

         }

      }

      return true;

   }


   template<typename NUMBER>
   NUMBER& translate_index(NUMBER& number) const {

      if (number < 0) {

         number += this->size() + 1;

         if (number < 0) {

            number = 0;

         }

      }
      else if (number > this->size()) {

         number = this->size();

      }

      return number;

   }


   //inline bool contains(CHARACTER ch = 0) const;
   inline bool contains(const SCOPED_STRING& scopedstr = 0) const;

   //inline bool contains(const string_base &str = 0) const;
   inline bool contains(CHARACTER ch) const { return ::is_set(find(ch)); }

   inline bool
      contains(const SCOPED_STRING& scopedstr, const CHARACTER** ppszBeg, const CHARACTER** ppszEnd = nullptr) const;
   //inline bool contains(const string_base &str, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;

   template<primitive_array STRING_ARRAY>
   inline bool contains_any(const STRING_ARRAY& stra) const;

   template<primitive_array STRING_ARRAY>
   inline bool contains_all(const STRING_ARRAY& stra) const;

   //inline bool case_insensitive_contains(CHARACTER ch = 0) const;
   inline bool case_insensitive_contains(const SCOPED_STRING& scopedstr = 0) const;

   //inline bool case_insensitive_contains(const string_base &str = 0) const;
   //inline bool case_insensitive_contains(CHARACTER ch, const CHARACTER ** ppszBeg) const;
   inline bool
      case_insensitive_contains(const SCOPED_STRING& scopedstr, const CHARACTER** ppszBeg, const CHARACTER** ppszEnd = nullptr) const;
   //inline bool case_insensitive_contains(const string_base &str, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;

   template<primitive_array STRING_ARRAY>
   inline bool case_insensitive_contains_at_least_one_of(const STRING_ARRAY& stra) const;

   template<primitive_array STRING_ARRAY>
   inline bool case_insensitive_contains_all(const STRING_ARRAY& stra) const;


   //inline bool unicode_case_insensitive_contains(CHARACTER ch = 0) const;
   inline bool unicode_case_insensitive_contains(const SCOPED_STRING& scopedstr = 0) const;

   //inline bool unicode_case_insensitive_contains(const string_base &str = 0) const;
   //inline bool unicode_case_insensitive_contains(CHARACTER ch, const CONST_STRING_RANGE &* ppszBeg) const;
   inline bool
      unicode_case_insensitive_contains(const SCOPED_STRING& scopedstr, const CHARACTER** ppszBeg, const CHARACTER** ppszEnd = nullptr) const;
   //inline bool unicode_case_insensitive_contains(const string_base &str, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;

   template<primitive_array STRING_ARRAY>
   inline bool unicode_case_insensitive_contains_at_least_one_of(const STRING_ARRAY& stra) const;

   template<primitive_array STRING_ARRAY>
   inline bool unicode_case_insensitive_contains_all(const STRING_ARRAY& stra) const;


   template<::comparison::equality<CHARACTER> EQUALITY>
   ::collection::count _occurrence_count_of(const SCOPED_STRING& scopedstr, EQUALITY equality) const {

      character_count nLen = scopedstr.size();

      character_count count = 0;

      auto range = (*this)();

      while ((range.begin(range.find(scopedstr, equality))) != nullptr) {

         count++;

         range.begin() += nLen;

      }

      return count;

   }


   ::collection::count occurrence_count_of(const SCOPED_STRING& scopedstr = 0) const {

      return _occurrence_count_of(scopedstr, ::comparison::comparison<CHARACTER>());

   }


   ::collection::count case_insensitive_occurrence_count_of(const SCOPED_STRING& scopedstr = 0) const {

      return _occurrence_count_of(scopedstr, ::comparison::case_insensitive<CHARACTER>());

   }



   // find routines

   // find the first occurrence of character 'ch', starting at index 'iStart'
   const_iterator find(CHARACTER ch) const RELEASENOTHROW;

   //   character_count find(CHARACTER ch) const RELEASENOTHROW;
   //   character_count find(CHARACTER ch) const RELEASENOTHROW;
   const_iterator case_insensitive_find(CHARACTER ch) const RELEASENOTHROW;

   // find routines

// find the first occurrence of character 'ch', starting at index 'iStart'
    //character_count find_index(CHARACTER ch) const RELEASENOTHROW { return this->index_of(this->find(ch)); }

    //   character_count find(CHARACTER ch) const RELEASENOTHROW;
    //   character_count find(CHARACTER ch) const RELEASENOTHROW;
   character_count case_insensitive_find_index(CHARACTER ch) const RELEASENOTHROW { return this->index_of(case_insensitive_find(ch)); }
   character_count case_insensitive_find_index(CHARACTER ch, character_count start) const RELEASENOTHROW { return this->index_of((*this)(start).case_insensitive_find(ch)); }

   const_iterator find_skip_or_end(CHARACTER ch = 0) const RELEASENOTHROW
   {

      auto p = this->begin();

      while (p < this->end()) {

         if (*p == ch) {

            p++;

            return p;

         }

         p++;

      }

      return p;

   }

   /// <summary>
   /// for the rear_* functions the most relevant returned
   /// value is actually in m_end.
   /// </summary>
   ITERATOR_TYPE find_first_whitespace() const RELEASENOTHROW { return this->find_first_character_in(typed_whitespace<CHARACTER>()); }

   ITERATOR_TYPE skip_whitespace() const RELEASENOTHROW { return this->skip_any_character_in(typed_whitespace<CHARACTER>()); }

   ::character_count count_left(const SCOPED_STRING& range = typed_whitespace<CHARACTER>()) const RELEASENOTHROW { return this->skip_any_character_in(range) - this->begin(); }

   //    string_range& trim_left(const SCOPED_STRING& range = typed_whitespace<CHARACTER>()) RELEASENOTHROW { this->m_begin += count_left(range); return *this; }


   ITERATOR_TYPE rear_find_first_whitespace() const RELEASENOTHROW { return this->rear_find_first_character_in(typed_whitespace<CHARACTER>()); }

   ITERATOR_TYPE rear_skip_whitespace() const RELEASENOTHROW { return this->rear_skip_any_character_in(typed_whitespace<CHARACTER>()); }

   ::character_count count_right(const SCOPED_STRING& range = typed_whitespace<CHARACTER>()) const RELEASENOTHROW { return this->m_end - this->rear_skip_any_character_in(range); }

   //    string_range& trim_right(const SCOPED_STRING& range = typed_whitespace<CHARACTER>()) RELEASENOTHROW { this->m_end -= count_right(range); return *this; }

   ::character_count count_left_and_right(const SCOPED_STRING& range = typed_whitespace<CHARACTER>()) const RELEASENOTHROW { ::character_count c; return ((c = count_left(range)) == this->size()) ? c : c + count_right(range); }

   //    string_range& trim(const SCOPED_STRING& range = typed_whitespace<CHARACTER>()) RELEASENOTHROW { trim_left(range); trim_right(range); return *this; }

   //    bool paired_trim(CHARACTER character1, CHARACTER character2)
   //    {
   //
   //       if (this->size() < 2)
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       if (this->first() != character1 || this->last() != character2)
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       this->begin()++;
   //
   //       this->end()--;
   //
   //       return true;
   //
   //    }


   //    bool begins_eat(CHARACTER character)
   //    {
   //
   //       if (this->size() <= 0)
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       if (this->first() != character)
   //       {
   //
   //          return false;
   //
   //       }
   //
   //      this->begin()++;
   //
   //      return true;
   //
   //    }


   //    bool defer_consume_character(CHARACTER & character)
   //    {
   //
   //       if (this->size() <= 0)
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       character = this->first();
   //
   //       this->begin()++;
   //
   //       return true;
   //
   //    }


   //    int defer_consume_digit(int iBase)
   //    {
   //
   //       CHARACTER character;
   //
   //       if (!defer_consume_character(character))
   //       {
   //
   //          return -1;
   //
   //       }
   //
   //       if (character >= '0' && character <= ('0' + minimum(iBase - 1, 9)))
   //       {
   //
   //          return character - '0';
   //
   //       }
   //
   //       if (iBase <= 10)
   //       {
   //
   //          return -1;
   //
   //       }
   //
   //       if (character >= 'a' && character <= ('a' + minimum(iBase - 11, 'z')))
   //       {
   //
   //          return character - 'a';
   //
   //       }
   //       else if (character >= 'A' && character <= ('A' + minimum(iBase - 11, 'Z')))
   //       {
   //
   //          return character - 'A';
   //
   //       }
   //
   //       return -1;
   //
   //    }

   const_string_range& operator=(const THIS_RANGE& range)
   {
      BASE_RANGE::operator=(range);
      return *this;
   }

   const_string_range& operator=(const_string_range&& range) {
      BASE_RANGE::operator=(::transfer(range));
      return *this;
   }

   //const_string_range& operator=(const atom& atom);

   const_string_range& operator=(const block& block);




   //inline bool begins(const SCOPED_STRING & scopedstrPrefix) const;
   //inline bool ends(const SCOPED_STRING & scopedstrSuffix) const;

   inline bool case_insensitive_begins(const SCOPED_STRING& scopedstrPrefix) const;

   inline bool case_insensitive_ends(const SCOPED_STRING& scopedstrSuffix) const;


   // look for a specific sub-string_base

   //bool _find_prefix(character_count & i, const string_base &str, character_count & start, character_count & blockLen, character_count & nEndPosition, const CHARACTER ** ppszTail) const RELEASENOTHROW;

   // find the first occurrence of string_base 'block', starting at index 'iStart'
   //const_iterator find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;



   const_iterator unicode_find(const SCOPED_STRING& scopedstr) const RELEASENOTHROW;

   const_iterator unicode_case_insensitive_find(const SCOPED_STRING& scopedstr) const RELEASENOTHROW;
   ::collection::index unicode_case_insensitive_find_index(const SCOPED_STRING& scopedstr, character_count start = 0) const RELEASENOTHROW
   {

      return this->index_of(this->operator()(start).unicode_case_insensitive_find(scopedstr));

   }

   // find the first occurrence of string_base 'block', starting at index 'iStart', if found returns the index of first character after the end of the found string_base
   //const_iterator rear_find(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;

   const_iterator unicode_rear_find(const SCOPED_STRING& scopedstr) const RELEASENOTHROW;

   const_iterator unicode_case_insensitive_rear_find(const SCOPED_STRING& scopedstr) const RELEASENOTHROW;

   // find the first occurrence of any of the characters in string_base 'pszCharSet'
   //const_iterator find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //const_iterator find_first_character_in(const SCOPED_STRING & scopedstrCharacters) const RELEASENOTHROW;
   //character_count find_first_character_in(const CHARACTER * blockCharacters, character_count iStart = 0) const RELEASENOTHROW;

   //const_iterator _find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
   //const_iterator _find_first_character_in(const SCOPED_STRING & scopedstrCharacters) const RELEASENOTHROW;
   ///character_count _find_first_character_in(const CHARACTER * blockCharacters, character_count iStart = 0) const RELEASENOTHROW;

   const_iterator find_first(CHARACTER chSeparator, ::character_count start = 0) const RELEASENOTHROW;

   //character_count find_first_in(const string_base &str) const RELEASENOTHROW;
   //character_count find_first_in(const string_base &str) const RELEASENOTHROW;
   ////character_count find_first_in(const string_base &str) const RELEASENOTHROW;
   //character_count find_first_in(CHARACTER ca) const RELEASENOTHROW;

   //const_iterator skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;

   //const_iterator skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;

   //character_count skip_any_character_in(const CHARACTER * pszCharacters) const RELEASENOTHROW;
   // const_iterator skip(CHARACTER chSkip) const RELEASENOTHROW;

   //const_iterator
   //_skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;

   //const_iterator _skip_any_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;

   //character_count _skip_any_character_in(const CHARACTER * pszCharacters) const RELEASENOTHROW;
   //const_iterator _skip(CHARACTER chSkip) const RELEASENOTHROW;


//character_count find_last_not_in(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
    //character_count find_last_not_in(const string_base &str) const RELEASENOTHROW;
    ////character_count find_last_not_in(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
    //character_count find_last_not_in(CHARACTER ca, character_count pos = -1) const RELEASENOTHROW;

//    const_iterator rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
//
//    const_iterator rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters, character_count iStart,
//                                                character_count n) const RELEASENOTHROW;
    //character_count rear_find_first_character_in(const CHARACTER * blockCharacters) const RELEASENOTHROW;

//    const_iterator _rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters) const RELEASENOTHROW;
//
//    const_iterator _rear_find_first_character_in(const SCOPED_STRING &scopedstrCharacters, character_count iStart,
//                                                 character_count n) const RELEASENOTHROW;
    //character_count _rear_find_first_character_in(const CHARACTER * blockCharacters) const RELEASENOTHROW;

    //character_count find_first_of(const string_base &str) const RELEASENOTHROW;
    //character_count find_first_of(const string_base &str) const RELEASENOTHROW;
    //character_count find_first_of(const CHARACTER * pszCharacters) const RELEASENOTHROW;
    //character_count find_first_of(CHARACTER ca) const RELEASENOTHROW;
    //character_count find_first_of(CHARACTER ca, character_count pos) const RELEASENOTHROW;

    //character_count find_first_not_of(const string_base &str) const RELEASENOTHROW;
    //character_count find_first_not_of(const string_base &str) const RELEASENOTHROW;
    //character_count find_first_not_of(const string_base &str) const RELEASENOTHROW;
    //character_count find_first_not_of(CHARACTER ca) const RELEASENOTHROW;

    //const_iterator rear_skip_any_character_in(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
    //const_iterator rear_skip_any_character_in(const SCOPED_STRING & scopedstr) const RELEASENOTHROW;
    //character_count rear_skip_any_character_in(const CHARACTER * psz, character_count pos = -1) const RELEASENOTHROW;

    //const_iterator rear_skip(CHARACTER ca) const RELEASENOTHROW;
    //const_iterator rear_skip(CHARACTER ca) const RELEASENOTHROW;


    //const_iterator _rear_skip_any_character_in(const SCOPED_STRING &scopedstr) const RELEASENOTHROW;
    //const_iterator _rear_skip_any_character_in(const SCOPED_STRING & scopedstr) const RELEASENOTHROW;


   using BASE_RANGE::_rear_skip;


   //const_iterator _rear_skip_any_character_in(CHARACTER ca) const RELEASENOTHROW;
   const_iterator _rear_skip(CHARACTER ca) const RELEASENOTHROW
   {

      return this->_rear_skip(ca, ::comparison::comparison < CHARACTER >());

   }

   using BASE_RANGE::rear_skip;

   //character_count _rear_skip_any_character_in(const CHARACTER * psz, character_count pos = -1) const RELEASENOTHROW;
   const_iterator rear_skip(CHARACTER ca) const RELEASENOTHROW
   {

      return this->rear_skip(ca, ::comparison::comparison < CHARACTER>());

   }

   //character_count find_last_of(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
   //character_count find_last_of(const string_base &str) const RELEASENOTHROW;
   ////character_count find_last_of(const string_base &str, character_count pos = -1) const RELEASENOTHROW;
   //character_count find_last_of(CHARACTER ca, character_count pos = -1) const RELEASENOTHROW;

   // find the last occurrence of character 'ch'
   //const_iterator rear_find(CHARACTER ch) const RELEASENOTHROW;

   // find the last occurrence of string_base 'sz'
   //const_iterator rear_find(const SCOPED_STRING & scopedstr) const RELEASENOTHROW;



   CHARACTER last_char(character_count count = -1) const;


   inline character_count unichar_count() const;

   inline const_iterator unichar_at(character_count iUnicharIndex) const;


   //const_iterator __replace(const_iterator start, const_iterator end, const SCOPED_STRING & scopedstr)
   //{

   //   ::memory_transfer((void *)start, start + scopedstr.size(), this->end() - end);

   //   string_count_copy(start, scopedstr.begin(), scopedstr.size());

   //}


   //bool equals(const string_base &str) const;
   //bool case_insensitive_equals(const string_base &str) const;
   //inline bool operator==(const ::ansi_string& str) const;

   //inline bool operator==(const ::wd16_string& str) const;

   //inline bool operator==(const ::wd32_string& str) const;

//   template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
   inline bool operator==(const ::range < const CHARACTER* >& range) const;

   template < character_count n >
   inline bool operator==(const CHARACTER(&s)[n]) const
   {

      return this->equals(s);

   }

   template < typename OTHER_CHARACTER >
   inline bool operator==(const ::range < const OTHER_CHARACTER* >& range) const
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER >;

   //inline bool operator ==(const SCOPED_STRING & scopedstr) const { return this->equals(scopedstr); }

   inline bool operator==(const ::ansi_character* psz) const { return this->equals(psz); }

   inline bool operator==(const ::wd16_character* psz) const { return this->equals(psz); }

   inline bool operator==(const ::wd32_character* psz) const { return this->equals(psz); }

   inline bool operator==(const ::inline_number_string& inline_number_string) const {
      return this->equals((const SCOPED_STRING&)inline_number_string);
   }

   //inline ::std::strong_ordering operator<=>(const string_base & range) const { return this->order(range); }
   //inline ::std::strong_ordering operator<=>(const SCOPED_STRING &scopedstr) const { return this->order(scopedstr); }
   //inline ::std::strong_ordering operator<=>(const CHARACTER * psz) const { return *this <=> ((const SCOPED_STRING &)psz); }
   //inline int operator<=>(CHARACTER ch) const;
   //inline bool operator==(CHARACTER ch) const;
   //inline bool operator==(CHARACTER ch) const;
   //inline bool operator>(const string_base &str2) const;
   //inline bool operator>(CHARACTER ch) const;
   //inline bool operator<(const string_base &str2) const;
   //inline bool operator<(CHARACTER ch) const;
   //inline bool operator!=(const string_base &str) const { return !operator ==(scopedstr); }
   //inline bool operator!=(CHARACTER ch) const { return !operator ==(ch); }
   //inline bool operator>=(const string_base &str) const { return !operator <(scopedstr); }
   //inline bool operator>=(CHARACTER ch) const { return !operator <(ch); }
   //inline bool operator<=(const CHARACTER * psz) const { return !operator >(scopedstr); }
   //inline bool operator<=(CHARACTER ch) const { return !operator >(ch); }



  //character_count rear_find(CHARACTER ch) const RELEASENOTHROW
  //{
  //   return rear_find(ch, iStart);
  //};
  //character_count rear_find(const string_base &str) const RELEASENOTHROW
  //{
  //   return rear_find(sz, iStart);
  //};


   bool xml_is_comment() const;


   ///========================================================
   /// Name   : _tcsenicmp
   /// Desc   : similar with case_insensitive_ansi_count_compare with escape process
   /// Param  : escape - will be escape character
   /// Return :
   ///--------------------------------------------------------
   /// Coder    Date                      Desc
   /// bro      2002-10-29
   ///========================================================
   ::std::strong_ordering escape_case_insensitive_count_order(const ::scoped_string& scopedstr, int escape) const;



   STRING surrounded(const SCOPED_STRING& scopedstr) const;

   STRING surrounded(const SCOPED_STRING& scopedstrLeft, const SCOPED_STRING& scopedstrRight) const;

   STRING double_quoted(bool bEscape = false) const;

   STRING single_quoted(bool bEscape) const;


   STRING_ARRAY explode(const SCOPED_STRING& scopedstrSeparator, bool bAddEmpty = true) const;


   //ITERATOR_TYPE __count_parts_from_beginning(::collection::count & cPathPartCountToConsume, CHARACTER chSeparator) const;


   //::collection::count count_parts_from_beginning(::collection::count  cPathPartCountToConsume, CHARACTER chSeparator) const;


   STRING_RANGE _get_count_parts_from_beginning(::collection::count cPathPartCountToConsume, CHARACTER chSeparator) const
   {

      auto range = this->operator()();

      auto cConsumed = cPathPartCountToConsume;

      range.m_begin = range.__count_parts_from_beginning(cConsumed, chSeparator);

      if (cPathPartCountToConsume == cConsumed)
      {

         return range;

      }

      return {};
      
   }


   //STRING_RANGE get_count_parts_from_beginning(::collection::count cPathPartCountToConsume, CHARACTER chSeparator) const
   //{

   //   if (cPathPartCountToConsume <= 0)
   //   {

   //      return this->operator()();

   //   }

   //   return this->_get_count_parts_from_beginning(cPathPartCountToConsume, chSeparator);

   //}


   THIS_RANGE right(character_count nCount) const;

   THIS_RANGE left(character_count count) const;

   THIS_RANGE left(const_iterator p) const { return ::transfer(this->left(p - this->begin())); }

   THIS_RANGE left_including_any_character_in(const SCOPED_STRING& scopedstrCharSet) const;

   THIS_RANGE left_skipping_any_character_in(const SCOPED_STRING& scopedstrCharSet) const;

   //THIS_RANGE consume_token_until_any_character_in(const SCOPED_STRING& scopedstrCharacters = 0, bool bReturnSeparator = false, bool bSkipAnyCharactersIn = true) const;


   inline ITERATOR_TYPE __count_parts_from_beginning(::collection::count & cPathMaxPartCount, CHARACTER chPartSeparator) const
   {

      ::collection::index i = 0;

      auto p = this->m_begin;

      for (; i < cPathMaxPartCount; i++)
      {

         p = string_find_character(p, chPartSeparator);

         if (::is_null(p))
         {

            break;

         }

         p = p + 1;

      }

      cPathMaxPartCount = i;

      return p;

   }


};




#include "const_string_range_static_array.h"



template<primitive_character CHARACTER>
constexpr ::range<const CHARACTER*> _string_range(const CHARACTER* psz);

template<primitive_character CHARACTER>
constexpr ::range<const CHARACTER*>
_start_count_string_range(const CHARACTER* psz, memsize start, memsize count);



//template < std::size_t n >
//class ansi_string_literal :
//   public const_ansi_range
//{
//public:
//
//   char m_s[n]{};
//
//   constexpr ansi_string_literal(char const(&s)[n])
//   {
//      std::ranges::copy(s, m_s);
//      this->m_begin = s;
//      this->m_end = s + (s[n-1]=='\0'? n-1:n);
//      this->m_erange = (enum_range) (e_range_string_literal
//      | (s[n - 1] == '\0' ? e_range_null_terminated : 0));
//
//   }
//
//
//};
//
//
//template < ansi_string_literal literal >
//constexpr auto operator ""_ansi()
//{
//
//   return literal;
//
//}
//

CLASS_DECL_ACME void log_const_ansi_range_literal(int n);


template < typename ITERATOR_TYPE >
class string_literal :
   public const_string_range < ITERATOR_TYPE >
{
public:


   constexpr string_literal(ITERATOR_TYPE s, std::size_t n)
   {

      this->m_begin = s;
      this->m_end = s + n;
      this->m_erange = e_range_string_literal | e_range_null_terminated;

   }


};


constexpr string_literal < const_char_pointer >operator ""_ansi(const_char_pointer s, std::size_t n)
{

   return { s, n };

}


constexpr string_literal < const ::wd16_character * > operator ""_wd16(const ::wd16_character * s, std::size_t n)
{

   return { s, n };

}


constexpr string_literal < const ::wd32_character* > operator ""_wd32(const ::wd32_character * s, std::size_t n)
{

   return { s, n };

}


template < primitive_character CHARACTER, character_count n >
::const_string_range < const CHARACTER * > as_range(const CHARACTER(&s)[n])
{
   return
   {
      s,
      s + (s[n - 1] == CHARACTER{} ? n - 1 : n),
      (enum_range)
         (s[n - 1] == CHARACTER{} ?
               e_range_null_terminated : e_range_none)
   };

}


template < typename TYPED_STRING_LITERAL, typename CHARACTER >
concept typed_string_literal =
::std::is_same_v < TYPED_STRING_LITERAL, CHARACTER >&&
primitive_character < TYPED_STRING_LITERAL >;










