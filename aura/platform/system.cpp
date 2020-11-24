#include "framework.h"
#include "aqua/xml/_.h"
#include "apex/platform/app_core.h"
#include "acme/const/id.h"
#include "aura/node/_node.h"
#include "acme/platform/profiler.h"
#include "apex/platform/static_setup.h"
#include "apex/platform/str_context.h"
#include "acme/node/windows/registry.h"
#include "apex/platform/history.h"
#include "aura/gpu/gpu/_.h"


int GetMainScreenRect(LPRECT32 lprect);


#ifdef LINUX
const char * get_main_app_id();
#endif



#ifdef CUBE
extern "C"
::apex::library * experience_get_new_library();
#endif


#ifdef WINDOWS_DESKTOP
#include <highlevelmonitorconfigurationapi.h>
#endif


//void ___compile_test_sort_array_21304528734();

//void enum_display_monitors(::aura::system * psystem);

#ifdef WINDOWS_DESKTOP
CLASS_DECL_AURA ::user::interaction * create_system_message_window(::layered * pobjectContext);
#endif


#ifdef LINUX
#include <sys/time.h>
#endif

extern string_map < __pointer(::apex::library) > * g_pmapLibrary;


CLASS_DECL_AURA void __simple_tracea(::matter * pobjectContext, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


void os_post_quit();

//extern ::mutex * &System.m_mutexLibrary;



#ifdef UNIT_TEST
void unit_test_primitive_var_aura_block();
#endif


void dappy(const char * psz);


//#ifdef WINDOWS_DESKTOP
//string get_user_name()
//{
//   WCHAR wsz[1024];
//   ::u32 dwSize = sizeof(wsz) / sizeof(WCHAR);
//   ::GetUserNameW(wsz,&dwSize);
//   return string(wsz);
//}
//#include "aura/os/windows/_c.h"
//#endif
//
//
namespace aura
{





   //class ::id system::idEmpty;

   //system * system::g_p = nullptr;
   ::mutex * g_pmutexImage = nullptr;

   ::mutex * get_image_mutex()
   {

      return g_pmutexImage;

   }


   system::system()
   {

      m_paurasystem = this;

      m_bAvoidFirstResponder = false;

      create_factory < ::aura::session, ::apex::session >();
      create_factory < ::aura::application, ::apex::application >();

      m_bMessageThread = true;

      common_construct();

   }


   void system::common_construct()
   {


      m_bSimpleMessageLoop = false;

      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;

      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

   }


   ::estatus system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::aqua::system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      enable_trace_category(trace_category_windowing, true);

      enable_trace_category(trace_category_prodevian, false);

    #ifdef WINDOWS_DESKTOP

      {

         auto hdc = CreateCompatibleDC(NULL);

         m_dpi = (float) GetDeviceCaps(hdc, LOGPIXELSX);

         ::DeleteDC(hdc);

      }

   #else

      m_dpi = 96.0;

   #endif

      m_pDraw2dFactoryExchange = nullptr;

      g_pmutexImage = new ::mutex();

      m_bThreadToolsForIncreasedFps = false;

#ifndef WINDOWS

      exception::translator::attach();

#endif

      m_bProdevianMouse = false;

      m_bSystemSynchronizedCursor = true;
      m_bSystemSynchronizedScreen = true;

      string strId;
      strId = "ca2log";

      if (!initialize_log(strId))
      {

         //xxdebug_box("Could not initialize log", "Failed to initialize log", 0);

         __throw(::exception::exception("failed to initialize log"));

      }

      {

         bool bGlobalEnableStackTrace = true;

         ::file::path pathNoExceptionStackTrace = ::dir::config() / "system/no_exception_stack_trace.txt";

         if (file_exists(pathNoExceptionStackTrace))
         {

            bGlobalEnableStackTrace = false;

         }

         ::exception::exception::exception_enable_stack_trace(bGlobalEnableStackTrace);

      }
 
      __node_aura_factory_exchange();


      m_bGudoNetCache = true;

      //m_purldepartment = nullptr;

      m_millisAfterApplicationFirstRequest = 0;



      ::draw2d::static_initialize();

      estatus = __compose_new(m_pwindowmap);

      if (!estatus)
      {

         return estatus;

      }

  
      m_pDraw2dFactoryExchange = nullptr;

      create_factory < ::user::control_descriptor >();

      create_factory < ::draw2d::icon >();

    
#ifdef WINDOWS_DESKTOP

      m_uiWindowsTaskbarCreatedMessage = 0;

#endif

      thread::s_bAllocReady = true;


      return estatus;

   }


   void system::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {


   }


   string system::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   bool system::on_get_thread_name(string& strThreadName)
   {

      if (is_console_app())
      {

         return false;

      }

      return ::apex::system::on_get_thread_name(strThreadName);

   }



//   ::apex::library * system::get_library(const char * pszLibrary1, bool bOpenCa2)
//   {
//
//      sync_lock sl(&System.m_mutexLibrary);
//
//      string strLibrary(pszLibrary1);
//
//      strLibrary.ends_eat_ci(".dll");
//      strLibrary.ends_eat_ci(".so");
//      strLibrary.ends_eat_ci(".dylib");
//      strLibrary.begins_eat_ci("lib");
//
//      auto & plibrary = System.m_mapLibrary[strLibrary];
//
//      bool bLibraryOk = true;
//
//      if (plibrary.is_null())
//      {
//
//         __compose(plibrary, on_get_library(strLibrary));
//
//         if (plibrary.is_null())
//         {
//
//            __compose_new(plibrary);
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


   system::~system()
   {

      ::acme::del(g_pmutexImage);

      os_post_quit();

   }


   class ::user::window_map & system::window_map()
   {

      return *m_pwindowmap;

   }


   //void system::defer_check_exit()
   //{

   //   if (!m_bDoNotExitIfNoApplications)
   //   {

   //      auto applicationa = get_applicationa();

   //      for (i32 i = 0; i < applicationa.get_size();)
   //      {

   //         try
   //         {

   //            if (!applicationa[i] || applicationa[i]->is_session() || applicationa[i]->is_system())
   //            {

   //               applicationa.remove_at(i);

   //               continue;

   //            }
   //            else if (applicationa[i]->is_serviceable())
   //            {

   //               applicationa.remove_at(i);

   //               continue;

   //            }

   //         }
   //         catch (...)
   //         {

   //            applicationa.remove_at(i);

   //            continue;

   //         }

   //         i++;

   //      }

   //      if (applicationa.get_size() <= 0)
   //      {

   //         __destroy();

   //      }

   //      if (applicationa.get_size() == 1 && applicationa.contains(this))
   //      {

   //         __destroy();

   //      }

   //   }


   //}


   //base_factory & system::factory()
   //{

   //   return *m_pfactory;

   //}


   //::datetime::department & system::datetime()
   //{

   //   return *m_pdatetime;

   //}


   //::aura::str & system::str()
   //{

   //   return *m_puserstr;

   //}
















   ::estatus system::process_init()
   {

      auto estatus = ::apex::system::process_init();

      if (!estatus)
      {

         return estatus;

      }

      //auto estatus = system_prep();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = system_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}



      //if (!create_session())
      //{

      //   message_box("Failed to allocate Session!!");

      //   return false;

      //}

      //m_papplicationStartup = get_new_application(get_context_session(), m_strAppId);

      //if (!m_papplicationStartup)
      //{

      //   message_box("Failed to allocate Application!!");

      //   return false;

      //}

      //set_main_struct(*m_papplicationStartup);

      //string strAppId = m_papplicationStartup->m_strAppId;

      //auto pcommand = get_command();

      //auto pcreate = pcommand->m_pcreate;

      //TRACE("m_pcreate WARNING");
      //TRACE("m_pcreate WARNING");
      //TRACE("m_pcreate WARNING");
      //TRACE("m_pcreate WARNING");
      //TRACE("m_pcreate WARNING");
      //TRACE("m_pcreate WARNING");
      //TRACE("m_pcreate WARNING");
      //TRACE("m_pcreate COMMENT BEGIN");
      //auto pcreate = m_pcreate;

      //pcreate->m_strAppId = strAppId;
      //TRACE("m_pcreate COMMENT END");

      //create_factory < ::database::field >();


      //if (is_true("show_application_information"))
      //{

      //   printf("%s", "\n\nApplication Information\n");
      //   output_debug_string("\n\nApplication Information\n");

      //   int iPid;

      //   iPid = ::get_current_process_id();

      //   printf("%s", ("Process PID: " + __str(iPid) + "\n").c_str());
      //   output_debug_string("Process PID: " + __str(iPid) + "\n");

      //}

//#ifdef LINUX
//
//      {
//
//         string str;
//
//         str = ::dir::home() / ".profile";
//
//         if(!file_exists(str))
//         {
//
//            str = ::dir::home() / ".bashrc";
//
//         }
//
//         string_array straLines;
//
//         {
//
//            memory memory;
//
//            FILE * fp = popen(". " + str + " ; echo PATH=$PATH ;", "r");
//
//            memory.fread(fp);
//
//            pclose(fp);
//
//            string strContents = memory.as_utf8();
//
//            straLines.add_lines(strContents);
//
//         }
//
//         for(auto & strLine : straLines)
//         {
//
//            strLine.trim();
//
//            strsize i = strLine.find('=');
//
//            if(i > 0)
//            {
//
//               int iSize = strLine.get_length();
//
//               iSize *= 2;
//
//               iSize = max(iSize, 4096);
//
//               char * pszEnvLine = (char *) ::malloc(iSize);
//
//               ::zero(pszEnvLine, iSize);
//
//               strcpy(pszEnvLine, strLine);
//
//               ::putenv(pszEnvLine);
//
//            }
//
//         }
//
//      }
//
//#endif

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

      //estatus = __compose_new(m_pxml);

      //if (!estatus)
      //{

      //   throw exception::exception(estatus);

      //}

      //m_pxml->initialize(this);

      //if (!m_pxml->init1())
      //{
      //   __throw(::exception::exception("failed to construct system m_pxml->init1()"));

      //}

      //if (!m_pxml->init())
      //{

      //   __throw(::exception::exception("failed to construct system m_pxml->initialize()"));

      //}

//      create_factory < ::create >();
//      //create_factory < application_bias >();
//      create_factory < command_line >();
//      create_factory < http::context >();
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

      //if(!__compose(m_pfilesystem))
      //{

      //   ERR("failed to initialize file-system");

      //   return false;

      //}

      //if(!__compose(m_pdirsystem))
      //{

      //   ERR("failed to initialize dir-system");

      //   return false;

      //}

      //INFO("aura::session::process_init .3");

      //estatus = m_pfilesystem->init_system();

      //if (!estatus)
      //{

      //   m_estatus = estatus;

      //   return estatus;

      //}

      //estatus = m_pdirsystem->init_system();

      //if (!estatus)
      //{

      //   m_estatus = estatus;

      //   return estatus;

      //}

      //estatus = ::context::initialize_context();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (!m_ptrace->process_init())
      //{

      //   WARN("failed to process_init ::aura::log trace");

      //}

      ////output_debug_string("CommonAppData (matter) : " + Context.dir().commonappdata()  + "\n");
      ////output_debug_string("commonappdata (matter) : " + Context.dir().commonappdata() + "\n");
      ////output_debug_string("Common App Data (matter) : " + Context.dir().commonappdata() + "\n");
      ////output_debug_string("common app data (matter) : " + Context.dir().commonappdata() + "\n");

      //__compose_new(m_pcrypto);

      //if (!::is_set(m_pcrypto))
      //{

      //   return false;

      //}

      if(m_bDraw2d)
      {

         if (!init_draw2d())
         {

            return false;

         }

      }

      on_update_matter_locator();

//
//    estatus = initialize_sockets();
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

      ::acme::profiler::initialize();

#ifdef LINUX

      ::user::g_defer_init();

#endif // LINUX

      INFO("success");

      return true;

   }


   void system::get_time(struct timeval * point)
   {
#ifdef _WIN32
      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      GetSystemTimeAsFileTime(&ft);
      u64 tt;
      ::memcpy_dup(&tt, &ft, sizeof(tt));
      tt /= 10; // make it usecs
      point->tv_sec = (long)tt / 1000000;
      point->tv_usec = (long)tt % 1000000;
#else
      gettimeofday(point, nullptr);
#endif
   }


   ::estatus system::init_draw2d()
   {

      ::estatus estatus = ::success;

      try
      {

         if (!draw2d_factory_exchange())
         {

            message_box("Failed to initialize draw2d library.");

            estatus = error_failed;

         }

      }
      catch (...)
      {

         estatus = error_exception;

      }

      if (!estatus)
      {

         TRACE("draw2d_factory_exchange has failed.\n\nSome reasons:\n   - No draw2d library present;\n   - Failure to open any suitable draw2d library.", e_message_box_ok);

         return estatus;

      }

      if (m_bImaging)
      {

         try
         {

            if (!imaging_factory_exchange())
            {

               WARN("Failed to initialize imaging library.");

#if !defined(MOBILE_PLATFORM)

               message_box("Failed to initialize imaging library.");

#endif
               // Non fatal? Missing images (if using images)?
                           //bOk = false;

            }

         }
         catch (...)
         {

         }

      }

      sync_lock sl(&System.m_mutexLibrary);

      estatus = __construct_new(m_pdraw2d);

      if (!estatus)
      {

         TRACE("Couldn't construct new draw2d.");

         return false;

      }

      estatus = m_pdraw2d->init1();

      if(!estatus)
      {

         TRACE("Couldn't initialize draw2d (init1).");

         return estatus;

      }

      if (::succeeded(estatus))
      {

         create_factory < ::draw2d::thread_tool_item >(::e_thread_tool_draw2d);

      }

      return estatus;

   }


   string system::draw2d_get_default_library_name()
   {

      string str;

      if (file_exists(::dir::system() / "config\\system\\draw2d.txt"))
      {

         str = file_as_string(::dir::system() / "config\\system\\draw2d.txt");

   }
      else
      {

         ::file::path strPath;

         strPath = ::dir::appdata() / "draw2d.txt";

         str = file_as_string(strPath);

      }

      if (str.has_char())
         return "draw2d_" + str;
      else
      #ifdef WINDOWS_DESKTOP
         return "draw2d_gdiplus";
#elif __APPLE__
      return "draw2d_quartz2d";
#elif defined(_UWP)
         return "draw2d_direct2d";
#else
         return "draw2d_cairo";
      #endif
   }


   ::estatus system::draw2d_factory_exchange()
   {

      string strLibrary;

      if (has_property("draw2d"))
      {

         strLibrary = value("draw2d");

         //strDraw2d.trim();

         //if (strDraw2d.has_char())
         //{

         //   ::str::begins_eat_ci(strDraw2d, "draw2d_");

         //   ::str::begins_eat_ci(strDraw2d, "draw2d");

         //   strLibrary = "draw2d_" + strDraw2d;

         //}

      }

      ::estatus estatus;

      if (strLibrary.has_char())
      {

         estatus = do_factory_exchange("draw2d", strLibrary);

         if (estatus)
         {

            return ::success;

         }

      }

      strLibrary = draw2d_get_default_library_name();

      if (strLibrary.is_empty())
      {

#ifdef WINDOWS

         strLibrary = "draw2d_gdiplus";

#else

         strLibrary = "draw2d_cairo";

#endif

      }

      estatus = do_factory_exchange("draw2d", strLibrary);

      if (estatus)
      {

         return ::success;

      }


#ifdef WINDOWS_DESKTOP


      if (strLibrary != "draw2d_gdiplus")
      {

         estatus = do_factory_exchange("draw2d", "gdiplus");

         if (estatus)
         {

            return ::success;

         }

      }


      if (strLibrary != "draw2d_direct2d")
      {

         estatus = do_factory_exchange("draw2d", "direct2d");

         if (estatus)
         {

            return ::success;

         }

      }


#endif

      if (strLibrary != "draw2d_cairo")
      {


         estatus = do_factory_exchange("draw2d", "cairo");

         if (estatus)
         {

            return ::success;

         }

      }

      //output_debug_string("No draw2d pluging available!!.");
      return error_failed;

   //finalize:

   //   PFN_factory_exchange pfn_factory_exchange = plibrary->get < PFN_factory_exchange >("draw2d_factory_exchange");

   //   if (pfn_factory_exchange == nullptr)
   //   {

   //      return false;

   //   }

   //   pfn_factory_exchange();

   //   return true;

//#endif

   }


   bool system::imaging_factory_exchange()
   {


      string strLibrary;

      if (has_property("imaging"))
      {

         string strImaging = value("imaging");

         strImaging.trim();

         if (strImaging.has_char())
         {

            ::str::ends_eat_ci(strImaging, "_imaging");

            ::str::ends_eat_ci(strImaging, "imaging");

            ::str::begins_eat_ci(strImaging, "imaging_");

            ::str::begins_eat_ci(strImaging, "imaging");

         }

      }

      ::estatus estatus = ::error_failed;

      if (strLibrary.has_char())
      {

         estatus = do_factory_exchange("imaging", strLibrary);

         if (estatus)
         {

            return true;

         }

      }

      strLibrary = imaging_get_default_library_name();

      if (strLibrary.is_empty())
      {

#ifdef WINDOWS

         strLibrary = "imaging_wic";

#elif defined(__APPLE__)

         strLibrary = "imaging_coreimage";

#else

         strLibrary = "imaging_freeimage";

#endif

      }

      estatus = do_factory_exchange("imaging", strLibrary);

      if (estatus)
      {

         return true;

      }

#ifdef WINDOWS_DESKTOP

      if (strLibrary != "imaging_wic")
      {

         estatus = do_factory_exchange("imaging", "wic");

         if (estatus)
         {

            return true;

         }

      }

#endif

      if (strLibrary != "imaging_freeimage")
      {

         estatus = do_factory_exchange("imaging", "freeimage");

         if (estatus)
         {

            return true;

         }

      }

      output_debug_string("No imaging pluging available!!.");

      return false;

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

   }


   string system::imaging_get_default_library_name()
   {

#ifdef WINDOWS

      return "imaging_wic";

#elif defined(__APPLE__)

      return "imaging_coreimage";

#else

      return "imaging_freeimage";

#endif

   }


   ::estatus system::init_thread()
   {

      
      return ::aqua::system::init_thread();


      //if (m_psystemParent)
      //{

      //   m_psystemParent->add_reference(this);

      //}

      //auto estatus = process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = init_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = initial_check_directrix();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return true;

   }


   ::estatus system::init()
   {

      m_millisHeartBeat.Now();

      auto psession = Session;

      if (has_property("save_processing"))
      {

         psession->savings().save(::e_resource_processing);

      }

      if (has_property("save_blur_back"))
      {

         psession->savings().save(::e_resource_blur_background);

      }

      if (has_property("save_transparent_back"))
      {

         psession->savings().save(::e_resource_translucent_background);

      }

      if (::is_set(m_pdraw2d))
      {

         if (!m_pdraw2d->init())
         {

            return false;

         }

      }

      return true;

   }


   ::estatus system::init1()
   {
//
//#ifdef DEBUG
//
//      ___compile_test_sort_array_21304528734();
//
//#endif

      auto estatus = __compose_new(m_puserstr);

      if (!m_puserstr || !estatus)
      {

         return estatus;

      }

      estatus = __compose_new(m_pimaging);

      if (!estatus)
      {

         if (m_bUser && m_bDraw2d && m_bImaging)
         {

            return estatus;

         }

      }

      auto psession = Session;

      if (psession->m_puserstrcontext)
      {

         psession->m_puserstrcontext->defer_ok(m_puserstr);

      }

      //__throw(todo("filehandler"));

      //estatus = __compose_new(m_pfilehandler);

      //if (!estatus)
      //{

      //   return estatus;

      //}

#if !defined(CUBE) && !defined(ANDROID)

#if !defined(_DEBUG) || defined(WINDOWS)

      try
      {

#endif

         find_applications_from_cache();

#if !defined(_DEBUG) || defined(WINDOWS)

      }
      catch (...)
      {

      }

#endif

#endif

//      enum_display_monitors();

      return true;

   }


   ::estatus system::post_create_requests()
   {

      //while(auto pcreate = get_command()->get_create())
      while (auto pcreate = get_create())
      {

         do_request(pcreate);

      }

      return true;

   }


   ::estatus system::inline_init()
   {

      ::estatus estatus = ::aqua::system::inline_init();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::estatus system::inline_term()
   {

      ::estatus estatus = ::aqua::system::inline_term();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void system::term()
   {

      ::aqua::system::term();

      __release(m_phistory);

   }


   ::estatus system::system_prep()
   {

      auto estatus = ::aqua::system::system_prep();

      if(!estatus)
      {

         return estatus;

      }

      os_init_windowing();

      return ::success;

   }

   void system::term1()
   {

   }


   void system::term2()
   {

      ::aqua::system::term2();

      for (int i = 0; i < m_serviceptra.get_size(); i++)
      {

         try
         {

            m_serviceptra[i]->Stop(0);

         }
         catch (...)
         {

         }

      }

      for (int i = 0; i < m_serviceptra.get_size(); i++)
      {

         try
         {

            m_serviceptra[i]->Stop((5000) * 2);

         }
         catch (...)
         {

         }

      }

      m_serviceptra.remove_all();

      try
      {

         if (m_pdraw2d)
         {

            m_pdraw2d->term();

         }

      }
      catch (...)
      {

      }

      try
      {

         m_mapImage.remove_all();

      }
      catch (...)
      {

      }


      try
      {

         sync_lock sl(&System.m_mutexLibrary);

         if (System.m_mapLibrary["draw2d"].is_set() && System.m_mapLibrary["draw2d"]->is_opened())
         {

            if (m_pDraw2dFactoryExchange != nullptr)
            {

               delete m_pDraw2dFactoryExchange;

               m_pDraw2dFactoryExchange = nullptr;

            }

         }

      }
      catch (...)
      {

      }


      ::aqua::system::term2();

   }


   ::estatus system::thread_loop()
   {

//#ifdef LINUX

  //    run_gtk_main(this);

    //  return m_estatus;

//#else

      return thread::thread_loop();

//#endif // LINUX

   }

   void system::term_thread()
   {

      try
      {

         term_system();

      }
      catch(...)
      {

      }


      try
      {

         ::thread::term_thread();

      }
      catch(...)
      {

      }
   }


//   void system::term_system()
//   {
//
//      try
//      {
//
//         term2();
//
//      }
//      catch (...)
//      {
//
//      }
//
//      try
//      {
//
//         term1();
//
//      }
//      catch (...)
//      {
//
//      }
//
//            try
//      {
//
//         term();
//
//      }
//      catch (...)
//      {
//
//      }
//
//      try
//      {
//
//         process_term();
//
//      }
//      catch (...)
//      {
//
//      }
//
//
//      try
//      {
//
//         TermSystem();
//
//      }
//      catch (...)
//      {
//
//      }
//
//
//   }
//
//


   void system::TermSystem()
   {

      ::aqua::system::TermSystem();

#ifdef LINUX

      // dirty
      // (forcing premature gtk event loop (main loop) quitting)
      // the "most elegant" is to let just ~system (::aura::system destructor)...
      // ... do this call, but this requires all references to ::aura::system ...
      // ... to be released. This is a bit of an ideal situation that may not ...
      // ... always happen as the wish the program finishes when it is closed ...
      //os_post_quit();

#elif defined(__APPLE__)

      os_post_quit();

#endif

   }


   void system::process_term()
   {

      //::aura::application::process_term();



      try
      {

         m_mapAppLibrary.remove_all();

      }
      catch (...)
      {

      }

   }


   ::u32 system::os_post_to_all_threads(const ::id & id,WPARAM wparam,lparam lparam)
   {

      post_to_all_threads(id, wparam, lparam);

      return 0;

   }



   //bool system::is_system() const
   //{

   //   return true;

   //}


   i32 system::_001OnDebugReport(i32 i1,const char * psz1,i32 i2,const char * psz2,const char * psz3,va_list args)
   {

      return _debug_logging_report(i1,psz1,i2,psz2,psz3,args);

   }


   i32 system::_debug_logging_report(i32 iReportType, const char * pszFileName, i32 iLineNumber, const char * pszModuleName, const char * pszFormat,va_list list)
   {

      if(!m_ptrace || !m_ptrace->m_bExtendedLog)
      {

         return ::apex::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);

      }

      string str;

      if(pszFileName != nullptr || pszModuleName != nullptr)
      {

         string_array stra;

         if (pszFileName != nullptr)
         {

            stra.add(pszFileName);

         }

         if (pszModuleName != nullptr)
         {

            stra.add(pszFileName);

         }

         str += stra.implode(", ");

         str += ": ";

      }

      string str2;

      if(pszFormat != nullptr)
      {

//         if(list != nullptr)
         {

            str2.Format(pszFormat,list);

         }
         //     else
         {

            //          str2 = pszFormat;

         }

      }

      str = str + str2;

      string strPrint(str);

      strPrint.replace("%","%%");

      if(m_ptrace)
      {

         m_ptrace->print(strPrint);

      }

      if(iReportType == _CRT_ASSERT)
      {

         return 1;

      }
      else
      {

         return 0;

      }

   }




   bool system::assert_failed_line(const char * pszFileName,i32 iLine)

   {
      UNREFERENCED_PARAMETER(pszFileName);

      UNREFERENCED_PARAMETER(iLine);
      return false;
   }


   bool system::on_assert_failed_line(const char * pszFileName,i32 iLine)

   {
      UNREFERENCED_PARAMETER(pszFileName);

      UNREFERENCED_PARAMETER(iLine);
      return true;
   }


   void system::__set_thread_on()
   {

      ::thread::__set_thread_on();

   }


//   ::mutex * system::get_openweather_city_mutex()
//   {
//
//      sync_lock sl(mutex());
//
//      if (m_spmutexOpenweatherCity.is_null())
//      {
//
//#ifdef _UWP
//
//         m_spmutexOpenweatherCity = __new(::mutex());
//
//#else
//
//         m_spmutexOpenweatherCity = __new(::mutex(e_create_new, false, "Global\\ca2_weather_city"));
//
//#endif
//
//      }
//
//      return m_spmutexOpenweatherCity;
//
//   }


   //void system::on_allocation_error(const ::string & str, ::object * pobject)
   //{

   //   string strMessage("Allocation Error!! : ");

   //   strMessage += "Type: " + str;

   //   //if (::is_null(pobject))
   //   //{

   //   //   strMessage += " : (Parent: (nullptr))";

   //   //}
   //   //else
   //   //{

   //   //   strMessage += " : (Parent: ";

   //   //   try
   //   //   {
   //   //      strMessage += pobject->type_name();

   //   //   }
   //   //   catch (...)
   //   //   {

   //   //   }

   //   //   strMessage += "(0x" + ::hex::lower_from((iptr)pobject) + ") )";

   //   //}

   //   TRACE(strMessage);

   //}


   //::xml::department & system::xml()
   //{

   //   return *m_pxml;

   //}


   //class ::str::base64 & system::base64()
   //{

   //   return *m_pbase64;

   //}


   //::aura::log & system::log()
   //{

   //   return *m_ptrace;

   //}



   //machine_event_central & system::machine_event_central()
   //{
   //   return *m_pmachineeventcentral;
   //}


   //__pointer(regex) system::create_regular_expression(const char* pszStyle, const string& str)
   //{

   //   return nullptr;

   //}


   //__pointer(regex_context) system::create_regular_expression_context(const char* pszStyle, int iCount)
   //{

   //   return nullptr;

   //}


   ::apex::session * system::session(index iEdge)
   {

      auto ppair = m_sessionmap.plookup(iEdge);

      if (!ppair)
      {

         return nullptr;

      }

      return ppair->element2();

   }


   //::aura::os & system::os()
   //{

   //   return *m_spos;

   //}


//__pointer_array(::aura::session) & system::basesessionptra()
//{

//   return m_basesessionptra;

//}


   //::process::department & system::process()
   //{

   //   return *m_pprocess;

   //}


   ::estatus system::initialize_log(const char * pszId)
   {

      if (m_ptrace)
      {

         return ::success_none;

      }

      auto estatus = __compose_new(m_ptrace);

      if (!estatus)
      {

         return estatus;

      }

      m_ptrace->set_extended_log();

      estatus = m_ptrace->initialize_apex_log(trace_level_warning, pszId);

      if(!estatus)
      {

         __release(m_ptrace);

         return estatus;

      }

      return estatus;

   }





   void system::appa_load_string_table()
   {

      //retry_single_lock rsl(mutex(),millis(100),millis(100));

//      for(i32 i = 0; i < appptra().get_size(); i++)
      //    {
      //     ::aura::application * papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }


   void system::appa_set_locale(const char * pszLocale, const ::action_context & context)
   {

      retry_single_lock rsl(mutex(),millis(100),millis(100));

//      for(i32 i = 0; i < appptra().get_size(); i++)
//     {
      //       ::aura::application * papp = appptra()(i);
      //       papp->set_locale(pszLocale,context);
      //    }

   }


   void system::appa_set_schema(const char * pszStyle, const ::action_context & context)
   {

      retry_single_lock rsl(mutex(),millis(100),millis(100));

//      for(i32 i = 0; i < appptra().get_size(); i++)
      //    {
      //       ::aura::application * papp = appptra()(i);
      //       papp->set_schema(pszStyle,context);
      //    }

   }



   bool system::assert_running_global(const char * pszAppName,const char * pszId)
   {
      if(string(pszId).has_char())
      {
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_id_mutex_name(pszAppName, pszId));
         ::mutex * pmutex = ::mutex::open_mutex(get_global_id_mutex_name(pszAppName,pszId));
         if(pmutex == nullptr)
         {

            string strApp = pszAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__APPLE__)

            ::apex::shell_launcher launcher(nullptr,nullptr, Context.dir().module()/strApp,strParameters,nullptr,display_normal);

            launcher.execute();

#else

            __throw(todo());

#endif

            return false;
         }
         else
         {
            delete pmutex;
         }
         return true;
      }
      else
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_mutex_name(pszAppName));
         ::mutex * pmutex = ::mutex::open_mutex(get_global_mutex_name(pszAppName));
         if(pmutex == nullptr)
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#if defined(_UWP)

            __throw(todo());

#else

            ::apex::shell_launcher launcher(nullptr,nullptr,Context.dir().module()/strApp,nullptr,nullptr, display_normal);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
   }

   bool system::assert_running_local(const char * pszAppName,const char * pszId)
   {
      string strAppName(pszAppName);
      string strId(pszId);
      if(strId.has_char())
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_id_mutex_name(pszAppName, strId));
         ::mutex * pmutex = ::mutex::open_mutex(get_local_id_mutex_name(pszAppName,strId));
         if(pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef _UWP

            __throw(todo());

#else

            ::apex::shell_launcher launcher(nullptr,nullptr, Context.dir().ca2module() / strApp,strParameters,nullptr, display_normal);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
      else
      {
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_mutex_name(pszAppName));
         ::mutex * pmutex = ::mutex::open_mutex(get_local_mutex_name(pszAppName));
         if(pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef _UWP

            __throw(todo());

#else

            ::apex::shell_launcher launcher(nullptr,nullptr, Context.dir().ca2module() / strApp,strParameters,nullptr, display_normal);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
   }










   ::count system::get_application_count()
   {

      ::count c = 0;

      //try
      //{

      //   for(index iBaseSession = 0; iBaseSession < m_basesessionptra.get_count(); iBaseSession++)
      //   {

      //      try
      //      {

      //         c += m_basesessionptra[iBaseSession]->appptra().get_count();

      //      }
      //      catch(...)
      //      {

      //      }

      //   }

      //}
      //catch(...)
      //{

      //}

      return c;

   }


   //string system::crypto_md5_text(const string & str)
   //{

   //   ::exception::throw_not_implemented();

   //   return "";

   //}


   void system::install_progress_add_up(int iAddUp)
   {

      UNREFERENCED_PARAMETER(iAddUp);

   }


   ::estatus system::create_session(index iEdge)
   {

      if (session(iEdge))
      {

         return ::success;

      }

      auto psession = on_create_session(iEdge);

      if (!psession)
      {

         return false;

      }

      session_add(iEdge, psession);

      return ::success;

   }


   __result(::apex::session) system::on_create_session(index iEdge)
   {

      return ::aqua::system::on_create_session(iEdge);

   }


   string system::get_system_configuration()
   {

#ifndef CA2_PLATFORM_VERSION

#error "CA2_PLATFORM_VERSION not defined"

#endif

#ifndef CA2_BASIS

#error "CA2_BASIS not defined"

#endif

#ifndef CA2_STAGE

#error "CA2_STAGE not defined"

#endif

#if CA2_PLATFORM_VERSION == CA2_BASIS

      return "basis";

//#pragma message "CA2_PLATFORM_VERSION is CA2_BASIS"

#elif CA2_PLATFORM_VERSION == CA2_STAGE

      return "stage";

//#pragma message "CA2_PLATFORM_VERSION is CA2_STAGE"

#else

#error "CA2_PLATFORM_VERSION has unsupported definition"

#endif

   }


   string system::get_system_platform()
   {

#ifdef X86

      return "x86";

#else

      return "x64";

#endif

   }




   void system::on_request(::create * pcreate)
   {

      ::apex::session * psession = session();

      if(psession == nullptr)
      {

         return;

      }

      INFO("%s", ("::aura::system::on_request session = " + string(psession->type_name()) + "("+__str((iptr) psession)+")\n\n").c_str());

      psession->do_request(pcreate);

   }


   ::file::path system::local_get_matter_path()
   {

      return ::dir::ca2roaming() / "appmatter";

   }


   ::file::path system::local_get_matter_path(string strMatter)
   {

#ifdef _UWP

      return "";

#else

      return local_get_matter_path() / strMatter;

#endif

   }


   ::file::path system::local_get_matter_cache_path()
   {

      return ::dir::ca2roaming() / "cache/appmatter";

   }


   ::file::path system::local_get_matter_cache_path(string strMatter)
   {

      return local_get_matter_cache_path() / strMatter;

   }


   bool system::find_applications_from_cache()
   {

      return false;

//      on_start_find_applications_from_cache();
//
//      if(has_property("install"))
//         return true;
//
//      file_pointer pfile = Context.file().get_file(Context.dir().appdata() / "applibcache.bin",::file::type_binary | ::file::mode_read);
//
//      if(!pfile)
//         return false;
//
//      ::binary_stream is(pfile);
//
//      is >> m_mapAppLibrary;
//
//      on_end_find_applications_from_cache(is);
//
//      return true;

   }


   bool system::find_applications_to_cache(bool bSave)
   {

      return true;

#if defined(CUBE) || defined(ANDROID)
      return true;
#endif

      /*      m_spfilehandler(new ::aura::filehandler::handler(this));*/

//      m_mapAppLibrary.remove_all();
//
//      string strLibraryId;
//
//      ::file::listing straTitle(this);
//
//      ::file::path pathCa2Module = Context.dir().ca2module();
//
//      ::output_debug_string("\n\n::aura::system::find_applications_to_cache\n\n");
//
//      ::output_debug_string("ca2 module folder : " + pathCa2Module);
//
//      ::output_debug_string("\n\n\n");
//
//      straTitle.ls_pattern(pathCa2Module, { "*.*" });
//
//      for(i32 i = 0; i < straTitle.get_count(); i++)
//      {
//
//         strLibraryId = straTitle[i];
//
//
//         if(::str::ends_eat_ci(strLibraryId,".dll")
//               || ::str::ends_eat_ci(strLibraryId,".so")
//               || ::str::ends_eat_ci(strLibraryId,".dylib"))
//         {
//
//            if(::str::begins_ci(strLibraryId,"libdraw2d_")
//                  || ::str::begins_ci(strLibraryId,"libbase"))
//            {
//               continue;
//            }
//
//            ::output_debug_string("library("+__str(i)+") : " + strLibraryId+"\n\n");
//
//            map_application_library(strLibraryId);
//
//         }
//
//      }
//
//      if(!bSave)
//         return true;
//
//      file_pointer file;
//
//      try
//      {
//
//         file = psession->file().get_file(Context.dir().appdata() / "applibcache.bin",::file::defer_create_directory | ::file::type_binary | ::file::mode_create | ::file::mode_write);
//
//      }
//      catch(::exception::exception &)
//      {
//
//         return false;
//
//      }
//
//      stream os(file);
//
//      os << m_mapAppLibrary;
//
//      on_end_find_applications_to_cache(os);
//
//      return true;

   }


   bool system::map_application_library(const char * pszLibrary)
   {

      ::apex::library library;

      library.initialize_apex_library(this, 0);

      if(!strcmp(pszLibrary,"app_core_rdpclient"))
      {
         TRACE("reach");
      }

      if(!ansi_compare_ci(pszLibrary, "app_core_hellomultiverse"))
      {
         TRACE("reach app_core_hellomultiverse");
      }

      if(!ansi_compare_ci(pszLibrary, "experience_lite"))
      {
         TRACE("reach experience_lite");
      }

      if(!ansi_compare_ci(pszLibrary, "app_core_hellomultiverse"))
      {
         TRACE("reach app_core_hellomultiverse");
      }

      if(!library.open(pszLibrary, true))
      {
         ::output_debug_string("::system::map_application_library Failed to open library :" + string(pszLibrary) + "\n\n");
         return false;
      }

      if(!library.open_ca2_library())
      {

         ::output_debug_string("::system::map_application_library open_ca2_library(2) Failed :" + string(pszLibrary) + "\n\n");

         return false;

      }

      on_map_application_library(library);

      string_array stra;

      string strRoot = library.get_root();

      library.get_app_list(stra);

      if(stra.get_count() <= 0)
         return false;

      strRoot += "/";

      if(stra.get_count() == 1)
      {

         m_mapAppLibrary.set_at(strRoot + stra[0],pszLibrary);

      }

      string strLibrary = ::file::path(pszLibrary).title();

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      if(strLibrary == "libbase")
      {

         strLibrary = "base";

      }
      else if(!::str::begins_eat(strLibrary,"libbase"))
      {

         ::str::begins_eat(strLibrary,"lib");

      }

#endif

      string strPrefix = strRoot;

      strPrefix.replace("-","_");

      strPrefix.replace("/","_");

      ::str::begins_eat_ci(strLibrary,strPrefix);

      strRoot += strLibrary;

      strRoot += "/";

      for(i32 i = 0; i < stra.get_count(); i++)
      {

         m_mapAppLibrary.set_at(strRoot + stra[i],pszLibrary);

      }

      return true;

   }


   ::estatus system::do_request(::create * pcreate)
   {

      if (pcreate->m_ecommand == ::command_check_exit)
      {

         return ::success;

      }

      return ::thread::do_request(pcreate);

   }




   //string system::url_encode(const string & str)
   //{

   //   //__throw(interface_only_exception());

   //   return url_encode(str);

   //}

#ifdef ANDROID

   bool system::android_set_user_wallpaper(string strUrl)
   {

      oslocal().m_strSetUserWallpaper = strUrl;

      return true;

   }

   bool system::android_get_user_wallpaper(string & strUrl)
   {

      oslocal().m_bGetUserWallpaper = true;

      for(int i = 0; i < 10; i++)
      {

         if (!oslocal().m_bGetUserWallpaper)
         {


         }

         millis_sleep(50);

      }

      strUrl = oslocal().m_strGetUserWallpaper;

      return true;

   }


#endif

   // class ::crypto::crypto & system::crypto()
   // {

   //    return *m_pcrypto;

   // }


   //__pointer(::account::user_set) system::userset()
   //{

   //   return m_puserset;

   //}


   bool system::defer_accumulate_on_open_file(string_array stra, string strExtra)
   {

      sync_lock sl(mutex());

      m_millisCommandLineLast.Now();

      m_iCommandLineDelay = 1000;

      index iIndex = stra.find_first(":");

      if(iIndex >= 0)
      {

         if(iIndex > 0)
         {

            m_straCommandLineAccumul.add(stra.slice(0, iIndex));

         }

         m_straCommandLineExtra.add(stra.slice(iIndex));

      }
      else
      {

         if(m_straCommandLineExtra.has_elements())
         {

            m_straCommandLineExtra.add(stra);

         }
         else
         {

            m_straCommandLineAccumul.add(stra);

         }

      }

      auto psession = Session;

      auto appptra = psession->get_applicationa();

      ::apex::application * papp = nullptr;

      appptra.pred_remove([](auto & papp)
      {

         return papp->is_system() || papp->is_session();

      });

      if(appptra.has_elements())
      {

         papp = appptra[0];

      }

      if(papp != nullptr)
      {

         __pointer(::create) pcreate(e_create_new);

         merge_accumulated_on_open_file(pcreate);

         papp->post_object(e_message_system, system_message_create, pcreate);

      }

      return true;

   }


   bool system::on_application_menu_action(const char * pszCommand)
   {

      sync_lock sl(mutex());

      auto psession = Session;

      auto applicationa = psession->m_applicationa;

      sl.unlock();

      for(auto & papp : applicationa)
      {

         ASSERT(papp != this);

         if(papp == this)
         {

            continue;

         }

         if(papp->on_application_menu_action(pszCommand))
         {

            return true;

         }

      }

      return false;

   }


   bool system::merge_accumulated_on_open_file(::create * pcreate)
   {

      if(m_straCommandLineAccumul.is_empty())
      {

         return true;

      }

      string_array straAccumul = m_straCommandLineAccumul;

      string_array straExtra = m_straCommandLineExtra;

      m_straCommandLineAccumul.remove_all();

      m_straCommandLineExtra.remove_all();

      command_line_pointer line(e_create_new);

      string strExtra = straExtra.implode(" ");

      if(straAccumul.is_empty())
      {

         line->_001ParseCommandFork("app.exe : open_default " + strExtra);

      }
      else
      {

         string strParam = straAccumul.surround_and_implode(" ", "\"", "\"");

         line->_001ParseCommandFork("app.exe " + strParam + " " + ::str::has_char(strExtra, " : "));

      }

      if(pcreate->m_pcommandline.is_null())
      {

         pcreate->m_pcommandline = line;

      }
      else if(line->m_ecommand == command_line::command_file_open)
      {

         pcreate->m_pcommandline->m_varFile.stra().add_unique_ci(line->m_varFile.stra());

         pcreate->m_pcommandline->m_ecommand = command_line::command_file_open;

      }
      else if(line->m_ecommand == command_line::command_application_start)
      {

         pcreate->m_pcommandline->m_varFile.stra().add(line->m_varFile.stra());

         pcreate->m_pcommandline->m_ecommand = command_line::command_application_start;

      }

      return true;

   }


   bool system::on_open_file(payload varFile, string strExtra)
   {

      auto psession = Session;

      auto applicationa = psession->get_applicationa();

      ::apex::application * papp = nullptr;

      if(applicationa.get_size() > 0)
      {

         papp = applicationa[0];

      }
      else
      {

         return false;

      }

      if(papp != nullptr)
      {

         if(varFile.is_empty())
         {

            papp->request({"app.exe : open_default " + strExtra});

         }
         else
         {

            papp->request({"app.exe \"" + varFile.get_file_path() + "\" " + ::str::has_char(strExtra, " : ")});

         }

         return true;

      }

      return false;

   }


   LPWAVEOUT system::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      auto psession = Session;

      for (auto & papp : psession->m_applicationa)
      {

         Au(papp).waveout_open(iChannel, pformat, pcallback);

      }

      return nullptr;

   }


   // bool system::initialize_native_window1()
   // {

   //    return true;

   // }

