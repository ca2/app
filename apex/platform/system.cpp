#include "framework.h"
#include "apex/operating_system.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "apex/platform/app_core.h"
#include "acme/id.h"
//#include "apex/node/_node.h"
#include "acme/platform/profiler.h"
#include "acme/platform/static_setup.h"
#include "apex/id.h"
#ifdef LINUX
#include <unistd.h>
#endif
#include "apex/platform/node.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/parallelization/install_mutex.h"


//extern ::apex::system* g_papexsystem;

//CLASS_DECL_APEX void apex_generate_random_bytes(void* p, memsize s);

//int GetMainScreenRect(RECTANGLE_I32 * lprect);


///const ::string & g_pszMultimediaLibraryName = nullptr;

void apex_system_update(const ::id & id, const ::payload & payload);

void apex_system_set_modified(const ::id& id);


// CLASS_DECL_APEX void multimedia_set_library_name(const ::string & psz)
// {

//    g_pszMultimediaLibraryName = psz;

// }


// CLASS_DECL_APEX const ::string & multimedia_get_library_name()
// {

//    return g_pszMultimediaLibraryName;

// }


#ifdef CUBE
extern "C"
::acme::library * experience_get_new_library();
#endif



#ifdef LINUX
#include <sys/time.h>
#endif

CLASS_DECL_APEX void __simple_tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


//void os_post_quit();


#ifdef UNIT_TEST
void unit_test_primitive_var_apex_block();
#endif


void dappy(const ::string & psz);


#ifdef WINDOWS_DESKTOP

#include <Lmcons.h>

string get_user_name()
{
   
   WCHAR wsz[UNLEN * 2];

   DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);

   ::GetUserNameW(wsz,&dwSize);

   return string(wsz);

}

//#include "acme/node/operating_system/windows/_c.h"
#endif



namespace apex
{


   system::system()
   {

      m_papexsystem = this;

      ::factory::add_factory_item < ::thread >();

      ::factory::add_factory_item<::apex::idpool, ::acme::idpool >();

      m_edisplay = e_display_default;

      //set_layer(LAYERED_APEX, this);

#ifdef _UWP

      m_bPreferLessGraphicsParallelization = true;

#else

      m_bPreferLessGraphicsParallelization = false;

#endif

      m_bMessageThread = true;

      m_bSystemSynchronizedCursor = true;
      m_bSystemSynchronizedScreen = true;

      common_construct();

   }


   void system::common_construct()
   {

      ::factory::add_factory_item < ::apex::session >();
      ::factory::add_factory_item < ::application >();
      //add_factory_item < ::imaging >();

      m_bSimpleMessageLoop = false;

      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;

      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

   }


#ifdef _DEBUG


   i64 system::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::system::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 system::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::system::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   ::e_status system::initialize(::object * pobject)
   {

      auto estatus = ::apex::context::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_pcontext = this;

      __compose_new(m_pthreading);

      ::datetime::time timeNow = ::datetime::time::now();

      auto pnode = node();

      if (pnode)
      {

         if (timeNow.hour() >= 6 && timeNow.hour() <= 17)
         {

            pnode->set_simple_ui_darkness(0);

         }
         else
         {

            pnode->set_simple_ui_darkness(255);

         }

      }


      set_callstack_mask({ get_callstack_mask(), callstack_fork_global});

#if !defined(_UWP) && !defined(ANDROID)

      m_pmutexMatter = __new(::mutex(this, false, "Local\\ca2-appmatter"));

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

#ifdef __DEBUG

      estatus = __compose_new(m_pdumpcontext);

      if (!estatus)
      {

         return estatus;

      }

#endif

#ifndef WINDOWS

      exception_translator::attach();

#endif

      m_nSafetyPoolSize = 512;        // default size_i32

      estatus = __compose_new(m_pgeometry);

      if (!estatus)
      {

         return estatus;

      }

      string strId;
      strId = "ca2log";

      if (!initialize_log(strId))
      {

         throw ::exception("failed to initialize log");

      }

      {

         bool bGlobalEnableStackTrace = true;

         ::file::path pathNoExceptionStackTrace = m_psystem->m_pacmedir->config() / "system/no_exception_stack_trace.txt";

         if (m_psystem->m_pacmefile->exists(pathNoExceptionStackTrace))
         {

            bGlobalEnableStackTrace = false;

         }

         ::exception::exception_enable_stack_trace(bGlobalEnableStackTrace);

      }

      //add_factory_item < ::stdio_file, ::file::text_file >();
      //add_factory_item < ::stdio_file, ::file::file >();
      ::factory::add_factory_item < ::i64_array >();
      ::factory::add_factory_item < ::double_array >();
      ::factory::add_factory_item < ::acme::library >();

      ::factory::add_factory_item < ::file::path_object >();

      ::factory::add_factory_item < string_array >();
      ::factory::add_factory_item < memory >();
      ::factory::add_factory_item < memory_file >();
      ::factory::add_factory_item < int_array >();

      ::factory::add_factory_item < ::file::path_object >();
      ::factory::add_factory_item < ::i64_array >();
      ::factory::add_factory_item < ::double_array >();
      ::factory::add_factory_item < ::acme::library >();

      ::factory::add_factory_item < ::file::path_object >();

      ::factory::add_factory_item < string_array >();
      ::factory::add_factory_item < memory >();
      ::factory::add_factory_item < memory_file >();
      ::factory::add_factory_item < int_array >();

      estatus = __compose_new(m_pdatetime);

      if (!estatus)
      {

         return estatus;

      }

      thread::s_bAllocReady = true;

      estatus = __compose_new(m_purldepartment);

      if (!estatus)
      {

         return estatus;

      }

//#ifdef WINDOWS_DESKTOP
//
//      m_uiWindowsTaskbarCreatedMessage = 0;
//
//#endif

      return estatus;

   }


