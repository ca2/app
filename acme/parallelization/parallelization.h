// Created by camilo on 2026-07-10 08:19 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


namespace parallelization
{

   struct defer_lock_t
   {
   };
   struct adopt_lock_t
   {
   };

   class mutex_impl;

   class CLASS_DECL_ACME mutex
   {
   public:

            mutex_impl *m_pimpl;
      // SRWLOCK m_lock{};

      mutex() noexcept;

      mutex(const mutex &) = delete;
      mutex &operator=(const mutex &) = delete;

      ~mutex() noexcept;

      void lock() noexcept;

      bool try_lock() noexcept;
      void unlock() noexcept;

   };


   class unique_lock
   {
   public:


      ::parallelization::mutex *m_pmutex{};
      bool m_bOwnsLock{};


      explicit unique_lock(::parallelization::mutex &mutex) noexcept : m_pmutex(&mutex) { lock(); }

      unique_lock(::parallelization::mutex &mutex, defer_lock_t) noexcept : m_pmutex(&mutex) {}

      unique_lock(::parallelization::mutex &mutex, adopt_lock_t) noexcept : m_pmutex(&mutex), m_bOwnsLock(true) {}

      unique_lock(const unique_lock &) = delete;
      unique_lock &operator=(const unique_lock &) = delete;

      unique_lock(unique_lock &&other) noexcept : m_pmutex(other.m_pmutex), m_bOwnsLock(other.m_bOwnsLock)
      {
         other.m_pmutex = nullptr;
         other.m_bOwnsLock = false;
      }

      unique_lock &operator=(unique_lock &&other) noexcept
      {
         if (this != &other)
         {
            if (m_bOwnsLock)
            {
               unlock();
            }

            m_pmutex = other.m_pmutex;
            m_bOwnsLock = other.m_bOwnsLock;

            other.m_pmutex = nullptr;
            other.m_bOwnsLock = false;
         }

         return *this;
      }

      ~unique_lock()
      {
         if (m_bOwnsLock)
         {
            unlock();
         }
      }

      void lock()
      {
         if (m_pmutex == nullptr)
         {
            throw ::exception(error_operation_not_permitted);
         }

         if (m_bOwnsLock)
         {
            throw ::exception(error_resource_deadlock_would_occur);
         }

         m_pmutex->lock();
         m_bOwnsLock = true;
      }

      bool try_lock()
      {
         if (m_pmutex == nullptr)
         {
            throw ::exception(error_operation_not_permitted);
         }

         if (m_bOwnsLock)
         {
            throw ::exception(error_resource_deadlock_would_occur);
         }

         m_bOwnsLock = m_pmutex->try_lock();

         return m_bOwnsLock;
      }

      void unlock()
      {
         if (m_pmutex == nullptr || !m_bOwnsLock)
         {
            throw ::exception(error_operation_not_permitted);
         }

         m_pmutex->unlock();
         m_bOwnsLock = false;
      }

      [[nodiscard]]
      bool owns_lock() const noexcept
      {
         return m_bOwnsLock;
      }

      explicit operator bool() const noexcept { return owns_lock(); }

      [[nodiscard]]
      ::parallelization::mutex *mutex() const noexcept
      {
         return m_pmutex;
      }
   };


   //enum class enum_condition_variable
   //{
   //   e_condition_variable_nno_timeout,
   //   e_condition_variable_timeout
   //};
   class condition_payload_impl;

   class CLASS_DECL_ACME condition_payload
   {
   public:
      condition_payload_impl *m_pimpl;

      condition_payload() noexcept;

      condition_payload(const condition_payload &) = delete;
      condition_payload &operator=(const condition_payload &) = delete;

      // CONDITION_VARIABLE does not require destruction.
      ~condition_payload();

      void notify_one() noexcept;

      void notify_all() noexcept;

      void wait(unique_lock &lock);

      template<typename PREDICATE>
      void wait(unique_lock &lock, PREDICATE predicate)
      {
         while (!predicate())
         {
            wait(lock);
         }
      }

      ::e_status wait_for(unique_lock &lock, const class ::time &duration);
      //{
      //   validate_lock(lock);

      //   DWORD dwTimeout = duration_to_timeout(duration);

      //   BOOL bResult = SleepConditionVariableSRW(&m_conditionvariable, &lock.m_pmutex->m_lock, dwTimeout, 0);

      //   if (bResult)
      //   {
      //      return win32_cv_status::no_timeout;
      //   }

      //   DWORD dwError = GetLastError();

      //   if (dwError == ERROR_TIMEOUT)
      //   {
      //      return win32_cv_status::timeout;
      //   }

      //   throw_win32_error(dwError);
      //}

      //template<typename REPRESENTATION, typename PERIOD>
      //::e_status wait_for(unique_lock &lock, const std::chrono::duration<REPRESENTATION, PERIOD> &duration)
      //{
      //   using namespace std::chrono;

      //   if (duration <= duration.zero())
      //   {
      //      return win32_cv_status::timeout;
      //   }

      //   // Round upward so a positive sub-millisecond timeout does not
      //   // accidentally become a zero-millisecond poll.
      //   auto millisecondsDuration = ceil<milliseconds>(duration);

      //   return wait_for(lock, millisecondsDuration);
      //}

      template< typename PREDICATE>
      bool wait_for(unique_lock &lock, const class ::time & duration,
                    PREDICATE predicate)
      {
         //using clock = std::chrono::steady_clock;

         if (predicate())
         {
            return true;
         }

         if (duration <= 0_ms)
         {
            return predicate();
         }

         auto deadline = ::time::now() + duration;

         return wait_until(lock, deadline, ::transfer(predicate));
      }

      //template<typename DURATION>
      ::e_status wait_until(unique_lock &lock, const class ::time &deadline);
      //{
      //   auto now = CLOCK::now();

      //   if (deadline <= now)
      //   {
      //      return win32_cv_status::timeout;
      //   }

      //   return wait_for(lock, deadline - now);
      //}

      template< typename PREDICATE>
      bool wait_until(unique_lock &lock, const class ::time &deadline,
                      PREDICATE predicate)
      {
         while (!predicate())
         {
            auto now = ::time::now();

            if (deadline <= now)
            {
               return predicate();
            }

            auto status = wait_for(lock, deadline - now);

            if (status == error_timeout)
            {
               return predicate();
            }
         }

         return true;
      }

   /*private:


      CONDITION_VARIABLE m_conditionvariable{};*/
   };


} // namespace parallelization




