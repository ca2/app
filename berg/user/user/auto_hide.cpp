#include "platform.h"
#include "auto_hide.h"
#include "fps_debug.h"
#include <chrono>
#include "aura/graphics/graphics/buffer_item.h"
#include "aura/graphics/draw2d/graphics.h"
#include "acme/constant/timer.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/message/user.h"
#include "aura/windowing/window.h"
#include "aura/windowing/display.h"

namespace user
{
   auto_hide::auto_hide() { defer_create_synchronization(); }
   auto_hide::~auto_hide() {}

   void auto_hide::attach(::user::interaction * powner)
   {
      if (m_powner == powner) return;
      detach();
      m_powner = powner;
   }

   void auto_hide::detach()
   {
      if (m_powner && (m_bAutoHidePolling || m_bControlVisibilityChanging))
         m_powner->kill_timer(e_timer_defer_handle_auto_hide_tabs);
      m_bAutoHidePolling = false;
      m_bControlVisibilityChanging = false;
      {
         synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         m_bVisibilityCalculationPosted = false;
      }
      debug_cancel_reveal();
      m_powner = nullptr;
   }

   ::pointer_array<::user::interaction> auto_hide::auto_hide_interactions_snapshot()
   {
      ::pointer_array<::user::interaction> interactions;
      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      for (auto pinteraction : m_interactionaAutoHide)
         if (pinteraction && !pinteraction->has_destroying_flag())
            interactions.add(pinteraction);
      return interactions;
   }

   void auto_hide::add_auto_hide_interaction(::user::interaction * pinteraction, ::i32 iHeight)
   {
      if (!pinteraction || pinteraction == m_powner) return;
      bool bAdded;
      {
         synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         bAdded = !m_interactionaAutoHide.contains(pinteraction);
         m_interactionaAutoHide.add_unique(pinteraction);
         m_mapKeepOpenHeight[pinteraction] = iHeight;
      }
      // Updating strip geometry during layout must not re-enter visibility handling.
      if (bAdded) auto_hide_calculate_control_visibility();
   }

   void auto_hide::erase_auto_hide_interaction(::user::interaction * pinteraction)
   {
      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      m_interactionaAutoHide.erase(pinteraction);
      m_mapKeepOpenHeight.erase(pinteraction);
      m_mapOverlayAfter.erase(pinteraction);
      for (auto psubscriber : m_interactionaAutoHide)
         if (m_mapOverlayAfter[psubscriber] == pinteraction)
            m_mapOverlayAfter[psubscriber] = nullptr;
   }

   void auto_hide::set_overlay_after(::user::interaction * pinteraction, ::user::interaction * pprevious)
   {
      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      if (pinteraction && pinteraction != pprevious
         && m_interactionaAutoHide.contains(pinteraction)
         && (!pprevious || m_interactionaAutoHide.contains(pprevious)))
         m_mapOverlayAfter[pinteraction] = pprevious;
   }

   ::i32 auto_hide::overlay_top(::user::interaction * pinteraction, ::user::interaction * pparent,
      ::user::enum_layout elayout)
   {
      if (!pparent || !m_bEffectiveVisibleControl) return 0;
      ::pointer<::user::interaction> pprevious;
      ::i32 iHeight = -1;
      {
         synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         auto p = m_mapOverlayAfter[pinteraction];
         if (p && m_interactionaAutoHide.contains(p) && !p->has_destroying_flag())
         {
            pprevious = p;
            iHeight = m_mapKeepOpenHeight[p];
         }
      }
      if (!pprevious || !pprevious->is_window_visible(elayout)) return 0;
      if (iHeight < 0) iHeight = pprevious->height(elayout);
      return maximum(0, pprevious->screen_origin(elayout).y + iHeight
         - pparent->screen_origin(elayout).y);
   }

   bool auto_hide::auto_hide_is_top_level_full_screen_or_transparent()
   {
      return m_powner && (m_powner->top_level()->frame_is_transparent()
         || m_powner->top_level_frame()->layout().is_full_screen(::user::e_layout_sketch));
   }

