#pragma once


#include <tuple>
// OpenBSD it includes <version> that includes <string> that includes <cstdio> that includes <stdio.h>


namespace std
{


   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::set_node < PAIR > > : public ::integral_constant<size_t, 2> {};

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 0, set_node < PAIR > >
   {
   public:
      using type = typename ::set_node < PAIR >::TYPE1;
   };

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 1, set_node < PAIR > >
   {
   public:
      using type = typename ::set_node < PAIR >::TYPE2;
   };


} // namespace std


namespace std
{


   template < typename T1, typename T2 >
   struct tuple_element < 0, ::pair < T1, T2 > >
   {

      using type = T1;

   };


   template < typename T1, typename T2 >
   struct tuple_element < 1, ::pair < T1, T2 > >
   {

      using type = T2;

   };


} // namespace std

   
template < size_t n, typename T1, typename T2 >
constexpr typename std::tuple_element < n, ::pair < T1, T2 > >::type& get(::pair < T1, T2 > & pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return pair.element1();

   }
   else
   {

      return pair.element2();

   }

}


template < size_t n, typename T1, typename T2 >
constexpr const typename std::tuple_element < n, ::pair < T1, T2 > >::type& get(const ::pair < T1, T2 > & pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return pair.element1();

   }
   else
   {

      return pair.element2();

   }

}


template < size_t n, typename T1, typename T2 >
constexpr typename std::tuple_element < n, ::pair < T1, T2 > >::type&& get(::pair < T1, T2 > && pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return ::transfer(pair.transfer_element1());

   }
   else
   {

      return ::transfer(pair.transfer_element2());

   }

}


template < size_t n, typename T1, typename T2 >
constexpr const typename std::tuple_element < n, ::pair < T1, T2 > >::type&& get(const ::pair < T1, T2 > && pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return ::transfer(pair.transfer_element1());

   }
   else
   {

      return ::transfer(pair.transfer_element2());

   }

}



namespace std
{


   template < size_t n, typename PAIR >
   struct tuple_element < n, ::make_pair < PAIR > >
   {
   
      static_assert(n < 2, "pair index out of bounds");
   
      using type = conditional_t < n == 0, typename PAIR::TYPE1, typename PAIR::TYPE2 >;
   
   };


   template < typename A, typename B >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::pair < A, B > > : public ::integral_constant<size_t, 2> {};

} //namespace std






template < size_t n, typename PAIR >
constexpr typename std::tuple_element < n, ::make_pair < PAIR > >::type& get(::make_pair < PAIR > & pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return pair.element1();

   }
   else
   {

      return pair.element2();

   }

}


template < size_t n, typename PAIR >
constexpr const typename std::tuple_element < n, ::make_pair < PAIR > >::type& get(const ::make_pair < PAIR > & pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return pair.element1();

   }
   else
   {

      return pair.element2();

   }

}


template < size_t n, typename PAIR >
constexpr typename std::tuple_element < n, ::make_pair < PAIR > >::type&& get(::make_pair < PAIR > && pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return ::transfer(pair.transfer_element1());

   }
   else
   {

      return ::transfer(pair.transfer_element2());

   }

}


template < size_t n, typename PAIR >
constexpr const typename std::tuple_element < n, ::make_pair < PAIR > >::type&& get(const ::make_pair < PAIR > && pair)
{

   static_assert(n < 2, "index not accepted for a pair");

   if constexpr (n == 0)
   {

      return ::transfer(pair.move_element1());

   }
   else
   {

      return ::transfer(pair.move_element2());

   }

}


#if defined(__ANDROID__)

#define ALIENATED_ANDROID_ANARCHY class

#else

#define ALIENATED_ANDROID_ANARCHY struct

#endif


namespace std
{


   template < typename T >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::single <T > > : integral_constant<size_t, 1> {};


} // namespace std



