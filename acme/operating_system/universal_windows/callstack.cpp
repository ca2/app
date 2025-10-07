// From windows/callstack.cpp by camilo on 2023-02-11 00:57 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/platform/_synchronization.h"
#include "acme/platform/node.h"


#include "acme/_operating_system.h"


#include <TlHelp32.h>
#include <DbgHelp.h>



//#include <TlHelp32.h>
//#include <DbgHelp.h>
//
//
////#include "acme/parallelization/mutex.h"
////#include "acme/parallelization/synchronous_lock.h"
//////#include "acme/prototype/prototype/function.h"
////#include "acme/prototype/prototype/memory.h"
////#include <dbghelp.h>
////#pragma comment(lib, "dbghelp.lib")
////
////
////#ifdef WINDOWS
////
////
////bool g_bInitializeCallstack = false;
////
////
//////CLASS_DECL_ACME class ::exception_engine& exception_engine();
////
////
////#endif
////
////
//////extern ::pointer < ::mutex > g_pmutexSymDbgHelp;
////
////
////
////
//////   if (iSkip >= 0)
//////   {
//////
//////      iSkip++;
//////
//////   }
//////
//////   const ::scoped_string & scopedstr;
//////
//////   synchronous_lock synchronouslock(::exception_engine().mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//////
//////#if defined(LINUX)
//////
//////   psz = strdup(::exception_engine().xxxstack_trace(iSkip, m_caller_address));
//////
//////#elif defined(__APPLE__)
//////   
//////   ::exception_engine().xxxstack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount);
//////   
//////   psz = _strdup(::exception_engine()._strS);
//////
//////#else
//////
//////   ::exception_engine().xxxstack_trace(iSkip, m_pszFormat, m_iCount);
//////
//////   psz = _strdup(::exception_engine()._strS);
//////
//////#endif
//////
//////   return psz;
//////
//////}
////
//
//
//::critical_section g_criticalsectionSymDbgHelp;
//
//
//::critical_section * sym_dbg_help_critical_section() { return &g_criticalsectionSymDbgHelp; }

namespace platform
{


   //void node::defer_update_callstack()
   //{

   //   //critical_section_lock synchronouslock(sym_dbg_help_critical_section());

   //   //auto process = GetCurrentProcess();

   //   //if (!m_bCallstackInitialized)
   //   //{

   //   //   m_bCallstackInitialized = false;

   //   //   SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

   //   //   SymInitialize(process, NULL, TRUE);

   //   //}
   //   //else if (m_bUpdateCallstack)
   //   //{

   //   //   SymRefreshModuleList(process);

   //   //}

   //   //m_bUpdateCallstack = false;

   //}


   //string node::get_callstack(const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
   //{

   //   return {};

   //   //critical_section_lock synchronouslock(sym_dbg_help_critical_section());

   //   //string strCallstack;

   //   //const size_t iMaximumFramesToCapture = 62; // does not support more then 62 frames of stackbacktrace

   //   //void * stack[iMaximumFramesToCapture];

   //   //defer_update_callstack();

   //   //auto frames = CaptureStackBackTrace(0, iMaximumFramesToCapture, stack, NULL);

   //   //int iMaximumNameLength = 1024;

   //   //memory memory(sizeof(SYMBOL_INFO) + iMaximumNameLength * sizeof(char));

   //   //SYMBOL_INFO * psymbolinfo = (SYMBOL_INFO *)memory.data();

   //   //psymbolinfo->MaxNameLen = iMaximumNameLength;

   //   //psymbolinfo->SizeOfStruct = sizeof(SYMBOL_INFO);

   //   //auto process = GetCurrentProcess();

   //   //for (auto i = 0; i < frames; ++i)
   //   //{

   //   //   SymFromAddr(process, (DWORD64)(stack[i]), 0, psymbolinfo);

   //   //   string strLine;

   //   //   strLine.formatf("%02d : %" PRIdPTR " : %s\n", frames - i - 1, psymbolinfo->Address, psymbolinfo->Name);

   //   //   strCallstack += strLine;

   //   //}

   //   //return ::transfer(strCallstack);

   //}