   void system::install_message_routing(::channel* pchannel)
   {

      ::apex::context::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_erase_session, pchannel, this, &system::on_message_erase_session);

   }


   void system::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   {


   }


   string system::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   void system::on_add_session(::apex::session* papexsession)
   {

      if (papexsession->m_iEdge == 0)
      {

         if (!m_papexsession)
         {

            m_papexsession = papexsession;

         }

      }

      papexsession->m_pacmesystem = this;
      papexsession->m_pacmesystem = this;

   }


   void system::add_session(index iEdge, ::apex::session * psession)
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

      on_add_session(psession);

   }


   void system::erase_session(index iEdge)
   {

      auto psession = m_sessionmap[iEdge];

      m_sessionmap.erase_key(iEdge);

      if (m_sessionmap.is_empty() && m_bFinalizeIfNoSession)
      {

         set_finish();

      }

      if (psession)
      {

         duration duration;

         duration.Now();

         while (true)
         {

            if (psession->m_countReference <= 1)
            {

               break;

            }

            preempt(100_ms);

            if (duration.elapsed() > 10_s)
            {

               break;

            }

         }

      }

   }


   bool system::on_get_task_name(string& strTaskName)
   {

      if (is_console_app())
      {

         return false;

      }

      return ::apex::context::on_get_task_name(strTaskName);

   }


   system::~system()
   {

#ifndef WINDOWS

      exception_translator::detach();

#endif

   }


   __transport(::factory::factory) & system::node_factory()
   {

      auto & pfactory = factory("apex", PLATFORM_NAME);

      if(!pfactory)
      {

         return pfactory;

      }

      pfactory->merge_to_global_factory();

      return pfactory;

   }


   ::e_status system::process_init()
   {

      
      ::factory::add_factory_item<::create>();
      ::factory::add_factory_item<command_line>();
      ::factory::add_factory_item<http::context>();

      auto estatus = ::system::process_init();

      if (!estatus)
      {

         return estatus;

      }


#if !defined(ANDROID)

      if (!m_papplicationStartup->is_service() || m_papplicationStartup->is_user_service())
      {

         m_pmutexUserAppData = __new(::mutex(this, false, "Local\\ca2.UserAppData"));
         m_pmutexSystemAppData = __new(::mutex(this, false, "Local\\ca2.SystemAppData"));

      }

#endif


      // estatus = ([a-z0-9_]+)_factory("apex", PLATFORM_NAME);

      // if (!estatus)
      // {

      //    return estatus;

      // }

      //estatus = __compose(m_papexnode);

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      set_system_update(&apex_system_update);

      //set_system_set_modified(&apex_system_set_modified);

      estatus = system_prep();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::init1()
   {

      auto estatus = ::system::init1();

      if (!estatus)
      {

         return estatus;

      }

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

      if (m_bWriteText.undefined())
      {

         m_bWriteText = m_bDraw2d;

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

      //string strAppId = m_papplicationStartup->m_strAppId;


#if !defined(_UWP)


      if (is_true("show_application_information"))
      {

         printf("%s", "\n\nApplication Information\n");
         output_debug_string("\n\nApplication Information\n");

         int iPid;

         iPid = ::get_current_process_id();

         printf("%s", ("Process PID: " + __string(iPid) + "\n").c_str());
         output_debug_string("Process PID: " + __string(iPid) + "\n");

      }


#endif


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

      {

         {

#ifdef WINDOWS_DESKTOP

            {

               ASSERT(m_hinstancePrev == nullptr);

               HINSTANCE hinstance = (HINSTANCE)m_hinstanceThis;

               //auto edisplay = m_edisplay;

               // handle critical errors and avoid Windows message boxes
               SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

               //m_edisplay = edisplay;

               //SetCurrentHandles();

            }

#endif

         }

      }

      //estatus = __compose_new(m_pxml);

      //if (!estatus)
      //{

      //   throw ::exception(estatus);

      //}

      //m_pxml->initialize(this);

      //if (!m_pxml->init1())
      //{
      //   __throw(::exception("failed to construct system m_pxml->init1()"));

      //}

      //if (!m_pxml->init())
      //{

      //   __throw(::exception("failed to construct system m_pxml->initialize()"));

      //}

      //add_factory_item < application_bias >();

      //add_factory_item < ::mutex >();
      //add_factory_item < event >();

      //if (!::application::process_init())
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

                           auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->create("/ca2core");

                  m_psystem->m_pacmefile->put_contents("/ca2core/teste.txt", str, str.length());
                  */
#endif

#if 0

         // Create authorization object
         OSStatus status;

         AuthorizationRef authorizationRef;

         // AuthorizationCreate and pass nullptr as the initial
         // AuthorizationRights set so that the AuthorizationRef gets created
         // successfully, and then later call AuthorizationCopyRights to
         // determine or extend the allowable rights.
         // http://developer.apple.com/qa/qa2001/qa1172.html
         status = AuthorizationCreate(nullptr, kAuthorizationEmptyEnvironment,
            kAuthorizationFlagDefaults, &authorizationRef);

         if (status != errAuthorizationSuccess)
         {
            FORMATTED_TRACE("Error Creating Initial Authorization: %d", status);

            return false;

         }

         // kAuthorizationRightExecute == "system.privilege.admin"
         AuthorizationItem right = { kAuthorizationRightExecute, 0, nullptr, 0 };

         AuthorizationRights rights = { 1, &right };

         AuthorizationFlags flags = kAuthorizationFlagDefaults |
            kAuthorizationFlagInteractionAllowed |
            kAuthorizationFlagPreAuthorize |
            kAuthorizationFlagExtendRights;

         // Call AuthorizationCopyRights to determine or extend the allowable rights.

         status = AuthorizationCopyRights(authorizationRef, &rights, nullptr, flags, nullptr);

         if (status != errAuthorizationSuccess)
         {

            FORMATTED_TRACE("Copy Rights Unsuccessful: %d", status);

            return false;

         }

#endif

      }

      if (!m_pmachineeventcentral)
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

         if (m_pmachineeventcentral->is_close_application())
         {

            return false;

         }

#endif

      }

      estatus = __compose(m_pfilesystem);

      if(!estatus)
      {

         ERROR("failed to initialize file-system");

         return estatus;

      }

      estatus = __compose(m_pdirsystem);

      if (!estatus)
      {

         ERROR("failed to initialize dir-system");

         return false;

      }

      ///INFORMATION("apex::session::process_init .3");

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

      //estatus = ::apex::context::initialize_context();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = m_psystem;

      auto pdatetime = psystem->datetime();

      string strLogTime = pdatetime->international().get_date_time_for_file_with_no_spaces();

      strLogTime.replace("-", "/");

      strLogTime.replace("_", "/");

      {

         string_array straCmds;

         for (int i = 0; i < m_argc; i++)
         {

            if (m_argv && m_argv[i])
            {

               char* thisCmd = m_argv[i];

               straCmds.add(thisCmd);

            }
            else if (m_wargv && m_wargv[i])
            {

               wchar_t* thisCmd = m_wargv[i];

               straCmds.add(thisCmd);

            }

         }

         string strCmd = straCmds.implode("\n");

         string strAppId = m_strAppId;

         string strCmdLineDumpFileName = strAppId / strLogTime + "-command_line.txt";

         ::file::path pathCmdLineDumpFile = m_psystem->m_pacmedir->home() / "application" / strCmdLineDumpFileName;

         m_psystem->m_pacmefile->put_contents(pathCmdLineDumpFile, strCmd);

      }

      {

         string_array straEnv;

         if (m_wenvp)
         {

            for (auto wenv = m_wenvp; *wenv != 0; wenv++)
            {

               auto thisEnv = *wenv;

               straEnv.add(thisEnv);

            }

         }
         else if (m_envp)
         {

            for (auto env = m_envp; *env != 0; env++)
            {

               auto thisEnv = *env;

               straEnv.add(thisEnv);

            }

         }

         string strEnv = straEnv.implode("\n");

         string strAppId = m_strAppId;

         string strEnvDumpFileName = strAppId / strLogTime + "-environment_variables.txt";

         ::file::path pathEnvDumpFile = m_psystem->m_pacmedir->home() / "application" / strEnvDumpFileName;

         m_psystem->m_pacmefile->put_contents(pathEnvDumpFile, strEnv);

      }

//      {
//
//         string strCurrentWorkingDirectory;
//
//         strCurrentWorkingDirectory = get_current_directory_name();
//
//         ::output_debug_string("\nCurrent Working Directory : " + strCurrentWorkingDirectory);
//
//      }

      //estatus = m_ptracelog->process_init();

      //if(!estatus)
      //{

         //WARNING("failed to process_init ::apex::log trace");

      //}

      estatus = initialize_context();

      if (!estatus)
      {

         return estatus;

      }

      auto & pfactoryCrypto = factory("crypto", "openssl");

      if (!pfactoryCrypto)
      {

         WARNING("Could not open crypto openssl plugin.");

         return pfactoryCrypto;

      }

      pfactoryCrypto->merge_to_global_factory();

      estatus = pfactoryCrypto->__compose(this, m_pcrypto);

      if(!estatus)
      {

         return estatus;

      }

      if (!::is_set(m_pcrypto))
      {

         return false;

      }

      on_update_matter_locator();

      estatus = initialize_sockets();

      if (!estatus)
      {

         m_estatus = estatus;

         return estatus;

      }

      bool bMatterFromHttpCache = false;

      bool bMatterFromResource = false;

      auto pfile = m_papexsystem->file().create_resource_file("app/_matter/main/_std/_std/thomasborregaardsorensen.txt");

      if (pfile)
      {

         bMatterFromResource = true;

      }

      if (bMatterFromResource)
      {

         m_pdirsystem->m_bMatterFromHttpCache = false;

         m_pdirsystem->m_bMatterFromResource = true;

      }
      else
      {

         if (m_iMatterFromHttpCache == -1)
         {

            ::file::path pathSide = m_pcontext->m_papexcontext->side_get_matter_path("app/_matter/main");

            ::file::path pathLocal = local_get_matter_path("app/_matter/main");

            bool bFileSystemMatter = m_pacmedir->is(pathSide) || m_pacmedir->is(pathLocal);

            bMatterFromHttpCache = !bFileSystemMatter;

         }
         else
         {

            bMatterFromHttpCache = m_iMatterFromHttpCache != 0;

         }

         m_pdirsystem->m_bMatterFromHttpCache = bMatterFromHttpCache;

         m_pdirsystem->m_bMatterFromResource = false;

      }

      //estatus = create_html();

      //if (!estatus)
      //{

      //   FATAL("axis::application::process_init .2");

      //   return false;

      //}

      //INFORMATION("start");

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
//      ::user::aaa_g_defer_init();
//
//#endif // LINUX

      //INFORMATION("success");

//      return true;


//#ifdef _DEBUG
//
//      ___compile_test_sort_array_21304528734();
//
//#endif



      //__throw(todo("filehandler"));

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
//      find_applications_from_cache();
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

      auto strMain = m_pcontext->m_papexcontext->dir().install() / "app/_appmatter/main";

      if (!m_ptexttable->load(strMain))
      {

         return error_failed;

      }

      return true;

   }


   ::e_status system::init2()
   {

      ::e_status estatus = create_session();

      if (!estatus)
      {

         //output_error_message("Failed to allocate get_session()!!");

         output_debug_string("Failed to allocate get_session()!!");

         return estatus;

      }

      if (m_bConsole)
      {

         estatus = get_session()->inline_init();

         if (!estatus)
         {

            return estatus;

         }

      }
      else
      {

         if (!m_papexsession->begin_synch())
         {

            output_debug_string("\nFailed to begin_synch the session (::apex::session or ::apex::session derived)");

            return false;

         }

      }

      estatus = __compose_new(m_ptexttable);

      if (!m_ptexttable || !estatus)
      {

         return estatus;

      }

      auto psession = get_session();

      psession->m_ptextcontext->defer_ok(m_ptexttable);


      //if(!::application::init2())
      //   return false;

      //auto estatus = ::apex::system::init2();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      estatus = __compose_new(m_phistory);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::initialize_context()
   {

      auto estatus = ::apex::context::initialize_context();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::on_system_construct()
   {

      //auto estatus = create_os_node();

      //if(m_bUser)
      //{

      //   if (!estatus)
      //   {

      //      return estatus;

      //   }

      //}

      //return estatus;

      return ::success;

   }


   ::e_status system::on_start_system()
   {

      auto estatus = ::system::on_start_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


//   ::e_status system::start()
//   {
//
//      auto pnode = Node;
//
//      ::e_status estatus = error_exception;
//
//      if(pnode)
//      {
//
//         estatus = pnode->start();
//
//      }
//      else
//      {
//
//         estatus = on_start_system();
//
//      }
//
//      return estatus;
//
//   }
//
//
//   void system::get_time(micro_duration * pmicroduration)
//   {
//
//
//#ifdef _WIN32
//      
//      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
//      
//      GetSystemTimeAsFileTime(&ft);
//      
//      u64 tt;
//      
//      ::memcpy_dup(&tt, &ft, sizeof(tt));
//
//      tt /= 10; // make it usecs
//      
//      pmicroduration->m_secs = (long)tt / 1'000'000;
//      
//      pmicroduration->m_micros = (long)tt % 1'000'000;
//
//#else
//
//      struct timeval timeval;
//
//      gettimeofday(&timeval, nullptr);
//
//      pmicroduration->m_secs = timeval.tv_sec;
//
//      pmicroduration->m_micros = timeval.tv_usec;
//
//#endif
//
//
//   }
//

   ::e_status system::init_thread()
   {

      //auto estatus = ([a-z0-9_]+)_factory();

      //if(!estatus)
      //{

        // return estatus;

      //}

      auto estatus = process_init();

      if(!estatus)
      {

         return estatus;

      }

      if (m_psystemParent)
      {

         m_psystemParent->add_reference(this);

      }


      if (!estatus)
      {

         return estatus;

      }

      estatus = init1();

      if(!estatus)
      {

         return estatus;

      }

      estatus = init2();

      if (!estatus)
      {

         return estatus;

      }


//      estatus = process_init();
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }


      //estatus = process_creation_requests();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return true;

   }


   ::e_status system::init()
   {

      return true;

   }




   ::e_status system::post_creation_requests()
   {

      //while(auto pcreate = get_command()->get_create())
      while (auto pcreate = get_create())
      {

         do_request(pcreate);

      }

      return true;

   }


   ::e_status system::post_initial_request()
   {

      //auto papp = m_papplicationMain;

      //auto psession = m_papexsession;

      //papp->initialize(psession);

      //set_main_struct(*papp);

      //papp->inline_init();
      
      m_bPostedInitialRequest = true;

      auto pcreate = __create_new< ::create>();

      string strAppId = m_strAppId;

      if (strAppId.is_empty())
      {

         if (m_papplicationStartup)
         {

            strAppId = m_papplicationStartup->m_strAppId;

         }

      }

      pcreate->m_strAppId = strAppId;

      pcreate->m_pcommandline = __create_new < command_line >();

      string strCommandLine = get_command_line();

      pcreate->m_pcommandline->initialize_command_line(strCommandLine);

      pcreate->finish_initialization();

      add_create(pcreate);

      post_creation_requests();

      return ::success;

   }


   ::e_status system::inline_init()
   {

      auto estatus = ::system::inline_init();

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::apex::context::inline_init();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::inline_term()
   {

      ::e_status estatus = ::apex::context::inline_term();

      if (!estatus)
      {

         return estatus;

      }

#if OBJECT_REFERENCE_COUNT_DEBUG

      release(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, nullptr));

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

      //if (m_papplication)
      //{

      //   estatus = m_papplication->m_estatus;

      //}

      return estatus;

   }


   ::application* system::get_main_application()
   {

      return m_papplicationMain;

   }


   ::e_status system::init_system()
   {

      auto estatus = ::system::init_system();

      if(!estatus)
      {

         return estatus;

      }

      auto papplicationStartup = new_application(m_strAppId);

      if (!papplicationStartup)
      {

         return -1;

      }

      __refer(m_papplicationStartup, papplicationStartup);

      m_papplicationStartup->initialize(this);

      m_papplicationStartup->get_property_set().merge(get_property_set());

      set_main_struct(*m_papplicationStartup);

      return estatus;

   }


   void system::term()
   {

      m_psignalmap.release();

      __release(m_phistory);

   }


   void system::on_message_erase_session(::message::message * pmessage)
   {

      auto iEdge = pmessage->m_wparam;

      erase_session(iEdge);

   }


   string system::get_application_server_name()
   {

      string strApplicationServerName = m_strAppId;

      strApplicationServerName.replace("/", ".");

      strApplicationServerName.replace("_", "-");

      return strApplicationServerName;

   }


   bool system::task_get_run() const
   {

      return ::apex::context::task_get_run();

   }


   void system::term1()
   {

   }


   void system::term2()
   {

      try
      {

         if (m_pmachineeventcentral)
         {

            m_pmachineeventcentral->destroy();

         }

      }
      catch (...)
      {

      }

   }


   ::e_status system::thread_loop()
   {

      return thread::thread_loop();

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


   //void system::post_to_all_threads(const ::id & id, WPARAM wparam, LPARAM lparam)
   //{

   //   synchronous_lock synchronouslock(m_mutexThread);

   //   for (auto& pair : get_system()->m_threadidmap)
   //   {

   //      try
   //      {

   //         pair.element1()->post_message(message, wparam, lparam);

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //}



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

      ::system::TermSystem();

   }


   ::e_status system::create_os_node()
   {

      ::e_status estatus = ::success;

      estatus = ::system::create_os_node();

      if(!estatus)
      {

         return estatus;

      }

//      estatus = m_pnode->initialize(this);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      return estatus;

   }




   void system::process_term()
   {

      //::application::process_term();



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


   ::u32 system::os_post_to_all_threads(const ::id & id,wparam wparam,lparam lparam)
   {

      post_to_all_threads(id,wparam,lparam);

      return 0;

   }


   bool system::is_system() const
   {

      return true;

   }


   i32 system::_001OnDebugReport(i32 i1,const ::string & psz1,i32 i2,const ::string & psz2,const ::string & psz3,va_list args)
   {

      return _debug_logging_report(i1,psz1,i2,psz2,psz3,args);

   }


   i32 system::_debug_logging_report(i32 iReportType, const ::string & pszFileName, i32 iLineNumber, const ::string & pszModuleName, const ::string & pszFormat,va_list list)
   {

      //if(!m_ptracelog || !m_ptracelog->m_bExtendedLog)
      //{

      //   return ::apex::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);

      //}

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

            str2.format(pszFormat,list);

         }
         //     else
         {

            //          str2 = pszFormat;

         }

      }

      str = str + str2;

      string strPrint(str);

      strPrint.replace("%","%%");

      //if(m_ptracelog)
      //{

      //   m_ptracelog->print(strPrint);

      //}

      INFORMATION(strPrint);

      if(iReportType == _CRT_ASSERT)
      {

         return 1;

      }
      else
      {

         return 0;

      }

   }




   bool system::assert_failed_line(const ::string & pszFileName,i32 iLine)

   {
      __UNREFERENCED_PARAMETER(pszFileName);

      __UNREFERENCED_PARAMETER(iLine);
      return false;
   }


   bool system::on_assert_failed_line(const ::string & pszFileName,i32 iLine)

   {
      __UNREFERENCED_PARAMETER(pszFileName);

      __UNREFERENCED_PARAMETER(iLine);
      return true;
   }


   void system::__set_thread_on()
   {

      ::thread::__set_thread_on();

   }


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




   //class ::str::base64 & system::base64()
   //{

   //   return *m_pbase64;

   //}


   //::apex::log & system::log()
   //{

   //   return *m_ptracelog;

   //}



   machine_event_central & system::machine_event_central()
   {
      return *m_pmachineeventcentral;
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


   ::operating_system::department & system::process()
   {

      return *m_pprocess;

   }


   ::e_status system::initialize_log(const ::string & pszId)
   {

      //if (m_ptracelog)
      //{

      //   return ::success_none;

      //}

      //m_ptracelog = __create_new < ::apex::log >();

      //if (!m_ptracelog)
      //{

      //   return error_no_memory;

      //}

      //m_ptracelog->set_extended_log();

      //auto estatus = m_ptracelog->initialize_log(e_trace_level_warning, pszId);

      //if(!estatus)
      //{

      //   __release(m_ptracelog);

      //   return estatus;

      //}

      return ::success;

   }





   void system::appa_load_string_table()
   {

      //retry_single_lock rsl(mutex(),::duration(100),::duration(100));

//      for(i32 i = 0; i < appptra().get_size(); i++)
      //    {
      //     ::application * papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }


   void system::appa_set_locale(const ::string & pszLocale, const ::action_context & context)
   {

      //retry_single_lock rsl(mutex(),::duration(100),::duration(100));
      single_lock rsl(mutex());

      rsl.lock(10_s);

//      for(i32 i = 0; i < appptra().get_size(); i++)
//     {
      //       ::application * papp = appptra()(i);
      //       papp->set_locale(pszLocale,context);
      //    }

   }


   void system::appa_set_schema(const ::string & pszStyle, const ::action_context & context)
   {

      //retry_single_lock rsl(mutex(),::duration(100),::duration(100));
      single_lock rsl(mutex());

      rsl.lock(10_s);

//      for(i32 i = 0; i < appptra().get_size(); i++)
      //    {
      //       ::application * papp = appptra()(i);
      //       papp->set_schema(pszStyle,context);
      //    }

   }



   bool system::assert_running_global(const ::string & pszAppName,const ::string & pszId)
   {

      if(string(pszId).has_char())
      {

         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_id_mutex_name(pszAppName, pszId));
         auto pmutex = ::open_mutex(this, get_global_id_mutex_name(pszAppName,pszId));

         if(pmutex == nullptr)
         {

            string strApp = pszAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__APPLE__)

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, m_pcontext->m_papexcontext->dir().module() / strApp, strParameters, nullptr, e_display_normal);

            plauncher->launch();

#else

            __throw(todo);

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
         auto pmutex = ::open_mutex(this, get_global_mutex_name(pszAppName));
         if(pmutex == nullptr)
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#if defined(_UWP)

            __throw(todo);

#else

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, m_pcontext->m_papexcontext->dir().module() / strApp, nullptr, nullptr, e_display_normal);

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

   bool system::assert_running_local(const ::string & pszAppName,const ::string & pszId)
   {
      string strAppName(pszAppName);
      string strId(pszId);
      if(strId.has_char())
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_id_mutex_name(pszAppName, strId));
         auto pmutex = ::open_mutex(this, get_local_id_mutex_name(pszAppName,strId));
         if(pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef _UWP

            __throw(todo);

#else

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, m_pcontext->m_papexcontext->dir().module() / strApp, strParameters, nullptr, e_display_normal);

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
         auto pmutex = ::open_mutex(this, get_local_mutex_name(pszAppName));
         if(pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef _UWP

            __throw(todo);

#else

            auto plauncher = __create < ::apex::shell_launcher >();
            
            plauncher->setup(nullptr, nullptr, m_pcontext->m_papexcontext->dir().module() / strApp, strParameters, nullptr, e_display_normal);

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


   //string system::crypto_md5_text(const ::string & str)
   //{

   //   throw interface_only_exception();

   //   return "";

   //}


   void system::install_progress_add_up(int iAddUp)
   {

      __UNREFERENCED_PARAMETER(iAddUp);

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

      add_session(iEdge, psession);

      return ::success;

   }


   __transport(::apex::session) system::on_create_session(index iEdge)
   {

      __pointer(::apex::session) psession;

      auto estatus = __construct(psession);

      if (!estatus)
      {

         return estatus;

      }

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

      INFORMATION("::apex::system::on_request session = " << __type_name(psession) << "(" << __string((iptr) psession) << ")");

      psession->do_request(pcreate);

   }


   ::file::path system::local_get_matter_path()
   {

      return m_psystem->m_pacmedir->ca2roaming() / "appmatter";

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

      return m_psystem->m_pacmedir->ca2roaming() / "cache/appmatter";

   }


   ::file::path system::local_get_matter_cache_path(string strMatter)
   {

      return local_get_matter_cache_path() / strMatter;

   }


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
////      file_pointer pfile = m_pcontext->m_papexcontext->file().get_file(m_pcontext->m_papexcontext->dir().appdata() / "applibcache.bin",::file::e_open_binary | ::file::e_open_read);
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
//      /*      m_spfilehandler(new ::apex::filehandler::handler(this));*/
//
////      m_mapAppLibrary.erase_all();
////
////      string strLibraryId;
////
////      ::file::listing straTitle(this);
////
////      ::file::path pathCa2Module = m_pcontext->m_papexcontext->dir().ca2module();
////
////      ::output_debug_string("\n\n::apex::system::find_applications_to_cache\n\n");
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
////         file = psession->file().get_file(m_pcontext->m_papexcontext->dir().appdata() / "applibcache.bin",::file::e_open_defer_create_directory | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_write);
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
//      library.initialize_library(this, 0);
//
//      if(!strcmp(pszLibrary,"app_core_rdpclient"))
//      {
//         INFORMATION("reach");
//      }
//
//      if(!ansi_compare_ci(pszLibrary, "app_core_hellomultiverse"))
//      {
//         INFORMATION("reach app_core_hellomultiverse");
//      }
//
//      if(!ansi_compare_ci(pszLibrary, "experience_lite"))
//      {
//         INFORMATION("reach experience_lite");
//      }
//
//      if(!ansi_compare_ci(pszLibrary, "app_core_hellomultiverse"))
//      {
//         INFORMATION("reach app_core_hellomultiverse");
//      }
//
//      if(!library.open(pszLibrary, true))
//      {
//         INFORMATION("::system::map_application_library Failed to open library :" << pszLibrary);
//         return false;
//      }
//
//      //if(!library.open_library())
//      //{
//
//      //   ::output_debug_string("::system::map_application_library open_ca2_library(2) Failed :" + string(pszLibrary) + "\n\n");
//
//      //   return false;
//
//      //}
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
//

   void system::do_request(::create * pcreate)
   {

      //if (pcreate->m_ecommand == ::command_check_exit)
      //{

      //   return ::success;

      //}

      //on_request(pcreate);

      ::thread::do_request(pcreate);

   }




   //string system::url_encode(const ::string & str)
   //{

   //   //throw ::interface_only_exception();

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

   ::crypto::crypto * system::crypto()
   {

      return m_pcrypto;

   }


   //__pointer(::account::user_set) system::userset()
   //{

   //   return m_puserset;

   //}


   bool system::defer_accumulate_on_open_file(string_array stra, string strExtra)
   {

      synchronous_lock synchronouslock(mutex());

      m_durationCommandLineLast.Now();

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

      auto psession = get_session();

      auto appptra = psession->get_applicationa();

      ::application * papp = nullptr;

      appptra.predicate_erase([](auto & papp)
      {

         return papp->is_system() || papp->is_session();

      });

      if(appptra.has_elements())
      {

         papp = appptra[0];

      }

      if(papp != nullptr)
      {

         __pointer(::create) pcreate(e_create_new, this);

         merge_accumulated_on_open_file(pcreate)
;
         papp->post_element(e_message_system, e_system_message_create, pcreate);

      }

      return true;

   }




   bool system::merge_accumulated_on_open_file(::create * pcreate)
   {

      if(m_straCommandLineAccumul.is_empty())
      {

         return true;

      }

      string_array straAccumul = m_straCommandLineAccumul;

      string_array straExtra = m_straCommandLineExtra;

      m_straCommandLineAccumul.erase_all();

      m_straCommandLineExtra.erase_all();

      command_line_pointer line(e_create_new, this);

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


   bool system::on_open_file(::payload payloadFile, string strExtra)
   {

      //auto psession = get_session();

      //auto applicationa = psession->get_applicationa();

      //::application * papp = nullptr;

      //if(applicationa.get_size() > 0)
      //{

      //   papp = applicationa[0];

      //}
      //else
      //{

      //   return false;

      //}

      //if(papp != nullptr)
      //{

      //   if(payloadFile.is_empty())
      //   {

      //      papp->request({"app.exe : open_default " + strExtra});

      //   }
      //   else
      //   {

      //      papp->request({"app.exe \"" + payloadFile.get_file_path() + "\" " + ::str::has_char(strExtra, " : ")});

      //   }

      //   return true;

      //}

      return false;

   }


   ::e_status system::on_open_file(const ::string & pszFile)
   {
      
      defer_accumulate_on_open_file({pszFile}, "");
      
      return ::success;
      
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
////      m_monitorinfoa.erase_all();
////
////      ::EnumDisplayMonitors(nullptr, nullptr, psystem::monitor_enum_proc, (LPARAM)(dynamic_cast < ::apex::system * > (this)));
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

      return m_psystem->m_pacmefile->as_string(m_pcontext->m_papexcontext->dir().standalone() / (str + ".txt"));

   }


   bool system::set_standalone_setting(string str, string strSetting)
   {

      return m_psystem->m_pacmefile->put_contents(m_pcontext->m_papexcontext->dir().standalone() / (str + ".txt"), strSetting);

   }


   void system::on_extra(string str)
   {

      auto psystem = m_psystem;

      auto purl = psystem->url();

      string strProtocol = purl->get_protocol(str);

#ifdef WINDOWS_DESKTOP

      if (strProtocol == "ca2project")
      {

         string strBase = purl->get_server(str);

         string strAppId = purl->get_script(str);

         ::str::begins_eat(strAppId, "/");

         string strQuery = purl->get_query(str);

         string strMessage;

         strMessage.format("protocol: ca2project\nbase: %s\nAppId: %s\nquery: %s\n", strBase, strAppId, strQuery);

         //message_box(strMessage, e_message_box_ok);

         string strParams;

         //strParams.format("\"ca2project\" \"%s\" \"%s\" \"%s\"\n", strBase, strAppId, strQuery);

         string strProj;

         strProj = strAppId;

         string_array stra;

         stra.explode("/", strAppId);

         strProj.replace_ci("-", "_");
         strProj.replace_ci("/", "_");

         //strProj = "..\\..\\..\\" + stra[0] + "\\" + stra[1] + "\\" + stra[1] + ".vcxproj";

         strParams.format("\"openvsproject://%s\"", strProj);


         //int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", e_display_none, 30, 1000, nullptr, 0);

      }
#elif defined MACOS
      if (strProtocol == "ca2project")
      {

         string strBase = purl->get_server(str);

         string strScheme = purl->get_script(str);

         ::str::begins_eat(strScheme, "/");

         if(strBase == "scheme")
         {

//         int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", e_display_none, 30, 1000, nullptr, 0);

            ::file::path pathScript = m_psystem->m_pacmedir->tool() / "papaya/script/xcode_set_active_scheme.scpt";

            ::system("osascript \""+pathScript + "\" \"" + strScheme + "\"");

         }
         else if(strBase == "archive")
         {

            ::system("xcodebuild -scheme \"" + strScheme + "\" archive");

         }

      }
#endif

   }






   //void system::__tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz)
   //{

   //   if (m_ptracelog.is_null())
   //   {

   //      __simple_tracea(trace_object(pobject), elevel, pszFunction, pszFile, iLine, psz);

   //      return;

   //   }

   //   log().__tracea(trace_object(pobject), elevel, pszFunction, pszFile, iLine, psz);

   //}



   string system::get_user_language()
   {

      auto psystem = get_system()->m_papexsystem;

      return psystem->standalone_setting("current_language");

   }


   bool system::set_user_language(::application * papp, index iSel)
   {

      auto psystem = get_system()->m_papexsystem;

      if (iSel < 0 || iSel >= psystem->get_session()->get_current_application()->m_puserlanguagemap->m_straLang.get_count())
      {

         return false;

      }

      string strLang = psystem->get_session()->get_current_application()->m_puserlanguagemap->m_straLang[iSel];

      if (strLang == psystem->get_session()->get_current_application()->m_puserlanguagemap->m_strLang)
      {

         return true;

      }

      if (!set_user_language(papp, strLang))
      {

         return false;

      }

      return true;

   }


   bool system::set_user_language(::application * papp, string strLang)
   {

      auto psystem = get_system()->m_papexsystem;

      psystem->get_session()->get_current_application()->m_puserlanguagemap->set_language(papp, strLang);

      return psystem->set_standalone_setting("current_language", strLang);

   }


   void system::process_machine_event_data(machine_event_data * pdata)
   {

      if (pdata->m_fixed.m_bRequestCloseApplication)
      {

         destroy();

      }

   }


::e_status system::browser(string strUrl, string strBrowser, string strProfile, string strTarget)
   {

       m_pcontext->m_papexcontext->os_context()->link_open(strUrl, strProfile);

       return ::success;

#if 0

      if (strProfile.is_empty() && strTarget.is_empty() && strBrowser.is_empty())
      {

         //::os_message_box(NULL, strUrl, strUrl, e_message_box_ok);

         m_pcontext->m_papexcontext->os().link_open(strUrl);

         return;

      }

      string strBrowserPath;
      string strBrowserDir;
      string strBrowserHelperPath;
      string strBrowserHelperDir;

      string strId;

      ::file::path path;

      string strParam;

      m_pcontext->m_papexcontext->os().get_default_browser(strId, path, strParam);

      if (strProfile.is_empty() || strProfile == "native")
      {

         strProfile = "default";

      }

      string strUser = strProfile;

      string strWeather = strBrowser;

      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
      {

         strWeather = m_pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedir->system() / "browser_weather.txt");

      }

      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
      {

         strWeather = "browser_day";

      }

      ::datetime::time timeNow = ::datetime::time::now();

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

            //strUrl = "https://ca2.software/open_f___?url=" + psystem->url_encode(strUrl) + "&profile=" + psystem->url_encode(strProfile) + "&target=" + psystem->url_encode(strTarget);

         }
         else
         {

            //strUrl = "https://ca2.software/open_tab?url=" + psystem->url_encode(strUrl) + "&profile=" + psystem->url_encode(strProfile) + "&target=" + psystem->url_encode(strTarget);

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

            chromium(strUrl, strBrowser, strId, m_pcontext->m_papexcontext->os().get_app_path("chrome"), strProfile, strParam);

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

         ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
            ref new ::winrt::Windows::UI::Core::DispatchedHandler([pstrNew]()
               {

                  ::winrt::Windows::Foundation::Uri ^ uri = ref new ::winrt::Windows::Foundation::Uri(*pstrNew);

                  delete pstrNew;

                  LauncherOptions ^ options = ref new LauncherOptions();

                  options->TreatAsUntrusted = false;

                  Launcher::LaunchUriAsync(uri, options);

               }));

         //#elif defined(LINUX)
         //
         //      class ::system("xdg-open \"" + strUrl + "\"");
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

            // psystem->m_pandroidinitdata->m_pszOpenUrl = strdup(strLink);

            ::oslocal()->m_pszOpenUrl = strdup(strUrl);

         }


#elif defined(MACOS)

         class ::system("open -a /Applications/Safari.app \"" + strUrl + "\"");

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

         //call_sync("C:\\Program Files\\Opera.exe", "--user-data-dir=\"" + path + "\" " + strUrl, "C:\\Users\\camilo\\AppData\\Local\\Vivaldi\\papplication", SW_SHOWNORMAL, 0);

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

            class ::system("xdg-open " + strUrl);

         }



#endif

      }

