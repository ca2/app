#pragma once

#include "acme/primitive/primitive/move.h"

//#ifdef CPP17
//
//
//#define PAIR_IMPL(T1, T2, ARG_T1, ARG_T2, m_element1, m_element2) 
//public: 
// 
// 
//   typedef T1         TYPE1; 
//   typedef ARG_T1     ARG_TYPE1; 
//   typedef T2         TYPE2; 
//   typedef ARG_T2     ARG_TYPE2; 
// 
// 
//   T1       m_element1; 
//   T2       m_element2; 
// 
// 
//   inline T1 & element1() { return m_element1; } 
//   inline T2 & element2() { return m_element2; } 
//   inline T1 & key() { return m_element1; } 
//   inline T2 & value() { return m_element2; } 
// 
//   inline const T1 & element1() const { return m_element1; } 
//   inline const T2 & element2() const { return m_element2; } 
//   inline const T1 & key() const { return m_element1; } 
//   inline const T2 & value() const { return m_element2; } 
//template<std::size_t N> 
//auto & get() const { 
//   if constexpr (N == 0) return element1(); 
//   else if constexpr (N == 1) return element2(); }  
//
//template<std::size_t N> 
//auto & get()  { 
//   
//      if constexpr (N == 0) return element1(); 
//      else if constexpr (N == 1) return element2(); 
//}
//
//
//#else
//
//
//#define PAIR_IMPL(T1, T2, ARG_T1, ARG_T2, m_element1, m_element2) 


template < typename T1, typename T2, typename ARG_T1, typename ARG_T2 >
class pair 
{
public: 
   
   
   typedef T1         TYPE1; 
   typedef ARG_T1     ARG_TYPE1; 
   typedef T2         TYPE2; 
   typedef ARG_T2     ARG_TYPE2; 

   using ELEMENT1 = T1;
   using ELEMENT2 = T2;
   
   
   T1       m_element1; 
   T2       m_element2; 
   
   
   inline T1 & element1() { return m_element1; } 
   inline T2 & element2() { return m_element2; } 
   inline T1 & first() { return m_element1; }
   inline T2 & second() { return m_element2; }
   inline T1 & key() { return m_element1; }
   inline T2 & value() { return m_element2; } 
   
   inline const T1 & element1() const { return m_element1; } 
   inline const T2 & element2() const { return m_element2; } 
   inline const T1 & first() const { return m_element1; }
   inline const T2 & second() const { return m_element2; }
   inline const T1 & key() const { return m_element1; }
   inline const T2 & value() const { return m_element2; }

   pair()
   { 
   } 
 
   pair(ARG_T1 element1) : 
      m_element1(element1) 
   { 
 
   } 
 
   pair(ARG_T1 element1, ARG_T2 element2) : 
      m_element1(element1), 
      m_element2(element2) 
   { 
 
   }


   pair & get_pair(T1 & t1, T2 & t2)
   {

      t1 = m_element1;

      t2 = m_element2;

   }


};


#if defined(ANDROID)

#define ALIENATED_ANDROID_ANARCHY class

#else

#define ALIENATED_ANDROID_ANARCHY struct

#endif

template<typename A, typename B> pair(A, B) -> pair<A, B>;

#include <utility>

#include <tuple>

namespace std
{


template < size_t n, typename A, typename B, typename ARG_A, typename ARG_B >
struct tuple_element < n, ::pair < A, B, ARG_A, ARG_B > >
{
   
   static_assert(n < 2, "pair index out of bounds");
   
   using type = conditional_t < n == 0, A, B >;
   
};

template < typename A, typename B, typename ARG_A, typename ARG_B >
ALIENATED_ANDROID_ANARCHY tuple_size< ::pair < A, B, ARG_A, ARG_B > > : integral_constant<size_t, 2> {};

}//namespace std
//#ifdef WINDOWS_DESKTOP
   template < size_t n, typename A, typename B, typename ARG_A, typename ARG_B >
   constexpr typename std::tuple_element < n, ::pair < A, B, ARG_A, ARG_B > >::type &
      get(::pair < A, B, ARG_A, ARG_B > & pair)
   {

      if constexpr (n % 2 == 0)
      {

         return pair.m_element1;

      }
      else
      {
         
         return pair.m_element2;
         
      }

   }


   template < size_t n, typename A, typename B, typename ARG_A, typename ARG_B >
   constexpr const typename std::tuple_element < n, ::pair < A, B, ARG_A, ARG_B > >::type & 
      get(const ::pair < A, B, ARG_A, ARG_B > & pair) noexcept
   {
      
      if constexpr (n %2 == 0)
      {

         return pair.m_element1;

      }
      else
      {
      
         return pair.m_element2;
      
      }

   }


   template < size_t n, typename A, typename B, typename ARG_A, typename ARG_B >
   constexpr typename std::tuple_element < n, ::pair < A, B, ARG_A, ARG_B > >::type &&
      get(::pair < A, B, ARG_A, ARG_B > && pair)
   {

      if constexpr (n % 2 == 0)
      {

         return ::move(pair.m_element1);

      }
      else
      {

         return ::move(pair.m_element2);

      }

   }


   template < size_t n, typename A, typename B, typename ARG_A, typename ARG_B >
   constexpr const typename std::tuple_element < n, ::pair < A, B, ARG_A, ARG_B > >::type &&
      get(const ::pair < A, B, ARG_A, ARG_B > && pair) noexcept
   {

      if constexpr (n % 2 == 0)
      {

         return ::move(pair.m_element1);

      }
      else
      {

         return ::move(pair.m_element2);

      }

   }

//#endif
//
//} // namespace std
//
//#if !defined(WINDOWS_DESKTOP)
//
//template <size_t n, class _T1, class _T2>
//inline constexpr
//typename ::std::tuple_element<n, ::pair<_T1, _T2> >::type&
//get(::pair<_T1, _T2>& pair) _NOEXCEPT
//{
//   if constexpr (n %2 == 0)
//   {
//
//      return pair.m_element1;
//
//   }
//   else
//   {
//
//      return pair.m_element2;
//
//   }
//
//}
//
//template <size_t n, class _T1, class _T2>
//inline constexpr
//const typename ::std::tuple_element<n, ::pair<_T1, _T2> >::type&
//get(const ::pair<_T1, _T2>& pair) _NOEXCEPT
//{
//   if constexpr (n %2 == 0)
//   {
//
//      return (_T1&)pair.m_element1;
//
//   }
//   else
//   {
//
//      return (_T2&)pair.m_element2;
//
//   }
//
//}
//
//
//#endif
//
