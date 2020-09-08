#include "framework.h"


BSTR CLASS_DECL_AQUA bstring::sys_alloc_string_byte_len(LPCSTR psz, strsize len)
{

   auto srclen = len < 0 ? strlen(psz) : len;

   BSTR bstr = nullptr;

   auto dstlen = ::str::utf_to_utf_length(bstr, psz, srclen);

   bstr = ::SysAllocStringLen(nullptr, (UINT) dstlen);

   if (bstr == nullptr)
   {

      return nullptr;

   }

   ::str::utf_to_utf(bstr, psz, srclen);

   return bstr;

}


BSTR CLASS_DECL_AQUA bstring::sys_alloc_string(const OLECHAR * sz)
{

   return ::SysAllocString(sz);

}


void bstring::sys_free_string(BSTR bstr)
{

   if (::is_null(bstr))
   {

      return;

   }

   ::SysFreeString(bstr);
   
}
