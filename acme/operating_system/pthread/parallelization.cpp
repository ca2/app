// Created by camilo on 2026-07-12 06:07 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "acme/parallelization/parallelization.h"
#include "acme/_operating_system.h"

#include <pthread.h>
#include <time.h>

#include <cerrno>
#include <exception>
#include <limits>
#include <string>
#include <system_error>


namespace parallelization
{


   [[noreturn]]
   static void parallelization_terminate() noexcept
   {

      std::terminate();

   }


   [[noreturn]]
   static void throw_posix_error(
      int iError,
      const char * pszOperation)
   {

      std::string strMessage;

      if (pszOperation != nullptr)
      {

         strMessage = pszOperation;

      }
      else
      {

         strMessage = "POSIX parallelization operation";

      }

      strMessage += " failed: ";
      strMessage += std::generic_category().message(iError);

      throw ::exception(
         error_failed,
         strMessage.c_str());

   }


   class mutex_impl
   {

   public:


      pthread_mutex_t m_lock{};


   };


   mutex::mutex() noexcept
   {

      m_pimpl = new mutex_impl;

      int iError = pthread_mutex_init(
         &m_pimpl->m_lock,
         nullptr);

      if (iError != 0)
      {

         delete m_pimpl;

         m_pimpl = nullptr;

         parallelization_terminate();

      }

   }


   mutex::~mutex() noexcept
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      int iError = pthread_mutex_destroy(
         &m_pimpl->m_lock);

      if (iError != 0)
      {

         // Usually means that the mutex is still locked or is otherwise
         // being used while its owner is being destroyed.
         parallelization_terminate();

      }

      delete m_pimpl;

