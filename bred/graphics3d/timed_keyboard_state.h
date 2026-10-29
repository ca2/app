#pragma once
#include <array>
#include <chrono>
#include <mutex>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace graphics3d
{
   // Retain event durations between rendered frames, including complete taps.
   template <size_t KeyCount>
   class timed_keyboard_state
   {
   public:
      using clock = std::chrono::steady_clock;
      using time_point = clock::time_point;
      using keys = std::array<bool, KeyCount>;
      struct interval { double seconds; keys pressed; };

      // With zero movement keys this records ordinary held durations. In step
      // mode only movement keys get an initial impulse and delayed repeat;
      // remaining keys are modifiers applied to each movement interval.
      void configure(double tapSeconds, double holdDelaySeconds, size_t movementKeys)
      {
         if (!std::isfinite(tapSeconds) || !std::isfinite(holdDelaySeconds)
            || tapSeconds < 0. || tapSeconds > 10. || holdDelaySeconds < 0.
            || holdDelaySeconds > 60. || movementKeys > KeyCount)
            throw std::invalid_argument("Invalid keyboard movement timing");
         std::lock_guard<std::mutex> lock(m_mutex);
         m_tapSeconds = tapSeconds;
         m_holdDelay = std::chrono::duration_cast<clock::duration>(std::chrono::duration<double>(holdDelaySeconds));
         m_movementKeys = movementKeys;
         clear();
      }

      void set(size_t key, bool down, time_point now = clock::now())
      {
         if (key >= KeyCount) return;
         std::lock_guard<std::mutex> lock(m_mutex);
         if (m_keys[key] == down) return; // Repeats do not restart a hold.
         append(now);
         m_keys[key] = down;
         if (down)
         {
            m_pressTime[key] = now;
            if (key < m_movementKeys && m_tapSeconds > 0.)
            {
               keys tap{};
               tap[key] = true;
               for (size_t i = m_movementKeys; i < KeyCount; ++i) tap[i] = m_keys[i];
               push(m_tapSeconds, tap);
            }
         }
         m_started = true;
      }

      std::vector<interval> take(time_point now = clock::now())
      {
         std::lock_guard<std::mutex> lock(m_mutex);
         append(now);
         std::vector<interval> result;
         result.swap(m_intervals);
         return result;
      }

      void reset()
      {
         std::lock_guard<std::mutex> lock(m_mutex);
         clear();
      }

   private:
      void clear()
      {
         m_keys = {};
         m_intervals.clear();
         m_started = false;
      }
      void push(double seconds, const keys & pressed)
      {
         if (!m_intervals.empty() && m_intervals.back().pressed == pressed)
            m_intervals.back().seconds += seconds;
         else
            m_intervals.push_back({seconds, pressed});
      }
      void append(time_point now)
      {
         if (m_started && now > m_last)
         {
            auto cursor = m_last;
            while (cursor < now)
            {
               auto end = now;
               auto pressed = m_keys;
               for (size_t i = 0; i < m_movementKeys; ++i)
               {
                  const auto continuousStart = m_pressTime[i] + m_holdDelay;
                  if (pressed[i] && cursor < continuousStart)
                  {
                     pressed[i] = false;
                     end = std::min(end, continuousStart);
                  }
               }
               bool active = false;
               const auto count = m_movementKeys ? m_movementKeys : KeyCount;
               for (size_t i = 0; i < count; ++i) active |= pressed[i];
               if (active) push(std::chrono::duration<double>(end - cursor).count(), pressed);
               cursor = end;
            }
         }
         m_last = now;
      }
      std::mutex m_mutex;
      keys m_keys{};
      time_point m_last{};
      std::array<time_point, KeyCount> m_pressTime{};
      clock::duration m_holdDelay{};
      double m_tapSeconds = 0.;
      size_t m_movementKeys = 0;
      bool m_started = false;
      std::vector<interval> m_intervals;
   };
}
