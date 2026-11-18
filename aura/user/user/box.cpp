#include "platform.h"
#include "box.h"
#include "acme/platform/__string.h"
#include "acme/constant/user_message.h"
#include "acme/constant/simple_command.h"
#include "acme/parallelization/single_lock.h"
#include "acme/parallelization/_.h"
#include "acme/platform/scoped_restore.h"
#include "acme/platform/keep.h"
#include "acme/platform/system.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/_text_stream.h"
#include "apex/database/_binary_stream.h"
#include "apex/message/simple_command.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/windowing/display.h"
#include "aura/windowing/monitor.h"


namespace user
{


   box::box()
   {

      m_windowdisplayandlayoutStore.m_edisplay = ::e_display_undefined;

   }


   box::~box()
   {

   }


   void box::initialize(::particle * pparticle)
   {

      interaction::initialize(pparticle);

   }


   void box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &box::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_size, pchannel, this, &box::on_message_size);
      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &box::on_message_show_window);

   }


   void box::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

   }


   void box::on_message_size(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void box::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   ::e_display box::window_stored_display()
   {

      auto edisplayStored = m_windowdisplayandlayout.m_edisplay;

      return edisplayStored;

   }


   ::e_display box::_window_previous_display()
   {

      auto edisplayPrevious = m_windowdisplayandlayout.m_edisplayPrevious;

      return edisplayPrevious;

   }


   ::e_display box::window_previous_display()
   {

      auto edisplayPrevious = _window_previous_display();

      if (edisplayPrevious == const_layout().design().display()
         && edisplayPrevious == e_display_zoomed)
      {

         edisplayPrevious = m_windowdisplayandlayout.m_edisplayLastNormal;

      }

      return edisplayPrevious;

   }


   void box::set_window_previous_display(::e_display edisplayPrevious)
   {

      m_windowdisplayandlayout.m_edisplayPrevious = edisplayPrevious;

   }


   void box::_on_configure_notify_unlocked(const ::i32_rectangle & rectangle)
   {

      ::user::interaction::_on_configure_notify_unlocked(rectangle);

      auto & edisplay = layout().design().display();

      if (m_iRestoreDiagnosticConfigureCount > 0)
      {

         auto rectangleNative = window()->get_window_rectangle();
         auto rectangleWindow = layout().window().parent_raw_rectangle();
         auto rectangleDesign = layout().design().parent_raw_rectangle();

         ::string strRestoreTrace;
         strRestoreTrace.formatf(
             "Restore trace: configure remaining=%d rect=(%d,%d,%d,%d) size=%dx%d native=(%d,%d,%d,%d) design=(%d,%d,%d,%d) window=(%d,%d,%d,%d) sketch_display=%d lading_display=%d layout_display=%d design_display=%d window_display=%d",
            m_iRestoreDiagnosticConfigureCount,
            rectangle.left, rectangle.top, rectangle.right, rectangle.bottom,
            rectangle.width(), rectangle.height(),
            rectangleNative.left, rectangleNative.top, rectangleNative.right, rectangleNative.bottom,
            rectangleDesign.left, rectangleDesign.top, rectangleDesign.right, rectangleDesign.bottom,
            rectangleWindow.left, rectangleWindow.top, rectangleWindow.right, rectangleWindow.bottom,
            (int)layout().sketch().display(), (int)layout().lading().display(),
            (int)layout().layout().display(), (int)layout().design().display(),
            (int)layout().window().display());
         information() << strRestoreTrace;
         --m_iRestoreDiagnosticConfigureCount;

      }

      m_windowdisplayandlayout.m_edisplay = const_layout().window().display();

      m_windowdisplayandlayout.m_rectangleWindow = rectangle;

      // Configure notifications can arrive while the layout stages disagree
      // during a transition. Check every stage so a full-screen rectangle
      // cannot be learned as a normal restore preset.
      auto bSpecialDisplay = layout().is_full_screen(::user::e_layout_sketch)
         || layout().is_full_screen(::user::e_layout_lading)
         || layout().is_full_screen(::user::e_layout_layout)
         || layout().is_full_screen(::user::e_layout_design)
         || layout().is_full_screen(::user::e_layout_output)
         || layout().is_full_screen(::user::e_layout_window)
         || layout().is_zoomed(::user::e_layout_sketch)
         || layout().is_zoomed(::user::e_layout_lading)
         || layout().is_zoomed(::user::e_layout_layout)
         || layout().is_zoomed(::user::e_layout_design)
         || layout().is_zoomed(::user::e_layout_output)
         || layout().is_zoomed(::user::e_layout_window);

      if (bSpecialDisplay)
      {

         return;

      }

      if (is_docking_appearance(edisplay))
      {

         m_windowdisplayandlayout.m_rectangleSnapped = m_windowdisplayandlayout.m_rectangleWindow;

      }
      //else if (!layout().is_docking() && (system()->acme_windowing()->get_ewindowing() != ::windowing::e_windowing_wayland) && is_equivalent_in_equivalence_sink(edisplay, e_display_normal))
      else if (!layout().is_docking() && is_equivalent_in_equivalence_sink(edisplay, e_display_normal))
      {

         ::i32_rectangle rectangleWorkspace;

         if (calculate_broad_and_compact_restore(&rectangleWorkspace) < 0)
         {

            return;

         }

         auto sizeMin = get_window_minimum_size();
         auto sizeMaximumRestore = sizeMin.maximum(rectangleWorkspace.size() * 9 / 10);
         auto sizeWindow = rectangle.size();

         // Do not learn full-screen/maximized transition geometry as a restore
         // preset, even if its configure event arrives during a normal state.
         if (!(sizeWindow >= sizeMin) || !(sizeWindow <= sizeMaximumRestore))
         {

            return;

         }

         ::e_display edisplay = ::e_display_undefined;

         if (m_windowdisplayandlayout.m_rectangleWindow.size() >= m_rectangleRestoreBroad.size() * 0.8)
         {

            m_windowdisplayandlayout.m_rectangleBroad = m_windowdisplayandlayout.m_rectangleWindow;

            debug() << "Detected as m_windowdisplayandlayout.m_rectangleBroad (1) : " << m_windowdisplayandlayout.m_rectangleBroad;

            edisplay = ::e_display_broad;

            debug() << "Detected at box::_on_configure_notify_unlocked() as e_display_broad";

         }
         else if (m_windowdisplayandlayout.m_rectangleWindow.size() <= m_rectangleRestoreCompact.size() * 1.125)
         {

            m_windowdisplayandlayout.m_rectangleCompact = m_windowdisplayandlayout.m_rectangleWindow;

            debug() << "Detected as m_windowdisplayandlayout.m_rectangleCompact (1) : " << m_windowdisplayandlayout.m_rectangleCompact;

            edisplay = ::e_display_compact;

            debug() << "Detected at box::_on_configure_notify_unlocked() as e_display_compact";

         }
         else
         {

            m_windowdisplayandlayout.m_rectangleNormal = m_windowdisplayandlayout.m_rectangleWindow;

            debug() << "Detected as m_windowdisplayandlayout.m_rectangleNormal (1) : " << m_windowdisplayandlayout.m_rectangleNormal;

            edisplay = ::e_display_normal;

            debug() << "Detected at box::_on_configure_notify_unlocked() as e_display_normal";

         }

         if (layout().m_statea[::user::e_layout_sketch].m_edisplay != edisplay)
         {

            information() << "Changing user interaction state from \"" <<
               ::as_string(layout().m_statea[::user::e_layout_sketch].m_edisplay) <<
               "\" to \"" << ::as_string(edisplay) << "\".";

            layout().m_statea[::user::e_layout_sketch].m_edisplay = edisplay;
            layout().m_statea[::user::e_layout_lading].m_edisplay = edisplay;
            layout().m_statea[::user::e_layout_layout].m_edisplay = edisplay;
            layout().m_statea[::user::e_layout_design].m_edisplay = edisplay;
            layout().m_statea[::user::e_layout_output].m_edisplay = edisplay;
            layout().m_statea[::user::e_layout_window].m_edisplay = edisplay;
            layout().m_statea[::user::e_layout_normal].m_edisplay = edisplay;

         }

         // layout().m_statea[::user::e_layout_sketch].m_size = s;
         // layout().m_statea[::user::e_layout_lading].m_size = s;
         // layout().m_statea[::user::e_layout_layout].m_size = s;
         // layout().m_statea[::user::e_layout_design].m_size = s;
         // layout().m_statea[::user::e_layout_output].m_size = s;
         // layout().m_statea[::user::e_layout_window].m_size = s;
         // layout().m_statea[::user::e_layout_normal].m_size = s;


         //else
         //{

         //   if (m_windowdisplayandlayout.m_rectangleRestored.is_empty()
         //      || m_windowdisplayandlayout.m_rectangleRestored.size() == m_sizeRestoreCompact
         //      || m_windowdisplayandlayout.m_rectangleRestored.size() == m_sizeRestoreBroad)
         //   {

         //      m_windowdisplayandlayout.m_rectangleRestored = m_windowdisplayandlayout.m_rectangleWindow;

         //   }

         //}



      }

//                                  });

//#endif

   }


//   void box::_window_show_change_visibility_unlocked()
//   {
//
//      ::user::interaction::_window_show_change_visibility_unlocked();
//
//      m_windowdisplayandlayout.m_edisplay = const_layout().window().display();
//
//   }


   bool box::should_save_window_rectangle()
   {

#if defined(UNIVERSAL_WINDOWS) || defined(APPLE_IOS)

      return false;

#else

      return m_bSaveWindowRect && m_bEnableSaveWindowRect2;

#endif

   }


   void box::WindowDataSaveWindowRectangle()
   {

      bool bSave = false;

      if (should_save_window_rectangle())
      {

         if (const_layout().sketch().display() == ::e_display_none)
         {

            return;

         }

         defer_update_display();

         string strDataKey = get_data_key(window_data_key_modifier());

         save_window_display_and_layout(strDataKey);

      }

   }


   string box::window_data_key_modifier()
   {

      if (get_parent() != nullptr)
      {

         return m_strDisplay + ".child";

      }
      else
      {

         return m_strDisplay;

      }

   }


   bool box::WindowDataLoadWindowRectangle()
   {

      bool bLoad = false;

      defer_update_display();

      auto strDataKey = get_data_key(window_data_key_modifier());

      bLoad = load_window_display_and_layout(strDataKey);

      if (!bLoad)
      {

         at_end_of_scope
         {

            m_bLoadingWindowRectangle = false;

         };

         m_bLoadingWindowRectangle = true;

         ::collection::index iDisplay = good_restore(nullptr, {}, true, { ::user::e_activation_set_foreground, nullptr}, e_zorder_top, initial_restore_display());

         bool bRestore = iDisplay >= 0;

         if (bRestore)
         {

            set_need_layout();

            display();

         };

         return bRestore;

      }

      return bLoad;

   }




   bool box::FancyWindowDataLoadWindowRectangle(bool bForceRestore, bool bInitialFramePosition)
   {

      bool bLoad = false;

      defer_update_display();

      auto strDataKey = get_data_key(window_data_key_modifier());

      bLoad = FancyLoadWindowRectangle(strDataKey, bForceRestore, bInitialFramePosition);

      if (!bLoad)
      {

         at_end_of_scope
         {

            m_bLoadingWindowRectangle = false;

         };

         m_bLoadingWindowRectangle = true;

         ::collection::index iDisplay = good_restore(nullptr, {}, true, { ::user::e_activation_set_foreground, nullptr }, e_zorder_top, initial_restore_display());

         bool bRestore = iDisplay >= 0;

         if (!bRestore)
         {

            set_need_layout();

            display();

         };

         return bRestore;

      }

      return bLoad;

   }


   bool box::load_window_display_and_layout(const ::scoped_string & strDataKey)
   {

      if (!m_bAutomaticallyStoreWindowRectangle)
      {

         return false;

      }

      at_end_of_scope
      {

         m_bLoadingWindowRectangle = false;

      };

      m_bLoadingWindowRectangle = true;

      ::user::window_display_and_layout windowdisplayandlayout;

      ::pointer<::aura::application>papp = get_app();

      if (!papp->datastream()->get(strDataKey, windowdisplayandlayout))
      {

         return false;

      }

      m_windowdisplayandlayoutStore = windowdisplayandlayout;

      m_windowdisplayandlayout = m_windowdisplayandlayoutStore;

      ::string strRestoreTrace;
      strRestoreTrace.formatf(
          "Restore trace: load display=%d appearance=%d normal=(%d,%d,%d,%d) compact=(%d,%d,%d,%d) broad=(%d,%d,%d,%d)",
         (int)windowdisplayandlayout.m_edisplay, (int)windowdisplayandlayout.m_eappearance,
         windowdisplayandlayout.m_rectangleNormal.left, windowdisplayandlayout.m_rectangleNormal.top,
         windowdisplayandlayout.m_rectangleNormal.right, windowdisplayandlayout.m_rectangleNormal.bottom,
         windowdisplayandlayout.m_rectangleCompact.left, windowdisplayandlayout.m_rectangleCompact.top,
         windowdisplayandlayout.m_rectangleCompact.right, windowdisplayandlayout.m_rectangleCompact.bottom,
         windowdisplayandlayout.m_rectangleBroad.left, windowdisplayandlayout.m_rectangleBroad.top,
         windowdisplayandlayout.m_rectangleBroad.right, windowdisplayandlayout.m_rectangleBroad.bottom);
      information() << strRestoreTrace;

      auto edisplay = windowdisplayandlayout.m_edisplay;

      const_layout().sketch().appearance() = windowdisplayandlayout.m_eappearance;

      order(e_zorder_top);

      if (m_ewindowflag & e_window_flag_disable_window_placement_snapping)
      {

         if (is_docking_appearance(edisplay))
         {

            edisplay = e_display_normal;

         }

      }

      //if (!bForceRestore
      //   && (edisplay == e_display_zoomed
      //      || edisplay == e_display_full_screen
      //      || (edisplay == e_display_iconic && !bInitialFramePosition)))
      if (
         edisplay == e_display_zoomed
      || edisplay == e_display_full_screen
      || edisplay == e_display_iconic
      || equivalence_sink(edisplay) == e_display_normal
         )
      {

         ::e_display edisplayForRestore = edisplay;

         strRestoreTrace.formatf(
             "Restore trace: load apply display=%d normal=(%d,%d,%d,%d) compact=(%d,%d,%d,%d) broad=(%d,%d,%d,%d) sketch=(%d,%d,%d,%d)",
            (int)edisplayForRestore,
            windowdisplayandlayout.m_rectangleNormal.left, windowdisplayandlayout.m_rectangleNormal.top,
            windowdisplayandlayout.m_rectangleNormal.right, windowdisplayandlayout.m_rectangleNormal.bottom,
            windowdisplayandlayout.m_rectangleCompact.left, windowdisplayandlayout.m_rectangleCompact.top,
            windowdisplayandlayout.m_rectangleCompact.right, windowdisplayandlayout.m_rectangleCompact.bottom,
            windowdisplayandlayout.m_rectangleBroad.left, windowdisplayandlayout.m_rectangleBroad.top,
            windowdisplayandlayout.m_rectangleBroad.right, windowdisplayandlayout.m_rectangleBroad.bottom,
            const_layout().sketch().parent_raw_rectangle().left,
            const_layout().sketch().parent_raw_rectangle().top,
            const_layout().sketch().parent_raw_rectangle().right,
            const_layout().sketch().parent_raw_rectangle().bottom);
         information() << strRestoreTrace;

         information() << "user::box::load_window_display_and_layout " << edisplay;

         // Keep these boundaries visible when a window stops during restoration.
         auto traceRestore = [&](const char * stage)
         {
            information() << "window_restore: " << stage
               << " thread=" << (::iptr) ::current_itask()
               << " window=" << (::iptr) this
               << " display=" << edisplayForRestore;
         };

         information() << "window_restore: saved rectangles"
            << " thread=" << (::iptr) ::current_itask()
            << " window=" << (::iptr) this
            << " normal=" << windowdisplayandlayout.m_rectangleNormal
            << " compact=" << windowdisplayandlayout.m_rectangleCompact
            << " broad=" << windowdisplayandlayout.m_rectangleBroad;

         switch(edisplayForRestore.m_cflag)
         {
            case e_display_compact:
               traceRestore("before place compact");
               place(windowdisplayandlayout.m_rectangleCompact);
               traceRestore("after place compact");
               strRestoreTrace.formatf("Restore trace: load placed mode=compact rect=(%d,%d,%d,%d)",
                  windowdisplayandlayout.m_rectangleCompact.left, windowdisplayandlayout.m_rectangleCompact.top,
                  windowdisplayandlayout.m_rectangleCompact.right, windowdisplayandlayout.m_rectangleCompact.bottom);
               information() << strRestoreTrace;
               break;
            case e_display_broad:
               traceRestore("before place broad");
               place(windowdisplayandlayout.m_rectangleBroad);
               traceRestore("after place broad");
               strRestoreTrace.formatf("Restore trace: load placed mode=broad rect=(%d,%d,%d,%d)",
                  windowdisplayandlayout.m_rectangleBroad.left, windowdisplayandlayout.m_rectangleBroad.top,
                  windowdisplayandlayout.m_rectangleBroad.right, windowdisplayandlayout.m_rectangleBroad.bottom);
               information() << strRestoreTrace;
               break;
            default:
               traceRestore("before place normal");
               place(windowdisplayandlayout.m_rectangleNormal);
               traceRestore("after place normal");
               strRestoreTrace.formatf("Restore trace: load placed mode=normal rect=(%d,%d,%d,%d)",
                  windowdisplayandlayout.m_rectangleNormal.left, windowdisplayandlayout.m_rectangleNormal.top,
                  windowdisplayandlayout.m_rectangleNormal.right, windowdisplayandlayout.m_rectangleNormal.bottom);
               information() << strRestoreTrace;
               edisplayForRestore = e_display_normal;
               break;

         }

         traceRestore("before display");
         display(edisplayForRestore);
         traceRestore("after display");

         return true;

         //auto rectangleWindow = window_rectangle();

         //good_restore(nullptr, rectangleWindow, true, ::user::e_activation_default, e_zorder_top, edisplayForRestore);

         //display(edisplay);

      }
      else if (is_docking_appearance(edisplay)
         && windowing()->display()->would_be_docked(windowdisplayandlayout.m_rectangleSnapped))
      {

         place(windowdisplayandlayout.m_rectangleSnapped);

         display(edisplay);

         return true;

      }
      else
      {

         return false;

///*         auto functionGoodRestore = [this, windowrectangle]()
//         {
//
//            good_restore(nullptr, windowrectangle.XXXm_rectangleRestored, true, ::user::e_activation_default, e_zorder_top, windowrectangle.m_edisplay);
//
//         };
//
//         if (m_ewindowflag & e_window_flag_window_created)
//         {
//
//            send_procedure(functionGoodRestore);
//
//         }
//         else
//         {
//
//            functionGoodRestore();
//
//         */}//

      }

      return false;

   }


   bool box::FancyLoadWindowRectangle(const ::scoped_string & strDataKey, bool bForceRestore, bool bInitialFramePosition)
   {

      if (!m_bAutomaticallyStoreWindowRectangle)
      {

         return false;

      }

      at_end_of_scope
      {

         m_bLoadingWindowRectangle = false;

      };

      m_bLoadingWindowRectangle = true;

      ::user::window_display_and_layout windowdisplayandlayout;

      ::pointer<::aura::application>papp = get_app();

      if (!papp->datastream()->get(strDataKey, windowdisplayandlayout))
      {

         return false;

      }

      m_windowdisplayandlayoutStore = windowdisplayandlayout;

      m_windowdisplayandlayout = m_windowdisplayandlayoutStore;

      auto edisplay = windowdisplayandlayout.m_edisplay;

      const_layout().sketch().appearance() = windowdisplayandlayout.m_eappearance;

      if (edisplay == e_display_iconic && bInitialFramePosition)
      {

         edisplay = windowdisplayandlayout.m_edisplayPrevious;

      }

      order(e_zorder_top);

      if (m_ewindowflag & e_window_flag_disable_window_placement_snapping)
      {

         if (is_docking_appearance(edisplay))
         {

            edisplay = e_display_normal;

         }

      }

      if(!bForceRestore
         && (edisplay == e_display_zoomed
         || edisplay == e_display_full_screen
         || (edisplay == e_display_iconic && !bInitialFramePosition)))
      {

//         if(bInitialFramePosition)
//         {
//
//            display( edisplay);
//
//         }

         //place(windowrectangle.m_rectangleWindow);

         display(edisplay);

      }
      else if (!bForceRestore && is_docking_appearance(edisplay))
      {

         place(windowdisplayandlayout.m_rectangleSnapped);

         display(edisplay);

      }
      else
      {
         
         auto functionGoodRestore = [this, windowdisplayandlayout]()
         {

            information() << "FancyLoadWindowRectangle windowrectangle.m_rectangleNormal " << windowdisplayandlayout.m_rectangleNormal;

            good_restore(nullptr, windowdisplayandlayout.m_rectangleNormal, true, { ::user::e_activation_default, nullptr}, e_zorder_top, windowdisplayandlayout.m_edisplay);
               
         };
         
         if(m_ewindowflag & e_window_flag_window_created)
         {
            
            user_send(functionGoodRestore);
            
         }
         else
         {
            
            functionGoodRestore();
            
         }

      }

      return true;

   }


   void box::save_window_display_and_layout(const ::scoped_string & strDataKey)
   {

      if (!m_bAutomaticallyStoreWindowRectangle)
      {

         return;

      }

      if (m_windowdisplayandlayout.m_edisplay == ::e_display_none)
      {

         return;

      }

      // Full-screen startup is an app presentation choice, not a restored
      // window size. Keep the last persisted normal/broad/compact rectangles.
      if (layout().is_full_screen() || layout().is_zoomed())
      {

         ::string strRestoreTrace;
         strRestoreTrace.formatf(
             "Restore trace: save skipped full_screen=%d zoomed=%d sketch=%d lading=%d layout=%d design=%d output=%d window=%d",
            (int)layout().is_full_screen(), (int)layout().is_zoomed(),
            (int)layout().sketch().display(),
            (int)layout().lading().display(), (int)layout().layout().display(),
            (int)layout().design().display(), (int)layout().output().display(),
            (int)layout().window().display());
         information() << strRestoreTrace;

         return;

      }

      if (m_windowdisplayandlayoutStore.m_edisplay == e_display_undefined)
      {

         ::cast < ::database::client > pdatabaseclient = get_app();

         if(pdatabaseclient)
         {

            pdatabaseclient->datastream()->get(strDataKey, m_windowdisplayandlayoutStore);

         }

      }
      
      m_windowdisplayandlayoutStore = m_windowdisplayandlayout;

      ::string strRestoreTrace;
      strRestoreTrace.formatf(
          "Restore trace: save display=%d window=(%d,%d,%d,%d) normal=(%d,%d,%d,%d) compact=(%d,%d,%d,%d) broad=(%d,%d,%d,%d)",
         (int)m_windowdisplayandlayout.m_edisplay,
         m_windowdisplayandlayout.m_rectangleWindow.left, m_windowdisplayandlayout.m_rectangleWindow.top,
         m_windowdisplayandlayout.m_rectangleWindow.right, m_windowdisplayandlayout.m_rectangleWindow.bottom,
         m_windowdisplayandlayout.m_rectangleNormal.left, m_windowdisplayandlayout.m_rectangleNormal.top,
         m_windowdisplayandlayout.m_rectangleNormal.right, m_windowdisplayandlayout.m_rectangleNormal.bottom,
         m_windowdisplayandlayout.m_rectangleCompact.left, m_windowdisplayandlayout.m_rectangleCompact.top,
         m_windowdisplayandlayout.m_rectangleCompact.right, m_windowdisplayandlayout.m_rectangleCompact.bottom,
         m_windowdisplayandlayout.m_rectangleBroad.left, m_windowdisplayandlayout.m_rectangleBroad.top,
         m_windowdisplayandlayout.m_rectangleBroad.right, m_windowdisplayandlayout.m_rectangleBroad.bottom);
      information() << strRestoreTrace;

//      auto windowrect = m_windowdisplayandlayoutStore;
//
//      bool bGot = m_windowdisplayandlayoutStore.m_edisplay != e_display_undefined;
//
//      windowrect.m_edisplay = const_layout().sketch().display();
//
//      windowrect.m_eappearance = const_layout().sketch().appearance();
//
//      window_rectangle(windowrect.m_rectangleWindow, e_layout_sketch);
//
//      auto edisplay = windowrect.m_edisplay;
//
//      if (bGot &&
//            (edisplay == ::e_display_zoomed
//             || edisplay == ::e_display_full_screen
//             || edisplay == ::e_display_iconic))
//      {
//
//      }
//      else if (bGot && is_docking_appearance(windowrect.m_edisplay))
//      {
//
//         windowrect.m_rectangleSnapped = windowrect.m_rectangleWindow;
//
//      }
//      else if (windowrect.m_rectangleWindow.size() == m_rectangleRestoreCompact.size())
//      {
//
//         windowrect.m_rectangleCompact = windowrect.m_rectangleWindow;
//
//         windowrect.m_edisplay = e_display_compact;
//
//      }
//      else if (windowrect.m_rectangleWindow.size() == m_rectangleRestoreBroad.size())
//      {
//
//         windowrect.m_rectangleBroad = windowrect.m_rectangleWindow;
//
//         windowrect.m_edisplay = e_display_broad;
//
//      }
//      else
//      {
//
//         windowrect.m_rectangleNormal = windowrect.m_rectangleWindow;
//
//         windowrect.m_edisplay = e_display_normal;
//
//      }
//
//      if (windowrect.m_rectangleNormal.width() < get_window_minimum_size().cx
//         || windowrect.m_rectangleNormal.height() < get_window_minimum_size().cy)
//      {
//
//         if (windowrect.m_rectangleWindow.width() > get_window_minimum_size().cx
//            && windowrect.m_rectangleWindow.height() > get_window_minimum_size().cy)
//         {
//
//            windowrect.m_rectangleNormal = windowrect.m_rectangleWindow;
//
//         }
//
//      }

      ::pointer<::aura::application>papp = get_app();

      papp->datastream()->set(strDataKey, m_windowdisplayandlayoutStore);
      //{

      //   return false;

      //}

      //m_windowdisplayandlayoutStore = windowrect;

      //return true;

   }


   ::i32_rectangle box::get_window_normal_stored_rectangle()
   {

      return m_windowdisplayandlayout.m_rectangleNormal;

   }


   ::i32_rectangle box::get_window_broad_stored_rectangle()
   {

      return m_windowdisplayandlayout.m_rectangleBroad;

   }


   ::i32_rectangle box::get_window_compact_stored_rectangle()
   {

      return m_windowdisplayandlayout.m_rectangleCompact;
   
   }


   void box::set_window_normal_stored_rectangle(const ::i32_rectangle & rectangle)
   {

      m_windowdisplayandlayout.m_rectangleNormal = rectangle;

   }


   void box::display_normal(::e_display edisplay, const ::user::activation & useractivation)
   {

#ifdef INFO_LAYOUT_DISPLAY

      information() << "interaction_layout::display_normal";

#endif

      if (is_frame_window())
      {

         auto edisplayRequested = edisplay;

         if (equivalence_sink(edisplay) != e_display_normal)
         {

            edisplay = e_display_normal;

         }
         
         auto rectangleSketch = const_layout().sketch().parent_raw_rectangle();

         auto rectangleStored = edisplay == e_display_broad
            ? m_windowdisplayandlayout.m_rectangleBroad
            : edisplay == e_display_compact
               ? m_windowdisplayandlayout.m_rectangleCompact
               : m_windowdisplayandlayout.m_rectangleNormal;

         ::string strRestoreTrace;
         strRestoreTrace.formatf(
             "Restore trace: choose requested=%d stored_mode=%d normal=(%d,%d,%d,%d) compact=(%d,%d,%d,%d) broad=(%d,%d,%d,%d) sketch=(%d,%d,%d,%d) selected=(%d,%d,%d,%d)",
            (int)edisplayRequested, (int)edisplay,
            m_windowdisplayandlayout.m_rectangleNormal.left, m_windowdisplayandlayout.m_rectangleNormal.top,
            m_windowdisplayandlayout.m_rectangleNormal.right, m_windowdisplayandlayout.m_rectangleNormal.bottom,
            m_windowdisplayandlayout.m_rectangleCompact.left, m_windowdisplayandlayout.m_rectangleCompact.top,
            m_windowdisplayandlayout.m_rectangleCompact.right, m_windowdisplayandlayout.m_rectangleCompact.bottom,
            m_windowdisplayandlayout.m_rectangleBroad.left, m_windowdisplayandlayout.m_rectangleBroad.top,
            m_windowdisplayandlayout.m_rectangleBroad.right, m_windowdisplayandlayout.m_rectangleBroad.bottom,
            rectangleSketch.left, rectangleSketch.top, rectangleSketch.right, rectangleSketch.bottom,
            rectangleStored.left, rectangleStored.top, rectangleStored.right, rectangleStored.bottom);
         information() << strRestoreTrace;

         ::i32_rectangle rectangleWorkspace;

         if (calculate_broad_and_compact_restore(&rectangleWorkspace, {},
            rectangleStored.is_empty() ? rectangleSketch : rectangleStored) >= 0)
         {

            auto sizeMin = get_window_minimum_size();
            auto sizeMaximum = sizeMin.maximum(rectangleWorkspace.size() * 9 / 10);

            bool bWrongModeSize = edisplay == e_display_broad
               ? !(rectangleStored.size() >= sizeMin.maximum(rectangleWorkspace.size() * 7 / 10))
               : edisplay == e_display_compact
                  && !(rectangleStored.size() <= sizeMin.maximum(rectangleWorkspace.size() / 2));

            bool bOutsideWorkspace = rectangleStored.left < rectangleWorkspace.left
               || rectangleStored.top < rectangleWorkspace.top
               || rectangleStored.right > rectangleWorkspace.right
               || rectangleStored.bottom > rectangleWorkspace.bottom;

            if (!(rectangleStored.size() >= sizeMin)
               || !(rectangleStored.size() <= sizeMaximum) || bWrongModeSize || bOutsideWorkspace)
            {

               ::string strRestoreTrace;
               strRestoreTrace.formatf(
                   "Restore trace: repairing requested_mode=%d stored=(%d,%d,%d,%d) workspace=(%d,%d,%d,%d) minimum=%dx%d maximum=%dx%d wrong_mode_size=%d outside_workspace=%d",
                  (int)edisplay,
                  rectangleStored.left, rectangleStored.top, rectangleStored.right, rectangleStored.bottom,
                  rectangleWorkspace.left, rectangleWorkspace.top, rectangleWorkspace.right, rectangleWorkspace.bottom,
                  sizeMin.cx, sizeMin.cy, sizeMaximum.cx, sizeMaximum.cy,
                  (int)bWrongModeSize, (int)bOutsideWorkspace);
               information() << strRestoreTrace;

               auto default_rectangle = [&](int numerator)
               {

                  ::i32_rectangle rectangleDefault;
                  rectangleDefault.set_size(sizeMin.maximum(rectangleWorkspace.size() * numerator / 5));
                  rectangleDefault.move_to(rectangleWorkspace.top_left()
                     + (rectangleWorkspace.size() - rectangleDefault.size()) / 2);
                  return rectangleDefault;

               };

                // Repair the requested slot with its own default. Switching to
                // a different mode based on stale dimensions breaks restore
                // cycling (for example, broad can unexpectedly become compact).
                auto iDefaultNumerator = edisplay == e_display_broad ? 4
                   : edisplay == e_display_compact ? 2 : 3;
                auto rectangleChosen = default_rectangle(iDefaultNumerator);

                // Record the chosen default immediately; configure notifications
                // should not be required to repair the stored restore preset.
                if (edisplay == e_display_broad)
                   m_windowdisplayandlayout.m_rectangleBroad = rectangleChosen;
                else if (edisplay == e_display_compact)
                   m_windowdisplayandlayout.m_rectangleCompact = rectangleChosen;
                else
                   m_windowdisplayandlayout.m_rectangleNormal = rectangleChosen;

               strRestoreTrace.formatf(
                    "Restore trace: repaired requested_mode=%d chosen=(%d,%d,%d,%d)",
                  (int)edisplay, rectangleChosen.left, rectangleChosen.top,
                  rectangleChosen.right, rectangleChosen.bottom);
               information() << strRestoreTrace;

            }

         }


         if (edisplay == e_display_broad)
         {
            
            auto rectangle = m_windowdisplayandlayout.m_rectangleBroad.is_empty() ? rectangleSketch : m_windowdisplayandlayout.m_rectangleBroad;

            ::i32_rectangle rectanglePlaced;

            m_iRestoreDiagnosticConfigureCount = 4;

            information() << "display_normal m_windowdisplayandlayout.m_rectangleBroad : " << m_windowdisplayandlayout.m_rectangleBroad << ", rectangleSketch : " << rectangleSketch;

            good_restore(&rectanglePlaced, rectangle, true, useractivation, e_zorder_top, e_display_broad);

            ::string strRestoreTrace;
            strRestoreTrace.formatf(
                "Restore trace: applied mode=broad input=(%d,%d,%d,%d) placed=(%d,%d,%d,%d)",
               rectangle.left, rectangle.top, rectangle.right, rectangle.bottom,
               rectanglePlaced.left, rectanglePlaced.top, rectanglePlaced.right, rectanglePlaced.bottom);
            information() << strRestoreTrace;

            m_windowdisplayandlayout.m_rectangleBroad = rectanglePlaced;

         }
         else if (edisplay == e_display_compact)
         {

            auto rectangle = m_windowdisplayandlayout.m_rectangleCompact.is_empty() ? rectangleSketch : m_windowdisplayandlayout.m_rectangleCompact;

            ::i32_rectangle rectanglePlaced;

            m_iRestoreDiagnosticConfigureCount = 4;

            information() << "display_normal m_windowdisplayandlayout.m_rectangleCompact : " << m_windowdisplayandlayout.m_rectangleCompact << ", rectangleSketch : " << rectangleSketch;

            good_restore(&rectanglePlaced, rectangle, true, useractivation, e_zorder_top, e_display_compact);

            ::string strRestoreTrace;
            strRestoreTrace.formatf(
                "Restore trace: applied mode=compact input=(%d,%d,%d,%d) placed=(%d,%d,%d,%d)",
               rectangle.left, rectangle.top, rectangle.right, rectangle.bottom,
               rectanglePlaced.left, rectanglePlaced.top, rectanglePlaced.right, rectanglePlaced.bottom);
            information() << strRestoreTrace;

            m_windowdisplayandlayout.m_rectangleCompact = rectanglePlaced;

         }
         else
         {

            auto rectangle = m_windowdisplayandlayout.m_rectangleNormal.is_empty() ? rectangleSketch : m_windowdisplayandlayout.m_rectangleNormal;

            ::i32_rectangle rectanglePlaced;

            m_iRestoreDiagnosticConfigureCount = 4;

            information() << "display_normal m_windowdisplayandlayout.m_rectangleNormal : " << m_windowdisplayandlayout.m_rectangleNormal << ", rectangleSketch : " << rectangleSketch;

            good_restore(&rectanglePlaced, rectangle, true, useractivation, e_zorder_top, e_display_normal);

            ::string strRestoreTrace;
            strRestoreTrace.formatf(
                "Restore trace: applied mode=normal input=(%d,%d,%d,%d) placed=(%d,%d,%d,%d)",
               rectangle.left, rectangle.top, rectangle.right, rectangle.bottom,
               rectanglePlaced.left, rectanglePlaced.top, rectanglePlaced.right, rectanglePlaced.bottom);
            information() << strRestoreTrace;

            m_windowdisplayandlayout.m_rectangleNormal = rectanglePlaced;

         }

         defer_save_window_placement();

      }
      else
      {

         set_display(edisplay);

         set_activation(useractivation);

      }

      {

         auto edisplayNormal = layout().sketch().display();

         if (equivalence_sink(edisplayNormal) == e_display_normal)
         {

            m_windowdisplayandlayout.m_edisplayLastNormal = edisplayNormal;

         }

      }

   }


   void box::display_full_screen(::collection::index iMonitor, const ::user::activation & useractivation)
   {

      best_monitor(nullptr, const_layout().sketch().parent_raw_rectangle(), true, { ::user::e_activation_default, nullptr }, e_zorder_top);

   }



   //void box::display_stored_state()
   //{

   //   //::user::interaction::display_restored();

   //   //if(::equivalence_sink(m_edisplayStored, e_display_normal))
   //   //{
   //   ////if (!m_windowdisplayandlayout.m_rectangleRestored.is_empty())
   //   ////{

   //    //  place(m_windowdisplayandlayout.m_rectangleRestored);

   //      display(m_edisplayStored);

   //   //}

   //}


   //void box::display_restore()
   //{

   //   ::user::interaction::display_restore();
   //   
   //   //auto edisplayPrevious = m_windowdisplayandlayout.m_edisplayPrevious;
   //   //
   //   //if(edisplayPrevious == e_display_restore)
   //   //{
   //   //   
   //   //   display(e_display_normal);
   //   //   
   //   //}
   //   //else if (!::is_visible(edisplayPrevious))
   //   //{

   //   //   layout().sketch().display() = e_display_restore;

   //   //}
   //   //else
   //   //{
   //   //
   //   //   display(edisplayPrevious);
   //   //   
   //   //}
   //   
   //}


   void box::design_window_iconic()
   {
      
      ::user::interaction::design_window_iconic();
      
   }


   void box::design_window_normal(::e_display edisplay)
   {

      ::user::interaction::design_window_normal(edisplay);

   }


   string box::calculate_display()
   {

      //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      string strDisplay;

      //i32_rectangle rectangleNormal;

      //get_rect_normal(rectangleNormal);

      ::i32_rectangle rectangleMainMonitor;


      auto pdisplay = windowing()->display();

      pdisplay->get_main_monitor(rectangleMainMonitor);

      strDisplay.formatf("Display(%d, %d)", rectangleMainMonitor.width(), rectangleMainMonitor.height());

      return strDisplay;

   }


   bool box::does_display_match()
   {

      single_lock synchronouslock(synchronization(), true);

      if (m_strDisplay.is_empty())
         return false;

      return m_strDisplay == calculate_display();

   }


   void box::defer_update_display()
   {

      //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_strDisplay = calculate_display();

   }




   void box::on_command(::message::command * pcommand)
   {

      ::user::interaction::on_command(pcommand);

   }


   bool box::on_before_set_parent(::user::interaction_base * puiParent)
   {

      if (!::user::interaction::on_before_set_parent(puiParent))
      {

         return false;

      }

      m_bEnableSaveWindowRect2 = false;

      return true;

   }


   bool box::on_set_parent(::user::interaction_base * puiParent)
   {

      if(!::user::interaction::on_set_parent(puiParent))
      {

         return false;

      }

      return true;

   }


   //bool box::is_local_data()
   //{

   //   return m_strDataKeyWindowRect.m_bLocalData;

   //}


   //bool box::parent_is_local_data()
   //{

   //   ::user::interaction * puiParent = get_parent();

   //   ::pointer<::database::client>pclient = puiParent;

   //   if(pclient.is_set())
   //   {

   //      if(pclient->is_local_data())
   //      {

   //         return true;

   //      }
   //      else
   //      {

   //         return false;

   //      }

   //   }

   //   return false;

   //}


   //bool box::is_local_data()
   //{

   //   if(::database::client::is_local_data())
   //   {

   //      return true;

   //   }

   //   if(parent_is_local_data())
   //   {

   //      return true;

   //   }

   //   return false;

   //}

   void box::on_simple_command(::message::simple_command * psimplecommand)
   {

      switch (psimplecommand->command())
      {
         case e_simple_command_load_window_rect:

            //WindowDataLoadWindowRectangle(psimplecommand->m_lparam != false);

            WindowDataLoadWindowRectangle();

            psimplecommand->m_bRet = true;

            break;

         default:

            break;

      }

      if (psimplecommand->m_bRet)
      {

         return;

      }

      ::user::interaction::on_simple_command(psimplecommand);

   }


   string box::get_display_tag()
   {

      return m_strDisplay;

   }


   //void box::set_restored_rectangle(const ::i32_rectangle & rectangleRestored)
   //{

   //   m_windowdisplayandlayout.m_rectangleNormal = rectangleRestored;

   //}


} // namespace user



