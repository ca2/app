// Created by camilo on 2022-11-22 <3ThomasBorregaardSorensen!!
//
//  _numeric_concepts.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/22.
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


struct point2_t{};
struct size2_t{};
struct matrix_t{};


#include <format>



template < typename ITERATOR_TYPE >
class scoped_string_base;



template < typename SEQUENCE >
concept prototype_sequence = ::is_same < typename SEQUENCE::sequence_tag, sequence_t >;

template<typename SEQUENCE2>
concept prototype_sequence2 = requires(SEQUENCE2 s2) {

   s2.x;
   s2.y;

};
template<typename SEQUENCE3>
concept prototype_sequence3 = requires(SEQUENCE3 s3) {
   s3.x;
   s3.y;
   s3.z;
};
template<typename SEQUENCE4>
concept prototype_sequence4 = requires(SEQUENCE4 s4) {
   s4.x;
   s4.y;
   s4.z;
   s4.w;
};

template < typename ENUM >
concept prototype_enum = 
   std::is_enum < ::decay < ENUM > >::value 
   || ::is_same < typename ENUM::ENUM_TYPE_TAG, enum_type_t >;


template < typename BLOCK >
concept prototype_block = ::is_same<typename BLOCK::PRIMITIVE_BLOCK_TAG, PRIMITIVE_BLOCK_TAG_TYPE >;

template< typename RAW_ARRAY >
concept prototype_raw_array = ::is_raw_array < RAW_ARRAY>;


//template < typename T >
//concept prototype_integral_up_to_32_bit =
//(std::is_integral_v < T > ||
//std::is_enum < T >::value ||
//::is_same < T, ::e_status >::value) && sizeof(T) <= 4;

template < typename T >
concept prototype_integral_up_to_32_bit =
(std::is_integral_v < T >) && sizeof(T) <= 4;

template < typename T >
concept prototype_integer = std::is_integral < T >::value;

template < typename T >
concept prototype_natural = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept prototype_signed = std::is_integral < T >::value && std::is_signed < T >::value;

template < typename T >
concept prototype_signed_not_8bit = prototype_signed < T > && sizeof(T) != 1;

template < typename T >
concept prototype_unsigned = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept prototype_unsigned_not_8bit = prototype_unsigned < T > && sizeof(T) != 1;

template < typename FLOATING >
concept prototype_floating = std::is_floating_point < ::decay < FLOATING > >::value;



template < typename AGGREGATE >
concept prototype_aggregate = ::std::is_aggregate_v < AGGREGATE >;


template < typename T >
concept prototype_fundamental = std::is_fundamental < T >::value || std::is_pointer < T >::value;

template < typename T >
concept prototype_type = !std::is_fundamental < T >::value && !std::is_pointer < T >::value;

template<typename ITERATOR_TYPE>
class range;

template < typename T >
concept prototype_range = ::std::is_base_of_v < ::range< typename T::this_iterator >, T >;

template < typename T >
concept std_range = requires(const T &t)
{
t.begin();
   t.end();

};


template < typename T, typename ITERATOR_TYPE >
concept typed_range = 
prototype_range < T >
|| ::is_same < non_const < ITERATOR_TYPE >, non_const < typename T::this_iterator > >;


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
concept prototype_character =
   ::is_same < ::non_const<T>, char> || 
   ::is_same < ::non_const<T>, char8_t> ||
   ::is_same < ::non_const<T>, wchar_t> ||
   ::is_same < ::non_const<T>, ::ansi_character> ||
   ::is_same < ::non_const<T>, ::wd16_character> || 
   ::is_same < ::non_const<T>, ::wd32_character>;

template<typename T>
concept const_pointer_to_prototype_character =
   ::is_raw_pointer<T> 
   && ::is_const<::non_pointer<T>>
   && prototype_character<::non_const<::non_pointer<T>>>;

template<typename T>
struct is_const_prototype_character_array : ::false_type
{
};




