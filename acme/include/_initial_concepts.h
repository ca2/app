// Created by camilo on 2022-11-22 <3ThomasBorregaardSorensen!!
//
//  _numeric_concepts.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/22.
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


template < typename SEQUENCE >
concept primitive_sequence = ::std::is_same < typename SEQUENCE::sequence_tag, sequence_t >::value;


template < typename ENUM >
concept primitive_enum = 
   std::is_enum < ::decay < ENUM > >::value 
   || ::std::is_same < typename ENUM::ENUM_TYPE_TAG, enum_type_t >::value;


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

   {t.begin()}-> ::std::convertible_to<ITERATOR_TYPE &>;
   {t.end()}->std::convertible_to<ITERATOR_TYPE &>;

};


template < typename FROM, typename TO >
concept castable_to =
::std::is_convertible < FROM, TO >::value ||
::std::is_convertible < FROM, const TO >::value;

template < typename FROM, typename TO >
concept non_castable_to = !castable_to < FROM, TO >;


template < typename FROM, typename TO >
concept pointer_castable_to =
::std::is_convertible < ::decay < FROM > *, TO >::value;


template < typename FROM, typename TO >
concept pointer_not_castable_to = !pointer_castable_to < FROM, TO >;


template < typename FROM, typename TO_POINTER >
concept raw_pointer_castable =
::std::is_convertible < FROM, TO_POINTER * >::value ||
::std::is_convertible < FROM, const TO_POINTER * >::value;

template < typename FROM, typename TO_POINTER >
concept non_raw_pointer_castable = !raw_pointer_castable < FROM, TO_POINTER >;


template < typename T >
concept primitive_character =
std::is_same < T, unsigned char >::value ||
std::is_same < T, char >::value ||
std::is_same < T, char8_t >::value ||
std::is_same < T, wchar_t >::value ||
std::is_same < T, ::ansi_character >::value ||
std::is_same < T, ::wd16_character >::value ||
std::is_same < T, ::wd32_character >::value ||
std::is_same < T, const unsigned char >::value ||
std::is_same < T, const char >::value ||
std::is_same < T, const char8_t >::value ||
std::is_same < T, const wchar_t >::value ||
std::is_same < T, const ::ansi_character >::value ||
std::is_same < T, const ::wd16_character >::value ||
std::is_same < T, const ::wd32_character >::value;


template < typename T >
concept primitive_character_iterator =
std::is_same < T, unsigned char * >::value ||
std::is_same < T, char * >::value ||
std::is_same < T, char8_t * >::value ||
std::is_same < T, wchar_t * >::value ||
std::is_same < T, ::ansi_character * >::value ||
std::is_same < T, ::wd16_character * >::value ||
std::is_same < T, ::wd32_character * >::value ||
std::is_same < T, const unsigned char * >::value ||
std::is_same < T, const char * >::value ||
std::is_same < T, const char8_t * >::value ||
std::is_same < T, const wchar_t * >::value ||
std::is_same < T, const ::ansi_character * >::value ||
std::is_same < T, const ::wd16_character * >::value ||
std::is_same < T, const ::wd32_character * >::value;


template < typename T >
concept primitive_character_iterator_reference =
std::is_same < T, unsigned char * & >::value ||
std::is_same < T, char * & >::value ||
std::is_same < T, char8_t *& >::value ||
std::is_same < T, wchar_t * & >::value ||
std::is_same < T, ::ansi_character * & >::value ||
std::is_same < T, ::wd16_character * & >::value ||
std::is_same < T, ::wd32_character * & >::value ||
std::is_same < T, const unsigned char * & >::value ||
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

//template < typename CONTAINER >
//concept primitive_container = ::std::is_same < typename CONTAINER::PRIMITIVE_CONTAINER_TAG, PRIMITIVE_CONTAINER_TAG_TYPE >::value;

template < typename PAYLOAD >
concept primitive_payload = ::std::is_same < typename PAYLOAD::PRIMITIVE_PAYLOAD_TAG, PRIMITIVE_PAYLOAD_TAG_TYPE >::value;


template < typename A_CONST >
concept primitive_const = ::std::is_const < A_CONST > ::value;

template < typename NON_CONST >
concept primitive_non_const = !primitive_const < NON_CONST >;

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


template < typename SEQUENCE2 >
concept primitive_sequence2 =
   ::std::is_same < typename SEQUENCE2::sequence_tag, sequence_t >::value &&
   ::std::is_same < typename SEQUENCE2::sequence_size, sequence_size_t < 2 > >::value;


template < typename SEQUENCE3 >
concept primitive_sequence3 =
   ::std::is_same < typename SEQUENCE3::sequence_tag, sequence_t >::value &&
   ::std::is_same < typename SEQUENCE3::sequence_size, sequence_size_t < 3 > >::value;


template < typename SEQUENCE4 >
concept primitive_sequence4 =
   ::std::is_same < typename SEQUENCE4::sequence_tag, sequence_t >::value &&
   ::std::is_same < typename SEQUENCE4::sequence_size, sequence_size_t < 4 > >::value;


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
   rectangle.left();
   rectangle.top();
   rectangle.right();
   rectangle.bottom();
};


