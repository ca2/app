#include "framework.h"
#include "callstack.h"

#undef Context


#include <malloc.h>
#define WORK_AROUND_SRCLINE_BUG

#pragma warning(disable: 4091)
#include <ImageHlp.h>





// The following is defined for x86 (XP and higher), x64 and IA64:
#define GET_CURRENT_CONTEXT(pc, contextFlags) \
   do { \
   __memset(pc, 0, sizeof(CONTEXT)); \
   pc->ContextFlags = contextFlags; \
   RtlCaptureContext(pc); \
   } while(0);







HANDLE SymGetProcessHandle()
{

   return GetCurrentProcess();

}



bool engine_get_line_from_address(HANDLE hprocess, OS_DWORD uiAddress, ::u32 * puiDisplacement, OS_IMAGEHLP_LINE * pline)
{

#ifdef WORK_AROUND_SRCLINE_BUG
   // "Debugging Applications" John Robbins
   // The problem is that the symbol callstack finds only those source
   // line addresses (after the first lookup) that fall exactly on
   // a zero displacement. I'll walk backward 100 bytes to
   // find the line and return the proper displacement.
   DWORD dwDisplacement = 0;

   while (!OS_SymGetLineFromAddr(hprocess, uiAddress - dwDisplacement, &dwDisplacement, pline))
   {

      if (100 == ++dwDisplacement)
      {

         return false;

      }

   }

   // "Debugging Applications" John Robbins
   // I found the line, and the source line information is correct, so
   // change the displacement if I had to search backward to find the source line.
   if (puiDisplacement)
   {

      *puiDisplacement = dwDisplacement;

   }

   return true;

#else

   return 0 != OS_SymGetLineFromAddr(hprocess, uiAddress, (DWORD *)puiDisplacement, pline);

#endif

}




index engine_fileline(OS_DWORD dwAddress, char * psz, int nCount, u32 * pline, u32 * pdisplacement = 0)
{

   OS_IMAGEHLP_LINE img_line = {};

   img_line.SizeOfStruct = sizeof(OS_IMAGEHLP_LINE);

   HANDLE hprocess = SymGetProcessHandle();

   ::u32 displacement = 0;

   if (!engine_get_line_from_address(hprocess, dwAddress, &displacement, &img_line))
   {

      return 0;

   }

   if (pdisplacement)
   {

      *pdisplacement = displacement;

   }

   if (pline)
   {

      *pline = img_line.LineNumber;

   }

   if (psz)
   {

      ansi_count_copy(psz, img_line.FileName, nCount);

   }

   return ansi_length(img_line.FileName);

}


size_t engine_symbol(char * sz, int n, OS_DWORD * pdisplacement, OS_DWORD dwAddress)
{

   byte symbol[4096];
   OS_PIMAGEHLP_SYMBOL pSym = (OS_PIMAGEHLP_SYMBOL)&symbol;
   __memset(pSym, 0, sizeof(symbol));
   pSym->SizeOfStruct = sizeof(OS_IMAGEHLP_SYMBOL);
   pSym->MaxNameLength = sizeof(symbol) - sizeof(OS_IMAGEHLP_SYMBOL);

   HANDLE hprocess = SymGetProcessHandle();
   OS_DWORD displacement = 0;
   int r = OS_SymGetSymFromAddr(hprocess, dwAddress, &displacement, pSym);
   if (!r) return 0;
   if (pdisplacement)
      *pdisplacement = displacement;

   strncpy_s(sz, n, pSym->Name, n);

   return strlen(sz);
}

#define USED_CONTEXT_FLAGS CONTEXT_FULL

//#include <tlhelp32.h>


// #ifdef VERIFY
// #undef VERIFY
// #endif // VERIFY

// #ifdef __DEBUG
// #define VERIFY(x) ASSERT(x)
// #else //__DEBUG
// #define VERIFY(x) (x)
// #endif //!__DEBUG


// #ifdef __DEBUG
// //#if 1
// // #define SYM_ENGINE_TRACE_SPIN_COUNT
// #endif //__DEBUG

int_bool __stdcall engine_ReadProcessMemory(HANDLE      hProcess,
   DWORD64     qwBaseAddress,
   PVOID       pBuffer,

   ::u32       nSize,
   LPDWORD     pNumberOfBytesRead

);



//#ifdef AMD64

/*typedef
BOOL
(__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)(
_In_ HANDLE hProcess,
_In_ DWORD64 qwBaseAddress,
_Out_writes_bytes_(nSize) PVOID pBuffer,

_In_ u32 nSize,
_Out_ LPDWORD pNumberOfBytesRead

);*/


int_bool __stdcall engine_ReadProcessMemory(
   HANDLE      hProcess,
   DWORD64     qwBaseAddress,
   PVOID       pBuffer,

   ::u32       nSize,
   LPDWORD     pNumberOfBytesRead

)
{

   SIZE_T size = 0;

   if (!ReadProcessMemory(hProcess, (const void *)qwBaseAddress, (LPVOID)pBuffer, nSize, &size))

   {

      return FALSE;

   }
   *pNumberOfBytesRead = (u32)size;


   return TRUE;

}


