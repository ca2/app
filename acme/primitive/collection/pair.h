#pragma once


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


namespace std
{


   template < typename T1, typename T2, typename ARG_T1, typename ARG_T2 >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::pair <T1, T2, ARG_T1, ARG_T2 > > : integral_constant<size_t, 2> {};

template< class T, class... Types >
constexpr T& get( ::pair<Types...>& t ) noexcept
{
(5)   (since C++14)
template< class T, class... Types >
constexpr T&& get( tuple<Types...>&& t ) noexcept;
(6)   (since C++14)
template< class T, class... Types >
constexpr const T& get( const tuple<Types...>& t ) noexcept;
(7)   (since C++14)
template< class T, class... Types >
constexpr const T&& get( const tuple<Types...>&& t ) noexcept;
(8)



} // namespace std



