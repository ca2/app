#include "framework.h"
#include "acme/operating_system.h"
#include "acme/os/windows_common/_file_c.h"
#include <stdio.h>
#include <share.h>
#include <io.h>
#include <fcntl.h>




int_bool read_resource_as_file(const char * pszFile, HINSTANCE hinstance, DWORD nID, LPCTSTR pcszType)

{

   HRSRC hrsrc = FindResource(hinstance, MAKEINTRESOURCE(nID), pcszType);

   HGLOBAL hglobalResource;
   u32 dwResourseSize;
   int_bool bOk;
   DWORD * pResource;
   FILE * file;

   if(hrsrc == nullptr)
      return false;

   hglobalResource = LoadResource(hinstance, hrsrc);

   if(hglobalResource == nullptr)
      return false;

   dwResourseSize = SizeofResource(hinstance, hrsrc);

   if(hglobalResource != nullptr)
   {

      bOk = false;

      pResource = (DWORD *) LockResource(hglobalResource);

      dir::mk(dir::name(pszFile));

      file = fopen_dup(pszFile, "wb", _SH_DENYNO);

      if(file != nullptr)
      {

         auto dwWritten = fwrite(pResource, 1, dwResourseSize, file);

         fclose(file);

         bOk = dwWritten == dwResourseSize;

      }

      return bOk;

   }

   return false;

}


int_bool file_exists(const char * path1)
{

   u32 dwFileAttributes = windows_get_file_attributes(path1);

   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
   {

      return false;

   }

   return true;

}


int_bool file_put_contents(const char * path, const char * contents, memsize len)
{

   dir::mk(dir::name(path));

   wstring wstr(path);

   FILE * file = fopen_dup(path, "w", _SH_DENYWR);

   if (file == nullptr)
   {

      return false;

   }

   count dwWrite;

   if(len < 0)
      dwWrite = ansi_length(contents);
   else
      dwWrite = len;

   auto dwWritten = fwrite(contents, 1, (u32) dwWrite, file);

   int_bool bOk = dwWritten == dwWrite;

   fclose(file);

   return dwWrite == dwWritten && bOk != false;

}


filesize file_length_dup(const char * path)
{

   HANDLE hfile = CreateFileW(wstring(path), GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

   if(hfile == INVALID_HANDLE_VALUE)
      return 0;

   DWORD dwHi = 0;

   u64 u = GetFileSize(hfile, &dwHi);

   u |= ((u64)dwHi) << 32ULL;

   CloseHandle(hfile);

   return u;

}


int_bool file_is_equal_path_dup(const char * psz1, const char * psz2)
{

   const i32 iBufSize = MAX_PATH * 8;

   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);

   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);

   unichar * pwszFile1;

   unichar * pwszFile2;

   unichar * pwszPath1 = new unichar[iBufSize];

   unichar * pwszPath2 = new unichar[iBufSize];

   i32 iCmp = -1;
   
   if(GetFullPathNameW(pwsz1, iBufSize, pwszPath1, &pwszFile1))
   {
      
      if(GetFullPathNameW(pwsz2, iBufSize, pwszPath2, &pwszFile2))
      {
         
         string path1 = ::str::international::unicode_to_utf8(pwszPath1);
         
         string path2 = ::str::international::unicode_to_utf8(pwszPath2);
         
         iCmp = ansi_compare_ci(path1, path2);

      }

   }

   delete pwszPath1;

   delete pwszPath2;

   return iCmp == 0;

}



































