#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "apex/platform/static_setup.h"


void __node_base_factory_exchange();


namespace base
{


   system::system()
   {

      m_pbasesystem = this;

      common_construct();

   }


   system::~system()
   {

//
//      ::acme::del(m_ppatch);
//
//      if (g_p == this)
//      {
//
//         g_p = nullptr;
//
//      }
//
//      //::acme::del(m_purldepartment);
//
//      //::acme::del(m_pcompress);
//
//      ::acme::del(g_pmutexImage);
//
//      //try
//      //{
//
//      //   ::acme::del(m_pmachineeventcentral);
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      //try
//      //{
//
//      //   if (m_pfactory.is_set())
//      //   {
//
//      //      m_pfactory->enable_simple_factory_request(false);
//
//      //      m_pfactory.release();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//      //   TRACE("system::~system: Potentially catastrophical error : error disabling simple factory request");
//      //}
//
//      if (g_p == this)
//      {
//
//         g_p = nullptr;
//
//      }
//
//#ifdef LINUX
//
//      os_post_quit();
//
//#elif defined(__APPLE__)
//
//      os_post_quit();
//
//#endif
//
//#ifndef WINDOWS
//
//      exception::translator::detach();
//
//#endif

   }


   void system::common_construct()
   {

      create_factory < ::base::session, ::apex::session >();
      create_factory < ::base::application, ::apex::application >();
      create_factory < ::base::user, ::user::user >();

   }


   ::estatus system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::axis::system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      __node_base_factory_exchange();

      return estatus;

   }


