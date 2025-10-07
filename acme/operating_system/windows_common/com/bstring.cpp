#include "framework.h"
#include "bstring.h"
#include "acme/prototype/string/string.h"

//
// BSTR bstring::allocate_string(const ::scoped_string & scopedstr)
// {
//
//    // auto srclen = scopedstr.size();
//    //
//    // BSTR bstr = nullptr;
//    //
//    // auto dstlen = utf_to_utf_length(bstr, scopedstr.data(), srclen);
//    //
//    // bstr = ::SysAllocStringLen(nullptr, (unsigned int) dstlen);
//    //
//    // if (bstr == nullptr)
//    // {
//    //
//    //    return nullptr;
//    //
//    // }
//    //
//    // ::utf_to_utf(bstr, scopedstr.data(), srclen);
//
//    return bstr;
//
// }


BSTR bstring::allocate_string(const OLECHAR * sz)
{

   return ::SysAllocString(sz);

}


BSTR bstring::allocate_string(const ::scoped_string & scopedstr)
{

   wstring wstr(scopedstr);

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



