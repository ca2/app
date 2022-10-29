// Created by camilo on 2022-02-11 09:27 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/primitive/function.h"
#include "acme/primitive/primitive/memory.h"
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")


#ifdef WINDOWS


bool g_bInitializeCallstack = false;


//CLASS_DECL_ACME class ::exception_engine& exception_engine();


#endif


//extern ::pointer < ::mutex > g_pmutexSymDbgHelp;


CLASS_DECL_ACME void defer_initialize_callstack()
{

   critical_section_lock synchronouslock(sym_dbg_help_critical_section());

   auto process = GetCurrentProcess();

   if (!g_bInitializeCallstack)
   {

	  g_bInitializeCallstack = true;

	  SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

	  SymInitialize(process, NULL, TRUE);

   }
   else
   {

	  SymRefreshModuleList(process);

   }

}


string get_callstack(const char* pszFormat, i32 iSkip, void * caller_address, int iCount)
{

   critical_section_lock synchronouslock(sym_dbg_help_critical_section());

   string strCallstack;

   const size_t iMaximumFramesToCapture = 62; // does not support more then 62 frames of stackbacktrace

   void * stack[iMaximumFramesToCapture];

   defer_initialize_callstack();

   auto frames = CaptureStackBackTrace(0, iMaximumFramesToCapture, stack, NULL);

   int iMaximumNameLength = 1024;

   memory memory(sizeof(SYMBOL_INFO) + iMaximumNameLength * sizeof(char));

   SYMBOL_INFO* psymbolinfo = (SYMBOL_INFO *) memory.get_data();

   psymbolinfo->MaxNameLen = iMaximumNameLength;

   psymbolinfo->SizeOfStruct = sizeof(SYMBOL_INFO);

   auto process = GetCurrentProcess();

   for (auto i = 0; i < frames; ++i) 
   {
	
	  SymFromAddr(process, (DWORD64)(stack[i]), 0, psymbolinfo);

	  string strLine;

	  strLine.format("%02d : %" PRIdPTR " : %s\n", frames - i - 1, psymbolinfo->Address, psymbolinfo->Name);

	  strCallstack += strLine;

   }

   return ::move(strCallstack);

}


//   if (iSkip >= 0)
//   {
//
//      iSkip++;
//
//   }
//
//   const char * psz;
//
//   synchronous_lock synchronouslock(::exception_engine().mutex());
//
//#if defined(LINUX)
//
//   psz = strdup(::exception_engine().xxxstack_trace(iSkip, m_caller_address));
//
//#elif defined(__APPLE__)
//   
//   ::exception_engine().xxxstack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount);
//   
//   psz = _strdup(::exception_engine()._strS);
//
//#else
//
//   ::exception_engine().xxxstack_trace(iSkip, m_pszFormat, m_iCount);
//
//   psz = _strdup(::exception_engine()._strS);
//
//#endif
//
//   return psz;
//
//}

