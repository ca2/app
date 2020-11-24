#include "framework.h"
//#include "acme/node/ansios/ansios.h"
#include "_linux.h"


#ifdef IMPLEMENT_VISTA_TOOLS

#define ASSERT_HERE ASSERT(FALSE)

/*#if ( NTDDI_VERSION < NTDDI_LONGHORN )
#   error NTDDI_VERSION must be defined as NTDDI_LONGHORN or later
#endif*/

//////////////////////////////////////////////////////////////////
// if ASSERT was not defined already, let's define our own version,
// to use the CRT assert()

/*#ifndef ASSERT
#   ifdef __DEBUG
#      include <assert.h>
#      define ASSERT(x) assert( x )
#      define ASSERT_HERE assert( FALSE )
#   else // __DEBUG
#      define ASSERT(x)
#      define ASSERT_HERE
#   endif //!__DEBUG
#endif//ASSERT*/

///////////////////////////////////////////////////////////////////
// a handy macro to get the number of characters (not bytes!)
// a string buffer can hold

#ifndef _tsizeof
#   define _tsizeof( s )  (sizeof(s)/sizeof(s[0]))
#endif//_tsizeof



namespace VistaTools
{

///////////////////////////////////////////////////////////////

// macros to handle the functions implemented in a DLL properly

//////////////////////////////////////////////////////////
// MyShellExec is just a wrapper around a call to ShellExecuteEx,
// to be able to specify the verb easily.

   int_bool
   MyShellExec(   HWND hwnd,
                  const char * pszVerb,
                  const char * pszPath,
                  const char * pszParameters,   // = nullptr
                  const char * pszDirectory,   // = nullptr
                  HANDLE * phProcess )   // = nullptr
   {
      SHELLEXECUTEINFO shex;

      __memset( &shex, 0, sizeof( shex) );

      shex.cbSize         = sizeof( SHELLEXECUTEINFO );
      shex.fMask         = (phProcess ? SEE_MASK_NOCLOSEPROCESS : 0);
      shex.hwnd         = hwnd;
      shex.pVerb         = pszVerb;

      shex.pFile         = pszPath;

      shex.pParameters   = pszParameters;

      shex.pDirectory   = pszDirectory;

      shex.nShow         = SW_NORMAL;

      int_bool bRet = ::ShellExecuteEx( &shex );

      if ( phProcess )
         *phProcess = shex.hProcess;

      return bRet;
   }

   int_bool IsVista()
   {
      OSVERSIONINFO osver;

      osver.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

      if (   ::GetVersionEx( &osver ) &&
             osver.dwPlatformId == VER_PLATFORM_WIN32_NT &&
             (osver.dwMajorVersion >= 6 ) )
         return TRUE;

      return FALSE;
   }

#ifndef WIN64 // we need this when compiling 32-bit code only

   typedef int_bool (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE hProcess,PBOOL Wow64Process);

   LPFN_ISWOW64PROCESS fnIsWow64Process =
   (LPFN_ISWOW64PROCESS)::GetProcAddress( ::GetModuleHandle("kernel32"),"IsWow64Process");

   int_bool
   IsWow64()
   {
      int_bool bIsWow64 = FALSE;

      if (nullptr != fnIsWow64Process)
      {
         if ( !fnIsWow64Process( ::GetCurrentProcess(),&bIsWow64) )
         {
            ASSERT_HERE;
         }
      }

      return bIsWow64;
   }

#endif//WIN64

   HRESULT
   GetElevationType( __out TOKEN_ELEVATION_TYPE * ptet )
   {
      if ( !IsVista() )
         return E_FAIL;

      ASSERT( ptet );

      HRESULT hResult = E_FAIL; // assume an error occurred
      HANDLE hToken   = nullptr;

      if ( !::OpenProcessToken(
            ::GetCurrentProcess(),
            TOKEN_QUERY,
            &hToken ) )
      {
         ASSERT_HERE;
         return hResult;
      }

      ::u32 dwReturnLength = 0;

      if ( !::GetTokenInformation(
            hToken,
            TokenElevationType,
            ptet,
            sizeof( *ptet ),
            &dwReturnLength ) )
      {
         ASSERT_HERE;
      }
      else
      {
         ASSERT( dwReturnLength == sizeof( *ptet ) );
         hResult = S_OK;
      }

      ::CloseHandle( hToken );

      return hResult;
   }

