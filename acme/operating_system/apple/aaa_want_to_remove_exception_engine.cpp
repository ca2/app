// // /*
// // Copyright (ca) 2001 - 2002
// // Author: Konstantin Boukreev
// // E-mail: konstantin@mail.primorye.ru
// // Created: 25.12.2001 19:41:07
// // Version: 1.0.2

// // Permission to use, copy, modify, distribute and sell this software
// // and its documentation for any purpose is hereby granted without fee,
// // provided that the above copyright notice appear in all copies and
// // that both that copyright notice and this permission notice appear
// // in supporting documentation.  Konstantin Boukreev makes no representations
// // about the suitability of this software for any purpose.
// // It is provided "as is" without express or implied warranty.

// // */

// // #include "framework.h"
// // #ifdef WINDOWS_DESKTOP
// // #define WORK_AROUND_SRCLINE_BUG

// // #include <ImageHlp.h>


// // #elif defined(LINUX)
// // #include <execinfo.h>
// // #include <cxxabi.h>
// // #undef USE_MISC

// // #elif defined(__APPLE__)
// // #include <execinfo.h>
// // #elif defined(__ANDROID__)
// // #undef USE_MISC

// // #include <unwind.h>
// // #include <dlfcn.h>
// // #include <cxxabi.h>
// // #endif
// // #ifdef __USE_BFD
// // bool resolve_addr_file_func_line(void *address, const char * * filename, const char ** func, unsigned & iLine);
// // void init_resolve_addr_file_func_line();
// // static int bfdinit = 0;
// // #endif
// // #ifdef __ANDROID__

// // struct BacktraceState
// // {
// //    void** current;
// //    void** end;
// // };

// // static _Unwind_Reason_Code unwindCallback(struct _Unwind_Context* context,void* arg)
// // {
// //    BacktraceState* state = static_cast<BacktraceState*>(arg);
// //    ::u32ptr_t pc = _Unwind_GetIP(context);
// //    if(pc)
// //    {
// //       if(state->current == state->end)
// //       {
// //          return _URC_END_OF_STACK;
// //       }
// //       else
// //       {
// //          *state->current++ = reinterpret_cast<void*>(pc);
// //       }
// //    }
// //    return _URC_NO_REASON;
// // }

// // size_t captureBacktrace(void** buffer,size_t maximum)
// // {
// //    BacktraceState state = {buffer, buffer + maximum};
// //    _Unwind_Backtrace(unwindCallback,&state);

// //    return state.current - buffer;
// // }

// // string dumpBacktrace(void** buffer,size_t count)
// // {
// //    string str;
// //    for(size_t idx = 0; idx < count; ++idx)
// //    {
// //       const void* addr = buffer[idx];
// //       const char* symbol = "";

// //       Dl_info info;

// //       if(dladdr(addr,&info) && info.dli_sname)
// //       {

// //          symbol = info.dli_sname;

// //       }

// //       int status = 0;

// //       char * demangled = __cxxabiv1::__cxa_demangle(symbol, 0, 0, &status);

// //       //str += "  #";
// //       if (idx < 10)
// //       {
// //          str += "0";
// //       }
// //       str += as_string(idx);
// //       //str += ": 0x";
// //       //str += ::hex::upper_from((uptr) addr);
// //       str += "  ";
// //       str += (nullptr != demangled && 0 == status) ? demangled : symbol;
// //       str += "\n";

// //       if (demangled != nullptr)
// //       {

// //          free(demangled);

// //       }

// //    }

// //    return str;

// // }


// // #endif



// // // The following is defined for x86 (XP and higher), x64 and IA64:
// // #define GET_CURRENT_CONTEXT(pc, contextFlags) \
// //    do { \
// //    memory_set(pc, 0, sizeof(CONTEXT)); \
// //    pc->ContextFlags = contextFlags; \
// //    RtlCaptureContext(pc); \
// //    } while(0);







// // HANDLE SymGetProcessHandle()
// // {
// // #ifdef _WIN32
// //    return GetCurrentProcess();
// // #else
// //    return (HANDLE)(INT_PTR)getpid();
// // #endif
// // }

// // #ifdef WINDOWS_DESKTOP


// // bool engine_get_line_from_address(HANDLE hprocess, OS_DWORD uiAddress, unsigned int * puiDisplacement, OS_IMAGEHLP_LINE * pline)
// // {

// // #ifdef WORK_AROUND_SRCLINE_BUG
// //    // "Debugging Applications" John Robbins
// //    // The problem is that the symbol engine finds only those source
// //    // line addresses (after the first lookup) that fall exactly on
// //    // a zero displacement. I'hi walk backward 100 bytes to
// //    // find the line and return the proper displacement.
// //    unsigned int dwDisplacement = 0;

// //    while (!OS_SymGetLineFromAddr(hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
// //    {

// //       if (100 == ++dwDisplacement)
// //       {

// //          return false;

// //       }

// //    }

// //    // "Debugging Applications" John Robbins
// //    // I found the line, and the source line information is correct, so
// //    // change the displacement if I had to search backward to find the source line.
// //    if (dwDisplacement)
// //    {

// //       *puiDisplacement = dwDisplacement;

// //    }

// //    return true;

// // #else

// //    return 0 != OS_SymGetLineFromAddr(hprocess, uiAddress, (unsigned int *)puiDisplacement, pline);

// // #endif

// // }




// // index engine_fileline(OS_DWORD dwAddress, char * psz, int nCount, unsigned int * pline, unsigned int * pdisplacement = 0)
// // {

// //    OS_IMAGEHLP_LINE img_line = {};

// //    img_line.SizeOfStruct = sizeof(OS_IMAGEHLP_LINE);

// //    HANDLE hprocess = SymGetProcessHandle();

// //    unsigned int displacement = 0;

// //    if (!engine_get_line_from_address(hprocess, dwAddress, &displacement, &img_line))
// //    {

// //       return 0;

// //    }

// //    if (pdisplacement)
// //    {

// //       *pdisplacement = displacement;

// //    }

// //    if (pline)
// //    {

// //       *pline = img_line.LineNumber;

// //    }

// //    if (scopedstr)
// //    {

// //       ansi_count_copy(scopedstr, img_line.FileName, nCount);

// //    }

// //    return ansi_length(img_line.FileName);

// // }


// // #if OSBIT == 64
// // size_t engine_symbol(char * sz,int n,DWORD64 * pdisplacement,DWORD64 dwAddress)
// // {

// //    unsigned char symbol[4096];
// //    PIMAGEHLP_SYMBOL64 pSym = (PIMAGEHLP_SYMBOL64)&symbol;
// //    memory_set(pSym,0,sizeof(symbol)) ;
// //    pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64) ;
// //    pSym->MaxNameLength = sizeof(symbol) - sizeof(IMAGEHLP_SYMBOL64);

