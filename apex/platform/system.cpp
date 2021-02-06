#include "framework.h"
#include "apex/operating_system.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "apex/platform/app_core.h"
#include "acme/id.h"
#include "apex/node/_node.h"
#include "acme/platform/profiler.h"
#include "apex/platform/static_setup.h"
#include "apex/id.h"
#ifndef WINDOWS
#include "acme/os/cross/windows/_windows.h"
#endif


//extern ::apex::system* g_papexsystem;

CLASS_DECL_APEX void apex_generate_random_bytes(void* p, memsize s);

//int GetMainScreenRect(RECTANGLE_I32 * lprect);


const char* g_pszMultimediaLibraryName = nullptr;

void apex_system_update(const ::id & id, const ::payload & payload);

void apex_system_set_modified(const ::id& id);


CLASS_DECL_APEX void multimedia_set_library_name(const char* psz)
{

   g_pszMultimediaLibraryName = psz;

}


CLASS_DECL_APEX const char * multimedia_get_library_name()
{

   return g_pszMultimediaLibraryName;

}


#ifdef CUBE
extern "C"
::apex::library * experience_get_new_library();
#endif



#ifdef LINUX
#include <sys/time.h>
#endif

extern string_map < __pointer(::apex::library) > * g_pmapLibrary;


CLASS_DECL_APEX void __simple_tracea(::matter * pobjectContext, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


void os_post_quit();


#ifdef UNIT_TEST
void unit_test_primitive_var_apex_block();
#endif


void dappy(const char * psz);


#ifdef WINDOWS_DESKTOP

#include <Lmcons.h>

string get_user_name()
{
   
   WCHAR wsz[UNLEN * 2];

   DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);

   ::GetUserNameW(wsz,&dwSize);

   return string(wsz);

}

#include "acme/os/windows/_c.h"
#endif


namespace apex
{


   system::system()
   {

      create_factory < ::thread >();

      m_papexsystem = this;

#ifdef _UWP

      m_bPreferLessGraphicsParallelization = true;

#else

      m_bPreferLessGraphicsParallelization = false;

#endif

      m_bMessageThread = true;

      m_bSystemSynchronizedCursor = true;
      m_bSystemSynchronizedScreen = true;

      //set_context_system(this OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);



      common_construct();

   }


   void system::common_construct()
   {

      create_factory < ::apex::session >();
      create_factory < ::apex::application >();
      //create_factory < ::imaging >();

      m_bSimpleMessageLoop = false;

      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;

      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

   }


   ::e_status system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::context_thread::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      //set_context_system(this);

      set_context(this);

      set_context_thread(this);

      if (::is_set(get_context_application()))
      {

         //__compose(m_psystemParent, get_context_application()->get_context_system());

      }

      __compose_new(m_pthreading);

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      auto pnode = node();

      if (pnode)
      {

         if (timeNow.GetHour() >= 6 && timeNow.GetHour() <= 17)
         {

            pnode->set_simple_ui_darkness(0);

         }
         else
         {

            pnode->set_simple_ui_darkness(255);

         }

      }

      string_to_string map;

      {

         map["ab"] = "1";

         string str1 = map["ab"];

         auto cstr = str1.c_str();

         INFO("%s", cstr);

      }

      {

         map["abc"] = "2";

         string str2 = map["abc"];
         INFO("%s", str2.c_str());

      }

      set_callstack_mask({ get_callstack_mask(), callstack_fork_global});

#ifdef UNIT_TEST

      unit_test_primitive_var_apex_block();

#endif

#if !defined(_UWP) && !defined(ANDROID)

      m_pmutexMatter = __new(::mutex(e_create_new, false, "Local\\ca2-appmatter"));

#endif

      estatus = __compose_new(m_pbase64);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose_new(m_pprocess);

      if (!estatus)
      {

         return estatus;

      }

      if (m_bPreferLessGraphicsParallelization)
      {

         m_bThreadToolsForIncreasedFps = false;

      }
      else
      {

         m_bThreadToolsForIncreasedFps = false;

      }

      //::factory::g_pfactorymap->InitHashTable(16189);

#ifdef __DEBUG

      estatus = __compose_new(m_pdumpcontext);

      if (!estatus)
      {

         return estatus;

      }

#endif

#ifndef WINDOWS

      exception::translator::attach();

#endif

      m_nSafetyPoolSize = 512;        // default size_i32

      estatus = __compose_new(m_pmath);

      if (!estatus)
      {

         return estatus;

      }

      set_generate_random_bytes(&::apex_generate_random_bytes);

      estatus = __compose_new(m_pgeometry);

      if (!estatus)
      {

         return estatus;

      }

      string strId;
      strId = "ca2log";

      if (!initialize_log(strId))
      {

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

      //create_factory < ::stdio_file, ::file::text_file >();
      //create_factory < ::stdio_file, ::file::file >();
      create_factory < ::i64_array >();
      create_factory < ::double_array >();
      create_factory < ::apex::library >();

      create_factory < ::file::path_object >();

      create_factory < string_array >();
      create_factory < memory >();
      create_factory < memory_file >();
      create_factory < int_array >();



      create_factory < ::file::path_object >();
      create_factory < ::i64_array >();
      create_factory < ::double_array >();
      create_factory < ::apex::library >();

      create_factory < ::file::path_object >();

      create_factory < string_array >();
      create_factory < memory >();
      create_factory < memory_file >();
      create_factory < int_array >();

      //create_factory < ::draw2d::icon >();

      __node_apex_factory_exchange();

      estatus = __compose_new(m_pdatetime);

      if (!estatus)
      {

         return estatus;

      }

      thread::s_bAllocReady = true;

      m_bGudoNetCache = true;

      //m_purldepartment = nullptr;

//      m_millisAfterApplicationFirstRequest = 0;

      estatus = __compose_new(m_purldepartment);

      if (!estatus)
      {

         return estatus;

      }

      // __thread(todo("graphics"));
      //::draw2d::static_initialize();

      // acme commented
      //estatus = __compose_new(m_pwindowmap);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ////g_pszCooperativeLevel = "axis";

      //m_pDraw2dFactoryExchange = nullptr;

      //m_puserstr = nullptr;

//      __node_axis_factory_exchange();



      //estatus = ::apex::application::initialize(pobjectContext);

     //if (!estatus)
     //{

     //   return estatus;

     //}

     //m_strAppId = "base_system";
     //m_strAppName = "base_system";
     //m_strBaseSupportId = "base_system";
     //m_strInstallToken = "base_system";

      //create_factory < ::draw2d::icon >();

      //#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
      //
      //      m_possystemwindow = new os_system_window();
      //
      //#endif



            //estatus = ::apex::application::initialize(pobject);

            //if (!estatus)
            //{

            //   return estatus;

            //}

            //m_strAppId                    = "core_system";
            //m_strAppName                  = "core_system";
            //m_strBaseSupportId            = "core_system";
            //m_strInstallToken             = "core_system";

      //m_phistory = nullptr;
      //m_ppatch = new ::apex::patch();
      //g_pszCooperativeLevel = "apex";

      //estatus = __compose(m_puserset, __new(::account::user_set(this)));

      //if (!estatus)
      //{

      //   throw ::exception::exception(estatus);

      //}

      //#ifdef _UWP
      //      m_window                                  = nullptr;
      //#endif

            //::apex::application * papp = ::get_context_application(pobject);

            //if(papp == nullptr)
            //{

            //   set("parent_system") = nullptr;

            //}
            //else
            //{

            //   set("parent_system") = papp->m_psystem;

            //}

      ///string strId;
      //strId = m_strAppName;
      //strId += ::str::has_char(m_strAppId, ".");
      //strId += ::str::has_char(m_strBaseSupportId, ".");










      // m_userset.set_app(this);
      //      m_email.set_app(this);






      //m_bInitApplication         = false;
      //m_bInitApplicationResult   = false;
      //m_bProcessInitialize       = false;
      //m_bProcessInitializeResult = false;

      //m_puserstr                 = nullptr;

      //m_pparserfactory           = nullptr;

      //m_bLicense                 = false;

      //m_prunstartinstaller       = nullptr;
      //m_bLicense                 = false;

#ifdef WINDOWS_DESKTOP

      m_uiWindowsTaskbarCreatedMessage = 0;

#endif

      return estatus;

   }