template<typename CHARACTER, std::size_t N>
   requires (prototype_character<CHARACTER>)
struct is_const_prototype_character_array<const CHARACTER[N]> : ::true_type
{
   using char_type = CHARACTER;
   static constexpr std::size_t size = N;
};



template<typename T>
struct is_const_non_prototype_character_array : ::false_type
{
};



template<typename NONCHARACTER, std::size_t N>
   requires (!prototype_character<NONCHARACTER>)
            struct is_const_non_prototype_character_array<const NONCHARACTER[N]> : ::true_type
{
   using type = NONCHARACTER;
   static constexpr std::size_t size = N;
};


            
template<typename T>
struct is_non_prototype_character_array : ::false_type
{
};
template<typename NONCHARACTER, std::size_t N>
   requires (!prototype_character<NONCHARACTER>)
            struct is_non_prototype_character_array<NONCHARACTER[N]> : ::true_type
{
   using type = NONCHARACTER;
   static constexpr std::size_t size = N;
};


template<typename NONCHARACTER, std::size_t N>
   requires (!prototype_character<NONCHARACTER>)
            struct is_non_prototype_character_array<const NONCHARACTER[N]> : ::true_type
{
   using type = NONCHARACTER;
   static constexpr std::size_t size = N;
};


template<typename T>
concept const_array_of_prototype_character = is_const_prototype_character_array<T>::payload;

template<typename T>
concept const_array_of_non_prototype_character = is_const_non_prototype_character_array<T>::payload;

template<typename T>
concept array_of_non_prototype_character = 
   ::prototype_raw_array<T> && 
   !prototype_character<::decay_array<T>>;


template < typename T >
concept prototype_character_iterator =
::is_same < T, unsigned char * > ||
::is_same < T, char * > ||
::is_same < T, char8_t * > ||
::is_same < T, wchar_t * > ||
::is_same < T, ::ansi_character * > ||
::is_same < T, ::wd16_character * > ||
::is_same < T, ::wd32_character * > ||
::is_same < T, const unsigned char * > ||
::is_same < T, const_char_pointer > ||
::is_same < T, const char8_t * > ||
::is_same < T, const wchar_t * > ||
::is_same < T, const_char_pointer > ||
::is_same < T, const ::wd16_character * > ||
::is_same < T, const ::wd32_character * >;


template < typename T >
concept prototype_character_iterator_reference =
::is_same < T, unsigned char * & > ||
::is_same < T, char * & > ||
::is_same < T, char8_t *& > ||
::is_same < T, wchar_t * & > ||
::is_same < T, ::ansi_character * & > ||
::is_same < T, ::wd16_character * & > ||
::is_same < T, ::wd32_character * & > ||
::is_same < T, const unsigned char * & > ||
::is_same < T, const_char_pointer &> ||
::is_same < T, const char8_t *& > ||
::is_same < T, const wchar_t * & > ||
::is_same < T, const_char_pointer &> ||
::is_same < T, const ::wd16_character * & > ||
::is_same < T, const ::wd32_character * & >;


template < typename T, typename CHARACTER >
concept typed_primitive_character_iterator_reference =
::is_same < T, CHARACTER*& > ||
::is_same < T, const CHARACTER*& >;

template < typename T, typename CHARACTER >
concept other_primitive_character_iterator_reference =
prototype_character < T > &&
!::is_same < T, CHARACTER*& > &&
!::is_same < T, const CHARACTER*& >;

template < typename T, typename CHARACTER >
concept other_primitive_character =
prototype_character < T > &&
!::is_same < T, CHARACTER >;


template < typename CHARACTER_POINTER >
concept character_pointer =
::std::is_pointer_v<CHARACTER_POINTER>
&& !::std::is_array_v<CHARACTER_POINTER>
&& prototype_character<::non_const <::non_pointer<CHARACTER_POINTER>>>;