//   ::aura::audio * system::defer_get_audio()
//   {
//
//      if (!m_paudio)
//      {
//
//         defer_audio();
//
//      }
//
//      return m_paudio;
//
//   }
//
//
//   void system::defer_audio()
//   {
//
//      auto plibrary = get_library("audio");
//
//      bool bOk = true;
//
//      bOk = !!plibrary;
//
//      if (bOk)
//      {
//
//         auto pgetnewaudio = plibrary->get<PFUNCTION_GET_NEW_AUDIO>("get_new_audio");
//
//         bOk = !!pgetnewaudio;
//
//         if (bOk)
//         {
//
//            auto estatus = __compose(m_paudio, ::move_transfer(pgetnewaudio()));
//
//            bOk = !!estatus;
//
//            if (bOk)
//            {
//
//               bOk = !!m_paudio->init3();
//
//            }
//
//         }
//
//      }
//
////      if (!bOk)
//  //    {
//
//         //message_box("Could not open platform audio library.");
//
//    //  }
//
//   }
//
//
//   ::aura::multimedia * system::defer_get_multimedia()
//   {
//
//      if (!m_pmultimedia)
//      {
//
//         defer_multimedia();
//
//      }
//
//      return m_pmultimedia;
//
//   }
//
//
//   void system::defer_multimedia()
//   {
//
//      string strName;
//
//      if (::is_set(g_pszMultimediaLibraryName) && !strcmp(g_pszMultimediaLibraryName, "veriwell_multimedia"))
//      {
//
//         strName = "veriwell_multimedia";
//
//      }
//      else
//      {
//
//         strName = "multimedia";
//
//      }
//
//      auto plibrary = get_library(strName);
//
//      if (plibrary)
//      {
//
//         auto pgetnewmultimedia = plibrary->get<PFUNCTION_GET_NEW_MULTIMEDIA>("get_new_multimedia");
//
//         __compose(m_pmultimedia, ::move_transfer(pgetnewmultimedia()));
//
//         m_pmultimedia->initialize_multimedia(this);
//
//      }
//
//   }
//
//
//   void system::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
//   {
//
//
//   }
//
//
//   string system::get_locale_schema_dir()
//   {
//
//      return "_std/_std";
//
//   }
//
//
//   void system::session_add(index iEdge, ::aura::session * psession)
//   {
//
//      if (!::is_set(psession))
//      {
//
//         return;
//
//      }
//
//      if (m_sessionmap.is_empty())
//      {
//
//         m_bFinalizeIfNoSession = m_bFinalizeIfNoSessionSetting;
//
//      }
//
//      m_sessionmap[iEdge] = psession;
//
//      if (iEdge == 0)
//      {
//
//         set_context_session(psession);
//
//      }
//
//   }
//
//
//   void system::session_remove(index iEdge)
//   {
//
//      m_sessionmap.remove_key(iEdge);
//
//      if (m_sessionmap.is_empty() && m_bFinalizeIfNoSession)
//      {
//
//         set_finish();
//
//      }
//
//   }
//
//
//#ifdef DEBUG
//
//
//   void system::set_context(::context* pcontext)
//   {
//
//      m_pcontextContext = pcontext;
//
//   }
//
//
//   void system::set_context_thread(::thread* pthread)
//   {
//
//      m_pthreadContext = pthread;
//
//   }
//
//
//   void system::set_context_app(::aura::application* pappContext)
//   {
//
//      m_pappContext = pappContext;
//
//   }
//
//
//   void system::set_context_session(::aura::session* psessionContext)
//   {
//
//      m_psessionContext = psessionContext;
//
//   }
//
//
//   void system::set_context_system(::aura::system* psystemContext)
//   {
//
//      m_psystemContext = psystemContext;
//
//   }
//
//
//#endif
//
//
//   //::apex::library * system::on_get_library(const char * pszLibrary)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//
//   bool system::on_get_thread_name(string& strThreadName)
//   {
//
//      if (is_console_app())
//      {
//
//         return false;
//
//      }
//
//      return ::aura::context_thread::on_get_thread_name(strThreadName);
//
//   }
//
//
//
//   ::apex::library * system::get_library(const char * pszLibrary1, bool bOpenCa2)
//   {
//
//      sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//      string strLibrary(pszLibrary1);
//
//      strLibrary.ends_eat_ci(".dll");
//      strLibrary.ends_eat_ci(".so");
//      strLibrary.ends_eat_ci(".dylib");
//      strLibrary.begins_eat_ci("lib");
//
//      __pointer(::apex::library) & plibrary = ::get_context_system()->m_mapLibrary[strLibrary];
//
//      bool bLibraryOk = true;
//
//      if (plibrary.is_null())
//      {
//
//         plibrary = on_get_library(strLibrary);
//
//         if (plibrary.is_null())
//
//         {
//
//            plibrary.create();
//
//            if (!plibrary->open(strLibrary))
//            {
//
////#if !defined(ANDROID)
////               if (!plibrary->open(Context.dir().ca2module() / pszLibrary))
////#endif
////               {
////
////               }
//
//            }
//
//            bLibraryOk = plibrary->is_opened();
//
//         }
//
//#ifndef CUBE
//
//         if (bOpenCa2 && bLibraryOk)
//         {
//
//            plibrary->open_ca2_library();
//
//         }
//
//#endif
//
//      }
//
//      if(!bLibraryOk)
//      {
//
//         return nullptr;
//
//      }
//
//#ifndef CUBE
//
//      if (bOpenCa2)
//      {
//
//         if (plibrary->m_pca2library.is_null())
//         {
//
//            return nullptr;
//
//         }
//
//      }
//
//#endif
//
//      return plibrary;
//
//   }
//
//
//   system::~system()
//   {
//
//
//      ::acme::del(m_ppatch);
//
//      if (g_p == this)
//      {
//
//         g_p = nullptr;
//
//      }
//
//      //::acme::del(m_purldepartment);
//
//      //::acme::del(m_pcompress);
//
//      ::acme::del(g_pmutexImage);
//
//      //try
//      //{
//
//      //   ::acme::del(m_pmachineeventcentral);
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      //try
//      //{
//
//      //   if (m_pfactory.is_set())
//      //   {
//
//      //      m_pfactory->enable_simple_factory_request(false);
//
//      //      m_pfactory.release();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//      //   TRACE("system::~system: Potentially catastrophical error : error disabling simple factory request");
//      //}
//
//      if (g_p == this)
//      {
//
//         g_p = nullptr;
//
//      }
//
//#ifdef LINUX
//
//      os_post_quit();
//
//#elif defined(__APPLE__)
//
//      os_post_quit();
//
//#endif
//
//#ifndef WINDOWS
//
//      exception::translator::detach();
//
//#endif
//
//   }
//
//
//
//
//
//   class ::user::window_map & system::window_map()
//   {
//
//      return *m_pwindowmap;
//
//   }
//
//
//   //void system::defer_check_exit()
//   //{
//
//   //   if (!m_bDoNotExitIfNoApplications)
//   //   {
//
//   //      auto applicationa = get_applicationa();
//
//   //      for (i32 i = 0; i < applicationa.get_size();)
//   //      {
//
//   //         try
//   //         {
//
//   //            if (!applicationa[i] || applicationa[i]->is_session() || applicationa[i]->is_system())
//   //            {
//
//   //               applicationa.remove_at(i);
//
//   //               continue;
//
//   //            }
//   //            else if (applicationa[i]->is_serviceable())
//   //            {
//
//   //               applicationa.remove_at(i);
//
//   //               continue;
//
//   //            }
//
//   //         }
//   //         catch (...)
//   //         {
//
//   //            applicationa.remove_at(i);
//
//   //            continue;
//
//   //         }
//
//   //         i++;
//
//   //      }
//
//   //      if (applicationa.get_size() <= 0)
//   //      {
//
//   //         __destroy();
//
//   //      }
//
//   //      if (applicationa.get_size() == 1 && applicationa.contains(this))
//   //      {
//
//   //         __destroy();
//
//   //      }
//
//   //   }
//
//
//   //}
//
//
//   //base_factory & system::factory()
//   //{
//
//   //   return *m_pfactory;
//
//   //}
//
//
//   ::datetime::department & system::datetime()
//   {
//
//      return *m_pdatetime;
//
//   }
//
//
//   ::aura::str & system::str()
//   {
//
//      return *m_puserstr;
//
//   }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//   ::estatus system::process_init()
//   {
//
//      auto estatus = system_prep();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = system_init();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//
//
//      if (!create_session())
//      {
//
//         message_box("Failed to allocate Session!!");
//
//         return false;
//
//      }
//
//      m_papplicationStartup = get_new_application(get_context_session(), m_strAppId);
//
//      if (!m_papplicationStartup)
//      {
//
//         message_box("Failed to allocate Application!!");
//
//         return false;
//
//      }
//
//      set_main_struct(*m_papplicationStartup);
//
//      string strAppId = m_papplicationStartup->m_strAppId;
//
//      //auto pcommand = get_command();
//
//      //auto pcreate = pcommand->m_pcreate;
//
//      //TRACE("m_pcreate WARNING");
//      //TRACE("m_pcreate WARNING");
//      //TRACE("m_pcreate WARNING");
//      //TRACE("m_pcreate WARNING");
//      //TRACE("m_pcreate WARNING");
//      //TRACE("m_pcreate WARNING");
//      //TRACE("m_pcreate WARNING");
//      //TRACE("m_pcreate COMMENT BEGIN");
//      auto pcreate = m_pcreate;
//
//      pcreate->m_strAppId = strAppId;
//      //TRACE("m_pcreate COMMENT END");
//
//      create_factory < ::database::field >();
//
//
//      if (is_true("show_application_information"))
//      {
//
//         printf("%s", "\n\nApplication Information\n");
//         output_debug_string("\n\nApplication Information\n");
//
//         int iPid;
//
//         iPid = ::get_current_process_id();
//
//         printf("%s", ("Process PID: " + __str(iPid) + "\n").c_str());
//         output_debug_string("Process PID: " + __str(iPid) + "\n");
//
//      }
//
////#ifdef LINUX
////
////      {
////
////         string str;
////
////         str = ::dir::home() / ".profile";
////
////         if(!file_exists(str))
////         {
////
////            str = ::dir::home() / ".bashrc";
////
////         }
////
////         string_array straLines;
////
////         {
////
////            memory memory;
////
////            FILE * fp = popen(". " + str + " ; echo PATH=$PATH ;", "r");
////
////            memory.fread(fp);
////
////            pclose(fp);
////
////            string strContents = memory.as_utf8();
////
////            straLines.add_lines(strContents);
////
////         }
////
////         for(auto & strLine : straLines)
////         {
////
////            strLine.trim();
////
////            strsize i = strLine.find('=');
////
////            if(i > 0)
////            {
////
////               int iSize = strLine.get_length();
////
////               iSize *= 2;
////
////               iSize = max(iSize, 4096);
////
////               char * pszEnvLine = (char *) ::malloc(iSize);
////
////               ::zero(pszEnvLine, iSize);
////
////               strcpy(pszEnvLine, strLine);
////
////               ::putenv(pszEnvLine);
////
////            }
////
////         }
////
////      }
////
////#endif
//
//      {
//
//         {
//
//#ifdef WINDOWS_DESKTOP
//
//            {
//
//               ASSERT(m_hPrevInstance == nullptr);
//
//               HINSTANCE hinstance = m_hinstance;
//
//               auto edisplay = m_edisplay;
//
//               // handle critical errors and avoid Windows message boxes
//               SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);
//
//               m_edisplay = edisplay;
//
//               //SetCurrentHandles();
//
//            }
//
//#endif
//
//         }
//
//      }
//
//      //estatus = __compose_new(m_pxml);
//
//      //if (!estatus)
//      //{
//
//      //   throw exception::exception(estatus);
//
//      //}
//
//      //m_pxml->initialize(this);
//
//      //if (!m_pxml->init1())
//      //{
//      //   __throw(::exception::exception("failed to construct system m_pxml->init1()"));
//
//      //}
//
//      //if (!m_pxml->init())
//      //{
//
//      //   __throw(::exception::exception("failed to construct system m_pxml->initialize()"));
//
//      //}
//
//      create_factory < ::create >();
//      //create_factory < application_bias >();
//      create_factory < command_line >();
//      create_factory < http::context >();
////      create_factory < manual_reset_event >();
//      //create_factory < ::mutex >();
//      //create_factory < event >();
//
//      //if (!::aura::application::process_init())
//      //{
//
//      //   return false;
//
//      //}
//
//      //m_spos.create();
//
//      //if(is_installing() || is_unstalling())
//      {
//
//#ifdef MACOS
//
//         /*         if(0 != setuid(0))
//                     return false;
//
//                  uid_t uid = getuid();
//
//                  string str("installing or unstalling as root : getuid() %d", uid);
//
//                  ::dir::mk("/ca2core");
//
//                  file_put_contents("/ca2core/teste.txt", str, str.length());
//                  */
//#endif
//
//#if 0
//
//         // Create authorization context_object
//         OSStatus status;
//
//         AuthorizationRef authorizationRef;
//
//         // AuthorizationCreate and pass nullptr as the initial
//         // AuthorizationRights set so that the AuthorizationRef gets created
//         // successfully, and then later call AuthorizationCopyRights to
//         // determine or extend the allowable rights.
//         // http://developer.apple.com/qa/qa2001/qa1172.html
//         status = AuthorizationCreate(nullptr, kAuthorizationEmptyEnvironment,
//                                      kAuthorizationFlagDefaults, &authorizationRef);
//
//         if(status != errAuthorizationSuccess)
//         {
//            TRACE("Error Creating Initial Authorization: %d", status);
//
//            return false;
//
//         }
//
//         // kAuthorizationRightExecute == "system.privilege.admin"
//         AuthorizationItem right = {kAuthorizationRightExecute, 0, nullptr, 0};
//
//         AuthorizationRights rights = {1, &right};
//
//         AuthorizationFlags flags = kAuthorizationFlagDefaults |
//                                    kAuthorizationFlagInteractionAllowed |
//                                    kAuthorizationFlagPreAuthorize |
//                                    kAuthorizationFlagExtendRights;
//
//         // Call AuthorizationCopyRights to determine or extend the allowable rights.
//
//         status = AuthorizationCopyRights(authorizationRef, &rights, nullptr, flags, nullptr);
//
//         if (status != errAuthorizationSuccess)
//         {
//
//            TRACE("Copy Rights Unsuccessful: %d", status);
//
//            return false;
//
//         }
//
//#endif
//
//      }
//
//      if(!m_pmachineeventcentral)
//      {
//
//#ifndef APPLE_IOS
//
//         auto estatus = __compose_new(m_pmachineeventcentral);
//
//         if (!estatus)
//         {
//
//            return false;
//
//         }
//
//         //if(!m_pmachineeventcentral->initialize())
//         //{
//
//         //   return false;
//
//         //}
//
//         if(m_pmachineeventcentral->is_close_application())
//         {
//
//            return false;
//
//         }
//
//#endif
//
//      }
//
//      if(!__compose(m_pfilesystem))
//      {
//
//         ERR("failed to initialize file-system");
//
//         return false;
//
//      }
//
//      if(!__compose(m_pdirsystem))
//      {
//
//         ERR("failed to initialize dir-system");
//
//         return false;
//
//      }
//
//      INFO("aura::session::process_init .3");
//
//      estatus = m_pfilesystem->init_system();
//
//      if (!estatus)
//      {
//
//         m_estatus = estatus;
//
//         return estatus;
//
//      }
//
//      estatus = m_pdirsystem->init_system();
//
//      if (!estatus)
//      {
//
//         m_estatus = estatus;
//
//         return estatus;
//
//      }
//
//      estatus = ::context::initialize_context();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      if (!m_ptrace->process_init())
//      {
//
//         WARN("failed to process_init ::aura::log trace");
//
//      }
//
//      //output_debug_string("CommonAppData (matter) : " + Context.dir().commonappdata()  + "\n");
//      //output_debug_string("commonappdata (matter) : " + Context.dir().commonappdata() + "\n");
//      //output_debug_string("Common App Data (matter) : " + Context.dir().commonappdata() + "\n");
//      //output_debug_string("common app data (matter) : " + Context.dir().commonappdata() + "\n");
//
//      __compose_new(m_pcrypto);
//
//      if (!::is_set(m_pcrypto))
//      {
//
//         return false;
//
//      }
//
//      if(m_bDraw2d)
//      {
//
//         if (!init_draw2d())
//         {
//
//            return false;
//
//         }
//
//      }
//
//      enum_display_monitors();
//
//      on_update_matter_locator();
//
//      estatus = initialize_sockets();
//
//      if (!estatus)
//      {
//
//         m_estatus = estatus;
//
//         return estatus;
//
//      }
//
//      bool bMatterFromHttpCache = false;
//
//      if(m_iMatterFromHttpCache == -1)
//      {
//
//         ::file::path pathSide = Context.side_get_matter_path("app/_matter/main");
//
//         ::file::path pathLocal = local_get_matter_path("app/_matter/main");
//
//         bool bFileSystemMatter = ::dir::is(pathSide) || ::dir::is(pathLocal);
//
//         bMatterFromHttpCache = !bFileSystemMatter;
//
//      }
//      else
//      {
//
//         bMatterFromHttpCache = m_iMatterFromHttpCache != 0;
//
//      }
//
//      m_pdirsystem->m_bMatterFromHttpCache = bMatterFromHttpCache;
//
//      //estatus = create_html();
//
//      //if (!estatus)
//      //{
//
//      //   FATAL("axis::application::process_init .2");
//
//      //   return false;
//
//      //}
//
//      INFO("start");
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_uiWindowsTaskbarCreatedMessage == 0)
//      {
//
//         m_uiWindowsTaskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
//
//      }
//
//#endif
//
//      ::aura::profiler::initialize();
//
//#ifdef LINUX
//
//      ::user::g_defer_init();
//
//#endif // LINUX
//
//      INFO("success");
//
//      return true;
//
//   }
//
//
//   void system::get_time(struct timeval * point)
//   {
//#ifdef _WIN32
//      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
//      GetSystemTimeAsFileTime(&ft);
//      u64 tt;
//      ::memcpy_dup(&tt, &ft, sizeof(tt));
//      tt /= 10; // make it usecs
//      point->tv_sec = (long)tt / 1000000;
//      point->tv_usec = (long)tt % 1000000;
//#else
//      gettimeofday(point, nullptr);
//#endif
//   }
//
//
//   ::estatus system::init_draw2d()
//   {
//
//      ::estatus estatus = ::success;
//
//      try
//      {
//
//         if (!draw2d_factory_exchange())
//         {
//
//            message_box("Failed to initialize draw2d library.");
//
//            estatus = error_failed;
//
//         }
//
//      }
//      catch (...)
//      {
//
//         estatus = error_exception;
//
//      }
//
//      if (!estatus)
//      {
//
//         TRACE("draw2d_factory_exchange has failed.\n\nSome reasons:\n   - No draw2d library present;\n   - Failure to open any suitable draw2d library.", MB_OK);
//
//         return estatus;
//
//      }
//
//      try
//      {
//
//         if (!imaging_factory_exchange())
//         {
//
//            WARN("Failed to initialize imaging library.");
//
//#if !defined(MOBILE_PLATFORM)
//
//            message_box("Failed to initialize imaging library.");
//
//#endif
//// Non fatal? Missing images (if using images)?
//            //bOk = false;
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//      estatus = __construct_new(m_pdraw2d);
//
//      if (!estatus)
//      {
//
//         TRACE("Couldn't construct new draw2d.");
//
//         return false;
//
//      }
//
//      estatus = m_pdraw2d->init1();
//
//      if(!estatus)
//      {
//
//         TRACE("Couldn't initialize draw2d (init1).");
//
//         return estatus;
//
//      }
//
//      if (::succeeded(estatus))
//      {
//
//         create_factory < ::draw2d::thread_tool_item >(::e_thread_tool_draw2d);
//
//      }
//
//      return estatus;
//
//   }
//
//
//   string system::draw2d_get_default_library_name()
//   {
//
//      string str;
//
//      if (file_exists(::dir::system() / "config\\system\\draw2d.txt"))
//      {
//
//         str = file_as_string(::dir::system() / "config\\system\\draw2d.txt");
//
//   }
//      else
//      {
//
//         ::file::path strPath;
//
//         strPath = ::dir::appdata() / "draw2d.txt";
//
//         str = file_as_string(strPath);
//
//      }
//
//      if (str.has_char())
//         return "draw2d_" + str;
//      else
//      #ifdef WINDOWS_DESKTOP
//         return "draw2d_gdiplus";
//#elif __APPLE__
//      return "draw2d_quartz2d";
//#elif defined(_UWP)
//         return "draw2d_direct2d";
//#else
//         return "draw2d_cairo";
//      #endif
//   }
//
//
//   bool system::draw2d_factory_exchange()
//   {
//
//#ifdef CUBE
//
//      if (g_pfnfactoryexchangeDraw2d)
//      {
//
//         g_pfnfactoryexchangeDraw2d();
//
//      }
//
//      return true;
//
//#else
//
//      sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//      __pointer(::apex::library) & plibrary = ::get_context_system()->m_mapLibrary["draw2d"];
//
//      if (plibrary->is_opened())
//      {
//
//         return true;
//
//      }
//
//      string strLibrary;
//
//      if (has_property("draw2d"))
//      {
//
//         string strDraw2d = value("draw2d");
//
//         strDraw2d.trim();
//
//         if (strDraw2d.has_char())
//         {
//
//            ::str::begins_eat_ci(strDraw2d, "draw2d_");
//
//            ::str::begins_eat_ci(strDraw2d, "draw2d");
//
//            strLibrary = "draw2d_" + strDraw2d;
//
//         }
//
//      }
//
//      if (strLibrary.has_char())
//      {
//
//         plibrary->open(strLibrary);
//
//         if (plibrary->is_opened())
//            goto finalize;
//
//      }
//
//      strLibrary = draw2d_get_default_library_name();
//
//      if (strLibrary.is_empty())
//#ifdef WINDOWS
//         strLibrary = "draw2d_gdiplus";
//#else
//         strLibrary = "draw2d_cairo";
//#endif
//
//      plibrary->open(strLibrary);
//
//      if (plibrary->is_opened())
//         goto finalize;
//
//#ifdef WINDOWS_DESKTOP
//
//
//      if (strLibrary != "draw2d_gdiplus")
//      {
//
//         plibrary->open("draw2d_gdiplus");
//
//         if (plibrary->is_opened())
//            goto finalize;
//
//      }
//
//
//      if (strLibrary != "draw2d_direct2d")
//      {
//
//         plibrary->open("draw2d_directd");
//
//         if (plibrary->is_opened())
//            goto finalize;
//
//      }
//
//
//#endif
//
//      if (strLibrary != "draw2d_cairo")
//      {
//
//
//         plibrary->open("draw2d_cairo");
//
//         if (plibrary->is_opened())
//            goto finalize;
//
//      }
//
//      output_debug_string("No draw2d pluging available!!.");
//      return false;
//
//   finalize:
//
//      PFN_factory_exchange pfn_factory_exchange = plibrary->get < PFN_factory_exchange >("draw2d_factory_exchange");
//
//      if (pfn_factory_exchange == nullptr)
//      {
//
//         return false;
//
//      }
//
//      pfn_factory_exchange();
//
//      return true;
//
//#endif
//
//   }
//
//
//   bool system::imaging_factory_exchange()
//   {
//
//#ifdef CUBE
//
//      if (g_pfnfactoryexchangeImaging)
//      {
//
//         g_pfnfactoryexchangeImaging();
//
//      }
//
//      return true;
//
//#else
//
//      sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//      __pointer(::apex::library)& plibrary = ::get_context_system()->m_mapLibrary["imaging"];
//
//      auto estatus = __defer_construct_new(plibrary);
//
//      if (!estatus)
//      {
//
//         return false;
//
//      }
//
//      if (plibrary->is_opened())
//      {
//
//         return true;
//
//      }
//
//      string strLibrary;
//
//      if (has_property("imaging"))
//      {
//
//         string strImaging = value("imaging");
//
//         strImaging.trim();
//
//         if (strImaging.has_char())
//         {
//
//            ::str::ends_eat_ci(strImaging, "_imaging");
//
//            ::str::ends_eat_ci(strImaging, "imaging");
//
//            strLibrary = strImaging + "_imaging";
//
//         }
//
//      }
//
//      if (strLibrary.has_char())
//      {
//
//         plibrary->open(strLibrary);
//
//         if (plibrary->is_opened())
//         {
//
//            goto finalize;
//
//         }
//
//      }
//
//      strLibrary = imaging_get_default_library_name();
//
//      if (strLibrary.is_empty())
//      {
//
//#ifdef WINDOWS
//
//         strLibrary = "imaging_wic";
//
//#elif defined(__APPLE__)
//
//         strLibrary = "imaging_coreimage";
//
//#else
//
//         strLibrary = "imaging_freeimage";
//
//#endif
//
//      }
//
//      plibrary->open(strLibrary);
//
//      if (plibrary->is_opened())
//      {
//
//         goto finalize;
//
//      }
//
//#ifdef WINDOWS_DESKTOP
//
//      if (strLibrary != "wic_imaging")
//      {
//
//         plibrary->open("wic_imaging");
//
//         if (plibrary->is_opened())
//         {
//
//            goto finalize;
//
//         }
//
//      }
//
//#endif
//
//      if (strLibrary != "freeimage_imaging")
//      {
//
//         plibrary->open("freeimage_imaging");
//
//         if (plibrary->is_opened())
//         {
//
//            goto finalize;
//
//         }
//
//      }
//
//      output_debug_string("No imaging pluging available!!.");
//
//      return false;
//
//   finalize:
//
//      PFN_factory_exchange pfn_factory_exchange = plibrary->get < PFN_factory_exchange >("imaging_factory_exchange");
//
//      if (pfn_factory_exchange == nullptr)
//      {
//
//         return false;
//
//      }
//
//      pfn_factory_exchange();
//
//      return true;
//
//#endif // CUBE
//
//   }
//
//
//   string system::imaging_get_default_library_name()
//   {
//
//#ifdef WINDOWS
//
//      return "imaging_wic";
//
//#elif defined(__APPLE__)
//
//      return "imaging_coreimage";
//
//#else
//
//      return "imaging_freeimage";
//
//#endif
//
//   }
//
//
//   ::estatus system::init_thread()
//   {
//
//      if (m_psystemParent)
//      {
//
//         m_psystemParent->add_reference(this);
//
//      }
//
//      auto estatus = process_init();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = init_system();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = initial_check_directrix();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return true;
//
//   }
//
//
//   ::estatus system::init()
//   {
//
//      if (::is_set(m_pdraw2d))
//      {
//
//         if (!m_pdraw2d->init())
//         {
//
//            return false;
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//
//   ::estatus system::init1()
//   {
//
//#ifdef DEBUG
//
//      ___compile_test_sort_array_21304528734();
//
//#endif
//
//      auto estatus = __compose_new(m_puserstr);
//
//      if (!m_puserstr || !estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = __compose(m_pimaging);
//
//      if (!estatus)
//      {
//
//         if (m_bUser && m_bDraw2d)
//         {
//
//            return estatus;
//
//         }
//
//      }
//
//      get_context_session()->m_puserstrcontext->defer_ok(m_puserstr);
//
//      //__throw(todo("filehandler"));
//
//      //estatus = __compose_new(m_pfilehandler);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//#if !defined(CUBE) && !defined(ANDROID)
//
//#if !defined(_DEBUG) || defined(WINDOWS)
//
//      try
//      {
//
//#endif
//
//         find_applications_from_cache();
//
//#if !defined(_DEBUG) || defined(WINDOWS)
//
//      }
//      catch (...)
//      {
//
//      }
//
//#endif
//
//#endif
//
//      return true;
//
//   }
//
//
//   ::estatus system::initial_check_directrix()
//   {
//
//      //while(auto pcreate = get_command()->get_create())
//      while (auto pcreate = get_create())
//      {
//
//         do_request(pcreate);
//
//      }
//
//      return true;
//
//   }
//
//
//   ::estatus system::inline_init()
//   {
//
//      ::estatus estatus = ::aura::context_thread::inline_init();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      set_context_app(m_papplicationStartup);
//
//      m_papplicationStartup.release();
//
//      return estatus;
//
//   }
//
//
//   ::estatus system::inline_term()
//   {
//
//      ::estatus estatus = ::aura::context_thread::inline_term();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//   ::estatus system::init_system()
//   {
//
//      if (m_bConsole)
//      {
//
//         auto estatus = get_context_session()->inline_init();
//
//         if (!estatus)
//         {
//
//            return estatus;
//
//         }
//
//      }
//      else
//      {
//
//         if (!get_context_session()->begin_synch())
//         {
//
//            return false;
//
//         }
//
//      }
//
//      auto estatus = init1();
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = init2();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return ::success;
//
//   }
//
//
//   //bool system::is_system() const
//   //{
//
//   //   return true;
//
//   //}
//
//
//
//   string system::crypto_md5_text(const string & str)
//   {
//
//      return crypto().md5(str);
//
//   }
//
//
//   //__pointer(::aura::session) system::on_create_session()
//   //{
//
//   //   return __new(::axis::session);
//
//   //}
//
//
//   //void system::on_request(::create * pcreate)
//   //{
//
//   //   ::aura::system::on_request(pcreate);
//
//   //}
//
//
//
//
//
//
//
//   //::user::document * system::place_hold(::user::interaction * pinteraction)
//   //{
//
//
//   //   //if(m_pcubeInterface != nullptr)
//   //   //{
//   //   // return m_pcubeInterface->hold(pinteraction);
//   //   //}
//
//   //   return nullptr;
//
//   //}
//
//
//   //::aura::session * system::query_session(index iEdge)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//
//
//
//
//
//
//
//
//   //void system::hist_hist(const char * psz)
//   //{
//   //}
//
//   //void system::on_request(::create * pcreate)
//   //{
//
//   //   ::axis::system::on_request(pcreate);
//
//   //}
//
//   //::user::interaction_impl * system::impl_from_handle(void * posdata)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//   //::user::interaction * system::ui_from_handle(void * posdata)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//
//   string system::url_encode(const string & str)
//   {
//
//      return m_purldepartment->url_encode(str);
//
//   }
//
//
//} // namespace base
//
//
//CLASS_DECL_BASE ::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
//{
//
//   string strFolder = pathExe.folder();
//
//   strFolder.replace(":", "");
//
//   return dir::ca2roaming() / "appdata" / strFolder / strAppId / pszPlatform / pszConfiguration / pszLocale / pszSchema;
//
//}
//
//
//CLASS_DECL_BASE bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
//{
//
//   ::file::path path;
//
//   path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";
//
//   strBuild = file_as_string(path);
//
//   return strBuild.has_char();
//
//}
//
//
//CLASS_DECL_BASE bool set_application_installed(const ::file::path & pathExe, string strAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
//{
//
//   ::file::path path;
//
//   path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";
//
//   return file_put_contents(path, pszBuild);
//
//}
//
//
//CLASS_DECL_BASE::file::path get_application_path(string strAppId, const char * pszPlatform, const char * pszConfiguration)
//{
//
//   ::file::path pathFolder;
//
//   pathFolder = dir::stage(strAppId, pszPlatform, pszConfiguration);
//
//   string strName;
//
//   strName = ::process::app_id_to_app_name(strAppId);
//
//   ::file::path path;
//
//   path = pathFolder / (strName + ".exe");
//
//   return path;
//
//}
//
//
//CLASS_DECL_BASE ::file::path get_last_run_application_path_file(string strAppId)
//{
//
//   ::file::path pathFile = ::dir::local() / "appdata" / strAppId / "last_run_path.txt";
//
//   return pathFile;
//
//}
//
//
//CLASS_DECL_BASE::file::path get_last_run_application_path(string strAppId)
//{
//
//   ::file::path pathFile = get_last_run_application_path_file(strAppId);
//
//   ::file::path path = ::file_as_string(pathFile);
//
//   return path;
//
//}
//
//
//CLASS_DECL_BASE bool set_last_run_application_path(string strAppId)
//{
//
//   ::file::path path = ::file::app_module();
//
//   ::file::path pathFile = get_last_run_application_path_file(strAppId);
//
//   return file_put_contents(pathFile, path);
//
//}
//
//
//
//
//
//
//
//
////#include "base/node/_node.h"
//
//
//#ifdef WINDOWS_DESKTOP
////#include "aura/os/windows/windows_system_interaction_impl.h"
//#elif defined(_UWP)
//#include "aura/os/uwp/_uwp.h"
//#endif
//
//
////#if !defined(WINDOWS) && !defined(MACOS)
////#include <ft2build.h>
////#include FT_FREETYPE_H
////#endif
//
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//
////#include "base/os/windows/windows_system_interaction_impl.h"
//
//
//#include <HighLevelMonitorConfigurationAPI.h>
//
//DWORD mc_color_kelvin(MC_COLOR_TEMPERATURE e)
//{
//   switch (e)
//   {
//   case MC_COLOR_TEMPERATURE_4000K:
//      return 4000;
//   case MC_COLOR_TEMPERATURE_5000K:
//      return 5000;
//   case MC_COLOR_TEMPERATURE_6500K:
//      return 6500;
//   case MC_COLOR_TEMPERATURE_7500K:
//      return 7500;
//   case MC_COLOR_TEMPERATURE_8200K:
//      return 8200;
//   case MC_COLOR_TEMPERATURE_9300K:
//      return 9300;
//   case MC_COLOR_TEMPERATURE_10000K:
//      return 10000;
//   case MC_COLOR_TEMPERATURE_11500K:
//      return 11500;
//   default:
//      return 0;
//   }
//}
//
//MC_COLOR_TEMPERATURE kelvin_mc_color(DWORD kelvin)
//{
//   if (kelvin < 4500)
//   {
//      return MC_COLOR_TEMPERATURE_4000K;
//   }
//   else if (kelvin < 5750)
//   {
//      return MC_COLOR_TEMPERATURE_5000K;
//   }
//   else if (kelvin < 7000)
//   {
//      return MC_COLOR_TEMPERATURE_6500K;
//   }
//   else if (kelvin < 7850)
//   {
//      return MC_COLOR_TEMPERATURE_7500K;
//   }
//   else if (kelvin < 8750)
//   {
//      return MC_COLOR_TEMPERATURE_8200K;
//   }
//   else if (kelvin < 9650)
//   {
//      return MC_COLOR_TEMPERATURE_9300K;
//   }
//   else if (kelvin < 10750)
//   {
//      return MC_COLOR_TEMPERATURE_10000K;
//   }
//   else
//   {
//      return MC_COLOR_TEMPERATURE_11500K;
//   }
//}
//
//#elif defined(LINUX)
//
//
//#endif
//
//
//
//
////#ifdef CUBE
////
////extern "C" DECLARE_NEW_BASE_LIBRARY(experience);
////
////#endif
//
//#ifdef WINDOWS
//#undef new
//#define new ACME_NEW
//#endif
//
//#ifdef LINUX
//#include <dlfcn.h>
//
//void* g_pbasecore = nullptr;
//
//
//typedef void BASECORE_INIT();
//#endif // LINUX
//
//
//namespace base
//{
//
//   CLASS_DECL_BASE void black_body(float* r, float* g, float* b, DWORD dwTemp);
//
//   /*  bool system::on_application_menu_action(const char * pszCommand)
//     {
//        return ::aura::system::on_application_menu_action(pszCommand);
//     }*/
//
//
//     //system::system()
//     //{
//
//     //   m_bFinalizeIfNoSessionSetting = true;
//     //   m_bFinalizeIfNoSession = false;
//
//     //   create_factory < ::aura::session, ::aura::session >();
//
//     //}
//
//
//  //   ::estatus system::initialize_system(::object* pobject, app_core* pappcore)
//  //   {
//  //
//  //      auto estatus = ::aura::system::initialize_system(pobject, pappcore);
//  //
//  //      if (!estatus)
//  //      {
//  //
//  //         return estatus;
//  //
//  //      }
//  //
//  //      //estatus = ::aura::application::initialize(pobjectContext);
//  //
//  //     //if (!estatus)
//  //     //{
//  //
//  //     //   return estatus;
//  //
//  //     //}
//  //
//  //     //m_strAppId = "base_system";
//  //     //m_strAppName = "base_system";
//  //     //m_strBaseSupportId = "base_system";
//  //     //m_strInstallToken = "base_system";
//  //
//  //      create_factory < ::draw2d::icon >();
//  //
//  //      //#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
//  //      //
//  //      //      m_possystemwindow = new os_system_window();
//  //      //
//  //      //#endif
//  //
//  //
//  //
//  //            //estatus = ::aura::application::initialize(pobject);
//  //
//  //            //if (!estatus)
//  //            //{
//  //
//  //            //   return estatus;
//  //
//  //            //}
//  //
//  //            //m_strAppId                    = "core_system";
//  //            //m_strAppName                  = "core_system";
//  //            //m_strBaseSupportId            = "core_system";
//  //            //m_strInstallToken             = "core_system";
//  //
//  //      m_phistory = nullptr;
//  //      m_ppatch = new aura::patch();
//  //      g_pszCooperativeLevel = "aura";
//  //
//  //      estatus = __compose(m_puserset, __new(::account::user_set(this)));
//  //
//  //      if (!estatus)
//  //      {
//  //
//  //         throw ::exception::exception(estatus);
//  //
//  //      }
//  //
//  //      //#ifdef _UWP
//  //      //      m_window                                  = nullptr;
//  //      //#endif
//  //
//  //            //::aura::application * papp = ::get_context_application(pobject);
//  //
//  //            //if(papp == nullptr)
//  //            //{
//  //
//  //            //   set("parent_system") = nullptr;
//  //
//  //            //}
//  //            //else
//  //            //{
//  //
//  //            //   set("parent_system") = papp->m_psystem;
//  //
//  //            //}
//  //
//  //      string strId;
//  //      //strId = m_strAppName;
//  //      //strId += ::str::has_char(m_strAppId, ".");
//  //      //strId += ::str::has_char(m_strBaseSupportId, ".");
//  //
//  //
//  //
//  //
//  //
//  //
//  //
//  //
//  //
//  //
//  //      // m_userset.set_app(this);
//  //      //      m_email.set_app(this);
//  //
//  //
//  //
//  //
//  //
//  //
//  //      //m_bInitApplication         = false;
//  //      //m_bInitApplicationResult   = FALSE;
//  //      //m_bProcessInitialize       = false;
//  //      //m_bProcessInitializeResult = false;
//  //
//  //      //m_puserstr                 = nullptr;
//  //
//  //      //m_pparserfactory           = nullptr;
//  //
//  //      //m_bLicense                 = false;
//  //
//  //      //m_prunstartinstaller       = nullptr;
//  //      //m_bLicense                 = false;
//  //
//  //#ifdef WINDOWS_DESKTOP
//  //
//  //      m_uiWindowsTaskbarCreatedMessage = 0;
//  //
//  //#endif
//  //
//  //      return estatus;
//  //
//  //   }
//
//
//     //system::~system()
//     //{
//
//     //
//
//     //}
//
//
//   void system::discard_to_factory(__pointer(object) pca)
//   {
//
//      UNREFERENCED_PARAMETER(pca);
//
//   }
//
//
//   //bool system::is_system() const
//   //{
//
//   //   return true;
//
//   //}
//
//
//   ::estatus system::defer_xml()
//   {
//
//      if (m_pxml)
//      {
//
//         return ::success;
//
//      }
//
//      auto estatus = __compose_new(m_pxml);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = m_pxml->init1();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = m_pxml->init();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//
//   ::estatus system::init2()
//   {
//
//      //if(!::aura::application::init2())
//      //   return false;
//
//      //auto estatus = ::aura::system::init2();
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//         auto estatus = __compose_new(m_phistory);
//
//         if(!estatus)
//         {
//
//            return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//   //bool system::InitApplication()
//   //{
//
//   //   if(m_bInitApplication)
//   //      return m_bInitApplicationResult;
//
//   //   m_bInitApplicationResult      = FALSE;
//   //   m_bInitApplication            = true;
//
//   //   m_bInitApplicationResult = ::aura::system::InitApplication();
//
//   //   return m_bInitApplicationResult;
//   //}
//
////
////   ::estatus system::process_init()
////   {
////
////      //if (m_bProcessInitialize)
////      //{
////
////      //   return m_bProcessInitializeResult;
////
////      //}
////
////      INFO("start");
////
////      //m_bProcessInitializeResult    = false;
////
////      //m_bProcessInitialize          = true;
////
////#ifdef WINDOWS_DESKTOP
////
////      if (m_uiWindowsTaskbarCreatedMessage == 0)
////      {
////
////         m_uiWindowsTaskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
////
////      }
////
////#endif
////
////      //if (!::aura::application::process_init())
////      //{
////
////      //   ERR(".1");
////
////      //   return false;
////
////      //}
////
////      if (!::aura::system::process_init())
////      {
////
////         ERR(".2");
////
////         return false;
////
////      }
////
////      ::aura::profiler::initialize();
////
////
////#ifdef LINUX
////
////      ::user::g_defer_init();
////
////#endif // LINUX
////
////
////      //m_phtml = create_html();
////
////      //m_phtml->add_ref(OBJ_REF_DBG_ARGS);
////
////      //if(m_phtml == nullptr)
////      //   return false;
////
////      //m_phtml->construct(this);
////
////      //m_bProcessInitializeResult = true;
////
////      INFO("success");
////
////      return true;
////
////   }
//
//
//   //::estatus system::init()
//   //{
//   //   //
//   //   //#ifndef APPLEOS
//   //   //
//   //   //      if(m_pparserfactory == nullptr)
//   //   //      {
//   //   //
//   //   //      }
//   //   //
//   //   //#endif
//
//   //         //if (!::aura::application::init())
//   //         //{
//
//   //         //   return false;
//
//   //         //}
//
//   //   return true;
//
//   //}
//
//
////   ::estatus system::init1()
////   {
////
////      m_pfilehandler = __new(::filehandler::handler(this));
////
////      //if (!::aura::application::init1())
////      //{
////
////      //   return false;
////
////      //}
////
////      if (!::aura::system::init1())
////      {
////
////         return false;
////
////      }
////
////      //if(Session.account()->create_system_user("system") == nullptr)
////      // return false;
////
////#if !defined(CUBE) && !defined(ANDROID)
////
////#if !defined(_DEBUG) || defined(WINDOWS)
////      try
////      {
////#endif
////         find_applications_from_cache();
////#if !defined(_DEBUG) || defined(WINDOWS)
////      }
////      catch (...)
////      {
////      }
////#endif
////
////#endif
////
////      //if(!m_phtml->initialize())
////      //   return false;
////
////      return true;
////
////   }
////
//
//
//
//   //::filehandler::handler& system::filehandler()
//   //{
//   //    __throw(todo("filehandler"));
//   //    return *m_pfilehandler;
//
//   //}
//
//
//   void system::on_start_find_applications_from_cache()
//   {
//
//      __throw(todo("filehandler"));
//     // m_pfilehandler->m_ptree->remove_all();
//
//   }
//
//   void system::on_end_find_applications_from_cache(stream& is)
//   {
//
//      //__throw(todo("filehandler"));
//      //is >> *m_pfilehandler;
//
//   }
//
//   void system::on_end_find_applications_to_cache(stream& os)
//   {
//
//      //__throw(todo("filehandler"));
//      //os << *m_pfilehandler;
//
//   }
//
//   void system::on_map_application_library(::apex::library& library)
//   {
//
//      __throw(todo("filehandler"));
//      // m_pfilehandler->defer_add_library(library.m_pca2library);
//
//   }
//
//
//   void system::on_graphics_ready()
//   {
//
//      //::aura::system::on_graphics_ready();
//
//      //if (Session.userex()->shell()->m_bPendingUpdate)
//      //{
//
//      //   Session.userex()->shell()->on_update_sizes_interest();
//
//      //}
//
//   }
//
//
//   //::estatus system::init3()
//   //{
//
//   //   //if(!::aura::application::init3())
//   //   //{
//
//   //   //   return false;
//
//   //   //}
//
//   //   if(m_phistory == nullptr)
//   //   {
//   //      m_phistory = __new(os_history(this));
//   //   }
//
//   //   return true;
//
//   //}
//
//
//   //::estatus system::init_system()
//   //{
//
//   //   if (!::aura::system::init_system())
//   //   {
//
//   //      return false;
//
//   //   }
//
//   //   /*set_enum_name(::type_null      , "null");
//   //   set_enum_name(::type_empty     , "is_empty");
//   //   set_enum_name(::type_string    , "string");
//   //   set_enum_name(::type_int32   , "integer");
//   //   set_enum_name(::type_uint32     , "ulong");
//   //   set_enum_name(::type_element       , "ca2");
//   //   set_enum_name(::type_bool      , "bool");
//   //   set_enum_name(::type_double    , "double");*/
//
//   //   //if (!::aura::application::init_application())
//   //   //{
//
//   //   //   return false;
//
//   //   //}
//
//   //   //m_pbergedgemap = __new(::aura::session::map);
//
//
//   //   return true;
//
//   //}
//
//
//   //::estatus system::bergedge_start()
//   //{
//
//   //   return true;
//
//   //}
//
//
//
//
//
////
////
////
////   void system::term_system()
////   {
////
////
////
////      //__wait_threading_count(::millis((5000) * 8));
////
////      //::multithreading::wait_threads(40_s);
////
//////#ifdef LINUX
//////
//////      BASECORE_INIT * f =  (BASECORE_INIT *) dlsym(g_pbasecore, "linux_g_direct_term");
//////
//////      if(f != nullptr)
//////      {
//////
//////         output_debug_string("linux_g_direct_term entry point not found at basecore library");
//////
//////         (*f)();
//////
//////      }
//////
//////#endif
////      //::aura::application::term_application();
////      try
////      {
////
////         ::aura::system::term_system();
////
////      }
////      catch (...)
////      {
////
////         m_result.add(error_failed);
////
////      }
////
////#ifdef LINUX
////
////      try
////      {
////
////         ::user::g_defer_term();
////
////      }
////      catch (...)
////      {
////
////      }
////
////#endif // LINUX
////
////
////   }
//
//
//   //__pointer(::aura::session) system::on_create_session()
//   //{
//
//   //   return __new(::aura::session);
//
//   //}
//
//
//   //::aura::session * system::query_session(index iEdge)
//   //{
//
//   //   ::aura::session * pbergedge = nullptr;
//
//   //   if (m_pbergedgemap == nullptr)
//   //   {
//
//   //      return nullptr;
//
//   //   }
//
//   //   if(!m_pbergedgemap->lookup(iEdge,pbergedge))
//   //   {
//
//   //      return nullptr;
//
//   //   }
//
//   //   return pbergedge;
//
//   //}
//
//
//
//   ::aura::history& system::hist()
//   {
//
//      return *m_phistory;
//
//   }
//
//
//   estatus system::set_history(::aura::history* phistory)
//   {
//
//      auto estatus = __compose(m_phistory, phistory);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//   ::apex::library * system::on_get_library(const char* pszLibrary)
//   {
//
//      __pointer(::apex::library) plibrary;
//
//      bool bLibraryOk = false;
//
//      auto plibraryfactory = ::static_setup::get_first(::static_setup::flag_library, pszLibrary);
//
//      if(!plibraryfactory)
//      {
//
//         return nullptr;
//
//      }
//
//      plibrary = plibraryfactory->new_library();
//
//      if(!plibrary)
//      {
//
//         return nullptr;
//
//      }
//
//      auto estatus = plibrary->initialize(this);
//
//      if (estatus)
//      {
//
//         bLibraryOk = true;
//
//      }
//
//      if (plibrary && bLibraryOk)
//      {
//
//         return plibrary;
//
//      }
//
//      return nullptr;
//
//   }
//
//
//   //void system::term()
//   //{
//
//   //   m_phistory.release();
//
//
//   //   m_pfilehandler.release();
//
//   //   try
//   //   {
//
//   //      ::aura::system::term();
//
//   //   }
//   //   catch (...)
//   //   {
//
//   //      m_result.add(error_failed);
//
//   //   }
//
//   //}
//
//
//   void system::on_allocation_error(const ::string& str, ::object* pobject)
//   {
//
//      string strMessage;
//
//      strMessage.Format("system::on_allocation_error Implement \"%s\" allocation\n", str.c_str());
//
//      dev_log(strMessage);
//
//   }
//
//
//   //void system::on_request(::create* pcreate)
//   //{
//
//   //   //get_platform(pcreate->m_pcommandline->m_iEdge,pcreate->m_pcommandline->m_papplicationbias);
//
//   //   ::aura::system::on_request(pcreate);
//
//   //}
//
//
//   bool system::sync_load_url(string& str, const char* pszUrl, ::account::user* puser, ::http::cookies* pcookies)
//
//   {
//
//      string filename = Context.file().time_square();
//
//      property_set set;
//
//      set["user"] = puser;
//
//      set["cookies"] = pcookies;
//
//      if (!Context.http().download(pszUrl, filename, set))
//
//      {
//
//         return false;
//
//      }
//
//      string strLocation = set["get_headers"]["Location"];
//
//      if (strLocation.has_char())
//      {
//
//         property_set set;
//
//         set["user"] = puser;
//
//         set["cookies"] = pcookies;
//
//         Context.file().del(filename);
//
//         return Context.http().download(str, strLocation, set);
//
//      }
//
//      str = Context.file().as_string(filename);
//
//      return true;
//
//   }
//
//
//   ::aura::patch& system::patch()
//   {
//
//      return *m_ppatch;
//
//   }
//
//
//   //::http::system & system::http()
//   //{
//
//   //   return *m_sphttpsystem;
//
//   //}
//
//
//   //bool system::base_support()
//   //{
//
//   //   return true;
//
//   //}
//
//
//   //index system::get_new_bergedge(application_bias * pbiasCreation)
//   //{
//
//   //   index iNewEdge = m_iNewEdge;
//
//   //   ::aura::session * pbergedge = nullptr;
//
//   //   while(m_pbergedgemap->lookup(iNewEdge,pbergedge))
//   //   {
//
//   //      iNewEdge++;
//
//   //   }
//
//   //   if (get_context_session(iNewEdge, pbiasCreation) == nullptr)
//   //   {
//
//   //      return -1;
//
//   //   }
//
//   //   m_iNewEdge = iNewEdge + 1;
//
//   //   return iNewEdge;
//
//   //}
//
//
//
//
//   //::user::document * system::place_hold(::user::interaction * pinteraction)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//
//   //bool system::on_install()
//   //{
//
//   //   //try
//   //   //{
//
//   //   //   xxdebug_box("system::on_install","system::on_install",0);
//
//   //   //   if (!::aura::application::on_install())
//   //   //   {
//
//   //   //      return false;
//
//   //   //   }
//
//   //   //}
//   //   //catch(...)
//   //   //{
//
//   //   //   return false;
//
//   //   //}
//
//   //   return true;
//
//   //}
//
//
//   string system::get_host_location_url()
//   {
//
//      return "";
//
//   }
//
//
//   ::estatus system::add_view_library(::apex::library* plibrary)
//   {
//
//      m_libraryspa.add(plibrary);
//
//      ::array < ::id > ida;
//
//      plibrary->get_create_view_id_list(ida);
//
//      for (i32 i = 0; i < ida.get_count(); i++)
//      {
//
//         m_idmapCreateViewLibrary.set_at(ida[i], plibrary);
//
//      }
//
//      return true;
//
//   }
//
//
//   //   void system::post_fork_uri(const char * pszUri,application_bias * papplicationbias)
//   //   {
//   //
//   //      add_fork_uri(pszUri,papplicationbias);
//   //
//   //      //if(has_property("version"))
//   //      //{
//   //
//   //      //   install().m_strVersion = m_varTopicQuery["version"];
//   //
//   //      //}
//   //
//   //      if(m_varTopicQuery["locale"].array_get_count() > 0)
//   //      {
//   //
//   //         Session.set_locale(m_varTopicQuery["locale"].stra()[0],::source_user);
//   //
//   //      }
//   //
//   //      if(m_varTopicQuery["schema"].array_get_count() > 0)
//   //      {
//   //
//   //         Session.set_schema(m_varTopicQuery["schema"].stra()[0],::source_user);
//   //
//   //      }
//   //
//   //   }
//
//
//#ifdef _UWP
//
//
//   bool system::get_window_rect(RECT* prect)
//   {
//
//      if (::is_null(get_context_session()))
//      {
//
//         return false;
//
//      }
//
//      try
//      {
//
//         if (::is_null(get_context_session()->m_puiHost))
//         {
//
//            return false;
//
//         }
//
//         get_context_session()->m_puiHost->get_window_rect(prect);
//
//      }
//      catch (...)
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }
//
//
//#endif
//
//
//   //::estatus     system::do_request(::create* pcreate)
//   //{
//
//   //   return aura::system::do_request(pcreate);
//
//   //}
//
//
//   void system::assert_valid() const
//   {
//
//      ::thread::assert_valid();
//
//   }
//
//
//   void system::dump(dump_context& context) const
//   {
//
//      ::thread::dump(context);
//
//   }
//
//
//   ::estatus     system::main()
//   {
//
//      return ::thread::main();
//
//   }
//
//
//   //__pointer_array(::aura::session) & system::planesessionptra()
//   //{
//
//   //   return m_planesessionptra;
//
//   //}
//
//
//   void system::hist_hist(const char* psz)
//   {
//
//      hist().hist(psz);
//
//   }
//
//
//   //::type system::get_pane_tab_view_type_info()
//   //{
//
//   //   return __type(userex::pane_tab_view);
//
//   //}
//
//
//
//
////
////   ::estatus system::initialize_system(::object* pobjectContext, ::app_core* pappcore)
////   {
////
////      auto estatus = ::aura::system::initialize_system(pobjectContext, pappcore);
////
////      if (!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      //estatus = ::aura::application::initialize(pobjectContext);
////
////      //if (!estatus)
////      //{
////
////      //   return estatus;
////
////      //}
////
////      //m_strAppId = "base_system";
////      //m_strAppName = "base_system";
////      //m_strBaseSupportId = "base_system";
////      //m_strInstallToken = "base_system";
////
////      create_factory < ::draw2d::icon >();
////
////      g_pszCooperativeLevel = "aura";
////
////#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
////
////      m_possystemwindow = new os_system_window();
////
////#endif
////
////      return estatus;
////
////   }
//
//
//   //void system::term_system()
//   //{
//
//   //   //aura::application::term_application();
//   //   aura::system::term_system();
//
//   //}
//
//
//   void system::set_active_guie(::user::interaction* pinteraction)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      if (pinteraction == nullptr)
//      {
//
//         ::set_active_window(nullptr);
//
//      }
//      else
//      {
//
//         ::set_active_window(pinteraction->get_wnd()->get_safe_handle());
//
//      }
//
//#endif
//
//   }
//
//
//   void system::set_focus_guie(::user::interaction* pinteraction)
//   {
//
//      if (pinteraction == nullptr)
//      {
//
//         ::set_focus(nullptr);
//
//         return;
//
//      }
//
//
//      ::set_focus(pinteraction->get_safe_handle());
//
//      if (pinteraction->get_wnd() != nullptr)
//      {
//
//         pinteraction->SetFocus();
//
//      }
//
//      return;
//
//   }
//
//
//   //::count system::get_monitor_count()
//   //{
//
//   //   return ::aura::system::get_monitor_count();
//
//   //}
//
//
//   DWORD system::get_monitor_color_temperature(index iMonitor)
//   {
//
//#ifdef _UWP
//
//      return 0;
//
//#elif defined(LINUX)
//
//      return 0;
//
//#elif defined(MACOS)
//
//      return 0;
//
//#elif defined(APPLE_IOS)
//
//      return 0;
//
//#elif defined(ANDROID)
//
//      return 0;
//
//#else
//
//      if (iMonitor < 0)
//      {
//
//         return 0;
//
//      }
//
//      if (iMonitor >= m_hmonitora.get_count())
//      {
//
//         return 0;
//
//      }
//
//      MC_COLOR_TEMPERATURE e;
//
//      if (!GetMonitorColorTemperature(m_hmonitora[iMonitor], &e))
//      {
//
//         return 0;
//
//      }
//
//      return mc_color_kelvin(e);
//
//#endif
//
//   }
//
//   ::mutex g_monitor_adjust;
//
//   bool system::adjust_monitor(index iMonitor, DWORD dwTemperature, double dBrightness, double dGamma)
//   {
//
//#ifdef _UWP
//
//      return true;
//
//#elif defined(LINUX)
//
//      return true;
//
//#elif defined(MACOS)
//
//      return true;
//
//#elif defined(APPLE_IOS)
//
//      return true;
//
//#elif defined(ANDROID)
//
//      return true;
//
//#else
//
//      sync_lock sl(&g_monitor_adjust);
//
//      if (iMonitor < 0)
//      {
//
//         return 0;
//
//      }
//
//      if (iMonitor >= m_hmonitora.get_count())
//      {
//
//         return 0;
//
//      }
//
//      if (dBrightness <= 0.0)
//      {
//
//         dBrightness = 0.1;
//
//      }
//
//      if (dBrightness >= 1.0)
//      {
//
//         dBrightness = 1.0;
//
//      }
//
//      if (dGamma <= 0.1)
//      {
//
//         dGamma = 0.1;
//
//      }
//
//      if (dGamma >= 10.0)
//      {
//
//         dGamma = 10.0;
//
//      }
//
//
//      DWORD dwMinDriveR;
//      DWORD dwCurDriveR;
//      DWORD dwMaxDriveR;
//      DWORD dwMinDriveG;
//      DWORD dwCurDriveG;
//      DWORD dwMaxDriveG;
//      DWORD dwMinDriveB;
//      DWORD dwCurDriveB;
//      DWORD dwMaxDriveB;
//      DWORD dwMinGainR;
//      DWORD dwCurGainR;
//      DWORD dwMaxGainR;
//      DWORD dwMinGainG;
//      DWORD dwCurGainG;
//      DWORD dwMaxGainG;
//      DWORD dwMinGainB;
//      DWORD dwCurGainB;
//      DWORD dwMaxGainB;
//
//      float fR;
//      float fG;
//      float fB;
//
//      //dwTemperature = 4000;
//
//      black_body(&fR, &fG, &fB, dwTemperature);
//
//      MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);
//
//      HMONITOR hMonitor = nullptr;
//      DWORD cPhysicalMonitors;
//      LPPHYSICAL_MONITOR pPhysicalMonitors = nullptr;
//
//      // Get the number of physical monitors.
//      BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
//         m_hmonitora[iMonitor],
//         &cPhysicalMonitors
//      );
//
//      if (!bSuccess || cPhysicalMonitors <= 0)
//      {
//
//         return 0;
//
//      }
//
//      PHYSICAL_MONITOR monitor;
//
//      bSuccess = GetPhysicalMonitorsFromHMONITOR(m_hmonitora[iMonitor], 1, &monitor);
//
//      Sleep(500);
//
//      //MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);
//
//
//
//      //if (!SetMonitorColorTemperature(monitor.hPhysicalMonitor, e))
//      //{
//
//      //   return false;
//
//      //}
//      //return true;
//
//
//      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
//      {
//
//         DWORD dwLastError = get_last_error();
//
//         TRACELASTERROR();
//
//         goto error;
//
//      }
//
//      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
//      {
//
//         return false;
//
//      }
//
//      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
//      {
//
//         return false;
//
//      }
//
//      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
//      {
//
//         return false;
//
//      }
//
//      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
//      {
//
//         return false;
//
//      }
//
//      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
//      {
//
//         return false;
//
//      }
//
//
//      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMinGainR);
//      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMinGainG);
//      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMinGainB);
//            //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, (DWORD)(dwMinDriveR + (dwMaxDriveR - dwMinDriveR) * r));
//            //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, (DWORD)(dwMinDriveG + (dwMaxDriveG - dwMinDriveG) * g));
//            //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, (DWORD)(dwMinDriveB + (dwMaxDriveB - dwMinDriveB) * b));
//            //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMaxGainR);
//            //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMaxGainG);
//            //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMaxGainB);
//      bool bDifferent = false;
//      if (dwMaxDriveR != dwCurDriveR)
//      {
//         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
//         bDifferent = true;
//      }
//      if (dwMaxDriveG != dwCurDriveG)
//      {
//         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
//         bDifferent = true;
//      }
//      if (dwMaxDriveB != dwCurDriveB)
//      {
//         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
//         bDifferent = true;
//      }
//
//
//      /* Helper macro used in the fill functions */
////#define F(Y, C)  pow(dBrightness * C, 1.0 / dGamma)
//#define F(C)  pow(dBrightness * C, 1.0 / dGamma)
//
//      DWORD dwR = (DWORD)(dwMinGainR + (dwMaxGainR - dwMinGainR) * F(fR));
//      DWORD dwG = (DWORD)(dwMinGainG + (dwMaxGainG - dwMinGainG) * F(fG));
//      DWORD dwB = (DWORD)(dwMinGainB + (dwMaxGainB - dwMinGainB) * F(fB));
//
//      if (dwR != dwCurGainR)
//      {
//         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
//         bDifferent = true;
//      }
//      if (dwG != dwCurGainG)
//      {
//         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
//         bDifferent = true;
//      }
//      if (dwB != dwCurGainB)
//      {
//         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
//         bDifferent = true;
//      }
//
//#undef F
//
//      if (!bDifferent)
//      {
//
//         goto finalize;
//
//      }
//
//      int iRepeat = 0;
//   repeat:
//
//      bDifferent = false;
//
//      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
//      {
//
//         if (dwCurDriveR != dwMaxDriveR)
//         {
//            Sleep(500);
//            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
//            Sleep(500);
//            bDifferent = true;
//         }
//
//      }
//
//      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
//      {
//
//         if (dwCurDriveG != dwMaxDriveG)
//         {
//            Sleep(500);
//            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
//            Sleep(500);
//            bDifferent = true;
//         }
//
//      }
//
//      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
//      {
//
//         if (dwCurDriveB != dwMaxDriveB)
//         {
//            Sleep(500);
//            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
//            Sleep(500);
//            bDifferent = true;
//         }
//
//      }
//
//      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
//      {
//
//         if (dwCurGainR != dwR)
//         {
//            Sleep(500);
//            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
//            Sleep(500);
//            bDifferent = true;
//         }
//
//
//      }
//
//      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
//      {
//
//         if (dwCurGainG != dwG)
//         {
//            Sleep(500);
//            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
//            Sleep(500);
//            bDifferent = true;
//         }
//
//      }
//
//      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
//      {
//
//         if (dwCurGainB != dwB)
//         {
//            Sleep(500);
//            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
//            Sleep(500);
//            bDifferent = true;
//         }
//
//      }
//
//      if (bDifferent)
//      {
//
//         iRepeat++;
//
//         if (iRepeat < 3)
//         {
//
//            goto repeat;
//
//         }
//
//      }
//      Sleep(500);
//   finalize:
//      ;
//      DestroyPhysicalMonitors(1, &monitor);
//      return true;
//   error:
//      ;
//      Sleep(500);
//      // Close the monitor handles.
//      DestroyPhysicalMonitors(1, &monitor);
//      return false;
//
//#endif
//
//   }
//
//
////   bool system::get_monitor_rect(index iMonitor, RECT* prect)
////   {
////
////#ifdef _UWP
////
////      get_window_rect(prect);
////
////      return true;
////
////#elif defined(LINUX)
////
////
////      return ::aura::system::get_monitor_rect(iMonitor, prect);
////
////      //return os_get_monitor_rect(iMonitor, prect);
////
////
////
////#else
////
////      return ::aura::system::get_monitor_rect(iMonitor, prect);
////
////
////#endif
////
////   }
//
//
//   //bool system::get_wkspace_rect(index iWkspace, RECT* prect)
//   //{
//
//   //   //#ifdef LINUX
//   //   //
//   //   //      xdisplay  d;
//   //   //
//   //   //      if(!d.open(nullptr))
//   //   //         return false;
//   //   //
//   //   //      prect->left = 0;
//
//   //   //      prect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
//
//   //   //      prect->top = 0;
//
//   //   //      prect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
//
//   //   //
//   //   //      return true;
//   //   //
//   //   //#else
//
//   //   return ::aura::system::get_wkspace_rect(iWkspace, prect);
//
//
//   //   //#endif
//
//   //}
//
//   //
//   //   ::estatus system::process_init()
//   //   {
//   //
//   //
//   //      //::aura::application * papp = ::get_context_application(get_object());
//   //
//   //      //if (papp == nullptr)
//   //      //{
//   //
//   //      //   set("parent_system") = nullptr;
//   //
//   //      //}
//   //      //else
//   //      //{
//   //
//   //      //   set("parent_system") = papp->m_psystem;
//   //
//   //      //}
//   ////#if !defined(WINDOWS) && !defined(MACOS)
//   ////
//   ////      i32 error = FT_Init_FreeType((FT_Library *)&m_ftlibrary);
//   ////
//   ////      if (error)
//   ////      {
//   ////
//   ////         TRACE("an error occurred during Free Type library initialization");
//   ////
//   ////         return false;
//   ////
//   ////      }
//   ////
//   ////#endif
//   //
//   //      //if (m_peengine != nullptr)
//   //      //{
//   //
//   //      //   m_peengine = new ::exception::engine(this);
//   //
//   //      //}
//   //
//   //
//   //      //if (!::aura::application::process_init())
//   //        // return false;
//   //
//   //      if (!::aura::system::process_init())
//   //         return false;
//   //
//   //
//   //      //create_factory < ::OS::window_buffer >   (__type(::window_graphics));
//   //
//   //
//   //
//   //      //m_spos.create(this);
//   //
//   //
//   //
//   //
//   //
//   //      return true;
//   //
//   //   }
//
//
//   //   bool system::initialize_native_window1()
//   //   {
//   //
//   //#if !defined(LINUX) && !defined(WINDOWS_DESKTOP) && !defined(MACOS)
//   //
//   //      get_context_session()->m_puiMain = __new(::user::interaction);
//   //
//   //      get_context_session()->m_puiMain->initialize(get_context_session());
//   //
//   //#endif
//   //
//   //      return true;
//   //
//   //   }
//
//   void system::on_apply(::action * paction)
//   {
//
//      //::update updateSetting(pupdate);
//
//      //fork([this, updateSetting]
//      //     ()
//      //     {
//
//      //        ::update update(updateSetting);
//
//      //        __pointer(::user::interaction) pinteraction;
//
//      //        __pointer(::aura::session) psession = m_psession;
//
//      //        if(psession == nullptr)
//      //        {
//
//      //           return;
//
//      //        }
//
//      //        int iFrame = 0;
//
//      //        while(psession->get_frame(pinteraction))
//      //        {
//
//      //           iFrame++;
//
//      //           pinteraction->apply(paction);
//
//      //        }
//
//      //     });
//
//   }
//
//
//
//
//   /* colorramp.c -- color temperature calculation source
//   This file is part of Redshift.
//   Redshift is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//   Redshift is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//   You should have received a copy of the GNU General Public License
//   along with Redshift.  If not, see <http://www.gnu.org/licenses/>.
//   Copyright (c) 2013-2014  Jon Lund Steffensen <jonlst@gmail.com>
//   Copyright (c) 2013  Ingo Thies <ithies@astro.uni-bonn.de>
//   */
//
//   /* Whitepoint values for temperatures at 100K intervals.
//   These will be interpolated for the actual temperature.
//   This table was provided by Ingo Thies, 2013. See
//   the file README-colorramp for more information. */
//   static const float g_fa_blackbody_color[] =
//   {
//      1.00000000f,  0.18172716f,  0.00000000f, /* 1000K */
//      1.00000000f,  0.25503671f,  0.00000000f, /* 1100K */
//      1.00000000f,  0.30942099f,  0.00000000f, /* 1200K */
//      1.00000000f,  0.35357379f,  0.00000000f, /* ...   */
//      1.00000000f,  0.39091524f,  0.00000000f,
//      1.00000000f,  0.42322816f,  0.00000000f,
//      1.00000000f,  0.45159884f,  0.00000000f,
//      1.00000000f,  0.47675916f,  0.00000000f,
//      1.00000000f,  0.49923747f,  0.00000000f,
//      1.00000000f,  0.51943421f,  0.00000000f,
//      1.00000000f,  0.54360078f,  0.08679949f,
//      1.00000000f,  0.56618736f,  0.14065513f,
//      1.00000000f,  0.58734976f,  0.18362641f,
//      1.00000000f,  0.60724493f,  0.22137978f,
//      1.00000000f,  0.62600248f,  0.25591950f,
//      1.00000000f,  0.64373109f,  0.28819679f,
//      1.00000000f,  0.66052319f,  0.31873863f,
//      1.00000000f,  0.67645822f,  0.34786758f,
//      1.00000000f,  0.69160518f,  0.37579588f,
//      1.00000000f,  0.70602449f,  0.40267128f,
//      1.00000000f,  0.71976951f,  0.42860152f,
//      1.00000000f,  0.73288760f,  0.45366838f,
//      1.00000000f,  0.74542112f,  0.47793608f,
//      1.00000000f,  0.75740814f,  0.50145662f,
//      1.00000000f,  0.76888303f,  0.52427322f,
//      1.00000000f,  0.77987699f,  0.54642268f,
//      1.00000000f,  0.79041843f,  0.56793692f,
//      1.00000000f,  0.80053332f,  0.58884417f,
//      1.00000000f,  0.81024551f,  0.60916971f,
//      1.00000000f,  0.81957693f,  0.62893653f,
//      1.00000000f,  0.82854786f,  0.64816570f,
//      1.00000000f,  0.83717703f,  0.66687674f,
//      1.00000000f,  0.84548188f,  0.68508786f,
//      1.00000000f,  0.85347859f,  0.70281616f,
//      1.00000000f,  0.86118227f,  0.72007777f,
//      1.00000000f,  0.86860704f,  0.73688797f,
//      1.00000000f,  0.87576611f,  0.75326132f,
//      1.00000000f,  0.88267187f,  0.76921169f,
//      1.00000000f,  0.88933596f,  0.78475236f,
//      1.00000000f,  0.89576933f,  0.79989606f,
//      1.00000000f,  0.90198230f,  0.81465502f,
//      1.00000000f,  0.90963069f,  0.82838210f,
//      1.00000000f,  0.91710889f,  0.84190889f,
//      1.00000000f,  0.92441842f,  0.85523742f,
//      1.00000000f,  0.93156127f,  0.86836903f,
//      1.00000000f,  0.93853986f,  0.88130458f,
//      1.00000000f,  0.94535695f,  0.89404470f,
//      1.00000000f,  0.95201559f,  0.90658983f,
//      1.00000000f,  0.95851906f,  0.91894041f,
//      1.00000000f,  0.96487079f,  0.93109690f,
//      1.00000000f,  0.97107439f,  0.94305985f,
//      1.00000000f,  0.97713351f,  0.95482993f,
//      1.00000000f,  0.98305189f,  0.96640795f,
//      1.00000000f,  0.98883326f,  0.97779486f,
//      1.00000000f,  0.99448139f,  0.98899179f,
//      1.00000000f,  1.00000000f,  1.00000000f, /* 6500K */
//      0.98947904f,  0.99348723f,  1.00000000f,
//      0.97940448f,  0.98722715f,  1.00000000f,
//      0.96975025f,  0.98120637f,  1.00000000f,
//      0.96049223f,  0.97541240f,  1.00000000f,
//      0.95160805f,  0.96983355f,  1.00000000f,
//      0.94303638f,  0.96443333f,  1.00000000f,
//      0.93480451f,  0.95923080f,  1.00000000f,
//      0.92689056f,  0.95421394f,  1.00000000f,
//      0.91927697f,  0.94937330f,  1.00000000f,
//      0.91194747f,  0.94470005f,  1.00000000f,
//      0.90488690f,  0.94018594f,  1.00000000f,
//      0.89808115f,  0.93582323f,  1.00000000f,
//      0.89151710f,  0.93160469f,  1.00000000f,
//      0.88518247f,  0.92752354f,  1.00000000f,
//      0.87906581f,  0.92357340f,  1.00000000f,
//      0.87315640f,  0.91974827f,  1.00000000f,
//      0.86744421f,  0.91604254f,  1.00000000f,
//      0.86191983f,  0.91245088f,  1.00000000f,
//      0.85657444f,  0.90896831f,  1.00000000f,
//      0.85139976f,  0.90559011f,  1.00000000f,
//      0.84638799f,  0.90231183f,  1.00000000f,
//      0.84153180f,  0.89912926f,  1.00000000f,
//      0.83682430f,  0.89603843f,  1.00000000f,
//      0.83225897f,  0.89303558f,  1.00000000f,
//      0.82782969f,  0.89011714f,  1.00000000f,
//      0.82353066f,  0.88727974f,  1.00000000f,
//      0.81935641f,  0.88452017f,  1.00000000f,
//      0.81530175f,  0.88183541f,  1.00000000f,
//      0.81136180f,  0.87922257f,  1.00000000f,
//      0.80753191f,  0.87667891f,  1.00000000f,
//      0.80380769f,  0.87420182f,  1.00000000f,
//      0.80018497f,  0.87178882f,  1.00000000f,
//      0.79665980f,  0.86943756f,  1.00000000f,
//      0.79322843f,  0.86714579f,  1.00000000f,
//      0.78988728f,  0.86491137f,  1.00000000f, /* 10000K */
//      0.78663296f,  0.86273225f,  1.00000000f,
//      0.78346225f,  0.86060650f,  1.00000000f,
//      0.78037207f,  0.85853224f,  1.00000000f,
//      0.77735950f,  0.85650771f,  1.00000000f,
//      0.77442176f,  0.85453121f,  1.00000000f,
//      0.77155617f,  0.85260112f,  1.00000000f,
//      0.76876022f,  0.85071588f,  1.00000000f,
//      0.76603147f,  0.84887402f,  1.00000000f,
//      0.76336762f,  0.84707411f,  1.00000000f,
//      0.76076645f,  0.84531479f,  1.00000000f,
//      0.75822586f,  0.84359476f,  1.00000000f,
//      0.75574383f,  0.84191277f,  1.00000000f,
//      0.75331843f,  0.84026762f,  1.00000000f,
//      0.75094780f,  0.83865816f,  1.00000000f,
//      0.74863017f,  0.83708329f,  1.00000000f,
//      0.74636386f,  0.83554194f,  1.00000000f,
//      0.74414722f,  0.83403311f,  1.00000000f,
//      0.74197871f,  0.83255582f,  1.00000000f,
//      0.73985682f,  0.83110912f,  1.00000000f,
//      0.73778012f,  0.82969211f,  1.00000000f,
//      0.73574723f,  0.82830393f,  1.00000000f,
//      0.73375683f,  0.82694373f,  1.00000000f,
//      0.73180765f,  0.82561071f,  1.00000000f,
//      0.72989845f,  0.82430410f,  1.00000000f,
//      0.72802807f,  0.82302316f,  1.00000000f,
//      0.72619537f,  0.82176715f,  1.00000000f,
//      0.72439927f,  0.82053539f,  1.00000000f,
//      0.72263872f,  0.81932722f,  1.00000000f,
//      0.72091270f,  0.81814197f,  1.00000000f,
//      0.71922025f,  0.81697905f,  1.00000000f,
//      0.71756043f,  0.81583783f,  1.00000000f,
//      0.71593234f,  0.81471775f,  1.00000000f,
//      0.71433510f,  0.81361825f,  1.00000000f,
//      0.71276788f,  0.81253878f,  1.00000000f,
//      0.71122987f,  0.81147883f,  1.00000000f,
//      0.70972029f,  0.81043789f,  1.00000000f,
//      0.70823838f,  0.80941546f,  1.00000000f,
//      0.70678342f,  0.80841109f,  1.00000000f,
//      0.70535469f,  0.80742432f,  1.00000000f,
//      0.70395153f,  0.80645469f,  1.00000000f,
//      0.70257327f,  0.80550180f,  1.00000000f,
//      0.70121928f,  0.80456522f,  1.00000000f,
//      0.69988894f,  0.80364455f,  1.00000000f,
//      0.69858167f,  0.80273941f,  1.00000000f,
//      0.69729688f,  0.80184943f,  1.00000000f,
//      0.69603402f,  0.80097423f,  1.00000000f,
//      0.69479255f,  0.80011347f,  1.00000000f,
//      0.69357196f,  0.79926681f,  1.00000000f,
//      0.69237173f,  0.79843391f,  1.00000000f,
//      0.69119138f,  0.79761446f,  1.00000000f, /* 15000K */
//      0.69003044f,  0.79680814f,  1.00000000f,
//      0.68888844f,  0.79601466f,  1.00000000f,
//      0.68776494f,  0.79523371f,  1.00000000f,
//      0.68665951f,  0.79446502f,  1.00000000f,
//      0.68557173f,  0.79370830f,  1.00000000f,
//      0.68450119f,  0.79296330f,  1.00000000f,
//      0.68344751f,  0.79222975f,  1.00000000f,
//      0.68241029f,  0.79150740f,  1.00000000f,
//      0.68138918f,  0.79079600f,  1.00000000f,
//      0.68038380f,  0.79009531f,  1.00000000f,
//      0.67939381f,  0.78940511f,  1.00000000f,
//      0.67841888f,  0.78872517f,  1.00000000f,
//      0.67745866f,  0.78805526f,  1.00000000f,
//      0.67651284f,  0.78739518f,  1.00000000f,
//      0.67558112f,  0.78674472f,  1.00000000f,
//      0.67466317f,  0.78610368f,  1.00000000f,
//      0.67375872f,  0.78547186f,  1.00000000f,
//      0.67286748f,  0.78484907f,  1.00000000f,
//      0.67198916f,  0.78423512f,  1.00000000f,
//      0.67112350f,  0.78362984f,  1.00000000f,
//      0.67027024f,  0.78303305f,  1.00000000f,
//      0.66942911f,  0.78244457f,  1.00000000f,
//      0.66859988f,  0.78186425f,  1.00000000f,
//      0.66778228f,  0.78129191f,  1.00000000f,
//      0.66697610f,  0.78072740f,  1.00000000f,
//      0.66618110f,  0.78017057f,  1.00000000f,
//      0.66539706f,  0.77962127f,  1.00000000f,
//      0.66462376f,  0.77907934f,  1.00000000f,
//      0.66386098f,  0.77854465f,  1.00000000f,
//      0.66310852f,  0.77801705f,  1.00000000f,
//      0.66236618f,  0.77749642f,  1.00000000f,
//      0.66163375f,  0.77698261f,  1.00000000f,
//      0.66091106f,  0.77647551f,  1.00000000f,
//      0.66019791f,  0.77597498f,  1.00000000f,
//      0.65949412f,  0.77548090f,  1.00000000f,
//      0.65879952f,  0.77499315f,  1.00000000f,
//      0.65811392f,  0.77451161f,  1.00000000f,
//      0.65743716f,  0.77403618f,  1.00000000f,
//      0.65676908f,  0.77356673f,  1.00000000f,
//      0.65610952f,  0.77310316f,  1.00000000f,
//      0.65545831f,  0.77264537f,  1.00000000f,
//      0.65481530f,  0.77219324f,  1.00000000f,
//      0.65418036f,  0.77174669f,  1.00000000f,
//      0.65355332f,  0.77130560f,  1.00000000f,
//      0.65293404f,  0.77086988f,  1.00000000f,
//      0.65232240f,  0.77043944f,  1.00000000f,
//      0.65171824f,  0.77001419f,  1.00000000f,
//      0.65112144f,  0.76959404f,  1.00000000f,
//      0.65053187f,  0.76917889f,  1.00000000f,
//      0.64994941f,  0.76876866f,  1.00000000f, /* 20000K */
//      0.64937392f,  0.76836326f,  1.00000000f,
//      0.64880528f,  0.76796263f,  1.00000000f,
//      0.64824339f,  0.76756666f,  1.00000000f,
//      0.64768812f,  0.76717529f,  1.00000000f,
//      0.64713935f,  0.76678844f,  1.00000000f,
//      0.64659699f,  0.76640603f,  1.00000000f,
//      0.64606092f,  0.76602798f,  1.00000000f,
//      0.64553103f,  0.76565424f,  1.00000000f,
//      0.64500722f,  0.76528472f,  1.00000000f,
//      0.64448939f,  0.76491935f,  1.00000000f,
//      0.64397745f,  0.76455808f,  1.00000000f,
//      0.64347129f,  0.76420082f,  1.00000000f,
//      0.64297081f,  0.76384753f,  1.00000000f,
//      0.64247594f,  0.76349813f,  1.00000000f,
//      0.64198657f,  0.76315256f,  1.00000000f,
//      0.64150261f,  0.76281076f,  1.00000000f,
//      0.64102399f,  0.76247267f,  1.00000000f,
//      0.64055061f,  0.76213824f,  1.00000000f,
//      0.64008239f,  0.76180740f,  1.00000000f,
//      0.63961926f,  0.76148010f,  1.00000000f,
//      0.63916112f,  0.76115628f,  1.00000000f,
//      0.63870790f,  0.76083590f,  1.00000000f,
//      0.63825953f,  0.76051890f,  1.00000000f,
//      0.63781592f,  0.76020522f,  1.00000000f,
//      0.63737701f,  0.75989482f,  1.00000000f,
//      0.63694273f,  0.75958764f,  1.00000000f,
//      0.63651299f,  0.75928365f,  1.00000000f,
//      0.63608774f,  0.75898278f,  1.00000000f,
//      0.63566691f,  0.75868499f,  1.00000000f,
//      0.63525042f,  0.75839025f,  1.00000000f,
//      0.63483822f,  0.75809849f,  1.00000000f,
//      0.63443023f,  0.75780969f,  1.00000000f,
//      0.63402641f,  0.75752379f,  1.00000000f,
//      0.63362667f,  0.75724075f,  1.00000000f,
//      0.63323097f,  0.75696053f,  1.00000000f,
//      0.63283925f,  0.75668310f,  1.00000000f,
//      0.63245144f,  0.75640840f,  1.00000000f,
//      0.63206749f,  0.75613641f,  1.00000000f,
//      0.63168735f,  0.75586707f,  1.00000000f,
//      0.63131096f,  0.75560036f,  1.00000000f,
//      0.63093826f,  0.75533624f,  1.00000000f,
//      0.63056920f,  0.75507467f,  1.00000000f,
//      0.63020374f,  0.75481562f,  1.00000000f,
//      0.62984181f,  0.75455904f,  1.00000000f,
//      0.62948337f,  0.75430491f,  1.00000000f,
//      0.62912838f,  0.75405319f,  1.00000000f,
//      0.62877678f,  0.75380385f,  1.00000000f,
//      0.62842852f,  0.75355685f,  1.00000000f,
//      0.62808356f,  0.75331217f,  1.00000000f,
//      0.62774186f,  0.75306977f,  1.00000000f, /* 25000K */
//      0.62740336f,  0.75282962f,  1.00000000f  /* 25100K */
//   };
//
//   static void
//      interpolate_color(float a, const float* c1, const float* c2, float* r, float* g, float* b)
//   {
//      *r = (1.0f - a) * c1[0] + a * c2[0];
//      *g = (1.0f - a) * c1[1] + a * c2[1];
//      *b = (1.0f - a) * c1[2] + a * c2[2];
//   }
//
//
//
//
//   CLASS_DECL_BASE void black_body(float* r, float* g, float* b, DWORD dwTemp)
//   {
//
//      int temp_index = ((dwTemp - 1000) / 100) * 3;
//
//      if (temp_index < 0)
//      {
//
//         temp_index = 0;
//
//      }
//      else if (temp_index > (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3)
//      {
//
//         temp_index = (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3;
//
//      }
//
//      float alpha = (dwTemp % 100) / 100.0f;
//
//      interpolate_color(alpha, &g_fa_blackbody_color[temp_index], &g_fa_blackbody_color[temp_index + 3], r, g, b);
//
//   }
//
//
//
//
//   //namespace command
//   //{
//   //
//   //
//   //   command::command()
//   //   {
//   //
//   //      defer_create_mutex();
//   //
//   //   }
//
//
//      //command::~command()
//      //{
//
//      //}
//
//   ::type system::get_pane_tab_view_type_info()
//   {
//
//      return m_typePaneTabView;
//
//   }


   __namespace_system_factory(system);


} // namespace base





void __node_base_factory_exchange()
{


}


