#include "framework.h"
#include "process.h"


#undef User


#include <Wtsapi32.h>
#include <Userenv.h>


HANDLE dup_handle(HANDLE h)
{

   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &h, 0, FALSE, DUPLICATE_SAME_ACCESS);

   return h;

}


//typedef struct _PROCESS_BASIC_INFORMATION64
//{
//   u64  Reserved1;
//   u64  PebBaseAddress;
//   u64  Reserved2[2];
//   u64  UniqueProcessId;
//   u64  Reserved3;
//} PROCESS_BASIC_INFORMATION64;

//typedef NTSTATUS(NTAPI *_NtQueryInformationProcess)(HANDLE ProcessHandle, u32 ProcessInformationClass, PVOID ProcessInformation, u32 ProcessInformationLength, PDWORD ReturnLength);
//
//PPEB GetPebAddress(HANDLE handleProcess);
//
//CLASS_DECL_ACME string get_command_line(HANDLE handleProcess)
//{
//
//   PPEB ppeb = GetPebAddress(handleProcess);
//
//   PRTL_USER_PROCESS_PARAMETERS pparam1 = nullptr;
//
//   if (!ReadProcessMemory(handleProcess, (PCHAR)&ppeb->ProcessParameters, &pparam1, sizeof(PRTL_USER_PROCESS_PARAMETERS), nullptr) || pparam1 == nullptr)
//   {
//      ::output_debug_string("Could not read the address of ProcessParameters!\n");
//      return "";
//   }
//
//
//   _UNICODE_STRING ustrCommandLine;
//
//   if (!ReadProcessMemory(handleProcess, (PCHAR)&pparam1->CommandLine, &ustrCommandLine, sizeof(ustrCommandLine), nullptr))
//   {
//      ::output_debug_string("Could not read CommandLine!\n");
//      return "";
//   }
//
//   /* allocate memory to hold the command line */
//   WCHAR * commandLineContents = (WCHAR *)memory_alloc(ustrCommandLine.Length + sizeof(WCHAR));
//   /* read the command line */
//   if (!ReadProcessMemory(handleProcess, ustrCommandLine.Buffer, commandLineContents, ustrCommandLine.Length, nullptr))
//   {
//      ::output_debug_string("Could not read the command line string!\n");
//      return "";
//   }
//   commandLineContents[ustrCommandLine.Length / sizeof(WCHAR)] = L'\0';
//   string str = ::str::international::unicode_to_utf8(commandLineContents);
//   memory_free_dbg(commandLineContents, 0);
//   return str;
//}






//string get_display_error(u32 NTStatusMessage);
//
//PPEB GetPebAddress(HANDLE handleProcess)
//{
//   _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
//   PROCESS_BASIC_INFORMATION pbi;
//   __memset(&pbi, 0, sizeof(pbi));
//   DWORD dwInLen = sizeof(pbi);
//   DWORD dwOutLen = 0xffffffff;
//   u32 dwStatus = NtQueryInformationProcess(handleProcess, ProcessBasicInformation, &pbi, dwInLen, &dwOutLen);
//   string strError = get_display_error(dwStatus);
//   if ((dwStatus & 3) == 3)
//   {
//      return nullptr;
//   }
//   return pbi.PebBaseAddress;
//}


string get_display_error(u32 NTStatusMessage)
{

   return get_system_error_message(NTStatusMessage);

}


struct shell_execute :
   public SHELLEXECUTEINFOW
{

   wstring        m_wstrFile;

   wstring        m_wstrParams;

   shell_execute(const char * pszFile, const char * pszParams)
   {

      ::zero(this, sizeof(SHELLEXECUTEINFOW));

      cbSize = sizeof(SHELLEXECUTEINFOW);

      m_wstrFile = pszFile;

      lpFile = m_wstrFile;


      if (pszParams)
      {

         m_wstrParams = pszParams;

         lpParameters = m_wstrParams;


      }

   }


   bool async()
   {

      if (::ShellExecuteExW(this))
      {

         return false;

      }

      return true;

   }


   bool sync(::duration durationTimeout)
   {

      fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;

      if (!async())
      {

         return false;

      }

      ::datetime::time timeEnd = ::datetime::time::get_current_time() + durationTimeout;

      DWORD dwError = ::GetLastError();

      DWORD dwExitCode = 0;

      while(::datetime::time::get_current_time() < timeEnd)
      {

         if (::GetExitCodeProcess(hProcess, &dwExitCode))
         {

            if (dwExitCode != STILL_ACTIVE)
            {

               break;

            }

         }
         else
         {

            break;

         }

         Sleep(1000);

      }

      ::CloseHandle(hProcess);

      return true;


   }


};