   //::apex::audio * system::defer_get_audio()
   //{

   //   if (!m_paudio)
   //   {

   //      defer_audio();

   //   }

   //   return m_paudio;

   //}


   ::e_status system::do_factory_exchange(const char* pszComponent, const char* pszImplementation)
   {

      string strComponent(pszComponent);

      string strImplementation(pszImplementation);

      ::str::begins_eat_ci(strImplementation, strComponent + "_");

      ::str::begins_eat_ci(strImplementation, strComponent);

#ifdef CUBE

      auto pfnFactoryExchange = m_mapFactoryExchange[strComponent][strImplementation];

      if (::is_null(pfnFactoryExchange))
      {

         return ::error_failed;

      }

      pfnFactoryExchange();

      return ::success;

#else

      auto plibrary = open_component_library(pszComponent, pszImplementation);

      if (!plibrary)
      {

         return ::error_failed;

      }


      PFN_factory_exchange pfn_factory_exchange = plibrary->get < PFN_factory_exchange >(strComponent + "_" + strImplementation + "_factory_exchange");

      if (pfn_factory_exchange == nullptr)
      {

         pfn_factory_exchange = plibrary->get < PFN_factory_exchange >(strComponent + "_factory_exchange");

         if (pfn_factory_exchange == nullptr)
         {

            pfn_factory_exchange = plibrary->get < PFN_factory_exchange >("factory_exchange");

            if (pfn_factory_exchange == nullptr)
            {

               return ::error_failed;

            }

         }

      }

      pfn_factory_exchange();

      return ::success;

#endif

   }


   __pointer(::apex::library) system::open_component_library(const char* pszComponent, const char* pszImplementation)
   {

      // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"

      sync_lock sl(&System.m_mutexLibrary);

      __pointer(::apex::library) plibrary = System.m_mapLibrary[pszComponent];

      if (plibrary && plibrary->is_opened())
      {

         return plibrary;

      }

      string strComponent(pszComponent);

      string strImplementation(pszImplementation);

      strComponent.trim();

      strImplementation.trim();

      string strLibrary;

      if (strImplementation.is_empty())
      {

         return nullptr;

      }

      ::str::begins_eat_ci(strImplementation, strComponent + "_");

      ::str::begins_eat_ci(strImplementation, strComponent);

      strLibrary = strComponent + "_" + strImplementation;

#ifdef CUBE

      auto plibraryfactory = ::static_setup::get_first(::static_setup::flag_library, strLibrary);

      if (!plibraryfactory)
      {

         return nullptr;

      }

      plibrary = plibraryfactory->new_library();

#else

      if (!plibrary)
      {

         plibrary = __new(::apex::library);

         plibrary->initialize(this);

      }

      if (!plibrary->open(strLibrary))
      {

         return nullptr;

      }


      if (!plibrary->is_opened())
      {

         return nullptr;

      }

#endif

      return plibrary;

   }

   ::e_status system::set_factory_exchange(const char* pszComponent, const char * pszImplementation, PFN_factory_exchange pfnFactoryExchange)
   {

      m_mapFactoryExchange[pszComponent][pszImplementation] = pfnFactoryExchange;

      return ::success;

   }


   // acme commented
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


   // acme commented
   //::apex::multimedia * system::defer_get_multimedia()
   //{

   //   if (!m_pmultimedia)
   //   {

   //      defer_multimedia();

   //   }

   //   return m_pmultimedia;

   //}


   // acme commented
   //void system::defer_multimedia()
   //{

   //   string strName;

   //   if (::is_set(g_pszMultimediaLibraryName) && !strcmp(g_pszMultimediaLibraryName, "veriwell_multimedia"))
   //   {

   //      strName = "veriwell_multimedia";

   //   }
   //   else
   //   {

   //      strName = "multimedia";

   //   }

   //   auto plibrary = get_library(strName);

   //   if (plibrary)
   //   {

   //      auto pgetnewmultimedia = plibrary->get<PFUNCTION_GET_NEW_MULTIMEDIA>("get_new_multimedia");

   //      __compose(m_pmultimedia, ::move_transfer(pgetnewmultimedia()));

   //      m_pmultimedia->initialize_multimedia(this);

   //   }

   //}


   void system::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {


   }


   string system::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   void system::session_add(index iEdge, ::apex::session * psession)
   {

      if (!::is_set(psession))
      {

         return;

      }

      if (m_sessionmap.is_empty())
      {

         m_bFinalizeIfNoSession = m_bFinalizeIfNoSessionSetting;

      }

      m_sessionmap[iEdge] = psession;

      if (iEdge == 0)
      {

         if (!get_context_session())
         {

            set_context_session(psession);

         }

      }

   }


   void system::session_remove(index iEdge)
   {

      m_sessionmap.remove_key(iEdge);

      if (m_sessionmap.is_empty() && m_bFinalizeIfNoSession)
      {

         finish();

      }

   }



   //::apex::library * system::on_get_library(const char * pszLibrary)
   //{

   //   return nullptr;

   //}


   bool system::on_get_thread_name(string& strThreadName)
   {

      if (is_console_app())
      {

         return false;

      }

      return ::apex::context_thread::on_get_thread_name(strThreadName);

   }