#endif

   }



   void system::chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam)
   {

#ifdef _UWP

      m_pcontext->m_papexcontext->os_context()->native_full_web_browser(strUrl);

      return;

#endif

      ::file::path pathDir;

      pathDir = path.folder();

      ::file::path pathAppDataDir(m_psystem->m_pacmedir->ca2roaming());

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

            strParam += " " + m_psystem->m_pacmefile->as_string(m_psystem->m_pacmedir->localconfig() / "app-core/commander/chrome.txt");

            auto psystem = m_psystem;

            auto pnode = psystem->node();

            pnode->call_async(path, strParam, pathDir, e_display_default, false);

         }

#elif defined(MACOS)

         string_array sa;

         sa = get_c_args_for_c(strParam);

         sa.add("--user-data-dir=" + pathProfile + "");

         string strChrome = m_psystem->m_pacmefile->as_string(m_psystem->m_pacmedir->localconfig() / "app-core/commander/chrome.txt");

         string_array sa2 = get_c_args_for_c(strChrome);

         sa.add(sa2);

         auto argv = sa.c_ansi_get();

         argv.add(nullptr);
         
         auto psystem = m_psystem;
         
         auto purl = psystem->url();

         string strApp = purl->url_decode(path);

         // 0x00010000 NSWorkspaceLaunchAsync
         // 0x00080000 NSWorkspaceLaunchNewInstance

         auto pnode = psystem->node();
         
         pnode->launch_app(strApp, argv.get_data(), 0x00010000 | 0x00080000);

