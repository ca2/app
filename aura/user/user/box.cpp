#include "framework.h"
#include "box.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"
#include "acme/parallelization/single_lock.h"
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

      MESSAGE_LINK(e_message_create, pchannel, this, &box::on_message_create);
      MESSAGE_LINK(e_message_size, pchannel, this, &box::on_message_size);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &box::on_message_show_window);

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


   void box::_on_configure_notify_unlocked(const ::int_rectangle & rectangle)
   {

      ::user::interaction::_on_configure_notify_unlocked(rectangle);

//#if !defined(UNIVERSAL_WINDOWS)

      //user_post([this]()
                                  //{

      auto & edisplay = layout().design().display();

      m_windowdisplayandlayout.m_edisplay = const_layout().window().display();

      //window_rectangle(m_windowdisplayandlayout.m_rectangleWindow, e_layout_design);

      m_windowdisplayandlayout.m_rectangleWindow = rectangle;

      if (is_docking_appearance(edisplay))
      {

         m_windowdisplayandlayout.m_rectangleSnapped = m_windowdisplayandlayout.m_rectangleWindow;

      }
      else if (!layout().is_docking() && (system()->acme_windowing()->get_ewindowing() != ::windowing::e_windowing_wayland) && is_equivalent_in_equivalence_sink(edisplay, e_display_normal))
      {

         calculate_broad_and_compact_restore();

         ::e_display edisplay = ::e_display_undefined;

         if (m_windowdisplayandlayout.m_rectangleWindow.size() >= m_rectangleRestoreBroad.size() * 0.8)
         {

            m_windowdisplayandlayout.m_rectangleBroad = m_windowdisplayandlayout.m_rectangleWindow;

            information() << "m_windowdisplayandlayout.m_rectangleBroad (1) : " << m_windowdisplayandlayout.m_rectangleBroad;

            edisplay = ::e_display_broad;

            information() << "box::_on_configure_notify_unlocked() : e_display_broad";

         }
         else if (m_windowdisplayandlayout.m_rectangleWindow.size() <= m_rectangleRestoreCompact.size() * 1.125)
         {

            m_windowdisplayandlayout.m_rectangleCompact = m_windowdisplayandlayout.m_rectangleWindow;

            information() << "m_windowdisplayandlayout.m_rectangleCompact (1) : " << m_windowdisplayandlayout.m_rectangleCompact;

            edisplay = ::e_display_compact;

            information() << "box::_on_configure_notify_unlocked() : e_display_compact";

         }
         else
         {

            m_windowdisplayandlayout.m_rectangleNormal = m_windowdisplayandlayout.m_rectangleWindow;

            information() << "m_windowdisplayandlayout.m_rectangleNormal (1) : " << m_windowdisplayandlayout.m_rectangleNormal;

            edisplay = ::e_display_normal;

            information() << "box::_on_configure_notify_unlocked() : e_display_normal";

         }


         layout().m_statea[::user::e_layout_sketch].m_edisplay = edisplay;
         layout().m_statea[::user::e_layout_lading].m_edisplay = edisplay;
         layout().m_statea[::user::e_layout_layout].m_edisplay = edisplay;
         layout().m_statea[::user::e_layout_design].m_edisplay = edisplay;
         layout().m_statea[::user::e_layout_output].m_edisplay = edisplay;
         layout().m_statea[::user::e_layout_window].m_edisplay = edisplay;
         layout().m_statea[::user::e_layout_normal].m_edisplay = edisplay;

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

      enum_display edisplay = windowdisplayandlayout.m_edisplay;

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

         information() << "user::box::load_window_display_and_layout " << edisplay;

         switch(edisplayForRestore)
         {
            case e_display_compact:
               place(windowdisplayandlayout.m_rectangleCompact);
               break;
            case e_display_broad:
               place(windowdisplayandlayout.m_rectangleBroad);
               break;
            default:
               place(windowdisplayandlayout.m_rectangleNormal);
               edisplayForRestore = e_display_normal;
               break;

         }

         display(edisplayForRestore);

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

      enum_display edisplay = windowdisplayandlayout.m_edisplay;

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

      if (m_windowdisplayandlayoutStore.m_edisplay == e_display_undefined)
      {

         ::cast < ::database::client > pdatabaseclient = get_app();

         if(pdatabaseclient)
         {

            pdatabaseclient->datastream()->get(strDataKey, m_windowdisplayandlayoutStore);

         }

      }
      
      m_windowdisplayandlayoutStore = m_windowdisplayandlayout;

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
//      if (windowrect.m_rectangleNormal.width() < get_window_minimum_size().cx()
//         || windowrect.m_rectangleNormal.height() < get_window_minimum_size().cy())
//      {
//
//         if (windowrect.m_rectangleWindow.width() > get_window_minimum_size().cx()
//            && windowrect.m_rectangleWindow.height() > get_window_minimum_size().cy())
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


   ::int_rectangle box::get_window_normal_stored_rectangle()
   {

      return m_windowdisplayandlayout.m_rectangleNormal;

   }


   ::int_rectangle box::get_window_broad_stored_rectangle()
   {

      return m_windowdisplayandlayout.m_rectangleBroad;

   }


   ::int_rectangle box::get_window_compact_stored_rectangle()
   {

      return m_windowdisplayandlayout.m_rectangleCompact;
   
   }


   void box::set_window_normal_stored_rectangle(const ::int_rectangle & rectangle)
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

         if (equivalence_sink(edisplay) != e_display_normal)
         {

            edisplay = e_display_normal;

         }
         
         auto rectangleSketch = const_layout().sketch().parent_raw_rectangle();

         if (edisplay == e_display_broad)
         {
            
            auto rectangle = m_windowdisplayandlayout.m_rectangleBroad.is_empty() ? rectangleSketch : m_windowdisplayandlayout.m_rectangleBroad;

            information() << "display_normal m_windowdisplayandlayout.m_rectangleBroad : " << m_windowdisplayandlayout.m_rectangleBroad << ", rectangleSketch : " << rectangleSketch;

            good_restore(nullptr, rectangle, true, useractivation, e_zorder_top, e_display_broad);

         }
         else if (edisplay == e_display_compact)
         {

            auto rectangle = m_windowdisplayandlayout.m_rectangleCompact.is_empty() ? rectangleSketch : m_windowdisplayandlayout.m_rectangleCompact;

            information() << "display_normal m_windowdisplayandlayout.m_rectangleCompact : " << m_windowdisplayandlayout.m_rectangleCompact << ", rectangleSketch : " << rectangleSketch;

            good_restore(nullptr, rectangle, true, useractivation, e_zorder_top, e_display_compact);

         }
         else
         {

            auto rectangle = m_windowdisplayandlayout.m_rectangleNormal.is_empty() ? rectangleSketch : m_windowdisplayandlayout.m_rectangleNormal;

            information() << "display_normal m_windowdisplayandlayout.m_rectangleNormal : " << m_windowdisplayandlayout.m_rectangleNormal << ", rectangleSketch : " << rectangleSketch;

            good_restore(nullptr, rectangle, true, useractivation, e_zorder_top, e_display_normal);

         }

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

      //synchronous_lock synchronouslock(this->synchronization());

      string strDisplay;

      //int_rectangle rectangleNormal;

      //get_rect_normal(rectangleNormal);

      ::int_rectangle rectangleMainMonitor;


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

      //synchronous_lock synchronouslock(this->synchronization());

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


   //void box::set_restored_rectangle(const ::int_rectangle & rectangleRestored)
   //{

   //   m_windowdisplayandlayout.m_rectangleNormal = rectangleRestored;

   //}


} // namespace user