template < typename RECTANGLE >
concept struct_rectangle = requires(RECTANGLE rectangle)
{
   { rectangle.left } -> primitive_number;
   { rectangle.top } -> primitive_number;
   { rectangle.right } -> primitive_number;
   { rectangle.bottom } -> primitive_number;
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



template<typename>
struct __is_raw_pointer_helper
   : public false_type { };

template<typename _Tp>
struct __is_raw_pointer_helper<_Tp*>
   : public true_type { };

/// is_pointer
template<typename _Tp>
struct is_raw_pointer_struct
   : public __is_raw_pointer_helper<erase_const_effemeral<_Tp>>
{ };


template<typename T>
inline constexpr bool is_raw_pointer = is_raw_pointer_struct < T >::value;


template < typename POINTER >
concept primitive_raw_pointer = ::is_raw_pointer < POINTER >;

template < typename RAW_TYPE >
concept _primitive_raw_type = 
   ::primitive_number < decay < RAW_TYPE > >
   || ::std::is_same_v < typename decay < RAW_TYPE >::RAW_TYPE_TAG, raw_type_t >;


template < typename RAW_TYPE >
concept primitive_raw_type = 
   ::_primitive_raw_type < RAW_TYPE >
   || (::std::is_bounded_array_v<RAW_TYPE>
       && _primitive_raw_type<dereference<RAW_TYPE>>);


template < typename POINTER >
concept primitive_pointer2 = 
   ::std::is_same_v < typename decay <POINTER >::POINTER_TYPE_TAG, pointer_type_t >;

template < typename OBJECT >
concept primitive_object = 
   !::is_raw_pointer < OBJECT >
   && !::is_function < OBJECT >
   && !primitive_pointer2 < OBJECT >
   && !primitive_raw_type < OBJECT >;

template < typename PARTICLE >
concept primitive_particle = ::std::is_base_of_v<::particle, PARTICLE>;


template < typename T, typename TYPE >
concept same_as = ::std::is_same < TYPE, erase_const_effemeral < T > >::value;


template < typename T, typename TYPE >
concept non_same_as = !::std::is_same < TYPE, erase_const_effemeral < T > >::value;


template < typename T, typename TYPE >
concept non_pointer_same_as = same_as < T, TYPE > && !::is_raw_pointer < T >;


template < typename T >
concept bool_type = same_as < T, bool >;

template < typename T >
concept i8_type = same_as < T, char >;

template < typename T >
concept char_type = same_as < T, char >;

template < typename A_PARTICLE >
concept a_particle = ::std::derived_from<A_PARTICLE, ::particle>;

template < typename NON_PARTICLE >
concept non_particle = !a_particle < NON_PARTICLE >;


//template < typename T, typename ...Args >
//inline T * __call__allocate(Args &&... args);
//
//template < typename T >
//inline void __call__delete(T * p);


template < primitive_character CHARACTER >
constexpr bool string_compare_prefix(::std::strong_ordering & ordering, const CHARACTER * pszA, const CHARACTER * pszB) noexcept;


template < primitive_fundamental TYPE >
constexpr bool equals(TYPE a, TYPE b) { return a == b; }


template < primitive_type TYPE >
constexpr bool equals(const TYPE & a, const TYPE & b) { return a == b; }


template < primitive_fundamental TYPE >
constexpr ::std::strong_ordering compare(TYPE a, TYPE b) { return ::std::strong_order(a, b); }


template < primitive_type TYPE >
constexpr ::std::strong_ordering compare(const TYPE & a, const TYPE & b) { return ::std::strong_order(a, b); }



template<primitive_character CHARACTER, character_count m_sizeMaximumLength>
class inline_string;


using inline_number_string = inline_string<char, 64>;




template < typename T >
concept has_string_getter = requires(T t, ::string & str)
{

   { t.as(str) } -> std::same_as < void >;

};




template < typename CONTAINER >
concept container_type = requires(CONTAINER container)
{

   {container.this_is_a_container()} -> std::same_as<void>;

};


template < typename ARRAY >
concept primitive_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   array.element_at(i);
   array.set_size(c);
};

template < typename ARRAY >
concept primitive_raw_type_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->primitive_raw_type;
   array.set_size(c);
};


template < typename ARRAY >
concept primitive_raw_pointer_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->primitive_raw_pointer;
   array.set_size(c);
};


template < typename ARRAY >
concept primitive_particle_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->primitive_pointer2;
   array.set_size(c);
};


template < typename ARRAY >
concept primitive_object_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->primitive_object;
   array.set_size(c);
};


template < typename CONTAINER >
concept primitive_container = primitive_array < CONTAINER >;

template < typename CONTAINER >
concept non_container = !primitive_container < CONTAINER >;



template < primitive_enum ENUM >
inline huge_integer as_huge_integer(const ENUM & e) { return (huge_integer)(::raw_enum_of<ENUM>) e; }




template < typename CONST_STRING_CASTABLE >
concept const_string_castable =
::std::is_convertible < CONST_STRING_CASTABLE, ::string >::value ||
::std::is_convertible < CONST_STRING_CASTABLE, ::scoped_string >::value ||
::std::is_convertible < CONST_STRING_CASTABLE, const char * >::value;



template < typename SUBPARTICLE >
concept primitive_subparticle = ::std::is_base_of_v<::subparticle, SUBPARTICLE>;


template < typename NON_SUBPARTICLE >
concept non_primitive_subparticle = !primitive_subparticle<NON_SUBPARTICLE>;



