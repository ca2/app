//
// Created by camilo on 23/12/2022 01:30 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/include/_forward_declaration.h"

#include "acme/platform/platform.h"


#if REFERENCING_DEBUGGING
#include "acme/platform/reference_item.h"
#include "acme/platform/reference_item_array.h"
CLASS_DECL_ACME::critical_section * refdbg_cs();
#endif


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
        m_psubparticle(nullptr)
{

}


template < class T >
inline pointer < T > ::pointer(nullptr_t):
        m_p(nullptr),
        m_psubparticle(nullptr)
{

}


template < class T >
template < typename T2 >
inline pointer < T > ::pointer(place_t, T2 * p)
{

#if REFERENCING_DEBUGGING

   critical_section_lock criticalsectionlock(refdbg_cs());

#endif

   if(::is_set(p))
   {

      auto pNew = dynamic_cast < T * > (p);

      if(::is_null(pNew))
      {

         ::release(p);

         m_p = nullptr;

         m_psubparticle = nullptr;

         throw_resource_exception("OBJECT * p is not of type T (pointer < T >).");

      }
      else
      {

         m_p = pNew;

         m_psubparticle = m_p;

#if REFERENCING_DEBUGGING

         if (m_psubparticle->is_referencing_debugging_enabled())
         {

            if(m_psubparticle->m_prefererTransfer2)
            {

               m_preferer = m_psubparticle->m_prefererTransfer2;

               m_psubparticle->m_prefererTransfer2 = nullptr;

            }
            else
            {

               auto preferenceitem = m_psubparticle->m_preferenceitema->m_itema.last();

               m_preferer = preferenceitem->m_preferer;

            }

         }

#endif

      }

   }
   else
   {

      m_p = nullptr;

      m_psubparticle = nullptr;

   }

}


template < class T >
template < typename ...Args >
pointer < T >::pointer(allocate_t, Args &&... args)
{

   auto p = ___new T (::std::forward<Args>(args)...);

//#if REFERENCING_DEBUGGING
//
//   task_on_after_new_particle(p);
//
//#endif

   m_p = dynamic_cast <T *> (p);

   m_psubparticle = m_p;

   if (::is_null(m_p))
   {

      ::release(p);

      m_p = nullptr;

      m_psubparticle = nullptr;

      throw_resource_exception("OBJECT * p is not of type T (pointer < T >).");

   }

}


template < class T >
inline pointer < T > ::pointer(const pointer & t)
{

#if REFERENCING_DEBUGGING

   critical_section_lock criticalsectionlock(refdbg_cs());

#endif

   auto pNew = t.m_psubparticle;

   if (::is_null(pNew))
   {

      m_p = nullptr;

      m_psubparticle = nullptr;
#if REFERENCING_DEBUGGING

      m_preferer = nullptr;
#endif
   }
   else
   {

#if REFERENCING_DEBUGGING

      ::reference_referer * prefererNew = nullptr;

      if(pNew->is_referencing_debugging_enabled())
      {

         //::allocator::defer_push_referer(pNew, { pNew, this, __FUNCTION_FILE_LINE__  });
         ::allocator::defer_push_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

      }

#endif

      pNew->increment_reference_count();

      m_psubparticle = pNew;

      m_p = t.m_p;

#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;

#endif

   }

}


template < class T >
inline pointer < T > ::pointer(pointer && t) :
m_p(t.m_p),
m_psubparticle(t.m_psubparticle),
m_estatus(t.m_estatus)
#if REFERENCING_DEBUGGING

,m_preferer(t.m_preferer)
#endif
{

t.m_p = nullptr;

t.m_psubparticle = nullptr;
#if REFERENCING_DEBUGGING

t.m_preferer = nullptr;
#endif
}



//template < class T >
//template < typename T2 >
//inline pointer < T > ::pointer(const T2 * p) :
//   m_p((T *) p),
//   m_psubparticle(m_p)
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


