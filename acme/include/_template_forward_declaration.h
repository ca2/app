//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/09/22 22:30
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
//
#pragma once



#include "acme/primitive/primitive/enumeration.h"


template < typename ITERATOR_TYPE >
class scoped_string_base;


using scoped_ansi_string = scoped_string_base < const ::ansi_character * >;
using scoped_wd16_string = scoped_string_base < const ::wd16_character * >;
using scoped_wd32_string = scoped_string_base < const ::wd32_character * >;
using scoped_wide_string = scoped_string_base < const ::wide_character * >;


using scoped_string = scoped_ansi_string;
using scoped_wstring = scoped_wide_string;


//// template < typename FILE >
class binary_stream;

//// template < typename FILE >
class write_text_stream;

template < typename RESULT >
class process;


template<class T>
class pointer;


template < typename HOLDEE >
class holdee
{
};



template<class T>
class pointer_array;



template<class T>
class pointer;


template<class T>
class pointer_array;


using image_pointer = ::pointer<::image>;


using mutex_pointer = ::pointer<::mutex>;


namespace write_text
{


   using font_pointer = ::pointer<font>;


} // namespace write_text





//template < typename TYPE_CHAR >
//class simple_string_base;
//
//
//using simple_ansistring = simple_string_base < ::ansi_character >;
//using simple_wd16string = simple_string_base < ::wd16_character >;
//using simple_wd32string = simple_string_base < ::wd32_character >;
//using simple_widestring = simple_string_base < ::wide_character >;


//typedef simple_ansistring simple_string;
//typedef simple_widestring simple_wstring;



//template < typename >
//constexpr bool is_const = false; // determine whether type argument is const qualified
//
//
//template < typename TYPE >
//constexpr bool is_const < const TYPE > = true;



template < typename T >
concept const_c_string =
std::is_convertible < T, const ::ansi_character * >::value ||
std::is_convertible < T, const ::wd16_character * >::value ||
std::is_convertible < T, const ::wd32_character * >::value;


template < typename T >
concept non_const_c_string =
std::is_convertible < T, ::ansi_character * >::value ||
std::is_convertible < T, ::wd16_character * >::value ||
std::is_convertible < T, ::wd32_character * >::value;

template < typename T >
concept c_string =
const_c_string < T > ||
non_const_c_string < T >;

template < typename T >
struct base_const_c_string
{

   using type =
      typename if_else <
      std::is_convertible < T, const ::ansi_character * >::value,
      const ::ansi_character *,
      typename if_else <
      std::is_convertible < T, const ::wd16_character * >::value,
      const ::wd16_character *,
      typename if_else <
      std::is_convertible < T, const ::wd32_character * >::value,
      const ::wd32_character *,
      void *
      >::type
      >::type
      >::type;

};




template<typename Type, typename RawType = Type, ::enum_type m_etypeContainer = e_type_element >
class string_array_base;





//class e_status;


template <template <class...> class Template, class... Args>
void derived_from_specialization_impl(const Template<Args...>&);

template <class T, template <class...> class Template>
concept derived_from_specialization_of = requires(const T & t) {
   derived_from_specialization_impl<Template>(t);
};

template <class... Types> struct inherits : Types... {};





//template < bool, typename T1, typename T2 >
//struct boolean_type_selection { using type = T1; };
//
//template < typename T1, typename T2 >
//struct boolean_type_selection<false, T1, T2> { using type = T2; };


template < typename T1, typename T2 >
struct largest_type_struct {
   using type = if_else< (sizeof(T1) >= sizeof(T2) ), T1, T2>;
};


template < typename T1, typename T2 >
using largest_type = typename largest_type_struct<T1, T2>::type;


template < typename T1, typename T2 >
struct largest_number_struct {
   using type = if_else < 
      ((::std::is_floating_point_v < T1 > && sizeof(T1) < sizeof(T2))
      || (::std::is_floating_point_v < T2 > && sizeof(T2) < sizeof(T1))),
      double,
      if_else < ((::std::is_floating_point_v < T1 >
      && ::std::is_floating_point_v < T2 > &&
      sizeof(T1) > sizeof(T2)) 
      || (sizeof(T1) == sizeof(T2) &&
         ::std::is_floating_point_v < T1 >)
      || (sizeof(T1) > sizeof(T2))), T1, T2 > >;
};