// //    HANDLE hprocess = SymGetProcessHandle();
// //    DWORD64 displacement = 0;
// //    int r = SymGetSymFromAddr64(hprocess,dwAddress,&displacement,pSym);
// //    if(!r) return 0;
// //    if(pdisplacement)
// //       *pdisplacement = displacement;

// //    strncpy_s(sz,n,pSym->Name,n);

// //    return strlen(sz);
// // }
// // #else
// // size_t engine_symbol(char * sz, int n, unsigned int * pdisplacement, unsigned int dwAddress)
// // {

// //    unsigned char symbol[4096];
// //    PIMAGEHLP_SYMBOL pSym = (PIMAGEHLP_SYMBOL)&symbol;
// //    memory_set(pSym, 0, sizeof(symbol));
// //    pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
// //    pSym->MaxNameLength = sizeof(symbol) - sizeof(IMAGEHLP_SYMBOL);

// //    HANDLE hprocess = SymGetProcessHandle();
// //    unsigned int displacement = 0;
// //    int r = SymGetSymFromAddr(hprocess, dwAddress, &displacement, pSym);
// //    if (!r) return 0;
// //    if (pdisplacement)
// //       *pdisplacement = displacement;

// //    strncpy_s(sz, n, pSym->Name, n);

// //    return strlen(sz);
// // }

// // #endif
// // #define USED_CONTEXT_FLAGS CONTEXT_FULL

// // #endif

// // // #ifdef VERIFY
// // // #undef VERIFY
// // // #endif // VERIFY

// // // #ifdef _DEBUG
// // // #define VERIFY(x) ASSERT(x)
// // // #else // __DEBUG
// // // #define VERIFY(x) (x)
// // // #endif // !__DEBUG


// // ///////////////////////////////////////////////////////////////////////

// // HANDLE SymGetProcessHandle();
// // int_bool __stdcall My_ReadProcessMemory(HANDLE      hProcess,
// //                                         DWORD64     qwBaseAddress,
// //                                         PVOID       pBuffer,

// //                                         unsigned int       nSize,
// //                                         LPDWORD     pNumberOfBytesRead

// //                                        );



// // HANDLE SymGetProcessHandle();


// // //#ifdef AMD64

// // /*typedef
// // BOOL
// // (__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)(
// // _In_ HANDLE hProcess,
// // _In_ DWORD64 qwBaseAddress,
// // _Out_writes_bytes_(nSize) PVOID pBuffer,

// // _In_ unsigned int nSize,
// // _Out_ LPDWORD pNumberOfBytesRead

// // );*/


// // int_bool __stdcall My_ReadProcessMemory (
// // HANDLE      hProcess,
// // DWORD64     qwBaseAddress,
// // PVOID       pBuffer,

// // unsigned int       nSize,
// // LPDWORD     pNumberOfBytesRead

// // )
// // {

// //    SIZE_T size = 0;
// // #if defined(UNIVERSAL_WINDOWS) || defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(SOLARIS)
// //    return false;
// // #else
// //    if(!ReadProcessMemory(hProcess, (const void *) qwBaseAddress, (LPVOID) pBuffer, nSize, &size))

// //       return false;
// //    *pNumberOfBytesRead = (unsigned int) size;


// //    return true;
// // #endif

// // }


// // #ifndef FAST_STACK_TRACE

// // int_bool __stdcall My_ReadProcessMemory32(HANDLE hProcess, unsigned int qwBaseAddress, PVOID pBuffer, unsigned int nSize, LPDWORD lpNumberOfBytesRead)

// // {

// //    SIZE_T size = 0;
// // #if defined(UNIVERSAL_WINDOWS) || defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(SOLARIS)
// //    throw ::exception(todo);
// // #else
// //    if (!ReadProcessMemory(hProcess, (const void *)qwBaseAddress, (LPVOID)pBuffer, nSize, &size))

// //       return false;
// // #endif
// //    *pNumberOfBytesRead = (unsigned int)size;


// //    return true;

// // }

// // #endif

// // /*
// // #else
// // int_bool __stdcall My_ReadProcessMemory (HANDLE, const void * pBaseAddress, LPVOID lpBuffer, unsigned int nSize, SIZE_T * lpNumberOfBytesRead)

// // {
// // return ReadProcessMemory(GetCurrentProcess(), pBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead) != false;

// // }
// // #endif
// // */

// // //class ::exception_engine * g_pexceptionengine = nullptr;

// // namespace exception
// // {

// // //   CLASS_DECL_ACME class ::exception_engine & engine()
// // //   {
// // //
// // //      return *g_pexceptionengine;
// // //
// // //   }

// //    typedef int_bool (__stdcall *PReadProcessMemoryRoutine)(
// //    HANDLE      hProcess,
// //    DWORD64     qwBaseAddress,
// //    PVOID       pBuffer,

// //    unsigned int       nSize,
// //    LPDWORD     pNumberOfBytesRead,

// //    LPVOID      pUserData  // optional data, which was passed in "ShowCallstack"
// //    );

// //    // The following is used to pass the "userData"-Pointer to the user-provided readMemoryFunction
// //    // This has to be done due to a problem with the "hProcess"-parameter in x64...
// //    // Because this class is in no case multi-threading-enabled (because of the limitations
// //    // of dbghelp.dll) it is "safe" to use a static-variable

// // #ifdef WINDOWS

// //    static PReadProcessMemoryRoutine s_readMemoryFunction = nullptr;
// //    static LPVOID s_readMemoryFunction_UserData = nullptr;

// // #endif

// //    engine::engine(::particle * pparticle) :
// //       matter(pparticle)
// // #ifdef WINDOWS_DESKTOP
// //       ,m_bOk(false)
// //       ,m_bInit(false)
// // #endif
// //    {

// // #ifdef WINDOWS_DESKTOP
// //       m_iHa = 0;
// //       m_iMa = 0;
// //       zero(m_szaModule);
// // #else
// // #endif
// //    }

// //    engine::~engine()
// //    {
// // #ifdef WINDOWS_DESKTOP
// //       clear();
// // #endif



// //    }

// // #ifdef WINDOWS_DESKTOP

// //    size_t engine::module(char * psz, int nCount)
// //    {
// //       if (!check())
// //          return 0;

// //       HANDLE hprocess = SymGetProcessHandle();
// //       HMODULE hmodule = (HMODULE)SymGetModuleBase64 (hprocess, address());
// //       if (!hmodule) return 0;
// //       return get_module_name(hmodule, psz, nCount);
// //    }
// // #endif

// // #ifdef WINDOWS_DESKTOP


// //    size_t engine::symbol(char * psz, int nCount, unsigned int * pdisplacement)
// //    {

// //       if (!check())
// //          return 0;

// //       engine_symbol(scopedstr, nCount, pdisplacement, address());

// //       ansi_concatenate(scopedstr, "()");