//template < class T >
//inline T * pointer < T > ::operator ->()
//{
//
//   return is_null() ? nullptr : m_p;
//
//}
//
//
//template < class T >
//inline T * pointer < T > ::operator ->() const
//{
//
//   return is_null() ? nullptr : m_p;
//
//}


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
//   return is_null() ? nullptr : m_p;
//
//}
//
//
//template < class T >
//inline pointer < T > ::operator T * const () const
//{
//
//   return is_null() ? nullptr : m_p;
//
//}
//
//
//template < class T >
//inline T * pointer < T > ::get()
//{
//
//   return is_null() ? nullptr : m_p;
//
//}
//
//
//template < class T >
//inline const T * pointer < T > ::get() const
//{
//
//   return is_null() ? nullptr : m_p;
//
//}


template < class T >
inline bool pointer < T > ::is_set() const
{

   return !!m_p && !!m_psubparticle;

}


template < class T >
inline bool pointer < T > ::is_null() const
{

   return !this->is_set();

}




template < class T >
inline bool pointer < T > ::ok() const
{

   return ::is_set(m_p) && ::is_set(m_psubparticle) && m_psubparticle->_is_ok();

}


template < class T >
inline bool pointer < T > ::nok() const
{

   return !this->ok();

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



//template < class T >
//inline pointer < T >& pointer < T > ::reset(T * p)
//{
//
//   if (::is_null(p))
//   {
//
//      release();
//
//   }
//   else if(m_p != p)
//   {
//
//      auto pparticleOld = m_psubparticle;
//
//      p->increment_reference_count();
//
//      m_p = p;
//
//      m_psubparticle = p;
//
//      if (::is_set(pparticleOld))
//      {
//
//         ::release(pparticleOld);
//
//      }
//
//   }
//
//   return *this;
//
//}


template < class T >
template < typename T2 >
inline pointer < T > & pointer < T > ::reset (T2 * p)
{

   if (::is_null(p))
   {

      release();

   }
   else
   {

      auto pNew = dynamic_cast < T * >((non_const < T2 > *) p);

      if (m_p == pNew)
      {

#if REFERENCING_DEBUGGING

         ::allocator::defer_erase_referer(pNew);

#endif

      }
      else
      {

         ::subparticle * pOld = nullptr;

#if REFERENCING_DEBUGGING

         ::reference_referer * prefererOld = nullptr;

#endif

         {

#if REFERENCING_DEBUGGING

            critical_section_lock criticalsectionlock(refdbg_cs());

            prefererOld = m_preferer;

#endif

            pOld = m_p;

            if (::is_set(pNew))
            {

#if REFERENCING_DEBUGGING

               ::reference_referer * prefererNew = nullptr;

               if (pNew->is_referencing_debugging_enabled())
               {

                  //prefererNew = ::allocator::defer_push_referer(pNew, { pNew, this, __FUNCTION_FILE_LINE__  });

                  prefererNew = ::allocator::defer_push_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

               }
               else
               {

                  ::allocator::defer_erase_referer(pNew);

               }

#endif

               pNew->increment_reference_count();

               m_p = pNew;

               m_psubparticle = pNew;

#if REFERENCING_DEBUGGING

               m_preferer = prefererNew;

#endif

            }
            else
            {

               m_p = nullptr;

               m_psubparticle = nullptr;

#if REFERENCING_DEBUGGING

               m_preferer = nullptr;

#endif

            }

         }

         if (::is_set(pOld))
         {

#if REFERENCING_DEBUGGING

            if (pOld->is_referencing_debugging_enabled())
            {

               ::allocator::add_releaser(prefererOld);

            }

#endif

            ::release(pOld);

         }

      }

   }

   return *this;

}


template < class T >
template < typename T2 >
inline pointer < T > & pointer < T > ::transfer(T2 * p)
{

   if (::is_null(p))
   {

      release();

   }
   else
   {

      auto pNew = dynamic_cast <T *>((non_const < T2 > *) p);

      ::subparticle * pOld = nullptr;

#if REFERENCING_DEBUGGING

      ::reference_referer * prefererOld = nullptr;

#endif

      if (m_p != pNew)
      {

         {

#if REFERENCING_DEBUGGING

            critical_section_lock criticalsectionlock(refdbg_cs());

#endif

            pOld = m_p;

#if REFERENCING_DEBUGGING

            prefererOld = m_preferer;

#endif

            if (::is_set(pNew))
            {

#if REFERENCING_DEBUGGING

               ::reference_referer * prefererNew = nullptr;

               if (pNew->is_referencing_debugging_enabled())
               {

                  if(pNew->m_prefererTransfer)
                  {

                     ::allocator::_push_referer(pNew->m_prefererTransfer);

                  }

                  prefererNew = ::allocator::defer_push_referer(pNew, { pNew, this, __FUNCTION_FILE_LINE__  });

               }

#endif

               //pNew->increment_reference_count();

               m_p = pNew;

               m_psubparticle = pNew;

#if REFERENCING_DEBUGGING

               m_preferer = prefererNew;

#endif

            }
            else
            {

               m_p = nullptr;

               m_psubparticle = nullptr;

#if REFERENCING_DEBUGGING

               m_preferer = nullptr;

#endif

            }

         }

         if (::is_set(pOld))
         {

#if REFERENCING_DEBUGGING

            if (pOld->is_referencing_debugging_enabled())
            {

               ::allocator::add_releaser(prefererOld);

            }

#endif

            ::release(pOld);

         }

      }

   }

   return *this;

}


template < class T >
inline pointer < T > & pointer < T > ::operator = (const pointer & t)
{

   if (m_p != t.m_p)
   {

      ::subparticle * pOld = nullptr;

#if REFERENCING_DEBUGGING

      ::reference_referer * prefererOld = nullptr;

#endif

      {

#if REFERENCING_DEBUGGING

         critical_section_lock criticalsectionlock(refdbg_cs());

         prefererOld = m_preferer;

#endif

         pOld = m_psubparticle;

         auto pNew = t.m_psubparticle;

         if (::is_null(pNew))
         {

            m_p = nullptr;

            m_psubparticle = nullptr;

#if REFERENCING_DEBUGGING

            m_preferer = nullptr;

#endif

         }
         else
         {

#if REFERENCING_DEBUGGING

            ::reference_referer * prefererNew = nullptr;

            if (pNew->is_referencing_debugging_enabled())
            {

               //prefererNew = ::allocator::defer_push_referer(pNew, { pNew, this, __FUNCTION_FILE_LINE__  });

               prefererNew = ::allocator::defer_push_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

            }

#endif

            pNew->increment_reference_count();

            m_p = t.m_p;

            m_psubparticle = pNew;

#if REFERENCING_DEBUGGING

            m_preferer = prefererNew;

#endif

         }

      }

      if (::is_set(pOld))
      {

#if REFERENCING_DEBUGGING

         if (pOld->is_referencing_debugging_enabled())
         {

            ::allocator::add_releaser(prefererOld);

         }

#endif

         ::release(pOld);

      }

   }

   return *this;

}


template < class T >
inline pointer < T > & pointer < T > ::operator = (pointer && t)
{

   if(m_p != t.m_p)
   {

      ::subparticle * pOld = nullptr;

#if REFERENCING_DEBUGGING

      ::reference_referer * prefererOld = nullptr;

#endif

      {

#if REFERENCING_DEBUGGING

         critical_section_lock criticalsectionlock(refdbg_cs());

         prefererOld = m_preferer;

#endif

         pOld = m_psubparticle;

         m_p               = t.m_p;

         m_psubparticle    = t.m_psubparticle;

#if REFERENCING_DEBUGGING

         m_preferer        = t.m_preferer;

#endif

         t.m_p             = nullptr;

         t.m_psubparticle  = nullptr;

#if REFERENCING_DEBUGGING

         t.m_preferer      = nullptr;

#endif

      }

      if (::is_set(pOld))
      {

#if REFERENCING_DEBUGGING

         if (pOld->is_referencing_debugging_enabled())
         {

            ::allocator::add_releaser(prefererOld);

         }

#endif

         ::release(pOld);

      }

   }

   return *this;

}


//template < class T >
//inline T * pointer < T > ::detach()
//{
//
//   auto p = m_p;
//
//   m_p = nullptr;
//
//   m_psubparticle = nullptr;
//
//   m_preferer = nullptr;
//
//   return p;
//
//}
//
//
//template < class T >
//inline ::subparticle * pointer < T > ::detach_particle()
//{
//
//   auto p = m_psubparticle;
//
//   m_p = nullptr;
//
//   m_psubparticle = nullptr;
//
//   m_preferer = nullptr;
//
//   return p;
//
//}


// cut and paste with very good capabilities of RealVNC for MacOS in OVH.fr/eu/pt cloud from Windows client.
// slashes with ABNT 2 keyboard and even c cedilha working with RealVNC
template < class T >
inline long long pointer <T>::release()
{

   ::subparticle * pparticle = nullptr;

   ::collection::count c = -1;

   {

#if REFERENCING_DEBUGGING

      critical_section_lock criticalsectionlock(refdbg_cs());

#endif

      //ASSERT(referer == m_referer);

      //return ::release(m_psubparticle);

#if REFERENCING_DEBUGGING

      ::collection::index iSerial = -1;

#endif

      {

         pparticle = m_psubparticle;

#if REFERENCING_DEBUGGING

         auto preferer = m_preferer;

#endif

         if (::is_null(m_p))
         {

            return -1;

         }

         m_p = nullptr;

         m_psubparticle = nullptr;

#if REFERENCING_DEBUGGING

         m_preferer = nullptr;

         ::allocator::add_releaser(preferer);

         if (::is_set(preferer))
         {

            iSerial = preferer->m_iSerial;

         }
#endif
         try
         {

            c = pparticle->decrement_reference_count();

         }
         catch (...)
         {

            informationf("exception release pparticle->release() \n");

         }
#if REFERENCING_DEBUGGING

         if (::allocator::get_releaser() == preferer && preferer)
         {

            ::output_debug_string("releaser stacked but not consumed");

         }
#endif
      }

   }

   if (c == 0)
   {

      try
      {

         pparticle->delete_this();

      }
      catch (...)
      {

      }

   }
   //if (preferer)
   //{

   //   ::output_debug_string("releaser stacked");

   ////}

   //auto i = ::release(m_psubparticle);

   //if (::allocator::get_releaser() == preferer && preferer)
   //{

   //   ::output_debug_string("releaser stacked but not consumed");

   //}

   return c;

}


//template < class T >
//inline long long pointer <T>::global_release()
//{
//
//   //ASSERT(referer == m_referer);
//
//   auto i = ::global_release(m_psubparticle);
//
//   if (!m_psubparticle)
//   {
//
//      m_p = nullptr;
//
//      m_preferer = nullptr;
//
//   }
//
//   return i;
//
//}


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
inline bool operator ==(const ::pointer<T>& t1, const ::pointer<T> & t2)
{
   return t1.m_p == t2.m_p;
}


template < class T1, class T2 >
inline bool operator ==(const ::pointer<T1>& t1, const ::pointer<T2> & t2)
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
pointer < TYPE > clone(TYPE * p)
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

   m_psubparticle = (::subparticle *)(::iptr)lparam.m_lparam;
   
   m_p = dynamic_cast <T *>(m_psubparticle);

#if REFERENCING_DEBUGGING

   m_preferer = m_psubparticle->m_prefererTransfer2;

   m_psubparticle->m_prefererTransfer2 = nullptr;

#endif
   
   if(::is_null(m_p) && ::is_set(m_psubparticle))
   {

#if REFERENCING_DEBUGGING

      if (::is_set(m_preferer))
      {

         ::allocator::add_releaser(m_preferer);

         m_preferer = nullptr;

      }

#endif

      ::release(m_psubparticle);

   }

   lparam.m_lparam = 0;

}


