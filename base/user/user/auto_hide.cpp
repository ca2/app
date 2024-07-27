// Created by camilo on 2023-10-02 03:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "auto_hide.h"
#include "acme/constant/id.h"
#include "acme/constant/timer.h"
#include "acme/handler/topic.h"
#include "acme/platform/timer.h"
#include "aura/user/user/frame.h"
#include "aura/message/user.h"


namespace user
{


   auto_hide::auto_hide()
   {

      m_bVisibleControl = true;

      m_bEffectiveVisibleControl = m_bVisibleControl;

      m_bControlVisibilityChanging = false;

      m_bOverrideVisibleControl = false;

      m_bHideControlOnFullScreenOrTransparentFrame = true;

      m_bForceHiddenControl = false; 

      m_bVisibleIfWindowActive = false;

   }


   auto_hide::~auto_hide()
   {


   }


   void auto_hide::auto_hide_on_message_create(::message::message * pmessage)
   {

      m_bEffectiveVisibleControl = m_bVisibleControl;

   }


   void auto_hide::auto_hide_calculate_control_visibility()
   {

      if (m_bForceHiddenControl)
      {

         m_bEffectiveVisibleControl = false;

      }
      else if (m_bHideControlOnFullScreenOrTransparentFrame)
      {

         auto bNewVisible = auto_hide_full_screen_or_transparent_frame_control_visibility();

         if (is_different(bNewVisible, m_bEffectiveVisibleControl))
         {

            if (!m_bControlVisibilityChanging)
            {

               m_bControlVisibilityChanging = true;

               m_timeLastControlVisibilityChange.Now();

               SetTimer(e_timer_defer_handle_auto_hide_tabs, 100_ms);

            }
            else if (m_timeLastControlVisibilityChange.elapsed() > 2_s)
            {

               m_bControlVisibilityChanging = false;

               m_bEffectiveVisibleControl = bNewVisible;

            }

         }

      }
      else if (m_bVisibleControl)
      {

         m_bEffectiveVisibleControl = m_bVisibleControl;

      }

      //return m_bCalculatedVisibleTabs;

      //auto bVisible = are_tabs_visible();

      //auto puiTopLevel = top_level();

      //if (puiTopLevel->frame_is_transparent() && !top_level_frame()->layout().is_full_screen())
      //{

      //   if (m_bShowTabs)
      //   {

      //      m_bShowTabs = false;

      //      set_need_layout();

      //   }

      //   return;

      //}

      //if(m_bNoTabs)
      //{

      //   if(m_bShowTabs)
      //   {

      //      m_bShowTabs = false;

      //      set_need_layout();

      //   }

      //   return;

      //}

      //if(m_bShowTabs)
      //{

      //   if(top_level_frame()!= nullptr && top_level_frame()->is_full_screen())
      //   {

      //      ::rectangle_i32 rectangleTab(get_data()->m_rectangleTab);

      //      rectangleTab+=client_to_screen();

      //      auto pointCursor = get_cursor_position();

      //      bool bShowTabs = rectangleTab.contains(pointCursor);

      //      if(is_different(bShowTabs, m_bShowTabs))
      //      {

      //         m_bShowTabs = bShowTabs;

      //         set_need_layout();

      //         bNeedLayout = true;

      //      }

      //   }

      //}
      //else
      //{

      //   auto pframe = parent_frame();

      //   if(::is_set(pframe) && !pframe->layout().is_full_screen())
      //   {

      //      m_bShowTabs = true;

      //      set_need_layout();

      //   }
      //   else if(::is_set(get_app()) && ::is_set(get_app()->get_session()))
      //   {

      //      ::rectangle_i32 rectangleWindow;

      //      window_rectangle(rectangleWindow);

      //      bool bShowTabs;

      //      auto pointCursor = get_cursor_position();

      //      if(get_data()->m_bVertical)
      //      {

      //         bShowTabs = pointCursor.x() <= rectangleWindow.left();

      //      }
      //      else
      //      {

      //         bShowTabs = pointCursor.y() <= rectangleWindow.top();

      //      }

      //      m_bShowTabs = bShowTabs;

      //      if(bShowTabs)
      //      {

      //         set_need_layout();

      //      }

      //   }

      //}

   }


