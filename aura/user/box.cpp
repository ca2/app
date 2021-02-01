#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/message.h"
#include "apex/message/simple_command.h"
//#include "apex/platform/pred_procedure.h"


namespace user
{


   box::box()
   {

      m_databasekey.m_strDataKey = "WindowRect";

      m_databasekey.m_bLocalData = true;

      m_windowrectStore.m_edisplay = ::e_display_undefined;



   }


   box::~box()
   {

   }


   ::e_status box::initialize(::layered * pobjectContext)
   {

      auto estatus = interaction::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      if (m_id.is_empty())
      {

         m_id = type_name();

      }

      m_databasekey.m_strDataKey = m_id;

      return estatus;

   }




   void box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      //scroll::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &box::_001OnCreate);
      MESSAGE_LINK(e_message_size, pchannel, this, &box::_001OnSize);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &box::_001OnShowWindow);

   }


   void box::_001OnCreate(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

   }


   void box::_001OnSize(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void box::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   ::e_display box::window_stored_display() const
   {

      auto edisplayStored = m_windowrect.m_edisplay;

      return edisplayStored;

   }


   ::e_display box::window_previous_display() const
   {

      auto edisplayPrevious = m_windowrect.m_edisplayPrevious;

      return edisplayPrevious;

   }


   void box::on_visual_applied()
   {

      ::user::interaction::on_visual_applied();

      auto edisplay = layout().design().display();

      get_window_rect(m_windowrect.m_rectWindow, e_layout_design);

      if (is_docking_appearance(edisplay))
      {

         m_windowrect.m_rectSnapped = m_windowrect.m_rectWindow;

      }
      else if (is_equivalent(edisplay, e_display_normal))
      {

         calculate_broad_and_compact_restore();

         if (m_windowrect.m_rectWindow.size() != m_sizeRestoreBroad
            && m_windowrect.m_rectWindow.size() != m_sizeRestoreCompact)
         {

            if (m_windowrect.m_rectWindow.size() != m_windowrect.m_rectRestored.size())
            {

               m_windowrect.m_rectRestored = m_windowrect.m_rectWindow;

            }
            else if (m_windowrect.m_rectWindow != m_windowrect.m_rectRestored)
            {

               m_windowrect.m_rectRestored = m_windowrect.m_rectWindow;

            }

         }
         else
         {

            if (m_windowrect.m_rectRestored.is_empty()
               || m_windowrect.m_rectRestored.size() == m_sizeRestoreCompact
               || m_windowrect.m_rectRestored.size() == m_sizeRestoreBroad)
            {

               m_windowrect.m_rectRestored = m_windowrect.m_rectWindow;

            }

         }

      }

   }


   void box::window_show_change_visibility()
   {

      ::user::interaction::window_show_change_visibility();

      m_windowrect.m_edisplay = layout().window().display();

   }


   bool box::should_save_window_rect()
   {

#if defined(_UWP) || defined(APPLE_IOS)

      return false;

#else

      return m_bSaveWindowRect && m_bEnableSaveWindowRect2;

#endif

   }


   bool box::WindowDataSaveWindowRect()
   {

      bool bSave = false;

      if (should_save_window_rect())
      {

         if (layout().sketch().display() == ::e_display_none)
         {

            return false;

         }

         defer_update_display();

         bSave = SaveWindowRect_(m_databasekey + window_data_key_modifier());

      }

      return bSave;

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


   bool box::WindowDataLoadWindowRect(bool bForceRestore, bool bInitialFramePosition)
   {

      bool bLoad = false;

      defer_update_display();

      auto key = m_databasekey + window_data_key_modifier();

      bLoad = LoadWindowRect_(key, bForceRestore, bInitialFramePosition);

      if (!bLoad)
      {

         m_ewindowflag |= e_window_flag_loading_window_rect;

         //main_async([this]()
         //           {

         bool bRestore = good_restore(nullptr, nullptr, true, e_activation_default, zorder_top, initial_restore_display()) >= 0;

         if (!bRestore)
         {

            set_need_layout();

            display();

         }

//         });

         //bool bRestore = true;

         return bRestore;

      }

      return bLoad;

   }


   bool box::LoadWindowRect_(const ::database::key & key, bool bForceRestore, bool bInitialFramePosition)
   {

      if (!(m_ewindowflag & e_window_flag_auto_store_window_rect))
      {

         return false;

      }

      try
      {

         window_rect windowrect;

         if (!Application.data_get(key, windowrect))
         {

            return false;

         }

         m_ewindowflag |= e_window_flag_loading_window_rect;

         m_windowrectStore = windowrect;

         m_windowrect = m_windowrectStore;

         enum_display edisplay = windowrect.m_edisplay;

         layout().sketch().appearance() = windowrect.m_eappearance;

         if (edisplay == e_display_iconic && bInitialFramePosition)
         {

            edisplay = windowrect.m_edisplayPrevious;

         }

         order(zorder_top);

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

            if(bInitialFramePosition)
            {

               layout().sketch().display() = edisplay;

            }

            layout().sketch() = windowrect.m_rectWindow;

            layout().sketch() = edisplay;

            layout().sketch().set_ready();

         }
         else if (!bForceRestore && is_docking_appearance(edisplay))
         {

            if(bInitialFramePosition)
            {

               layout().sketch() = edisplay;

            }

            layout().sketch() = windowrect.m_rectSnapped;

            layout().sketch() = edisplay;

            layout().sketch().set_ready();

         }
         else
         {
            
            send_routine(__routine([this, windowrect]()
            {

               good_restore(nullptr, windowrect.m_rectRestored, true, e_activation_default, zorder_top, windowrect.m_edisplay);
               
            }));

         }

         return true;

      }
      catch (exception_pointer pe)
      {

         handle_exception(pe);

      }
      catch (...)
      {

      }

      return false;

   }


   bool box::SaveWindowRect_(const ::database::key & key)
   {

      if (!(m_ewindowflag & e_window_flag_auto_store_window_rect))
      {

         return false;

      }

      if (layout().sketch().display() == ::e_display_none)
      {

         return false;

      }

      if (m_windowrectStore.m_edisplay == e_display_undefined)
      {

         Application.data_get(key, m_windowrectStore);

      }

      auto windowrect = m_windowrectStore;

      bool bGot = m_windowrectStore.m_edisplay != e_display_undefined;

      windowrect.m_edisplay = layout().sketch().display();

      windowrect.m_eappearance = layout().sketch().appearance();

      get_window_rect(windowrect.m_rectWindow, e_layout_sketch);

      auto edisplay = windowrect.m_edisplay;

      if (bGot &&
            (edisplay == ::e_display_zoomed
             || edisplay == ::e_display_full_screen
             || edisplay == ::e_display_iconic))
      {

      }
      else if (bGot && is_docking_appearance(windowrect.m_edisplay))
      {

         windowrect.m_rectSnapped = windowrect.m_rectWindow;

      }
      else if (windowrect.m_rectWindow.size() == m_sizeRestoreCompact)
      {

         windowrect.m_edisplay = e_display_compact;

      }
      else if (windowrect.m_rectWindow.size() == m_sizeRestoreBroad)
      {

         windowrect.m_edisplay = e_display_broad;

      }
      else
      {

         windowrect.m_rectRestored = windowrect.m_rectWindow;

      }

      if (windowrect.m_rectRestored.width() < get_window_minimum_size().cx
         || windowrect.m_rectRestored.height() < get_window_minimum_size().cy)
      {

         if (windowrect.m_rectWindow.width() > get_window_minimum_size().cx
            && windowrect.m_rectWindow.height() > get_window_minimum_size().cy)
         {

            windowrect.m_rectRestored = windowrect.m_rectWindow;

         }

      }

      if (!Application.data_set(key, windowrect))
      {

         return false;

      }

      m_windowrectStore = windowrect;

      return true;

   }


   void box::sketch_prepare_window_restore(edisplay edisplay)
   {

      get_wnd()->post_routine(__routine([this, edisplay]()
      {

         good_restore(NULL, layout().sketch().screen_rect(), true, layout().sketch().activation(), layout().sketch().zorder(), edisplay);

      }));

   }


   string box::calc_display()
   {

      sync_lock sl(mutex());

      string strDisplay;

      //::rectangle_i32 rectNormal;

      //get_rect_normal(rectNormal);

      ::rectangle_i32 rectMainMonitor;

      auto psession = Session;

      psession->get_main_monitor(rectMainMonitor);

      strDisplay.Format("Display(%d, %d)", rectMainMonitor.width(), rectMainMonitor.height());

      return strDisplay;

   }

   bool box::does_display_match()
   {

      single_lock sl(mutex(), true);

      if (m_strDisplay.is_empty())
         return false;

      return m_strDisplay == calc_display();

   }


   void box::defer_update_display()
   {

      sync_lock sl(mutex());

      m_strDisplay = calc_display();

   }




   void box::on_command(::user::command * pcommand)
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

   //   return m_datakeyWindowRect.m_bLocalData;

   //}


   bool box::parent_is_local_data()
   {

      ::user::interaction * puiParent = get_parent();

      __pointer(::database::client) pclient = puiParent;

      if(pclient.is_set())
      {

         if(pclient->is_local_data())
         {

            return true;

         }
         else
         {

            return false;

         }

      }

      return false;

   }


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

      switch (psimplecommand->m_esimplecommand)
      {
         case simple_command_load_window_rect:

            WindowDataLoadWindowRect(psimplecommand->m_lparam != FALSE);

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


} // namespace user
















