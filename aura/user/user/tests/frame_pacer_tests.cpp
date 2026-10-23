#include "../frame_pacer.h"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace std::chrono_literals;
using pacer = user::frame_pacer;

static void test_deadlines_and_early_wakeups()
{
   pacer clock;
   auto origin = pacer::time_point{};
   auto interval = std::chrono::duration_cast<pacer::duration>(16'666'667ns);
   auto deadline = clock.begin_frame(origin, interval);
   assert(deadline == origin + interval);

   // Rendering and message processing cannot consume the presentation tick.
   assert(clock.should_wait(origin + 5ms));
   assert(clock.should_wait(origin + 10ms));
   assert(clock.m_deadline == deadline);
   assert(!clock.should_wait(deadline));
   assert(clock.complete_frame(deadline) == 0);
   assert(clock.begin_frame(deadline + 2ms, interval) == origin + interval * 2);
}

static void test_overrun_and_rate_change()
{
   pacer clock;
   auto origin = pacer::time_point{};
   auto interval = std::chrono::duration_cast<pacer::duration>(10ms);
   clock.begin_frame(origin, interval);
   assert(!clock.should_wait(origin + 45ms));
   assert(clock.complete_frame(origin + 45ms) == 3);
   assert(clock.begin_frame(origin + 45ms, interval) == origin + 50ms);
   assert(clock.should_wait(origin + 49ms));

   auto slower = std::chrono::duration_cast<pacer::duration>(20ms);
   assert(clock.begin_frame(origin + 45ms, slower) == origin + 65ms);
   clock.reset();
   assert(clock.begin_frame(origin + 1s, interval) == origin + 1010ms);
}

static void test_fractional_rate_and_invalid_interval()
{
   pacer clock;
   auto origin = pacer::time_point{};
   auto interval = std::chrono::duration_cast<pacer::duration>(
      std::chrono::duration<double>(1.0 / 59.94));
   auto deadline = clock.begin_frame(origin, interval);
   for (int i = 0; i < 10'000; ++i)
   {
      clock.complete_frame(deadline + 100us);
      deadline = clock.begin_frame(deadline + 100us, interval);
   }
   assert(deadline == origin + interval * 10'001);

   clock.reset();
   assert(clock.begin_frame(origin, pacer::duration::zero()) > origin);
   assert(clock.m_interval > pacer::duration::zero());
}

static double simulated_fps(std::chrono::milliseconds render, std::chrono::milliseconds present)
{
   pacer clock;
   auto interval = std::chrono::duration_cast<pacer::duration>(
      std::chrono::duration<double>(1.0 / 60.0));
   auto now = pacer::time_point{};
   auto first = now;
   auto last = now;
   for (int i = 0; i < 1000; ++i)
   {
      auto deadline = clock.begin_frame(now, interval);
      now += render;
      if (clock.should_wait(now))
      {
         now = deadline;
      }
      if (i == 0)
      {
         first = now;
      }
      last = now;
      now += present;
      clock.complete_frame(now);
   }
   return 999.0 / std::chrono::duration<double>(last - first).count();
}

int main()
{
   test_deadlines_and_early_wakeups();
   test_overrun_and_rate_change();
   test_fractional_rate_and_invalid_interval();
   assert(std::abs(simulated_fps(5ms, 2ms) - 60.0) < 0.01);
   // A 25 ms workload has a 40 FPS ceiling. An overrun must not add another
   // pre-render wait and reduce it to a divisor of the 60 Hz target.
   assert(std::abs(simulated_fps(20ms, 5ms) - 40.0) < 0.01);
   std::cout << "PASS: deadlines, early wakes, overruns, rate changes, fractional FPS, render/present budget\n";
}
