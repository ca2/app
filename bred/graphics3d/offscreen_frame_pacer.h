#pragma once


#include <chrono>
#include <cmath>


namespace graphics3d
{


   class offscreen_frame_pacer
   {
   public:


      using clock = std::chrono::steady_clock;
      using duration = clock::duration;
      using time_point = clock::time_point;

      static constexpr float s_fDefaultFps = 60.0f;

      bool m_bInitialized = false;
      bool m_bPreviousFrameOverran = false;
      float m_fAppliedFps = s_fDefaultFps;
      time_point m_timeNextFrame{};


      static float validated_fps(float fDesiredFps) noexcept
      {

         if (!std::isfinite(fDesiredFps) || fDesiredFps <= 0.0f)
         {

            return s_fDefaultFps;

         }

         return fDesiredFps;

      }


      static duration frame_interval(float fDesiredFps) noexcept
      {

         auto fValidatedFps = validated_fps(fDesiredFps);
         using floating_duration = std::chrono::duration<long double, duration::period>;
         auto timeFloatingInterval = std::chrono::duration_cast<floating_duration>(
            std::chrono::duration<long double>(1.0L / static_cast<long double>(fValidatedFps)));
         auto timeMinimumInterval = floating_duration(duration{1});
         auto timeMaximumInterval = floating_duration(duration::max());

         if (timeFloatingInterval <= timeMinimumInterval)
         {

            return duration{1};

         }

         if (timeFloatingInterval >= timeMaximumInterval)
         {

            return duration::max();

         }

         return std::chrono::duration_cast<duration>(timeFloatingInterval);

      }


      static time_point saturating_add(time_point timeBase, duration timeInterval) noexcept
      {

         if (timeBase > time_point::max() - timeInterval)
         {

            return time_point::max();

         }

         return timeBase + timeInterval;

      }


      static duration wait_slice(duration timeRemaining) noexcept
      {

         auto timeMaximumSlice = std::chrono::duration_cast<duration>(std::chrono::milliseconds(10));

         if (timeRemaining <= duration::zero())
         {

            return duration::zero();

         }

         return timeRemaining < timeMaximumSlice ? timeRemaining : timeMaximumSlice;

      }


      time_point begin_frame(time_point timeNow, float fDesiredFps) noexcept
      {

         auto fValidatedFps = validated_fps(fDesiredFps);
         auto bFpsChanged = !m_bInitialized || fValidatedFps != m_fAppliedFps;
         auto timeFrameInterval = frame_interval(fValidatedFps);

         if (bFpsChanged || m_bPreviousFrameOverran)
         {

            m_timeNextFrame = saturating_add(timeNow, timeFrameInterval);

         }
         else
         {

            auto timeAccumulatedDeadline = saturating_add(m_timeNextFrame, timeFrameInterval);

            if (timeAccumulatedDeadline <= timeNow)
            {

               m_timeNextFrame = saturating_add(timeNow, timeFrameInterval);

            }
            else
            {

               m_timeNextFrame = timeAccumulatedDeadline;

            }

         }

         m_bInitialized = true;
         m_bPreviousFrameOverran = false;
         m_fAppliedFps = fValidatedFps;

         return m_timeNextFrame;

      }


      bool should_wait(time_point timeNow) noexcept
      {

         m_bPreviousFrameOverran = timeNow >= m_timeNextFrame;

         return !m_bPreviousFrameOverran;

      }


      time_point deadline() const noexcept
      {

         return m_timeNextFrame;

      }


   };


} // namespace graphics3d