#elif defined(LINUX)

         ::file::path shell;

         shell = "/bin/bash";

         strParam += "--user-data-dir=\"" + pathProfile + "\"";

         strParam += " " + m_psystem->m_pacmefile->as_string(m_psystem->m_pacmedir->localconfig() / "app-core/commander/chrome.txt");

         string strCmd = path + " " + strParam;

         strCmd.replace("\'", "\\\'");

         strParam = " -c '" + strCmd + "'";

         output_debug_string(strParam);

         auto psystem = m_psystem;

         auto pnode = psystem->node();

         pnode->call_async(shell, strParam, pathDir, e_display_default, false);

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

      if (m_pcontext->m_papexcontext->dir().is(pathProfile))
      {

         return;

      }

      ::file::path pathDir;

      pathDir = pathFirefox.folder();

      ::file::path pathProfileDir;

      pathProfileDir = pathProfile.folder();

      m_pcontext->m_papexcontext->dir().mk(pathProfileDir);

      string strParam = "-no-remote -CreateProfile \"" + strProfileName + " " + pathProfile + "\"";

      ::property_set set;

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      pnode->call_sync(pathFirefox, strParam, pathDir, e_display_default, 3_minute, set);

#endif

   }




   ::e_status system::firefox(string strUrl, string strBrowser, string strProfile, string strParam)
   {

#ifdef _UWP

      m_pcontext->m_papexcontext->os_context()->native_full_web_browser(strUrl);

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

      auto estatus = m_papexnode->get_firefox_installation_info(strBrowserPath, strBrowserDir);

      if (::failed(estatus))
      {

         return estatus;

      }

      if (!m_pcontext->m_papexcontext->file().exists(strBrowserPath) || !m_pcontext->m_papexcontext->dir().is(strBrowserDir))
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

         auto psystem = m_psystem;

         auto pnode = psystem->node();

         pnode->call_async(strBrowserPath, strParam, strBrowserDir, e_display_normal, false);

         pnode->call_async(strBrowserHelperPath, "/SetAsDefaultAppUser", strBrowserHelperDir, e_display_none, false);

      }

      if (strBrowser.has_char())
      {

         m_pcontext->m_papexcontext->file().put_text_utf8(m_psystem->m_pacmedir->system() / "browser.txt", strBrowser);

         m_pcontext->m_papexcontext->file().put_text_utf8(m_psystem->m_pacmedir->system() / "browser_path.txt", strBrowserPath);

         m_pcontext->m_papexcontext->file().put_text_utf8(m_psystem->m_pacmedir->system() / "browser_dir.txt", strBrowserDir);

      }