// #ifndef APPLE_IOS
//    void * system::initialize_native_window2(const ::rect & rect)

//    {

//       return nullptr;

//    }
// #endif

#ifndef ANDROID

   void system::on_os_text(e_os_text etext, string strText)
   {


   }

#endif

//#ifdef _UWP
//
//
//
//   CLASS_DECL_AURA bool get_window_rect(::aura::system_window ^ pwindow, RECTD * prect)
//
//   {
//
//      Windows::Foundation::Rect rect = pwindow->get_window_rect();
//
//      prect->left = rect.X;
//
//      prect->top = rect.Y;
//
//      prect->right = prect->left + rect.Width;
//
//      prect->bottom = prect->top + rect.Height;
//
//
//      return true;
//   }
//
//
//   CLASS_DECL_AURA bool get_window_rect(::aura::system_window ^ pwindow, RECT32 * prect)
//   {
//
//      ::rectd rect;
//
//      if (!get_window_rect(pwindow, (RECTD*)rect))
//      {
//
//         return false;
//
//      }
//
//      ::copy(prect, rect);
//
//      return true;
//
//   }
//
//
//#endif



   ::user::interaction_impl * system::impl_from_handle(void * pdata)
   {

      return oswindow_interaction_impl((oswindow)pdata);

   }

   ::user::interaction * system::ui_from_handle(void * pdata)
   {

      ::user::interaction_impl * pimpl = impl_from_handle(pdata);

      if (pimpl == nullptr)
      {

         return nullptr;

      }

      try
      {

         return pimpl->m_puserinteraction;

      }
      catch (...)
      {

         __throw(resource_exception("not good window anymore"));

      }

      return nullptr;

   }