   ::apex::library * system::get_library(const char * pszLibrary1, bool bOpenCa2)
   {

      sync_lock sl(&System.m_mutexLibrary);

      string strLibrary(pszLibrary1);

      strLibrary.ends_eat_ci(".dll");
      strLibrary.ends_eat_ci(".so");
      strLibrary.ends_eat_ci(".dylib");
      strLibrary.begins_eat_ci("lib");

      __composite(::apex::library) & plibrary = System.m_mapLibrary[strLibrary];

      bool bLibraryOk = true;

      if (plibrary.is_null())
      {

         __m_own(&System, plibrary, on_get_library(strLibrary));

         if (plibrary.is_null())

         {

            System.__compose_new(plibrary);

            if (!plibrary->open(strLibrary))
            {

//#if !defined(ANDROID)
//               if (!plibrary->open(get_context()->dir().ca2module() / pszLibrary))
//#endif
//               {
//
//               }

            }

            bLibraryOk = plibrary->is_opened();

         }

#ifndef CUBE

         if (bOpenCa2 && bLibraryOk)
         {

            plibrary->open_ca2_library();

         }

#endif

      }

      if(!bLibraryOk)
      {

         return nullptr;

      }

#ifndef CUBE

      if (bOpenCa2)
      {

         if (plibrary->m_pca2library.is_null())
         {

            return nullptr;

         }

      }

#endif

      return plibrary;

   }


   system::~system()
   {


      //::acme::del(m_ppatch);


      //::acme::del(m_purldepartment);

      //::acme::del(m_pcompress);

      //::acme::del(g_pmutexImage);

      //try
      //{

      //   ::acme::del(m_pmachineeventcentral);

      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   if (m_pfactory.is_set())
      //   {

      //      m_pfactory->enable_simple_factory_request(false);

      //      m_pfactory.release();

      //   }

      //}
      //catch (...)
      //{
      //   TRACE("system::~system: Potentially catastrophical error : error disabling simple factory request");
      //}

      //if (g_p == this)
      //{

      //   g_p = nullptr;

      //}

#ifdef LINUX

      auto pnode = Node;

      pnode->post_quit();

#elif defined(__APPLE__)

      os_post_quit();

#endif

#ifndef WINDOWS

      exception::translator::detach();

#endif

   }





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


   ::datetime::department & system::datetime()
   {

      return *m_pdatetime;

   }


   ::apex::str & system::str()
   {

      return *m_puserstr;

   }


   ::layered * system::get_layered_window(oswindow oswindow)
   {

      return nullptr;

   }


   ::e_status system::process_init()
   {

//      set_system_update(&apex_system_update);

      //set_system_set_modified(&apex_system_set_modified);

      auto estatus = system_prep();

      if (!estatus)
      {

         return estatus;

      }

      if (!create_session())
      {

         message_box("Failed to allocate Session!!");

         return false;

      }

      if (!m_papplicationStartup)
      {

         message_box("Startup application is not allocated!!");

         return false;

      }

      estatus = m_papplicationStartup->initialize(get_context_session());

      if(!estatus)
      {

         message_box("Failed to initialize Application object!!");

         return false;

      }

      set_main_struct(*m_papplicationStartup);

      m_strAppId = m_papplicationStartup->m_strAppId;

      estatus = system_init();

      if (!estatus)
      {

         return estatus;

      }

      if (m_bConsole.undefined())
      {

         m_bConsole = false;

      }

      if (m_bDraw2d.undefined())
      {

         m_bDraw2d = !m_bConsole;

      }

      if (m_bUser.undefined())
      {

         m_bUser = !m_bConsole;

      }

      if (m_bUserEx.undefined())
      {

         m_bUserEx = !m_bConsole;

      }

      if (m_bImaging.undefined())
      {

         m_bImaging = !m_bConsole;

      }

      #ifdef WINDOWS_DESKTOP

      if (m_bGdiplus.undefined())
      {

         m_bGdiplus = !m_bConsole;

      }

      #endif

      #if defined(LINUX)

         if (m_bGtkApp.undefined())
         {

            m_bGtkApp = !m_bConsole;

         }

      #endif

      if (m_bShowApplicationInformation.undefined())
      {

         m_bShowApplicationInformation = false;

      }

      string strAppId = m_papplicationStartup->m_strAppId;

      ::apex::idpool::init();

      auto pcreate = m_pcreate;

      pcreate->m_strAppId = strAppId;

      if (is_true("show_application_information"))
      {

         printf("%s", "\n\nApplication Information\n");
         output_debug_string("\n\nApplication Information\n");

         int iPid;

         iPid = ::get_current_process_id();

         printf("%s", ("Process PID: " + __str(iPid) + "\n").c_str());
         output_debug_string("Process PID: " + __str(iPid) + "\n");

      }

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

      {

         {

#ifdef WINDOWS_DESKTOP

            {

               ASSERT(m_hPrevInstance == nullptr);

               HINSTANCE hinstance = (HINSTANCE)m_hinstance;

               auto edisplay = m_edisplay;

               // handle critical errors and avoid Windows message boxes
               SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

               m_edisplay = edisplay;

               //SetCurrentHandles();

            }

#endif

         }

      }

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

      create_factory < ::create >();
      //create_factory < application_bias >();
      create_factory < command_line >();
      create_factory < http::context >();

      //create_factory < ::mutex >();
      //create_factory < event >();

      //if (!::apex::application::process_init())
      //{

      //   return false;

      //}

      //m_spos.create();

      //if(is_installing() || is_unstalling())
      {

#ifdef MACOS

         /*         if(0 != setuid(0))
                     return false;

                  uid_t uid = getuid();

                  string str("installing or unstalling as root : getuid() %d", uid);

                  ::dir::mk("/ca2core");

                  file_put_contents("/ca2core/teste.txt", str, str.length());
                  */
#endif

#if 0

         // Create authorization context_object
         OSStatus status;

         AuthorizationRef authorizationRef;

         // AuthorizationCreate and pass nullptr as the initial
         // AuthorizationRights set so that the AuthorizationRef gets created
         // successfully, and then later call AuthorizationCopyRights to
         // determine or extend the allowable rights.
         // http://developer.apple.com/qa/qa2001/qa1172.html
         status = AuthorizationCreate(nullptr, kAuthorizationEmptyEnvironment,
                                      kAuthorizationFlagDefaults, &authorizationRef);

         if(status != errAuthorizationSuccess)
         {
            TRACE("Error Creating Initial Authorization: %d", status);

            return false;

         }

         // kAuthorizationRightExecute == "system.privilege.admin"
         AuthorizationItem right = {kAuthorizationRightExecute, 0, nullptr, 0};

         AuthorizationRights rights = {1, &right};

         AuthorizationFlags flags = kAuthorizationFlagDefaults |
                                    kAuthorizationFlagInteractionAllowed |
                                    kAuthorizationFlagPreAuthorize |
                                    kAuthorizationFlagExtendRights;

         // Call AuthorizationCopyRights to determine or extend the allowable rights.

         status = AuthorizationCopyRights(authorizationRef, &rights, nullptr, flags, nullptr);

         if (status != errAuthorizationSuccess)
         {

            TRACE("Copy Rights Unsuccessful: %d", status);

            return false;

         }

#endif

      }

      if(!m_pmachineeventcentral)
      {

#ifndef APPLE_IOS

         auto estatus = __compose_new(m_pmachineeventcentral);

         if (!estatus)
         {

            return false;

         }

         //if(!m_pmachineeventcentral->initialize())
         //{

         //   return false;

         //}

         if(m_pmachineeventcentral->is_close_application())
         {

            return false;

         }

#endif

      }

      if(!__compose(m_pfilesystem))
      {

         ERR("failed to initialize file-system");

         return false;

      }

      if(!__compose(m_pdirsystem))
      {

         ERR("failed to initialize dir-system");

         return false;

      }

      INFO("apex::session::process_init .3");

      estatus = m_pfilesystem->init_system();

      if (!estatus)
      {

         m_estatus = estatus;

         return estatus;

      }

      estatus = m_pdirsystem->init_system();

      if (!estatus)
      {

         m_estatus = estatus;

         return estatus;

      }

      estatus = ::context::initialize_context();

      if (!estatus)
      {

         return estatus;

      }

      if (!m_ptrace->process_init())
      {

         WARN("failed to process_init ::apex::log trace");

      }

      //output_debug_string("CommonAppData (matter) : " + get_context()->dir().commonappdata()  + "\n");
      //output_debug_string("commonappdata (matter) : " + get_context()->dir().commonappdata() + "\n");
      //output_debug_string("Common App Data (matter) : " + get_context()->dir().commonappdata() + "\n");
      //output_debug_string("common app data (matter) : " + get_context()->dir().commonappdata() + "\n");

      __compose_new(m_pcrypto);

      if (!::is_set(m_pcrypto))
      {

         return false;

      }


//#ifdef WINDOWS_DESKTOP
//
//      if (m_bGdiplus)
//      {
//
//         init_gdi_plus();
//
//      }
//
//#endif

      //if(m_bDraw2d)
      //{

      //   if (!init_draw2d())
      //   {

      //      return false;

      //   }

      //}

      //enum_display_monitors();

      on_update_matter_locator();

      estatus = initialize_sockets();

      if (!estatus)
      {

         m_estatus = estatus;

         return estatus;

      }

      bool bMatterFromHttpCache = false;

      if(m_iMatterFromHttpCache == -1)
      {

         ::file::path pathSide = get_context()->side_get_matter_path("app/_matter/main");

         ::file::path pathLocal = local_get_matter_path("app/_matter/main");

         bool bFileSystemMatter = ::dir::is(pathSide) || ::dir::is(pathLocal);

         bMatterFromHttpCache = !bFileSystemMatter;

      }
      else
      {

         bMatterFromHttpCache = m_iMatterFromHttpCache != 0;

      }

      m_pdirsystem->m_bMatterFromHttpCache = bMatterFromHttpCache;

      //estatus = create_html();

      //if (!estatus)
      //{

      //   FATAL("axis::application::process_init .2");

      //   return false;

      //}

      INFO("start");

#ifdef WINDOWS_DESKTOP

      if (m_uiWindowsTaskbarCreatedMessage == 0)
      {

         m_uiWindowsTaskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");

      }

#endif

      //::apex::profiler::initialize();

//      estatus = create_os_node();

//      if(!estatus)
//      {

//         return estatus;

//      }

//      estatus = node()->initialize()
//
//#ifdef LINUX
//
//      ::user::g_defer_init();
//
//#endif // LINUX

      INFO("success");

      return true;

   }


