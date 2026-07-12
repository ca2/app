// Created by camilo on 2026-07-10 08:18 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "acme/parallelization/parallelization.h"
#include "acme/_operating_system.h"


namespace parallelization
{


   class mutex_impl
   {
   public:

      SRWLOCK m_lock{};
   };


   mutex::mutex() noexcept
   {

      m_pimpl = new mutex_impl;
      InitializeSRWLock(&m_pimpl->m_lock);
   }

   mutex::~mutex() noexcept { delete m_pimpl; }


   void mutex::lock() noexcept { AcquireSRWLockExclusive(&m_pimpl->m_lock); }

   bool mutex::try_lock() noexcept { return TryAcquireSRWLockExclusive(&m_pimpl->m_lock) != FALSE; }

   void mutex::unlock() noexcept { ReleaseSRWLockExclusive(&m_pimpl->m_lock); }


   //enum class win32_cv_status
   //{
   //   no_timeout,
   //   timeout
   //};


   class condition_payload_impl
   {

   public:


      CONDITION_VARIABLE m_conditionvariable{};
   };



   
   static void condition_payload_validate_lock(const unique_lock &lock)
   {
      if (lock.m_pmutex == nullptr || !lock.m_bOwnsLock)
      {
         throw ::exception(error_operation_not_permitted,
                                 "condition-variable wait requires an owned lock");
      }
   }

   static DWORD condition_payload_duration_to_timeout(const class ::time & duration) noexcept
   {
      if (duration <= 0_ms)
      {
         return 0;
      }

      // INFINITE is reserved by Win32, so the largest finite timeout is
      // INFINITE - 1.
      constexpr auto maximumFiniteTimeout = static_cast<unsigned long long>(INFINITE) - 1ULL;

      auto count = static_cast<unsigned long long>(duration.integral_millisecond());

      if (count > maximumFiniteTimeout)
      {
         return INFINITE - 1;
      }

      return static_cast<DWORD>(count);
   }
   [[noreturn]]
   static void condition_payload_throw_win32_error(DWORD dwError)
   {
      throw ::exception(error_failed, {::windows::last_error(dwError)}, "Win32 condition-variable operation failed");
   }

   [[noreturn]]
   static void condition_payload_throw_last_error()
   {
      condition_payload_throw_win32_error(GetLastError());
   }

   condition_payload::condition_payload() noexcept
   {
      m_pimpl = new condition_payload_impl();
      InitializeConditionVariable(&m_pimpl->m_conditionvariable);
   }

   // condition_payload(const condition_payload &) = delete;
   // condition_payload &operator=(const condition_payload &) = delete;

   // CONDITION_VARIABLE does not require destruction.
   condition_payload::~condition_payload() { delete m_pimpl; }

   void condition_payload::notify_one() noexcept { WakeConditionVariable(&m_pimpl->m_conditionvariable); }

   void condition_payload::notify_all() noexcept { WakeAllConditionVariable(&m_pimpl->m_conditionvariable); }

   void condition_payload::wait(unique_lock &lock)
   {
      condition_payload_validate_lock(lock);

      BOOL bResult = SleepConditionVariableSRW(&m_pimpl->m_conditionvariable, &lock.m_pmutex->m_pimpl->m_lock, INFINITE, 0);

      if (!bResult)
      {
         condition_payload_throw_last_error();
      }
   }

   //template<typename PREDICATE>
   //void condition_payload::wait(unique_lock &lock, PREDICATE predicate)
   //{
   //   while (!predicate())
   //   {
   //      wait(lock);
   //   }
   //}

   ::e_status condition_payload::wait_for(unique_lock &lock, const class ::time &duration)
   {
      condition_payload_validate_lock(lock);

      DWORD dwTimeout = condition_payload_duration_to_timeout(duration);

      BOOL bResult = SleepConditionVariableSRW(&m_pimpl->m_conditionvariable, &lock.m_pmutex->m_pimpl->m_lock, dwTimeout, 0);

      if (bResult)
      {
         return ::success;
      }

      DWORD dwError = GetLastError();

      if (dwError == ERROR_TIMEOUT)
      {
         return error_timeout;
      }

      condition_payload_throw_win32_error(dwError);
   }

   ////template<typename REPRESENTATION, typename PERIOD>
   // win32_cv_status wait_for(unique_lock &lock, const std::chrono::duration<REPRESENTATION, PERIOD> &duration)
   //{
   //    using namespace std::chrono;

   //   if (duration <= duration.zero())
   //   {
   //      return win32_cv_status::timeout;
   //   }

   //   // Round upward so a positive sub-millisecond timeout does not
   //   // accidentally become a zero-millisecond poll.
   //   auto millisecondsDuration = ceil<milliseconds>(duration);

   //   return wait_for(lock, millisecondsDuration);
   //}

   // template<typename REPRESENTATION, typename PERIOD, typename PREDICATE>
   // bool wait_for(unique_lock &lock, const std::chrono::duration<REPRESENTATION, PERIOD> &duration,
   //               PREDICATE predicate)
   //{
   //    using clock = std::chrono::steady_clock;

   //   if (predicate())
   //   {
   //      return true;
   //   }

   //   if (duration <= duration.zero())
   //   {
   //      return predicate();
   //   }

   //   auto deadline = clock::now() + duration;

   //   return wait_until(lock, deadline, std::move(predicate));
   //}

   // template<typename CLOCK, typename DURATION>
   ::e_status condition_payload::wait_until(unique_lock &lock, const class ::time &deadline)
   {
      auto now = ::time::now();

      if (deadline <= now)
      {
         return error_timeout;
      }

      return wait_for(lock, deadline - now);
   }

   // template<typename CLOCK, typename DURATION, typename PREDICATE>
   // bool wait_until(unique_lock &lock, const std::chrono::time_point<CLOCK, DURATION> &deadline,
   //                 PREDICATE predicate)
   //{
   //    while (!predicate())
   //    {
   //       auto now = CLOCK::now();

   //      if (deadline <= now)
   //      {
   //         return predicate();
   //      }

   //      auto status = wait_for(lock, deadline - now);

   //      if (status == win32_cv_status::timeout)
   //      {
   //         return predicate();
   //      }
   //   }

   //   return true;
   //}


   //


} // namespace parallelization




