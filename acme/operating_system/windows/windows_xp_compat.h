#pragma once

#if defined(WINDOWS_XP)
#include <windows.h>
#include <dbghelp.h>

inline DWORD ca2_xp_get_thread_id(HANDLE thread)
{
   using get_thread_id = DWORD (WINAPI *)(HANDLE);
   static const auto getThreadId = reinterpret_cast<get_thread_id>(
      GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetThreadId"));
   if (getThreadId)
      return getThreadId(thread);

   // ThreadBasicInformation (class 0) exists on NT5. Query through NTDLL
   // rather than inspecting another thread's TEB or taking ownership of it.
   struct thread_basic_information
   {
      LONG exitStatus;
      PVOID teb;
      HANDLE processId;
      HANDLE threadId;
      ULONG_PTR affinity;
      LONG priority;
      LONG basePriority;
   } information{};
   using query_thread = LONG (NTAPI *)(HANDLE, ULONG, PVOID, ULONG, PULONG);
   using status_to_error = ULONG (WINAPI *)(LONG);
   const auto ntdll = GetModuleHandleW(L"ntdll.dll");
   static const auto queryThread = reinterpret_cast<query_thread>(
      GetProcAddress(ntdll, "NtQueryInformationThread"));
   static const auto statusToError = reinterpret_cast<status_to_error>(
      GetProcAddress(ntdll, "RtlNtStatusToDosError"));
   if (!queryThread)
   {
      SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
      return 0;
   }
   const LONG status = queryThread(thread, 0, &information, sizeof(information), nullptr);
   if (status < 0)
   {
      SetLastError(statusToError ? statusToError(status) : ERROR_GEN_FAILURE);
      return 0;
   }
   return static_cast<DWORD>(reinterpret_cast<ULONG_PTR>(information.threadId));
}

inline int ca2_xp_current_processor_index()
{
   using get_processor = DWORD (WINAPI *)();
   static const auto getProcessor = reinterpret_cast<get_processor>(
      GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetCurrentProcessorNumber"));
   // -1 is the node interface's existing unknown-processor value. Do not
   // change thread affinity or report an invented CPU index on XP.
   return getProcessor ? static_cast<int>(getProcessor()) : -1;
}

inline bool ca2_xp_is_light_theme()
{
   HKEY key = nullptr;
   if (RegOpenKeyExW(HKEY_CURRENT_USER,
      L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
      0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS)
      return true; // XP has no AppsUseLightTheme setting.
   DWORD value = 1, type = 0, size = sizeof(value);
   const LONG result = RegQueryValueExW(key, L"AppsUseLightTheme", nullptr,
      &type, reinterpret_cast<BYTE *>(&value), &size);
   RegCloseKey(key);
   return result != ERROR_SUCCESS || type != REG_DWORD || size != sizeof(value) || value != 0;
}

inline BOOL ca2_xp_refresh_module_list(HANDLE process)
{
   using refresh_modules = BOOL (WINAPI *)(HANDLE);
   static const auto refresh = reinterpret_cast<refresh_modules>(
      GetProcAddress(GetModuleHandleW(L"dbghelp.dll"), "SymRefreshModuleList"));
   if (refresh)
      return refresh(process);
   // Caller holds the shared DbgHelp lock. Re-invade the process on XP's old
   // DbgHelp; this drops its cached symbols, which will be resolved again.
   if (!SymCleanup(process))
      return FALSE;
   return SymInitialize(process, nullptr, TRUE);
}
#endif