#ifndef FAST_STACK_TRACE

int_bool __stdcall engine_ReadProcessMemory32(HANDLE hProcess, ::u32 qwBaseAddress, PVOID pBuffer, ::u32 nSize, LPDWORD lpNumberOfBytesRead)

{

   SIZE_T size = 0;

   if (!ReadProcessMemory(hProcess, (const void *)qwBaseAddress, (LPVOID)pBuffer, nSize, &size))

      return FALSE;

   *pNumberOfBytesRead = (u32)size;


   return TRUE;

}

#endif

/*
#else
int_bool __stdcall My_ReadProcessMemory (HANDLE, const void * pBaseAddress, LPVOID lpBuffer, u32 nSize, SIZE_T * lpNumberOfBytesRead)

{
return ReadProcessMemory(GetCurrentProcess(), pBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead) != FALSE;

}
#endif
*/

namespace windows
{

   critical_section callstack::g_cs;

   callstack::callstack(const char * pszFormat, i32 iSkip, void * caller_address, int iCount):
      m_iSkip(iSkip),
      m_iCount(iCount),
      m_bOk(false),
      m_bInit(false)
   {

      m_pszFormat = pszFormat;
      m_caller_address = caller_address;

      m_iHa = 0;
      m_iMa = 0;
      xxf_zero(m_szaModule);

   }

   callstack::~callstack()
   {

      clear();

   }


   size_t callstack::module(char * psz, int nCount)
   {

      if (!check())
      {

         return 0;

      }

      HANDLE hprocess = SymGetProcessHandle();

      HMODULE hmodule = (HMODULE)SymGetModuleBase64(hprocess, address());

      if (!hmodule)
      {

         return 0;


      }

      return get_module_name(hmodule, psz, nCount);

   }


   size_t callstack::symbol(char * psz, int nCount, OS_DWORD * pdisplacement)
   {

      if (!check())
         return 0;

      engine_symbol(psz, nCount, pdisplacement, address());

      ansi_concatenate(psz, "()");

      return strlen(psz);

   }


   index callstack::fileline(char * psz, int nCount, u32 * pline, u32 * pdisplacement)
   {

      if (!check())
      {

         return 0;

      }

      return engine_fileline(address(), psz, nCount, pline, pdisplacement);

   }


   bool callstack::stack_first(CONTEXT * pcontext, int iCount)
   {
      m_iAddressRead = 0;
#if !FAST_STACK_TRACE
      if (!pcontext || IsBadReadPtr(pcontext, sizeof(CONTEXT)))
         return false;

      if (!check())
         return false;

      __memset(&m_stackframe, 0, sizeof(m_stackframe));

      //  s_readMemoryFunction = readMemoryFunction;
      //s_readMemoryFunction_UserData = pUserData;


#ifdef AMD64
      m_stackframe.AddrPC.Offset = pcontext->Rip;
      m_stackframe.AddrPC.Mode = AddrModeFlat;
      m_stackframe.AddrStack.Offset = pcontext->Rsp;
      m_stackframe.AddrStack.Mode = AddrModeFlat;
      m_stackframe.AddrFrame.Offset = pcontext->Rsp;
      m_stackframe.AddrFrame.Mode = AddrModeFlat;
#elif defined(X86)
      m_stackframe.AddrPC.Offset = pcontext->Eip;
      m_stackframe.AddrPC.Mode = AddrModeFlat;
      m_stackframe.AddrStack.Offset = pcontext->Esp;
      m_stackframe.AddrStack.Mode = AddrModeFlat;
      m_stackframe.AddrFrame.Offset = pcontext->Ebp;
      m_stackframe.AddrFrame.Mode = AddrModeFlat;
#else
      m_stackframe.AddrPC.offset = (u32)pcontext->Fir;
      m_stackframe.AddrPC.Mode = AddrModeFlat;
      m_stackframe.AddrReturn.offset = (u32)pcontext->IntRa;
      m_stackframe.AddrReturn.Mode = AddrModeFlat;
      m_stackframe.AddrStack.offset = (u32)pcontext->IntSp;
      m_stackframe.AddrStack.Mode = AddrModeFlat;
      m_stackframe.AddrFrame.offset = (u32)pcontext->IntFp;
      m_stackframe.AddrFrame.Mode = AddrModeFlat;
#endif

      m_context = *pcontext;
#endif

      backtrace(iCount);

      return m_iAddressRead < m_iAddressWrite;

   }


   void callstack::backtrace(OS_DWORD * pinteraction, int & c)
   {
      cslock csl(&g_cs);

#if FAST_STACK_TRACE

      ::u32 maxframes = c;
      ULONG BackTraceHash;
      c = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID *>(pinteraction), &BackTraceHash);

#endif
   }


   void callstack::backtrace(int iCount)
   {

#if FAST_STACK_TRACE
      ::u32 maxframes = min_non_neg(iCount, (int)(sizeof(m_uia) / sizeof(m_uia[0])));
      ULONG BackTraceHash;
      m_iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID *>(&m_uia), &BackTraceHash);