   bool auto_hide::auto_hide_full_screen_or_transparent_frame_control_visibility()
   {
      if (!m_powner) return false;
      if (m_powner->is_sandboxed() || !m_bHideControlOnFullScreenOrTransparentFrame)
         return true;
      if (m_bOverrideVisibleControl) return true;
      if (m_bVisibleIfWindowActive && m_powner->is_active_window()) return true;
      if (auto_hide_is_top_level_full_screen_or_transparent()) return false;
      return true;
   }

   void auto_hide::notify_auto_hide_interactions()
   {
      if (!m_powner) return;
      auto interactions = auto_hide_interactions_snapshot();
      if (interactions.is_empty()) return;
      auto ptopic = m_powner->create_topic("auto_hide_visibility");
      ptopic->payload("coordinated") = m_bHideControlOnFullScreenOrTransparentFrame
         && m_powner->top_level_frame()->layout().is_full_screen(::user::e_layout_sketch);
      ptopic->payload("visible") = m_bEffectiveVisibleControl;
      for (auto & pinteraction : interactions)
         if (!pinteraction->has_destroying_flag())
            pinteraction->handle(ptopic, nullptr);
   }

   void auto_hide::auto_hide_calculate_control_visibility()
   {
      if (!m_powner || m_powner->has_destroying_flag()) return;
      if (!m_powner->user_thread()) return;
      if (!m_powner->is_branch_current())
      {
         ::pointer<::user::interaction> owner = m_powner;
         ::pointer<auto_hide> self = this;
         {
            synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
            if (m_bVisibilityCalculationPosted) return;
            m_bVisibilityCalculationPosted = true;
         }
         try
         {
            owner->user_post([self, owner]()
            {
               {
                  synchronous_lock lock(self->synchronization(), self.get(), SYNCHRONOUS_LOCK_SUFFIX);
                  self->m_bVisibilityCalculationPosted = false;
               }
               if (self->m_powner == owner.get() && !owner->has_destroying_flag())
                  self->auto_hide_calculate_control_visibility();
            });
         }
         catch (...)
         {
            synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
            m_bVisibilityCalculationPosted = false;
            throw;
         }
         return;
      }
      bool bWasVisible = m_bEffectiveVisibleControl;
      bool bWasPolling = m_bAutoHidePolling;
      bool bPoll = !m_powner->is_sandboxed() && m_bHideControlOnFullScreenOrTransparentFrame
         && auto_hide_is_top_level_full_screen_or_transparent();
      if (bPoll && !bWasPolling)
         m_powner->set_timer(e_timer_defer_handle_auto_hide_tabs, 100_ms);
      if (!bPoll && bWasPolling)
         m_powner->kill_timer(e_timer_defer_handle_auto_hide_tabs);
      m_bAutoHidePolling = bPoll;
      m_bOverrideVisibleControl = false;
#if FPS_DEBUG
      bool bEdgeHit = false;
      ::i32_point debugCursor;
      ::i32_rectangle debugKeepOpenRectangle;
      ::pointer<::user::interaction> debugKeepOpenInteraction;
#endif
      if (bPoll)
      {
         auto pwindow = m_powner->window();
         if (pwindow && pwindow->display())
         {
            auto pointScreen = pwindow->display()->get_mouse_cursor_position();
#if FPS_DEBUG
            debugCursor = pointScreen;
#endif
            auto point = pointScreen;
            point -= m_powner->screen_origin();
            // A frame coordinates chrome; its full client must never keep it open.
            bool bFrameOwner = m_powner == m_powner->top_level_frame();
            auto iHeight = bWasPolling && bWasVisible && !bFrameOwner
               ? (m_iKeepOpenHeight < 0 ? m_powner->height() : m_iKeepOpenHeight)
               : m_iAutoHideRevealHeight;
            // The edge remains a reveal/keep-open region for a frame controller.
            iHeight = maximum(iHeight, m_iAutoHideRevealHeight);
            m_bOverrideVisibleControl = m_powner->raw_rectangle().contains(point)
               && point.y >= 0 && point.y < iHeight;
#if FPS_DEBUG
            bEdgeHit = m_bOverrideVisibleControl;
#endif
            if (bWasPolling && bWasVisible && !m_bOverrideVisibleControl)
            {
               for (auto & pinteraction : auto_hide_interactions_snapshot())
               {
                  if (!pinteraction->is_window_visible()) continue;
                  auto rectangle = pinteraction->screen_rectangle();
                  {
                     synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
                     auto iSubscriberHeight = m_mapKeepOpenHeight[pinteraction.get()];
                     if (iSubscriberHeight >= 0)
                        rectangle.bottom = minimum(rectangle.bottom, rectangle.top + iSubscriberHeight);
                  }
                  if (rectangle.contains(pointScreen))
                  {
                     m_bOverrideVisibleControl = true;
#if FPS_DEBUG
                     debugKeepOpenInteraction = pinteraction;
                     debugKeepOpenRectangle = rectangle;
#endif
                     break;
                  }
               }
            }
         }
      }
      bool bWanted = !m_bForceHiddenControl && m_bVisibleControl
         && auto_hide_full_screen_or_transparent_frame_control_visibility();
      if (bWanted)
      {
         m_bEffectiveVisibleControl = true;
         m_bControlVisibilityChanging = false;
      }
      else if (m_bForceHiddenControl || (bPoll && !bWasPolling))
      {
         m_bEffectiveVisibleControl = false;
         m_bControlVisibilityChanging = false;
      }
      else if (m_bEffectiveVisibleControl)
      {
         if (!m_bControlVisibilityChanging)
         {
            m_bControlVisibilityChanging = true;
            m_timeLastControlVisibilityChange.Now();
            if (!bPoll) m_powner->set_timer(e_timer_defer_handle_auto_hide_tabs, 100_ms);
         }
         else if (m_timeLastControlVisibilityChange.elapsed() >= 2_s)
         {
            m_bEffectiveVisibleControl = false;
            m_bControlVisibilityChanging = false;
         }
      }
      if (bWasVisible != m_bEffectiveVisibleControl)
      {
         if (m_bEffectiveVisibleControl) debug_record_reveal(false);
         else debug_cancel_reveal();
         m_powner->set_need_layout();
         m_powner->set_need_redraw();
         m_powner->post_redraw();
      }
      // Stop timers only after the owner has evaluated the current state.
      if (!m_bAutoHidePolling && !m_bControlVisibilityChanging)
         m_powner->kill_timer(e_timer_defer_handle_auto_hide_tabs);
#if FPS_DEBUG
      if (bWasVisible != m_bEffectiveVisibleControl
         || (m_bEffectiveVisibleControl && m_timeLastVisibilityDebug.elapsed() >= 2_s))
      {
         m_timeLastVisibilityDebug.Now();
         ::string report;
         report.formatf("FPS auto-hide state: owner=%p visible=%d polling=%d reason=%s "
            "cursor=(%d,%d) keep_open=%p rect=(%d,%d,%d,%d) countdown=%d\n",
            (void *)m_powner, (int)m_bEffectiveVisibleControl, (int)m_bAutoHidePolling,
            bEdgeHit ? "edge" : debugKeepOpenInteraction ? "subscriber"
               : bWanted ? "visibility_policy" : m_bEffectiveVisibleControl ? "hide_delay" : "hidden",
            debugCursor.x, debugCursor.y, (void *)debugKeepOpenInteraction.get(),
            debugKeepOpenRectangle.left, debugKeepOpenRectangle.top,
            debugKeepOpenRectangle.right, debugKeepOpenRectangle.bottom,
            (int)m_bControlVisibilityChanging);
         ::output_debug_string(report);
      }
#endif
      notify_auto_hide_interactions();
   }

