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


namespace write_text
{


   using font_pointer = ::pointer<font>;


} // namespace write_text





template < typename POINT >
concept primitive_point = requires(POINT point)
{
   point.x;
   point.y;
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
   size.cx;
   size.cy;
};


template < typename SIZE >
concept primitive_Dim = requires(SIZE size)
{
   size.Width;
   size.Height;
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



template < typename TYPE_CHAR >
class simple_string_base;


using simple_ansistring = simple_string_base < ansichar >;
using simple_wd16string = simple_string_base < wd16char >;
using simple_wd32string = simple_string_base < wd32char >;
using simple_widestring = simple_string_base < widechar >;


typedef simple_ansistring simple_string;
typedef simple_widestring simple_wstring;





template < bool B, class TRUE_TYPE = void, class ELSE_TYPE = void >
struct if_else {};

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else < true, TRUE_TYPE, ELSE_TYPE > { using type = TRUE_TYPE; };

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else < false, TRUE_TYPE, ELSE_TYPE > { using type = ELSE_TYPE; };










template < typename FROM, typename TO_POINTER >
concept raw_pointer_castable =
::std::is_convertible < FROM, TO_POINTER * >::value ||
::std::is_convertible < FROM, const TO_POINTER * >::value;


template < typename T >
concept primitive_character =
std::is_same < T, char >::value ||
std::is_same < T, wchar_t >::value ||
std::is_same < T, ::ansichar >::value ||
std::is_same < T, ::wd16char >::value ||
std::is_same < T, ::wd32char >::value;


template < typename T >
concept const_c_string =
std::is_convertible < T, const ::ansichar * >::value ||
std::is_convertible < T, const ::wd16char * >::value ||
std::is_convertible < T, const ::wd32char * >::value;


template < typename T >
concept non_const_c_string =
std::is_convertible < T, ::ansichar * >::value ||
std::is_convertible < T, ::wd16char * >::value ||
std::is_convertible < T, ::wd32char * >::value;

template < typename T >
concept c_string =
const_c_string < T > ||
non_const_c_string < T >;

template < typename T >
struct base_const_c_string
{

   using type =
      typename if_else <
      std::is_convertible < T, const ansichar * >::value,
      const ansichar *,
      typename if_else <
      std::is_convertible < T, const wd16char * >::value,
      const wd16char *,
      typename if_else <
      std::is_convertible < T, const wd32char * >::value,
      const wd32char *,
      void *
      >::type
      >::type
      >::type;

};


template < primitive_character CHARACTER >
class string_base;


using ansistring = string_base<ansichar>;
using wd16string = string_base<wd16char>;
using wd32string = string_base<wd32char>;
using widestring = string_base<widechar>;
using string = string_base < ansichar >;
using wstring = string_base < widechar >;




template<typename Type, typename RawType = Type, ::enum_type m_etypeContainer = e_type_element >
class string_array_base;





class e_status;


template <template <class...> class Template, class... Args>
void derived_from_specialization_impl(const Template<Args...>&);

template <class T, template <class...> class Template>
concept derived_from_specialization_of = requires(const T & t) {
   derived_from_specialization_impl<Template>(t);
};

template <class... Types> struct inherits : Types... {};

template < typename T >
concept a_enum = std::is_enum < T >::value;

template < typename T >
concept primitive_integral = 
   std::is_integral_v < T > || 
   std::is_enum < T >::value ||
   std::is_same < T, ::e_status >::value;


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




template < bool, typename T1, typename T2 >
struct boolean_type_selection { using type = T1; };

template < typename T1, typename T2 >
struct boolean_type_selection<false, T1, T2> { using type = T2; };


template < typename T1, typename T2 >
struct largest_type {
   using type = typename ::boolean_type_selection< (sizeof(T1) > sizeof(T2)), T1, T2>::type;
};


template < typename T1, typename T2 >
struct smaller_type {
   using type = typename ::boolean_type_selection< (sizeof(T1) < sizeof(T2)), T1, T2>::type;
};


template < typename T1, typename T2, typename T3 >
struct largest_type_of_3 {
   using largest_type_of_1_and_2 = typename largest_type < T1, T2 >::type;
   using type = typename ::boolean_type_selection < (sizeof(largest_type_of_1_and_2) > sizeof(T3)), largest_type_of_1_and_2, T3>::type;
};


template < typename TYPE, std::size_t SIZE >
using array_reference = TYPE(&)[SIZE];

namespace allocator
{


   template < typename TYPE >
   class def;

   template < typename TYPE >
   class nodef;

} // namespace allocator


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type m_etypeContainer = e_type_element >
class array_base;


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE >, ::enum_type m_etypeContainer = e_type_element >
class array;

template < typename FUNCTION >
class function;

template < class TYPE, class ARG_TYPE = const TYPE & >
class list;

template < typename ARGUMENT >
class argument_of
{
public:

   using type = const ARGUMENT &;

};


template < primitive_number NUMBER >
class argument_of < NUMBER >
{
public:

   using type = NUMBER;

};



template < typename T, typename ARG_T = typename argument_of < T >::type >
class single;



template < class KEY, class ARG_KEY = typename argument_of < KEY >::type, class PAYLOAD = single < KEY, ARG_KEY > >
class set;


template < typename T1, typename T2, typename ARG_T1 = typename argument_of < T1 >::type, typename ARG_T2 = typename argument_of < T2 >::type >
class pair;


template < class KEY, class VALUE, class ARG_KEY = typename argument_of < KEY >::type, class ARG_VALUE = typename argument_of < VALUE >::type, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE > >
class map;


template<class ENUM>
class flags;


template<class EENUM, EENUM edefault = (EENUM)0>
class base_enum;


template < typename BLOCK >
concept primitive_block = requires(BLOCK block)
{

   block.get_data();
   block.get_size();

};


template < typename CONTAINER >
concept primitive_container = ::std::is_same < typename CONTAINER::PRIMITIVE_CONTAINER_TAG, PRIMITIVE_CONTAINER_TAG_TYPE >::value;

template < typename PAYLOAD >
concept primitive_payload = ::std::is_same < typename PAYLOAD::PRIMITIVE_PAYLOAD_TAG, PRIMITIVE_PAYLOAD_TAG_TYPE >::value;

template < typename ATOM >
concept primitive_atom = ::std::is_same < typename ATOM::PRIMITIVE_ATOM_TAG, PRIMITIVE_ATOM_TAG_TYPE >::value;

template < typename STRING >
concept primitive_string = ::std::is_same < typename STRING::PRIMITIVE_STRING_TAG, PRIMITIVE_STRING_TAG_TYPE >::value;

using item_pointer = ::pointer < ::item >;

using memory_pointer = ::pointer < ::memory >;

template < typename TYPE, typename ARG_TYPE = typename argument_of < TYPE >::type, typename PAIR = pair < ::atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE > >
using atom_map = ::map < atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE, PAIR >;



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
inline ::pointer < T > move_transfer(T * p);


#define __new(...) ::move_transfer( memory_new __VA_ARGS__ )


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

using dword_array = u32_array;
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

//using strsize_ptr_array = ptr_array < strsize *  >;


using byte_array = u8_array;

using task_pointer = ::pointer < task >;


//#include "acme/primitive/primitive/_u32hash.h"


CLASS_DECL_ACME task_pointer fork(::particle * pparticle, const ::procedure & procedure);


namespace draw2d
{


   using graphics_pointer = ::pointer<graphics>;


} // namespace draw2d



template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline void copy(NUMBER1& number1, const NUMBER2& number2)
{

    number1 = (NUMBER1)number2;

}




template < typename CHAR_STRING >
inline bool is_string_empty(CHAR_STRING p) { return ::is_null(p) || *p == '\0'; }

inline bool is_empty(const ansichar * p) { return is_string_empty(p); }
inline bool is_empty(const wd16char * p) { return is_string_empty(p); }
inline bool is_empty(const wd32char * p) { return is_string_empty(p); }


inline bool has_char(const ansichar * p) { return !is_empty(p); }
inline bool has_char(const wd16char * p) { return !is_empty(p); }
inline bool has_char(const wd32char * p) { return !is_empty(p); }



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

   rect1.left = (decltype(RECTANGLE::left))xydim.x;
   rect1.top = (decltype(RECTANGLE::top))xydim.y;
   rect1.right = (decltype(RECTANGLE::right))(xydim.x + xydim.width);
   rect1.bottom = (decltype(RECTANGLE::bottom))(xydim.y + xydim.height);

}