// //       return strlen(scopedstr);

// //    }

// //    index engine::fileline (char * psz, int nCount, unsigned int * pline, unsigned int * pdisplacement)
// //    {

// //       if (!check())
// //          return 0;

// //       return engine_fileline(address(), psz, nCount, pline, pdisplacement);

// //    }


// //    bool engine::stack_first(CONTEXT* pcontext)
// //    {
// //       m_iAddressRead = 0;
// // #if !FAST_STACK_TRACE
// //       if(!pcontext || IsBadReadPtr(pcontext, sizeof(CONTEXT)))
// //          return false;

// //       if(!check())
// //          return false;

// //       memory_set(&m_stackframe, 0, sizeof(m_stackframe));

// //       //  s_readMemoryFunction = readMemoryFunction;
// //       //s_readMemoryFunction_UserData = pUserData;


// // #ifdef AMD64
// //       m_stackframe.AddrPC.Offset       = pcontext->Rip;
// //       m_stackframe.AddrPC.Mode         = AddrModeFlat;
// //       m_stackframe.AddrStack.Offset    = pcontext->Rsp;
// //       m_stackframe.AddrStack.Mode      = AddrModeFlat;
// //       m_stackframe.AddrFrame.Offset    = pcontext->Rsp;
// //       m_stackframe.AddrFrame.Mode      = AddrModeFlat;
// // #elif defined(X86)
// //       m_stackframe.AddrPC.Offset       = pcontext->Eip;
// //       m_stackframe.AddrPC.Mode         = AddrModeFlat;
// //       m_stackframe.AddrStack.Offset    = pcontext->Esp;
// //       m_stackframe.AddrStack.Mode      = AddrModeFlat;
// //       m_stackframe.AddrFrame.Offset    = pcontext->Ebp;
// //       m_stackframe.AddrFrame.Mode      = AddrModeFlat;
// // #else
// //       m_stackframe.AddrPC.offset       = (unsigned int)pcontext->Fir;
// //       m_stackframe.AddrPC.Mode         = AddrModeFlat;
// //       m_stackframe.AddrReturn.offset   = (unsigned int)pcontext->IntRa;
// //       m_stackframe.AddrReturn.Mode     = AddrModeFlat;
// //       m_stackframe.AddrStack.offset    = (unsigned int)pcontext->IntSp;
// //       m_stackframe.AddrStack.Mode      = AddrModeFlat;
// //       m_stackframe.AddrFrame.offset    = (unsigned int)pcontext->IntFp;
// //       m_stackframe.AddrFrame.Mode      = AddrModeFlat;
// // #endif

// //       m_context = *pcontext;
// // #endif
// //       xxxbacktrace();
// //       return stack_next();
// //    }


// //    void engine::xxxbacktrace(OS_DWORD *pinteraction, int &c)
// //    {
// //       cslock csl(&m_cs);

// // #if FAST_STACK_TRACE

// //       unsigned int maxframes = c;
// //       ULONG BackTraceHash;
// //       c = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID*>(pinteraction), &BackTraceHash);

// // #endif
// //    }
// //    void engine::xxxbacktrace()
// //    {

// // #if FAST_STACK_TRACE
// //       unsigned int maxframes = sizeof(m_uia) / sizeof(m_uia[0]);
// //       ULONG BackTraceHash;
// //       m_iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID*>(&m_uia), &BackTraceHash);
// // #else
// //       m_iAddressWrite = 0;
// //       //if (!m_bOk)
// //       //{
// //       // _ASSERTE(0);
// //       //return;
// //       //}


// //       while (true)
// //       {

// //          set_last_error(0);
// //          HANDLE hprocess = SymGetProcessHandle();

// //          unsigned int dwType;

// //          bool bRetry;

// // #ifdef AMD64
// //          dwType = IMAGE_FILE_MACHINE_AMD64;
// // #else
// //          dwType = IMAGE_FILE_MACHINE_I386;
// // #endif

// // #if OSBIT == 64
// //          bool r = StackWalk64(
// //                   dwType,   // __in      unsigned int MachineType,
// //                   hprocess,        // __in      HANDLE hProcess,
// //                   current_htask(),         // __in       htask,
// //                   &m_stackframe,                       // __inout   LP STACKFRAME64 StackFrame,
// //                   &m_context,                  // __inout   PVOID ContextRecord,
// //                   My_ReadProcessMemory,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
// //                   //nullptr,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
// //                   SymFunctionTableAccess64,                      // __in_opt  PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
// //                   SymGetModuleBase64,                     // __in_opt  PGET_MODULE_AXIS_ROUTINE64 GetModuleBaseRoutine,
// //                   nullptr                       // __in_opt  PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress
// //                   ) != false;
// // #else
// //          bool r = StackWalk(
// //                   dwType,   // __in      unsigned int MachineType,
// //                   hprocess,        // __in      HANDLE hProcess,
// //                   current_htask(),         // __in      htask htask,
// //                   &m_stackframe,                       // __inout   LP STACKFRAME64 StackFrame,
// //                   &m_context,                  // __inout   PVOID ContextRecord,
// //                   My_ReadProcessMemory32,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
// //                   //nullptr,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
// //                   SymFunctionTableAccess,                      // __in_opt  PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
// //                   SymGetModuleBase,                     // __in_opt  PGET_MODULE_AXIS_ROUTINE64 GetModuleBaseRoutine,
// //                   nullptr                       // __in_opt  PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress
// //                   ) != false;

// // #endif
// //          /*#else
// //          bool r = StackWalk64 (
// //          ,
// //          hprocess,
// //          current_htask(),
// //          &m_stackframe,
// //          m_papplication,
// //          My_ReadProcessMemory,
// //          SymFunctionTableAccess64,
// //          SymGetModuleBase64,
// //          0) != false;
// // #endif*/

// //          if (!r || !m_stackframe.AddrFrame.Offset)
// //          {

// //          return;

// //          }

// //          bRetry = false;

// //          retry_get_base:

// //          // "Debugging Applications" John Robbins
// //          // Before I get too carried away and start calculating
// //          // everything, I need to double-check that the address returned
// //          // by StackWalk really exists. I've seen cases in which
// //          // StackWalk returns true but the address doesn't belong to
// //          // a module in the process.

// //          DWORD64 dwModBase = SymGetModuleBase64(hprocess, m_stackframe.AddrPC.Offset);

// //          if (!dwModBase)
// //          {
// //          //informationf("engine::stack_next :: StackWalk returned true but the address doesn't belong to a module in the process.");
// //          return;
// //          if (bRetry)
// //          {

// //          m_bSkip = true;

// //          return;

// //          }

// //          ::exception_engine().reset();

// //          bRetry = true;

// //          goto retry_get_base;

// //          }
// //          m_bSkip = false;
// //          address(m_stackframe.AddrPC.Offset);

// //          }