#else
      m_iAddressWrite = 0;
      //if (!m_bOk)
      //{
      // _ASSERTE(0);
      //return;
      //}


      while (true)
      {

         set_last_error(0);
         HANDLE hprocess = SymGetProcessHandle();

         u32 dwType;

         bool bRetry;

#ifdef AMD64
         dwType = IMAGE_FILE_MACHINE_AMD64;
#else
         dwType = IMAGE_FILE_MACHINE_I386;
#endif

#if OSBIT == 64
         bool r = StackWalk64(
            dwType,   // __in      u32 MachineType,
            hprocess,        // __in      HANDLE hProcess,
            get_current_hthread(),         // __in      hthread_t hthread,
            &m_stackframe,                       // __inout   LP STACKFRAME64 StackFrame,
            &m_context,                  // __inout   PVOID ContextRecord,
            My_ReadProcessMemory,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
            //nullptr,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
            SymFunctionTableAccess64,                      // __in_opt  PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
            SymGetModuleBase64,                     // __in_opt  PGET_MODULE_AXIS_ROUTINE64 GetModuleBaseRoutine,
            nullptr                       // __in_opt  PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress
         ) != FALSE;
#else
         bool r = StackWalk(
            dwType,   // __in      u32 MachineType,
            hprocess,        // __in      HANDLE hProcess,
            get_current_hthread(),         // __in      hthread_t hthread,
            &m_stackframe,                       // __inout   LP STACKFRAME64 StackFrame,
            &m_context,                  // __inout   PVOID ContextRecord,
            My_ReadProcessMemory32,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
            //nullptr,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
            SymFunctionTableAccess,                      // __in_opt  PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
            SymGetModuleBase,                     // __in_opt  PGET_MODULE_AXIS_ROUTINE64 GetModuleBaseRoutine,
            nullptr                       // __in_opt  PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress
         ) != FALSE;

#endif
         /*#else
         bool r = StackWalk64 (
         ,
         hprocess,
         get_current_hthread(),
         &m_stackframe,
         m_pcontext,
         My_ReadProcessMemory,
         SymFunctionTableAccess64,
         SymGetModuleBase64,
         0) != FALSE;
#endif*/

         if (!r || !m_stackframe.AddrFrame.Offset)
         {

            return;

         }

         bRetry = false;

      retry_get_base:

         // "Debugging Applications" John Robbins
         // Before I get too carried away and start calculating
         // everything, I need to double-check that the address returned
         // by StackWalk really exists. I've seen cases in which
         // StackWalk returns TRUE but the address doesn't belong to
         // a module in the process.

         DWORD64 dwModBase = SymGetModuleBase64(hprocess, m_stackframe.AddrPC.Offset);

         if (!dwModBase)
         {
            //::output_debug_string("callstack::stack_next :: StackWalk returned TRUE but the address doesn't belong to a module in the process.");
            return;
            if (bRetry)
            {

               m_bSkip = true;

               return;

            }

            ::exception::callstack().reset();

            bRetry = true;

            goto retry_get_base;

         }
         m_bSkip = false;
         address(m_stackframe.AddrPC.Offset);

      }

