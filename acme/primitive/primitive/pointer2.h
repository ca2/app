#pragma once

//CLASS_DECL_ACME void throw_resource_exception(const ::scoped_string & scopedstr);

//template < class T >
//inline pointer < T >::pointer(lparam& lparam)
//{
//
//   m_pparticle = (::particle*)(::iptr)lparam.m_lparam;
//   m_p = dynamic_cast <T*>(m_pparticle);
//   lparam.m_lparam = 0;
//
//}
//
//
//// ::ca::null_class back link to operational system oswindow.h
////
////
////
////
//// operational system nullptr/void itself to a windowing service
////
//// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
//template < class T >
//inline pointer < T > ::pointer() :
//   m_p(nullptr),
//   m_pparticle(nullptr)
//{
//
//}
//
//
//template < class T >
//inline pointer < T > ::pointer(std::nullptr_t):
//   m_p(nullptr),
//   m_pparticle(nullptr)
//{
//
//}
//
//template < class T >
//template < typename T2 >
//inline pointer < T > ::pointer(enum_move_transfer, T2 * p)
//{
//
//   if(::is_set(p))
//   {
//
//      m_p = dynamic_cast < T * > (p);
//
//      m_pparticle = m_p;
//
//      if(::is_null(m_p))
//      {
//
//         ::release(p);
//
//         m_p = nullptr;
//
//         m_pparticle = nullptr;
//
//         throw ::resource_exception("OBJECT * p is not of type T (pointer < T >).");
//
//      }
//
//   }
//   else
//   {
//
//      m_p = nullptr;
//
//      m_pparticle = nullptr;
//
//   }
//
//}
//
//
//template < class T >
//inline pointer < T > ::pointer(const pointer & t) :
//   m_p(t.m_p),
//   m_pparticle(t.m_pparticle)
//{
//
//   if (::is_set(m_p))
//   {
//
//      m_pparticle->increment_reference_count();
//
//   }
//
//}
//
//
//template < class T >
//inline pointer < T > ::pointer(pointer && t) :
//m_p(t.m_p),
//m_pparticle(t.m_pparticle)
//{
//
//   t.m_p = nullptr;
//
//   t.m_pparticle = nullptr;
//
//}
//
//
//
////template < class T >
////template < typename T2 >
////inline pointer < T > ::pointer(const T2 * p) :
////   m_p((T *) p),
////   m_pparticle(m_p)
////{
////
////   ::increment_reference_count(m_p);
////
////}
//
//
//
//template < class T >
//inline pointer < T > ::~pointer()
//{
//
//   release();
//
//}
//
//
//template < class T >
//inline T * pointer < T > ::operator ->()
//{
//
//   return m_p;
//
//}
//
//
//template < class T >
//inline T * pointer < T > ::operator ->() const
//{
//
//   return m_p;
//
//}
//
//
//template < class T >
//inline T & pointer < T > ::operator * ()
//{
//
//   return *m_p;
//
//}
//
//
//template < class T >
//inline T & pointer < T > ::operator * () const
//{
//
//   return *m_p;
//
//}
//
//
//template < class T >
//inline pointer < T > ::operator T * ()
//{
//
//   return m_p;
//
//}
//
//
//template < class T >
//inline pointer < T > ::operator T * const () const
//{
//
//   return m_p;
//
//}
//
//
//template < class T >
//inline T * pointer < T > ::get()
//{
//
//   return m_p;
//
//}
//
//
//template < class T >
//inline const T * pointer < T > ::get() const
//{
//
//   return m_p;
//
//}
//
//
//template < class T >
//inline bool pointer < T > ::is_null() const
//{
//
//   return ::is_null(m_p);
//
//}
//
//
//template < class T >
//inline bool pointer < T > ::is_set() const
//{
//
//   return ::is_set(m_p);
//
//}
//
////
////template < class T >
////inline void __dynamic_cast(T*& ptarget, T* psource)
////{
////
////   ptarget = psource;
////
////}
////
////
////template < class T , typename T2 >
////inline void __dynamic_cast(T * & ptarget, T2 * psource)
////{
////
////   ptarget = dynamic_cast < T2 * >(psource);
////
////}
//
//
//template < class T >
//T* __dynamic_cast(const T* p)
//{
//
//   return (T*)p;
//
//}
//
//template < class T, typename T2 >
//T * __dynamic_cast(const T2 * p)
//{
//   return dynamic_cast <T*>((T2*)p);
//}
//
//
//
//
//
//template < class T >
//template < typename T2 >
//inline pointer < T > & pointer < T > ::reset (T2 * pNew OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEFINITION)
//{
//
//   if (::is_null(pNew))
//   {
//
//      m_pparticle = nullptr;
//
//      ::release(m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//   }
//   else
//   {
//
//      T* p;
//
//      __dynamic_cast(p, pNew);
//
//      if (m_p != p)
//      {
//
//         auto pOld = m_p;
//
//         if (::is_set(p))
//         {
//
//            p->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//            m_p = p;
//
//            m_pparticle = p;
//
//         }
//         else
//         {
//
//            m_p = nullptr;
//
//            m_pparticle = nullptr;
//
//         }
//
//         if (::is_set(pOld))
//         {
//
//            ::release(pOld OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//         }
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
//inline pointer < T > & pointer < T > ::operator = (const pointer  & t)
//{
//   if (this != &t)
//   {
//
//      auto pold = m_pparticle;
//
//      m_p = t.m_p;
//
//      m_pparticle = t.m_pparticle;
//
//      if (::is_set(m_p))
//      {
//
//         m_pparticle->increment_reference_count();
//
//      }
//
//      ::release(pold REF_DBG_COMMA_POINTER);
//
//   }
//   return *this;
//
//}
//
//
//template < class T >
//inline pointer < T > & pointer < T > ::operator = (pointer && t)
//{
//
//   if(&t != this)
//   {
//
//      auto pOld         = m_pparticle;
//
//      m_p           = t.m_p;
//
//      m_pparticle        = t.m_pparticle;
//
//      t.m_p         = nullptr;
//
//      t.m_pparticle      = nullptr;
//
//      ::release(pOld REF_DBG_COMMA_POINTER);
//
//   }
//
//   return *this;
//
//}
//
//
//template < class T >
//inline T * pointer < T > ::detach()
//{
//
//   auto p = m_p;
//
//   m_p = nullptr;
//
//   m_pparticle = nullptr;
//
//   return p;
//
//}
//
//
//// cut and paste with very good capabilities of RealVNC for MacOS in OVH.fr/eu/pt cloud from Windows client.
//// slashes with ABNT 2 keyboard and even c cedilha working with RealVNC
//template < class T >
//inline i64 pointer <T>::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEFINITION)
//{
//
//   m_p = nullptr;
//
//   return ::release(m_pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//template < class T1, class T2 >
//inline bool operator ==(const T1  * t1, const ::pointer<T2>& t2)
//{
//   auto p1 = dynamic_cast < T1 * > (t2.m_p);
//   if(p1 != nullptr)
//   {
//      return p1 == t1;
//   }
//   auto p2 = dynamic_cast < T2 * > ((T1 *) t1);
//   if(p2 != nullptr)
//   {
//      return p2 == t2.m_p;
//   }
//   return false;
//}
//
//
//template < class T1, class T2 >
//inline bool operator ==(const ::pointer<T1>& t1, const T2 * t2)
//{
//   auto p1 = dynamic_cast < T1 * > ((T2 *) t2);
//   if(p1 != nullptr)
//   {
//      return p1 == t1.m_p;
//   }
//   auto p2 = dynamic_cast < T2 * > (t1.m_p);
//   if(p2 != nullptr)
//   {
//      return p2 == t2;
//   }
//   return false;
//}
//
//
//template < class T1, class T2 >
//inline bool operator ==(const ::pointer<T1>& t1, const ::pointer<T2> t2)
//{
//   auto p1 = dynamic_cast < T1 * > (t2.m_p);
//   if(p1 != nullptr)
//   {
//      return p1 == t1.m_p;
//   }
//   auto p2 = dynamic_cast < T2 * > (t1.m_p);
//   if(p2 != nullptr)
//   {
//      return p2 == t2.m_p;
//   }
//   return false;
//}
//
//
//template < class T1, class T2 >
//inline bool operator ==(T1 * t1, const ::pointer<T2>& t2)
//{
//
//   return operator == ((const T1 *) t1, t2);
//
//}
//
//
//template < class T1, class T2 >
//inline bool operator ==(const ::pointer<T1>& t1, T2 * t2)
//{
//
//   return operator == (t1,  (const T2 *) t2);
//
//}
//
//
//template < class T1, class T2 >
//inline bool operator !=(const T1 * t1, const ::pointer<T2>& t2)
//{
//
//   return !operator == (t1, t2);
//
//}
//
//
//template < class T1, class T2 >
//inline bool operator !=(const ::pointer<T1>& t1, const T2 * t2)
//{
//
//   return !operator == (t1, t2);
//
//}
//
//
//template < class T1, class T2 >
//inline bool operator !=(T1 * t1, const ::pointer<T2>& t2)
//{
//
//   return !operator == ((const T1 *) t1, t2);
//
//}
//
//
//template < class T1, class T2 >
//inline bool operator !=(const ::pointer<T1>& t1, T2 * t2)
//{
//   return !operator == (t1, (const T2 *) t2);
//}
//
//
//template < class T1, class T2 >
//inline bool operator !=(const ::pointer<T1>& t1, const ::pointer<T2> t2)
//{
//
//   return !operator == (t1, t2);
//
//}
//
//
//
//
////template < typename TYPE >
//////inline bool is_set(const ::pointer<TYPE>& p)
////{
////
////   return p.is_set();
////
////}
//
//
////template<typename TYPE>
////inline bool is_null(const ::pointer<TYPE>& p)
////{
////
////   return ::is_null(p.m_p);
////
////}
//
//
//template < typename TYPE >
//inline ::pointer<TYPE>clone(const ::pointer<TYPE> & p)
//{
//
//   if (!p)
//   {
//
//      return p;
//
//   }
//
//   auto pelement = p->clone();
//
//   if(__pointer_is_null(pelement))
//   {
//
//      throw ::exception(error_failed);
//
//   }
//
//   auto pNew = dynamic_cast < TYPE * > (pelement);
//
//   if(__pointer_is_null(pNew))
//   {
//
//      throw ::exception(error_wrong_type);
//
//   }
//
//   return ::pointer_transfer(pNew);
//
//}
//
//
//template < typename TYPE >
//inline ::pointer<TYPE>& clone(::pointer<TYPE> & p)
//{
//
//   return p = ::clone((const ::pointer<TYPE>&) p);
//
//}
//
//
//template < typename TYPE >
//inline ::pointer<TYPE>& defer_clone(::pointer<TYPE> & p)
//{
//
//   if (!p || p->reference_count() <= 1)
//   {
//
//      return p;
//
//   }
//
//   return p = ::clone(p);
//
//}
//
//
//template < typename TYPE >
//ptr < TYPE > clone(TYPE * p)
//{
//
//   if(__pointer_is_null(p))
//   {
//
//      throw ::exception(error_null_pointer);
//
//   }
//
//   auto pelement = p->clone();
//
//   auto pNew = dynamic_cast < TYPE * > (pelement);
//
//   if(__pointer_is_null(pNew))
//   {
//
//      throw ::exception(error_wrong_type);
//
//   }
//
//   return ::pointer_transfer(pNew);
//
//}
//
//
//