// // #endif
// //    }

// //    bool engine::stack_next()
// //    {
// //       if (m_iAddressRead >= m_iAddressWrite)
// //          return false;
// //       m_iAddressRead++;
// //       return true;
// //    }


// //    bool engine::get_line_from_address (HANDLE hprocess, OS_DWORD uiAddress, unsigned int * puiDisplacement, OS_IMAGEHLP_LINE * pline)
// //    {

// //       return engine_get_line_from_address(hprocess, uiAddress, puiDisplacement, pline);
// // //#ifdef WORK_AROUND_SRCLINE_BUG
// // //      // "Debugging Applications" John Robbins
// // //      // The problem is that the symbol engine finds only those source
// // //      // line addresses (after the first lookup) that fall exactly on
// // //      // a zero displacement. I'hi walk backward 100 bytes to
// // //      // find the line and return the proper displacement.
// // //      unsigned int dwDisplacement = 0 ;
// // //      while (!SymGetLineFromAddr (hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
// // //      {
// // //         if (100 == ++dwDisplacement)
// // //            return false;
// // //      }
// // //
// // //      // "Debugging Applications" John Robbins
// // //      // I found the line, and the source line information is correct, so
// // //      // change the displacement if I had to search backward to find the source line.
// // //      if(dwDisplacement)
// // //         *puiDisplacement = dwDisplacement;
// // //      return true;
// // //#else
// // //      return 0 != SymGetLineFromAddr64 (hprocess, uiAddress, (unsigned int *) puiDisplacement, pline);
// // //#endif
// //    }
// // //#else
// // //   bool engine::get_line_from_address(HANDLE hprocess, DWORD64 uiAddress, unsigned int * puiDisplacement, IMAGEHLP_LINE64 * pline)
// // //   {
// // //
// // //      return engine_get_line_from_address(hprocess, uiAddress, puiDisplacement, pline);
// // //#ifdef WORK_AROUND_SRCLINE_BUG
// // //      // "Debugging Applications" John Robbins
// // //      // The problem is that the symbol engine finds only those source
// // //      // line addresses (after the first lookup) that fall exactly on
// // //      // a zero displacement. I'hi walk backward 100 bytes to
// // //      // find the line and return the proper displacement.
// // //      unsigned int dwDisplacement = 0;
// // //      while (!SymGetLineFromAddr64(hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
// // //      {
// // //         if (100 == ++dwDisplacement)
// // //            return false;
// // //      }
// // //
// // //      // "Debugging Applications" John Robbins
// // //      // I found the line, and the source line information is correct, so
// // //      // change the displacement if I had to search backward to find the source line.
// // //      if (dwDisplacement)
// // //         *puiDisplacement = dwDisplacement;
// // //      return true;
// // //#else
// // //      return 0 != SymGetLineFromAddr64(hprocess, uiAddress, (unsigned int *)puiDisplacement, pline);
// // //#endif
// // //   }
// // //#endif

// //    size_t engine::get_module_name (HMODULE hmodule, char * psz, int nCount)
// //    {

// //       for (int i = 0; i < m_iMa; i++)
// //       {
// //          if (m_ma[i] == hmodule)
// //          {
// //             if (m_szaModule[i] == nullptr)
// //                return 0;
// //             ansi_count_copy(scopedstr, m_szaModule[i], nCount);
// //             return strlen(scopedstr);

// //          }
// //       }

// //       char filename[MAX_PATH];
// //       if (!GetModuleFileNameA(hmodule, filename, MAX_PATH))
// //       {
// //          m_ma[m_iMa] = hmodule;
// //          m_szaModule[m_iMa++] = nullptr;

// //          return 0;
// //       }

// //       m_ma[m_iMa] = hmodule;
// //       m_szaModule[m_iMa] = strdup(filename);
// //       ansi_count_copy(scopedstr, m_szaModule[m_iMa++], nCount);
// //       //unsigned int r = GetModuleFileNameA(hmodule, psz, nCount);

// //       //if(!r)
// //       // return 0;



// //       // find the last '\' mark.
// //       //char * point = strrchr(scopedstr, '\\');

// //       //if(point != nullptr)
// //       //{

// //       //   *(point + 1) = '\0';

// //       //}

// //       return strlen(scopedstr);

// //    }


// //    bool engine::check()
// //    {
// //       if (!m_bOk)
// //          m_bOk = init();
// //       return m_bOk;
// //    }


// // #endif






















// // #ifdef WINDOWS_DESKTOP

// // #include <malloc.h>

// //    bool engine::load_modules()
// //    {

// //       return true;

// // //      HANDLE hprocess = SymGetProcessHandle();
// // //      unsigned int  dwPid = get_current_process_id();
// // //
// // //      // enumerate modules
// // //      if (is_windows_nt())
// // //      {
// // //         typedef bool (WINAPI *ENUMPROCESSMODULES)(HANDLE, HMODULE*, unsigned int, LPDWORD);
// // //
// // //         HINSTANCE hInst = LoadLibrary("psapi.dll");
// // //         if (hInst)
// // //         {
// // //            ENUMPROCESSMODULES fnEnumProcessModules =
// // //            (ENUMPROCESSMODULES)GetProcAddress(hInst, "EnumProcessModules");
// // //            unsigned int cbNeeded = 0;
// // //            if (fnEnumProcessModules &&
// // //                  fnEnumProcessModules(GetCurrentProcess(), 0, 0, &cbNeeded) &&
// // //                  cbNeeded)
// // //            {
// // //               HMODULE * pmod = (HMODULE *)alloca(cbNeeded);
// // //               unsigned int cb = cbNeeded;
// // //               if (fnEnumProcessModules(GetCurrentProcess(), pmod, cb, &cbNeeded))
// // //               {
// // //                  m_iRef = 0;
// // //                  for (unsigned int i = 0; i < cb / sizeof (HMODULE); ++i)
// // //                  {
// // //                     if (!load_module(hprocess, pmod[i]))
// // //                     {
// // //                        //   m_iRef = -1;
// // //                        //   break;
// // ////                        _ASSERTE(0);
// // //                        m_iRef = -1;
// // //                        break;
// // //                     }
// // //                  }
// // //               }
// // //            }
// // //            else
// // //            {
// // //               _ASSERTE(0);
// // //            }
// // //            VERIFY(FreeLibrary(hInst));
// // //         }
// // //         else
// // //         {
// // //            _ASSERTE(0);
// // //         }
// // //      }
// // //      else
// // //      {
// // //         typedef HANDLE (WINAPI *CREATESNAPSHOT)(unsigned int, unsigned int);
// // //         typedef bool (WINAPI *MODULEWALK)(HANDLE, LPMODULEENTRY32);
// // //
// // //         HMODULE hMod = GetModuleHandle("kernel32");
// // //         CREATESNAPSHOT fnCreateToolhelp32Snapshot = (CREATESNAPSHOT)GetProcAddress(hMod, "CreateToolhelp32Snapshot");
// // //         MODULEWALK fnModule32First = (MODULEWALK)GetProcAddress(hMod, "Module32First");
// // //         MODULEWALK fnModule32Next  = (MODULEWALK)GetProcAddress(hMod, "Module32Next");
// // //
// // //         if (fnCreateToolhelp32Snapshot &&
// // //               fnModule32First &&
// // //               fnModule32Next)
// // //         {
// // //            HANDLE hModSnap = fnCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
// // //            if (hModSnap)
// // //            {
// // //               MODULEENTRY32 me32 = {0};
// // //               me32.dwSize = sizeof(MODULEENTRY32);
// // //               if (fnModule32First(hModSnap, &me32))
// // //               {
// // //                  m_iRef = 0;
// // //                  do
// // //                  {
// // //                     if (!load_module(hprocess, me32.hModule))
// // //                     {
// // //                        //   m_iRef = -1;
// // //                        //   break;
// // //                     }
// // //                  }
// // //                  while(fnModule32Next(hModSnap, &me32));
// // //               }
// // //               VERIFY(CloseHandle(hModSnap));
// // //            }
// // //         }
// // //      }
// // //
// // //      if (m_iRef == -1)
// // //      {
// // //         VERIFY(SymCleanup(SymGetProcessHandle()));
// // //      }
// // //
// //       return true;

