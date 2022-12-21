//
//  callstack.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Sørensen on 14/02/22.
//  15:33
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
#include "callstack.h"
#include "acme/platform/node.h"
#include "acme/primitive/string/string.h"
#include <execinfo.h>
#include <cxxabi.h>


void backtrace_symbol_parse(string &strSymbolName, string &strAddress, char *pmessage, void *address);

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

   int i = iSkip;

   for (; i < frames && *ppMessages != nullptr; ++i, ppMessages++)
   {

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

      backtrace_symbol_parse(strSymbolName, strAddress, pmessage, ppui[i]);

      string strLine;

      strLine.format("%02d : %s : %s\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str());

      strCallstack += strLine;

   }

   return strCallstack;

}


namespace acme
{


   void node::defer_update_callstack()
   {


   }


   string node::get_callstack(const ::scoped_string & strFormat, i32 iSkip, void *caller_address, int iCount)
   {

      const int iMaximumFramesToCapture = 100;

      void * stack[iMaximumFramesToCapture];

      auto frames = ::backtrace(stack, iMaximumFramesToCapture);

      string str = _ansi_stack_trace(stack, minimum(iCount, frames), strFormat, iSkip);

      return str;

   }


} // namespace acme



