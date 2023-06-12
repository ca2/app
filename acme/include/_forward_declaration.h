//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/09/22 22:30
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once



template <class TYPE, TYPE t >
struct integral_constant
{

   inline static constexpr TYPE payload = t;

};


template < bool b >
using bool_constant = integral_constant < bool, b >;


using true_type = bool_constant < true >;

using false_type = bool_constant < false >;

template<class T> struct is_const_struct : false_type {};
template<class T> struct is_const_struct<const T> : true_type {};

template < class T >
inline constexpr bool is_const = is_const_struct < T >::payload;


template<class T> struct is_reference_struct : false_type {};
template<class T> struct is_reference_struct<T &> : true_type {};
template<class T> struct is_reference_struct<T &&> : true_type {};

template < class T >
inline constexpr bool is_reference = is_reference_struct < T >::payload;


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
//struct all_s<size_t> :true_type {};
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
//struct fun_all_s<C, R, R(C &, Args...)> :true_type {};
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



template < bool B, class TRUE_TYPE = void, class ELSE_TYPE = void >
struct if_else_base {};

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else_base < true, TRUE_TYPE, ELSE_TYPE > { using type = TRUE_TYPE; };

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else_base < false, TRUE_TYPE, ELSE_TYPE > { using type = ELSE_TYPE; };

template < bool B, class TRUE_TYPE = void, class ELSE_TYPE = void >
using if_else = typename if_else_base < B, TRUE_TYPE, ELSE_TYPE >::type;

template<class T>
struct is_array_struct : false_type {};

template<class T>
struct is_array_struct<T[]> : true_type {};

template<class T, std::size_t N>
struct is_array_struct<T[N]> : true_type {};

template<class T>
inline constexpr bool is_array = is_array_struct < T >::payload;


namespace detail
{
   template<class T>
   struct type_identity { using type = T; }; // or use std::type_identity (since C++20)

   template<class T>
   auto try_add_pointer(int) -> type_identity< non_reference<T> *>;
   template<class T>
   auto try_add_pointer(...) -> type_identity<T>;
} // namespace detail

template<class T>
struct add_pointer_struct : decltype(detail::try_add_pointer<T>(0)) {};

template < typename T >
using add_pointer = typename add_pointer_struct < T >::type;


template<class T> struct erase_pointer_struct { typedef T type; };
template<class T> struct erase_pointer_struct<T *> { typedef T type; };
template<class T> struct erase_pointer_struct<T * const> { typedef T type; };
template<class T> struct erase_pointer_struct<T * volatile> { typedef T type; };
template<class T> struct erase_pointer_struct<T * const volatile> { typedef T type; };


template < typename T >
using erase_pointer = typename erase_pointer_struct < T >::type;

template<class T>
struct erase_extent_struct { using type = T; };

template<class T>
struct erase_extent_struct<T[]> { using type = T; };

template<class T, std::size_t N>
struct erase_extent_struct<T[N]> { using type = T; };


template < typename T >
using non_extent = typename erase_pointer_struct < T >::type;
























template<typename T>
struct is_function_struct : ::integral_constant<
   bool,
   !is_const< const T > && !is_reference< T >
> {};

template<typename T>
inline constexpr bool is_function = is_function_struct < T >::payload;


//// primary template
//template<class>
//struct is_function_struct : false_type {};
//
//// specialization for regular functions
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...)> : true_type {};
//
//// specialization for variadic functions such as std::printf
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......)>  : true_type {};
//
//// specialization for function types that have cv-qualifiers
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) volatile>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const volatile>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) volatile>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const volatile>  : true_type {};
//
//// specialization for function types that have ref-qualifiers
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) volatile &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const volatile &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) volatile &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const volatile &>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) &&>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const &&>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) volatile &&>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const volatile &&>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) &&>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const &&>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) volatile &&>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const volatile &&>  : true_type {};
//
//// specializations for noexcept versions of all the above (C++17 and later)
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) volatile noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const volatile noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) volatile noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const volatile noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) volatile & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const volatile & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) volatile & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const volatile & noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) && noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const && noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) volatile && noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args...) const volatile && noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) && noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const && noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) volatile && noexcept>  : true_type {};
//template<class Ret, class... Args>
//struct is_function_struct<Ret(Args......) const volatile && noexcept>  : true_type {};



//// primary template
//template<typename T>
//using is_function = typename is_function_struct<T > :: type;

