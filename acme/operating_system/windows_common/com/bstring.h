#pragma once


#include "acme/_operating_system.h"


class CLASS_DECL_ACME bstring
{
public:

   
   BSTR        m_bstr;


   bstring() { m_bstr = nullptr; }
   bstring(const OLECHAR * sz) { m_bstr = allocate_string(sz); }

   bstring(const ::scoped_string & scopedstr)
   {

      m_bstr = allocate_string(scopedstr);

   }

   ~bstring() { if(m_bstr) allocate_string(m_bstr); m_bstr = nullptr; }


   operator BSTR() { return m_bstr; }
   operator BSTR() const { return m_bstr; }

   BSTR c_str() const { return m_bstr; }

   static BSTR allocate_string(const OLECHAR * sz);

   static BSTR allocate_string(const ::scoped_string & scopedstr);

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
