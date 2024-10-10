#pragma once


//#include "aura/_defer.h"


//#if !defined(DEBUG) && !defined(CUBE)
//
//
//#include "aura/inline/_new_impl.h"
//
//
//#endif

//
//namespace prototype
//{
//
//
//   template < typename TYPE >
//   template < typename OBJECT >
//   ::pointer<OBJECT>member < TYPE >::cast() const
//   {
//
//      return ::is_null((TYPE*)m_p) ? nullptr : (TYPE*)m_p;
//
//   }
//
//
//} // namespace prototype
//
//
//template < class T >
//template < typename T2 >
//inline pointer < T > & pointer < T >::defer_create_new()
//{
//
//   if (is_null())
//   {
//
//      create_new < T2 >();
//
//   }
//
//   return *this;
//
//}
//
//
//template < class T >
//template < typename T2 >
//inline pointer < T > & pointer < T >::defer_assign_to(T2 * & p)
//{
//
//   if (!is_null())
//   {
//
//      try
//      {
//
//         p = dynamic_cast < T2 * >(m_p);
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//   return *this;
//
//}
//
//
//template < class T >
//template < typename T2 >
//inline pointer < T > & pointer < T >::create_new()
//{
//
//   auto p = __new T2();
//
//   return operator=(p);
//
//}
//
//
//template < class T >
//template < typename T2, typename OBJECT >
//inline pointer < T > & pointer < T >::defer_create_new(OBJECT * pparticle)
//{
//
//   if (is_null())
//   {
//
//      create_new < T2 >(pparticle);
//
//   }
//
//   return *this;
//
//}
//
//
//template < class T >
//template < typename T2, typename OBJECT >
//inline pointer < T > & pointer < T >::create_new(OBJECT * pparticle)
//{
//
//   auto p = __new T2();
//
//   if (p)
//   {
//
//      p->initialize(pparticle);
//
//   }
//
//   return operator=(p);
//
//}
//
//
//template < typename TYPE1, typename TYPE2 >
//inline void copy(TYPE1* p1, const TYPE2* p2) { ::copy(p1, p2); }
//
//template < typename TYPE1, typename TYPE2 >
//inline void copy(TYPE1& t1, const TYPE2* p2) { ::copy(&t1, p2); }
//
//template < typename TYPE1, typename TYPE2 >
//inline void copy(TYPE1* p1, const TYPE2& t2) { ::copy(p1, &t2); }
//
//template < typename TYPE1, typename TYPE2 >
//inline void copy(TYPE1& p1, const TYPE2& p2) { ::copy(&p1, &p2); }
//
//
//template < typename TYPE >
//inline auto copy(const TYPE& t) { return TYPE(t); }
//
//
//
