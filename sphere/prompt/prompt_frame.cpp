#include "framework.h"
#include "aura/update.h"


namespace prompt
{


   frame::frame(::layered * pobjectContext) :
      ::object(pobject),
      simple_frame_window(pobject),
      m_spqueue(e_create)
   {

      m_pimagelist = nullptr;


      m_bTimerHide = false;

      window_enable_full_screen();

      m_bMoveDrag = true;

   }


   frame::~frame()
   {

   }



   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }



   void frame::_001OnTimer(::timer * ptimer)
   {

      simple_frame_window::_001OnTimer(ptimer);;

      auto uEvent = ptimer->m_uEvent;

      static float theta;

      if(uEvent == 3)
      {

      }
      else if(uEvent == 1000)
      {
         KillTimer(uEvent);
         m_bTimerOn = false;

#ifdef WINDOWS_DESKTOP

         bool bLControlKeyDown = (GetAsyncKeyState (VK_LCONTROL) >> ((sizeof(SHORT) * 8) - 1)) != 0;
         bool bLAltKeyDown = (GetAsyncKeyState (VK_LMENU) >> ((sizeof(SHORT) * 8) - 1)) != 0;
         if(bLControlKeyDown && !bLAltKeyDown)
         {
            OnHoverAction(true);
         }
         else
         {
            hide();
         }

#else

         __throw(todo());

#endif

      }
      else if(uEvent == 1001)
      {
         KillTimer(uEvent);
         //
         //hide();
         
         display();
         
      }
      else if(uEvent == 8913)
      {
      }
      // every 100 ms approximately
      else if(uEvent == 4033)
      {
         /*      ::rect rectWindow;
               get_window_rect(rectWindow);
               ::point point;
               point = psession->get_cursor_pos();
               if(rectWindow.is_empty().contains(point) && !m_bTimerHide)
               {
                  m_bTimerHide = true;
                  SetTimer(1001, 800, nullptr);
               }
               else
               {
                  m_bTimerHide = false;
                  KillTimer(1001);
               }*/
         /*::point point;
         if(m_bHoverMouse && ::get_tick() > m_millisLastHover + 300)
         {
            OnHoverAction();
         }
         if(psession->get_cursor_pos(&pt))
         {
            if(!m_bHoverMouse && point.x == 0 && point.y == 0)
            {
               m_millisLastHover= ::millis::now();
               m_bHoverMouse = true;

            }
            else if(m_bHoverMouse && (point.x > 10 || point.y > 0))
            {
               m_bHoverMouse = false;
            }

         }*/
         // OpenGL animation code goes here

         //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
         //glClear( GL_COLOR_BUFFER_BIT );

         /*glPushMatrix();
         glRotatef( theta, 0.0f, 1.0f, 1.0f );
         glBegin( GL_TRIANGLES );
         glColor3f( 1.0f, 0.0f, 0.0f ); glVertgenf( 0.0f, 1.0f );
         glColor3f( 0.0f, 1.0f, 0.0f ); glVertgenf( 0.87f, -0.5f );
         glColor3f( 0.0f, 0.0f, 1.0f ); glVertgenf( -0.87f, -0.5f );
         glEnd();
         glPopMatrix();*/

         //SwapBuffers( m_hdcOpenGL );

         theta += 2.0f;

      }
      // simple_frame_window::OnTimer(uEvent);
   }


   void frame::ShowControlBars(bool bShow)
   {
      ::u32 nShow;
      if(bShow)
      {
         nShow = e_display_normal;
      }
      else
      {
         nShow = SW_HIDE;
      }

      /*   m_toolbar.ShowWindow(nShow);
         m_toolbarView.ShowWindow(nShow);
      //   m_statusbar.ShowWindow(nShow);
         m_menubar.ShowWindow(nShow);
         m_dialogbar.ShowWindow(nShow);*/

   }







   void frame::OnHoverAction(bool bShowWinActionArea)
   {
      if(!is_window_visible())
      {
         if(bShowWinActionArea)
         {
            if(GetActiveDocument() != nullptr)
            {
               GetActiveDocument()->update_all_views(id_select_main_tab);
            }
         }
         ToFront();
      }
   }


   void frame::_001OnClose(::message::message * pmessage)
   {
      
      pmessage->m_bRet = true;
      
      //hide();
      
      hide();
      
   }


   void frame::install_message_routing(::channel * pchannel)
   {
      simple_frame_window::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &frame::_001OnCreate);
      MESSAGE_LINK(e_message_close, pchannel, this, &frame::_001OnClose);
