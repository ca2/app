#include "framework.h"
//#include "apex/filesystem/filehandler/_data.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
//#include "apex/xml/_.h"
#include "apex/platform/app_core.h"
#include "apex/const/id.h"
#include "apex/node/_node.h"
//#include "apex/net/ftp/_.h"
#include "acme/platform/profiler.h"
#include "apex/platform/static_setup.h"
#include "acme/os/_os.h"
#include "apex/id.h"

////#ifdef _OPENGL
//#include "apex/gpu/gpu/_.h"
////#endif


#ifdef WINDOWS_DESKTOP


namespace user
{


   CLASS_DECL_ACME bool calc_system_dark_mode();


   CLASS_DECL_ACME bool calc_app_dark_mode();


} // namespace user


#endif


extern ::apex::system* g_papexsystem;

CLASS_DECL_APEX void apex_generate_random_bytes(void* p, memsize s);

int GetMainScreenRect(LPRECT lprect);


const char* g_pszMultimediaLibraryName = nullptr;

void apex_system_call_update(int iUpdate, const ::var& var);


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


//void ___compile_test_sort_array_21304528734();

//void enum_display_monitors(::apex::system * psystem);

//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_APEX ::user::interaction * create_system_message_window(::layered * pobjectContext);
//#endif


#ifdef LINUX
#include <sys/time.h>
#endif

extern string_map < __pointer(::apex::library) > * g_pmapLibrary;


CLASS_DECL_APEX void __simple_tracea(::element * pobjectContext, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


void os_post_quit();

//extern ::mutex * &::get_context_system()->m_mutexLibrary;



#ifdef UNIT_TEST
void unit_test_primitive_var_apex_block();
#endif


void dappy(const char * psz);


#ifdef WINDOWS_DESKTOP
string get_user_name()
{
   WCHAR wsz[1024];
   DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);
   ::GetUserNameW(wsz,&dwSize);
   return string(wsz);
}
#include "acme/os/windows/_c.h"
#endif


namespace apex
{


   ::mutex * g_pmutexImage = nullptr;

   ::mutex * get_image_mutex()
   {

      return g_pmutexImage;

   }

