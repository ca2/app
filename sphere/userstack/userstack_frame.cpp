#include "framework.h"


namespace userstack
{


   frame::frame(::layered * pobjectContext) :
      ::object(pobject),
      simple_frame_window(pobject),
      m_spqueue(e_create)
   {

      m_pdocument = nullptr;

      window_enable_full_screen();

      m_bLayered = true;

      set_translucent();

      m_ppaneview = nullptr;

      m_bMouseOver = false;

   }


   frame::~frame()
   {

   }


   void frame::_001OnCreate(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      m_bWindowFrame = true;

      m_bWindowFrame = GetTypedParent < ::plugin::host_interaction >() == nullptr;

      if(pmessage->previous())
         return;

      if(!m_spqueue->create_message_queue("::ca2::account::message_wnd::bergedge::" + System.get_local_mutex_id(), this))
      {
         pcreate->m_lresult= -1;
         pcreate->m_bRet = true;
         return;
      }

      set_window_text("bergedge");

   }


   void frame::install_message_routing(::channel * pchannel)
   {
      simple_frame_window::install_message_routing(pchannel);
      //MESSAGE_LINK(e_message_close,          pchannel, this, &frame::_001OnClose);
//      //MESSAGE_LINK(e_message_timer,          pchannel, this, &frame::_001OnTimer);
      MESSAGE_LINK(e_message_create,         pchannel, this, &frame::_001OnCreate);
      MESSAGE_LINK(WM_APP + 1,        pchannel, this, &frame::_001OnApp1);
      MESSAGE_LINK(e_message_mouse_leave,     pchannel, this, &frame::_001OnMouseLeave);
   }