template < typename T1, typename T2 >
using largest_number = typename largest_number_struct<T1, T2>::type;



template < typename T1, typename T2 >
struct smallest_type_struct 
{
   using type = if_else< (sizeof(T1) < sizeof(T2)), T1, T2>;
};


template < typename T1, typename T2 >
using smallest_type = typename smallest_type_struct<T1, T2>::type;


template < typename T1, typename T2, typename T3 >
struct largest_type_of_3_struct {
   using type = largest_type < largest_type < T1, T2 >, T3 >;
};


template < typename T1, typename T2, typename T3 >
using largest_type_of_3 = typename largest_type_of_3_struct < T1, T2, T3 >::type;



template < typename TYPE, std::size_t SIZE >
using array_reference = TYPE(&)[SIZE];

namespace allocator
{


   template < typename TYPE >
   class def;

   template < typename TYPE >
   class nodef;

} // namespace allocator


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE  >, ::enum_type m_etypeContainer = e_type_element >
class array_base;

template < class TYPE, class ARG_TYPE = const TYPE & >
class row;

template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE  >, ::enum_type m_etypeContainer = e_type_element >
class array_2d;

template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE  >, ::enum_type m_etypeContainer = e_type_element >
class array;

template < typename FUNCTION >
class function;

template < class TYPE, class ARG_TYPE = const TYPE & >
class list;


template < typename T >
class single;


template < typename SINGLE >
struct make_single ;


template < typename NODE >
class node_set;


template < typename KEY, typename NODE = single < KEY > >
using set = node_set < ::make_single < NODE > >;


template < typename T1, typename T2 >
class pair;


template < typename PAIR >
class pair_map;


template < typename TYPE1, typename TYPE2, class PAIR = pair < TYPE1, TYPE2 > >
using map = pair_map < PAIR >;


template<class ENUM>
class flags;


template<class EENUM, EENUM edefault = (EENUM)0>
class base_enum;



using item_pointer = ::pointer < ::item >;

using memory_pointer = ::pointer < ::memory >;

template < typename TYPE, typename PAIR = pair < ::atom, TYPE > >
using atom_map = ::map < atom, TYPE, PAIR >;



template < typename CONTAINER >
concept container_type = requires(CONTAINER container)
{

   {container.this_is_a_container()} -> std::same_as<void>;

};


template < typename ARRAY >
concept primitive_array = requires(ARRAY array, ::index i)
{
   array.get_count();
   array.element_at(i);
};



template < class TYPE, class ARG_TYPE = const TYPE &, class ARRAY_TYPE = array < TYPE, ARG_TYPE > >
class comparable_eq_array;


template < class TYPE, class ARG_TYPE = TYPE const &, class ARRAY_TYPE = comparable_eq_array < TYPE, ARG_TYPE > >
class comparable_array;


namespace allocator
{


   template < typename TYPE >
   class raw;


   template < typename TYPE >
   class zero;


} // namespace allocator

template < typename TYPE, typename ARG_TYPE = const TYPE &, typename ALLOCATOR = ::allocator::raw < TYPE >, ::enum_type m_etypeContainer = e_type_element >
class raw_array;


template < typename POINTER, class ARRAY_TYPE = comparable_array < POINTER, POINTER, comparable_eq_array < POINTER, POINTER, raw_array < POINTER, POINTER, ::allocator::zero < POINTER > > > > >
class address_array;


class exception;


using exception_array = ::array < ::exception >;


template < typename T >
concept has_string_getter = requires(T t, ::string & str)
{

   { t.as(str) } -> std::same_as < void >;

};

using particle_array = pointer_array < particle >;



using regular_expression_pointer = ::pointer<::regular_expression::regular_expression>;




typedef address_array < const char * > const_char_ptra;

typedef address_array < void * > void_ptra;


using particle_address_array = address_array < particle * >;


