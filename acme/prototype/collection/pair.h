#pragma once


#include "acme/prototype/prototype/transfer.h"
//#include "acme/prototype/prototype/_u32hash.h"


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

//#define PAIR_TUPLE(PAIR, T1, T2, MEMBER1, MEMBER2) \
//   template < > \
//   struct std::tuple_element < 0, PAIR > \
//   { \
//      \
//      using type = T1; \
//      \
//   }; \
//   \
//   \
//   template <  > \
//   struct tuple_element < 1, PAIR > \
//   { \
//      \
//      using type = T2; \
//      \
//   }; \
//   \
//} \
//\
//template < > constexpr T1 & get<0>(PAIR & pair) { return pair.MEMBER1; } \
//template < > constexpr T2 & get<1>(PAIR & pair) { return pair.MEMBER2; } \
//template < > constexpr T1 && get<0>(PAIR && pair) { return pair.MEMBER1; } \
//template < > constexpr T2 && get<1>(PAIR && pair) { return pair.MEMBER2; } \
//template < > constexpr const T1 & get<0>(const PAIR & pair) { return pair.MEMBER1; } \
//template < > constexpr const T2 & get<1>(const PAIR & pair) { return pair.MEMBER2; } \
//template < > constexpr const T1 && get<0>(const PAIR && pair) { return pair.MEMBER1; } \
//template < > constexpr const T2 && get<1>(const PAIR && pair) { return pair.MEMBER2; }

#include "acme/memory/quantum.h"


#define MAKE_PAIR(PAIR, T1, T2, MEMBER1, MEMBER2) \
class PAIR : \
   public memory_quantum\
{  \
public: \
\
\
   using TYPE1 = T1;                               \
   using TYPE2 = T2;                               \
   using CONST_TYPE1 = ::const_of < TYPE1 >;       \
   using CONST_TYPE2 = ::const_of < TYPE2 >;       \
   using ARG_TYPE1 = ::argument_of < TYPE1 >;\
   using ARG_TYPE2 = ::argument_of < TYPE2 >;\
\
\
   T1       MEMBER1;\
   T2       MEMBER2;\
\
\
   inline T1 & element1() { return MEMBER1; } \
   inline T2 & element2() { return MEMBER2; } \
   inline CONST_TYPE1 & element1() const { return (CONST_TYPE1 &) MEMBER1; } \
   inline CONST_TYPE2 & element2() const { return (CONST_TYPE2 &) MEMBER2; } \
   inline T1 && transfer_element1() { return ::transfer(MEMBER1); } \
   inline T2 && transfer_element2() { return ::transfer(MEMBER2); } \
   inline CONST_TYPE1 && transfer_element1() const { return (CONST_TYPE1 &&) ::transfer(MEMBER1); } \
   inline CONST_TYPE2 && transfer_element2() const { return (CONST_TYPE2 &&) ::transfer(MEMBER2); } \
   inline T1 & key() { return MEMBER1; } \
   inline T2 & value() { return MEMBER2; } \
   inline CONST_TYPE1 & key() const { return (CONST_TYPE1 &) MEMBER1; } \
   inline CONST_TYPE2 & value() const { return (CONST_TYPE2 &) MEMBER2; } \
   inline T1 && transfer_key() { return ::transfer(MEMBER1); } \
   inline T2 && transfer_value() { return ::transfer(MEMBER2); } \
   inline CONST_TYPE1 && transfer_key() const { return (CONST_TYPE1 &&) ::transfer(MEMBER1); } \
   inline CONST_TYPE2 && transfer_value() const { return (CONST_TYPE2 &&) ::transfer(MEMBER2); } \
\
\
   PAIR() {} \
   PAIR(ARG_TYPE1 t1) : MEMBER1(t1) {} \
   PAIR(ARG_TYPE1 t1, ARG_TYPE2 t2) : MEMBER1(t1), MEMBER2(t2) {}   \
\
\
}