template < primitive_XY POINT1, primitive_point POINT2 >
void copy(POINT1 point1, const POINT2 & point2)
{

   point1.X = (decltype(POINT1::X))point2.x;
   point1.Y = (decltype(POINT1::Y))point2.y;

}


template < primitive_point POINT1, primitive_XY POINT2 >
void copy(POINT1 & point1, const POINT2 & point2)
{

   point1.x = (decltype(POINT1::x))point2.X;
   point1.y = (decltype(POINT1::y))point2.Y;

}


template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
void copy(XYDim & xydim, const RECTANGLE & rectangle)
{

   xydim.X = (decltype(XYDim::X))rectangle.left;
   xydim.Y = (decltype(XYDim::Y))rectangle.top;
   xydim.Width = (decltype(XYDim::Width))(rectangle.right - rectangle.left);
   xydim.Height = (decltype(XYDim::Height))(rectangle.bottom - rectangle.top);

}


template < primitive_xydim XYDIM, primitive_rectangle RECTANGLE >
void copy(XYDIM & xydim, const RECTANGLE & rectangle)
{

   xydim.x = (decltype(XYDIM::X))rectangle.left;
   xydim.y = (decltype(XYDIM::Y))rectangle.top;
   xydim.width = (decltype(XYDIM::Width))(rectangle.right - rectangle.left);
   xydim.height = (decltype(XYDIM::Height))(rectangle.bottom - rectangle.top);

}


