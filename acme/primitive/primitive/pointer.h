#pragma once


//#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/primitive/ptr.h"
#include "acme/platform/reference_referer.h"


//struct transfer_t {};


//CLASS_DECL_ACME ::factory::factory * get_system_factory();


//#if REFERENCING_DEBUGGING
//
//
//CLASS_DECL_ACME::particle * task_get_top_track();
//CLASS_DECL_ACME void task_on_new_particle(::particle * pparticle);
//CLASS_DECL_ACME void task_on_after_new_particle(::particle * pparticle);
//
//
//#endif


#define TEMPLATE_TYPE typename __TEMPLATE_TYPE__ = nullptr_t
#define TEMPLATE_ARG __TEMPLATE_TYPE__ t = nullptr

template < class c_derived >
inline i64 increment_reference_count(c_derived * pca);

class particle;


// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system nullptr/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
template < typename T >
class pointer
{
public:

   using TYPE = T;

   using RAW_POINTER = TYPE *;

   T *                  m_p;
   ::particle *         m_pparticle;
   ::e_status           m_estatus;
#if REFERENCING_DEBUGGING
   reference_referer *  m_preferer = nullptr;
#endif


   inline pointer();
   inline pointer( std::nullptr_t);
   inline pointer(lparam& lparam);

   template < typename ...Args >
   pointer(allocate_t, Args &&... args);

   pointer(const pointer & t);
   pointer(pointer && t);
   template < typename T2 >
   pointer(const ptr < T2 > & p);
   template < typename T2 >
   pointer(ptr < T2 > && p);
   //inline pointer(const ::trait & trait);


   //inline _pointer < enum_create_new > :
   //   m_p(aaa_memory_new T)
   //{

   //}


   /// consumes a referer
   template < typename PARTICLE >
   inline pointer(enum_create_new, PARTICLE * pparticle) :
      m_p(nullptr),
      m_pparticle(nullptr)
   {

      //m_preferer = ::allocator::get_referer();

      REFDBG_THIS(this);

      pparticle->__construct_new(*this);

   }


   /// consumes a referer
   template < typename PARTICLE >
   inline pointer(enum_create, PARTICLE * pparticle, ::factory::factory * pfactory = nullptr) :
      m_p(nullptr),
      m_pparticle(nullptr)
   {

      //m_preferer = ::allocator::get_referer();

      REFDBG_THIS(this);

      pparticle->__construct(*this, pfactory);

   }


   /// referer is transferred?
   template < typename T2 >
   inline pointer(transfer_t, T2* p);


   /// consumes a referer
   template < class T2 >
   inline pointer(const T2 * p)
   {

      if (::is_null(p))
      {

         m_p = nullptr;

         m_pparticle = nullptr;
#if REFERENCING_DEBUGGING

         m_preferer = nullptr;
#endif
         return;

      }

      auto pNew = dynamic_cast <T *> ((T2 *)p);

      if (::is_set(pNew))
      {
#if REFERENCING_DEBUGGING

         ::reference_referer * prefererNew = nullptr;

         if (pNew->is_referencing_debugging_enabled())
         {

            prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

         }
#endif
         pNew->increment_reference_count();

         m_p = pNew;

         m_pparticle = pNew;
#if REFERENCING_DEBUGGING

         m_preferer = prefererNew;
#endif
      }
      else
      {

         m_pparticle = nullptr;

         m_p = nullptr;
#if REFERENCING_DEBUGGING

         m_preferer = nullptr;
#endif
      }

   }


   /// consumes a referer
   template < class T2 >
   inline pointer(const ::pointer<T2>& p) :
      pointer(p.m_p)
   {

   }


   inline bool operator !() const
   {

      return is_null();

   }


   //inline operator int() const
   //{

   //   return is_set() ? 1 : 0;

   //}

   //template < typename T2 >
   //inline pointer(const T2 * p);

   //inline pointer(const void * p) : pointer(e_pointer_transfer, (T *)p) {}

   //template < class T2 >
   //inline pointer(const ::pointer<T2> t2)
   //{

   //   m_p = dynamic_cast <T*>(t2.m_p);

   //   m_pparticle = m_p;

   //   if (::is_set(m_p))
   //   {

   //      m_p->increment_reference_count();

   //   }

   //}


