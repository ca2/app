#include "framework.h"
#include "bstring.h"
#include "acme/prototype/string/string.h"


BSTR bstring::string_byte_len(const char * psz, character_count len)
{

   auto srclen = len < 0 ? strlen(psz) : len;

   BSTR bstr = nullptr;

   auto dstlen = utf_to_utf_length(bstr, psz, srclen);

   bstr = ::SysAllocStringLen(nullptr, (unsigned int) dstlen);

   if (bstr == nullptr)
   {

      return nullptr;

   }

   ::utf_to_utf(bstr, psz, srclen);

   return bstr;

}


BSTR bstring::allocate_string(const OLECHAR * sz)
{

   return ::SysAllocString(sz);

}


BSTR bstring::allocate_string(const char * psz)
{

   wstring wstr(psz);

   return ::SysAllocString(wstr);

}


void bstring::free_string(BSTR bstr)
{

   if (::is_null(bstr))
   {

      return;

   }

   ::SysFreeString(bstr);
   
}



