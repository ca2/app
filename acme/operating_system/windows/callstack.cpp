// Created by camilo on 2022-02-11 09:27 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/platform/_synchronization.h"
#include "acme/platform/node.h"


#include "acme/_operating_system.h"


#include <TlHelp32.h>
#include <DbgHelp.h>


//#include "acme/parallelization/mutex.h"
//#include "acme/parallelization/synchronous_lock.h"
////#include "acme/primitive/primitive/function.h"
//#include "acme/primitive/primitive/memory.h"
//#include <dbghelp.h>
//#pragma comment(lib, "dbghelp.lib")
//
//
//#ifdef WINDOWS
//
//
//bool g_bInitializeCallstack = false;
//
//
////CLASS_DECL_ACME class ::exception_engine& exception_engine();
//
//
//#endif
//
//
////extern ::pointer < ::mutex > g_pmutexSymDbgHelp;
//
//
//
//
////   if (iSkip >= 0)
////   {
////
////      iSkip++;
////
////   }
////
////   const ::scoped_string & scopedstr;
////
////   synchronous_lock synchronouslock(::exception_engine().mutex());
////
////#if defined(LINUX)
////
////   psz = strdup(::exception_engine().xxxstack_trace(iSkip, m_caller_address));
////
////#elif defined(__APPLE__)
////   
////   ::exception_engine().xxxstack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount);
////   
////   psz = _strdup(::exception_engine()._strS);
////
////#else
////
////   ::exception_engine().xxxstack_trace(iSkip, m_pszFormat, m_iCount);
////
////   psz = _strdup(::exception_engine()._strS);
////
////#endif
////
////   return psz;
////
////}
//


::critical_section g_criticalsectionSymDbgHelp;


::critical_section * sym_dbg_help_critical_section() { return &g_criticalsectionSymDbgHelp; }


namespace acme
{


   void node::defer_update_callstack()
   {

      critical_section_lock synchronouslock(sym_dbg_help_critical_section());

      auto process = GetCurrentProcess();

      if (!m_bCallstackInitialized)
      {

         m_bCallstackInitialized = false;

         SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

         SymInitialize(process, NULL, TRUE);

      }
      else if(m_bUpdateCallstack)
      {

         SymRefreshModuleList(process);

      }

      m_bUpdateCallstack = false;

   }


   string node::get_callstack(const ::scoped_string & scopedstrFormat, i32 iSkip, void* caller_address, int iCount)
   {

      critical_section_lock synchronouslock(sym_dbg_help_critical_section());

      string strCallstack;

      const size_t iMaximumFramesToCapture = 62; // does not support more then 62 frames of stackbacktrace

      void* stack[iMaximumFramesToCapture];

      defer_update_callstack();

      auto frames = CaptureStackBackTrace(0, iMaximumFramesToCapture, stack, NULL);

      int iMaximumNameLength = 1024;

      memory memory(sizeof(SYMBOL_INFO) + iMaximumNameLength * sizeof(char));

      SYMBOL_INFO* psymbolinfo = (SYMBOL_INFO*)memory.data();

      psymbolinfo->MaxNameLen = iMaximumNameLength;

      psymbolinfo->SizeOfStruct = sizeof(SYMBOL_INFO);

      auto process = GetCurrentProcess();

      ::string_array stra;

      strsize maximum_line_length = 0;

      for (auto i = 0; i < frames; ++i)
      {

         IMAGEHLP_LINE imagehlp_line{ .SizeOfStruct = sizeof(IMAGEHLP_LINE) };

         DWORD dwDisplacement = 0;

         SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &dwDisplacement, &imagehlp_line);

         ::string strLine;

         strLine.format("%s (%d)", imagehlp_line.FileName, imagehlp_line.LineNumber);

         if (strLine.length() > maximum_line_length)
         {

            maximum_line_length = strLine.length();

         }

         stra.add(strLine);

      }

      for (auto i = 0; i < frames; ++i)
      {

         SymFromAddr(process, (DWORD64)(stack[i]), 0, psymbolinfo);

         IMAGEHLP_LINE imagehlp_line{.SizeOfStruct =sizeof(IMAGEHLP_LINE)};

         ::string strPrefix;

         strPrefix = stra[i];

         ::string strSpacing;

         strSpacing.assign(' ', maximum_line_length - strPrefix.length());

         strPrefix += strSpacing;

         ::string strLine;

         strLine.format("%s : %02d : %s\n", strPrefix.c_str(), frames - i - 1, psymbolinfo->Name);

         strCallstack += strLine;

      }

      return ::transfer(strCallstack);

   }


} // namespace acme