   void system::get_time(micro_duration * pmicroduration)
   {

#ifdef _WIN32
      
      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      
      GetSystemTimeAsFileTime(&ft);
      
      u64 tt;
      
      ::memcpy_dup(&tt, &ft, sizeof(tt));

      tt /= 10; // make it usecs
      
      pmicroduration->m_secs = (long)tt / 1'000'000;
      
      pmicroduration->m_micros = (long)tt % 1'000'000;

#else
      gettimeofday(point, nullptr);
#endif
   }


   ::e_status system::init_thread()
   {

      if (m_psystemParent)
      {

         m_psystemParent->add_reference(this);

      }

      auto estatus = process_init();

      if (!estatus)
      {

         return estatus;

      }

      estatus = init_system();

      if (!estatus)
      {

         return estatus;

      }

      //estatus = process_creation_requests();

      //if (!estatus)
      //{

        // return estatus;

      //}

      return true;

   }


   ::e_status system::init()
   {


      return true;

   }


   ::e_status system::init1()
   {

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

      //// apex commented
      //estatus = __compose(m_pimaging);

      //if (!estatus)
      //{

      //   if (m_bUser && m_bDraw2d)
      //   {

      //      return estatus;

      //   }

      //}

      get_context_session()->m_puserstrcontext->defer_ok(m_puserstr);

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

      return true;

   }


   ::e_status system::post_create_requests()
   {

      //while(auto pcreate = get_command()->get_create())
      while (auto pcreate = get_create())
      {

         do_request(pcreate);

      }

      return true;

   }


   ::e_status system::inline_init()
   {

      ::e_status estatus = ::apex::context_thread::inline_init();

      if (!estatus)
      {

         return estatus;

      }

      set_context_app(m_papplicationStartup);

      m_papplicationStartup->inline_init();

      get_context_application()->get_property_set().merge(get_property_set());

      __unbind(this, m_papplicationStartup OBJ_REF_DBG_COMMA_THIS);

      return estatus;

   }


   ::e_status system::inline_term()
   {

      ::e_status estatus = ::apex::context_thread::inline_term();

      if (!estatus)
      {

         return estatus;

      }

#if OBJ_REF_DBG

      release(OBJ_REF_DBG_P_NOTE(this, nullptr));

      try
      {

         if (m_countReference > 1)
         {

            __check_pending_releases(this);

         }

      }
      catch (...)
      {

      }

#endif


      return estatus;

   }


   ::e_status system::init_system()
   {

      if (m_bConsole)
      {

         auto estatus = get_context_session()->inline_init();

         if (!estatus)
         {

            return estatus;

         }

      }
      else
      {

         if (!get_context_session()->begin_synch())
         {

            return false;

         }

      }

      auto estatus = init1();

      if(!estatus)
      {

         return estatus;

      }

      estatus = init2();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void system::term()
   {

      post_destroy_all();

      __release(m_phistory);

      //__throw(todo("filehandler"));
      //__release(m_pfilehandler);

      //__throw(todo("ftp"));

      //if (::ftp::command::info2::g_pTheOneAndOnly != nullptr)
      //{

      //   try
      //   {

      //      delete ::ftp::command::info2::g_pTheOneAndOnly;

      //   }
      //   catch (...)
      //   {

      //      m_result.add(error_failed);

      //   }

      //}

      //::parallelization::wait_threads(1_min, { this });

   }


   bool system::thread_get_run() const
   {

      return ::apex::context_thread::thread_get_run();

   }



   void system::term1()
   {

   }


   void system::term2()
   {

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

         if (m_pmachineeventcentral)
         {

            m_pmachineeventcentral->finalize();

         }

      }
      catch (...)
      {

      }


   }