bool shell_execute_async(const char * pszFile, const char * pszParams)
{

   shell_execute execute(pszFile, pszParams);

   return execute.async();

}


bool shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout)
{

   shell_execute execute(pszFile, pszParams);

   return execute.sync(durationTimeout);

}


bool root_execute_async(const char * pszFile, const char * pszParams)
{

   shell_execute execute(pszFile, pszParams);

   execute.lpVerb = L"RunAs";


   return execute.async();

}


bool root_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout)
{

   shell_execute execute(pszFile, pszParams);

   execute.lpVerb = L"RunAs";


   return execute.sync(durationTimeout);

}



#include "framework.h"


i32 call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::edisplay edisplay, bool bPrivileged, unsigned int *puiPid)
{

   SHELLEXECUTEINFOW info = {};

   wstring wstrFile = unicode(pszPath);
   wstring wstrParam = unicode(pszParam);
   wstring wstrDir = unicode(pszDir);

   info.cbSize = sizeof(SHELLEXECUTEINFOW);

   if (edisplay == display_default)
   {
      info.nShow = SW_SHOWDEFAULT;
   }
   else
   {
      info.nShow = is_visible(edisplay) ? SW_NORMAL : SW_HIDE;

   }
   info.lpFile = wstrFile;
   info.lpParameters = wstrParam;
   info.lpDirectory = wstrDir;


   if (bPrivileged)
   {

      info.lpVerb = L"RunAs";


   }

   if (puiPid != nullptr)
   {

      info.fMask |= SEE_MASK_NOCLOSEPROCESS;

   }


   int iOk = ::ShellExecuteExW(&info);

   if (puiPid != nullptr)
   {

      *puiPid = ::GetProcessId(info.hProcess);

      ::CloseHandle(info.hProcess);

   }

   DWORD dwError = ::GetLastError();

   return iOk;

}


u32 call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::edisplay edisplay, const ::duration & durationTimeout, ::property_set & set)
{

   SHELLEXECUTEINFOW infoa;

   __memset(&infoa, 0, sizeof(infoa));

   wstring wstrFile(pszPath);
   wstring wstrParam(pszParam);
   wstring wstrDir(pszDir);

   infoa.cbSize = sizeof(infoa);
   infoa.lpFile = wstrFile;

   infoa.lpParameters = wstrParam;

   infoa.lpDirectory = wstrDir;

   infoa.nShow = is_visible(edisplay) ? display_normal : SW_HIDE;

   infoa.fMask |= SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;

   if (set.is_true("privileged"))
   {

      infoa.lpVerb = L"RunAs";

   }

   if (!::ShellExecuteExW(&infoa))
   {

      DWORD dwLastError = ::GetLastError();

      return -1;

   }

   set["pid"] = (::u32) ::GetProcessId(infoa.hProcess);

   DWORD dwExitCode = (DWORD) -1;

   ::tick tick;

   tick.Now();

   while (::thread_get_run())
   {
      // Thanks from Blehman@Twitch from Slovakia through Googling...
      // 2020-02-19
      if (WaitForSingleObject(infoa.hProcess, 200) == WAIT_OBJECT_0)
      {

         break;

      }

      if (tick.elapsed() > durationTimeout)
      {

         set["timed_out"] = true;

         break;

      }

   }

   GetExitCodeProcess(infoa.hProcess, &dwExitCode);

   if(set.is_true("timed_out"))
   {

      if(set.is_true("terminate_on_timeout"))
      {

         auto TerminateProcess_return = ::TerminateProcess(infoa.hProcess, -1);
         auto TerminateProcess_GetLastError = ::GetLastError();

         set["TerminateProcess_return"] = TerminateProcess_return;
         set["TerminateProcess_GetLastError"] = (::u32) TerminateProcess_GetLastError;

      }

   }

   ::CloseHandle(infoa.hProcess);

   return dwExitCode;

}


i32 get_current_processor_index()
{


   return ::GetCurrentProcessorNumber();


}