//
      MESSAGE_LINK(e_message_move, pchannel, this, &frame::_001OnMove);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &frame::_001OnShowWindow);
      MESSAGE_LINK(WM_APP + 2000, pchannel, this, &frame::_001OnApp2000);
   }

   void frame::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pmessage->previous();

      if(pmessage->m_bRet)
         return;

      if(!data_get("DockPosition", (i32 &) m_eposition))
      {

         m_eposition = e_position_left;

      }


      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);



      m_pimagelist = new image_list(get_object());
      m_pimagelist->create(16, 16, 0, 10, 10);
      m_pimagelist->add_matter_icon("system/language_change->ico");



      if (!LoadToolBar(0,"command\\toolbar.xml") )
      {
         pcreate->failed("Failed to create toolbar\n");
         pcreate->m_lresult =-1;
         pcreate->m_bRet = true;
         return;
      }

      if(!m_spqueue->create_message_queue("::ca2::account::message_wnd::command", this))
      {
         pcreate->m_lresult =-1;
         pcreate->m_bRet = true;
         return;
      }

   }

   void frame::_001OnMove(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      /*if(m_pframewindow->move_manager()->IsMoving())
      {
         oswindow oswindowDesktop = ::get_desktop_window();
         ::rect rectDesktop;
         ::get_window_rect(oswindowDesktop, rectDesktop);
         ::rect rectWindow;
         get_window_rect(rectWindow);
         double a = (double) rectDesktop.height() / (double) rectDesktop.width();
         if(rectWindow.left < (rectDesktop.width() / 2))
         {
            // to the left
            if(rectWindow.top < rectWindow.left * a)
            {
               // top
               m_eposition = e_position_top;
            }
            else if(rectWindow.top > (rectDesktop.height() - rectWindow.left * a))
            {
               // bottom
               m_eposition = e_position_bottom;
            }
            else
            {
               // left
               m_eposition = e_position_left;
            }
         }
         else
         {
            // to the right
            // to the left
            if(rectWindow.top > rectWindow.left * a)
            {
               // bottom
               m_eposition = e_position_bottom;
            }
            else if(rectWindow.top < (rectDesktop.height() - rectWindow.left * a))
            {
               // top
               m_eposition = e_position_top;
            }
            else
            {
               // right
               m_eposition = e_position_right;
            }
         }
         data_set("DockPosition", (i32) m_eposition);
      }*/
   }

   void frame::_001OnShowWindow(::message::message * pmessage)
   {
      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if(!pshowwindow->m_bShow)
      {
         if(GetActiveDocument() != nullptr)
            GetActiveDocument()->update_all_views(id_update_current_area);
      }
   }


   void frame::ToFront()
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);
      
      display(e_display_restore);
      
      bool bChanged = false;
      if(rectWindow.width() < 400)
      {
         rectWindow.right = rectWindow.left + 400;
         bChanged = true;
      }
      if(rectWindow.height() < 200)
      {
         rectWindow.bottom = rectWindow.top + 200;
         bChanged = true;
      }
      set_window_pos(      zorder_top_most,      rectWindow,      SWP_SHOWWINDOW);
   }

   void frame::message_queue_message_handler(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      if(pbase->m_id == (WM_APP + 2000))
      {
         _001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
   }

   void frame::_001OnApp2000(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);


      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 1)
         {
            m_bTimerOn = true;
            SetTimer(1000, 23, nullptr);
         }
         else if(pbase->m_lparam == 0)
         {
            KillTimer(1000);
            m_bTimerOn = false;
         }

      }
      else if(pbase->m_wparam == 1)
      {
         pbase->m_lresult =2;
      }
      else if(pbase->m_wparam == 2)
      {
         pbase->m_lresult =4;
      }
      else if(pbase->m_wparam == 3)
      {
         if(pbase->m_lparam == 6)
         {
            //GetTopLevelFrame()->hide();
            
            GetTopLevelFrame()->hide();
            
            __post_quit_message(36);
         }
      }
      else if(pbase->m_wparam == 4)
      {
         pbase->m_lresult =5;
      }
      else if(pbase->m_wparam == 5)
      {
         pbase->m_lresult =8;
      }
      else if(pbase->m_wparam == 8)
      {
         pbase->m_lresult =11;
      }
      else if(pbase->m_wparam == 11)
      {
         pbase->m_lresult =23;
      }
      else if(pbase->m_wparam == 23)
      {
         pbase->m_lresult =33;
      }
      else if(pbase->m_wparam == 33)
      {
         pbase->m_lresult =1;
      }
      pbase->m_bRet = true;
   }


   void frame::on_command(::user::command * pcommand)
   {

      if(pcommand->m_id == "app_exit")
      {

         simple_frame_window::OnClose();

         pcommand->m_bRet = true;

         return;

      }

      simple_frame_window::on_command(pcommand);

   }


   void frame::on_command_probe(::user::command * pcommand)
   {

      if(pcommand->m_id == "app_exit")
      {

         pcommand->enable();

         pcommand->m_bRet = true;

         return;

      }

   }


} // namespace prompt