   ::e_status system::thread_loop()
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


   void system::term_system()
   {

      try
      {

         term2();

      }
      catch (...)
      {

      }

      try
      {

         term1();

      }
      catch (...)
      {

      }

      try
      {

         term();

      }
      catch (...)
      {

      }

      try
      {

         process_term();

      }
      catch (...)
      {

      }

      try
      {

         TermSystem();

      }
      catch (...)
      {

      }

   }


   void system::TermSystem()
   {

      //::apex::application::TermSystem();


#ifdef LINUX

      // dirty
      // (forcing premature gtk event loop (main loop) quitting)
      // the "most elegant" is to let just ~system (::apex::system destructor)...
      // ... do this call, but this requires all references to ::apex::system ...
      // ... to be released. This is a bit of an ideal situation that may not ...
      // ... always happen as the wish the program finishes when it is closed ...
      auto pnode = m_pnode;

      if(pnode)
      {

         pnode->post_quit();

      }

#elif defined(__APPLE__)

      os_post_quit();

#endif

   }


   ::e_status system::create_os_node()
   {

      ::e_status estatus = ::success;

#ifdef LINUX

      auto edesktop = get_edesktop();

      if(edesktop & ::user::e_desktop_kde)
      {

         estatus = do_factory_exchange("node", "kde");

      }
      else if(edesktop & ::user::e_desktop_gnome)
      {

         estatus = do_factory_exchange("node", "gnome");

      }
      else
      {

         estatus = do_factory_exchange("node", "kde");

         if(!estatus)
         {

            estatus = do_factory_exchange("node", "gnome");

         }

      }



#elif defined(WINDOWS_DESKTOP)

      estatus = do_factory_exchange("node", "windows");

#endif

      if(!estatus)
      {

         return estatus;

      }

      estatus = ::acme::system::create_os_node();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }




   void system::process_term()
   {

      //::apex::application::process_term();



      try
      {

         m_mapAppLibrary.remove_all();

      }
      catch (...)
      {

      }

   }


   ::u32 system::os_post_to_all_threads(const ::id & id,wparam wparam,lparam lparam)
   {

      post_to_all_threads(id,wparam,lparam);

      return 0;

   }


   bool system::is_system() const
   {

      return true;

   }


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


   ::xml::department & system::xml()
   {

      return *m_pxml;

   }


   class ::str::base64 & system::base64()
   {

      return *m_pbase64;

   }


   ::apex::log & system::log()
   {

      return *m_ptrace;

   }



   machine_event_central & system::machine_event_central()
   {
      return *m_pmachineeventcentral;
   }


   __pointer(regex) system::create_regular_expression(const char* pszStyle, const string& str)
   {

      return nullptr;

   }


   __pointer(regex_context) system::create_regular_expression_context(const char* pszStyle, int iCount)
   {

      return nullptr;

   }


   ::apex::session * system::session(index iEdge)
   {

      auto ppair = m_sessionmap.plookup(iEdge);

      if (!ppair)
      {

         return nullptr;

      }

      return ppair->element2();

   }


   //::apex::os & system::os()
   //{

   //   return *m_spos;

   //}


//__pointer_array(::apex::session) & system::basesessionptra()
//{

//   return m_basesessionptra;

//}


   ::process::department & system::process()
   {

      return *m_pprocess;

   }


   ::e_status system::initialize_log(const char * pszId)
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

      estatus = m_ptrace->initialize_apex_log(e_trace_level_warning, pszId);

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
      //     ::apex::application * papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }


   void system::appa_set_locale(const char * pszLocale, const ::action_context & context)
   {

      retry_single_lock rsl(mutex(),millis(100),millis(100));

//      for(i32 i = 0; i < appptra().get_size(); i++)
//     {
      //       ::apex::application * papp = appptra()(i);
      //       papp->set_locale(pszLocale,context);
      //    }

   }


   void system::appa_set_schema(const char * pszStyle, const ::action_context & context)
   {

      retry_single_lock rsl(mutex(),millis(100),millis(100));

//      for(i32 i = 0; i < appptra().get_size(); i++)
      //    {
      //       ::apex::application * papp = appptra()(i);
      //       papp->set_schema(pszStyle,context);
      //    }

   }



   bool system::assert_running_global(const char * pszAppName,const char * pszId)
   {
      if(string(pszId).has_char())
      {
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_id_mutex_name(pszAppName, pszId));
         ::mutex * pmutex = ::mutex::open_mutex(get_global_id_mutex_name(pszAppName,pszId));
         if(pmutex == nullptr)
         {

            string strApp = pszAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__APPLE__)

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, get_context()->dir().module() / strApp, strParameters, nullptr, e_display_normal);

            plauncher->launch();

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
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_mutex_name(pszAppName));
         ::mutex * pmutex = ::mutex::open_mutex(get_global_mutex_name(pszAppName));
         if(pmutex == nullptr)
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#if defined(_UWP)

            __throw(todo());

#else

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, get_context()->dir().module() / strApp, nullptr, nullptr, e_display_normal);

            plauncher->launch();

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
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_id_mutex_name(pszAppName, strId));
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

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, get_context()->dir().ca2module() / strApp, strParameters, nullptr, e_display_normal);

            plauncher->launch();

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
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_mutex_name(pszAppName));
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

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, get_context()->dir().ca2module() / strApp, strParameters, nullptr, e_display_normal);

            plauncher->launch();

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


   ::e_status system::create_session(index iEdge)
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

      __pointer(::apex::session) psession;

      auto estatus = __construct(psession);

      if (!estatus)
      {

         return estatus;

      }

      //psession->set_context_system(this);

      set_context_session(psession);

      psession->m_iEdge = iEdge;

      return psession;

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

      INFO("%s", ("::apex::system::on_request session = " + string(psession->type_name()) + "("+__str((iptr) psession)+")\n\n").c_str());

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
//      file_pointer pfile = get_context()->file().get_file(get_context()->dir().appdata() / "applibcache.bin",::file::e_open_binary | ::file::e_open_read);
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

      /*      m_spfilehandler(new ::apex::filehandler::handler(this));*/

