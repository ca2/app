#include "framework.h"
#include "frame_window.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/item.h"
#include "acme/platform/application_menu.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "apex/handler/signal.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/user/user/system.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"
#include "berg/platform/application.h"
#include "berg/platform/session.h"
#include "berg/user/user/user.h"
#include "department.h"
#include "frame.h"
#include "menu_manager.h"
#include "dock_manager.h"
#include "move_manager.h"
#include "size_manager.h"
#include "control_box.h"
#include "axis/user/user/list_box.h"
#include "berg/platform/system.h"


template < primitive_rectangle R1, primitive_rectangle R2 >
void constrain_vertex_left(R1 & r1, const R2 & r2)
{

   {

      auto diff = r2.left() - r1.right();

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

      auto diff = r2.right() - r1.left();

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

      auto diff = r2.top() - r1.bottom();

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

      auto diff = r2.bottom() - r1.top();

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

      m_bEnableDragResize = false;
      m_bEnableDefaultControlBox = false;

      m_bDefaultParentMouseMessageHandling = false;
      m_bDefaultMouseHoverHandling = true;

      m_eupdown = e_updown_normal_frame;

      m_pupdowntarget = nullptr;

      m_bFullScreenOnZoom = false;

      m_bInitialFramePosition = true;

   }


   frame_window::~frame_window()
   {

   }



#ifdef _DEBUG

   long long frame_window::increment_reference_count()
   {
      return ::user::frame_window::increment_reference_count();
   }
   long long frame_window::decrement_reference_count()
   {
      return ::user::frame_window::decrement_reference_count();
   }

#endif


   void frame_window::pre_translate_message(::message::message * pmessage)
   {

      //#ifdef WINDOWS_DESKTOP
      //
      //      if (pmessage->m_emessage == WM_GETTEXT)
      //      {
      //
      //         return;
      //
      //      }
      //      else if (pmessage->m_emessage == WM_GETTEXTLENGTH)
      //      {
      //
      //         return;
      //
      //      }
      //      else
      //
      //#endif

      if (pmessage->m_emessage == e_message_mouse_move)
      {

         return;

      }
      else if (pmessage->m_emessage == e_message_key_down
         || pmessage->m_emessage == e_message_key_up
         || pmessage->m_emessage == e_message_sys_key_down
         || pmessage->m_emessage == e_message_sys_key_up)
      {

         auto pkey = pmessage->m_union.m_pkey;

         

         if(pkey->user_interaction() == this)
         {

            if (pmessage->m_emessage == e_message_key_down || pmessage->m_emessage == e_message_sys_key_down)
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

                     if (session()->is_key_pressed(::user::e_key_control) && session()->is_key_pressed(::user::e_key_alt))
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
            else if (pmessage->m_emessage == e_message_key_up || pmessage->m_emessage == e_message_sys_key_up)
            {

               if (pkey->m_ekey == ::user::e_key_return)
               {

               }
               else if (pkey->m_ekey == ::user::e_key_alt || pkey->m_ekey == ::user::e_key_left_alt || pkey->m_ekey == ::user::e_key_right_alt)
               {

                  if (layout().is_full_screen() && session()->is_key_pressed(::user::e_key_control) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
                  {

                     pkey->m_bRet = true;

                     good_move(&m_windowdisplayandlayout.m_rectangleNormal);

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

                  if (layout().is_full_screen() && session()->is_key_pressed(::user::e_key_alt) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
                  {

                     pkey->m_bRet = true;

                     display_previous(pmessage->user_activation_token());

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


   ::pointer<::experience::experience>frame_window::create_experience(const ::scoped_string & scopedstrExperience)
   {

      auto puser = user();

      return puser->experience()->create_experience(this, scopedstrExperience);

   }


   ::pointer<::experience::experience>frame_window::experience(const ::scoped_string & scopedstrExperience)
   {

      auto puser = user();

      return puser->experience()->experience(this, scopedstrExperience);

   }


   ::pointer<::experience::frame>frame_window::frame_experience(const ::scoped_string & scopedstrExperience, const ::scoped_string & scopedstrFrame, const ::scoped_string & scopedstrStyle)
   {

      auto puser = user();

      auto pexperience = puser->experience();

      ::string strExperienceRequest(scopedstrExperience);

      if (strExperienceRequest.is_empty())
      {

         strExperienceRequest = m_papplication->preferred_experience();

      }

      auto pframe = pexperience->frame_experience(this, scopedstrExperience, scopedstrFrame);

      pframe->m_pframewindow = this;

      auto psignal = signal(id_user_style_change);

      psignal->add_handler(pframe);

      set_user_style(scopedstrStyle);

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

      //      int iMessage = pusermessage->id();


            //if (pusermessage->id() == WM_GETTEXT)
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
            //else if (pusermessage->id() == WM_GETTEXTLENGTH)
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

      ::user::frame_window::_001OnDraw(pgraphics);

      pgraphics->payload("log_fill_rectangle") = 0;

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

      pgraphics->payload("log_fill_rectangle") = 1;


   }


   void frame_window::on_defer_display()
   {

      if (m_bWindowFrame && m_pframe.is_set())
      {

         m_pframe->on_defer_display();

      }

   }


   void frame_window::enable_dock()
   {

      m_bDockEnable = true;

   }


   void frame_window::disable_dock()
   {

      m_bDockEnable = false;

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


   //void frame_window::GetRegionClientRectangle(::int_rectangle * prectangle)
   //{

   //   ASSERT(m_pframe != nullptr);

   //   m_pframe->get_client_rectangle(prectangle);

   //}



   void frame_window::initialize_frame_window_experience()
   {

      if (m_pdockmanager == nullptr)
      {

         m_pdockmanager = __initialize_new class dock_manager ();

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

         m_pmovemanager = __initialize_new class move_manager ();

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

         m_psizemanager = __initialize_new class size_manager ();

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

         m_pmenumanager = __initialize_new class menu_manager ();

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


   void frame_window::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == ::id_click && m_pframe != nullptr
          && m_pframe
          && m_pframe->get_control_box() != nullptr)
      {

         auto atom = ptopic->user_interaction_id();

         informationf("frame_window::handle_event btn_clkd=%s", string(atom).c_str());

         auto ebutton = m_pframe->get_control_box()->get_control_box_button_type(atom);

         switch (ebutton)
         {
         case e_button_close:

            informationf("button_clicked : button_close");

            post_message(e_message_close);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_minimize:

            informationf("button_clicked : button_minimize");

            window_minimize();

            ptopic->m_bRet = true;

            return;

         case e_button_maximize:

            informationf("button_clicked : button_maximize");

            window_maximize();

            // display(e_display_zoomed);
            //
            // set_reposition(true);
            //
            // set_need_layout();
            //
            // set_need_redraw();
            //
            // post_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_restore:

            informationf("button_clicked : button_restore");

            frame_experience_restore();

            ptopic->m_bRet = true;

            return;

         case e_button_up:

            informationf("button_clicked : button_up");

            display(e_display_up);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_down:

            informationf("button_clicked : button_down");

            display(e_display_down);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_transparent_frame:

            informationf("button_clicked : button_transparent_frame");

            toggle_appearance(e_appearance_transparent_frame);

            defer_save_window_placement();

            if (!is_this_visible())
            {

               display();

            }

            set_reposition();

            set_need_layout();

            set_need_redraw();

            post_redraw();

            ptopic->m_bRet = true;

            return;

         case e_button_notify_icon:

            informationf("button_clicked : button_notify_icon");

            display(e_display_notify_icon);

            set_need_redraw();

            ptopic->m_bRet = true;

            return;

         default:

            break;

         }

      }
      else if (ptopic->id() == id_app_activated)
      {

         frame_toggle_restore(ptopic->m_actioncontext.user_activation_token());

      }

      ::user::frame_window::handle(ptopic, phandlercontext);

   }


   void frame_window::on_command(::message::command * pcommand)
   {

      if (pcommand->m_emessage == ::e_message_system_command && m_pframe != nullptr)
      {

         auto ebutton = m_pframe->get_control_box()->get_control_box_button_type(pcommand->command_id());

         switch (ebutton)
         {
         case e_button_close:

            post_message(e_message_close);

            set_need_redraw();

            pcommand->m_bRet = true;

            return;

         case e_button_minimize:

            display(e_display_iconic, { ::user::e_activation_no_activate } );

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

      display(e_display_iconic, { ::user::e_activation_no_activate } );

   }


   void frame_window::display_previous_restore()
   {

      if (::is_screen_visible(m_windowdisplayandlayout.m_edisplayPrevious))
      {

         return display(m_windowdisplayandlayout.m_edisplayPrevious);

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


   //  define System flags que serao usados para posicionar ou
   //  dimensionar pelo uso da funcao set_window_position

   void frame_window::SetSWPFlags(unsigned int uFlags)
   {

      m_uiSWPFlags = uFlags;

      //m_pmovemanager->SetSWPFlags(m_uiSWPFlags);

      //m_psizemanager->SetSWPFlags(m_uiSWPFlags);

   }


   void frame_window::SetActiveFlag(bool fActive)
   {

      if (is_different(fActive, m_fActive))
      {

         //informationf("frame_window::SetActiveFlag %d\n", fActive);

         m_fActive = fActive;

         if (fActive)
         {
            
            informationf("frame_window::SetActiveFlag Active");
            
         }
         else
         {

            informationf("frame_window::SetActiveFlag Not Active");

         }

         if (m_pframe != nullptr)
         {

            m_pframe->OnActivate();

         }

         if (this->m_ewindowflag & ::e_window_flag_window_created)
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


   void frame_window::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //::user::frame_window::on_perform_top_down_layout(pgraphics);

      if (!is_frame_experience_enabled())
      {

         ::user::frame_window::on_perform_top_down_layout(pgraphics);

         return;

      }

      ::user::main_window::on_perform_top_down_layout(pgraphics);

      //::int_rectangle frame_window::rectangle(::user::enum_layout elayout)
      //{

         //information() << "experience::frame_experience::on_perform_top_down_layout (2)";

         if (::is_set(m_pframe))
         {

            //information() << "experience::frame_experience::on_perform_top_down_layout m_pframe is_set";

            auto rectangleHosting = this->rectangle(::user::e_layout_lading);

            m_pframe->calculate_hosting_rectangle(&rectangleHosting, pgraphics);

            m_rectangleHosting = rectangleHosting;

           // return ::user::frame_window::rectangle(elayout);

         }

         //return m_pframe->rectangle(elayout);

      //}

      if (m_pframe != nullptr)
      {

         m_pframe->on_perform_top_down_layout(pgraphics);

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

         m_psizemanager = __initialize_new class size_manager ();

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

      SetActiveFlag(pactivate->m_eactivate == e_activate_active || pactivate->m_eactivate == e_activate_click_active);

      pactivate->m_bRet = true;

      pactivate->m_lresult = 0;

   }


   bool frame_window::is_full_screen_enabled()
   {

      return m_bFullScreenEnable;

   }


   ::int_rectangle frame_window::outer_frame()
   {

      return m_pframe->outer_frame();

   }


   ::item_pointer frame_window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
   {

      //if (is_sizing_enabled())
      //{

      //   if (::is_item_set(m_psizemanager->m_pitemCursor))
      //   {

      //      return m_psizemanager->m_pitemCursor;

      //      //switch (m_psizemanager->m_eframeCursor)
      //      //{
      //      //case e_frame_sizing_left:
      //      //   return øallocate ::item(e_element_resize_left);
      //      //case e_frame_sizing_top:
      //      //   return øallocate ::item(e_element_resize_top);
      //      //case e_frame_sizing_right:
      //      //   return øallocate ::item(e_element_resize_right);
      //      //case e_frame_sizing_bottom:
      //      //   return øallocate ::item(e_element_resize_bottom);
      //      //case e_frame_sizing_top_left:
      //      //   return øallocate ::item(e_element_resize_top_left);
      //      //case e_frame_sizing_top_right:
      //      //   return øallocate ::item(e_element_resize_top_right);
      //      //case e_frame_sizing_bottom_left:
      //      //   return øallocate ::item(e_element_resize_bottom_left);
      //      //case e_frame_sizing_bottom_right:
      //      //   return øallocate ::item(e_element_resize_bottom_right);
      //      //   default:
      //      //      
      //      //      return nullptr;

      //      //}

      //   }

      //}

      return ::user::frame_window::hit_test(pmouse, ezorder);

   }


   void frame_window::window_enable_full_screen(bool bEnable)
   {

      m_bFullScreenEnable = bEnable;

   }


   void frame_window::install_message_routing(::channel * pchannel)
   {

      ::user::frame_window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &frame_window::on_message_create);
      MESSAGE_LINK(e_message_parent_left_button_down, pchannel, this, &frame_window::on_message_parent_left_button_down);
      MESSAGE_LINK(e_message_parent_left_button_up, pchannel, this, &frame_window::on_message_parent_left_button_up);
      //MESSAGE_LINK(e_message_parent_left_button_double_click, pchannel, this, &frame_window::on_message_parent_left_button_double_click);
      MESSAGE_LINK(e_message_parent_mouse_move, pchannel, this, &frame_window::on_message_parent_mouse_move);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &frame_window::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &frame_window::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &frame_window::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &frame_window::on_message_right_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &frame_window::on_message_mouse_move);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, this, &frame_window::_001OnNcLButtonDown);
      MESSAGE_LINK(e_message_non_client_left_button_up, pchannel, this, &frame_window::_001OnNcLButtonUp);
      MESSAGE_LINK(e_message_non_client_mouse_move, pchannel, this, &frame_window::_001OnNcMouseMove);
      MESSAGE_LINK(e_message_non_client_hit_test, pchannel, this, &frame_window::_001OnNcHitTest);
      MESSAGE_LINK(e_message_activate, pchannel, this, &frame_window::_001OnActivate);

      MESSAGE_LINK(e_message_size, pchannel, this, &frame_window::on_message_size);

   }


   void frame_window::on_message_create(::message::message * pmessage)
   {

      if(!windowing()->has_readily_gettable_absolute_coordinates()
      || !windowing()->display()->has_readily_gettable_absolute_pointer_position())
      {

         disable_dock();

      }

      if(m_pusersystem && m_pusersystem->m_bWindowFrame)
      {

         m_bWindowFrame = true;

      }
      
      auto papp = get_app();
      
      if (m_bWindowFrame.undefined())
      {

         auto & bApplicationExperienceMainFrame = papp->m_bExperienceMainFrame;

         if (bApplicationExperienceMainFrame.is_set())
         {

            if (get_parent() == nullptr)
            {

               m_bWindowFrame = bApplicationExperienceMainFrame;

            }
            else
            {

               m_bWindowFrame = false;

            }

         }
//         else if(windowing()->is_sandboxed())
//         {
//            
//            m_bWindowFrame = false;
//            
//         }
//         else
         {

            m_bWindowFrame = get_parent() == nullptr || wfi_has_up_down();

         }

      }
      
      //if(m_bWindowFrame)
      //{
      //   
      //   auto papplicationmenu = application()->application_menu();
      //   
      //   {
      //      
      //      auto ppopupView = papplicationmenu->popup("View");
      //      
      //      //ppopupView->add(pmenuView);
      //      
      //      ppopupView->item("Transparent Frame", "transparent_frame", "", "");
      //      
      //   }

      //   application()->application_menu_update();
      //   
      //}

   }


   void frame_window::on_message_size(::message::message * pmessage)
   {

      ::cast < ::message::size > psize(pmessage);

      if(psize->m_wparam & 1024)
      {

         m_bNeedPerformLayout = true;

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

   }


   void frame_window::on_message_parent_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_frame_experience_enabled())
      {

         pmouse->m_bRet = false;

         return;

      }

      if (::is_set(m_pframe))
      {

         m_pframe->on_message_parent_left_button_down(pmouse);

      }

      if (pmouse->m_bRet)
      {

         pmouse->m_lresult = 1;

      }

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

      //if (pmouse->m_bRet)
      //{

      //   pmouse->m_lresult = 1;

      //}

   }


//   void frame_window::on_visual_applied()
//   {
//
//      ::user::frame_window::on_visual_applied();
//
//
//   }


   void frame_window::on_message_parent_mouse_move(::message::message * pmessage)
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

            //information() << "e_message_mouse_move during window transfer ignored!!";

         }
         else if (pmouse->m_eflagMessage & ::message::e_flag_synthesized)
         {

            information() << "synthesized e_message_mouse_move ignored!!";

         }
         else
         {

            //information() << "e_message_mouse_move for experience::frame";

            if (m_pframe->on_message_parent_mouse_move(pmouse))
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

            //information() << "e_message_mouse_move during window transfer ignored!!";

         }
         else if (pmouse->m_eflagMessage & ::message::e_flag_synthesized)
         {

            information() << "synthesized e_message_mouse_move ignored!!";

         }
         else
         {

            //information() << "e_message_mouse_move for experience::frame";

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


   void frame_window::on_message_parent_left_button_up(::message::message * pmessage)
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


   void frame_window::on_message_left_button_up(::message::message * pmessage)
   {

      //auto pmouse = pmessage->m_union.m_pmouse;

      //if (!is_frame_experience_enabled())
      //{

      //   pmouse->m_bRet = false;

      //   return;

      //}

      //ASSERT(m_pframe != nullptr);

      //m_pframe->on_message_left_button_up(pmouse);

      //if (pmouse->m_bRet)
      //{

      //   pmouse->m_lresult = 1;

      //}

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


   void frame_window::on_message_right_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pitem = update_hover(pmouse, ::user::e_zorder_any);

      if (pitem)
      {

         if (pitem->m_item.m_eelement == e_element_title_bar)
         {

            window()->defer_show_system_menu(pmouse);

         }

      }

      //if (!is_frame_experience_enabled())
      //{

      //   pmouse->m_bRet = false;

      //   return;

      //}

      //ASSERT(m_pframe != nullptr);

      //m_pframe->on_message_left_button_up(pmouse);

      //if (pmouse->m_bRet)
      //{

      //   pmouse->m_lresult = 1;

      //}

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

   //         information() << "e_message_mouse_move during window transfer ignored!!";

   //      }
   //      else if (psetcursor->m_eflagMessage & ::message::flag_synthesized)
   //      {

   //         information() << "synthesized e_message_mouse_move ignored!!";

   //      }
   //      else
   //      {

   //         //information() << "e_message_mouse_move for experience::frame";

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


   void frame_window::on_timer(::timer * ptimer)
   {

      //if(!is_frame_experience_enabled())
      //{

      //   ptimer->destroy();

      //   return;

      //}

      //if(m_pframe != nullptr)
      //{

      //   if(!m_pframe->on_timer((unsigned int) ptimer->m_uTimer))
      //   {

      //      ptimer->destroy();

      //   }

      //}

   }


   void frame_window::OnNcCalcSize(::int_rectangle * prectangle)
   {

      ASSERT(m_pframe != nullptr);

      m_pframe->OnNcCalcSize(prectangle);

   }


   // int_point should be in screen coordinates
   ::experience::enum_frame frame_window::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   //::item_pointer frame_window::experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
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

      m_pframe = pframe;

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

      //auto useractivation = layout().sketch().activation();

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


   void frame_window::display_docked(::e_display edisplay, const ::user::activation & useractivation)
   {

      if (!is_docking_appearance(edisplay))
      {

         throw ::exception(error_wrong_state);

      }

      set_display(edisplay);

      set_activation(useractivation);

   }


#define ZONEING_COMPARE ::comparison


   ::collection::index frame_window::get_best_zoneing(::e_display & edisplay, ::int_rectangle * prectangle, const ::int_rectangle & rectangleRequest, bool bPreserveSize)
   {

      //long long g_i_get_best_zoneing = 0;

      ::int_rectangle rectangle;

      if (rectangleRequest.is_set())
      {

         rectangle = rectangleRequest;

      }
      else
      {

         rectangle = screen_rectangle();

      }

      ::int_rectangle rectangleWorkspace;

      ::collection::index iBestWorkspace = get_best_workspace(&rectangleWorkspace, rectangle);

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

         ::int_rectangle rectangleOld(rectangle);

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

      ::int_point pointCursor(no_initialize_t{});

      if (bCursorPosition)
      {

         //auto pwindow = window();

         pointCursor = window()->m_pointCursor2;

      }

      auto psystem = system();

      double dMargin = psystem->m_dDpi * 0.75 * (1.0 - sqrt((double)rectangle.area() / (double)rectangleWorkspace.area()));

      if (ZONEING_COMPARE::is_equal(rectangle.top(), rectangleWorkspace.top(), dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rectangle.move_top_to(rectangleWorkspace.top());

         }
         else
         {

            rectangle.top() = rectangleWorkspace.top();

         }

      }
      else
      {

         edisplay -= e_display_top;

      }

      if (ZONEING_COMPARE::is_equal(rectangleWorkspace.bottom(), rectangle.bottom(), dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rectangle.move_bottom_to(rectangleWorkspace.bottom());

         }
         else
         {

            rectangle.bottom() = rectangleWorkspace.bottom();

         }

      }
      else
      {

         edisplay -= e_display_bottom;

      }

      if (ZONEING_COMPARE::is_equal(rectangle.left(), rectangleWorkspace.left(), dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rectangle.move_left_to(rectangleWorkspace.left());

         }
         else
         {

            rectangle.left() = rectangleWorkspace.left();

         }

      }
      else
      {

         edisplay -= e_display_left;

      }

      if (ZONEING_COMPARE::is_equal(rectangleWorkspace.right(), rectangle.right(), dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rectangle.move_right_to(rectangleWorkspace.right());

         }
         else
         {

            rectangle.right() = rectangleWorkspace.right();

         }

      }
      else
      {

         edisplay -= e_display_right;

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.top(), rectangle.top(), rectangle.bottom(), rectangleWorkspace.bottom()))
         {

            if (dock_manager()->window_is_docking())
            {

               edisplay |= e_display_bottom;

               edisplay |= e_display_top;

               rectangle.bottom() = rectangleWorkspace.bottom();

               rectangle.top() = rectangleWorkspace.top();

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

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.left(), rectangle.left(), rectangle.right(), rectangleWorkspace.right()))
         {

            if (dock_manager()->window_is_docking())
            {

               edisplay |= e_display_left;

               edisplay |= e_display_right;

               rectangle.left() = rectangleWorkspace.left();

               rectangle.right() = rectangleWorkspace.right();

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


   ::item_pointer frame_window::on_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   {

      if (!m_pframe)
      {

         return nullptr;

      }

       auto eframe = m_pframe->experience_frame_hit_test(point, ezorder);

       if (eframe == ::experience::e_frame_title_bar)
       {

          auto pitem = øallocate ::item(::e_element_title_bar, 0);

          pitem->initialize(this);

          return pitem;

       }

       auto pitem = ::user::frame_window::on_hit_test(point, ezorder);

       if (!pitem)
       {

          return nullptr;

       }

       return pitem;

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
   //         //::int_rectangle rectangleWindow;
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


   bool frame_window::is_window_resizing()
   {

      if(!size_manager())
      {

         return false;

      }

      return size_manager()->window_is_sizing();

   }


   bool frame_window::is_window_repositioning()
   {

      if(!move_manager())
      {

         return false;

      }

      return move_manager()->window_is_moving();

   }


   bool frame_window::is_window_docking()
   {

      if(!dock_manager())
      {

         return false;

      }

      return dock_manager()->window_is_docking();

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


   void frame_window::frame_experience_restore(const ::user::activation & useractivation)
   {

      if(system()->acme_windowing()->get_ewindowing() == ::windowing::e_windowing_wayland)
      {

         window_restore();

         return;

      }

      calculate_broad_and_compact_restore();

      //auto rectangleCurrent = screen_rect();

      ::e_display edisplay = const_layout().sketch().display();

      if (equivalence_sink(edisplay) != e_display_normal)
      {

         if (equivalence_sink(m_windowdisplayandlayout.m_edisplayPrevious) == e_display_normal)
         {

            display_normal(m_windowdisplayandlayout.m_edisplayPrevious, useractivation);

         }
         else
         {

            display_normal(m_windowdisplayandlayout.m_edisplayLastNormal, useractivation);

         }

      }
      else if(edisplay == e_display_broad)
      {

         //if (m_windowdisplayandlayout.m_rectangleRestored.size() == m_sizeRestore)
         //{

         //good_restore(nullptr, m_windowdisplayandlayout.m_rectangleCompact, true, ::user::e_activation_default, e_zorder_top, e_display_compact);

         display_normal(e_display_compact, useractivation);

         //}
//         else
  //       {

      //      good_move(m_windowdisplayandlayout.m_rectangleRestored);

    //     }

      }
      else if (edisplay == e_display_compact)
      {

         auto sizeRectangleNormal = m_windowdisplayandlayout.m_rectangleNormal;

         if (sizeRectangleNormal == m_rectangleRestoreCompact.size())
         {

            display_normal(e_display_broad, useractivation);

            //good_restore(nullptr, m_windowdisplayandlayout.m_rectangleBroad, true, ::user::e_activation_default, e_zorder_top, e_display_broad);

         }
         else
         {

            //good_restore(nullptr, m_windowdisplayandlayout.m_rectangleNormal, true, ::user::e_activation_default, e_zorder_top, e_display_normal);

            display_normal(e_display_normal, useractivation);

         }

      }
      else
      {

         //good_restore(nullptr, m_windowdisplayandlayout.m_rectangleBroad, true, ::user::e_activation_default, e_zorder_top, e_display_broad);

         display_normal(e_display_broad, useractivation);

      }

      set_reposition(true);

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }


   void frame_window::place_set_need_redraw(const ::int_rectangle & rectangleAfter, const ::int_rectangle & rectangleBefore, ::draw2d::graphics * pgraphics)
   {

      if (::is_null(m_pframe))
      {

         ::user::frame_window::place_set_need_redraw(rectangleAfter, rectangleBefore, pgraphics);

         return;
      }
      m_pframe->place_set_need_redraw(rectangleAfter, rectangleBefore, pgraphics);
   }


   void frame_window::destroy()
   {

      m_pmovemanager.defer_destroy();
      m_psizemanager.defer_destroy();
      m_pdockmanager.defer_destroy();
      m_pmenumanager.defer_destroy();

      m_pframe.defer_destroy();


      ::user::frame_window::destroy();

   }


   void frame_window::_001OnAfterEnterZoomed()
   {

      ::user::frame_window::_001OnAfterEnterZoomed();

      if(m_bWindowFrame)
      {

         m_pframe->m_pcontrolbox->hide_button(e_button_maximize);

         m_pframe->m_pcontrolbox->layout_control_box_buttons();

      }

   }


   void frame_window::_001OnAfterExitZoomed()
   {

      ::user::frame_window::_001OnAfterEnterZoomed();

      if(m_bWindowFrame)
      {

         m_pframe->m_pcontrolbox->hide_button(e_button_maximize, false);

         m_pframe->m_pcontrolbox->layout_control_box_buttons();

      }

   }


} // namespace experience