// //    }

// // #endif
















// // #ifdef WINDOWS_DESKTOP
// // #define LDR_DLL_NOTIFICATION_REASON_LOADED     1
// // #define LDR_DLL_NOTIFICATION_REASON_UNLOADED     2



// //    typedef struct _LDR_DLL_LOADED_NOTIFICATION_DATA
// //    {
// //       ULONG Flags;                    //Reserved.
// //       PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
// //       PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
// //       PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
// //       ULONG SizeOfImage;              //The size of the DLL image, in bytes.
// //    } LDR_DLL_LOADED_NOTIFICATION_DATA, *PLDR_DLL_LOADED_NOTIFICATION_DATA;
// //    //The LDR_DLL_UNLOADED_NOTIFICATION_DATA structure has the following definition :

// //    typedef struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA
// //    {
// //       ULONG Flags;                    //Reserved.
// //       PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
// //       PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
// //       PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
// //       ULONG SizeOfImage;              //The size of the DLL image, in bytes.
// //    } LDR_DLL_UNLOADED_NOTIFICATION_DATA, *PLDR_DLL_UNLOADED_NOTIFICATION_DATA;

// //    typedef union _LDR_DLL_NOTIFICATION_DATA
// //    {
// //       LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
// //       LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
// //    } LDR_DLL_NOTIFICATION_DATA, *PLDR_DLL_NOTIFICATION_DATA;


// //    VOID CALLBACK LdrDllNotification(
// //    ULONG NotificationReason,
// //    PLDR_DLL_NOTIFICATION_DATA NotificationData,
// //    PVOID Context
// //    )
// //    {
// //       class ::exception_engine * pengine = (class ::exception_engine *)Context;
// //       if (NotificationReason == LDR_DLL_NOTIFICATION_REASON_LOADED)
// //       {

// //          cslock csl(&pengine->m_cs);

// //          HANDLE hprocess = SymGetProcessHandle();

// //          SymRefreshModuleList(hprocess);

// //       }

// //    }

// //    typedef NTSTATUS NTAPI FN_LdrUnregisterDllNotification(
// //    _In_ PVOID Cookie
// //    );
// //    typedef FN_LdrUnregisterDllNotification * PFN_LdrUnregisterDllNotification;


// //    PFN_LdrUnregisterDllNotification g_pLdrUnregisterDllNotification = nullptr;

// //    typedef VOID CALLBACK FN_LdrDllNotification(
// //    ULONG NotificationReason,
// //    PLDR_DLL_NOTIFICATION_DATA NotificationData,
// //    PVOID Context
// //    );
// //    typedef FN_LdrDllNotification * PFN_LdrDllNotification;

// //    typedef NTSTATUS NTAPI FN_LdrRegisterDllNotification(
// //    _In_     ULONG                          Flags,
// //    _In_     PFN_LdrDllNotification NotificationFunction,
// //    _In_opt_ PVOID                          Context,
// //    _Out_    PVOID                          *Cookie
// //    );
// //    typedef FN_LdrRegisterDllNotification * PFN_LdrRegisterDllNotification;


// //    PFN_LdrRegisterDllNotification g_pLdrRegisterDllNotification = nullptr;


// //    bool engine::init()
// //    {

// //       //if(!::file_system()->exists("C:\\acme\\exception_engine.txt"))
// //       //{
// //       //   return false;
// //       //}


// //       cslock csl(&m_cs);

// //       if (m_bInit)
// //       {

// //          return true;

// //       }

// //       HANDLE hprocess = SymGetProcessHandle();
// //       unsigned int  dwPid = get_current_process_id();

// //       // initializes
// //       //SymSetOptions(SymGetOptions()|SYMOPT_DEFERRED_LOADS|SYMOPT_LOAD_LINES);
// //       SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);
// //       //   SymSetOptions (SYMOPT_UNDNAME|SYMOPT_LOAD_LINES);
// //       if (!::SymInitialize(hprocess, 0, true))
// //       {
// //          unsigned int dw = ::GetLastError();
// //          informationf("Last Error = " + as_string(dw));
// //          ASSERT(0);

// //          //load_modules();
// //          return false;
// //       }

// //       if (g_pLdrUnregisterDllNotification == nullptr)
// //       {
// //          HINSTANCE h = LoadLibrary("Ntdll.dll");

// //          g_pLdrUnregisterDllNotification = (PFN_LdrUnregisterDllNotification) GetProcAddress(h, "LdrUnregisterDllNotification");
// //          g_pLdrRegisterDllNotification = (PFN_LdrRegisterDllNotification) GetProcAddress(h, "LdrRegisterDllNotification");

// //       }
// //       m_bInit = true;

// //       m_pvoidDllNotificationCookie = nullptr;

// //       if (g_pLdrUnregisterDllNotification != nullptr &&
// //             g_pLdrRegisterDllNotification != nullptr)
// //       {

// //          (*g_pLdrRegisterDllNotification)(0, &LdrDllNotification, this, &m_pvoidDllNotificationCookie);

// //       }

// //       return true;

// //    }

// // #endif














// // #ifdef WINDOWS_DESKTOP



// //    bool engine::fail() const
// //    {

// // //      return m_iRef == -1;
// //       return !m_bInit;

// //    }

// // #endif





// // #ifdef WINDOWS_DESKTOP




// //    void engine::clear()
// //    {

// //       cslock csl(&m_cs);

// //       if (!m_bInit)
// //       {

