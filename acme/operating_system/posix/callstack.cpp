//
// Created by camilo on 5/17/22 02:38 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/platform/node.h"
// #include "acme/primitive/string/string.h"
#include <cxxabi.h>


//#ifdef FREEBSD
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
//   if (pszAddress && pszMangledName)
//   {
//
//      *pszMangledName++ = '\0';
//      *pszOffsetBeg++ = '\0';
//
//      i32 status;
//
//      acme::malloc < char * > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);
//
//      const ::ansi_character * pszSymbolName;
//
//      if (status == 0)
//      {
//
//         strSymbolName = (const char *) (char *) pszRealName;
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

    if (pszMangledName && pszOffsetBegin && pszOffsetEnd && pszMangledName < pszOffsetBegin)
    {

        *pszMangledName++ = '\0';
        *pszOffsetBegin++ = '\0';
        *pszOffsetEnd++ = '\0';

        i32 status;

        acme::malloc < char * > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);

        const ::ansi_character * pszSymbolName;

        if (status == 0)
        {

            strSymbolName = (const char *) (char *) pszRealName;

        }
        else
        {

            strSymbolName = pszMangledName;

        }

        strAddress = pszOffsetEnd;

    }

}

void apple_backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address)
{

   char * pszMangledName = nullptr;
   
   char * pszMangledNameEnd = nullptr;

   char * pszOffsetBegin = nullptr;

   char * pszOffsetEnd = nullptr;
   
   int i = 0;

   bool bWasSpace = false;
   char * psz = pmessage;
   
    // find parantheses and +address offset surrounding mangled name
    for (; *psz; ++psz)
    {

        if (*psz == ' ')
        {
           
           if(::is_null(pszMangledNameEnd))
           {
              
              if(::is_set(pszMangledName))
              {
                 
                 pszMangledNameEnd = psz;
                 
              }
              
           }
           
           if(!bWasSpace)
           {

              i++;
              
           }
           
           bWasSpace = true;

        }
        else
        {
           
           if(bWasSpace)
           {
              
              if(i == 3)
              {
                 
                 pszMangledName = psz;
                 
              }
              
           }
           
           bWasSpace = false;
           
        }

    }
   
   if(::is_null(pszMangledNameEnd))
   {
      
      if(::is_set(pszMangledName))
      {
         
         pszMangledNameEnd = psz;
         
      }
      
   }

    if (pszMangledName)
    {

        *pszMangledNameEnd = '\0';

        i32 status;

        acme::malloc < char * > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);

        const ::ansi_character * pszSymbolName;

        if (status == 0)
        {

            strSymbolName = (const char *) (char *) pszRealName;

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
////#if defined(__clang__) && !defined(ANDROID)
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
