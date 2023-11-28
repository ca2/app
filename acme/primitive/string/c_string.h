// Created by camilo on 2023-11-25 21:17 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/c.h"


namespace c
{

   class CLASS_DECL_ACME string
   {
   public:

      char * m_psz;
      string()
      {
         m_psz = nullptr;
      }
      string(const char * psz)
      {
         m_psz = strdup(psz);
      }
      string(const string & str)
      {
         m_psz = strdup(str.m_psz);
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
         if (this != &str) {
            destroy();
            m_psz = strdup(str.m_psz);
         }
         return *this;
      }
      string & operator = (const char * psz) {
         if (psz != m_psz)
         {
            destroy();
            m_psz = strdup(psz);
         }
         return *this;
      }
      string & operator = (string && str) {
         if (this != &str) {
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