//      m_mapAppLibrary.remove_all();
//
//      string strLibraryId;
//
//      ::file::listing straTitle(this);
//
//      ::file::path pathCa2Module = get_context()->dir().ca2module();
//
//      ::output_debug_string("\n\n::apex::system::find_applications_to_cache\n\n");
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
//         file = psession->file().get_file(get_context()->dir().appdata() / "applibcache.bin",::file::e_open_defer_create_directory | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_write);
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


   ::e_status system::do_request(::create * pcreate)
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

      //oslocal().m_strSetUserWallpaper = strUrl;

      return true;

   }

   bool system::android_get_user_wallpaper(string & strUrl)
   {

      //oslocal().m_bGetUserWallpaper = true;

      //for(int i = 0; i < 10; i++)
      //{

      //   if (!oslocal().m_bGetUserWallpaper)
      //   {


      //   }

      //   sleep(50_ms);

      //}

      //strUrl = oslocal().m_strGetUserWallpaper;

      return true;

   }


#endif

   class ::crypto::crypto & system::crypto()
   {

      return *m_pcrypto;

   }


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

         papp->post_object(e_message_system, e_system_message_create, pcreate);

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


   bool system::on_open_file(::payload varFile, string strExtra)
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


   //LPWAVEOUT system::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   //{

   //   for (auto & papp : psession->m_applicationa)
   //   {

   //      papp->waveout_open(iChannel, pformat, pcallback);

   //   }

   //   return nullptr;

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

   void system::on_os_text(e_os_text etext, string strText)
   {


   }

//#endif

//#ifdef _UWP
//
//
//
//   CLASS_DECL_APEX bool get_window_rect(::apex::system_window ^ pwindow, RECTANGLE_F64 * prectangle)
//
//   {
//
//      Windows::Foundation::Rect rectangle_i32 = pwindow->get_window_rect();
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
//   CLASS_DECL_APEX bool get_window_rect(::apex::system_window ^ pwindow, RECTANGLE_I32 * prectangle)
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



//   void system::enum_display_monitors()
//   {
//
//   __throw(todo("aura"));
////#ifdef WINDOWS_DESKTOP
////
////      m_monitorinfoa.remove_all();
////
////      ::EnumDisplayMonitors(nullptr, nullptr, &system::monitor_enum_proc, (LPARAM)(dynamic_cast < ::apex::system * > (this)));
////
////#elif defined(LINUX)
////
////      ::enum_display_monitors(this);
////
////#endif
//
//   }


   string system::standalone_setting(string str)
   {

      return file_as_string(get_context()->dir().standalone() / (str + ".txt"));

   }


   bool system::set_standalone_setting(string str, string strSetting)
   {

      return file_put_contents(get_context()->dir().standalone() / (str + ".txt"), strSetting);

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


         //int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", e_display_none, 30, 1000, nullptr, 0);

      }
