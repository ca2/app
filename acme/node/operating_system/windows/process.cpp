// Recreated by camilo on 2021-12-16 19:41 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"


CLASS_DECL_ACME::u32 get_current_process_id()
{

   return ::GetCurrentProcessId();

}


CLASS_DECL_ACME::u64 translate_processor_affinity(int iOrder)
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


bool set_process_priority(::enum_priority epriority)
{

   return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(epriority)) != 0);


}


CLASS_DECL_ACME ::e_status command_system(int & iExitCode, const char* psz, const ::duration& durationTimeout)
{

   string str(psz);

   wstring wstr;

   wstr = str;

   STARTUPINFO info = { sizeof(info) };

   PROCESS_INFORMATION processInfo;

   if (!CreateProcessW(nullptr, wstr, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &info, &processInfo))
   {

      DWORD dwLastError = ::GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      return estatus;

   }

   DWORD dwTimeout = durationTimeout.is_infinite() ? INFINITE : durationTimeout.integral_millisecond().m_i;
   
   WaitForSingleObject(processInfo.hProcess, dwTimeout);

   DWORD dwExitCode = 0;

   if (GetExitCodeProcess(processInfo.hProcess, &dwExitCode))
   {

      iExitCode = dwExitCode;

   }

   CloseHandle(processInfo.hProcess);

   CloseHandle(processInfo.hThread);

   return ::success;

}
