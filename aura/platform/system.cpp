#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/gpu/gpu/_.h"
#include "aura/gpu/gpu/_gpu.h"
//#include "aqua/xml/_.h"
//#include "apex/platform/app_core.h"
//#include "acme/id.h"
//#include "aura/node/_node.h"
//#include "acme/platform/profiler.h"
#include "acme/platform/static_setup.h"
#include "acme/primitive/text/context.h"
//#include "acme/node/windows/registry.h"
#include "apex/platform/history.h"
#include "aura/gpu/gpu/_.h"
#include "aura/const/idpool.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"
//#ifdef _UWP
//#include "aura/node/universal_windows/directx_application.h"
//#include "aura/os/windows_common/draw2d_direct2d_global.h"
//#endif
#include "aura/graphics/draw2d/_draw2d.h"
//#include "acme/platform/system_impl.h"

int GetMainScreenRect(RECTANGLE_I32 * lprect);


#ifdef LINUX
const char * get_main_app_id();
#endif

//void ([a-z0-9_]+)_factory(::factory::factory * pfactory);

#ifdef CUBE
extern "C"
::acme::library * experience_get_new_library();
#endif


//#ifdef WINDOWS_DESKTOP
//#include <highlevelmonitorconfigurationapi.h>
//#endif
//

//void ___compile_test_sort_array_21304528734();

//void enum_display_monitors(::aura::system * psystem);

#ifdef WINDOWS_DESKTOP
CLASS_DECL_AURA __pointer(::user::interaction) create_system_message_window(::object * pobject);
#endif


#ifdef LINUX
#include <sys/time.h>
#endif

extern string_map < __pointer(::acme::library) > * g_pmapLibrary;


CLASS_DECL_AURA void __simple_tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


void os_post_quit();

//extern ::mutex * m_mutexLibrary;



#ifdef UNIT_TEST
void unit_test_primitive_var_aura_block();
#endif


void dappy(const ::string & psz);


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





   //class ::atom system::idEmpty;

   //system * system::g_p = nullptr;
   ::mutex * g_pmutexImage = nullptr;

   ::mutex * get_image_mutex()
   {

      return g_pmutexImage;

   }


   system::system()
   {

      m_bAvoidFirstResponder = false;


      m_bMessageThread = true;

      common_construct();

   }


   system::~system()
   {

      ::acme::del(g_pmutexImage);

      //#if !defined(WIN32)
      //
      //      if(m_pnode)
      //      {
      //
      //         m_pnode->os_post_quit();
      //
      //      }
      //      
      //#endif

   }


   void system::common_construct()
   {


      m_paurasystem = this;

      m_bSimpleMessageLoop = false;

      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;

      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

      ::factory::add_factory_item < ::aura::session, ::apex::session >();
      ::factory::add_factory_item < ::aura::application, ::application >();
      ::factory::add_factory_item < ::aura::idpool, ::acme::idpool >();
      ::factory::add_factory_item < ::user::user >();




   }


   void system::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::aqua::system::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      enable_trace_category(e_trace_category_windowing, true);

      enable_trace_category(e_trace_category_prodevian, false);
    
      g_pmutexImage = new ::mutex();

      m_bProdevianMouse = false;

      m_bSystemSynchronizedCursor = true;
      m_bSystemSynchronizedScreen = true;

      string strId;
      strId = "ca2log";

      m_pauracontext = this;

      initialize_log(strId);
      //{

      //   //xxdebug_box("Could not initialize log", "Failed to initialize log", 0);

      //   throw ::exception(error_failed, "failed to initialize log");

      //}

      //{

      //   bool bGlobalEnableStackTrace = true;

      //   ::file::path pathNoExceptionStackTrace = m_psystem->m_pacmedir->config() / "system/no_exception_stack_trace.txt";

      //   if (m_psystem->m_pacmefile->exists(pathNoExceptionStackTrace))
      //   {

      //      bGlobalEnableStackTrace = false;

      //   }

      //   ::exception::exception_enable_stack_trace(bGlobalEnableStackTrace);

      //}
 
      //([a-z0-9_]+)_factory(::factory_item::get_factory());

      //m_bGudoNetCache = true;

      //m_purldepartment = nullptr;

      m_durationAfterApplicationFirstRequest = 0_s;



      ::draw2d::static_initialize();

      ::factory::add_factory_item < ::draw2d::icon >();

    
//#ifdef WINDOWS_DESKTOP
//
//      m_uiWindowsTaskbarCreatedMessage = 0;
//
//#endif

      thread::s_bAllocReady = true;


      //return estatus;

   }


   void system::on_add_session(::apex::session* papexsession)
   {

      ::apex::system::on_add_session(papexsession);

      if (papexsession->m_iEdge == 0)
      {

         if (!m_paurasession)
         {

            m_paurasession = papexsession->m_paurasession;

         }

      }

      papexsession->m_paurasystem = this;

   }


   void system::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   {


   }


   string system::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   ::aura::estamira* system::estamira()
   {

      return m_pestamira ? m_pestamira->m_pauraestamira : nullptr;

   }


//   void system::run_system()
//   {
//
//      auto estatus = ::apex::system::run_system();
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


   //bool system::on_get_task_name(string& strTaskName)
   //{

   //   if (is_console_app())
   //   {

   //      return false;

   //   }

   //   return ::apex::system::on_get_task_name(strTaskName);

   //}



//   ::acme::library * system::get_library(const ::string & pszLibrary1, bool bOpenCa2)
//   {
//
//      synchronous_lock synchronouslock(m_mutexLibrary);
//
//      string strLibrary(pszLibrary1);
//
//      strLibrary.ends_eat_ci(".dll");
//      strLibrary.ends_eat_ci(".so");
//      strLibrary.ends_eat_ci(".dylib");
//      strLibrary.begins_eat_ci("lib");
//
//      auto & plibrary = m_mapLibrary[strLibrary];
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
////               if (!plibrary->open(pcontext->m_papexcontext->dir().ca2module() / pszLibrary))
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




   //class ::user::window_map & system::window_map()
   //{

   //   return *m_pwindowmap;

   //}


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

   //               applicationa.erase_at(i);

   //               continue;

   //            }
   //            else if (applicationa[i]->is_serviceable())
   //            {

   //               applicationa.erase_at(i);

   //               continue;

   //            }

   //         }
   //         catch (...)
   //         {

   //            applicationa.erase_at(i);

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


   //base_factory & system::factory_item()
   //{

   //   return *m_pfactory;

   //}


   //::datetime::department & system::datetime()
   //{

   //   return *m_pdatetime;

   //}

   
   void system::system_main()
   {

      //auto estatus =
      
      ::aqua::system::system_main();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = create_os_node();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (m_pnode)
      //{

      //   return m_pnode->start();

      //}

      //return ::success;

   }


   void system::on_start_system()
   {

      //auto estatus = 
      
      ::aqua::system::on_start_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = create_os_node();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (m_pnode)
      //{

      //   return m_pnode->start();

      //}

      //return ::success;

   }


   //::aura::str & system::str()
   //{

   //   return *m_puserstr;

   //}


   __pointer(::factory::factory) & system::node_factory()
   {

      auto & pfactory = factory("node", OPERATING_SYSTEM_NAME);

//#ifdef LINUX
//
//      auto edesktop = get_edesktop();
//
//      if (edesktop & ::user::e_desktop_kde)
//      {
//
//         estatus = ([a-z0-9_]+)_factory("desktop_environment", "kde");
//
//      }
//      else if (edesktop & ::user::e_desktop_gnome)
//      {
//
//         estatus = ([a-z0-9_]+)_factory("desktop_environment", "gnome");
//
//      }
//      else
//      {
//
//         estatus = ([a-z0-9_]+)_factory("desktop_environment", "gnome");
//
//         if (!estatus)
//         {
//
//            estatus = ([a-z0-9_]+)_factory("desktop_environment", "kde");
//
//         }
//
//      }
//
//#else
//
//      estatus = ([a-z0-9_]+)_factory("aura", "windows");
//
//#endif

      if (!pfactory)
      {

         output_debug_string("Fatal Error: Failed to do node factory_item exchange (system::([a-z0-9_]+)_factory).\n");

         return pfactory;

      }

      pfactory->merge_to_global_factory();

      return pfactory;

   }


   void system::process_init()
   {

      //auto estatus =
      
      ::apex::system::process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}



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

      //   output_error_message("Failed to allocate Session!!");

      //   return false;

      //}

      //m_papplicationStartup = get_new_application(get_session(), m_XstrAppId);

      //if (!m_papplicationStartup)
      //{

      //   output_error_message("Failed to allocate papplication!!");

      //   return false;

      //}

      //set_main_struct(*m_papplicationStartup);

      //string strAppId = m_papplicationStartup->m_XstrAppId;

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

      //pcreate->m_XstrAppId = strAppId;
      //TRACE("m_pcreate COMMENT END");

      //add_factory_item < ::database::field >();


      //if (is_true("show_application_information"))
      //{

      //   printf("%s", "\n\nApplication Information\n");
      //   output_debug_string("\n\nApplication Information\n");

      //   int iPid;

      //   iPid = ::get_current_process_id();

      //   printf("%s", ("Process PID: " + __string(iPid) + "\n").c_str());
      //   output_debug_string("Process PID: " + __string(iPid) + "\n");

      //}

//#ifdef LINUX
//
//      {
//
//         string str;
//
//         str = m_psystem->m_pacmedir->home() / ".profile";
//
//         if(!m_psystem->m_pacmefile->exists(str))
//         {
//
//            str = m_psystem->m_pacmedir->home() / ".bashrc";
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
//               iSize = maximum(iSize, 4096);
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

      //   throw ::exception(estatus);

      //}

      //m_pxml->initialize(this);

      //if (!m_pxml->init1())
      //{
      //   throw ::exception(::exception("failed to construct system m_pxml->init1()"));

      //}

      //if (!m_pxml->init())
      //{

      //   throw ::exception(::exception("failed to construct system m_pxml->initialize()"));

      //}

//      add_factory_item < ::create >();
//      //add_factory_item < application_bias >();
//      add_factory_item < command_line >();
//      add_factory_item < http::context >();
//      //add_factory_item < ::mutex >();
//      //add_factory_item < event >();
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
//                           auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->create("/ca2core");
//
//                  m_psystem->m_pacmefile->put_contents("/ca2core/teste.txt", str, str.length());
//                  */
//#endif
//
//#if 0
//
//         // Create authorization object
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
//            FORMATTED_TRACE("Error Creating Initial Authorization: %d", status);
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
//            FORMATTED_TRACE("Copy Rights Unsuccessful: %d", status);
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

      //   ERROR("failed to initialize file-system");

      //   return false;

      //}

      //if(!__compose(m_pdirsystem))
      //{

      //   ERROR("failed to initialize dir-system");

      //   return false;

      //}

      //INFORMATION("aura::session::process_init .3");

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

      //estatus = ::apex::context::initialize_context();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (!m_ptrace->process_init())
      //{

      //   WARNING("failed to process_init ::aura::log trace");

      //}

      ////output_debug_string("CommonAppData (matter) : " + pcontext->m_papexcontext->dir().commonappdata()  + "\n");
      ////output_debug_string("commonappdata (matter) : " + pcontext->m_papexcontext->dir().commonappdata() + "\n");
      ////output_debug_string("Common App Data (matter) : " + pcontext->m_papexcontext->dir().commonappdata() + "\n");
      ////output_debug_string("common app data (matter) : " + pcontext->m_papexcontext->dir().commonappdata() + "\n");

      //__compose_new(m_pcrypto);

      //if (!::is_set(m_pcrypto))
      //{

      //   return false;

      //}

      //return true;

   }

