// Created by camilo on 2023-11-25 21:17 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/c.h"
#include <string.h>

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
      string(const_char_pointer psz)
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
      string(const ::c::string & str)
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
      string(::c::string && str)
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
      string & operator = (const ::c::string & str) {
         if (m_psz != str.m_psz) {
            destroy();
            if (str.m_psz)
            {
               m_psz = strdup(str.m_psz);
            }
         }
         return *this;
      }
      string & operator = (const_char_pointer psz) {
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

      operator const_char_pointer () const { return m_psz; }

      bool operator == (const_char_pointer psz)
      {

         return !strcmp(m_psz, psz);
      }

      int size() const;

      int find_replace(const_char_pointer search, const_char_pointer replace);
      int find_replace(char search, char replace);

      string & operator += (const_char_pointer p);

   };

} // namespace c

