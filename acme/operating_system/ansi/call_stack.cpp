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


#include "call_stack.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include <execinfo.h>
#include <cxxabi.h>


//#define __USE_BFD


#if defined(__APPLE__)
#define DISABLE_BACKTRACE 0

void apple_backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address);

#elif defined(FREEBSD)
#define DISABLE_BACKTRACE 0
void freebsd_backtrace_symbol_parse(::particle * pparticle, string & strSymbolName, string & strModule, string & strAddress, char * pmessage, void * address);

#elif defined(OPENBSD)
#define DISABLE_BACKTRACE 1
void openbsd_backtrace_symbol_parse(::particle * pparticle, string & strSymbolName, string & strModule, string & strAddress, char * pmessage, void * address);

#else
#define DISABLE_BACKTRACE 0
void backtrace_symbol_parse(string &strSymbolName, string &strAddress, char *pmessage, void *address);

#endif


#if !defined(__ANDROID__)

string _ansi_stack_trace(::particle * pparticle, void *const *ppui, int frames, const char *pszFormat, int iSkip)
{

#if DISABLE_BACKTRACE

   return "";

#else

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
               ansi_from_unsigned_long_long(szN, iLine, 10);
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

      freebsd_backtrace_symbol_parse(pparticle, strSymbolName, strModule, strAddress, pmessage, ppui[i]);

      strLine.formatf("%02d : %s : %s (%s)\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str(), strModule.c_str());

#elif defined(OPENBSD)

      string strModule;

      openbsd_backtrace_symbol_parse(pparticle, strSymbolName, strModule, strAddress, pmessage, ppui[i]);

      strLine.formatf("%02d : %s : %s (%s)\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str(), strModule.c_str());

#else
      
      backtrace_symbol_parse(strSymbolName, strAddress, pmessage, ppui[i]);
      
      strLine.formatf("%02d : %s : %s\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str());

#endif

      strCallstack += strLine;

   }

   return strCallstack;

#endif

}


#endif


namespace platform
{


   void node::defer_update_call_stack()
   {


   }

#if !defined(__ANDROID__)

   void node::get_call_stack_frames(void ** stack, int & frame_count)
   {

#if DISABLE_BACKTRACE
      frame_count = 0;
#else

#if defined(FREEBSD) || defined(OPENBSD)
      const int iMaximumFramesToCapture = 32;
#else
      const int iMaximumFramesToCapture = 96;
#endif
      
      int iFrameCount = minimum(frame_count, iMaximumFramesToCapture);

      auto frames = ::backtrace(stack, iFrameCount);
      
      frame_count = frames;
#endif

   }

#endif

   int node::get_call_stack_default_frame_count()
   {
      
   #if defined(FREEBSD) || defined(OPENBSD)
         const int iMaximumFramesToCapture = 32;
   #else
         const int iMaximumFramesToCapture = 96;
   #endif
      
      return iMaximumFramesToCapture;
      
   }


   string node::get_call_stack_trace(const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
   {
      
      return _get_call_stack_trace(scopedstrFormat, iSkip, caller_address, iCount);
      
   }


   string node::get_call_stack_trace(void ** stack, int frame_count, const ::scoped_string & strFormat, int iSkip, void *caller_address, int iCount)
   {

      auto psynchronization = ::system()->synchronization();

      _synchronous_lock sl(psynchronization);

#if defined(FREEBSD) || defined(OPENBSD)
      const int iMaximumFramesToCapture = 32;
#else
      const int iMaximumFramesToCapture = 96;
#endif

      string str = _ansi_stack_trace(this, stack, minimum_non_negative(frame_count, iMaximumFramesToCapture), strFormat, maximum(iSkip, 0));

      return str;

   }


} // namespace acme



#endif