   HRESULT
   IsElevated( __out_opt int_bool * pbElevated ) //= nullptr )
   {
      if ( !IsVista() )
         return E_FAIL;

      HRESULT hResult = E_FAIL; // assume an error occurred
      HANDLE hToken   = nullptr;

      if ( !::OpenProcessToken(
            ::GetCurrentProcess(),
            TOKEN_QUERY,
            &hToken ) )
      {
         ASSERT_HERE;
         return hResult;
      }

      TOKEN_ELEVATION te = { 0 };
      ::u32 dwReturnLength = 0;

      if ( !::GetTokenInformation(
            hToken,
            TokenElevation,
            &te,
            sizeof( te ),
            &dwReturnLength ) )
      {
         ASSERT_HERE;
      }
      else
      {
         ASSERT( dwReturnLength == sizeof( te ) );

         hResult = te.TokenIsElevated ? S_OK : S_FALSE;

         if ( pbElevated)
            *pbElevated = (te.TokenIsElevated != 0);
      }

      ::CloseHandle( hToken );

      return hResult;
   }

////////////////////////////////
// RunElevated simply calls ShellExecuteEx with the verb "runas" to start the elevated process.
// I wish there was a just as easy way to start a non-elevated process, as well.

   int_bool
   RunElevated(
   __in      HWND   hwnd,
   __in      const char * pszPath,
   __in_opt   const char * pszParameters,   //   = nullptr,
   __in_opt   const char * pszDirectory,   //   = nullptr,
   __out_opt   HANDLE *phProcess )      //   = nullptr );
   {
      return MyShellExec(
             hwnd,
             IsVista() ? "runas" : nullptr,
             pszPath,
             pszParameters,
             pszDirectory,
             phProcess );
   }

#ifndef DONTWANT_RunNonElevated
///////////////////////////////////////
// RunNonElevated() implementation

///////////////////////////////////////////////////
//   The shared data, to be able to share
//   data between ours and the shell proceses

#pragma section( "ve_shared", read, write, shared )

   __declspec(allocate("ve_shared"))
   HHOOK   hVEHook                     = nullptr;

   __declspec(allocate("ve_shared"))
   ::u32   uVEMsg                     = 0;

   __declspec(allocate("ve_shared"))
   int_bool   bVESuccess                  = FALSE;

   __declspec(allocate("ve_shared"))
   char   szVE_Path[ MAX_PATH ]         = "";

   __declspec(allocate("ve_shared"))
   char   szVE_Parameters[ MAX_PATH ]      = "";

   __declspec(allocate("ve_shared"))
   char   szVE_Directory[ MAX_PATH ]      = "";

   __declspec(allocate("ve_shared"))
   int_bool    bVE_NeedProcessHandle         = FALSE;

   __declspec(allocate("ve_shared"))
   HANDLE   hVE_Process               = nullptr;

//////////////////////////////////e
// the hook callback routine, it is called in the context of th shell proces

   LRESULT CALLBACK
   VistaEelevator_HookProc_MsgRet( int code, WPARAM wParam, LPARAM lParam )
   {
      if ( code >= 0 && lParam )
      {
         CWPRETSTRUCT * pwrs = (CWPRETSTRUCT *)lParam;

         if (pwrs->message == uVEMsg )
         {
            bVESuccess = VistaTools::MyShellExec(
                         pwrs->hwnd,
                         nullptr,
                         szVE_Path,
                         szVE_Parameters,
                         szVE_Directory,
                         bVE_NeedProcessHandle ? &hVE_Process : nullptr );
         }
      }

      return ::CallNextHookEx( hVEHook, code, wParam, lParam );
   }

////////////////////////////////////////////////////////////
// The code below needs to call GetModuleHandleEx,
// but it is available on Windows XP and Vista only.
// To make the code run under Windows 2000 as well, we will
// link to GetModuleHandleEx dynamically:

   typedef
   WINBASEAPI
   int_bool
   (WINAPI
    *PGetModuleHandleExW)(
    __in        ::u32    dwFlags,
    __in_opt    const unichar * pModuleName,

    __out HMODULE* phModule
    );

   static PGetModuleHandleExW pGetModuleHandleExW = nullptr;