//   index system::get_main_monitor(RECT32 * prect)
//   {
//
//      index iMainMonitor = 0;
//
//#ifdef WINDOWS_DESKTOP
//
//      HMONITOR hmonitorPrimary = GetPrimaryMonitorHandle();
//
//      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
//      {
//
//         if (m_hmonitora[iMonitor] == hmonitorPrimary)
//         {
//
//            iMainMonitor = iMonitor;
//
//            break;
//
//         }
//
//      }
//
//
//#endif
//
//      if (prect != nullptr)
//
//      {
//
//         get_monitor_rect(iMainMonitor, prect);
//
//
//      }
//
//      return iMainMonitor;
//
//   }


   /*::count system::get_monitor_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#elif defined(MACOS)

      return GetScreenCount();

#elif defined(LINUX)

      sync_lock sl(mutex());

      return m_rectaMonitor.get_count();

#else

      return 1;

#endif

   }*/


//   bool system::get_monitor_rect(index iMonitor, RECT32 * prect)
//   {
//
//#if MOBILE_PLATFORM
//
//      //get_context_session()->m_puiHost->get_window_rect(prect);
//
//      GetMainScreenRect(prect);
//
//      return true;
//
//#elif defined(WINDOWS_DESKTOP)
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      *prect = m_monitorinfoa[iMonitor].rcMonitor;
//
//
//#elif defined(_UWP)
//
//
//      return false;
//
//
//#elif defined(LINUX)
//
//      sync_lock sl(mutex());
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      *prect = m_rectaMonitor[iMonitor];
//
//
//#elif defined(__APPLE__)
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      GetScreenRect(prect, (int) iMonitor);
//
//
//#else
//
//      prect->left = 0;
//
//      prect->top = 0;
//
//      prect->right = oslocal().m_iScreenWidth;
//
//      prect->bottom = oslocal().m_iScreenHeight;
//
//
//#endif
//
//      return true;
//
//   }
//
//
//   ::count system::get_desk_monitor_count()
//   {
//
//      return get_monitor_count();
//
//   }
//
//
//   bool system::get_desk_monitor_rect(index iMonitor, RECT32 * prect)
//
//   {
//
//      return get_monitor_rect(iMonitor, prect);
//
//
//   }
//
//
//   index system::get_main_wkspace(RECT32 * prect)
//
//   {
//
//      index iMainWkspace = 0;
//
//#ifdef WINDOWS_DESKTOP
//
//      HMONITOR hwkspacePrimary = GetPrimaryMonitorHandle();
//
//      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
//      {
//
//         if (m_hmonitora[iWkspace] == hwkspacePrimary)
//         {
//
//            iMainWkspace = iWkspace;
//
//            break;
//
//         }
//
//      }
//
//
//#endif
//
//      if (prect != nullptr)
//
//      {
//
//         get_wkspace_rect(iMainWkspace, prect);
//
//
//      }
//
//      return iMainWkspace;
//
//   }