   bool frame::pre_create_window(::user::create_struct * pcreatestruct)
   {

      if( !simple_frame_window::pre_create_window(pcreatestruct) )
         return FALSE;

      pcreatestruct->m_createstruct.dwExStyle &= ~WS_EX_WINDOWEDGE;

      return TRUE;

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
         
         display();
         
         KillTimer(uEvent);
         
         m_bTimerOn = false;

      }
      else if(uEvent == 8913)
      {
      }
      else if(uEvent == 4033)
      {
         ::point point;
         if(m_bHoverMouse && ::get_tick() > m_millisLastHover + 300)
         {
            OnHoverAction();
         }
         point = psession->get_cursor_pos();
         if(!m_bHoverMouse && point.x == 0 && point.y == 0)
         {
            m_millisLastHover = ::millis::now();
            m_bHoverMouse = true;

         }
         else if(m_bHoverMouse && (point.x > 10 || point.y > 0))
         {
            m_bHoverMouse = false;
         }
         theta += 2.0f;

      }
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
   }



   void frame::_000OnMouse(::message::mouse * pmouse)
   {
      psession->m_pointCursor = pmouse->m_point;
//      ::aspheresp(::aura::application) pappParent = &App(Application.get_context_application()->m_pcoreapp);
//      ::aspheresp(::aura::application) papp = &Application;
      /*      if(pmouse->m_uiMessage == e_message_mouse_move
            && m_pdocument != nullptr
            && m_pdocument->m_pplatformdocument != nullptr
            && m_pdocument->m_pplatformdocument->get_platform_frame() != nullptr)
            {
               ::rect rectClient;
               get_client_rect(rectClient);
               ::point point = pmouse->m_point;
               _001ScreenToClient(point);
               if(rectClient.contains(point))
               {
                  get_wnd()->set_capture();
                  if(!m_bMouseOver)
                  {
                     m_bMouseOver = true;
                     m_pdocument->m_pplatformdocument->get_platform_frame()->super_dock_on_bergedge();
                  }
               }
               else
               {
                  get_wnd()->release_capture();
                  m_bMouseOver = false;
                  m_pdocument->m_pplatformdocument->get_platform_frame()->super_dock_on_bergedge();
               }
            }*/
      simple_frame_window::_000OnMouse(pmouse);
   }

   void frame::_001OnMouseLeave(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

//      __pointer(::message::mouse) pmouse(pmessage);
//      m_bMouseOver = false;
//      bergedgesp(::aura::application) papp = dynamic_cast < bergedgesp(::aura::application) > (get_object());
   }

   void frame::pre_translate_message(::message::message * pmessage)
   {
//      __pointer(::message::base) pbase(pmessage);
      simple_frame_window::pre_translate_message(pmessage);
   }


   void frame::OnHoverAction()
   {
      if(layout().is_full_screen())
      {
         //      bergedge::get_context_application()->show_platform();
      }
      else
      {
         display(e_display_full_screen);
      }
   }


   void frame::message_handler(::message::base * pbase)
   {

      simple_frame_window::message_handler(pbase);

   }


   void frame::message_queue_message_handler(::message::message * pmessage)
   {
      __pointer(::message::base) pbase(pmessage);
      if(pbase->m_id == (WM_APP + 2000))
      {
         _001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
      else if(pbase->m_id == WM_COPYDATA)
      {
#ifdef WINDOWS_DESKTOP
         i32 iEdge = 0;
         COPYDATASTRUCT * pstruct = (COPYDATASTRUCT *) pbase->m_lparam.m_lparam;
         if(pstruct->dwData == 2000)
         {
            ::memory_file file(pstruct->lpData, pstruct->cbData);
            string strPath;
            file.to_string(strPath);
            psession->open_by_file_extension(strPath);
         }
#else
         __throw(todo());
#endif
      }

   }


   void frame::_001OnApp2000(::message::message * pmessage)
   {
      __pointer(::message::base) pbase(pmessage);


      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 2)
         {
            //OnHoverAction(true);
            //display(e_display_normal);
            
            display();
            
            set_window_pos(zorder_top, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
            display(e_display_full_screen);
         }
         else if(pbase->m_lparam == 5)
         {
#ifdef WINDOWS_DESKTOP
            ::rect rect;
            ::GetWindowRect(::get_desktop_window(), rect);
            ::point point = rect.center();
            if(!is_window_visible()
                  || ::WindowFromPoint(point) != get_safe_handle())
            {
               display(e_display_full_screen);
            }
            else
            {
               hide();
            }
#else
            __throw(todo());
#endif
         }
      }
      /*         else if(pbase->m_lparam == 1)
               {
                  m_bTimerOn = true;
                  SetTimer(1000, 23, nullptr);
               }
               else if(pbase->m_lparam == 0)
               {
                  KillTimer(1000);
                  m_bTimerOn = false;
               }
               else if(pbase->m_lparam == 3)
               {
                 hide();
               }
        */
      /*  }
      */
      else if(pbase->m_wparam == 33)
      {
         string str = System.get_local_mutex_id();
         ::str::begins_eat_ci(str, "bergedge");
         i32 iEdge = atoi(str);
         if(iEdge == 0)
            iEdge = 77;
         else
            iEdge += 2000;
         pbase->m_lresult = iEdge;
      }
      else if(pbase->m_wparam == 25)
      {
#ifdef WINDOWS_DESKTOP
         pbase->m_lresult = (LRESULT) top_level_frame()->get_safe_handle();
#else
         __throw(todo());
#endif
      }
      pbase->m_bRet = true;
   }

   /*else if(pbase->m_wparam == 1)
   {
      pbase->set_lresult(2);
   }
   else if(pbase->m_wparam == 2)
   {
      pbase->set_lresult(4);
   }
   else if(pbase->m_wparam == 3)
   {
      if(pbase->m_lparam == 6)
      {
         top_level_frame()->hide();
         __post_quit_message(36);
      }
   }
   else if(pbase->m_wparam == 4)
   {
      pbase->set_lresult(5);
   }
   else if(pbase->m_wparam == 5)
   {
      pbase->set_lresult(8);
   }
   else if(pbase->m_wparam == 8)
   {
      pbase->set_lresult(11);
   }
   else if(pbase->m_wparam == 11)
   {
      pbase->set_lresult(23);
   }
   else if(pbase->m_wparam == 23)
   {
      pbase->set_lresult(33);
   }
   else if(pbase->m_wparam == 33)
   {
      pbase->set_lresult(68);
   }
   pbase->m_bRet = true;*/
   //}


   void frame::_001OnApp1(::message::message * pmessage)
   {

#ifdef WINDOWS_DESKTOP

      __pointer(::message::base) pbase(pmessage);

      MESSAGE * pmsg = (MESSAGE *) pbase->m_lparam.m_lparam;

      pmsg->hwnd = get_safe_handle();

      try
      {

         if(pmsg->message != WM_KICKIDLE)
         {

            ::pointer < ::message::base > spbase;

            spbase = Application.get_message_base(pmsg);

            pre_translate_message(spbase);

            if(!spbase->m_bRet)
            {

               send(spbase);

            }

         }

      }
      catch(const ::exception::exception & )
      {
      }
      catch(...)
      {
      }

      delete pmsg;

#else

      __throw(todo());

#endif

   }


} // namespace userstack



