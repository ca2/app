#pragma once
#include <atomic>
#include <chrono>
#include <memory>

namespace graphics
{
   // One reveal, retained until a buffer containing it is successfully committed.
   struct presentation_trace
   {
      long long event_ns = 0;
      bool from_event = false;
      std::atomic<bool> completed{false};
      std::atomic<bool> cancelled{false};
      static long long now_ns()
      {
         return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
      }
   };

   // Per-buffer timestamps. Copy these with the presentation of this exact buffer.
   struct CLASS_DECL_AURA presentation_trace_frame
   {
      std::shared_ptr<presentation_trace> trace;
      long long tab_draw_ns = 0;
      long long render_end_ns = 0;
      long long present_start_ns = 0;
      long long owner_queued_ns = 0;
      long long owner_start_ns = 0;
      long long frame_start_ns = 0;
      long long layout_start_ns = 0;
      long long layout_end_ns = 0;
      void finish(long long native_start_ns, long long native_end_ns,
         bool succeeded, unsigned long error, const char * api) const;
   };
}