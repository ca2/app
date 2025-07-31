#pragma once


#include "acme/_operating_system.h"


class CLASS_DECL_ACME bstring
{
public:

   
   BSTR        m_bstr;


   bstring() { m_bstr = nullptr; }
   bstring(const OLECHAR * sz) { m_bstr = allocate_string(sz); }

   bstring(const char * psz, int len = -1) { m_bstr = ::is_null(scopedstr) ? nullptr : string_byte_len(scopedstr, len < 0 ? (unsigned int) strlen(scopedstr) : len); }

   ~bstring() { if(m_bstr) allocate_string(m_bstr); m_bstr = nullptr; }


   operator BSTR() { return m_bstr; }
   operator BSTR() const { return m_bstr; }

   BSTR c_str() const { return m_bstr; }

   static BSTR string_byte_len(const char * psz, character_count i);

   static BSTR allocate_string(const OLECHAR * sz);

   static BSTR allocate_string(const char * psz);

   static void free_string(BSTR bstr);

   inline static unsigned int SysStringByteLen(BSTR bstr)
   {
      if (bstr == 0)
         return 0;
      return *((unsigned int *)bstr - 1);
   }

   inline static unsigned int SysStringLen(BSTR bstr)
   {
      return SysStringByteLen(bstr) / sizeof(OLECHAR);
   }

   BSTR detach()
   {
      auto bstr = m_bstr;

      m_bstr = nullptr;
      return bstr;

   }

};