using file_pointer = ::pointer<::file::file>;


using memory_file_pointer = ::pointer<::memory_file>;


using folder_pointer = ::pointer<::folder>;


template < typename T >
class c_number;


using wparam = c_number<iptr>;


template < typename T >
concept an_object = !std::is_pointer < T >::value
                    && !std::is_integral < T >::value
                    && !std::is_enum < T >::value
                    && !std::is_floating_point < T >::value;


template<typename T>
inline ::pointer < T > pointer_transfer(T * p);


#define __new(...) ::pointer_transfer( memory_new __VA_ARGS__ )


template < typename SEQUENCE >
class sequencer;


using manager_pointer = ::pointer<manager>;
using context_pointer = ::pointer<context>;


using topic_pointer = ::pointer<topic>;
using extended_topic_pointer = ::pointer<extended_topic>;

template < typename SEQUENCE >
class sequencer;

template < typename SEQUENCE >
class sequence;


template < typename FUNCTION >
class function;

using procedure = ::function < void() >;

using procedure_array = ::comparable_array < ::procedure >;

using procedure_map = ::atom_map < ::procedure_array >;

using procedure_list = ::list < ::procedure >;




template < typename TYPE, ::enum_type m_etypeContainer = e_type_element >
class unique_number_sort_array;


template < typename TYPE, ::enum_type m_etypeContainer = e_type_element >
class numeric_array;


using i8_array = numeric_array < i8 >;
using i16_array = numeric_array < i16 >;
using i32_array = numeric_array < i32 >;
using i64_array = numeric_array < i64 >;

using u8_array = numeric_array < u8 >;
using u16_array = numeric_array < u16 >;
using u32_array = numeric_array < u32 >;
using u64_array = numeric_array < u64 >;

using f32_array = numeric_array < f32 >;
using f64_array = numeric_array < f64 >;


using i32_array_array = ::array < i32_array >;

using f32_array_array = ::array < f32_array >;
using f64_array_array = ::array < f64_array >;


using index_array = numeric_array < ::index >;
using count_array = numeric_array < ::count >;


using u32_array = numeric_array < ::u32 >;


using unique_i32_sort_array = unique_number_sort_array < i32 >;
using unique_i64_sort_array = unique_number_sort_array < i64 >;


#ifdef OS64BIT


using iptr_array = i64_array;
using uptr_array = u64_array;

using unique_iptr_sort_array = unique_i64_sort_array;


#else


using iptr_array = i32_array;
using uptr_array = u32_array;

using unique_iptr_sort_array = unique_i32_sort_array;


#endif

using f32_array = numeric_array < ::f32 >;
using f64_array = numeric_array < ::f64 >;

using strsize_array = iptr_array;

using process_identifier_array = ::numeric_array < process_identifier >;

//using strsize_ptr_array = ptr_array < strsize *  >;


using byte_array = u8_array;

using task_pointer = ::pointer < task >;


//#include "acme/primitive/primitive/_u32hash.h"


CLASS_DECL_ACME task_pointer fork(::particle * pparticle, const ::procedure & procedure);


namespace draw2d
{


   using graphics_pointer = ::pointer<graphics>;


} // namespace draw2d





//template<typename TYPE>
//inline bool is_ok(const ::pointer<TYPE>& p);
//
//
//template<typename TYPE>
//inline bool nok(TYPE & t)
//{
//
//   return !::is_ok(t);
//
//}
//





template < typename TYPE, std::size_t SIZE >
inline std::size_t item_count(array_reference < TYPE, SIZE > &) { return SIZE; }


template < typename T >
inline ::u8 u8_clip(const T & t) { return ((::u8)(((t) < (::u8)0) ? (::u8)0 : (((t) > (::u8)255) ? (::u8)255 : (::u8)t))); }


template < typename A, typename B >
void __swap(A & a, B & b)
{

   A aCopy = a;

   a = b;

   b = aCopy;

}



typedef pointer_array < ::particle > particle_array;



template <class TYPEA, class TYPEB, class ARRAYA = array < TYPEA >, class ARRAYB = array < TYPEB > >
class spreadset;


