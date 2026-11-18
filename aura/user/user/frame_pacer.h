#pragma once

#include <chrono>


namespace user
{

   // Presentation deadlines stay on one monotonic clock grid. Rendering may
   // start immediately; a late frame does not accumulate a queue of old ticks.
   class frame_pacer
   {
   public:

      using clock = std::chrono::steady_clock;
      using time_point = clock::time_point;
      using duration = clock::duration;

      bool m_bInitialized = false;
      duration m_interval{};
      time_point m_deadline{};

      void reset() noexcept
      {
         m_bInitialized = false;
      }

      time_point begin_frame(time_point now, duration interval) noexcept
      {
         if (interval <= duration::zero())
         {
            interval = std::chrono::duration_cast<duration>(std::chrono::duration<double>(1.0 / 60.0));
         }

         if (!m_bInitialized || interval != m_interval)
         {
            m_interval = interval;
            m_deadline = now + interval;
            m_bInitialized = true;
         }

         return m_deadline;
      }

      bool should_wait(time_point now) const noexcept
      {
         return m_bInitialized && now < m_deadline;
      }

      unsigned long long complete_frame(time_point now) noexcept
      {
         if (!m_bInitialized)
         {
            return 0;
         }

         auto skipped = now > m_deadline ? (now - m_deadline) / m_interval : 0;
         m_deadline += m_interval * (skipped + 1);
         return static_cast<unsigned long long>(skipped);
      }

   };

}
