#pragma once


#define TEMPLATE_TYPE typename __TEMPLATE_TYPE__ = nullptr_t
#define TEMPLATE_ARG __TEMPLATE_TYPE__ t = nullptr




class particle;

// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system nullptr/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
template < class T >
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

   template < typename OBJECT >
   inline pointer(enum_create_new, OBJECT * pobject) :
      m_p(memory_new T),
      m_pparticle(m_p)
   {

      m_p->initialize(pobject);

   }


   template < typename OBJECT >
   inline pointer(enum_create, OBJECT * pobject) :
      m_p(nullptr),
      m_pparticle(nullptr)
   {

      create(pobject);

   }


   template < typename T2 >
   inline pointer(enum_move_transfer, T2* p);

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


   inline operator int() const
   {

      return is_set() ? 1 : 0;

   }

   //template < typename T2 >
   //inline pointer(const T2 * p);

   //inline pointer(const void * p) : pointer(e_move_transfer, (T *)p) {}

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

         __dynamic_cast(m_p, t.m_p);

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
   inline pointer & operator = (::pointer<T2>&& t)
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


   inline i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

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


   inline bool ok() const
   {

      return ::is_ok(m_p);

   }


   inline bool nok() const
   {

      return ::nok(m_p);

   }


   template < typename CONTAINER, typename OBJECT, typename ATTRIBUTE >
   pointer & merge(const CONTAINER & pcontainer, const OBJECT & pobject, const ATTRIBUTE & attribute)
   {

      auto pModified = __new(TYPE(*m_p));

      pModified->apply(pobject, attribute);

      return operator =(pcontainer->get_existing(pModified));

   }

   template < typename OBJECT, typename ATTRIBUTE >
   pointer & container_merge(const OBJECT & pobject, const ATTRIBUTE & attribute)
   {

      return merge(m_p->m_pcontainer, pobject, attribute);

   }

   template < typename CONTAINER, typename OBJECT >
   pointer & copy(const CONTAINER & pcontainer, const OBJECT & pobject)
   {

      auto pobjectParent = m_p;

      auto pOld = m_p;

      m_p = memory_new TYPE(*pobject);

      m_pparticle = m_p;

      pcontainer->erase(pOld);

      pcontainer->add(m_p);

      m_p->initialize(pobjectParent);

      m_p->m_pcontainer = pcontainer;

      return *this;

   }


   template < typename OBJECT >
   pointer & container_copy(const OBJECT & pobject)
   {

      return copy(m_p->m_pcontainer, pobject);

   }

   template < typename T2 >
   inline pointer & reset(T2 * ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   inline bool operator ==(std::nullptr_t) const { return is_null(); }

   inline bool operator !=(std::nullptr_t) const { return is_set(); }

   template < typename T2 >
   inline bool operator ==(const T2 * p) const { return m_p == p; }

   template < typename T2 >
   inline bool operator !=(const T2 * p) const { return m_p != p; }

   inline bool operator ==(const T * p) const { return m_p == p; }
   inline bool operator !=(const T * p) const { return m_p != p; }

   //template < typename TYPE = T >
   //inline pointer < T > & defer_create_new();

   template < typename TYPE >
   inline pointer < T > & defer_assign_to(TYPE * & p);

   //template < typename TYPE = T >
   //inline pointer < T > & create_new();

   template < typename OBJECT >
   inline pointer < T > & defer_create_new(OBJECT * pobject);

   template < typename OBJECT >
   inline pointer < T > & create_new(OBJECT * pobject);

   //template < TEMPLATE_TYPE >
   //inline pointer < T > & defer_create(TEMPLATE_ARG);

   //template < TEMPLATE_TYPE >
   //inline pointer < T > & create(TEMPLATE_ARG);

   template < typename OBJECT >
   inline pointer < T > & defer_create(OBJECT * pobject);

   template < typename OBJECT >
   inline pointer < T > & create(OBJECT * pobject);

   template < typename OBJECT >
   inline pointer < T > & create(OBJECT * pobject, bool bCreate);

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
//   guard____pointer(guard____pointer < T > && t): pointer<T>(::move(t)) {}
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
//      pointer<T>(::move(t)) {}
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
inline bool __found(const pointer < T > & p) { return p.is_set(); }


template < typename T >
inline bool __not_found(const pointer < T > & p) { return p.is_null(); }


template < typename T >
inline pointer < T > __move_transfer(T* p) { return { e_move_transfer, p }; }


template < typename TYPE >
inline void swap(::pointer<TYPE>& a, ::pointer<TYPE> & b)
{

   auto t = a.m_p;
   a.m_p = b.m_p;
   b.m_p = t;

}




template < typename TYPE >
inline ::pointer<TYPE>clone(const ::pointer<TYPE> & p);


template < typename TYPE >
inline ::pointer<TYPE>& clone(::pointer<TYPE> & p);


template < typename TYPE >
inline ::pointer<TYPE>& defer_clone(::pointer<TYPE> & p);


template < typename TYPE >
ptr < TYPE > clone(TYPE * p);





template < class T >
inline pointer < T >::pointer(lparam& lparam)
{

   m_pparticle = (::particle*)(::iptr)lparam.m_lparam;
   m_p = dynamic_cast <T*>(m_pparticle);
   lparam.m_lparam = 0;

}


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
inline pointer < T > ::pointer(enum_move_transfer, T2 * p)
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

   return ::is_null(m_p);

}


template < class T >
inline bool pointer < T > ::is_set() const
{

   return ::is_set(m_p);

}

//
//template < class T >
//inline void __dynamic_cast(T*& ptarget, T* psource)
//{
//
//   ptarget = psource;
//
//}
//
//
//template < class T , typename T2 >
//inline void __dynamic_cast(T * & ptarget, T2 * psource)
//{
//
//   ptarget = dynamic_cast < T2 * >(psource);
//
//}


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

      __dynamic_cast(p, pNew);

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


template < typename TYPE >
inline ::pointer<TYPE>clone(const ::pointer<TYPE> & p)
{

   if (!p)
   {

      return p;

   }

   auto pelement = p->clone();

   if(__pointer_is_null(pelement))
   {

      throw_exception(error_failed);

   }

   auto pNew = dynamic_cast < TYPE * > (pelement);

   if(__pointer_is_null(pNew))
   {

      throw_exception(error_wrong_type);

   }

   return ::move_transfer(pNew);

}


template < typename TYPE >
inline ::pointer<TYPE>& clone(::pointer<TYPE> & p)
{

   return p = ::clone((const ::pointer<TYPE>&) p);

}


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

   return ::move_transfer(pNew);

}