   system::system()
   {

      m_paurasystem = nullptr;
      m_paxissystem = nullptr;
      m_pbasesystem = nullptr;
      m_pcoresystem = nullptr;

      m_bMessageThread = true;

      m_bSystemSynchronizedCursor = true;
      m_bSystemSynchronizedScreen = true;

      set_context_system(this);

      if (g_papexsystem == nullptr)
      {

         g_papexsystem = this;

      }

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


   ::estatus system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::context_thread::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      set_context_system(this);

      set_context(this);

      set_context_thread(this);

      if (::is_set(get_context_application()))
      {

         __compose(m_psystemParent, get_context_application()->get_context_system());

      }

      __compose_new(m_pthreading);

      // __thread(todo("datetime"));
      //::datetime::time timeNow = ::datetime::time::get_current_time();

      //if (timeNow.GetHour() >= 6 && timeNow.GetHour() <= 17)
      //{

      //   set_simple_ui_darkness(0);

      //}
      //else
      //{

      //   set_simple_ui_darkness(255);

      //}

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

      m_spmutexMatter = __new(::mutex(e_create_new, false, "Local\\ca2-appmatter"));

#endif

      // __thread(todo("datetime"));
      //m_pDraw2dFactoryExchange = nullptr;

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

      //estatus = __compose_new(m_pemaildepartment);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      g_pmutexImage = new ::mutex();

      m_bThreadToolsForIncreasedFps = false;

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

      m_bProdevianMouse = false;

      //g_pszCooperativeLevel = "apex";

      m_nSafetyPoolSize = 512;        // default size

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



      //m_phtml = nullptr;


      //m_bDoNotExitIfNoApplications = true;




      //      m_peengine = nullptr;


      //m_pmachineeventcentral = nullptr;

      string strId;
      strId = "ca2log";

      //xxdebug_box("Going to start Log", "Just before (initialize) log", 0);

      // log starts here - ENABLE_TRACE macro should be non-zero during
      // compilation to enable log tracing
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

      //create_factory < ::user::control_descriptor >();
      create_factory < ::file::path_object >();
//      create_factory < ::stdio_file, ::file::text_file >();
  //    create_factory < ::stdio_file, ::file::file >();
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

      m_tickAfterApplicationFirstRequest = 0;

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
      //m_bInitApplicationResult   = FALSE;
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


   ::estatus system::do_factory_exchange(const char* pszComponent, const char* pszImplementation)
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

      sync_lock sl(&::get_context_system()->m_mutexLibrary);

      __pointer(::apex::library)& plibrary = ::get_context_system()->m_mapLibrary[pszComponent];

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

   ::estatus system::set_factory_exchange(const char* pszComponent, const char * pszImplementation, PFN_factory_exchange pfnFactoryExchange)
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

         set_context_session(psession);

      }

   }


   void system::session_remove(index iEdge)
   {

      m_sessionmap.remove_key(iEdge);

      if (m_sessionmap.is_empty() && m_bFinalizeIfNoSession)
      {

         set_finish();

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

      sync_lock sl(&::get_context_system()->m_mutexLibrary);

      string strLibrary(pszLibrary1);

      strLibrary.ends_eat_ci(".dll");
      strLibrary.ends_eat_ci(".so");
      strLibrary.ends_eat_ci(".dylib");
      strLibrary.begins_eat_ci("lib");

      __pointer(::apex::library) & plibrary = ::get_context_system()->m_mapLibrary[strLibrary];

      bool bLibraryOk = true;

      if (plibrary.is_null())
      {

         plibrary = on_get_library(strLibrary);

         if (plibrary.is_null())

         {

            plibrary.create();

            if (!plibrary->open(strLibrary))
            {

//#if !defined(ANDROID)
//               if (!plibrary->open(Context.dir().ca2module() / pszLibrary))
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

      if (g_papexsystem == this)
      {

         g_papexsystem = nullptr;

      }

      //::acme::del(m_purldepartment);

      //::acme::del(m_pcompress);

      ::acme::del(g_pmutexImage);

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

      os_post_quit();

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
















   ::estatus system::process_init()
   {

      set_system_call_update(&apex_system_call_update);

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

      m_papplicationStartup = get_new_application(get_context_session(), m_strAppId);

      if (!m_papplicationStartup)
      {

         message_box("Failed to allocate Application!!");

         return false;

      }

      set_main_struct(*m_papplicationStartup);
      
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
      auto pcreate = m_pcreate;

      pcreate->m_strAppId = strAppId;
      //TRACE("m_pcreate COMMENT END");

      //create_factory < ::database::field >();


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

               HINSTANCE hinstance = m_hinstance;

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
//      create_factory < manual_reset_event >();
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

      //output_debug_string("CommonAppData (matter) : " + Context.dir().commonappdata()  + "\n");
      //output_debug_string("commonappdata (matter) : " + Context.dir().commonappdata() + "\n");
      //output_debug_string("Common App Data (matter) : " + Context.dir().commonappdata() + "\n");
      //output_debug_string("common app data (matter) : " + Context.dir().commonappdata() + "\n");

      __compose_new(m_pcrypto);

      if (!::is_set(m_pcrypto))
      {

         return false;

      }


#ifdef WINDOWS_DESKTOP

      if (m_bGdiplus)
      {

         init_gdi_plus();

      }

#endif

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

         ::file::path pathSide = Context.side_get_matter_path("app/_matter/main");

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
//      //estatus = __construct_new(m_pdraw2d);
//
//      //if (!estatus)
//      //{
//
//      //   TRACE("Couldn't construct new draw2d.");
//
//      //   return false;
//
//      //}
//
//      //estatus = m_pdraw2d->init1();
//
//      //if(!estatus)
//      //{
//
//      //   TRACE("Couldn't initialize draw2d (init1).");
//
//      //   return estatus;
//
//      //}
//
//      //if (::succeeded(estatus))
//      //{
//
//      //   create_factory < ::draw2d::thread_tool_item >(::e_thread_tool_draw2d);
//
//      //}
//
//      return estatus;
//
//   }


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


//   ::estatus system::draw2d_factory_exchange()
//   {
//
////#ifdef CUBE
////
////      if (g_pfnfactoryexchangeDraw2d)
////      {
////
////         g_pfnfactoryexchangeDraw2d();
////
////      }
////
////      return true;
////
////#else
//
//
//      //__pointer(::apex::library) plibrary;
//
//      //bool bLibraryOk = false;
//
//      //auto plibraryfactory = ::static_setup::get_first(::static_setup::flag_library, pszLibrary);
//
//      //if (!plibraryfactory)
//      //{
//
//      //   return nullptr;
//
//      //}
//
//      //plibrary = plibraryfactory->new_library();
//
//      //if (!plibrary)
//      //{
//
//      //   return nullptr;
//
//      //}
//
//      //auto estatus = plibrary->initialize(this);
//
//      //if (estatus)
//      //{
//
//      //   bLibraryOk = true;
//
//      //}
//
//      //if (plibrary && bLibraryOk)
//      //{
//
//      //   return plibrary;
//
//      //}
//
//
//
//
//      //sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//      //__pointer(::apex::library) & plibrary = ::get_context_system()->m_mapLibrary["draw2d"];
//
//      //if (plibrary->is_opened())
//      //{
//
//      //   return true;
//
//      //}
//
//      string strLibrary;
//
//      if (has_property("draw2d"))
//      {
//
//         strLibrary = value("draw2d");
//
//         //strDraw2d.trim();
//
//         //if (strDraw2d.has_char())
//         //{
//
//         //   ::str::begins_eat_ci(strDraw2d, "draw2d_");
//
//         //   ::str::begins_eat_ci(strDraw2d, "draw2d");
//
//         //   strLibrary = "draw2d_" + strDraw2d;
//
//         //}
//
//      }
//
//      ::estatus estatus;
//
//      if (strLibrary.has_char())
//      {
//
//         estatus = do_factory_exchange("draw2d", strLibrary);
//
//         if (estatus)
//         {
//
//            return ::success;
//
//         }
//
//      }
//
//      strLibrary = draw2d_get_default_library_name();
//
//      if (strLibrary.is_empty())
//      {
//
//#ifdef WINDOWS
//
//         strLibrary = "draw2d_gdiplus";
//
//#else
//
//         strLibrary = "draw2d_cairo";
//
//#endif
//
//      }
//
//      estatus = do_factory_exchange("draw2d", strLibrary);
//
//      if (estatus)
//      {
//
//         return ::success;
//
//      }
//
//      //if (plibrary->is_opened())
//      //   goto finalize;
//
//#ifdef WINDOWS_DESKTOP
//
//
//      if (strLibrary != "draw2d_gdiplus")
//      {
//
//         estatus = do_factory_exchange("draw2d", "gdiplus");
//
//         if (estatus)
//         {
//
//            return ::success;
//
//         }
//
//      }
//
//
//      if (strLibrary != "draw2d_direct2d")
//      {
//
//         estatus = do_factory_exchange("draw2d", "direct2d");
//
//         if (estatus)
//         {
//
//            return ::success;
//
//         }
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
//         estatus = do_factory_exchange("draw2d", "cairo");
//
//         if (estatus)
//         {
//
//            return ::success;
//
//         }
//
//      }
//
//      //output_debug_string("No draw2d pluging available!!.");
//      return error_failed;
//
//   //finalize:
//
//   //   PFN_factory_exchange pfn_factory_exchange = plibrary->get < PFN_factory_exchange >("draw2d_factory_exchange");
//
//   //   if (pfn_factory_exchange == nullptr)
//   //   {
//
//   //      return false;
//
//   //   }
//
//   //   pfn_factory_exchange();
//
//   //   return true;
//
////#endif
//
//   }


//   bool system::imaging_factory_exchange()
//   {
//
////#ifdef CUBE
////
////      if (g_pfnfactoryexchangeImaging)
////      {
////
////         g_pfnfactoryexchangeImaging();
////
////      }
////
////      return true;
////
////#else
//
//      //sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//      //__pointer(::apex::library)& plibrary = ::get_context_system()->m_mapLibrary["imaging"];
//
//      //auto estatus = __defer_construct_new(plibrary);
//
//      //if (!estatus)
//      //{
//
//      //   return false;
//
//      //}
//
//      //if (plibrary->is_opened())
//      //{
//
//      //   return true;
//
//      //}
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
//            ::str::begins_eat_ci(strImaging, "imaging_");
//
//            ::str::begins_eat_ci(strImaging, "imaging");
//
//         }
//
//      }
//
//      ::estatus estatus = ::error_failed;
//
//      if (strLibrary.has_char())
//      {
//
//         estatus = do_factory_exchange("imaging", strLibrary);
//
//         if (estatus)
//         {
//
//            return true;
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
//      estatus = do_factory_exchange("imaging", strLibrary);
//
//      if (estatus)
//      {
//
//         return true;
//
//      }
//
//#ifdef WINDOWS_DESKTOP
//
//      if (strLibrary != "imaging_wic")
//      {
//
//         estatus = do_factory_exchange("imaging", "wic");
//
//         if (estatus)
//         {
//
//            return true;
//
//         }
//
//      }
//
//#endif
//
//      if (strLibrary != "imaging_freeimage")
//      {
//
//         estatus = do_factory_exchange("imaging", "freeimage");
//
//         if (estatus)
//         {
//
//            return true;
//
//         }
//
//      }
//
//      output_debug_string("No imaging pluging available!!.");
//
//      return false;
//
////   finalize:
////
////      PFN_factory_exchange pfn_factory_exchange = plibrary->get < PFN_factory_exchange >("imaging_factory_exchange");
////
////      if (pfn_factory_exchange == nullptr)
////      {
////
////         return false;
////
////      }
////
////      pfn_factory_exchange();
////
////      return true;
////
////#endif // CUBE
//
//   }


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

   ::estatus system::init_thread()
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

      estatus = initial_check_directrix();

      if (!estatus)
      {

         return estatus;

      }

      return true;

   }


   ::estatus system::init()
   {

      //if (::is_set(m_pdraw2d))
      //{

      //   if (!m_pdraw2d->init())
      //   {

      //      return false;

      //   }

      //}

      return true;

   }


   ::estatus system::init1()
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


   ::estatus system::initial_check_directrix()
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

      ::estatus estatus = ::apex::context_thread::inline_init();

      if (!estatus)
      {

         return estatus;

      }

      set_context_app(m_papplicationStartup);

      m_papplicationStartup->inline_init();

      get_context_application()->get_property_set().merge(get_property_set());

      m_papplicationStartup.release();

      return estatus;

   }


   ::estatus system::inline_term()
   {

      ::estatus estatus = ::apex::context_thread::inline_term();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::estatus system::init_system()
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

      //::multithreading::wait_threads(1_min, { this });

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

      //try
      //{

      //   if (m_pdraw2d.is_set())
      //   {

      //      m_pdraw2d->term();

      //   }

      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   m_mapImage.remove_all();

      //}
      //catch (...)
      //{

      //}

      //m_pdraw2d.release();

//      try
//      {
//
//#ifndef _UWP
//
//         // The Global namespace is not availabel for Windows Store App
//         ::mutex m(e_create_new, false, "Global\\ca2_datetime_departament");
//
//         sync_lock sl(&m);
//
//#endif
//
//         m_pdatetime.release();
//
//      }
//      catch (...)
//      {
//
//      }

      //m_ptrace.release();

      //m_pmath.release();


      //try
      //{

      //   sync_lock sl(&::get_context_system()->m_mutexLibrary);

      //   if (::get_context_system()->m_mapLibrary["draw2d"].is_set() && ::get_context_system()->m_mapLibrary["draw2d"]->is_opened())
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

 /*     try
      {

         m_spos.release();

      }
      catch (...)
      {

      }*/

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

      //m_ptrace.release();

      //{

      //   sync_lock sl(&m_mutexFactory);

      //   m_factorymap.remove_all();

      //}



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

         TermApplication();

      }
      catch (...)
      {

      }


   }


   void system::TermApplication()
   {

      //::apex::application::TermApplication();


#ifdef LINUX

      // dirty
      // (forcing premature gtk event loop (main loop) quitting)
      // the "most elegant" is to let just ~system (::apex::system destructor)...
      // ... do this call, but this requires all references to ::apex::system ...
      // ... to be released. This is a bit of an ideal situation that may not ...
      // ... always happen as the wish the program finishes when it is closed ...
      os_post_quit();

#elif defined(__APPLE__)

      os_post_quit();

#endif

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


   UINT system::os_post_to_all_threads(UINT uiMessage,WPARAM wparam,lparam lparam)

   {

      post_to_all_threads(uiMessage,wparam,lparam);


      return 0;

   }


   os_local & system::oslocal()
   {

      return *m_poslocal;

   }


//void system::discard_to_factory(object * pca)
//{

//   //if (m_pfactory == nullptr)
//   //{

//   //   return;

//   //}

//   //m_pfactory->discard(pca);

//}


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

      __pointer(::apex::session) psession;

      auto estatus = __construct(psession);

      if (!estatus)
      {

         return estatus;

      }

      psession->set_context_system(this);

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

      /*      m_spfilehandler(new ::apex::filehandler::handler(this));*/

//      m_mapAppLibrary.remove_all();
//
//      string strLibraryId;
//
//      ::file::listing straTitle(this);
//
//      ::file::path pathCa2Module = Context.dir().ca2module();
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
//         file = Session.file().get_file(Context.dir().appdata() / "applibcache.bin",::file::defer_create_directory | ::file::type_binary | ::file::mode_create | ::file::mode_write);
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

      if(!ansi_compare_ci(pszLibrary, "experience_core"))
      {
         TRACE("reach experience_core");
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

         Sleep(50);

      }

      strUrl = oslocal().m_strGetUserWallpaper;

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

      m_tickCommandLineLast.Now();

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

      auto appptra = Session.get_applicationa();

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

         papp->post_object(SYSTEM_MESSAGE, system_message_create, pcreate);

      }

      return true;

   }


   bool system::on_application_menu_action(const char * pszCommand)
   {

      sync_lock sl(mutex());

      auto applicationa = Session.m_applicationa;

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


   bool system::on_open_file(var varFile, string strExtra)
   {

      auto applicationa = Session.get_applicationa();

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

   //   for (auto & papp : Session.m_applicationa)
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
//   CLASS_DECL_APEX bool get_window_rect(::apex::system_window ^ pwindow, RECTD * prect)
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
//   CLASS_DECL_APEX bool get_window_rect(::apex::system_window ^ pwindow, RECT * prect)
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


//#ifdef WINDOWS_DESKTOP
//
//   BOOL CALLBACK system::monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, RECT * prcMonitor, LPARAM dwData)
//
//   {
//
//      ::apex::system * psystem = (::apex::system *) dwData;
//
//      psystem->monitor_enum(hmonitor, hdcMonitor, prcMonitor);
//
//
//      return TRUE; // to enumerate all
//
//   }
//
//   void system::monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, RECT * prcMonitor)
//
//   {
//
//      UNREFERENCED_PARAMETER(hdcMonitor);
//      UNREFERENCED_PARAMETER(prcMonitor);
//
//
//      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);
//
//      xxf_zero(m_monitorinfoa.last());
//
//      m_hmonitora.add(hmonitor);
//
//      m_monitorinfoa.last().cbSize = sizeof(MONITORINFO);
//
//      ::GetMonitorInfo(hmonitor, &m_monitorinfoa.last());
//
//      MONITORINFO mi = m_monitorinfoa.last();
//
//      TRACE("session::monitor_enum\n");
//      TRACE("upper_bound %d\n", m_monitorinfoa.get_upper_bound());
//      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
//      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);
//
//   }
//
//
//#endif



   //::image_pointer system::matter_cache_image(::layered * pobjectContext, const string & strMatter)
   //{

   //   string str(strMatter);

   //   if (!str.begins_ci("matter://"))
   //   {

   //      str = "matter://" + str;

   //   }

   //   return get_cache_image(pobjectContext, str);

   //}



   //::image_pointer system::get_cache_image(::layered * pobjectContext, const ::var & varFile)
   //{

   //   ::file::path path = varFile.get_file_path();

   //   if (path.is_empty())
   //   {

   //      return nullptr;

   //   }

   //   sync_lock sl(get_image_mutex());

   //   auto & pimage = m_mapImage[path];

   //   if (!pimage)
   //   {

   //      pobjectContext->__construct(pimage);

   //      pimage->set_nok();

   //   }

   //   return pimage;

   //}


   //::image_pointer system::get_image(::layered * pobjectContext, const ::var & varFile, bool bCache, bool bSync)
   //{

   //   auto pimage = get_cache_image(pobjectContext, varFile);

   //   if (!::is_ok(pimage))
   //   {

   //      Ctx(pobjectContext)._load_image(pimage, varFile, bSync);

   //   }

   //   return pimage;

   //}


   //::image_pointer system::matter_image(::layered * pobjectContext, const string & strMatter, bool bCache, bool bSync)
   //{

   //   string str(strMatter);

   //   if (!str.begins_ci("matter://"))
   //   {

   //      str = "matter://" + str;

   //   }

   //   return get_image(pobjectContext, str, bSync);

   //}


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

         //message_box(strMessage, MB_OK);

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

   }


   void system::__tracea(::element * pobjectContext, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
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

      if (iSel < 0 || iSel >= get_context_system()->get_context_session()->get_current_application()->m_puserlanguagemap->m_straLang.get_count())
      {

         return false;

      }

      string strLang = get_context_system()->get_context_session()->get_current_application()->m_puserlanguagemap->m_straLang[iSel];

      if (strLang == get_context_system()->get_context_session()->get_current_application()->m_puserlanguagemap->m_strLang)
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

      get_context_system()->get_context_session()->get_current_application()->m_puserlanguagemap->set_language(papp, strLang);

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

       Context.os().link_open(strUrl);

       return;

#if 0

      if (strProfile.is_empty() && strTarget.is_empty() && strBrowser.is_empty())
      {

         //::os_message_box(NULL, strUrl, strUrl, MB_OK);

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

            //MessageBox(nullptr, strParam, path, MB_OK);

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


   ::thread* system::get_thread(ITHREAD ithread)
   {

      sync_lock sl(&m_mutexThread);

      return m_threadmap[ithread];

   }


   ITHREAD system::get_thread_id(::thread* pthread)
   {

      sync_lock sl(&m_mutexThread);

      ITHREAD ithread = NULL_ITHREAD;

      if (!m_threadidmap.lookup(pthread, ithread))
      {

         return 0;

      }

      return ithread;

   }


   void system::set_thread(ITHREAD ithread, ::thread* pthread)
   {

      sync_lock sl(&m_mutexThread);

      m_threadmap[ithread].reset(pthread OBJ_REF_DBG_ADD_P_NOTE(this, "thread::thread_set"));

      m_threadidmap[pthread] = ithread;

   }


   void system::unset_thread(ITHREAD ithread, ::thread * pthread)
   {

      sync_lock sl(&m_mutexThread);

#if OBJ_REF_DBG

      m_threadmap[ithread].release(this);

#endif

      m_threadmap.remove_key(ithread);

      m_threadidmap.remove_key(pthread);

   }


////#ifdef _OPENGL
//   ::estatus system::create_gpu()
//   {
//
//      if (m_pgpu)
//      {
//
//         return ::success;
//
//      }
//
//      //System.load_library("gpu_opengl");
//
//      auto estatus = System.do_factory_exchange("gpu", "opengl");
//
//      //System.get_library("gpu_opengl");
//
//
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = __compose(m_pgpu);
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
////#endif



   ::thread_group * system::thread_group(::e_priority epriority)
   {

      //return nullptr;

      if (m_bAvoidProcFork)
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


   ::update * system::new_update(const MESSAGE& message)
   {

      //auto pupdate = new_update();

      //pupdate->m_id = (::iptr) msg.wParam;

      //pupdate->m_pobjectTopic = (::object*) msg.lParam;

      //return pupdate;

      __throw(interface_only_exception);

      return nullptr;

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


   ::estatus system::verb() // ambigous inheritance from ::apex::system/::axis::application
   {

      return ::thread::verb();

   }



   //::estatus system::init_system()
   //{

   //   if (!::apex::system::init_system())
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


   //::estatus system::init()
   //{

   //   //if (!::axis::application::init())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::apex::system::init())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void system::term_system()
   //{

   //   //      __wait_threading_count(::millis((5000) * 8));

   //         //axis::application::term_application();

   //         //::acme::del(m_phtml);

   //   try
   //   {

   //      ::apex::system::term_system();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //}


   //bool system::is_system() const
   //{

   //   return true;

   //}



   string system::crypto_md5_text(const string & str)
   {

      return crypto().md5(str);

   }


   //__pointer(::apex::session) system::on_create_session()
   //{

   //   return __new(::axis::session);

   //}


   //void system::on_request(::create * pcreate)
   //{

   //   ::apex::system::on_request(pcreate);

   //}







   //::user::document * system::place_hold(::user::interaction * pinteraction)
   //{


   //   //if(m_pcubeInterface != nullptr)
   //   //{
   //   // return m_pcubeInterface->hold(pinteraction);
   //   //}

   //   return nullptr;

   //}


   //::apex::session * system::query_session(index iEdge)
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
//#include "apex/os/windows/windows_system_interaction_impl.h"
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

   CLASS_DECL_APEX void black_body(float* r, float* g, float* b, DWORD dwTemp);

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


  //   ::estatus system::initialize_system(::object* pobject, app_core* pappcore)
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

   //   m_bInitApplicationResult      = FALSE;
   //   m_bInitApplication            = true;

   //   m_bInitApplicationResult = ::apex::system::InitApplication();

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
//      //if (!::apex::application::process_init())
//      //{
//
//      //   ERR(".1");
//
//      //   return false;
//
//      //}
//
//      if (!::apex::system::process_init())
//      {
//
//         ERR(".2");
//
//         return false;
//
//      }
//
//      ::apex::profiler::initialize();
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

   //         //if (!::apex::application::init())
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
//      //if (!::apex::application::init1())
//      //{
//
//      //   return false;
//
//      //}
//
//      if (!::apex::system::init1())
//      {
//
//         return false;
//
//      }
//
//      //if(Session.account()->create_system_user("system") == nullptr)
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

      //::apex::system::on_graphics_ready();

      //if (Session.userex()->shell()->m_bPendingUpdate)
      //{

      //   Session.userex()->shell()->on_update_sizes_interest();

      //}

   }


   //::estatus system::init3()
   //{

   //   //if(!::apex::application::init3())
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

   //   if (!::apex::system::init_system())
   //   {

   //      return false;

   //   }

   //   /*set_enum_name(::type_null      , "null");
   //   set_enum_name(::type_empty     , "is_empty");
   //   set_enum_name(::type_string    , "string");
   //   set_enum_name(::type_int32   , "integer");
   //   set_enum_name(::type_uint32     , "ulong");
   //   set_enum_name(::type_element       , "ca2");
   //   set_enum_name(::type_bool      , "bool");
   //   set_enum_name(::type_double    , "double");*/

   //   //if (!::apex::application::init_application())
   //   //{

   //   //   return false;

   //   //}

   //   //m_pbergedgemap = __new(::apex::session::map);


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
//      //::multithreading::wait_threads(40_s);
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
//      //::apex::application::term_application();
//      try
//      {
//
//         ::apex::system::term_system();
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


   //__pointer(::apex::session) system::on_create_session()
   //{

   //   return __new(::apex::session);

   //}


   //::apex::session * system::query_session(index iEdge)
   //{

   //   ::apex::session * pbergedge = nullptr;

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

#ifdef LINUX

   bool system::init_x11()
   {

      return false;

   }


   bool system::sn_start_context()
   {

      return false;

   }

#endif

   ::apex::history& system::hist()
   {

      return *m_phistory;

   }


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


   //::estatus system::add_view_library(::apex::library* plibrary)
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
   //         Session.set_locale(m_varTopicQuery["locale"].stra()[0],::source_user);
   //
   //      }
   //
   //      if(m_varTopicQuery["schema"].array_get_count() > 0)
   //      {
   //
   //         Session.set_schema(m_varTopicQuery["schema"].stra()[0],::source_user);
   //
   //      }
   //
   //   }


#ifdef _UWP


   bool system::get_window_rect(RECT* prect)
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


   ::estatus     system::main()
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


   //::type system::get_pane_tab_view_type_info()
   //{

   //   return __type(userex::pane_tab_view);

   //}




//
//   ::estatus system::initialize_system(::object* pobjectContext, ::app_core* pappcore)
//   {
//
//      auto estatus = ::apex::system::initialize_system(pobjectContext, pappcore);
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
//      g_pszCooperativeLevel = "apex";
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

   //   //apex::application::term_application();
   //   apex::system::term_system();

   //}


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


   //::count system::get_monitor_count()
   //{

   //   return ::apex::system::get_monitor_count();

   //}




//   bool system::get_monitor_rect(index iMonitor, RECT* prect)
//   {
//
//#ifdef _UWP
//
//      get_window_rect(prect);
//
//      return true;
//
//#elif defined(LINUX)
//
//
//      return ::apex::system::get_monitor_rect(iMonitor, prect);
//
//      //return os_get_monitor_rect(iMonitor, prect);
//
//
//
//#else
//
//      return ::apex::system::get_monitor_rect(iMonitor, prect);
//
//
//#endif
//
//   }


   //bool system::get_wkspace_rect(index iWkspace, RECT* prect)
   //{

   //   //#ifdef LINUX
   //   //
   //   //      xdisplay  d;
   //   //
   //   //      if(!d.open(nullptr))
   //   //         return false;
   //   //
   //   //      prect->left = 0;

   //   //      prect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

   //   //      prect->top = 0;

   //   //      prect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

   //   //
   //   //      return true;
   //   //
   //   //#else

   //   return ::apex::system::get_wkspace_rect(iWkspace, prect);


   //   //#endif

   //}

   //
   //   ::estatus system::process_init()
   //   {
   //
   //
   //      //::apex::application * papp = ::get_context_application(get_object());
   //
   //      //if (papp == nullptr)
   //      //{
   //
   //      //   set("parent_system") = nullptr;
   //
   //      //}
   //      //else
   //      //{
   //
   //      //   set("parent_system") = papp->m_psystem;
   //
   //      //}
   ////#if !defined(WINDOWS) && !defined(MACOS)
   ////
   ////      i32 error = FT_Init_FreeType((FT_Library *)&m_ftlibrary);
   ////
   ////      if (error)
   ////      {
   ////
   ////         TRACE("an error occurred during Free Type library initialization");
   ////
   ////         return false;
   ////
   ////      }
   ////
   ////#endif
   //
   //      //if (m_peengine != nullptr)
   //      //{
   //
   //      //   m_peengine = new ::exception::engine(this);
   //
   //      //}
   //
   //
   //      //if (!::apex::application::process_init())
   //        // return false;
   //
   //      if (!::apex::system::process_init())
   //         return false;
   //
   //
   //      //create_factory < ::OS::window_buffer >   (__type(::window_graphics));
   //
   //
   //
   //      //m_spos.create(this);
   //
   //
   //
   //
   //
   //      return true;
   //
   //   }


   //   bool system::initialize_native_window1()
   //   {
   //
   //#if !defined(LINUX) && !defined(WINDOWS_DESKTOP) && !defined(MACOS)
   //
   //      get_context_session()->m_puiMain = __new(::user::interaction);
   //
   //      get_context_session()->m_puiMain->initialize(get_context_session());
   //
   //#endif
   //
   //      return true;
   //
   //   }

   void system::update(::update* pupdate)
   {

      if (pupdate->m_id == id_open_hyperlink)
      {

         auto plink = pupdate->m_var.cast < ::hyperlink >();

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
      else if(pupdate->m_id == id_calc_os_dark_mode)
      {

         defer_calc_os_dark_mode();

      }


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

      //           pinteraction->call_update(pupdate);

      //        }

      //     });

   }


   void system::defer_calc_os_dark_mode()
   {

#ifdef LINUX
      string strTheme = ::os::get_os_desktop_theme();

      if(strTheme.contains_ci("dark"))
      {
         ::user::set_app_dark_mode(true);
      }
      else
      {
      ::user::set_app_dark_mode(false);
      }

#elif defined(WINDOWS_DESKTOP)

      ::user::set_system_dark_mode(::user::calc_system_dark_mode());

      ::user::set_app_dark_mode(::user::calc_app_dark_mode());

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

   //::type system::get_pane_tab_view_type_info()
   //{

   //   return m_typePaneTabView;

   //}


   void system::finalize()
   {

      ::apex::context_thread::finalize();

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

            wait_future future;

            os_message_box(strMessage, "Could not open required library.", MB_ICONEXCLAMATION, future);

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

   auto pobject = move_transfer(pstaticsetup->new_object());

   if (!pobject)
   {

      return nullptr;

   }

   return pobject.cast < ::apex::system >();

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

} // namespace apex



void apex_system_call_update(int iUpdate, const ::var& var)
{

   auto pupdate = new_update();

   pupdate->m_id = iUpdate;

   pupdate->m_var = var;

   ::get_context_system()->call_update(pupdate);

}
