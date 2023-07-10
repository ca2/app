// Created by camilo on 2022-11-22 <3ThomasBorregaardSorensen!!
//
//  _numeric_concepts.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/22.
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


struct ENUM_TYPE_TAG {};


struct sequence_t {};


template < typename SEQUENCE >
concept primitive_sequence = ::std::is_same < typename SEQUENCE::sequence_tag, sequence_t >::value;


template < typename ENUM >
concept primitive_enum = 
   std::is_enum < ::decay < ENUM > >::value 
   || ::std::is_same < typename ENUM::ENUM_TAG, ENUM_TYPE_TAG >::value;


template < typename BLOCK >
concept primitive_block = ::std::is_same<typename BLOCK::PRIMITIVE_BLOCK_TAG, PRIMITIVE_BLOCK_TAG_TYPE >::value;


template < typename INTEGRAL >
concept primitive_integral = std::is_integral_v < ::decay < INTEGRAL > >;

//template < typename T >
//concept primitive_integral_up_to_32_bit =
//(std::is_integral_v < T > ||
//std::is_enum < T >::value ||
//std::is_same < T, ::e_status >::value) && sizeof(T) <= 4;

template < typename T >
concept primitive_integral_up_to_32_bit =
(std::is_integral_v < T >) && sizeof(T) <= 4;

template < typename T >
concept primitive_integer = std::is_integral < T >::value;

template < typename T >
concept primitive_natural = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept primitive_signed = std::is_integral < T >::value && std::is_signed < T >::value;

template < typename T >
concept primitive_signed_not_8bit = primitive_signed < T > && sizeof(T) != 1;

template < typename T >
concept primitive_unsigned = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept primitive_unsigned_not_8bit = primitive_unsigned < T > && sizeof(T) != 1;

template < typename FLOATING >
concept primitive_floating = std::is_floating_point < ::decay < FLOATING > >::value;



template < typename AGGREGATE >
concept primitive_aggregate = ::std::is_aggregate_v < AGGREGATE >;


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
std::is_same < T, ::u8 >::value ||
std::is_same < T, char >::value ||
std::is_same < T, char8_t >::value ||
std::is_same < T, wchar_t >::value ||
std::is_same < T, ::ansi_character >::value ||
std::is_same < T, ::wd16_character >::value ||
std::is_same < T, ::wd32_character >::value ||
std::is_same < T, const ::u8 >::value ||
std::is_same < T, const char >::value ||
std::is_same < T, const char8_t >::value ||
std::is_same < T, const wchar_t >::value ||
std::is_same < T, const ::ansi_character >::value ||
std::is_same < T, const ::wd16_character >::value ||
std::is_same < T, const ::wd32_character >::value;


template < typename T >
concept primitive_character_iterator =
std::is_same < T, ::u8 * >::value ||
std::is_same < T, char * >::value ||
std::is_same < T, char8_t * >::value ||
std::is_same < T, wchar_t * >::value ||
std::is_same < T, ::ansi_character * >::value ||
std::is_same < T, ::wd16_character * >::value ||
std::is_same < T, ::wd32_character * >::value ||
std::is_same < T, const ::u8 * >::value ||
std::is_same < T, const char * >::value ||
std::is_same < T, const char8_t * >::value ||
std::is_same < T, const wchar_t * >::value ||
std::is_same < T, const ::ansi_character * >::value ||
std::is_same < T, const ::wd16_character * >::value ||
std::is_same < T, const ::wd32_character * >::value;


template < typename T >
concept primitive_character_iterator_reference =
std::is_same < T, ::u8 * & >::value ||
std::is_same < T, char * & >::value ||
std::is_same < T, char8_t *& >::value ||
std::is_same < T, wchar_t * & >::value ||
std::is_same < T, ::ansi_character * & >::value ||
std::is_same < T, ::wd16_character * & >::value ||
std::is_same < T, ::wd32_character * & >::value ||
std::is_same < T, const ::u8 * & >::value ||
std::is_same < T, const char * & >::value ||
std::is_same < T, const char8_t *& >::value ||
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


template < typename ITERATOR >
class string_base;


using ansi_string = string_base < const ::ansi_character * >;
using wd16_string = string_base < const ::wd16_character * >;
using wd32_string = string_base < const ::wd32_character * >;
using wide_string = string_base < const ::wide_character * >;
using string      = ::ansi_string;
using wstring     = ::wide_string;


template < typename HAS_AS_STRING >
concept has_as_string = requires(HAS_AS_STRING has_as_string)
{

   { has_as_string.as_string() } -> ::std::same_as <::string>;

};

template < typename HAS_GET_STRING >
concept has_get_string = requires(HAS_GET_STRING has_get_string)
{

   { has_get_string.get_string() } -> ::std::same_as <::string>;

};



