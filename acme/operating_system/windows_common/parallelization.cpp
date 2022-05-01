#include "framework.h"
#include "acme/operating_system.h"


#include "api.h"
#include "parallelization.h"


typedef HRESULT WINAPI FN_GetThreadDescription(HANDLE htask, PWSTR* ppszThreadDescription);




string get_task_name(htask_t htask)
{

   HRESULT hr;

   LPWSTR lpwsz = nullptr;

#ifdef _UWP

   hr = GetThreadDescription(htask, &lpwsz);

#else

   hr = E_FAIL;

   static auto pfn_get_thread_description = ::windows::api < FN_GetThreadDescription* >::get_address("Kernel32.dll", "GetThreadDescription");

   if (pfn_get_thread_description)
   {

      hr = pfn_get_thread_description((HANDLE) htask, &lpwsz);

   }

#endif

   if (SUCCEEDED(hr))
   {

      string str;

      str = lpwsz;

      ::LocalFree(lpwsz);

      return str;

   }

   ::task* ptask = ::get_task();

   if (::is_null(ptask))
   {

      return "";

   }

   return ::get_task_name(ptask);

}


typedef HRESULT WINAPI FN_SetThreadDescription(_In_ htask_t htask, _In_ PCWSTR pThreadDescription);


CLASS_DECL_ACME void task_set_name(htask_t htask, const char* pszName)
{

   bool bOk1 = false;

#ifdef _UWP

   bOk1 = SUCCEEDED(SetThreadDescription(htask, wstring(pszName)));

#else

   static auto pfn_set_thread_description = ::windows::api < FN_SetThreadDescription* >::get_address("kernel32.dll", "SetThreadDescription");

   if (pfn_set_thread_description)
   {

      bOk1 = SUCCEEDED(pfn_set_thread_description(htask, wstring(pszName)));

   }

   if (!bOk1)
   {

      bOk1 = SetThreadName(GetThreadId((HANDLE) htask), pszName) != false;

   }

#endif

   if (!bOk1)
   {

      throw ::exception(error_failed);

   }

}



typedef HRESULT WINAPI FN_SetThreadDescription(_In_ htask_t htask, _In_ PCWSTR pThreadDescription);


i32 get_os_thread_priority(::enum_priority epriority)
{

   if (epriority <= ::e_priority_none)
      return THREAD_PRIORITY_NORMAL;

   if (epriority <= ::e_priority_idle)
      return THREAD_PRIORITY_IDLE;

   if (epriority <= ::e_priority_lowest)
      return THREAD_PRIORITY_LOWEST;

   if (epriority <= ::e_priority_below_normal)
      return THREAD_PRIORITY_BELOW_NORMAL;

   if (epriority <= ::e_priority_normal)
      return THREAD_PRIORITY_NORMAL;

   if (epriority <= ::e_priority_above_normal)
      return THREAD_PRIORITY_ABOVE_NORMAL;

   if (epriority <= ::e_priority_highest)
      return THREAD_PRIORITY_HIGHEST;

   return THREAD_PRIORITY_TIME_CRITICAL;

}



i32 get_os_priority_class(::enum_priority epriority)
{

   if (epriority <= ::e_priority_none)
      return NORMAL_PRIORITY_CLASS;

   if (epriority <= ::e_priority_idle)
      return IDLE_PRIORITY_CLASS;

   if (epriority <= ::e_priority_lowest)
      return BELOW_NORMAL_PRIORITY_CLASS;

   if (epriority <= ::e_priority_below_normal)
      return BELOW_NORMAL_PRIORITY_CLASS;

   if (epriority <= ::e_priority_normal)
      return NORMAL_PRIORITY_CLASS;

   if (epriority <= ::e_priority_above_normal)
      return ABOVE_NORMAL_PRIORITY_CLASS;

   if (epriority <= ::e_priority_highest)
      return HIGH_PRIORITY_CLASS;

   return REALTIME_PRIORITY_CLASS;

}