// //          return;

// //       }

// //       if (g_pLdrUnregisterDllNotification != nullptr)
// //       {
// //          (*g_pLdrUnregisterDllNotification)(&m_pvoidDllNotificationCookie);

// //       }

// //       VERIFY(SymCleanup(SymGetProcessHandle()));
// //       m_bInit = false;

// //    }

// // #endif




// //    void engine::reset()
// //    {

// //       cslock csl(&m_cs);

// // #ifdef WINDOWS_DESKTOP

// //       if (!m_bInit)
// //       {

// //          init();

// //       }
// //       else
// //       {
// //          HANDLE hprocess = SymGetProcessHandle();
// //          SymRefreshModuleList(hprocess);

// //       }
// // #endif

// //    }

// // #ifdef WINDOWS_DESKTOP


// //    bool engine::load_module(HANDLE hProcess, HMODULE hMod)
// //    {

// //       for(int i = 0; i < m_iHa; i++)
// //       {
// //          if(m_ha[i] == hMod)
// //             return true;
// //       }

// //       m_ha[m_iHa++] = hMod;

// //       char filename[MAX_PATH];
// //       if (!GetModuleFileNameA(hMod, filename, MAX_PATH))
// //       {

// //          return false;
// //       }

// //       HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, 0);
// //       if (hFile == INVALID_HANDLE_VALUE)
// //       {
// //          return false;
// //       }

// //       // "Debugging Applications" John Robbins
// //       // For whatever reason, SymLoadModule can return zero, but it still loads the modules. Sheez.
// //       set_last_error(ERROR_SUCCESS);
// //       if (!SymLoadModule(hProcess, hFile, filename, 0, (uptr)hMod, 0) && ERROR_SUCCESS != get_last_error())
// //       {
// //          ::CloseHandle(hFile);
// //          return false;
// //       }

// //       ::CloseHandle(hFile);

// //       return true;
// //    }


// // #endif






// // #ifdef WINDOWS_DESKTOP


// //    bool engine::xxxstack_trace(CONTEXT * pcontext, uptr uiSkip, const ::scoped_string & scopedstrFormat)
// //    {

// //       if(!pszFormat)
// //          return false;

// //       return xxxstack_trace(pcontext, uiSkip, false, pszFormat);

// //    }


// // #endif















// #ifdef WINDOWS_DESKTOP


// /////////////////////////////////////////////
// // prints a current thread's stack

//    struct current_context : CONTEXT
//    {
//       HANDLE   thread;
//       volatile int signal;
//    };

//    unsigned int WINAPI engine::stack_trace_ThreadProc(void * pvoidParam)

//    {


//       current_context * pcontext = reinterpret_cast<current_context*>(pvoidParam);


//       __try
//       {
//          // Konstantin, 14.01.2002 17:21:32
//          // must wait in spin lock until Main thread will leave a ResumeThread (must return back to ::account::user context)
//          int iInverseAgility = 26 + 33; // former iPatienceQuota
//          int iPatience = iInverseAgility;
//          while(pcontext->signal && iPatience > 0)
//          {
//             if(!SwitchToThread())
//                sleep(10_ms); // forces switch to another thread
//             iPatience--;
//          }

//          //         char sz[200];
//          //         sprintf(sz, "engine::xxxstack_trace patience near down %u%%\n", iPatience * 100 / iInverseAgility);
//          //         ::information(sz);

//          if (-1 == SuspendThread(pcontext->thread))
//          {
//             pcontext->signal  = -1;
//             __leave;
//          }

//          __try
//          {
// #ifdef AMD64
//             GET_CURRENT_CONTEXT(pcontext, USED_CONTEXT_FLAGS);
// #else
//             pcontext->signal = GetThreadContext(pcontext->thread, pcontext) ? 1 : -1;
// #endif
//          }
//          __finally
//          {
//             VERIFY(-1 != ResumeThread(pcontext->thread));
//          }
//       }
//       __except(EXCEPTION_EXECUTE_HANDLER)
//       {
//          pcontext->signal  = -1;
//       }
//       return 0;
//    }

// #endif






// //    char * engine::xxxstack_trace(iptr uiSkip, void * caller_address, const ::scoped_string & scopedstrFormat, int iCount)
// //    {

// //       cslock csl(&m_cs);

// //       *_strS = '\0';

// // #ifdef WINDOWS_DESKTOP

// //       if (!pszFormat) return false;

// //       // attempts to get current thread's context

// // #if FAST_STACK_TRACE
// //       xxxstack_trace(nullptr, uiSkip, false, pszFormat);

// // #else

// //       current_context context;
// //       memory_set(&context, 0, sizeof(current_context));

// //       bool bOk = DuplicateHandle(GetCurrentProcess(), current_htask(), GetCurrentProcess(), &context.thread, 0, 0, DUPLICATE_SAME_ACCESS) != false;

// //       _ASSERTE(bOk);
// //       _ASSERTE(context.thread);

// //       if (!bOk || !context.thread)
// //          return false;

// //       context.ContextFlags = CONTEXT_CONTROL; // CONTEXT_FULL;
// //       context.signal = -1;


// //       GET_CURRENT_CONTEXT((&context), USED_CONTEXT_FLAGS);

// //       xxxstack_trace(&context, uiSkip, false, pszFormat);


// // #endif



// //       return true;
// // #elif defined(UNIVERSAL_WINDOWS) || defined(SOLARIS)

// //       return _strS;

// // #elif defined(__ANDROID__)

// //       const size_t maximum = 30;

// //       void* buffer[maximum];

// //       int iSkip = minimum(uiSkip, maximum - 1);

// //       if (iSkip == maximum - 1)
// //       {

// //          strcpy(_strS, "");

// //          return _strS;

// //       }

// //       int iCount = captureBacktrace(buffer, maximum);

// //       ansi_count_copy(_strS, dumpBacktrace(&buffer[iSkip], iCount - iSkip), sizeof(_strS));

// //       return _strS;

// // #else

// //       void * array[64];

// //       int size = ::xxxbacktrace(array, 64);

// //       if(caller_address != nullptr)
// //       {

// //          array[1] = caller_address;

// //       }

// //       return xxxstack_trace(array, size);


// // #endif



// //    }





// #ifdef WINDOWS_DESKTOP


//    bool engine::xxxstack_trace(CONTEXT * pcontext, uptr uiSkip, bool bSkip, const ::scoped_string & scopedstrFormat)
//    {

//       *_strS = '\0';

//       if (!stack_first(pcontext))
//       {

//          return false;

//       }

//       uptr uiSkipStart = uiSkip;

//       int iLine;

//       do
//       {

//          if (!uiSkip && !bSkip || uiSkip == DEFAULT_SE_EXCEPTION_callstack_SKIP)
//          {

//             iLine = 0;

//             char * psz = get_frame(scopedstrFormat, iLine);

