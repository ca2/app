#pragma once

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

      Release();

   }

   HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter = nullptr, ::u32 dwClsContext = CLSCTX_ALL)
   {

      Release();

      return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(TYPE), (void **)&m_p);

   }

   template < class IFACE >
   HRESULT As(comptr < IFACE > & iface)
   {

      if (m_p == nullptr)
      {

         return E_FAIL;

      }

      return m_p->QueryInterface< IFACE >(&iface);

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



   TYPE ** operator & ()
   {

      Release();

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


   ULONG Release()
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


   bool is_null()
   {

      return m_p == nullptr;

   }


   bool is_set()
   {

      return !is_null();

   }


};