//template <typename HANDLER, typename ITEM>
//concept ::comparison::comparison = 
//::std::is_same<typename HANDLER::ORDERING, ORDERING_HANDLER_TAG >::value
//&& ::std::is_same<typename HANDLER::ORDERING, ORDERING_HANDLER_TAG >::value;


//template <typename COMPARE_ITEM, typename ITEM>
//concept compare_predicate = ::std::convertible_to<COMPARE_ITEM,::function<::std::strong_ordering(ITEM, ITEM)> >
//|| ::std::convertible_to<COMPARE_ITEM,::std::function< ::strong_ordering(const ITEM &, const ITEM &)>>;
//
//


//template < typename BLOCK >
//concept primitive_block = requires(BLOCK block)
//{
//
//   block.data();
//   block.size();
//   block.length_in_bytes();
//
//};


#ifdef ANDROID

namespace std
{
   template<class FROM, class TO>
   concept convertible_to = ::std::is_convertible_v<FROM, TO>;

}
#endif



//template < typename TYPED_BLOCK, typename ITEM_TYPE >
//concept typed_block = requires(TYPED_BLOCK typed_block, ITEM_TYPE item_type)
//{
//
//   { typed_block.data() }->::std::convertible_to<ITEM_TYPE*>;
//   typed_block.size();
//   typed_block.length_in_bytes();
//
//};

template < typename CONTAINER >
concept primitive_container = ::std::is_same < typename CONTAINER::PRIMITIVE_CONTAINER_TAG, PRIMITIVE_CONTAINER_TAG_TYPE >::value;

template < typename PAYLOAD >
concept primitive_payload = ::std::is_same < typename PAYLOAD::PRIMITIVE_PAYLOAD_TAG, PRIMITIVE_PAYLOAD_TAG_TYPE >::value;

template < typename HAS_AS_STRING_NOT_PAYLOAD >
concept has_as_string_not_payload = has_as_string < HAS_AS_STRING_NOT_PAYLOAD > && !primitive_payload<HAS_AS_STRING_NOT_PAYLOAD>;


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




template < typename NUMBER >
concept primitive_number =
primitive_integral < NUMBER > ||
primitive_floating < NUMBER > ||
primitive_enum < NUMBER >;


template < typename POINT >
concept raw_primitive_point = requires(POINT point)
{
   { point.x }->primitive_number;
   { point.y }->primitive_number;
};


template < typename POINT >
concept primitive_point = requires(POINT point)
{
   { point.x() }->primitive_number;
   { point.y() }->primitive_number;
};


template < typename POLE >
concept primitive_pole = requires(POLE pole)
{
   { pole.x() }->primitive_number;
   { pole.y() }->primitive_number;
   { pole.z() }->primitive_number;
};


template < typename POINT >
concept primitive_XY = requires(POINT point)
{
   point.X;
   point.Y;
};


template < typename SIZE >
concept primitive_size = requires(SIZE size)
{
   size.cx();
   size.cy();
};


template < typename Dimension >
concept primitive_Dimension = requires(Dimension dimension)
{
   dimension.Width;
   dimension.Height;
};


template < typename DIMENSION >
concept primitive_dimension = requires(DIMENSION dimension)
{
   dimension.width;
   dimension.height;
};


template < typename RECTANGLE >
concept primitive_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.left;
   rectangle.top;
   rectangle.right;
   rectangle.bottom;
};


template < typename RECTANGLE >
concept primitive_XYDim = requires(RECTANGLE rectangle)
{
   rectangle.X;
   rectangle.Y;
   rectangle.Width;
   rectangle.Height;
};


template < typename RECTANGLE >
concept primitive_xydim = requires(RECTANGLE rectangle)
{
   rectangle.x;
   rectangle.y;
   rectangle.width;
   rectangle.height;
};


template < typename RECTANGLE >
concept primitive_origin_size = requires(RECTANGLE rectangle)
{
   { rectangle.origin }->raw_primitive_point;
   { rectangle.size }->primitive_dimension;
};


//template < typename ORIGIN_SIZE >
//concept origin_size = requires(ORIGIN_SIZE origin_size)
//{
//
//   { origin_size.origin } -> primitive_point;
//   { origin_size.size } -> primitive_dim;
//
//};



template < primitive_number NUMBER >
struct argument_of_struct < NUMBER >
{

   using type = NUMBER;

};



template < primitive_number NUMBER >
class point_type;


template < primitive_number NUMBER >
class size_type;


template < primitive_number NUMBER >
class rectangle_type;






//
//
//template < primitive_number NUMBER1, primitive_number NUMBER2 >
//inline void copy(NUMBER1& number1, const NUMBER2& number2)
//{
//
//   number1 = (NUMBER1)number2;
//
//}
//