   void auto_hide::debug_record_reveal(bool bEvent, long long event_ns)
   {
#if FPS_DEBUG
      auto timestamp = event_ns ? event_ns : ::graphics::presentation_trace::now_ns();
      debug_cancel_reveal();
      auto trace = std::make_shared<::graphics::presentation_trace>();
      trace->event_ns = timestamp;
      trace->from_event = bEvent;
      std::atomic_store(&m_pPresentationTrace, trace);
      m_iDebugRevealTimestamp.store(bEvent ? timestamp : -timestamp);
#endif
   }

   void auto_hide::debug_on_tab_draw(::draw2d::graphics * pgraphics)
   {
#if FPS_DEBUG
      auto trace = std::atomic_load(&m_pPresentationTrace);
      if (trace && !trace->cancelled.load() && !trace->completed.load()
         && pgraphics && pgraphics->m_pgraphicsbufferitem)
      {
         auto & frame = pgraphics->m_pgraphicsbufferitem->m_presentationTrace;
         frame.trace = trace;
         frame.tab_draw_ns = ::graphics::presentation_trace::now_ns();
      }
      auto timestamp = m_iDebugRevealTimestamp.exchange(0);
      if (!timestamp) return;
      auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
         std::chrono::steady_clock::now().time_since_epoch()).count();
      auto start = timestamp > 0 ? timestamp : -timestamp;
      ::string report;
      report.formatf("FPS auto-hide: owner=%p source=%s reveal_to_tab_draw=%.2fms id=%lld (CPU draw; excludes presentation/RDP)\n",
         (void *)m_powner, timestamp > 0 ? "event" : "poll/layout", (now - start) / 1000000.0, start);
      ::output_debug_string(report);
#endif
   }

   void auto_hide::debug_cancel_reveal()
   {
#if FPS_DEBUG
      auto trace = std::atomic_exchange(&m_pPresentationTrace,
         std::shared_ptr<::graphics::presentation_trace>{});
      if (trace) trace->cancelled.store(true);
      m_iDebugRevealTimestamp.store(0);
#endif
   }

   bool auto_hide::should_draw()
   {
      return m_bEffectiveVisibleControl;
   }

   void auto_hide::operator()(::timer * ptimer)
   {
      if (ptimer->m_etimer == e_timer_defer_handle_auto_hide_tabs)
      {
         auto_hide_calculate_control_visibility();
      }
   }

   void auto_hide::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      if (ptopic->id() != "auto_hide_visibility")
         auto_hide_calculate_control_visibility();
   }

   void auto_hide::auto_hide_on_message_mouse_move(::message::message * pmessage)
   {
      if (!m_powner) return;
      ::pointer<::message::mouse> pmouse(pmessage);
      auto point = pmouse->m_pointHost;
      point -= m_powner->host_origin();
      auto_hide_on_mouse_move(point);
   }

   void auto_hide::auto_hide_on_mouse_move(const ::i32_point & point, long long event_ns)
   {
#if FPS_DEBUG
      if (!event_ns) event_ns = ::graphics::presentation_trace::now_ns();
#endif
      if (!m_powner || m_powner->has_destroying_flag() || !m_powner->user_thread()) return;
      if (!m_powner->is_branch_current())
      {
         ::pointer<::user::interaction> owner = m_powner;
         ::pointer<auto_hide> self = this;
         owner->user_post([self, owner, point, event_ns]()
         {
            if (self->m_powner == owner.get() && !owner->has_destroying_flag())
               self->auto_hide_on_mouse_move(point, event_ns);
         });
         return;
      }
      // Preserve brief edge hits that the periodic live-cursor poll could miss.
      if (auto_hide_is_top_level_full_screen_or_transparent()
         && m_bHideControlOnFullScreenOrTransparentFrame && !m_bForceHiddenControl
         && m_bVisibleControl && m_powner->raw_rectangle().contains(point)
         && point.y >= 0 && point.y < m_iAutoHideRevealHeight)
      {
         if (!m_bAutoHidePolling)
         {
            m_powner->set_timer(e_timer_defer_handle_auto_hide_tabs, 100_ms);
            m_bAutoHidePolling = true;
         }
         bool bWasVisible = m_bEffectiveVisibleControl;
#if FPS_DEBUG
         if (!bWasVisible) debug_record_reveal(true, event_ns);
#endif
         m_bOverrideVisibleControl = true;
         m_bEffectiveVisibleControl = true;
         m_bControlVisibilityChanging = false;
         if (!bWasVisible)
         {
            // Publish subscriber visibility before requesting the frame draw.
            notify_auto_hide_interactions();
            m_powner->set_need_layout();
            m_powner->set_need_redraw();
            m_powner->post_redraw();
         }
      }
      else auto_hide_calculate_control_visibility();
   }

   void auto_hide::auto_hide_on_message_mouse_leave(::message::message * pmessage)
   {
      auto_hide_calculate_control_visibility();
   }
}
