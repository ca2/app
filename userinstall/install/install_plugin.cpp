#include "framework.h"
//#include "base/user/user.h"


#if defined()



#if defined(WINDOWS)
#define minimum minimum
#define maximum maximum
//#include <gdiplus.h>
#undef minimum
#undef maximum
#endif


// #ifndef i32_x
// #define i32_x(lp)                        ((i32)(i16)LOWORD(lp))
// #endif
// #ifndef i32_y
// #define i32_y(lp)                        ((i32)(i16)HIWORD(lp))
// #endif




#ifdef WINDOWS
//#include <process.h>
#endif

#ifdef WINDOWS

void simple_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
{
   //throw ::exception(::exception("integer_exception" + as_string($1)));
}

#endif // defined WINDOWS


namespace install
{


   string get_version()
   {

#if CA2_PLATFORM_VERSION == CA2_BASIS

      string strVersion = "basis";

#else

      string strVersion = "stage";

#endif

      if(file_system()->exists(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "config\\plugin\\version.txt"))
         strVersion = file_system()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "config\\plugin\\version.txt");

      return strVersion;

   }


   plugin::plugin(::particle * pparticle) :
      ::object(pparticle),
      ::simple_ui::style(pparticle),
      ::aura::session(pparticle),
      ::axis::session(pparticle),
      hotplugin::plugin(pparticle),
      ::aura::ipc::base(pparticle),
      ::aura::ipc::tx(pparticle),
      ::aura::ipc::ipc(pparticle),
      m_canvas(pparticle),
      m_startca2(pparticle)
   {

      m_bCa2Login             = false;
      m_bCa2Logout            = false;


      m_pstyle = this;

      m_iHealingSurface       = 0;
      m_iEdge                 = -1;
      m_bAppStarted           = false;
      //m_evReady               = nullptr;

      //m_bHasCred              = false;
      //m_bHasCredEval          = false;
      m_bPendingRestartCa2    = false;


#ifdef UNIVERSAL_WINDOWS

      throw ::exception(::exception("todo")); // aura::ipc::ipc

#else

      m_timeTimeout             = (5000) * 11;

#endif

      m_bLogged               = false;
      m_bLogin                = false;

      m_bRestartCa2           = false;
      m_bPendingStream        = false;
      m_timeLastRestart         = 0;

      m_bPluginDownloaded     = false;
      m_bPluginTypeTested     = false;
      m_bNativeLaunch         = false;
      m_bNativeLaunchFail     = false;

      m_startca2.m_pplugin = this;

      m_startca2.begin();

   }


   plugin::~plugin()
   {

   }


   IMPL_IMH(plugin,::user::interaction)
   MSG_LBUTTONUP
   END_IMH


   bool plugin::set_host(::hotplugin::host * phost)
   {

      if (!::hotplugin::plugin::set_host(phost))
         return false;

      m_strLoginRequestingServer = purl->get_server(m_phost->get_host_location_url());

      return true;

   }


   void plugin::on_prepare_memory()
   {

   }


   void plugin::restart_aura_ipc()
   {

      if(!is_installing())
      {

         if((m_timeLastRestart.elapsed()) > (5000) * 5)
         {

            m_timeLastRestart= ::time::now();

            start_ca2();

         }

      }

   }


   bool plugin::is_installing()
   {

      if(m_phost->m_bInstalling)
      {

         if((m_timeLastInstallingCheck.elapsed()) > 2000)
         {

            m_timeLastInstallingCheck= ::time::now();

            try
            {

               m_phost->m_bInstalling = psystem->install().is_installing_ca2();

            }
            catch(...)
            {

            }

         }

      }
      else if((m_timeLastInstallingCheck.elapsed()) > ((5000) * 2))
      {

         m_timeLastInstallingCheck= ::time::now();

         try
         {

            m_phost->m_bInstalling = psystem->install().is_installing_ca2();

         }
         catch(...)
         {

         }

      }

      if(m_phost->m_bInstalling)
      {

         if(m_bNativeLaunch)
         {

            m_bNativeLaunch = false;

         }

      }

      return m_phost->m_bInstalling;

   }


   bool plugin::thread_start_ca2_on_idle()
   {

      //if (!m_bHasCred && (m_bLogin || !m_bLogged || m_bCa2Login || m_bCa2Logout))
      //if(!m_bHasCred && (m_bLogin || !m_bLogged || m_bCa2Login || m_bCa2Logout))
      if(m_bLogin || m_bCa2Login || m_bCa2Logout)
         return false;

#ifdef UNIVERSAL_WINDOWS

      throw ::exception(::exception("todo"));

#else

      bool bJob = false;

      if(m_bRestartCa2 && m_phost != nullptr)
      {

         if(m_straLinesNativeLaunch.get_count() >= 2 && m_straLinesNativeLaunch[0] == "native_desktop_launcher")
         {

            m_bRestartCa2        = false;

            if(!m_bNativeLaunch || m_bNativeLaunchFail)
            {

               m_bNativeLaunchFail  = false;

               m_bNativeLaunch      = true;

               native_launch();

            }

         }
         else if(is_rx_tx_ok())
         {

            m_timeLastOk= ::time::now();

            m_bRestartCa2        = false;

            m_bPendingStream     = false;

            bJob                 = true;

         }
         else if(m_timeLastOk.elapsed() > ((5000) * 2))
         {


            try
            {

               if (psystem->install().is_installing_ca2())
               {

                  m_timeLastOk= ::time::now();

                  return false; // "no job done"

               }
               else
               {

                  string str;

                  str = hex::lower_from((iptr)m_phost);

                  m_phost->m_strBitmapChannel = str;

                  ::hotplugin::container_launcher launcher(process_platform_name(), str);

                  launcher.m_iStart = 1; // only one attempt to start, as we repeatealy and accordingly make this process of
                  // reopening channel as needed. Repetdely trying to open channel using default m_iStart = 11, make
                  // is_lock_file_locked evaluation be ignored, which is unnaccording.

                  string strChannel = "\\aura\\app_app_nest-";

                  strChannel += str;

#ifdef WINDOWS
                  open_ab(strChannel, "plugin-container.exe", &launcher);
#else
                  open_ab(strChannel, &launcher);
#endif

               }

            }
            catch(...)
            {

            }

            m_bRestartCa2        = false;

            m_bPendingStream     = true;

            bJob                 = true;

            m_timeLastOk          = ::time::now();

         }

      }

      if(m_bPendingStream && m_phost != nullptr)
      {

         if(m_phost->m_bStream)
         {

            try
            {

               //set_ready();

               ensure_tx(::hotplugin::message_set_plugin_url,(void *)(const ::string &)m_phost->m_pbasecomposer->m_strPluginUrl,(i32)m_phost->m_pbasecomposer->m_strPluginUrl.length());

               ensure_tx(::hotplugin::message_set_ready, m_phost->m_memory.get_data(), (i32)m_phost->m_memory.get_size());

            }
            catch(...)
            {

            }

            m_bPendingStream     = false;

            bJob                 = true;

         }

      }

      return bJob;

#endif

   }

   plugin::thread_start_ca2::thread_start_ca2(::particle * pparticle) :
      ::object(pparticle),
      thread(pparticle)
   {

//      m_timeRunLock = ::time(84 + 77);

   }



   i32 plugin::thread_start_ca2::run()
   {


      while (task_get_run())
      {

         m_pplugin->thread_start_ca2_on_idle();

         sleep(500_ms);

      }

      return true;

   }


   bool plugin::native_launch()
   {

      m_phost->m_pbasecomposer->m_strEntryHallText = "***papp started.";

      property_set set;

      set.parse_network_arguments(m_straLinesNativeLaunch[1]);

      string strPath = ::path::platform::application(process_platform_name());

      string strCommandLine;

      strCommandLine = " :";

      for(auto property : set)
      {

         if(!property.get_string().has_char()
               &&
               (property.name() == "app"
                || property.name() == "build"
                || property.name() == "app_type"
                || property.name() == "locale"
                || property.name() == "schema"
                || property.name() == "app"
                || property.name() == "session_start"
                || property.name() == "version"
               )
           )
            continue;

         strCommandLine += " ";

         strCommandLine += property.name();

         if(!property.get_string().has_char())
            continue;

         strCommandLine += "=";

         strCommandLine += property.get_string();

      }

      strPath += strCommandLine;

      bool bTimedOut = false;

      u32 dwExitCode = psystem->process().synch(strPath,e_display_normal,2_s),&bTimedOut);

      if(bTimedOut)
      {

         //::message_box(nullptr," - " + set["app"].get_string() + "\nhas timed out while trying to run.\n\nFor developers it is recommended to\nfix this timeout problem.\n\nYou may kill it manually :\n - \"" + strPath + "\"\nif it it does not come up.","Error Message",e_message_box_icon_information | e_message_box_ok);

         //m_phost->m_pbasecomposer->m_strEntryHallText = "Starting papp->..";

         //m_bNativeLaunchFail = true;

         m_phost->m_pbasecomposer->m_strEntryHallText = "***papp started.";

         m_bNativeLaunchFail = false;

      }
      else if((int) dwExitCode >= 0)
      {

         //  ::message_box(nullptr,"Successfully run : " + strPath,"Debug only message, please install.",e_message_box_icon_information | e_message_box_ok);

         m_phost->m_pbasecomposer->m_strEntryHallText = "***papp started.";

         m_bNativeLaunchFail = false;

      }
      else
      {

         //::message_box(nullptr,strPath + "\n\nFailed return code : " + as_string(dwExitCode),"Error Message",e_message_box_icon_information | e_message_box_ok);

         //m_phost->m_pbasecomposer->m_strEntryHallText = "***Failed to start application.";

         m_phost->m_pbasecomposer->m_strEntryHallText = "Starting papp->..";

         m_bNativeLaunchFail = true;

      }

      return true;

   }


   void plugin::start_ca2()
   {

      //if(!m_bHasCredEval)
      //{
      //
      //   string strUsername;

      //   string strPassword;

      //   string str = ::account::get_cred(get_app(),strUsername,strPassword,"ca2");

      //   if(strUsername.has_char() && strPassword.has_char() && str == "ok")
      //   {

      //      m_bHasCred = true;

      //      m_bPendingRestartCa2 = true;

      //   }
      //   else
      //   {

      //      m_bHasCred = false;

      //   }

      //   m_bHasCredEval = true;

      //}


      if(m_bCa2Login || m_bCa2Logout)
         return;

      string strScript = purl->get_script(m_phost->m_pbasecomposer->m_strPluginUrl);

      //if(!m_bHasCred || (!m_bLogged && (strScript == "/ca2login" || strScript == "/ca2logout")))
      if(!m_bLogged && (strScript == "/ca2login" || strScript == "/ca2logout"))
      {

         m_phost->m_pbasecomposer->m_strEntryHallText = "Checking credentials...";

         xxdebug_box("plugin::start_ca2 not logged", "not logged", 0);

         m_bLogin = true;

         if(m_phost->m_pbasecomposer->m_strPluginUrl.has_char())
         {

            m_bLogged = psession->account()->get_user(false,m_phost->m_pbasecomposer->m_strPluginUrl) != nullptr;

         }

         m_bCa2Login = false;

         m_bCa2Logout = false;

         m_bNativeLaunch = false;

      }

      ///if(!m_phost->m_bOk || (!m_bLogged && (strScript == "/ca2login" || strScript == "/ca2logout")) || (!m_bHasCred && !m_bLogged))
      if(!m_phost->m_bOk || (!m_bLogged && (strScript == "/ca2login" || strScript == "/ca2logout")))
         return;

      bool bJustLoggedIn = false;

      if(m_bLogin)
      {

         bJustLoggedIn = true;

         m_bLogin = false;

      }

      if(!m_bCa2Login && strScript == "/ca2login")
      {

         m_bCa2Login = true;

         m_bOk = false;

         m_phost->m_bOk = false;

         property_set set;

         set.parse_network_arguments(purl->get_query(m_phost->m_pbasecomposer->m_strPluginUrl));

         string strUrl(set["ruri"]);

         if(strUrl.is_empty())
         {

            strUrl = "http://" + psession->account()->get_server(m_phost->m_pbasecomposer->m_strPluginUrl) + "/";

         }

         purl->set_param(strUrl,strUrl,"sessid",psession->account()->get_user()->get_sessid(purl->get_server(m_phost->m_pbasecomposer->m_strPluginUrl)));

         m_phost->open_link(strUrl, "");

         m_startca2.set_finish();

         return;

      }
      else if(!m_bCa2Logout && strScript == "/ca2logout")
      {

         m_phost->m_pbasecomposer->m_strEntryHallText = "Performing Log Out...";

         m_bCa2Logout = true;

         m_bOk = false;

         m_phost->m_bOk = false;

         property_set set;

         set.parse_network_arguments(purl->get_query(m_phost->m_pbasecomposer->m_strPluginUrl));

         //ca2logout(set);

         m_startca2.set_finish();

         return;

      }


      if(bJustLoggedIn)
      {

         m_phost->m_pbasecomposer->m_strEntryHallText.empty(); // It was Checking Credentials... no more checking credentials.

      }

      if(psystem->install().is_installing_ca2())
      {

         m_phost->m_pbasecomposer->m_strEntryHallText = "";

         m_bPendingRestartCa2 = true;

         m_bRestartCa2     = false;

         m_bNativeLaunch   = false;

         if(!m_phost->m_bInstalling)
         {

            m_phost->m_bInstalling = true;

            // shouldn't do advanced operations using ca
            // starter_start will only kick a default app_app_admin.exe if one isn't already running, cleaning file lock if any

         }

         set_ready();

         return;

      }

      psystem->install().update_ca2_installed(true);


      if(psystem->install().is_ca2_installed())
      {

         if(!m_bPluginTypeTested)
         {

            if(!m_bPluginDownloaded)
            {

               string strUrl = m_phost->m_pbasecomposer->m_strPluginUrl;

               property_set set;

               set["raw_http"] = true;

               for(i32 iAttempt = 0; iAttempt < 3; iAttempt++)
               {

                  //strPluginData = http_get_dup(strPluginUrl, false, &ms_get_dup_status_callback, (void *) &iStatusCode, false);

                  http()->get(strUrl,m_phost->m_pbasecomposer->m_strPluginData,set);

                  if(::http::status_succeeded(set["get_status"]))
                     break;

               }

               if(::http::status_succeeded(set["get_status"]))
               {

                  m_bPluginDownloaded = true;

               }

            }



            if(m_bPluginDownloaded && m_phost->m_pbasecomposer->m_strPluginData.has_char())
            {

               m_bPluginTypeTested = true;

               string_array straSeparator;

               straSeparator.add("\r\n");
               straSeparator.add("\r");
               straSeparator.add("\n");

               m_straLinesNativeLaunch.erase_all();

               m_straLinesNativeLaunch.add_smallest_tokens(m_phost->m_pbasecomposer->m_strPluginData,straSeparator,false);

            }




         }

         if(!m_bPluginTypeTested)
            return;

         m_bPendingRestartCa2 = false;

         m_bRestartCa2        = true;

         m_bPendingStream     = false;

         //m_bNativeLaunch      = false;

         m_bNativeLaunchFail  = false;

      }
      else
      {

         set_ready();

      }






   }






   bool plugin::hist(const ::string & pszUrl)
   {
      return open_link(pszUrl, "");
   }


   void plugin::run_start_install(const ::string & pszType, const ::string & pszInstall, const ::string & pszLocale, const ::string & pszSchema)
   {

      {

         ::xml::document node;

         // erase install tag : should be turned into a function dependant of spalib at maximum

         if(!node.load(file_system()->as_string(dir::appdata() / "install.xml")))
            goto run_install;


#if CA2_PLATFORM_VERSION == CA2_BASIS

         ::xml::node * lpnodeVersion = node.get_child("basis");

#else

         ::xml::node * lpnodeVersion = node.get_child("stage");

#endif

         if(lpnodeVersion == nullptr)
            goto run_install;

         string strBuild = psystem->install().get_latest_build_number(nullptr);

         ::xml::node * lpnodeInstalled = node.GetChildByAttr("installed", "build", strBuild);

         if(lpnodeInstalled == nullptr)
            goto run_install;

         ::xml::node * lpnodeType = lpnodeInstalled->get_child(pszType);

         if(lpnodeType == nullptr)
            goto run_install;

         ::xml::node * pnode = lpnodeType->GetChildByAttr(pszType, "id", pszInstall);

         if(pnode == nullptr)
            goto run_install;

         lpnodeType->erase_child(pnode);

         file_system()->put_contents(dir::appdata() / "install.xml", node.get_xml(nullptr));

      }

run_install:

      m_phost->start_app_install(pszInstall);


   }




   void plugin::on_paint(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 &lprect)
   {

#ifdef UNIVERSAL_WINDOWS

      throw ::exception(::exception("todo"));

#else

      //::u32 dwTime1= ::time::now();



      //if(!m_bLogin && (m_bLogged || m_bHasCred) && !m_bCa2Login && !m_bCa2Logout && !m_bNativeLaunch && !is_installing() && psystem->install().is_ca2_installed())
      if(!m_bLogin && !m_bCa2Login && !m_bCa2Logout && !m_bNativeLaunch && !is_installing() && psystem->install().is_ca2_installed())
      {
         //::u32 dwTime3= ::time::now();

         //informationf("eval1 %d",dwTime3 - dwTime1);

         //if(ensure_tx(::hotplugin::message_paint, (void *) &lprect, sizeof(lprect)))
         if(ensure_tx(WM_APP+WM_USER,(void *)&lprect,sizeof(lprect)))
         {

            //::u32 dwTime5= ::time::now();

            //informationf("ensure_tx %d",dwTime5 - dwTime3);

            if(m_phost->m_pbasecomposer->m_bSendActivationState)
            {

               m_phost->m_pbasecomposer->m_bSendActivationState = false;

               m_phost->m_pbasecomposer->m_bActivationStateSent = false;

            }

            if(m_phost->m_pbasecomposer->m_bActive)
            {

               if(!m_phost->m_pbasecomposer->is_active() || !m_phost->m_pbasecomposer->m_bActivationStateSent)
               {

                  m_phost->m_pbasecomposer->m_bActive = false;

                  LRESULT lresult;

                  ::pointer<user::message>paxis = __allocate user::message(get_app(),this,e_message_activate,MAKEWPARAM(WA_INACTIVE,0),0,lresult);

                  m_phost->::hotplugin::host::message_handler(paxis);

               }

            }
            else
            {

               if(m_phost->m_pbasecomposer->is_active() || !m_phost->m_pbasecomposer->m_bActivationStateSent)
               {

                  m_phost->m_pbasecomposer->m_bActive = true;

                  LRESULT lresult;

                  ::pointer<user::message>paxis = __allocate user::message(get_app(),this,e_message_activate,MAKEWPARAM(WA_ACTIVE,0),0,lresult);

                  m_phost->::hotplugin::host::message_handler(paxis);

               }
            }


            if(m_phost->m_pbasecomposer->m_bFocus)
            {

               if(!has_keyboard_focus() || !m_phost->m_pbasecomposer->m_bActivationStateSent)
               {

                  m_phost->m_pbasecomposer->m_bFocus = false;

                  LRESULT lresult;

                  ::pointer<user::message>paxis = __allocate user::message(get_app(),this,e_message_kill_focus,0,0,lresult);

                  m_phost->::hotplugin::host::message_handler(paxis);

               }

            }
            else
            {

               if(has_keyboard_focus() || !m_phost->m_pbasecomposer->m_bActivationStateSent)
               {

                  m_phost->m_pbasecomposer->m_bFocus = true;

                  LRESULT lresult;

                  ::pointer<user::message>paxis = __allocate user::message(get_app(),this,e_message_set_focus,0,0,lresult);

                  m_phost->::hotplugin::host::message_handler(paxis);

               }

            }

            if(!m_phost->m_pbasecomposer->m_bActivationStateSent)
            {

               m_phost->m_pbasecomposer->m_bActivationStateSent = true;

            }

            //::u32 dwTime7= ::time::now();

            //informationf("focus_update %d",dwTime7 - dwTime5);


            m_phost->blend_bitmap(pgraphics, lprect);

            //::u32 dwTime9= ::time::now();

            //informationf("blend %d",dwTime9 - dwTime7);


            return;

         }

      }

      psystem->install().update_ca2_installed();

      if(!m_phost->m_pbasecomposer->m_bSendActivationState)
      {

         m_phost->m_pbasecomposer->m_bSendActivationState = true;

      }

      if(m_phost->m_pbasecomposer->m_bRectSent)
      {

         m_phost->m_pbasecomposer->m_bRectSent = false;

      }



#endif


      ::rectangle_i32 rectangle_i32;

      ::rectangle_i32 rectangleWindow;

      window_rectangle(&rectangleWindow);

      i32 cx = rectangleWindow.right() - rectangleWindow.left();
      i32 cy = rectangleWindow.bottom() - rectangleWindow.top();

      rectangle.left()         = 0;
      rectangle.top()          = 0;
      rectangle.right()        = cx;
      rectangle.bottom()       = cy;

      //simple_bitmap b;



      pgraphics->offset_origin(rectangleWindow.left(), rectangleWindow.top());

      //b.create(cx, cy, pgraphics);

      //simple_graphics pgraphics;

      //pgraphics->create_from_bitmap(b);

      //pgraphics->bit_blt(0, 0, cx, cy, pgraphics, ::hotplugin::plugin::m_rectangle.left(), ::hotplugin::plugin::m_rectangle.top());

//      HFONT hfontOld = nullptr;
//      HFONT hfont = nullptr;

      bool bInstallingCa2 = false;

      if(m_bLogin)
      {
         //informationf("m_bLogin");
         //get_login().draw(pgraphics);
      }
      else if (psystem->install().is_installing_ca2())
      {

         bInstallingCa2 = true;

         m_canvas.on_paint(pgraphics, rectangle);

         m_bPendingRestartCa2 = true;

      }
      else if (!psystem->install().is_ca2_installed())
      {

         m_bPendingRestartCa2 = true;

         /* HPEN hpen = (HPEN) ::create_solid(1, rgb(0, 0, 0));
         HPEN hpenOld = (HPEN) ::SelectObject(hdc, hpen);
         HBRUSH hbrush = (HBRUSH) ::create_solid(rgb(255, 0, 255));
         HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc, hbrush);

         ::Ellipse(hdc, 23, 23, 49, 49);

         ::SelectObject(hdc, (HGDIOBJ) hpenOld);
         ::SelectObject(hdc, (HGDIOBJ) hbrushOld);*/

         /*         ::rectangle_i32 rectangle_i32;
         rectangle.left()      = 0;
         rectangle.top()       = 0;
         rectangle.bottom()    = cx;
         rectangle.right()     = cy;
         ::FillSolidRect_dup(hdc, &rectangle, rgb(255, 255, 255));
         ::SetTextColor(hdc, rgb(255, 0, 255));
         const ::scoped_string & scopedstr = "ca is not installed! You may try to install using low level installer_install.exe.";
         ::TextOutU_dup(hdc, 10, 10, psz, ansi_length(psz));*/
      }
      else
      {
         //informationf("Neither");
      }

#ifdef WINDOWS

      pgraphics->set_origin(0, 0);
      //pgraphics.bit_blt(lprect->left()                , lprect->top()                 , lprect->right() - lprect->left(), lprect->bottom() - lprect->top(),
      //     pgraphics         , lprect->left() - ::hotplugin::plugin::m_rectangle.left()  , lprect.top() - ::hotplugin::plugin::m_rectangle.top()    );

      /*string strx = ansi_string_from_i64(lprect->left());
      string stry = ansi_string_from_i64(lprect->top());
      text_out(hdcWindow, lprect->left() + 10, lprect->top() + 10, strx, strx.get_length());
      text_out(hdcWindow, lprect->left() + 110, lprect->top() + 10, stry, stry.get_length());
      string strx2 = ansi_string_from_i64(m_rectangle.left());
      string stry2 = ansi_string_from_i64(m_rectangle.top());
      text_out(hdcWindow, lprect->left() + 210, lprect->top() + 10, strx2, strx2.get_length());
      text_out(hdcWindow, lprect->left() + 310, lprect->top() + 10, stry2, stry2.get_length());
      */
      //hdc,       lprect->left(), lprect->top());
      //::BitBlt(hdcWindow, m_rectangle.left(), m_rectangle.top(), cx, cy, hdc, 0, 0);

#endif

      if((!m_bLogin) && bInstallingCa2)
      {

         on_update_progress();

         on_bare_paint(pgraphics, lprect);

      }
      else
      {

         //informationf("m_bLogin || !bInstallingCa2");
      }


   }


   void plugin::on_message_left_button_up(::message::message * pmessage)
   {

      if(pmessage->previous())
         return;

      m_iHealingSurface = m_canvas.increment_mode();

   }



   void plugin::message_handler(::user::message * pusermessage)
   {

      if(!m_bLogin && !m_bCa2Login && !m_bCa2Logout && !m_bNativeLaunch && pmessage != nullptr && !is_installing() && psystem->install().is_ca2_installed())
         //if(!m_bLogin && (m_bLogged || m_bHasCred) && !m_bCa2Login && !m_bCa2Logout && !m_bNativeLaunch && pmessage != nullptr && !is_installing() && psystem->install().is_ca2_installed())
      {

         ::hotplugin::plugin::message_handler(pusermessage);

      }
      else
      {

         ::user::interaction::message_handler(pusermessage);

      }

   }



   bool plugin::plugin_initialize()
   {

      start_ca2();

      return true;

   }

   //::user::interaction * plugin::get_focus()
   //{

   //   if (m_phost != nullptr)
   //   {

   //      return m_phost->get_focus();

   //   }
   //
   //   return nullptr;

   //}

   //void plugin::set_focus(::user::interaction * puiFocus)
   //{

   //   if (m_phost != nullptr)
   //   {

   //      m_phost->set_focus(puiFocus);

   //   }

   //}


   void plugin::on_paint_progress(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 &lprect)
   {

      ::hotplugin::plugin::on_paint_progress(pgraphics, lprect);

   }


   double plugin::extract_spa_progress_rate()
   {

      ::u32 dwRead;

      HANDLE hfile = ::create_file(::path::install_log(process_platform_name()), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

      double dRate = 0.0;

      bool bRate = false;

      bool bStatus = false;

      if(hfile != INVALID_HANDLE_VALUE)
      {

         i32 iTell = ::SetFilePointer(hfile, 0, nullptr, SEEK_END);
         iTell--;
         string strLine;
         i32 iSkip = 0;
         bool bStatus2 = false;
         char ch = '\0';
         bool bFirst = true;
         while(iTell >= 0)
         {
            ::SetFilePointer(hfile, iTell, nullptr, SEEK_SET);
            if(!ReadFile(hfile, &ch,  1, &dwRead, nullptr))
               break;
            if(dwRead <= 0)
               break;

            if(ch == '\r')
            {
               iSkip++;
            }
            else if(ch == '\n')
            {
               iSkip++;
            }
            else if(bFirst || iSkip > 0)
            {
               bFirst = false;
               iSkip = 0;
               strLine.trim();
               if(strLine.begins_eat("#----------"))
               {
                  m_strStatus = "Thank you";
                  bStatus = true;
                  m_strStatus2 = strLine;
                  bStatus2 = true;
                  dRate = 0.0;
                  bRate = true;
               }
               else if(!bRate && strLine.begins_eat("|||"))
               {
                  bRate = true;
                  dRate = ((double) ansi_to_i32(strLine)) / (1000.0 * 1000.0 * 1000.0 );
               }
               else if (!bStatus2 && strLine.begins_eat("***"))
               {
                  bStatus2 = true;
                  m_strStatus2 = strLine;
               }
               else if (!bStatus && strLine.begins_eat(":::"))
               {
                  bStatus = true;
                  m_strStatus = strLine;
               }

               if(bRate && bStatus && bStatus2)
                  break;

               strLine = ch;
            }
            else
            {
               strLine = ch + strLine;
            }
            iTell--;
         }
         ::CloseHandle(hfile);
      }
      return dRate;
   }


   void plugin::deferred_prodevian_redraw()
   {

      ::hotplugin::plugin::deferred_prodevian_redraw();

      // this flag is only set if spaadmin is installing ca files while npca2 is started
      // it isn't set when npca2 is already running and spaadmin starts, may be only in the case above, when npca2 restarts.
      // this enables spaadmin to install ca files to ca folder, because npca2 would not use any ca shared libraries.
      if(m_phost->m_bRunningSpaAdmin)
      {
         throw ::exception(todo);
         /*if(!_c_lock_is_active("Global\\::ca::account::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784"))
         {
            m_phost->m_bRunningSpaAdmin = false;
            m_phost->start_plugin();
            return;
         }*/
      }


      if(m_phost->is_ca2_installation_ready())
      {
         m_phost->set_ca2_installation_ready(false);
         m_phost->start_ca2();
      }

   }

#ifndef UNIVERSAL_WINDOWS


   void plugin::on_receive(::aura::ipc::rx * prx, i32 message, void * pdata, i32 len)
   {

      if(prx == &m_rx)
      {

         if(message == ::hotplugin::message_open_url)
         {

            string strUrl((const ::string &) pdata, len);

            open_link(strUrl, "");

         }

      }

   }


   void plugin::on_post(::aura::ipc::rx * prx, i64 a, i64 b)
   {

      if(prx == &m_rx)
      {

         if(a == 1)
         {

            m_phost->m_bInstalling = b != false;

         }
         else if(a == 3)
         {

            if(b == 1)
            {

               if(m_phost->m_bStream)
               {

                  m_bRestartCa2        = true;

                  m_bPendingStream     = false;

               }

            }

         }

      }

   }

#endif

   bool plugin::set_window_position(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags)
   {

      bool bOk = ::hotplugin::plugin::set_window_position(z, x, y, cx, cy, nFlags);

      return bOk;

   }


   void plugin::on_ready()
   {

      if(m_phost == nullptr)
         return;

      if(!m_phost->m_bOk)
         return;

      if(m_bLogin)
         return;

      //if(!m_bLogged && !m_bHasCred)
      // return;

      if(psystem->install().is_installing_ca2())
         return;

      string strScript = purl->get_script(m_phost->m_pbasecomposer->m_strPluginUrl);

      if (!m_bInstalling && psystem->install().is_ca2_installed())
      {

         xxdebug_box("on_ready", "on_ready", 0);

         m_bRestartCa2 = true;

         m_bPendingStream = false;

      }
      else if(!m_phost->m_bHostStarterStart)
      {

         string strData;

         if (m_phost->m_memory.get_data() != nullptr && m_phost->m_memory.get_size() > 0)
         {

            strData = string((const ::string &)m_phost->m_memory.get_data(),m_phost->m_memory.get_size());

         }
         else
         {

            i32 iTry = 0;

retry_get_prompt:

            property_set set;

            set["raw_http"] = true;

            strData = http()->get(m_phost->m_pbasecomposer->m_strPluginUrl,set);

            if(strData.is_empty())
            {

               if (iTry < 9)
               {

                  sleep(iTry * 84);

                  iTry++;

                  goto retry_get_prompt;

               }

            }

         }

         string strApp;

         string strPrompt(strData);

         if(strPrompt.case_insensitive_begins_eat("ca2prompt"))
         {

            strPrompt.trim();

            strApp = purl->get_script(strPrompt);

         }
         else if(strPrompt.case_insensitive_begins_eat("native_desktop_launcher"))
         {

            strPrompt.trim();

         }
         else
         {

            strPrompt.empty();

         }

         if(strApp.is_empty() && (!url_query_get_param(strApp,"app",strApp) || strApp.is_empty()))
            if(!url_query_get_param(strApp,"app",m_phost->m_pbasecomposer->m_strPluginUrl) || strApp.is_empty())
               strApp = "bergedge";

         string strLocale;

         if (strPrompt.is_empty() || !url_query_get_param(strLocale, "locale", strPrompt) || strLocale.is_empty())
            if(strPrompt.is_empty() || !url_query_get_param(strLocale,"lang",strPrompt) || strLocale.is_empty())
               if(!url_query_get_param(strLocale,"locale",m_phost->m_pbasecomposer->m_strPluginUrl) || strLocale.is_empty())
                  if(!url_query_get_param(strLocale,"lang",m_phost->m_pbasecomposer->m_strPluginUrl) || strLocale.is_empty())
                     strLocale = str_get_system_default_locale_dup();

         string strSchema;

         if (strPrompt.is_empty() || !url_query_get_param(strSchema, "schema", strPrompt) || strSchema.is_empty())
            if(strPrompt.is_empty() || !url_query_get_param(strSchema,"styl",strPrompt) || strSchema.is_empty())
               if(!url_query_get_param(strSchema,"schema",m_phost->m_pbasecomposer->m_strPluginUrl) || strSchema.is_empty())
                  if(!url_query_get_param(strSchema,"styl",m_phost->m_pbasecomposer->m_strPluginUrl) || strSchema.is_empty())
                     strSchema = str_get_system_default_schema_dup();

         string strVersion;

         if(strPrompt.is_empty() || !url_query_get_param(strVersion,"version",strPrompt) || strVersion.is_empty())
            if(!url_query_get_param(strVersion,"schema",m_phost->m_pbasecomposer->m_strPluginUrl) || strVersion.is_empty())
               strVersion = ::install::get_version();

         if (strLocale.is_empty())
            strLocale = "_std";

         if (strSchema.is_empty())
            strSchema = "_std";

         if(strVersion.is_empty())
            strVersion = "stage";

         m_phost->start_app_install(": app=" + strApp + " app_type=application install locale=" + strLocale + " schema=" + strSchema + " version=" + strVersion);

      }

   }


   void plugin::on_login_result(const ::e_status & estatus, const ::string & pszResponse)
   {

      if(eresult == ::account::result_auth)
      {

         m_bLogged   = true;

         m_bLogin    = false;

         start_ca2();

      }
      else
      {

         m_bLogin    = true;

      }


   }

   string plugin::defer_get_plugin()
   {

      string str;

      i32 iAttemptStream = 0;
      i32 iAttemptUrl = 0;
      i32 iAttempt = 0;

restart:

      while(!m_phost->m_bStream)
      {
         iAttemptStream++;
         if(iAttemptStream > 49)
            return "";
         sleep(iAttemptStream * 84);
      }

      while(m_phost->m_pbasecomposer->m_strPluginUrl.is_empty())
      {
         if(!m_phost->m_bStream)
         {
            iAttemptStream = 0;
            goto restart;
         }
         iAttemptUrl++;
         if(iAttemptUrl > 49)
            return "";
         sleep(iAttemptUrl * 84);
      }

      property_set set;

      while((str = http()->get(m_phost->m_pbasecomposer->m_strPluginUrl,set)).is_empty())
      {
         if(!m_phost->m_bStream)
         {
            iAttemptStream = 0;
            goto restart;
         }
         iAttempt++;
         if(iAttempt > 7)
            return "";
         sleep(iAttempt * 840);
      }

      return str;

   }

   void plugin::viewport_screen_to_client(::point_i32 * ppt)
   {
      //::user::interaction::viewport_screen_to_client(ppt);
   }


   void plugin::viewport_client_to_screen(::point_i32 * ppt)
   {
      //::user::interaction::viewport_client_to_screen(ppt);

   }


   void plugin::on_host_timer()
   {

      //if(m_bNativeLaunch && !m_bNativeLaunchFail)
      //{

      //   psystem->install().update_ca2_installed();

      //   if(!psystem->install().is_ca2_installed() || psystem->install().is_installing_ca2())
      //   {

      //      m_bNativeLaunchFail = true;

      //   }

      //}

      if((m_bLogin && !m_bLogged) || !m_phost->m_bOk || m_bNativeLaunch || m_bPendingRestartCa2)
      {

         if((m_timeLastRestart.elapsed()) > (840 + 770))
         {

            m_timeLastRestart= ::time::now();

            start_ca2();

         }

      }

      //if(!m_bLogin && (m_bLogged || m_bHasCred) && !m_bCa2Login && !m_bCa2Logout && !m_bNativeLaunch && !is_installing() && psystem->install().is_ca2_installed())
      if(!m_bLogin && !m_bCa2Login && !m_bCa2Logout && !m_bNativeLaunch && !is_installing() && psystem->install().is_ca2_installed())
      {

#ifdef UNIVERSAL_WINDOWS

         throw ::exception(::exception("todo"));

#else


         ::rectangle_i32 rectangle;

         window_rectangle(rectangle);

         if(!m_phost->m_pbasecomposer->m_bRectSent || m_rectangleSent != rectangle)
         {

            m_phost->m_pbasecomposer->m_bRectSent = true;

            m_rectangleSent = rectangle;

            if(!ensure_tx(::hotplugin::message_set_window,(void *)&rectangle,sizeof(::rectangle_i32)))
            {

               m_phost->m_pbasecomposer->m_bRectSent = false;

            }

         }
         else
         {

            // informationf("probably very healthly ignoring install::plugin::set_window_position");

         }

#endif

      }


   }

} // namespace install

#if !defined(CUBE) && !defined(ANDROID)

::hotplugin::plugin * new_hotplugin(::particle * pparticle)
{
   return ___new ::install::plugin (pparticle);
}

#endif


#endif





