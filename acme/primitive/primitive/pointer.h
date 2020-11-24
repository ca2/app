#pragma once


struct voidarg : public payload_type < voidarg >{ voidarg(); };

#define TEMPLATE_TYPE typename __TEMPLATE_TYPE__ = nullptr_t
#define TEMPLATE_ARG __TEMPLATE_TYPE__ t = nullptr


class layered;
namespace factory
{

   template < typename TYPE >
   __pointer(TYPE) create();


} // namespace factory


template < class root_derived >
inline i64 add_ref(root_derived * pca OBJ_REF_DBG_COMMA_PARAMS);

template < class root_derived >
inline i64 release(root_derived * & pca OBJ_REF_DBG_COMMA_PARAMS);

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

   using RAW____pointer = TYPE *;

   T * m_p;


   inline ___pointer();
   inline ___pointer(std::nullptr_t);
   inline ___pointer(const lparam & lparam);

   inline ___pointer(const ___pointer & t);
   inline ___pointer(___pointer && t);
   //inline ___pointer(const ::trait & trait);


   inline ___pointer(enum_create_new) :
      m_p(nullptr)
   {

      create_new();

   }


   inline ___pointer(enum_create_new, ::layered * pobject) :
      m_p(nullptr)
   {

      create_new();

      m_p->initialize(pobject);

   }

   template < TEMPLATE_TYPE >
   inline ___pointer(enum_create, TEMPLATE_ARG) :
      m_p(nullptr)
   {

      create();

   }

   template < typename OBJECT >
   inline ___pointer(enum_create, OBJECT * p) :
      m_p(nullptr)
   {

      create();

      m_p->initialize(p);

   }

   inline ___pointer(enum_move_transfer, T * p) : m_p(p) {}

   template < typename OBJECT >
   inline ___pointer(enum_move_transfer, OBJECT * p);

   template < class T2 >
   inline ___pointer(const T2 * p)
   {

      if (::is_null(p))
      {

         m_p = nullptr;

         return;

      }

      m_p = dynamic_cast <T *> ((T2 *)p);

      if (m_p)
      {

         ::add_ref(m_p);

      }

   }

   template < class T2 >
   inline ___pointer(const __composite(T2) & p)
   {

      if (!p)
      {

         m_p = nullptr;

         return;

      }

      m_p = dynamic_cast <T *> ((T2 *)p);

      if (m_p)
      {

         ::add_ref(m_p);

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


   inline ___pointer(const T * p);

   inline ___pointer(const void * p) : ___pointer(e_move_transfer, (T *)p) {}

   template < class T2 >
   inline ___pointer(const ___pointer < T2 > & t2) :
      m_p(nullptr)
   {

      auto p2 = (T2 *) t2.m_p;

      auto p = dynamic_cast <T *>(p2);

      operator = (p);

   }


   template < class T2 >
   inline ___pointer(___pointer < T2 > && t)
   {

      if (::is_set(t.m_p))
      {

         m_p = dynamic_cast <T *>(t.m_p);

         if (::is_set(m_p))
         {

            t.m_p = nullptr;

         }

      }
      else
      {

         m_p = nullptr;

      }

   }


   inline ~___pointer();

   //template < typename OTHER >
   //inline ___pointer & operator +=(__composite(OTHER) & p) { m_p->compose(p); return *this; }

   //template < typename OTHER >
   //inline ___pointer & operator -=(__composite(OTHER) & p) { m_p->release(p); return *this; }

   inline static string type_str();

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

   inline ___pointer & operator = (const ___pointer & t);
   inline ___pointer & operator = (___pointer && t);

   template < typename VAR >
   inline ___pointer & operator = (const payload_type < VAR > & payload);


   template < class T2 >
   inline ___pointer & operator = (const T2 * p)
   {

      return operator = (dynamic_cast <T *> ((T2 *) p));

   }


   inline ___pointer & operator = (const T * p)
   {

      return reset((T *) p);

   }


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

      return operator = (dynamic_cast <T *> (t.m_p));

   }


   template < class T2 >
   inline ___pointer & operator = (___pointer < T2 > && t)
   {

      auto pOld = m_p;

      if (::is_set(t.m_p))
      {

         m_p = dynamic_cast <T *>(t.m_p);

         if (::is_set(m_p))
         {

            t.m_p = nullptr;

         }

      }
      else
      {

         m_p = nullptr;

      }

      ::release(pOld);

      return *this;

   }


   inline i64 release(OBJ_REF_DBG_PARAMS);

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

      pModified->process(pobject, attribute);

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

      ::layered * pobjectParent = m_p->get_context_object();

      auto pOld = m_p;

      m_p = new TYPE(*pobject);

      pcontainer->remove(pOld);

      pcontainer->add(m_p);

      m_p->set_context_object(pobjectParent);

      m_p->m_pcontainer = pcontainer;

      return *this;

   }


   template < typename OBJECT >
   ___pointer & container_copy(const OBJECT & pobject)
   {

      return copy(m_p->m_pcontainer, pobject);

   }


   inline ___pointer & reset(T * ptr OBJ_REF_DBG_COMMA_PARAMS);

   inline bool operator ==(std::nullptr_t) const { return is_null(); }

   inline bool operator !=(std::nullptr_t) const { return is_set(); }

   template < typename T2 >
   inline bool operator ==(const T2 * p) const { return m_p == p; }

   template < typename T2 >
   inline bool operator !=(const T2 * p) const { return m_p != p; }

   inline bool operator ==(const T * p) const { return m_p == p; }
   inline bool operator !=(const T * p) const { return m_p != p; }

   template < typename TYPE = T >
   inline __pointer(T) & defer_create_new();

   template < typename TYPE >
   inline __pointer(T) & defer_assign_to(TYPE * & p);

   template < typename TYPE = T >
   inline __pointer(T) & create_new();

   template < typename TYPE = T, typename OBJECT >
   inline __pointer(T) & defer_create_new(OBJECT * pobjectContext);

   template < typename TYPE = T, typename OBJECT >
   inline __pointer(T) & create_new(OBJECT * pobjectContext);

   template < TEMPLATE_TYPE >
   inline __pointer(T) & defer_create(TEMPLATE_ARG);

   template < TEMPLATE_TYPE >
   inline __pointer(T) & create(TEMPLATE_ARG);

   template < typename TYPE = T, typename OBJECT  >
   inline __pointer(T) & defer_create(OBJECT * pobjectContext);

   template < typename TYPE = T, typename OBJECT >
   inline __pointer(T) & create(OBJECT * pobjectContext);

   template < typename TYPE = T, typename OBJECT >
   inline __pointer(T) & create(OBJECT * pobjectContext, bool bCreate);

   inline __pointer(T) & clone(::matter * pobjectContext);






   inline void run_and_release()
   {

      if (is_null())
      {

         return;

      }

      m_p->run();

      release();

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


// finalize solves this.

template < class T >
class guard____pointer :
   public ::___pointer < T >
{
public:
   guard____pointer() {}
   guard____pointer(const lparam& lparam) : ::___pointer<T>(lparam) {}

   guard____pointer(const ___pointer < T > & t): ::___pointer< T>(t) {}
   guard____pointer(guard____pointer < T > && t): ::___pointer<T>(::move(t)) {}
   guard____pointer(const allocer & allocer): ::___pointer<T>(allocer) {}
   template < class T2 >
   guard____pointer(T2 * p) : ::___pointer <T>(p) {}
   guard____pointer(T * p) : ::___pointer <T>(p) {}

   template < class T2 >
   guard____pointer(const T2 * p): ::___pointer <T>(p) {}

   template < class T2 >
   guard____pointer(const ___pointer < T2 > & t): ::___pointer <T>(t) {}


   template < class T2 >
   guard____pointer(guard____pointer < T2 > && t) :
      ::___pointer <T>(::move(t)) {}

   ~guard____pointer()
   {

      if(::is_set(this->m_p))
      {

         ::destruct(this->m_p);

      }

      this->release();

   }


};

template < typename T >
inline bool __found(const __pointer(T) & p) { return p.is_set(); }

template < typename T >
inline bool __not_found(const __pointer(T) & p) { return p.is_null(); }



//namespace papaya
//{
//
//
//   template < typename T>
//   _____pointer(T) & defer_new(_____pointer(T) & t, ::matter * p)
//   {
//
//      if (t.is_null())
//      {
//
//         T * ptype = new T(p);
//
//         ptype->m_countReference--;
//
//         t = ptype;
//
//
//
//      }
//
//      return t;
//   }
//
//} // namespace papaya





template < typename T >
inline __pointer(T) __move_transfer(T * p) { return ::___pointer < T >(e_move_transfer, p); }



template < typename TYPE >
inline void swap(__pointer(TYPE) & a, __pointer(TYPE) & b)
{

   auto t = a.m_p;
   a.m_p = b.m_p;
   b.m_p = t;

}


template < typename TYPE >
inline __pointer(TYPE) __clone(const __pointer(TYPE) & p)
{

   if (!p)
   {

      return nullptr;

   }

   return p->clone();

}



template < typename TYPE >
inline __pointer(TYPE) & __fork(__pointer(TYPE) & p)
{

   if (!p)
   {

      return p;

   }

   return p = p->clone();

}


template < typename TYPE >
inline __pointer(TYPE) & __defer_fork(__pointer(TYPE) & p)
{

   if (!p || !p->is_shared())
   {

      return p;

   }

   return p = p->clone();

}


template < class TYPE >
inline ::i64 release(__pointer(TYPE)& pointer OBJ_REF_DBG_COMMA_PARAMS);

template < class TYPE >
inline ::i64 __finalize(__pointer(TYPE)& pointer OBJ_REF_DBG_COMMA_PARAMS);

template < class REFERENCE >
inline ::i64 release(__reference(REFERENCE)& preference OBJ_REF_DBG_COMMA_PARAMS);



