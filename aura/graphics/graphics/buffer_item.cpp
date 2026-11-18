// From graphics.cpp by camilo on 2026-07-31 20:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "buffer_item.h"
#include "fps_debug.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/windowing/window.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"


namespace graphics
{


   //::draw2d::graphics_lease buffer_item::acquire_graphics()
   //{

   //   return ::transfer(m_pimageBufferItem->acquire_graphics());

   //}


   //::draw2d::graphics_pointer buffer_item::owned_graphics()
   ::draw2d::graphics_lease buffer_item::acquire_graphics()
   {

      if (m_pgraphicsBufferItem)
      {

         return { system()->draw2d(), m_pgraphicsBufferItem, nullptr, true };

      }
      else
      {

         return ::transfer(m_pimageBufferItem->acquire_graphics());

      }

      //if (pdraw2dgraphics)
      //{

      //   pdraw2dgraphics->m_egraphics = m_egraphics;

      //}

      //if (!pdraw2dgraphics->m_callbackImage32CpuBuffer)
      //{

      //   pdraw2dgraphics->m_callbackImage32CpuBuffer = [this](const ::image32_t * pimage32, ::i32 cx, ::i32 cy, ::i32 scan)
      //      {

      //         //_synchronous_lock synchronouslock(this->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //         m_pimage2->image32()->copy(cx, cy, m_pimage2->m_iScan, pimage32, scan);

      //      };

      //}

      //return ::transfer(pdraw2dgraphics);

   }





   void buffer_item::switch_to_draw()
   {

      m_egraphics = e_graphics_draw;

      //owned_graphics();

      //m_pimageBufferItem->set_owned_graphics();


   }


   void presentation_trace_frame::finish(long long native_start_ns, long long native_end_ns,
      bool succeeded, unsigned long error, const char * api) const
   {
#if FPS_DEBUG
      if (!trace || trace->cancelled.load() || trace->completed.load()) return;
      if (succeeded && trace->completed.exchange(true)) return;
      auto ms = [](long long end, long long start) { return (end - start) / 1000000.0; };
      // The reveal may arrive during a frame already in progress. Partition only
      // time after the event, and report that phase instead of negative waits.
      auto after_event_ms = [&](long long end, long long begin)
      {
         auto start = begin > trace->event_ns ? begin : trace->event_ns;
         return end > start ? ms(end, start) : 0.0;
      };
      auto phase = trace->event_ns <= frame_start_ns ? "before_frame"
         : trace->event_ns < layout_start_ns ? "frame_setup"
         : trace->event_ns < layout_end_ns ? "layout" : "drawing";
      ::string report;
      report.formatf("FPS auto-hide present: id=%lld source=%s result=%s api=%s error=%lu "
         "event_to_present=%.2fms event_to_tab=%.2fms event_phase=%s "
         "event_to_frame_start=%.2fms frame_setup_after_event=%.2fms "
         "layout_after_event=%.2fms layout_to_tab=%.2fms "
         "layout_total=%.2fms frame_age_at_event=%.2fms remaining_render=%.2fms "
         "pacing=%.2fms present_prepare=%.2fms owner_wait=%.2fms "
         "owner_prepare=%.2fms native_commit=%.2fms (native API return; excludes compositor/RDP)\n",
         trace->event_ns, trace->from_event ? "event" : "poll/layout",
         succeeded ? "success" : "failed", api, error,
         ms(native_end_ns, trace->event_ns), ms(tab_draw_ns, trace->event_ns), phase,
         after_event_ms(frame_start_ns, trace->event_ns),
         after_event_ms(layout_start_ns, frame_start_ns),
         after_event_ms(layout_end_ns, layout_start_ns),
         after_event_ms(tab_draw_ns, layout_end_ns),
         ms(layout_end_ns, layout_start_ns),
         trace->event_ns > frame_start_ns ? ms(trace->event_ns, frame_start_ns) : 0.0,
         ms(render_end_ns, tab_draw_ns), ms(present_start_ns, render_end_ns),
         ms(owner_queued_ns, present_start_ns), ms(owner_start_ns, owner_queued_ns),
         ms(native_start_ns, owner_start_ns), ms(native_end_ns, native_start_ns));
      ::output_debug_string(report);
#endif
   }
   void buffer_item::destroy()
   {

      ::particle::destroy();

      m_pmutex.release();

      m_pimageBufferItem.defer_destroy_and_release();

      //m_pgraphicsBufferItem.release();

      //m_pwindowbuffer.release();

   }


} // namespace graphics



