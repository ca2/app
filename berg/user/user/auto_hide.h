#pragma once
#include "aura/user/user/interaction.h"
#include <atomic>
#include "aura/graphics/graphics/presentation_trace.h"

namespace user
{
   // A composed controller. The owner forwards timer and mouse events and must
   // detach before destruction. Neither owner nor subscribers are retained.
   class CLASS_DECL_BERG auto_hide : virtual public ::matter
   {
   public:
      ::user::interaction * m_powner = nullptr;
      bool m_bEffectiveVisibleControl = true;
      bool m_bControlVisibilityChanging = false;
      bool m_bOverrideVisibleControl = false;
      bool m_bHideControlOnFullScreenOrTransparentFrame = true;
      bool m_bVisibleControl = true;
      bool m_bForceHiddenControl = false;
      bool m_bVisibleIfWindowActive = false;
      bool m_bAutoHidePolling = false;
      void debug_record_reveal(bool bEvent, long long event_ns = 0);
      void debug_on_tab_draw(::draw2d::graphics * pgraphics);
      void debug_cancel_reveal();
      ::i32 m_iAutoHideRevealHeight = 1;
      // Zero for a frame coordinator: only registered chrome keeps it open.
      ::i32 m_iKeepOpenHeight = -1;
      class ::time m_timeLastControlVisibilityChange;
      ::address_array_base<::user::interaction *> m_interactionaAutoHide;
      ::map_base<::user::interaction *, ::i32> m_mapKeepOpenHeight;

      // Optional layout dependency: an overlay starts below another member's
      // registered strip. Visibility coordination does not reserve client space.
      ::map_base<::user::interaction *, ::user::interaction *> m_mapOverlayAfter;
      void set_overlay_after(::user::interaction * pinteraction, ::user::interaction * pprevious);
      ::i32 overlay_top(::user::interaction * pinteraction, ::user::interaction * pparent,
         ::user::enum_layout elayout = ::user::e_layout_sketch);

      auto_hide();
      ~auto_hide() override;
      void attach(::user::interaction * powner);
      void detach();
      void add_auto_hide_interaction(::user::interaction * pinteraction, ::i32 iHeight = -1);
      void erase_auto_hide_interaction(::user::interaction * pinteraction);
      ::pointer_array<::user::interaction> auto_hide_interactions_snapshot();
      void notify_auto_hide_interactions();
      void auto_hide_calculate_control_visibility();
      bool auto_hide_is_top_level_full_screen_or_transparent();
      bool auto_hide_full_screen_or_transparent_frame_control_visibility();
      bool should_draw();
      void operator()(::timer * ptimer);
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      void auto_hide_on_message_mouse_move(::message::message * pmessage);
      void auto_hide_on_mouse_move(const ::i32_point & pointOwner, long long event_ns = 0);
      void auto_hide_on_message_mouse_leave(::message::message * pmessage);

      // Append diagnostics so existing controller state retains its offsets.
      // Positive for event reveal, negative for poll/layout; same layout with FPS_DEBUG off.
      std::atomic<long long> m_iDebugRevealTimestamp{0};
      std::shared_ptr<::graphics::presentation_trace> m_pPresentationTrace;
      // Protected by synchronization(); visibility transitions run on the owner UI task.
      bool m_bVisibilityCalculationPosted = false;
      class ::time m_timeLastVisibilityDebug;
   };
}