template < typename TYPED_CHARACTER_POINTER, typename CHARACTER >
concept typed_character_pointer = 
::std::is_pointer_v<TYPED_CHARACTER_POINTER> 
&& !::std::is_array_v<TYPED_CHARACTER_POINTER>
&& ::is_same < ::non_const<CHARACTER>, ::non_const <::non_pointer<TYPED_CHARACTER_POINTER>>>;


template < typename OTHER_CHARACTER_POINTER, typename CHARACTER >
concept other_character_pointer =
::std::is_pointer_v<OTHER_CHARACTER_POINTER>
&& !::std::is_array_v<OTHER_CHARACTER_POINTER>
&& prototype_character< ::non_const < ::non_pointer<OTHER_CHARACTER_POINTER>>>
&& !::is_same < CHARACTER, ::non_const <::non_pointer<OTHER_CHARACTER_POINTER>>>;


//template < typename CHARACTER_POINTER >
//concept character_array =
//::std::is_pointer_v<CHARACTER_POINTER>
//&& ::std::is_array_v<CHARACTER_POINTER>
//&& prototype_character<::non_const <::non_pointer<CHARACTER_POINTER>>>;
//
//
//template < typename TYPED_CHARACTER_POINTER, typename CHARACTER >
//concept typed_character_array =
//::std::is_pointer_v<TYPED_CHARACTER_POINTER>
//&& ::std::is_array_v<CHARACTER_POINTER>
//&& ::is_same < CHARACTER, ::non_const <::non_pointer<TYPED_CHARACTER_POINTER>>>;

template < typename ITERATOR_TYPE >
class character_range;

template <typename ITERATOR_TYPE>
struct std::formatter<::character_range<ITERATOR_TYPE>>;



template < typename CHARACTER_RANGE >
concept prototype_character_range =
(::std::is_base_of_v < ::character_range< const typename CHARACTER_RANGE::CHARACTER* >, CHARACTER_RANGE >
&& prototype_character < typename CHARACTER_RANGE::CHARACTER > )||
(::is_same < ::character_range< const typename CHARACTER_RANGE::ITEM* >, CHARACTER_RANGE > &&
prototype_character < typename CHARACTER_RANGE::ITEM >);



template < typename TYPED_CHARACTER_RANGE, typename CHARACTER >
concept typed_character_range =
(::std::is_base_of_v < ::character_range< const CHARACTER* >, TYPED_CHARACTER_RANGE >
   || ::is_same < ::character_range< const CHARACTER* >, TYPED_CHARACTER_RANGE >)
   && prototype_character < CHARACTER >;


template < typename OTHER_CHARACTER_RANGE, typename CHARACTER >
concept other_character_range = 
(::std::is_base_of_v < ::character_range< const typename OTHER_CHARACTER_RANGE::CHARACTER* >, OTHER_CHARACTER_RANGE >
   && other_primitive_character < typename OTHER_CHARACTER_RANGE::CHARACTER, CHARACTER >) ||
   (::is_same < ::character_range< const typename OTHER_CHARACTER_RANGE::ITEM* >, OTHER_CHARACTER_RANGE > &&
      other_primitive_character < typename OTHER_CHARACTER_RANGE::ITEM, CHARACTER >);


struct ITERATOR_TYPE_TAG {};

template < typename ITERATOR >
concept prototype_iterator = ::is_same<typename ITERATOR::TYPE_TAG, ITERATOR_TYPE_TAG >;


template < typename TYPE >
struct for_type {};


namespace comparison
{


   template < typename ORDERING, typename TYPE >
   concept ordering = ::is_same<typename ORDERING::ORDERING, for_type < TYPE > >;

