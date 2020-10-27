#include "framework.h"
#include "aura/id.h"


#ifdef WINDOWS_DESKTOP
#include "aura/app_core.h"
#endif


#if defined(LINUX) || defined(ANDROID) || defined(APPLEOS)
//#include <sys/mman.h>
////#include <sys/stat.h>
////#include <fcntl.h>
#endif

void CLASS_DECL_AURA __cdecl _ca2_purecall_();


void CLASS_DECL_AURA __cdecl _ca2_purecall_()
{
   __throw(::exception::exception());
}

namespace plugin
{

   void ms_get_dup_status_callback(void * p, i32 i, uptr dw);
   void my_se_translator_function(u32, struct _EXCEPTION_POINTERS* );


   plugin::plugin()
   {

      m_puiHost               = nullptr;
      m_iHealingSurface       = 0;
      m_iEdge                 = -1;
      m_bAppStarted           = false;
//      m_pbReady               = nullptr;
      m_bMainReady            = false;

      m_pmutexBitmap          = nullptr;

   }


   bool plugin::plugin_initialize()
   {

      if(!::hotplugin::plugin::plugin_initialize())
         return false;

      start_ca2_system();

      return true;

   }


   bool plugin::hist(const char * pszUrl)
   {

      return open_link(pszUrl, "");

   }


   void plugin::run_start_install(const char * pszInstall)
   {

      UNREFERENCED_PARAMETER(pszInstall);

   }


   i32 plugin::start_ca2_system()
   {

#ifdef _UWP

      __throw(todo());

      return 0;

#else

      string strMutex = m_phost->m_strChannel;

      ::str::begins_eat_ci(strMutex, "\\aura\\");

      m_pmutexBitmap = new ::mutex(e_create_new, false, "Global\\" + strMutex);

      bool bNew = false;

      //Sleep(15 * 1000);

      sync_lock mlSystem(&m_phost->m_mutexSystem);

      if(m_phost->get_context_system() == nullptr)
      {

#ifdef WINDOWS

         _set_purecall_handler(_ca2_purecall_);

#endif

         ::aura::system * psystem = new ::aura::system();

         m_phost->set_context_system(psystem);

         mlSystem.unlock();

//         i32 nReturnCode = 0;

         /*         ::win::main_init_data * pinitmaindata  = new ::win::main_init_data;

                  pinitmaindata->m_hInstance             = hInstance;
                  pinitmaindata->m_hPrevInstance         = hPrevInstance;
                  pinitmaindata->m_strCommandLine        = ::str::international::unicode_to_utf8(::GetCommandLineW());
                  pinitmaindata->m_nCmdShow              = nCmdShow;


                  psystem->init_main_data(pinitmaindata);*/

#ifdef WINDOWS

         psystem->m_hinstance = ::GetModuleHandleW(L"aura.dll");

#endif

         throw_todo();

         //if(!psystem->InitApplication())
         //   return 0;

         if(!psystem->process_init())
            return 0;

         //psystem->start_application(true, nullptr);



      }

      mlSystem.unlock();


      m_puiHost = create_host_interaction();
      m_puiHost->m_pplugin = this;
      m_puiHost->install_message_routing(m_puiHost->m_pimpl);

      if(m_puiHost != nullptr)
      {

         System.value("top_parent") = m_puiHost;

      }

///      System.m_puiInitialPlaceHolderContainer = m_puiHost;
      //System.add_frame(m_puiHost);
      m_puiHost->on_layout(::draw2d::graphics_pointer & pgraphics);

//      if(m_pbReady == nullptr)
      //       m_pbReady = (bool *) memory_alloc(sizeof(bool));


#ifdef WINDOWS
      // Create Message Queue
      MESSAGE msg;
      PeekMessage(&msg, nullptr, 0, 0xffffffffu, FALSE);
#endif


      if(bNew || !m_bAppStarted)
      {
         m_bAppStarted = true;
//         System.begin();
      }

      m_bInitialized = true;

      m_bApp = true;

      set_ready();

      return 0;

#endif

   }

   //void copy_colorref(int cxParam,int cyParam,COLORREF * pcolorrefDst,COLORREF * pcolorrefSrc,int iStrideDst, int iStrideSrc)
   //{

   //   if(iStrideDst <= 0)
   //   {

   //      iStrideDst = cxParam * sizeof(COLORREF);