// specialization for regular functions
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...)> :: type;

//// specialization for variadic functions such as std::printf
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......)> :: type;
//
//// specialization for function types that have cv-qualifiers
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) volatile> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const volatile> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) volatile> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const volatile> :: type;
//
//// specialization for function types that have ref-qualifiers
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) volatile &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const volatile &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) volatile &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const volatile &> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) &&> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const &&> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) volatile &&> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const volatile &&> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) &&> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const &&> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) volatile &&> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const volatile &&> :: type;
//
//// specializations for noexcept versions of all the above (C++17 and later)
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) volatile noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const volatile noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) volatile noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const volatile noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) volatile & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const volatile & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) volatile & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const volatile & noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) && noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const && noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) volatile && noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args...) const volatile && noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) && noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const && noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) volatile && noexcept> :: type;
//template<class Ret, class... Args>
//using is_function = typename is_function_struct<Ret(Args......) const volatile && noexcept> :: type;



template<class T>
struct decay_struct
{
private:
   using U = ::non_reference<T>;
public:
   using type = 
   if_else <
      is_array < U >,
      add_pointer < non_extent < U > >,
      if_else <
      is_function < U >, add_pointer < U >, non_const < U > >
   >;
};


template <typename T>
using decay = typename decay_struct<T>::type;




namespace opengl
{


   class opengl;


} // namespace opengl


namespace operating_system
{


   class summary;


} // namespace operating_system


namespace message
{


   class command;


} // namespace message
class matter;


namespace acme
{


   class system; // acme - cam


   class application; // apex(::apex::application) - tbs offloading his deep stack in ::acme::application(::acme):cstbs

   class session;


   class application_container;



   class node;
   class library;


} // namespace acme


class memory_counter;



namespace acme_posix
{


   class node;


} // namespace acme_posix



namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)
{


   class node;
   class buffer;


} // namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)


namespace acme_posix { class node; }
namespace apex_posix { class node; }
namespace aura_posix { class node; }


namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_) { class node; }
namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(apex_) { class node; }
namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_) { class node; }



namespace acme
{


   class system;


   class node;


} // namespace acme


namespace apex
{


   class system;


   class node;


} // namespace apex


namespace aura
{


   class system;


   class node;


} // namespace aura



class object;
class thread;


class os_context;


namespace node_gtk
{


   class node;


} // namespace node_gtk


namespace node_gnome
{


   class node;


} // namespace node_gnome


namespace node_kde
{


   class node;


} // namespace node_kde


namespace node_xfce
{


   class node;


} // namespace node_xfce


namespace desktop_environment_gnome
{


   class node;


} // namespace desktop_environment_gnome


namespace windowing
{

   class window;

} // namespace windowing


namespace windows
{

   
   class generic_handle;


} // namespace windows


using hinstance = void*;
#ifdef UNICODE
using tchar = wchar_t;
#else
using tchar = char;
#endif


namespace desktop_environment_kde
{


   class node;


} // namespace desktop_environment_kde


namespace desktop_environment_xfce
{


   class node;


} // namespace desktop_environment_xfce


namespace acme
{

   class system;
   class context;
   class library;
   class node;
   class application;
   class exclusive;

} // namespace acme


namespace apex { class application; }
class thread;
class task;
class property_object;
class task;
class task_pool;
class action_context;
class object;
//class dump_context;
class __id;
class string_exchange;
class lparam;
class time;
class timer_callback;
namespace message { class message; }
class payload;
struct block;
class property_set;
class particle;
//class element;
class matter;
class exception_translator;
class counter;
class type;

class acme_file;
class acme_path;
class acme_directory;


class sub_system;


class dir_context;
class dir_system;
class file_context;
class file_system;


enum enum_zero_init
{

   e_zero_init

};


namespace networking
{


   class application;


} // namespace networking


namespace operating_system
{

   class department;

   class process;

   struct exit_status;

} // namespace operating_system


namespace regular_expression
{

   class context;
   class regular_expression;

} // namespace regular_expression


namespace file
{


   class path;
   class path_object;
   struct file_status;


} // namespace file


namespace factory
{


   class factory;

   //CLASS_DECL_ACME ::factory::factory * get_factory();


} // namespace factory


namespace crypto
{


   class crypto;


} // namespace crypto


namespace data
{


