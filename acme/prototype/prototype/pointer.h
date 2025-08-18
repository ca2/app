#pragma once


//#include "acme/prototype/prototype/subparticle.h"
#include "acme/prototype/prototype/pointer.h"
#include "acme/platform/reference_referer.h"


struct place_t {};

//struct transfer_t {};


//CLASS_DECL_ACME ::factory::factory * get_system_factory();


//#if REFERENCING_DEBUGGING
//
//
//CLASS_DECL_ACME::subparticle * task_get_top_track();
//CLASS_DECL_ACME void task_on_new_particle(::subparticle * pparticle);
//CLASS_DECL_ACME void task_on_after_new_particle(::subparticle * pparticle);
//
//
//#endif


#define TEMPLATE_TYPE typename __TEMPLATE_TYPE__ = nullptr_t
#define TEMPLATE_ARG __TEMPLATE_TYPE__ t = nullptr

template < class c_derived >
inline long long increment_reference_count(c_derived * pca);

class subparticle;

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

   using POINTER_TYPE_TAG = pointer_type_t;
   using TYPE = T;

   using RAW_POINTER = TYPE *;

   T *                  m_p;
   ::subparticle *      m_psubparticle;
   ::e_status           m_estatus;
#if REFERENCING_DEBUGGING
   reference_referer *  m_preferer = nullptr;
