// Created by camilo on 2023-11-25 21:17 <3ThomasBorregaardSorensen!!
#pragma once


#include "acid/platform/c.h"


namespace c
{

   class CLASS_DECL_ACID string
   {
   public:

      char * m_psz;
      string()
      {
         m_psz = nullptr;
      }
      string(const char * psz)
      {
         if (psz)
         {
            m_psz = strdup(psz);
         }
         else
         {
            m_psz = nullptr;
         }
      }
      string(const string & str)
      {
         if (str.m_psz)
         {
            m_psz = strdup(str.m_psz);
         }
         else
         {
            m_psz = nullptr;
         }
      }
      string(string && str)
      {
         auto psz = str.m_psz;
         str.m_psz = nullptr;
         m_psz = psz;
      }
      ~string()
      {
         destroy();
      }
      void destroy()
      {
         auto psz = m_psz;
         m_psz = nullptr;
         if (psz) free(psz);
      }
      string & operator = (nullptr_t) 
      {
         destroy(); 
         return *this;
      }
      string & operator = (const string & str) {
         if (m_psz != str.m_psz) {
            destroy();
            if (str.m_psz)
            {
               m_psz = strdup(str.m_psz);
            }
         }
         return *this;
      }
      string & operator = (const char * psz) {
         if (psz != m_psz)
         {
            destroy();
            if (psz)
            {
               m_psz = strdup(psz);
            }
         }
         return *this;
      }
      string & operator = (string && str) noexcept {
         if (m_psz != str.m_psz) {
            destroy();
            auto psz = str.m_psz;
            str.m_psz = nullptr;
            m_psz = psz;
         }
         return *this;

      }

      operator const char * () const { return m_psz; }


   };

} // namespace c