   int_bool
   RunNonElevated(
   __in      HWND   hwnd,
   __in      const char * pszPath,
   __in_opt   const char * pszParameters,   //   = nullptr,
   __in_opt   const char * pszDirectory,   //   = nullptr,
   __out_opt   HANDLE *phProcess)      //   = nullptr );
   {
      ASSERT( pszPath && *pszPath );   // other args are optional

      ASSERT( pszPath );

      // Determine whether we can use the regular ShellExecuteEx
      // We can use it if we are not running Vista, or if this process is already non-elevated,
      // or if the current ::account::user account has no "split" token (and therefore has no distinction
      // between the elevated and non-elevated proceses

      TOKEN_ELEVATION_TYPE tet;

      if (   !IsVista() ||
             FAILED( GetElevationType( &tet ) ) ||
             tet != TokenElevationTypeFull )
      {
         // if the current process is not elevated, we can use ShellExecuteEx directly!

         return MyShellExec( hwnd,
                             nullptr,
                             pszPath,
                             pszParameters,
                             pszDirectory,
                             phProcess );
      }

#ifndef WIN64

      // If 32-bit code is executing under x64 version of Windows, it will not work, because
      // the shell is a 64-bit process, and to hook it successfully this code needs to be 64-bit as well

      if ( IsWow64() )
      {
         ASSERT_HERE;
         return FALSE;
      }

#endif//WIN64


      //////////////////////////////////////////////
      //
      // How this code works:
      //
      // To start a non-elevated process, we need to inject our code into a non-elevated
      // process already running on the target computer. Since Windows shell is non-elevated,
      // and we can safely assume it to always run, (when was the last time you saw Windows
      // running without its shell?), we will try to inject our code into the shell process.
      //
      // To inject the code, we will install a global hook, and send a message to
      // a ::ca::user::interaction_impl created by the shell. This will cause our hook callback routine to be executed
      // in the context of the shell proces.
      //
      // Because this trick uses a global hook, the hook routine must be in a DLL.
      //

      /////////////////////
      // First, register a private message, to communicate with the (hooked) shell process

      if ( !uVEMsg )
         uVEMsg = ::RegisterWindowMessage( "VistaElevatorMsg" );

      //////////////////////////////////////
      // find the shell ::ca::user::interaction_impl (the desktop)

      HWND hwndShell = ::FindWindow( "Progman", nullptr);

      if ( !hwndShell )
      {
         ASSERT_HERE;
         return FALSE;
      }

      if ( !hwnd )
         hwnd = ::GetForegroundWindow();

      // Link (dynamically) to the GetModuleHandleExW API:

      if ( !pGetModuleHandleExW )
      {
         pGetModuleHandleExW = (PGetModuleHandleExW)::GetProcAddress(
                               ::GetModuleHandle( "Kernel32" ), "GetModuleHandleExW" );
      }

      if ( !pGetModuleHandleExW )
      {
         ASSERT_HERE;
         return FALSE;
      }

      HMODULE hModule = nullptr;   // we need to know hModule of this DLL to install a global hook

      if ( !pGetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (const unichar *)VistaEelevator_HookProc_MsgRet,
            &hModule ) )
      {
         ASSERT_HERE;
         return FALSE;
      }

      /////////////////////////////////////////
      // Install a global hook, to inject our code into the shell proces

      hVEHook = ::SetWindowsHookEx( WH_CALLWNDPROCRET,   // hook called after SendMessage() !!!
                                    (HOOKPROC)VistaEelevator_HookProc_MsgRet, hModule, 0);

      if ( !hVEHook )
      {
         ASSERT_HERE;
         return FALSE;
      }

      //////////////////////////////////
      // Prepare the parameters for launching the non-elevated process
      // from the hook callback routine (they are placed into the shared data section)

      if (!( ansi_count_copy(
             szVE_Path,
             pszPath, _tsizeof(szVE_Path) ) ) )
      {
         ASSERT_HERE;
         return FALSE;
      }

      if (!( ansi_count_copy(
             szVE_Parameters,

             pszParameters ? pszParameters : "",
             _tsizeof(szVE_Parameters)) ) )
      {
         ASSERT_HERE;
         return FALSE;
      }

      if ( FAILED( ansi_count_copy(
                   szVE_Directory,
                   pszDirectory ? pszDirectory : "",
                   _tsizeof(szVE_Directory)) ) )
      {
         ASSERT_HERE;
         return FALSE;
      }

      bVE_NeedProcessHandle = (phProcess != nullptr);

      /////////////////////////////////////////
      // Activate our hook callback routine:

      bVESuccess = FALSE; // assume failure

      ::SendMessage( hwndShell, uVEMsg, 0, 0 );

      ////////////////////////////////////////////////////////
      // At this point our hook routine has been executed!

      if ( phProcess )
         *phProcess = hVE_Process;

      /////////////////////////////////////
      // The hook is no longer needed, remov it:

      ::UnhookWindowsHookEx( hVEHook );
      hVEHook = nullptr;

      //////////////////////
      // All done!

      return bVESuccess;
   }
#endif //DONTWANT_RunNonElevated

} // namespace VistaTools

#endif// IMPLEMENT_VISTA_TOOLS