//   ::count system::get_wkspace_count()
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return m_monitorinfoa.get_count();
//
//#else
//
//      return get_monitor_count();
//
//#endif
//
//   }
//

//   bool system::get_wkspace_rect(index iWkspace, RECT32 * prect)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//         return false;
//
//      *prect = m_monitorinfoa[iWkspace].rcWork;
//
//
//#elif defined(_UWP)
//
//      return get_monitor_rect(iWkspace, prect);
//
//
//      //#elif defined(LINUX)
//      //
//      //return false;
//      //
//#elif defined(__APPLE__)
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//      {
//
//         return false;
//
//      }
//
//      GetWkspaceRect(prect, (int) iWkspace);
//
//
//      //      prect->top += ::mac::get_system_main_menu_bar_height();
//
//      //    prect->bottom -= ::mac::get_system_dock_height();
//
//#elif defined(LINUX)
//
//      sync_lock sl(mutex());
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//      {
//
//         return false;
//
//      }
//
//      *prect = m_rectaWork[iWkspace];
//
//
//      return true;
//
//#else
//
//      //__throw(todo());
//
//      //::get_window_rect(::get_desktop_window(),prect);
//
//
//      get_monitor_rect(iWkspace, prect);
//
//
//#endif
//
//      return true;
//
//   }
//
//
//   ::count system::get_desk_wkspace_count()
//   {
//
//      return get_wkspace_count();
//
//   }
//
//
//   bool system::get_desk_wkspace_rect(index iWkspace, RECT32 * prect)
//
//   {
//
//      return get_wkspace_rect(iWkspace, prect);
//
//
//   }
//
//   index system::get_ui_wkspace(::user::interaction * pinteraction)
//   {
//
//      index iMainWkspace = 0;
//
//#ifdef WINDOWS_DESKTOP
//
//      HMONITOR hwkspacePrimary = GetUiMonitorHandle(pinteraction->get_handle());
//
//      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
//      {
//
//         if (m_hmonitora[iWkspace] == hwkspacePrimary)
//         {
//
//            iMainWkspace = iWkspace;
//
//            break;
//
//         }
//
//      }
//
//#endif
//
//      return iMainWkspace;
//
//   }

   ::image_pointer system::matter_cache_image(::layered * pobjectContext, const string & strMatter)
   {

      string str(strMatter);

      if (!str.begins_ci("matter://"))
      {

         str = "matter://" + str;

      }

      return get_cache_image(pobjectContext, str);

   }



   ::image_pointer system::get_cache_image(::layered * pobjectContext, const ::payload & varFile)
   {

      ::file::path path = varFile.get_file_path();

      if (path.is_empty())
      {

         return nullptr;

      }

      sync_lock sl(get_image_mutex());

      auto & pimage = m_mapImage[path];

      if (!pimage)
      {

         __construct(pimage);

         pimage->set_nok();

      }

      return pimage;

   }


   ::image_pointer system::get_image(::layered * pobjectContext, const ::payload & varFile, bool bCache, bool bSync)
   {

      auto pimage = get_cache_image(pobjectContext, varFile);

      if (!::is_ok(pimage))
      {

         Application.image()._load_image(pimage, varFile, bSync);

      }

      return pimage;

   }


   ::image_pointer system::matter_image(::layered * pobjectContext, const string & strMatter, bool bCache, bool bSync)
   {

      string str(strMatter);

      if (!str.begins_ci("matter://"))
      {

         str = "matter://" + str;

      }

      return get_image(pobjectContext, str, bSync);

   }


   string system::standalone_setting(string str)
   {

      return file_as_string(Context.dir().standalone() / (str + ".txt"));

   }


   bool system::set_standalone_setting(string str, string strSetting)
   {

      return file_put_contents(Context.dir().standalone() / (str + ".txt"), strSetting);

   }


   void system::on_extra(string str)
   {

      string strProtocol = System.url().get_protocol(str);

#ifdef WINDOWS_DESKTOP

      if (strProtocol == "ca2project")
      {

         string strBase = System.url().get_server(str);

         string strAppId = System.url().get_script(str);

         ::str::begins_eat(strAppId, "/");

         string strQuery = System.url().get_query(str);

         string strMessage;

         strMessage.Format("protocol: ca2project\nbase: %s\nAppId: %s\nquery: %s\n", strBase, strAppId, strQuery);

         //message_box(strMessage, e_message_box_ok);

         string strParams;

         //strParams.Format("\"ca2project\" \"%s\" \"%s\" \"%s\"\n", strBase, strAppId, strQuery);

         string strProj;

         strProj = strAppId;

         string_array stra;

         stra.explode("/", strAppId);

         strProj.replace_ci("-", "_");
         strProj.replace_ci("/", "_");

         //strProj = "..\\..\\..\\" + stra[0] + "\\" + stra[1] + "\\" + stra[1] + ".vcxproj";

         strParams.Format("\"openvsproject://%s\"", strProj);


         //int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", display_none, 30, 1000, nullptr, 0);

      }
#elif defined MACOS
      if (strProtocol == "ca2project")
      {

         string strBase = System.url().get_server(str);

         string strScheme = System.url().get_script(str);

         ::str::begins_eat(strScheme, "/");

         if(strBase == "scheme")
         {

//         int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", display_none, 30, 1000, nullptr, 0);

            ::file::path pathScript = ::dir::tool() / "papaya/script/xcode_set_active_scheme.scpt";

            ::system("osascript \""+pathScript + "\" \"" + strScheme + "\"");

         }
         else if(strBase == "archive")
         {

            ::system("xcodebuild -scheme \"" + strScheme + "\" archive");

         }

      }
#endif

   }





   void system::on_initial_frame_position(::user::frame * pframe)
   {

      if(has_property("client_only"))
      {

#ifdef _UWP

         //auto psession = Session;

         auto puserinteraction = __user_interaction(pframe);

         __pointer(::uwp::interaction_impl) pimpl = puserinteraction->m_pimpl;

         if (pimpl.is_set())
         {

            auto pdirectxapplication = pimpl->m_frameworkview;

            auto directx = pdirectxapplication->m_directx;

            directx->UpdateForWindowSizeChange();

         }

#endif

      }

   }


   //void system::on_graphics_ready()
   //{

   //}


   void system::__tracea(::matter * pobjectContext, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
   {

      if (m_ptrace.is_null())
      {

         __simple_tracea(trace_object(pobjectContext), elevel, pszFunction, pszFile, iLine, psz);

         return;

      }

      log().__tracea(trace_object(pobjectContext), elevel, pszFunction, pszFile, iLine, psz);

   }


   void system::browser(string strUrl, string strBrowser, string strProfile, string strTarget)
   {

       Context.os().link_open(strUrl);

       return;

#if 0

      if (strProfile.is_empty() && strTarget.is_empty() && strBrowser.is_empty())
      {

         //::os_message_box(NULL, strUrl, strUrl, e_message_box_ok);

         Context.os().link_open(strUrl);

         return;

      }

      string strBrowserPath;
      string strBrowserDir;
      string strBrowserHelperPath;
      string strBrowserHelperDir;

      string strId;

      ::file::path path;

      string strParam;

      Context.os().get_default_browser(strId, path, strParam);

      if (strProfile.is_empty() || strProfile == "native")
      {

         strProfile = "default";

      }

      string strUser = strProfile;

      string strWeather = strBrowser;

      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
      {

         strWeather = Context.file().as_string(::dir::system() / "browser_weather.txt");

      }

      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
      {

         strWeather = "browser_day";

      }

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      if (timeNow.GetMonth() == 12)
      {
         if (timeNow.GetDay() >= 16)
         {

            strWeather = "synth_" + strWeather;

         }

      }
      else if (timeNow.GetMonth() == 1)
      {
         if (timeNow.GetDay() <= 14)
         {

            strWeather = "synth_" + strWeather;

         }

      }



      strProfile = strProfile + "." + strWeather;

      if (strUrl.has_char())
      {

         if (strBrowser == "firefox")
         {

            //strUrl = "https://ca2.cc/open_f___?url=" + System.url_encode(strUrl) + "&profile=" + System.url_encode(strProfile) + "&target=" + System.url_encode(strTarget);

         }
         else
         {

            //strUrl = "https://ca2.cc/open_tab?url=" + System.url_encode(strUrl) + "&profile=" + System.url_encode(strProfile) + "&target=" + System.url_encode(strTarget);

         }

      }


      if (strId == "firefox")
      {

         firefox(strUrl, strBrowser, strProfile, strParam);

      }
      else if (strId == "chrome")
      {

         chromium(strUrl, strBrowser, strId, path, strProfile, strParam);

      }
      else if (strId == "vivaldi")
      {

         chromium(strUrl, strBrowser, strId, path, strProfile, strParam);

      }
      else if (strId == "commander")
      {

         //if (m_strAppName == "app-core/commander")
         {

            chromium(strUrl, strBrowser, strId, Context.os().get_app_path("chrome"), strProfile, strParam);

         }
         //else
         {

            //commander(strUrl, strWeather, strUser, path, strParam);

         }

      }
      else
      {

#if defined(_UWP)


         string * pstrNew = new string(strUrl);

         Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::Windows::UI::Core::CoreDispatcherPriority::Normal,
            ref new Windows::UI::Core::DispatchedHandler([pstrNew]()
               {

                  ::Windows::Foundation::Uri ^ uri = ref new ::Windows::Foundation::Uri(*pstrNew);

                  delete pstrNew;

                  LauncherOptions ^ options = ref new LauncherOptions();

                  options->TreatAsUntrusted = false;

                  Launcher::LaunchUriAsync(uri, options);

               }));

         //#elif defined(LINUX)
         //
         //      ::system("xdg-open \"" + strUrl + "\"");
         //
         //      return true;
         //
         //#elif defined(__APPLE__)
         //    openURL(strLink);
         //  return true;
#elif defined(ANDROID)

         string strOpenUrl;

         if (System.oslocal().m_pszOpenUrl != nullptr)
         {

            strOpenUrl = System.oslocal().m_pszOpenUrl;

            try
            {

               ::free((void *)System.oslocal().m_pszOpenUrl);

            }
            catch (...)
            {


            }

            System.oslocal().m_pszOpenUrl = nullptr;

         }


         //strOpenUrl = strUrl + str::has_char(strOpenUrl, ";");

         //if (strOpenUrl.has_char())
         {

            // System.m_pandroidinitdata->m_pszOpenUrl = strdup(strLink);

            System.oslocal().m_pszOpenUrl = strdup(strUrl);

         }


#elif defined(MACOS)

         ::system("open -a /Applications/Safari.app \"" + strUrl + "\"");

#elif defined(APPLE_IOS)

         ui_open_url(strUrl);

#elif defined(WINDOWS_DESKTOP)

         if (strUrl.is_empty())
         {

            strUrl = "foo.html";

         }

         ::ShellExecuteW(nullptr, L"open", wstring(strUrl), nullptr, L"C:\\Windows", SW_SHOWDEFAULT);

         //::file::path path = getenv("APPDATA");

         //path /= strProfile;

         //call_sync("C:\\Program Files\\Opera.exe", "--user-data-dir=\"" + path + "\" " + strUrl, "C:\\Users\\camilo\\AppData\\Local\\Vivaldi\\Application", SW_SHOWNORMAL, 0);

#else

         if (strUrl.has_char())
         {

            strParam = "\"" + strUrl + "\"";

         }

         ::file::path pathDir;

         pathDir = path.folder();

         ::file::path shell;

         shell = "/bin/bash";

         if (strBrowser == "vivaldi")
         {

            ::file::path pathHome(getenv("HOME"));

            ::file::path pathProfile;

            pathProfile = pathHome / "ca2/Vivaldi/Profile" / strProfile;

            call_async(shell, " -c \"" + path + " --user-data-dir=\\\"" + pathProfile + "\\\" " + strParam, pathHome, display_default, false);

         }
         else if (strBrowser == "chrome")
         {

            ::file::path pathHome(getenv("HOME"));

            ::file::path pathProfile;

            pathProfile = pathHome / "ca2/Chrome/Profile" / strProfile;

            string strCmd = path + " --user-data-dir=\"" + pathProfile + "\" " + strParam;

            strCmd.replace("\"", "\\\"");

            strParam = " -c \"" + strCmd + "\"";

            //MessageBox(nullptr, strParam, path, e_message_box_ok);

            call_async(shell, strParam, pathHome, display_default, false);

         }
         else if (strBrowser == "firefox")
         {

            ::file::path pathHome(getenv("HOME"));

            ::file::path pathProfile;

            pathProfile = pathHome / "ca2/Firefox/Profile" / strProfile;

            call_async(shell, "-c \"" + path + " -profile=\\\"" + pathProfile + "\\\" " + strParam + "\"", pathHome, display_default, false);

         }
         else
         {

            ::system("xdg-open " + strUrl);

         }



#endif

      }

#endif

   }



   void system::chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam)
   {

#ifdef _UWP

      Context.os().native_full_web_browser(strUrl);

      return;

#endif

      ::file::path pathDir;

      pathDir = path.folder();

      ::file::path pathAppDataDir(::dir::ca2roaming());

      ::file::path pathProfile;

      string strBrowserProfile;

      if (strId == "chrome" || strId == "commander")
      {

         strBrowserProfile = "Chrome";


      }
      else if (strId == "vivaldi")
      {

         strBrowserProfile = "Vivaldi";

      }
      else
      {

         strBrowserProfile = "Chromium";

      }


      try
      {

         bool bFound = false;

         pathProfile = pathAppDataDir / strBrowserProfile / "Profile" / strProfile;

         if (!bFound)
         {

            if (strUrl.has_char())
            {

               strsize iFind = strParam.find("%1");

               if (iFind >= 0)
               {

                  strParam = strParam.Left(iFind) + strUrl + strParam.Mid(iFind + 2) + " ";

               }
               else
               {

                  strParam = "\"" + strUrl + "\" ";

               }

            }
            else
            {

               strParam = "";

            }

         }

#ifdef WINDOWS_DESKTOP

         {

            if (strParam.trimmed().begins_ci("--"))
            {

               strParam = "--user-data-dir=\"" + pathProfile + "\" " + strParam;

            }
            else
            {

               strParam += "--user-data-dir=\"" + pathProfile + "\"";

            }

            strParam += " " + file_as_string(dir::localconfig() / "app-core/commander/chrome.txt");

            call_async(path, strParam, pathDir, display_default, false);

         }

#elif defined(MACOS)

         string_array sa;

         sa = get_c_args_for_c(strParam);

         sa.add("--user-data-dir=" + pathProfile + "");

         string strChrome = file_as_string(dir::localconfig() / "app-core/commander/chrome.txt");

         string_array sa2 = get_c_args_for_c(strChrome);

         sa.add(sa2);

         auto argv = sa.c_ansi_get();

         argv.add(nullptr);

         string strApp = System.url().url_decode(path);

         // 0x00010000 NSWorkspaceLaunchAsync
         // 0x00080000 NSWorkspaceLaunchNewInstance

         ns_launch_app(strApp, argv.get_data(), 0x00010000 | 0x00080000);

#elif defined(LINUX)

         ::file::path shell;

         shell = "/bin/bash";

         strParam += "--user-data-dir=\"" + pathProfile + "\"";

         strParam += " " + file_as_string(dir::localconfig() / "app-core/commander/chrome.txt");

         string strCmd = path + " " + strParam;

         strCmd.replace("\'", "\\\'");

         strParam = " -c '" + strCmd + "'";

         output_debug_string(strParam);

         call_async(shell, strParam, pathDir, display_default, false);

#endif

      }
      catch (...)
      {


      }

   }


   void system::defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile)
   {

#ifdef _UWP


#else

      if (Context.dir().is(pathProfile))
      {

         return;

      }

      ::file::path pathDir;

      pathDir = pathFirefox.folder();

      ::file::path pathProfileDir;

      pathProfileDir = pathProfile.folder();

      Context.dir().mk(pathProfileDir);

      string strParam = "-no-remote -CreateProfile \"" + strProfileName + " " + pathProfile + "\"";

      ::property_set set;

      call_sync(pathFirefox, strParam, pathDir, display_default, 3_min, set);

#endif

   }


   ::estatus system::get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory)
   {

#ifdef WINDOWS_DESKTOP

      try
      {

         ::windows::registry::key key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox");

         string strCurrentVersion;

         key.get("CurrentVersion", strCurrentVersion);

         key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox\\" + strCurrentVersion + "\\Main");

         key.get("PathToExe", strPathToExe);

         key.get("Install Directory", strInstallDirectory);

      }
      catch (const ::estatus & estatus)
      {

         return estatus;

      }

      return ::success;

#else

      return ::error_failed;

#endif

   }


   ::estatus system::firefox(string strUrl, string strBrowser, string strProfile, string strParam)
   {

#ifdef _UWP

      Context.os().native_full_web_browser(strUrl);

#else

      string strBrowserPath;
      string strBrowserDir;
      string strBrowserHelperPath;
      string strBrowserHelperDir;

      ::file::path pathAppDataDir(getenv("APPDATA"));

      ::file::path pathProfile;

      strParam = "-P \"" + strProfile + "\"";

      if (strUrl.has_char())
      {

         strParam += " -new-tab \"" + strUrl + "\"";

      }

      auto estatus = get_firefox_installation_info(strBrowserPath, strBrowserDir);

      if (::failed(estatus))
      {

         return estatus;

      }

      if (!Context.file().exists(strBrowserPath) || !Context.dir().is(strBrowserDir))
      {

         return error_not_found;

      }

      strBrowserHelperPath = ::file::path(strBrowserDir) / "uninstall/helper.exe";

      strBrowserHelperDir = ::file::path(strBrowserDir) / "uninstall";

      pathProfile = pathAppDataDir / "ca2/Firefox/Profile" / strProfile;

      defer_create_firefox_profile(strBrowserPath, strProfile, pathProfile);

      bool bFound = false;

      if (!bFound)
      {

         call_async(strBrowserPath, strParam, strBrowserDir, display_normal, false);

         call_async(strBrowserHelperPath, "/SetAsDefaultAppUser", strBrowserHelperDir, display_none, false);

      }

      if (strBrowser.has_char())
      {

         Context.file().put_contents_utf8(::dir::system() / "browser.txt", strBrowser);

         Context.file().put_contents_utf8(::dir::system() / "browser_path.txt", strBrowserPath);

         Context.file().put_contents_utf8(::dir::system() / "browser_dir.txt", strBrowserDir);

      }

#endif

      return ::success;

   }

   string system::get_local_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s", pszAppName);
      return strMutex;
   }

   string system::get_local_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s, id:%s", pszAppName, strId.c_str());
      return strMutex;
   }

   string system::get_global_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s", pszAppName);
      return strMutex;
   }

   string system::get_global_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s, id:%s", pszAppName, strId.c_str());
      return strMutex;
   }