//             if (uiSkip == DEFAULT_SE_EXCEPTION_callstack_SKIP)
//             {

//                if (::str::case_insensitive_find("KiUserExceptionDispatcher", psz) >= 0)
//                {

//                   uiSkip = 0;

//                }

//                continue;

//             }
//             else if (uiSkipStart == DEFAULT_SE_EXCEPTION_callstack_SKIP)
//             {

//                if (iLine == 0)
//                {

//                   break;

//                }

//             }

//             ansi_concatenate(_strS, psz);

//          }
//          else
//          {

//             --uiSkip;

//          }

//       }
//       while(stack_next());

//       return true;

//    }

// #if OSBIT == 32
//    char * engine::xxxstack_trace(unsigned int * pinteraction, int c, const ::scoped_string & scopedstrFormat)
// #else
//    char * engine::xxxstack_trace(DWORD64 * pinteraction, int c, const ::scoped_string & scopedstrFormat)
// #endif
//    {

//       cslock csl(&m_cs);

//       *_strS = '\0';

//       ::memory_copy(m_uia, pinteraction, minimum(c*sizeof(*pinteraction), sizeof(m_uia)));

//       m_iAddressWrite = c;
//       m_iAddressRead = 0;
//       char * psz;

//       int iLine;

//       do
//       {

//          iLine = 0;

//          psz = get_frame(scopedstrFormat, iLine);

//          if (scopedstr == nullptr)
//          {

//             break;

//          }

//          ansi_concatenate(_strS, psz);

//       }
//       while (stack_next());

//       return _strS;
//    }

// #endif

// #if defined(WINDOWS_DESKTOP)


//    char * engine::get_frame(const ::scoped_string & scopedstrFormat, int & iLine)
//    {


//       *_str = '\0';
//       *_strBuf = '\0';
//       *_strFile = '\0';
//       *_strSymbol = '\0';

//       unsigned int uiLineDisplacement = 0;
//       unsigned int uiLineNumber = 0;
// #if OSBIT == 32
//       unsigned int uiSymbolDisplacement = 0;
// #else
//       DWORD64 uiSymbolDisplacement = 0;
// #endif

//       char sz[2];
//       sz[1] = '\0';
//       for (char * point = (char *)pszFormat; *point; ++point)
//       {
//          if (*point == '%')
//          {
//             ++point; // skips '%'
//             char ca = *point;
//             switch (ca)
//             {
//             case 'm':
//                if(module(_strBuf, sizeof(_strBuf)))
//                {
//                   ansi_concatenate(_str, _strBuf);
//                }
//                else
//                {
//                   ansi_concatenate(_str, "?.?");
//                }
//                break;
//             case 'f':
//                if(*_strFile == '\0')
//                {
//                   if(!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
//                   {
//                      strcpy(_strFile, " ");
//                   }
//                }
//                ansi_concatenate(_str, _strFile);
//                break;
//             case 'l':
//                if (*_strFile == '\0')
//                {
//                   if(!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
//                   {
//                      strcpy(_strFile, " ");
//                   }
//                }
//                if (*(point + 1) == 'd')
//                {
//                   ansi_from_unsigned_long_long(_strBuf, uiLineDisplacement, 10);
//                   ansi_concatenate(_str, _strBuf);
//                   ++point;
//                }
//                else
//                {
//                   ansi_from_unsigned_long_long(_strBuf, uiLineNumber, 10);
//                   ansi_concatenate(_str, _strBuf);
//                }
//                break;
//             case 's':
//                if(*_strSymbol == '\0')
//                {
//                   if(!symbol(_strSymbol, sizeof(_strSymbol), &uiSymbolDisplacement))
//                   {
//                      strcpy(_strSymbol, "?()");
//                   }
//                }
//                if (*(point + 1) == 'd')
//                {
//                   ansi_from_unsigned_long_long(_strBuf, uiSymbolDisplacement, 10);
//                   ansi_concatenate(_str, _strBuf);
//                   ++point;
//                }
//                else
//                {
//                   if (ansi_count_compare(_strSymbol, "dispatch::AddMessageHandler", strlen("dispatch::AddMessageHandler")) == 0)
//                   {
// //                     strcpy(_strS, "\n");
//                      //                   ansi_concatenate(_strS, _strSymbol);
//                      //                 ansi_concatenate(_strS, "\n");
//                      //               return nullptr;
//                      ansi_concatenate(_strS, " * * * ");
//                   }
//                   ansi_concatenate(_str, _strSymbol);
//                }
//                break;
//             case '%':
//                ansi_concatenate(_str, "%");
//                break;
//             default:
//                ansi_concatenate(_str, "%");
//                sz[0] = ca;
//                ansi_concatenate(_str, sz);
//                break;
//             }
//          }
//          else
//          {
//             sz[0] = *point;
//             ansi_concatenate(_str, sz);
//          }

//       }

//       iLine = uiLineNumber;

//       return _str;

//    }

// #elif defined(__APPLE__)

//    void engine::backtrace(void **pinteraction, int &c)
//    {

//       cslock csl(&m_cs);

//       unsigned int maxframes = c;

//       c = ::backtrace(pinteraction, maxframes);

//    }

//    char * engine::xxxstack_trace(void * const * pinteraction, int c, const ::scoped_string & scopedstrFormat)
//    {

//       char ** messages = backtrace_symbols(pinteraction, c);

//       char szN[24];

//       *_strS = '\0';

//       char syscom[1024];

//       const char * func;
//       const char * file;
//       unsigned iLine;

//       for (int i = 1; i < c && messages != nullptr; ++i)
//       {

//          char *mangled_name = 0, *offset_begin = 0, *offset_end = 0;

//          // find parantheses and +address offset surrounding mangled name
//          for (char *point = messages[i]; *point; ++point)
//          {

//             if (*point == '(')
//             {

//                mangled_name = point;

//             }
//             else if (*point == '+')
//             {

//                offset_begin = point;

//             }
//             else if (*point == ')')
//             {

//                offset_end = point;

//                break;

//             }

//          }

//          if (mangled_name && offset_begin && offset_end && mangled_name < offset_begin)
//          {

//             *mangled_name++ = '\0';
//             *offset_begin++ = '\0';
//             *offset_end++ = '\0';

//             string real_name = get_demangle(mangled_name);

//             ansi_concatenate(_strS, "[bt]: (");
//             ansi_from_unsigned_long_long(szN, i, 10);
//             ansi_concatenate(_strS, szN);
//             ansi_concatenate(_strS, ") ");
//             ansi_concatenate(_strS, messages[i]);
//             ansi_concatenate(_strS, " : ");

//             ansi_concatenate(_strS, real_name);

//             ansi_concatenate(_strS, "+");
//             ansi_concatenate(_strS, offset_begin);
//             ansi_concatenate(_strS, offset_end);
//             ansi_concatenate(_strS,"\n");