#endif


   inline pointer();
   inline pointer( nullptr_t);
   inline pointer(lparam& lparam);

   template < typename ...Args >
   pointer(allocate_t, Args &&... args);

   pointer(const pointer & t);
   pointer(pointer && t);
   //template < typename T2 >
   //pointer(const ptr < T2 > & p);
   //template < typename T2 >
   //pointer(ptr < T2 > && p);
   //inline pointer(const ::trait & trait);


   //inline _pointer < enum_create_new > :
   //   m_p(aaa_memory_new T)
   //{

   //}


   /// consumes a referer
   template < typename PARTICLE >
   inline pointer(enum_create_new, PARTICLE * pparticle) :
      m_p(nullptr),
      m_psubparticle(nullptr)
   {

      //m_preferer = ::allocator::get_referer();

      REFDBG_THIS(this);

      pparticle->øconstruct_new(*this);

   }


   /// consumes a referer
   template < typename PARTICLE >
   inline pointer(enum_create, PARTICLE * pparticle, ::factory::factory * pfactory = nullptr) :
      m_p(nullptr),
      m_psubparticle(nullptr)
   {

      //m_preferer = ::allocator::get_referer();

      REFDBG_THIS(this);

      pparticle->øconstruct(*this, pfactory);

   }


   /// referer is transferred?
   template < typename T2 >
   inline pointer(transfer_t, T2* p) :pointer(place_t{}, p) {}
   template < typename T2 >
   inline pointer(place_t, T2* p);


   /// consumes a referer
   template < class T2 >
   inline pointer(const T2 * p)
   {

      if (::is_null(p))
      {

         m_p = nullptr;

         m_psubparticle = nullptr;
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

            //prefererNew = ::allocator::push_referer({pNew, this, __FUNCTION_FILE_LINE__ });

            prefererNew = ::allocator::push_referer({ this, __FUNCTION_FILE_LINE__ });

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

         m_psubparticle = nullptr;

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

   //   m_psubparticle = m_p;

   //   if (::is_set(m_p))
   //   {

   //      m_p->increment_reference_count();

   //   }

   //}


   template < class T2 >
   inline pointer(::pointer<T2>&& t)
      requires (!::std::is_same<T2, T>::value)
   {

      if (::is_set(t.m_p))
      {

         auto p = dynamic_cast < T * > (t.m_p);

         if (::is_set(p))
         {

            m_p = p;

            m_psubparticle = t.m_psubparticle;

            m_estatus = t.m_estatus;

#if REFERENCING_DEBUGGING

            m_preferer = t.m_preferer;

#endif

            t.m_p = nullptr;

            t.m_psubparticle = nullptr;

#if REFERENCING_DEBUGGING

            t.m_preferer = nullptr;

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
      else
      {

         m_p = nullptr;

         m_psubparticle = nullptr;
#if REFERENCING_DEBUGGING

         m_preferer = nullptr;
#endif
      }

   }

   template < class T2 >
   inline pointer(::pointer<T2>&& t)
      requires ::std::is_same<T2, T>::value
   {

      if (::is_set(t.m_p))
      {

         auto p = t.m_p;

         if (::is_set(p))
         {

            m_p = p;

            m_psubparticle = t.m_psubparticle;

            m_estatus = t.m_estatus;

#if REFERENCING_DEBUGGING

            m_preferer = t.m_preferer;

#endif

            t.m_p = nullptr;

            t.m_psubparticle = nullptr;

#if REFERENCING_DEBUGGING

            t.m_preferer = nullptr;

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
      else
      {

         m_p = nullptr;

         m_psubparticle = nullptr;
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

   //inline static const_char_pointer ::type(this).name();

   inline T* operator ->() { return m_p; }
   inline T* operator ->() const { return m_p; }
   inline T & operator *() { return *m_p; }
   inline T & operator *() const { return *m_p; }
   inline operator T * () { return m_p; }
   inline operator T * const () const { return m_p; }
   inline T * get() { return m_p; }
   inline const T * get() const { return m_p; }

   inline ::iptr iptr() const { return (::iptr) m_p;}

   inline bool is_set() const;
   inline bool is_null() const;

   inline bool ok() const;
   inline bool nok() const;

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


   //template < typename T2 >
   //pointer & operator = (const ptr < T2 > & p);
   //template < typename T2 >
   //pointer & operator = (ptr < T2 > && p);



   //template < typename VAR >
   //inline pointer & operator = (const payload_type < VAR > & payload);

   //void set_referer()
   //{

   //   m_referer = referer;

   //}

   //void on_initialize_particle()
   //{

   //   m_psubparticle->add_reference_item(m_referer);

   //}


   //void add_reference_item()
   //{

   //   set_referer();

   //   m_psubparticle->add_reference_item();

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

   inline long long release();

   //inline long long global_release();

   inline ::pointer < T > detach() { return ::transfer(*this); }
   //inline ::subparticle * detach_particle();


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
   inline non_const < T2 > * raw_cast()
   {

      return dynamic_cast <non_const < T2 > * > (m_p);

   }


   template < class T2 >
   inline const non_const < T2 > * raw_cast() const
   {

      return (const non_const < T2 > *) dynamic_cast <non_const < T2 > * > ((non_const < T > *)m_p);

   }


   template < class T2 >
   inline bool is() const
   {

      return cast < T2 >().is_set();

   }


   //inline bool ok() const;


   //inline bool nok() const
   //{

   //   return !ok();

   //}


   //template < typename CONTAINER, typename OBJECT, typename ATTRIBUTE >
   //pointer & merge(const CONTAINER & pcontainer, const OBJECT & pparticle, const ATTRIBUTE & attribute)
   //{

   //   auto pModified = øallocate TYPE(*m_p);

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

   //   m_p = ___new TYPE(*pparticle);

   //   m_psubparticle = m_p;

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

   //inline pointer& reset(T * p);

   template < typename T2 >
   inline pointer& reset(const ::pointer < T2 > & p) { return reset(p.m_p); }


   template < typename T2 >
   inline pointer & reset(T2 * ptr);


   template < typename T2 >
   inline pointer & transfer(T2 * ptr);


   inline bool operator ==(nullptr_t) const { return is_null(); }
   //inline bool operator <=>(nullptr_t) const { return m_p <=> nullptr; }


   //inline bool operator !=(nullptr_t) const { return is_set(); }

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
      
      ((TYPE *) m_p)->call();
      
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
inline bool is_found(const ::pointer < T > & p) { return p.is_set(); }


template < typename T >
inline bool not_found(const ::pointer < T > & p) { return p.is_null(); }


//template < typename T >
//inline pointer < T > __move_transfer(T* p) { return { e_pointertransfer, p }; }
//
//
template < typename TYPE >
inline void swap(::pointer<TYPE>& a, ::pointer<TYPE> & b)
{

   auto t = a;
   a = b;
   b = t;

}




//template < typename TYPE >
//inline ::pointer<TYPE>clone(const ::pointer<TYPE> & p);


//template < typename TYPE >
//inline ::pointer<TYPE>& clone(::pointer<TYPE> & p);


template < typename TYPE >
inline ::pointer<TYPE>& defer_clone(::pointer<TYPE> & p);


template < typename TYPE >
pointer < TYPE > clone(TYPE * p);


//template < typename TYPE >
//inline ::pointer<TYPE> __call__create_new( ::subparticle* pparticle);


template < typename TARGET, typename SOURCE >
inline void copy(::pointer < TARGET > & pTarget, const ::pointer < SOURCE > & pSource);



//template < typename T, typename ...Args >
//::pointer < T > øallocate(Args &&... args)
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


//template < typename TYPE >
//ptr < TYPE >::ptr(const ::pointer < TYPE > & p)
//{
//
//   auto pNew = p.m_p;
//
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//#if REFERENCING_DEBUGGING
//      ::reference_referer * prefererNew = nullptr;
//
//      if (pNew->is_referencing_debugging_enabled())
//      {
//
//         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });
//
//      }
//#endif
//      pNew->increment_reference_count();
//
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//      m_preferer = prefererNew;
//#endif
//   }
//
//}
//
//template < typename TYPE >
//ptr < TYPE >::ptr(::pointer < TYPE > && p)
//{
//
//   auto pNew = p.m_p;
//
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//      if (!pNew->is_referencing_debugging_enabled())
//      {
//
//         if (p.m_preferer)
//         {
//
//            throw "error_wrong_state: "  __FUNCTION_FILE_LINE__;
//
//         }
//
//      }
//
//      m_preferer = p.m_preferer;
//#endif
//      p.m_p = nullptr;
//      p.m_psubparticle = nullptr;
//      p.m_estatus = error_not_initialized;
//#if REFERENCING_DEBUGGING
//      p.m_preferer = nullptr;
//#endif
//
//   }
//}
//
//template < typename TYPE >
//template < typename T2 >
//ptr < TYPE >::ptr(const ::pointer < T2 > & p)
//{
//
//   auto pNew = dynamic_cast < TYPE * >((T2*)p.m_p);
//
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//#if REFERENCING_DEBUGGING
//
//      ::reference_referer * prefererNew = nullptr;
//
//      if (pNew->is_referencing_debugging_enabled())
//      {
//
//         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });
//
//      }
//#endif
//
//      pNew->increment_reference_count();
//      
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = prefererNew;
//#endif
//
//   }
//
//}
//
//template < typename TYPE >
//template < typename T2 >
//ptr < TYPE >::ptr(::pointer < T2 > && p)
//{
//
//   auto pNew = dynamic_cast < TYPE * >(p.m_p);
//
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//
//   }
//   else
//   {
//
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//      if (!pNew->is_referencing_debugging_enabled())
//      {
//
//         if (p.m_preferer)
//         {
//
//            throw "error_wrong_state: "  __FUNCTION_FILE_LINE__;
//
//         }
//
//      }
//
//      m_preferer = p.m_preferer;
//#endif
//      p.m_p = nullptr;
//
//      p.m_psubparticle = nullptr;
//
//      p.m_estatus = error_not_initialized;
//#if REFERENCING_DEBUGGING
//
//      p.m_preferer = nullptr;
//#endif
//   }
//}
//
//
//
//
//
//
//
//template < typename TYPE >
//ptr < TYPE > & ptr < TYPE >::operator =(const ::pointer < TYPE > & p)
//{
//
//   auto pNew = p.m_p;
//
//   auto pOld = m_p;
//
//   if (pNew == m_p)
//   {
//
//      return *this;
//
//   }
//#if REFERENCING_DEBUGGING
//
//   auto prefererOld = m_preferer;
//#endif
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//#if REFERENCING_DEBUGGING
//
//      ::reference_referer * prefererNew = nullptr;
//
//      if (pNew->is_referencing_debugging_enabled())
//      {
//
//         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });
//
//      }
//#endif
//      pNew->increment_reference_count();
//
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = prefererNew;
//#endif
//   }
//
//   if (::is_set(pOld))
//   {
//
//
//#if REFERENCING_DEBUGGING
//
//      if (pOld->is_referencing_debugging_enabled())
//      {
//
//         ::allocator::add_releaser(prefererOld);
//
//      }
//
//#endif
//      pOld->release();
//
//   }
//
//   return *this;
//
//
//}
//
//template < typename TYPE >
//ptr < TYPE > & ptr < TYPE >::operator =(::pointer < TYPE > && p)
//{
//
//   auto pNew = p.m_p;
//
//   auto pOld = m_p;
//
//   if (pNew == m_p)
//   {
//
//      return *this;
//
//   }
//#if REFERENCING_DEBUGGING
//
//   auto prefererOld = m_preferer;
//#endif
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//
//   }
//   else
//   {
//
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = p.m_preferer;
//#endif
//      p.m_p = nullptr;
//      p.m_psubparticle = nullptr;
//      p.m_estatus = error_not_initialized;
//#if REFERENCING_DEBUGGING
//
//      p.m_preferer = nullptr;
//#endif
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
//      pOld->release();
//
//   }
//
//   return *this;
//
//}
//
//template < typename TYPE >
//template < typename T2 >
//ptr < TYPE > & ptr < TYPE >::operator =(const ::pointer < T2 > & p)
//{
//
//   auto pNew = dynamic_cast <TYPE *>((T2 *)p.m_p);
//
//   auto pOld = m_p;
//
//   if (pNew == m_p)
//   {
//
//      return *this;
//
//   }
//#if REFERENCING_DEBUGGING
//
//   auto prefererOld = m_preferer;
//#endif
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//#if REFERENCING_DEBUGGING
//
//      ::reference_referer * prefererNew = nullptr;
//
//      if (pNew->is_referencing_debugging_enabled())
//      {
//
//         prefererNew = ::allocator::defer_get_referer(pNew, { this, __FUNCTION_FILE_LINE__ });
//
//      }
//#endif
//      pNew->increment_reference_count();
//
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = prefererNew;
//#endif
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
//      pOld->release();
//
//   }
//
//   return *this;
//
//}
//
//template < typename TYPE >
//template < typename T2 >
//ptr < TYPE > & ptr < TYPE >::operator =(::pointer < T2 > && p)
//{
//
//   auto pNew = dynamic_cast <TYPE *>((T2 *)p.m_p);
//
//   auto pOld = m_p;
//
//   if (pNew == m_p)
//   {
//
//      return *this;
//
//   }
//
//#if REFERENCING_DEBUGGING
//
//   auto prefererOld = m_preferer;
//
//#endif
//   if (::is_null(pNew))
//   {
//
//      m_p = nullptr;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = nullptr;
//#endif
//   }
//   else
//   {
//
//      m_p = pNew;
//#if REFERENCING_DEBUGGING
//
//      m_preferer = p.m_preferer;
//#endif
//      p.m_p = nullptr;
//      p.m_psubparticle = nullptr;
//      p.m_estatus = error_not_initialized;
//#if REFERENCING_DEBUGGING
//
//      p.m_preferer = nullptr;
//#endif
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
//      pOld->release();
//
//   }
//
//   return *this;
//
//}


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


//template < typename TYPE >
//inline void defer_finalize_and_release(::pointer < TYPE > & p)
//{
//
//   auto pFinalizeAndRelease = ::transfer(p);
//
//   if (pFinalizeAndRelease)
//   {
//
//      ::defer_finalize(pFinalizeAndRelease);
//
//      pFinalizeAndRelease.release();
//
//   }
//
//}


//template < typename TYPE >
//inline void defer_finalize__destroy_and_release(::pointer < TYPE >& p)
//{
//
//   auto pFinalize_DestroyAndRelease = ::transfer(p);
//
//   if (pFinalize_DestroyAndRelease)
//   {
//
//      ::defer_finalize(pFinalize_DestroyAndRelease);
//
//      ::defer_destroy(pFinalize_DestroyAndRelease);
//
//      pFinalize_DestroyAndRelease.release();
//
//   }
//
//}


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


template < typename TYPE >
::pointer < TYPE > as_pointer(TYPE * p)
{

return p;

}


// https://stackoverflow.com/questions/71921797/c-concepts-checking-if-derived-from-a-templated-class-with-unknown-template-p
/**
 * @brief Checks if class type Specialisation (the implicit concept
 * argument) is indeed a specialisation of TemplateClass type
 * (e.g. satisfied for TemplateClass=SomeLibrary and
 * Specialisation=SomeLibrary<A, B>). Also accepts classes
 * deriving from specialised TemplateClass.
 *
 * tparam PartialSpecialisation optional partial specialisation
 * of the TemplateClass to be required
 */
template<class specialization, template<typename> class template_class,
   typename ...partial_specialization>
concept specializes = requires (specialization s) {
   [] <typename ...template_args>(
       template_class<partial_specialization..., template_args...>&) {}(s);
};

// https://stackoverflow.com/questions/71921797/c-concepts-checking-if-derived-from-a-templated-class-with-unknown-template-p
template <typename POINTER>
concept pointer_derived = requires(POINTER  p) {
   // IILE, that only binds to A<...> specialisations
   // Including classes derived from them
   [] <typename TYPE>(::pointer<TYPE>&) {}(p);
};

template < typename POINTER >
concept primitive_subparticle_pointer = 
::std::is_base_of_v < ::subparticle, ::erase_pointer < POINTER > > 
|| pointer_derived<POINTER>;


using subparticle_pointer = ::pointer < ::subparticle >;

class time;

template < typename RUNNABLE >
concept primitive_runnable = requires(RUNNABLE r) {
   
   { r() } ->::std::convertible_to<void>;
#if defined(MS_COMPILER)
   { r.get_run_timeout() } ->::std::convertible_to<::time>;
#else
   { r.get_run_timeout() } ->::std::convertible_to<class ::time>;
#endif
};


template < primitive_subparticle SUBPARTICLE >
::pointer < SUBPARTICLE > as_pointer(SUBPARTICLE* p)
{

   return { p };

}


template < primitive_subparticle SUBPARTICLE >
::pointer < SUBPARTICLE > as_pointer(const ::pointer < SUBPARTICLE > & p)
{

   return { p };

}


template < primitive_subparticle SUBPARTICLE >
::pointer < SUBPARTICLE > transfer_as_pointer(SUBPARTICLE* p)
{

   return { ::transfer_t{}, p };

}


class __pointer_site
{
public:


#if REFERENCING_DEBUGGING


   reference_referer * m_preferer;


   __pointer_site(const ::reference_referer & referer, ::reference_referer ** pprefererGet = nullptr)
   {

      //m_preferer = __raw_new ::reference_referer(referer);

      m_preferer = ::allocator::push_referer(referer);

      if (pprefererGet)
      {

         *pprefererGet = m_preferer;

      }

   }


#else


   __pointer_site()
   {


   }


#endif


   template < primitive_subparticle SUBPARTICLE >
   ::pointer < SUBPARTICLE > operator << (SUBPARTICLE* p)
   { 

#if REFERENCING_DEBUGGING

      ::pointer < SUBPARTICLE > pointer({ transfer_t{}, p });

      if (p->is_referencing_debugging_enabled())
      {

         pointer.m_preferer = m_preferer;

      }

      p->on_after_construct(m_preferer);

      return ::transfer(pointer);

#else
      
      return { transfer_t{}, p }; 

#endif
   
   }

   template < primitive_subparticle SUBPARTICLE >
   ::pointer < SUBPARTICLE > operator += (SUBPARTICLE* p)
   {
      
#if REFERENCING_DEBUGGING

      //::allocator::_push_referer(m_preferer);

      return p;

#else

      return p;

#endif   
   }


};


//inline static __pointer_site __g__pointer_site;

//#if !REFERENCING_DEBUGGING

#define __transfer_as_pointer __pointer_site(__refdbg_function_file_line__) <<

#define __preferernew_transfer_as_pointer __pointer_site(__refdbg_function_file_line__preferernew) <<

#define øallocate __transfer_as_pointer new

#define __preferernew_allocate __preferernew_transfer_as_pointer new

#define __as_pointer __pointer_site(__refdbg_function_file_line__) +=

#define __retain __as_pointer

//#endif



class __g_initialize_pointer
{
public:


#if REFERENCING_DEBUGGING


   reference_referer* m_preferer;


#endif

   ::particle * m_p;


   __g_initialize_pointer(::particle* p COMMA_REFERENCING_DEBUGGING_PARAMETERS_DECLARATION) :
      m_p(p) 
   {

   
#if REFERENCING_DEBUGGING

      m_preferer = ::allocator::push_referer(referer);

      //if (pprefererGet)
      //{

      //   *pprefererGet = m_preferer;

      //}

#endif

   
   }


   template < typename TYPE >
   ::pointer < TYPE > operator << (TYPE * p) 
   {

#if REFERENCING_DEBUGGING

      ::pointer < TYPE > pointer({ transfer_t{}, p });

      if (p->is_referencing_debugging_enabled())
      {

         pointer.m_preferer = m_preferer;

      }

      p->on_after_construct(m_preferer);

      //return ::transfer(pointer);

#else

      ::pointer < TYPE > pointer{ transfer_t{}, p };

#endif

      pointer->initialize(m_p);

      return ::transfer(pointer);
   
   }

};

#define __initialize_pointer_with(P) __g_initialize_pointer(P __comma_refdbg_function_file_line__) <<

#define __preferernew_initialize_pointer_with(P) __g_initialize_pointer(P __comma_refdbg_function_file_line__preferernew) <<

#define __initialize_pointer __initialize_pointer_with(this)

#define __preferernew_initialize_pointer __preferernew_initialize_pointer_with(this)

#define __initialize_new_with(P) __initialize_pointer_with(P) new

#define __preferernew_initialize_new_with(P) __preferernew_initialize_pointer_with(P) new

#define __initialize_new __initialize_pointer new

#define __preferernew_initialize_new __preferernew_initialize_pointer new



class __site
{
public:

   CLASS_DECL_ACME ::string operator()(const ::scoped_string & scopedstr);

};


static inline __site __;


// template < typename TYPE >
// class scoped_pointer
// {
// public:
//
//
//    TYPE * m_p;
//
//
//    scoped_pointer(nullptr_t)
//    {
//
//       m_p = nullptr;
//    }
//
//    template < pointer_but_not_integral< TYPE > TOPIC_POINTER >
//    scoped_pointer(TOPIC_POINTER p)
//    {
//
//       m_p = p;
//
//    }
//
//
//    // template < ::std::convertible_to< ::pointer < TYPE > > POINTER >
//    // scoped_pointer(const POINTER & p)
//    // {
//    //
//    //    m_p = p.m_p;
//    //
//    // }
//
//    operator TYPE *() {return m_p;}
//
//    TYPE * operator->() {return m_p;}
//
// };





template < typename TYPE, typename ...Args>
::pointer < TYPE > øcreate_pointer(Args &&... args)
{

   return  { transfer_t{}, new TYPE(::std::forward<Args>(args)...) };

}



