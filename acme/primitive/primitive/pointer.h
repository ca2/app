#pragma once


#define TEMPLATE_TYPE typename __TEMPLATE_TYPE__ = nullptr_t
#define TEMPLATE_ARG __TEMPLATE_TYPE__ t = nullptr



// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system nullptr/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
template < class T >
class ___pointer
{
public:

   using TYPE = T;

   using RAW_POINTER = TYPE *;

   T *            m_p;
   ::element *    m_pelement;
   ::e_status    m_estatus;


   inline ___pointer();
   inline ___pointer(std::nullptr_t);
   inline ___pointer(lparam& lparam);

   ___pointer(const ___pointer & t);
   ___pointer(___pointer && t);
   template < typename T2 >
   ___pointer(const ptr < T2 > & p);
   template < typename T2 >
   ___pointer(ptr < T2 > && p);
   //inline ___pointer(const ::trait & trait);


   //inline ___pointer(enum_create_new) :
   //   m_p(memory_new T)
   //{

   //}

   template < typename OBJECT >
   inline ___pointer(enum_create_new, OBJECT * pobject) :
      m_p(memory_new T),
      m_pelement(m_p)
   {

      m_p->initialize(pobject);

   }


   template < typename OBJECT >
   inline ___pointer(enum_create, OBJECT * pobject) :
      m_p(nullptr),
      m_pelement(nullptr)
   {

      create(pobject);

   }


   template < typename T2 >
   inline ___pointer(enum_move_transfer, T2* p);

   template < class T2 >
   inline ___pointer(const T2 * p)
   {

      if (::is_null(p))
      {

         m_p = nullptr;

         m_pelement = nullptr;

         return;

      }

      m_p = dynamic_cast <T *> ((T2 *)p);

      if (::is_set(m_p))
      {

         ::increment_reference_count(m_p);

         m_pelement = m_p;

      }
      else
      {

         m_pelement = nullptr;

      }

   }


   template < class T2 >
   inline ___pointer(const __composite(T2) & p)
   {

      if (!p)
      {

         m_p = nullptr;

         m_pelement = nullptr;

         return;

      }

      m_p = dynamic_cast <T *> ((T2 *)p);

      if (m_p)
      {

         ::increment_reference_count(m_p);

         m_pelement = m_p;

      }

   }


   inline bool operator !() const
   {

      return is_null();

   }


   inline operator int() const
   {

      return is_set() ? 1 : 0;

   }

   //template < typename T2 >
   //inline ___pointer(const T2 * p);

   //inline ___pointer(const void * p) : ___pointer(e_move_transfer, (T *)p) {}

   template < class T2 >
   inline ___pointer(const ___pointer < T2 >& t2)
   {

      m_p = dynamic_cast <T*>(t2.m_p);

      m_pelement = m_p;

      if (::is_set(m_p))
      {

         m_p->increment_reference_count();

      }

   }


   template < class T2 >
   inline ___pointer(___pointer < T2 > && t)
   {

      if (::is_set(t.m_p))
      {

         __dynamic_cast(m_p, t.m_p);

         m_pelement = t.m_pelement;

         if (::is_set(m_p))
         {

            t.m_p = nullptr;

            t.m_pelement = nullptr;

         }

      }
      else
      {

         m_p = nullptr;

         m_pelement = nullptr;

      }

   }


   inline ~___pointer();

   //template < typename OTHER >
   //inline ___pointer & operator +=(__composite(OTHER) & p) { m_p->compose(p); return *this; }

   //template < typename OTHER >
   //inline ___pointer & operator -=(__composite(OTHER) & p) { m_p->release(p); return *this; }

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

   ___pointer & operator = (const ___pointer & t);
   ___pointer & operator = (___pointer && t);
   template < typename T2 >
   ___pointer & operator = (const ptr < T2 > & p);
   template < typename T2 >
   ___pointer & operator = (ptr < T2 > && p);

   template < typename VAR >
   inline ___pointer & operator = (const payload_type < VAR > & payload);


   //inline ___pointer& operator = (T * p)
   //{

   //   return reset((T *) p);

   //}


   template < class T2 >
   inline ___pointer & operator = (T2 * p)
   {

      return reset(p);

   }

   //template < typename T2 >
   //inline ___pointer & operator = (const T2 * p)
   //{

   //   return reset((T *) p);

   //}


   template < class T2 >
   inline ___pointer& operator = (const ::primitive::composite < T2 >& composite)
   {

      return operator = (composite.get());

   }


   template < class T2 >
   inline ___pointer& operator = (const ::primitive::reference < T2 >& reference)
   {

      return operator = (reference.get());

   }

   template < class T2 >
   inline ___pointer & operator = (const ___pointer < T2 > & t)
   {

      return operator = (t.m_p);

   }


   template < class T2 >
   inline ___pointer & operator = (___pointer < T2 > && t)
   {

      auto pOld = m_p;

      if (::is_set(t.m_p))
      {

         m_p = dynamic_cast <T *>(t.m_p);

         m_pelement = t.m_pelement;

         if (::is_set(m_p))
         {

            t.m_p = nullptr;

            t.m_pelement = nullptr;

         }

      }
      else
      {

         m_p = nullptr;

         m_pelement = nullptr;

      }

      ::release(pOld);

      return *this;

   }


   inline i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   inline T * detach();


