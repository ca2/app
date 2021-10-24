#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/message.h"


namespace user
{


   box::box()
   {

      m_databasekey.m_strDataKey = "WindowRect";

      m_databasekey.m_bLocalData = true;

      m_windowrectangleStore.m_edisplay = ::e_display_undefined;

   }


   box::~box()
   {

   }


   ::e_status box::initialize(::object * pobject)
   {

      auto estatus = interaction::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      if (m_id.is_empty())
      {

         m_id = __type_name(this);

      }

      m_databasekey.m_strDataKey = m_id;

      return estatus;

   }




   void box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      //::user::scroll::install_message_routing(pchannel);

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

         if (layout().design().display() == ::e_display_none)
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

         bool bRestore = good_restore(nullptr, nullptr, true, e_activation_default, e_zorder_top, initial_restore_display()) >= 0;

         if (!bRestore)
         {

            set_need_layout();

            display();

         }

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

         window_rectangle windowrectangle;

         if (!papplication->data_get(key, windowrect))
         {

            return false;

         }

         m_ewindowflag |= e_window_flag_loading_window_rect;

         m_windowrectangleStore = windowrect;

         m_windowrectangle = m_windowrectangleStore;

         enum_display edisplay = windowrect.m_edisplay;

         set_appearance(windowrect.m_eappearance);

         if (edisplay == e_display_iconic && bInitialFramePosition)
         {

            edisplay = windowrect.m_edisplayPrevious;

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

            if(bInitialFramePosition)
            {

               ui_state().m_edisplay3 = edisplay;

            }

            place(windowrect.m_rectangleWindow);

            layout().sketch().m_edisplay3 = edisplay;

            m_bRequestReady = true;

         }
         else if (!bForceRestore && is_docking_appearance(edisplay))
         {

            if(bInitialFramePosition)
            {

               ui_state().m_edisplay3 = edisplay;

            }

            place(windowrect.m_rectangleSnapped);

            layout().sketch().m_edisplay3 = edisplay;

            m_bRequestReady = true;

         }
         else
         {

            good_restore(nullptr, windowrect.m_rectangleRestored, true, e_activation_default, e_zorder_top, windowrect.m_edisplay);

         }

         return true;

      }
      catch (const ::exception & exception)
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

      if (layout().design().display() == ::e_display_none)
      {

         return false;

      }

      if (m_windowrectangleStore.m_edisplay == e_display_undefined)
      {

         papplication->data_get(key, m_windowrectangleStore);

      }

      auto windowrect = m_windowrectangleStore;

      bool bGot = m_windowrectangleStore.m_edisplay != e_display_undefined;

      windowrect.m_edisplay = layout().sketch().display();

      windowrect.m_eappearance = layout().sketch().appearance();

      get_window_rect(windowrect.m_rectangleWindow);

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
      else if (windowrect.m_rectangleWindow.size() == m_sizeRestoreCompact)
      {

         windowrect.m_edisplay = e_display_compact;

      }
      else if (windowrect.m_rectangleWindow.size() == m_sizeRestoreBroad)
      {

         windowrect.m_edisplay = e_display_broad;

      }
      else
      {

         windowrect.m_rectangleRestored = windowrect.m_rectangleWindow;

      }

      if (windowrect.m_rectangleRestored.width() < get_window_minimum_size().cx
         || windowrect.m_rectangleRestored.height() < get_window_minimum_size().cy)
      {

         if (windowrect.m_rectangleWindow.width() > get_window_minimum_size().cx
            && windowrect.m_rectangleWindow.height() > get_window_minimum_size().cy)
         {

            windowrect.m_rectangleRestored = windowrect.m_rectangleWindow;

         }

      }

      if (!papplication->data_set(key, windowrect))
      {

         return false;

      }

      m_windowrectangleStore = windowrect;

      return true;

   }


   void box::prodevian_prepare_window_restore(edisplay edisplay)
   {

      good_restore(NULL, window_request_rect(), true, layout().sketch().m_eactivation, layout().sketch().m_zorder, edisplay);

   }


   string box::get_display_tag()
   {

      return m_strDisplay;

   }


   string box::calc_display()
   {

      synchronous_lock synchronouslock(mutex());

      string strDisplay;

      //::rectangle rectangleNormal;

      //get_rect_normal(rectangleNormal);

      ::rectangle rectangleMainMonitor;

      psession->get_main_monitor(rectangleMainMonitor);

      strDisplay.Format("Display(%d, %d)", rectangleMainMonitor.width(), rectangleMainMonitor.height());

      return strDisplay;

   }

   bool box::does_display_match()
   {

      single_lock synchronouslock(mutex(), true);

      if (m_strDisplay.is_empty())
         return false;

      return m_strDisplay == calc_display();

   }


   void box::defer_update_display()
   {

      synchronous_lock synchronouslock(mutex());

      m_strDisplay = calc_display();

   }




   void box::on_command(::message::command * pcommand)
   {

      ::user::interaction::on_command(pcommand);

   }


   bool box::on_before_set_parent(::user::interaction * puiParent)
   {

      if (!::user::interaction::on_before_set_parent(puiParent))
      {

         return false;

      }

      m_bEnableSaveWindowRect2 = false;

      return true;

   }


   bool box::on_set_parent(::user::interaction * puiParent)
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
         case e_simple_command_load_window_rect:

            WindowDataLoadWindowRect(psimplecommand->m_lparam != false);

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




} // namespace user
















