#include "framework.h"


CLASS_DECL_APEX string __get_text(string str)
{

   ::apex::application* papp = ::get_context_application();

   if (papp == nullptr)
   {

      papp = ::get_global_application();

      if (papp == nullptr)
      {

         return str;

      }

   }

   return papp->__get_text(str);

}
//
//
//CLASS_DECL_APEX int __c_get_text_length(const char* psz)
//{
//
//   string str = __get_text(psz);
//
//   return (int)str.get_length();
//
//}
//
//
//CLASS_DECL_APEX void __c_get_text(char* pszText, int iLen, const char* psz)
//{
//
//   string str = __get_text(psz);
//
//   iLen = min(iLen, (int)str.get_length());
//
//   strncpy(pszText, str, iLen);
//
//   pszText[iLen] = '\0';
//
//}