   template < typename EQUALITY, typename TYPE >
   concept equality = ::is_same<typename EQUALITY::EQUALITY, for_type < TYPE > >;


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


using ansi_string = string_base < const_char_pointer >;
using wd16_string = string_base < const ::wd16_character * >;
using wd32_string = string_base < const ::wd32_character * >;
using wide_string = string_base < const ::wide_character * >;
using string = ::ansi_string;
using wstring = ::wide_string;



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
//::is_same<typename HANDLER::ORDERING, ORDERING_HANDLER_TAG >
//&& ::is_same<typename HANDLER::ORDERING, ORDERING_HANDLER_TAG >;


//template <typename COMPARE_ITEM, typename ITEM>
//concept compare_predicate = ::std::convertible_to<COMPARE_ITEM,::function<::std::strong_ordering(ITEM, ITEM)> >
//|| ::std::convertible_to<COMPARE_ITEM,::std::function< ::strong_ordering(const ITEM &, const ITEM &)>>;
//
//


//template < typename BLOCK >
//concept prototype_block = requires(BLOCK block)
//{
//
//   block.data();
//   block.size();
//   block.length_in_bytes();
//
//};


//#ifdef __ANDROID__
//
//namespace std
//{
//   template<class FROM, class TO>
//   concept convertible_to = ::std::is_convertible_v<FROM, TO>;
//
//}
//#endif



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
//concept prototype_container = ::is_same < typename CONTAINER::PRIMITIVE_CONTAINER_TAG, PRIMITIVE_CONTAINER_TAG_TYPE >;

template < typename PAYLOAD >
concept prototype_payload = 
::std::is_base_of_v < ::payload, PAYLOAD >
|| ::is_same < ::payload, PAYLOAD >;


template < typename A_CONST >
concept prototype_const = ::std::is_const < A_CONST > ::value;

template < typename NON_CONST >
concept prototype_non_const = !prototype_const < NON_CONST >;

template < typename HAS_AS_STRING_NOT_PAYLOAD >
concept has_as_string_not_payload = has_as_string < HAS_AS_STRING_NOT_PAYLOAD > && !prototype_payload<HAS_AS_STRING_NOT_PAYLOAD>;


template < typename ATOM >
concept prototype_atom = ::is_same < typename ATOM::PRIMITIVE_ATOM_TAG, PRIMITIVE_ATOM_TAG_TYPE >;

template < typename STRING >
concept prototype_string = ::is_same < typename STRING::PRIMITIVE_STRING_TAG, PRIMITIVE_STRING_TAG_TYPE >;

template < typename TYPED_PRIMITIVE_STRING, typename CHARACTER >
concept typed_primitive_string =
(::std::is_base_of_v < ::string_base< const CHARACTER* >, TYPED_PRIMITIVE_STRING >
   || ::is_same < ::string_base< const CHARACTER* >, TYPED_PRIMITIVE_STRING >)
   && prototype_character < CHARACTER >;


template < typename OTHER_PRIMITIVE_STRING, typename CHARACTER >
concept other_primitive_string =
(::std::is_base_of_v < ::string_base< const typename OTHER_PRIMITIVE_STRING::CHARACTER* >, OTHER_PRIMITIVE_STRING >
   && other_primitive_character < typename OTHER_PRIMITIVE_STRING::CHARACTER, CHARACTER >) ||
   (::is_same < ::string_base< const typename OTHER_PRIMITIVE_STRING::ITEM* >, OTHER_PRIMITIVE_STRING > &&
      other_primitive_character < typename OTHER_PRIMITIVE_STRING::ITEM, CHARACTER >);

template < typename SCOPED_STRING >
concept prototype_scoped_string = ::is_same < typename SCOPED_STRING::PRIMITIVE_SCOPED_STRING_TAG, PRIMITIVE_SCOPED_STRING_TAG_TYPE >;



template < typename T >
concept character_range_not_string = prototype_character_range<T> && !prototype_string<T>;


template < typename T >
concept character_range_not_string_neither_scoped_string = prototype_character_range<T> && !prototype_string<T> && !prototype_scoped_string<T>;




template < typename NUMBER >
concept prototype_number =
prototype_integral < NUMBER > ||
prototype_floating < NUMBER > ||
prototype_enum < NUMBER >;


template < typename POINT >
concept raw_primitive_point = requires(POINT point)
{
   { point.x }->prototype_number;
   { point.y }->prototype_number;
};


template < typename POINT >
concept function_point = requires(POINT point)
{
   { point.semantic_t() } ->::std::convertible_to<point2_t>;
   { point.x }->prototype_number;
   { point.y }->prototype_number;
};

template < typename POINT >
concept struct_point = requires(POINT point)
{
   { point.semantic_t() } ->::std::convertible_to<point2_t>;
   { point.x }->prototype_number;
   { point.y }->prototype_number;
};


template < typename POINT >
concept prototype_point = function_point<POINT> || struct_point<POINT >;


//template < typename SEQUENCE2 >
//concept prototype_sequence2 =
//   ::is_same < typename SEQUENCE2::sequence_tag, sequence_t > &&
//   ::is_same < typename SEQUENCE2::sequence_size, sequence_size_t < 2 > >;
//
//
//template < typename SEQUENCE3 >
//concept prototype_sequence3 =
//   ::is_same < typename SEQUENCE3::sequence_tag, sequence_t > &&
//   ::is_same < typename SEQUENCE3::sequence_size, sequence_size_t < 3 > >;
//
//
//template < typename SEQUENCE4 >
//concept prototype_sequence4 =
//   ::is_same < typename SEQUENCE4::sequence_tag, sequence_t > &&
//   ::is_same < typename SEQUENCE4::sequence_size, sequence_size_t < 4 > >;


template < typename POLE >
concept prototype_pole = requires(POLE pole)
{
   { pole.x }->prototype_number;
   { pole.y }->prototype_number;
   { pole.z }->prototype_number;
};


template < typename POINT >
concept prototype_XY = requires(POINT point)
{
   point.X;
   point.Y;
};




template < typename SIZE >
concept function_size = requires(SIZE s)
{
   { s.semantic_t() } ->::std::convertible_to<size2_t>;
   { s.x }->prototype_number;
   { s.y }->prototype_number;
};


template < typename SIZE >
concept struct_size = requires(SIZE s)
{
   { s.semantic_t() } ->::std::convertible_to<size2_t>;
   { s.x }->prototype_number;
   { s.y }->prototype_number;
};



template < typename SIZE >
concept prototype_size = function_size <SIZE> || struct_size <SIZE>;


template < typename Dimension >
concept prototype_Dimension = requires(Dimension dimension)
{
   dimension.Width;
   dimension.Height;
};


template < typename DIMENSION >
concept prototype_dimension = requires(DIMENSION dimension)
{
   dimension.width;
   dimension.height;
};


template<typename RECTANGLE>
concept function_rectangle = requires(RECTANGLE rectangle) {
   rectangle.left;
   rectangle.top;
   rectangle.right;
   rectangle.bottom;
};


template<typename RECTANGLE>
concept struct_rectangle = requires(RECTANGLE rectangle) {
   { rectangle.left } -> prototype_number;
   { rectangle.top } -> prototype_number;
   { rectangle.right } -> prototype_number;
   { rectangle.bottom } -> prototype_number;
};


template < typename RECTANGLE >
concept prototype_rectangle = 
   function_rectangle<RECTANGLE> 
   || struct_rectangle<RECTANGLE>;




template < typename RECTANGLE >
concept prototype_XYDim = requires(RECTANGLE rectangle)
{
   rectangle.X;
   rectangle.Y;
   rectangle.Width;
   rectangle.Height;
};

template < typename RECTANGLE >
concept struct_xydim = requires(RECTANGLE rectangle)
{
   rectangle.x;
   rectangle.y;
   rectangle.width;
   rectangle.height;
};

template < typename RECTANGLE >
concept prototype_xydim = struct_xydim<RECTANGLE> && !prototype_rectangle<RECTANGLE>;
// {
//    rectangle.x;
//    rectangle.y;
//    rectangle.width;
//    rectangle.height;
// };


template < typename RECTANGLE >
concept prototype_origin_size = requires(RECTANGLE rectangle)
{
   { rectangle.origin }->raw_primitive_point;
   { rectangle.size }->prototype_dimension;
};


//template < typename ORIGIN_SIZE >
//concept origin_size = requires(ORIGIN_SIZE origin_size)
//{
//
//   { origin_size.origin } -> prototype_point;
//   { origin_size.size } -> prototype_dim;
//
//};



template < prototype_number NUMBER >
struct argument_of_struct < NUMBER >
{

