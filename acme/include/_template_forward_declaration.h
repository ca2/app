//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 22:30
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once
// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once




//constexpr ::u64 operator "" _uintmax(unsigned long long int u) { return u << 32LL; }

template < typename DERIVED, typename BASE >
concept is_derived_from =
::std::is_base_of < BASE, DERIVED >::value;


template < typename FILE >
class binary_stream;
template < typename RESULT >
class process;


template<class T>
class pointer;


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




template<typename Type, typename RawType = Type, ::enum_type m_etypeContainer = e_type_element >
class string_array_base;


template<typename CHAR_TYPE>
class string_base;



#define CONSIDER_AS(as, use) using use = as


using ansistring = string_base<ansichar>;
using wd16string = string_base<wd16char>;
using wd32string = string_base<wd32char>;
using widestring = string_base<widechar>;


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


using string = string_base < ansichar >;
using wstring = string_base < widechar >;


typedef string_array_base < string, string, e_type_string_array > string_array;

template < typename TYPE_CHAR >
class string_natural_pointer;

using natural_ansistring = string_natural_pointer < ansichar >;
using natural_wd16string = string_natural_pointer < wd16char >;
using natural_wd32string = string_natural_pointer < wd32char >;
using natural_widestring = string_natural_pointer < widechar >;

typedef natural_ansistring natural_string;
typedef natural_widestring natural_wstring;





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






class e_status;


template < typename T >
concept a_pointer = std::is_pointer < T >::value;

template < typename T >
concept non_pointer = !std::is_pointer < T >::value;

template < typename T >
concept a_enum = std::is_enum < T >::value;

template < typename T >
concept primitive_integral = std::is_integral < T >::value || std::is_enum < T >::value || std::is_same < T, ::e_status >::value;

template < typename T >
concept primitive_integer = std::is_integral < T >::value;

template < typename T >
concept primitive_natural = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept primitive_signed = (std::is_integral < T >::value || std::is_enum < T >::value) && std::is_signed < T >::value;

template < typename T >
concept primitive_unsigned = (std::is_integral < T >::value || std::is_enum < T >::value) && !std::is_signed < T >::value;


template < typename T >
concept primitive_floating = std::is_floating_point < T >::value;

template < typename T >
concept primitive_number = std::is_integral < T >::value || std::is_enum < T >::value || std::is_floating_point < T >::value;







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

   using type = typename smaller_type < ARGUMENT, const ARGUMENT & >::type;

};


template < >
class argument_of < ::string >
{
public:

   using type = ::block;

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


template < typename PAYLOAD >
concept primitive_payload = ::std::is_base_of < ::PAYLOAD_TAG, PAYLOAD >::value;

//template < typename PROPERTY >
//concept primitive_property = is_derived_from < PROPERTY, ::PROPERTY_TAG >;

template < typename ATOM >
concept primitive_atom = ::std::is_base_of < ::ATOM_TAG, ATOM >::value;


using item_pointer = ::pointer < ::item >;

using memory_pointer = ::pointer < ::memory >;



template < typename CONTAINER >
concept container_type = requires(CONTAINER container)
{

   {container.this_is_a_container()} -> std::same_as<void>;

};


template < container_type CONTAINERX, container_type CONTAINERY >
inline CONTAINERX operator +(CONTAINERX x, const CONTAINERY & y)
{

   x += y;

   return x;

}


template < typename ARRAY >
concept primitive_array = requires(ARRAY array, ::index i)
{
   array.get_count();
   array.element_at(i);
};

template<primitive_array ARRAY1, primitive_array ARRAY2>
bool operator==(const ARRAY1 &array1, const ARRAY2 &array2)
{

   if (array1.get_size() != array2.get_size())
   {

      return false;

   }

   for (::index i = 0; i < array1.get_size(); i++)
   {

      if (array1.element_at(i) != array2.element_at(i))
      {

         return false;

      }

   }

   return true;

}


template<primitive_array ARRAY1, primitive_array ARRAY2>
bool operator!=(const ARRAY1 &array1, const ARRAY2 &array2)
{

   return !operator==(array1, array2);

}


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

using element_array = pointer_array < element >;



//#include "acme/primitive/collection/string_map.h"


using regular_expression_pointer = ::pointer<::regular_expression::regular_expression>;


template < class T, typename C >
void std_string_assign(T & t, const C * psz);


template < class T >
void std_string_bassign(T & t, const u8 * psz, strsize nsize);





typedef address_array < const char * > const_char_ptra;

typedef address_array < void * > void_ptra;

//typedef address_array < matter * > simple_object_ptra;


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


using handler_pointer = ::pointer<handler>;
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

CLASS_DECL_ACME task_pointer fork(::particle * pparticle, const ::procedure & procedure);



namespace draw2d
{


   using graphics_pointer = ::pointer<graphics>;


} // namespace draw2d



template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline void copy(NUMBER1 * pnumber1, const NUMBER2 * pnumber2)
{

   *pnumber1 = (NUMBER1) *pnumber2;

}


template < primitive_number NUMBER >
inline void copy(string * pstring, const NUMBER * pnumber)
{

   *pstring = __string(*pnumber);

}


template < primitive_payload PAYLOAD >
CLASS_DECL_ACME void copy(string * pstring, const PAYLOAD * ppayload)
{

   *pstring = ppayload->string();

}


template < primitive_payload PAYLOAD, primitive_number NUMBER >
inline void copy(const PAYLOAD * ppayload, const NUMBER* pnumber)
{

   *ppayload = *pnumber;

}


template < primitive_payload PAYLOAD >
CLASS_DECL_ACME void copy(::payload * ppayload, const string * pstring)
{

   *ppayload = *pstring;

}


template < primitive_payload PAYLOAD1, primitive_payload PAYLOAD2 >
CLASS_DECL_ACME void copy(PAYLOAD1 * ppayload1, const PAYLOAD2 * ppayload2)
{

   *ppayload1 = *ppayload2;

}








template < a_pointer POINTER >
inline bool is_null(POINTER p)
{

   return ((size_t)p <= 65536);

}


template < typename CHAR_STRING >
inline bool is_string_empty(CHAR_STRING p) { return ::is_null(p) || *p == '\0'; }

inline bool is_empty(const ansichar * p) { return is_string_empty(p); }
inline bool is_empty(const wd16char * p) { return is_string_empty(p); }
inline bool is_empty(const wd32char * p) { return is_string_empty(p); }


inline bool has_char(const ansichar * p) { return !is_empty(p); }
inline bool has_char(const wd16char * p) { return !is_empty(p); }
inline bool has_char(const wd32char * p) { return !is_empty(p); }


template < a_pointer POINTER >
inline bool is_set(POINTER p)
{

   return !is_null(p);

}


template<typename TYPE>
inline bool is_ref_set(const TYPE & t)
{

   return is_set(&t);

}


template<typename TYPE>
inline bool is_ok(const TYPE * p)
{

   return ::is_set(p) && p->is_ok();

}


template<typename TYPE>
inline bool is_ok(const ::pointer<TYPE> & p)
{

   return ::is_ok(p.m_p);

}


template<typename TYPE>
inline bool nok(TYPE & t)
{

   return !::is_ok(t);

}






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



