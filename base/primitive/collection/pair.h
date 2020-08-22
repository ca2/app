#pragma once


#ifdef CPP17


#define PAIR_IMPL(T1, T2, ARG_T1, ARG_T2, DATA1, DATA2) \
public: \
 \
 \
   typedef T1         TYPE1; \
   typedef ARG_T1     ARG_TYPE1; \
   typedef T2         TYPE2; \
   typedef ARG_T2     ARG_TYPE2; \
 \
 \
   T1       DATA1; \
   T2       DATA2; \
 \
 \
   inline T1 & element1() { return DATA1; } \
   inline T2 & element2() { return DATA2; } \
 \
   inline const T1 & element1() const { return DATA1; } \
   inline const T2 & element2() const { return DATA2; } \
template<std::size_t N> \
auto & get() const { \
   if constexpr (N == 0) return element1(); \
   else if constexpr (N == 1) return element2(); }  \
\
template<std::size_t N> \
auto & get()  { \
   \
      if constexpr (N == 0) return element1(); \
      else if constexpr (N == 1) return element2(); \
}


#else


#define PAIR_IMPL(T1, T2, ARG_T1, ARG_T2, DATA1, DATA2) \
public: \
 \
 \
   typedef T1         TYPE1; \
   typedef ARG_T1     ARG_TYPE1; \
   typedef T2         TYPE2; \
   typedef ARG_T2     ARG_TYPE2; \
 \
 \
   T1       DATA1; \
   T2       DATA2; \
 \
 \
   inline T1 & element1() { return DATA1; } \
   inline T2 & element2() { return DATA2; } \
 \
   inline const T1 & element1() const { return DATA1; } \
   inline const T2 & element2() const { return DATA2; }


#endif


#define PAIR_DEFAULT_CONSTRUCTORS(PAIR, T1, T2, ARG_T1, ARG_T2, DATA1, DATA2) \
   PAIR()\
   { \
   } \
 \
   PAIR(ARG_T1 element1) : \
      DATA1(element1) \
   { \
 \
   } \
 \
   PAIR(ARG_T1 element1, ARG_T2 element2) : \
      DATA1(element1), \
      DATA2(element2) \
   { \
 \
   }

#define PAIR_DEFAULT_IMPL(PAIR, T1, T2, ARG_T1, ARG_T2, DATA1, DATA2) \
PAIR_IMPL(T1, T2, ARG_T1, ARG_T2, DATA1, DATA2) \
PAIR_DEFAULT_CONSTRUCTORS(PAIR, T1, T2, ARG_T1, ARG_T2, DATA1, DATA2)


template < typename T1, typename T2, typename ARG_T1, typename ARG_T2 >
class pair
{

   PAIR_DEFAULT_IMPL(pair, T1, T2, ARG_T1, ARG_T2, m_element1, m_element2)

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


namespace std
{


   template < typename T1, typename T2, typename ARG_T1, typename ARG_T2 >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::pair <T1, T2, ARG_T1, ARG_T2 > > : integral_constant<size_t, 2> {};


} // namespace std
