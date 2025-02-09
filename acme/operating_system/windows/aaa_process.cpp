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
//   unsigned long long  Reserved1;
//   unsigned long long  PebBaseAddress;
//   unsigned long long  Reserved2[2];
//   unsigned long long  UniqueProcessId;
//   unsigned long long  Reserved3;
//} PROCESS_BASIC_INFORMATION64;

//typedef NTSTATUS(NTAPI *_NtQueryInformationProcess)(HANDLE ProcessHandle, unsigned int ProcessInformationClass, PVOID ProcessInformation, unsigned int ProcessInformationLength, PDWORD ReturnLength);
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
//      informationf("Could not read the address of ProcessParameters!\n");
//      return "";
//   }
//
//
//   _UNICODE_STRING ustrCommandLine;
//
//   if (!ReadProcessMemory(handleProcess, (PCHAR)&pparam1->CommandLine, &ustrCommandLine, sizeof(ustrCommandLine), nullptr))
//   {
//      informationf("Could not read CommandLine!\n");
//      return "";
//   }
//
//   /* allocate memory to hold the command line */
//   WCHAR * commandLineContents = (WCHAR *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(ustrCommandLine.Length + sizeof(WCHAR));
//   /* read the command line */
//   if (!ReadProcessMemory(handleProcess, ustrCommandLine.Buffer, commandLineContents, ustrCommandLine.Length, nullptr))
//   {
//      informationf("Could not read the command line string!\n");
//      return "";
//   }
//   commandLineContents[ustrCommandLine.Length / sizeof(WCHAR)] = L'\0';
//   string str = unicode_to_utf8(commandLineContents);
//   memory_free_debug(commandLineContents, 0);
//   return str;
//}






//string get_display_error(unsigned int NTStatusMessage);
//
//PPEB GetPebAddress(HANDLE handleProcess)
//{
//   _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
//   PROCESS_BASIC_INFORMATION pbi;
//   memory_set(&pbi, 0, sizeof(pbi));
//   DWORD dwInLen = sizeof(pbi);
//   DWORD dwOutLen = 0xffffffff;
//   unsigned int dwStatus = NtQueryInformationProcess(handleProcess, ProcessBasicInformation, &pbi, dwInLen, &dwOutLen);
//   string strError = get_display_error(dwStatus);
//   if ((dwStatus & 3) == 3)
//   {
//      return nullptr;
//   }
//   return pbi.PebBaseAddress;
//}



struct shell_execute :
   public SHELLEXECUTEINFOW
{

   wstring        m_wstrFile;

   wstring        m_wstrParams;

   shell_execute(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams)
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


   bool synchronization(const class ::wait & wait)
   {

      fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;

      if (!async())
      {

         return false;

      }

      auto start = ::wait::now();

      DWORD dwError = ::GetLastError();

      DWORD dwExitCode = 0;

      while(true)
      {
         
         class ::wait waitNow = minimum(wait - start.elapsed(), 1000_ms);

         if (waitNow.is_null())
         {

            break;

         }

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

         preempt(waitNow);

      }

      ::CloseHandle(hProcess);

      return true;


   }


};


bool shell_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams)
{

   shell_execute execute(pszFile, pszParams);

   return execute.async();

}


bool shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::duration durationTimeout)
{

   shell_execute execute(pszFile, pszParams);

   return execute.synchronization(durationTimeout);

}


bool root_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams)
{

   shell_execute execute(pszFile, pszParams);

   execute.lpVerb = L"RunAs";


   return execute.async();

}


bool root_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::duration durationTimeout)
{

   shell_execute execute(pszFile, pszParams);

   execute.lpVerb = L"RunAs";


   return execute.synchronization(durationTimeout);

}


void call_async(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int *puiPid)
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


void call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
{

   SHELLEXECUTEINFOW infoa;

   memory_set(&infoa, 0, sizeof(infoa));

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

   set["pid"] = (unsigned int) ::GetProcessId(infoa.hProcess);

   DWORD dwExitCode = (DWORD) -1;

   ::duration duration;

   duration.Now();

   while (::task_get_run())
   {
      // Thanks from Blehman@Twitch from Slovakia through Googling...
      // 2020-02-19
      if (WaitForSingleObject(infoa.hProcess, 200) == WAIT_OBJECT_0)
      {

         break;

      }

      if (duration.elapsed() > durationTimeout)
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
         set["TerminateProcess_GetLastError"] = (unsigned int) TerminateProcess_GetLastError;

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





//int get_current_processor_index()
//{
//
//
//   return ::GetCurrentProcessorNumber();
//
//
//}
//
//int get_current_process_maximum_affinity()
//{
//
//   DWORD_PTR dwProcessAffinityMask;
//   DWORD_PTR dwSystemAffinityMask;
//   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
//   {
//      return 0;
//   }
//   int iMax = -1;
//   uptr dwMask = 1;
//   for (int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
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
//int get_current_process_affinity_order()
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
//   int iCount = 0;
//   uptr dwMask = 1;
//   for (int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
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
//CLASS_DECL_ACMEunsigned long long translate_processor_affinity(int iOrder)
//{
//
//   DWORD_PTR dwProcessAffinityMask;
//   DWORD_PTR dwSystemAffinityMask;
//   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
//   {
//      return 0;
//   }
//   int j = 0;
//   uptr dwMask = 1;
//   for (int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
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

CLASS_DECL_ACME unsigned int get_current_process_id()
{

   return ::GetCurrentProcessId();

}





//
//namespace process
//{


   bool set_process_priority(::enum_priority epriority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(epriority)) != 0);


   }

//
//} // namespace process


//CLASS_DECL_ACME_WINDOWS_COMMONunsigned int get_current_process_id()
//{
//
//   return ::GetCurrentProcessId();
//
//}