//
//   ::thread* system::get_task(ithread_t ithread)
//   {
//
//      sync_lock sl(&m_mutexTask);
//
//      return m_threadmap[ithread];
//
//   }
//
//
//   ithread_t system::get_thread_id(::thread* pthread)
//   {
//
//      sync_lock sl(&m_mutexTask);
//
//      ithread_t ithread = NULL_ITHREAD;
//
//      if (!m_threadidmap.lookup(pthread, ithread))
//      {
//
//         return 0;
//
//      }
//
//      return ithread;
//
//   }
//
//
//   void system::set_thread(ithread_t ithread, ::thread* pthread)
//   {
//
//      sync_lock sl(&m_mutexTask);
//
//      m_threadmap[ithread].reset(pthread OBJ_REF_DBG_COMMA_P_NOTE(this, "thread::thread_set"));
//
//      m_threadidmap[pthread] = ithread;
//
//   }
//
//
//   ::aura::estamira& system::estamira()
//   {
//
//      if (!m_pestamira)
//      {
//
//         __compose_new(m_pestamira);
//
//         m_pestamira->init_instance();
//
//      }
//
//      return *m_pestamira.get();
//
//   }
//
//   void system::unset_thread(ithread_t ithread, ::thread * pthread)
//   {
//
//      sync_lock sl(&m_mutexTask);
//
//#if OBJ_REF_DBG
//
//      m_threadmap[ithread].release(this);
//
//#endif
//
//      m_threadmap.remove_key(ithread);
//
//      m_threadidmap.remove_key(pthread);
//
//   }


//#ifdef _OPENGL
   ::estatus system::create_gpu()
   {

      if (m_pgpu)
      {

         return ::success;

      }

      //System.load_library("gpu_opengl");

      auto estatus = System.do_factory_exchange("gpu", "opengl");

      //System.get_library("gpu_opengl");



      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose(m_pgpu);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }
//#endif



   ::thread_group * system::thread_group(::e_priority epriority)
   {

      //return nullptr;

      if (m_bitAvoidProcFork)
      {

         return nullptr;

      }

      sync_lock sl(mutex());

      auto & threadgroupa = m_threadgroupmap[epriority];

      if (threadgroupa.is_empty())
      {

         auto pgroup = __new(::thread_group(this, epriority));

         threadgroupa.add(pgroup);

      }

      return threadgroupa.last();

   }


   ::thread_tool * system::thread_tool(::enum_thread_tool etool)
   {

      sync_lock sl(mutex());

      auto& threadtoola = m_threadtoolmap[etool];

      if (threadtoola.is_empty())
      {

         auto ptool = __new(::thread_tool);

         ptool->m_id = etool;

         threadtoola.add(ptool);

      }

      return threadtoola.last();

   }


   //::thread_toolset * system::toolset(e_tool etool)
   //{

   //   if (m_bAvoidProcFork)
   //   {

   //      return nullptr;

   //   }

   //   __pointer(thread_toolset) & pset = m_toolset.element_at_grow((index)etool);

   //   if (pset.is_null())
   //   {

   //      pset = create_thread_toolset(etool);

   //   }

   //   if (!m_toolmap[::priority_none]->select_toolset(pset))
   //   {

   //      return nullptr;

   //   }

   //   return pset;

   //}


   void system::open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      fork([=]()
      {

         browser(strUrl, "", strProfile, strTarget);

      });

   }


   ::estatus system::verb() // ambigous inheritance from ::aura::system/::axis::application
   {

      return ::thread::verb();

   }



   //::estatus system::init_system()
   //{

   //   if (!::aura::system::init_system())
   //   {

   //      return false;

   //   }

   //   //if (!::axis::application::init_application())
   //   //{

   //   //   return false;

   //   //}

   //   return true;

   //}


   //void system::term()
   //{

   //   //__wait_threading_count_except(this,::millis((5000) * 77));

   //   if (::ftp::command::info2::g_pTheOneAndOnly != nullptr)
   //   {

   //      try
   //      {

   //         delete ::ftp::command::info2::g_pTheOneAndOnly;

   //      }
   //      catch (...)
   //      {

   //         m_result.add(error_failed);

   //      }

   //   }


   //   //try
   //   //{

   //   //   if(m_spcrypto.is_set())
   //   //   {

   //   //      m_spcrypto.release();

   //   //   }

   //   //}
   //   //catch(...)
   //   //{

   //   //   m_result.add(error_failed);

   //   //}

   //   //try
   //   //{

   //   //   ::axis::application::term();

   //   //}
   //   //catch(...)
   //   //{

   //   //   m_result.add(error_failed);

   //   //}

   //   //try
   //   //{

   //   //   if(m_spfile.is_set())
   //   //   {

   //   //      m_spfile.release();

   //   //   }

   //   //}
   //   //catch(...)
   //   //{

   //   //   m_result.add(error_failed);

   //   //}

   //}




   string system::crypto_md5_text(const string & str)
   {

      return crypto().md5(str);

   }


   //__pointer(::aura::session) system::on_create_session()
   //{

   //   return __new(::axis::session);

   //}


   //void system::on_request(::create * pcreate)
   //{

   //   ::aura::system::on_request(pcreate);

   //}







   //::user::document * system::place_hold(::user::interaction * pinteraction)
   //{


   //   //if(m_pcubeInterface != nullptr)
   //   //{
   //   // return m_pcubeInterface->hold(pinteraction);
   //   //}

   //   return nullptr;

   //}


   //::aura::session * system::query_session(index iEdge)
   //{

   //   return nullptr;

   //}









   //void system::hist_hist(const char * psz)
   //{
   //}

   //void system::on_request(::create * pcreate)
   //{

   //   ::axis::system::on_request(pcreate);

   //}

   //::user::interaction_impl * system::impl_from_handle(void * posdata)
   //{

   //   return nullptr;

   //}

   //::user::interaction * system::ui_from_handle(void * posdata)
   //{

   //   return nullptr;

   //}


   string system::url_encode(const string & str)
   {

      return m_purldepartment->url_encode(str);

   }


} // namespace aura


//CLASS_DECL_AURA ::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
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
//CLASS_DECL_AURA bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
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
//CLASS_DECL_AURA bool set_application_installed(const ::file::path & pathExe, string strAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
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
//CLASS_DECL_AURA::file::path get_application_path(string strAppId, const char * pszPlatform, const char * pszConfiguration)
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
//CLASS_DECL_AURA ::file::path get_last_run_application_path_file(string strAppId)
//{
//
//   ::file::path pathFile = ::dir::local() / "appdata" / strAppId / "last_run_path.txt";
//
//   return pathFile;
//
//}
//
//
//CLASS_DECL_AURA::file::path get_last_run_application_path(string strAppId)
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
//CLASS_DECL_AURA bool set_last_run_application_path(string strAppId)
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





//#include "base/node/_node.h"


#ifdef WINDOWS_DESKTOP
//#include "aura/os/windows/windows_system_interaction_impl.h"
#elif defined(_UWP)
#include "aura/os/uwp/_uwp.h"
#endif


//#if !defined(WINDOWS) && !defined(MACOS)
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#endif



#ifdef WINDOWS_DESKTOP



//#include "base/os/windows/windows_system_interaction_impl.h"


//#include <HighLevelMonitorConfigurationAPI.h>
//
//::u32 mc_color_kelvin(MC_COLOR_TEMPERATURE e)
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

//MC_COLOR_TEMPERATURE kelvin_mc_color(::u32 kelvin)
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

#elif defined(LINUX)


#endif




//#ifdef CUBE
//
//extern "C" DECLARE_NEW_AURA_LIBRARY(experience);
//
//#endif

#ifdef WINDOWS
#undef new
#define new ACME_NEW
#endif

#ifdef LINUX
#include <dlfcn.h>

void* g_pbasecore = nullptr;


typedef void BASECORE_INIT();
#endif // LINUX


namespace aura
{

   //CLASS_DECL_AURA void black_body(float* r, float* g, float* b, ::u32 dwTemp);

   /*  bool system::on_application_menu_action(const char * pszCommand)
     {
        return ::aura::system::on_application_menu_action(pszCommand);
     }*/


     //system::system()
     //{

     //   m_bFinalizeIfNoSessionSetting = true;
     //   m_bFinalizeIfNoSession = false;

     //   create_factory < ::aura::session, ::aura::session >();

     //}


  //   ::estatus system::initialize_system(::object* pobject, app_core* pappcore)
  //   {
  //
  //      auto estatus = ::aura::system::initialize_system(pobject, pappcore);
  //
  //      if (!estatus)
  //      {
  //
  //         return estatus;
  //
  //      }
  //
  //      //estatus = ::aura::application::initialize(pobjectContext);
  //
  //     //if (!estatus)
  //     //{
  //
  //     //   return estatus;
  //
  //     //}
  //
  //     //m_strAppId = "base_system";
  //     //m_strAppName = "base_system";
  //     //m_strBaseSupportId = "base_system";
  //     //m_strInstallToken = "base_system";
  //
  //      create_factory < ::draw2d::icon >();
  //
  //      //#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
  //      //
  //      //      m_possystemwindow = new os_system_window();
  //      //
  //      //#endif
  //
  //
  //
  //            //estatus = ::aura::application::initialize(pobject);
  //
  //            //if (!estatus)
  //            //{
  //
  //            //   return estatus;
  //
  //            //}
  //
  //            //m_strAppId                    = "core_system";
  //            //m_strAppName                  = "core_system";
  //            //m_strBaseSupportId            = "core_system";
  //            //m_strInstallToken             = "core_system";
  //
  //      m_phistory = nullptr;
  //      m_ppatch = new aura::patch();
  //      g_pszCooperativeLevel = "aura";
  //
  //      estatus = __compose(m_puserset, __new(::account::user_set(this)));
  //
  //      if (!estatus)
  //      {
  //
  //         throw ::exception::exception(estatus);
  //
  //      }
  //
  //      //#ifdef _UWP
  //      //      m_window                                  = nullptr;
  //      //#endif
  //
  //            //::aura::application * papp = ::get_context_application(pobject);
  //
  //            //if(papp == nullptr)
  //            //{
  //
  //            //   set("parent_system") = nullptr;
  //
  //            //}
  //            //else
  //            //{
  //
  //            //   set("parent_system") = papp->m_psystem;
  //
  //            //}
  //
  //      string strId;
  //      //strId = m_strAppName;
  //      //strId += ::str::has_char(m_strAppId, ".");
  //      //strId += ::str::has_char(m_strBaseSupportId, ".");
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
  //      // m_userset.set_app(this);
  //      //      m_email.set_app(this);
  //
  //
  //
  //
  //
  //
  //      //m_bInitApplication         = false;
  //      //m_bInitApplicationResult   = FALSE;
  //      //m_bProcessInitialize       = false;
  //      //m_bProcessInitializeResult = false;
  //
  //      //m_puserstr                 = nullptr;
  //
  //      //m_pparserfactory           = nullptr;
  //
  //      //m_bLicense                 = false;
  //
  //      //m_prunstartinstaller       = nullptr;
  //      //m_bLicense                 = false;
  //
  //#ifdef WINDOWS_DESKTOP
  //
  //      m_uiWindowsTaskbarCreatedMessage = 0;
  //
  //#endif
  //
  //      return estatus;
  //
  //   }


     //system::~system()
     //{

     //

     //}


   void system::discard_to_factory(__pointer(object) pca)
   {

      UNREFERENCED_PARAMETER(pca);

   }


   //bool system::is_system() const
   //{

   //   return true;

   //}


   //::estatus system::defer_xml()
   //{

   //   if (m_pxml)
   //   {

   //      return ::success;

   //   }

   //   auto estatus = __compose_new(m_pxml);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   estatus = m_pxml->init1();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   estatus = m_pxml->init();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}



   ::estatus system::init2()
   {

      //if(!::aura::application::init2())
      //   return false;

      //auto estatus = ::aura::system::init2();

      //if (!estatus)
      //{

      //   return estatus;

      //}

         auto estatus = __compose_new(m_phistory);

         if(!estatus)
         {

            return estatus;

      }

         post_create_requests();



      return estatus;

   }


   __pointer(::data::node) system::load_xml(const char* pszXml)
   {

      __throw(interface_only_exception());

      return nullptr;

   }


   //bool system::InitApplication()
   //{

   //   if(m_bInitApplication)
   //      return m_bInitApplicationResult;

   //   m_bInitApplicationResult      = FALSE;
   //   m_bInitApplication            = true;

   //   m_bInitApplicationResult = ::aura::system::InitApplication();

   //   return m_bInitApplicationResult;
   //}

//
//   ::estatus system::process_init()
//   {
//
//      //if (m_bProcessInitialize)
//      //{
//
//      //   return m_bProcessInitializeResult;
//
//      //}
//
//      INFO("start");
//
//      //m_bProcessInitializeResult    = false;
//
//      //m_bProcessInitialize          = true;
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
//      //if (!::aura::application::process_init())
//      //{
//
//      //   ERR(".1");
//
//      //   return false;
//
//      //}
//
//      if (!::aura::system::process_init())
//      {
//
//         ERR(".2");
//
//         return false;
//
//      }
//
//      ::aura::profiler::initialize();
//
//
//#ifdef LINUX
//
//      ::user::g_defer_init();
//
//#endif // LINUX
//
//
//      //m_phtml = create_html();
//
//      //m_phtml->add_ref(OBJ_REF_DBG_ARGS);
//
//      //if(m_phtml == nullptr)
//      //   return false;
//
//      //m_phtml->construct(this);
//
//      //m_bProcessInitializeResult = true;
//
//      INFO("success");
//
//      return true;
//
//   }


   //::estatus system::init()
   //{
   //   //
   //   //#ifndef APPLEOS
   //   //
   //   //      if(m_pparserfactory == nullptr)
   //   //      {
   //   //
   //   //      }
   //   //
   //   //#endif

   //         //if (!::aura::application::init())
   //         //{

   //         //   return false;

   //         //}

   //   return true;

   //}


//   ::estatus system::init1()
//   {
//
//      m_pfilehandler = __new(::filehandler::handler(this));
//
//      //if (!::aura::application::init1())
//      //{
//
//      //   return false;
//
//      //}
//
//      if (!::aura::system::init1())
//      {
//
//         return false;
//
//      }
//
//      //if(psession->account()->create_system_user("system") == nullptr)
//      // return false;
//
//#if !defined(CUBE) && !defined(ANDROID)
//
//#if !defined(_DEBUG) || defined(WINDOWS)
//      try
//      {
//#endif
//         find_applications_from_cache();
//#if !defined(_DEBUG) || defined(WINDOWS)
//      }
//      catch (...)
//      {
//      }
//#endif
//
//#endif
//
//      //if(!m_phtml->initialize())
//      //   return false;
//
//      return true;
//
//   }
//



   //::filehandler::handler& system::filehandler()
   //{
   //    __throw(todo("filehandler"));
   //    return *m_pfilehandler;

   //}


   void system::on_start_find_applications_from_cache()
   {

      __throw(todo("filehandler"));
     // m_pfilehandler->m_ptree->remove_all();

   }

   void system::on_end_find_applications_from_cache(stream& is)
   {

      //__throw(todo("filehandler"));
      //is >> *m_pfilehandler;

   }

   void system::on_end_find_applications_to_cache(stream& os)
   {

      //__throw(todo("filehandler"));
      //os << *m_pfilehandler;

   }

   void system::on_map_application_library(::apex::library& library)
   {

      __throw(todo("filehandler"));
      // m_pfilehandler->defer_add_library(library.m_pca2library);

   }