#endif
   }


   bool callstack::stack_next()
   {

      if (m_iAddressRead >= m_iAddressWrite)
      {

         return false;

      }

      m_iAddressRead++;

      return true;

   }


   bool callstack::get_line_from_address(HANDLE hprocess, OS_DWORD uiAddress, ::u32 * puiDisplacement, OS_IMAGEHLP_LINE * pline)
   {

      return engine_get_line_from_address(hprocess, uiAddress, puiDisplacement, pline);
      //#ifdef WORK_AROUND_SRCLINE_BUG
      //      // "Debugging Applications" John Robbins
      //      // The problem is that the symbol callstack finds only those source
      //      // line addresses (after the first lookup) that fall exactly on
      //      // a zero displacement. I'll walk backward 100 bytes to
      //      // find the line and return the proper displacement.
      //      u32 dwDisplacement = 0 ;
      //      while (!SymGetLineFromAddr (hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
      //      {
      //         if (100 == ++dwDisplacement)
      //            return false;
      //      }
      //
      //      // "Debugging Applications" John Robbins
      //      // I found the line, and the source line information is correct, so
      //      // change the displacement if I had to search backward to find the source line.
      //      if(dwDisplacement)
      //         *puiDisplacement = dwDisplacement;
      //      return true;
      //#else
      //      return 0 != SymGetLineFromAddr64 (hprocess, uiAddress, (u32 *) puiDisplacement, pline);
      //#endif
   }
   //#else
   //   bool callstack::get_line_from_address(HANDLE hprocess, DWORD64 uiAddress, ::u32 * puiDisplacement, IMAGEHLP_LINE64 * pline)
   //   {
   //
   //      return engine_get_line_from_address(hprocess, uiAddress, puiDisplacement, pline);
   //#ifdef WORK_AROUND_SRCLINE_BUG
   //      // "Debugging Applications" John Robbins
   //      // The problem is that the symbol callstack finds only those source
   //      // line addresses (after the first lookup) that fall exactly on
   //      // a zero displacement. I'll walk backward 100 bytes to
   //      // find the line and return the proper displacement.
   //      u32 dwDisplacement = 0;
   //      while (!SymGetLineFromAddr64(hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
   //      {
   //         if (100 == ++dwDisplacement)
   //            return false;
   //      }
   //
   //      // "Debugging Applications" John Robbins
   //      // I found the line, and the source line information is correct, so
   //      // change the displacement if I had to search backward to find the source line.
   //      if (dwDisplacement)
   //         *puiDisplacement = dwDisplacement;
   //      return true;
   //#else
   //      return 0 != SymGetLineFromAddr64(hprocess, uiAddress, (u32 *)puiDisplacement, pline);
   //#endif
   //   }
   //#endif


   size_t callstack::get_module_name(HMODULE hmodule, char * psz, int nCount)
   {

      for (i32 i = 0; i < m_iMa; i++)
      {
         if (m_ma[i] == hmodule)
         {
            if (m_szaModule[i] == nullptr)
               return 0;
            ansi_count_copy(psz, m_szaModule[i], nCount);
            return strlen(psz);

         }
      }

      char filename[MAX_PATH];
      if (!GetModuleFileNameA(hmodule, filename, MAX_PATH))
      {
         m_ma[m_iMa] = hmodule;
         m_szaModule[m_iMa++] = nullptr;

         return 0;
      }

      m_ma[m_iMa] = hmodule;
      m_szaModule[m_iMa] = strdup(filename);
      ansi_count_copy(psz, m_szaModule[m_iMa++], nCount);
      //u32 r = GetModuleFileNameA(hmodule, psz, nCount);

      //if(!r)
      // return 0;



      // find the last '\' mark.
      //char * point = strrchr(psz, '\\');

      //if(point != nullptr)
      //{

      //   *(point + 1) = '\0';

      //}

      return strlen(psz);

   }


   bool callstack::check()
   {
      if (!m_bOk)
         m_bOk = init();
      return m_bOk;
   }


   bool callstack::load_modules()
   {

      return true;

      //      HANDLE hprocess = SymGetProcessHandle();
      //      u32  dwPid = get_current_process_id();
      //
      //      // enumerate modules
      //      if (is_windows_nt())
      //      {
      //         typedef bool (WINAPI *ENUMPROCESSMODULES)(HANDLE, HMODULE*, u32, LPDWORD);
      //
      //         HINSTANCE hInst = LoadLibrary("psapi.dll");
      //         if (hInst)
      //         {
      //            ENUMPROCESSMODULES fnEnumProcessModules =
      //            (ENUMPROCESSMODULES)GetProcAddress(hInst, "EnumProcessModules");
      //            ::u32 cbNeeded = 0;
      //            if (fnEnumProcessModules &&
      //                  fnEnumProcessModules(GetCurrentProcess(), 0, 0, &cbNeeded) &&
      //                  cbNeeded)
      //            {
      //               HMODULE * pmod = (HMODULE *)alloca(cbNeeded);
      //               ::u32 cb = cbNeeded;
      //               if (fnEnumProcessModules(GetCurrentProcess(), pmod, cb, &cbNeeded))
      //               {
      //                  m_iRef = 0;
      //                  for (u32 i = 0; i < cb / sizeof (HMODULE); ++i)
      //                  {
      //                     if (!load_module(hprocess, pmod[i]))
      //                     {
      //                        //   m_iRef = -1;
      //                        //   break;
      ////                        _ASSERTE(0);
      //                        m_iRef = -1;
      //                        break;
      //                     }
      //                  }
      //               }
      //            }
      //            else
      //            {
      //               _ASSERTE(0);
      //            }
      //            VERIFY(FreeLibrary(hInst));
      //         }
      //         else
      //         {
      //            _ASSERTE(0);
      //         }
      //      }
      //      else
      //      {
      //         typedef HANDLE (WINAPI *CREATESNAPSHOT)(u32, u32);
      //         typedef bool (WINAPI *MODULEWALK)(HANDLE, LPMODULEENTRY32);
      //
      //         HMODULE hMod = GetModuleHandle("kernel32");
      //         CREATESNAPSHOT fnCreateToolhelp32Snapshot = (CREATESNAPSHOT)GetProcAddress(hMod, "CreateToolhelp32Snapshot");
      //         MODULEWALK fnModule32First = (MODULEWALK)GetProcAddress(hMod, "Module32First");
      //         MODULEWALK fnModule32Next  = (MODULEWALK)GetProcAddress(hMod, "Module32Next");
      //
      //         if (fnCreateToolhelp32Snapshot &&
      //               fnModule32First &&
      //               fnModule32Next)
      //         {
      //            HANDLE hModSnap = fnCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
      //            if (hModSnap)
      //            {
      //               MODULEENTRY32 me32 = {0};
      //               me32.dwSize = sizeof(MODULEENTRY32);
      //               if (fnModule32First(hModSnap, &me32))
      //               {
      //                  m_iRef = 0;
      //                  do
      //                  {
      //                     if (!load_module(hprocess, me32.hModule))
      //                     {
      //                        //   m_iRef = -1;
      //                        //   break;
      //                     }
      //                  }
      //                  while(fnModule32Next(hModSnap, &me32));
      //               }
      //               VERIFY(CloseHandle(hModSnap));
      //            }
      //         }
      //      }
      //
      //      if (m_iRef == -1)
      //      {
      //         VERIFY(SymCleanup(SymGetProcessHandle()));
      //      }
      //
      return true;

   }

