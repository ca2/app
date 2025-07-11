// From cotaskptr.h by camilo on 2022-11-14 06:53 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/string/string.h"


template < typename TYPE >
class comptr_array
{
public:


   TYPE** m_pp;
   UINT32            m_cCount;

   comptr_array(TYPE** pp = nullptr, UINT32 cCount = 0) :
      m_pp(pp),
      m_cCount(cCount)
   {

   }


   ~comptr_array()
   {

      free();

   }

   bool is_null() const
   {

      return m_pp == nullptr;

   }

   bool is_set() const
   {

      return m_pp != nullptr;

   }

   virtual void free()
   {

      if (m_pp != nullptr)
      {

         for (UINT32 u = 0; u < m_cCount; u++)
         {

            if (m_pp[u])
            {

               m_pp[u]->Release();

            }

         }

         ::CoTaskMemFree(m_pp);

         m_pp = nullptr;

      }

   }


   operator TYPE** ()
   {

      return m_pp;

   }

   operator const TYPE** () const
   {

      return m_pp;

   }


   TYPE** operator ->()
   {

      return m_pp;

   }


   const TYPE** operator ->() const
   {

      return m_pp;

   }

   TYPE*** operator &()
   {

      free();

      return &m_pp;

   }

   const TYPE*** operator &() const
   {

      return &m_pp;

   }


};

#define __comptr_array(a) &a.m_pp, &a.m_cCount
