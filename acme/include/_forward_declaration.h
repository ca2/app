//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/09/22 22:30
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once


class subparticle;


template<typename ENUM>
struct raw_enum_of_struct
{
   using type = ENUM;
};


template<class TYPE, TYPE t>
struct integral_constant
{

   inline static constexpr TYPE payload = t;

};


template<bool b>
using bool_constant = integral_constant<bool, b>;


using true_type = bool_constant<true>;

using false_type = bool_constant<false>;


template<class T>
struct is_const_struct : false_type
{
};


template<class T>
struct is_const_struct<const T> : true_type
{
};


template<class T>
inline constexpr bool is_const = is_const_struct<T>::payload;


template<class T>
struct is_reference_struct : false_type
{
};


template<class T>
struct is_reference_struct<T &> : true_type
{
};


template<class T>
struct is_reference_struct<T &&> : true_type
{
};


template<class T>
inline constexpr bool is_reference = is_reference_struct<T>::payload;


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
struct const_of_struct<TYPE *>
{
   using CONST_OF_TYPE = const TYPE *;
};


template<typename TYPE>
struct const_of_struct<TYPE const &>
{
   using CONST_OF_TYPE = const TYPE &;
};


template<typename TYPE>
struct const_of_struct<TYPE * const>
{
   using CONST_OF_TYPE = const TYPE *;
};


template<typename TYPE>
struct const_of_struct<TYPE const &&>
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


template<typename TYPE>
struct erase_const_struct
{
   using NON_CONST_TYPE = TYPE;
};


template<typename TYPE>
struct erase_const_struct<TYPE &>
{
   using NON_CONST_TYPE = TYPE &;
};


template<typename TYPE>
struct erase_const_struct<const TYPE>
{
   using NON_CONST_TYPE = TYPE;
};


template<typename TYPE>
struct erase_const_struct<const TYPE &>
{
   using NON_CONST_TYPE = TYPE &;
};


template<typename TYPE>
struct erase_const_struct<const TYPE *>
{
   using NON_CONST_TYPE = TYPE *;
};


template<typename TYPE>
struct erase_const_struct<const TYPE &&>
{
   using NON_CONST_TYPE = TYPE &&;
};


template<typename TYPE>
using non_const = typename erase_const_struct<TYPE>::NON_CONST_TYPE;


template<typename TYPE>
struct erase_reference_struct
{
   using NON_REFERENCE_TYPE = TYPE;
};


template<typename TYPE>
struct erase_reference_struct<TYPE &>
{
   using NON_REFERENCE_TYPE = TYPE;
};


template<typename TYPE>
struct erase_reference_struct<const TYPE &>
{
   using NON_REFERENCE_TYPE = const TYPE;
};


template<typename TYPE>
struct erase_reference_struct<TYPE &&>
{
   using NON_REFERENCE_TYPE = TYPE;
};


template<typename TYPE>
struct erase_reference_struct<const TYPE &&>
{
   using NON_REFERENCE_TYPE = const TYPE;
};


template<typename TYPE>
using non_reference = typename erase_reference_struct<TYPE>::NON_REFERENCE_TYPE;


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


//constexpr unsigned long long operator "" _uintmax(unsigned long long u) { return u << 32LL; }

template<typename DERIVED, typename BASE>
concept is_derived_from =
   ::std::is_base_of<BASE, DERIVED>::value;


template<bool B, class TRUE_TYPE = void, class ELSE_TYPE = void>
struct if_else_base
{
};


template<class TRUE_TYPE, class ELSE_TYPE>
struct if_else_base<true, TRUE_TYPE, ELSE_TYPE>
{
   using type = TRUE_TYPE;
};


template<class TRUE_TYPE, class ELSE_TYPE>
struct if_else_base<false, TRUE_TYPE, ELSE_TYPE>
{
   using type = ELSE_TYPE;
};


template<bool B, class TRUE_TYPE = void, class ELSE_TYPE = void>
using if_else = typename if_else_base<B, TRUE_TYPE, ELSE_TYPE>::type;



template<typename T>
struct is_raw_array_struct : ::false_type
{
};

template<typename T, std::size_t N>
struct is_raw_array_struct<T[N]> : ::true_type
{
};