string file_get_mozilla_firefox_plugin_container_path()
{

   string strPath;
   HKEY hkeyMozillaFirefox;

   if(::RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Mozilla\\Mozilla Firefox", &hkeyMozillaFirefox) != ERROR_SUCCESS)
      return "";
   {

      DWORD dwType;
      DWORD dwData;
      dwData = 0;
      if(::WinRegGetValueW(hkeyMozillaFirefox, nullptr, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, nullptr, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrVersion;
      auto pwszVersion = wstrVersion.get_string_buffer(dwData);
      if(::WinRegGetValueW(hkeyMozillaFirefox, nullptr, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, pwszVersion, &dwData) != ERROR_SUCCESS)
      {
         wstrVersion.release_string_buffer();
         goto ret1;
      }
      wstrVersion.release_string_buffer();

      wstring wstrMainSubKey = wstrVersion + L"\\Main";
      dwData = 0;

      if(::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, nullptr, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrDir;
      auto pwszDir = wstrDir.get_string_buffer(dwData);
      if(::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, pwszDir, &dwData) != ERROR_SUCCESS)
      {
         wstrDir.release_string_buffer();
         goto ret1;
      }
      wstrDir.release_string_buffer();

      ::file::path strDir;

      strDir = ::str::international::unicode_to_utf8(wstrDir);

      strPath = strDir / "plugin-container.exe";
   }

ret1:
   ::RegCloseKey(hkeyMozillaFirefox);
   return strPath;

}






::file::path dir::sys_temp()
{

   return ::dir::appdata() / "time";

}



string file_as_string(const char * path, strsize iReadAtMostByteCount)
{

   string str;

   FILE * file = ::fopen_dup(path, "r", _SH_DENYNO);

   if (file == nullptr)
   {

      DWORD dwLastError = ::GetLastError();

      TRACELASTERROR();

      return "";

   }

   DWORD dwSize;

   dwSize = (DWORD) FILE_get_size(file);

   iReadAtMostByteCount = iReadAtMostByteCount < 0 ? dwSize :  min(iReadAtMostByteCount, (::strsize)dwSize);

   char * psz = str.get_string_buffer(iReadAtMostByteCount);

   ::size_t iPos = 0;

   while (iReadAtMostByteCount - iPos > 0)
   {

      auto dwRead = ::fread(psz + iPos, 1, (size_t)iReadAtMostByteCount - iPos, file);

      if (dwRead <= 0)
      {

         break;

      }

      iPos += dwRead;

   }
   
   psz[iPos] = '\0';

   str.release_string_buffer(iReadAtMostByteCount);

   fclose(file);

   return str;

}


memsize file_as_memory(const char * path, void * p, memsize s)
{

   FILE * file = ::fopen_dup(path, "r", _SH_DENYNO);

   if (file == nullptr)
   {

      return false;

   }

   memsize sRead = 0;

   try
   {

      sRead = ::fread(p, 1, (size_t) s, file);


   }
   catch (...)
   {

   }

   fclose(file);

   return sRead;

}




bool file_as_memory(memory_base & memory, const char * path, memsize iReadAtMostByteCount)
{

   memory.set_size(0);

   FILE * file = ::fopen_dup(path, "r", _SH_DENYNO);

   if (file == nullptr)
   {

      return false;

   }

   filesize iSize = FILE_get_size(file);

   if(iSize < 0)
   {

      ::fclose(file);

      return false;

   }

   iReadAtMostByteCount = min_non_neg(iReadAtMostByteCount, (::strsize) iSize);

   memory.set_size(iReadAtMostByteCount);

   auto dwRead = ::fread(memory.get_data(), 1, (u32) iReadAtMostByteCount, file);

   memory.set_size(dwRead);

   ::fclose(file);

   return true;

}









//#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

struct PROCESS_INFO_t
{
   wstring csProcess;
   u32 dwImageListIndex;
};


//#if !defined(LINUX) && !defined(MACOS) && !defined(_UWP) && !defined(ANDROID)
//
////#include <Tlhelp32.h>
////#include <Psapi.h>
//
//
////void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext );
////void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext, HANDLE hDriver, GetFinalPathNameByHandleDef pGetFinalPathNameByHandle );
//
//const const widechar * DRV_DOS_NAME = L"\\\\.\\ListFileDrv";
//const const widechar * DRV_NAME = L"ListOpenedFileDrv";
//const const widechar * DRV_FILE_NAME = L"ListOpenedFileDrv.sys";
//
//#define DRIVER_FILE_NAME_32 L"\\ListOpenedFileDrv_32.sys"
//#define DRIVER_FILE_NAME_64 L"\\ListOpenedFileDrv_64.sys"
//
//
//// This Function install the driver and starts it
//HANDLE OnlyGetDrv()
//{
//
//
//   HMODULE hModule = GetModuleHandle(_T("acme.dll"));
//   if( !hModule )
//   {
//      output_debug_string( L"GetModuleHandle(_T(\"acme.dll\")); failed" );
//      return 0;
//   }
//   wstring csFilePath;
//   LPWSTR pPath = csFilePath.get_buffer( MAX_PATH );
//
//   GetModuleFileNameW( hModule,pPath, MAX_PATH );
//
//   LIBCALL(shlwapi,PathRemoveFileSpecW)(pPath);
//
//   csFilePath.release_string_buffer();
//   if(IsWow64())
//   {
//      csFilePath += DRIVER_FILE_NAME_64;
//   }
//   else
//   {
//      csFilePath += DRIVER_FILE_NAME_32;
//   }
//
//   if(!LIBCALL(shlwapi, PathFileExistsW)(csFilePath))
//   {
//      message_box(nullptr,"Cannot find driver " + string(csFilePath),"Cannot find driver " + string(csFilePath),e_message_box_ok);
//      return 0;
//   }
//
//
//
//   // Delete the temp file...
//   //DeleteFile( csPath );
//   HANDLE hFile = CreateFileW( DRV_DOS_NAME, GENERIC_READ|GENERIC_WRITE,
//                              FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
//                              OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0 );
//   return hFile;
//
//}
//
//
////extern "C" CLASS_DECL_ACME void GetOpenedFiles(const widechar * pPath, OF_TYPE Filter, OF_CALLBACK CallBackProc, uptr pUserContext)
////
////{
////   string csPath = pPath;
////
////   csPath.make_lower();
////   EnableTokenPrivilege( SE_DEBUG_NAME );
////   if( Filter& MODULES_ONLY )
////   {
////      EnumerateLoadedModules( csPath, CallBackProc, pUserContext );
////   }
////
////   if( Filter& FILES_ONLY )
////   {
////
////
////      // Extract the driver from the resource and install it.
////      //HANDLE hDriver = ExtractAndInstallDrv();
////      //HANDLE hDriver = OnlyGetDrv();
////      HANDLE hDriver = nullptr;
////      GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = 0;
////      if(  !hDriver )
////      {
////         pGetFinalPathNameByHandle = (GetFinalPathNameByHandleDef)GetProcAddress( GetModuleHandle(_T("kernel32.dll")), "GetFinalPathNameByHandleW" );
////      }
////      // Now walk all handles
////      EnumerateOpenedFiles( csPath, CallBackProc, pUserContext, hDriver, pGetFinalPathNameByHandle );
////      //if( hDriver )
////      {
////         // Time to wind up
////         //StopAndUninstallDrv( hDriver );
////      }
////   }
////}
//
////#ifndef _UWP
////
////typedef struct _SYSTEM_HANDLE_INFORMATION
////{
////   u32         dwCount;
////   SYSTEM_HANDLE Handles[1];
////} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION, **PPSYSTEM_HANDLE_INFORMATION;
////
////typedef enum _SYSTEM_INFORMATION_CLASS2
////{
////   SystemHandleInformation = 0X10,
////} SYSTEM_INFORMATION_CLASS2;
////
////#endif
//
////typedef NTSTATUS ( WINAPI *PNtQuerySystemInformation)
////( IN SYSTEM_INFORMATION_CLASS2 SystemInformationClass,
////  OUT   PVOID              SystemInformation,
////  IN ULONG              SystemInformationLength,
////  OUT   PULONG                ReturnLength OPTIONAL );
//
////DWORD g_CurrentIndex = 0;
////struct THREAD_PARAMS
////{
////   PSYSTEM_HANDLE_INFORMATION pSysHandleInformation;
////   GetFinalPathNameByHandleDef pGetFinalPathNameByHandle;
////   LPWSTR pPath;
////
////   i32 nFileType;
////   HANDLE hStartEvent;
////   HANDLE hFinishedEvent;
////   bool bStatus;
////};
//
////DWORD WINAPI  ThreadProc(void * p)
////{
////
////   THREAD_PARAMS * pThreadParam = (THREAD_PARAMS *) p;
////
////   FILE_NAME_INFO * pinfo = (FILE_NAME_INFO *)new byte[MAX_PATH * 8];
////
////   GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = pThreadParam->pGetFinalPathNameByHandle;
////   for( g_CurrentIndex; g_CurrentIndex < pThreadParam->pSysHandleInformation->dwCount;  )
////   {
////
////      WaitForSingleObject( pThreadParam->hStartEvent, U32_INFINITE_TIMEOUT );
////      ResetEvent( pThreadParam->hStartEvent );
////      pThreadParam->bStatus = false;
////      SYSTEM_HANDLE& sh = pThreadParam->pSysHandleInformation->Handles[g_CurrentIndex];
////      g_CurrentIndex++;
////      HANDLE hDup = (HANDLE)sh.wValue;
////      HANDLE hProcess = OpenProcess( PROCESS_DUP_HANDLE, false, sh.dwProcessId );
////      if( hProcess )
////      {
////         bool b = DuplicateHandle( hProcess, (HANDLE)sh.wValue, GetCurrentProcess(), &hDup, 0, false, DUPLICATE_SAME_ACCESS ) != false;
////         if( !b )
////         {
////            hDup = (HANDLE)sh.wValue;
////         }
////         CloseHandle( hProcess );
////      }
////      //u32 dwRet = pGetFinalPathNameByHandle( hDup, pThreadParam->pPath, MAX_PATH, 0 );
////
////      //u32 dwRet = GetFileInformationByHandleEx(hDup, FileNameInfo, pinfo, MAX_PATH * 8);
////      u32 dwRet = GetFinalPathNameByHandleW( hDup, pThreadParam->pPath, MAX_PATH, 0 );
////
////      //wcsncpy(pThreadParam->pPath, pinfo->FileName, pinfo->FileNameLength);
////
////      if( hDup && (hDup != (HANDLE)sh.wValue))
////      {
////         CloseHandle( hDup );
////      }
////      if(dwRet)
////      {
////         pThreadParam->bStatus = true;
////      }
////      SetEvent( pThreadParam->hFinishedEvent );
////
////   }
////   delete[] (byte *) pinfo;
////   return ::success;
////}
//
////void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext, HANDLE hDriver,
////                           GetFinalPathNameByHandleDef pGetFinalPathNameByHandle )
////{
////   i32 nFileType;
////
////   if(is_windows_vista_or_greater())
////   {
////      nFileType = VISTA_FILETYPE;
////   }
////   else
////   {
////      nFileType = XP_FILETYPE;
////   }
////
////   const char * pPath = csPath;
////
////   wstring csShortName;
////   GetShortPathNameW( wstring(csPath), csShortName.get_buffer( MAX_PATH), MAX_PATH );
////   csShortName.release_string_buffer();
////   string strShortName(csShortName);
////   strShortName.make_lower();
////   bool bShortPath = false;
////   const char * pShortPath = strShortName;
////
////   if(string( csShortName )!= csPath && false == csShortName.is_empty())
////   {
////      bShortPath = true;
////   }
////
////   HMODULE hModule = GetModuleHandleW(L"ntdll.dll");
////   PNtQuerySystemInformation NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress( hModule, "NtQuerySystemInformation" );
////   if( 0 == NtQuerySystemInformation )
////   {
////      output_debug_string( L"Getting proc of NtQuerySystemInformation failed" );
////      return;
////   }
////
////   // Get the list of all handles in the file_system
////   PSYSTEM_HANDLE_INFORMATION pSysHandleInformation = new SYSTEM_HANDLE_INFORMATION;
////   u32 size = sizeof(SYSTEM_HANDLE_INFORMATION);
////   DWORD needed = 0;
////   NTSTATUS status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
////   if( !NT_SUCCESS(status))
////   {
////      if( 0 == needed )
////      {
////         return;// some other error
////      }
////      // The previously supplied buffer wasn't enough.
////      delete pSysHandleInformation;
////      size = needed + 1024;
////      pSysHandleInformation = (PSYSTEM_HANDLE_INFORMATION)new byte[size_i32];
////      status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
////      if( !NT_SUCCESS(status))
////      {
////         // some other error so quit.
////         delete pSysHandleInformation;
////         return;
////      }
////   }
////
////   if( pGetFinalPathNameByHandle )// there is no driver, we have do it ugly way
////   {
////      g_CurrentIndex = 0;
//////    TCHAR tcFileName[MAX_PATH+1];
////      THREAD_PARAMS ThreadParams;
////      wstring wstrFileName;
////
////      
////      ThreadParams.pPath = wstrFileName.get_buffer(MAX_PATH * 8);;
////
////      ThreadParams.nFileType = nFileType;
////      ThreadParams.pGetFinalPathNameByHandle = pGetFinalPathNameByHandle;
////      ThreadParams.pSysHandleInformation = pSysHandleInformation;
////      ThreadParams.hStartEvent = ::CreateEvent( 0, true, false, 0 );
////      ThreadParams.hFinishedEvent = ::CreateEvent( 0, true, false, 0 );
////      HANDLE ThreadHandle = 0;
////      while( g_CurrentIndex < pSysHandleInformation->dwCount )
////      {
////         if( !ThreadHandle )
////         {
////            ThreadHandle = CreateThread(NULL, 0, ThreadProc, &ThreadParams, 0, NULL);
////         }
////         ResetEvent( ThreadParams.hFinishedEvent );
////         SetEvent( ThreadParams.hStartEvent );
////         if( WAIT_TIMEOUT == WaitForSingleObject( ThreadParams.hFinishedEvent, 100 ))
////         {
////            string csError;
////            csError.Format("Query hang for handle %d", (i32)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue);
////            output_debug_string(csError );
////            TerminateThread( ThreadHandle, 0 );
////            CloseHandle( ThreadHandle );
////            ThreadHandle = 0;
////            continue;
////         }
////         if( !ThreadParams.bStatus )
////         {
////            continue;
////         }
////         i32 nCmpStart = 4;
////         string csFileName( ::str::international::unicode_to_utf8(&ThreadParams.pPath[nCmpStart]));
////
////         csFileName.make_lower();
////         if(csFileName.find("vs11_dp_ctp") >= 0)
////         {
////            continue;
////         }
////         else if( 0 != strcmp( pPath, csFileName))
////
////         {
////            continue;
////         }
////         OF_INFO_t stOFInfo;
////         stOFInfo.dwPID = pSysHandleInformation->Handles[g_CurrentIndex - 1].dwProcessId;
////         wstring wstrCallback;
////         wstrCallback = ::str::international::utf8_to_unicode(csFileName);
////         stOFInfo.pFile = wstrCallback;
////
////         stOFInfo.hFile  = (HANDLE)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue;
////         CallBackProc( stOFInfo, pUserContext );
////      }
////      if( ThreadHandle )
////      {
////         if( WAIT_TIMEOUT == WaitForSingleObject( ThreadHandle, 1000 ))
////         {
////            TerminateThread( ThreadHandle, 0 );
////         }
////         CloseHandle( ThreadHandle );
////      }
////      CloseHandle( ThreadParams.hStartEvent );
////      CloseHandle( ThreadParams.hFinishedEvent );
////      return;
////   }
////
////   // Walk through the handle list
////   for ( u32 i = 0; i < pSysHandleInformation->dwCount; i++ )
////   {
////      SYSTEM_HANDLE& sh = pSysHandleInformation->Handles[i];
////      if( sh.bObjectType != nFileType )// Under windows XP file handle is of type 28
////      {
////         continue;
////      }
////
////      string csFileName;
////      string csDir;
////      if( hDriver )
////      {
////         HANDLE_INFO stHandle = {0};
////         ADDRESS_INFO stAddress;
////         stAddress.pAddress = sh.pAddress;
////         DWORD dwReturn = 0;
////         bool bSuccess = DeviceIoControl( hDriver, IOCTL_LISTDRV_BUFFERED_IO, &stAddress, sizeof(ADDRESS_INFO), &stHandle, sizeof(HANDLE_INFO), &dwReturn, nullptr ) != false;
////
////
////         if( bSuccess && stHandle.tcFileName[0] != 0 &&
////               stHandle.uType != FILE_DEVICE_SOUND &&
////               stHandle.uType != FILE_DEVICE_NAMED_PIPE )
////         {
////
////            if( stHandle.uType != FILE_DEVICE_NETWORK_FILE_SYSTEM  )
////            {
////               // Get the drive name from the dos device name
////               if( !GetDrive(string(stHandle.tcDeviceName), csFileName, true ))
////               {
////                  output_debug_string( "GetDrive failed" );
////               }
////               csFileName += stHandle.tcFileName;
////            }
////            else
////            {
////               csFileName = "\\";
////               csFileName += stHandle.tcFileName;
////            }
////         }
////         else
////         {
////            continue;
////         }
////      }
////      else
////      {
////         return;
////      }
////
////
////      csFileName.make_lower();
////      // Check whether the file belongs to the specified folder
//////       if( -1 == csFileName.Find( csPath ))
//////       {
//////          if( bShortPath )
//////          {
//////             // Some times the file name may be in i16 path form.
//////             if( -1 == csFileName.Find( csShortName ))
//////             {
//////                continue;
//////             }
//////          }
//////          else
//////          {
//////             continue;
//////          }
//////       }
////
////      if( 0 != strcmp( pPath, csFileName))
////
////      {
////         if( bShortPath )
////         {
////            // Some times the file name may be in i16 path form.
////            if( 0 != strcmp( pShortPath, csFileName))
////
////            {
////               continue;
////            }
////         }
////         else
////         {
////            continue;
////         }
////      }
////      OF_INFO_t stOFInfo;
////      stOFInfo.dwPID = sh.dwProcessId;
////      wstring wstrCallback;
////      wstrCallback = ::str::international::utf8_to_unicode(csFileName);
////      stOFInfo.pFile = wstrCallback;
////
////      stOFInfo.hFile  = (HANDLE)sh.wValue;
////      CallBackProc( stOFInfo, pUserContext );
////   }
////   delete pSysHandleInformation;
////
////}
//
//
////void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext )
////{
////   wstring csShortName;
////   GetShortPathNameW(wstring( csPath), csShortName.get_buffer( MAX_PATH), MAX_PATH );
////   csShortName.release_string_buffer();
////   string strShortName(csShortName);
////   strShortName.make_lower();
////   bool bShortPath = false;
////   if(csPath !=  string(csShortName) && !csShortName.is_empty())
////   {
////      bShortPath = true;
////   }
////
////   u32 dwsize = 300;
////   PDWORD pDwId = (PDWORD)new byte[dwsize];
////   DWORD dwReturned = dwsize;
////   // Enum all the process first
////   while( 1 )
////   {
////      EnumProcesses( pDwId, dwsize, &dwReturned );
////      if( dwsize > dwReturned  )
////      {
////         break;
////      }
////      delete pDwId;
////      dwsize += 50;
////      pDwId = (PDWORD)new byte[dwsize];
////   }
////   i32 nCount = dwReturned / sizeof(u32);
////   i32 nItemCount = -1;
////   // Enumerate modules of the above process
////   for( i32 nIdx = 0; nIdx < nCount; nIdx++ )
////   {
////      if( 0 != pDwId[nIdx] )
////      {
////         HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
////         MODULEENTRY32W me32;
////         // Take a snapshot of all modules in the specified process.
////         hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pDwId[nIdx] );
////         if( hModuleSnap == INVALID_HANDLE_VALUE )
////         {
////            continue;
////         }
////         me32.dwSize = sizeof( MODULEENTRY32W );
////         if( !Module32FirstW( hModuleSnap, &me32 ) )
////         {
////            CloseHandle( hModuleSnap );
////            continue;
////         }
////         bool bFirst = true;
////         PROCESS_INFO_t stInfo;
////         do
////         {
////            string csModule;
////            if( bFirst )
////            {
////               // First module is always the exe name
////               bFirst = false;
////               if(!LIBCALL(shlwapi,PathFileExistsW)(me32.szExePath))
////               {
////                  WCHAR tcFileName[MAX_PATH];
////                  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, true, pDwId[nIdx] );
////                  if( GetProcessImageFileNameW( hProcess, tcFileName, MAX_PATH ))
////                  {
////                     GetDrive( string(tcFileName), csModule, false );
////                  }
////                  CloseHandle( hProcess );
////               }
////               else
////               {
////                  csModule = me32.szExePath;
////               }
////               csModule.make_lower();
////            }
////            else
////            {
////               csModule = me32.szExePath;
////               csModule.make_lower();
////            }
////            if( -1 == csModule.find( csPath ))
////            {
////               if( bShortPath )
////               {
////                  if( -1 == csModule.find( string(csShortName)))
////                  {
////                     continue;
////                  }
////               }
////               else
////               {
////                  continue;
////               }
////            }
////            OF_INFO_t stOFInfo;
////            stOFInfo.dwPID = pDwId[nIdx];
////            wstring wstrCallback;
////
////            wstrCallback = ::str::international::utf8_to_unicode(csModule);
////
////            stOFInfo.pFile = wstrCallback;
////
////            CallBackProc( stOFInfo, pUserContext );
////         }
////         while( Module32NextW( hModuleSnap, &me32 ) );
////         CloseHandle( hModuleSnap );
////      }
////   }
////
////   delete pDwId;
////
////}
////
////
////
////#endif // LINUX
//




int ftruncate(int file, filesize len)
{
   return _chsize_s (file, len);
}





int_bool ensure_file_size_fd(i32 fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      return 0;

   return 1;

}

int_bool FILE_set_size(FILE * file, size_t iSize)
{

   return ensure_file_size_fd(_fileno(file), iSize);

}


int_bool ensure_file_size_handle(HANDLE h, u64 iSize)
{

   DWORD dwHi;

   DWORD dwLo = GetFileSize(h, &dwHi);

   if(((u64) dwLo | ((u64)dwHi << 32)) != iSize)
   {

      LONG l = (iSize >> 32) & 0xffffffff;

      if(SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET) != (DWORD) (iSize & 0xffffffff))
         return false;

      if(l != ((iSize >> 32) & 0xffffffff))
         return false;

      if(!SetEndOfFile(h))
         return false;

   }


   return 1;

}































int_bool file_set_length(const char * lpszName, size_t iSize)
{

   wstring wstr(lpszName);

   HANDLE h = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

   if(h == INVALID_HANDLE_VALUE)
      return false;

   if(!ensure_file_size_handle(h, iSize))
   {

      ::CloseHandle(h);

      return false;

   }

   ::CloseHandle(h);

   return true;

}


int_bool file_move(const char * pszNewName, const char * pszOldName)
{

   wstring wstrOldName(pszOldName);

   wstring wstrNewName(pszNewName);

   if (!::MoveFileW(wstrOldName, wstrNewName))
   {

      return false;

   }

   return true;

}


int_bool file_delete(const char * pszFileName)
{

   wstring wstrFileName(pszFileName);

   if (!::DeleteFileW(wstrFileName))
   {

      return false;

   }

   return true;

}


int_bool file_is_equal_path(const char * psz1,const char * psz2)
{

   wstring wstr1(psz1);

   wstring wstr2(psz2);

   unichar * pwszFile1;

   unichar * pwszFile2;

   ::acme::malloc < unichar * > pwszPath1;

   ::acme::malloc < unichar * > pwszPath2;

   pwszPath1.alloc((size_t)(wstr1.get_length() * 2 * sizeof(unichar)));

   pwszPath2.alloc((size_t)(wstr2.get_length() * 2 * sizeof(unichar)));

   i32 iCmp = -1;

   if(GetFullPathNameW(wstr1, (DWORD)( pwszPath1.m_iSize / sizeof(unichar)), pwszPath1, &pwszFile1))
   {

      if(GetFullPathNameW(wstr2, (DWORD) (pwszPath2.m_iSize / sizeof(unichar)), pwszPath2, &pwszFile2))
      {

         iCmp = _wcsicmp(pwszPath1, pwszPath2);

      }

   }

   return iCmp == 0;

}


char get_drive_letter(const char * pDevicePath)
{

   wchar_t d = 'A';

   while(d <= L'Z')
   {

      wchar_t szDeviceName[3] = {d,L':',L'\0'};

      wchar_t szTarget[512] = {0};

      if (QueryDosDeviceW(szDeviceName, szTarget, 511) != 0)
      {

         if (wcscmp(wstring(pDevicePath), szTarget) == 0)
         {

            return (char)d;

         }

      }

      d++;
   
   }

   return '\0';

}


memory file_as_memory(const char * path, memsize iReadAtMostByteCount)
{

   memory mem;

   if (iReadAtMostByteCount < 0)
   {

      file_as_memory(mem, path);

   }
   else
   {

      mem.set_size(iReadAtMostByteCount);

      memsize iRead = file_as_memory(path, mem.get_data(), mem.get_size());

      mem.set_size(iRead);

   }

   return mem;

}



//#include "framework.h"
//#include <Winsvc.h>

//const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
//const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
//const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

// Function resolves the fosedevice name to drive name
bool GetDrive(const char * pszDosName, string& csDrive, bool bDriveLetterOnly)
{
   WCHAR tcDeviceName[50];
   WCHAR tcDrive[3] = L"A:";

   wstring wstrDosName(pszDosName);

   // Iterating through the drive letters
   for (WCHAR actDrive = L'A'; actDrive <= L'Z'; actDrive++)
   {
      tcDrive[0] = actDrive;
      // Query the device for the drive letter
      if (QueryDosDeviceW(tcDrive, tcDeviceName, 50) != 0)
      {
         // Is this the drive letter we are looking for?
         if (wcsnicmp(tcDeviceName, wstrDosName, wcslen(tcDeviceName)) == 0)
         {
            if (bDriveLetterOnly)
            {
               csDrive = tcDrive;
            }
            else
            {
               csDrive = pszDosName;
               csDrive.replace(string(tcDeviceName), string(tcDrive));
            }
            return true;
         }
      }
   }
   return false;
}

//#ifdef _M_IX86
//#define DRVIER_ID IDR_XPDRIVER32
//#else
//#define DRVIER_ID IDR_XPDRIVER64
//#endif

//#ifdef _M_IX86
//#define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
//#else
//#define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")
//#endif

// This Function install the driver and starts it
//HANDLE ExtractAndInstallDrv()
//{
//   SC_HANDLE hSCManager = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
//   SC_HANDLE hService = OpenServiceW(hSCManager, DRV_NAME, SERVICE_ALL_ACCESS);
//   string csPath;
//   if (0 == hService)
//   {
//      //Service not installed. So install the service.
//
//      /*OSVERSIONINFO info = { 0 };
//      info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//      GetVersionEx(&info);
//      i32 nDriverId = IDR_VISTA_DRIVER;
//      if( info.dwMajorVersion == 5 )
//      {
//      nDriverId = IDR_XPDRIVER;
//      }*/
//
//
//      /*// First extract the resource
//      HINSTANCE hModule= __get_instance_handle();
//      HRSRC hRsrc = FindResource(hModule, MAKEINTRESOURCE(DRVIER_ID),_T("BINARY"));
//      HGLOBAL hDrvRsrc = LoadResource(hModule, hRsrc);
//      u32 dwDriverSize = SizeofResource(hModule, hRsrc);
//      LPVOID pvDriver = LockResource(hDrvRsrc);
//
//      CFile File;
//      if( !File.Open( DRV_FILE_NAME, CFile::modeCreate|CFile::modeWrite ))
//      {
//      return 0;
//      }
//      File.Write( pvDriver, dwDriverSize );
//
//      csPath = File.GetFilePath();
//      File.Close();*/
//
//
//      HMODULE hModule = GetModuleHandle(_T("acme.dll"));
//      if (!hModule)
//      {
//         output_debug_string(L"GetModuleHandle(_T(\"acme.dll\")); failed");
//         return 0;
//      }
//      wstring csFilePath;
//      LPWSTR pPath = csFilePath.get_buffer(MAX_PATH);
//
//      GetModuleFileNameW(hModule, pPath, MAX_PATH);
//
//      LIBCALL(shlwapi, PathRemoveFileSpecW)(pPath);
//
//      csFilePath.release_string_buffer();
//      if (IsWow64())
//      {
//         csFilePath += DRIVER_FILE_NAME_64;
//      }
//      else
//      {
//         csFilePath += DRIVER_FILE_NAME_32;
//      }
//
//      if (!LIBCALL(shlwapi, PathFileExistsW)(csFilePath))
//      {
//         message_box(nullptr, "Cannot find driver " + string(csFilePath), "Cannot find driver " + string(csFilePath), e_message_box_ok);
//         return 0;
//      }
//
//
//
//      hService = CreateServiceW(hSCManager, DRV_NAME, DRV_NAME, SERVICE_ALL_ACCESS,
//                               SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
//                               csFilePath, nullptr, nullptr, nullptr, nullptr, nullptr);
//
//      if (0 == hService)
//      {
//         output_debug_string(L"CreateService failed");
//         CloseServiceHandle(hSCManager);
//         return 0;
//      }
//   }
//
//   if (!StartService(hService, 0, nullptr))
//   {
//      u32 dwLastError = GetLastError();
//      if (dwLastError != ERROR_SERVICE_ALREADY_RUNNING)
//      {
//         DeleteService(hService);
//         CloseServiceHandle(hService);
//         CloseServiceHandle(hSCManager);
//         //DeleteFile( csPath );
//         output_debug_string(L"StartService failed");
//         return 0;
//      }
//
//   }
//   // Delete the temp file...
//   //DeleteFile( csPath );
//   HANDLE hFile = CreateFileW(DRV_DOS_NAME, GENERIC_READ | GENERIC_WRITE,
//                             FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
//                             OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
//   if (INVALID_HANDLE_VALUE == hFile)
//   {
//      hFile = 0;
//      SERVICE_STATUS  stSrvStatus = { 0 };
//      ControlService(hService, SERVICE_CONTROL_STOP, &stSrvStatus);
//   }
//   CloseServiceHandle(hService);
//   CloseServiceHandle(hSCManager);
//   return hFile;
//}
//
//// Function stops the service and then deletes it.
//int_bool StopAndUninstallDrv(HANDLE hDrvHandle)
//{
//   CloseHandle(hDrvHandle);
//   SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
//   SC_HANDLE hService = OpenServiceW(hSCManager, DRV_NAME, SERVICE_ALL_ACCESS);
//   SERVICE_STATUS  stSrvStatus = { 0 };
//   ControlService(hService, SERVICE_CONTROL_STOP, &stSrvStatus);
//   int_bool bDeleted = DeleteService(hService);
//   CloseServiceHandle(hService);
//   CloseServiceHandle(hSCManager);
//   return bDeleted;
//}
//














CLASS_DECL_ACME bool read_resource_as_memory(memory & m, HINSTANCE hinstance, DWORD nID, const char * pcszType, strsize iReadAtMostByteCount)

{

   HRSRC hrsrc;
   
   if (::is_set(pcszType))
   {
      hrsrc = FindResourceW(hinstance, MAKEINTRESOURCEW(nID), wstring(pcszType));
   }
   else
   {
      hrsrc = FindResourceW(hinstance, MAKEINTRESOURCEW(nID), (const WCHAR *) (pcszType));
   }


   if (!hrsrc)
   {

      if (::is_set(pcszType))
      {
         hrsrc = FindResourceW(nullptr, MAKEINTRESOURCEW(nID), wstring(pcszType));
      }  
      else
      {
         hrsrc = FindResourceW(nullptr, MAKEINTRESOURCEW(nID), (const WCHAR *)(pcszType));
      }
      if (!hrsrc)
      {

         if (::is_set(pcszType))
         {
            hrsrc = FindResourceW(::GetModuleHandle(NULL), MAKEINTRESOURCEW(nID), wstring(pcszType));
         }
         else
         {
            hrsrc = FindResourceW(::GetModuleHandle(NULL), MAKEINTRESOURCEW(nID), (const WCHAR *)(pcszType));
         }
      }
   }

   HGLOBAL hglobalResource;
   strsize dwResourceSize;
   int_bool bOk;
   DWORD * pResource;

   if (hrsrc == nullptr)
      return false;

   hglobalResource = LoadResource(hinstance, hrsrc);

   if (hglobalResource == nullptr)
      return false;

   dwResourceSize = SizeofResource(hinstance, hrsrc);

   if (hglobalResource != nullptr)
   {

      bOk = true;

      pResource = (DWORD *) LockResource(hglobalResource);

      auto iSize = min_non_neg(dwResourceSize, iReadAtMostByteCount);

      m.assign(pResource, iSize);

      return bOk;

   }

   return false;

}



CLASS_DECL_ACME HANDLE hfile_create(
const char *            pFileName,

::u32                   dwDesiredAccess,
::u32                   dwShareMode,
void *   pSecurityAttributes,
::u32                   dwCreationDisposition,
::u32                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
)
{

   wstring wstr(pFileName);


   return ::CreateFileW(
          wstr,
          dwDesiredAccess,
          dwShareMode,
          (LPSECURITY_ATTRIBUTES) pSecurityAttributes,
          dwCreationDisposition,
          dwFlagsAndAttributes,
          hTemplateFile);

}








string get_volume_path(const char * psz)
{
   WCHAR wsz[4096];
   if (!GetVolumePathNameW(::str::international::utf8_to_unicode(psz), wsz, sizeof(wsz) / sizeof(wsz[0])))
   {
      return "";
   }
   return wsz;
}



namespace file
{

#ifdef WINDOWS


   bool exception::get_error_message(string & str, unsigned int * pnHelpContext)
   {

      // if (pnHelpContext != nullptr)
      //      *pnHelpContext = m_cause + __IDP_FILE_NONE;

      string strMessage;

      string strFileName = m_path;

      if (strFileName.is_empty())
      {

         strFileName = "IDS_UNNAMED_FILE";

      }

      if (m_lOsError == ERROR_ACCESS_DENIED || m_lOsError == ERROR_SHARING_VIOLATION)
      {

         wstring wstr;

         wstr = ::str::international::utf8_to_unicode(m_path.name());

         // #ifdef WINDOWS_DESKTOP
         //          GetOpenedFiles(wstr, ALL_TYPES, &exception::CallBackFunc, (uptr)this);
         // #endif

         if (m_strAdd.has_char())
         {
            ((exception *)this)->m_strAdd = " Process Using the file = " + m_strAdd;
         }
         else
         {
            ((exception *)this)->m_strAdd = " Process Using the file Not Found ";
         }

      }


      string strExtra;

      strExtra = get_system_error_message(m_lOsError);

      strExtra += m_strAdd;

      strMessage.Format("file error number: %d - %s - file: %s", m_estatus.m_estatus, strExtra.c_str(), strFileName.c_str());

      str = strMessage;

      return true;
   }


#endif


} // namespace file








int_bool file_exists_raw(const char * path1)
{


   u32 dwFileAttributes = GetFileAttributesA(path1);

   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
   {

      return false;

   }

   return true;


}