   using type = NUMBER;

};



template < prototype_number NUMBER >
class point_type;


template < prototype_number NUMBER >
class size_type;


template < prototype_number NUMBER >
class rectangle_type;



template<typename SUBPARTICLE>
concept prototype_subparticle = ::std::is_base_of_v<::subparticle, SUBPARTICLE>;



//
//
//template < prototype_number NUMBER1, prototype_number NUMBER2 >
//inline void copy(NUMBER1& number1, const NUMBER2& number2)
//{
//
//   number1 = (NUMBER1)number2;
//
//}
//



template < typename RAW_TYPE >
concept _primitive_raw_type = 
   ::prototype_number < decay < RAW_TYPE > >
   || ::is_same < typename decay < RAW_TYPE >::RAW_TYPE_TAG, raw_type_t >;


template < typename RAW_TYPE >
concept prototype_raw_type = 
   ::_primitive_raw_type < RAW_TYPE >
   || (::std::is_bounded_array_v<RAW_TYPE>
       && _primitive_raw_type<dereference<RAW_TYPE>>);


template < typename POINTER >
concept prototype_pointer2 = 
   ::is_same < typename decay <POINTER >::POINTER_TYPE_TAG, pointer_type_t >;

template < typename OBJECT >
concept prototype_object = 
   !::is_raw_pointer < OBJECT >
   && !::is_function < OBJECT >
   && !prototype_pointer2 < OBJECT >
   && !prototype_raw_type < OBJECT >;

template < typename PARTICLE >
concept prototype_particle = ::std::is_base_of_v<::particle, PARTICLE>;


template < typename T, typename TYPE >
concept same_as = ::is_same < TYPE, erase_const_effemeral < T > >;


template < typename T, typename TYPE >
concept non_same_as = !::is_same < TYPE, erase_const_effemeral < T > >;


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
//inline T * __call_allocate(Args &&... args);
//
//template < typename T >
//inline void __call__delete(T * p);


template < prototype_character CHARACTER >
constexpr bool string_compare_prefix(::std::strong_ordering & ordering, const CHARACTER * pszA, const CHARACTER * pszB) noexcept;


template < prototype_fundamental TYPE >
constexpr bool equals(TYPE a, TYPE b) { return a == b; }


template < prototype_type TYPE >
constexpr bool equals(const TYPE & a, const TYPE & b) { return a == b; }


template < prototype_fundamental TYPE >
constexpr ::std::strong_ordering compare(TYPE a, TYPE b) { return ::std::strong_order(a, b); }


template < prototype_type TYPE >
constexpr ::std::strong_ordering compare(const TYPE & a, const TYPE & b) { return ::std::strong_order(a, b); }



template<prototype_character CHARACTER, character_count m_sizeMaximumLength>
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
concept prototype_array = requires (const ARRAY & array)
{

   array.array_range_ok();

};


template < typename LIST >
concept prototype_list = requires(const LIST & list)
{

   list.list_base_ok();

};


template < typename MAP >
concept prototype_map = requires(const MAP & map)
{

   map.pair_map_base_ok();

};


template < typename ARRAY >
concept prototype_raw_type_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->prototype_raw_type;
   array.set_size(c);
};