using i32_spreadset = spreadset < i32, i32, unique_i32_sort_array, unique_i32_sort_array >;

using i64_spreadset = spreadset < i64, i64, unique_i64_sort_array, unique_i64_sort_array >;





template < typename TYPE, std::size_t SIZE >
inline array_reference < TYPE, SIZE >& zero(TYPE(&)[SIZE]);


template < typename TYPE >
inline TYPE& zero(TYPE & type);


template < typename TYPE, std::size_t Size >
inline bool __is_zero(TYPE(&array)[Size]);



//#include "acme/primitive/time/as_string.h"



//struct true_type
//{
//};
//struct false_type
//{
//};






// raw_type discorvery
// raw_type discorvery
// raw_type discorvery


template<typename POINTER>
class raw_pointer
{
public:

   using RAW_POINTER = POINTER;

};


template<typename TYPE>
class raw_type
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<TYPE*>
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<TYPE*&>
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<const TYPE*>
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<const TYPE*&>
{
public:

   using RAW_TYPE = TYPE;

};







namespace write_text
{



   using font_enumeration_item_array = pointer_array < font_enumeration_item >;


} // namespace write_text





namespace mathematics
{

   template<typename T>
   class complex;


} // namespace mathematics



template < typename HOLDEE >
class ___shape;



namespace _std
{


   template<class T>
   void __swap(T& a, T& b)
   {
      T c(a);
      a = b;
      b = c;
   }


}




#define return_(y, x) {y = x; return;}






template<typename POINTER_TYPE>
class ptr_array;


using object_ptra = pointer_array < ::matter >; // Please use just for keeping non-member-based references.

using matter_array = pointer_array < ::matter >; // Please use just for keeping non-member-based references.

using task_array = pointer_array < ::task >; // Please use just for keeping non-member-based references.


template < typename SEQUENCE >
class sequence;

#ifdef WINDOWS

template < typename POINTER_TYPE >
class cotaskptr;

template < typename POINTER_TYPE >
class cotaskptr_array;

#endif


using arguments = payload_array;


template<class T>
class guard_pointer;





template < typename SEQUENCE >
class sequencer;


template < class T >
inline void __dynamic_cast(T*& ptarget, T* psource);


template < class T , typename T2 >
inline void __dynamic_cast(T*& ptarget, T2* psource);


using enum_application_capability_array = ::comparable_array < enum_application_capability >;



// From subject_listener from apex_database by camilo on day after ThomasBirthday2021 07:26 BRT
#pragma once


using signal_handler = ::function < void(::topic*, ::context*) >;
//{
//public:
//
//
//
//   using function::function;
//
//
//   ~handle_function() {}
//   //method(const ::matter_pointer & pmatter) : matter_pointer(pmatter) { }
//   //method(const ::method & method) : matter_pointer(method) { }
//
//
//   //inline void operator()() const;
//
//   //void operator()(::topic * ptopic, ::context * pcontext) 
//   //{
//
//   //   this-(ptopic, pcontext);
//
//   //}
//
//   //template < typename PRED >
//   //void pred(PRED pred);
//
//   //inline method & operator = (const ::method & method) { m_pmatter = method.m_pmatter; return *this; }
//   //method & operator = (const ::payload & payload);
//
//
//};
//
//
////template < typename PREDICATE >
////::matter_pointer __handle_function(PREDICATE predicate)
////{
////
////   return __new(han<PREDICATE>(predicate));
////
////}


// hi5 and shegotmad
consteval auto as_const(auto asconst)
{

   return asconst;

}


namespace acme
{


   using session_map = ::map < index, ::pointer < ::acme::session > >;


} // namespace acme


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


template < typename TYPE >
constexpr memsize index_of(const TYPE * p, const TYPE * pBegin);


template<typename T>
struct dereference_struct { using type = T; };
template<typename T>
struct dereference_struct<T *> { using type = T; };

template < typename T >
using dereference = typename dereference_struct < T >::type;


template<primitive_character CHARACTER, strsize m_sizeMaximumLength>
class inline_string;


using inline_number_string = inline_string<char, 64>;