i32 get_current_process_maximum_affinity()
{

   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
   {
      return 0;
   }
   i32 iMax = -1;
   uptr dwMask = 1;
   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if ((dwMask & dwProcessAffinityMask) != 0)
      {
         iMax = i;
      }
      dwMask = dwMask << 1;
   }

   return iMax;

}

i32 get_current_process_affinity_order()
{


   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;

   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
   {

      return 0;

   }

   i32 iCount = 0;
   uptr dwMask = 1;
   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if ((dwMask & dwProcessAffinityMask) != 0)
      {
         iCount++;
      }
      dwMask = dwMask << 1;
   }

   return iCount;


}

CLASS_DECL_ACME DWORD_PTR translate_processor_affinity(int iOrder)
{

   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
   {
      return 0;
   }
   i32 j = 0;
   uptr dwMask = 1;
   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if ((dwMask & dwProcessAffinityMask) != 0)
      {
         if (iOrder == j)
         {
            return dwMask;
         }
         j++;
      }
      dwMask = dwMask << 1;
   }

   return 0;

}


bool process_modules(string_array & stra, u32 processID)
{

   HANDLE hProcess;

   DWORD cbNeeded;

   u32 i;

   hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

   if (nullptr == hProcess)
      return false;

   const i32 iMaxModuleCount = 1024 * 8;

   HMODULE * hMods = new HMODULE[iMaxModuleCount];

   const i32 iImageSize = MAX_PATH * 8;

   wchar_t * szImage = (wchar_t *)memory_alloc(iImageSize * 2);

   if (EnumProcessModules(hProcess, hMods, sizeof(HMODULE) * iMaxModuleCount, &cbNeeded))
   {

      for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
      {

         if (GetModuleFileNameExW(hProcess, hMods[i], szImage, iImageSize / sizeof(char)))
         {

            stra.add(string(szImage));

         }

      }

   }

   memory_free_dbg(szImage, 0);

   delete hMods;

   CloseHandle(hProcess);

   return true;

}


bool load_modules_diff(string_array & straOld, string_array & straNew, const char * pszExceptDir)
{

   bool bFound;

   HMODULE hmodule;

   ::count iLenExcept;

   if (pszExceptDir != nullptr)
   {

      iLenExcept = ansi_length(pszExceptDir);

   }
   else
   {

      iLenExcept = 0;

   }

   for (i32 i = 0; i < straOld.get_count(); i++)
   {

      bFound = false;

      if (iLenExcept > 0)
      {

         if (ansi_length(straOld[i]) > iLenExcept)
         {

            if (_strnicmp(straOld[i], pszExceptDir, (size_t)iLenExcept) == 0)
            {

               continue;

            }

         }

      }

      for (i32 j = 0; j < straNew.get_count(); j++)
      {

         if (ansi_compare_ci(straOld[i], straNew[j]) == 0)
         {

            bFound = true;

            break;

         }

      }

      if (!bFound)
      {

         hmodule = nullptr;

         // double check, ensure, that the module has not been already loaded
         // it may happen by loading a missing module that loads dependencies that satisfies straOld modules state.

         if (::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, straOld[i], &hmodule) == FALSE || hmodule == nullptr)
         {

            try
            {

               ::LoadLibraryW(wstring(straOld[i]));

            }
            catch (...)
            {

            }

         }

      }

   }

   return true;

}










id_array module_path_get_pid(const char * pszModulePath, bool bModuleNameIsPropertyFormatted)
{

   ::file::path pathModule(pszModulePath);

   id_array iaPid;

   if (pathModule.is_empty())
   {

      return iaPid;

   }

   ::mutex veri_global_ca2(e_create_new, NULL, "Global\\the_veri_global_ca2");

   sync_lock lock_the_veri_global_ca2(&veri_global_ca2);

   HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   PROCESSENTRY32 entry;

   DWORD dwError = ::GetLastError();

   if (Process32First(process_snap, &entry) && dwError != ERROR_NO_MORE_FILES)
   {

repeat_process:

      string strPath;

      strPath = module_path_from_pid(entry.th32ProcessID);

      //::output_debug_string(strPath + "\n");


      if (bModuleNameIsPropertyFormatted)
      {
         if (entry.th32ProcessID != 0 && strPath.compare_ci(pathModule) == 0)
         {

            iaPid.add((::i64) entry.th32ProcessID);

         }
      }
      else
      {
         if (entry.th32ProcessID != 0 && ::file::path(strPath) == pathModule)
         {

            iaPid.add((::i64) entry.th32ProcessID);

         }

      }

      DWORD dwError = ::GetLastError();

      if (Process32Next(process_snap, &entry) && dwError != ERROR_NO_MORE_FILES)
      {

         goto repeat_process;

      }

   }

   ::CloseHandle(process_snap);

   return iaPid;

}