   template < class T2 >
   inline pointer(::pointer<T2>&& t)
   {

      if (::is_set(t.m_p))
      {

         auto p = dynamic_cast < T * > (t.m_p);

         if (::is_set(p))
         {

            m_p = p;

            m_pparticle = t.m_pparticle;

            m_estatus = t.m_estatus;

#if REFERENCING_DEBUGGING

            m_preferer = t.m_preferer;

#endif

            t.m_p = nullptr;

            t.m_pparticle = nullptr;

#if REFERENCING_DEBUGGING

            t.m_preferer = nullptr;

#endif

         }
         else
         {
          
            m_p = nullptr;

            m_pparticle = nullptr;
#if REFERENCING_DEBUGGING

            m_preferer = nullptr;
#endif
         }

      }
      else
      {

         m_p = nullptr;

         m_pparticle = nullptr;
#if REFERENCING_DEBUGGING

         m_preferer = nullptr;
#endif
      }

   }


   inline ~pointer();

   //template < typename OTHER >
   //inline pointer & operator +=(::pointer<OTHER>& p) { m_p->compose(p); return *this; }

   //template < typename OTHER >
   //inline pointer & operator -=(::pointer<OTHER>& p) { m_p->release(p); return *this; }

   //inline static const char * ::type(this).name();

   inline T * operator ->();
   inline T * operator ->() const;
   inline T & operator *();
   inline T & operator *() const;
   inline operator T * ();
   inline operator T * const () const;
   inline T * get();
   inline const T * get() const;

   inline ::iptr iptr() const { return (::iptr) m_p;}

   inline bool is_null() const;
   inline bool is_set() const;


   template < class T2 >
   inline pointer & operator = (T2 * p)
   {

      return reset(p);

   }


   pointer & operator = (const pointer & t);
   pointer & operator = (pointer && t);


   template < class T2 >
   inline pointer & operator = (const ::pointer<T2> & t);
   template < class T2 >
   inline pointer & operator = (::pointer<T2> && t);


   template < typename T2 >
   pointer & operator = (const ptr < T2 > & p);
   template < typename T2 >
   pointer & operator = (ptr < T2 > && p);



   //template < typename VAR >
   //inline pointer & operator = (const payload_type < VAR > & payload);

   //void set_referer()
   //{

   //   m_referer = referer;

   //}

   //void on_initialize_particle()
   //{

   //   m_pparticle->add_reference_item(m_referer);

   //}


   //void add_reference_item()
   //{

   //   set_referer();

   //   m_pparticle->add_reference_item();

   //}


   //inline pointer& operator = (T * p)
   //{

   //   return reset((T *) p);

   //}


   //template < typename T2 >
   //inline pointer & operator = (const T2 * p)
   //{

   //   return reset((T *) p);

   //}


   //template < class T2 >
   //inline pointer& operator = (const ::primitive::composite < T2 >& composite)
   //{

   //   return operator = (composite.get());

   //}


   //template < class T2 >
   //inline pointer& operator = (const ::primitive::reference < T2 >& reference)
   //{

   //   return operator = (reference.get());

   //}

   inline bool defer_destroy();

   inline i64 release();

   //inline i64 global_release();

   inline ::pointer < T > detach() { return ::transfer(*this); }
   //inline ::particle * detach_particle();


   template < class T2 >
   inline ::pointer<T2>cast()
   {

      return m_p;

   }


   template < class T2 >
   inline ::pointer<T2>cast() const
   {

      return m_p;

   }


   template < class T2 >
   inline bool is() const
   {

      return cast < T2 >().is_set();

   }


   inline bool ok() const;


   inline bool nok() const
   {

      return !ok();

   }


   //template < typename CONTAINER, typename OBJECT, typename ATTRIBUTE >
   //pointer & merge(const CONTAINER & pcontainer, const OBJECT & pparticle, const ATTRIBUTE & attribute)
   //{

   //   auto pModified = __allocate< TYPE >(*m_p);

   //   pModified->apply(pparticle, attribute);

   //   return operator =(pcontainer->get_existing(pModified));

   //}

   //template < typename OBJECT, typename ATTRIBUTE >
   //pointer & container_merge(const OBJECT & pparticle, const ATTRIBUTE & attribute)
   //{

   //   return merge(m_p->m_pcontainer, pparticle, attribute);

   //}

   //template < typename CONTAINER, typename OBJECT >
   //pointer & copy(const CONTAINER & pcontainer, const OBJECT & pparticle)
   //{