   void system::on_graphics_ready()
   {

      //::aura::system::on_graphics_ready();

      //if (psession->userex()->shell()->m_bPendingUpdate)
      //{

      //   psession->userex()->shell()->on_update_sizes_interest();

      //}

   }


   //::estatus system::init3()
   //{

   //   //if(!::aura::application::init3())
   //   //{

   //   //   return false;

   //   //}

   //   if(m_phistory == nullptr)
   //   {
   //      m_phistory = __new(os_history(this));
   //   }

   //   return true;

   //}


   //::estatus system::init_system()
   //{

   //   if (!::aura::system::init_system())
   //   {

   //      return false;

   //   }

   //   /*set_enum_name(::e_type_null      , "null");
   //   set_enum_name(::type_empty     , "is_empty");
   //   set_enum_name(::type_string    , "string");
   //   set_enum_name(::type_int32   , "integer");
   //   set_enum_name(::type_::u32     , "ulong");
   //   set_enum_name(::type_element       , "ca2");
   //   set_enum_name(::type_bool      , "bool");
   //   set_enum_name(::type_double    , "double");*/

   //   //if (!::aura::application::init_application())
   //   //{

   //   //   return false;

   //   //}

   //   //m_pbergedgemap = __new(::aura::session::map);


   //   return true;

   //}


   //::estatus system::bergedge_start()
   //{

   //   return true;

   //}





//
//
//
//   void system::term_system()
//   {
//
//
//
//      //__wait_threading_count(::millis((5000) * 8));
//
//      //::parallelization::wait_threads(40_s);
//
////#ifdef LINUX
////
////      BASECORE_INIT * f =  (BASECORE_INIT *) dlsym(g_pbasecore, "linux_g_direct_term");
////
////      if(f != nullptr)
////      {
////
////         output_debug_string("linux_g_direct_term entry point not found at basecore library");
////
////         (*f)();
////
////      }
////
////#endif
//      //::aura::application::term_application();
//      try
//      {
//
//         ::aura::system::term_system();
//
//      }
//      catch (...)
//      {
//
//         m_result.add(error_failed);
//
//      }
//
//#ifdef LINUX
//
//      try
//      {
//
//         ::user::g_defer_term();
//
//      }
//      catch (...)
//      {
//
//      }
//
//#endif // LINUX
//
//
//   }


   //__pointer(::aura::session) system::on_create_session()
   //{

   //   return __new(::aura::session);

   //}


   //::aura::session * system::query_session(index iEdge)
   //{

   //   ::aura::session * pbergedge = nullptr;

   //   if (m_pbergedgemap == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   if(!m_pbergedgemap->lookup(iEdge,pbergedge))
   //   {

   //      return nullptr;

   //   }

   //   return pbergedge;

   //}



   //::aura::history& system::hist()
   //{

   //   return *m_phistory;

   //}