template < class c_derived >
inline long long increment_reference_count(c_derived * pca)
{

   if (::is_null(pca))
   {

      return -1;

   }

   return pca->increment_reference_count();

}


template < class c_derived, typename SOURCE >
inline long long increment_reference_count(c_derived * & pca, const SOURCE * psource)
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
inline long long increment_reference_count(c_derived *& pderived, const ::pointer<SOURCE>& psource)
{

   return increment_reference_count(pderived, psource.m_p);

}



template < typename TYPE >
inline long long release(::pointer<TYPE>& pointer)
//inline long long release(::pointer<TYPE>& pointer COMMA_REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DEFINITION)
{

   return release(pointer.m_p);

}


template < typename TYPE >
inline long long __finalize(::pointer<TYPE> pointer)
{

if (!pointer) return -1;

pointer->destroy();

return release(pointer.m_p);

}

//
//template < class REFERENCE >
//inline long long release(::pointer<REFERENCE>& preference)
//{
//
//   return release(preference.m_p);
//
//}


template < class c_derived >
inline long long ref_count(c_derived * pca)
{

   if (pca == nullptr)
   {

      return -1;

   }

   return pca->get_ref_count();

}


//class CLASS_DECL_ACME global_particle :
//   virtual public ::subparticle
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

   auto p = __allocate T();

   //p.set_referer();

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