template < typename ARRAY >
concept prototype_raw_pointer_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->prototype_raw_pointer;
   array.set_size(c);
};


template < typename ARRAY >
concept prototype_particle_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->prototype_pointer2;
   array.set_size(c);
};


template < typename ARRAY >
concept prototype_object_array = requires(ARRAY array, ::collection::index i, ::collection::count c)
{
   array.get_count();
   {array.element_at(i)}->prototype_object;
   array.set_size(c);
};


template < typename CONTAINER >
concept prototype_container =
   prototype_array < CONTAINER >
|| prototype_list < CONTAINER >
|| prototype_map < CONTAINER >;

template < typename CONTAINER >
concept non_container = !prototype_container < CONTAINER >;



template < prototype_enum ENUM >
inline long long as_long_long(const ENUM & e) { return (long long)(::raw_enum_of<ENUM>) e; }


template<typename ITERATOR_TYPE>
class character_range;


template<typename ITERATOR_TYPE>
class const_string_range;



using const_ansi_range = ::const_string_range < const ::ansi_character* >;
using const_wd16_range = ::const_string_range < const ::wd16_character* >;
using const_wd32_range = ::const_string_range < const ::wd32_character* >;
using const_wide_range = ::const_string_range < const ::wide_character* >;



template < typename CONST_STRING_CASTABLE >
concept const_string =
::std::is_convertible < CONST_STRING_CASTABLE, ::const_ansi_range >::value ||
::std::is_convertible < CONST_STRING_CASTABLE, ::string >::value ||
::std::is_convertible < CONST_STRING_CASTABLE, ::scoped_string >::value;


