// Created by camilo on 2025-04-17 09:37 <3ThomasBorregaardSorensen!!
#pragma once
#include <format>


#include "acme/prototype/collection/range.h"
#include "acme/prototype/string/string_heap_data.h"


template < typename TYPE >
inline const TYPE & for_copy(TYPE && t)
{

   return (const TYPE &) t;

}


template < typename ITERATOR_TYPE >
inline void string_base_increment_reference_count(ITERATOR_TYPE piterator);


template < typename ITERATOR_TYPE >
inline void string_base_release(ITERATOR_TYPE piterator);


//template < typename RANGE, typename ITERATOR_TYPE >
//inline RANGE & create_string(RANGE & rangeTarget, const ::range < ITERATOR_TYPE > & rangeSource)
//requires (::std::is_base_of < ::range < ITERATOR_TYPE >, RANGE >::value);
// {
//
//    this->m_begin =
//
// }


//template < character_count n >
//scoped_string_base(const char (&cha)[n]) :m_str(e_zero_initialize), BASE_RANGE(e_zero_initialize) { _construct1(cha); }
//template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
template < typename RANGE, typename ITERATOR_TYPE >
RANGE & create_string(RANGE & range, ITERATOR_TYPE start, ITERATOR_TYPE end, enum_range erange = e_range_none)
requires (::std::is_base_of < ::range < ITERATOR_TYPE >, RANGE >::value);


template < typename RANGE, typename OTHER_ITERATOR_TYPE >
RANGE & create_string(RANGE & range, OTHER_ITERATOR_TYPE start, OTHER_ITERATOR_TYPE end, enum_range erange = e_range_none)
requires (sizeof(get_iterator_item < OTHER_ITERATOR_TYPE >) != sizeof(typename RANGE::ITEM)
   && ::std::is_base_of < ::range < typename RANGE::this_iterator >, RANGE >::value);


template < typename ITERATOR_TYPE >
inline ITERATOR_TYPE character_range_defer_increment_reference_count(ITERATOR_TYPE piterator, enum_range erange);


template < typename RANGE >
inline RANGE & character_range_defer_increment_reference_count(RANGE & range);


template < typename RANGE >
inline RANGE & character_range_defer_release(RANGE & range);