template < primitive_XYDim XYDim1, primitive_XYDim XYDim2 >
void copy(XYDim1 & xydim1, const XYDim2 & xydim2)
{

   xydim1.X = (decltype(XYDim1::X))xydim2.X;
   xydim1.Y = (decltype(XYDim1::Y))xydim2.Y;
   xydim1.Width = (decltype(XYDim1::Width))xydim2.Width;
   xydim1.Height = (decltype(XYDim1::Height))xydim2.Height;

}


template < primitive_point POINT1, primitive_point POINT2 >
void copy(POINT1 & point1, const POINT2 & point2)
{

   point1.x = (decltype(POINT1::x))point2.x;
   point1.y = (decltype(POINT1::y))point2.y;

}


template < primitive_point POINT, primitive_size SIZE >
void copy(POINT & point, const SIZE & size)
{

   point.x = (decltype(POINT::x))size.cx;
   point.y = (decltype(POINT::y))size.cy;

}


template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
void copy(SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2)
{

   size1.cx = (decltype(SIZE_TYPE1::cx))size2.cx;
   size1.cy = (decltype(SIZE_TYPE1::cy))size2.cy;

}





template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB,
   class ARRAYA = array < TYPEA, ARG_TYPEA >, class ARRAYB = array < TYPEB, ARG_TYPEB > >
class spreadset;


using i32_spreadset = spreadset < i32, i32, i32, i32, unique_i32_sort_array, unique_i32_sort_array >;

using i64_spreadset = spreadset < i64, i64, i64, i64, unique_i64_sort_array, unique_i64_sort_array >;





template < typename TYPE, std::size_t SIZE >
inline array_reference < TYPE, SIZE >& zero(TYPE(&)[SIZE]);


template < typename TYPE >
inline TYPE& zero(TYPE & type);


template < typename TYPE, std::size_t Size >
inline bool __is_zero(TYPE(&array)[Size]);



#include "acme/primitive/duration/__string.h"



// erase_const
// erase_const
// erase_const


template<typename TYPE>
struct erase_const_struct
{

   // erase top-level const qualifier
   using NON_CONST_TYPE = TYPE;


};

template<typename TYPE>
struct erase_const_struct<TYPE&>
{
   using NON_CONST_TYPE = TYPE&;
};


template<typename TYPE>
struct erase_const_struct<const TYPE>
{
   using NON_CONST_TYPE = TYPE;
};

template<typename TYPE>
struct erase_const_struct<const TYPE&>
{
   using NON_CONST_TYPE = TYPE&;
};

template<class TYPE>
using non_const = typename erase_const_struct<TYPE>::NON_CONST_TYPE;

struct true_type
{
};
struct false_type
{
};






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







