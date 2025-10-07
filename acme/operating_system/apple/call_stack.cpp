//
//  callstack.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  15:22
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acme/operating_system/ansi/call_stack.h"
#include "acme/platform/node.h"
#include "call_stack.h"
#include <execinfo.h>
#include <cxxabi.h>

//
//namespace acme
//{
//
//
//   void node::defer_update_callstack()
//   {
//
//
//   }
//
//
//   string node::get_callstack(const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
//   {
//
//      const size_t iMaximumFramesToCapture = 64;
//
//      void * stack[iMaximumFramesToCapture];
//
//      auto frames = ::backtrace(stack, iMaximumFramesToCapture);
//
//      return _ansi_stack_trace(stack, frames, scopedstrFormat);
//
//   }
//
//
//} // namespace acme
//
//
//void backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address)
//{
//   
//   char * pszOrdinal = pmessage;
//   
//   char * pszModule = nullptr;
//   
//   char * pszAddress = nullptr;
//
//   char * pszMangledName = nullptr;
//
//   char * pszOffsetBegin = nullptr;
//   
//   int iSpace = 0;
//   
//   bool bWhitespace = false;
//
//   for (char * psz = pmessage; *psz; ++psz)
//   {
//      
//      if(!bWhitespace)
//      {
//         
//         if(*psz == ' ')
//         {
//            
//            bWhitespace = true;
//            
//            iSpace++;
//            
//            *psz = '\0';
//            
//         }
//         
//      }
//      else
//      {
//         
//         if(*psz != ' ')
//         {
//            
//            bWhitespace = false;
//            
//            if(iSpace == 1)
//            {
//             
//               pszModule = psz;
//               
//            }
//            else if(iSpace == 2)
//            {
//             
//               pszAddress = psz;
//               
//            }
//            else if(iSpace == 3)
//            {
//             
//               pszMangledName = psz;
//               
//            }
//
//         }
//
//      }
//
//   }
//
//   if (scopedstrMangledName && pszAddress && pszMangledName > pszAddress)
//   {
//
//      int status;
//
//      acme::malloc < char * > pszRealName = abi::__cxa_demangle(scopedstrMangledName, 0, 0, &status);
//
//      if (status == 0)
//      {
//
//         strSymbolName = pszRealName.get();
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
//
//



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

      int status;

      acme::malloc < char * > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);

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
