// Created by camilo on 2022-02-11 09:27 PM <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "acme/operating_system/windows/windows_xp_compat.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/platform/_synchronization.h"
#include "acme/platform/node.h"


#include "acme/_operating_system.h"


#include <TlHelp32.h>
#include <DbgHelp.h>


//#include "acme/parallelization/mutex.h"
//#include "acme/parallelization/synchronous_lock.h"
////#include "acme/prototype/prototype/function.h"
//#include "acme/prototype/prototype/memory.h"
//#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
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
//
//
//::critical_section g_criticalsectionSymDbgHelp;
//
//
//::critical_section * ::platform::get()->sym_dbg_help_critical_section() { return &g_criticalsectionSymDbgHelp; }
//

// Raw traces intentionally avoid DbgHelp and any debug-information translation.
#ifndef CA2_RAW_STACK_TRACE
#if defined(__REACTOS__)
#define CA2_RAW_STACK_TRACE 1
#else
#define CA2_RAW_STACK_TRACE 0
#endif
#endif

namespace platform
{


   ::i32 node::get_call_stack_default_frame_count()
   {

      return 62;

   }


   void node::defer_update_call_stack()
   {

      critical_section_lock synchronouslock(::platform::get()->sym_dbg_help_critical_section());

      auto process = GetCurrentProcess();

      if (!m_bCallStackInitialized)
      {

         m_bCallStackInitialized = false;

         SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

#if defined(WINDOWS_XP)
         m_bCallStackInitialized = SymInitialize(process, NULL, TRUE) != FALSE;
         if (!m_bCallStackInitialized)
            return;
#else
         SymInitialize(process, NULL, TRUE);
#endif

      }
      else if(m_bUpdateCallStack)
      {

#if defined(WINDOWS_XP)
         if (!ca2_xp_refresh_module_list(process))
         {
            m_bCallStackInitialized = false;
            return; // Retry initialization rather than using an invalid session.
         }
#else
         SymRefreshModuleList(process);
#endif

      }

      m_bUpdateCallStack = false;

   }


   void node::get_call_stack_frames(void** stack, ::i32& frame_count)
   {

      critical_section_lock synchronouslock(::platform::get()->sym_dbg_help_critical_section());

      string strCallstack;

      frame_count = ::minimum(62, frame_count); // does not support more then 62 frames of stackbacktrace

#if !CA2_RAW_STACK_TRACE
      defer_update_call_stack();
#endif

      frame_count = CaptureStackBackTrace(0, frame_count, stack, NULL);

      //return get_call_stack_trace(stack, frame_count, scopedstrFormat, iSkip, caller_address, iCount);

   }



   string node::get_call_stack_trace(const ::scoped_string& scopedstrFormat, ::i32 iSkip, void* caller_address, ::i32 iCount)
   {

      critical_section_lock synchronouslock(::platform::get()->sym_dbg_help_critical_section());

      const ::i32 iMaximumFrameCount = 62; // does not support more then 62 frames of stackbacktrace

      void* stack[iMaximumFrameCount];

      ::i32 frame_count = iMaximumFrameCount;

      get_call_stack_frames(stack, frame_count);

      return get_call_stack_trace(stack, frame_count, scopedstrFormat, iSkip, caller_address, iCount);

   }


   string node::get_call_stack_trace(void ** stack, ::i32 frame_count, const ::scoped_string & scopedstrFormat, ::i32 iSkip, void* caller_address, ::i32 iCount)
   {

      critical_section_lock synchronouslock(::platform::get()->sym_dbg_help_critical_section());

      string strCallstack;

      //const size_t iMaximumFramesToCapture = 62; // does not support more then 62 frames of stackbacktrace

      ///void* stack[iMaximumFramesToCapture];

      //defer_update_call_stack();

      //auto frames = CaptureStackBackTrace(0, iMaximumFramesToCapture, stack, NULL);

#if CA2_RAW_STACK_TRACE
      // Keep addresses useful even when no module information is available.
      strCallstack = "CA2_RAW_STACK_TRACE (untranslated; module offsets are RVAs)\n";
      const DWORD savedError = GetLastError();
      const ::i32 first = iSkip > 0 ? ::minimum(iSkip, frame_count) : 0;
      const ::i32 last = iCount >= 0 ? first + ::minimum(iCount, frame_count - first) : frame_count;
      for (::i32 i = first; i < last; ++i)
      {
         MEMORY_BASIC_INFORMATION region{};
         HMODULE module = nullptr;
         char modulePath[32768] = {};
         if (VirtualQuery(stack[i], &region, sizeof(region)) && region.Type == MEM_IMAGE)
         {
            module = static_cast<HMODULE>(region.AllocationBase);
            const DWORD length = GetModuleFileNameA(module, modulePath, sizeof(modulePath));
            if (!length || length >= sizeof(modulePath))
               modulePath[0] = 0;
         }
         ::string line;
         if (module)
         {
            line.formatf("#%02d pc=%p base=%p rva=0x%llx module=%s\n",
               i - first, stack[i], static_cast<void *>(module),
               static_cast<unsigned long long>(reinterpret_cast<uptr>(stack[i]) - reinterpret_cast<uptr>(module)),
               modulePath[0] ? modulePath : "<unknown>");
         }
         else
         {
            line.formatf("#%02d pc=%p module=<unknown>\n", i - first, stack[i]);
         }
         strCallstack += line;
      }
      SetLastError(savedError);
      return strCallstack;
#else
      ::i32 iMaximumNameLength = 1024;

      memory memory(sizeof(SYMBOL_INFO) + iMaximumNameLength * sizeof(::i8));

      SYMBOL_INFO* psymbolinfo = (SYMBOL_INFO*)memory.data();

      psymbolinfo->MaxNameLen = iMaximumNameLength;

      psymbolinfo->SizeOfStruct = sizeof(SYMBOL_INFO);

      auto process = GetCurrentProcess();

      ::string_array_base stra;

      character_count maximum_line_length = 0;

      for (auto i = 0; i < frame_count; ++i)
      {

         IMAGEHLP_LINE64 imagehlp_line{ .SizeOfStruct = sizeof(IMAGEHLP_LINE64) };

         DWORD dwDisplacement = 0;

         SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &dwDisplacement, &imagehlp_line);

         ::string strLine;

         strLine.formatf("%s (%d)", imagehlp_line.FileName, imagehlp_line.LineNumber);

         if (strLine.length() > maximum_line_length)
         {

            maximum_line_length = strLine.length();

         }

         stra.add(strLine);

      }

      for (auto i = 0; i < frame_count; ++i)
      {

         SymFromAddr(process, (DWORD64)(stack[i]), 0, psymbolinfo);

         IMAGEHLP_LINE imagehlp_line{.SizeOfStruct =sizeof(IMAGEHLP_LINE)};

         ::string strPrefix;

         strPrefix = stra[i];

         ::string strSpacing;

         strSpacing.assign(' ', maximum_line_length - strPrefix.length());

         strPrefix += strSpacing;

         ::string strLine;

         strLine.formatf("%s : %02d : %s\n", strPrefix.c_str(), frame_count - i - 1, psymbolinfo->Name);

         strCallstack += strLine;

      }

      return ::transfer(strCallstack);
#endif

   }


} // namespace platform



