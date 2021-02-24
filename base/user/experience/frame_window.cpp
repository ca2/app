#include "framework.h"
#include "base/user/experience/_experience.h"
#include "aura/update.h"
#include "aura/message.h"


namespace experience
{


   frame_window::frame_window()
   {

      m_edisplayRestore = e_display_default;

      m_ewindowflag += e_window_flag_load_window_rect_on_impl;

      m_bUseNc = false;
      m_bEnableMouse = true;
      m_bFullScreenEnable = false;
      m_bHoverModeOn = false;
      m_bHoverActive = false;
      m_bDockEnable = true;
      m_bMoveEnable = true;
      m_bSizeEnable = true;
      m_bMenuEnable = true;
      m_bEnableFrameExperience = true;

      m_eupdown = updown_normal_frame;

      m_pupdowntarget = nullptr;

      m_bFullScreenOnZoom = false;

      m_bInitialFramePosition = true;

   }


   frame_window::~frame_window()
   {

   }


   void frame_window::pre_translate_message(::message::message * pmessage)
   {

//#ifdef WINDOWS_DESKTOP
//
//      if (pmessage->m_id == WM_GETTEXT)
//      {
//
//         return;
//
//      }
//      else if (pmessage->m_id == WM_GETTEXTLENGTH)
//      {
//
//         return;
//
//      }
//      else
//
//#endif

         if (pmessage->m_id == e_message_mouse_move)
      {

         return;

      }
      else if (pmessage->m_id == e_message_key_down
         || pmessage->m_id == e_message_key_up
         || pmessage->m_id == e_message_sys_key_down
         || pmessage->m_id == e_message_sys_key_up)
      {

         __pointer(::message::key) pkey(pmessage);

         auto psession = Session;

         if (pkey->userinteraction() == this)
         {

            if (pmessage->m_id == e_message_key_down || pmessage->m_id == e_message_sys_key_down)
            {

               if (!m_bFullScreenOnMaximize)
               {

                  if (pkey->m_ekey == ::user::e_key_alt || pkey->m_ekey == ::user::e_key_lalt || pkey->m_ekey == ::user::e_key_ralt)
                  {

                     m_bFullScreenAlt = false;

                  }
                  else if (pkey->m_ekey == ::user::e_key_control || pkey->m_ekey == ::user::e_key_lcontrol || pkey->m_ekey == ::user::e_key_rcontrol)
                  {

                     m_bFullScreenCtrl = false;

                  }
                  else if (pkey->m_ekey == ::user::e_key_return)
                  {

                     if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
                     {

                        m_bFullScreenReturn = true;

                        m_bFullScreenAlt = true;

                        m_bFullScreenCtrl = true;

                        pkey->m_bRet = true;

                        if (!layout().is_full_screen())
                        {

                           display(e_display_full_screen);

                           set_need_redraw();

                           post_redraw();

                           return;

                        }

                     }

                  }

               }

            }
            else if (pmessage->m_id == e_message_key_up || pmessage->m_id == e_message_sys_key_up)
            {

               if (pkey->m_ekey == ::user::e_key_return)
               {

               }
               else if (pkey->m_ekey == ::user::e_key_alt || pkey->m_ekey == ::user::e_key_lalt || pkey->m_ekey == ::user::e_key_ralt)
               {

                  auto psession = Session;

                  if (layout().is_full_screen() && psession->is_key_pressed(::user::e_key_control) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
                  {

                     pkey->m_bRet = true;

                     defer_restore(m_windowrect.m_rectRestored);

                     display(e_display_restore);

                     set_reposition();

                     set_need_layout();

                     set_need_redraw();

                     post_redraw();

                     m_bFullScreenAlt = false;

                     return;

                  }

                  m_bFullScreenAlt = false;

               }
               else if (pkey->m_ekey == ::user::e_key_control || pkey->m_ekey == ::user::e_key_lcontrol || pkey->m_ekey == ::user::e_key_rcontrol)
               {

                  if (layout().is_full_screen() && psession->is_key_pressed(::user::e_key_alt) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
                  {

                     pkey->m_bRet = true;

                     defer_restore(m_windowrect.m_rectRestored);

                     display(e_display_restore);

                     set_reposition();

                     set_need_layout();

                     set_need_redraw();

                     post_redraw();

                     m_bFullScreenAlt = false;

                     return;

                  }

                  m_bFullScreenAlt = false;

               }

            }

         }

      }

      ::user::frame_window::pre_translate_message(pmessage);

   }


   ::experience::experience* frame_window::get_new_experience(const char* pszExperienceLibrary)
   {

      auto puser = User;

      return puser->experience()->get_new_experience2(this, pszExperienceLibrary);

   }


   ::experience::experience* frame_window::get_experience(const char* pszExperienceLibrary)
   {

      auto puser = User;

      return puser->experience()->get_experience2(this, pszExperienceLibrary);

   }


   ::experience::frame* frame_window::get_frame_experience(const char* pszExperienceLibrary, const char* pszFrame, const char* pszStyle)
   {

      auto puser = User;

      auto pframe = puser->experience()->experience_get_frame2(this, pszExperienceLibrary, pszFrame);

      pframe->m_pframewindow = this;

      auto psubject = subject(id_user_style_change);

      psubject->add(pframe);

      set_user_style(pszStyle);

      return pframe;

   }


   void frame_window::toggle_restore()
   {

#ifdef MACOS

      ns_main_async(^()
                     {

      if(get_parent() == nullptr && get_owner() == nullptr)
      {

         if(!is_window_visible()
            || (!(m_ewindowflag & window_flag_miniaturizable)
                && !is_window_screen_visible()))
         {

            display_previous_restore();

         }
         else if(_001GetTopLeftWeightedOccludedOpaqueRate()  > 0.025)
         {

            order(::e_zorder_top);

            display(e_display_default, e_activation_set_foreground);

         }
         else if(m_pimpl2 && m_pimpl2->m_millisLastExposureAddUp.elapsed() < 300)
         {

            INFO("Ignored minituarize request (by toggle intent) because of recent full exposure.");

         }
         else
         {

            display(e_display_iconic, e_activation_no_activate);

         }

         set_need_redraw();

         post_redraw();

      }

      });

#else

      if (!is_window_visible() || _001GetTopLeftWeightedOccludedOpaqueRate() > 0.025 || layout().is_iconic())
      {

         set_tool_window(false);

         if (!is_window_screen_visible())
         {

            frame_experience_restore();

         }
         else
         {

            order_top();

            display(e_display_normal, e_activation_set_foreground);

         }

      }
      else
      {

         set_tool_window();

         hide();

      }

      set_need_redraw();

      post_redraw();

#endif

   }


   void frame_window::message_handler(::message::message* pusermessage)
   {

//      int iMessage = pusermessage->m_id;


      //if (pusermessage->m_id == WM_GETTEXT)
      //{

      //   _008GetWindowText(pusermessage);

      //   pusermessage->m_uiMessageFlags |= 3; // message considered pre translated
      //   pusermessage->m_uiMessageFlags |= 16384; //  by early optmization

      //   if (!pusermessage->m_bRet)
      //   {

      //      default_window_procedure();

      //   }

      //   return;

      //}
      //else if (pusermessage->m_id == WM_GETTEXTLENGTH)
      //{

      //   _008GetWindowTextLength(pusermessage);

      //   pusermessage->m_uiMessageFlags |= 3; // message considered pre translated
      //   pusermessage->m_uiMessageFlags |= 16384; //  by early optmization

      //   if (!pusermessage->m_bRet)
      //   {

      //      default_window_procedure();

      //   }

      //   return;

      //}
      //else
      //{

         relay_event(pusermessage);

//      }

      if (pusermessage->m_bRet)
      {

         return;

      }

      ::user::frame_window::message_handler(pusermessage);

   }


   void frame_window::relay_event(::message::message * pmessage)
   {

      if (pmessage->m_bRet)
      {

         return;

      }

      if (!layout().is_full_screen() || !layout().is_zoomed())
      {

         if (!layout().is_full_screen())
         {

            if (m_pmenumanager.is_set() && is_sysmenu_enabled())
            {

               m_pmenumanager->relay_event(pmessage);

               if (pmessage->m_bRet)
               {

                  return;

               }

            }

         }

      }

   }


   void frame_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (is_frame_experience_enabled() && m_pframe != nullptr && !layout().is_full_screen())
      {

         try
         {

            if(m_pframe->m_bPendingStyleChange)
            {

               m_pframe->m_bPendingStyleChange = false;

               m_pframe->_on_style_change(pgraphics);

            }

            m_pframe->_001OnDraw(pgraphics);

         }
         catch (...)
         {

         }

      }

   }


   void frame_window::on_defer_display()
   {

      if (m_pframe.is_set())
      {

         m_pframe->on_defer_display();

      }

   }


   void frame_window::enable_dock(bool bEnable)
   {

      m_bDockEnable = bEnable;

   }


   void frame_window::enable_move(bool bEnable)
   {

      m_bMoveEnable = bEnable;

   }


   void frame_window::enable_size(bool bEnable)
   {

      m_bSizeEnable = bEnable;

   }


   void frame_window::enable_menu(bool bEnable)
   {

      m_bMenuEnable = bEnable;

   }


   bool frame_window::is_docking_enabled()
   {

      return m_bDockEnable;

   }


   bool frame_window::is_moving_enabled()
   {

      return is_frame_experience_enabled() && m_bMoveEnable && !layout().is_full_screen() && !layout().is_zoomed();

   }


   bool frame_window::is_sizing_enabled()
   {

      return is_frame_experience_enabled() && m_bSizeEnable && layout().design().display() != e_display_fixed_size;

   }


   bool frame_window::is_sysmenu_enabled()
   {

      return m_bMenuEnable;

   }


   void frame_window::GetRegionClientRect(RECTANGLE_I32 * prectangle)
   {

      ASSERT(m_pframe != nullptr);

      m_pframe->get_window_client_rect(prectangle);

   }


   void frame_window::get_draw_client_rect(RECTANGLE_I32 * prectangle)
   {

      ASSERT(m_pframe != nullptr);

      m_pframe->get_window_client_rect(prectangle);

   }


   bool frame_window::initialize_frame_window_experience()
   {

      if (m_pdockmanager == nullptr)
      {

         __compose(m_pdockmanager, __new(class dock_manager(this)));

      }

      if (m_pmovemanager == nullptr)
      {

         __compose(m_pmovemanager,__new(class move_manager(this)));

      }

      if (m_psizemanager == nullptr)
      {

         __compose(m_psizemanager, __new(class size_manager(this)));

      }

      if (m_pmenumanager == nullptr)
      {

         __compose(m_pmenumanager, __new(class menu_manager(this)));

      }

//      m_pdockmanager->SetSWPFlags(SWP_SHOWWINDOW);

//      m_psizemanager->SetSWPFlags(SWP_SHOWWINDOW);

//      m_pmovemanager->SetSWPFlags(SWP_SHOWWINDOW);

      if (!m_pmovemanager->set_frame_window(this))
      {

         return false;

      }

      if (!m_pdockmanager->set_frame_window(this))
      {

      return false;

      }

      if (!m_psizemanager->set_frame_window(this))
      {

      return false;

      }

      if (!m_pmenumanager->set_frame_window(this))
      {

      return false;

      }

      try
      {

         m_pframe->on_initialize_appearance();

         return true;

      }
      catch (...)
      {

      }


      return true;

   }


   void frame_window::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_button_clicked && m_pframe != nullptr)
      {

         ::id id = pevent->m_puie->GetDlgCtrlId();

         string str(__str(id));

         TRACE("frame_window::on_control_event btn_clkd=%s", str.c_str());

         auto ebutton = m_pframe->get_control_box()->get_control_box_button_type(id);

         switch (ebutton)
         {
         case e_button_close:

            TRACE("button_clicked : button_close");

            post_message(e_message_close);

            set_need_redraw();

            pevent->m_bRet = true;

            return;

         case e_button_minimize:

            TRACE("button_clicked : button_minimize");

            display(e_display_iconic, e_activation_no_activate);

            set_need_redraw();

            pevent->m_bRet = true;

            return;

         case e_button_maximize:

            TRACE("button_clicked : button_maximize");

            display(e_display_zoomed);

            set_reposition(true);

            set_need_layout();

            set_need_redraw();

            post_redraw();

            pevent->m_bRet = true;

            return;

         case e_button_restore:

            TRACE("button_clicked : button_restore");

            frame_experience_restore();

            pevent->m_bRet = true;

            return;

         case e_button_up:

            TRACE("button_clicked : button_up");

            display(e_display_up);

            set_need_redraw();

            pevent->m_bRet = true;

            return;

         case e_button_down:

            TRACE("button_clicked : button_down");

            display(e_display_down);

            set_need_redraw();

            pevent->m_bRet = true;

            return;

         case e_button_transparent_frame:

            TRACE("button_clicked : button_transparent_frame");

            layout().toggle_appearance(e_appearance_transparent_frame);

            display();

            set_need_layout();

            set_need_redraw();

            defer_save_window_placement();

            post_redraw();

            pevent->m_bRet = true;

            return;

         case e_button_notify_icon:

            TRACE("button_clicked : button_notify_icon");

            display(e_display_notify_icon);

            set_need_redraw();

            pevent->m_bRet = true;

            return;

         default:

            break;

         }

      }

   }


   void frame_window::on_command_message(::message::command * pcommand)
   {

      if (pcommand->m_id == ::e_message_system_command && m_pframe != nullptr)
      {

         auto ebutton = m_pframe->get_control_box()->get_control_box_button_type(pcommand->m_id);

         switch (ebutton)
         {
         case e_button_close:

            post_message(e_message_close);

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_minimize:

            display(e_display_iconic, e_activation_no_activate);

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_maximize:

            display(e_display_zoomed);

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_restore:

            frame_experience_restore();

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_up:

            display(e_display_up);

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_down:

            display(e_display_down);

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_transparent_frame:

            layout().toggle_appearance(e_appearance_transparent_frame);

            display();

            set_need_layout();

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_dock:

            pcommand->m_bRet = false;

            return;

         default:

            break;

         }

      }

      ::user::frame_window::on_command_message(pcommand);

   }


   void frame_window::route_command_message(::message::command* pcommand)
   {

      ::user::frame_window::route_command_message(pcommand);
      //::experience::frame_window::route_command_message(pcommand);

      //if (pcommand->m_bRet)
      //{

        // return;

      //}

      //if (pcommand->m_pcommandtargetSource == this)
      //{

      //   // then pump through frame
      //   ::user::frame_window::route_command_message(pcommand);

      //   if (pcommand->m_bRet)
      //   {

      //      return;

      //   }

      //}


   }


   void frame_window::display_system_minimize()
   {

      display(e_display_iconic, e_activation_no_activate);

   }


   void frame_window::display_previous_restore()
   {

      if(::is_screen_visible(m_windowrect.m_edisplayPrevious))
      {

         display(m_windowrect.m_edisplayPrevious);

      }
      else
      {

         display(e_display_restore);

      }

   }


   void frame_window::_001OnSysCommand(::message::message * pmessage)
   {

      __pointer(::message::message) pusermessage(pmessage);

   }




   bool frame_window::_001CanEnterScreenSaver()
   {

      return true;

   }


   //void frame_window::_001OnCommand(::message::message * pmessage)
   //{

   //   __pointer(::message::message) pusermessage(pmessage);

   //   if (m_pframe == nullptr)
   //   {

   //      pusermessage->m_bRet = false;

   //   }
   //   else
   //   {

   //      pusermessage->m_bRet = m_pframe->_001OnCommand(pusermessage->m_wparam, pusermessage->m_lparam, pusermessage->m_lresult);

   //   }

   //}


   //  define System flags que serão usados para posicionar ou
   //  dimensionar pelo uso da função set_window_position

   void frame_window::SetSWPFlags(::u32 uFlags)
   {

      m_uiSWPFlags = uFlags;

      //m_pmovemanager->SetSWPFlags(m_uiSWPFlags);

      //m_psizemanager->SetSWPFlags(m_uiSWPFlags);

   }


   void frame_window::SetActiveFlag(bool fActive)
   {

      if (is_different(fActive, m_fActive))
      {

         TRACE("frame_window::SetActiveFlag %d\n", fActive);

         m_fActive = fActive;

         if (m_pframe != nullptr)
         {

            m_pframe->OnActivate();

         }

         set_need_redraw();

         post_redraw();

      }

   }


   bool frame_window::Start()
   {

      return true;

   }


   void frame_window::FrameWnd(::user::interaction * pframewindow)
   {

      UNREFERENCED_PARAMETER(pframewindow);

   }


   void frame_window::ChildWnd(::user::interaction * pframewindow, ::user::interaction * pwndParent)
   {

      UNREFERENCED_PARAMETER(pframewindow);
      UNREFERENCED_PARAMETER(pwndParent);

   }


   void frame_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (!is_frame_experience_enabled())
      {

         return;

      }

      if (m_pframe != nullptr)
      {

         m_pframe->on_layout(pgraphics);

      }

   }


   void frame_window::on_reposition()
   {

      if (!is_frame_experience_enabled())
      {

         return;

      }

      if (m_pframe != nullptr)
      {

         m_pframe->on_reposition();

      }

   }


   size_manager * frame_window::size_manager()
   {

      if(m_psizemanager == nullptr)
      {

         __compose(m_psizemanager, __new(class size_manager(this)));

      }

      return m_psizemanager;

   }


   void frame_window::set_dock_mask(e_dock emask)
   {

      ASSERT(m_pdockmanager != nullptr);

      m_pdockmanager->set_dock_mask(emask);

   }


   dock_manager * frame_window::dock_manager()
   {

      return m_pdockmanager;

   }


   bool frame_window::IsHoverActive()
   {

      return m_bHoverActive;

   }


   bool frame_window::IsHoverModeOn()
   {

      return m_bHoverModeOn;

   }


   move_manager * frame_window::move_manager()
   {

      return m_pmovemanager;

   }


   void frame_window::_001OnActivate(::message::message * pmessage)
   {

      __pointer(::message::activate) pactivate(pmessage);

      __pointer(::user::interaction) pActive = (pactivate->m_eactivate == e_activate_inactive ? pactivate->m_pWndOther : this);

      if(pActive == nullptr)
      {

      }
      else if(base_class < ::user::combo_list >::bases(pActive))
      {

         ::user::combo_list * plist = dynamic_cast <::user::combo_list *> (pActive.m_p);

         if(plist != nullptr && plist->m_bComboList)
         {

            pactivate->m_bRet = true;

            plist->m_puiDeactivateTogether = this;

            return;

         }

      }

      pactivate->m_bRet = false;

      SetActiveFlag(pactivate->m_eactivate == e_activate_active || pactivate->m_eactivate == e_activate_click_active);

   }


   bool frame_window::is_full_screen_enabled() const
   {

      return m_bFullScreenEnable;

   }


   void frame_window::window_enable_full_screen(bool bEnable)
   {

      m_bFullScreenEnable = bEnable;

   }


   void frame_window::install_message_routing(::channel * pchannel)
   {

      ::user::frame_window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&frame_window::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&frame_window::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&frame_window::_001OnMouseMove);
      MESSAGE_LINK(e_message_non_client_left_button_down,pchannel,this,&frame_window::_001OnNcLButtonDown);
      MESSAGE_LINK(e_message_non_client_left_button_up,pchannel,this,&frame_window::_001OnNcLButtonUp);
      MESSAGE_LINK(e_message_non_client_mouse_move,pchannel,this,&frame_window::_001OnNcMouseMove);
      MESSAGE_LINK(e_message_nchittest,pchannel,this,&frame_window::_001OnNcHitTest);
      MESSAGE_LINK(e_message_activate,pchannel,this,&frame_window::_001OnActivate);
      //MESSAGE_LINK(e_message_command,pchannel,this,&frame_window::_001OnCommand);

