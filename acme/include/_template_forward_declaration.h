//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 22:30
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
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


template<typename TYPE>
struct const_of_struct
{
   using CONST_OF_TYPE = const TYPE;
};
template<typename TYPE>
struct const_of_struct<TYPE &>
{
   using CONST_OF_TYPE = const TYPE &;
};
template<typename TYPE>
struct const_of_struct< TYPE *>
{
   using CONST_OF_TYPE = const TYPE *;
};
template<typename TYPE>
struct const_of_struct< TYPE const &>
{
   using CONST_OF_TYPE = const TYPE &;
};
template<typename TYPE>
struct const_of_struct < TYPE * const>
{
   using CONST_OF_TYPE = const TYPE *;
};
template<typename TYPE>
struct const_of_struct< TYPE const && >
{
   using CONST_OF_TYPE = const TYPE &&;
};


//template < typename FUNCTION  >
//struct const_of_struct < void(*FUNCTION) >
//{
//
//   using CONST_OF_TYPE = FUNCTION;
//
//};
//
//template < typename FUNCTION, typename RETURN_TYPE  >
//struct const_of_struct < RETURN_TYPE( *FUNCTION) >
//{
//
//   using CONST_OF_TYPE = FUNCTION;
//
//};
//
//
//template < typename FUNCTION, typename RETURN_TYPE, typename... TYPES >
//struct const_of_struct < RETURN_TYPE( *FUNCTION) (TYPES...) >
//{
//
//   using CONST_OF_TYPE = FUNCTION;
//
//};
//
//
//template < typename FUNCTION, typename... TYPES >
//struct const_of_struct < void( *FUNCTION)(TYPES...) >
//{
//
//   using CONST_OF_TYPE = FUNCTION;
//
//};



//template <class... Args>
//struct all_s :std::false_type {};
//
//template <>
//struct all_s<size_t> :std::true_type {};
//
//template <class... Args>
//struct all_s<size_t, Args...> :all_s<Args...> {};
//template <class... Args>
//concept all_s_con = all_s<Args...>::value;
//
//template<class C, class R, class Fun>
//struct fun_all_s :std::false_type {};
//template<class C, class R, class... Args>
//   requires all_s_con<Args...>
//struct fun_all_s<C, R, R(C &, Args...)> :std::true_type {};
//
//template<class C, typename Policy>
//concept FooConcept = fun_all_s<C, typename C::value_type, decltype(Policy::foo)>::value;





template<typename TYPE>
using const_of = typename const_of_struct<TYPE>::CONST_OF_TYPE;






// erase_const
// erase_const
// erase_const

template<typename TYPE>
struct erase_const
{
   using NON_CONST_TYPE = TYPE;
};
template<typename TYPE>
struct erase_const<TYPE &>
{
   using NON_CONST_TYPE = TYPE &;
};
template<typename TYPE>
struct erase_const<const TYPE>
{
   using NON_CONST_TYPE = TYPE;
};
template<typename TYPE>
struct erase_const<const TYPE &>
{
   using NON_CONST_TYPE = TYPE &;
};
template<typename TYPE>
struct erase_const<const TYPE *>
{
   using NON_CONST_TYPE = TYPE *;
};
template<typename TYPE>
struct erase_const<const TYPE &&>
{
   using NON_CONST_TYPE = TYPE &&;
};
template<typename TYPE>
using non_const = typename erase_const<TYPE>::NON_CONST_TYPE;




template<typename TYPE>
struct erase_reference
{
   using NON_REFERENCE_TYPE = TYPE;
};

template<typename TYPE>
struct erase_reference<TYPE &>
{
   using NON_REFERENCE_TYPE = TYPE;
};

template<typename TYPE>
struct erase_reference<const TYPE &>
{
   using NON_REFERENCE_TYPE = const TYPE;
};

template<typename TYPE>
struct erase_reference<TYPE &&>
{
   using NON_REFERENCE_TYPE = TYPE;
};

template<typename TYPE>
struct erase_reference<const TYPE &&>
{
   using NON_REFERENCE_TYPE = const TYPE;
};

template<typename TYPE>
using non_reference = typename erase_reference<TYPE>::NON_REFERENCE_TYPE;






template<typename TYPE>
struct insert_const
{

   // erase top-level const qualifier
   using CONST_TYPE = const TYPE;


};

template<typename TYPE>
struct insert_const<TYPE &>
{
   using CONST_TYPE = const TYPE &;
};


template<typename TYPE>
struct insert_const<TYPE *>
{
   using CONST_TYPE = const TYPE *;
};

template<typename TYPE>
struct insert_const<const TYPE>
{
   using CONST_TYPE = const TYPE;
};

template<typename TYPE>
struct insert_const<const TYPE &>
{
   using CONST_TYPE = const TYPE &;
};

template<typename TYPE>
struct insert_const<const TYPE *>
{
   using CONST_TYPE = const TYPE *;
};


template<class TYPE>
using add_const = typename insert_const<TYPE>::CONST_TYPE;


