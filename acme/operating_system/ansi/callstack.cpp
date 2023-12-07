//
//  callstack.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  15:33
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"

#if !defined(WINDOWS)


#include "callstack.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include <execinfo.h>
#include <cxxabi.h>


//#define __USE_BFD


#if defined(__APPLE__)

void apple_backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address);

#elif defined(FREEBSD)

void freebsd_backtrace_symbol_parse(string & strSymbolName, string & strModule, string & strAddress, char * pmessage, void * address);

#else

void backtrace_symbol_parse(string &strSymbolName, string &strAddress, char *pmessage, void *address);

#endif

string _ansi_stack_trace(void *const *ppui, int frames, const char *pszFormat, int iSkip)
{

   ::string strCallstack;

   ::acme::malloc<char **> messages(::backtrace_symbols(ppui, frames));

   //char szN[24];

   //*_strS = '\0';

   //char syscom[1024];

   //const char * func;
   //const char * file;
   //unsigned iLine;

   auto ppMessages = messages.get();

   int i = 0;

   for (; i < frames && *ppMessages != nullptr; ++i, ppMessages++)
   {

      if(i < iSkip)
      {

         continue;

      }

      //printf("backtrace %s\n", *ppMessages);
#ifdef __USE_BFD

      if(resolve_addr_file_func_line(((void **)ppui)[i], &file, &func, iLine))
            {


               ansi_concatenate(_strS, file);
               ansi_concatenate(_strS, ":");
               ansi_from_u64(szN, iLine, 10);
               ansi_concatenate(_strS, szN);
               ansi_concatenate(_strS, ":1: warning: ");

            }
#endif // __USE_BFD

      auto pmessage = *ppMessages;




      //printf("%s", pmessage);

      string strSymbolName;

      string strAddress;

      string strLine;

#if defined(__APPLE__)
      
      apple_backtrace_symbol_parse(strSymbolName, strAddress, pmessage, ppui[i]);

      strLine.formatf("%02d : %s : %s\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str());

#elif defined(FREEBSD)

      string strModule;

      freebsd_backtrace_symbol_parse(strSymbolName, strModule, strAddress, pmessage, ppui[i]);

      strLine.formatf("%02d : %s : %s (%s)\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str(), strModule.c_str());

#else
      
      backtrace_symbol_parse(strSymbolName, strAddress, pmessage, ppui[i]);
      
      strLine.formatf("%02d : %s : %s\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str());

#endif

      strCallstack += strLine;

   }

   return strCallstack;

}


namespace acme
{


//   void node::defer_update_callstack()
//   {
//
//
//   }


   string node::get_call_stack_trace(const ::scoped_string & strFormat, i32 iSkip, void *caller_address, int iCount)
   {

      auto psynchronization = this->platform()->system()->synchronization();

      synchronous_lock sl(psynchronization);

#if defined(FREEBSD)
      const int iMaximumFramesToCapture = 32;
#else
      const int iMaximumFramesToCapture = 96;
#endif

      void * stack[iMaximumFramesToCapture];

      auto frames = ::backtrace(stack, iMaximumFramesToCapture);

      string str = _ansi_stack_trace(stack, minimum_non_negative(iCount, frames), strFormat, maximum( iSkip, 0));

      return str;

   }


} // namespace acme



#endif