template<typename T, std::size_t N>
struct is_raw_array_struct<T (&)[N]> : ::true_type
{
};

template<typename T>
struct is_raw_array_struct<T[]> : ::true_type
{
};

template<typename T>
struct is_raw_array_struct<T (&)[]> : ::true_type
{
};

template<class T>
inline constexpr bool is_raw_array = is_raw_array_struct<T>::payload;


template<typename T>
struct erase_const_effemeral_struct
{
   using type = T;
};

template<typename T>
struct erase_const_effemeral_struct<const T>
{
   using type = T;
};

template<typename T>
struct erase_const_effemeral_struct<volatile T>
{
   using type = T;
};

template<typename T>
struct erase_const_effemeral_struct<const volatile T>
{
   using type = T;
};


template<typename T>
using erase_const_effemeral = typename erase_const_effemeral_struct<T>::type;




template<typename>
struct is_raw_pointer_bool : public false_type
{
};

template<typename T>
struct is_raw_pointer_bool<T *> : public true_type
{
};


template<typename T>
struct is_raw_pointer_struct : public is_raw_pointer_bool<erase_const_effemeral<T>>
{
};


template<typename T>
inline constexpr bool is_raw_pointer = is_raw_pointer_struct<T>::payload;


template<typename POINTER>
concept prototype_raw_pointer = ::is_raw_pointer<POINTER>;

namespace inner_detail
{
   template<class T>
   struct type_identity
   {
      using type = T;
   }; // or use std::type_identity (since C++20)

   template<class T>
   auto try_add_pointer(int) -> type_identity<non_reference<T> *>;


   template<class T>
   auto try_add_pointer(...) -> type_identity<T>;
} // namespace detail

template<class T>
struct add_pointer_struct : decltype(inner_detail::try_add_pointer<T>(0))
{
};


template<typename T>
using add_pointer = typename add_pointer_struct<T>::type;


template<class T>
struct erase_pointer_struct
{
   typedef T type;
};


template<class T>
struct erase_pointer_struct<T *>
{
   typedef T type;
};


template<class T>
struct erase_pointer_struct<T * const>
{
   typedef T type;
};


template<class T>
struct erase_pointer_struct<T * volatile>
{
   typedef T type;
};


template<class T>
struct erase_pointer_struct<T * const volatile>
{
   typedef T type;
};


template<typename T>
using non_pointer = typename erase_pointer_struct<T>::type;


template<class T>
struct erase_extent_struct
{
   using type = T;
};


template<class T>
struct erase_extent_struct<T[]>
{
   using type = T;
};


template<class T, std::size_t N>
struct erase_extent_struct<T[N]>
{
   using type = T;
};


template<typename T>
using non_extent = typename erase_extent_struct<T>::type;


#if REFERENCING_DEBUGGING


class reference_referer;


namespace allocator
{


   //CLASS_DECL_ACME ::reference_referer* defer_add_referer(const ::reference_referer& referer);


   CLASS_DECL_ACME ::reference_referer* push_referer(const ::reference_referer& referer);

   CLASS_DECL_ACME ::reference_referer * defer_push_referer(::subparticle * psubparticleExisting, const ::reference_referer& referer);


   CLASS_DECL_ACME void _push_referer(::reference_referer* preferer);


   //CLASS_DECL_ACME ::reference_referer* defer_pop_referer(::subparticle* p, const ::reference_referer& referer);


   //CLASS_DECL_ACME ::reference_referer* get_referer();


   CLASS_DECL_ACME ::reference_referer* pop_referer();


   CLASS_DECL_ACME ::reference_referer* get_top_referer();


   CLASS_DECL_ACME void defer_erase_referer();


   CLASS_DECL_ACME void defer_erase_referer(::subparticle * psubparticle);


   CLASS_DECL_ACME void erase_referer(::reference_referer* preferer);


   CLASS_DECL_ACME void add_releaser(::reference_referer* preferer);


   CLASS_DECL_ACME ::reference_referer* get_releaser();


   CLASS_DECL_ACME ::reference_referer* pop_releaser();


   CLASS_DECL_ACME void defer_erase_releaser(bool bParticleReferencingDebuggingEnabled);


