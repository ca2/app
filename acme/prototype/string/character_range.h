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


// template < typename ITERATOR_TYPE >
// inline void string_base_increment_reference_count(ITERATOR_TYPE piterator);
//
//
// template < typename ITERATOR_TYPE >
// inline void string_base_release(ITERATOR_TYPE piterator);


//template < typename RANGE, typename ITERATOR_TYPE >
//inline RANGE & create_string(RANGE & rangeTarget, const ::character_range < ITERATOR_TYPE > & rangeSource)
//requires (::std::is_base_of < ::character_range < ITERATOR_TYPE >, RANGE >::value);
// {
//
//    this->m_begin =
//
// }
//
//
// //template < character_count n >
// //scoped_string_base(const char (&cha)[n]) :m_str(e_zero_initialize), BASE_RANGE(e_zero_initialize) { _construct1(cha); }
// //template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
// template < typename RANGE, typename ITERATOR_TYPE >
// RANGE & create_string(RANGE & range, ITERATOR_TYPE start, ITERATOR_TYPE end, enum_range erange = e_range_none)
// requires (::std::is_base_of < ::character_range < ITERATOR_TYPE >, RANGE >::value);
//
//
// template < typename RANGE, typename OTHER_ITERATOR_TYPE >
// RANGE & create_string(RANGE & range, OTHER_ITERATOR_TYPE start, OTHER_ITERATOR_TYPE end, enum_range erange = e_range_none)
// requires (sizeof(get_iterator_item < OTHER_ITERATOR_TYPE >) != sizeof(typename RANGE::ITEM)
//    && ::std::is_base_of < ::character_range < typename RANGE::this_iterator >, RANGE >::value);
//
//
// template < typename ITERATOR_TYPE >
// inline ITERATOR_TYPE character_range_defer_increment_reference_count(ITERATOR_TYPE piterator, enum_range erange);
//
//
// template < typename RANGE >
// inline RANGE & character_range_defer_increment_reference_count(RANGE & range);
//
//
// template < typename RANGE >
// inline RANGE & character_range_defer_release(RANGE & range);
//


