// Recreated by camilo on 2026-10-11 07:47 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "acme/exception/call_stack.h"

// With get_callstatck from windows to windows_common by camilo on 2022-03-11 13:59 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "acme/parallelization/synchronous_lock.h"
//#include <dbghelp.h>
//#pragma comment(lib, "dbghelp.lib")


bool g_bInitializeCallstack = false;


CLASS_DECL_ACME void defer_initialize_callstack()
{

   critical_section_lock criticalsectionlock(::platform::get()->sym_dbg_help_critical_section());

   //auto process = GetCurrentProcess();

   if (!g_bInitializeCallstack)
   {

      g_bInitializeCallstack = true;

   }

}

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
//
//
//bool g_bInitializeCallstack = false;
//
//
//
////extern ::pointer< ::mutex > g_pmutexSymDbgHelp;
//
//
//CLASS_DECL_ACME void defer_initialize_callstack()
//{
//
//   critical_section_lock criticalsectionlock(::platform::get()->sym_dbg_help_critical_section());
//
//   auto process = GetCurrentProcess();
//
//   if (!g_bInitializeCallstack)
//   {
//
//      g_bInitializeCallstack = true;
//
//   }
//
//}
//
//
////string get_callstack(::particle * pparticle, const ::scoped_string & scopedstrFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
//call_stack::call_stack(const_char_pointer pszFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
//{
//
//   critical_section_lock criticalsectionlock(sym_dbg_help_critical_section());
//
//   string str;
//
//   //constexpr ::u32 TRACE_MAX_STACK_FRAMES = 99;
//
//   //void * stack[TRACE_MAX_STACK_FRAMES];
//
//   ULONG hash = 0;
//
//   m_iCount = CaptureStackBackTrace(iSkip + 1, TRACE_MAX_STACK_FRAMES, m_stack, &hash);
//
//   m_u32Hash = hash;
//
//
//   str = string_format("Stack hash: 0x%08lx\n", hash);
//
//   for (::i32 i = 0; i < numFrames; ++i)
//   {
//
//      void * moduleBaseVoid = nullptr;
//
//      RtlPcToFileHeader(stack[i], &moduleBaseVoid);
//
//      auto moduleBase = (const ::u8 *)moduleBaseVoid;
//
//      constexpr auto MODULE_BUF_SIZE = 4096U;
//
//      wchar_t modulePath[MODULE_BUF_SIZE];
//
//      const wchar_t * moduleFilename = modulePath;
//
//      if (moduleBase != nullptr)
//      {
//
//         GetModuleFileName((HMODULE)moduleBase, modulePath, MODULE_BUF_SIZE);
//
//         auto strName = ::file::path(modulePath).name();
//
//         str += string_format("%02d:%s+0x%016llx\n", i, strName.c_str(), (uptr)((::u8 *)stack[i] - moduleBase));
//
//      }
//      else
//      {
//
//         str += string_format("%02d:%s+0x%016llx\n", i, moduleFilename, (uptr)stack[i]);
//
//      }
//
//   }
//
//   return ::transfer(str);
//
//}
//
//
//#endif

void call_stack::capture(::i32 iSkip, void * caller_address, ::i32 iCount)
{

   ULONG hash = 0;

   m_iCount = CaptureStackBackTrace(iSkip + 1, TRACE_MAX_STACK_FRAMES, m_stack, &hash);

   m_u32Hash = hash;

}


// 0 - most deep call stack logging
// 4 - most lite call stack logging
//::i32 g_iCallStackLevel = 4;

//e_callstack g_ecallstack = callstack_none;


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
//
//
//call_stack::~call_stack()
//{
//
//   if (m_pszCallStack != nullptr)
//   {
//
//      free((void *)m_pszCallStack);
//
//   }
//
//}


