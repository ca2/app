#pragma once


#include "acme/prototype/string/string.h"


template < typename POINTER_TYPE >
class cotaskptr
{
public:


   POINTER_TYPE   m_p;

   cotaskptr()
   {

      m_p = nullptr;

   }


   ~cotaskptr()
   {

      free();

   }

   void alloc(SIZE_T size)
   {

      if (m_p != nullptr)
      {

         m_p = (POINTER_TYPE) CoTaskMemRealloc(m_p, size);

      }
      else
      {

         m_p = (POINTER_TYPE) CoTaskMemAlloc(size);

      }

   }

   bool is_null() const
   {

      return m_p == nullptr;

   }

   bool is_set() const
   {

      return m_p != nullptr;

   }

   void free()
   {

      if (m_p != nullptr)
      {

         ::CoTaskMemFree(m_p);

         m_p = nullptr;

      }

   }


   operator POINTER_TYPE()
   {

      return m_p;

   }

   operator const POINTER_TYPE() const
   {

      return m_p;

   }


   POINTER_TYPE operator ->()
   {

      return m_p;

   }


   const POINTER_TYPE operator ->() const
   {

      return m_p;

   }

   POINTER_TYPE * operator &()
   {

      free();

      return &m_p;

   }

   const POINTER_TYPE * operator &() const
   {

      return &m_p;

   }


};


template < typename POINTER_TYPE >
class sec_cotaskptr :
   public cotaskptr < POINTER_TYPE >
{
public:


   DWORD          m_size;


   sec_cotaskptr(DWORD size = 0)
   {

      m_size = size;

   }


   ~sec_cotaskptr()
   {

      free();

   }

   using cotaskptr < POINTER_TYPE > ::alloc;
   void alloc()
   {

      alloc(m_size);

   }

   void free()
   {

      if (this->m_p != nullptr)
      {

         if (m_size > 0)
         {

            SecureZeroMemory(this->m_p, m_size);

            m_size = 0;

         }

         ::cotaskptr < POINTER_TYPE > ::free();

      }

   }

};






#define cotaskp(POINTER_TYPE) cotaskptr < POINTER_TYPE >



   template < typename POINTER_TYPE >
   inline auto as_string(const cotaskptr < POINTER_TYPE >& ptr)
   {

      return ::as_string((const POINTER_TYPE)ptr);

   }



   //namespace str
   //{
   //

   inline ansi_string& assign(ansi_string& ansistrDst, const cotaskptr < PWSTR >& pwidesz)
   {

      ansistrDst.assign(pwidesz.operator const PWSTR());

      return ansistrDst;

   }


   inline wide_string& assign(wide_string& widestrDst, const cotaskptr < PSTR >& pansisz)
   {

      widestrDst.assign(pansisz.operator const PSTR());

      return widestrDst;

   }


   inline ansi_string& assign(ansi_string& ansistrDst, const cotaskptr < PSTR >& pansisz)
   {

      ansistrDst.assign(pansisz.operator const PSTR());

      return ansistrDst;

   }


   inline wide_string& assign(wide_string& widestrDst, const cotaskptr < PWSTR >& pwidesz)
   {

      widestrDst.assign(pwidesz.operator const PWSTR());

      return widestrDst;

   }
   //
   //
   //} // namespace str