   CLASS_DECL_ACME void erase_releaser(::reference_referer* preferer);


} // namespace allocator


#endif


template<typename T>
struct is_function_struct : ::integral_constant<
      bool,
      !is_const<const T> && !is_reference<T>
   >
{
};


template<typename T>
inline constexpr bool is_function = is_function_struct<T>::payload;


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
   if_else<
      is_raw_array<U>,
      add_pointer<non_extent<U>>,
      if_else<
         is_function<U>, add_pointer<U>, non_const<U>>
   >;
};


template<typename T>
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


namespace platform
{


   class system; // acme - cam


   class application;
   // apex(::apex::application) - tbs offloading his deep stack in ::platform::application(::acme):cstbs

   class session;


   class system_factory;

   class context;

   class application_container;

   class static_start;

   class node;
   class library;


   class http;


} // namespace platform


class memory_counter;


namespace acme_posix
{


   class node;


} // namespace acme_posix


namespace
IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)
{


   class node;
   class buffer;


} // namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)


namespace acme_posix
{
   class node;
}


namespace apex_posix
{
   class node;
}


namespace aura_posix
{
   class node;
}


namespace
IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)
{
   class node;
}


namespace
IDENTIFIER_SUFFIX_OPERATING_SYSTEM(apex_)
{
   class node;
}


namespace
IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)
{
   class node;
}


// namespace acme
// {
//
//
//    class system;
//
//
//    class node;
//
//
// } // namespace acme


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


//class os_context;


namespace node_gtk3
{


   class node;


} // namespace node_gtk3


namespace node_gtk4
{


   class node;


} // namespace node_gtk4


namespace node_gtk_based
{


   class node;


} // namespace node_gtk_based


namespace node_kde5
{


   class node;


} // namespace node_kde5


namespace node_kde6
{


   class node;


} // namespace node_kde6


namespace node_xfce
{


   class node;


} // namespace node_xfce


namespace windowing
{

   class window;

} // namespace windowing


namespace windows
{


   class generic_handle;


} // namespace windows


using hinstance = void *;
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


// namespace acme
// {
//
//    class system;
//    class context;
//    class library;
//    class node;
//    class application;
//    class exclusive;
//
// } // namespace acme


namespace apex
{


   class application;


} // namespace apex


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

namespace platform
{
   class message;
} // namespace message
namespace message
{
   class message;
} // namespace message
namespace user
{
   class message;
} // namespace message

class value;
struct block;
class property_set;
class subparticle;
class particle;
//class element;
class matter;
class exception_translator;
//class counter;
//class type;

class file_system;
class path_system;
class directory_system;


namespace platform
{


   class platform;


   //inline ::platform::platform * get();


} // namespace platform


class directory_context;
class directory_system;
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
//   class item;


} // namespace data


class memory_base;


struct HAS_STRING_LABEL_TAG
{
};


struct PRIMITIVE_BLOCK_TAG_TYPE
{
};


struct PRIMITIVE_CONTAINER_TAG_TYPE
{
};


struct PRIMITIVE_PAYLOAD_TAG_TYPE
{
};


struct PRIMITIVE_ATOM_TAG_TYPE
{
};


struct PRIMITIVE_STRING_TAG_TYPE
{
};


struct PRIMITIVE_SCOPED_STRING_TAG_TYPE
{
};


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

   class message;
   class session;

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

   class interaction_base;
   class element;
   class prototype_impl;

   class item;


} // namespace user


class conversation;


namespace image
{


   class image;


   class image_list;


   class image_context;


   class imaging;


   class icon;


   class cursor;


} // namespace image


//class e_check;
//class boolean;


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

CLASS_DECL_ACME subparticle* as_subparticle(const payload& payload);


struct MESSAGE;

class item;


class memory;


class istring;


class property_set;


class payload_array_base;

//using payload_array = ::make_particle < payload_array_base >;


class property;


class timer_future;


namespace acme
{

   class Timer;

   class exclusive;


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
   class http_client_socket;
   class http_tunnel;

} // namespace sockets // only usable from base.dll and dependants


namespace simpledb
{

