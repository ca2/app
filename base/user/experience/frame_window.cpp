#include "framework.h"
#include "frame_window.h"
#include "acme/constant/message.h"
#include "acme/constant/id.h"
#include "acme/handler/item.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"
#include "base/platform/session.h"
#include "base/user/user/user.h"
#include "department.h"
#include "frame.h"
#include "menu_manager.h"
#include "dock_manager.h"
#include "move_manager.h"
#include "size_manager.h"
#include "control_box.h"
#include "axis/user/user/list_box.h"
#include "base/platform/system.h"


template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex_left(R1 & r1, const R2 & r2)
{

   {

      auto diff = r2.left - r1.right;

      if (diff > 0)
      {

         x_offset_rect(&r1, diff);

      }

   }

}


template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex_right(R1 & r1, const R2 & r2)
{

   {

      auto diff = r2.right - r1.left;

      if (diff < 0)
      {

         x_offset_rect(&r1, diff);

      }

   }

}



template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex_top(R1 & r1, const R2 & r2)
{

   {

      auto diff = r2.top - r1.bottom;

      if (diff > 0)
      {

         y_offset_rect(&r1, diff);

      }

   }

}


template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex_bottom(R1 & r1, const R2 & r2)
{

   {

      auto diff = r2.bottom - r1.top;

      if (diff < 0)
      {

         y_offset_rect(&r1, diff);

      }

   }



}


template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex_x(R1 & r1, const R2 & r2)
{

   constrain_vertex_left(r1, r2);

   constrain_vertex_right(r1, r2);

}


template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex_y(R1 & r1, const R2 & r2)
{

   constrain_vertex_top(r1, r2);

   constrain_vertex_bottom(r1, r2);

}