template < typename ITERATOR_TYPE >
class character_range :
   public ::range < ITERATOR_TYPE >
{
public:

   using THIS_CHARACTER_RANGE = character_range < ITERATOR_TYPE >;
   using RAW_CHARACTER_RANGE = THIS_CHARACTER_RANGE;

   using BASE_RANGE = ::character_range < ITERATOR_TYPE >;
   using BASE_RAW_RANGE = ::character_range < ITERATOR_TYPE >;
   using _BASE_RAW_RANGE = ::range < ITERATOR_TYPE >;

   using this_iterator = typename BASE_RANGE::this_iterator;

   using CHARACTER = typename BASE_RANGE::ITEM;
   using BASE_DATA = ::base_data < CHARACTER >;

   BASE_DATA * m_pbasedata;

   constexpr character_range(no_initialize_t) :
      _BASE_RAW_RANGE(no_initialize_t{}) { }

   constexpr character_range() : _BASE_RAW_RANGE()
   {
      m_pbasedata = nullptr;
   }

   constexpr character_range(nullptr_t) : _BASE_RAW_RANGE(nullptr)
   {
      m_pbasedata = nullptr;
   }

   template < typed_character_pointer < typename character_range < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   character_range(CHARACTER_POINTER begin, CHARACTER_POINTER end, enum_range erange = e_range_none, BASE_DATA * pbasedata = nullptr) :
      _BASE_RAW_RANGE(begin, end, erange)
   {

      this->m_begin = begin;
   
      this->m_pbasedata = pbasedata;

      if (::is_set(this->m_pbasedata) && !(erange & e_range_scoped_ownership))
      {

         this->m_pbasedata->base_data_increment_reference_count();

      }
   
   }


   template < other_character_pointer < typename character_range < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   character_range(OTHER_CHARACTER_POINTER start, OTHER_CHARACTER_POINTER end, enum_range erange = e_range_none) = delete;


   template < character_count length >
   character_range(const CHARACTER (&s)[length]) :
      _BASE_RAW_RANGE(no_initialize_t{})
   {

      auto lengthNew = string_safe_length2(s, length);

      this->m_begin = s;

      this->m_end = s + lengthNew;

      this->m_erange = e_range_none;

      this->m_pbasedata = nullptr;

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
      _BASE_RAW_RANGE(characterrange)
   {

      this->m_pbasedata = characterrange.m_pbasedata;

      if (::is_set(this->m_pbasedata) && !(this->m_erange & e_range_scoped_ownership))
      {

         this->m_pbasedata->base_data_increment_reference_count();

      }

   }

   character_range(character_range&& characterrange) :
      _BASE_RAW_RANGE(::transfer(characterrange))
   {

      m_pbasedata = characterrange.m_pbasedata;

      characterrange.m_pbasedata = nullptr;

   }


   template < typename TYPED_RANGE >
   character_range(const TYPED_RANGE& range) requires
      (typed_range<TYPED_RANGE, this_iterator>
         && !std::is_same_v<std::decay_t<TYPED_RANGE>, character_range>) :
      character_range(range.m_begin, range.m_end, range.m_erange, range.m_pbasedata) { }

   template < typename OTHER_RANGE >
   character_range(const OTHER_RANGE& range) requires
      (other_character_range<OTHER_RANGE, CHARACTER>) = delete;

   // constexpr character_range(this_iterator begin, this_iterator end, enum_range erange = e_range_none) :
   // BASE_RANGE(character_range_defer_increment_reference_count(begin, erange), end, erange) { }


   BASE_DATA * create_string_data2(character_count lengthNew, enum_range erange)
   {

      auto allocationSize = lengthNew;

      if (erange & e_range_buffer)
      {

         allocationSize *= 2;

      }

      auto pbasedata = BASE_DATA::create_base_data2(allocationSize + 1);

      this->m_pbasedata = pbasedata;

      this->m_erange = (enum_range) (erange & ~(e_range_string_literal));

      return pbasedata;

   }


   inline memsize storage_count() const
   {

      auto pbasedata = this->m_pbasedata;

      if (is_null(pbasedata))
      {

         return 0;

      }

      return pbasedata->storage_count();

   }


   inline character_count storage_character_count() const
   {

      auto pbasedata = this->m_pbasedata;

      if (is_null(pbasedata))
      {

         return 0;

      }

      return pbasedata->storage_character_count();

   }

   inline character_count length() const { return this->m_end - this->m_begin; }
   inline character_count size() const { return this->length(); }
   inline memsize character_count_in_bytes() const { return this->length() * sizeof(CHARACTER); };
   inline memsize null_terminated_character_count_in_bytes() const { return (this->length() + 1) * sizeof(CHARACTER); }

   character_range& operator=(const character_range& range)
   {
      _BASE_RAW_RANGE::operator=(range);
      this->m_pbasedata = range.m_pbasedata;
      return *this;
   }


   character_range& operator=(character_range&& range) {
      _BASE_RAW_RANGE::operator=(::transfer(range));
      this->m_pbasedata = range.m_pbasedata;
      range.m_pbasedata = nullptr;
      return *this;
   }


   // inline ::character_count storage_character_count() const
   // {
   //
   //    if (!m_pbasedata)
   //    {
   //
   //       return 0;
   //
   //    }
   //
   //    return (::character_count);
   //
   // }


   constexpr bool has_string_storage() const { return m_pbasedata != nullptr; }


   constexpr bool is_null_terminated() const { return !*this->m_end; }


   void set_null()
   {

      _BASE_RAW_RANGE::set_null();

      this->m_pbasedata = nullptr;

   }

   // inline static BASE_DATA * create_base_data(character_count character_count)
   // {
   //
   //    auto pbasedata = BASE_DATA::heap_data_create(character_count);
   //
   //    return pbasedata;
   //
   // }


   void _set_length(::character_count count)
   {

      this->m_end = this->m_begin + count;

      *((CHARACTER *)this->m_end) = {};

   }


   void construct_string(ITERATOR_TYPE start, ITERATOR_TYPE end, enum_range erange = e_range_none)
   {

      auto length = end - start;

      auto lengthNew = string_safe_length2(start, length);

      auto pbasedata = this->create_string_data2(lengthNew, erange);

      auto pdata = pbasedata->data();

      this->m_begin = pdata;

      memory_transfer(pdata, start, lengthNew);

      this->_set_length(lengthNew);

   }


   template < typename OTHER_ITERATOR_TYPE >
   void construct_string(OTHER_ITERATOR_TYPE start, OTHER_ITERATOR_TYPE end, enum_range erange = e_range_none)
   requires (sizeof(get_iterator_item < OTHER_ITERATOR_TYPE >) != sizeof(CHARACTER))
   {

      auto srclen = end - start;

      character_count lengthSrc = srclen;

      auto lengthNew = utf_to_utf_length2(this->m_begin, start, lengthSrc);

      auto pbasedata = this->create_string_data2(lengthNew, erange);

      auto pdata = pbasedata->data();

      this->m_begin = pdata;

      utf_to_utf(pdata, start, lengthSrc);

      this->_set_length(lengthNew);

   }


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




