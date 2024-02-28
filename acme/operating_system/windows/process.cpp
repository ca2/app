// Created by camilo from _.h on 2023-05-12 12:09 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_.h"
//
//
//namespace windows
//{
//
//
//   CLASS_DECL_ACME bool for_each_process_module(DWORD dwProcess, ::function < bool(const MODULEENTRY32 & moduleentry32) > & function)
//   {
//
//      HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
//
//      MODULEENTRY32 me32;
//
//      bool bStopped = false;
//
//      hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcess);
//
//      if (hModuleSnap == INVALID_HANDLE_VALUE)
//      {
//
//         return false;
//
//      }
//
//      me32.dwSize = sizeof(MODULEENTRY32);
//
//      if (!Module32First(hModuleSnap, &me32))
//      {
//
//         ::CloseHandle(hModuleSnap);
//
//         return false;
//
//      }
//
//      do
//      {
//
//         if (!function(me32))
//         {
//
//            bStopped = true;
//
//            break;
//
//         }
//
//      } while (Module32Next(hModuleSnap, &me32));
//
//      ::CloseHandle(hModuleSnap);
//
//      return bStopped;
//
//   }
//
//
//   bool for_each_process_identifier(::function < bool(::process_identifier processidentifier) > & function)
//   {
//
//      HANDLE hProcessSnap;
//
//      PROCESSENTRY32 pe32;
//
//      hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//
//      if (hProcessSnap == INVALID_HANDLE_VALUE)
//      {
//
//         return false;
//
//      }
//
//      pe32.dwSize = sizeof(PROCESSENTRY32);
//
//      if (!Process32First(hProcessSnap, &pe32))
//      {
//
//         ::CloseHandle(hProcessSnap);
//
//         return false;
//
//      }
//
//      bool bStopped = false;
//
//      do
//      {
//
//         if (!function((::process_identifier)pe32.th32ProcessID))
//         {
//
//            bStopped = true;
//
//            break;
//
//         }
//
//      } while (Process32Next(hProcessSnap, &pe32));
//
//      ::CloseHandle(hProcessSnap);
//
//      return bStopped;
//
//   }
//
//
//} // namespace windows
//
//
//
