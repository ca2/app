#pragma once


#include "acme/_operating_system.h"


template <class T> void SafeRelease(T ** ppT)
{
   if (*ppT)
   {
      (*ppT)->Release();
      *ppT = NULL;
   }
}

template < typename TYPE >
class comptr
{
public:


   using BASE_TYPE = TYPE;


   TYPE * m_p;

   comptr()
   {
      m_p = nullptr;

   }


   explicit comptr(std::nullptr_t)
   {

      m_p = nullptr;

   }

   comptr(const comptr & ptr)
   {
      if (ptr.m_p != nullptr)
      {
         ptr.m_p->AddRef();
      }
      m_p = ptr.m_p;

   }

   template < typename TYPE2 >
      requires (!::std::is_same_v<TYPE, TYPE2 >)
   comptr(const comptr<TYPE2 > & ptr)
   {

      if constexpr (::std::is_convertible_v < TYPE2 *, TYPE * >)
      {

         m_p = static_cast < TYPE * >(ptr.m_p);

         if (m_p != nullptr)
         {

            m_p->AddRef();

         }

      }
      else
      {

         m_p = nullptr;

         ptr.as(*this);

      }

   }

   comptr(comptr && ptr) :
      m_p(ptr.m_p)
   {
      ptr.m_p = nullptr;

   }

   comptr(::transfer_t , TYPE * p)
   {
      m_p = p;

   }

   comptr(TYPE * p)
   {
      if (p != nullptr)
      {
         p->AddRef();
      }
      m_p = p;
   }






   ~comptr()
   {

      release();

   }

   HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter = nullptr, ::u32 dwClsContext = CLSCTX_ALL)
   {

      release();

      return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(TYPE), (void **)&m_p);

   }

   template < class IFACE >
   HRESULT as(comptr < IFACE > & iface) const
   {

      if (m_p == nullptr)
      {

         return E_FAIL;

      }

      return m_p->QueryInterface(__uuidof(IFACE), (void **) & iface);

   }

   template < class IFACE >
   comptr < IFACE > as() const
   {

      comptr < IFACE > pointer;

      this->as(pointer);

      return pointer;

   }



   TYPE * operator ->()
   {

      return (TYPE *)m_p;

   }

   TYPE * operator ->() const
   {

      return (TYPE *)m_p;

   }

   operator bool() const
   {

      return ::is_set(m_p);

   }

   bool operator !() const
   {

      return !this->operator bool();

   }

   TYPE * detach()
   {

      TYPE * p = operator ->();

      m_p = nullptr;

      return p;

   }

   // Returns a pointer to this pointer suitable for IID_PPV_ARGS.
   TYPE*const* pp() const
   {
      return &m_p;
   }


   TYPE ** operator & ()
   {
      release();
      return &(TYPE * &)m_p;

   }


   operator TYPE * ()
   {

      return (TYPE *)m_p;

   }

   comptr & operator = (TYPE * p)
   {

      if (m_p != p)
      {

         if (p != nullptr)
         {

            p->AddRef();


         }

         if (m_p != nullptr)
         {

            m_p->Release();

         }

         m_p = p;

      }

      return *this;

   }

   template < typename TYPE2 >
   requires (!::std::is_same_v<TYPE, TYPE2 >)
   comptr & operator = (TYPE2 * p)
   {

      if constexpr (::std::is_convertible_v < TYPE2 *, TYPE * >)
      {

         return operator = (static_cast < TYPE * >(p));

      }
      else
      {

         comptr < TYPE > ptr;

         if (p != nullptr)
         {

            p->QueryInterface(__uuidof(TYPE), (void **) &ptr);

         }

         return operator = (::std::move(ptr));

      }

   }


   template < typename TYPE2 >
   requires (!::std::is_same_v<TYPE, TYPE2 >)
   comptr & operator = (const comptr < TYPE2 > & ptr)
   {

      if constexpr (::std::is_convertible_v < TYPE2 *, TYPE * >)
      {

         return operator = (static_cast < TYPE * >(ptr.m_p));

      }
      else
      {

         comptr < TYPE > ptrQuery;

         ptr.as(ptrQuery);

         return operator = (::std::move(ptrQuery));

      }

   }

   comptr & operator = (const comptr & ptr)
   {

      if (&ptr != this)
      {

         if (ptr.m_p != nullptr)
         {

            ptr.m_p->AddRef();


         }

         if (m_p != nullptr)
         {

            m_p->Release();

         }

         m_p = ptr.m_p;

      }

      return *this;

   }


   comptr & operator = (comptr && ptr)
   {


      if (m_p != nullptr)
      {

         m_p->Release();

      }

      m_p = ptr.m_p;

      ptr.m_p = nullptr;

      return *this;

   }


   ULONG release()
   {

      ULONG ul = 0;

      try
      {

         if (m_p != nullptr)
         {

            ul = m_p->Release();

         }

      }
      catch (...)
      {


      }

      m_p = nullptr;


      return ul;

   }


   bool is_null() const
   {

      return m_p == nullptr;

   }


   bool is_set() const
   {

      return !is_null();

   }


};


#define __interface_of(comptr) __uuidof(decltype(*comptr.m_p)), (void **) &comptr.m_p
#define __unknown_of(comptr) __uuidof(decltype(*comptr.m_p)), reinterpret_cast < IUnknown ** > (&comptr.m_p)


template < typename TYPE >
inline bool is_null(const comptr < TYPE > & p)
{

   return ::is_null(p.m_p);

}

