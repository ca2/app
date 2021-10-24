///////////////////////////////
/* VistaTools.cxx - version 2.1

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 2007.  WinAbility Software Corporation.

Author: Andrei Belogortseff [ http://www.winability.com ]

TERMS OF USE: You are free to use this file in any way you like,
for both the commercial and non-commercial purposes, royalty-free,
AS ::i32 AS you agree with the warranty disclaimer above,
EXCEPT that you may not remov or modify this or any of the
preceeding paragraphs. If you make any changes, please document
them in the MODIFICATIONS section below. If the changes are of general
interest, please let us know and we will consider incorporating them in
this file, as well.

If you use this file in your own project, an acknowledgement will be appreciated,
although it's not required.

SUMMARY:

This file contains several Vista-specific functions helpful when dealing with the
"elevation" features of Windows Vista. See the descriptions of the functions below
for information on what each function does and how to use it.

This file contains the Win32 stuff only, it can be used with or without other frameworks,
such as ca2 API, gen, etc.

HOW TO USE THIS FILE:

Make sure you have the latest Windows SDK (see msdn.microsoft.com for more information)
or this file may not compile!

This is a "combo" file that contains both the declarations (usually placed in the .h files)
as well as the definitions (usually placed in the .cpp files) of the functions.

To get the declarations only, include it as you would any .h file, for example:

//#include "VistaTools.cxx"

To get both the declarations and definitions, define IMPLEMENT_VISTA_TOOLS before including the file:

#define IMPLEMENT_VISTA_TOOLS
//#include "VistaTools.cxx"

(The above should be done once and only once per project).

To use the function RunNonElevated, this file must be compiled into a DLL.
In such a case, define DLL_EXPORTS when compiling the DLL,
and do not define DLL_EXPORTS when compiling the projects linking to the DLL.

If you don't need to use RunNonElevated, then this file may be a part of an EXE
project. In such a case, define DONTWANT_RunNonElevated and NO_DLL_IMPORTS to make
this file compile properly.

NOTE: The file VistaTools.cxx can be included in the VisualStudio projects, but it should be
excluded from the build process (because its contents is compiled when it is included
in another .cpp file with IMPLEMENT_VISTA_TOOLS defined, as shown above.)

MODIFICATIONS:

   v.2.1 (2007-May-20, by Andrei Belogortseff)

      Removed the deprecated function RunAsStdUser.

      Updated RunElevated and RunNonElevated so that if they are called under
      a pre-Vista version of Windows, they would run the application as usual,
      without raising an assertion.

      Enclosed the VistaTools APIs inside of the namespace VistaTools.

      Updated MyShellExec, RunElevated and RunNonElevated: added
      optional phProcess argument.

      Changed the call to GetModuleHandleEx to dynamic linking,
      to make the code work with Windows 2000.

      Made several cosmetic changes.

   v.2.0 (2007-Feb-20, by Andrei Belogortseff)

      Deprecated RunAsStdUser().

      emented RunNonElevated() to replace RunAsStdUser().

      Added function declarations for use in a DLL project.

   v.1.0 (2006-Dec-16, by Andrei Belogortseff)

      The first release.
*/

#include "framework.h"
//#include "universal_windows.h"

#ifdef IMPLEMENT_VISTA_TOOLS

#define ASSERT_HERE ASSERT(false)

/*#if ( NTDDI_VERSION < NTDDI_LONGHORN )
#   error NTDDI_VERSION must be defined as NTDDI_LONGHORN or later
#endif*/

//////////////////////////////////////////////////////////////////
// if ASSERT was not defined already, let's define our own version,
// to use the CRT assert()

// #ifndef ASSERT
// #   ifdef __DEBUG
// #      include <assert.h>
// #      define ASSERT(x) assert( x )
// #      define ASSERT_HERE assert( false )
// #   else// __DEBUG
// #      define ASSERT(x)
// #      define ASSERT_HERE
// #   endif//__DEBUG
// #endif//ASSERT

///////////////////////////////////////////////////////////////////
// a handy macro to get the number of characters (not bytes!)
// a string buffer can hold

#ifndef _tsizeof
#   define _tsizeof( s )  (sizeof(s)/sizeof(s[0]))
#endif//_tsizeof

#ifdef WINDOWS_DESKTOP


namespace VistaTools
{

///////////////////////////////////////////////////////////////

// macros to handle the functions implemented in a DLL properly

//////////////////////////////////////////////////////////
// MyShellExec is just a wrapper around a call to ShellExecuteEx,
// to be able to specify the verb easily.

   bool
   MyShellExec(   oswindow hwnd,
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
      shex.lpVerb         = pszVerb;
      shex.lpFile         = pszPath;
      shex.lpParameters   = pszParameters;
      shex.lpDirectory   = pszDirectory;
      shex.nShow         = SW_NORMAL;

      bool bRet = ::ShellExecuteEx( &shex ) != false;

      if ( phProcess )
         *phProcess = shex.hProcess;

      return bRet;
   }