   estatus system::set_history(::apex::history* phistory)
   {

      auto estatus = __compose(m_phistory, phistory);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::apex::library * system::on_get_library(const char* pszLibrary)
   {

      __pointer(::apex::library) plibrary;

      bool bLibraryOk = false;

      auto plibraryfactory = ::static_setup::get_first(::static_setup::flag_library, pszLibrary);

      if(!plibraryfactory)
      {

         return nullptr;

      }

      plibrary = plibraryfactory->new_library();

      if(!plibrary)
      {

         return nullptr;

      }

      auto estatus = plibrary->initialize(this);

      if (estatus)
      {

         bLibraryOk = true;

      }

      if (plibrary && bLibraryOk)
      {

         return plibrary;

      }

      return nullptr;

   }


   //void system::term()
   //{

   //   m_phistory.release();


   //   m_pfilehandler.release();

   //   try
   //   {

   //      ::aura::system::term();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //}


   void system::on_allocation_error(const ::string& str, ::object* pobject)
   {

      string strMessage;

      strMessage.Format("system::on_allocation_error Implement \"%s\" allocation\n", str.c_str());

      dev_log(strMessage);

   }


   //void system::on_request(::create* pcreate)
   //{

   //   //get_platform(pcreate->m_pcommandline->m_iEdge,pcreate->m_pcommandline->m_papplicationbias);

   //   ::aura::system::on_request(pcreate);

   //}



   //bool system::sync_load_url(string& str, const char* pszUrl, ::account::user* puser, ::http::cookies* pcookies)
   bool system::sync_load_url(string& str, const char* pszUrl, ::http::cookies* pcookies)

   {

      string filename = Context.file().time_square();

      property_set set;

      //set["user"] = puser;

      set["cookies"] = pcookies;

      if (!Context.http().download(pszUrl, filename, set))

      {

         return false;

      }

      string strLocation = set["get_headers"]["Location"];

      if (strLocation.has_char())
      {

         property_set set;

         //set["user"] = puser;

         set["cookies"] = pcookies;

         Context.file().del(filename);

         return Context.http().download(str, strLocation, set);

      }

      str = Context.file().as_string(filename);

      return true;

   }


   //::aura::patch& system::patch()
   //{

   //   return *m_ppatch;

   //}


   //::http::system & system::http()
   //{

   //   return *m_sphttpsystem;

   //}


   //bool system::base_support()
   //{

   //   return true;

   //}


   //index system::get_new_bergedge(application_bias * pbiasCreation)
   //{

   //   index iNewEdge = m_iNewEdge;

   //   ::aura::session * pbergedge = nullptr;

   //   while(m_pbergedgemap->lookup(iNewEdge,pbergedge))
   //   {

   //      iNewEdge++;

   //   }

   //   if (get_context_session(iNewEdge, pbiasCreation) == nullptr)
   //   {

   //      return -1;

   //   }

   //   m_iNewEdge = iNewEdge + 1;

   //   return iNewEdge;

   //}




   //::user::document * system::place_hold(::user::interaction * pinteraction)
   //{

   //   return nullptr;

   //}


   //bool system::on_install()
   //{

   //   //try
   //   //{

   //   //   xxdebug_box("system::on_install","system::on_install",0);

   //   //   if (!::aura::application::on_install())
   //   //   {

   //   //      return false;

   //   //   }

   //   //}
   //   //catch(...)
   //   //{

   //   //   return false;

   //   //}

   //   return true;

   //}


   string system::get_host_location_url()
   {

      return "";

   }


   ::estatus system::add_view_library(::apex::library* plibrary)
   {

      m_libraryspa.add(plibrary);

      ::array < ::id > ida;

      plibrary->get_create_view_id_list(ida);

      for (i32 i = 0; i < ida.get_count(); i++)
      {

         m_idmapCreateViewLibrary.set_at(ida[i], plibrary);

      }

      return true;

   }


   //   void system::post_fork_uri(const char * pszUri,application_bias * papplicationbias)
   //   {
   //
   //      add_fork_uri(pszUri,papplicationbias);
   //
   //      //if(has_property("version"))
   //      //{
   //
   //      //   install().m_strVersion = m_varTopicQuery["version"];
   //
   //      //}
   //
   //      if(m_varTopicQuery["locale"].array_get_count() > 0)
   //      {
   //
   //         psession->set_locale(m_varTopicQuery["locale"].stra()[0],::source_user);
   //
   //      }
   //
   //      if(m_varTopicQuery["schema"].array_get_count() > 0)
   //      {
   //
   //         psession->set_schema(m_varTopicQuery["schema"].stra()[0],::source_user);
   //
   //      }
   //
   //   }


#ifdef _UWP


   bool system::get_window_rect(RECT32* prect)
   {

      if (::is_null(get_context_session()))
      {

         return false;

      }

      try
      {

         if (::is_null(get_context_session()->m_puiHost))
         {

            return false;

         }

         auto puiHost = __user_interaction(get_context_session()->m_puiHost);

         puiHost->get_window_rect(prect);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


#endif


   //::estatus     system::do_request(::create* pcreate)
   //{

   //   return aura::system::do_request(pcreate);

   //}


   void system::assert_valid() const
   {

      ::thread::assert_valid();

   }


   void system::dump(dump_context& context) const
   {

      ::thread::dump(context);

   }


   ::estatus     system::main()
   {

      return ::aqua::system::main();

   }


   //__pointer_array(::aura::session) & system::planesessionptra()
   //{

   //   return m_planesessionptra;

   //}


   //void system::hist_hist(const char* psz)
   //{

   //   hist().hist(psz);

   //}


   //::type system::get_pane_tab_view_type_info()
   //{

   //   return __type(userex::pane_tab_view);

   //}




//
//   ::estatus system::initialize_system(::object* pobjectContext, ::app_core* pappcore)
//   {
//
//      auto estatus = ::aura::system::initialize_system(pobjectContext, pappcore);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      //estatus = ::aura::application::initialize(pobjectContext);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //m_strAppId = "base_system";
//      //m_strAppName = "base_system";
//      //m_strBaseSupportId = "base_system";
//      //m_strInstallToken = "base_system";
//
//      create_factory < ::draw2d::icon >();
//
//      g_pszCooperativeLevel = "aura";
//
//#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
//
//      m_possystemwindow = new os_system_window();
//
//#endif
//
//      return estatus;
//
//   }


   //void system::term_system()
   //{

   //   //aura::application::term_application();
   //   aura::system::term_system();

   //}


   void system::set_active_guie(::user::interaction* pinteraction)
   {

#ifdef WINDOWS_DESKTOP

      if (pinteraction == nullptr)
      {

         ::set_active_window(nullptr);

      }
      else
      {

         ::set_active_window(pinteraction->get_wnd()->get_safe_handle());

      }

#endif

   }


   void system::set_focus_guie(::user::interaction* pinteraction)
   {

      if (pinteraction == nullptr)
      {

         ::set_focus(nullptr);

         return;

      }


      ::set_focus(pinteraction->get_safe_handle());

      if (pinteraction->get_wnd() != nullptr)
      {

         pinteraction->SetFocus();

      }

      return;

   }


   void system::on_apply(::subject * paction)
   {

      ::aqua::system::on_apply(paction);

   }


   ::estatus system::initialize_estamira()
   {

      if (m_pestamira)
      {

         return ::success;

      }

      auto estatus = __compose(m_pestamira);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pestamira->init_instance();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /* colorramp.c -- color temperature calculation source
   This file is part of Redshift.
   Redshift is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   Redshift is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with Redshift.  If not, see <http://www.gnu.org/licenses/>.
   Copyright (c) 2013-2014  Jon Lund Steffensen <jonlst@gmail.com>
   Copyright (c) 2013  Ingo Thies <ithies@astro.uni-bonn.de>
   */

   /* Whitepoint values for temperatures at 100K intervals.
   These will be interpolated for the actual temperature.
   This table was provided by Ingo Thies, 2013. See
   the file README-colorramp for more information. */
   static const float g_fa_blackbody_color[] =
   {
      1.00000000f,  0.18172716f,  0.00000000f, /* 1000K */
      1.00000000f,  0.25503671f,  0.00000000f, /* 1100K */
      1.00000000f,  0.30942099f,  0.00000000f, /* 1200K */
      1.00000000f,  0.35357379f,  0.00000000f, /* ...   */
      1.00000000f,  0.39091524f,  0.00000000f,
      1.00000000f,  0.42322816f,  0.00000000f,
      1.00000000f,  0.45159884f,  0.00000000f,
      1.00000000f,  0.47675916f,  0.00000000f,
      1.00000000f,  0.49923747f,  0.00000000f,
      1.00000000f,  0.51943421f,  0.00000000f,
      1.00000000f,  0.54360078f,  0.08679949f,
      1.00000000f,  0.56618736f,  0.14065513f,
      1.00000000f,  0.58734976f,  0.18362641f,
      1.00000000f,  0.60724493f,  0.22137978f,
      1.00000000f,  0.62600248f,  0.25591950f,
      1.00000000f,  0.64373109f,  0.28819679f,
      1.00000000f,  0.66052319f,  0.31873863f,
      1.00000000f,  0.67645822f,  0.34786758f,
      1.00000000f,  0.69160518f,  0.37579588f,
      1.00000000f,  0.70602449f,  0.40267128f,
      1.00000000f,  0.71976951f,  0.42860152f,
      1.00000000f,  0.73288760f,  0.45366838f,
      1.00000000f,  0.74542112f,  0.47793608f,
      1.00000000f,  0.75740814f,  0.50145662f,
      1.00000000f,  0.76888303f,  0.52427322f,
      1.00000000f,  0.77987699f,  0.54642268f,
      1.00000000f,  0.79041843f,  0.56793692f,
      1.00000000f,  0.80053332f,  0.58884417f,
      1.00000000f,  0.81024551f,  0.60916971f,
      1.00000000f,  0.81957693f,  0.62893653f,
      1.00000000f,  0.82854786f,  0.64816570f,
      1.00000000f,  0.83717703f,  0.66687674f,
      1.00000000f,  0.84548188f,  0.68508786f,
      1.00000000f,  0.85347859f,  0.70281616f,
      1.00000000f,  0.86118227f,  0.72007777f,
      1.00000000f,  0.86860704f,  0.73688797f,
      1.00000000f,  0.87576611f,  0.75326132f,
      1.00000000f,  0.88267187f,  0.76921169f,
      1.00000000f,  0.88933596f,  0.78475236f,
      1.00000000f,  0.89576933f,  0.79989606f,
      1.00000000f,  0.90198230f,  0.81465502f,
      1.00000000f,  0.90963069f,  0.82838210f,
      1.00000000f,  0.91710889f,  0.84190889f,
      1.00000000f,  0.92441842f,  0.85523742f,
      1.00000000f,  0.93156127f,  0.86836903f,
      1.00000000f,  0.93853986f,  0.88130458f,
      1.00000000f,  0.94535695f,  0.89404470f,
      1.00000000f,  0.95201559f,  0.90658983f,
      1.00000000f,  0.95851906f,  0.91894041f,
      1.00000000f,  0.96487079f,  0.93109690f,
      1.00000000f,  0.97107439f,  0.94305985f,
      1.00000000f,  0.97713351f,  0.95482993f,
      1.00000000f,  0.98305189f,  0.96640795f,
      1.00000000f,  0.98883326f,  0.97779486f,
      1.00000000f,  0.99448139f,  0.98899179f,
      1.00000000f,  1.00000000f,  1.00000000f, /* 6500K */
      0.98947904f,  0.99348723f,  1.00000000f,
      0.97940448f,  0.98722715f,  1.00000000f,
      0.96975025f,  0.98120637f,  1.00000000f,
      0.96049223f,  0.97541240f,  1.00000000f,
      0.95160805f,  0.96983355f,  1.00000000f,
      0.94303638f,  0.96443333f,  1.00000000f,
      0.93480451f,  0.95923080f,  1.00000000f,
      0.92689056f,  0.95421394f,  1.00000000f,
      0.91927697f,  0.94937330f,  1.00000000f,
      0.91194747f,  0.94470005f,  1.00000000f,
      0.90488690f,  0.94018594f,  1.00000000f,
      0.89808115f,  0.93582323f,  1.00000000f,
      0.89151710f,  0.93160469f,  1.00000000f,
      0.88518247f,  0.92752354f,  1.00000000f,
      0.87906581f,  0.92357340f,  1.00000000f,
      0.87315640f,  0.91974827f,  1.00000000f,
      0.86744421f,  0.91604254f,  1.00000000f,
      0.86191983f,  0.91245088f,  1.00000000f,
      0.85657444f,  0.90896831f,  1.00000000f,
      0.85139976f,  0.90559011f,  1.00000000f,
      0.84638799f,  0.90231183f,  1.00000000f,
      0.84153180f,  0.89912926f,  1.00000000f,
      0.83682430f,  0.89603843f,  1.00000000f,
      0.83225897f,  0.89303558f,  1.00000000f,
      0.82782969f,  0.89011714f,  1.00000000f,
      0.82353066f,  0.88727974f,  1.00000000f,
      0.81935641f,  0.88452017f,  1.00000000f,
      0.81530175f,  0.88183541f,  1.00000000f,
      0.81136180f,  0.87922257f,  1.00000000f,
      0.80753191f,  0.87667891f,  1.00000000f,
      0.80380769f,  0.87420182f,  1.00000000f,
      0.80018497f,  0.87178882f,  1.00000000f,
      0.79665980f,  0.86943756f,  1.00000000f,
      0.79322843f,  0.86714579f,  1.00000000f,
      0.78988728f,  0.86491137f,  1.00000000f, /* 10000K */
      0.78663296f,  0.86273225f,  1.00000000f,
      0.78346225f,  0.86060650f,  1.00000000f,
      0.78037207f,  0.85853224f,  1.00000000f,
      0.77735950f,  0.85650771f,  1.00000000f,
      0.77442176f,  0.85453121f,  1.00000000f,
      0.77155617f,  0.85260112f,  1.00000000f,
      0.76876022f,  0.85071588f,  1.00000000f,
      0.76603147f,  0.84887402f,  1.00000000f,
      0.76336762f,  0.84707411f,  1.00000000f,
      0.76076645f,  0.84531479f,  1.00000000f,
      0.75822586f,  0.84359476f,  1.00000000f,
      0.75574383f,  0.84191277f,  1.00000000f,
      0.75331843f,  0.84026762f,  1.00000000f,
      0.75094780f,  0.83865816f,  1.00000000f,
      0.74863017f,  0.83708329f,  1.00000000f,
      0.74636386f,  0.83554194f,  1.00000000f,
      0.74414722f,  0.83403311f,  1.00000000f,
      0.74197871f,  0.83255582f,  1.00000000f,
      0.73985682f,  0.83110912f,  1.00000000f,
      0.73778012f,  0.82969211f,  1.00000000f,
      0.73574723f,  0.82830393f,  1.00000000f,
      0.73375683f,  0.82694373f,  1.00000000f,
      0.73180765f,  0.82561071f,  1.00000000f,
      0.72989845f,  0.82430410f,  1.00000000f,
      0.72802807f,  0.82302316f,  1.00000000f,
      0.72619537f,  0.82176715f,  1.00000000f,
      0.72439927f,  0.82053539f,  1.00000000f,
      0.72263872f,  0.81932722f,  1.00000000f,
      0.72091270f,  0.81814197f,  1.00000000f,
      0.71922025f,  0.81697905f,  1.00000000f,
      0.71756043f,  0.81583783f,  1.00000000f,
      0.71593234f,  0.81471775f,  1.00000000f,
      0.71433510f,  0.81361825f,  1.00000000f,
      0.71276788f,  0.81253878f,  1.00000000f,
      0.71122987f,  0.81147883f,  1.00000000f,
      0.70972029f,  0.81043789f,  1.00000000f,
      0.70823838f,  0.80941546f,  1.00000000f,
      0.70678342f,  0.80841109f,  1.00000000f,
      0.70535469f,  0.80742432f,  1.00000000f,
      0.70395153f,  0.80645469f,  1.00000000f,
      0.70257327f,  0.80550180f,  1.00000000f,
      0.70121928f,  0.80456522f,  1.00000000f,
      0.69988894f,  0.80364455f,  1.00000000f,
      0.69858167f,  0.80273941f,  1.00000000f,
      0.69729688f,  0.80184943f,  1.00000000f,
      0.69603402f,  0.80097423f,  1.00000000f,
      0.69479255f,  0.80011347f,  1.00000000f,
      0.69357196f,  0.79926681f,  1.00000000f,
      0.69237173f,  0.79843391f,  1.00000000f,
      0.69119138f,  0.79761446f,  1.00000000f, /* 15000K */
      0.69003044f,  0.79680814f,  1.00000000f,
      0.68888844f,  0.79601466f,  1.00000000f,
      0.68776494f,  0.79523371f,  1.00000000f,
      0.68665951f,  0.79446502f,  1.00000000f,
      0.68557173f,  0.79370830f,  1.00000000f,
      0.68450119f,  0.79296330f,  1.00000000f,
      0.68344751f,  0.79222975f,  1.00000000f,
      0.68241029f,  0.79150740f,  1.00000000f,
      0.68138918f,  0.79079600f,  1.00000000f,
      0.68038380f,  0.79009531f,  1.00000000f,
      0.67939381f,  0.78940511f,  1.00000000f,
      0.67841888f,  0.78872517f,  1.00000000f,
      0.67745866f,  0.78805526f,  1.00000000f,
      0.67651284f,  0.78739518f,  1.00000000f,
      0.67558112f,  0.78674472f,  1.00000000f,
      0.67466317f,  0.78610368f,  1.00000000f,
      0.67375872f,  0.78547186f,  1.00000000f,
      0.67286748f,  0.78484907f,  1.00000000f,
      0.67198916f,  0.78423512f,  1.00000000f,
      0.67112350f,  0.78362984f,  1.00000000f,
      0.67027024f,  0.78303305f,  1.00000000f,
      0.66942911f,  0.78244457f,  1.00000000f,
      0.66859988f,  0.78186425f,  1.00000000f,
      0.66778228f,  0.78129191f,  1.00000000f,
      0.66697610f,  0.78072740f,  1.00000000f,
      0.66618110f,  0.78017057f,  1.00000000f,
      0.66539706f,  0.77962127f,  1.00000000f,
      0.66462376f,  0.77907934f,  1.00000000f,
      0.66386098f,  0.77854465f,  1.00000000f,
      0.66310852f,  0.77801705f,  1.00000000f,
      0.66236618f,  0.77749642f,  1.00000000f,
      0.66163375f,  0.77698261f,  1.00000000f,
      0.66091106f,  0.77647551f,  1.00000000f,
      0.66019791f,  0.77597498f,  1.00000000f,
      0.65949412f,  0.77548090f,  1.00000000f,
      0.65879952f,  0.77499315f,  1.00000000f,
      0.65811392f,  0.77451161f,  1.00000000f,
      0.65743716f,  0.77403618f,  1.00000000f,
      0.65676908f,  0.77356673f,  1.00000000f,
      0.65610952f,  0.77310316f,  1.00000000f,
      0.65545831f,  0.77264537f,  1.00000000f,
      0.65481530f,  0.77219324f,  1.00000000f,
      0.65418036f,  0.77174669f,  1.00000000f,
      0.65355332f,  0.77130560f,  1.00000000f,
      0.65293404f,  0.77086988f,  1.00000000f,
      0.65232240f,  0.77043944f,  1.00000000f,
      0.65171824f,  0.77001419f,  1.00000000f,
      0.65112144f,  0.76959404f,  1.00000000f,
      0.65053187f,  0.76917889f,  1.00000000f,
      0.64994941f,  0.76876866f,  1.00000000f, /* 20000K */
      0.64937392f,  0.76836326f,  1.00000000f,
      0.64880528f,  0.76796263f,  1.00000000f,
      0.64824339f,  0.76756666f,  1.00000000f,
      0.64768812f,  0.76717529f,  1.00000000f,
      0.64713935f,  0.76678844f,  1.00000000f,
      0.64659699f,  0.76640603f,  1.00000000f,
      0.64606092f,  0.76602798f,  1.00000000f,
      0.64553103f,  0.76565424f,  1.00000000f,
      0.64500722f,  0.76528472f,  1.00000000f,
      0.64448939f,  0.76491935f,  1.00000000f,
      0.64397745f,  0.76455808f,  1.00000000f,
      0.64347129f,  0.76420082f,  1.00000000f,
      0.64297081f,  0.76384753f,  1.00000000f,
      0.64247594f,  0.76349813f,  1.00000000f,
      0.64198657f,  0.76315256f,  1.00000000f,
      0.64150261f,  0.76281076f,  1.00000000f,
      0.64102399f,  0.76247267f,  1.00000000f,
      0.64055061f,  0.76213824f,  1.00000000f,
      0.64008239f,  0.76180740f,  1.00000000f,
      0.63961926f,  0.76148010f,  1.00000000f,
      0.63916112f,  0.76115628f,  1.00000000f,
      0.63870790f,  0.76083590f,  1.00000000f,
      0.63825953f,  0.76051890f,  1.00000000f,
      0.63781592f,  0.76020522f,  1.00000000f,
      0.63737701f,  0.75989482f,  1.00000000f,
      0.63694273f,  0.75958764f,  1.00000000f,
      0.63651299f,  0.75928365f,  1.00000000f,
      0.63608774f,  0.75898278f,  1.00000000f,
      0.63566691f,  0.75868499f,  1.00000000f,
      0.63525042f,  0.75839025f,  1.00000000f,
      0.63483822f,  0.75809849f,  1.00000000f,
      0.63443023f,  0.75780969f,  1.00000000f,
      0.63402641f,  0.75752379f,  1.00000000f,
      0.63362667f,  0.75724075f,  1.00000000f,
      0.63323097f,  0.75696053f,  1.00000000f,
      0.63283925f,  0.75668310f,  1.00000000f,
      0.63245144f,  0.75640840f,  1.00000000f,
      0.63206749f,  0.75613641f,  1.00000000f,
      0.63168735f,  0.75586707f,  1.00000000f,
      0.63131096f,  0.75560036f,  1.00000000f,
      0.63093826f,  0.75533624f,  1.00000000f,
      0.63056920f,  0.75507467f,  1.00000000f,
      0.63020374f,  0.75481562f,  1.00000000f,
      0.62984181f,  0.75455904f,  1.00000000f,
      0.62948337f,  0.75430491f,  1.00000000f,
      0.62912838f,  0.75405319f,  1.00000000f,
      0.62877678f,  0.75380385f,  1.00000000f,
      0.62842852f,  0.75355685f,  1.00000000f,
      0.62808356f,  0.75331217f,  1.00000000f,
      0.62774186f,  0.75306977f,  1.00000000f, /* 25000K */
      0.62740336f,  0.75282962f,  1.00000000f  /* 25100K */
   };

   static void
      interpolate_color(float a, const float* c1, const float* c2, float* r, float* g, float* b)
   {

      *r = (1.0f - a) * c1[0] + a * c2[0];
      *g = (1.0f - a) * c1[1] + a * c2[1];
      *b = (1.0f - a) * c1[2] + a * c2[2];

   }


   //CLASS_DECL_AURA void black_body(float* r, float* g, float* b, ::u32 dwTemp)
   //{

   //   int temp_index = ((dwTemp - 1000) / 100) * 3;

   //   if (temp_index < 0)
   //   {

   //      temp_index = 0;

   //   }
   //   else if (temp_index > (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3)
   //   {

   //      temp_index = (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3;

   //   }

   //   float alpha = (dwTemp % 100) / 100.0f;

   //   interpolate_color(alpha, &g_fa_blackbody_color[temp_index], &g_fa_blackbody_color[temp_index + 3], r, g, b);

   //}


   ::estatus system::main_user_async(const ::routine & procedure, ::e_priority epriority)
   {

#ifdef _UWP

      return m_pimplMain->main_async(routine, epriority);

#else

      __throw(not_implemented);

      return ::error_interface_only;

#endif

   }


   //namespace command
   //{
   //
   //
   //   command::command()
   //   {
   //
   //      defer_create_mutex();
   //
   //   }


      //command::~command()
      //{

      //}

   ::type system::get_pane_tab_view_type_info()
   {

      return m_typePaneTabView;

   }


   void system::finalize()
   {

      if (m_pdraw2d)
      {

         m_pdraw2d->finalize();

         m_pdraw2d.release();

      }

      ::aqua::system::finalize();

   }

   __namespace_system_factory(system);

} // namespace aura


#ifdef __APPLE__

string get_bundle_app_library_name();

#endif