#elif defined MACOS
      if (strProtocol == "ca2project")
      {

         string strBase = System.url().get_server(str);

         string strScheme = System.url().get_script(str);

         ::str::begins_eat(strScheme, "/");

         if(strBase == "scheme")
         {

//         int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", e_display_none, 30, 1000, nullptr, 0);

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

   }


   void system::__tracea(::matter * pobjectContext, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
   {

      if (m_ptrace.is_null())
      {

         __simple_tracea(trace_object(pobjectContext), elevel, pszFunction, pszFile, iLine, psz);

         return;

      }

      log().__tracea(trace_object(pobjectContext), elevel, pszFunction, pszFile, iLine, psz);

   }



   string system::get_user_language()
   {

      return System.standalone_setting("current_language");

   }


   bool system::set_user_language(::apex::application * papp, index iSel)
   {

      if (iSel < 0 || iSel >= System.get_context_session()->get_current_application()->m_puserlanguagemap->m_straLang.get_count())
      {

         return false;

      }

      string strLang = System.get_context_session()->get_current_application()->m_puserlanguagemap->m_straLang[iSel];

      if (strLang == System.get_context_session()->get_current_application()->m_puserlanguagemap->m_strLang)
      {

         return true;

      }

      if (!set_user_language(papp, strLang))
      {

         return false;

      }

      return true;

   }


   bool system::set_user_language(::apex::application * papp, string strLang)
   {

      System.get_context_session()->get_current_application()->m_puserlanguagemap->set_language(papp, strLang);

      return System.set_standalone_setting("current_language", strLang);

   }


   void system::process_machine_event_data(machine_event_data * pdata)
   {

      if (pdata->m_fixed.m_bRequestCloseApplication)
      {

         finalize();

      }

   }


   void system::browser(string strUrl, string strBrowser, string strProfile, string strTarget)
   {

       get_context()->os().link_open(strUrl);

       return;

#if 0

      if (strProfile.is_empty() && strTarget.is_empty() && strBrowser.is_empty())
      {

         //::os_message_box(NULL, strUrl, strUrl, e_message_box_ok);

         get_context()->os().link_open(strUrl);

         return;

      }

      string strBrowserPath;
      string strBrowserDir;
      string strBrowserHelperPath;
      string strBrowserHelperDir;

      string strId;

      ::file::path path;

      string strParam;

      get_context()->os().get_default_browser(strId, path, strParam);

      if (strProfile.is_empty() || strProfile == "native")
      {

         strProfile = "default";

      }

      string strUser = strProfile;

      string strWeather = strBrowser;

      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
      {

         strWeather = get_context()->file().as_string(::dir::system() / "browser_weather.txt");

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

            chromium(strUrl, strBrowser, strId, get_context()->os().get_app_path("chrome"), strProfile, strParam);

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

         if (::oslocal()->m_pszOpenUrl != nullptr)
         {

            strOpenUrl = ::oslocal()->m_pszOpenUrl;

            try
            {

               ::free((void *)::oslocal()->m_pszOpenUrl);

            }
            catch (...)
            {


            }

            ::oslocal()->m_pszOpenUrl = nullptr;

         }


         //strOpenUrl = strUrl + str::has_char(strOpenUrl, ";");

         //if (strOpenUrl.has_char())
         {

            // System.m_pandroidinitdata->m_pszOpenUrl = strdup(strLink);

            ::oslocal()->m_pszOpenUrl = strdup(strUrl);

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

            call_async(shell, " -c \"" + path + " --user-data-dir=\\\"" + pathProfile + "\\\" " + strParam, pathHome, e_display_default, false);

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

            call_async(shell, strParam, pathHome, e_display_default, false);

         }
         else if (strBrowser == "firefox")
         {

            ::file::path pathHome(getenv("HOME"));

            ::file::path pathProfile;

            pathProfile = pathHome / "ca2/Firefox/Profile" / strProfile;

            call_async(shell, "-c \"" + path + " -profile=\\\"" + pathProfile + "\\\" " + strParam + "\"", pathHome, e_display_default, false);

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

      get_context()->os().native_full_web_browser(strUrl);

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

            call_async(path, strParam, pathDir, e_display_default, false);

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

         call_async(shell, strParam, pathDir, e_display_default, false);

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

      if (get_context()->dir().is(pathProfile))
      {

         return;

      }

      ::file::path pathDir;

      pathDir = pathFirefox.folder();

      ::file::path pathProfileDir;

      pathProfileDir = pathProfile.folder();

      get_context()->dir().mk(pathProfileDir);

      string strParam = "-no-remote -CreateProfile \"" + strProfileName + " " + pathProfile + "\"";

      ::property_set set;

      call_sync(pathFirefox, strParam, pathDir, e_display_default, 3_min, set);

#endif

   }


   ::e_status system::get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory)
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
      catch (const ::e_status & estatus)
      {

         return estatus;

      }

      return ::success;

#else

      return ::error_failed;

#endif

   }


   ::e_status system::firefox(string strUrl, string strBrowser, string strProfile, string strParam)
   {

#ifdef _UWP

      get_context()->os().native_full_web_browser(strUrl);

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

      if (!get_context()->file().exists(strBrowserPath) || !get_context()->dir().is(strBrowserDir))
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

         call_async(strBrowserPath, strParam, strBrowserDir, e_display_normal, false);

         call_async(strBrowserHelperPath, "/SetAsDefaultAppUser", strBrowserHelperDir, e_display_none, false);

      }

      if (strBrowser.has_char())
      {

         get_context()->file().put_contents_utf8(::dir::system() / "browser.txt", strBrowser);

         get_context()->file().put_contents_utf8(::dir::system() / "browser_path.txt", strBrowserPath);

         get_context()->file().put_contents_utf8(::dir::system() / "browser_dir.txt", strBrowserDir);

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


//   ::thread* system::get_task(ithread_t ithread)
//   {
//
//      sync_lock sl(&m_mutexThread);
//
//      return m_threadmap[ithread];
//
//   }
//
//
//   ithread_t system::get_thread_id(::thread* pthread)
//   {
//
//      sync_lock sl(&m_mutexThread);
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
//      sync_lock sl(&m_mutexThread);
//
//      m_threadmap[ithread].reset(pthread OBJ_REF_DBG_COMMA_P_NOTE(this, "thread::thread_set"));
//
//      m_threadidmap[pthread] = ithread;
//
//   }
//
//
//   void system::unset_thread(ithread_t ithread, ::thread * pthread)
//   {
//
//      sync_lock sl(&m_mutexThread);
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


   ::thread_group * system::thread_group(::e_priority epriority)
   {

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


   __pointer(::promise::subject) system::new_subject(const MESSAGE& message)
   {

      auto psubject = subject((::iptr) message.wParam);

      psubject->m_pobjectTopic = (::object*) message.lParam.m_lparam;

      return psubject;

   }


   void system::open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      fork([this, strUrl, strProfile, strTarget]()
      {

         browser(strUrl, "", strProfile, strTarget);

      });

   }


   ::e_status system::verb() // ambigous inheritance from ::apex::system/::axis::application
   {

      return ::thread::verb();

   }


   string system::crypto_md5_text(const string & str)
   {

      return crypto().md5(str);

   }


   string system::url_encode(const string & str)
   {

      return m_purldepartment->url_encode(str);

   }


} // namespace apex


CLASS_DECL_APEX ::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
{

   string strFolder = pathExe.folder();

   strFolder.replace(":", "");

   return dir::ca2roaming() / "appdata" / strFolder / strAppId / pszPlatform / pszConfiguration / pszLocale / pszSchema;

}


CLASS_DECL_APEX bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
{

   ::file::path path;

   path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

   strBuild = file_as_string(path);

   return strBuild.has_char();

}


CLASS_DECL_APEX bool set_application_installed(const ::file::path & pathExe, string strAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
{

   ::file::path path;

   path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

   return file_put_contents(path, pszBuild);

}


CLASS_DECL_APEX::file::path get_application_path(string strAppId, const char * pszPlatform, const char * pszConfiguration)
{

   ::file::path pathFolder;

   pathFolder = dir::stage(strAppId, pszPlatform, pszConfiguration);

   string strName;

   strName = ::process::app_id_to_app_name(strAppId);

   ::file::path path;

   path = pathFolder / (strName + ".exe");

   return path;

}


CLASS_DECL_APEX ::file::path get_last_run_application_path_file(string strAppId)
{

   ::file::path pathFile = ::dir::local() / "appdata" / strAppId / "last_run_path.txt";

   return pathFile;

}


CLASS_DECL_APEX::file::path get_last_run_application_path(string strAppId)
{

   ::file::path pathFile = get_last_run_application_path_file(strAppId);

   ::file::path path = ::file_as_string(pathFile);

   return path;

}


CLASS_DECL_APEX bool set_last_run_application_path(string strAppId)
{

   ::file::path path = ::file::app_module();

   ::file::path pathFile = get_last_run_application_path_file(strAppId);

   return file_put_contents(pathFile, path);

}








//#include "base/node/_node.h"


#ifdef WINDOWS_DESKTOP
#elif defined(_UWP)
#include "apex/os/uwp/_uwp.h"
#endif


//#if !defined(WINDOWS) && !defined(MACOS)
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#endif






//#ifdef CUBE
//
//extern "C" DECLARE_NEW_APEX_LIBRARY(experience);
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


namespace apex
{

   CLASS_DECL_APEX void black_body(float* r, float* g, float* b, ::u32 dwTemp);

   /*  bool system::on_application_menu_action(const char * pszCommand)
     {
        return ::apex::system::on_application_menu_action(pszCommand);
     }*/


     //system::system()
     //{

     //   m_bFinalizeIfNoSessionSetting = true;
     //   m_bFinalizeIfNoSession = false;

     //   create_factory < ::apex::session, ::apex::session >();

     //}


  //   ::e_status system::initialize_system(::object* pobject, app_core* pappcore)
  //   {
  //
  //      auto estatus = ::apex::system::initialize_system(pobject, pappcore);
  //
  //      if (!estatus)
  //      {
  //
  //         return estatus;
  //
  //      }
  //
  //      //estatus = ::apex::application::initialize(pobjectContext);
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
  //            //estatus = ::apex::application::initialize(pobject);
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
  //      m_ppatch = new apex::patch();
  //      g_pszCooperativeLevel = "apex";
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
  //            //::apex::application * papp = ::get_context_application(pobject);
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


   //::e_status system::defer_xml()
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



   ::e_status system::init2()
   {

      //if(!::apex::application::init2())
      //   return false;

      //auto estatus = ::apex::system::init2();

      //if (!estatus)
      //{

      //   return estatus;

      //}

         auto estatus = __compose_new(m_phistory);

         if(!estatus)
         {

            return estatus;

      }

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

   //   m_bInitApplicationResult      = false;
   //   m_bInitApplication            = true;

   //   m_bInitApplicationResult = ::apex::system::InitApplication();

   //   return m_bInitApplicationResult;
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

      //::apex::system::on_graphics_ready();

      //if (psession->userex()->shell()->m_bPendingUpdate)
      //{

      //   psession->userex()->shell()->on_update_sizes_interest();

      //}

   }


#ifdef LINUX


//   ::e_status system::defer_initialize_x11()
//   {
//
//      return ::acme::system::defer_initialize_x11();
//
//   }


//   bool system::sn_start_context()
//   {
//
//      return false;
//
//   }


#endif


   ::apex::history& system::hist()
   {

      return *m_phistory;

   }


   ::e_status system::set_history(::apex::history* phistory)
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

   //      ::apex::system::term();

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

   //   ::apex::system::on_request(pcreate);

   //}


   //bool system::sync_load_url(string& str, const char* pszUrl, ::account::user* puser, ::http::cookies* pcookies)
   bool system::sync_load_url(string& str, const char* pszUrl, ::http::cookies* pcookies)

   {

      string filename = get_context()->file().time_square();

      property_set set;

      //set["user"] = puser;

      set["cookies"] = pcookies;

      if (!get_context()->http().download(pszUrl, filename, set))

      {

         return false;

      }

      string strLocation;
      
      strLocation = set["get_headers"]["Location"];

      if (strLocation.has_char())
      {

         property_set set;

         //set["user"] = puser;

         set["cookies"] = pcookies;

         get_context()->file().del(filename);

         return get_context()->http().download(str, strLocation, set);

      }

      str = get_context()->file().as_string(filename);

      return true;

   }


   //::apex::patch& system::patch()
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

   //   ::apex::session * pbergedge = nullptr;

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

   //   //   if (!::apex::application::on_install())
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


   bool system::is_thread() const
   {

      return false;

   }


   //::e_status system::add_view_library(::apex::library* plibrary)
   //{

   //   m_libraryspa.add(plibrary);

   //   ::array < ::id > ida;

   //   plibrary->get_create_view_id_list(ida);

   //   for (i32 i = 0; i < ida.get_count(); i++)
   //   {

   //      m_idmapCreateViewLibrary.set_at(ida[i], plibrary);

   //   }

   //   return true;

   //}


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


#ifdef _UWP


   bool system::get_window_rect(RECTANGLE_I32* prectangle)
   {

      if (::is_null(get_context_session()))
      {

         return false;

      }

      return true;

   }


#endif


   void system::assert_valid() const
   {

      ::thread::assert_valid();

   }


   void system::dump(dump_context& context) const
   {

      ::thread::dump(context);

   }


   ::e_status     system::main()
   {

      return ::thread::main();

   }


   //__pointer_array(::apex::session) & system::planesessionptra()
   //{

   //   return m_planesessionptra;

   //}


   void system::hist_hist(const char* psz)
   {

      hist().hist(psz);

   }


   void system::on_subject(::promise::subject * psubject)
   {

      if (psubject->id() == id_open_hyperlink)
      {

         auto plink = psubject->m_payload.cast < ::hyperlink >();

         if (plink)
         {

            //if (plink->m_bProfile)
            {

               open_profile_link(plink->m_strLink, plink->m_strProfile, plink->m_strTarget);

            }
            //else
            {

               // open_link(plink->m_strLink, plink->m_strProfile, plink->m_strTarget);

            }

         }

      }

      acme::system::on_subject(psubject);

   }


   void system::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      acme::system::on_subject(psubject, pcontext);

      //::update updateSetting(pupdate);

      //fork([this, updateSetting]
      //     ()
      //     {

      //        ::update update(updateSetting);

      //        __pointer(::user::interaction) pinteraction;

      //        __pointer(::apex::session) psession = m_psession;

      //        if(psession == nullptr)
      //        {

      //           return;

      //        }

      //        int iFrame = 0;

      //        while(psession->get_frame(pinteraction))
      //        {

      //           iFrame++;

      //           pinteraction->apply(psubject);

      //        }

      //     });

   }


   void system::finalize()
   {

      ::app_core::finalize();

      ::apex::context_thread::finalize();

#ifdef WINDOWS_DESKTOP

      ::exception::translator::finalize();

#endif

      for (auto& plibrary : m_mapLibrary.values())
      {

         if (plibrary)
         {

            plibrary->finalize();

         }

      }

      m_mapLibrary.remove_all();

   }


   __namespace_system_factory(system);


} // namespace apex


#ifdef __APPLE__

string get_bundle_app_library_name();

#endif



::apex::system* platform_create_system(const char * pszAppId)
{

#if !defined(CUBE)

   string strAppId(pszAppId);

   if (strAppId.has_char())
   {

      string strMessage;

      string strLibrary = strAppId;

      strLibrary.replace("/", "_");

      strLibrary.replace("-", "_");

      strLibrary.replace(".", "_");

      auto plibrary = __node_library_open(strLibrary, strMessage);

      if (!plibrary)
      {

         {

            auto pfuture = __sync_future();

            //message_box(strMessage, "Could not open required library. Want to give an yes/no answer insted of pression cancel?", e_message_box_icon_exclamation | e_message_box_yes_no_cancel, pfuture);

            pfuture->wait(10_s);

            int iDialogResult = pfuture->m_var;

            ::output_debug_string("result " + __str(iDialogResult));

         }

         __throw(::exception::exception(strMessage + "\n\nCould not open required library."));

         return nullptr;

      }

   }

#endif

   auto pstaticsetup = ::static_setup::get_first(::static_setup::flag_system, "");

   if (!pstaticsetup)
   {

      return nullptr;

   }

   auto pobject = pstaticsetup->new_object();

   if (!pobject)
   {

      return nullptr;

   }

   auto psystem = dynamic_cast<::apex::system*>(pobject);

   if(!psystem)
   {

      delete pobject;

      return nullptr;

   }

   return psystem;

}


::apex::session * platform_create_session()
{

   auto pstaticsetup = ::static_setup::get_first(::static_setup::flag_system, "");

   if (!pstaticsetup)
   {

      return nullptr;

   }

   auto pobject = move_transfer(pstaticsetup->new_object());

   if (!pobject)
   {

      return nullptr;

   }

   return pobject.cast < ::apex::session >();

}



void apex_application_main(int argc, char* argv[], const char* pszCommandLine);

namespace apex
{

   void system::application_main(int argc, char* argv[], const char* pszCommandLine)
   {

      apex_application_main(argc, argv, pszCommandLine);

   }


   ::e_status system::message_box(const char* pszText, const char* pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process)
   {

      return ::acme::system::message_box(pszText, pszTitle, emessagebox, process);


   }


} // namespace apex


void apex_system_update(const ::id & id, const ::payload & payload)
{

   System.process_subject(id, payload);

}



void apex_system_set_modified(const ::id& id)
{

   System.set_modified(id);

}