   class node;
   class item;


} // namespace data


class memory_base;

struct HAS_STRING_LABEL_TAG { };
struct PRIMITIVE_BLOCK_TAG_TYPE { };
struct PRIMITIVE_CONTAINER_TAG_TYPE { };
struct PRIMITIVE_PAYLOAD_TAG_TYPE { };
struct PRIMITIVE_ATOM_TAG_TYPE { };
struct PRIMITIVE_STRING_TAG_TYPE { };
struct PRIMITIVE_SCOPED_STRING_TAG_TYPE { };

//class handler;
class manager;
class context;
class topic;
class extended_topic;


namespace file
{

   class file;
   class item;
   class item_array;


} // namespace file


namespace apex
{


   class savings;


} // namespace apex

class stdio_file;
class string_stream;
class string_buffer;


namespace http
{

   class cookie;
   class cookies;


} // namespace http








class error_code;


namespace user
{


   class tool_item;
   class mouse;
   class drag;
   class drag_client;

   class primitive;
   class element;
   class primitive_impl;

   //class object;


} // namespace user


class conversation;


class image;
//class e_check;
class tristate;




namespace write_text
{


   class font;


} // namespace write_text


namespace interprocess
{


   class target;


} // namespace interprocess




struct pixmap;


#define CONSIDER_AS(as, use) using use = as



//typedef natural_ansistring natural_string;
//typedef natural_widestring natural_wstring;

class property;
class payload;
class atom;


struct MESSAGE;

class item;


class memory;



class istring;


class property_set;


class payload_array;


class property;


class timer_future;


namespace acme
{

   class Timer;

};


class timer;
class timer_task;

namespace message
{


   class mouse;


} // namespace message


class form_property_set;


namespace acme
{


   //class application;
   //class system;
   //class application_message;

   class command;


} // namespace acme


namespace gpu
{

   class approach;

} // namespace gpu


namespace data
{


   class listener;


   class data;


   class simple_data;


   class data_container_base;


} // namespace data

namespace sockets // only usable from base.dll and dependants
{

   class sockets; // only usable from base.dll and dependants


} // namespace sockets // only usable from base.dll and dependants


namespace url
{

   class url; // only usable from base.dll and dependants


} // namespace url


class compress_department; // only usable from axis.dll and dependants


class channel;


//class dump_context;


//class atom_space;


class ptra;


class factory_item_base;


class fixed_alloc_no_sync;


class critical_section;


class channel;


class critical_section;


class mutex;


class atom;

namespace colorertake5
{

   class ParserFactory;


} // namespace colorertake5


//class pixmap;


class memory;


namespace datetime
{


   class datetime;


   class time;


   class time_span;


} // namespace datetime




namespace file
{

   class listing;


   class path;


   class file;


   enum enum_type
   {

      e_type_unknown = 0,
      e_type_exists = 1 << 0,
      e_type_folder = e_type_exists | (1 << 1),
      e_type_file = e_type_exists | (1 << 2),
      e_type_file_or_folder = e_type_folder | e_type_file,
      e_type_element = e_type_exists | (1 << 3),
      e_type_doesnt_exist = 0x80000000,

   };


} // namespace file


namespace install
{


   class installer;


} // namespace install

//#include "acme/primitive/primitive/transfer.h"

class task;




class machine_event_data;

namespace hotplugin
{

   class host;


   class plugin;

}


namespace html
{


   class html;


   class element;


} // namespace html


namespace audio
{


   class plugin;


} // namespace audio

class file_time;

class time;


namespace earth
{


   class date_span;

   class time_span;

   class time;


} // namespace earth


class folder;

class memory_file;

extern "C"
typedef ::acme::library * NEW_LIBRARY();

typedef NEW_LIBRARY * PFN_NEW_LIBRARY;




namespace draw2d
{


   class graphics;



} // namespace draw2d


namespace handle
{


   class ini;


} // namespace handle


struct system_time_t;

//class scalar_base;


CLASS_DECL_ACME int __node_is_debugger_attached();

class create_task_attributes;
class security_attributes;


namespace operating_system
{


   CLASS_DECL_ACME const char * get_message_text(enum_message emessage);


} // namespace operating_system


namespace acme
{

   class static_start;

   class session;

   class system;

   class application;


   extern CLASS_DECL_ACME bool g_bAcme;


} // namespace acme


class acme_directory;

class acme_file;

