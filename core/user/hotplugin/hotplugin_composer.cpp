#include "framework.h"



namespace hotplugin
{


   composer::composer()
   {

      m_bFocus                   = false;

      m_bActive                  = false;

      m_bActivationStateSent     = false;

      m_bSendActivationState     = false;

      m_bRectSent                = false;

      m_bInit                 = true; // default implemenation assume initialized on construction, derivations may change it

      m_estate               = state_start_axis_system;
      m_bBaseSystemOk         = false;
      m_bComposerSystemOk     = false;
      m_bTryInitHost          = false;
      m_bHostOk               = false;
      m_bTryInitWindow        = false;
      m_bWindowOk             = false;
      m_bOk                   = false;
      m_bResponsive           = true;
      m_bWrite                = false;
      m_bEntryHallTextStarted = false;

      m_pcomposersystem       = nullptr;

      m_paxishost             = nullptr;

      m_bHostInit             = false;

   }


   composer::~composer()
   {

   }


   ::hotplugin::host * composer::create_host(__pointer(::aura::system) psystem)
   {

      return nullptr;

   }


   void composer::hotplugin_composer_on_timer()
   {

      if(m_estate == state_start_axis_system)
      {

         if(m_bBaseSystemOk)
         {

            m_estate = state_start_composer_system;

         }
         else
         {

            if(::hotplugin::get_aura_system() == nullptr)
            {

               ::hotplugin::defer_start_base_system();

            }
            else
            {


               if(::hotplugin::get_aura_system()->m_bReady)
               {

                  if(::hotplugin::get_aura_system()->get_result_status() != 0)
                  {

                     string str;

                     str.format("::hotplugin::g_pbasesystem initialization error %d",::hotplugin::get_aura_system()->get_result_status());

                     ::output_debug_string(str);

                  }
                  else
                  {

                     m_bBaseSystemOk = true;

                  }

               }

            }


         }


      }
      else if(m_estate == state_start_composer_system)
      {

         if(m_bComposerSystemOk)
         {

            m_estate = state_start_host;

         }
         else
         {

            if(get_composer_system() == nullptr)
            {

               defer_start_composer_system();

            }
            else
            {


               if(get_composer_system()->m_bReady)
               {

                  if(get_composer_system()->get_result_status() != 0)
                  {

                     string str;

                     str.format("m_pcomposersystem initialization error %d",get_composer_system()->get_result_status());

                     ::output_debug_string(str);

                  }
                  else
                  {

                     m_bComposerSystemOk = true;

                  }

               }

            }


         }


      }
      else if(m_estate == state_start_host)
      {

         if(m_bHostOk)
         {

            m_estate = state_init_host;

         }
         else if(m_bInit)
         {

            if(m_paxishost == nullptr)
            {

               m_paxishost = create_host(get_composer_system());

               m_paxishost->m_pbasecomposer = this;

               m_paxishost->hotplugin_host_begin();

            }
            else
            {

               if(m_paxishost->m_bReady)
               {

                  if(m_paxishost->get_result_status() != 0)
                  {

                     string str;

                     str.format("::hotplugin::composer::m_paxishost initialization error %d",::hotplugin::get_aura_system()->get_result_status());

                     ::output_debug_string(str);

                  }
                  else
                  {

                     m_bHostOk = true;

                  }

               }

            }

         }

      }
      else if(m_estate == state_init_host)
      {

         if(m_bHostInit)
         {

            m_estate = state_start_window;

         }
         else
         {

            m_bTryInitHost = true;

            if(!m_paxishost->hotplugin_host_is_initialized())
            {

               if(m_paxishost->hotplugin_host_initialize())
               {

                  m_bHostInit = true;

               }

            }

         }

      }
      else if(m_estate == state_start_window)
      {

         if(m_bWindowOk)
         {

            m_estate = state_ok;

         }
         else if(!m_bTryInitWindow)
         {

            m_bTryInitWindow = true;

            if(on_composer_init_window())
            {

               m_bWindowOk = true;

            }

         }

      }
      else if(m_estate == state_ok)
      {

         if(!m_bOk)
         {

            m_bOk = true;

         }
      }


      if(m_paxishost != nullptr && m_paxishost->hotplugin_host_is_initialized())
      {

         if(m_bWrite)
         {

            m_bWrite = false;

            m_paxishost->hotplugin_host_on_write(); // at least m_strPluginUrl is ready

         }

      }


      if(m_bOpenUrl)
      {

         m_bOpenUrl = false;

         if(!_open_link(m_strOpenUrl, m_strOpenTarget))
         {

            m_bOpenUrl = true;

         }

      }

   }


