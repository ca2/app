// With get_callstatck from windows to windows_common by camilo on 2022-03-11 13:59 <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
//#include <dbghelp.h>
//#pragma comment(lib, "dbghelp.lib")


#ifdef WINDOWS_DESKTOP


bool g_bInitializeCallstack = false;



//extern ::pointer< ::mutex > g_pmutexSymDbgHelp;


CLASS_DECL_ACME void defer_initialize_callstack()
{

   critical_section_lock criticalsectionlock(sym_dbg_help_critical_section());

   auto process = GetCurrentProcess();

   if (!g_bInitializeCallstack)
   {

      g_bInitializeCallstack = true;

   }

}


string get_callstack(const ::scoped_string & scopedstrFormat, i32 iSkip, void * caller_address, int iCount)
{

   critical_section_lock criticalsectionlock(sym_dbg_help_critical_section());

   string str;

   constexpr ::u32 TRACE_MAX_STACK_FRAMES = 99;
   
   void * stack[TRACE_MAX_STACK_FRAMES];
   
   ULONG hash;
   
   const int numFrames = CaptureStackBackTrace(iSkip + 1, TRACE_MAX_STACK_FRAMES, stack, &hash);

   str = string_format("Stack hash: 0x%08lx\n", hash);

   for (int i = 0; i < numFrames; ++i) 
   {

      void * moduleBaseVoid = nullptr;

      RtlPcToFileHeader(stack[i], &moduleBaseVoid);

      auto moduleBase = (const unsigned char *)moduleBaseVoid;

      constexpr auto MODULE_BUF_SIZE = 4096U;

      wchar_t modulePath[MODULE_BUF_SIZE];

      const wchar_t * moduleFilename = modulePath;

      if (moduleBase != nullptr) 
      {

         GetModuleFileName((HMODULE)moduleBase, modulePath, MODULE_BUF_SIZE);

         auto strName = ::file::path(modulePath).name();

         str += string_format("%02d:%s+0x%016llx\n", i, strName.c_str(), (uptr)((unsigned char *)stack[i] - moduleBase));

      }
      else
      {
      
         str += string_format("%02d:%s+0x%016llx\n", i, moduleFilename, (uptr)stack[i]);

      }

   }
   
   return ::move(str);

}


#endif