template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex(R1 & r1, const R2 & r2)
{

   constrain_vertex_x(r1, r2);

   constrain_vertex_y(r1, r2);

}


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
      //m_bEatsDoubleClick = false;

      m_eupdown = e_updown_normal_frame;

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
      //      if (pmessage->m_atom == WM_GETTEXT)
      //      {
      //
      //         return;
      //
      //      }
      //      else if (pmessage->m_atom == WM_GETTEXTLENGTH)
      //      {
      //
      //         return;
      //
      //      }
      //      else
      //
      //#endif

      if (pmessage->m_atom == e_message_mouse_move)
      {

         return;

      }
      else if (pmessage->m_atom == e_message_key_down
         || pmessage->m_atom == e_message_key_up
         || pmessage->m_atom == e_message_sys_key_down
         || pmessage->m_atom == e_message_sys_key_up)
      {

         auto pkey = pmessage->m_union.m_pkey;

         auto psession = get_session();

         if(::user::message_user_interaction(pkey) == this)
         {

            if (pmessage->m_atom == e_message_key_down || pmessage->m_atom == e_message_sys_key_down)
            {

               if (!m_bFullScreenOnMaximize)
               {

                  if (pkey->m_ekey == ::user::e_key_alt || pkey->m_ekey == ::user::e_key_left_alt || pkey->m_ekey == ::user::e_key_right_alt)
                  {

                     m_bFullScreenAlt = false;

                  }
                  else if (pkey->m_ekey == ::user::e_key_control || pkey->m_ekey == ::user::e_key_left_control || pkey->m_ekey == ::user::e_key_right_control)
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
            else if (pmessage->m_atom == e_message_key_up || pmessage->m_atom == e_message_sys_key_up)
            {

               if (pkey->m_ekey == ::user::e_key_return)
               {

               }
               else if (pkey->m_ekey == ::user::e_key_alt || pkey->m_ekey == ::user::e_key_left_alt || pkey->m_ekey == ::user::e_key_right_alt)
               {

                  auto psession = get_session();

                  if (layout().is_full_screen() && psession->is_key_pressed(::user::e_key_control) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
                  {

                     pkey->m_bRet = true;

                     good_move(&m_windowrectangle.m_rectangleNormal);

                     display(e_display_normal);

                     set_reposition();

                     set_need_layout();

                     set_need_redraw();

                     post_redraw();

                     m_bFullScreenAlt = false;

                     return;

                  }

                  m_bFullScreenAlt = false;

               }
               else if (pkey->m_ekey == ::user::e_key_control || pkey->m_ekey == ::user::e_key_left_control || pkey->m_ekey == ::user::e_key_right_control)
               {

                  if (layout().is_full_screen() && psession->is_key_pressed(::user::e_key_alt) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
                  {

                     pkey->m_bRet = true;

                     display_previous();

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


   ::pointer<::experience::experience>frame_window::create_experience(const ::string & strExperience)
   {

      auto psession = get_session();

      auto puser = psession->user();

      return puser->experience()->create_experience(this, strExperience);

   }


   ::pointer<::experience::experience>frame_window::experience(const ::string & strExperience)
   {

      auto psession = get_session();

      auto puser = psession->user();

      return puser->experience()->experience(this, strExperience);

   }


   ::pointer<::experience::frame>frame_window::frame_experience(const ::string & strExperience, const ::string & strFrame, const ::string & strStyle)
   {

      auto psession = get_session();

      auto puser = psession->user();

      auto pframe = puser->experience()->frame_experience(this, strExperience, strFrame);

      pframe->m_pframewindow = this;

      auto psignal = get_signal(id_user_style_change);

      psignal->add_handler(pframe);

      set_user_style(strStyle);

      auto pframewindow = this;

      pframewindow->handle(psignal, nullptr);

      return pframe;

   }


   //   void frame_window::frame_toggle_restore()
   //   {
   //
   //      if(m_pimpl2 && m_pimpl2->m_pwindow)
   //      {
   //
   //         return m_pimpl2->m_pwindow->frame_toggle_restore();
   //
   //      }
   //      else
   //      {
   //
   //         return ::user::frame_window::frame_toggle_restore();
   //
   //      }
   //
   //
   //
   ////#ifdef MACOS
   ////
   ////
   ////#else
   ////
   ////
   ////#endif
   //
   //   }


   void frame_window::message_handler(::message::message * pusermessage)
   {

      //      int iMessage = pusermessage->m_atom;


            //if (pusermessage->m_atom == WM_GETTEXT)
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
            //else if (pusermessage->m_atom == WM_GETTEXTLENGTH)
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

            if (m_pframe->m_bPendingStyleChange)
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

      if (m_bWindowFrame && m_pframe.is_set())
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

      return is_frame_experience_enabled() && m_bSizeEnable && const_layout().design().display() != e_display_fixed_size;

   }


   bool frame_window::is_sysmenu_enabled()
   {

      return m_bMenuEnable;

   }


   void frame_window::GetRegionClientRect(::rectangle_i32 * prectangle)
   {

      ASSERT(m_pframe != nullptr);

      m_pframe->get_window_client_rect(prectangle);

   }


   void frame_window::get_draw_client_rect(::rectangle_i32 * prectangle)
   {

      ASSERT(m_pframe != nullptr);

      m_pframe->get_window_client_rect(prectangle);

   }


   void frame_window::initialize_frame_window_experience()
   {

      if (m_pdockmanager == nullptr)
      {

         __construct(m_pdockmanager, __new(class dock_manager));

         try
         {

            m_pdockmanager->initialize_dock_manager(this);

            m_pdockmanager->set_frame_window(this);

         }
         catch (...)
         {

         }

      }

      if (m_pmovemanager == nullptr)
      {

         __construct(m_pmovemanager, __new(class move_manager));

         try
         {

            m_pmovemanager->initialize_move_manager(this);

            m_pmovemanager->set_frame_window(this);

         }
         catch (...)
         {

         }

      }

      if (m_psizemanager == nullptr)
      {

         __construct(m_psizemanager, __new(class size_manager));

         try
         {

            m_psizemanager->initialize_size_manager(this);

            m_psizemanager->set_frame_window(this);

         }
         catch (...)
         {


         }

      }

      if (m_pmenumanager == nullptr)
      {

         __construct(m_pmenumanager, __new(class menu_manager));

         try
         {

            m_pmenumanager->initialize_menu_manager(this);

            m_pmenumanager->set_frame_window(this);

         }
         catch (...)
         {

         }

      }

      //      m_pdockmanager->SetSWPFlags(SWP_SHOWWINDOW);

      //      m_psizemanager->SetSWPFlags(SWP_SHOWWINDOW);

      //      m_pmovemanager->SetSWPFlags(SWP_SHOWWINDOW);

            //if(estatusMoveManager.succeeded())
            //{

            //   if (!m_pmovemanager->set_frame_window(this))
            //   {

            //      estatusMoveManager = error_failed;

            //   }

            //}

            //if(estatusDockManager.succeeded())
            //{

            //   if (!m_pdockmanager->set_frame_window(this))
            //   {

            //      estatusDockManager = error_failed;

            //   }

            //}

            //if(estatusSizeManager.succeeded())
            //{

            //   if (!m_psizemanager->set_frame_window(this))
            //   {

            //      estatusSizeManager = error_failed;

            //   }

            //}

            //if(estatusMenuManager.succeeded())
            //{

            //   if (!m_pmenumanager->set_frame_window(this))
            //   {

            //      estatusMenuManager = error_failed;

            //   }

            //}

      try
      {

         m_pframe->on_initialize_appearance();

         //return ::success;

      }
      catch (...)
      {

      }


      //return error_failed;

   }


   void frame_window::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == ::id_click && m_pframe != nullptr)
      {

         auto atom = ptopic->user_element_id();

         FORMATTED_TRACE("frame_window::handle_event btn_clkd=%s", string(atom).c_str());

         auto ebutton = m_pframe->get_control_box()->get_control_box_button_type(atom);

         switch (ebutton)
         {
         case e_button_close:

            TRACE("button_clicked : button_close");

            post_message(MESSAGE_CLOSE);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_minimize:

            TRACE("button_clicked : button_minimize");

            display(e_display_iconic, e_activation_no_activate);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_maximize:

            TRACE("button_clicked : button_maximize");

            display(e_display_zoomed);

            set_reposition(true);

            set_need_layout();

            set_need_redraw();

            post_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_restore:

            TRACE("button_clicked : button_restore");

            frame_experience_restore();

            ptopic->m_bRet = true;

            return;

         case e_button_up:

            TRACE("button_clicked : button_up");

            display(e_display_up);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_down:

            TRACE("button_clicked : button_down");

            display(e_display_down);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_transparent_frame:

            TRACE("button_clicked : button_transparent_frame");

            toggle_appearance(e_appearance_transparent_frame);

            defer_save_window_placement();

            display();

            set_reposition();

            set_need_layout();

            set_need_redraw();

            post_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_notify_icon:

            TRACE("button_clicked : button_notify_icon");

            display(e_display_notify_icon);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         default:

            break;

         }

      }
      else if (ptopic->m_atom == id_app_activated)
      {

         frame_toggle_restore();

      }

      ::user::frame_window::handle(ptopic, pcontext);

   }


   void frame_window::on_command(::message::command * pcommand)
   {

      if (pcommand->m_atom == ::e_message_system_command && m_pframe != nullptr)
      {

         auto ebutton = m_pframe->get_control_box()->get_control_box_button_type(pcommand->m_atom);

         switch (ebutton)
         {
         case e_button_close:

            post_message(MESSAGE_CLOSE);

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

            toggle_appearance(e_appearance_transparent_frame);

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

      ::user::frame_window::on_command(pcommand);

   }


   void frame_window::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      ::user::frame_window::route_command(pcommand, bRouteToKeyDescendant);
      //::experience::frame_window::route_command(pcommand);

      //if (pcommand->m_bRet)
      //{

        // return;

      //}

      //if (pcommand->m_pcommandtargetSource == this)
      //{

      //   // then pump through frame
      //   ::user::frame_window::route_command(pcommand);

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

      if (::is_screen_visible(m_windowrectangle.m_edisplayPrevious))
      {

         return display(m_windowrectangle.m_edisplayPrevious);

      }
      else
      {

         return display(e_display_normal);

      }

   }


   void frame_window::_001OnSysCommand(::message::message * pmessage)
   {

      ::pointer<::message::message>pusermessage(pmessage);

   }




   bool frame_window::_001CanEnterScreenSaver()
   {

      return true;

   }


   //void frame_window::_001OnCommand(::message::message * pmessage)
   //{

   //   ::pointer<::message::message>pusermessage(pmessage);

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

         //FORMATTED_TRACE("frame_window::SetActiveFlag %d\n", fActive);

         m_fActive = fActive;

         if (!fActive)
         {

            FORMATTED_TRACE("frame_window::SetActiveFlag Not Active");

         }

         if (m_pframe != nullptr)
         {

            m_pframe->OnActivate();

         }

         if (m_puserinteraction->m_ewindowflag & ::e_window_flag_window_created)
         {

            set_need_redraw();

            post_redraw();

         }

      }

   }


   bool frame_window::Start()
   {

      return true;

   }


   void frame_window::FrameWnd(::user::interaction * pframewindow)
   {

      __UNREFERENCED_PARAMETER(pframewindow);

   }


   void frame_window::ChildWnd(::user::interaction * pframewindow, ::user::interaction * puserinteractionParent)
   {

      __UNREFERENCED_PARAMETER(pframewindow);
      __UNREFERENCED_PARAMETER(puserinteractionParent);

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

      if (m_psizemanager == nullptr)
      {

         __construct(m_psizemanager, __new(class size_manager));

         //auto estatus = 

         m_psizemanager->initialize_size_manager(this);

         //if (!estatus)
         //{

         //   __release(m_psizemanager);

         //}

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

      ::pointer<::message::activate>pactivate(pmessage);

      ::pointer<::user::interaction>pActive = (pactivate->m_eactivate == e_activate_inactive ? pactivate->m_pWndOther : this);

      if (pActive == nullptr)
      {

      }
      else if (base_class < ::user::list_box >::bases(pActive))
      {

         ::user::list_box * plist = dynamic_cast <::user::list_box *> (pActive.m_p);

         if (plist != nullptr && plist->m_bComboList)
         {

            pactivate->m_bRet = true;

            plist->m_puiDeactivateTogether = this;

            return;

         }

      }

      pactivate->m_bRet = false;

      SetActiveFlag(pactivate->m_eactivate == e_activate_active || pactivate->m_eactivate == e_activate_click_active);

   }


   bool frame_window::is_full_screen_enabled()
   {

      return m_bFullScreenEnable;

   }


   ::item_pointer frame_window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
   {

      if (is_sizing_enabled())
      {

         if (m_psizemanager->m_eframeCursor != e_frame_none)
         {


            switch (m_psizemanager->m_eframeCursor)
            {
            case e_frame_sizing_left:
               return __new(::item(e_element_resize_left));
            case e_frame_sizing_top:
               return __new(::item(e_element_resize_top));
            case e_frame_sizing_right:
               return __new(::item(e_element_resize_right));
            case e_frame_sizing_bottom:
               return __new(::item(e_element_resize_bottom));
            case e_frame_sizing_top_left:
               return __new(::item(e_element_resize_top_left));
            case e_frame_sizing_top_right:
               return __new(::item(e_element_resize_top_right));
            case e_frame_sizing_bottom_left:
               return __new(::item(e_element_resize_bottom_left));
            case e_frame_sizing_bottom_right:
               return __new(::item(e_element_resize_bottom_right));
               default:
                  
                  return nullptr;

            }

         }

      }

      return ::user::frame_window::hit_test(pmouse, ezorder);

   }


   void frame_window::window_enable_full_screen(bool bEnable)
   {

      m_bFullScreenEnable = bEnable;

   }


   void frame_window::install_message_routing(::channel * pchannel)
   {

      ::user::frame_window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &frame_window::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &frame_window::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &frame_window::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &frame_window::on_message_mouse_move);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, this, &frame_window::_001OnNcLButtonDown);
      MESSAGE_LINK(e_message_non_client_left_button_up, pchannel, this, &frame_window::_001OnNcLButtonUp);
      MESSAGE_LINK(e_message_non_client_mouse_move, pchannel, this, &frame_window::_001OnNcMouseMove);
      MESSAGE_LINK(e_message_non_client_hit_test, pchannel, this, &frame_window::_001OnNcHitTest);
      MESSAGE_LINK(e_message_activate, pchannel, this, &frame_window::_001OnActivate);

      MESSAGE_LINK(e_message_size, pchannel, this, &frame_window::on_message_size);

   }


   void frame_window::on_message_size(::message::message * pmessage)
   {

   }


   void frame_window::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      if (::is_set(m_pframe))
      {

         m_pframe->on_message_left_button_down(pmouse);

      }

      if (pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }


   void frame_window::on_visual_applied()
   {

      ::user::frame_window::on_visual_applied();


   }


   void frame_window::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_frame_experience_enabled())
      {

         return;

      }

      if (::is_set(m_pframe))
      {

         if (layout().m_eflag & ::user::interaction_layout::flag_apply_visual)
         {

            INFORMATION("e_message_mouse_move during window transfer ignored!!");

         }
         else if (pmouse->m_eflagMessage & ::message::e_flag_synthesized)
         {

            INFORMATION("synthesized e_message_mouse_move ignored!!");

         }
         else
         {

            //INFORMATION("e_message_mouse_move for experience::frame");

            if (m_pframe->on_message_mouse_move(pmouse))
            {

               pmouse->m_bRet = true;

            }

         }

      }

      if (pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }


   void frame_window::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      ASSERT(m_pframe != nullptr);

      m_pframe->on_message_left_button_up(pmouse);

      if (pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }


   void frame_window::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      ASSERT(m_pframe != nullptr);

      m_pframe->on_message_left_button_double_click(pmouse);

      if (pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }


   //void frame_window::on_message_set_cursor(::message::message* pmessage)
   //{

   //   ::pointer<::message::set_cursor>psetcursor(pmessage);

   //   if (!is_frame_experience_enabled())
   //   {

   //      return;

   //   }

   //   if (::is_set(m_pframe))
   //   {

   //      if (layout().m_eflag & ::user::interaction_layout::flag_apply_visual)
   //      {

   //         INFORMATION("e_message_mouse_move during window transfer ignored!!");

   //      }
   //      else if (psetcursor->m_eflagMessage & ::message::flag_synthesized)
   //      {

   //         INFORMATION("synthesized e_message_mouse_move ignored!!");

   //      }
   //      else
   //      {

   //         //INFORMATION("e_message_mouse_move for experience::frame");

   //         //if (m_pframe->on_message_set_cursor(psetcursor))
   //         //{

   //         //   psetcursor->m_bRet = true;

   //         //}

   //      }

   //   }

   //   if (psetcursor->m_bRet)
   //   {

   //      psetcursor->m_lresult = 1;

   //   }

   //}


   void frame_window::_001OnNcLButtonDown(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      ASSERT(m_pframe != nullptr);

      m_pframe->_001OnNcLButtonDown(pmouse);

      if (pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

   }

   void frame_window::_001OnNcMouseMove(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      ASSERT(m_pframe != nullptr);

      m_pframe->_001OnNcMouseMove(pmouse);

      if (pmouse->m_bRet)
      {
         pmouse->m_lresult = 1;
      }

   }

   void frame_window::_001OnNcLButtonUp(::message::message * pmessage)
   {
      auto pmouse = pmessage->m_union.m_pmouse;
      if (!is_frame_experience_enabled())
      {
         pmouse->m_bRet = false;
         return;
      }
      ASSERT(m_pframe != nullptr);
      m_pframe->_001OnNcLButtonUp(pmouse);
      if (pmouse->m_bRet)
      {
         pmouse->m_lresult = 1;
      }

   }


   void frame_window::_001OnNcHitTest(::message::message * pmessage)
   {

      ::pointer<::message::nc_hit_test>pnchittest(pmessage);

      if (!is_frame_experience_enabled())
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

      //   ptimer->destroy();

      //   return;

      //}

      //if(m_pframe != nullptr)
      //{

      //   if(!m_pframe->_001OnTimer((::u32) ptimer->m_uEvent))
      //   {

      //      ptimer->destroy();

      //   }

      //}

   }


   void frame_window::OnNcCalcSize(::rectangle_i32 * prectangle)
   {

      ASSERT(m_pframe != nullptr);

      m_pframe->OnNcCalcSize(prectangle);

   }


   // point_i32 should be in screen coordinates
   ::experience::enum_frame frame_window::experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   {

      ASSERT(m_pframe != nullptr);

      return m_pframe->experience_frame_hit_test(point, ::user::e_zorder_any);

   }


   void frame_window::set_frame(::experience::frame * pframe)
   {

      if (m_pframe != nullptr && m_pframe != pframe)
      {

         m_pframe->frame_on_detach();

         m_pframe->m_pframewindow = nullptr;

      }

      if (pframe == nullptr)
      {

         return;

      }

      __construct(m_pframe, pframe);

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


   //bool frame_window::_001CallOnBeforeAppearance()
   //{

   //   if (!_001OnBeforeAppearance())
   //   {

   //      display(const_layout().design().display());

   //      return false;

   //   }

   //   return true;

   //}


   bool frame_window::sketch_on_display()
   {

      if (!is_frame_experience_enabled())
      {

         return ::user::frame_window::sketch_on_display();

      }

      auto edisplay = const_layout().sketch().display();

      //auto eactivation = layout().sketch().activation();

      if (edisplay == e_display_iconic)
      {

         if (m_bitMinimizeToTray)
         {

            display(e_display_notify_icon);

         }

      }
      else if (edisplay == e_display_zoomed)
      {

         if (m_bFullScreenOnMaximize)
         {

            display(e_display_full_screen);

         }

      }
      else if (edisplay == ::e_display_up)
      {

         m_eupdown = e_updown_up;

      }
      else if (edisplay == ::e_display_down)
      {

         m_eupdown = e_updown_down;

      }

      if (!::user::frame_window::sketch_on_display())
      {

         return false;

      }

      return true;

   }


   void frame_window::display_docked(::e_display edisplay, ::e_activation eactivation)
   {

      if (!is_docking_appearance(edisplay))
      {

         throw ::exception(error_wrong_state);

      }

      set_display(edisplay);

      set_activation(eactivation);

   }


#define ZONEING_COMPARE ::comparison


   index frame_window::get_best_zoneing(::e_display & edisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleRequest, bool bPreserveSize)
   {

      //i64 g_i_get_best_zoneing = 0;

      ::rectangle_i32 rectangle;

      if (rectangleRequest.is_set())
      {

         rectangle = rectangleRequest;

      }
      else
      {

         rectangle = screen_rect();

      }

      ::rectangle_i32 rectangleWorkspace;

      index iBestWorkspace = get_best_workspace(&rectangleWorkspace, rectangle);

      if (rectangle.is_empty())
      {

         return iBestWorkspace;

      }

      auto sizeMinimum = get_window_minimum_size();

      if (rectangle.height() < sizeMinimum.cy())
      {

         rectangle.set_height(sizeMinimum.cy());

         rectangle._001ConstrainY(rectangleWorkspace);

      }

      if (rectangle.width() < sizeMinimum.cx())
      {

         rectangle.set_width(sizeMinimum.cx());

         rectangle._001ConstrainX(rectangleWorkspace);

      }

      if (iBestWorkspace >= 0)
      {

         ::rectangle_i32 rectangleOld(rectangle);

         auto pwindowing = windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_good_move(&rectangle, rectangleOld, this);

      }

      if (!is_docking_appearance(edisplay))
      {

         edisplay = e_display_none;

      }

      ::e_display edisplayPrevious = edisplay != e_display_none ? edisplay : const_layout().design().display();

      bool bCursorPosition = layout().is_moving();

      ::point_i32 pointCursor(e_no_initialize);

      if (bCursorPosition)
      {

         auto pwindow = window();

         pointCursor = pwindow->get_cursor_position();

      }

      auto psystem = acmesystem()->m_pbasesystem;

      double dMargin = psystem->m_dDpi * 0.75 * (1.0 - sqrt((double)rectangle.area() / (double)rectangleWorkspace.area()));

      if (ZONEING_COMPARE::is_equal(rectangle.top, rectangleWorkspace.top, dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rectangle.move_top_to(rectangleWorkspace.top);

         }
         else
         {

            rectangle.top = rectangleWorkspace.top;

         }

      }
      else
      {

         edisplay -= e_display_top;

      }

      if (ZONEING_COMPARE::is_equal(rectangleWorkspace.bottom, rectangle.bottom, dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rectangle.move_bottom_to(rectangleWorkspace.bottom);

         }
         else
         {

            rectangle.bottom = rectangleWorkspace.bottom;

         }

      }
      else
      {

         edisplay -= e_display_bottom;

      }

      if (ZONEING_COMPARE::is_equal(rectangle.left, rectangleWorkspace.left, dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rectangle.move_left_to(rectangleWorkspace.left);

         }
         else
         {

            rectangle.left = rectangleWorkspace.left;

         }

      }
      else
      {

         edisplay -= e_display_left;

      }

      if (ZONEING_COMPARE::is_equal(rectangleWorkspace.right, rectangle.right, dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rectangle.move_right_to(rectangleWorkspace.right);

         }
         else
         {

            rectangle.right = rectangleWorkspace.right;

         }

      }
      else
      {

         edisplay -= e_display_right;

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.top, rectangle.top, rectangle.bottom, rectangleWorkspace.bottom))
         {

            if (dock_manager()->window_is_docking())
            {

               edisplay |= e_display_bottom;

               edisplay |= e_display_top;

               rectangle.bottom = rectangleWorkspace.bottom;

               rectangle.top = rectangleWorkspace.top;

            }

         }
         else if ((edisplayPrevious & (e_display_left | e_display_right))
            != (edisplay & (e_display_left | e_display_right)))
         {

            edisplay = e_display_none;

         }

      }

      if (!(edisplay & e_display_left || edisplay & e_display_right)
         && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.left, rectangle.left, rectangle.right, rectangleWorkspace.right))
         {

            if (dock_manager()->window_is_docking())
            {

               edisplay |= e_display_left;

               edisplay |= e_display_right;

               rectangle.left = rectangleWorkspace.left;

               rectangle.right = rectangleWorkspace.right;

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

         if (const_layout().sketch().display() == e_display_full_screen)
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

         *prectangle = rectangleWorkspace;

      }
      else
      {

         *prectangle = rectangleRequest;

      }

      return iBestWorkspace;

   }


#undef ZONEING_COMPARE


   //void frame_window::_001OnAfterExitAppearance()
   //{
//
  // }


   //      void frame_window::on_message_dock_button_left_button_down(::message::message *pmessage)
   //      {
   //
   //         auto pmouse = pmessage->m_union.m_pmouse;
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
   //         //::rectangle_i32 rectangleWindow;
   //
   //         //ptopic->user_interaction()->window_rectangle(rectangleWindow);
   //
   //         ///dock_manager()->m_pointCursorOrigin = rectangleWindow.center();
   //
   //      }


   bool frame_window::_001OnBeforeEnterAppearance()
   {

      auto edisplayRequest = const_layout().sketch().display();

      if (edisplayRequest == e_display_notify_icon)
      {

         if (!window_is_notify_icon_enabled())
         {

            return false;

         }

      }

      return ::user::frame_window::_001OnBeforeEnterAppearance();

   }


   //bool frame_window::_001OnEnterFullScreen()
   //{

   //   return true;

   //}


   //void frame_window::_001OnExitFullScreen()
   //{

   //   ::user::box::_001OnExitFullScreen();

   //   set_need_layout();

   //}


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

      //auto rectangleCurrent = screen_rect();

      ::e_display edisplay = const_layout().sketch().display();

      if (equivalence_sink(edisplay) != e_display_normal)
      {

         if (equivalence_sink(m_windowrectangle.m_edisplayPrevious) == e_display_normal)
         {

            display_normal(m_windowrectangle.m_edisplayPrevious, e_activation_default);

         }
         else
         {

            display_normal(m_windowrectangle.m_edisplayLastNormal, e_activation_default);

         }

      }
      else if(edisplay == e_display_broad)
      {

         //if (m_windowrectangle.m_rectangleRestored.size() == m_sizeRestore)
         //{

         //good_restore(nullptr, m_windowrectangle.m_rectangleCompact, true, e_activation_default, e_zorder_top, e_display_compact);

         display_normal(e_display_compact, e_activation_default);

         //}
//         else
  //       {

      //      good_move(m_windowrectangle.m_rectangleRestored);

    //     }

      }
      else if (edisplay == e_display_compact)
      {

         auto sizeRectangleNormal = m_windowrectangle.m_rectangleNormal;

         if (sizeRectangleNormal == m_sizeRestoreCompact)
         {

            display_normal(e_display_broad, e_activation_default);

            //good_restore(nullptr, m_windowrectangle.m_rectangleBroad, true, e_activation_default, e_zorder_top, e_display_broad);

         }
         else
         {

            //good_restore(nullptr, m_windowrectangle.m_rectangleNormal, true, e_activation_default, e_zorder_top, e_display_normal);

            display_normal(e_display_normal, e_activation_default);

         }

      }
      else
      {

         //good_restore(nullptr, m_windowrectangle.m_rectangleBroad, true, e_activation_default, e_zorder_top, e_display_broad);

         display_normal(e_display_broad, e_activation_default);

      }

      set_reposition(true);

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }


} // namespace experience