string module_path_from_pid(u32 pid)
{

   //HANDLE hModuleSnap = INVALID_HANDLE_VALUE;

   //MODULEENTRY32 me32;

   //hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

   //if(hModuleSnap == INVALID_HANDLE_VALUE)
   //{

   //   return "";

   //}

   //me32.dwSize = sizeof(MODULEENTRY32);

   //if(!Module32First(hModuleSnap,&me32))
   //{

   //   CloseHandle(hModuleSnap);           // clean the snapshot matter

   //   return "";

   //}

   //string strName  = solve_relative(me32.szExePath);
   //
   //CloseHandle(hModuleSnap);

   //return strName;



   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

   if (hProcess == nullptr)
      return "";

   WCHAR path[MAX_PATH * 4];

   string strPath;

   if (GetModuleFileNameExW(hProcess, 0, path, sizeof(path) / sizeof(path[0])))
   {
      strPath = solve_relative(string(path));

   }

   ::CloseHandle(hProcess);

   return strPath;

}


// http://stackoverflow.com/questions/4178443/get-the-full-path-from-a-pid-using-delphi
//function GetPathFromPID(const PID: cardinal): string;
//var
//hProcess: THandle;
//path: array[0..MAX_PATH - 1] of char;
//begin
//hProcess := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ,false,PID);
//if hProcess <> 0 then
//try
//if GetModuleFileNameEx(hProcess,0,path,MAX_PATH) = 0 then
//RaiseLastOSError;
//result:= path;
//finally
//CloseHandle(hProcess)
//end
//else
//RaiseLastOSError;
//end;




CLASS_DECL_ACME bool is_shared_library_busy(u32 processid, const string_array & stra)
{

   string_array straSuffix(stra);

   straSuffix.surround("\\");

   return ::windows::pred_process_module(processid, [&](auto & me32)
   {

      return !straSuffix.suffixes_ci(string(me32.szModule)) && !stra.contains_ci(string(me32.szModule));

   });

}


CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra)
{

   return ::windows::pred_process([&](auto pid)
   {

      return !is_shared_library_busy(pid, stra);

   });

}


//CLASS_DECL_ACME bool launch_application(::matter * pobject, const string & strAppId, const string & strParams, int iBitCount)
//{
//
//   ::file::path path;
//
//   if (iBitCount == 64)
//   {
//
//      path = ::dir::program_files_x86() / "ca2/install/x64/install.exe";
//
//   }
//   else if (iBitCount == 32)
//   {
//
//      path = ::dir::program_files_x86() / "ca2/install/x86/install.exe";
//
//   }
//   else
//   {
//
//#if OSBIT == 32
//
//      path = ::dir::program_files_x86() / "ca2/install/x86/install.exe";
//
//#else
//
//      path = ::dir::program_files_x86() / "ca2/install/x64/install.exe";
//
//#endif
//
//   }
//
//   string strApp(strAppId);
//
//   string strExtra;
//
//   if (strParams.has_char())
//   {
//
//      strExtra = " " + strParams;
//
//   }
//
//
//   ::fork(pobject, [=]
//   {
//
//      unsigned int uiPid;
//
//      ::call_async(path, ": app=" + strApp + strExtra, path.folder(), display_normal, false, &uiPid);
//
//   });
//
//   return true;
//
//}