//constexpr ::u64 operator "" _uintmax(unsigned long long int u) { return u << 32LL; }

template < typename DERIVED, typename BASE >
concept is_derived_from =
::std::is_base_of < BASE, DERIVED >::value;


template < typename FILE >
class binary_stream;

template < typename FILE >
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








template < typename POINT >
concept primitive_XY = requires(POINT point)
{
   point.X;
   point.Y;
};


template < typename SIZE >
concept primitive_size = requires(SIZE size)
{
   size.cx;
   size.cy;
};


template < typename SIZE >
concept primitive_Dim = requires(SIZE size)
{
   size.Width;
   size.Height;
};

template < typename SIZE >
concept primitive_dim = requires(SIZE size)
{
   size.width;
   size.height;
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
   rectangle.x();
   rectangle.y();
   rectangle.width;
   rectangle.height;
};




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


template < bool B, class TRUE_TYPE = void, class ELSE_TYPE = void >
struct if_else_base {};

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else_base < true, TRUE_TYPE, ELSE_TYPE > { using type = TRUE_TYPE; };

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else_base < false, TRUE_TYPE, ELSE_TYPE > { using type = ELSE_TYPE; };

template < bool B, class TRUE_TYPE = void, class ELSE_TYPE = void >
using if_else = typename if_else_base < B, TRUE_TYPE, ELSE_TYPE >::type;


template <class TYPE, TYPE t>
struct integral_constant
{

   static constinit TYPE value = t;

};


template < bool b >
using bool_constant = integral_constant < bool, b >;


using true_type = bool_constant < true >;

using false_type = bool_constant < false >;


template < typename >
constexpr bool is_const = false; // determine whether type argument is const qualified


template < typename TYPE >
constexpr bool is_const < const TYPE > = true;



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
   using type = if_else< (sizeof(T1) >= sizeof(T2)), T1, T2>;
};


template < typename T1, typename T2 >
using largest_type = typename largest_type_struct<T1, T2>::type;


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


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE  >, ::enum_type m_etypeContainer = e_type_element >
class array;

template < typename FUNCTION >
class function;

template < class TYPE, class ARG_TYPE = const TYPE & >
class list;


template < typename ARGUMENT >
struct argument_of_struct
{

   using type = const ARGUMENT &;

};


template < typename TYPE >
struct argument_of_struct < TYPE * >
{

   using type = TYPE *;

};




//template < primitive_function FUNCTION >
//struct argument_of_struct < FUNCTION >
//{
//
//   using type = FUNCTION;
//
//};


template < typename ARGUMENT >
using argument_of = typename argument_of_struct < ARGUMENT >::type;


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


using int_array = i32_array;


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

using float_array = numeric_array < float  >;
using double_array = numeric_array < double  >;

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
inline byte byte_clip(const T & t) { return ((byte)(((t) < (byte)0) ? (byte)0 : (((t) > (byte)255) ? (byte)255 : (byte)t))); }


template < typename A, typename B >
void __swap(A & a, B & b)
{

   A aCopy = a;

   a = b;

   b = aCopy;

}



typedef pointer_array < ::particle > particle_array;


template < primitive_XYDim XYDim, typename X, typename Y, typename W, typename H >
inline XYDim & set_dim(XYDim & rectTarget, X x, Y y, W w, H h)
{

   rectTarget.X = (decltype(rectTarget.X))x;
   rectTarget.Y = (decltype(rectTarget.Y))y;
   rectTarget.Width = (decltype(rectTarget.Width))w;
   rectTarget.Height = (decltype(rectTarget.Height))h;

   return rectTarget;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
void copy(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rect1.left = (decltype(RECT_TYPE1::left))rect2.left;
   rect1.top = (decltype(RECT_TYPE1::top))rect2.top;
   rect1.right = (decltype(RECT_TYPE1::right))rect2.right;
   rect1.bottom = (decltype(RECT_TYPE1::bottom))rect2.bottom;

}


template < primitive_rectangle RECTANGLE, primitive_XYDim XYDim >
void copy(RECTANGLE & rectangle, const XYDim & xydim)
{

   rectangle.left = (decltype(RECTANGLE::left))xydim.X;
   rectangle.top = (decltype(RECTANGLE::top))xydim.Y;
   rectangle.right = (decltype(RECTANGLE::right))(xydim.X + xydim.Width);
   rectangle.bottom = (decltype(RECTANGLE::bottom))(xydim.Y + xydim.Height);

}


template < primitive_rectangle RECTANGLE, primitive_xydim XYDIM >
void copy(RECTANGLE & rect1, const XYDIM  & xydim)
{

   rect1.left = (decltype(RECTANGLE::left))xydim.x();
   rect1.top = (decltype(RECTANGLE::top))xydim.y();
   rect1.right = (decltype(RECTANGLE::right))(xydim.x() + xydim.width);
   rect1.bottom = (decltype(RECTANGLE::bottom))(xydim.y() + xydim.height);

}



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