   //   auto pobjectParent = m_p;

   //   auto pOld = m_p;

   //   m_p = __new< TYPE >(*pparticle);

   //   m_pparticle = m_p;

   //   pcontainer->erase(pOld);

   //   pcontainer->add(m_p);

   //   m_p->initialize(pobjectParent);

   //   m_p->m_pcontainer = pcontainer;

   //   return *this;

   //}


   //template < typename OBJECT >
   //pointer & container_copy(const OBJECT & pparticle)
   //{

   //   return copy(m_p->m_pcontainer, pparticle);

   //}

   inline pointer& reset(const ::pointer < T > & p);

   template < typename T2 >
   inline pointer & reset(T2 * ptr);


   inline bool operator ==(std::nullptr_t) const { return is_null(); }
   //inline bool operator <=>(std::nullptr_t) const { return m_p <=> nullptr; }


   //inline bool operator !=(std::nullptr_t) const { return is_set(); }

//   template < typename T2 >
//   inline bool operator ==(const T2 * p) const { return m_p == p; }
   //template < typename T2 >
   //inline bool operator <=>(const T2 * p) const { return m_p <=> p; }

   //template < typename T2 >
   //inline bool operator !=(const T2 * p) const { return m_p != p; }

   //inline bool operator ==(const T * p) const { return m_p == p; }
   //inline bool operator <=>(const T * p) const { return m_p <=> p; }
   //inline bool operator !=(const T * p) const { return m_p != p; }

   //template < typename TYPE = T >
   //inline pointer < T > & defer_create_new();

   template < typename TYPE >
   inline pointer < T > & defer_assign_to(TYPE * & p);

   //template < typename TYPE = T >
   //inline pointer < T > & create_new();

   template < typename OBJECT >
   inline pointer < T > & defer_create_new(OBJECT * pparticle);

   template < typename OBJECT >
   inline pointer < T > & create_new(OBJECT * pparticle);

   //template < typename OBJECT >
   //inline pointer < T > & defer_create(OBJECT * pparticle, ::factory::factory * pfactory = nullptr);

   //template < typename OBJECT >
   //inline pointer < T > & create(OBJECT * pparticle, ::factory::factory * pfactory = nullptr);

   template < typename T2 >
   inline pointer < T > & clone(T2 * p);

   inline void run_and_release()
   {

      if (is_null())
      {

         return;

      }

      m_p->run();

      release();

   }
   
   
   inline void operator()() const
   {
      
      ((TYPE *) m_p)->call_run();
      
   }
   

};


// It must not free memory directly allocated to matter pointed by 'p'.
// It is recommended to let final deletion and destruction happens at normal destructor.
// 'destruct' semantics gives a class the ability to use the scoped guard____pointer
// to release outer references (from operating system for example) that would prevent
// the matter to be deleted/destroyed when the matter is released by a conventional pointer.
//
template < class T >
inline void destruct(T * p)
{

   try
   {

      p->destruct();

   }
   catch(...)
   {

   }

}


//// destroy solves this.
//
//template < class T >
//class guard____pointer :
//   public pointer< T >
//{
//public:
//   guard__pointer <  > {}
//   guard____pointer(const lparam& lparam) : pointer<T>(lparam) {}
//
//   guard____pointer(const pointer < T > & t): pointer< T>(t) {}
//   guard____pointer(guard____pointer < T > && t): pointer<T>(::transfer(t)) {}
//   //guard____pointer(const allocer & allocer): pointer<T>(allocer) {}
//   template < class T2 >
//   guard____pointer(T2 * p) : pointer<T>(p) {}
//   guard____pointer(T * p) : pointer<T>(p) {}
//
//   template < class T2 >
//   guard____pointer(const T2 * p): pointer<T>(p) {}
//
//
//   template < class T2 >
//   guard____pointer(const ::pointer<T2>& t): pointer<T>(t) {}
//
//
//   template < class T2 >
//   guard____pointer(guard____pointer < T2 > && t) :
//      pointer<T>(::transfer(t)) {}
//
//
//   ~guard__pointer <  >
//   {
//
//      if(::is_set(this->m_p))
//      {
//
//         ::destruct(this->m_p);
//
//      }
//
//      this->release();
//
//   }
//
//
//};
//

template < typename T >
inline bool is_found(const pointer < T > & p) { return p.is_set(); }


