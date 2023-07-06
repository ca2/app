//
// Created by camilo on 23/12/2022 01:30 <3ThomasBorregaardSorensen!!
//
#pragma once


// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system nullptr/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
template < class T >
inline pointer < T > ::pointer() :
        m_p(nullptr),
        m_pparticle(nullptr)
{

}


template < class T >
inline pointer < T > ::pointer(std::nullptr_t):
        m_p(nullptr),
        m_pparticle(nullptr)
{

}

template < class T >
template < typename T2 >
inline pointer < T > ::pointer(enum_pointer_transfer, T2 * p)
{

   if(::is_set(p))
   {

      m_p = dynamic_cast < T * > (p);

      m_pparticle = m_p;

      if(::is_null(m_p))
      {

         ::release(p);

         m_p = nullptr;

         m_pparticle = nullptr;

         throw_resource_exception("OBJECT * p is not of type T (pointer < T >).");

      }

   }
   else
   {

      m_p = nullptr;

      m_pparticle = nullptr;

   }

}


template < class T >
inline pointer < T > ::pointer(const pointer & t) :
        m_p(t.m_p),
        m_pparticle(t.m_pparticle)
{

   if (::is_set(m_p))
   {

      m_pparticle->increment_reference_count();

   }

}


template < class T >
inline pointer < T > ::pointer(pointer && t) :
m_p(t.m_p),
m_pparticle(t.m_pparticle)
{

t.m_p = nullptr;

t.m_pparticle = nullptr;

}



//template < class T >
//template < typename T2 >
//inline pointer < T > ::pointer(const T2 * p) :
//   m_p((T *) p),
//   m_pparticle(m_p)
//{
//
//   ::increment_reference_count(m_p);
//
//}



template < class T >
inline pointer < T > ::~pointer()
{

   release();

}


template < class T >
inline T * pointer < T > ::operator ->()
{

   return m_p;

}


template < class T >
inline T * pointer < T > ::operator ->() const
{

   return m_p;

}


template < class T >
inline T & pointer < T > ::operator * ()
{

   return *m_p;

}


template < class T >
inline T & pointer < T > ::operator * () const
{

   return *m_p;

}


template < class T >
inline pointer < T > ::operator T * ()
{

   return m_p;

}


template < class T >
inline pointer < T > ::operator T * const () const
{

   return m_p;

}


template < class T >
inline T * pointer < T > ::get()
{

   return m_p;

}


template < class T >
inline const T * pointer < T > ::get() const
{

   return m_p;

}


template < class T >
inline bool pointer < T > ::is_null() const
{

   return ::is_null(this) || ::is_null(m_p) || ::is_null(m_pparticle);

}


template < class T >
inline bool pointer < T > ::is_set() const
{

   return !is_null() && m_pparticle->is_set();

}



template < class T >
T* __dynamic_cast(const T* p)
{

   return (T*)p;

}

template < class T, typename T2 >
T * __dynamic_cast(const T2 * p)
{
   return dynamic_cast <T*>((T2*)p);
}