//#define LDR_DLL_NOTIFICATION_REASON_LOADED     1
//#define LDR_DLL_NOTIFICATION_REASON_UNLOADED     2
//
//
//
//   typedef struct _LDR_DLL_LOADED_NOTIFICATION_DATA
//   {
//      ULONG Flags;                    //Reserved.
//      PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
//      PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
//      PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
//      ULONG SizeOfImage;              //The size of the DLL image, in bytes.
//   } LDR_DLL_LOADED_NOTIFICATION_DATA, * PLDR_DLL_LOADED_NOTIFICATION_DATA;
//   //The LDR_DLL_UNLOADED_NOTIFICATION_DATA structure has the following definition :
//
//   typedef struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA
//   {
//      ULONG Flags;                    //Reserved.
//      PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
//      PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
//      PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
//      ULONG SizeOfImage;              //The size of the DLL image, in bytes.
//   } LDR_DLL_UNLOADED_NOTIFICATION_DATA, * PLDR_DLL_UNLOADED_NOTIFICATION_DATA;
//
//   typedef union _LDR_DLL_NOTIFICATION_DATA
//   {
//      LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
//      LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
//   } LDR_DLL_NOTIFICATION_DATA, * PLDR_DLL_NOTIFICATION_DATA;
//
//
//   VOID CALLBACK LdrDllNotification(
//      ULONG NotificationReason,
//      PLDR_DLL_NOTIFICATION_DATA NotificationData,
//      PVOID Context
//   )
//   {
//      class ::windows::callstack * pengine = (class ::windows::callstack *)Context;
//      if (NotificationReason == LDR_DLL_NOTIFICATION_REASON_LOADED)
//      {
//
//         cslock csl(&::windows::callstack::g_cs);
//
//         HANDLE hprocess = SymGetProcessHandle();
//
//         SymRefreshModuleList(hprocess);
//
//      }
//
//   }
//
//   typedef NTSTATUS NTAPI FN_LdrUnregisterDllNotification(_In_ PVOID Cookie);
//   typedef FN_LdrUnregisterDllNotification * PFN_LdrUnregisterDllNotification;
//
//
//   PFN_LdrUnregisterDllNotification g_pLdrUnregisterDllNotification = nullptr;
//
//   typedef VOID CALLBACK FN_LdrDllNotification(
//      ULONG NotificationReason,
//      PLDR_DLL_NOTIFICATION_DATA NotificationData,
//      PVOID Context
//   );
//   typedef FN_LdrDllNotification * PFN_LdrDllNotification;
//
//   typedef NTSTATUS NTAPI FN_LdrRegisterDllNotification(
//      _In_     ULONG                          Flags,
//      _In_     PFN_LdrDllNotification NotificationFunction,
//      _In_opt_ PVOID                          Context,
//      _Out_    PVOID * Cookie
//   );
//   typedef FN_LdrRegisterDllNotification * PFN_LdrRegisterDllNotification;
//
//
//   PFN_LdrRegisterDllNotification g_pLdrRegisterDllNotification = nullptr;


   bool callstack::init()
   {

      //if(!::file_exists("C:\\acme\\callstack.txt"))
      //{
      //   return false;
      //}


      cslock csl(&g_cs);

      if (m_bInit)
      {

         return true;

      }

      HANDLE hprocess = SymGetProcessHandle();
      u32  dwPid = get_current_process_id();

      // initializes
      //SymSetOptions(SymGetOptions()|SYMOPT_DEFERRED_LOADS|SYMOPT_LOAD_LINES);
      SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);
      //   SymSetOptions (SYMOPT_UNDNAME|SYMOPT_LOAD_LINES);
      if (!::SymInitialize(hprocess, 0, TRUE))
      {
         ::u32 dw = ::GetLastError();
         output_debug_string("Last Error = " + __str(dw));
         ASSERT(0);

         //load_modules();
         return false;
      }

      //if (g_pLdrUnregisterDllNotification == nullptr)
      //{
      //   HINSTANCE h = LoadLibraryW(L"Ntdll.dll");

      //   g_pLdrUnregisterDllNotification = (PFN_LdrUnregisterDllNotification)GetProcAddress(h, "LdrUnregisterDllNotification");
      //   g_pLdrRegisterDllNotification = (PFN_LdrRegisterDllNotification)GetProcAddress(h, "LdrRegisterDllNotification");

      //}
      m_bInit = true;

      //m_pvoidDllNotificationCookie = nullptr;

      //if (g_pLdrUnregisterDllNotification != nullptr &&
      //   g_pLdrRegisterDllNotification != nullptr)
      //{

      //   (*g_pLdrRegisterDllNotification)(0, &LdrDllNotification, this, &m_pvoidDllNotificationCookie);

      //}

      return true;

   }



   bool callstack::fail() const
   {

      //      return m_iRef == -1;
      return !m_bInit;

   }



   void callstack::clear()
   {

      cslock csl(&g_cs);

      if (!m_bInit)
      {

         return;

      }

      //if (g_pLdrUnregisterDllNotification != nullptr)
      //{
      //   (*g_pLdrUnregisterDllNotification)(&m_pvoidDllNotificationCookie);

      //}

      VERIFY(SymCleanup(SymGetProcessHandle()));
      m_bInit = false;

   }






   void callstack::reset()
   {

      cslock csl(&g_cs);


      if (!m_bInit)
      {

         init();

      }
      else
      {
         HANDLE hprocess = SymGetProcessHandle();
         SymRefreshModuleList(hprocess);

      }

   }


   bool callstack::load_module(HANDLE hProcess, HMODULE hMod)
   {

      for (i32 i = 0; i < m_iHa; i++)
      {

         if (m_ha[i] == hMod)
         {

            return true;

         }

      }

      m_ha[m_iHa++] = hMod;

      char filename[MAX_PATH];

      if (!GetModuleFileNameA(hMod, filename, MAX_PATH))
      {

         return false;

      }

      HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, 0);

      if (hFile == INVALID_HANDLE_VALUE)
      {

         return false;

      }

      // "Debugging Applications" John Robbins
      // For whatever reason, SymLoadModule can return zero, but it still loads the modules. Sheez.
      ::SetLastError(ERROR_SUCCESS);

      if (!SymLoadModule(hProcess, hFile, filename, 0, (uptr)hMod, 0) && ERROR_SUCCESS != ::GetLastError())
      {
         
         ::CloseHandle(hFile);
         
         return false;

      }

      ::CloseHandle(hFile);

      return true;

   }


   bool callstack::stack_trace(CONTEXT * pcontext, iptr iSkip, const char * pszFormat, int iCount)
   {

      if (!pszFormat)
      {

         return false;

      }

      if (iSkip >= 0)
      {

         iSkip++;

      }

      return stack_trace(pcontext, iSkip, false, pszFormat);

   }


   /////////////////////////////////////////////
   // prints a current thread's stack

   struct current_context : CONTEXT
   {
      HANDLE   thread;
      volatile i32 signal;
   };


   u32 WINAPI callstack::stack_trace_ThreadProc(void * pvoidParam)
   {

      current_context * pcontext = reinterpret_cast<current_context *>(pvoidParam);

      try
      {
         
         // Konstantin, 14.01.2002 17:21:32
         
         // must wait in spin lock until Main thread will leave a ResumeThread (must return back to ::account::user context)

         i32 iInverseAgility = 26 + 24; // former iPatienceQuota
         
         i32 iPatience = iInverseAgility;

         while (pcontext->signal && iPatience > 0)
         {

            if (!SwitchToThread())
            {

               sleep(10); // forces switch to another thread

            }

            iPatience--;

         }

         //         char sz[200];
         //         sprintf(sz, "callstack::stack_trace patience near down %u%%\n", iPatience * 100 / iInverseAgility);
         //         ::output_debug_string(sz);

         if (-1 == SuspendThread(pcontext->thread))
         {
            
            pcontext->signal = -1;

            return 0;

         }

         try
         {

#ifdef AMD64

            GET_CURRENT_CONTEXT(pcontext, USED_CONTEXT_FLAGS);

#else

            pcontext->signal = GetThreadContext(pcontext->thread, pcontext) ? 1 : -1;

#endif

         }
         catch(...)
         {
            
            VERIFY(-1 != ResumeThread(pcontext->thread));

         }

      }
      catch (...)
      {
         
         pcontext->signal = -1;

      }
      
      return 0;

   }


   bool callstack::stack_trace(iptr iSkip, const char * pszFormat, int iCount)
   {

      if (iSkip >= 0)
      {

         iSkip++;

      }

      cslock csl(&g_cs);

      *_strS = '\0';

      if (!pszFormat) return false;

      // attempts to get current thread's context

#if FAST_STACK_TRACE
      stack_trace(nullptr, iSkip, false, pszFormat, iCount);

#else

      current_context context;
      __memset(&context, 0, sizeof(current_context));

      bool bOk = DuplicateHandle(GetCurrentProcess(), get_current_hthread(), GetCurrentProcess(), &context.thread, 0, 0, DUPLICATE_SAME_ACCESS) != FALSE;

      _ASSERTE(bOk);
      _ASSERTE(context.thread);

      if (!bOk || !context.thread)
         return false;

      context.ContextFlags = CONTEXT_CONTROL; // CONTEXT_FULL;
      context.signal = -1;


      GET_CURRENT_CONTEXT((&context), USED_CONTEXT_FLAGS);

      stack_trace(&context, uiSkip, false, pszFormat);


#endif


      return true;


   }


   bool callstack::stack_trace(CONTEXT * pcontext, iptr iSkip, bool bSkip, const char * pszFormat, int iCount)
   {

      if (iSkip >= 0)
      {

         iSkip += 3;

      }

      *_strS = '\0';

      if (!stack_first(pcontext, (int)(iSkip >= 0 && iCount >= 0 ? iSkip + iCount + 1 : -1)))
      {

         return false;

      }

      uptr uiSkipStart = iSkip;

      int iLine;

      do
      {


         if (!iSkip && !bSkip || iSkip == DEFAULT_SE_EXCEPTION_callstack_SKIP)
         {

            iLine = 0;

            char * psz = get_frame(pszFormat, iLine);

            if (iCount > 0)
            {

               iCount--;

            }

            if (iSkip == DEFAULT_SE_EXCEPTION_callstack_SKIP)
            {

               if (::str::find_ci("KiUserExceptionDispatcher", psz) >= 0)
               {

                  iSkip = 0;

               }

               continue;

            }
            else if (uiSkipStart == DEFAULT_SE_EXCEPTION_callstack_SKIP)
            {

               if (iLine == 0)
               {

                  break;

               }

            }

            ansi_concatenate(_strS, psz);

         }
         else
         {

            --iSkip;

         }

         if (iCount == 0)
         {

            break;

         }

      } while (stack_next());

      return true;

   }


   //char * callstack::stack_trace(OS_DWORD * pinteraction, int c, const char * pszFormat, int iCount)
   //{

   //   cslock csl(&g_cs);

   //   *_strS = '\0';

   //   ::memcpy_dup(m_uia, pinteraction, min(c * sizeof(*pinteraction), sizeof(m_uia)));

   //   m_iAddressWrite = c;
   //   m_iAddressRead = 0;
   //   char * psz;

   //   int iLine;

   //   do
   //   {

   //      iLine = 0;

   //      psz = get_frame(pszFormat, iLine);

   //      if (psz == nullptr)
   //      {

   //         break;

   //      }

   //      ansi_concatenate(_strS, psz);

   //   } while (stack_next());

   //   return _strS;
   //}



   //char * callstack::get_frame(const char * pszFormat, int & iLine)
   //{


   //   *_str = '\0';
   //   *_strBuf = '\0';
   //   *_strFile = '\0';
   //   *_strSymbol = '\0';

   //   u32 uiLineDisplacement = 0;
   //   u32 uiLineNumber = 0;
   //   OS_DWORD uiSymbolDisplacement = 0;


   //   char sz[2];
   //   sz[1] = '\0';
   //   for (char * point = (char *)pszFormat; *point; ++point)
   //   {
   //      if (*point == '%')
   //      {
   //         ++point; // skips '%'
   //         char ca = *point;
   //         switch (ca)
   //         {
   //         case 'm':
   //            if (module(_strBuf, sizeof(_strBuf)))
   //            {
   //               ansi_concatenate(_str, _strBuf);
   //            }
   //            else
   //            {
   //               ansi_concatenate(_str, "?.?");
   //            }
   //            break;
   //         case 'f':
   //            if (*_strFile == '\0')
   //            {
   //               if (!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
   //               {
   //                  strcpy(_strFile, " ");
   //               }
   //            }
   //            ansi_concatenate(_str, _strFile);
   //            break;
   //         case 'l':
   //            if (*_strFile == '\0')
   //            {
   //               if (!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
   //               {
   //                  strcpy(_strFile, " ");
   //               }
   //            }
   //            if (*(point + 1) == 'd')
   //            {
   //               ansi_from_u64(_strBuf, uiLineDisplacement, 10);
   //               ansi_concatenate(_str, _strBuf);
   //               ++point;
   //            }
   //            else
   //            {
   //               ansi_from_u64(_strBuf, uiLineNumber, 10);
   //               ansi_concatenate(_str, _strBuf);
   //            }
   //            break;
   //         case 's':
   //            if (*_strSymbol == '\0')
   //            {
   //               if (!symbol(_strSymbol, sizeof(_strSymbol), &uiSymbolDisplacement))
   //               {
   //                  strcpy(_strSymbol, "?()");
   //               }
   //            }
   //            if (*(point + 1) == 'd')
   //            {
   //               ansi_concatenate_i64(_str, uiSymbolDisplacement);
   //               ++point;
   //            }
   //            else
   //            {
   //               if (ansi_count_compare(_strSymbol, "dispatch::AddMessageHandler", strlen("dispatch::AddMessageHandler")) == 0)
   //               {
   //                  //                     strcpy(_strS, "\n");
   //                  //                   ansi_concatenate(_strS, _strSymbol);
   //                  //                 ansi_concatenate(_strS, "\n");
   //                  //               return nullptr;
   //                  ansi_concatenate(_strS, " * * * ");
   //               }
   //               ansi_concatenate(_str, _strSymbol);
   //            }
   //            break;
   //         case '%':
   //            ansi_concatenate(_str, "%");
   //            break;
   //         default:
   //            ansi_concatenate(_str, "%");
   //            sz[0] = ca;
   //            ansi_concatenate(_str, sz);
   //            break;
   //         }
   //      }
   //      else
   //      {
   //         sz[0] = *point;
   //         ansi_concatenate(_str, sz);
   //      }

   //   }

   //   iLine = uiLineNumber;

   //   return _str;

   //}


} // namespace windows