CLASS_DECL_ACME bool process_contains_module(string & strImage, ::u32 processID, const char * pszLibrary)
{

   HANDLE hProcess;

   DWORD cbNeeded;

   index i;

   hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

   if (nullptr == hProcess)
      return false;

   const i32 iMaxModuleCount = 1024;

   array < HMODULE > hmods;

   hmods.set_size(iMaxModuleCount);

   const i32 iImageSize = MAX_PATH * 8;

   memory mem;

   mem.set_size(iImageSize);

   GetModuleFileNameExW(hProcess, nullptr, (WCHAR *)mem.get_data(), (DWORD) (mem.get_size() / sizeof(WCHAR)));

   strImage = (const wchar_t *)mem.get_data();

   wstring wstrLibrary(pszLibrary);

   bool bFound = false;

   if (EnumProcessModules(hProcess, hmods.get_data(), (DWORD) (hmods.get_size_in_bytes()), &cbNeeded))
   {

      for (i = 0; i < ::index(cbNeeded / sizeof(HMODULE)); i++)
      {

         // Get the full path to the module's file.

         if (GetModuleFileNameExW(hProcess, hmods[i], (WCHAR *)mem.get_data(), (DWORD) (mem.get_size() / sizeof(WCHAR))))
         {

            if (!wide_compare_case_insensitive((const wchar_t *)mem.get_data(), wstrLibrary))
            {

               bFound = true;

               break;

            }

         }

      }

   }

   CloseHandle(hProcess);

   return bFound;

}


CLASS_DECL_ACME void shared_library_process(dword_array & dwa, string_array & straProcesses, const char * pszLibrary)
{

   // Get the list of process identifiers.

   dword_array aProcesses;

   aProcesses.set_size(8192);

   DWORD cbNeeded, cProcesses;

   index i;

   if (!EnumProcesses((DWORD *) aProcesses.get_data(), (DWORD) (aProcesses.get_size_in_bytes()), &cbNeeded))
   {

      return;

   }

   // Calculate how many process identifiers were returned.

   cProcesses = cbNeeded / sizeof(DWORD);

   // Print the name of the modules for each process.

   string strImage;

   for (i = 0; i < ::index(cProcesses); i++)
   {

      if (process_contains_module(strImage, aProcesses[i], pszLibrary))
      {

         straProcesses.add(strImage); // there may processes with different pids but same image

         dwa.add(aProcesses[i]);

      }

   }

}








//CLASS_DECL_ACME ::file::path core_app_path(string strAppId)
//{
//
//   ::file::path path = get_last_run_application_path(strAppId);
//
//   if (path.has_char())
//   {
//
//      return path;
//
//   }
//
//   strAppId.replace("-", "_");
//
//   strAppId.replace("/", "_");
//
//   path = "C:\\acme\\time\\x64\\basis\\" + strAppId + ".exe";
//
//   return path;
//
//}
//
//
//
//CLASS_DECL_ACME ::u32 get_current_process_id()
//{
//
//   return ::GetCurrentProcessId();
//
//}






