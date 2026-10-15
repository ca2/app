// Created by camilo on 2023-11-22 09:39 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "call_stack.h"
#include "acme/platform/node.h"

// 0 - most deep call stack logging?!?!?
// 4 - most lite call stack logging?!?!?
//::i32 g_iCallStackLevel = 4;


#ifdef WINDOWS
CLASS_DECL_ACME ::string call_stack_default_format()
#else
::string call_stack_default_format()
#endif
{

   return "%f(%l) %s\n";

}


//CLASS_DECL_ACME void get_call_stack_frames(void** stack, ::i32 & frame_count)
//{
//
//   this->::system()->node()->get_call_stack_frames(stack, frame_count);
//
//}
//
//
//CLASS_DECL_ACME ::string get_call_stack_trace(void ** stack, ::i32 c, const_char_pointer pszFormat)
//{
//
//   return this->::system()->node()->get_call_stack_trace(stack, c, pszFormat);
//
//}





//#include "acme/exception/call_stack.h"
//
//// With get_callstatck from windows to windows_common by camilo on 2022-03-11 13:59 <3ThomasBorregaardSorensen!!
//#include "platform.h"
//#include "acme/parallelization/synchronous_lock.h"
////#include <dbghelp.h>
////#pragma comment(lib, "dbghelp.lib")


//void call_stack::capture(::i32 iSkip)
//{
//   
//   ULONG hash = 0;
//
//   m_iCount = CaptureStackBackTrace(iSkip + 1, TRACE_MAX_STACK_FRAMES, m_stack, &hash);
//
//   m_u32Hash = hash;
//
//}
//

//#ifdef WINDOWS_


//bool g_bInitializeCallstack = false;



//extern ::pointer< ::mutex > g_pmutexSymDbgHelp;


CLASS_DECL_ACME void defer_initialize_callstack();


call_stack::call_stack() :
   m_pszFormat(nullptr),
   m_iCount(0),
   m_caller_address(nullptr)
{


}


//string get_callstack(::particle * pparticle, const ::scoped_string & scopedstrFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
//call_stack::call_stack(const_char_pointer pszFormat, ::i32 iSkip, void * caller_address, ::i32 iCount) :
//   m_pszFormat(pszFormat),
//   m_iCount(iCount),
//   m_caller_address(caller_address)
//{
//
//   capture(iSkip);
//   m_pszCallStack = get_dup(m_pszFormat, iSkip, iCount);
//   //critical_section_lock criticalsectionlock(sym_dbg_help_critical_section());
//
//   //string str;
//
//   ////constexpr ::u32 TRACE_MAX_STACK_FRAMES = 99;
//
//   ////void * stack[TRACE_MAX_STACK_FRAMES];
//
//   //ULONG hash = 0;
//
//   //m_iCount = CaptureStackBackTrace(iSkip + 1, TRACE_MAX_STACK_FRAMES, m_stack, &hash);
//
//   //m_u32Hash = hash;
//
//
//   //str = string_format("Stack hash: 0x%08lx\n", hash);
//
//   //for (::i32 i = 0; i < numFrames; ++i)
//   //{
//
//   //   void * moduleBaseVoid = nullptr;
//
//   //   RtlPcToFileHeader(stack[i], &moduleBaseVoid);
//
//   //   auto moduleBase = (const ::u8 *)moduleBaseVoid;
//
//   //   constexpr auto MODULE_BUF_SIZE = 4096U;
//
//   //   wchar_t modulePath[MODULE_BUF_SIZE];
//
//   //   const wchar_t * moduleFilename = modulePath;
//
//   //   if (moduleBase != nullptr)
//   //   {
//
//   //      GetModuleFileName((HMODULE)moduleBase, modulePath, MODULE_BUF_SIZE);
//
//   //      auto strName = ::file::path(modulePath).name();
//
//   //      str += string_format("%02d:%s+0x%016llx\n", i, strName.c_str(), (uptr)((::u8 *)stack[i] - moduleBase));
//
//   //   }
//   //   else
//   //   {
//
//   //      str += string_format("%02d:%s+0x%016llx\n", i, moduleFilename, (uptr)stack[i]);
//
//   //   }
//
//   //}
//
//   //return ::transfer(str);
//
//}
//

//#endif




//e_callstack g_ecallstack = callstack_none;

//
//call_stack::call_stack(const_char_pointer pszFormat, ::i32 iSkip, void * address, ::i32 iCount) :
//   m_pszFormat(pszFormat),
//   m_iCount(iCount),
//   m_caller_address(address)
//{
//
//   m_pszCallStack = nullptr;
//
//   if (iSkip == CALLSTACK_DEFAULT_SKIP_TRIGGER)
//   {
//
//      iSkip = 1;
//
//   }
//   else if (iSkip >= 0)
//   {
//
//      iSkip += 1;
//
//   }
//
//   m_pszCallStack = call_stack::get_dup(m_pszFormat, iSkip, iCount);
//
//}


call_stack::~call_stack()
{

   if (m_pszCallStack != nullptr)
   {

      free((void *)m_pszCallStack);

   }

}


const_char_pointer call_stack::trace(const_char_pointer pszFormat)
{

   if (m_pszCallStack)
   {
      
      return m_pszCallStack;

   }

   auto iSize = _prepare_trace(pszFormat);
    
   m_pszCallStack = _trace(iSize, pszFormat);

   return m_pszCallStack;
   //}

//   if (iSkip >= 0)
//   {
//
//      iSkip++;
//
//   }
//
//   //const ::scoped_string & scopedstr;
//
//   synchronous_lock synchronouslock(::exception_engine().mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//#if defined(LINUX)
//
//   psz = strdup(::exception_engine().xxxstack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount));
//
//#elif defined(MACOS)
//
//   psz = strdup(::exception_engine().xxxstack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount));
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
}

//const_char_pointer call_stack::stack_trace() const
//{
//
//   return m_pszCallStack;
//
//}

//
//string get_call_stack(particle * pparticle, const_char_pointer pszFormat = call_stack_default_format(), ::i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, ::i32 iCount = -1)
//{
//
//   if (iSkip >= 0)
//   {
//
//      iSkip++;
//
//   }
//
//   auto pcallstack = allocateø callstack(scopedstrFormat, (::i32)iSkip, caller_address, (::i32)iCount);
//
//   return pcallstack;
//
//}

//
//CLASS_DECL_ACME::pointer<callstack>get_callstack(e_callstack ecallstack, ::i32 iCallStackAddUp)
//{
//
//   iCallStackAddUp++;
//
//   switch (ecallstack)
//   {
//   case callstack_fork_global:
//      return get_callstack("%s - %l\n", iCallStackAddUp, nullptr, 1);
//   default:
//      return get_callstack();
//   }
//
//}
//
//
//CLASS_DECL_ACME void set_callstack_mask(cflag < e_callstack > ecallstack)
//{
//
//   g_ecallstack = ecallstack;
//
//}
//
//
//CLASS_DECL_ACME e_callstack get_callstack_mask()
//{
//
//   return g_ecallstack;
//
//}


//CLASS_DECL_ACME bool is_callstack_enabled(e_callstack ecallstack)
//{
//
//   return g_ecallstack & ecallstack;
//
//}
