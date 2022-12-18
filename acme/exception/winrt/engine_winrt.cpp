#include "framework.h"
#include <malloc.h>






// The following is defined for x86 (XP and higher), x64 and IA64:
#define GET_CURRENT_CONTEXT(pc, contextFlags) \
   do { \
   memory_set(pc, 0, sizeof(CONTEXT)); \
   pc->ContextFlags = contextFlags; \
   RtlCaptureContext(pc); \
   } while(0);







HANDLE SymGetProcessHandle()
{

   return GetCurrentProcess();

}


namespace exception
{

   typedef int_bool(__stdcall *PReadProcessMemoryRoutine)(
   HANDLE      hProcess,
   DWORD64     qwBaseAddress,
   PVOID       lpBuffer,
   u32       nSize,
   LPDWORD     lpNumberOfBytesRead,
   LPVOID      pUserData  // optional data, which was passed in "ShowCallstack"
   );

   // The following is used to pass the "userData"-Pointer to the user-provided readMemoryFunction
   // This has to be done due to a problem with the "hProcess"-parameter in x64...
   // Because this class is in no case multi-threading-enabled (because of the limitations
   // of dbghelp.dll) it is "safe" to use a static-variable

   static PReadProcessMemoryRoutine s_readMemoryFunction = nullptr;
   static LPVOID s_readMemoryFunction_UserData = nullptr;

   engine::engine(::particle * pparticle) :
      matter(pparticle)
   {

   }


   engine::~engine()
   {

   }


   void engine::reset()
   {

   }


   char * engine::xxxstack_trace(uptr uiSkip, void * caller_address, const char * pszFormat)
   {

      return nullptr;

   }


} // namespace exception
