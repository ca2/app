﻿//
//  _numeric_concepts.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "acme/primitive/primitive/e_status.h"


template < typename T >
concept a_enum = std::is_enum < T >::value;

template < typename T >
concept primitive_integral =
   std::is_integral_v < T > ||
   std::is_enum < T >::value ||
   std::is_same < T, ::e_status >::value;

template < typename T >
concept primitive_integral_up_to_32_bit =
(std::is_integral_v < T > ||
std::is_enum < T >::value ||
std::is_same < T, ::e_status >::value) && sizeof(T) <= 4;

template < typename T >
concept primitive_integer = std::is_integral < T >::value;

template < typename T >
concept primitive_natural = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept primitive_signed = (std::is_integral < T >::value || std::is_enum < T >::value) && std::is_signed < T >::value;

template < typename T >
concept primitive_signed_not_8bit = primitive_signed < T > && sizeof(T) != 1;

template < typename T >
concept primitive_unsigned = (std::is_integral < T >::value || std::is_enum < T >::value) && !std::is_signed < T >::value;

template < typename T >
concept primitive_unsigned_not_8bit = primitive_unsigned < T > && sizeof(T) != 1;

template < typename T >
concept primitive_floating = std::is_floating_point < T >::value;

template < typename NUMBER >
concept primitive_number =
   std::is_integral_v < NUMBER > ||
   std::is_enum_v < NUMBER > ||
   std::is_floating_point_v < NUMBER >;


template < typename T >
concept primitive_fundamental = std::is_fundamental < T >::value || std::is_pointer < T >::value;

template < typename T >
concept primitive_type = !std::is_fundamental < T >::value && !std::is_pointer < T >::value;


template < typename T >
concept primitive_range = requires(T t)
{

   t.begin();
   t.end();

};


template < typename T, typename ITERATOR_TYPE >
concept typed_range = requires(T t, ITERATOR_TYPE iterator)
{

   {t.begin()}-> ::std::same_as<ITERATOR_TYPE &>;
   {t.end()}->std::same_as<ITERATOR_TYPE &>;

};




template < typename FROM, typename TO_POINTER >
concept raw_pointer_castable =
::std::is_convertible < FROM, TO_POINTER * >::value ||
::std::is_convertible < FROM, const TO_POINTER * >::value;


template < typename T >
concept primitive_character =
std::is_same < T, ::byte >::value ||
std::is_same < T, char >::value ||
std::is_same < T, wchar_t >::value ||
std::is_same < T, ::ansi_character >::value ||
std::is_same < T, ::wd16_character >::value ||
std::is_same < T, ::wd32_character >::value ||
std::is_same < T, const ::byte >::value ||
std::is_same < T, const char >::value ||
std::is_same < T, const wchar_t >::value ||
std::is_same < T, const ::ansi_character >::value ||
std::is_same < T, const ::wd16_character >::value ||
std::is_same < T, const ::wd32_character >::value;


template < typename T >
concept primitive_character_iterator =
std::is_same < T, ::byte * >::value ||
std::is_same < T, char * >::value ||
std::is_same < T, wchar_t * >::value ||
std::is_same < T, ::ansi_character * >::value ||
std::is_same < T, ::wd16_character * >::value ||
std::is_same < T, ::wd32_character * >::value ||
std::is_same < T, const ::byte * >::value ||
std::is_same < T, const char * >::value ||
std::is_same < T, const wchar_t * >::value ||
std::is_same < T, const ::ansi_character * >::value ||
std::is_same < T, const ::wd16_character * >::value ||
std::is_same < T, const ::wd32_character * >::value;


template < typename T >
concept primitive_character_iterator_reference =
std::is_same < T, ::byte * & >::value ||
std::is_same < T, char * & >::value ||
std::is_same < T, wchar_t * & >::value ||
std::is_same < T, ::ansi_character * & >::value ||
std::is_same < T, ::wd16_character * & >::value ||
std::is_same < T, ::wd32_character * & >::value ||
std::is_same < T, const ::byte * & >::value ||
std::is_same < T, const char * & >::value ||
std::is_same < T, const wchar_t * & >::value ||
std::is_same < T, const ::ansi_character * & >::value ||
std::is_same < T, const ::wd16_character * & >::value ||
std::is_same < T, const ::wd32_character * & >::value;