class acme_path;


namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)
{


   class acme_directory;

   class acme_file;

   class acme_path;


} // namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)




class signal;
class backing;
class manager;
class topic;
class context;
//class handler;
//template < typename RESULT > class process;
class extended_topic;


namespace dynamic_source
{


   class script_interface;


} // namespace dynamic_source





namespace apex
{


   class theme;


   class context;


   class idpool;


   class system;


   class session;


   class node;


   //   class application;


} // namespace apex


namespace aqua
{


   class system;


   class session;


   class application;


} // namespace aqua


namespace aura
{


   class theme;


   class context;


   class idpool;


   class application;


   class session;


   class node;


   class system;


} // namespace aura


namespace axis
{


   class idpool;


   class application;


   class session;


   class system;


   class user;


} // namespace axis


namespace base
{


   class idpool;


   class application;


   class session;


   class system;


   class user;


} // namespace base


namespace bred
{

   class system;


   class session;


   class application;

} // namespace bred


namespace core
{


   //   class idpool;


   class application;


   class session;


   class system;


} // namespace core



class machine_event_central;

struct block;


class payload;
struct block;







class trait;


class request;


class composite_base;





namespace write_text
{


   class font_enumeration_item;



} // namespace write_text









namespace draw2d
{


   class graphics;
   class path;


} // namespace draw2d


class wcsdup_array;




namespace geometry
{

   class geometry;

} // namespace geometry

class compress;
class uncompress;

//class system_impl;


//namespace str
//{
//
class base64;
//
//} // namespace str


namespace acme
{

   class library;


   //   using library_map = string_map < ::pointer<::acme::library >>;

} // namespace acme

class task_group;
class task_tool;



class node_data_exchange;

namespace xml
{


   class xml;


} // namespace xml





class ftpfs;


namespace fs
{

   class remote_native;


   class fs;


   class data;

}

class ifs;



namespace file
{

   class watcher;

} // namespace file







class mq_base;


namespace acme
{


   class timer_array;


} // namespace acme


namespace file
{


   class path;
   class path_object;
   class path_array;


} // namespace file

class task;


#ifdef WINDOWS_DESKTOP

struct hwnd { }; // as pointer is a HWND

using oswindow_t = hwnd;

#else

using oswindow_t = ::windowing::window;

#endif


using oswindow = oswindow_t*;




namespace core
{


   class user;


} // namespace core




namespace http
{

   class context;

} // namespace http


class object_meta;


class manual_reset_event;





namespace factory
{


   class factory_item_interface;


} // namespace factory


namespace user
{


   class interaction;

   class form;


} // namespace user




class thread;


namespace user
{

   class primitive;

   //class create;


} // namespace user


class action_context;


class event_map;


class thread_ptra;


namespace acme
{

   class topic;

} // namespace acme


class memory_base;





namespace message
{


   class message;


} // namespace status


class parents;


class children;


//namespace exception
//{


class exception;

//using exception_pointer = ::pointer<exception>


//} // namespace exception



namespace message
{


   class message;


} // namespace message


class sticker;



class context_image;


using lresult = iptr;



namespace mathematics
{

   class mathematics;

} // namespace mathematics





class type;

namespace text
{

   class text;
   class data;
   class translator;


   class table;
   class context;


   namespace international
   {

      class locale_schema;

   }


} // namespace text




class conversation;




class thread_parameter;






class atom;


namespace calculator
{


   class value;


} // namespace calculator


#ifndef WINDOWS_DESKTOP

typedef void* HDWP;

#endif


namespace factory
{


   class factory;


} // namespace factory




typedef bool FN_TIMER(timer* ptimer);

typedef FN_TIMER* PFN_TIMER;



class event;


namespace html
{

   class html; // defined and set by html library/component

}


class image_list;


namespace acme
{


   class file;



   namespace trace
   {

      class trace;

   }

   class session;

} // namespace acme


// only usable from base and base dependants
namespace base
{

   class application;

   class session;


   class system;

}


class app_core;


namespace data
{


   class item;


} // namespace data


namespace xml
{


   class node;


   class document;


} // namespace xml






typedef void(*PFN_factory)(::factory::factory* pfactory);



using argument = payload;




namespace message
{


   class particle;
   class key;
   class mouse;
   class context_menu;


} // namespace message


class request;


namespace nano
{

   class nano;

} // namespace nano