//#ifdef WINDOWS_DESKTOP

//      MESSAGE_LINK(WM_SYSCOMMAND, pchannel, this, &frame_window::_001OnSysCommand);

//#endif

      MESSAGE_LINK(e_message_size, pchannel, this, &frame_window::_001OnSize);

   }


   void frame_window::_001OnSize(::message::message* pmessage)
   {

   }


   void frame_window::on_message_left_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if(!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      if(::is_set(m_pframe))
      {

         m_pframe->on_message_left_button_down(pmouse);

      }

      if(pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }


   void frame_window::on_visual_applied()
   {

      ::user::frame_window::on_visual_applied();


      //if (layout().is_docking())
      //{

      //   dock_manager()->defer_cursor_pos();

      //}

   }


   void frame_window::_001OnMouseMove(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if(!is_frame_experience_enabled())
      {

         return;

      }

      if(::is_set(m_pframe))
      {

         if (layout().m_eflag & ::user::interaction_layout::flag_apply_visual)
         {

            INFO("e_message_mouse_move during window move ignored!!");

         }
         else if (pmouse->m_eflagMessage & ::message::flag_synthesized)
         {

            INFO("synthesized e_message_mouse_move ignored!!");

         }
         else
         {

            //INFO("e_message_mouse_move for experience::frame");

            if (m_pframe->_001OnMouseMove(pmouse))
            {

               pmouse->m_bRet = true;

            }

         }

      }

      if(pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }


   void frame_window::on_message_left_button_up(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if(!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      ASSERT(m_pframe != nullptr);

      m_pframe->on_message_left_button_up(pmouse);

      if(pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }


   void frame_window::_001OnNcLButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if(!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      ASSERT(m_pframe != nullptr);

      m_pframe->_001OnNcLButtonDown(pmouse);

      if(pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }

   void frame_window::_001OnNcMouseMove(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if(!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      ASSERT(m_pframe != nullptr);

      m_pframe->_001OnNcMouseMove(pmouse);

   if(pmouse->m_bRet)
   {
   pmouse->m_lresult = 1;
   }

   }

   void frame_window::_001OnNcLButtonUp(::message::message * pmessage)
   {
   __pointer(::message::mouse) pmouse(pmessage);
   if(!is_frame_experience_enabled())
   {
   pmouse->m_bRet = false;
   return;
   }
   ASSERT(m_pframe != nullptr);
   m_pframe->_001OnNcLButtonUp(pmouse);
   if(pmouse->m_bRet)
   {
   pmouse->m_lresult = 1;
   }

   }


   void frame_window::_001OnNcHitTest(::message::message * pmessage)
   {

      __pointer(::message::nc_hit_test) pnchittest(pmessage);

      if(!is_frame_experience_enabled())
      {
   
         pnchittest->m_bRet = false;
   
         return;
   
      }
      
      ASSERT(m_pframe != nullptr);

      enum_hit_test ehittest = e_hit_test_error;
   
      pnchittest->m_bRet = m_pframe->_001OnNcHitTest(pnchittest->m_point, ehittest);

      if (pnchittest->m_bRet)
      {

         pnchittest->set_hit_test(ehittest);

      }

   }


   void frame_window::_001OnTimer(::timer * ptimer)
   {

      //if(!is_frame_experience_enabled())
      //{

      //   ptimer->finalize();

      //   return;

      //}

      //if(m_pframe != nullptr)
      //{

      //   if(!m_pframe->_001OnTimer((::u32) ptimer->m_uEvent))
      //   {

      //      ptimer->finalize();

      //   }

      //}

   }


   void frame_window::OnNcCalcSize(RECTANGLE_I32 * prectangle)
   {

      ASSERT(m_pframe != nullptr);

      m_pframe->OnNcCalcSize(prectangle);

   }


   // point_i32 should be in screen coordinates
   e_hittest frame_window::_001HitTest(const ::point_i32 & pointCursor)
   {

      ASSERT(m_pframe != nullptr);

      return m_pframe->_001HitTest(pointCursor);

   }


   void frame_window::set_frame(::experience::frame * pframe)
   {

      if(m_pframe != nullptr && m_pframe != pframe)
      {

         m_pframe->frame_on_detach();

         m_pframe->m_pframewindow = nullptr;

      }

      if(pframe == nullptr)
      {

         return;

      }

      __compose(m_pframe, pframe);

      pframe->m_pframewindow = this;

      m_pframe->frame_on_attach();

   }


   void frame_window::enable_frame_experience(bool bEnable)
   {

      m_bEnableFrameExperience = bEnable;

      set_need_layout();

   }


   button * frame_window::get_box_button(enum_button ebutton)
   {

      if (!m_pframe)
      {

         return nullptr;

      }

      auto pcontrolbox = m_pframe->get_control_box();

      if (!pcontrolbox)
      {

         return nullptr; 

      }

      auto pbutton = pcontrolbox->get_button(ebutton);

      if (!pbutton)
      {

         return nullptr;

      }

      return nullptr;

   }


   bool frame_window::_001CallOnBeforeAppearance()
   {

      if (!_001OnBeforeAppearance())
      {

         layout().sketch() = layout().design().display();

         return false;

      }

      _001OnExitAppearance();

      return true;

   }


      bool frame_window::sketch_on_display()
      {

         if (!is_frame_experience_enabled())
         {

            return ::user::frame_window::sketch_on_display();

         }

         auto edisplay = layout().sketch().display();

         //auto eactivation = layout().sketch().activation();

         if (edisplay == e_display_iconic)
         {

            if (m_bitMinimizeToTray)
            {

               layout().sketch() = e_display_notify_icon;

            }

         }
         else if (edisplay == e_display_zoomed)
         {

            if (m_bFullScreenOnMaximize)
            {

               layout().sketch() = e_display_full_screen;

            }

         }
         else if (edisplay == ::e_display_up)
         {

            m_eupdown = updown_up;

         }
         else if (edisplay == ::e_display_down)
         {

            m_eupdown = updown_down;

         }

         if (layout().sketch().display() != e_display_iconic)
         {

            m_windowrect.m_edisplayPrevious = layout().sketch().display();

         }

         if (!_001CallOnBeforeAppearance())
         {

            return false;

         }

         if (!::user::frame_window::sketch_on_display())
         {

            return false;

         }

         return true;

      }


#define ZONEING_COMPARE ::comparison


      index frame_window::get_best_zoneing(edisplay & edisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectRequest, bool bPreserveSize)
      {

         //i64 g_i_get_best_zoneing = 0;

         ::rectangle_i32 rectangle;

         if (rectRequest.is_set())
         {

            rectangle = rectRequest;

         }
         else
         {

            rectangle = layout().sketch().screen_rect();

         }

         ::rectangle_i32 rectWorkspace;

         index iBestWorkspace = get_best_workspace(&rectWorkspace, rectangle);

         auto sizeMinimum = get_window_minimum_size();

         if (rectangle.height() < sizeMinimum.cy)
         {

            rectangle.set_height(sizeMinimum.cy);

            rectangle._001ConstraintY(rectWorkspace);

         }

         if (rectangle.width() < sizeMinimum.cx)
         {

            rectangle.set_width(sizeMinimum.cx);

            rectangle._001ConstraintX(rectWorkspace);

         }

         if (iBestWorkspace >= 0)
         {

            rectangle._001Constraint(rectWorkspace);

         }

         if (!is_docking_appearance(edisplay))
         {

            edisplay = e_display_none;

         }

         ::e_display edisplayPrevious = edisplay != e_display_none ? edisplay : layout().design().display();

         bool bCursorPosition = layout().is_moving();

         ::point_i32 pointCursor(e_no_initialize);

         if (bCursorPosition)
         {

            auto psession = Session;

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            pointCursor = pwindowing->get_cursor_position();

         }

         double dMargin = System.m_dpi * 0.75 * (1.0 - sqrt((double) rectangle.area() / (double) rectWorkspace.area()));

         if (ZONEING_COMPARE::is_equal(rectangle.top, rectWorkspace.top, dMargin, !(edisplayPrevious & e_display_top)))
         {

            edisplay |= e_display_top;

            if (bPreserveSize)
            {

               rectangle.move_top_to(rectWorkspace.top);

            }
            else
            {

               rectangle.top = rectWorkspace.top;

            }

         }
         else
         {

            edisplay -= e_display_top;

         }

         if (ZONEING_COMPARE::is_equal(rectWorkspace.bottom, rectangle.bottom, dMargin, !(edisplayPrevious & e_display_bottom)))
         {

            edisplay |= e_display_bottom;

            if (bPreserveSize)
            {

               rectangle.move_bottom_to(rectWorkspace.bottom);

            }
            else
            {

               rectangle.bottom = rectWorkspace.bottom;

            }

         }
         else
         {

            edisplay -= e_display_bottom;

         }

         if (ZONEING_COMPARE::is_equal(rectangle.left, rectWorkspace.left, dMargin, !(edisplayPrevious & e_display_left)))
         {

            edisplay |= e_display_left;

            if (bPreserveSize)
            {

               rectangle.move_left_to(rectWorkspace.left);

            }
            else
            {

               rectangle.left = rectWorkspace.left;

            }

         }
         else
         {

            edisplay -= e_display_left;

         }

         if (ZONEING_COMPARE::is_equal(rectWorkspace.right, rectangle.right, dMargin, !(edisplayPrevious & e_display_right)))
         {

            edisplay |= e_display_right;

            if (bPreserveSize)
            {

               rectangle.move_right_to(rectWorkspace.right);

            }
            else
            {

               rectangle.right = rectWorkspace.right;

            }

         }
         else
         {

            edisplay -= e_display_right;

         }

         if (!(edisplay & e_display_top || edisplay & e_display_bottom)
            && is_different(edisplay & e_display_left, edisplay & e_display_right))
         {

            if (ZONEING_COMPARE::is_centered(rectWorkspace.top, rectangle.top, rectangle.bottom, rectWorkspace.bottom))
            {

               if (dock_manager()->window_is_docking())
               {

                  edisplay |= e_display_bottom;

                  edisplay |= e_display_top;

                  rectangle.bottom = rectWorkspace.bottom;

                  rectangle.top = rectWorkspace.top;

               }

            }
            else if((edisplayPrevious & (e_display_left | e_display_right))
               != (edisplay & (e_display_left | e_display_right)))
            {

               edisplay = e_display_none;

            }

         }

         if (!(edisplay & e_display_left || edisplay & e_display_right)
            && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
         {

            if (ZONEING_COMPARE::is_centered(rectWorkspace.left, rectangle.left, rectangle.right, rectWorkspace.right))
            {

               if (dock_manager()->window_is_docking())
               {

                  edisplay |= e_display_left;

                  edisplay |= e_display_right;

                  rectangle.left = rectWorkspace.left;

                  rectangle.right = rectWorkspace.right;

               }

            }
            else if ((edisplayPrevious & (e_display_top | e_display_bottom))
               != (edisplay & (e_display_top | e_display_bottom)))
            {

               edisplay = e_display_none;

            }

         }

         bool bLeftXorRight = is_different(edisplay & e_display_left, edisplay & e_display_right);

         bool bTopXorBottom = is_different(edisplay & e_display_top, edisplay & e_display_bottom);

         bool bTopAndBottom = edisplay & e_display_top && edisplay & e_display_bottom;

         bool bLeftAndRight = edisplay & e_display_left && edisplay & e_display_right;

         if (bLeftXorRight && bTopXorBottom)
         {

         }
         else if (bTopAndBottom && bLeftAndRight && !bPreserveSize)
         {

            if (layout().sketch().display() == e_display_full_screen)
            {

               edisplay = e_display_full_screen;

            }
            else
            {

               edisplay = e_display_zoomed;

            }

         }

         if (edisplay == e_display_none)
         {

            edisplay = e_display_normal;

         }

         if (is_docking_appearance(edisplay))
         {

            *prectangle = rectangle;

         }
         else if (edisplay == e_display_zoomed)
         {

            *prectangle = rectWorkspace;

         }
         else
         {

            *prectangle = rectRequest;

         }

         return iBestWorkspace;

      }


#undef ZONEING_COMPARE


      void frame_window::_001OnAfterAppearance()
      {

      }


//      void frame_window::on_message_dock_button_left_button_down(::message::message *pmessage)
//      {
//
//         __pointer(::message::mouse) pmouse(pmessage);
//
//         if (!WfiOnStartDock())
//         {
//
//            return;
//
//         }
//
//         dock_manager()->on_message_left_button_down(pmouse);
//
//         //::rectangle_i32 rectWindow;
//
//         //pevent->m_puie->get_window_rect(rectWindow);
//
//         ///dock_manager()->m_pointCursorOrigin = rectWindow.center();
//
//      }


      bool frame_window::_001OnBeforeAppearance()
      {

         auto edisplay = layout().sketch().display();

         if (edisplay == e_display_notify_icon)
         {

            if(!window_is_notify_icon_enabled())
            {

               return false;

            }

         }

         return true;

      }


      void frame_window::_001OnExitFullScreen()
      {

         ::user::box::_001OnExitFullScreen();

         set_need_layout();

      }


      void frame_window::frame_Attach()
      {

         if (m_pupdowntarget != nullptr)
         {

            m_pupdowntarget->UpDownTargetAttach(this);

         }

      }


      void frame_window::frame_Detach()
      {

         if (m_pupdowntarget != nullptr)
         {

            m_pupdowntarget->UpDownTargetDetach(this);

         }

      }


      //void frame_window::_001OnTimer(::timer * ptimer)
      //{

      //   _001OnTimer(ptimer);

      //}


      //bool frame_window::update()
      //{

      //   if (m_pframewindow == nullptr)
      //   {

      //      return false;

      //   }

      //   if (m_pframe == nullptr)
      //   {

      //      return false;

      //   }

      //   //try
      //   //{

      //   //   if (m_pframe->m_puserstyle.is_null())
      //   //   {

      //   //      m_pframe->m_puserstyle = m_puserstyle;

      //   //   }

      //   //}
      //   //catch (...)
      //   //{

      //   //}


      //   return false;

      //}


      void frame_window::defer_save_window_placement()
      {


      }


      bool frame_window::window_is_notify_icon_enabled()
      {

         return false;

      }


   bool frame_window::is_frame_experience_enabled()
   {

      return m_bEnableFrameExperience && m_bWindowFrame;

   }


   void frame_window::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

      ::user::frame_window::on_start_layout_experience(elayoutexperience);

      check_transparent_mouse_events();

   }


   void frame_window::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {

      ::user::frame_window::on_end_layout_experience(elayoutexperience);

      check_transparent_mouse_events();

      defer_save_window_placement();

   }


   void frame_window::frame_experience_restore()
   {

      calculate_broad_and_compact_restore();

      auto rectRequest = layout().sketch().screen_rect();

      edisplay edisplay = layout().sketch().display();

      if (!::is_equivalent(edisplay, e_display_normal))
      {

         defer_restore(m_windowrect.m_rectRestored);

      }
      else if(rectRequest.size() == m_sizeRestoreBroad)
      {

         if (m_windowrect.m_rectRestored.size() == m_sizeRestoreBroad)
         {

            display(e_display_compact);

         }
         else
         {

            defer_restore(m_windowrect.m_rectRestored);

         }

      }
      else if (rectRequest.size() == m_sizeRestoreCompact)
      {

         display(e_display_broad);

      }
      else
      {

         display(e_display_compact);

      }

      set_reposition(true);

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }



   void frame_window::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      if(psubject->id() == id_app_activated)
      {

         toggle_restore();

      }

   }



} // namespace experience