#endif

      return ::success;

   }

   string system::get_local_mutex_name(const ::string & pszAppName)
   {
      string strMutex;
      strMutex.format("Local\\ca2_application_local_mutex:%s", pszAppName.c_str());
      return strMutex;
   }

   string system::get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.format("Local\\ca2_application_local_mutex:%s, id:%s", pszAppName.c_str(), strId.c_str());
      return strMutex;
   }

   string system::get_global_mutex_name(const ::string & pszAppName)
   {
      string strMutex;
      strMutex.format("Global\\ca2_application_global_mutex:%s", pszAppName.c_str());
      return strMutex;
   }

   string system::get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.format("Global\\ca2_application_global_mutex:%s, id:%s", pszAppName.c_str(), strId.c_str());
      return strMutex;
   }

   
   //::task_group * system::task_group(::enum_priority epriority)
   //{

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

   //      ptool->m_id = etool;

   //      threadtoola.add(ptool);

   //   }

   //   return threadtoola.last();

   //}


   //__pointer(::subject) system::new_subject(const MESSAGE& message)
   //{

   //   auto id = (::iptr)message.wParam;

   //   auto psubject = subject(id);

   //   psubject->m_pobjectTopic = (::object*) message.lParam.m_lparam;

   //   return psubject;

   //}


   ::e_status system::open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      fork([this, strUrl, strProfile, strTarget]()
      {

         browser(strUrl, "", strProfile, strTarget);

      });

      return ::success;

   }


   ::e_status system::verb() // ambigous inheritance from ::apex::system/::axis::application
   {

      return ::thread::verb();

   }


   string system::crypto_md5_text(const ::string & str)
   {

      auto psystem = m_psystem->m_papexsystem;

      auto pcrypto = psystem->crypto();

      return pcrypto->md5(str);

   }


   string system::url_encode(const ::string & str)
   {

      return m_purldepartment->url_encode(str);

   }


} // namespace apex