//          }
//          else
//          {

//             ansi_concatenate(_strS, "[bt]: (");
//             ansi_from_unsigned_long_long(szN, i, 10);
//             ansi_concatenate(_strS, szN);
//             ansi_concatenate(_strS, ") ");
//             ansi_concatenate(_strS, messages[i]);

//          }

//          ansi_concatenate(_strS,"\n");

//       }

//       return _strS;

//    }


// #elif defined(LINUX) || defined(MACOS)

//    void engine::backtrace(void ** ppui, int &c)
//    {

//       synchronous_lock synchronouslock(this->synchronization());

//       unsigned int maxframes = c;

//       c = ::backtrace(ppui, maxframes);

//    }

//    char * engine::xxxstack_trace(void * const * ppui, int c, const ::scoped_string & scopedstrFormat)
//    {

//       char ** messages = backtrace_symbols(ppui, c);

//       char szN[24];

//       *_strS = '\0';

//       char syscom[1024];

//       const char * func;
//       const char * file;
//       unsigned iLine;

//       for (int i = 1; i < c && messages != nullptr; ++i)
//       {
// #ifdef __USE_BFD

//          if(resolve_addr_file_func_line(((void **)ppui)[i], &file, &func, iLine))
//          {


//             ansi_concatenate(_strS, file);
//             ansi_concatenate(_strS, ":");
//             ansi_from_unsigned_long_long(szN, iLine, 10);
//             ansi_concatenate(_strS, szN);
//             ansi_concatenate(_strS, ":1: warning: ");

//          }
// #endif // __USE_BFD

//          char *mangled_name = 0, *offset_begin = 0, *offset_end = 0;

//          // find parantheses and +address offset surrounding mangled name
//          for (char *point = messages[i]; *point; ++point)
//          {

//             if (*point == '(')
//             {

//                mangled_name = point;

//             }
//             else if (*point == '+')
//             {

//                offset_begin = point;

//             }
//             else if (*point == ')')
//             {

//                offset_end = point;

//                break;

//             }

//          }

//          if (mangled_name && offset_begin && offset_end && mangled_name < offset_begin)
//          {

//             *mangled_name++ = '\0';
//             *offset_begin++ = '\0';
//             *offset_end++ = '\0';

//             int status;

//             char * real_name = abi::__cxa_demangle(mangled_name, 0, 0, &status);

//             ansi_concatenate(_strS, "[bt]: (");
//             ansi_from_unsigned_long_long(szN, i, 10);
//             ansi_concatenate(_strS, szN);
//             ansi_concatenate(_strS, ") ");
//             ansi_concatenate(_strS, messages[i]);
//             ansi_concatenate(_strS, " : ");

//             if (status == 0)
//             {

//                ansi_concatenate(_strS, real_name);

//             }
//             else
//             {

//                ansi_concatenate(_strS, mangled_name);

//             }

//             ansi_concatenate(_strS, "+");
//             ansi_concatenate(_strS, offset_begin);
//             ansi_concatenate(_strS, offset_end);
//             ansi_concatenate(_strS,"\n");

//             if(real_name != nullptr)
//             {

//                free(real_name);

//             }

//          }
//          else
//          {

//             ansi_concatenate(_strS, "[bt]: (");
//             ansi_from_unsigned_long_long(szN, i, 10);
//             ansi_concatenate(_strS, szN);
//             ansi_concatenate(_strS, ") ");
//             ansi_concatenate(_strS, messages[i]);

//          }

//          ansi_concatenate(_strS,"\n");

//       }

//       return _strS;

//    }


// #endif


// } // namespace exception

// #ifdef __USE_BFD

// #define _GNU_SOURCE
// #include <stdio.h>

// #include <dlfcn.h>

// #include <execinfo.h>
// #include <signal.h>
// #include <bfd.h>
// #undef USE_MISC


// /* globals retained across calls to resolve. */
// static const char * moda[]= {"/ca2/stage/x86/libaura.so", "/ca2/stage/x86/libbase.so", "/ca2/stage/x86/libcore.so", nullptr};
// static bfd* abfda[64];
// static asymbol **symsa[64];
// static asection *texta[64];
// static int bfdcount = 0;

// int free_resolve_addr_file_func_line()
// {

//    int i = 0;

//    while(i < 64)
//    {

//       if(abfda[i] == nullptr)
//       {

//          return i;

//       }

//       i++;

//    }

//    return -1;

// }

// bool prep_resolve_addr_file_func_line(const char * f)
// {

//    int i = free_resolve_addr_file_func_line();

//    if(i < 0)
//    {

//       return false;

//    }

//    bfd* & abfd = abfda[i];

//    asymbol ** & syms = symsa[i];

//    asection * & text = texta[i];

//    abfd = bfd_openr(f, 0);

//    if (!abfd)
//    {

//       perror("bfd_openr failed: ");

//       return false;

//    }

//    /* oddly, this is required for it to work... */
//    bfd_check_format(abfd,bfd_object);

//    unsigned storage_needed = bfd_get_symtab_upper_bound(abfd);

//    syms = (asymbol **) malloc(storage_needed);

//    unsigned cSymbols = bfd_canonicalize_symtab(abfd, syms);

//    text = bfd_get_section_by_name(abfd, ".text");

//    return true;

// }


// void init_resolve_addr_file_func_line()
// {

//    if(bfdinit)
//       return;

//    bfdinit = 1;

//    zero(abfda);

//    zero(symsa);

//    zero(texta)

//    bfd_init();

//    char ename[1024];

//    int l = readlink("/proc/self/exe",ename,sizeof(ename));

//    if (l == -1)
//    {

//       perror("failed to find executable\n");

//       return false;

//    }

//    ename[l] = 0;

//    prep_resolve_addr_file_func_line(ename);

//    const char ** point = (const char **) moda;

//    while(*point)
//    {

//       if(prep_resolve_addr_file_func_line(*point))
//       {
//          bfdcount++;

//       }

//       point++;

//    }

// }

// bool resolve_addr_file_func_line1(bfd* abfd, asymbol **syms, asection *text, void *address, const char * * filename, const char ** func, unsigned & iLine)
// {
//    long offset = ((long)address) - text->vma;
//    if (offset > 0)
//    {
//       *filename = nullptr;
//       *func = nullptr;

//       if (bfd_find_nearest_line(abfd, text, syms, offset, filename, func, &iLine) && *filename)
//          return true;
//       return false;
//    }
//    return false;
// }


// bool resolve_addr_file_func_line(void *address, const char * * filename, const char ** func, unsigned & iLine)
// {
//    int i;
//    while(i < bfdcount)
//    {

//       if(resolve_addr_file_func_line1(abfda[i], symsa[i], texta[i],address, filename, func, iLine))
//          return true;

//       i++;

//    }
//    return false;
// }


// #endif