template < typename T >
inline bool not_found(const pointer < T > & p) { return p.is_null(); }


//template < typename T >
//inline pointer < T > __move_transfer(T* p) { return { e_pointertransfer, p }; }
//
//
template < typename TYPE >
inline void swap(::pointer<TYPE>& a, ::pointer<TYPE> & b)
{

   auto t = a.m_p;
   a.m_p = b.m_p;
   b.m_p = t;

}




//template < typename TYPE >
//inline ::pointer<TYPE>clone(const ::pointer<TYPE> & p);


//template < typename TYPE >
//inline ::pointer<TYPE>& clone(::pointer<TYPE> & p);


template < typename TYPE >
inline ::pointer<TYPE>& defer_clone(::pointer<TYPE> & p);


template < typename TYPE >
ptr < TYPE > clone(TYPE * p);


//template < typename TYPE >
//inline ::pointer<TYPE> __call__create_new( ::particle* pparticle);


template < typename TARGET, typename SOURCE >
inline void copy(::pointer < TARGET > & pTarget, const ::pointer < SOURCE > & pSource);



//template < typename T, typename ...Args >
//::pointer < T > __allocate(Args &&... args)
//{
//
//   ::pointer < T > p{ transfer_t{}, ::new T(::std::forward<Args>(args)...) };
//
//   task_on_after_new_particle(p);
//
//   return ::transfer(p);
//
//}


//#else


template < typename T, typename ...Args >
::pointer < T > __call_allocate(Args &&... args);


template < typename TYPE >
ptr < TYPE >::ptr(const ::pointer < TYPE > & p)
{

   auto pNew = p.m_p;

   if (::is_null(pNew))
   {

      m_p = nullptr;
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

         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

      }
#endif
      pNew->increment_reference_count();

      m_p = pNew;
#if REFERENCING_DEBUGGING
      m_preferer = prefererNew;
#endif
   }

}

template < typename TYPE >
ptr < TYPE >::ptr(::pointer < TYPE > && p)
{

   auto pNew = p.m_p;

   if (::is_null(pNew))
   {

      m_p = nullptr;
#if REFERENCING_DEBUGGING
      m_preferer = nullptr;
#endif
   }
   else
   {

      m_p = pNew;
#if REFERENCING_DEBUGGING
      if (!pNew->is_referencing_debugging_enabled())
      {

         if (p.m_preferer)
         {

            throw "error_wrong_state: "  __FUNCTION_FILE_LINE__;

         }

      }

      m_preferer = p.m_preferer;
#endif
      p.m_p = nullptr;
      p.m_pparticle = nullptr;
      p.m_estatus = error_not_initialized;
#if REFERENCING_DEBUGGING
      p.m_preferer = nullptr;
#endif

   }
}

template < typename TYPE >
template < typename T2 >
ptr < TYPE >::ptr(const ::pointer < T2 > & p)
{

   auto pNew = dynamic_cast < TYPE * >((T2*)p.m_p);

   if (::is_null(pNew))
   {

      m_p = nullptr;
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

         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

      }
#endif

      pNew->increment_reference_count();
      
      m_p = pNew;
#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;
#endif

   }

}

template < typename TYPE >
template < typename T2 >
ptr < TYPE >::ptr(::pointer < T2 > && p)
{

   auto pNew = dynamic_cast < TYPE * >(p.m_p);

   if (::is_null(pNew))
   {

      m_p = nullptr;
#if REFERENCING_DEBUGGING

      m_preferer = nullptr;
#endif

   }
   else
   {

      m_p = pNew;
#if REFERENCING_DEBUGGING

      if (!pNew->is_referencing_debugging_enabled())
      {

         if (p.m_preferer)
         {

            throw "error_wrong_state: "  __FUNCTION_FILE_LINE__;

         }

      }

      m_preferer = p.m_preferer;
#endif
      p.m_p = nullptr;

      p.m_pparticle = nullptr;

      p.m_estatus = error_not_initialized;
#if REFERENCING_DEBUGGING

      p.m_preferer = nullptr;
#endif
   }
}







