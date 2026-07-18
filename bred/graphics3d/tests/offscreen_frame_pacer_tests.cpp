#include "../offscreen_frame_pacer.h"

#include <cassert>
#include <chrono>
#include <cmath>
#include <limits>


namespace
{


   using pacer = ::graphics3d::offscreen_frame_pacer;
   using clock = pacer::clock;


   bool approximately_equal(clock::duration left, clock::duration right)
   {

      auto difference = left > right ? left - right : right - left;

      return difference <= std::chrono::microseconds(1);

   }


   void test_default_sixty_fps_interval()
   {

      pacer framepacer;
      auto now = clock::time_point{};
      auto deadline = framepacer.begin_frame(now, 60.0f);

      assert(approximately_equal(deadline - now, std::chrono::duration_cast<clock::duration>(
         std::chrono::duration<double>(1.0 / 60.0))));
      assert(framepacer.should_wait(now + std::chrono::milliseconds(1)));

   }


   void test_runtime_fps_change_resets_deadline()
   {

      pacer framepacer;
      auto start = clock::time_point{};

      framepacer.begin_frame(start, 60.0f);
      assert(framepacer.should_wait(start + std::chrono::milliseconds(5)));

      auto changed = start + std::chrono::milliseconds(10);
      auto deadline = framepacer.begin_frame(changed, 30.0f);

      assert(approximately_equal(deadline - changed, std::chrono::duration_cast<clock::duration>(
         std::chrono::duration<double>(1.0 / 30.0))));

   }


   void test_same_fps_accumulates_deadlines()
   {

      pacer framepacer;
      auto start = clock::time_point{};
      auto firstDeadline = framepacer.begin_frame(start, 60.0f);

      assert(framepacer.should_wait(start + std::chrono::milliseconds(1)));

      auto secondDeadline = framepacer.begin_frame(firstDeadline, 60.0f);

      assert(approximately_equal(secondDeadline - firstDeadline, firstDeadline - start));

   }


   void test_overrun_resets_instead_of_catching_up()
   {

      pacer framepacer;
      auto start = clock::time_point{};

      framepacer.begin_frame(start, 60.0f);
      auto overrun = start + std::chrono::milliseconds(20);
      assert(!framepacer.should_wait(overrun));

      auto deadline = framepacer.begin_frame(overrun, 60.0f);

      assert(approximately_equal(deadline - overrun, std::chrono::duration_cast<clock::duration>(
         std::chrono::duration<double>(1.0 / 60.0))));

   }


   void test_late_wake_resets_instead_of_catching_up()
   {

      pacer framepacer;
      auto start = clock::time_point{};

      auto firstDeadline = framepacer.begin_frame(start, 60.0f);
      assert(framepacer.should_wait(start + std::chrono::milliseconds(1)));

      auto lateWake = start + std::chrono::milliseconds(40);
      auto deadline = framepacer.begin_frame(lateWake, 60.0f);

      assert(deadline > lateWake);
      assert(approximately_equal(deadline - lateWake, firstDeadline - start));

   }


   void test_invalid_fps_uses_sixty_fps()
   {

      assert(pacer::validated_fps(0.0f) == 60.0f);
      assert(pacer::validated_fps(-1.0f) == 60.0f);
      assert(pacer::validated_fps(std::numeric_limits<float>::infinity()) == 60.0f);
      assert(pacer::validated_fps(std::numeric_limits<float>::quiet_NaN()) == 60.0f);

   }


   void test_extreme_positive_fps_uses_representable_intervals()
   {

      assert(pacer::frame_interval(std::numeric_limits<float>::max()) == clock::duration{1});
      assert(pacer::frame_interval(std::numeric_limits<float>::denorm_min()) == clock::duration::max());

   }


   void test_expired_deadline_does_not_wait()
   {

      pacer framepacer;
      auto start = clock::time_point{};
      auto deadline = framepacer.begin_frame(start, 60.0f);

      assert(framepacer.should_wait(deadline - std::chrono::microseconds(1)));
      assert(!framepacer.should_wait(deadline));

   }


   void test_wait_slice_is_bounded_for_runtime_changes_and_shutdown()
   {

      auto maximumSlice = std::chrono::duration_cast<clock::duration>(std::chrono::milliseconds(10));
      auto shortRemaining = std::chrono::duration_cast<clock::duration>(std::chrono::milliseconds(3));

      assert(pacer::wait_slice(std::chrono::duration_cast<clock::duration>(
         std::chrono::seconds(1))) == maximumSlice);
      assert(pacer::wait_slice(shortRemaining) == shortRemaining);

   }


} // namespace


int main()
{

   test_default_sixty_fps_interval();
   test_runtime_fps_change_resets_deadline();
   test_same_fps_accumulates_deadlines();
   test_overrun_resets_instead_of_catching_up();
   test_late_wake_resets_instead_of_catching_up();
   test_invalid_fps_uses_sixty_fps();
   test_extreme_positive_fps_uses_representable_intervals();
   test_expired_deadline_does_not_wait();
   test_wait_slice_is_bounded_for_runtime_changes_and_shutdown();

   return 0;

}