   bool IsVista()
   {
      OSVERSIONINFO osver;

      osver.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

      if (   ::GetVersionEx( &osver ) &&
             osver.dwPlatformId == VER_PLATFORM_WIN32_NT &&
             (osver.dwMajorVersion >= 6 ) )
         return true;

      return false;
   }

#ifndef WIN64 // we need this when compiling 32-bit code only

   typedef bool (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE hProcess,PBOOL Wow64Process);

   LPFN_ISWOW64PROCESS fnIsWow64Process =
   (LPFN_ISWOW64PROCESS)::GetProcAddress( ::GetModuleHandle("kernel32"),"IsWow64Process");

   bool
   IsWow64()
   {
      BOOL bIsWow64 = false;

      if (nullptr != fnIsWow64Process)
      {
         if ( !fnIsWow64Process( ::GetCurrentProcess(),&bIsWow64) )
         {
            ASSERT_HERE;
         }
      }

      return bIsWow64 != false;
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
   IsElevated( __out_opt bool * pbElevated ) //= nullptr )
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

   bool
   RunElevated(
   __in      oswindow   hwnd,
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
   bool   bVESuccess                  = false;

   __declspec(allocate("ve_shared"))
   char   szVE_Path[ MAX_PATH ]         = "";

   __declspec(allocate("ve_shared"))
   char   szVE_Parameters[ MAX_PATH ]      = "";

   __declspec(allocate("ve_shared"))
   char   szVE_Directory[ MAX_PATH ]      = "";

   __declspec(allocate("ve_shared"))
   bool    bVE_NeedProcessHandle         = false;

   __declspec(allocate("ve_shared"))
   HANDLE   hVE_Process               = nullptr;

//////////////////////////////////e
// the hook callback procedure, it is called in the context of th shell proces

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
   bool
   (WINAPI
    *PGetModuleHandleExW)(
    __in        ::u32    dwFlags,
    __in_opt    const unichar * lpModuleName,
    __out HMODULE* phModule
    );

   static PGetModuleHandleExW pGetModuleHandleExW = nullptr;

   bool
   RunNonElevated(
   __in      oswindow   hwnd,
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
         return false;
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
      // a ::user::interaction_impl created by the shell. This will cause our hook callback procedure to be executed
      // in the context of the shell proces.
      //
      // Because this trick uses a global hook, the hook procedure must be in a DLL.
      //

      /////////////////////
      // First, register a private message, to communicate with the (hooked) shell process

      if ( !uVEMsg )
         uVEMsg = ::RegisterWindowMessage( "VistaElevatorMsg" );

      //////////////////////////////////////
      // find the shell ::user::interaction_impl (the desktop)

      oswindow hwndShell = ::FindWindow( "Progman", nullptr);

      if ( !hwndShell )
      {
         ASSERT_HERE;
         return false;
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
         return false;
      }

      HMODULE hModule = nullptr;   // we need to know hModule of this DLL to install a global hook

      if ( !pGetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (const unichar *)VistaEelevator_HookProc_MsgRet,
            &hModule ) )
      {
         ASSERT_HERE;
         return false;
      }

      /////////////////////////////////////////
      // Install a global hook, to inject our code into the shell proces

      hVEHook = ::SetWindowsHookEx( WH_CALLWNDPROCRET,   // hook called after SendMessage() !!!
                                    (HOOKPROC)VistaEelevator_HookProc_MsgRet, hModule, 0);

      if ( !hVEHook )
      {
         ASSERT_HERE;
         return false;
      }

      //////////////////////////////////
      // Prepare the parameters for launching the non-elevated process
      // from the hook callback procedure (they are placed into the shared data section)

      if (!( ansi_count_copy(
             szVE_Path,
             pszPath, _tsizeof(szVE_Path) ) ) )
      {
         ASSERT_HERE;
         return false;
      }

      if (!( ansi_count_copy(
             szVE_Parameters,

             pszParameters ? pszParameters : "",
             _tsizeof(szVE_Parameters)) ) )
      {
         ASSERT_HERE;
         return false;
      }

      if ( FAILED( ansi_count_copy(
                   szVE_Directory,
                   pszDirectory ? pszDirectory : "",
                   _tsizeof(szVE_Directory)) ) )
      {
         ASSERT_HERE;
         return false;
      }

      bVE_NeedProcessHandle = (phProcess != nullptr);

      /////////////////////////////////////////
      // Activate our hook callback procedure:

      bVESuccess = false; // assume failure

      ::SendMessage( hwndShell, uVEMsg, 0, 0 );

      ////////////////////////////////////////////////////////
      // At this point our hook procedure has been executed!

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

#endif

#endif// IMPLEMENT_VISTA_TOOLS