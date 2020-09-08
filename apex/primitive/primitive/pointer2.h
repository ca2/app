#pragma once

CLASS_DECL_APEX void throw_resource_exception(const char * psz);

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
   m_p(nullptr)
{

}


template < class T >
inline pointer < T > ::pointer(std::nullptr_t) :
   m_p(nullptr)
{

}

template < class T >
template < typename OBJECT >
inline pointer < T > ::pointer(enum_move_transfer, OBJECT * p)
{

   if(::is_set(p))
   {

      m_p = dynamic_cast < T * > (p);

      if(::is_null(m_p))
      {

         ::release(p);

         throw_resource_exception("OBJECT * p is not of type T (pointer < T >).");

      }

   }
   else
   {

      m_p = nullptr;

   }

}


template < class T >
inline pointer < T > ::pointer(const pointer & t) :
   m_p(nullptr)
{

   operator = (t);

}


template < class T >
inline pointer < T > ::pointer(pointer && t)
{

   m_p      = t.m_p;

   t.m_p    = nullptr;

}


template < class T >
inline pointer < T > ::pointer(const T * p) :
   m_p((T *) p)
{

   ::add_ref(m_p);

}


template < class T >
inline pointer < T > ::pointer(const lparam& lparam)
{

   auto * p = (::context_object *) lparam.m_lparam;

   m_p = dynamic_cast < T * > (p);

   if (::is_null(m_p))
   {

      ::release(p OBJ_REF_DBG_ADD_P_NOTE(nullptr, "pointer::pointer(LPARAM)"));

   }

}


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


template < class T >
inline pointer < T > & pointer < T > ::reset (T * pNew OBJ_REF_DBG_ADD_PARAMS_DEF)
{

   if(m_p != pNew)
   {

      auto pOld = m_p;

      if(::is_set(pNew))
      {

         pNew->add_ref(OBJ_REF_DBG_ARGS);

         m_p = pNew;

      }
      else
      {

         m_p = nullptr;

      }

      ::release(pOld OBJ_REF_DBG_ADD_ARGS);

   }

   return *this;

}


template < class T >
inline pointer < T > & pointer < T > ::operator = (const pointer  & t)
{

   return operator = (t.m_p);

}


template < class T >
inline pointer < T > & pointer < T > ::operator = (pointer && t)
{

   if(&t != this)
   {

      auto pOld = m_p;

      m_p      = t.m_p;

      t.m_p    = nullptr;

      ::release(pOld REF_DBG_ADD_POINTER);

   }

   return *this;

}


template < class T >
inline __pointer(T) pointer < T > ::detach()
{

   auto p = m_p;

   m_p = nullptr;

   return __move_transfer(p);

}


// cut and paste with very good capabilities of RealVNC for MacOS in OVH.fr/eu/pt cloud from Windows client.
// slashes with ABNT 2 keyboard and even c cedilha working with RealVNC
template < class T >
inline i64 pointer <T>::release(OBJ_REF_DBG_PARAMS_DEF)
{

   return ::release(m_p OBJ_REF_DBG_ADD_ARGS);

}


template < class T1, class T2 >
inline bool operator ==(const T1  * t1, const pointer < T2 > & t2)
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
inline bool operator ==(const pointer < T1 > & t1, const T2 * t2)
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
inline bool operator ==(const pointer < T1 > & t1, const pointer < T2 > & t2)
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
inline bool operator ==(T1 * t1, const pointer < T2 > & t2)
{

   return operator == ((const T1 *) t1, t2);

}


template < class T1, class T2 >
inline bool operator ==(const pointer < T1 > & t1, T2 * t2)
{

   return operator == (t1,  (const T2 *) t2);

}


template < class T1, class T2 >
inline bool operator !=(const T1 * t1, const pointer < T2 > & t2)
{

   return !operator == (t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(const pointer < T1 > & t1, const T2 * t2)
{

   return !operator == (t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(T1 * t1, const pointer < T2 > & t2)
{

   return !operator == ((const T1 *) t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(const pointer < T1 > & t1, T2 * t2)
{
   return !operator == (t1, (const T2 *) t2);
}


template < class T1, class T2 >
inline bool operator !=(const pointer < T1 > & t1, const pointer < T2 > & t2)
{

   return !operator == (t1, t2);

}


template < class T >
inline bool operator ==(LPARAM l, const pointer < T > & sp) { return ((T *) l) == sp.m_p; }


template < class T >
inline bool operator !=(LPARAM l, const pointer < T > & sp) { return ((T *) l) != sp.m_p; }



