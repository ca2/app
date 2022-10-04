//
//  callstack.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Sørensen on 14/02/22.
//  15:22
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
#include "acme/operating_system/ansi/callstack.h"
#include "callstack.h"
#include <execinfo.h>
#include <cxxabi.h>


string get_callstack(const char* pszFormat, i32 iSkip, void * caller_address, int iCount)
{

   const size_t iMaximumFramesToCapture = 64;

   void * stack[iMaximumFramesToCapture];

   auto frames = ::backtrace(stack, iMaximumFramesToCapture);
   
   return _ansi_stack_trace(stack, frames, pszFormat);

}




void backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address)
{
   
   char * pszOrdinal = pmessage;
   
   char * pszModule = nullptr;
   
   char * pszAddress = nullptr;

   char * pszMangledName = nullptr;

   char * pszOffsetBegin = nullptr;
   
   int iSpace = 0;
   
   bool bWhitespace = false;

   for (char * psz = pmessage; *psz; ++psz)
   {
      
      if(!bWhitespace)
      {
         
         if(*psz == ' ')
         {
            
            bWhitespace = true;
            
            iSpace++;
            
            *psz = '\0';
            
         }
         
      }
      else
      {
         
         if(*psz != ' ')
         {
            
            bWhitespace = false;
            
            if(iSpace == 1)
            {
             
               pszModule = psz;
               
            }
            else if(iSpace == 2)
            {
             
               pszAddress = psz;
               
            }
            else if(iSpace == 3)
            {
             
               pszMangledName = psz;
               
            }

         }

      }

   }

   if (pszMangledName && pszAddress && pszMangledName > pszAddress)
   {

      i32 status;

      acme::malloc < char * > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);

      if (status == 0)
      {

         strSymbolName = pszRealName.get();

      }
      else
      {

         strSymbolName = pszMangledName;

      }

      strAddress = pszAddress;

   }

}




