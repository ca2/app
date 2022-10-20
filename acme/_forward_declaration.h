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


#include "acme/constant/_constant.h"
#include "acme/primitive/primitive/estatus.h"


constexpr ::u64 operator "" _uintmax(unsigned long long int u) { return u << 32LL; }



namespace acme { class system; }
namespace acme { class application; }
namespace apex { class application; }
class thread;
class property_object;
class task;
class task_pool;
class action_context;
class object;
class dump_context;
class synchronization_object;
class __id;
class string_exchange;
namespace message { class message; }
class payload;
template < typename FILE >
class binary_stream;
class text_stream;
struct block;
class property_set;
class particle;

//namespace topic
//{

   class topic;
   class context;

//} // namespace topic



template<class T>
class pointer;


template<class T>
class pointer_array;


//#define ::pointer<TYPE>::reference < TYPE >


//#define ::pointer<TYPE>::pointer<TYPE>
//#define pointer_array < TYPE > ::pointer_array < TYPE >

//
//template < typename TYPE >
//class ___address
//{
//public:
//
//
//   TYPE* m_p;
//
//   ___address() : m_p(nullptr) {}
//   ~___address() { if (::is_set(m_p)) throw error_wrong_state; }
//
//   TYPE* get() { return m_p; }
//   TYPE* get() const { return m_p; }
//
//   operator TYPE* () const { return m_p; }
//   operator TYPE* () { return m_p; }
//
//   TYPE* operator ->() const { return m_p; }
//   TYPE* operator ->() { return m_p; }
//
//   bool is_null() const { return ::is_null(m_p); }
//   bool is_set() const { return ::is_set(m_p); }
//   bool operator !() const { return is_null(); }
//
//   template < typename OBJECT >
//   ::pointer<OBJECT>cast() const;
//
//
//   template < typename INTERMEDIATE >
//   void release(INTERMEDIATE* p) { ::release(p, m_p); }
//
//
//   template < typename ADDRESS >
//   ___address & operator = (ADDRESS & p) { p->increment_reference_count(); release(p); m_p = p; return *this; }
//
//};


//#define throw ::exception(...) throw_exception(__VA_ARGS__)


CLASS_DECL_ACME void output_error_message(const ansichar * pszMessage, const ansichar * pszTitle = nullptr, int iMessageBox = 0);
CLASS_DECL_ACME void output_debug_string(const ansichar * psz);
CLASS_DECL_ACME void output_debug_string(const wd16char * psz);
CLASS_DECL_ACME void output_debug_string(const wd32char * psz);



inline bool is_set_ptr(const void * p) { return (uptr)p > 65536; }



class error_code;


namespace user
{


   class tool_item;
   class mouse;
   class drag;
   class drag_client;


} // namespace user


class image;
class e_check;
class tristate;




template<class T>
class pointer;


template<class T>
class pointer_array;


using image_pointer = ::pointer<::image>;


namespace write_text
{


   class font;
   
   using font_pointer = ::pointer<font>;


} // namespace write_text


namespace interprocess
{

   
   class target;


} // namespace interprocess



template<typename Type, typename RawType = Type, enum_type t_etypePayload = e_type_element >
class string_array_base;


template<typename CHAR_TYPE>
class string_base;


struct pixmap;


#define CONSIDER_AS(as, use) using use = as


using ansistring = string_base<ansichar>;
using wd16string = string_base<wd16char>;
using wd32string = string_base<wd32char>;
using widestring = string_base<widechar>;


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

class property;
class payload;
class atom;







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




template < typename DERIVED, typename BASE >
concept is_derived_from =
::std::is_base_of < BASE, DERIVED >::value;




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


} // namespace allocator

template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE >, enum_type t_etypePayload = e_type_element >
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


class item;

using item_pointer = ::pointer < ::item >;