   //   }

   //   if(iStrideSrc <= 0)
   //   {

   //      iStrideDst = cxParam * sizeof(COLORREF);

   //   }

   //   int wsrc = iStrideSrc / sizeof(COLORREF);
   //   int wdst = iStrideDst / sizeof(COLORREF);
   //   int cw = cxParam * sizeof(COLORREF);


   //   COLORREF * psrc = pcolorrefSrc;
   //   COLORREF * pdst = pcolorrefDst;

   //   for(int i = 0; i < cyParam; i++)
   //   {

   //      ::memcpy_dup(pdst,psrc,cw);

   //      pdst += wdst;

   //      psrc += wsrc;

   //   }

   //}



   void plugin::on_paint(::draw2d::graphics_pointer & pgraphics, const ::rect & prectOut)
   {

      UNREFERENCED_PARAMETER(prectOut);


      ::rect rectClient;

      get_client_rect(rectClient);

      try
      {

         ensure_bitmap_data(rectClient, true);

         if (m_puiHost == nullptr)
         {

            return;

         }

         m_sizeBitmap = abs(rectClient.size());

         if (!m_sizeBitmap)
         {

            return;

         }

         __pointer(::user::interaction_impl) pimpl = m_phost->::user::interaction::m_pimpl;

         if(pimpl.is_null())
            return;

         //::image_pointer pimage = pimpl->m_spimageBuffer;

         //if(pimage->is_null())
         //   return;

         //if(pimage->area() <= 0)
         //   return;

         //cslock sl(pimpl->cs_display());


         //{

         //   sync_lock sl(m_pmutexBitmap);

         //   copy_colorref(
         //      min(pimage->width(),m_sizeBitmap.cx),
         //      min(pimage->height(),m_sizeBitmap.cy),
         //      (COLORREF *) m_memBitmap.get_data(),
         //      pimage->m_pcolorref,
         //      abs_dup(m_sizeBitmap.cx) * sizeof(COLORREF),
         //      abs_dup(pimage->width()) * sizeof(COLORREF));

         //}


      }
      catch(...)
      {
      }

      //try
      //{

      //   if(Application.install().is_installing_ca2())
      //   {

      //      reload_plugin();

      //   }

      //}
      //catch(...)
      //{
      //}

   }

   void plugin::on_ready()
   {
      m_puiHost->post_message(host_interaction::message_check, 0, 1);
   }


   void plugin::start_ca2_login()
   {

      fork([this]()    {         ca2_login();      });
      /*::begin_thread(m_puiHost, &plugin::thread_proc_ca2_login, this);*/

   }


   void plugin::start_ca2_logout()
   {

      fork([this]() {         ca2_logout();      });
      //::begin_thread(m_puiHost, &plugin::thread_proc_ca2_logout, this);

   }


   //::estatus     plugin::thread_proc_ca2_login(thread_parameter parameter)
   //{
   //   auto pplugin = parameter.cast < plugin > ();
   //   pplugin->ca2_login();
   //   return ::success;
   //}

   //::estatus     plugin::thread_proc_ca2_logout(thread_parameter parameter)
   //{
   //   auto pplugin = parameter.cast < plugin >();
   //   pplugin->ca2_logout();
   //   return ::success;
   //}

   void plugin::ca2_login()
   {

      property_set set;

      set.parse_url_query(m_strCa2LoginRuri);

      string strLocation = set["ruri"];

      if(strLocation.is_empty())
         strLocation = m_strCa2LoginRuri;

      property_set setUri;

      setUri.parse_url_query(strLocation);

      if(System.url().get_server(strLocation).is_empty())
      {
         strLocation = System.url().override_if_empty(strLocation, get_host_location_url(), false);
      }

      string strSessId = set["sessid"];

      property_set setLogin;

      //::account::user * puser = nullptr;

      //Sleep(15 * 1000);


      throw todo();

//
//
//      while(puser == nullptr)
//      {
//         puser = psession->account()->login(setLogin);
//      }
//
//      if(strSessId == puser->m_strFontopusServerSessId || puser->m_strFontopusServerSessId.get_length() < 16)
//      {
//
//         System.url().string_remove(strLocation, "sessid");
//
//      }
//      else
//      {
//
//         System.url().string_set(strLocation, "sessid", puser->m_strFontopusServerSessId);
//
//      }
//
//      System.url().string_remove(strLocation, "action");
//
//      open_link(strLocation, "");

   }