//CLASS_DECL_ACME BOOL LaunchAppIntoDifferentSession(const char* pszProcess, const char* pszCommand, const char* pszDir, STARTUPINFOW* psi, PROCESS_INFORMATION* ppi, int iSession)
//{
//   //PROCESS_INFORMATION pi;
//   //STARTUPINFO si;
//   BOOL bResult = FALSE;
//   DWORD dwSessionId, winlogonPid;
//   HANDLE hUserToken, hUserTokenDup, hPToken, hProcess;
//   DWORD dwCreationFlags;
//
//   // Log the client on to the local computer.
//
//   if (iSession < 0)
//   {
//      dwSessionId = WTSGetActiveConsoleSessionId();
//   }
//   else
//   {
//      dwSessionId = iSession;
//   }
//
//   //////////////////////////////////////////
//   // Find the winlogon process
//   ////////////////////////////////////////
//
//   PROCESSENTRY32W procEntry;
//
//   HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//   if (hSnap == INVALID_HANDLE_VALUE)
//   {
//      return 1;
//   }
//
//   procEntry.dwSize = sizeof(PROCESSENTRY32W);
//
//   if (!Process32FirstW(hSnap, &procEntry))
//   {
//      return 1;
//   }
//
//   do
//   {
//      if (wcsicmp(procEntry.szExeFile,L"winlogon.exe") == 0)
//      {
//         // We found a winlogon process...
//         // make sure it's running in the console session
//         DWORD winlogonSessId = 0;
//         HANDLE h = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, procEntry.th32ProcessID);
//         if (ProcessIdToSessionId(procEntry.th32ProcessID, &winlogonSessId))
//         {
//            if (winlogonSessId == dwSessionId)
//            {
//               winlogonPid = procEntry.th32ProcessID;
//               break;
//
//            }
//         }
//         else
//         {
//            DWORD dwLastError = get_last_error();
//
//            //            TRACE(get_object())("%d", dwLastError);
//         }
//      }
//
//   } while (Process32NextW(hSnap, &procEntry));
//
//   ////////////////////////////////////////////////////////////////////////
//
//   LIBCALL(wtsapi32, WTSQueryUserToken)(dwSessionId, &hUserToken);
//   dwCreationFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
//   //ZeroMemory(&si,sizeof(STARTUPINFO));
//   psi->cb = sizeof(STARTUPINFO);
//   psi->lpDesktop = L"winsta0\\default";
//
//   //ZeroMemory(&pi,sizeof(pi));
//   TOKEN_PRIVILEGES tp;
//   LUID luid;
//   hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, winlogonPid);
//
//   if (!::OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY
//      | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_SESSIONID
//      | TOKEN_READ | TOKEN_WRITE, &hPToken))
//   {
//      int abcd = get_last_error();
//      debug_print("Process token open Error: %u\n", get_last_error());
//   }
//
//   if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
//   {
//      debug_print("lookup Privilege value Error: %u\n", get_last_error());
//   }
//   tp.PrivilegeCount = 1;
//   tp.Privileges[0].Luid = luid;
//   tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
//
//   DuplicateTokenEx(hPToken, MAXIMUM_ALLOWED, nullptr,
//      SecurityIdentification, TokenPrimary, &hUserTokenDup);
//   int dup = get_last_error();
//
//   //Adjust Token privilege
//   SetTokenInformation(hUserTokenDup,
//      TokenSessionId, (void*)(DWORD_PTR)dwSessionId, sizeof(DWORD));
//
//   if (!AdjustTokenPrivileges(hUserTokenDup, FALSE, &tp, sizeof(TOKEN_PRIVILEGES),
//      (PTOKEN_PRIVILEGES)nullptr, nullptr))
//   {
//      int abc = get_last_error();
//      debug_print("Adjust Privilege value Error: %u\n", get_last_error());
//   }
//
//   if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
//   {
//      debug_print("Token does not have the provilege\n");
//   }
//
//   LPVOID pEnv = nullptr;
//
//   if (LIBCALL(userenv, CreateEnvironmentBlock)(&pEnv, hUserTokenDup, TRUE))
//   {
//      dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;
//   }
//   else
//      pEnv = nullptr;
//
//   // Launch the process in the client's logon session.
//
//   bResult = CreateProcessAsUserW(
//      hUserTokenDup,                     // client's access token
//      wstring(pszProcess),    // file to execute
//      (wchar_t*)(const wchar_t *) wstring(pszCommand),                 // command line
//      nullptr,            // pointer to process SECURITY_ATTRIBUTES
//      nullptr,               // pointer to thread SECURITY_ATTRIBUTES
//      FALSE,              // handles are not inheritable
//      dwCreationFlags,     // creation flags
//      pEnv,               // pointer to _new environment block
//      wstring(pszDir),               // name of current directory
//      psi,               // pointer to STARTUPINFO structure
//      ppi                // receives information about _new process
//   );
//   // End impersonation of client.
//
//   //get_last_error Shud be 0
//
//   int iResultOfCreateProcessAsUser = get_last_error();
//
//   //Perform All the Close Handles tasks
//
//   CloseHandle(hProcess);
//   CloseHandle(hUserToken);
//   CloseHandle(hUserTokenDup);
//   CloseHandle(hPToken);
//
//   return 0;
//}

