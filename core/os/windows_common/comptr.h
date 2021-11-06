#pragma once


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

   comptr(TYPE * point_i32)
   {
      if (point != nullptr)
      {
         point_i32->AddRef();
      }
      m_p = point;
   }






   ~comptr()
   {

      Release();

   }

   HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter = nullptr, ::u32 dwClsContext = CLSCTX_ALL)
   {

      Release();

      if (!defer_co_initialize_ex(false))
      {

         return E_FAIL;

      }

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

      TYPE * point = operator ->();

      m_p = nullptr;

      return point;

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

   comptr & operator = (TYPE * point_i32)
   {

      if (m_p != point_i32)
      {

         if (point != nullptr)
         {

            point_i32->AddRef();


         }

         if (m_p != nullptr)
         {

            m_p->Release();

         }

         m_p = point;

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




