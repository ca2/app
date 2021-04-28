#pragma once


#ifdef CPP17


#define SINGLE_IMPL(T, ARG_T, ARG_DATA) \
public: \
 \
 \
   typedef T         TYPE; \
   typedef ARG_T     ARG_TYPE; \
   typedef T2         TYPE2; \
   typedef ARG_T2     ARG_TYPE2; \
 \
 \
   T       DATA; \
   T2       DATA2; \
 \
 \
   inline T & element() { return DATA; } \
   inline T2 & element2() { return DATA2; } \
 \
   inline const T & element() const { return DATA; } \
   inline const T2 & element2() const { return DATA2; } \
template<std::size_t N> \
auto & get() const { \
   if constexpr (N == 0) return element(); \
   else if constexpr (N == 1) return element2(); }  \
\
template<std::size_t N> \
auto & get()  { \
   \
      if constexpr (N == 0) return element(); \
      else if constexpr (N == 1) return element2(); \
}


#else


#define SINGLE_IMPL(T, ARG_T, DATA) \
public: \
 \
 \
   typedef T         TYPE; \
   typedef ARG_T     ARG_TYPE; \
 \
 \
   T       DATA; \
 \
 \
   inline T & element() { return DATA; } \
   inline T & key() { return DATA; } \
 \
   inline const T & element() const { return DATA; } \
inline const T& key() const { return DATA; }


#endif


#define SINGLE_DEFAULT_CONSTRUCTORS(SINGLE, T, ARG_T, DATA) \
   SINGLE()\
   { \
   } \
 \
   SINGLE(ARG_T element) : \
      DATA(element) \
   { \
 \
   } \
 \

#define SINGLE_DEFAULT_IMPL(SINGLE, T, ARG_T, ARG_DATA) \
SINGLE_IMPL(T, ARG_T, ARG_DATA) \
SINGLE_DEFAULT_CONSTRUCTORS(SINGLE, T, ARG_T, ARG_DATA)


template < typename T, typename ARG_T >
class single
{

   SINGLE_DEFAULT_IMPL(single, T, ARG_T, m_element)

   single & get_single(T & t)
   {

      t = m_element;

   }


};


#if defined(ANDROID)

#define ALIENATED_ANDROID_ANARCHY class

#else

#define ALIENATED_ANDROID_ANARCHY struct

#endif


namespace std
{


   template < typename T, typename ARG_T >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::single <T, ARG_T > > : integral_constant<size_t, 1> {};


} // namespace std