   template < class T2 >
   inline __pointer(T2) cast()
   {

      return m_p;

   }


   template < class T2 >
   inline __pointer(T2) cast() const
   {

      return m_p;

   }


   template < class T2 >
   inline bool is() const
   {

      return cast < T2 >().is_set();

   }


   inline bool ok() const
   {

      return ::is_ok(m_p);

   }


   inline bool nok() const
   {

      return ::nok(m_p);

   }


   template < typename CONTAINER, typename OBJECT, typename ATTRIBUTE >
   ___pointer & merge(const CONTAINER & pcontainer, const OBJECT & pobject, const ATTRIBUTE & attribute)
   {

      auto pModified = __new(TYPE(*m_p));

      pModified->apply(pobject, attribute);

      return operator =(pcontainer->get_existing(pModified));

   }

   template < typename OBJECT, typename ATTRIBUTE >
   ___pointer & container_merge(const OBJECT & pobject, const ATTRIBUTE & attribute)
   {

      return merge(m_p->m_pcontainer, pobject, attribute);

   }

   template < typename CONTAINER, typename OBJECT >
   ___pointer & copy(const CONTAINER & pcontainer, const OBJECT & pobject)
   {

      auto pobjectParent = m_p;

      auto pOld = m_p;

      m_p = memory_new TYPE(*pobject);

      m_pelement = m_p;

      pcontainer->erase(pOld);

      pcontainer->add(m_p);

      m_p->initialize(pobjectParent);

      m_p->m_pcontainer = pcontainer;

      return *this;

   }


   template < typename OBJECT >
   ___pointer & container_copy(const OBJECT & pobject)
   {

      return copy(m_p->m_pcontainer, pobject);

   }

   template < typename T2 >
   inline ___pointer & reset(T2 * ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   inline bool operator ==(std::nullptr_t) const { return is_null(); }

   inline bool operator !=(std::nullptr_t) const { return is_set(); }

   template < typename T2 >
   inline bool operator ==(const T2 * p) const { return m_p == p; }

   template < typename T2 >
   inline bool operator !=(const T2 * p) const { return m_p != p; }

   inline bool operator ==(const T * p) const { return m_p == p; }
   inline bool operator !=(const T * p) const { return m_p != p; }

   //template < typename TYPE = T >
   //inline __pointer(T) & defer_create_new();

   template < typename TYPE >
   inline __pointer(T) & defer_assign_to(TYPE * & p);

   //template < typename TYPE = T >
   //inline __pointer(T) & create_new();

   template < typename OBJECT >
   inline __pointer(T) & defer_create_new(OBJECT * pobject);

   template < typename OBJECT >
   inline __pointer(T) & create_new(OBJECT * pobject);

   //template < TEMPLATE_TYPE >
   //inline __pointer(T) & defer_create(TEMPLATE_ARG);

   //template < TEMPLATE_TYPE >
   //inline __pointer(T) & create(TEMPLATE_ARG);

   template < typename OBJECT >
   inline __pointer(T) & defer_create(OBJECT * pobject);

   template < typename OBJECT >
   inline __pointer(T) & create(OBJECT * pobject);

   template < typename OBJECT >
   inline __pointer(T) & create(OBJECT * pobject, bool bCreate);

   template < typename T2 >
   inline __pointer(T) & clone(T2 * p);






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
// the matter to be deleted/destroyed when the matter is released by a conventional ___pointer.
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
//   public ::___pointer < T >
//{
//public:
//   guard____pointer() {}
//   guard____pointer(const lparam& lparam) : ::___pointer<T>(lparam) {}
//
//   guard____pointer(const ___pointer < T > & t): ::___pointer< T>(t) {}
//   guard____pointer(guard____pointer < T > && t): ::___pointer<T>(::move(t)) {}
//   //guard____pointer(const allocer & allocer): ::___pointer<T>(allocer) {}
//   template < class T2 >
//   guard____pointer(T2 * p) : ::___pointer <T>(p) {}
//   guard____pointer(T * p) : ::___pointer <T>(p) {}
//
//   template < class T2 >
//   guard____pointer(const T2 * p): ::___pointer <T>(p) {}
//
//
//   template < class T2 >
//   guard____pointer(const ___pointer < T2 > & t): ::___pointer <T>(t) {}
//
//
//   template < class T2 >
//   guard____pointer(guard____pointer < T2 > && t) :
//      ::___pointer <T>(::move(t)) {}
//
//
//   ~guard____pointer()
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
inline bool __found(const __pointer(T) & p) { return p.is_set(); }


template < typename T >
inline bool __not_found(const __pointer(T) & p) { return p.is_null(); }


template < typename T >
inline __pointer(T) __move_transfer(T* p) { return { e_move_transfer, p }; }


template < typename TYPE >
inline void swap(__pointer(TYPE) & a, __pointer(TYPE) & b)
{

   auto t = a.m_p;
   a.m_p = b.m_p;
   b.m_p = t;

}




template < typename TYPE >
inline __pointer(TYPE) clone(const __pointer(TYPE) & p);


template < typename TYPE >
inline __pointer(TYPE) & clone(__pointer(TYPE) & p);


template < typename TYPE >
inline __pointer(TYPE) & defer_clone(__pointer(TYPE) & p);


template < typename TYPE >
ptr < TYPE > clone(TYPE * p);



