//
// Created by camilo on 5/17/22 02:38 <3ThomasBorregaardSorensen!!
//
#include "framework.h"


#if !defined(WINDOWS)

#include "acme/platform/node.h"

#include <cxxabi.h>


//#if defined(FREEBSD) || defined(OPENBSD)
//
//
//void backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address)
//{
//
//   char * pszAddress = pmessage;
//
//   char * pszMangledName = nullptr;
//
//   char * pszOffsetBeg = nullptr;
//
//   // find parantheses and +address offset surrounding mangled name
//   for (char * psz = pmessage; *psz; ++psz)
//   {
//
//      if (*psz == '<')
//      {
//
//         pszMangledName = psz;
//
//      }
//      else if (*psz == '+')
//      {
//
//         pszOffsetBeg = psz;
//
//         break;
//
//      }
//
//   }
//
//   if (scopedstrAddress && pszMangledName)
//   {
//
//      *pszMangledName++ = '\0';
//      *pszOffsetBeg++ = '\0';
//
//      int status;
//
//      acme::malloc < char * > pszRealName = abi::__cxa_demangle(scopedstrMangledName, 0, 0, &status);
//
//      const_char_pointer pszSymbolName;
//
//      if (status == 0)
//      {
//
//         strSymbolName = (const_char_pointer )(char *) pszRealName;
//
//      }
//      else
//      {
//
//         strSymbolName = pszMangledName;
//
//      }
//
//      strAddress = pszAddress;
//
//   }
//
//}
//
//
//#else
//

void backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address)
{

    char * pszMangledName = nullptr;

    char * pszOffsetBegin = nullptr;

    char * pszOffsetEnd = nullptr;

    // find parantheses and +address offset surrounding mangled name
    for (char * psz = pmessage; *psz; ++psz)
    {

        if (*psz == '(')
        {

            pszMangledName = psz;

        }
        else if (*psz == '+')
        {

            pszOffsetBegin = psz;

        }
        else if (*psz == ')')
        {

            pszOffsetEnd = psz;

            break;

        }

    }

    if (scopedstrMangledName && pszOffsetBegin && pszOffsetEnd && pszMangledName < pszOffsetBegin)
    {

        *pszMangledName++ = '\0';
        *pszOffsetBegin++ = '\0';
        *pszOffsetEnd++ = '\0';

        int status;

        acme::malloc < char * > pszRealName = abi::__cxa_demangle(scopedstrMangledName, 0, 0, &status);

        const_char_pointer pszSymbolName;

        if (status == 0)
        {

            strSymbolName = (const_char_pointer )(char *) pszRealName;

        }
        else
        {

            strSymbolName = pszMangledName;

        }

        strAddress = pszOffsetEnd;

    }

}





//
//
//#endif
//
//
//namespace acme
//{
//
//
////#if defined(__clang__) && !defined(__ANDROID__)
////
////    ::string node::get_callstack()
////    {
////
////        return clang_backtrace();
////
////    }
////
////#endif
//
//
//} // namespace acme
//
//
//

#endif


