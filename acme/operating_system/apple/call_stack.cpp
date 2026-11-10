//
//  callstack.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  15:22
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "platform.h"
#include "acme/operating_system/ansi/call_stack.h"
#include "acme/platform/node.h"
#include "call_stack.h"
#include "acme/exception/call_stack.h"
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>
#include <cxxabi.h>


void call_stack::capture(::i32 iSkip, void * caller_address, ::i32 iCount)
{

   free((void *)m_pszCallStack);
   m_pszCallStack = nullptr;
   m_caller_address = caller_address;
   m_u32Hash = 0;
   m_iCount = 0;

   if (iCount == 0)
   {
      return;
   }

   auto frames = ::backtrace(m_stack, TRACE_MAX_STACK_FRAMES);
   // The first frame is capture itself; negative skip selects the default.
   auto skip = iSkip < 0 ? (frames > 0 ? 1 : 0) : (iSkip >= frames ? frames : iSkip + 1);
   // A supplied caller address selects the start when present in this stack.
   if (caller_address)
   {
      for (int i = skip; i < frames; ++i)
      {
         if (m_stack[i] == caller_address)
         {
            skip = i;
            break;
         }
      }
   }
   auto count = frames - skip;
   if (iCount >= 0 && count > iCount)
   {
      count = iCount;
   }
   for (int i = 0; i < count; ++i)
   {
      m_stack[i] = m_stack[i + skip];
      auto address = (uintptr_t)m_stack[i];
      // Fold every byte so that the hash includes all bits of a 64-bit PC.
      for (size_t byte = 0; byte < sizeof(address); ++byte)
      {
         m_u32Hash = m_u32Hash * 33 + (address & 0xff);
         address >>= 8;
      }
   }
   m_iCount = count;

}


::i32 call_stack::_prepare_trace(const_char_pointer pszFormat)
{

   // Match the Windows backend's module + offset representation.
   ::i32 size = 64;
   for (::i32 i = 0; i < m_iCount; ++i)
   {
      Dl_info info = {};
      const char * path = "(unknown)";
      m_modulea[i] = nullptr;
      if (::dladdr(m_stack[i], &info))
      {
         m_modulea[i] = info.dli_fbase;
         if (info.dli_fname && *info.dli_fname)
         {
            path = info.dli_fname;
         }
      }
      ::snprintf(m_szaModulePath[i], MODULE_BUF_SIZE, "%s", path);
      m_u32ModulePathLength[i] = ::strlen(m_szaModulePath[i]);
      size += m_u32ModulePathLength[i] + 64;
   }
   return size;

}


const_char_pointer call_stack::_trace(::i32 iSize, const_char_pointer pszFormat)
{

   if (iSize <= 0)
   {
      return nullptr;
   }
   auto trace = (char *)::malloc(iSize);
   if (!trace)
   {
      return nullptr;
   }
   trace[0] = '\0';
   auto written = ::snprintf(trace, iSize, "Stack hash: 0x%08x\n", (unsigned int)m_u32Hash);
   size_t used = written < 0 ? 0 : (size_t)written;
   for (::i32 i = 0; i < m_iCount && used < (size_t)iSize; ++i)
   {
      auto offset = (uintptr_t)m_stack[i] - (uintptr_t)m_modulea[i];
      written = ::snprintf(trace + used, iSize - used, "%02d:%s+0x%016llx\n",
         i, m_szaModulePath[i], (unsigned long long)offset);
      if (written < 0)
      {
         break;
      }
      used += (size_t)written;
   }
   return trace;

}


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
//   string node::get_callstack(const ::scoped_string & scopedstrFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
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
//void backtrace_symbol_parse(string & strSymbolName, string & strAddress, char_pointer pmessage, void * address)
//{
//   
//   char_pointer pszOrdinal = pmessage;
//   
//   char_pointer pszModule = nullptr;
//   
//   char_pointer pszAddress = nullptr;
//
//   char_pointer pszMangledName = nullptr;
//
//   char_pointer pszOffsetBegin = nullptr;
//   
//   ::i32 iSpace = 0;
//   
//   bool bWhitespace = false;
//
//   for (char_pointer psz = pmessage; *psz; ++psz)
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
//      ::i32 status;
//
//      acme::malloc < char_pointer > pszRealName = abi::__cxa_demangle(scopedstrMangledName, 0, 0, &status);
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



void apple_backtrace_symbol_parse(string & strSymbolName, string & strAddress, char_pointer pmessage, void * address)
{

   char_pointer pszMangledName = nullptr;

   char_pointer pszMangledNameEnd = nullptr;

   char_pointer pszOffsetBegin = nullptr;

   char_pointer pszOffsetEnd = nullptr;

   ::i32 i = 0;

   bool bWasSpace = false;
   char_pointer psz = pmessage;

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

      ::i32 status;

      acme::malloc < char_pointer > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);

      const_char_pointer pszSymbolName;

      if (status == 0)
      {

         strSymbolName = (const_char_pointer )(char_pointer ) pszRealName;

      }
      else
      {

         strSymbolName = pszMangledName;

      }

      strAddress = pszOffsetEnd;

   }

}