::enum_priority get_os_thread_scheduling_priority(i32 nPriority)
{

   ::enum_priority epriority;

   if (nPriority <= THREAD_PRIORITY_IDLE)
   {
      epriority = ::e_priority_idle;
   }
   else if (nPriority <= THREAD_PRIORITY_LOWEST)
   {
      epriority = ::e_priority_lowest;
   }
   else if (nPriority <= THREAD_PRIORITY_BELOW_NORMAL)
   {
      epriority = ::e_priority_below_normal;
   }
   else if (nPriority <= THREAD_PRIORITY_NORMAL)
   {
      epriority = ::e_priority_normal;
   }
   else if (nPriority <= THREAD_PRIORITY_ABOVE_NORMAL)
   {
      epriority = ::e_priority_above_normal;
   }
   else if (nPriority <= THREAD_PRIORITY_HIGHEST)
   {
      epriority = ::e_priority_highest;
   }
   else
   {
      epriority = ::e_priority_time_critical;
   }

   return epriority;

}


::enum_priority get_os_class_scheduling_priority(i32 nPriority)
{

   ::enum_priority epriority;

   if (nPriority <= IDLE_PRIORITY_CLASS)
   {
      epriority = ::e_priority_idle;
   }
   else if (nPriority <= BELOW_NORMAL_PRIORITY_CLASS)
   {
      epriority = ::e_priority_below_normal;
   }
   else if (nPriority <= NORMAL_PRIORITY_CLASS)
   {
      epriority = ::e_priority_normal;
   }
   else if (nPriority <= ABOVE_NORMAL_PRIORITY_CLASS)
   {
      epriority = ::e_priority_above_normal;
   }
   else if (nPriority <= HIGH_PRIORITY_CLASS)
   {
      epriority = ::e_priority_highest;
   }
   else
   {
      epriority = ::e_priority_time_critical;
   }

   return epriority;

}


namespace parallelization
{


   bool set_priority(::enum_priority epriority)
   {

      return set_priority(get_current_htask(), epriority);

   }


   bool set_priority(htask_t htask, ::enum_priority epriority)
   {

      return (::SetThreadPriority(htask, get_os_thread_priority(epriority)) != 0);

   }


   ::enum_priority get_priority()
   {

      return get_priority(get_current_htask());

   }


   ::enum_priority get_priority(htask_t htask)
   {

      return get_os_thread_scheduling_priority(::GetThreadPriority(htask));

   }


} // namespace acme


CLASS_DECL_ACME int get_processor_count()
{

   SYSTEM_INFO sysinfo;

   GetSystemInfo(&sysinfo);

   return sysinfo.dwNumberOfProcessors;

}


void task_set_name(const char* pszThreadName)
{

   /*return*/ task_set_name((htask_t) ::GetCurrentThread(), pszThreadName);

}


const ::u32 MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)

typedef struct tagTHREADNAME_INFO
{
   ::u32 dwType; // Must be 0x1000.
   const char * szName; // Pointer to name (in user addr space).
   ::u32 dwThreadID; // Thread ID (-1=caller thread).
   ::u32 dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

int_bool SetThreadName(::u32 dwThreadID, const char* threadName)
{
   THREADNAME_INFO info;
   info.dwType = 0x1000;
   info.szName = threadName;
   info.dwThreadID = dwThreadID;
   info.dwFlags = 0;
#pragma warning(push)
#pragma warning(disable: 6320 6322)
   __try {
      RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)& info);
   }
   __except (EXCEPTION_EXECUTE_HANDLER) {
   }
#pragma warning(pop)

   return true;

}


CLASS_DECL_ACME string task_get_name()
{

   return get_task_name((htask_t)::GetCurrentThread());

}


//enum_synchronization_result windows_wait_result_to_synchronization_result(int iResult)
//{
//
//   if (iResult >= WAIT_ABANDONED_0 && iResult < (WAIT_ABANDONED_0 + MAXIMUM_WAIT_OBJECTS))
//   {
//
//      return (enum_synchronization_result)((int)e_synchronization_result_abandoned_base + (iResult - WAIT_ABANDONED_0));
//
//   }
//   else if (iResult == WAIT_IO_COMPLETION)
//   {
//
//      return e_synchronization_result_io_completion;
//
//   }
//   else if (iResult == WAIT_FAILED)
//   {
//
//      return e_synchronization_result_error;
//
//   }
//   else if (iResult == WAIT_TIMEOUT)
//   {
//
//      return e_synchronization_result_timed_out;
//
//   }
//   else if (iResult >= WAIT_OBJECT_0 && iResult < (WAIT_OBJECT_0 + MAXIMUM_WAIT_OBJECTS))
//   {
//
//      return (enum_synchronization_result)((int)e_synchronization_result_signaled_base + (iResult - WAIT_OBJECT_0));
//
//   }
//   else
//   {
//
//      return e_synchronization_result_error;
//
//   }
//
//}