   class server;

}


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

   class listing_base;


   class path;


   class file;


   enum enum_type : int
   {

      e_type_unknown = 0,
      e_type_exists = 1 << 0,
      e_type_folder2 = 1 << 1,
      e_type_file2 = 1 << 2,
      e_type_element2 = 1 << 3,
      e_type_executable = 1 << 4,
      e_type_non_executable = 1 << 5,
      e_type_existent_folder = e_type_exists | e_type_folder2,
      e_type_existent_file = e_type_exists | e_type_file2,
      e_type_existent_element = e_type_exists | e_type_element2,
      e_type_file_or_folder2 = e_type_folder2 | e_type_file2,
      e_type_existent_file_or_folder = e_type_exists | e_type_folder2 | e_type_file2,
      e_type_doesnt_exist = I32_MINIMUM,

   };


} // namespace file


constexpr bool is_existent_folder(::file::enum_type etype)
{

   return (etype & ::file::e_type_existent_folder) == ::file::e_type_existent_folder;

}


constexpr bool is_existent_file(::file::enum_type etype)
{

   return (etype & ::file::e_type_existent_file) == ::file::e_type_existent_file;

}


namespace install
{


   class installer;


} // namespace install

//#include "acme/prototype/prototype/transfer.h"

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
typedef ::platform::library* NEW_LIBRARY();


typedef NEW_LIBRARY* PFN_NEW_LIBRARY;


namespace draw2d
{


   class graphics;


} // namespace draw2d


//namespace handle
//{
//
//
//   class ini;
//
//
//} // namespace handle


struct system_time_t;

//class scalar_base;


CLASS_DECL_ACME int __node_is_debugger_attached();


struct create_task_attributes_t;
class create_task_attributes;
class security_attributes;


namespace user
{


   CLASS_DECL_ACME const_char_pointer get_message_text(::user::enum_message eusermessage);


} // namespace operating_system


// namespace acme
// {
//
//    class static_start;
//
//    class session;
//
//    class system;
//
//    class application;
//
//
// //   extern CLASS_DECL_ACME bool g_bAcme;
//
//
// } // namespace acme


class directory_system;

class file_system;

class path_system;


namespace
IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)
{


   class directory_system;

   class file_system;

   class path_system;


} // namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)


namespace handler
{
   class signal;
}


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


   class application;


} // namespace apex


namespace aqua
{


   class system;


   class session;


   class application;


} // namespace aqua


namespace user
{


   class user;


} // namespace user


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


namespace berg
{


   class idpool;


   class application;


   class session;


   class system;

   
   class user;


} // namespace berg


namespace bred
{


   class system;


   class session;


   class application;


   class user;


} // namespace bred


namespace core
{


   class application;


   class session;


   class system;

   
   class user;


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


   //   using library_map = string_map_base < ::pointer<::acme::library >>;

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

namespace windowing
{

class window;

}


} // namespace acme


namespace file
{


   class path;
   class path_object;
   class path_array;


} // namespace file

class task;


#ifdef WINDOWS_DESKTOP

struct hwnd
{
}; // as pointer is a HWND

using oswindow_t = hwnd;

#else

using oswindow_t = ::acme::windowing::window;

#endif


using oswindow = oswindow_t *;


namespace core
{


   class user;


} // namespace core


namespace http
{


   class context;

   class proxy;
   class pac;


} // namespace http


class object_meta;


class manual_reset_happening;


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


using lresult = iptr;


namespace mathematics
{

   class mathematics;

} // namespace mathematics


//class type;

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


class happening;


namespace html
{

   class html; // defined and set by html library/component

}


namespace acme
{


   class file;


   namespace trace
   {

      class trace;

   }


} // namespace acme


// only usable from base and base dependants
namespace berg
{

   class application;

   class session;


   class system;

}


class app_core;


namespace xml
{


   class node;


   class document;


} // namespace xml


typedef void (*PFN_factory)(::factory::factory* pfactory);


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


   namespace http
   {
      class http;
   } //namespace http


} // namespace nano


template<typename ARGUMENT>
struct argument_of_struct
{

   using type = const ARGUMENT &;

};


template<typename TYPE>
struct argument_of_struct<TYPE *>
{

   using type = TYPE *;

};


//template < prototype_function FUNCTION >
//struct argument_of_struct < FUNCTION >
//{
//
//   using type = FUNCTION;
//
//};