//template < class T >
//template < typename T2 >
//inline pointer < T > ::pointer(const pointer < T2 > & t) 
//{
//
//   if (::is_null(t.m_p))
//   {
//
//      m_p = nullptr;
//
//      m_psubparticle = nullptr;
//
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//
//      auto pNew = dynamic_cast <T *>(t.m_p);
//
//      if (::is_null(pNew))
//      {
//
//         m_p = nullptr;
//
//         m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//         m_preferer = nullptr;
//#endif
//      }
//      else
//      {
//#if REFERENCING_DEBUGGING
//
//         ::reference_referer * prefererNew = nullptr;
//
//         if (pNew->is_referencing_debugging_enabled())
//         {
//
//            prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });
//
//         }
//#endif
//         pNew->increment_reference_count();
//
//         m_p = pNew;
//
//         m_psubparticle = pNew;
//#if REFERENCING_DEBUGGING
//
//         m_preferer = prefererNew;
//#endif
//
//      }
//
//   }
//
//}
//
//
//template < class T >
//template < typename T2 >
//inline pointer < T > ::pointer(pointer < T2 > && t)
//{
//
//   if (::is_null(t.m_p))
//   {
//
//      m_p = nullptr;
//
//      m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//
//   }
//   else
//   {
//
//      auto pNew = dynamic_cast <T *>(t.m_p);
//
//      if (::is_null(pNew))
//      {
//
//         m_p = nullptr;
//
//         m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//         m_preferer = nullptr;
//#endif
//      }
//      else
//      {
//
//         m_p = pNew;
//
//         m_psubparticle = pNew;
//#if REFERENCING_DEBUGGING
//
//         m_preferer = t.m_preferer;
//#endif
//         t.m_p = nullptr;
//
//         //t.m_preferer = nullptr;
//
//      }
//
//   }
//
//}


