#pragma once


#include "acme/primitive/primitive/ptr.h"


CLASS_DECL_ACME ::factory::factory * get_system_factory();


#define TEMPLATE_TYPE typename __TEMPLATE_TYPE__ = nullptr_t
#define TEMPLATE_ARG __TEMPLATE_TYPE__ t = nullptr

template < class c_derived >
inline i64 increment_reference_count(c_derived * pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF);

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

   T *            m_p;
   ::particle *   m_pparticle;
   ::e_status     m_estatus;


   inline pointer();
   inline pointer( std::nullptr_t);
   inline pointer(lparam& lparam);

   pointer(const pointer & t);
   pointer(pointer && t);
   template < typename T2 >
   pointer(const ptr < T2 > & p);
   template < typename T2 >
   pointer(ptr < T2 > && p);
   //inline pointer(const ::trait & trait);


   //inline _pointer < enum_create_new > :
   //   m_p(memory_new T)
   //{

   //}

   template < typename PARTICLE >
   inline pointer(enum_create_new, PARTICLE * pparticle) :
      m_p(memory_new T),
      m_pparticle(m_p)
   {

      m_p->initialize(pparticle);

   }


   template < typename PARTICLE >
   inline pointer(enum_create, PARTICLE * pparticle, ::factory::factory * pfactory = ::get_system_factory()) :
      m_p(nullptr),
      m_pparticle(nullptr)
   {

      create(pparticle, pfactory);

   }


   template < typename T2 >
   inline pointer(enum_pointer_transfer, T2* p);

   template < class T2 >
   inline pointer(const T2 * p)
   {

      if (::is_null(p))
      {

         m_p = nullptr;

         m_pparticle = nullptr;

         return;

      }

      m_p = dynamic_cast <T *> ((T2 *)p);

      if (::is_set(m_p))
      {

         ::increment_reference_count(m_p);

         m_pparticle = m_p;

      }
      else
      {

         m_pparticle = nullptr;

      }

   }


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

            t.m_p = nullptr;

            t.m_pparticle = nullptr;

         }
         else
         {
          
            m_p = nullptr;

            m_pparticle = nullptr;

         }

      }
      else
      {

         m_p = nullptr;

         m_pparticle = nullptr;

      }

   }


   inline ~pointer();

   //template < typename OTHER >
   //inline pointer & operator +=(::pointer<OTHER>& p) { m_p->compose(p); return *this; }

   //template < typename OTHER >
   //inline pointer & operator -=(::pointer<OTHER>& p) { m_p->release(p); return *this; }

   //inline static const char * __type_name(this);

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

   pointer & operator = (const pointer & t);
   pointer & operator = (pointer && t);
   template < typename T2 >
   pointer & operator = (const ptr < T2 > & p);
   template < typename T2 >
   pointer & operator = (ptr < T2 > && p);

   //template < typename VAR >
   //inline pointer & operator = (const payload_type < VAR > & payload);


   //inline pointer& operator = (T * p)
   //{

   //   return reset((T *) p);

   //}


   template < class T2 >
   inline pointer & operator = (T2 * p)
   {

      return reset(p);

   }

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

   template < class T2 >
   inline pointer & operator = (const ::pointer<T2>& t)
   {

      return operator = (t.m_p);

   }


   template < class T2 >
   inline pointer & operator = (::pointer<T2>&& t);


   inline i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   inline i64 global_release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   inline T * detach();


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


   template < typename CONTAINER, typename OBJECT, typename ATTRIBUTE >
   pointer & merge(const CONTAINER & pcontainer, const OBJECT & pparticle, const ATTRIBUTE & attribute)
   {

      auto pModified = __new(TYPE(*m_p));

      pModified->apply(pparticle, attribute);

      return operator =(pcontainer->get_existing(pModified));

   }

   template < typename OBJECT, typename ATTRIBUTE >
   pointer & container_merge(const OBJECT & pparticle, const ATTRIBUTE & attribute)
   {

      return merge(m_p->m_pcontainer, pparticle, attribute);

   }

   template < typename CONTAINER, typename OBJECT >
   pointer & copy(const CONTAINER & pcontainer, const OBJECT & pparticle)
   {

      auto pobjectParent = m_p;

      auto pOld = m_p;

      m_p = memory_new TYPE(*pparticle);

      m_pparticle = m_p;

      pcontainer->erase(pOld);

      pcontainer->add(m_p);

      m_p->initialize(pobjectParent);

      m_p->m_pcontainer = pcontainer;

      return *this;

   }


   template < typename OBJECT >
   pointer & container_copy(const OBJECT & pparticle)
   {

      return copy(m_p->m_pcontainer, pparticle);

   }

   inline pointer& reset(const ::pointer < T > & p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename T2 >
   inline pointer & reset(T2 * ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


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

   template < typename OBJECT >
   inline pointer < T > & defer_create(OBJECT * pparticle, ::factory::factory * pfactory = ::get_system_factory());

   template < typename OBJECT >
   inline pointer < T > & create(OBJECT * pparticle, ::factory::factory * pfactory = ::get_system_factory());

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


template < typename TYPE >
inline ::pointer<TYPE> __create_new(::particle* pparticle);


template < typename TARGET, typename SOURCE >
inline void copy(::pointer < TARGET > & pTarget, const ::pointer < SOURCE > & pSource);