   void plugin::ca2_logout()
   {

//      psession->account()->logout();
//
//      property_set set;
//
//      set.parse_url_query(m_strCa2LogoutRuri);
//
//      string strLocation = set["ruri"];
//
//      strLocation = System.url().string_remove(strLocation, "sessid");
//
//      strLocation = System.url().string_remove(strLocation, "action");
//
//      string strUrl;
//
//      strUrl = "https://account.ca2.cc/sec?action=logout";
//
//      System.url().string_set(strUrl, "ruri", strLocation);
//
//      open_link(strUrl, "");

   }


   void ms_get_dup_status_callback(void * p, i32 i, uptr dw)
   {

      if(i == -3)
      {
//         i32 * pi = (i32 *) point;
//         simple_http_status * ps = (simple_http_status *) dw;
         //       *pi = ps->m_dwStatusCode;
      }

   }


   void plugin::ready_on_main_thread()
   {

      __task_guard(m_bMainReady);

      xxdebug_box("aura plugin plugin", "ready_on_main_thread", 0);

      ::count iCount = get_memory_length();

      if(iCount > 0)
      {
         m_memory.set_size(iCount + 1);

         read_memory(m_memory, iCount);

         m_memory.get_data()[iCount] = '\0';

         open_ca2_string((const char *) m_memory.get_data());
      }
      else if(m_phost->m_pbasecomposer->m_strPluginUrl.get_length() > 0)
      {

         string strPluginUrl     = System.url().override_if_empty(m_phost->m_pbasecomposer->m_strPluginUrl,get_host_location_url());

         string strExtension     = ::file::path(System.url().get_script(strPluginUrl)).extension();

         if(strExtension.is_empty() || strExtension.compare_ci("ca2") == 0)
         {
            // remark alarm
            // STRESS : http_get_dup
            // in aura library normally System or Context.http() is used
            string strPluginData;

//            ::estatus     estatus = ::http::status_fail;

            string strUrl = strPluginUrl;

            strUrl = System.url().string_set(strUrl, "authnone", 1);

            property_set set;

            set["raw_http"] = true;

            for (i32 iAttempt = 0; iAttempt < 3; iAttempt++)
            {

               //strPluginData = http_get_dup(strPluginUrl, false, &ms_get_dup_status_callback, (void *) &iStatusCode, false);

               Context.http().get(strUrl, strPluginData, set);

               if(::succeeded(set["get_status"]))
                  break;

            }

            if (::succeeded(set["get_status"]))
            {

               open_ca2_string(strPluginData);

            }

         }
         else
         {

            auto pcreate = __new(::create);
            pcreate->m_puserinteractionParent = m_puiHost;
            pcreate->value("NativeWindowFocus") = false;
            System.session()->open_by_file_extension("\"" + strPluginUrl + "\"", pcreate);

         }

      }

   }

