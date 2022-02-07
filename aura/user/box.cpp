#include "framework.h"
#include "aura/user/_user.h"
#include "aura/message.h"
#include "acme/constant/simple_command.h"
#include "apex/message/simple_command.h"


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


   void box::initialize(::object * pobject)
   {

      //auto estatus = 
      
      interaction::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (m_atom.is_empty())
      {

         m_atom = __type_name(this);

      }

      m_databasekey.m_strDataKey = m_atom;

      //return estatus;

   }




   void box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      //scroll::install_message_routing(pchannel);

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


   ::e_display box::window_stored_display() const
   {

      auto edisplayStored = m_windowrectangle.m_edisplay;

      return edisplayStored;

   }


   ::e_display box::window_previous_display() const
   {

      auto edisplayPrevious = m_windowrectangle.m_edisplayPrevious;

      return edisplayPrevious;

   }


   void box::on_visual_applied()
   {

      ::user::interaction::on_visual_applied();

      auto edisplay = layout().design().display();

      get_window_rect(m_windowrectangle.m_rectangleWindow, e_layout_design);

      if (is_docking_appearance(edisplay))
      {

         m_windowrectangle.m_rectangleSnapped = m_windowrectangle.m_rectangleWindow;

      }
      else if (is_equivalent(edisplay, e_display_normal))
      {

         calculate_broad_and_compact_restore();

         if (m_windowrectangle.m_rectangleWindow.size() != m_sizeRestoreBroad
            && m_windowrectangle.m_rectangleWindow.size() != m_sizeRestoreCompact)
         {

            if (m_windowrectangle.m_rectangleWindow.size() != m_windowrectangle.m_rectangleRestored.size())
            {

               m_windowrectangle.m_rectangleRestored = m_windowrectangle.m_rectangleWindow;

            }
            else if (m_windowrectangle.m_rectangleWindow != m_windowrectangle.m_rectangleRestored)
            {

               m_windowrectangle.m_rectangleRestored = m_windowrectangle.m_rectangleWindow;

            }

         }
         else
         {

            if (m_windowrectangle.m_rectangleRestored.is_empty()
               || m_windowrectangle.m_rectangleRestored.size() == m_sizeRestoreCompact
               || m_windowrectangle.m_rectangleRestored.size() == m_sizeRestoreBroad)
            {

               m_windowrectangle.m_rectangleRestored = m_windowrectangle.m_rectangleWindow;

            }

         }

      }

   }


   void box::window_show_change_visibility()
   {

      ::user::interaction::window_show_change_visibility();

      m_windowrectangle.m_edisplay = layout().window().display();

   }


   bool box::should_save_window_rect()
   {

#if defined(_UWP) || defined(APPLE_IOS)

      return false;

#else

      return m_bSaveWindowRect && m_bEnableSaveWindowRect2;

#endif

   }


   void box::WindowDataSaveWindowRect()
   {

      bool bSave = false;

      if (should_save_window_rect())
      {

         if (layout().sketch().display() == ::e_display_none)
         {

            return;

         }

         defer_update_display();

         //bSave = 
         
         SaveWindowRect_(m_databasekey + window_data_key_modifier());

      }

      //return bSave;

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

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         ::index iDisplay = good_restore(nullptr, nullptr, true, e_activation_default, e_zorder_top, initial_restore_display());

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


   bool box::LoadWindowRect_(const ::database::key & key, bool bForceRestore, bool bInitialFramePosition)
   {

      if (!(m_ewindowflag & e_window_flag_auto_store_window_rect))
      {

         return false;

         //return;

      }

      //try
      //{

         window_rectangle windowrectangle;

         __pointer(::aura::application) papplication = get_application();

         if (!papplication->data_get(key, windowrectangle))
         {

            return false;

         }

         m_ewindowflag |= e_window_flag_loading_window_rect;

         m_windowrectangleStore = windowrectangle;

         m_windowrectangle = m_windowrectangleStore;

         enum_display edisplay = windowrectangle.m_edisplay;

         layout().sketch().appearance() = windowrectangle.m_eappearance;

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

            if(bInitialFramePosition)
            {

               layout().sketch().display() = edisplay;

            }

            layout().sketch() = windowrectangle.m_rectangleWindow;

            layout().sketch() = edisplay;

         }
         else if (!bForceRestore && is_docking_appearance(edisplay))
         {

            if(bInitialFramePosition)
            {

               layout().sketch() = edisplay;

            }

            layout().sketch() = windowrectangle.m_rectangleSnapped;

            layout().sketch() = edisplay;

         }
         else
         {
            
            send_routine(__routine([this, windowrectangle]()
            {

               good_restore(nullptr, windowrectangle.m_rectangleRestored, true, e_activation_default, e_zorder_top, windowrectangle.m_edisplay);
               
            }));

         }

         return true;

      //}
      //catch (const ::exception & pe)
      //{

      //   handle_exception(pe);

      //}
      //catch (...)
      //{

      //}

      //return false;

   }


   void box::SaveWindowRect_(const ::database::key & key)
   {

      if (!(m_ewindowflag & e_window_flag_auto_store_window_rect))
      {

         return;

      }

      if (layout().sketch().display() == ::e_display_none)
      {

         return;

      }

      if (m_windowrectangleStore.m_edisplay == e_display_undefined)
      {

         auto papplication = get_application();

         papplication->data_get(key, m_windowrectangleStore);

      }

      auto windowrect = m_windowrectangleStore;

      bool bGot = m_windowrectangleStore.m_edisplay != e_display_undefined;

      windowrect.m_edisplay = layout().sketch().display();

      windowrect.m_eappearance = layout().sketch().appearance();

      get_window_rect(windowrect.m_rectangleWindow, e_layout_sketch);

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

      __pointer(::aura::application) papplication = get_application();

      papplication->data_set(key, windowrect);
      //{

      //   return false;

      //}

      m_windowrectangleStore = windowrect;

      //return true;

   }


   void box::sketch_prepare_window_restore(edisplay edisplay)
   {

      get_wnd()->post_routine(__routine([this, edisplay]()
      {

         auto screen_rect = this->screen_rect();

         auto activation = layout().sketch().activation();

         auto zorder = layout().sketch().zorder();

         good_restore(NULL, screen_rect, true, activation, zorder, edisplay);

      }));

   }


   string box::calc_display()
   {

      //synchronous_lock synchronouslock(mutex());

      string strDisplay;

      //rectangle_i32 rectangleNormal;

      //get_rect_normal(rectangleNormal);

      ::rectangle_i32 rectangleMainMonitor;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      pdisplay->get_main_monitor(rectangleMainMonitor);

      strDisplay.format("Display(%d, %d)", rectangleMainMonitor.width(), rectangleMainMonitor.height());

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

      //synchronous_lock synchronouslock(mutex());

      m_strDisplay = calc_display();

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

      switch (psimplecommand->command())
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


   string box::get_display_tag()
   {

      return m_strDisplay;

   }


} // namespace user
















