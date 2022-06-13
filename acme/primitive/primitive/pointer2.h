#pragma once

//CLASS_DECL_ACME void throw_resource_exception(const char * psz);

template < class T >
inline ___pointer < T >::___pointer(lparam& lparam)
{

   m_pelement = (::element*)(::iptr)lparam.m_lparam;
   m_p = dynamic_cast <T*>(m_pelement);
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
inline ___pointer < T > ::___pointer() :
   m_p(nullptr),
   m_pelement(nullptr)
{

}


template < class T >
inline ___pointer < T > ::___pointer(std::nullptr_t) :
   m_p(nullptr),
   m_pelement(nullptr)
{

}

template < class T >
template < typename T2 >
inline ___pointer < T > ::___pointer(enum_move_transfer, T2 * p)
{

   if(::is_set(p))
   {

      m_p = dynamic_cast < T * > (p);

      m_pelement = m_p;

      if(::is_null(m_p))
      {

         ::release(p);

         m_p = nullptr;

         m_pelement = nullptr;

         throw ::resource_exception("OBJECT * p is not of type T (pointer < T >).");

      }

   }
   else
   {

      m_p = nullptr;

      m_pelement = nullptr;

   }

}


template < class T >
inline ___pointer < T > ::___pointer(const ___pointer & t) :
   m_p(t.m_p),
   m_pelement(t.m_pelement)
{

   if (::is_set(m_p))
   {

      m_pelement->increment_reference_count();

   }

}


template < class T >
inline ___pointer < T > ::___pointer(___pointer && t) :
m_p(t.m_p),
m_pelement(t.m_pelement)
{

   t.m_p = nullptr;

   t.m_pelement = nullptr;

}



//template < class T >
//template < typename T2 >
//inline ___pointer < T > ::___pointer(const T2 * p) :
//   m_p((T *) p),
//   m_pelement(m_p)
//{
//
//   ::increment_reference_count(m_p);
//
//}



template < class T >
inline ___pointer < T > ::~___pointer()
{

   release();

}


template < class T >
inline T * ___pointer < T > ::operator ->()
{

   return m_p;

}


template < class T >
inline T * ___pointer < T > ::operator ->() const
{

   return m_p;

}


template < class T >
inline T & ___pointer < T > ::operator * ()
{

   return *m_p;

}


template < class T >
inline T & ___pointer < T > ::operator * () const
{

   return *m_p;

}


template < class T >
inline ___pointer < T > ::operator T * ()
{

   return m_p;

}


template < class T >
inline ___pointer < T > ::operator T * const () const
{

   return m_p;

}


template < class T >
inline T * ___pointer < T > ::get()
{

   return m_p;

}


template < class T >
inline const T * ___pointer < T > ::get() const
{

   return m_p;

}


template < class T >
inline bool ___pointer < T > ::is_null() const
{

   return ::is_null(m_p);

}


template < class T >
inline bool ___pointer < T > ::is_set() const
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
inline ___pointer < T > & ___pointer < T > ::reset (T2 * pNew OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_null(pNew))
   {

      m_pelement = nullptr;

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

            m_pelement = p;

         }
         else
         {

            m_p = nullptr;

            m_pelement = nullptr;

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
inline ___pointer < T > & ___pointer < T > ::operator = (const ___pointer  & t)
{
   if (this != &t)
   {

      auto pold = m_pelement;

      m_p = t.m_p;

      m_pelement = t.m_pelement;

      if (::is_set(m_p))
      {

         m_pelement->increment_reference_count();

      }

      ::release(pold REF_DBG_COMMA_POINTER);

   }
   return *this;

}


template < class T >
inline ___pointer < T > & ___pointer < T > ::operator = (___pointer && t)
{

   if(&t != this)
   {

      auto pOld         = m_pelement;

      m_p           = t.m_p;

      m_pelement        = t.m_pelement;

      t.m_p         = nullptr;

      t.m_pelement      = nullptr;

      ::release(pOld REF_DBG_COMMA_POINTER);

   }

   return *this;

}


template < class T >
inline T * ___pointer < T > ::detach()
{

   auto p = m_p;

   m_p = nullptr;

   m_pelement = nullptr;

   return p;

}


// cut and paste with very good capabilities of RealVNC for MacOS in OVH.fr/eu/pt cloud from Windows client.
// slashes with ABNT 2 keyboard and even c cedilha working with RealVNC
template < class T >
inline i64 ___pointer <T>::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{
   
   m_p = nullptr;

   return ::release(m_pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < class T1, class T2 >
inline bool operator ==(const T1  * t1, const ___pointer < T2 > & t2)
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
inline bool operator ==(const ___pointer < T1 > & t1, const T2 * t2)
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
inline bool operator ==(const ___pointer < T1 > & t1, const ___pointer < T2 > & t2)
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
inline bool operator ==(T1 * t1, const ___pointer < T2 > & t2)
{

   return operator == ((const T1 *) t1, t2);

}


template < class T1, class T2 >
inline bool operator ==(const ___pointer < T1 > & t1, T2 * t2)
{

   return operator == (t1,  (const T2 *) t2);

}


template < class T1, class T2 >
inline bool operator !=(const T1 * t1, const ___pointer < T2 > & t2)
{

   return !operator == (t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(const ___pointer < T1 > & t1, const T2 * t2)
{

   return !operator == (t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(T1 * t1, const ___pointer < T2 > & t2)
{

   return !operator == ((const T1 *) t1, t2);

}


template < class T1, class T2 >
inline bool operator !=(const ___pointer < T1 > & t1, T2 * t2)
{
   return !operator == (t1, (const T2 *) t2);
}


template < class T1, class T2 >
inline bool operator !=(const ___pointer < T1 > & t1, const ___pointer < T2 > & t2)
{

   return !operator == (t1, t2);

}




template < typename TYPE >
inline bool is_set(const __pointer(TYPE) & p)
{

   return p.is_set();

}


template<typename TYPE>
inline bool is_null(const __pointer(TYPE) & p)
{

   return ::is_null(p.m_p);

}


template < typename TYPE >
inline __pointer(TYPE) clone(const __pointer(TYPE) & p)
{

   if (!p)
   {

      return p;

   }
   
   auto pelement = p->clone();
   
   if(__pointer_is_null(pelement))
   {
      
      throw ::exception(error_failed);
      
   }
   
   auto pNew = dynamic_cast < TYPE * > (pelement);
   
   if(__pointer_is_null(pNew))
   {
      
      throw ::exception(error_wrong_type);
      
   }

   return ::move_transfer(pNew);
   
}


template < typename TYPE >
inline __pointer(TYPE) & clone(__pointer(TYPE) & p)
{

   return p = ::clone((const __pointer(TYPE) &) p);

}


template < typename TYPE >
inline __pointer(TYPE) & defer_clone(__pointer(TYPE) & p)
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
      
      throw ::exception(error_null_pointer);
      
   }
   
   auto pelement = p->clone();
   
   auto pNew = dynamic_cast < TYPE * > (pelement);
   
   if(__pointer_is_null(pNew))
   {
      
      throw ::exception(error_wrong_type);
   
   }
   
   return ::move_transfer(pNew);
   
}