   void plugin::open_ca2_string(const char * psz)
   {

      try
      {

         //Sleep(15 * 1000);

         LPSTR pszAlloc = (LPSTR) (void *) psz;


         if(psz == nullptr)
         {

            TRACE("plugin::plugin::open_ca2_string nullptr !!!");

            return;

         }

         strsize iCount = strlen(psz);

         if(iCount <= 0)
         {

            TRACE("plugin::plugin::open_ca2_string EMPTY !!!");

            return;

         }

         //Sleep(15 * 1000);

         string strPluginUrl;

         strPluginUrl = m_phost->m_pbasecomposer->m_strPluginUrl;

         System.url().override_if_empty(strPluginUrl, get_host_location_url());

         string strPluginScript = System.url().get_script(m_phost->m_pbasecomposer->m_strPluginUrl);


         property_set headers;

         headers.parse_http_headers(m_phost->m_pbasecomposer->m_strPluginHeaders);

         string strContentType = headers[__id(content_type)];

         string str1;

         // TODO |) : Should parse Content-type:
         // ALSO: this case only happens if all file has been downloaded before the plugin has initialized
         if(::str::ends_ci(strPluginScript, ".mp3")
               || ::str::ends_ci(strPluginScript, ".mid")
               || ::str::ends_ci(strPluginScript, ".karaoke")
               || ::str::ends_ci(strPluginScript, ".st3"))
         {
            //System.m_puiInitialPlaceHolderContainer = m_puiHost;
            auto pcreate = __new(create);
            pcreate->m_puserinteractionParent = m_puiHost;
            pcreate->value("NativeWindowFocus") = false;
            System.session()->open_by_file_extension("\"" + strPluginUrl + "\"", pcreate);
         }
         else
         {
            LPSTR pszStart = pszAlloc;

            LPSTR pszEnd = nullptr;

            i32 i = 0;
            for(; i < iCount; i++)
            {
               pszEnd = &pszStart[i];

               if(*pszEnd == '\n')

               {
                  str1 = string(pszStart, pszEnd - pszStart);

                  break;
               }
            }
            str1.trim();

            string str2;

            pszStart = pszEnd;

            for(; (pszEnd - pszAlloc) <= iCount; i++)

            {
               if(*pszEnd == '\0' || !::str::ch::is_whitespace(pszEnd))

                  break;
               pszEnd = (char *) ::str::utf8_inc(pszEnd);

            }
            pszStart = pszEnd;

            for(; (pszEnd - pszAlloc) <= iCount; i++)

            {
               if(*pszEnd == '\0' || ::str::ch::is_space_char(pszEnd) || (pszEnd - pszAlloc) == iCount)

               {
                  str2 = string(pszStart, pszEnd - pszStart);

                  break;
               }
               pszEnd = (char *) ::str::utf8_inc(pszEnd);

            }

            string strAppId = str2;

            strsize iFind = strAppId.find("?");

            if(iFind >= 0)
            {

               strAppId = strAppId.Left(iFind);

            }

            property_set set;
            set.parse_url_query(str2);

            string strBuild =  set["build"];

            string strLocale = set["locale"];

            string strSchema = set["schema"];

            string strVersion = set["version"];

            string strRuri = set["ruri"];

            if(strBuild.is_empty())
            {

               strBuild = "latest";

            }

            //Sleep(15 * 1000);
            if(str1 == "ca2login")
            {
               // graphical - 2 - user interface for login - account - through the plugin
               /*if(!System.install().is(nullptr, strBuild, "application", "app/aura/account", strLocale, strSchema))
               {
               /*                  System.install().start(": app=session session_start=app/aura/account app_type=application install");
               #ifdef WINDOWS
                  ::TerminateProcess(::GetCurrentProcess(), 0);
               #else
                  kill(0, SIGSTOP);
               #endif
                  m_bMainReady = false;*/

               /*                  string strCommandLine(": app=session session_start=app/aura/account app_type=application install ruri=\"" + strRuri + "\" locale=" + strLocale + " schema=" + strSchema);


               #ifdef WINDOWS_DESKTOP
                                 PostMessage(m_phost->::aura::ipc::tx::m_oswindow, WM_USER + 100, 1, 1);
               #else
                                 ::exception::throw_not_implemented();
               #endif
                                 System.install().start(strCommandLine);

                                 m_phost->m_bReload = true;

               #ifdef WINDOWS_DESKTOP
                        //          ::TerminateProcess(::GetCurrentProcess(), 0);
               #else
                           //        kill(0, SIGSTOP);
               #endif

                                 m_bMainReady = false;



                                 return;
                              }*/
               m_strCa2LoginRuri = string(pszEnd + 1, iCount - (pszEnd - pszStart) - 1);

               start_ca2_login();
            }
            else if(str1 == "ca2logout")
            {
               // graphical - 2 - user interface for logout - account - through the plugin
               /*if(!System.install().is(nullptr, strBuild, "application", "app/aura/account", strLocale, strSchema))
               {
                  /*
                  System.install().start(": app=session session_start=app/aura/account app_type=application install");
               #ifdef WINDOWS
                  ::TerminateProcess(::GetCurrentProcess(), 0);
               #else
                  kill(0, SIGSTOP);
               #endif
                  m_bMainReady = false;*/

               /*                  string strCommandLine(": app=session session_start=app/aura/account app_type=application install ruri=\"" + strRuri + "\" locale=" + strLocale + " schema=" + strSchema);

               #ifdef WINDOWS_DESKTOP
                                 PostMessage(m_phost->::aura::ipc::tx::m_oswindow, WM_USER + 100, 1, 1);
               #else
                                 ::exception::throw_not_implemented();
               #endif

                                 System.install().start(strCommandLine);

                                 m_phost->m_bReload = true;

               #ifdef WINDOWS_DESKTOP
                        //          ::TerminateProcess(::GetCurrentProcess(), 0);
               #else
                           //        kill(0, SIGSTOP);
               #endif

                                 m_bMainReady = false;


                                 return;
                              }*/
               m_strCa2LogoutRuri = string(pszEnd + 1, iCount - (pszEnd - pszStart) - 1);

               start_ca2_logout();
            }
            else if(str1 == "ca2prompt" || str1 == "native_desktop_launcher")
            {
               if(System.url().get_script(get_host_location_url()) == "/non_auth")
               {
                  m_strCa2LoginRuri = System.url().set_script(get_host_location_url(), "/");
                  start_ca2_login();
               }
               else
               {
                  m_puiHost->on_layout(::draw2d::graphics_pointer & pgraphics);
                  if(!m_bApp)
                  {
                     while(!m_evReady.lock(millis(284)) && m_bApp)
                     {
                     }
                     if(!m_bApp)
                     {
                        debug_print("Session application is not initialized. Cannot start mplite.");
                        return;
                     }
                  }
                  if(str2.has_char())
                  {

                     string strPlatform = System.get_system_platform();

                     string strConfiguration = System.get_system_configuration();

                     strLocale.trim();

                     strSchema.trim();

                     ::file::path pathExe = strAppId;

                     if(strAppId.has_char() && !is_application_installed(pathExe, strAppId, strBuild, strPlatform, strConfiguration, strLocale, strSchema))
                     {

                        string strCommandLine;

                        strCommandLine = ": app=session session_start=" + strAppId;

                        for(auto & pproperty : set)
                        {

                           strCommandLine += " ";

                           strCommandLine += pproperty->name();

                           if(pproperty->name() == "build")
                           {

                              string strBuild;

                              if(pproperty->get_string().has_char())
                              {

                                 strBuild = pproperty->get_string();

                              }
                              else
                              {

                                 string strConfig = strConfiguration.trimmed().is_empty() ? "stage" : strConfiguration;

                                 strBuild = Context.get_latest_build_number(strConfiguration, strAppId).trimmed();

                                 if(strBuild.is_empty())
                                 {

                                    strBuild = Context.get_latest_build_number(strConfig, strAppId);

                                    if(strBuild.is_empty())
                                    {

                                       strBuild = "latest";

                                    }

                                 }

                              }

                              strCommandLine += "=\"";

                              strCommandLine += strBuild;

                              strCommandLine += "\"";

                              continue;

                           }

                           if(!pproperty->get_string().has_char())
                              continue;

                           strCommandLine += "=\"";

                           strCommandLine += pproperty->get_string();

                           strCommandLine += "\"";

                        }

                        strCommandLine += " install";

//                        System.install().asynch_install(strCommandLine);

#ifdef WINDOWS_DESKTOP
                        ExitProcess(0);
#endif

                        //m_phost->m_pszReloadCommandLine = (const char *) HeapAlloc(GetProcessHeap(), 0, strCommandLine.get_length() + 1);
                        //ansi_count_copy((char *) m_phost->m_pszReloadCommandLine, strCommandLine, strCommandLine.get_length() + 1);


#ifdef WINDOWS_DESKTOP
//                        PostMessage(m_phost->::aura::ipc::tx::m_oswindow, WM_USER + 100, 1, 1);
#else
                        ::exception::throw_not_implemented();
#endif

//                        System.install().start(strCommandLine);

                        //m_phost->m_bReload = true;

#ifdef WINDOWS_DESKTOP
                        //                      ExitProcess(0);
#else
                        //        kill(0, SIGSTOP);
#endif

                        //m_bMainReady = false;

                        return;
                        //m_puiHost->SetTimer(88881115, (5000 )* 2, nullptr);

                     }
                     else if(str1 == "native_desktop_launcher")
                     {

                        string strPath = ::path::app(process_platform_dir_name2(), process_configuration_dir_name());

                        string strCommandLine;

                        strCommandLine = " : app=" + strAppId;

                        for(auto & pproperty : set)
                        {

                           if(!pproperty->get_string().has_char()
                                 &&
                                 (pproperty->name() == "build"
                                  || pproperty->name() == "app_type"
                                  || pproperty->name() == "locale"
                                  || pproperty->name() == "schema"
                                  || pproperty->name() == "app"
                                  || pproperty->name() == "session_start"
                                  || pproperty->name() == "version"
                                 )
                             )
                              continue;


                           strCommandLine += " ";

                           strCommandLine += pproperty->name();

                           if(!pproperty->get_string().has_char())
                              continue;

                           strCommandLine += "=";

                           strCommandLine += pproperty->get_string();

                        }


                        strPath += strCommandLine;

                        bool bTimedOut = false;

                        auto exitstatus = System.process().synch(strPath,display_normal,seconds(8.41115770402),&bTimedOut);

                        if(bTimedOut)
                        {

                           ::message_box(nullptr, " - " + set["app"].get_string() + "\nhas timed out while trying to run.\n\nFor developers it is recommended to\nfix this installation timeout problem.\n\nYou may kill it manually :\n - \"" + strPath + "\"\nif it it does not come up.","Error Message",MB_ICONINFORMATION | MB_OK);

                        }
                        else if(exitstatus.m_iExitCode == 0)
                        {

                           //  ::message_box(nullptr,"Successfully run : " + strPath,"Debug only message, please install.",MB_ICONINFORMATION | MB_OK);

                        }
                        else
                        {

                           ::message_box(nullptr,strPath + "\n\nFailed return code : " + __str(exitstatus.m_iExitCode),"Error Message",MB_ICONINFORMATION | MB_OK);

                        }

                     }
                     else
                     {

                        m_puiHost->KillTimer(19841115);
                        //Sleep(15 * 1000);
                        //                     System.m_puiInitialPlaceHolderContainer = m_puiHost;
                        xxdebug_box("plugin", "open_ca2_string", 0);
                        auto pcreate = __new(::create);
                        pcreate->value("NativeWindowFocus") = false;
                        pcreate->m_puserinteractionParent = m_puiHost;
                        System.request({str2, pcreate});
                     }
                  }
               }
            }
         }
      }
      catch(installing_exception &)
      {
         m_bReload = true;
         /*#ifdef WINDOWS
                  ::TerminateProcess(::GetCurrentProcess(), 0);
         #else
                  kill(0, SIGSTOP);
         #endif*/
      }
   }