template < typename TYPE >
ptr < TYPE > & ptr < TYPE >::operator =(const ::pointer < TYPE > & p)
{

   auto pNew = p.m_p;

   auto pOld = m_p;

   if (pNew == m_p)
   {

      return *this;

   }
#if REFERENCING_DEBUGGING

   auto prefererOld = m_preferer;
#endif
   if (::is_null(pNew))
   {

      m_p = nullptr;
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

         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

      }
#endif
      pNew->increment_reference_count();

      m_p = pNew;
#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;
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
      pOld->release();

   }

   return *this;


}

template < typename TYPE >
ptr < TYPE > & ptr < TYPE >::operator =(::pointer < TYPE > && p)
{

   auto pNew = p.m_p;

   auto pOld = m_p;

   if (pNew == m_p)
   {

      return *this;

   }
#if REFERENCING_DEBUGGING

   auto prefererOld = m_preferer;
#endif
   if (::is_null(pNew))
   {

      m_p = nullptr;
#if REFERENCING_DEBUGGING

      m_preferer = nullptr;
#endif

   }
   else
   {

      m_p = pNew;
#if REFERENCING_DEBUGGING

      m_preferer = p.m_preferer;
#endif
      p.m_p = nullptr;
      p.m_pparticle = nullptr;
      p.m_estatus = error_not_initialized;
#if REFERENCING_DEBUGGING

      p.m_preferer = nullptr;
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
      pOld->release();

   }

   return *this;

}

template < typename TYPE >
template < typename T2 >
ptr < TYPE > & ptr < TYPE >::operator =(const ::pointer < T2 > & p)
{

   auto pNew = dynamic_cast <TYPE *>((T2 *)p.m_p);

   auto pOld = m_p;

   if (pNew == m_p)
   {

      return *this;

   }
#if REFERENCING_DEBUGGING

   auto prefererOld = m_preferer;
#endif
   if (::is_null(pNew))
   {

      m_p = nullptr;
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

         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });

      }
#endif
      pNew->increment_reference_count();

      m_p = pNew;
#if REFERENCING_DEBUGGING

      m_preferer = prefererNew;
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
      pOld->release();

   }

   return *this;

}

template < typename TYPE >
template < typename T2 >
ptr < TYPE > & ptr < TYPE >::operator =(::pointer < T2 > && p)
{

   auto pNew = dynamic_cast <TYPE *>((T2 *)p.m_p);

   auto pOld = m_p;

   if (pNew == m_p)
   {

      return *this;

   }

#if REFERENCING_DEBUGGING

   auto prefererOld = m_preferer;

#endif
   if (::is_null(pNew))
   {

      m_p = nullptr;
#if REFERENCING_DEBUGGING

      m_preferer = nullptr;
#endif
   }
   else
   {

      m_p = pNew;
#if REFERENCING_DEBUGGING

      m_preferer = p.m_preferer;
#endif
      p.m_p = nullptr;
      p.m_pparticle = nullptr;
      p.m_estatus = error_not_initialized;
#if REFERENCING_DEBUGGING

      p.m_preferer = nullptr;
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
      pOld->release();

   }

   return *this;

}


template < typename TYPE >
inline void defer_finalize(::pointer < TYPE >& p)
{

   try
   {

      if (p)
      {

         p->finalize();

      }

   }
   catch (...)
   {

   }

}


template < typename TYPE >
inline void defer_destroy(::pointer < TYPE >& p)
{

   try
   {

      if (p)
      {

         p->destroy();

      }

   }
   catch (...)
   {

   }

}


template < typename TYPE >
inline void defer_finalize_and_release(::pointer < TYPE > & p)
{

   auto pFinalizeAndRelease = ::transfer(p);

   if (pFinalizeAndRelease)
   {

      ::defer_finalize(pFinalizeAndRelease);

      pFinalizeAndRelease.release();

   }

}


template < typename TYPE >
inline void defer_finalize__destroy_and_release(::pointer < TYPE >& p)
{

   auto pFinalize_DestroyAndRelease = ::transfer(p);

   if (pFinalize_DestroyAndRelease)
   {

      ::defer_finalize(pFinalize_DestroyAndRelease);

      ::defer_destroy(pFinalize_DestroyAndRelease);

      pFinalize_DestroyAndRelease.release();

   }

}


template < typename TYPE >
inline void defer_destroy_and_release(::pointer < TYPE >& p)
{

   auto pDestroyAndRelease = ::transfer(p);

   if (pDestroyAndRelease)
   {

      ::defer_destroy(pDestroyAndRelease);

      pDestroyAndRelease.release();

   }

}