namespace  windows
{

   typedef int_bool(__stdcall * PReadProcessMemoryRoutine)(
      HANDLE      hProcess,
      DWORD64     qwBaseAddress,
      PVOID       pBuffer,

      u32       nSize,
      LPDWORD     pNumberOfBytesRead,

      LPVOID      pUserData  // optional data, which was passed in "ShowCallstack"
      );

   // The following is used to pass the "userData"-Pointer to the user-provided readMemoryFunction
   // This has to be done due to a problem with the "hProcess"-parameter in x64...
   // Because this class is in no case multi-threading-enabled (because of the limitations
   // of dbghelp.dll) it is "safe" to use a static-variable

   static PReadProcessMemoryRoutine s_readMemoryFunction = nullptr;
   static LPVOID s_readMemoryFunction_UserData = nullptr;


   //bool callstack::stack_trace(iptr iSkip, const char * pszFormat, int iCount)
   //{

   //   return false;

   //}

   char * callstack::stack_trace(OS_DWORD * pinteraction, int c, const char * pszFormat, int iCount)
   {

      cslock csl(&g_cs);

      *_strS = '\0';

      ::memcpy_dup(m_uia, pinteraction, min(c * sizeof(*pinteraction), sizeof(m_uia)));

      m_iAddressWrite = c;
      m_iAddressRead = 0;
      char * psz;

      int iLine;

      do
      {

         iLine = 0;

         psz = get_frame(pszFormat, iLine);

         if (psz == nullptr)
         {

            break;

         }

         ansi_concatenate(_strS, psz);

      } while (stack_next());

      return _strS;
   }