template < typename ITERATOR_TYPE >
class character_range :
   public ::range < ITERATOR_TYPE >
{
public:

   using THIS_CHARACTER_RANGE = character_range < ITERATOR_TYPE >;
   using RAW_CHARACTER_RANGE = THIS_CHARACTER_RANGE;


   using BASE_RANGE = ::range < ITERATOR_TYPE >;
   using BASE_RAW_RANGE = character_range < ITERATOR_TYPE >;

   using this_iterator = typename BASE_RANGE::this_iterator;

   using CHARACTER = typename BASE_RANGE::ITEM;
   using BASE_DATA = ::base_data < CHARACTER >;

   BASE_DATA * m_pbasedata = nullptr;

   character_range(no_initialize_t) :
      BASE_RANGE(no_initialize_t{}) { }


   template < typed_character_pointer < typename character_range < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   character_range(CHARACTER_POINTER begin, CHARACTER_POINTER end, enum_range erange = e_range_none) :
      BASE_RANGE(begin, end, erange) { }
   // {
   //
   //    if (end <= begin)
   //    {
   //
   //       this->set_null();
   //
   //       return;
   //
   //    }
   //
   //    if (erange & e_range_string)
   //    {
   //
   //       this->m_begin = begin;
   //
   //       this->m_end = end;
   //
   //       this->m_erange = erange;
   //
   //       character_range_defer_increment_reference_count(*this);
   //
   //       return;
   //
   //    }
   //
   //    this->m_begin = begin;
   //
   //    this->m_end = end;
   //
   //    this->m_erange = *this->m_end ? e_range_none : e_range_null_terminated;
   //
   // }


   template < other_character_pointer < typename character_range < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   character_range(OTHER_CHARACTER_POINTER start, OTHER_CHARACTER_POINTER end, enum_range erange = e_range_none) = delete;


   template < character_count length >
   character_range(const CHARACTER (&s)[length]) :
      BASE_RANGE(no_initialize_t{})
   {

      if constexpr (length >= 1)
      {

         if (s[length - 1] == CHARACTER{})
         {

            if (length - 1 <= 0)
            {

               this->set_null();

               return;

            }

            this->m_begin = s;

            this->m_end = s + length - 1;

            this->m_erange = e_range_none;

            return;

         }

      }

      this->m_begin = s;

      this->m_end = s + length;

      this->m_erange = e_range_none;

      //this->m_erange = *this->m_end ? e_range_none : e_range_null_terminated;

   }

   template < character_pointer CHARACTER_POINTER >
   //character_range(CHARACTER_POINTER start) : character_range(start, start + string_safe_length(start), e_range_null_terminated) { }
   character_range(CHARACTER_POINTER start) : character_range(start, start + string_safe_length(start), e_range_none) { }


   template < character_pointer CHARACTER_POINTER >
   character_range(CHARACTER_POINTER start, character_count length) = delete;


   template < other_primitive_character <CHARACTER> OTHER_CHARACTER, character_count length >
   character_range(const CHARACTER(&s)[length]) = delete;


   character_range(const character_range& characterrange) :
      character_range(characterrange.m_begin, characterrange.m_end, characterrange.m_end) { }

   character_range(character_range && characterrange) :
      character_range(::for_copy(characterrange)) { characterrange.set_null(); }

   character_range(const character_range& characterrange) :
      BASE_RANGE(characterrange)
   {

      m_pbasedata = characterrange.m_pbasedata;

      if (m_pbasedata)
      {

         m_pbasedata->base_data_increment_reference_count();

      }

   }

   character_range(character_range&& characterrange) :
      BASE_RANGE(::transfer(characterrange))
   {

      m_pbasedata = nullptr;

      characterrange.m_pbasedata = nullptr;

   }


   template < typename TYPED_RANGE >
   character_range(const TYPED_RANGE& range) requires
      (typed_range<TYPED_RANGE, this_iterator>
         && !std::is_same_v<std::decay_t<TYPED_RANGE>, character_range>) :
      character_range(range.m_begin, range.m_end, range.m_erange) { }

   template < typename OTHER_RANGE >
   character_range(const OTHER_RANGE& range) requires
      (other_character_range<OTHER_RANGE, CHARACTER>) = delete;

   // constexpr character_range(this_iterator begin, this_iterator end, enum_range erange = e_range_none) :
   // BASE_RANGE(character_range_defer_increment_reference_count(begin, erange), end, erange) { }


   character_range& operator=(const character_range& range)
   {
      BASE_RANGE::operator=(range);
      return *this;
   }


   character_range& operator=(character_range&& range) {
      BASE_RANGE::operator=(::transfer(range));
      return *this;
   }


   inline ::character_count storage_character_count() const
   {

      if (!m_pbasedata)
      {

         return 0;

      }

      return (::character_count)null_terminated_byte_length_to_character_count(m_pbasedata->m_sizeStorageInBytes);

   }


   constexpr bool has_string_storage() const { return m_pbasedata != nullptr; }


   constexpr bool is_null_terminated() const { return !*this->m_end; }
};



//
//template <typename ITERATOR_TYPE>
//struct std::formatter<character_range<ITERATOR_TYPE>> : std::formatter<std::string_view>
//{
//   template <typename FormatContext>
//   auto format(const character_range<ITERATOR_TYPE>& s, FormatContext& ctx) const
//   {
//      return std::formatter<std::string_view>::format(
//         std::string_view(s.begin(), s.size()), ctx);
//   }
//};
//
//
//


// Formatter for MyString<CharT>
template <typename CharT>
struct std::formatter<::character_range<const CharT *>, CharT> {
   // Reuse the existing string_view formatter
   std::formatter<std::basic_string_view<CharT>, CharT> formatter;

   constexpr auto parse(std::basic_format_parse_context<CharT>& ctx) {
      // Delegate parsing to string_view's formatter
      return formatter.parse(ctx);
   }

   template <typename FormatContext>
   auto format(const ::character_range<const CharT *>& s, FormatContext& ctx) {
      // Wrap in string_view and forward
      return formatter.format(
         std::basic_string_view<CharT>(s.data(), s.size()), ctx);
   }
};