template < typename CONST_STRING_CASTABLE >
concept const_string_castable =
::std::is_convertible < CONST_STRING_CASTABLE, ::string >::value ||
::std::is_convertible < CONST_STRING_CASTABLE, ::scoped_string >::value ||
::std::is_convertible < CONST_STRING_CASTABLE, const_char_pointer >::value;





template < typename NON_SUBPARTICLE >
concept non_primitive_subparticle = !prototype_subparticle<NON_SUBPARTICLE>;


template<typename Type, typename RawType = Type, ::enum_type t_etypeContainer = e_type_element >
class string_base_array;


using string_array_base = string_base_array < string, string, e_type_string_array >;
using wstring_array_base = string_base_array < wstring, wstring >;


using string_array = ::comparable_array_particle < string_array_base >;
using wstring_array = ::comparable_array_particle < wstring_array_base >;


template < typename POINTER_BUT_NO_INTEGRAL, typename TYPE >
concept pointer_but_not_integral = ::std::convertible_to < POINTER_BUT_NO_INTEGRAL, TYPE * > && !prototype_integral < POINTER_BUT_NO_INTEGRAL >;


template <class>
constexpr bool is_lvalue_reference = false; // determine whether type argument is an lvalue reference

template <class _Ty>
constexpr bool is_lvalue_reference<_Ty&> = true;


template <class _Ty>
constexpr _Ty&& land(_Ty&& t, non_reference < _Ty>& _Arg) noexcept {
   return t = static_cast<_Ty&&>(_Arg);
}

template <class _Ty>
constexpr _Ty&& land(_Ty&& t, non_reference < _Ty>&& _Arg) noexcept
{
   static_assert(!is_lvalue_reference<_Ty>, "bad argument");
   return t = static_cast<_Ty&&>(_Arg);
}

template < typename T >
concept generic_range = requires(const T & t)
{

   t.begin();
   t.end();

};


//template < typename T >
//concept container_range =
//::std::is_base_of_v < ::range< typename T::this_iterator >, T >
//&& !::std::is_base_of_v < ::character_range< typename T::this_iterator >, T >;



template < typename T >
concept container_range =
generic_range < T >
&& !::std::is_base_of_v < ::character_range< typename T::this_iterator >, T >;