   char * callstack::get_frame(const char * pszFormat, int & iLine)
   {


      *_str = '\0';
      *_strBuf = '\0';
      *_strFile = '\0';
      *_strSymbol = '\0';

      u32 uiLineDisplacement = 0;
      u32 uiLineNumber = 0;
      OS_DWORD uiSymbolDisplacement = 0;


      char sz[2];
      sz[1] = '\0';
      for (char * point = (char *)pszFormat; *point; ++point)
      {
         if (*point == '%')
         {
            ++point; // skips '%'
            char ca = *point;
            switch (ca)
            {
            case 'm':
               if (module(_strBuf, sizeof(_strBuf)))
               {
                  ansi_concatenate(_str, _strBuf);
               }
               else
               {
                  ansi_concatenate(_str, "?.?");
               }
               break;
            case 'f':
               if (*_strFile == '\0')
               {
                  if (!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
                  {
                     strcpy(_strFile, " ");
                  }
               }
               ansi_concatenate(_str, _strFile);
               break;
            case 'l':
               if (*_strFile == '\0')
               {
                  if (!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
                  {
                     strcpy(_strFile, " ");
                  }
               }
               if (*(point + 1) == 'd')
               {
                  ansi_from_u64(_strBuf, uiLineDisplacement, 10);
                  ansi_concatenate(_str, _strBuf);
                  ++point;
               }
               else
               {
                  ansi_from_u64(_strBuf, uiLineNumber, 10);
                  ansi_concatenate(_str, _strBuf);
               }
               break;
            case 's':
               if (*_strSymbol == '\0')
               {
                  if (!symbol(_strSymbol, sizeof(_strSymbol), &uiSymbolDisplacement))
                  {
                     strcpy(_strSymbol, "?()");
                  }
               }
               if (*(point + 1) == 'd')
               {
                  ansi_concatenate_i64(_str, uiSymbolDisplacement);
                  ++point;
               }
               else
               {
                  if (ansi_count_compare(_strSymbol, "dispatch::AddMessageHandler", strlen("dispatch::AddMessageHandler")) == 0)
                  {
                     //                     strcpy(_strS, "\n");
                     //                   ansi_concatenate(_strS, _strSymbol);
                     //                 ansi_concatenate(_strS, "\n");
                     //               return nullptr;
                     ansi_concatenate(_strS, " * * * ");
                  }
                  ansi_concatenate(_str, _strSymbol);
               }
               break;
            case '%':
               ansi_concatenate(_str, "%");
               break;
            default:
               ansi_concatenate(_str, "%");
               sz[0] = ca;
               ansi_concatenate(_str, sz);
               break;
            }
         }
         else
         {
            sz[0] = *point;
            ansi_concatenate(_str, sz);
         }

      }

      iLine = uiLineNumber;

      return _str;

   }

   const char * callstack::get_dup(const char * pszFormat, i32 iSkip, int iCount)
   {

      if (iSkip >= 0)
      {

         iSkip++;

      }

      const char * psz;

      //sync_lock sl(::callstack().mutex());

   #if defined(LINUX)

      psz = strdup(::exception::callstack().stack_trace(iSkip, m_caller_address));

   #elif defined(__APPLE__)

      ::exception::callstack().stack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount);

      psz = _strdup(::exception::callstack()._strS);

   #else

      stack_trace(iSkip, m_pszFormat, m_iCount);

      psz = _strdup(_strS);

   #endif

      return psz;

   }


} // namespace windows