template < typename T >
concept character_range = requires(T t)
{

   { t.begin() } -> primitive_character_iterator_reference;
   { t.end() } -> primitive_character_iterator_reference;

};


struct ITERATOR_TYPE_TAG {};

template < typename ITERATOR >
concept primitive_iterator = ::std::is_same<typename ITERATOR::TYPE_TAG, ITERATOR_TYPE_TAG >::value;


template < typename TYPE >
struct for_type {};


namespace comparison
{


   template < typename ORDERING, typename TYPE >
   concept ordering = ::std::is_same<typename ORDERING::ORDERING, for_type < TYPE > >::value;


   template < typename EQUALITY, typename TYPE >
   concept equality = ::std::is_same<typename EQUALITY::EQUALITY, for_type < TYPE > >::value;


   constexpr bool done_with_result(bool bEqual) { return !bEqual; }


   constexpr bool done_with_result(std::strong_ordering order) { return order != 0; }


   template < typename COMPARISON >
   constexpr auto tuple(COMPARISON comparison)
   {
      
      return comparison();

   }


   template<typename COMPARISON, typename... Args>
   constexpr auto tuple(COMPARISON comparison, Args... args) // recursive variadic function
   {

      auto result = comparison();
      
      if (done_with_result(result))
      {

         return result;

      }

      return tuple(args...);

   }


} // namespace comparison


//template <typename HANDLER, typename ITEM>
//concept ::comparison::comparison = 
//::std::is_same<typename HANDLER::ORDERING, ORDERING_HANDLER_TAG >::value
//&& ::std::is_same<typename HANDLER::ORDERING, ORDERING_HANDLER_TAG >::value;


//template <typename COMPARE_ITEM, typename ITEM>
//concept compare_predicate = ::std::convertible_to<COMPARE_ITEM,::std::function<::std::strong_ordering(ITEM, ITEM)> >
//|| ::std::convertible_to<COMPARE_ITEM,::std::function< ::std::strong_ordering(const ITEM &, const ITEM &)>>;
//
//


template < typename BLOCK >
concept primitive_block = requires(BLOCK block)
{

   block.data();
   block.size();
   block.length_in_bytes();

};


template < typename TYPED_BLOCK, typename ITEM_TYPE >
concept typed_block = requires(TYPED_BLOCK typed_block, ITEM_TYPE item_type)
{

   { typed_block.data() }->::std::convertible_to<ITEM_TYPE*>;
   typed_block.size();
   typed_block.length_in_bytes();

};

template < typename CONTAINER >
concept primitive_container = ::std::is_same < typename CONTAINER::PRIMITIVE_CONTAINER_TAG, PRIMITIVE_CONTAINER_TAG_TYPE >::value;

template < typename PAYLOAD >
concept primitive_payload = ::std::is_same < typename PAYLOAD::PRIMITIVE_PAYLOAD_TAG, PRIMITIVE_PAYLOAD_TAG_TYPE >::value;

template < typename ATOM >
concept primitive_atom = ::std::is_same < typename ATOM::PRIMITIVE_ATOM_TAG, PRIMITIVE_ATOM_TAG_TYPE >::value;

template < typename STRING >
concept primitive_string = ::std::is_same < typename STRING::PRIMITIVE_STRING_TAG, PRIMITIVE_STRING_TAG_TYPE >::value;

template < typename SCOPED_STRING >
concept primitive_scoped_string = ::std::is_same < typename SCOPED_STRING::PRIMITIVE_SCOPED_STRING_TAG, PRIMITIVE_SCOPED_STRING_TAG_TYPE >::value;


template < typename T >
concept character_range_not_string = character_range<T> && !primitive_string<T>;


template < typename T >
concept character_range_not_string_neither_scoped_string = character_range<T> && !primitive_string<T> && !primitive_scoped_string<T>;