//
//   void system::get_time(struct timeval * point_i32)
//   {
//#ifdef _WIN32
//      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
//      GetSystemTimeAsFileTime(&ft);
//      u64 tt;
//      ::memcpy_dup(&tt, &ft, sizeof(tt));
//      tt /= 10; // make it usecs
//      point_i32->tv_sec = (long)tt / 1000000;
//      point_i32->tv_usec = (long)tt % 1000000;
//#else
//      gettimeofday(point, nullptr);
//#endif
//   }


   void system::initialize_draw2d()
   {

      ::e_status estatus = ::success;

      try
      {

         m_pfactoryDraw2d = draw2d_factory();

         //if (m_pfactoryDraw2d)
         {

            m_pfactoryDraw2d->merge_to_global_factory();

         }
         //else
         //{

         //   output_debug_string("ERROR: Failed to initialize draw2d library.");

         //   ///estatus = (const ::extended::status &) m_pfactoryDraw2d;

         //}

      }
      catch (...)
      {

         estatus = error_exception;

      }

      //if (!estatus)
      //{

      //   INFORMATION("draw2d_factory has failed.\n\nSome reasons:\n   - No draw2d library present;\n   - Failure to open any suitable draw2d library.");

      //   retru

      //   //return estatus;

      //}

      if (m_bImaging)
      {

         try
         {

            auto & pfactoryImaging = imaging_factory();

            if (pfactoryImaging)
            {

               pfactoryImaging->merge_to_global_factory();

            }
            else
            {

               WARNING("Failed to initialize imaging library.");

#if !defined(MOBILE_PLATFORM)

               output_error_message("Failed to initialize imaging library.");

#endif
               // Non fatal? Missing images (if using images)?
                           //bOk = false;

            }

         }
         catch (...)
         {

         }

      }

      auto psystem = get_system();

      synchronous_lock synchronouslock(&m_mutexLibrary4);

      ///estatus = 
      
      __construct(m_pdraw2d);

      //if (!estatus)
      //{

      //   INFORMATION("Couldn't construct new draw2d.");

      //   return false;

      //}

      //estatus = 
      
      m_pdraw2d->init1();

      //if(!estatus)
      //{

      //   INFORMATION("Couldn't initialize draw2d (init1).");

      //   return estatus;

      //}

      //if (::succeeded(estatus))
      //{

         ::factory::add_factory_item < ::draw2d::task_tool_item >(::e_task_tool_draw2d);

      //}

      //return estatus;

   }


   string system::draw2d_get_default_library_name()
   {

      string str;

      ::file::path path = m_psystem->m_pacmedir->config() / "system/draw2d.txt";

      str = m_psystem->m_pacmefile->as_string(path);

      if(str.has_char())
      {

         return "draw2d_" + str;

      }

      path = m_psystem->m_pacmedir->appdata() / "draw2d.txt";

      str = m_psystem->m_pacmefile->as_string(path);

      if(str.has_char())
      {

         return "draw2d_" + str;

      }

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


   __pointer(::factory::factory) & system::draw2d_factory()
   {

      string strLibrary;

      if (has_property("draw2d"))
      {

         strLibrary = payload("draw2d");

         //strDraw2d.trim();

         //if (strDraw2d.has_char())
         //{

         //   ::str::begins_eat_ci(strDraw2d, "draw2d_");

         //   ::str::begins_eat_ci(strDraw2d, "draw2d");

         //   strLibrary = "draw2d_" + strDraw2d;

         //}

      }

      ::e_status estatus;

      if (strLibrary.has_char())
      {

         auto & pfactoryDraw2d = factory("draw2d", strLibrary);

         //if(pfactoryDraw2d)

         if(pfactoryDraw2d)
         {

            return pfactoryDraw2d;

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

      auto & pfactoryDraw2d = factory("draw2d", strLibrary);

      if(pfactoryDraw2d)
      {

         return pfactoryDraw2d;

      }


#ifdef WINDOWS_DESKTOP


      if (strLibrary != "draw2d_gdiplus")
      {

         auto & pfactoryDraw2d = factory("draw2d", "gdiplus");

         if(pfactoryDraw2d)
         {

            return pfactoryDraw2d;

         }

      }


      if (strLibrary != "draw2d_direct2d")
      {

         auto & pfactoryDraw2d = factory("draw2d", "direct2d");

         if(pfactoryDraw2d)
         {

            return pfactoryDraw2d;

         }

      }


#endif

      if (strLibrary != "draw2d_cairo")
      {

         auto & pfactoryDraw2d = factory("draw2d", "cairo");

         if(pfactoryDraw2d)
         {

            return pfactoryDraw2d;

         }

      }

      //output_debug_string("No draw2d pluging available!!.");
      if (pfactoryDraw2d)
      {

         return pfactoryDraw2d;

      }

      throw(error_not_found, "No draw2d plugin available");

   //destroy:

   //   PFN_factory ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >("([a-z0-9_]+)_factory");

   //   if (([a-z0-9_]+)_factory == nullptr)
   //   {

   //      return false;

   //   }

   //   ([a-z0-9_]+)_factory(::factory::factory * pfactory);

   //   return true;

//#endif

   }


   __pointer(::factory::factory) & system::imaging_factory()
   {

      string strLibrary;

      if (has_property("imaging"))
      {

         string strImaging;
         
         strImaging = payload("imaging");

         strImaging.trim();

         if (strImaging.has_char())
         {

            ::str::ends_eat_ci(strImaging, "_imaging");

            ::str::ends_eat_ci(strImaging, "imaging");

            ::str::begins_eat_ci(strImaging, "imaging_");

            ::str::begins_eat_ci(strImaging, "imaging");

         }

      }

      ::e_status estatus = ::error_failed;

      if (strLibrary.has_char())
      {

         auto & pfactoryImaging = factory("imaging", strLibrary);

         if(pfactoryImaging)
         {

            return pfactoryImaging;

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

      auto & pfactoryImaging = factory("imaging", strLibrary);

      if(pfactoryImaging)
      {

         return pfactoryImaging;

      }

#ifdef WINDOWS_DESKTOP

      if (strLibrary != "imaging_wic")
      {

         auto & pfactoryImaging = factory("imaging", "wic");

         if(pfactoryImaging)
         {

            return pfactoryImaging;

         }

      }

#endif

      if (strLibrary != "imaging_freeimage")
      {

         auto & pfactoryImaging = factory("imaging", "freeimage");

         if(pfactoryImaging)
         {

            return pfactoryImaging;

         }

      }

      if (!pfactoryImaging)
      {

         throw ::exception(error_resource, "No imaging pluging available!!.");

      }

      return pfactoryImaging;

//   destroy:
//
//      PFN_factory ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >("([a-z0-9_]+)_factory");
//
//      if (([a-z0-9_]+)_factory == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ([a-z0-9_]+)_factory(::factory::factory * pfactory);
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


   void system::init_thread()
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


   void system::init()
   {

      m_durationHeartBeat.Now();

      __pointer(::aura::session) psession = get_session();

      if (has_property("save_processing"))
      {

         psession->m_paurasession->savings().save(::e_resource_processing);

      }

      if (has_property("save_blur_back"))
      {

         psession->m_paurasession->savings().save(::e_resource_blur_background);

      }

      if (has_property("save_transparent_back"))
      {

         psession->m_paurasession->savings().save(::e_resource_translucent_background);

      }

      if (::is_set(m_pdraw2d))
      {

         m_pdraw2d->init();

         //if (!m_pdraw2d->init())
 /*        {

            return false;

         }*/

      }

      //return true;

   }


   void system::init1()
   {
//
//#ifdef _DEBUG
//
//      ___compile_test_sort_array_21304528734();
//
//#endif

      //auto estatus = __compose_new(m_puserstr);

      //if (!m_puserstr || !estatus)
      //{

      //   return estatus;

      //}

      //auto estatus = 
      
      ::apex::system::init1();

      //if (!estatus)
      //{

      //   return estatus;


      //}


      //auto psession = get_session();

      //if (psession->m_ptextcontext)
      //{

      //   psession->m_ptextcontext->defer_ok(m_puserstr);

      //}

      //throw ::exception(todo("filehandler"));

      //estatus = __compose_new(m_pfilehandler);

      //if (!estatus)
      //{

      //   return estatus;

      //}

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
      //         ::file::path pathSide = pcontext->m_papexcontext->side_get_matter_path("app/_matter/main");
      //
      //         ::file::path pathLocal = local_get_matter_path("app/_matter/main");
      //
      //         bool bFileSystemMatter =          auto psystem = m_psystem;
//
//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->is(pathSide) ||          auto psystem = m_psystem;
//
//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->is(pathLocal);
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
      //      INFORMATION("start");
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      if (m_emessageWindowsTaskbarCreatedMessage == 0)
      //      {
      //
      //         m_emessageWindowsTaskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
      //
      //      }
      //
      //#endif

      ::acme::profiler::initialize();

      //#ifdef LINUX
      //
      //      ::user::g_defer_init();
      //
      //#endif // LINUX

      INFORMATION("success");

//      enum_display_monitors();

      //return true;

   }


   //void system::post_creation_requests()
   //{

   //   //while(auto pcreate = get_command()->get_create())
   //   while (auto pcreate = get_create())
   //   {

   //      do_request(pcreate);

   //   }

   //   return true;

   //}


   void system::inline_init()
   {

      //::e_status estatus =
      
      ::aqua::system::inline_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::inline_term()
   {

      //::e_status estatus = 
      
      ::aqua::system::inline_term();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::term()
   {

      ::aqua::system::term();

      __release(m_phistory);

   }


   void system::system_prep()
   {

      //auto estatus = 
      
      ::aqua::system::system_prep();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      ////os_init_windowing();

      //return ::success;

   }


   void system::term1()
   {

   }


   void system::term2()
   {

      //::aqua::system::term2();

      //for (int i = 0; i < m_serviceptra.get_size(); i++)
      //{

      //   try
      //   {

      //      m_serviceptra[i]->Stop(0);

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      //for (int i = 0; i < m_serviceptra.get_size(); i++)
      //{

      //   try
      //   {

      //      m_serviceptra[i]->Stop((5000) * 2);

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      //m_serviceptra.erase_all();

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

         m_mapImage.erase_all();

      }
      catch (...)
      {

      }


      //try
      //{

      //   auto psystem = m_psystem->m_paurasystem;

      //   synchronous_lock synchronouslock(&m_mutexLibrary2);

      //   if (m_mapLibrary["draw2d"].is_set() && m_mapLibrary["draw2d"]->is_opened())
      //   {

      //      if (m_pDraw2dFactoryExchange != nullptr)
      //      {

      //         delete m_pDraw2dFactoryExchange;

      //         m_pDraw2dFactoryExchange = nullptr;

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}


      ::aqua::system::term2();

   }


   void system::thread_loop()
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

      //try
      //{

         term_system();

      //}
      //catch(...)
      //{

      //}


      //try
      //{

         ::thread::term_thread();

      //}
      //catch(...)
      //{

      //}

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


//   void system::TermSystem()
//   {
//
//      ::aqua::system::TermSystem();
//
//      auto pnode = node();
//
//      pnode->node_post_quit();
//
//#ifdef LINUX
//
//      // dirty
//      // (forcing premature gtk event loop (main loop) quitting)
//      // the "most elegant" is to let just ~system (::aura::system destructor)...
//      // ... do this call, but this requires all references to ::aura::system ...
//      // ... to be released. This is a bit of an ideal situation that may not ...
//      // ... always happen as the wish the program finishes when it is closed ...
//      //os_post_quit();
//
//#elif defined(__APPLE__)
//
//      os_post_quit();
//
//#endif
//
//   }


   void system::process_term()
   {

      //::aura::application::process_term();



//      try
//      {
//
//         m_mapAppLibrary.erase_all();
//
//      }
//      catch (...)
//      {
//
//      }

   }


   //::u32 system::os_post_to_all_threads(const ::atom & atom,wparam wparam,lparam lparam)
   //{

   //   post_to_all_threads(atom, wparam, lparam);

   //   return 0;

   //}



   //bool system::is_system() const
   //{

   //   return true;

   //}


   //i32 system::_001OnDebugReport(i32 i1, const ::string & psz1,i32 i2, const ::string & psz2, const ::string & psz3,va_list args)
   //{

   //   return _debug_logging_report(i1,psz1,i2,psz2,psz3,args);

   //}


//   i32 system::_debug_logging_report(i32 iReportType, const ::string & pszFileName, i32 iLineNumber, const ::string & pszModuleName, const ::string & pszFormat,va_list list)
//   {
//
//      if(!m_ptrace || !m_ptrace->m_bExtendedLog)
//      {
//
//         return ::apex::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);
//
//      }
//
//      string str;
//
//      if(pszFileName != nullptr || pszModuleName != nullptr)
//      {
//
//         string_array stra;
//
//         if (pszFileName != nullptr)
//         {
//
//            stra.add(pszFileName);
//
//         }
//
//         if (pszModuleName != nullptr)
//         {
//
//            stra.add(pszFileName);
//
//         }
//
//         str += stra.implode(", ");
//
//         str += ": ";
//
//      }
//
//      string str2;
//
//      if(pszFormat != nullptr)
//      {
//
////         if(list != nullptr)
//         {
//
//            str2.format(pszFormat,list);
//
//         }
//         //     else
//         {
//
//            //          str2 = pszFormat;
//
//         }
//
//      }
//
//      str = str + str2;
//
//      string strPrint(str);
//
//      strPrint.replace("%","%%");
//
//      if(m_ptrace)
//      {
//
//         m_ptrace->print(strPrint);
//
//      }
//
//      if(iReportType == _CRT_ASSERT)
//      {
//
//         return 1;
//
//      }
//      else
//      {
//
//         return 0;
//
//      }
//
//   }




   //bool system::assert_failed_line(const ::string & pszFileName,i32 iLine)

   //{
   //   __UNREFERENCED_PARAMETER(pszFileName);

   //   __UNREFERENCED_PARAMETER(iLine);
   //   return false;
   //}


   //bool system::on_assert_failed_line(const ::string & pszFileName,i32 iLine)

   //{
   //   __UNREFERENCED_PARAMETER(pszFileName);

   //   __UNREFERENCED_PARAMETER(iLine);
   //   return true;
   //}


   //void system::__set_thread_on()
   //{

   //   ::thread::__set_thread_on();

   //}


//   ::mutex * system::get_openweather_city_mutex()
//   {
//
//      synchronous_lock synchronouslock(mutex());
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
   //   //      strMessage += __type_name(pobject);

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


   //__pointer(regex) system::create_regular_expression(const ::string & pszStyle, const string& str)
   //{

   //   return nullptr;

   //}


   //__pointer(regex_context) system::create_regular_expression_context(const ::string & pszStyle, int iCount)
   //{

   //   return nullptr;

   //}


   //::apex::session * system::session(index iEdge)
   //{

   //   auto ppair = m_sessionmap.plookup(iEdge);

   //   if (!ppair)
   //   {

   //      return nullptr;

   //   }

   //   return ppair->element2();

   //}


   //::aura::os & system::os()
   //{

   //   return *m_spos;

   //}


//__pointer_array(::aura::session) & system::basesessionptra()
//{

//   return m_basesessionptra;

//}


   //::operating_system::department & system::process()
   //{

   //   return *m_pprocess;

   //}


   //void system::initialize_log(const ::string & pszId)
   //{

   //   if (m_ptrace)
   //   {

   //      return ::success_none;

   //   }

   //   auto estatus = __compose_new(m_ptrace);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   m_ptrace->set_extended_log();

   //   estatus = m_ptrace->initialize_apex_log(e_trace_level_warning, pszId);

   //   if(!estatus)
   //   {

   //      __release(m_ptrace);

   //      return estatus;

   //   }

   //   return estatus;

   //}





//   void system::appa_load_string_table()
//   {
//
//      //retry_single_lock rsl(mutex(),::duration(100),::duration(100));
//
////      for(i32 i = 0; i < appptra().get_size(); i++)
//      //    {
//      //     ::aura::application * papp = appptra()(i);
//      //   papp->load_string_table();
//      //}
//
//   }


//   void system::appa_set_locale(const ::string & pszLocale, const ::action_context & context)
//   {
//
//      //retry_single_lock rsl(mutex(),::duration(100),::duration(100));
//
//      single_lock sl(mutex());
//
//      sl.wait(10_s);
//
////      for(i32 i = 0; i < appptra().get_size(); i++)
////     {
//      //       ::aura::application * papp = appptra()(i);
//      //       papp->set_locale(pszLocale,context);
//      //    }
//
//   }


//   void system::appa_set_schema(const ::string & pszStyle, const ::action_context & context)
//   {
//
//      //retry_single_lock rsl(mutex(),::duration(100),::duration(100));
//
//      single_lock sl(mutex());
//
//      sl.wait(10_s);
//
////      for(i32 i = 0; i < appptra().get_size(); i++)
//      //    {
//      //       ::aura::application * papp = appptra()(i);
//      //       papp->set_schema(pszStyle,context);
//      //    }
//
//   }



//   bool system::assert_running_global(const ::string & pszAppName, const ::string & pszId)
//   {
//      if(string(pszId).has_char())
//      {
//         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_id_mutex_name(pszAppName, pszId));
//         ::mutex * pmutex = ::mutex::open_mutex(get_global_id_mutex_name(pszAppName,pszId));
//         if(pmutex == nullptr)
//         {
//
//            string strApp = pszAppName;
//            strApp += "app.exe";
//
//            string strParameters;
//            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";
//
//#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__APPLE__)
//
//            auto plauncher = __create_new<::apex::shell_launcher>();
//
//            auto pcontext = get_context();
//            
//            plauncher->setup(nullptr, nullptr, pcontext->m_papexcontext->dir().module() / strApp, strParameters, nullptr, e_display_normal);
//
//            plauncher->launch();
//
//#else
//
//            throw ::exception(todo);
//
//#endif
//
//            return false;
//         }
//         else
//         {
//            delete pmutex;
//         }
//         return true;
//      }
//      else
//      {
//         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_mutex_name(pszAppName));
//         ::mutex * pmutex = ::mutex::open_mutex(get_global_mutex_name(pszAppName));
//         if(pmutex == nullptr)
//         {
//            string strApp = pszAppName;
//            strApp += "app.exe";
//
//#if defined(_UWP)
//
//            throw ::exception(todo);
//
//#else
//            auto plauncher = __create_new<::apex::shell_launcher>();
//
//            auto pcontext = get_context();
//
//            plauncher->setup(nullptr,nullptr,pcontext->m_papexcontext->dir().module()/strApp,nullptr,nullptr, e_display_normal);
//
//            plauncher->launch();
//
//#endif
//
//            return false;
//         }
//         else
//         {
//            //::CloseHandle(h);
//            delete pmutex;
//         }
//         return true;
//      }
//   }

//   bool system::assert_running_local(const ::string & pszAppName, const ::string & pszId)
//   {
//      string strAppName(pszAppName);
//      string strId(pszId);
//      if(strId.has_char())
//      {
//         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_id_mutex_name(pszAppName, strId));
//         ::mutex * pmutex = ::mutex::open_mutex(get_local_id_mutex_name(pszAppName,strId));
//         if(pmutex == nullptr)
//         {
//            string strApp;
//            strApp = "app.exe";
//            string strParameters;
//            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";
//
//#ifdef _UWP
//
//            throw ::exception(todo);
//
//#else
//
//            auto plauncher = __create_new<::apex::shell_launcher>();
//
//            auto pcontext = get_context();
//
//            plauncher->setup(nullptr,nullptr, pcontext->m_papexcontext->dir().ca2module() / strApp,strParameters,nullptr, e_display_normal);
//
//            plauncher->launch();
//
//#endif
//
//            return false;
//         }
//         else
//         {
//            //::CloseHandle(h);
//            delete pmutex;
//         }
//         return true;
//      }
//      else
//      {
//         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_mutex_name(pszAppName));
//         ::mutex * pmutex = ::mutex::open_mutex(get_local_mutex_name(pszAppName));
//         if(pmutex == nullptr)
//         {
//            string strApp;
//            strApp = "app.exe";
//            string strParameters;
//            strParameters = ": app=" + strAppName;
//
//#ifdef _UWP
//
//            throw ::exception(todo);
//
//#else
//
//            auto plauncher = __create_new<::apex::shell_launcher>();
//
//            auto pcontext = get_context();
//
//            plauncher->setup(nullptr,nullptr, pcontext->m_papexcontext->dir().ca2module() / strApp,strParameters,nullptr, e_display_normal);
//
//            plauncher->launch();
//
//#endif
//
//            return false;
//         }
//         else
//         {
//            //::CloseHandle(h);
//            delete pmutex;
//         }
//         return true;
//      }
//   }










   //::count system::get_application_count()
   //{

   //   ::count c = 0;

   //   //try
   //   //{

   //   //   for(index iBaseSession = 0; iBaseSession < m_basesessionptra.get_count(); iBaseSession++)
   //   //   {

   //   //      try
   //   //      {

   //   //         c += m_basesessionptra[iBaseSession]->appptra().get_count();

   //   //      }
   //   //      catch(...)
   //   //      {

   //   //      }

   //   //   }

   //   //}
   //   //catch(...)
   //   //{

   //   //}

   //   return c;

   //}


   //string system::crypto_md5_text(const ::string & str)
   //{

   //   throw ::interface_only();

   //   return "";

   //}


   //void system::install_progress_add_up(int iAddUp)
   //{

   //   __UNREFERENCED_PARAMETER(iAddUp);

   //}


   //void system::create_session(index iEdge)
   //{

   //   if (session(iEdge))
   //   {

   //      return ::success;

   //   }

   //   auto psession = on_create_session(iEdge);

   //   if (!psession)
   //   {

   //      return false;

   //   }

   //   session_add(iEdge, psession);

   //   return ::success;

   //}


   //__pointer(::apex::session) system::on_create_session(index iEdge)
   //{

   //   return ::aqua::system::on_create_session(iEdge);

   //}


//   string system::get_system_configuration()
//   {
//
//#ifndef CA2_PLATFORM_VERSION
//
//#error "CA2_PLATFORM_VERSION not defined"
//
//#endif
//
//#ifndef CA2_BASIS
//
//#error "CA2_BASIS not defined"
//
//#endif
//
//#ifndef CA2_STAGE
//
//#error "CA2_STAGE not defined"
//
//#endif
//
//#if CA2_PLATFORM_VERSION == CA2_BASIS
//
//      return "basis";
//
////#pragma message "CA2_PLATFORM_VERSION is CA2_BASIS"
//
//#elif CA2_PLATFORM_VERSION == CA2_STAGE
//
//      return "stage";
//
////#pragma message "CA2_PLATFORM_VERSION is CA2_STAGE"
//
//#else
//
//#error "CA2_PLATFORM_VERSION has unsupported definition"
//
//#endif
//
//   }


//   string system::get_system_platform()
//   {
//
//#ifdef X86
//
//      return "x86";
//
//#else
//
//      return "x64";
//
//#endif
//
//   }




   //void system::on_request(::create * pcreate)
   //{

   //   ::apex::session * psession = session();

   //   if(psession == nullptr)
   //   {

   //      return;

   //   }

   //   FORMATTED_INFORMATION("%s", ("::aura::system::on_request session = " + string(__type_name(psession)) + "("+__string((iptr) psession)+")\n\n").c_str());

   //   psession->do_request(pcreate);

   //}


   //::file::path system::local_get_matter_path()
   //{

   //   return m_psystem->m_pacmedir->ca2roaming() / "appmatter";

   //}


//   ::file::path system::local_get_matter_path(string strMatter)
//   {
//
//#ifdef _UWP
//
//      return "";
//
//#else
//
//      return local_get_matter_path() / strMatter;
//
//#endif
//
//   }


   //::file::path system::local_get_matter_cache_path()
   //{

   //   return m_psystem->m_pacmedir->ca2roaming() / "cache/appmatter";

   //}


   //::file::path system::local_get_matter_cache_path(string strMatter)
   //{

   //   return local_get_matter_cache_path() / strMatter;

   //}


//   bool system::find_applications_from_cache()
//   {
//
//      return false;
//
////      on_start_find_applications_from_cache();
////
////      if(has_property("install"))
////         return true;
////
////      file_pointer pfile = pcontext->m_papexcontext->file().get_file(pcontext->m_papexcontext->dir().appdata() / "applibcache.bin",::file::e_open_binary | ::file::e_open_read);
////
////      if(!pfile)
////         return false;
////
////      ::binary_stream is(pfile);
////
////      is >> m_mapAppLibrary;
////
////      on_end_find_applications_from_cache(is);
////
////      return true;
//
//   }


//   bool system::find_applications_to_cache(bool bSave)
//   {
//
//      return true;
//
//#if defined(CUBE) || defined(ANDROID)
//      return true;
//#endif
//
//      /*      m_spfilehandler(new ::aura::filehandler::handler(this));*/
//
////      m_mapAppLibrary.erase_all();
////
////      string strLibraryId;
////
////      ::file::listing straTitle(this);
////
////      ::file::path pathCa2Module = pcontext->m_papexcontext->dir().ca2module();
////
////      ::output_debug_string("\n\n::aura::system::find_applications_to_cache\n\n");
////
////      ::output_debug_string("ca2 module folder : " + pathCa2Module);
////
////      ::output_debug_string("\n\n\n");
////
////      straTitle.ls_pattern(pathCa2Module, { "*.*" });
////
////      for(i32 i = 0; i < straTitle.get_count(); i++)
////      {
////
////         strLibraryId = straTitle[i];
////
////
////         if(::str::ends_eat_ci(strLibraryId,".dll")
////               || ::str::ends_eat_ci(strLibraryId,".so")
////               || ::str::ends_eat_ci(strLibraryId,".dylib"))
////         {
////
////            if(::str::begins_ci(strLibraryId,"libdraw2d_")
////                  || ::str::begins_ci(strLibraryId,"libbase"))
////            {
////               continue;
////            }
////
////            ::output_debug_string("library("+__string(i)+") : " + strLibraryId+"\n\n");
////
////            map_application_library(strLibraryId);
////
////         }
////
////      }
////
////      if(!bSave)
////         return true;
////
////      file_pointer file;
////
////      try
////      {
////
////         file = psession->file().get_file(pcontext->m_papexcontext->dir().appdata() / "applibcache.bin",::file::e_open_defer_create_directory | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_write);
////
////      }
////      catch(::exception &)
////      {
////
////         return false;
////
////      }
////
////      stream os(file);
////
////      os << m_mapAppLibrary;
////
////      on_end_find_applications_to_cache(os);
////
////      return true;
//
//   }


//   bool system::map_application_library(const ::string & pszLibrary)
//   {
//
//      ::acme::library library;
//
//      library.initialize_apex_library(this, 0);
//
//      if(!strcmp(pszLibrary,"app_core_rdpclient"))
//      {
//         TRACE("reach");
//      }
//
//      if(!ansi_compare_ci(pszLibrary, "app_core_hellomultiverse"))
//      {
//         TRACE("reach app_core_hellomultiverse");
//      }
//
//      if(!ansi_compare_ci(pszLibrary, "experience_lite"))
//      {
//         TRACE("reach experience_lite");
//      }
//
//      if(!ansi_compare_ci(pszLibrary, "app_core_hellomultiverse"))
//      {
//         TRACE("reach app_core_hellomultiverse");
//      }
//
//      if(!library.open(pszLibrary, true))
//      {
//         ::output_debug_string("::system::map_application_library Failed to open library :" + string(pszLibrary) + "\n\n");
//         return false;
//      }
//
//      if(!library.open_ca2_library())
//      {
//
//         ::output_debug_string("::system::map_application_library open_ca2_library(2) Failed :" + string(pszLibrary) + "\n\n");
//
//         return false;
//
//      }
//
//      on_map_application_library(library);
//
//      string_array stra;
//
//      string strRoot = library.get_root();
//
//      library.get_app_list(stra);
//
//      if(stra.get_count() <= 0)
//         return false;
//
//      strRoot += "/";
//
//      if(stra.get_count() == 1)
//      {
//
//         m_mapAppLibrary.set_at(strRoot + stra[0],pszLibrary);
//
//      }
//
//      string strLibrary = ::file::path(pszLibrary).title();
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//
//      if(strLibrary == "libbase")
//      {
//
//         strLibrary = "base";
//
//      }
//      else if(!::str::begins_eat(strLibrary,"libbase"))
//      {
//
//         ::str::begins_eat(strLibrary,"lib");
//
//      }
//
//#endif
//
//      string strPrefix = strRoot;
//
//      strPrefix.replace("-","_");
//
//      strPrefix.replace("/","_");
//
//      ::str::begins_eat_ci(strLibrary,strPrefix);
//
//      strRoot += strLibrary;
//
//      strRoot += "/";
//
//      for(i32 i = 0; i < stra.get_count(); i++)
//      {
//
//         m_mapAppLibrary.set_at(strRoot + stra[i],pszLibrary);
//
//      }
//
//      return true;
//
//   }


   //void system::do_request(::create * pcreate)
   //{

   //   if (pcreate->m_ecommand == ::command_check_exit)
   //   {

   //      return ::success;

   //   }

   //   return ::thread::do_request(pcreate);

   //}




   //string system::url_encode(const ::string & str)
   //{

   //   //throw ::interface_only();

   //   return url_encode(str);

   //}

#ifdef ANDROID

   bool system::android_set_user_wallpaper(string strUrl)
   {

      oslocal()->m_strSetUserWallpaper = strUrl;

      return true;

   }

   bool system::android_get_user_wallpaper(string & strUrl)
   {

      ::oslocal()->m_bGetUserWallpaper = true;

      for(int i = 0; i < 10; i++)
      {

         if (!::oslocal()->m_bGetUserWallpaper)
         {


         }

         sleep(50_ms);

      }

      strUrl = ::oslocal()->m_strGetUserWallpaper;

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


   //bool system::defer_accumulate_on_open_file(string_array stra, string strExtra)
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   m_durationCommandLineLast.Now();

   //   m_iCommandLineDelay = 1000;

   //   index iIndex = stra.find_first(":");

   //   if(iIndex >= 0)
   //   {

   //      if(iIndex > 0)
   //      {

   //         m_straCommandLineAccumul.add(stra.slice(0, iIndex));

   //      }

   //      m_straCommandLineExtra.add(stra.slice(iIndex));

   //   }
   //   else
   //   {

   //      if(m_straCommandLineExtra.has_elements())
   //      {

   //         m_straCommandLineExtra.add(stra);

   //      }
   //      else
   //      {

   //         m_straCommandLineAccumul.add(stra);

   //      }

   //   }

   //   auto psession = get_session();

   //   auto appptra = psession->get_applicationa();

   //   ::application * papp = nullptr;

   //   appptra.predicate_erase([](auto & papp)
   //   {

   //      return papp->is_system() || papp->is_session();

   //   });

   //   if(appptra.has_elements())
   //   {

   //      papp = appptra[0];

   //   }

   //   if(papp != nullptr)
   //   {

   //      __pointer(::create) pcreate(e_create_new);

   //      merge_accumulated_on_open_file(pcreate);

   //      papp->post_object(e_message_system, e_system_message_create, pcreate);

   //   }

   //   return true;

   //}


   //bool system::on_application_menu_action(const ::string & pszCommand)
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   auto psession = get_session();

   //   auto applicationa = psession->m_applicationa;

   //   synchronouslock.unlock();

   //   for(auto & papp : applicationa)
   //   {

   //      ASSERT(papp != this);

   //      if(papp == this)
   //      {

   //         continue;

   //      }

   //      if(papp->on_application_menu_action(pszCommand))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   //bool system::merge_accumulated_on_open_file(::create * pcreate)
   //{

   //   if(m_straCommandLineAccumul.is_empty())
   //   {

   //      return true;

   //   }

   //   string_array straAccumul = m_straCommandLineAccumul;

   //   string_array straExtra = m_straCommandLineExtra;

   //   m_straCommandLineAccumul.erase_all();

   //   m_straCommandLineExtra.erase_all();

   //   command_line_pointer line(e_create_new);

   //   string strExtra = straExtra.implode(" ");

   //   if(straAccumul.is_empty())
   //   {

   //      line->_001ParseCommandFork("app.exe : open_default " + strExtra);

   //   }
   //   else
   //   {

   //      string strParam = straAccumul.surround_and_implode(" ", "\"", "\"");

   //      line->_001ParseCommandFork("app.exe " + strParam + " " + ::str::has_char(strExtra, " : "));

   //   }

   //   if(pcreate->m_pcommandline.is_null())
   //   {

   //      pcreate->m_pcommandline = line;

   //   }
   //   else if(line->m_ecommand == command_line::command_file_open)
   //   {

   //      pcreate->m_pcommandline->m_varFile.stra().add_unique_ci(line->m_varFile.stra());

   //      pcreate->m_pcommandline->m_ecommand = command_line::command_file_open;

   //   }
   //   else if(line->m_ecommand == command_line::command_application_start)
   //   {

   //      pcreate->m_pcommandline->m_varFile.stra().add(line->m_varFile.stra());

   //      pcreate->m_pcommandline->m_ecommand = command_line::command_application_start;

   //   }

   //   return true;

   //}


   //bool system::on_open_file(::payload payloadFile, string strExtra)
   //{

   //   auto psession = get_session();

   //   auto applicationa = psession->get_applicationa();

   //   ::application * papp = nullptr;

   //   if(applicationa.get_size() > 0)
   //   {

   //      papp = applicationa[0];

   //   }
   //   else
   //   {

   //      return false;

   //   }

   //   if(papp != nullptr)
   //   {

   //      if(payloadFile.is_empty())
   //      {

   //         papp->request({"app.exe : open_default " + strExtra});

   //      }
   //      else
   //      {

   //         papp->request({"app.exe \"" + payloadFile.get_file_path() + "\" " + ::str::has_char(strExtra, " : ")});

   //      }

   //      return true;

   //   }

   //   return false;

   //}




   // bool system::initialize_native_window1()
   // {

   //    return true;

   // }

// #ifndef APPLE_IOS
//    void * system::initialize_native_window2(const ::rectangle_i32 & rectangle)

//    {

//       return nullptr;

//    }
// #endif

//#ifndef ANDROID
//
//   void system::on_os_text(e_os_text etext, string strText)
//   {
//
//
//   }
//
//#endif

//#ifdef _UWP
//
//
//
//   CLASS_DECL_AURA bool get_window_rect(::aura::system_window ^ pwindow, RECTANGLE_F64 * prectangle)
//
//   {
//
//      ::winrt::Windows::Foundation::Rect rectangle = pwindow->get_window_rect();
//
//      prectangle->left = rectangle.X;
//
//      prectangle->top = rectangle.Y;
//
//      prectangle->right = prectangle->left + rectangle.Width;
//
//      prectangle->bottom = prectangle->top + rectangle.Height;
//
//
//      return true;
//   }
//
//
//   CLASS_DECL_AURA bool get_window_rect(::aura::system_window ^ pwindow, RECTANGLE_I32 * prectangle)
//   {
//
//      ::rectangle_f64 rectangle;
//
//      if (!get_window_rect(pwindow, (RECTANGLE_F64*)rectangle_i32))
//      {
//
//         return false;
//
//      }
//
//      ::copy(prectangle, rectangle);
//
//      return true;
//
//   }
//
//
//#endif



   //::user::interaction_impl * system::impl_from_handle(void * pdata)
   //{

   //   return oswindow_interaction_impl((oswindow)pdata);

   //}

   //::user::interaction * system::ui_from_handle(void * pdata)
   //{

   //   ::user::interaction_impl * pimpl = impl_from_handle(pdata);

   //   if (pimpl == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   try
   //   {

   //      return pimpl->m_puserinteraction;

   //   }
   //   catch (...)
   //   {

   //      throw ::exception(resource_exception("not good window anymore"));

   //   }

   //   return nullptr;

   //}


//   index system::get_main_monitor(RECTANGLE_I32 * prectangle)
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
//      if (prectangle != nullptr)
//
//      {
//
//         get_monitor_rectangle(iMainMonitor, prectangle);
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

      synchronous_lock synchronouslock(mutex());

      return m_rectangleaMonitor.get_count();

#else

      return 1;

#endif

   }*/


//   bool system::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
//   {
//
//#if MOBILE_PLATFORM
//
//      //get_session()->m_puserinteractionHost->get_window_rect(prectangle);
//
//      GetMainScreenRect(prectangle);
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
//      *prectangle = m_monitorinfoa[iMonitor].rcMonitor;
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
//      synchronous_lock synchronouslock(mutex());
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      *prectangle = m_rectangleaMonitor[iMonitor];
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
//      GetScreenRect(prectangle, (int) iMonitor);
//
//
//#else
//
//      prectangle->left = 0;
//
//      prectangle->top = 0;
//
//      prectangle->right = oslocal().m_iScreenWidth;
//
//      prectangle->bottom = oslocal().m_iScreenHeight;
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
//   bool system::get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle)
//
//   {
//
//      return get_monitor_rectangle(iMonitor, prectangle);
//
//
//   }
//
//
//   index system::get_main_workspace(RECTANGLE_I32 * prectangle)
//
//   {
//
//      index iMainWorkspace = 0;
//
//#ifdef WINDOWS_DESKTOP
//
//      HMONITOR hworkspacePrimary = GetPrimaryMonitorHandle();
//
//      for (index iWorkspace = 0; iWorkspace < get_workspace_count(); iWorkspace++)
//      {
//
//         if (m_hmonitora[iWorkspace] == hworkspacePrimary)
//         {
//
//            iMainWorkspace = iWorkspace;
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
//      if (prectangle != nullptr)
//
//      {
//
//         get_workspace_rectangle(iMainWorkspace, prectangle);
//
//
//      }
//
//      return iMainWorkspace;
//
//   }


//   ::count system::get_workspace_count()
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

//   bool system::get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 * prectangle)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      if (iWorkspace < 0 || iWorkspace >= get_workspace_count())
//         return false;
//
//      *prectangle = m_monitorinfoa[iWorkspace].rcWork;
//
//
//#elif defined(_UWP)
//
//      return get_monitor_rectangle(iWorkspace, prectangle);
//
//
//      //#elif defined(LINUX)
//      //
//      //return false;
//      //
//#elif defined(__APPLE__)
//
//      if (iWorkspace < 0 || iWorkspace >= get_workspace_count())
//      {
//
//         return false;
//
//      }
//
//      GetWorkspaceRect(prectangle, (int) iWorkspace);
//
//
//      //      prectangle->top += ::mac::get_system_main_menu_bar_height();
//
//      //    prectangle->bottom -= ::mac::get_system_dock_height();
//
//#elif defined(LINUX)
//
//      synchronous_lock synchronouslock(mutex());
//
//      if (iWorkspace < 0 || iWorkspace >= get_workspace_count())
//      {
//
//         return false;
//
//      }
//
//      *prectangle = m_rectangleaWork[iWorkspace];
//
//
//      return true;
//
//#else
//
//      //throw ::exception(todo);
//
//      //::get_window_rect(::get_desktop_window(),prectangle);
//
//
//      get_monitor_rectangle(iWorkspace, prectangle);
//
//
//#endif
//
//      return true;
//
//   }
//
//
//   ::count system::get_desk_workspace_count()
//   {
//
//      return get_workspace_count();
//
//   }
//
//
//   bool system::get_desk_workspace_rect(index iWorkspace, RECTANGLE_I32 * prectangle)
//
//   {
//
//      return get_workspace_rectangle(iWorkspace, prectangle);
//
//
//   }
//
//   index system::get_ui_workspace(::user::interaction * pinteraction)
//   {
//
//      index iMainWorkspace = 0;
//
//#ifdef WINDOWS_DESKTOP
//
//      HMONITOR hworkspacePrimary = GetUiMonitorHandle(pinteraction->get_handle());
//
//      for (index iWorkspace = 0; iWorkspace < get_workspace_count(); iWorkspace++)
//      {
//
//         if (m_hmonitora[iWorkspace] == hworkspacePrimary)
//         {
//
//            iMainWorkspace = iWorkspace;
//
//            break;
//
//         }
//
//      }
//
//#endif
//
//      return iMainWorkspace;
//
//   }


   void system::on_initial_frame_position(::user::frame * pframe)
   {

      if(m_bExperienceMainFrame)
      {

//#ifdef _UWP
//
//         //auto psession = get_session();
//
//         auto puserinteraction = __user_interaction(pframe);
//
//         __pointer(::universal_windows::interaction_impl) pimpl = puserinteraction->m_pimpl;
//
//         if (pimpl.is_set())
//         {
//
//            auto pframeworkview = pimpl->m_pframeworkview;
//
//            auto directx = pframeworkview->m_directx;
//
//            directx->UpdateForWindowSizeChange();
//
//         }
//
//#endif

      }

   }


   //void system::on_graphics_ready()
   //{

   //}


   /*void system::__tracea(enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz) const
   {

      if (m_ptrace.is_null())
      {

         __simple_tracea(trace_object(pobject), elevel, pszFunction, pszFile, iLine, psz);

         return;

      }

      log().__tracea(trace_object(pobject), elevel, pszFunction, pszFile, iLine, psz);

   }*/


//   void system::browser(string strUrl, string strBrowser, string strProfile, string strTarget)
//   {
//
//       auto estatus = os().link_open(strUrl);
//
//       return estatus;
//
//#if 0
//
//      if (strProfile.is_empty() && strTarget.is_empty() && strBrowser.is_empty())
//      {
//
//         //::os_message_box(NULL, strUrl, strUrl, e_message_box_ok);
//
//         pcontext->m_papexcontext->os().link_open(strUrl);
//
//         return;
//
//      }
//
//      string strBrowserPath;
//      string strBrowserDir;
//      string strBrowserHelperPath;
//      string strBrowserHelperDir;
//
//      string strId;
//
//      ::file::path path;
//
//      string strParam;
//
//      pcontext->m_papexcontext->os().get_default_browser(strId, path, strParam);
//
//      if (strProfile.is_empty() || strProfile == "native")
//      {
//
//         strProfile = "default";
//
//      }
//
//      string strUser = strProfile;
//
//      string strWeather = strBrowser;
//
//      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
//      {
//
//         strWeather = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedir->system() / "browser_weather.txt");
//
//      }
//
//      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
//      {
//
//         strWeather = "browser_day";
//
//      }
//
//      ::datetime::time timeNow = ::datetime::time::now();
//
//      if (timeNow.GetMonth() == 12)
//      {
//         if (timeNow.GetDay() >= 16)
//         {
//
//            strWeather = "synth_" + strWeather;
//
//         }
//
//      }
//      else if (timeNow.GetMonth() == 1)
//      {
//         if (timeNow.GetDay() <= 14)
//         {
//
//            strWeather = "synth_" + strWeather;
//
//         }
//
//      }
//
//
//
//      strProfile = strProfile + "." + strWeather;
//
//      if (strUrl.has_char())
//      {
//
//         if (strBrowser == "firefox")
//         {
//
//            //strUrl = "https://ca2.software/open_f___?url=" + url_encode(strUrl) + "&profile=" + url_encode(strProfile) + "&target=" + url_encode(strTarget);
//
//         }
//         else
//         {
//
//            //strUrl = "https://ca2.software/open_tab?url=" + url_encode(strUrl) + "&profile=" + url_encode(strProfile) + "&target=" + url_encode(strTarget);
//
//         }
//
//      }
//
//
//      if (strId == "firefox")
//      {
//
//         firefox(strUrl, strBrowser, strProfile, strParam);
//
//      }
//      else if (strId == "chrome")
//      {
//
//         chromium(strUrl, strBrowser, strId, path, strProfile, strParam);
//
//      }
//      else if (strId == "vivaldi")
//      {
//
//         chromium(strUrl, strBrowser, strId, path, strProfile, strParam);
//
//      }
//      else if (strId == "commander")
//      {
//
//         //if (m_strAppName == "app-core/commander")
//         {
//
//            chromium(strUrl, strBrowser, strId, pcontext->m_papexcontext->os().get_app_path("chrome"), strProfile, strParam);
//
//         }
//         //else
//         {
//
//            //commander(strUrl, strWeather, strUser, path, strParam);
//
//         }
//
//      }
//      else
//      {
//
//#if defined(_UWP)
//
//
//         string * pstrNew = new string(strUrl);
//
//         ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainImpact->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
//            ref new ::winrt::Windows::UI::Core::DispatchedHandler([pstrNew]()
//               {
//
//                  ::winrt::Windows::Foundation::Uri ^ uri = ref new ::winrt::Windows::Foundation::Uri(*pstrNew);
//
//                  delete pstrNew;
//
//                  LauncherOptions ^ options = ref new LauncherOptions();
//
//                  options->TreatAsUntrusted = false;
//
//                  Launcher::LaunchUriAsync(uri, options);
//
//               }));
//
//         //#elif defined(LINUX)
//         //
//         //      ::system("xdg-open \"" + strUrl + "\"");
//         //
//         //      return true;
//         //
//         //#elif defined(__APPLE__)
//         //    openURL(strLink);
//         //  return true;
//#elif defined(ANDROID)
//
//         string strOpenUrl;
//
//         if (::oslocal()->m_pszOpenUrl != nullptr)
//         {
//
//            strOpenUrl = ::oslocal()->m_pszOpenUrl;
//
//            try
//            {
//
//               ::free((void *)::oslocal()->m_pszOpenUrl);
//
//            }
//            catch (...)
//            {
//
//
//            }
//
//            ::oslocal()->m_pszOpenUrl = nullptr;
//
//         }
//
//
//         //strOpenUrl = strUrl + str::has_char(strOpenUrl, ";");
//
//         //if (strOpenUrl.has_char())
//         {
//
//            // m_pandroidinitdata->m_pszOpenUrl = strdup(strLink);
//
//            ::oslocal()->m_pszOpenUrl = strdup(strUrl);
//
//         }
//
//
//#elif defined(MACOS)
//
//         ::system("open -a /Applications/Safari.app \"" + strUrl + "\"");
//
//#elif defined(APPLE_IOS)
//
//         ui_open_url(strUrl);
//
//#elif defined(WINDOWS_DESKTOP)
//
//         if (strUrl.is_empty())
//         {
//
//            strUrl = "foo.html";
//
//         }
//
//         ::ShellExecuteW(nullptr, L"open", wstring(strUrl), nullptr, L"C:\\Windows", SW_SHOWDEFAULT);
//
//         //::file::path path = getenv("APPDATA");
//
//         //path /= strProfile;
//
//         //call_sync("C:\\Program Files\\Opera.exe", "--user-data-dir=\"" + path + "\" " + strUrl, "C:\\Users\\camilo\\AppData\\Local\\Vivaldi\\papplication", SW_SHOWNORMAL, 0);
//
//#else
//
//         if (strUrl.has_char())
//         {
//
//            strParam = "\"" + strUrl + "\"";
//
//         }
//
//         ::file::path pathDir;
//
//         pathDir = path.folder();
//
//         ::file::path shell;
//
//         shell = "/bin/bash";
//
//         if (strBrowser == "vivaldi")
//         {
//
//            ::file::path pathHome(getenv("HOME"));
//
//            ::file::path pathProfile;
//
//            pathProfile = pathHome / "ca2/Vivaldi/Profile" / strProfile;
//
//            call_async(shell, " -c \"" + path + " --user-data-dir=\\\"" + pathProfile + "\\\" " + strParam, pathHome, e_display_default, false);
//
//         }
//         else if (strBrowser == "chrome")
//         {
//
//            ::file::path pathHome(getenv("HOME"));
//
//            ::file::path pathProfile;
//
//            pathProfile = pathHome / "ca2/Chrome/Profile" / strProfile;
//
//            string strCmd = path + " --user-data-dir=\"" + pathProfile + "\" " + strParam;
//
//            strCmd.replace("\"", "\\\"");
//
//            strParam = " -c \"" + strCmd + "\"";
//
//            //MessageBox(nullptr, strParam, path, e_message_box_ok);
//
//            call_async(shell, strParam, pathHome, e_display_default, false);
//
//         }
//         else if (strBrowser == "firefox")
//         {
//
//            ::file::path pathHome(getenv("HOME"));
//
//            ::file::path pathProfile;
//
//            pathProfile = pathHome / "ca2/Firefox/Profile" / strProfile;
//
//            call_async(shell, "-c \"" + path + " -profile=\\\"" + pathProfile + "\\\" " + strParam + "\"", pathHome, e_display_default, false);
//
//         }
//         else
//         {
//
//            ::system("xdg-open " + strUrl);
//
//         }
//
//
//
//#endif
//
//      }
//
//#endif
//
//   }
//


//   void system::chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam)
//   {
//
//#ifdef _UWP
//
//      pcontext->m_papexcontext->os().native_full_web_browser(strUrl);
//
//      return;
//
//#endif
//
//      ::file::path pathDir;
//
//      pathDir = path.folder();
//
//      ::file::path pathAppDataDir(m_psystem->m_pacmedir->ca2roaming());
//
//      ::file::path pathProfile;
//
//      string strBrowserProfile;
//
//      if (strId == "chrome" || strId == "commander")
//      {
//
//         strBrowserProfile = "Chrome";
//
//
//      }
//      else if (strId == "vivaldi")
//      {
//
//         strBrowserProfile = "Vivaldi";
//
//      }
//      else
//      {
//
//         strBrowserProfile = "Chromium";
//
//      }
//
//
//      try
//      {
//
//         bool bFound = false;
//
//         pathProfile = pathAppDataDir / strBrowserProfile / "Profile" / strProfile;
//
//         if (!bFound)
//         {
//
//            if (strUrl.has_char())
//            {
//
//               strsize iFind = strParam.find("%1");
//
//               if (iFind >= 0)
//               {
//
//                  strParam = strParam.Left(iFind) + strUrl + strParam.Mid(iFind + 2) + " ";
//
//               }
//               else
//               {
//
//                  strParam = "\"" + strUrl + "\" ";
//
//               }
//
//            }
//            else
//            {
//
//               strParam = "";
//
//            }
//
//         }
//
//#ifdef WINDOWS_DESKTOP
//
//         {
//
//            if (strParam.trimmed().begins_ci("--"))
//            {
//
//               strParam = "--user-data-dir=\"" + pathProfile + "\" " + strParam;
//
//            }
//            else
//            {
//
//               strParam += "--user-data-dir=\"" + pathProfile + "\"";
//
//            }
//
//            strParam += " " + m_psystem->m_pacmefile->as_string(         auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->localconfig() / "app-core/commander/chrome.txt");
//
//            call_async(path, strParam, pathDir, e_display_default, false);
//
//         }
//
//#elif defined(MACOS)
//
//         string_array sa;
//
//         sa = get_c_args_for_c(strParam);
//
//         sa.add("--user-data-dir=" + pathProfile + "");
//
//         string strChrome = m_psystem->m_pacmefile->as_string(         auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->localconfig() / "app-core/commander/chrome.txt");
//
//         string_array sa2 = get_c_args_for_c(strChrome);
//
//         sa.add(sa2);
//
//         auto argv = sa.c_ansi_get();
//
//         argv.add(nullptr);
//
//         string strApp = url().url_decode(path);
//
//         // 0x00010000 NSWorkspaceLaunchAsync
//         // 0x00080000 NSWorkspaceLaunchNewInstance
//
//         ns_launch_app(strApp, argv.get_data(), 0x00010000 | 0x00080000);
//
//#elif defined(LINUX)
//
//         ::file::path shell;
//
//         shell = "/bin/bash";
//
//         strParam += "--user-data-dir=\"" + pathProfile + "\"";
//
//         strParam += " " + m_psystem->m_pacmefile->as_string(         auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->localconfig() / "app-core/commander/chrome.txt");
//
//         string strCmd = path + " " + strParam;
//
//         strCmd.replace("\'", "\\\'");
//
//         strParam = " -c '" + strCmd + "'";
//
//         output_debug_string(strParam);
//
//         call_async(shell, strParam, pathDir, e_display_default, false);
//
//#endif
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//   }


//   void system::defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile)
//   {
//
//#ifdef _UWP
//
//
//#else
//
//      if (pcontext->m_papexcontext->dir().is(pathProfile))
//      {
//
//         return;
//
//      }
//
//      ::file::path pathDir;
//
//      pathDir = pathFirefox.folder();
//
//      ::file::path pathProfileDir;
//
//      pathProfileDir = pathProfile.folder();
//
//      pcontext->m_papexcontext->dir().create(pathProfileDir);
//
//      string strParam = "-no-remote -CreateProfile \"" + strProfileName + " " + pathProfile + "\"";
//
//      ::property_set set;
//
//      call_sync(pathFirefox, strParam, pathDir, e_display_default, 3_min, set);
//
//#endif
//
//   }


//   void system::get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      try
//      {
//
//         ::windows::registry::key key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox");
//
//         string strCurrentVersion;
//
//         key.get("CurrentVersion", strCurrentVersion);
//
//         key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox\\" + strCurrentVersion + "\\Main");
//
//         key.get("PathToExe", strPathToExe);
//
//         key.get("Install Directory", strInstallDirectory);
//
//      }
//      catch (const ::e_status & estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return ::success;
//
//#else
//
//      return ::error_failed;
//
//#endif
//
//   }
//
//
//   void system::firefox(string strUrl, string strBrowser, string strProfile, string strParam)
//   {
//
//#ifdef _UWP
//
//      pcontext->m_papexcontext->os().native_full_web_browser(strUrl);
//
//#else
//
//      string strBrowserPath;
//      string strBrowserDir;
//      string strBrowserHelperPath;
//      string strBrowserHelperDir;
//
//      ::file::path pathAppDataDir(getenv("APPDATA"));
//
//      ::file::path pathProfile;
//
//      strParam = "-P \"" + strProfile + "\"";
//
//      if (strUrl.has_char())
//      {
//
//         strParam += " -new-tab \"" + strUrl + "\"";
//
//      }
//
//      auto estatus = get_firefox_installation_info(strBrowserPath, strBrowserDir);
//
//      if (::failed(estatus))
//      {
//
//         return estatus;
//
//      }
//
//      if (!pcontext->m_papexcontext->file().exists(strBrowserPath) || !pcontext->m_papexcontext->dir().is(strBrowserDir))
//      {
//
//         return error_not_found;
//
//      }
//
//      strBrowserHelperPath = ::file::path(strBrowserDir) / "uninstall/helper.exe";
//
//      strBrowserHelperDir = ::file::path(strBrowserDir) / "uninstall";
//
//      pathProfile = pathAppDataDir / "ca2/Firefox/Profile" / strProfile;
//
//      defer_create_firefox_profile(strBrowserPath, strProfile, pathProfile);
//
//      bool bFound = false;
//
//      if (!bFound)
//      {
//
//         call_async(strBrowserPath, strParam, strBrowserDir, e_display_normal, false);
//
//         call_async(strBrowserHelperPath, "/SetAsDefaultAppUser", strBrowserHelperDir, e_display_none, false);
//
//      }
//
//      if (strBrowser.has_char())
//      {
//
//         pcontext->m_papexcontext->file().put_text_utf8(m_psystem->m_pacmedir->system() / "browser.txt", strBrowser);
//
//         pcontext->m_papexcontext->file().put_text_utf8(m_psystem->m_pacmedir->system() / "browser_path.txt", strBrowserPath);
//
//         pcontext->m_papexcontext->file().put_text_utf8(m_psystem->m_pacmedir->system() / "browser_dir.txt", strBrowserDir);
//
//      }
//
//#endif
//
//      return ::success;
//
//   }

   //string system::get_local_mutex_name(const ::string & pszAppName)
   //{
   //   string strMutex;
   //   strMutex.format("Local\\ca2_application_local_mutex:%s", pszAppName);
   //   return strMutex;
   //}

   //string system::get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId)
   //{
   //   string strId(pszId);
   //   string strMutex;
   //   strMutex.format("Local\\ca2_application_local_mutex:%s, atom:%s", pszAppName, strId.c_str());
   //   return strMutex;
   //}

   //string system::get_global_mutex_name(const ::string & pszAppName)
   //{
   //   string strMutex;
   //   strMutex.format("Global\\ca2_application_global_mutex:%s", pszAppName);
   //   return strMutex;
   //}

   //string system::get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId)
   //{
   //   string strId(pszId);
   //   string strMutex;
   //   strMutex.format("Global\\ca2_application_global_mutex:%s, atom:%s", pszAppName, strId.c_str());
   //   return strMutex;
   //}

//
//   ::thread* system::get_task(itask_t itask)
//   {
//
//      synchronous_lock synchronouslock(&m_mutexTask);
//
//      return m_threadmap[itask];
//
//   }
//
//
//   itask_t system::get_thread_id(::thread* pthread)
//   {
//
//      synchronous_lock synchronouslock(&m_mutexTask);
//
//      itask_t itask = null_ithread;
//
//      if (!m_threadidmap.lookup(pthread, itask))
//      {
//
//         return 0;
//
//      }
//
//      return itask;
//
//   }
//
//
//   void system::set_thread(itask_t itask, ::thread* pthread)
//   {
//
//      synchronous_lock synchronouslock(&m_mutexTask);
//
//      m_threadmap[itask].reset(pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(this, "thread::thread_set"));
//
//      m_threadidmap[pthread] = itask;
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
//   void system::unset_thread(itask_t itask, ::thread * pthread)
//   {
//
//      synchronous_lock synchronouslock(&m_mutexTask);
//
//#if OBJECT_REFERENCE_COUNT_DEBUG
//
//      m_threadmap[itask].release(this);
//
//#endif
//
//      m_threadmap.erase_key(itask);
//
//      m_threadidmap.erase_key(pthread);
//
//   }


//#ifdef _OPENGL
   void system::create_gpu()
   {

      if (m_pgpu)
      {

         return;

      }

      //load_library("gpu_opengl");

      auto & pfactoryGpu = factory("gpu", "opengl");

      //get_library("gpu_opengl");



      //if (!pfactoryGpu)
      //{

      //   ERROR("gpu_opengl ([a-z0-9_]+)_factory has failed");

      //   return pfactoryGpu;

      //}

      pfactoryGpu->merge_to_global_factory();

      //auto estatus =
      
      pfactoryGpu->__compose(this, m_pgpu);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }
//#endif



   //::task_group * system::task_group(::enum_priority epriority)
   //{

   //   //return nullptr;

   //   if (m_bAvoidProcedureFork)
   //   {

   //      return nullptr;

   //   }

   //   synchronous_lock synchronouslock(mutex());

   //   auto & threadgroupa = m_taskgroupmap[epriority];

   //   if (threadgroupa.is_empty())
   //   {

   //      auto pgroup = __new(::task_group(this, epriority));

   //      threadgroupa.add(pgroup);

   //   }

   //   return threadgroupa.last();

   //}


   //::task_tool * system::task_tool(::enum_task_tool etool)
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   auto& threadtoola = m_tasktoolmap[etool];

   //   if (threadtoola.is_empty())
   //   {

   //      auto ptool = __new(::task_tool);

   //      ptool->m_atom = etool;

   //      threadtoola.add(ptool);

   //   }

   //   return threadtoola.last();

   //}


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

   //   if (!m_toolmap[::e_priority_none]->select_toolset(pset))
   //   {

   //      return nullptr;

   //   }

   //   return pset;

   //}


   //void system::open_profile_link(string strUrl, string strProfile, string strTarget)
   //{

   //   fork([this, strUrl, strProfile, strTarget]()
   //   {

   //      browser(strUrl, "", strProfile, strTarget);

   //   });

   //}


   //void system::open_url(string strUrl, string strProfile, string strTarget)
   //{

   //   fork([this, strUrl, strProfile, strTarget]()
   //      {

   //         browser(strUrl, "", strProfile, strTarget);

   //      });

   //}



   //void system::open_link(string strUrl, string strProfile, string strTarget)
   //{

   //   fork([this, strUrl, strProfile, strTarget]()
   //      {

   //         browser(strUrl, "", strProfile, strTarget);

   //      });

   //}



   void system::verb() // ambigous inheritance from ::aura::system/::axis::application
   {

      return ::thread::verb();

   }



   //void system::init_system()
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

   //   //__wait_threading_count_except(this,::duration((5000) * 77));

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




   string system::crypto_md5_text(const ::string & str)
   {

      return crypto()->md5(str);

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









   //void system::hist_hist(const ::string & psz)
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


   string system::url_encode(const ::string & str)
   {

      return m_purldepartment->url_encode(str);

   }


} // namespace aura


//CLASS_DECL_AURA ::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
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
//CLASS_DECL_AURA bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
//{
//
//   ::file::path path;
//
//   path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";
//
//   strBuild = m_psystem->m_pacmefile->as_string(path);
//
//   return strBuild.has_char();
//
//}
//
//
//CLASS_DECL_AURA bool set_application_installed(const ::file::path & pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
//{
//
//   ::file::path path;
//
//   path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";
//
//   return m_psystem->m_pacmefile->put_contents(path, pszBuild);
//
//}
//
//
//CLASS_DECL_AURA::file::path get_application_path(string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration)
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
//   ::file::path pathFile = m_psystem->m_pacmedir->local() / "appdata" / strAppId / "last_run_path.txt";
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
//   ::file::path path = ::m_psystem->m_pacmefile->as_string(pathFile);
//
//   return path;
//
//}
//
//
//CLASS_DECL_AURA bool set_last_run_application_path(string strAppId)
//{
//
//   ::file::path path = m_psystem->m_pacmepath->app_module();
//
//   ::file::path pathFile = get_last_run_application_path_file(strAppId);
//
//   return m_psystem->m_pacmefile->put_contents(pathFile, path);
//
//}
//
//
//





//#include "base/node/_node.h"


#ifdef WINDOWS_DESKTOP
//#include "aura/os/windows/windows_system_interaction_impl.h"
#elif defined(_UWP)
//#include "aura/operating_system/universal_windows/_universal_windows.h"
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

   /*  bool system::on_application_menu_action(const ::string & pszCommand)
     {
        return ::aura::system::on_application_menu_action(pszCommand);
     }*/


     //system::system()
     //{

     //   m_bFinalizeIfNoSessionSetting = true;
     //   m_bFinalizeIfNoSession = false;

     //   add_factory_item < ::aura::session, ::aura::session >();

     //}


  //   void system::initialize_system(::object* pobject, app_core* pappcore)
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
  //      //estatus = ::aura::application::initialize(pobject);
  //
  //     //if (!estatus)
  //     //{
  //
  //     //   return estatus;
  //
  //     //}
  //
  //     //m_XstrAppId = "base_system";
  //     //m_strAppName = "base_system";
  //     //m_strBaseSupportId = "base_system";
  //     //m_strInstallToken = "base_system";
  //
  //      add_factory_item < ::draw2d::icon >();
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
  //            //m_XstrAppId                    = "core_system";
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
  //         throw ::exception(estatus);
  //
  //      }
  //
  //      //#ifdef _UWP
  //      //      m_window                                  = nullptr;
  //      //#endif
  //
  //            //::aura::application * papp = ::get_application(pobject);
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
  //      //strId += ::str::has_char(m_XstrAppId, ".");
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
  //      //m_bInitApplicationResult   = false;
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
  //      m_emessageWindowsTaskbarCreatedMessage = 0;
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


   //void system::discard_to_factory(__pointer(object) pca)
   //{

   //   __UNREFERENCED_PARAMETER(pca);

   //}


   //bool system::is_system() const
   //{

   //   return true;

   //}


   //void system::defer_xml()
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



   void system::init2()
   {

      //auto estatus = 
      
      ::apex::system::init2();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if(!::aura::application::init2())
      //   return false;

      //auto estatus = ::aura::system::init2();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __compose_new(m_phistory);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      ////post_creation_requests();

      //return estatus;

   }


   void system::initialize_context()
   {

      if (m_bDraw2d)
      {

         initialize_draw2d();

         ////if (!initialize_draw2d())
         //{

         //   return false;

         //}

      }

      //auto estatus =
      
      __compose_new(m_pimaging);

      /*/if (!estatus)
      {*/

      //   if (m_bUser && m_bDraw2d && m_bImaging)
      //   {

      //      throw_statu()

      //   }

      //}

      //estatus =
      
      ::aura::context::initialize_context();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   __pointer(::data::node) system::load_xml(const ::string & pszXml)
   {

      throw ::interface_only();

      return nullptr;

   }


   //bool system::InitApplication()
   //{

   //   if(m_bInitApplication)
   //      return m_bInitApplicationResult;

   //   m_bInitApplicationResult      = false;
   //   m_bInitApplication            = true;

   //   m_bInitApplicationResult = ::aura::system::InitApplication();

   //   return m_bInitApplicationResult;
   //}

//
//   void system::process_init()
//   {
//
//      //if (m_bProcessInitialize)
//      //{
//
//      //   return m_bProcessInitializeResult;
//
//      //}
//
//      INFORMATION("start");
//
//      //m_bProcessInitializeResult    = false;
//
//      //m_bProcessInitialize          = true;
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_emessageWindowsTaskbarCreatedMessage == 0)
//      {
//
//         m_emessageWindowsTaskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
//
//      }
//
//#endif
//
//      //if (!::aura::application::process_init())
//      //{
//
//      //   ERROR(".1");
//
//      //   return false;
//
//      //}
//
//      if (!::aura::system::process_init())
//      {
//
//         ERROR(".2");
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
//      //m_phtml->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//      //if(m_phtml == nullptr)
//      //   return false;
//
//      //m_phtml->construct(this);
//
//      //m_bProcessInitializeResult = true;
//
//      INFORMATION("success");
//
//      return true;
//
//   }


   //void system::init()
   //{
   //   //
   //   //#ifndef __APPLE__
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


//   void system::init1()
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
   //    throw ::exception(todo("filehandler"));
   //    return *m_pfilehandler;

   //}


   //void system::on_start_find_applications_from_cache()
   //{

   //   throw ::exception(todo, "filehandler");
   //  // m_pfilehandler->m_ptree->erase_all();

   //}

   //void system::on_end_find_applications_from_cache(stream& is)
   //{

   //   //throw ::exception(todo("filehandler"));
   //   //is >> *m_pfilehandler;

   //}

   //void system::on_end_find_applications_to_cache(stream& os)
   //{

   //   //throw ::exception(todo("filehandler"));
   //   //os << *m_pfilehandler;

   //}

   //void system::on_map_application_library(::acme::library& library)
   //{

   //   throw ::exception(todo, "filehandler");
   //   // m_pfilehandler->defer_add_library(library.m_pca2library);

   //}


   void system::on_graphics_ready()
   {

      //::aura::system::on_graphics_ready();

      //if (psession->userex()->shell()->m_bPendingUpdate)
      //{

      //   psession->userex()->shell()->on_update_sizes_interest();

      //}

   }


   //void system::init3()
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


   //void system::init_system()
   //{

   //   if (!::aura::system::init_system())
   //   {

   //      return false;

   //   }

   //   /*set_enum_name(::e_type_null      , "null");
   //   set_enum_name(::e_type_empty     , "is_empty");
   //   set_enum_name(::e_type_string    , "string");
   //   set_enum_name(::type_int32   , "integer");
   //   set_enum_name(::type_::u32     , "ulong");
   //   set_enum_name(::e_type_element       , "ca2");
   //   set_enum_name(::e_type_bool      , "bool");
   //   set_enum_name(::e_type_f64    , "double");*/

   //   //if (!::aura::application::init_application())
   //   //{

   //   //   return false;

   //   //}

   //   //m_pbergedgemap = __new(::aura::session::map);


   //   return true;

   //}


   //void system::bergedge_start()
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
//      //__wait_threading_count(::duration((5000) * 8));
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
////         output_debug_string("linux_g_direct_term entry point_i32 not found at basecore library");
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


   //void system::set_history(::apex::history* phistory)
   //{

   //   auto estatus = __compose(m_phistory, phistory);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   //::acme::library * system::on_get_library(const ::string & pszLibrary)
   //{

   //   __pointer(::acme::library) plibrary;

   //   bool bLibraryOk = false;

   //   auto plibraryfactory = ::static_setup::get_first(::static_setup::flag_library, pszLibrary);

   //   if(!plibraryfactory)
   //   {

   //      return nullptr;

   //   }

   //   plibrary = plibraryfactory->new_library();

   //   if(!plibrary)
   //   {

   //      return nullptr;

   //   }

   //   auto estatus = plibrary->initialize(this);

   //   if(estatus.succeeded())
   //   {

   //      bLibraryOk = true;

   //   }

   //   if (plibrary && bLibraryOk)
   //   {

   //      return plibrary;

   //   }

   //   return nullptr;

   //}


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

      strMessage.format("system::on_allocation_error Implement \"%s\" allocation\n", str.c_str());

      dev_log(strMessage);

   }


   //void system::on_request(::create* pcreate)
   //{

   //   //get_platform(pcreate->m_pcommandline->m_iEdge,pcreate->m_pcommandline->m_papplicationbias);

   //   ::aura::system::on_request(pcreate);

   //}



   ////bool system::sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser, ::http::cookies* pcookies)
   //bool system::sync_load_url(string& str, const ::string & pszUrl, ::http::cookies* pcookies)

   //{

   //   string filename = pcontext->m_papexcontext->file().time_square();

   //   property_set set;

   //   //set["user"] = puser;

   //   set["cookies"] = pcookies;

   //   if (!pcontext->m_papexcontext->http().download(pszUrl, filename, set))

   //   {

   //      return false;

   //   }

   //   string strLocation;
   //   
   //   strLocation = set["get_headers"]["Location"];

   //   if (strLocation.has_char())
   //   {

   //      property_set set;

   //      //set["user"] = puser;

   //      set["cookies"] = pcookies;

   //      pcontext->m_papexcontext->file().del(filename);

   //      return pcontext->m_papexcontext->http().download(str, strLocation, set);

   //   }

   //   str = pcontext->m_papexcontext->file().as_string(filename);

   //   return true;

   //}


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

   //   if (get_session(iNewEdge, pbiasCreation) == nullptr)
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


   //void system::add_view_library(::acme::library* plibrary)
   //{

   //   m_libraryspa.add(plibrary);

   //   ::array < ::atom > ida;

   //   plibrary->get_create_view_id_list(ida);

   //   for (i32 i = 0; i < ida.get_count(); i++)
   //   {

   //      m_idmapCreateImpactLibrary.set_at(ida[i], plibrary);

   //   }

   //   return true;

   //}


   //   void system::post_fork_uri(const ::string & pszUri,application_bias * papplicationbias)
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
   //         psession->set_locale(m_varTopicQuery["locale"].stra()[0],::e_source_user);
   //
   //      }
   //
   //      if(m_varTopicQuery["schema"].array_get_count() > 0)
   //      {
   //
   //         psession->set_schema(m_varTopicQuery["schema"].stra()[0],::e_source_user);
   //
   //      }
   //
   //   }


//#ifdef _UWP
//
//
//   bool system::get_window_rect(RECTANGLE_I32* prectangle)
//   {
//
//      if (::is_null(get_session()))
//      {
//
//         return false;
//
//      }
//
//      try
//      {
//
//         if (::is_null(get_session()->m_puserinteractionHost))
//         {
//
//            return false;
//
//         }
//
//         auto puserinteractionHost = __user_interaction(get_session()->m_puserinteractionHost);
//
//         puserinteractionHost->get_window_rect(prectangle);
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


   //void     system::do_request(::create* pcreate)
   //{

   //   return aura::system::do_request(pcreate);

   //}


   void system::assert_ok() const
   {

      ::thread::assert_ok();

   }


   void system::dump(dump_context& context) const
   {

      ::thread::dump(context);

   }


   void     system::main()
   {

      return ::aqua::system::main();

   }


   //__pointer_array(::aura::session) & system::planesessionptra()
   //{

   //   return m_planesessionptra;

   //}


   //void system::hist_hist(const ::string & psz)
   //{

   //   hist().hist(psz);

   //}


   //::type system::get_pane_tab_view_type_info()
   //{

   //   return __type(userex::pane_tab_view);

   //}




//
//   void system::initialize_system(::object* pobject, ::app_core* pappcore)
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
//      //estatus = ::aura::application::initialize(pobject);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //m_XstrAppId = "base_system";
//      //m_strAppName = "base_system";
//      //m_strBaseSupportId = "base_system";
//      //m_strInstallToken = "base_system";
//
//      add_factory_item < ::draw2d::icon >();
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


   



//   void system::on_subject(::topic * ptopic)
//   {
//
//
//      ::aqua::system::on_subject(ptopic);
//
//   }


   void system::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_font_enumeration)
      {

         draw2d()->write_text()->handle_font_enumeration(ptopic);

      }
      else if (ptopic->m_atom == id_operating_system_user_color_change)
      {


      }

      ::aqua::system::handle(ptopic, pcontext);

   }


   void system::initialize_estamira()
   {

      if (m_pestamira)
      {

         //return ::success;

         return;

      }

      //auto estatus = 
      
      __compose(m_pestamira);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      m_pestamira->init_instance();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

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


//   void system::main_user_async(const ::routine & routine, ::enum_priority epriority)
//   {
//
//#ifdef _UWP
//
//      return m_pimplMain->main_async(routine, epriority);
//
//#else
//
//      throw ::not_implemented();
//
//      throw ::interface_only();
//
//#endif
//
//   }


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

      return m_typePaneTabImpact;

   }


   //bool system::on_application_menu_action(const ::string & pszCommand)
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   auto psession = get_session();

   //   auto applicationa = psession->m_applicationa;

   //   synchronouslock.unlock();

   //   for (auto & papp : applicationa)
   //   {

   //      ASSERT(papp != this);

   //      if (papp == this)
   //      {

   //         continue;

   //      }

   //      if (papp->on_application_menu_action(pszCommand))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   void system::destroy()
   {

      //auto estatus =
      
      ::aqua::system::destroy();

      //return estatus;

   }


   void system::TermSystem()
   {

      ::aqua::system::TermSystem();

      if (m_pdraw2d)
      {

         m_pdraw2d->destroy();

         m_pdraw2d.release();

      }



   }

   //void system::on_initial_frame_position(::user::frame* pframe)
   //{

   //}

   //void system::on_graphics_ready()
   //{

   //   //::apex::system::on_graphics_ready();

   //   //if (psession->userex()->shell()->m_bPendingUpdate)
   //   //{

   //   //   psession->userex()->shell()->on_update_sizes_interest();

   //   //}

   //}


   //__pointer(::extended::sequence < ::conversation >) system::message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
   //{

   //   return m_pnode->message_box(puserinteraction, strMessage, strTitle, emessagebox);

   //}


//   __namespace_system_factory(system);


} // namespace aura


#ifdef __APPLE__

string get_bundle_app_library_name();

#endif