   // Created by camilo on 2022-02-11 09:27 PM <3ThomasBorregaardSorensen!!

//#include "acme/parallelization/mutex.h"
//#include "acme/parallelization/synchronous_lock.h"
////#include "acme/prototype/prototype/function.h"
//#include "acme/prototype/prototype/memory.h"
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
////   synchronous_lock synchronouslock(::exception_engine().mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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



      int node::get_call_stack_default_frame_count()
      {

         return 62;

      }


      void node::defer_update_call_stack()
      {

         critical_section_lock synchronouslock(sym_dbg_help_critical_section());

         auto process = GetCurrentProcess();

         if (!m_bCallStackInitialized)
         {

            m_bCallStackInitialized = false;

            //SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

            //SymInitialize(process, NULL, TRUE);

         }
         else if (m_bUpdateCallStack)
         {

            //SymRefreshModuleList(process);

         }

         m_bUpdateCallStack = false;

      }


      void node::get_call_stack_frames(void ** stack, int & frame_count)
      {

         critical_section_lock synchronouslock(sym_dbg_help_critical_section());

         string strCallstack;

         frame_count = ::minimum(62, frame_count); // does not support more then 62 frames of stackbacktrace

         defer_update_call_stack();

         frame_count = CaptureStackBackTrace(0, frame_count, stack, NULL);

         //return get_call_stack_trace(stack, frame_count, scopedstrFormat, iSkip, caller_address, iCount);

      }



      string node::get_call_stack_trace(const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
      {

         critical_section_lock synchronouslock(sym_dbg_help_critical_section());

         const int iMaximumFrameCount = 62; // does not support more then 62 frames of stackbacktrace

         void * stack[iMaximumFrameCount];

         int frame_count = iMaximumFrameCount;

         get_call_stack_frames(stack, frame_count);

         return get_call_stack_trace(stack, frame_count, scopedstrFormat, iSkip, caller_address, iCount);

      }


      string node::get_call_stack_trace(void ** stack, int frame_count, const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
      {

         critical_section_lock synchronouslock(sym_dbg_help_critical_section());

         string strCallstack;

         //const size_t iMaximumFramesToCapture = 62; // does not support more then 62 frames of stackbacktrace

         ///void* stack[iMaximumFramesToCapture];

         //defer_update_call_stack();

         //auto frames = CaptureStackBackTrace(0, iMaximumFramesToCapture, stack, NULL);

         int iMaximumNameLength = 1024;

         //memory memory(sizeof(SYMBOL_INFO) + iMaximumNameLength * sizeof(char));

         //SYMBOL_INFO * psymbolinfo = (SYMBOL_INFO *)memory.data();

         //psymbolinfo->MaxNameLen = iMaximumNameLength;

         //psymbolinfo->SizeOfStruct = sizeof(SYMBOL_INFO);

         auto process = GetCurrentProcess();

         ::string_array_base stra;

         character_count maximum_line_length = 0;

         //for (auto i = 0; i < frame_count; ++i)
         //{

         //   IMAGEHLP_LINE imagehlp_line{ .SizeOfStruct = sizeof(IMAGEHLP_LINE) };

         //   DWORD dwDisplacement = 0;

         //   SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &dwDisplacement, &imagehlp_line);

         //   ::string strLine;

         //   strLine.formatf("%s (%d)", imagehlp_line.FileName, imagehlp_line.LineNumber);

         //   if (strLine.length() > maximum_line_length)
         //   {

         //      maximum_line_length = strLine.length();

         //   }

         //   stra.add(strLine);

         //}

         //for (auto i = 0; i < frame_count; ++i)
         //{

         //   SymFromAddr(process, (DWORD64)(stack[i]), 0, psymbolinfo);

         //   IMAGEHLP_LINE imagehlp_line{ .SizeOfStruct = sizeof(IMAGEHLP_LINE) };

         //   ::string strPrefix;

         //   strPrefix = stra[i];

         //   ::string strSpacing;

         //   strSpacing.assign(' ', maximum_line_length - strPrefix.length());

         //   strPrefix += strSpacing;

         //   ::string strLine;

         //   strLine.formatf("%s : %02d : %s\n", strPrefix.c_str(), frame_count - i - 1, psymbolinfo->Name);

         //   strCallstack += strLine;

         //}

         return ::transfer(strCallstack);

      }



} // namespace platform



