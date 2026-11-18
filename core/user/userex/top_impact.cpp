#include "platform.h"
#include "top_impact.h"
#include "top_edit_impact.h"
#include "top_toggle_impact.h"
#include "acme/constant/timer.h"
#include "acme/handler/topic.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/windowing/window.h"
#include "aura/windowing/display.h"


namespace userex
{


   top_impact::top_impact()
   {

      m_peditimpact = nullptr;
      m_ptoggleimpact = nullptr;

   }


   top_impact::~top_impact()
   {
      set_auto_hide_coordinator(nullptr);
   }

   void top_impact::destroy()
   {
      set_auto_hide_coordinator(nullptr);
      kill_timer(e_timer_full_screen_editor_interest);
      ::user::split_impact::destroy();
   }

   void top_impact::set_auto_hide_coordinator(::user::auto_hide * pcoordinator, ::user::interaction * pprevious)
   {
      if (m_pAutoHideCoordinator == pcoordinator)
      {
         if (pcoordinator) pcoordinator->set_overlay_after(this, pprevious);
         return;
      }
      if (m_pAutoHideCoordinator)
         m_pAutoHideCoordinator->erase_auto_hide_interaction(this);
      m_pAutoHideCoordinator = pcoordinator;
      m_bCoordinatedFullScreenAutoHide = false;
      if (m_pAutoHideCoordinator)
      {
         m_pAutoHideCoordinator->add_auto_hide_interaction(this, m_iNormalEditorHeight);
         m_pAutoHideCoordinator->set_overlay_after(this, pprevious);
         update_full_screen_auto_hide();
      }
   }

   void top_impact::set_auto_hide_on_full_screen(bool bEnable)
   {
      m_bAutoHideOnFullScreen = bEnable;
      if (!bEnable)
         set_auto_hide_coordinator(nullptr);
      if (bEnable)
         set_timer(e_timer_full_screen_editor_interest, 100_ms);
      // Keep the timer for one more tick when disabling, to restore the row.
   }

   void top_impact::operator()(::timer * ptimer)
   {
      ::user::split_impact::operator()(ptimer);
      if (ptimer->m_etimer != e_timer_full_screen_editor_interest)
         return;
      update_full_screen_auto_hide();
   }

   void top_impact::update_full_screen_auto_hide()
   {
      auto psplit = get_typed_parent<::user::split_layout>();
      auto pholder = get_parent();
      auto pframe = top_level_frame();
      if (!psplit || !pholder || !pframe)
         return;

      bool bFullScreen = m_bAutoHideOnFullScreen
         && pframe->layout().is_full_screen(::user::e_layout_sketch);
      bool bVisible = true;
      if (bFullScreen)
      {
         if (!m_bWasAutoHiddenFullScreen)
         {
            auto iHeight = height(::user::e_layout_design);
            if (iHeight > 0)
               m_iNormalEditorHeight = iHeight;
            m_bFullScreenEditorRevealed = false;
         }
         if (m_bCoordinatedFullScreenAutoHide)
         {
            bVisible = psplit->is_window_visible(::user::e_layout_sketch)
               && m_bCoordinatedFullScreenVisible;
         }
         else
         {
            auto rectangleParent = psplit->screen_rectangle();
            auto pwindow = window();
            if (!pwindow || !pwindow->display())
               return;
            auto point = pwindow->display()->get_mouse_cursor_position();
            auto iRevealHeight = m_bFullScreenEditorRevealed
               ? maximum(m_iNormalEditorHeight, pholder->screen_rectangle().bottom - rectangleParent.top)
                  + m_iFullScreenRevealHeight : m_iFullScreenRevealHeight;
            bVisible = psplit->is_window_visible() && rectangleParent.contains(point)
               && point.y < rectangleParent.top + iRevealHeight;
            // A revealed editor remains usable while the user is typing.
            if (m_bFullScreenEditorRevealed && m_peditimpact
               && get_keyboard_focus() == m_peditimpact)
               bVisible = true;
         }
         m_bFullScreenEditorRevealed = bVisible;
      }

      if (bFullScreen && m_bCoordinatedFullScreenAutoHide && bVisible)
      {
         // The shared controller describes where this overlay belongs. Reapply
         // its geometry on reveal, even if the holder was laid out while hidden.
         auto rectangleEditor = psplit->raw_rectangle(::user::e_layout_sketch);
         rectangleEditor.top += m_pAutoHideCoordinator->overlay_top(this, psplit)
            + m_iFullScreenOverlaySpacing;
         rectangleEditor.bottom = minimum(rectangleEditor.bottom,
            rectangleEditor.top + m_iNormalEditorHeight);
         if (rectangleEditor != pholder->const_layout().sketch().parent_raw_rectangle())
         {
            pholder->place(rectangleEditor);
            pholder->order(e_zorder_top);
            psplit->set_need_layout();
         }
      }

      if ((bFullScreen || m_bWasAutoHiddenFullScreen)
         && pholder->const_layout().sketch().is_visible() != bVisible)
      {
         // Place holders automatically show their sole child during layout.
         // Hide only the holder, leaving the editor's own visibility stable.
         display(e_display_normal);
         pholder->display(bVisible ? e_display_normal : e_display_none);
         psplit->set_need_layout();
         psplit->set_need_redraw();
         psplit->post_redraw();
      }
      m_bWasAutoHiddenFullScreen = bFullScreen;
      if (!m_bAutoHideOnFullScreen)
         kill_timer(e_timer_full_screen_editor_interest);
   }


   void top_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == "auto_hide_visibility")
      {
         bool bCoordinated = ptopic->payload("coordinated").is_true();
         bool bVisible = ptopic->payload("visible").is_true();
         m_bCoordinatedFullScreenAutoHide = bCoordinated;
         m_bCoordinatedFullScreenVisible = bVisible;
         update_full_screen_auto_hide();
         return;
      }

      ::user::split_impact::handle(ptopic, phandlercontext);

   }


   void top_impact::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0, 0.80);

      initialize_split_layout();

      m_peditimpact = create_pane_impact < top_edit_impact >(0, "top_edit_impact");

      m_peditimpact->m_bParseDataPacks = true;

      if (m_peditimpact == nullptr)
      {

         output_error_message("Could not create folder edit impact");

      }

      m_peditimpact->m_ptopimpact = this;

      m_ptoggleimpact = create_pane_impact < top_toggle_impact >(1, "top_toggle_impact");

      if (m_ptoggleimpact == nullptr)
      {

         output_error_message("Could not create file list_base ::user::impact");

      }

      m_ptoggleimpact->m_ptopimpact = this;

   }


   bool top_impact::is_this_visible(::user::enum_layout elayout)
   {

      return ::user::split_impact::is_this_visible(elayout) && !top_level()->frame_is_transparent();

   }


   void top_impact::_001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::user::split_impact::_001OnNcDraw(pdraw2dgraphics);

   }


   void top_impact::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      string strType = "top_impact";

      auto timeStart = ::time::now();

      ::user::split_impact::_001OnDraw(pdraw2dgraphics);

      auto timeEllapsed = timeStart.elapsed();

#ifdef VERBOSE_LOG      

      if(d1 > 50_ms)
      {

         information()(e_trace_category_prodevian) << "(more than 50ms)(H) "<< strType << "::_000OnDraw took " << integral_millisecond(d1) << ".\n";

      }

#endif

   }


} // namespace userex