template < class T >
template < typename T2 >
inline pointer < T >& pointer < T > ::operator = (const pointer < T2 > & t)
{

   ::subparticle * pOld = nullptr;

#if REFERENCING_DEBUGGING

   ::reference_referer * prefererOld = nullptr;

#endif

   if (::is_null(t.m_p))
   {

      release();

   }
   else
   {

      auto pNew = dynamic_cast <T *>(t.m_p);

      if (pNew == m_p)
      {

         return *this;

      }
      else if (::is_null(pNew))
      {

         release();

      }
      else
      {

#if REFERENCING_DEBUGGING

         critical_section_lock criticalsectionlock(refdbg_cs());

         prefererOld = m_preferer;

#endif

         pOld = m_psubparticle;

#if REFERENCING_DEBUGGING

         ::reference_referer * prefererNew = nullptr;

         if (pNew->is_referencing_debugging_enabled())
         {

            //prefererNew = ::allocator::defer_push_referer(pNew, { pNew, this, __FUNCTION_FILE_LINE__  });
            prefererNew = ::allocator::defer_push_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

         }

#endif

         pNew->increment_reference_count();

         m_p = pNew;

         m_psubparticle = pNew;

#if REFERENCING_DEBUGGING

         m_preferer = prefererNew;

#endif

      }

   }

   if (::is_set(pOld))
   {

#if REFERENCING_DEBUGGING

      if (pOld->is_referencing_debugging_enabled())
      {

         ::allocator::add_releaser(prefererOld);

      }

#endif

      ::release(pOld);

   }

   return *this;

}