//CLASS_DECL_ACME bool enable_windows_token_privilege(HANDLE h, char * pcszName)
//{
//
//   TOKEN_PRIVILEGES tp;
//
//   if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
//   {
//
//      int iError = get_last_error();
//
//      debug_print("lookup Privilege value Error: %u\n", iError);
//
//      return false;
//
//   }
//
//   tp.PrivilegeCount = 1;
//
//   tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
//
//   if (!AdjustTokenPrivileges(h, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)nullptr, nullptr))
//   {
//
//      int iError = get_last_error();
//
//      debug_print("Adjust Privilege value Error: %u\n", iError);
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//CLASS_DECL_ACME BOOL LaunchAppIntoSystemAcc(const char* pszProcess, const char* pszCommand, const char* pszDir, STARTUPINFOW* psi, PROCESS_INFORMATION* ppi)
//{
//   //PROCESS_INFORMATION pi;
//   //STARTUPINFO si;
//   BOOL bResult = FALSE;
//   //   DWORD dwSessionId,winlogonPid;
//   HANDLE hUserTokenDup, hProcess, hPToken;
//   DWORD dwCreationFlags;
//   HANDLE hUserToken = nullptr;
//
//
//   // Log the client on to the local computer.
//
//   dwCreationFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
//   //ZeroMemory(&si,sizeof(STARTUPINFO));
//   psi->cb = sizeof(STARTUPINFOW);
//   psi->lpDesktop = L"winsta0\\default";
//
//   //ZeroMemory(&pi,sizeof(pi));
//
////   LUID luid;
//   //hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,winlogonPid);
//   hProcess = ::GetCurrentProcess();
//
//   //hPToken = hUserToken;
//
//   if (!::OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hPToken))
//   {
//      int abcd = get_last_error();
//      debug_print("Process token open Error: %u\n", get_last_error());
//   }
//
//   if (!enable_windows_token_privilege(hPToken, SE_DEBUG_NAME))
//   {
//
//      return FALSE;
//
//   }
//
//   if (!enable_windows_token_privilege(hPToken, SE_CREATE_TOKEN_NAME))
//   {
//      return FALSE;
//   }
//
//   if (!enable_windows_token_privilege(hPToken, SE_TCB_NAME))
//   {
//
//      return FALSE;
//
//   }
//
//   if (!enable_windows_token_privilege(hPToken, SE_ASSIGNPRIMARYTOKEN_NAME))
//   {
//
//      return FALSE;
//
//   }
//
//   if (!enable_windows_token_privilege(hPToken, SE_INCREASE_QUOTA_NAME))
//   {
//
//      return FALSE;
//
//   }
//
//   //if(get_last_error() == ERROR_NOT_ALL_ASSIGNED)
//   //{
//   //   debug_print("Token does not have the provilege\n");
//   //}
//   // "LOCAL SERVICE" or "LocalService" ?
//   // "NETWORK SERVICE" or "NetworkService" ?
//   if (!LogonUserW(L"LocalService", L"NT AUTHORITY", nullptr, LOGON32_LOGON_SERVICE, LOGON32_PROVIDER_DEFAULT, &hUserToken))
//   {
//      DWORD dwError = ::get_last_error();
//      string str;
//      str.Format("lookup Privilege value Error: %u\n", dwError);
//      message_box(str, "Help Me", e_message_box_ok);
//      return FALSE;
//   }
//   if (!DuplicateTokenEx(hUserToken, TOKEN_ALL_ACCESS, nullptr, SecurityDelegation, TokenPrimary, &hUserTokenDup))
//   {
//      int dup = get_last_error();
//      debug_print("DuplicateTokenEx Error: %u\n", get_last_error());
//   }
//
//   //Adjust Token privilege
//   //SetTokenInformation(hUserTokenDup,
//   //   TokenSessionId,(void*)dwSessionId,sizeof(DWORD));
//
//
//
//   LPVOID pEnv = nullptr;
//
//   if (LIBCALL(userenv, CreateEnvironmentBlock)(&pEnv, hUserTokenDup, TRUE))
//   {
//      dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;
//   }
//   else
//      pEnv = nullptr;
//
//   // Launch the process in the client's logon session.
//
//   bResult = CreateProcessAsUserW(
//      hUserTokenDup,                     // client's access token
//      wstring(pszProcess),    // file to execute
//      (wchar_t*)(const wchar_t*) wstring(pszCommand),                 // command line
//      nullptr,            // pointer to process SECURITY_ATTRIBUTES
//      nullptr,               // pointer to thread SECURITY_ATTRIBUTES
//      FALSE,              // handles are not inheritable
//      dwCreationFlags,     // creation flags
//      pEnv,               // pointer to _new environment block
//      wstring(pszDir),               // name of current directory
//      psi,               // pointer to STARTUPINFO structure
//      ppi                // receives information about _new process
//   );
//   // End impersonation of client.
//
//   //get_last_error Shud be 0
//
//   //int iResultOfCreateProcessAsUser = get_last_error();
//
//   //Perform All the Close Handles tasks
//
//   //CloseHandle(hProcess);
//   //CloseHandle(hUserToken);
//   //CloseHandle(hUserTokenDup);
//   //CloseHandle(hPToken);
//
//   return TRUE;
//}
//


CLASS_DECL_ACME int_bool is_process_running(::u32 pid)
{

   HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);

   DWORD ret = WaitForSingleObject(process, 0);

   CloseHandle(process);

   return ret == WAIT_TIMEOUT;

}