template<typename ARGUMENT>
using argument_of = typename argument_of_struct<ARGUMENT>::type;


namespace user
{


   class key_state;


} // namespace user


namespace acme
{
   class system_factory;

}


namespace innate_ui
{


   class innate_ui;


} // namespace innate_ui
namespace hardware
{

   class devices;

} // namespace hardware

namespace aura
{

   class estamira;

} // namespace aura

namespace user
{

   class frame_interaction;

} // namespace user


namespace networking
{

   class networking;

} // namespace networking


class manager_room;


namespace parallelization
{
   class threading;


} //namespace parallelization


namespace input
{

   class input;

}


namespace apex
{

   class history;

}


namespace aqua
{


   class audio;

   class audio_mixer;
   class multimedia;

   class audio_mixe;

   class estamira;


}


struct os_theme_colors;


namespace file
{
   class set;
}


namespace windowing
{
   class display;
}


class get_file_extension_mime_type;
//template<class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//class comparable_array;
class application_menu;


namespace user
{
   class language_map;

}


namespace interprocess
{

   class communication;
   class handler;

}


class service_handler;


namespace fs
{

   class folder_sync;
   class set;

}


class service;


namespace database
{

   class client;
   class server;

}


namespace innate_ui
{

   class icon;

}


namespace sockets
{

   class http_session;

}


namespace networking
{

   class application_handler;
   class application_socket;

   class email_department;

}


namespace number
{
   class number;
} // namespace number


class request;


namespace progress
{


   class real;

}

class shell_open;


namespace user
{


   class interaction_array;
   class tab_impact;
   class options_impact_handler;
   class document;
   class split_impact;
   class tab;
   class menu;


}



namespace aura
{

class game;

}





class main_hold_base;

struct platform_media_item_t;
namespace aqua
{

class media_item;

}


class task_message_queue;



#if REFERENCING_DEBUGGING



class referencing_debugging;


#endif




namespace account
{

   
   class department;


   class user;


   class credentials;


   class user_set;


} // namespace account


namespace geo
{


   class geo;


} // namespace geo


namespace html
{


   class html;


} // namespace html


namespace ftp
{


   class file_status;


} // namespace ftp




namespace aqua
{


   class game;


   class media_player;


} // namespace aqua




enum enum_method : int;
enum enum_future : int;




#ifdef __clang__

template<class T1, class T2>
struct is_same_struct : bool_constant<__is_same(T1, T2)>
{
};

#else

template<class, class>
constexpr bool is_same_type_bool = false;
template<class T>
constexpr bool is_same_type_bool<T, T> = true;

template<class T1, class T2>
struct is_same_struct : bool_constant<is_same_type_bool<T1, T2>>
{
};

#endif 

template<typename T1, typename T2>
inline constexpr bool is_same = is_same_struct<T1, T2>::payload;

//
//template<class>
//constexpr bool is_const_bool = false;
//
//template<class T>
//constexpr bool is_const_bool<const T> = true;
//
//template<class T>
//struct is_const_struct : bool_constant<is_const_bool<T>>
//{
//};
//
//
//template<typename T>
//inline constexpr bool is_const = is_const_struct<T1, T2>::payload;


template <typename ARRAY>
struct decay_array_struct;

template<typename ARRAY, std::size_t N>
struct decay_array_struct<ARRAY[N]>
{
    using type = ARRAY;
};

template<typename ARRAY, std::size_t N>
struct decay_array_struct<ARRAY (&)[N]> // also handles references to arrays
{
    using type = ARRAY;
};

template<typename ARRAY>
using decay_array = typename decay_array_struct<ARRAY>::type;

//
//template<typename T>
//struct is_array_struct : ::false_type
//{
//};
//
//template<typename T, std::size_t N>
//struct is_array_struct<T[N]> : ::true_type
//{
//};
//
//template<typename T, std::size_t N>
//struct is_array_struct<T (&)[N]> : ::true_type
//{
//};
//
//template<typename T>
//struct is_array_struct<T[]> : ::true_type
//{
//};
//
//template<typename T>
//struct is_array_struct<T (&)[]> : ::true_type
//{
//};
//
//template<typename T>
//inline constexpr bool is_array = is_array_struct<T>::payload;