template < class T >
template < typename T2 >
inline pointer < T >& pointer < T > ::operator = (pointer < T2 > && t)
{

#if REFERENCING_DEBUGGING

   ::reference_referer * prefererOld = nullptr;

#endif

   ::subparticle * pOld = nullptr;

   if (::is_null(t.m_p))
   {

      release();

   }
   else
   {

      auto pNew = dynamic_cast <T *>(t.m_p);

      if (pNew == m_p)
      {

         return *this;

      }
      else if (::is_null(pNew))
      {

         release();

      }
      else
      {

#if REFERENCING_DEBUGGING

         critical_section_lock criticalsectionlock(refdbg_cs());

         prefererOld = m_preferer;

#endif

         pOld = m_psubparticle;

         m_psubparticle = pNew;

         m_p = pNew;

#if REFERENCING_DEBUGGING

         m_preferer = t.m_preferer;

#endif

         t.m_p = nullptr;

         //t.m_preferer = nullptr;

      }

   }

   if (::is_set(pOld))
   {
      
#if REFERENCING_DEBUGGING

      if (pOld->is_referencing_debugging_enabled())
      {

         ::allocator::add_releaser(prefererOld);

      }

#endif

      ::release(pOld);

   }

   return *this;

}


//template < class T >
//template < typename T2 >
//inline pointer < T > & pointer < T > ::operator = (const pointer < T2 > & t)
//{
//
//   auto pOld = m_psubparticle;
//
//   if (pOld == t.m_psubparticle)
//   {
//
//      return *this;
//
//   }
//#if REFERENCING_DEBUGGING
//
//   auto prefererOld = m_preferer;
//#endif
//   if (::is_null(t.m_p))
//   {
//
//      m_p = nullptr;
//
//      m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//
//      auto pNew = dynamic_cast <T *>(t.m_p);
//
//      if (pNew == m_p)
//      {
//
//         return *this;
//
//      }
//      else if (::is_null(pNew))
//      {
//
//         m_p = nullptr;
//
//         m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//         m_preferer = nullptr;
//#endif
//      }
//      else
//      {
//#if REFERENCING_DEBUGGING
//
//         ::reference_referer * prefererNew = nullptr;
//
//         if (pNew->is_referencing_debugging_enabled())
//         {
//
//            prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });
//
//         }
//
//#endif
//
//         pNew->increment_reference_count();
//
//         m_psubparticle = t.m_psubparticle;
//
//         m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//         m_preferer = prefererNew;
//#endif
//      }
//
//   }
//
//   if (::is_set(pOld))
//   {
//#if REFERENCING_DEBUGGING
//
//      if (pOld->is_referencing_debugging_enabled())
//      {
//
//         ::allocator::add_releaser(prefererOld);
//
//      }
//#endif
//      ::release(pOld);
//
//   }
//
//   return *this;
//
//}


//template < class T >
//template < typename T2 >
//inline pointer < T > & pointer < T > ::operator = (pointer < T2 > && t)
//{
//
//   auto pOld = m_psubparticle;
//
//   if (pOld == t.m_psubparticle)
//   {
//
//      return *this;
//
//   }
//#if REFERENCING_DEBUGGING
//
//   auto prefererOld = m_preferer;
//#endif
//   if (::is_null(t.m_p))
//   {
//
//      m_p = nullptr;
//
//      m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//
//      auto pNew = dynamic_cast <T *>(t.m_p);
//
//      if (pNew == m_p)
//      {
//
//         return *this;
//
//      }
//      else if (::is_null(pNew))
//      {
//
//         m_p = nullptr;
//
//         m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//         m_preferer = nullptr;
//#endif
//      }
//      else
//      {
//
//         m_psubparticle = t.m_psubparticle;
//
//         m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//         if (!pNew->is_referencing_debugging_enabled())
//         {
//
//            if (t.m_preferer)
//            {
//
//               throw "error_wrong_state: " __FUNCTION_FILE_LINE__;
//
//            }
//
//         }
//
//         m_preferer = t.m_preferer;
//#endif
//         t.m_p = nullptr;
//
//         t.m_psubparticle = nullptr;
//#if REFERENCING_DEBUGGING
//
//         t.m_preferer = nullptr;
//#endif
//      }
//
//   }
//
//   if (::is_set(pOld))
//   {
//#if REFERENCING_DEBUGGING
//
//      if (pOld->is_referencing_debugging_enabled())
//      {
//
//         ::allocator::add_releaser(prefererOld);
//
//      }
//#endif
//      ::release(pOld);
//
//   }
//
//   return *this;
//
//}