   bool composer::on_composer_init_window()
   {

      return true;

   }


   bool composer::open_link(const ::string & strLink,const string & pszTarget)
   {

      m_strOpenUrl = strLink;

      m_strOpenTarget = pszTarget;

      m_bOpenUrl = true;

      return true;

   }


   bool composer::_open_link(const ::string & strLink,const string & pszTarget)
   {

      return true;

   }


   // if composer on paint returns (returns true), it has painted something meaningful : no other painting is needed or even desired (finally when system, and host are ok,
   // if host returns in a fashion-timed way the response for bitmap, it draw this bitmap, and not the default waiting [hall] screen painted by this composer).

   bool composer::windows_on_paint(::draw2d::graphics_pointer & pgraphics)
   {

      if((!m_bOk || !m_bResponsive) || m_paxishost == nullptr || !m_paxishost->hotplugin_host_is_initialized() || m_strEntryHallText.has_char())
      {

         if(!m_bEntryHallTextStarted)
         {

            m_bEntryHallTextStarted = true;
            
            m_durationEntryHallTextStart.Now();

         }

         //if(m_durationEntryHallTextStart.elapsed() > ((5000) / 3))
         //{

         //   ::hotplugin::entry_hall_windows_on_paint(pgraphics,m_rectangle,m_strEntryHallText);

         //}

         return true;

      }

      m_bEntryHallTextStarted = false;

      /*else
      {

         m_paxishost->m_bOnPaint = true;

         ::draw2d::graphics_pointer g(m_paxishost->create_new, this);

         g->Attach((HDC)hdc);

         ::rectangle_i32 rectangle;

         m_paxishost->get_window_rect(rectangle);

         m_paxishost->on_paint(g,rectangle_i32);

         g->Detach();

         m_paxishost->m_bOnPaint = false;

      }*/

      return false;


   }


   void composer::deferred_prodevian_redraw()
   {

      if(m_paxishost != nullptr && m_paxishost->hotplugin_host_is_initialized())
      {

         m_paxishost->deferred_prodevian_redraw();

      }

   }


   bool composer::is_active()
   {

      return true;

   }


   ::aura::system * composer::get_composer_system()
   {

      return m_pcomposersystem;

   }


   bool composer::defer_start_composer_system()
   {

      if(m_pcomposersystem != nullptr)
         return true;

      throw ::exception(todo(nullptr));

//      try
//      {
//
//         m_pcomposersystem = memory_new ::axis::system(nullptr);
//
//         ::axis::system * paxissystem = m_pcomposersystem;
//
//         paxissystem->m_bMatterFromHttpCache = true;
//
//         paxissystem->m_bSystemSynchronizedCursor = false;
//
//#ifdef WINDOWS
//
//         paxissystem->m_hinstance = (HINSTANCE)get_hinstance();
//
//#endif
//
//         xxdebug_box("box1","box1",e_message_box_icon_information);
//
//         paxissystem->m_bReady = false;
//
//         ::create_thread(nullptr,0,&::hotplugin::composer::composer_system_main,paxissystem,0,nullptr);
//
//      }
//      catch(...)
//      {
//
//         return false;
//
//      }

      return true;

   }


   u32 c_cdecl composer::composer_system_main(LPVOID pVoid)

   {

      throw_todo();

      ////i32 iReturnCode = 0;

      //::axis::system * paxissystem = (::axis::system *) pVoid;


      //try
      //{

      //   if(!paxissystem->pre_run())
      //   {

      //      paxissystem->m_result.add(error_failed);

      //      paxissystem->m_bReady = true;

      //      return -1;

      //   }

      //}
      //catch(...)
      //{

      //   paxissystem->m_result.add(error_failed);

      //   paxissystem->m_bReady = true;

      //   return -1;

      //}

      //paxissystem->main();

      //return paxissystem->get_result_status();

      return 0;

   }


   void composer::defer_stop_composer_system()
   {

      if(m_pcomposersystem != nullptr)
      {

         m_pcomposersystem->destroy();

         m_pcomposersystem = nullptr;

      }

   }


} // namespace hotplugin