   void my_se_translator_function(u32, struct _EXCEPTION_POINTERS* )
   {
   }


   void plugin::finalize()
   {

      if (!m_bAppStarted)
      {

         return;

      }


      g_bExiting = true;

#ifdef WINDOWS
      _set_se_translator(&my_se_translator_function);
#endif

      try
      {

         m_puiHost->DestroyWindow();

      }
      catch(...)
      {

      }

      try
      {

         ::multithreading::set_finish(&System);

      }
      catch(...)
      {

      }

      Sleep(2000);

      try
      {

         thread * pthread = &System;

         if(pthread->thread_get_run())
         {
            
            m_evReady.ResetEvent();
            
            pthread->m_pevReady = &m_evReady;

            pthread->finalize();

            int iRepeat = 0;

            while(!m_evReady.lock(millis(284)) && iRepeat < 49)
            {
               iRepeat++;
            }
         }


      }
      catch(...)
      {
      }

      //try
      //{
      //   delete m_psystem;
      //}
      //catch(...)
      //{
      //}

#ifdef WINDOWS
      /*      while(true)
            {
               try
               {
                  if(!::FreeLibrary(g_hmoduleOs))
                  {
                     break;
                  }

               }
               catch(...)
               {
               }

            }*/
#endif

   }


   void plugin::message_handler(::message::base * pmessage)
   {

   }


   ::estatus plugin::os_native_bergedge_start()
   {

      m_bApp = true;

      set_ready();

      return true;

   }

   void plugin::set_window_rect(const ::rect & rect)
   {

      SetPlacement(rect);

      if(m_puiHost != nullptr)
      {

         m_puiHost->m_bRectOk = true;

         ::rect rectHost(rect);

         rectHost.offset(-rectHost.top_left());

         m_puiHost->SetPlacement(rectHost);

         auto rectWindow = m_puiHost->get_window_rect();

         m_puiHost->order(zorder_top);

         m_puiHost->place(rectWindow);

         m_puiHost->send_message(e_message_size);

         m_puiHost->send_message(e_message_move);

         m_puiHost->on_layout(::draw2d::graphics_pointer & pgraphics);

      }

   }


} // namespace plugin