//#include "base/node/_node.h"


#ifdef WINDOWS_DESKTOP
#elif defined(_UWP)
#include "apex/node/operating_system/universal_windows/_universal_windows.h"
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


   void system::discard_to_factory(__pointer(object) pca)
   {

      __UNREFERENCED_PARAMETER(pca);

   }


   __pointer(::data::node) system::load_xml(const ::string & pszXml)
   {

      throw ::interface_only_exception();

      return nullptr;

   }


   void system::on_start_find_applications_from_cache()
   {

      __throw(todo, "filehandler");
     // m_pfilehandler->m_ptree->erase_all();

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

   void system::on_map_application_library(::acme::library& library)
   {

      __throw(todo, "filehandler");
      // m_pfilehandler->defer_add_library(library.m_pca2library);

   }



#ifdef LINUX


//   ::e_status system::defer_initialize_x11()
//   {
//
//      return class ::system::defer_initialize_x11();
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

      strMessage.format("system::on_allocation_error Implement \"%s\" allocation\n", str.c_str());

      dev_log(strMessage);

   }


   //void system::on_request(::create* pcreate)
   //{

   //   //get_platform(pcreate->m_pcommandline->m_iEdge,pcreate->m_pcommandline->m_papplicationbias);

   //   ::apex::system::on_request(pcreate);

   //}


   //bool system::sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser, ::http::cookies* pcookies)
   bool system::sync_load_url(string& str, const ::string & pszUrl, ::http::cookies* pcookies)

   {

      string filename = m_pcontext->m_papexcontext->file().time_square();

      property_set set;

      //set["user"] = puser;

      set["cookies"] = pcookies;

      if (!m_pcontext->m_papexcontext->http().download(pszUrl, filename, set))

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

         m_pcontext->m_papexcontext->file().del(filename);

         return m_pcontext->m_papexcontext->http().download(str, strLocation, set);

      }

      str = m_pcontext->m_papexcontext->file().as_string(filename);

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

   //   //   if (!::application::on_install())
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


   //::e_status system::add_view_library(::acme::library* plibrary)
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