//template < typename T >
//template < typename PARTICLE >
//inline pointer < T >& pointer<T> ::defer_create(PARTICLE* pparticle, ::factory::factory* pfactory)
//{
//
//   if (is_null())
//   {
//
//      operator=(pparticle->template __call__create < T >(pfactory));
//
//   }
//
//   return *this;
//
//}



//template < typename TYPE >
//inline ::pointer<TYPE> __call__create_new(::subparticle* pparticle)
//{
//
//   if (::is_null(pparticle))
//   {
//
//      throw_exception(error_wrong_state);
//
//   }
//
//   auto p = __allocate TYPE();
//
//   if (p)
//   {
//
//      p->initialize(pparticle);
//
//   }
//
//   return ::transfer(p);
//
//}


//template < typename TYPE >
//inline void __construct_new(::subparticle* pparticle, ::pointer<TYPE>& p)
//{
//
//   p = __allocate TYPE();
//
//   if (!p)
//   {
//
//      throw_exception(error_no_memory);
//
//   }
//
//   p->initialize(pparticle);
//
//}


template < typename TARGET, typename SOURCE >
inline void copy(::pointer < TARGET > & pTarget, const ::pointer < SOURCE > & pSource)
{

   pTarget = pSource;

}


//template < typename T >
//template < class T2 >
//inline pointer < T > & pointer < T >::operator = (::pointer<T2>&& t)
//{
//
//   auto pOld = m_p;
//
//   if (::is_set(t.m_p))
//   {
//
//      m_p = dynamic_cast <T *>(t.m_p);
//
//      m_psubparticle = t.m_psubparticle;
//
//      if (::is_set(m_p))
//      {
//
//         t.m_p = nullptr;
//
//         t.m_psubparticle = nullptr;
//
//      }
//
//   }
//   else
//   {
//
//      m_p = nullptr;
//
//      m_psubparticle = nullptr;
//
//   }
//
//   ::release(pOld);
//
//   return *this;
//
//}


//template < typename T >
//inline bool pointer < T > ::ok() const
//{
//
//   return is_set() && m_psubparticle->_is_ok();
//
//}


template < typename T >
inline bool pointer < T > ::defer_destroy()
{

   if (!this->is_set())
   {

      return false;

   }

   m_psubparticle->destroy();

   release();

   return true;

}


/// @brief consumes a releaser (a referer used to decrement reference count)
template < typename T >
inline long long release(T *& p)
{

   if (::is_null(p))
   {

      return -1;

   }

   ::subparticle * pparticle = p;

   try
   {

      p = nullptr;

   }
   catch (...)
   {

      informationf("exception release p = nullptr; \n");

   }

   try
   {

      return pparticle->release();

   }
   catch (...)
   {

      informationf("exception release pparticle->release() \n");

   }

   return -1;

}


/// @brief consumes a releaser (a referer used to decrement reference count)
template < typename T >
inline long long global_release(T *& p)
{

   if (::is_null(p))
   {

      return -1;

   }

   try
   {

      auto i = p->release();

      if (i <= 0)
      {

         p = nullptr;

      }

      return i;

   }
   catch (...)
   {

      informationf("exception release pparticle->release() \n");

   }

   return -1;

}




