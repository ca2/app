#include "framework.h"
#include "acme/operating_system.h"
#include <ShellApi.h>


#include "process.h"


#undef User
#undef Node


#include <Wtsapi32.h>
#include <Userenv.h>
#include <PSapi.h>


HANDLE dup_handle(HANDLE h)
{

   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &h, 0, false, DUPLICATE_SAME_ACCESS);

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
//   WCHAR * commandLineContents = (WCHAR *)memory_allocate(ustrCommandLine.Length + sizeof(WCHAR));
//   /* read the command line */
//   if (!ReadProcessMemory(handleProcess, ustrCommandLine.Buffer, commandLineContents, ustrCommandLine.Length, nullptr))
//   {
//      ::output_debug_string("Could not read the command line string!\n");
//      return "";
//   }
//   commandLineContents[ustrCommandLine.Length / sizeof(WCHAR)] = L'\0';
//   string str = ::str::international::unicode_to_utf8(commandLineContents);
//   memory_free_debug(commandLineContents, 0);
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

//
//string get_display_error(u32 NTStatusMessage)
//{
//
//   return get_last_error_message(NTStatusMessage);
//
//}


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


   bool synchronization_object(::duration durationTimeout)
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

         preempt(1000_ms);

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

   return execute.synchronization_object(durationTimeout);

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


   return execute.synchronization_object(durationTimeout);

}


::e_status call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int *puiPid)
{

   SHELLEXECUTEINFOW info = {};

   wstring wstrFile = unicode(pszPath);
   wstring wstrParam = unicode(pszParam);
   wstring wstrDir = unicode(pszDir);

   info.cbSize = sizeof(SHELLEXECUTEINFOW);

   if (edisplay == e_display_default)
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


::e_status call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
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

   infoa.nShow = is_visible(edisplay) ? e_display_normal : SW_HIDE;

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

   ::millis millis;

   millis.Now();

   while (::task_get_run())
   {
      // Thanks from Blehman@Twitch from Slovakia through Googling...
      // 2020-02-19
      if (WaitForSingleObject(infoa.hProcess, 200) == WAIT_OBJECT_0)
      {

         break;

      }

      if (millis.elapsed() > durationTimeout)
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

   int iExitCode = dwExitCode;

   if (iExitCode == 0)
   {

      return ::success;

   }
   else if(iExitCode > 0)
   {
    
      return e_status_process_result_positive_base + iExitCode;

   }
   else
   {

      return e_status_process_result_negative_base + iExitCode;

   }

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


CLASS_DECL_ACME ::u64 translate_processor_affinity(int iOrder)
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



//i32 get_current_processor_index()
//{
//
//
//   return ::GetCurrentProcessorNumber();
//
//
//}
//
//i32 get_current_process_maximum_affinity()
//{
//
//   DWORD_PTR dwProcessAffinityMask;
//   DWORD_PTR dwSystemAffinityMask;
//   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
//   {
//      return 0;
//   }
//   i32 iMax = -1;
//   uptr dwMask = 1;
//   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
//   {
//      if ((dwMask & dwProcessAffinityMask) != 0)
//      {
//         iMax = i;
//      }
//      dwMask = dwMask << 1;
//   }
//
//   return iMax;
//
//}
//
//i32 get_current_process_affinity_order()
//{
//
//
//   DWORD_PTR dwProcessAffinityMask;
//   DWORD_PTR dwSystemAffinityMask;
//
//   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
//   {
//
//      return 0;
//
//   }
//
//   i32 iCount = 0;
//   uptr dwMask = 1;
//   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
//   {
//      if ((dwMask & dwProcessAffinityMask) != 0)
//      {
//         iCount++;
//      }
//      dwMask = dwMask << 1;
//   }
//
//   return iCount;
//
//
//}
//
//
//CLASS_DECL_ACME::u64 translate_processor_affinity(int iOrder)
//{
//
//   DWORD_PTR dwProcessAffinityMask;
//   DWORD_PTR dwSystemAffinityMask;
//   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
//   {
//      return 0;
//   }
//   i32 j = 0;
//   uptr dwMask = 1;
//   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
//   {
//      if ((dwMask & dwProcessAffinityMask) != 0)
//      {
//         if (iOrder == j)
//         {
//            return dwMask;
//         }
//         j++;
//      }
//      dwMask = dwMask << 1;
//   }
//
//   return 0;
//
//}

CLASS_DECL_ACME::u32 get_current_process_id()
{

   return ::GetCurrentProcessId();

}






namespace process
{


   bool set_priority(::enum_priority epriority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(epriority)) != 0);


   }


} // namespace process


//CLASS_DECL_ACME_WINDOWS_COMMON::u32 get_current_process_id()
//{
//
//   return ::GetCurrentProcessId();
//
//}