#ifdef _UWP


   bool system::get_window_rect(RECTANGLE_I32* prectangle)
   {

      if (::is_null(get_session()))
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


   ::e_status system::main()
   {

      auto estatus = ::thread::main();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   //__pointer_array(::apex::session) & system::planesessionptra()
   //{

   //   return m_planesessionptra;

   //}


   void system::hist_hist(const ::string & psz)
   {

      hist().hist(psz);

   }


   void system::system_id_update(::i64 iUpdate, ::i64 iPayload)
   {
      
      call((::enum_id) iUpdate, iPayload);

   }


   void system::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      command_handler(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      //if (m_papexnode)
      //{

      //   m_papexnode->route_command(pcommand, false);

      //}

   }

   
   void system::handle(::subject * psubject, ::context * pcontext)
   {

//      auto psignal = get_signal((::enum_id) iUpdate);
//
//      psignal->m_payload = iPayload;
//
//      psignal->notify();
      
      if(psubject->id() == id_set_dark_mode)
      {
         
         if(psubject->m_payload.is_true())
         {

            m_pnode->background_color(::color::black);
            
         }
         else
         {
            
            m_pnode->background_color(::color::white);

         }
         
      }
      else if (psubject->id() == id_operating_system_user_theme_change)
      {

         auto pnode = node();

         string strTheme = pnode->os_get_user_theme();

         if (strTheme != m_strOsUserTheme)
         {

            m_strOsUserTheme = strTheme;

         }
         else
         {

            psubject->m_esubject = e_subject_not_modified;

         }

         //m_pnode->defer_update_dark_mode();

      }
      else if (psubject->id() == id_open_hyperlink)
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
      else if(psubject->id() == id_app_activated)
      {
         
         if(::is_set(m_papplicationMain))
         {
         
            m_papplicationMain->handle(psubject, pcontext);
            
         }
         
      }


   }


   ::e_status system::destroy()
   {

      ::app_core::destroy();

      ::apex::context::destroy();

#ifdef WINDOWS_DESKTOP

      ::exception_translator::destroy();

#endif

      for (auto& plibrary : m_mapLibrary4.values())
      {

         if (plibrary)
         {

            plibrary->destroy();

         }

      }

      m_sessionmap.clear();

      //m_mapLibrary4.clear();

      return ::success;

   }


   void system::process_exit_status(::object* pobject, const ::e_status& estatus)
   {

      if (estatus == error_exit_session)
      {

         pobject->get_session()->destroy();
      
      }
      else if (estatus == error_exit_application)
      {

         pobject->get_session()->destroy();
      
      }
      else
      {
      
         ::system::process_exit_status(pobject, estatus);
      
      }

   }


   int system::console_end(::e_status estatus)
   {

      int iStatus = (int)estatus;

      int iError = 0;

      if (iStatus < 0)
      {

         iError = iStatus;

      }
      else if (iStatus > 1)
      {

         iError = 0;

         if (is_true("show_application_information"))
         {

            printf("return code is %d", iStatus);

         }

      }

      system_end();

      return iError;

   }


   ::e_status system::system_construct(const ::main & main)
   {

      auto estatus = ::system::system_construct(main);

      if (!estatus)
      {

         return estatus;

      }

      estatus = apex_main_data::system_construct(main);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }



   //void system::system_construct(int argc, char** argv, char** envp)
   //{

   //   apex_main_data::system_construct(argc, argv, envp);

   //}


   //void system::system_construct(int argc, wchar_t** argv, wchar_t** envp)
   //{

   //   apex_main_data::system_construct(argc, argv, envp);

   //}


//#ifdef WINDOWS_DESKTOP
//
//   
//   ::e_status system::system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char* pCmdLine, i32 nCmdShow)
//   {
//
//      return apex_main_data::system_construct(hinstanceThis, hPrevInstance, pCmdLine, nCmdShow);
//
//   }
//
//
//#elif defined(_UWP)
//
//   
//   ::e_status system::system_construct(const ::string_array & stra)
//   {
//
//      return ::success;
//
//   }
//
//
//#else
//
//
//   ::e_status system::system_construct(const ::string & pszCommandLine, const ::e_display& edisplay)
//   {
//
//      return ::success;
//
//   }
//
//
//   ::e_status system::system_construct(os_local* poslocal, const ::e_display& edisplay)
//   {
//
//      return ::success;
//
//   }
//
//
//#endif


   //__namespace_system_factory(system);


} // namespace apex


#ifdef __APPLE__

string get_bundle_app_library_name();

#endif




//__pointer()::apex::session* platform_create_session()
//{
//
//   auto pstaticsetup = ::static_setup::get_first(::static_setup::flag_system, "");
//
//   if (!pstaticsetup)
//   {
//
//      return nullptr;
//
//   }
//
//   auto pelement = pstaticsetup->create_element();
//
//   if (!pelement)
//   {
//
//      return nullptr;
//
//   }
//
//   return pelement();
//
//}


//
//void apex_application_main(int argc, char* argv[], const ::string & pszCommandLine);

namespace apex
{

   void system::application_main(int argc, char* argv[], const ::string & pszCommandLine)
   {

      //apex_application_main(argc, argv, pszCommandLine);

   }


   //__pointer(::extended::future < ::conversation >) system::_message_box(::object * pobject, const ::string & pszText, const ::string & pszTitle, const ::e_message_box & emessagebox)
   //{

   //   return ::system::_message_box(pobject, pszText, pszTitle, emessagebox);

   //}

   // https://github.com/umpirsky/tld-list/blob/master/data/en/tld.txt
   

   ::e_status system::get_public_internet_domain_extension_list(string_array& stra)
   {

      auto estatus = ::system::get_public_internet_domain_extension_list(stra);
      
      return estatus;

   }


   ::e_status system::system_main()
   {

      auto estatus = ::system::system_main();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace apex


//void apex_system_update(const ::id & id, const ::payload & payload)
//{
//
//   psystem->process_subject(id, payload);
//
//}

//
//
//void apex_system_set_modified(const ::id& id)
//{
//
//
//
//   psystem->set_modified(id);
//
//}
//
//namespace apex
//{
//
//
//   void system::on_subject(::subject* psubject)
//   {
//
//
//      ::manager::on_subject(psubject);
//
//   }
//
//
//
//} // namespace apex
//


//void system_id_update(void* pSystem, ::i64 iUpdate, ::i64 iPayload)
//{
//
//   auto psystem = (class ::system *) pSystem;
//
//   psystem->system_id_update(iUpdate, iPayload);
//
//}
