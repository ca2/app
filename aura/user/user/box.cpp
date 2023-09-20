#include "framework.h"
#include "box.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"
#include "acme/parallelization/single_lock.h"
#include "acme/platform/scoped_restore.h"
#include "acme/platform/keep.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "acme/user/user/_text_stream.h"
#include "apex/database/_binary_stream.h"
#include "apex/message/simple_command.h"
#include "aura/platform/application.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "aura/windowing/monitor.h"


namespace user
{


   box::box()
   {

      m_windowrectangleStore.m_edisplay = ::e_display_undefined;

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

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &box::on_message_create);
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

      UNREFERENCED_PARAMETER(pmessage);

   }


   ::e_display box::window_stored_display()
   {

      auto edisplayStored = m_windowrectangle.m_edisplay;

      return edisplayStored;

   }


   ::e_display box::window_previous_display()
   {

      auto edisplayPrevious = m_windowrectangle.m_edisplayPrevious;

      return edisplayPrevious;

   }


   void box::set_window_previous_display(::e_display edisplayPrevious)
   {

      m_windowrectangle.m_edisplayPrevious = edisplayPrevious;

   }


   void box::on_visual_applied()
   {

      ::user::interaction::on_visual_applied();

#if !defined(UNIVERSAL_WINDOWS)

      user_post([this]()
                                  {

      auto & edisplay = layout().design().display();

      window_rectangle(m_windowrectangle.m_rectangleWindow, e_layout_design);

      if (is_docking_appearance(edisplay))
      {

         m_windowrectangle.m_rectangleSnapped = m_windowrectangle.m_rectangleWindow;

      }
      else if (!layout().is_docking() && is_equivalent_in_equivalence_sink(edisplay, e_display_normal))
      {

         calculate_broad_and_compact_restore();

         if (m_windowrectangle.m_rectangleWindow.size() == m_rectangleRestoreBroad.size())
         {

            m_windowrectangle.m_rectangleBroad = m_windowrectangle.m_rectangleWindow;

         }
         else if (m_windowrectangle.m_rectangleWindow.size() == m_rectangleRestoreCompact.size())
         {

            m_windowrectangle.m_rectangleCompact = m_windowrectangle.m_rectangleWindow;

         }
         else
         {

            m_windowrectangle.m_rectangleNormal = m_windowrectangle.m_rectangleWindow;

         }
         //else
         //{

         //   if (m_windowrectangle.m_rectangleRestored.is_empty()
         //      || m_windowrectangle.m_rectangleRestored.size() == m_sizeRestoreCompact
         //      || m_windowrectangle.m_rectangleRestored.size() == m_sizeRestoreBroad)
         //   {

         //      m_windowrectangle.m_rectangleRestored = m_windowrectangle.m_rectangleWindow;

         //   }

         //}

      }

                                  });

#endif

   }


