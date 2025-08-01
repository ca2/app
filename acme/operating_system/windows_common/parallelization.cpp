#include "framework.h"
//#include "parallelization.h"
//#include "api.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"

#include "acme/_operating_system.h"

int_bool SetThreadName(unsigned int dwThreadID, const_char_pointer threadName);
typedef HRESULT WINAPI FN_GetThreadDescription(HANDLE htask, PWSTR* ppszThreadDescription);


string get_task_name(htask htask)
{

   HRESULT hr;

   LPWSTR lpwsz = nullptr;

#ifdef UNIVERSAL_WINDOWS

   hr = GetThreadDescription(htask, &lpwsz);

#else

   hr = E_FAIL;

   static auto pfn_get_thread_description = ::windows::function < FN_GetThreadDescription* >::get_address("Kernel32.dll", "GetThreadDescription");

   if (pfn_get_thread_description)
   {

      hr = pfn_get_thread_description((HANDLE) htask.m_h, &lpwsz);

   }

#endif

   if (SUCCEEDED(hr))
   {

      string str;

      str = lpwsz;

      ::LocalFree(lpwsz);

      return str;

   }

   return "";

   //::task* ptask = ::get_task(htask);

   //if (::is_null(ptask))
   //{

   //   return "";

   //}

   //return ptask->m_strTaskName;

}


typedef HRESULT WINAPI FN_SetThreadDescription(_In_ htask htask, _In_ PCWSTR pThreadDescription);


CLASS_DECL_ACME void task_set_name(htask htask, const ::scoped_string & scopedstr)
{

   bool bOk1 = false;

#ifdef UNIVERSAL_WINDOWS

   bOk1 = SUCCEEDED(SetThreadDescription(htask, wstring(scopedstr)));

#else

   static auto pfn_set_thread_description = ::windows::function < FN_SetThreadDescription* >::get_address("kernel32.dll", "SetThreadDescription");

   if (pfn_set_thread_description)
   {

      bOk1 = SUCCEEDED(pfn_set_thread_description(htask, wstring(scopedstr)));

   }

   if (!bOk1 && ::is_debugger_attached())
   {

      bOk1 = SetThreadName(GetThreadId((HANDLE) htask.m_h), ::string(scopedstr)) != false;

   }

#endif

#ifdef _DEBUG

   if (!bOk1 && ::is_debugger_attached())
   {

      throw ::exception(error_failed);

   }

#endif

}



typedef HRESULT WINAPI FN_SetThreadDescription(_In_ htask htask, _In_ PCWSTR pThreadDescription);


int get_os_thread_priority(::enum_priority epriority)
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



int get_os_priority_class(::enum_priority epriority)
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


::enum_priority get_os_thread_scheduling_priority(int nPriority)
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


::enum_priority get_os_class_scheduling_priority(int nPriority)
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

      return set_priority(current_htask(), epriority);

   }


   bool set_priority(htask htask, ::enum_priority epriority)
   {

      return (::SetThreadPriority((HANDLE)htask.m_h, get_os_thread_priority(epriority)) != 0);

   }


   ::enum_priority get_priority()
   {

      return get_priority(current_htask());

   }


   ::enum_priority get_priority(htask htask)
   {

      return get_os_thread_scheduling_priority(::GetThreadPriority((HANDLE) htask.m_h));

   }


} // namespace acme


void task_set_name(const ::scoped_string & scopedstrThreadName)
{

   if (::string(scopedstrThreadName) == "task")
   {
      output_debug_string("task");

   }

   /*return*/ task_set_name((htask)(::uptr) ::GetCurrentThread(), scopedstrThreadName);

}


const unsigned int MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)

typedef struct tagTHREADNAME_INFO
{
   unsigned int dwType; // Must be 0x1000.
   const_char_pointer szName; // Pointer to name (in user addr space).
   unsigned int dwThreadID; // Thread ID (-1=caller thread).
   unsigned int dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)



int_bool SetThreadName(unsigned int dwThreadID, const_char_pointer threadName)
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

   return get_task_name((htask)(::uptr)::GetCurrentThread());

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






CLASS_DECL_ACME bool _hsynchronization_wait(::hsynchronization h, const class ::time& timeWait)
{

   auto handle = (HANDLE) h;

   if (!handle)
   {

      throw ::exception(error_wrong_state);

   }

#ifdef MUTEX_DEBUG

   //m_strThread = ::get_task_name(::get_task());

   //m_itask = ::current_itask();

#endif

   DWORD dwWait = ::windows::wait(timeWait);

   DWORD dwResult = ::WaitForSingleObjectEx(handle, dwWait, false);

   auto estatus = ::windows::wait_result_status(dwResult, 1);

   if (estatus == error_wait_timeout)
   {

      return false;

   }
   else if (estatus == signaled_base)
   {

      return true;

   }
   else
   {

      auto dwLastError = ::GetLastError();

      auto estatus = ::windows::last_error_status(dwLastError);

      auto errorcode = ::windows::last_error_error_code(dwLastError);

      throw ::exception(estatus, { errorcode }, "WaitForSingleObjectEx WAIT_FAILED");

      return false;

   }


}


CLASS_DECL_ACME int get_processor_count()
{

   SYSTEM_INFO sysinfo;

   GetSystemInfo(&sysinfo);

   return sysinfo.dwNumberOfProcessors;

}






CLASS_DECL_ACME class ::time default_run_timeout()
{

   class ::time timeDefaultTimeout;

#ifdef _DEBUG

   timeDefaultTimeout = 5_min;

#else

   timeDefaultTimeout = 15_s;

#endif

   return timeDefaultTimeout;

}



bool htask::operator==(const htask & htask) const
{

   DWORD dw1 = ::GetThreadId((HANDLE) m_h);

   DWORD dw2 = ::GetThreadId((HANDLE) htask.m_h);

   return dw1 == dw2;

}



bool itask::operator==(const itask & itask) const
{

   return m_i == itask.m_i;

}


bool htask::is_null() const
{

   return !m_h;

}


bool itask::is_null() const
{

   return !m_i;

}