#define MAKE_PAIR2(PAIR, T1, T2, MEMBER1, MEMBER2, member1, member2) \
class PAIR : \
public memory_quantum\
{  \
public: \
\
\
using TYPE1 = T1;                               \
using TYPE2 = T2;                               \
using CONST_TYPE1 = ::const_of < TYPE1 >;       \
using CONST_TYPE2 = ::const_of < TYPE2 >;       \
using ARG_TYPE1 = ::argument_of < TYPE1 >;\
using ARG_TYPE2 = ::argument_of < TYPE2 >;\
\
\
T1       MEMBER1;\
T2       MEMBER2;\
\
\
inline T1 & element1() { return MEMBER1; } \
inline T2 & element2() { return MEMBER2; } \
inline T1 & member1() { return MEMBER1; } \
inline T2 & member2() { return MEMBER2; } \
inline CONST_TYPE1 & element1() const { return (CONST_TYPE1 &) MEMBER1; } \
inline CONST_TYPE2 & element2() const { return (CONST_TYPE2 &) MEMBER2; } \
inline CONST_TYPE1 & member1() const { return (CONST_TYPE1 &) MEMBER1; } \
inline CONST_TYPE2 & member2() const { return (CONST_TYPE2 &) MEMBER2; } \
inline T1 && transfer_element1() { return ::transfer(MEMBER1); } \
inline T2 && transfer_element2() { return ::transfer(MEMBER2); } \
inline T1 && transfer_##member1() { return ::transfer(MEMBER1); } \
inline T2 && transfer_##member2() { return ::transfer(MEMBER2); } \
inline CONST_TYPE1 && transfer_element1() const { return (CONST_TYPE1 &&) ::transfer(MEMBER1); } \
inline CONST_TYPE2 && transfer_element2() const { return (CONST_TYPE2 &&) ::transfer(MEMBER2); } \
inline CONST_TYPE1 && transfer_##member1() const { return (CONST_TYPE1 &&) ::transfer(MEMBER1); } \
inline CONST_TYPE2 && transfer_##member2() const { return (CONST_TYPE2 &&) ::transfer(MEMBER2); } \
inline T1 & key() { return MEMBER1; } \
inline T2 & value() { return MEMBER2; } \
inline CONST_TYPE1 & key() const { return (CONST_TYPE1 &) MEMBER1; } \
inline CONST_TYPE2 & value() const { return (CONST_TYPE2 &) MEMBER2; } \
inline T1 && transfer_key() { return ::transfer(MEMBER1); } \
inline T2 && transfer_value() { return ::transfer(MEMBER2); } \
inline CONST_TYPE1 && transfer_key() const { return (CONST_TYPE1 &&) ::transfer(MEMBER1); } \
inline CONST_TYPE2 && transfer_value() const { return (CONST_TYPE2 &&) ::transfer(MEMBER2); } \
\
\
PAIR() {} \
PAIR(ARG_TYPE1 t1) : MEMBER1(t1) {} \
PAIR(ARG_TYPE1 t1, ARG_TYPE2 t2) : MEMBER1(t1), MEMBER2(t2) {}   \
\
\
}

//#define MAKE_PAIR(PAIR, T1, T2, MEMBER1, MEMBER2) \
//_MAKE_PAIR(PAIR, T1, T2, MEMBER1, MEMBER2) \
//PAIR_TUPLE(PAIR, T1, T2, MEMBER1, MEMBER2)



template < typename T1, typename T2 >
MAKE_PAIR(pair, T1, T2, m_element1, m_element2);







template < typename PAIR >
class make_pair :
   public PAIR
{
public:


   using RAW_NODE = PAIR;


   using TYPE1 = typename PAIR::TYPE1;
   using TYPE2 = typename PAIR::TYPE2;
   using ARG_TYPE1 = typename PAIR::ARG_TYPE1;
   using ARG_TYPE2 = typename PAIR::ARG_TYPE2;


   using ELEMENT1 = TYPE1;
   using ELEMENT2 = TYPE2;


   using ARG_ELEMENT1 = ARG_TYPE1;
   using ARG_ELEMENT2 = ARG_TYPE2;


   using KEY = TYPE1;
   using PAYLOAD = TYPE2;


   using ARG_KEY = ARG_TYPE1;
   using ARG_PAYLOAD = ARG_TYPE2;


   inline auto & key() { return this->element1(); }
   inline auto & payload() { return this->element2(); }
   inline auto & topic() { return *this; }


   inline auto & key() const { return this->element1(); }
   inline auto & payload() const { return this->element2(); }
   inline auto & topic() const { return *this; }


   inline auto transfer_key() { return ::transfer(this->transfer_element1()); }
   inline auto transfer_payload() { return ::transfer(this->transfer_element2()); }
   inline auto transfer_topic() { return ::transfer(*this); }

   inline auto transfer() { return ::transfer(*this); }

   make_pair() {}
   make_pair(ARG_TYPE1 t1) : PAIR(t1) {}
   make_pair(ARG_TYPE1 t1, ARG_TYPE2 t2) : PAIR(t1, t2) {}


   void defer_set_payload(ARG_PAYLOAD payload)
   {

      this->element2() = payload;

   }

};


#if defined(__ANDROID__)

#define ALIENATED_ANDROID_ANARCHY class

#else

#define ALIENATED_ANDROID_ANARCHY struct

#endif


template < typename A, typename B > pair(A, B) -> pair< A, B >;

template < typename A, typename B > make_pair(A, B) -> make_pair < pair< A, B > >;


//#include <utility>

//#include <tuple>