::i32 call_stack::_prepare_trace(const_char_pointer pszFormat)
{
//   str = string_format("Stack hash: 0x%08lx\n", hash);

   ::i32 iGoodSize = 256;

   for (::i32 i = 0; i < m_iCount; ++i)
   {

      void * moduleBase = nullptr;

      RtlPcToFileHeader(m_stack[i], &moduleBase);

      m_modulea[i] = moduleBase;

      if (moduleBase != nullptr)
      {

         m_u32ModulePathLength[i] = ::GetModuleFileName((HMODULE)moduleBase, m_szaModulePath[i], MODULE_BUF_SIZE);

      }
      else
      {

         wcscpy(m_szaModulePath[i], L"(unknown)");

         m_u32ModulePathLength[i] = wcslen(m_szaModulePath[i]);

      }

      iGoodSize += 64 +strlen(m_pszFormat) + m_u32ModulePathLength[i];

   }

   //for (::i32 i = 0; i < numFrames; ++i)
   //{

   //   void * moduleBaseVoid = nullptr;

   //   RtlPcToFileHeader(stack[i], &moduleBaseVoid);

   //   auto moduleBase = (const ::u8 *)moduleBaseVoid;

   //   wchar_t modulePath[MODULE_BUF_SIZE];

   //   const wchar_t * moduleFilename = modulePath;

   //   if (moduleBase != nullptr)
   //   {

   //      GetModuleFileName((HMODULE)moduleBase, modulePath, MODULE_BUF_SIZE);

   //      auto strName = ::file::path(modulePath).name();

   //      str += string_format("%02d:%s+0x%016llx\n", i, strName.c_str(), (uptr)((::u8 *)stack[i] - moduleBase));

   //   }
   //   else
   //   {

   //      str += string_format("%02d:%s+0x%016llx\n", i, moduleFilename, (uptr)stack[i]);

   //   }

   //}

   return iGoodSize;

}


const_char_pointer call_stack::_trace(::i32 iSize,const_char_pointer pszFormat)
{

   m_pszCallStack = (const_char_pointer)malloc(iSize);

   auto p = (char *)m_pszCallStack;

   //str = string_format("Stack hash: 0x%08lx\n", hash);

   sprintf(p, "Stack hash: 0x%08lx\n", m_u32Hash);

   p += strlen(p);

   //for (::i32 i = 0; i < m_iCount; ++i)
   //{

   //   void * moduleBaseVoid = nullptr;

   //   RtlPcToFileHeader(m_stack[i], &moduleBaseVoid);

   //   auto moduleBase = (const ::u8 *)moduleBaseVoid;

   //   m_modulea[i] = moduleBase;

   //}

   for (::i32 i = 0; i < m_iCount; ++i)
   {

      //void * moduleBaseVoid = nullptr;

      //RtlPcToFileHeader(stack[i], &moduleBaseVoid);

      //auto moduleBase = (const ::u8 *)moduleBaseVoid;

      //constexpr auto MODULE_BUF_SIZE = 4096U;

      //wchar_t modulePath[MODULE_BUF_SIZE];

      //const wchar_t * moduleFilename = modulePath;

      //if (moduleBase != nullptr)
      {

         //GetModuleFileName((HMODULE)moduleBase, modulePath, MODULE_BUF_SIZE);

         //auto strName = ::file::path(modulePath).name();
#ifdef WINDOWS
         sprintf(p, "%02d:%S+0x%016llx\n", i, m_szaModulePath[i], (uptr)((::u8 *)m_stack[i] - (::u8 *)m_modulea[i]));
#else
         sprintf(p, "%02d:%s+0x%016llx\n", i, m_szaModulePath[i], (uptr)((::u8 *)m_stack[i] - (::u8 *)m_modulea[i]));
#endif
         p += strlen(p);
      }
      //else
      //{

      //   str += string_format("%02d:%s+0x%016llx\n", i, moduleFilename, (uptr)stack[i]);

      //}

   }

   //return ::transfer(str);


   //if (iSkip >= 0)
   //{

   //   iSkip++;

   //}

   //const ::scoped_string & scopedstr;

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

   return m_pszCallStack;

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
