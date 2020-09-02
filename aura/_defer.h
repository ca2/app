#pragma once


#if !defined(CUBE)


#include "aura/inline/_new_impl.h"


#endif


#include "aura/primitive/string/_defer.h"


#include "aura/filesystem/file/_defer.h"


namespace primitive
{


   template < typename TYPE >
   template < typename OBJECT >
   __pointer(OBJECT) member < TYPE >::cast() const
   {

      return ::is_null((TYPE*)m_p) ? nullptr : (TYPE*)m_p;

   }


} // namespace primitive


template < class T >
template < typename T2 >
inline __pointer(T) & pointer < T >::defer_create_new()
{

   if (is_null())
   {

      create_new < T2 >();

   }

   return *this;

}


template < class T >
template < typename T2 >
inline __pointer(T) & pointer < T >::defer_assign_to(T2 * & p)
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
template < typename T2 >
inline __pointer(T) & pointer < T >::create_new()
{

   auto p = __new(T2);

   return operator=(p);

}


template < class T >
template < typename T2, typename OBJECT >
inline __pointer(T) & pointer < T >::defer_create_new(OBJECT * pobjectContext)
{

   if (is_null())
   {

      create_new < T2 >(pobjectContext);

   }

   return *this;

}


template < class T >
template < typename T2, typename OBJECT >
inline __pointer(T) & pointer < T >::create_new(OBJECT * pobjectContext)
{

   auto p = __new(T2);

   if (p)
   {

      p->initialize(pobjectContext);

   }

   return operator=(p);

}


template < typename TYPE1, typename TYPE2 >
inline void __copy(TYPE1* p1, const TYPE2* p2) { ::copy(p1, p2); }

template < typename TYPE1, typename TYPE2 >
inline void __copy(TYPE1& t1, const TYPE2* p2) { ::copy(&t1, p2); }

template < typename TYPE1, typename TYPE2 >
inline void __copy(TYPE1* p1, const TYPE2& t2) { ::copy(p1, &t2); }

template < typename TYPE1, typename TYPE2 >
inline void __copy(TYPE1& p1, const TYPE2& p2) { ::copy(&p1, &p2); }


template < typename TYPE >
inline auto __copy(const TYPE& t) { return TYPE(t); }


namespace papaya
{


   namespace array
   {

      
      template < class TDST,class TSRC >
      ::count __copy(TDST & dsta,const TSRC & srca)
      {

         dsta.set_size(srca.get_size());

         for(int i = 0; i < dsta.get_size(); i++)
         {

            ::__copy(dsta[i], srca[i]);

         }

         return dsta.get_count();

      }

   
   } // namespace array


} // namespace papaya