//   void box::_window_show_change_visibility_unlocked()
//   {
//
//      ::user::interaction::_window_show_change_visibility_unlocked();
//
//      m_windowrectangle.m_edisplay = const_layout().window().display();
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

         SaveWindowRectangle(strDataKey);

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

      bLoad = LoadWindowRectangle(strDataKey);

      if (!bLoad)
      {

         at_end_of_scope
         {

            m_bLoadingWindowRectangle = false;

         };

         m_bLoadingWindowRectangle = true;

         ::index iDisplay = good_restore(nullptr, {}, true, e_activation_default, e_zorder_top, initial_restore_display());

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

         ::index iDisplay = good_restore(nullptr, {}, true, e_activation_default, e_zorder_top, initial_restore_display());

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


   bool box::LoadWindowRectangle(const ::scoped_string & strDataKey)
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

      ::user::window_rectangle windowrectangle;

      ::pointer<::aura::application>papp = get_app();

      if (!papp->datastream()->get(strDataKey, windowrectangle))
      {

         return false;

      }

      m_windowrectangleStore = windowrectangle;

      m_windowrectangle = m_windowrectangleStore;

      enum_display edisplay = windowrectangle.m_edisplay;

      const_layout().sketch().appearance() = windowrectangle.m_eappearance;

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

         information() << "user::box::LoadWindowRectangle " << edisplay;

         switch(edisplayForRestore)
         {
            case e_display_compact:
               place(windowrectangle.m_rectangleCompact);
               break;
            case e_display_broad:
               place(windowrectangle.m_rectangleBroad);
               break;
            default:
               place(windowrectangle.m_rectangleNormal);
               edisplayForRestore = e_display_normal;
               break;

         }

         display(edisplayForRestore);

         return true;

         //auto rectangleWindow = window_rectangle();

         //good_restore(nullptr, rectangleWindow, true, e_activation_default, e_zorder_top, edisplayForRestore);

         //display(edisplay);

      }
      else if (is_docking_appearance(edisplay)
         && windowing()->display()->would_be_docked(windowrectangle.m_rectangleSnapped))
      {

         place(windowrectangle.m_rectangleSnapped);

         display(edisplay);

         return true;

      }
      else
      {

         return false;

///*         auto functionGoodRestore = [this, windowrectangle]()
//         {
//
//            good_restore(nullptr, windowrectangle.XXXm_rectangleRestored, true, e_activation_default, e_zorder_top, windowrectangle.m_edisplay);
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

      ::user::window_rectangle windowrectangle;

      ::pointer<::aura::application>papp = get_app();

      if (!papp->datastream()->get(strDataKey, windowrectangle))
      {

         return false;

      }

      m_windowrectangleStore = windowrectangle;

      m_windowrectangle = m_windowrectangleStore;

      enum_display edisplay = windowrectangle.m_edisplay;

      const_layout().sketch().appearance() = windowrectangle.m_eappearance;

      if (edisplay == e_display_iconic && bInitialFramePosition)
      {

         edisplay = windowrectangle.m_edisplayPrevious;

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

         place(windowrectangle.m_rectangleSnapped);

         display(edisplay);

      }
      else
      {
         
         auto functionGoodRestore = [this, windowrectangle]()
         {

            information() << "FancyLoadWindowRectangle windowrectangle.m_rectangleNormal " << windowrectangle.m_rectangleNormal;

            good_restore(nullptr, windowrectangle.m_rectangleNormal, true, e_activation_default, e_zorder_top, windowrectangle.m_edisplay);
               
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


   void box::SaveWindowRectangle(const ::scoped_string & strDataKey)
   {

      if (!m_bAutomaticallyStoreWindowRectangle)
      {

         return;

      }

      if (const_layout().sketch().display() == ::e_display_none)
      {

         return;

      }

      if (m_windowrectangleStore.m_edisplay == e_display_undefined)
      {

         auto papp = get_app();

         papp->datastream()->get(strDataKey, m_windowrectangleStore);

      }

      auto windowrect = m_windowrectangleStore;

      bool bGot = m_windowrectangleStore.m_edisplay != e_display_undefined;

      windowrect.m_edisplay = const_layout().sketch().display();

      windowrect.m_eappearance = const_layout().sketch().appearance();

      window_rectangle(windowrect.m_rectangleWindow, e_layout_sketch);

      auto edisplay = windowrect.m_edisplay;

      if (bGot &&
            (edisplay == ::e_display_zoomed
             || edisplay == ::e_display_full_screen
             || edisplay == ::e_display_iconic))
      {

      }
      else if (bGot && is_docking_appearance(windowrect.m_edisplay))
      {

         windowrect.m_rectangleSnapped = windowrect.m_rectangleWindow;

      }
      else if (windowrect.m_rectangleWindow.size() == m_rectangleRestoreCompact.size())
      {

         windowrect.m_rectangleCompact = windowrect.m_rectangleWindow;

         windowrect.m_edisplay = e_display_compact;

      }
      else if (windowrect.m_rectangleWindow.size() == m_rectangleRestoreBroad.size())
      {

         windowrect.m_rectangleBroad = windowrect.m_rectangleWindow;

         windowrect.m_edisplay = e_display_broad;

      }
      else
      {

         windowrect.m_rectangleNormal = windowrect.m_rectangleWindow;

         windowrect.m_edisplay = e_display_normal;

      }

      if (windowrect.m_rectangleNormal.width() < get_window_minimum_size().cx()
         || windowrect.m_rectangleNormal.height() < get_window_minimum_size().cy())
      {

         if (windowrect.m_rectangleWindow.width() > get_window_minimum_size().cx()
            && windowrect.m_rectangleWindow.height() > get_window_minimum_size().cy())
         {

            windowrect.m_rectangleNormal = windowrect.m_rectangleWindow;

         }

      }

      ::pointer<::aura::application>papp = get_app();

      papp->datastream()->set(strDataKey, windowrect);
      //{

      //   return false;

      //}

      m_windowrectangleStore = windowrect;

      //return true;

   }


   ::rectangle_i32 box::get_window_normal_stored_rectangle()
   {

      return m_windowrectangle.m_rectangleNormal;

   }


   ::rectangle_i32 box::get_window_broad_stored_rectangle()
   {

      return m_windowrectangle.m_rectangleBroad;

   }


   ::rectangle_i32 box::get_window_compact_stored_rectangle()
   {

      return m_windowrectangle.m_rectangleCompact;
   
   }


   void box::display_normal(::e_display edisplay, ::e_activation eactivation)
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
            
            auto rectangle = m_windowrectangle.m_rectangleBroad.is_empty() ? rectangleSketch : m_windowrectangle.m_rectangleBroad;

            information() << "display_normal m_windowrectangle.m_rectangleBroad : " << m_windowrectangle.m_rectangleBroad << ", rectangleSketch : " << rectangleSketch;

            good_restore(nullptr, rectangle, true, eactivation, e_zorder_top, e_display_broad);

         }
         else if (edisplay == e_display_compact)
         {

            auto rectangle = m_windowrectangle.m_rectangleCompact.is_empty() ? rectangleSketch : m_windowrectangle.m_rectangleCompact;

            information() << "display_normal m_windowrectangle.m_rectangleCompact : " << m_windowrectangle.m_rectangleCompact << ", rectangleSketch : " << rectangleSketch;

            good_restore(nullptr, rectangle, true, eactivation, e_zorder_top, e_display_compact);

         }
         else
         {

            auto rectangle = m_windowrectangle.m_rectangleNormal.is_empty() ? rectangleSketch : m_windowrectangle.m_rectangleNormal;

            information() << "display_normal m_windowrectangle.m_rectangleNormal : " << m_windowrectangle.m_rectangleNormal << ", rectangleSketch : " << rectangleSketch;

            good_restore(nullptr, rectangle, true, eactivation, e_zorder_top, e_display_normal);

         }

      }
      else
      {

         set_display(edisplay);

         set_activation(eactivation);

      }

      {

         auto edisplayNormal = layout().sketch().display();

         if (equivalence_sink(edisplayNormal) == e_display_normal)
         {

            m_windowrectangle.m_edisplayLastNormal = edisplayNormal;

         }

      }

   }


   void box::display_full_screen(::index iMonitor, ::e_activation eactivation)
   {

      best_monitor(nullptr, const_layout().sketch().parent_raw_rectangle(), true, e_activation_default, e_zorder_top);

   }



   //void box::display_stored_state()
   //{

   //   //::user::interaction::display_restored();

   //   //if(::equivalence_sink(m_edisplayStored, e_display_normal))
   //   //{
   //   ////if (!m_windowrectangle.m_rectangleRestored.is_empty())
   //   ////{

   //    //  place(m_windowrectangle.m_rectangleRestored);

   //      display(m_edisplayStored);

   //   //}

   //}


   //void box::display_restore()
   //{

   //   ::user::interaction::display_restore();
   //   
   //   //auto edisplayPrevious = m_windowrectangle.m_edisplayPrevious;
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

      //rectangle_i32 rectangleNormal;

      //get_rect_normal(rectangleNormal);

      ::rectangle_i32 rectangleMainMonitor;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      pdisplay->get_main_monitor(rectangleMainMonitor);

      strDisplay.format("Display(%d, %d)", rectangleMainMonitor.width(), rectangleMainMonitor.height());

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


   bool box::on_before_set_parent(::user::primitive * puiParent)
   {

      if (!::user::interaction::on_before_set_parent(puiParent))
      {

         return false;

      }

      m_bEnableSaveWindowRect2 = false;

      return true;

   }


   bool box::on_set_parent(::user::primitive * puiParent)
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


   //void box::set_restored_rectangle(const ::rectangle_i32 & rectangleRestored)
   //{

   //   m_windowrectangle.m_rectangleNormal = rectangleRestored;

   //}


} // namespace user



