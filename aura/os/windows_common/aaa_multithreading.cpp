#include "framework.h"
#include "new_api.h"


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

      hr = pfn_get_thread_description(htask, &lpwsz);

   }

#endif

   if (SUCCEEDED(hr))
   {

      string str;

      str = lpwsz;

      ::LocalFree(lpwsz);

      return str;

   }

   ::thread* pthread = ::get_task();

   if (::is_null(pthread))
   {

      return "";

   }

   if (pthread->m_strThreadName.has_char())
   {

      return pthread->m_strThreadName;

   }

   if (pthread->m_strThreadTag.has_char())
   {

      return pthread->m_strThreadTag;

   }

   return pthread->type_name();

}




typedef HRESULT WINAPI FN_SetThreadDescription(_In_ htask_t htask, _In_ PCWSTR pThreadDescription);


CLASS_DECL_AURA bool task_set_name(htask_t htask, const ::string & pszName)
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

      bOk1 = SetThreadName(GetThreadId(htask), pszName) != false;

   }

#endif

   bool bOk2 = true;

   ::thread* pthread = ::get_task();

   if (pthread != NULL)
   {

      if (!pthread->task_set_name(pszName))
      {

         bOk2 = false;

      }

   }

   return bOk1 && bOk2;

}



typedef HRESULT WINAPI FN_SetThreadDescription(_In_ htask_t htask, _In_ PCWSTR pThreadDescription);


i32 get_os_thread_priority(::e_priority epriority)
{

   if (epriority <= ::priority_none)
      return THREAD_PRIORITY_NORMAL;

   if (epriority <= ::priority_idle)
      return THREAD_PRIORITY_IDLE;

   if (epriority <= ::priority_lowest)
      return THREAD_PRIORITY_LOWEST;

   if (epriority <= ::priority_below_normal)
      return THREAD_PRIORITY_BELOW_NORMAL;

   if (epriority <= ::priority_normal)
      return THREAD_PRIORITY_NORMAL;

   if (epriority <= ::priority_above_normal)
      return THREAD_PRIORITY_ABOVE_NORMAL;

   if (epriority <= ::priority_highest)
      return THREAD_PRIORITY_HIGHEST;

   return THREAD_PRIORITY_TIME_CRITICAL;

}



i32 get_os_priority_class(::e_priority epriority)
{

   if (epriority <= ::priority_none)
      return NORMAL_PRIORITY_CLASS;

   if (epriority <= ::priority_idle)
      return IDLE_PRIORITY_CLASS;

   if (epriority <= ::priority_lowest)
      return BELOW_NORMAL_PRIORITY_CLASS;

   if (epriority <= ::priority_below_normal)
      return BELOW_NORMAL_PRIORITY_CLASS;

   if (epriority <= ::priority_normal)
      return NORMAL_PRIORITY_CLASS;

   if (epriority <= ::priority_above_normal)
      return ABOVE_NORMAL_PRIORITY_CLASS;

   if (epriority <= ::priority_highest)
      return HIGH_PRIORITY_CLASS;

   return REALTIME_PRIORITY_CLASS;

}


::e_priority get_os_thread_scheduling_priority(i32 nPriority)
{

   ::e_priority epriority;

   if (nPriority <= THREAD_PRIORITY_IDLE)
   {
      epriority = ::priority_idle;
   }
   else if (nPriority <= THREAD_PRIORITY_LOWEST)
   {
      epriority = ::priority_lowest;
   }
   else if (nPriority <= THREAD_PRIORITY_BELOW_NORMAL)
   {
      epriority = ::priority_below_normal;
   }
   else if (nPriority <= THREAD_PRIORITY_NORMAL)
   {
      epriority = ::priority_normal;
   }
   else if (nPriority <= THREAD_PRIORITY_ABOVE_NORMAL)
   {
      epriority = ::priority_above_normal;
   }
   else if (nPriority <= THREAD_PRIORITY_HIGHEST)
   {
      epriority = ::priority_highest;
   }
   else
   {
      epriority = ::priority_time_critical;
   }

   return epriority;

}


::e_priority get_os_class_scheduling_priority(i32 nPriority)
{

   ::e_priority epriority;

   if (nPriority <= IDLE_PRIORITY_CLASS)
   {
      epriority = ::priority_idle;
   }
   else if (nPriority <= BELOW_NORMAL_PRIORITY_CLASS)
   {
      epriority = ::priority_below_normal;
   }
   else if (nPriority <= NORMAL_PRIORITY_CLASS)
   {
      epriority = ::priority_normal;
   }
   else if (nPriority <= ABOVE_NORMAL_PRIORITY_CLASS)
   {
      epriority = ::priority_above_normal;
   }
   else if (nPriority <= HIGH_PRIORITY_CLASS)
   {
      epriority = ::priority_highest;
   }
   else
   {
      epriority = ::priority_time_critical;
   }

   return epriority;

}


namespace parallelization
{


   bool set_priority(::e_priority epriority)
   {

      return (::SetThreadPriority(::GetCurrentThread(), get_os_thread_priority(epriority)) != 0);

   }


   i32 priority()
   {

      return get_os_thread_scheduling_priority(::GetThreadPriority(::GetCurrentThread()));

   }


} // namespace aura


CLASS_DECL_AURA int get_processor_count()
{

   SYSTEM_INFO sysinfo;

   GetSystemInfo(&sysinfo);

   return sysinfo.dwNumberOfProcessors;

}


bool task_set_name(const ::string & pszThreadName)
{

   return task_set_name(::GetCurrentThread(), pszThreadName);

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

int_bool SetThreadName(::u32 dwThreadID, const ::string & threadName)
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


CLASS_DECL_AURA string task_get_name()
{

   return get_task_name(::GetCurrentThread());

}