   bool auto_hide::auto_hide_is_top_level_full_screen_or_transparent()
   {

      auto puiTopLevel = top_level();

      if (puiTopLevel->frame_is_transparent() || top_level_frame()->layout().is_full_screen())
      {

         return true;

      }

      return false;

   }


   bool auto_hide::auto_hide_full_screen_or_transparent_frame_control_visibility()
   {

      if (!m_bHideControlOnFullScreenOrTransparentFrame)
      {

         return true;

      }

      if (m_bOverrideVisibleControl)
      {

         return true;

      }

      if (m_bVisibleIfWindowActive &&
         is_active_window())
      {

         return true;

      }

      if (auto_hide_is_top_level_full_screen_or_transparent())
      {

         return false;

      }

      return true;

   }


   ::i32 auto_hide::auto_hide_threshold_height()
   {

      return this->height();

   }


   void auto_hide::auto_hide_on_message_mouse_move(::message::message * pmessage)
   {

      ::pointer < ::message::mouse > pmouse(pmessage);

      //if (pmessage->previous())
      //{

      //   return;

      //}

      //if (get_data()->m_iClickTab >= 0)
      //{

      //   if (get_data()->m_pcallback != nullptr)
      //   {

      //      get_data()->m_pcallback->_001DropTargetWindowRelay(this);

      //   }

      //}

      auto pointClient = pmouse->m_pointHost;

      host_to_client()(pointClient);

      track_mouse_hover();

      //auto ptabdata = get_data();

      int iAutoHideThresholdHeight = auto_hide_threshold_height();

      if (m_bEffectiveVisibleControl
         && m_bControlVisibilityChanging
         && pointClient.y() < iAutoHideThresholdHeight)
      {

         KillTimer(e_timer_defer_handle_auto_hide_tabs);

         m_bOverrideVisibleControl = true;

         m_bControlVisibilityChanging = false;

      }
      else if (pointClient.y() <= 1)
      {

         if (!m_bForceHiddenControl && m_bHideControlOnFullScreenOrTransparentFrame)
         {

            m_bOverrideVisibleControl = true;

            m_bEffectiveVisibleControl = true;

            set_need_layout();

            set_need_redraw();

            post_redraw();

         }

      }
      else if (pointClient.y() > iAutoHideThresholdHeight)
      {

         auto_hide_on_message_mouse_leave(pmessage);

      }

   }


   void auto_hide::auto_hide_on_message_mouse_leave(::message::message * pmessage)
   {

      if (m_bOverrideVisibleControl)
      {

         m_bOverrideVisibleControl = false;

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

   }



   bool auto_hide::should_draw()
   {

      if (!::user::interaction::should_draw())
      {

         return false;

      }

      if (!m_bEffectiveVisibleControl)
      {

         return false;

      }

      return true;

   }


   void auto_hide::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == e_timer_defer_handle_auto_hide_tabs)
      {

         auto_hide_calculate_control_visibility();

         if (!m_bControlVisibilityChanging)
         {

            KillTimer(e_timer_defer_handle_auto_hide_tabs);

            set_need_layout();

            set_need_redraw();

            post_redraw();

         }

      }

   }


   void auto_hide::handle(::topic * ptopic, ::context * pcontext)
   {
      
      if(m_bForceHiddenControl)
      {
       
         m_bEffectiveVisibleControl = false;
         
      }
      else
      {
         
         if (ptopic->m_atom == id_on_after_enter_full_screen)
         {
            
            m_bEffectiveVisibleControl = false;
            
         }
         else if (ptopic->m_atom == id_on_set_transparent_frame)
         {
            
            m_bEffectiveVisibleControl = false;
            
         }
         else if (ptopic->m_atom == id_on_after_exit_full_screen)
         {
            
            m_bEffectiveVisibleControl = auto_hide_full_screen_or_transparent_frame_control_visibility();
            
         }
         else if (ptopic->m_atom == id_on_clear_transparent_frame)
         {
            
            m_bEffectiveVisibleControl = auto_hide_full_screen_or_transparent_frame_control_visibility();
            
         }
         else if (ptopic->m_atom == id_on_activate)
         {
            
            m_bEffectiveVisibleControl = auto_hide_full_screen_or_transparent_frame_control_visibility();
            
         }
         
      }

   }


} // namespace user


