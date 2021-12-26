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


CLASS_DECL_ACME ::e_status command_system(string& strOutput, string& strError, int& iExitCode, const char* psz, enum_command_system ecommandsystem, const ::duration& durationTimeout)
{

   strOutput.Empty();

   string str(psz);

   wstring wstr;

   wstr = str;

   STARTUPINFO si = { sizeof(si) };
   PROCESS_INFORMATION pi = {};
   SECURITY_ATTRIBUTES saAttr;

   ZeroMemory(&saAttr, sizeof(saAttr));

   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
   saAttr.bInheritHandle = TRUE;
   saAttr.lpSecurityDescriptor = NULL;

   HANDLE hOutRd;
   HANDLE hOutWr;

   // Create a pipe for the child process's STDOUT. 

   if (!CreatePipe(&hOutRd, &hOutWr, &saAttr, 0))
   {

      // log error
      DWORD dwLastError = GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      return estatus;

   }

   // Ensure the read handle to the pipe for STDOUT is not inherited.
   if (!SetHandleInformation(hOutRd, HANDLE_FLAG_INHERIT, 0))
   {

      ::CloseHandle(hOutRd);
      ::CloseHandle(hOutWr);

      // log error
      DWORD dwLastError = GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      return estatus;

   }

   HANDLE hErrRd;
   HANDLE hErrWr;

   // Create a pipe for the child process's STDOUT. 

   if (!CreatePipe(&hErrRd, &hErrWr, &saAttr, 0))
   {

      ::CloseHandle(hOutRd);
      ::CloseHandle(hOutWr);

      // log error
      DWORD dwLastError = GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      return estatus;

   }


   // Ensure the read handle to the pipe for STDOUT is not inherited.
   if (!SetHandleInformation(hErrRd, HANDLE_FLAG_INHERIT, 0))
   {

      ::CloseHandle(hOutRd);
      ::CloseHandle(hOutWr);
      ::CloseHandle(hErrRd);
      ::CloseHandle(hErrWr);

      // log error
      DWORD dwLastError = GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      return estatus;

   }

   {
   
      DWORD dwState = PIPE_NOWAIT;

      SetNamedPipeHandleState(hOutRd, &dwState, nullptr, nullptr);

   }

   {

      DWORD dwState = PIPE_NOWAIT;

      SetNamedPipeHandleState(hErrRd, &dwState, nullptr, nullptr);

   }

   ZeroMemory(&si, sizeof(si));
   si.cb = sizeof(si);
   si.hStdError = hOutWr;
   si.hStdOutput = hErrWr;
   si.dwFlags |= STARTF_USESTDHANDLES;

   ZeroMemory(&pi, sizeof(pi));

   if (!CreateProcessW(nullptr, wstr, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
   {

      ::CloseHandle(hOutRd);
      ::CloseHandle(hOutWr);
      ::CloseHandle(hErrRd);
      ::CloseHandle(hErrWr);

      DWORD dwLastError = ::GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      return estatus;

   }

   ::duration durationStart;

   durationStart.Now();

   while (true)
   {

      auto result = WaitForSingleObject(pi.hProcess, 100);

      char sz[256];

      while (true)
      {

         DWORD dwRead = 0;

         if (!ReadFile(hOutRd, sz, 256, &dwRead, nullptr))
         {

            break;

         }

         string strMessage(sz, dwRead);

         if(ecommandsystem & e_command_system_inline_log)
         {

            printf("%s", strMessage.c_str());

         }

         strOutput += strMessage;

         if (dwRead == 0)
         {

            break;

         }

      };

      while (true)
      {

         DWORD dwRead = 0;

         if (!ReadFile(hErrRd, sz, 256, &dwRead, nullptr))
         {

            break;

         }

         string strMessage(sz, dwRead);

         if(ecommandsystem & e_command_system_inline_log)
         {

            fprintf(stderr, "%s", strMessage.c_str());

         }

         strError += strMessage;

         if (dwRead == 0)
         {

            break;

         }

      };

      if (result == WAIT_OBJECT_0)
      {

         break;

      }

      if (!durationTimeout.is_infinite() && durationStart.elapsed() > durationTimeout)
      {

         break;

      }

   }
   
   DWORD dwExitCode = 0;

   if (GetExitCodeProcess(pi.hProcess, &dwExitCode))
   {

      iExitCode = dwExitCode;

   }

   ::CloseHandle(hOutRd);
   ::CloseHandle(hOutWr);
   ::CloseHandle(hErrRd);
   ::CloseHandle(hErrWr);

   CloseHandle(pi.hProcess);
   CloseHandle(pi.hThread);


   return ::success;

}