      m_pimpl = nullptr;

   }


   void mutex::lock() noexcept
   {

      int iError = pthread_mutex_lock(
         &m_pimpl->m_lock);

      if (iError != 0)
      {

         parallelization_terminate();

      }

   }


   bool mutex::try_lock() noexcept
   {

      int iError = pthread_mutex_trylock(
         &m_pimpl->m_lock);

      if (iError == 0)
      {

         return true;

      }

      if (iError == EBUSY)
      {

         return false;

      }

      parallelization_terminate();

   }


   void mutex::unlock() noexcept
   {

      int iError = pthread_mutex_unlock(
         &m_pimpl->m_lock);

      if (iError != 0)
      {

         parallelization_terminate();

      }

   }


   class condition_payload_impl
   {

   public:


      pthread_cond_t m_condition{};


   };


   static void condition_payload_validate_lock(
      const unique_lock & lock)
   {

      if (lock.m_pmutex == nullptr || !lock.m_bOwnsLock)
      {

         throw ::exception(
            error_operation_not_permitted,
            "condition-variable wait requires an owned lock");

      }

   }


   [[noreturn]]
   static void condition_payload_throw_posix_error(
      int iError,
      const char * pszOperation)
   {

      throw_posix_error(
         iError,
         pszOperation);

   }


   static timespec condition_payload_wait_time(
      const class ::time & duration)
   {

      timespec deadline{};

#if !defined(__APPLE__)

      if (clock_gettime(
         CLOCK_MONOTONIC,
         &deadline) != 0)
      {

         condition_payload_throw_posix_error(
            errno,
            "clock_gettime(CLOCK_MONOTONIC)");

      }

#endif

      auto uMilliseconds =
         static_cast<unsigned long long>(
            duration.integral_millisecond());

      auto uSeconds = uMilliseconds / 1'000ULL;

      auto uRemainingMilliseconds =
         uMilliseconds % 1'000ULL;

      constexpr long long nanosecondsPerSecond =
         1'000'000'000LL;

      constexpr long long nanosecondsPerMillisecond =
         1'000'000LL;

      auto maximumTime =
         (std::numeric_limits<time_t>::max)();

      if (deadline.tv_sec >= maximumTime)
      {

         deadline.tv_sec = maximumTime;
         deadline.tv_nsec = nanosecondsPerSecond - 1;

         return deadline;

      }

      auto uAvailableSeconds =
         static_cast<unsigned long long>(
            maximumTime - deadline.tv_sec);

      if (uSeconds > uAvailableSeconds)
      {

         deadline.tv_sec = maximumTime;
         deadline.tv_nsec = nanosecondsPerSecond - 1;

         return deadline;

      }

      deadline.tv_sec +=
         static_cast<time_t>(uSeconds);

      auto nanoseconds =
         static_cast<long long>(deadline.tv_nsec)
         + static_cast<long long>(uRemainingMilliseconds)
         * nanosecondsPerMillisecond;

      if (nanoseconds >= nanosecondsPerSecond)
      {

         if (deadline.tv_sec == maximumTime)
         {

            deadline.tv_nsec = nanosecondsPerSecond - 1;

            return deadline;

         }

         ++deadline.tv_sec;

         nanoseconds -= nanosecondsPerSecond;

      }

      deadline.tv_nsec =
         static_cast<long>(nanoseconds);

      return deadline;

   }


   condition_payload::condition_payload() noexcept
   {

      m_pimpl = new condition_payload_impl;

      pthread_condattr_t attributes{};

      int iError =
         pthread_condattr_init(&attributes);

      if (iError != 0)
      {

         delete m_pimpl;

         m_pimpl = nullptr;

         parallelization_terminate();

      }

#if !defined(__APPLE__)

      // pthread_cond_timedwait() normally uses CLOCK_REALTIME. Using
      // CLOCK_MONOTONIC prevents wall-clock corrections from shortening or
      // extending a relative wait. Apple uses the relative wait API below.
      iError = pthread_condattr_setclock(
         &attributes,
         CLOCK_MONOTONIC);

      if (iError != 0)
      {

         pthread_condattr_destroy(&attributes);

         delete m_pimpl;

         m_pimpl = nullptr;

         parallelization_terminate();

      }

#endif

      iError = pthread_cond_init(
         &m_pimpl->m_condition,
         &attributes);

      int iDestroyAttributesError =
         pthread_condattr_destroy(&attributes);

      if (iError != 0)
      {

         delete m_pimpl;

         m_pimpl = nullptr;

         parallelization_terminate();

      }

      if (iDestroyAttributesError != 0)
      {

         pthread_cond_destroy(
            &m_pimpl->m_condition);

         delete m_pimpl;

         m_pimpl = nullptr;

         parallelization_terminate();

      }

   }


   condition_payload::~condition_payload()
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      int iError = pthread_cond_destroy(
         &m_pimpl->m_condition);

      if (iError != 0)
      {

         // Destruction while another thread is waiting is a programming
         // error. This destructor cannot safely report that by throwing.
         parallelization_terminate();

      }

      delete m_pimpl;

      m_pimpl = nullptr;

   }


   void condition_payload::notify_one() noexcept
   {

      int iError = pthread_cond_signal(
         &m_pimpl->m_condition);

      if (iError != 0)
      {

         parallelization_terminate();

      }

   }


   void condition_payload::notify_all() noexcept
   {

      int iError = pthread_cond_broadcast(
         &m_pimpl->m_condition);

      if (iError != 0)
      {

         parallelization_terminate();

      }

   }


   void condition_payload::wait(
      unique_lock & lock)
   {

      condition_payload_validate_lock(lock);

      int iError = pthread_cond_wait(
         &m_pimpl->m_condition,
         &lock.m_pmutex->m_pimpl->m_lock);

      if (iError != 0)
      {

         condition_payload_throw_posix_error(
            iError,
            "pthread_cond_wait");

      }

   }


   ::e_status condition_payload::wait_for(
      unique_lock & lock,
      const class ::time & duration)
   {

      condition_payload_validate_lock(lock);

      if (duration <= 0_ms)
      {

         return error_timeout;

      }

      auto waitTime =
         condition_payload_wait_time(duration);

#if defined(__APPLE__)

      int iError = pthread_cond_timedwait_relative_np(

#else

      int iError = pthread_cond_timedwait(

#endif

         &m_pimpl->m_condition,
         &lock.m_pmutex->m_pimpl->m_lock,
         &waitTime);

      if (iError == 0)
      {

         return ::success;

      }

      if (iError == ETIMEDOUT)
      {

         return error_timeout;

      }

      condition_payload_throw_posix_error(
         iError,
         "pthread_cond_timedwait");

   }


   ::e_status condition_payload::wait_until(
      unique_lock & lock,
      const class ::time & deadline)
   {

      auto now = ::time::now();

      if (deadline <= now)
      {

         return error_timeout;

      }

      return wait_for(
         lock,
         deadline - now);

   }


} // namespace parallelization



// One important behavioral detail remains the same as on Windows:
// condition-variable waits can wake spuriously.
// //Code waiting for a state should continue using a predicate loop:

//unique_lock lock(mutex);


//while (!bCondition)
//{


  // condition.wait(lock);

//}