template < class T >
inline pointer < T >& pointer < T > ::reset(const ::pointer < T > & pNew OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (pNew.is_null())
   {

      ::release(m_pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

      m_p = nullptr;

   }
   else if(m_p != pNew.m_p)
   {

      auto pparticleOld = m_pparticle;

      pNew.m_pparticle->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      m_p = pNew.m_p;

      m_pparticle = pNew.m_pparticle;

      if (::is_set(pparticleOld))
      {

         ::release(pparticleOld OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

      }

   }

   return *this;

}



template < class T >
template < typename T2 >
inline pointer < T > & pointer < T > ::reset (T2 * pNew OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_null(pNew))
   {

      m_pparticle = nullptr;

      ::release(m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

   }
   else
   {

      T* p;

      p = dynamic_cast < T * >(pNew);

      if (m_p != p)
      {

         auto pOld = m_p;

         if (::is_set(p))
         {

            p->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

            m_p = p;

            m_pparticle = p;

         }
         else
         {

            m_p = nullptr;

            m_pparticle = nullptr;

         }

         if (::is_set(pOld))
         {

            ::release(pOld OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

         }

      }

   }

   return *this;

}


template < class T >
inline pointer < T > & pointer < T > ::operator = (const pointer  & t)
{
   if (this != &t)
   {

      auto pold = m_pparticle;

      m_p = t.m_p;

      m_pparticle = t.m_pparticle;

      if (::is_set(m_p))
      {

         m_pparticle->increment_reference_count();

      }

      ::release(pold REF_DBG_COMMA_POINTER);

   }
   return *this;

}


template < class T >
inline pointer < T > & pointer < T > ::operator = (pointer && t)
{

   if(&t != this)
   {

      auto pOld         = m_pparticle;

      m_p           = t.m_p;

      m_pparticle        = t.m_pparticle;

      t.m_p         = nullptr;

      t.m_pparticle      = nullptr;

      ::release(pOld REF_DBG_COMMA_POINTER);

   }

   return *this;

}


template < class T >
inline T * pointer < T > ::detach()
{

   auto p = m_p;

   m_p = nullptr;

   m_pparticle = nullptr;

   return p;

}


// cut and paste with very good capabilities of RealVNC for MacOS in OVH.fr/eu/pt cloud from Windows client.
// slashes with ABNT 2 keyboard and even c cedilha working with RealVNC
template < class T >
inline i64 pointer <T>::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   m_p = nullptr;

   return ::release(m_pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}



template < class T >
inline i64 pointer <T>::global_release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto i = ::global_release(m_pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

   if (!m_pparticle)
   {

      m_p = nullptr;

   }

   return i;

}


template < class T1, class T2 >
inline bool operator ==(const T1  * t1, const ::pointer<T2>& t2)
{
   auto p1 = dynamic_cast < T1 * > (t2.m_p);
   if(p1 != nullptr)
   {
      return p1 == t1;
   }
   auto p2 = dynamic_cast < T2 * > ((T1 *) t1);
   if(p2 != nullptr)
   {
      return p2 == t2.m_p;
   }
   return false;
}


template < class T1, class T2 >
inline bool operator ==(const ::pointer<T1>& t1, const T2 * t2)
{
   auto p1 = dynamic_cast < T1 * > ((T2 *) t2);
   if(p1 != nullptr)
   {
      return p1 == t1.m_p;
   }
   auto p2 = dynamic_cast < T2 * > (t1.m_p);
   if(p2 != nullptr)
   {
      return p2 == t2;
   }
   return false;
}


template < typename T >
inline bool operator ==(const ::pointer<T>& t1, const ::pointer<T> t2)
{
   return t1.m_p == t2.m_p;
}


template < class T1, class T2 >
inline bool operator ==(const ::pointer<T1>& t1, const ::pointer<T2> t2)
{
   auto p1 = dynamic_cast < T1 * > (t2.m_p);
   if(p1 != nullptr)
   {
      return p1 == t1.m_p;
   }
   auto p2 = dynamic_cast < T2 * > (t1.m_p);
   if(p2 != nullptr)
   {
      return p2 == t2.m_p;
   }
   return false;
}


template < class T1, class T2 >
inline bool operator ==(T1 * t1, const ::pointer<T2>& t2)
{

   return operator == ((const T1 *) t1, t2);

}


template < class T1, class T2 >
inline bool operator ==(const ::pointer<T1>& t1, T2 * t2)
{

   return operator == (t1,  (const T2 *) t2);

}


template < class T1, class T2 >
inline bool operator !=(const T1 * t1, const ::pointer<T2>& t2)
{

   return !operator == (t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(const ::pointer<T1>& t1, const T2 * t2)
{

   return !operator == (t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(T1 * t1, const ::pointer<T2>& t2)
{

   return !operator == ((const T1 *) t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(const ::pointer<T1>& t1, T2 * t2)
{
   return !operator == (t1, (const T2 *) t2);
}


template < class T1, class T2 >
inline bool operator !=(const ::pointer<T1>& t1, const ::pointer<T2> t2)
{

   return !operator == (t1, t2);

}




//template < typename TYPE >
////inline bool is_set(const ::pointer<TYPE>& p)
//{
//
//   return p.is_set();
//
//}


//template<typename TYPE>
//inline bool is_null(const ::pointer<TYPE>& p)
//{
//
//   return ::is_null(p.m_p);
//
//}


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
//      throw_exception(error_failed);
//
//   }
//
//   auto pNew = dynamic_cast < TYPE * > (pelement);
//
//   if(__pointer_is_null(pNew))
//   {
//
//      throw_exception(error_wrong_type);
//
//   }
//
//   return ::pointer_transfer(pNew);
//
//}


//template < typename TYPE >
//inline ::pointer<TYPE>& clone(::pointer<TYPE> & p)
//{
//
//   return p = ::clone((const ::pointer<TYPE>&) p);
//
//}


template < typename TYPE >
inline ::pointer<TYPE>& defer_clone(::pointer<TYPE> & p)
{

   if (!p || p->reference_count() <= 1)
   {

      return p;

   }

   return p = ::clone(p);

}


template < typename TYPE >
ptr < TYPE > clone(TYPE * p)
{

   if(__pointer_is_null(p))
   {

      throw_exception(error_null_pointer);

   }

   auto pelement = p->clone();

   auto pNew = dynamic_cast < TYPE * > (pelement);

   if(__pointer_is_null(pNew))
   {

      throw_exception(error_wrong_type);

   }

   return ::pointer_transfer(pNew);

}


#include "acme/platform/lparam.h"


template < class T >
inline pointer < T >::pointer(lparam & lparam)
{

   m_pparticle = (::particle *)(::iptr)lparam.m_lparam;
   
   m_p = dynamic_cast <T *>(m_pparticle);
   
   if(::is_null(m_p) && ::is_set(m_pparticle))
   {

      ::release(m_pparticle);

   }

   lparam.m_lparam = 0;

}


template < class c_derived >
inline i64 increment_reference_count(c_derived * pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_null(pca))
   {

      return -1;

   }

   return pca->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


template < class c_derived, typename SOURCE >
inline i64 increment_reference_count(c_derived * & pca, const SOURCE * psource)
{

   c_derived * pderived = dynamic_cast <c_derived *>((SOURCE *)psource);

   if (::is_null(pderived))
   {

      throw_exception(error_wrong_type);

   }

   pca = pderived;

   return increment_reference_count(pca);

}


template < class c_derived, typename SOURCE >
inline i64 increment_reference_count(c_derived *& pderived, const ::pointer<SOURCE>& psource)
{

   return increment_reference_count(pderived, psource.m_p);

}



template < typename TYPE >
inline i64 release(::pointer<TYPE>& pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
inline i64 __finalize(::pointer<TYPE> pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

if (!pointer) return -1;

pointer->destroy();

return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}

//
//template < class REFERENCE >
//inline i64 release(::pointer<REFERENCE>& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   return release(preference.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


template < class c_derived >
inline i64 ref_count(c_derived * pca)
{

   if (pca == nullptr)
   {

      return -1;

   }

   return pca->get_ref_count();

}


//class CLASS_DECL_ACME global_particle :
//   virtual public ::particle
//{
//public:
//
//
//   global_particle * m_pglobalparticleNext;
//
//   global_particle();
//   ~global_particle() override;
//
//
//};


//template < typename TYPE >
//class global_pointer :
//   public ::global_particle,
//   public pointer <TYPE >
//{
//public:
//
//
//   using pointer < TYPE >::pointer;
//
//
//   using pointer < TYPE >::operator = ;
//
//};





template < class T >
template < typename T2 >
inline pointer < T > & pointer < T >::defer_assign_to(T2 * & p)
{

   if (!is_null())
   {

      try
      {

         p = dynamic_cast < T2 * >(m_p);

      }
      catch (...)
      {

      }

   }

   return *this;

}



template < class T >
template < typename OBJECT >
inline pointer < T > & pointer < T >::defer_create_new(OBJECT * pparticle)
{

   if (is_null())
   {

      create_new < T >(pparticle);

   }

   return *this;

}


template < class T >
template < typename OBJECT >
inline pointer < T > & pointer < T >::create_new(OBJECT * pparticle)
{

   auto p = __new(T);

   if (p)
   {

      p->initialize(pparticle);

   }

   return operator=(p);

}


template<typename T>
inline bool is_found(const pointer < T >& p);


template<typename T>
inline bool not_found(const pointer < T >& p);


//template<typename TDST, typename TSRC>
//inline ::pointer<TDST>& clone(::pointer<TDST>dst, const ::pointer<TSRC>rc);


//template<typename T>
//inline pointer < T > clone(const pointer < T >& t);


template<class POINTER_TYPE>
inline auto& __typed(::pointer<POINTER_TYPE>* pp) { return *pp->operator POINTER_TYPE * (); }


template<class POINTER_TYPE>
inline auto& __typed(::pointer<POINTER_TYPE>& p) { return *p; }


template<typename T>
void __destroy_and_release(pointer < T >& p)
{

   if (::is_null(p))
   {

      return;

   }

   try
   {

      p->destroy();

   }
   catch (...)
   {

   }

   p.release();

}


template < class T >
template < typename T2 >
inline pointer < T > ::pointer(const ptr < T2 >& t) :
        m_p(t.m_p),
        m_pparticle(t.m_p)
{

   if (::is_set(m_p))
   {

      m_pparticle->increment_reference_count();

   }

}


template < class T >
template < typename T2 >
inline pointer < T > ::pointer(ptr < T2 >&& t) :
        m_p(t.m_p),
        m_pparticle(t.m_p)
{

   if (::is_set(m_p))
   {

      m_pparticle->increment_reference_count();

   }

}


template < class T >
template < typename T2 >
inline pointer < T >& pointer < T > ::operator = (const ptr < T2 >& t)
{

   auto pold = m_pparticle;

   m_p = dynamic_cast <T*>(t.m_p);

   m_pparticle = t.m_p;

   if (::is_set(m_p))
   {

      m_pparticle->increment_reference_count();

   }

   ::release(pold REF_DBG_COMMA_POINTER);

   return *this;

}


template < class T >
template < typename T2 >
inline pointer < T >& pointer < T > ::operator = (ptr < T2 >&& t)
{

   auto pOld = m_pparticle;

   m_p = t.m_p;

   m_pparticle = t.m_p;

   t.m_p = nullptr;

   ::release(pOld REF_DBG_COMMA_POINTER);

   return *this;

}



template < typename T >
template < typename PARTICLE >
inline pointer < T >& pointer<T> ::defer_create(PARTICLE* pparticle, ::factory::factory* pfactory)
{

   if (is_null())
   {

      operator=(pparticle->template __create < T >());

   }

   return *this;

}



template < typename TYPE >
inline ::pointer<TYPE> __create_new(::particle* pparticle)
{

   if (::is_null(pparticle))
   {

      throw_exception(error_wrong_state);

   }

   auto p = __new(TYPE());

   if (p)
   {

      p->initialize(pparticle);

   }

   return ::transfer(p);

}


template < typename TYPE >
inline void __construct_new(::particle* pparticle, ::pointer<TYPE>& p)
{

   p = __new(TYPE);

   if (!p)
   {

      throw_exception(error_no_memory);

   }

   p->initialize(pparticle);

}


template < typename TARGET, typename SOURCE >
inline void copy(::pointer < TARGET > & pTarget, const ::pointer < SOURCE > & pSource)
{

   pTarget = pSource;

}


template < typename T >
template < class T2 >
inline pointer < T > & pointer < T >::operator = (::pointer<T2>&& t)
{

   auto pOld = m_p;

   if (::is_set(t.m_p))
   {

      m_p = dynamic_cast <T *>(t.m_p);

      m_pparticle = t.m_pparticle;

      if (::is_set(m_p))
      {

         t.m_p = nullptr;

         t.m_pparticle = nullptr;

      }

   }
   else
   {

      m_p = nullptr;

      m_pparticle = nullptr;

   }

   ::release(pOld);

   return *this;

}


template < typename T >
inline bool pointer < T > ::ok() const
{

   return is_set() && m_pparticle->is_ok();

}



