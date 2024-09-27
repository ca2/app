#include "framework.h"
#include "system.h"
#include "context.h"
#include "machine_event_data.h"
#include "machine_event.h"
#include "machine_event_central.h"
#include "shell_launcher.h"
//#include "node.h"
#include "application.h"
#include "context.h"
#include "node.h"
#include "history.h"
#include "acme/handler/topic.h"
//#include "app_launcher.h"
//#include "log.h"
#include "acme/compress/compress.h"
#include "acme/compress/uncompress.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/crypto/crypto.h"
#include "acme/exception/dump_context.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/handler/request.h"
//#include "apex/id.h"
#include "acme/prototype/prototype/url.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/single_lock.h"
#include "acme/platform/profiler.h"
#include "acme/platform/system_setup.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/command_line.h"
#include "apex/innate_ui/innate_ui.h"
#include "apex/input/input.h"
#include "apex/message/message.h"
//#include "apex/operating_system.h"
#include "apex/networking/http/context.h"
#include "apex/networking/http/cookie.h"
#include "apex/networking/internet.h"
#include "apex/networking/networking.h"
#include "apex/operating_system/department.h"
#include "apex/user/user/language_map.h"
#ifdef LINUX
#include <unistd.h>
#endif
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/dir_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/prototype/text/context.h"
#include "apex/message/command.h"
#include "acme/prototype/geometry2d/geometry.h"
#include "acme/platform/hyperlink.h"
//#include "acme/platform/system_impl.h"
#include "acme/prototype/string/base64.h"

int file_put_contents(const ::file::path & path, const char * contents);;
CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);


//extern ::apex::system* g_papexsystem;

//CLASS_DECL_APEX void apex_generate_random_bytes(void* p, memsize s);

//RECTANGLE__I32 get_main_screen_rectangle();


///const ::string & g_pszMultimediaLibraryName = nullptr;

void apex_system_update(const ::atom & atom, const ::payload & payload);

void apex_system_set_modified(const ::atom & atom);


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

CLASS_DECL_APEX void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz);


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


//#ifdef WINDOWS_DESKTOP
//
//#include <Lmcons.h>
//
//string get_user_name()
//{
//   
//   WCHAR wsz[UNLEN * 2];
//
//   DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);
//
//   ::GetUserNameW(wsz,&dwSize);
//
//   return string(wsz);
//
//}
//
////#include "acme/operating_system/windows/_c.h"
//#endif



namespace apex
{


   system::system()
   {

      m_papexsystem = this;

      //      factory()->add_factory_item < ::apex::app_launcher >();
      //
      //      factory()->add_factory_item<::apex::log, ::logger>();

            //factory()->add_factory_item < ::thread >();

            //factory()->add_factory_item<::apex::idpool, ::acme::idpool >();

            //m_edisplay = e_display_default;

            //set_layer(LAYERED_APEX, this);

#ifdef UNIVERSAL_WINDOWS

      m_bPreferLessGraphicsParallelization = true;

#else

      m_bPreferLessGraphicsParallelization = false;

#endif

      m_bMessageThread = true;

      m_bSystemSynchronizedCursor = true;
      m_bSystemSynchronizedScreen = true;

      common_construct();

   }


   system::~system()
   {

      //#ifndef WINDOWS
      //
      //      exception_translator::detach();
      //
      //#endif

   }


   //void system::on_set_platform()
   //{

   //}



   void system::common_construct()
   {

      //factory()->add_factory_item < ::apex::session >();
      //factory()->add_factory_item < ::apex::application >();
      //add_factory_item < ::imaging >();

      m_bSimpleMessageLoop = false;

      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;

      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

      //      factory()->add_factory_item < ::apex::application >();
            //factory()->add_factory_item < ::apex::idpool, ::acme::idpool >();


   }


#ifdef _DEBUG


   i64 system::increment_reference_count()
   {

      return ::acme::system::increment_reference_count();

   }


   i64 system::decrement_reference_count()
   {

      return ::acme::system::decrement_reference_count();

   }


#endif


   void system::on_set_platform()
   {

      apex::context::on_set_platform();

      acme::system::on_set_platform();

      factory()->add_factory_item < ::apex::session, ::apex::session >();

   }


   void system::on_initialize_particle()
   {

      ::apex::context::on_initialize_particle();

      ::acme::system::on_initialize_particle();

   }


   void system::install_message_routing(::channel * pchannel)
   {

      ::apex::context::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_erase_session, pchannel, this, &system::on_message_erase_session);

   }


   void system::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
   {


   }


   string system::get_locale_schema_dir()
   {

      return "_std/_std";

   }






   bool system::on_get_task_name(string & strTaskName)
   {

      if (platform()->is_console())
      {

         return false;

      }

      return ::apex::context::on_get_task_name(strTaskName);

   }


   ::pointer<::factory::factory> & system::node_factory()
   {

      auto & pfactory = factory("apex", OPERATING_SYSTEM_NAME);

      if (!pfactory)
      {

         return pfactory;

      }

      pfactory->merge_to_global_factory();

      return pfactory;

   }


   void system::process_init()
   {

      __construct_new(m_pinternet);


      if (!application()->m_bShowApplicationInformation)
      {

         string strShowApplicationInformation;

         if (is_command_line_parameter_true(strShowApplicationInformation, platform()->m_strCommandLine, "show_application_information"))
         {

            application()->m_bShowApplicationInformation = true;

         }

      }

      //auto psystem = system();

      //if (!psystem)
      //{

      //   return;

      //   //on_result(error_failed);

      //   //return false;

      //}

      //   psystem->common_construct();

      //::set_task(psystem);

      //debug_context_object(psystem);

      initialize(this);

      //set_object(psystem);


      // what could influence time before Main?
      // cold start (never previously called program and its Dlls...)?
      m_timeMainStart = m_timeStart;

      //xxdebug_box("box1", "box1", e_message_box_icon_information);
   //
     // ::file::path pathOutputDebugString = acmedirectory()->system() / strAppId / "information.txt" ;

      //::file::path pathGlobalOutputDebugString = acmedirectory()->config() / "information.txt" ;

      //::apex::g_bOutputDebugString = acmefile()->exists(pathOutputDebugString)||  acmefile()->exists(pathGlobalOutputDebugString);

      //return true;


      factory()->add_factory_item<http::context>();

      //auto estatus = 
      ::acme::system::process_init();

      __construct_new(m_pthreading);

      thread::s_bAllocReady = true;


      //      ::earth::time timeNow = ::earth::time::now();
      //
      //      auto pnode = node();
      //
      //      if (pnode)
      //      {
      //
      //         if (timeNow.hour() >= 6 && timeNow.hour() <= 17)
      //         {
      //
      //            pnode->set_dark_mode(false);
      //
      //         }
      //         else
      //         {
      //
      //            pnode->set_dark_mode(true);
      //
      //         }
      //
      //      }


            //set_callstack_mask({ get_callstack_mask(), callstack_fork_global});

#if !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID)

      m_pmutexMatter = node()->create_local_named_mutex(this, false, "ca2-appmatter");

#endif

      //estatus =

      __construct_new(m_pbase64);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      __construct_new(m_poperatingsystem);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (m_bPreferLessGraphicsParallelization)
      {

         m_bThreadToolsForIncreasedFps = false;

      }
      else
      {

         m_bThreadToolsForIncreasedFps = false;

      }

#ifdef __DEBUG

      //estatus =
      //__construct_new(m_pdumpcontext);

      //if (!estatus)
      //{

      //   return estatus;

      //}

#endif

//#if def WINDOWS
//
//      exception_translator::attach();
//
//#endif

      m_nSafetyPoolSize = 512;        // default size_i32

      //estatus =
      __construct_new(m_pgeometry);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      string strId;
      strId = "ca2log";

      initialize_log(strId);
      //{

      //   throw ::exception("failed to initialize log");

      //}

      // {

      //    bool bGlobalEnableStackTrace = true;

      //    ::file::path pathNoExceptionStackTrace = acmedirectory()->config() / "system/no_exception_stack_trace.txt";

      //    if (acmefile()->exists(pathNoExceptionStackTrace))
      //    {

      //       bGlobalEnableStackTrace = false;

      //    }

      //    ::exception::enable_call_stack_back_trace(bGlobalEnableStackTrace);

      // }

      //add_factory_item < ::stdio_file, ::file::text_file >();
      //add_factory_item < ::stdio_file, ::file::file >();
      factory()->add_factory_item < ::i64_array >();
      factory()->add_factory_item < ::f64_array >();
      factory()->add_factory_item < ::acme::library >();

      factory()->add_factory_item < ::file::path_object >();

      factory()->add_factory_item < string_array >();
      factory()->add_factory_item < memory >();
      factory()->add_factory_item < memory_file >();
      factory()->add_factory_item < ::i32_array >();

      //factory()->add_factory_item < ::file::path_object >();
      //factory()->add_factory_item < ::i64_array >();
      //factory()->add_factory_item < ::f64_array >();
      //factory()->add_factory_item < ::acme::library >();

      //factory()->add_factory_item < ::file::path_object >();

      //factory()->add_factory_item < string_array >();
      //factory()->add_factory_item < memory >();
      //factory()->add_factory_item < memory_file >();
      //factory()->add_factory_item < ::i32_array >();

      ///estatus =

      //if (!estatus)
      //{

      //   return estatus;

      //}


      //estatus =

      //if (!estatus)
      //{

      //   return estatus;

      //}

//#ifdef WINDOWS_DESKTOP
//
//      m_uiWindowsTaskbarCreatedMessage = 0;
//
//#endif

      //return estatus;


      //if (!estatus)
      //{

      //   return estatus;

      //}


#if !defined(ANDROID) && !defined(APPLE_IOS)

      if (!application()->is_service() || application()->m_papexapplication->is_user_service())
      {

         m_pmutexUserAppData = node()->create_local_named_mutex(this, false, "ca2.UserAppData");
         m_pmutexSystemAppData = node()->create_local_named_mutex(this, false, "ca2.SystemAppData");

      }

#endif


      // estatus = ([a-z0-9_]+)_factory("apex", OPERATING_SYSTEM_NAME);

      // if (!estatus)
      // {

      //    return estatus;

      // }

      //estatus = __construct(m_papexnode);

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      set_system_update(&apex_system_update);

      //set_system_set_modified(&apex_system_set_modified);

      //estatus = 
      //system_prep();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;





#if !defined(UNIVERSAL_WINDOWS)


      if (is_true("show_application_information"))
      {

         //printf("%s", "\n\nApplication Information\n");
         informationf("Application Information");

         auto iPid = node()->current_process_identifier();

         //printf("%s", ("Process PID: " + ::as_string(iPid) + "\n").c_str());

         informationf("Process PID: " + ::as_string(iPid));

      }


#endif


      //#ifdef LINUX
      //
      //      {
      //
      //         string str;
      //
      //         str = acmedirectory()->home() / ".profile";
      //
      //         if(!acmefile()->exists(str))
      //         {
      //
      //            str = acmedirectory()->home() / ".bashrc";
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
      //               int iSize = strLine.length();
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
//               ASSERT(m_hinstancePrev == nullptr);
//
//               HINSTANCE hinstance = (HINSTANCE)m_hinstanceThis;
//
//               //auto edisplay = m_edisplay;
//
//               // handle critical errors and avoid Windows message boxes
//               SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);
//
//               //m_edisplay = edisplay;
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

      //estatus = __construct_new(m_pxml);

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

      //add_factory_item < application_bias >();

      //add_factory_item < ::pointer < ::mutex > >();
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

                           auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create("/ca2core");

                  acmefile()->put_contents("/ca2core/teste.txt", str, str.length());
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

         //auto estatus =
         __construct_new(m_pmachineeventcentral);

         //if (!estatus)
         //{

         //   return false;

         //}

         //if(!m_pmachineeventcentral->initialize())
         //{

         //   return false;

         //}

         if (m_pmachineeventcentral->is_close_application())
         {

            // return false;

         }

#endif

      }


      //      {
      //
      //         string strCurrentWorkingDirectory;
      //
      //         strCurrentWorkingDirectory = get_current_directory_name();
      //
      //         ::acme::get()->platform()->informationf("\nCurrent Working Directory : " + strCurrentWorkingDirectory);
      //
      //      }

            //estatus = m_ptracelog->process_init();

            //if(!estatus)
            //{

               //WARNING("failed to process_init ::apex::log trace");

            //}

            //estatus = 

      initialize_context();


   }


   void system::init1()
   {

      //auto estatus = 
      ::acme::system::init1();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      //system_init();

      /*if (!estatus)
      {

         return estatus;

      }*/


      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (application()->m_bCrypto)
      {

         auto & pfactoryCrypto = factory("crypto", "openssl");

         //if (!pfactoryCrypto)
         //{

         //   WARNING("Could not open crypto openssl plugin.");

         //   //return pfactoryCrypto;

         //}

         pfactoryCrypto->merge_to_global_factory();

         //estatus = 
         pfactoryCrypto->__construct(this, m_pcrypto);

      }

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //if (!::is_set(m_pcrypto))
      //{

      //   return false;

      //}

      //on_update_matter_locator();

      //estatus = 

      if (application()->m_bNetworking || application()->m_bNetworking.undefined())
      {

         initialize_networking();

      }

      //if (!estatus)
      //{

      //   m_estatus = estatus;

      //   return estatus;

      //}

      // if (application()->m_bResource)
      // {
      //
      //    bool bMatterFromHttpCache = false;
      //
      //    bool bMatterFromResource = false;
      //
      //    auto pfile = m_papexsystem->file()->create_resource_file("app/_matter/main/_std/_std/Thomas Borregaard Sørensen.dedicatory");
      //
      //    if (pfile)
      //    {
      //
      //       information() << "found Thomas Borregaard Sørensen.dedicatory";
      //
      //       bMatterFromResource = true;
      //
      //    }
      //    else
      //    {
      //
      //       warning() << "Thomas Borregaard Sørensen.dedicatory not found";
      //
      //    }
      //
      //    if (bMatterFromResource)
      //    {
      //
      //       m_pdirsystem->m_bMatterFromHttpCache = false;
      //
      //       m_pdirsystem->m_bMatterFromResource = true;
      //
      //    }
      //    else
      //    {
      //
      //       if (m_iMatterFromHttpCache == -1)
      //       {
      //
      //          ::file::path pathSide = m_pcontext->m_papexcontext->side_get_matter_path("app/_matter/main");
      //
      //          ::file::path pathLocal = local_get_matter_path("app/_matter/main");
      //
      //          bool bFileSystemMatter = m_pacmedirectory->is(pathSide) || m_pacmedirectory->is(pathLocal);
      //
      //          bMatterFromHttpCache = !bFileSystemMatter;
      //
      //       }
      //       else
      //       {
      //
      //          bMatterFromHttpCache = m_iMatterFromHttpCache != 0;
      //
      //       }
      //
      //       m_pdirsystem->m_bMatterFromHttpCache = bMatterFromHttpCache;
      //
      //       m_pdirsystem->m_bMatterFromResource = false;
      //
      //    }
      //
      // }


      //initialize_matter();

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



      //throw ::exception(todo("filehandler"));

      //estatus = __construct_new(m_pfilehandler);

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


      //return true;

   }


   //void system::compress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation)
   //{

   //   /*auto estatus =*/

   //   ::pointer<::compress>pcompress = new_compress(scopedstrImplementation);
   //   /*  if (!estatus)
   //   {

   //      return estatus;

   //   }*/

   //   auto pfileTarget = file()->get_writer(payloadTarget);

   //   auto pfileSource = file()->get_reader(payloadSource);

   //   /*estatus = */ pcompress->transfer(pfileTarget, pfileSource);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return estatus;

   //}


   //void system::uncompress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation, transfer_progress_function transferprogressfunction)
   //{

   //   //::pointer<::uncompress>puncompress;

   //   /*auto estatus = */ 
   //   
   //   auto puncompress = new_uncompress(scopedstrImplementation);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   auto pfileTarget = file()->get_writer(payloadTarget);

   //   auto pfileSource = file()->get_reader(payloadSource);

   //   /*estatus = */ puncompress->transfer(pfileTarget, pfileSource, transferprogressfunction);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return estatus;

   //}


   void system::init2()
   {

      ::acme::system::init2();

      //::e_status estatus = 
      // create_session();

      //if (!estatus)
      //{

      //   //output_error_message("Failed to allocate get_session()!!");

      //   informationf("Failed to allocate get_session()!!");

      //   return estatus;

      //}

      //if (application()->is_console())
      //{

         //estatus = 

         //get_session()->inline_init();

         //if (!estatus)
         //{

         //   return estatus;

         //}

      //}
      //else
      //{

      //{

      //   informationf("\nFailed to begin_synch the session (::apex::session or ::apex::session derived)");

      //   return false;

      //}

   //}

   //estatus = 
      __construct_new(m_ptexttable);

      auto strMain = dir()->install() / "app/_appmatter/main";

      if (!m_ptexttable->load(strMain))
      {

         // return error_failed;

      }

      //if (!m_ptexttable || !estatus)
      //{

      //   return estatus;

      //}

      if (application()->m_bSession)
      {

         auto psession = session();

         psession->m_ptextcontext->defer_ok(m_ptexttable);

      }


      //if(!::application::init2())
      //   return false;

      //auto estatus = ::apex::system::init2();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      // estatus =

      __construct_new(m_phistory);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::initialize_context()
   {

      //auto estatus =
      ::apex::context::initialize_context();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::on_system_construct()
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

      //return ::success;

   }


   void system::on_start_system()
   {

      //auto estatus = 
      ::acme::system::on_start_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //   void system::start()
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
   //   void system::get_time(micro_time * pmicrotime)
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
   //      ::memory_copy(&tt, &ft, sizeof(tt));
   //
   //      tt /= 10; // make it usecs
   //      
   //      pmicrotime->m_secs = (long)tt / 1'000'000;
   //      
   //      pmicrotime->m_micros = (long)tt % 1'000'000;
   //
   //#else
   //
   //      struct timeval timeval;
   //
   //      gettimeofday(&timeval, nullptr);
   //
   //      pmicrotime->m_secs = timeval.tv_sec;
   //
   //      pmicrotime->m_micros = timeval.tv_usec;
   //
   //#endif
   //
   //
   //   }
   //


   void system::init_task()
   {

      ::thread::init_task();

      call_init_system();

      //auto estatus = ([a-z0-9_]+)_factory();

      //if(!estatus)
      //{

        // return estatus;

      //}

      //auto estatus =
//      process_init();
//
//      //if(!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      if (m_psystemParent)
//      {
//
//         m_psystemParent->add_reference(this);
//
//      }
//
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //estatus =
//      init1();
//
//      //if(!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //estatus =
//      init2();
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//
////      estatus = process_init();
////
////      if (!estatus)
////      {
////
////         return estatus;
////
////      }
//
//
//      //estatus = process_creation_requests();
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //return true;

   }


   void system::init()
   {

      //return true;

   }


   void system::post_pending_requests()
   {

      while (post_next_pending_request())
      {

      }

   }


   void system::defer_post_initial_request()
   {

      ::acme::system::defer_post_initial_request();

      //if (!m_bPostedInitialRequest)
      //{

      //   m_bPostedInitialRequest = true;

      //   auto prequest = __create_new< ::request>();

      //   string strAppId = application()->m_strAppId;

      //   if (strAppId.is_empty())
      //   {

      //      if (application())
      //      {

      //         strAppId = application()->m_strAppId;

      //      }

      //   }

      //   prequest->m_strAppId = strAppId;

      //   //pcreate->m_pcommandline = __create_new < command_line >();
      //   post_request(prequest);

      //}

   }


   //void system::post_request(::request* prequest)
   //{

   //   auto straArguments = platform()->get_arguments();

   //   if (straArguments.has_element())
   //   {

   //      prequest->initialize_arguments(straArguments);

   //   }
   //   else
   //   {

   //      string strCommandLine = application()->m_strCommandLine;

   //      prequest->initialize_command_line2(strCommandLine);

   //   }

   //   prequest->finish_initialization();

   //   add_request(prequest);

   //   prequest->procedure_array(ID_COMPLETE)->add([this]()
   //      {

   //         post_next_pending_request();

   //      });

   //   post_next_pending_request();

   //}


   void system::inline_init()
   {

      ::acme::system::inline_init();

      ::apex::context::inline_init();

   }


   void system::inline_term()
   {

      ::apex::context::inline_term();

#if REFERENCING_DEBUGGING

      release();

      try
      {

         if (m_countReference > 1)
         {

            check_pending_releases();

         }

      }
      catch (...)
      {

      }

#endif

   }


   void system::__task_init()
   {

      try
      {

         ::apex::context::__task_init();

      }
      catch (exception & exception)
      {

         string strMoreDetails;

         strMoreDetails = "command line: " + string(platform()->m_strCommandLine) + "\n\n";

         exception_message_box(exception, strMoreDetails);

         throw exception;

      }

   }


   ::acme::application * system::get_main_app()
   {

      return application();

   }


   void system::init_system()
   {

      //auto estatus = 
      ::acme::system::init_system();

      //if(!estatus)
      //{

      //   return estatus;

      //}

//      ::acme::application * pappStartup = ::acme::application::g_p;
//
//      if(::is_null(pappStartup))
//      {
//
//         pappStartup = new_app(m_strAppId);
//
//      }
//
//      //if (!pappStartup)
//      //{
//
//      //   return -1;
//
//      //}
//
//      __refer(application(), pappStartup);
//
//      application()->initialize(this);
//
//      application()->get_property_set().merge(get_property_set());
//
//      set_main_struct(*application());

      //return estatus;

   }


   void system::term()
   {

      m_psignalmap.release();

      m_phistory.release();

   }


   void system::on_message_erase_session(::message::message * pmessage)
   {

      auto iEdge = pmessage->m_wparam;

      erase_session(iEdge);

   }


   string system::get_application_server_name()
   {

      string strApplicationServerName = application()->m_strAppId;

      strApplicationServerName.replace_with(".", "/");

      strApplicationServerName.replace_with("-", "_");

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


   void system::thread_loop()
   {

      return thread::thread_loop();

   }


   void system::term_task()
   {

      try
      {

         term_system();

      }
      catch (...)
      {

      }

      try
      {

         ::thread::term_task();

      }
      catch (...)
      {

      }

   }


   //void system::post_to_all_threads(const ::atom & atom, WPARAM wparam, LPARAM lparam)
   //{

   //   synchronous_lock synchronouslock(m_pmutexThread);

   //   for (auto& pair : system()->m_threadidmap)
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

      ::acme::system::TermSystem();

   }


   void system::create_os_node()
   {

      ::acme::system::create_os_node();

   }


   ::apex::node * system::node()
   {

      return m_pnode ? m_pnode->m_papexnode : nullptr;

   }


   ::input::input * system::input()
   {

      if (!m_pinput)
      {

         auto pinput = node()->m_papexnode->create_input();

         m_pinput = pinput;

      }

      return m_pinput;


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


   ::u32 system::os_post_to_all_threads(const ::atom & atom, wparam wparam, lparam lparam)
   {

      post_to_all_threads(atom, wparam, lparam);

      return 0;

   }


   bool system::is_system() const
   {

      return true;

   }


   i32 system::_001OnDebugReport(i32 i1, const ::string & psz1, i32 i2, const ::string & psz2, const ::string & psz3, va_list args)
   {

      return _debug_logging_report(i1, psz1, i2, psz2, psz3, args);

   }


   i32 system::_debug_logging_report(i32 iReportType, const ::string & strFileName, i32 iLineNumber, const ::string & strModuleName, const char * pszFormat, va_list list)
   {

      //if(!m_ptracelog || !m_ptracelog->m_bExtendedLog)
      //{

      //   return ::apex::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);

      //}

      string str;

      if (strFileName.has_char() || strModuleName.has_char())
      {

         string_array stra;

         if (strFileName.has_char())
         {

            stra.add(strFileName);

         }

         if (strModuleName.has_char())
         {

            stra.add(strModuleName);

         }

         str += stra.implode(", ");

         str += ": ";

      }

      string str2;

      if (pszFormat != nullptr)
      {

         //         if(list != nullptr)
         {

            str2.formatf(pszFormat, list);

         }
         //     else
         {

            //          str2 = pszFormat;

         }

      }

      str = str + str2;

      string strPrint(str);

      strPrint.replace_with("%%", "%");

      //if(m_ptracelog)
      //{

      //   m_ptracelog->print(strPrint);

      //}

      informationf(strPrint);

      if (iReportType == _CRT_ASSERT)
      {

         return 1;

      }
      else
      {

         return 0;

      }

   }


   bool system::assert_failed_line(const ::string & pszFileName, i32 iLine)
   {

      __UNREFERENCED_PARAMETER(pszFileName);

      __UNREFERENCED_PARAMETER(iLine);

      return false;

   }


   bool system::on_assert_failed_line(const ::string & pszFileName, i32 iLine)
   {

      __UNREFERENCED_PARAMETER(pszFileName);

      __UNREFERENCED_PARAMETER(iLine);

      return true;

   }


   void system::__set_thread_on()
   {

      ::thread::__set_thread_on();

   }


   //   ::pointer< ::mutex > system::get_openweather_city_mutex()
   //   {
   //
   //      synchronous_lock synchronouslock(this->synchronization());
   //
   //      if (m_spmutexOpenweatherCity.is_null())
   //      {
   //
   //#ifdef UNIVERSAL_WINDOWS
   //
   //         m_spmutexOpenweatherCity = ::place(new ::pointer < ::mutex > ());
   //
   //#else
   //
   //         m_spmutexOpenweatherCity = ::place(new ::pointer < ::mutex > (e_create_new, false, "Global\\ca2_weather_city"));
   //
   //#endif
   //
   //      }
   //
   //      return m_spmutexOpenweatherCity;
   //
   //   }


      //void system::on_allocation_error(const ::string & str, ::particle * pparticle)
      //{

      //   string strMessage("Allocation Error!! : ");

      //   strMessage += "Type: " + str;

      //   //if (::is_null(pparticle))
      //   //{

      //   //   strMessage += " : (Parent: (nullptr))";

      //   //}
      //   //else
      //   //{

      //   //   strMessage += " : (Parent: ";

      //   //   try
      //   //   {
      //   //      strMessage += ::type(pparticle).name();

      //   //   }
      //   //   catch (...)
      //   //   {

      //   //   }

      //   //   strMessage += "(0x" + ::hex::lower_from((iptr)pparticle) + ") )";

      //   //}

      //   TRACE(strMessage);

      //}




      //class ::base64 & system::base64()
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







   //::apex::os & system::os()
   //{

   //   return *m_spos;

   //}


//pointer_array < ::apex::session > & system::basesessionptra()
//{

//   return m_basesessionptra;

//}


   ::operating_system::department & system::operating_system()
   {

      return *m_poperatingsystem;

   }


   void system::initialize_log(const ::string & pszId)
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

      //return ::success;

   }


   void system::appa_load_string_table()
   {

      //retry_single_lock rsl(mutex(),::time(100),::time(100));

//      for(i32 i = 0; i < appptra().get_size(); i++)
      //    {
      //     ::application * papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }


   void system::appa_set_locale(const ::string & pszLocale, const ::action_context & context)
   {

      //retry_single_lock rsl(mutex(),::time(100),::time(100));
      single_lock rsl(synchronization());

      rsl.wait(10_s);

      //      for(i32 i = 0; i < appptra().get_size(); i++)
      //     {
            //       ::application * papp = appptra()(i);
            //       papp->set_locale(pszLocale,context);
            //    }

   }


   void system::appa_set_schema(const ::string & pszStyle, const ::action_context & context)
   {

      //retry_single_lock rsl(mutex(),::time(100),::time(100));
      single_lock rsl(synchronization());

      rsl.wait(10_s);

      //      for(i32 i = 0; i < appptra().get_size(); i++)
            //    {
            //       ::application * papp = appptra()(i);
            //       papp->set_schema(pszStyle,context);
            //    }

   }



   bool system::assert_running_global(const ::string & pszAppName, const ::string & pszId)
   {

      if (string(pszId).has_char())
      {

         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_id_mutex_name(pszAppName, pszId));
         auto pmutex = node()->open_global_named_mutex(this, m_pnode->get_global_id_mutex_name(pszAppName, pszId));

         if (pmutex == nullptr)
         {

            string strApp = pszAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__APPLE__)

            auto plauncher = __create < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, dir()->module() / strApp, strParameters, nullptr, e_display_normal);

            plauncher->launch();

#else

            throw ::exception(todo);

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
         auto pmutex = node()->open_global_named_mutex(this, m_pnode->get_global_mutex_name(pszAppName));
         if (pmutex == nullptr)
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#if defined(UNIVERSAL_WINDOWS)

            throw ::exception(todo);

#else

            auto plauncher = __create < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, dir()->module() / strApp, nullptr, nullptr, e_display_normal);

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

   bool system::assert_running_local(const ::string & pszAppName, const ::string & pszId)
   {
      string strAppName(pszAppName);
      string strId(pszId);
      if (strId.has_char())
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_id_mutex_name(pszAppName, strId));
         auto pmutex = node()->open_local_named_mutex(this, m_pnode->get_local_id_mutex_name(pszAppName, strId));
         if (pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef UNIVERSAL_WINDOWS

            throw ::exception(todo);

#else

            auto plauncher = __create < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, dir()->module() / strApp, strParameters, nullptr, e_display_normal);

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
         auto pmutex = node()->open_local_named_mutex(this, m_pnode->get_local_mutex_name(pszAppName));
         if (pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef UNIVERSAL_WINDOWS

            throw ::exception(todo);

#else

            auto plauncher = __create < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, dir()->module() / strApp, strParameters, nullptr, e_display_normal);

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


   ::collection::count system::get_application_count()
   {

      ::collection::count c = 0;

      //try
      //{

      //   for(::collection::index iBaseSession = 0; iBaseSession < m_basesessionptra.get_count(); iBaseSession++)
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

   //   throw ::interface_only();

   //   return "";

   //}


   void system::install_progress_add_up(int iAddUp)
   {

      __UNREFERENCED_PARAMETER(iAddUp);

   }




   void system::on_request(::request * prequest)
   {

      ::acme::system::on_request(prequest);

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
   ////      file_pointer pfile = file()->get_file(dir()->appdata() / "applibcache.bin",::file::e_open_binary | ::file::e_open_read);
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
   //      /*      m_spfilehandler(new ::apex::filehandler::handler (this));*/
   //
   ////      m_mapAppLibrary.erase_all();
   ////
   ////      string strLibraryId;
   ////
   ////      ::file::listing straTitle(this);
   ////
   ////      ::file::path pathCa2Module = dir()->ca2module();
   ////
   ////      ::acme::get()->platform()->informationf("\n\n::apex::system::find_applications_to_cache\n\n");
   ////
   ////      ::acme::get()->platform()->informationf("ca2 module folder : " + pathCa2Module);
   ////
   ////      ::acme::get()->platform()->informationf("\n\n\n");
   ////
   ////      straTitle.ls_pattern(pathCa2Module, { "*.*" });
   ////
   ////      for(i32 i = 0; i < straTitle.get_count(); i++)
   ////      {
   ////
   ////         strLibraryId = straTitle[i];
   ////
   ////
   ////         if(strLibraryId.case_insensitive_ends_eat(".dll")
   ////               || strLibraryId.case_insensitive_ends_eat(".so")
   ////               || strLibraryId.case_insensitive_ends_eat(".dylib"))
   ////         {
   ////
   ////            if(case_insensitive_string_begins(strLibraryId,"libdraw2d_")
   ////                  || case_insensitive_string_begins(strLibraryId,"libbase"))
   ////            {
   ////               continue;
   ////            }
   ////
   ////            ::acme::get()->platform()->informationf("library("+as_string(i)+") : " + strLibraryId+"\n\n");
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
   ////         file = psession->file()->get_file(dir()->appdata() / "applibcache.bin",::file::e_open_defer_create_directory | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_write);
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
   //      if(!case_insensitive_ansi_compare(pszLibrary, "app_core_hello_multiverse"))
   //      {
   //         INFORMATION("reach app_core_hello_multiverse");
   //      }
   //
   //      if(!case_insensitive_ansi_compare(pszLibrary, "experience_lite"))
   //      {
   //         INFORMATION("reach experience_lite");
   //      }
   //
   //      if(!case_insensitive_ansi_compare(pszLibrary, "app_core_hello_multiverse"))
   //      {
   //         INFORMATION("reach app_core_hello_multiverse");
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
   //      //   ::acme::get()->platform()->informationf("::system::map_application_library open_ca2_library(2) Failed :" + string(pszLibrary) + "\n\n");
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
   //      else if(!strLibrary.begins_eat("libbase"))
   //      {
   //
   //         strLibrary.begins_eat("lib");
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
   //      strLibrary.case_insensitive_begins_eat(strPrefix);
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

   //void system::do_request(::create* pcreate)
   //{

   //   //if (pcreate->m_ecommand == ::command_check_exit)
   //   //{

   //   //   return ::success;

   //   //}

   //   //on_request(pcreate);

   //   ::thread::do_request(pcreate);

   //}




   //string system::url::encode(const ::string & str)
   //{

   //   //throw ::interface_only();

   //   return ::url::encode(str);

   //}

#ifdef ANDROID

   bool system::android_set_user_wallpaper(string strUrl)
   {

      //operating_system_driver::get().m_strSetUserWallpaper = strUrl;

      return true;

   }

   bool system::android_get_user_wallpaper(string & strUrl)
   {

      //operating_system_driver::get().m_bGetUserWallpaper = true;

      //for(int i = 0; i < 10; i++)
      //{

      //   if (!operating_system_driver::get().m_bGetUserWallpaper)
      //   {


      //   }

      //   sleep(50_ms);

      //}

      //strUrl = operating_system_driver::get().m_strGetUserWallpaper;

      return true;

   }


#endif

   //::crypto::crypto* system::crypto()
   //{

   //   return m_pcrypto;

   //}


   //::pointer<::account::user_set>system::userset()
   //{

   //   return m_puserset;

   //}


   bool system::defer_accumulate_on_open_file(string_array stra, string strExtra)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_timeCommandLineLast.Now();

      m_iCommandLineDelay = 1000;

      ::collection::index iIndex = stra.find_first(":");

      if (iIndex >= 0)
      {

         if (iIndex > 0)
         {

            m_straCommandLineAccumul.append(stra.slice(0, iIndex));

         }

         m_straCommandLineExtra.append(stra.slice(iIndex));

      }
      else
      {

         if (m_straCommandLineExtra.has_elements())
         {

            m_straCommandLineExtra.append(stra);

         }
         else
         {

            m_straCommandLineAccumul.append(stra);

         }

      }

      ::acme::application * papplication = nullptr;

      auto psession = session();

      if (psession == nullptr)
      {

         papplication = application();

      }
      else
      {

         auto appptra = psession->get_applicationa();

         appptra.predicate_erase([](auto & papp)
            {

               return papp->is_system() || papp->is_session();

            });

         if (appptra.has_elements())
         {

            papplication = appptra[0];

         }

      }

      if (papplication != nullptr)
      {

         ::pointer<::request>prequest(e_create_new, this);

         //merge_accumulated_on_open_file(pcreate)
         ;
         papplication->post_request(prequest);

      }

      return true;

   }




   //bool system::merge_accumulated_on_open_file(::request * prequest)
   //{

   //   if(m_straCommandLineAccumul.is_empty())
   //   {

   //      return true;

   //   }

   //   string_array straAccumul = m_straCommandLineAccumul;

   //   string_array straExtra = m_straCommandLineExtra;

   //   m_straCommandLineAccumul.erase_all();

   //   m_straCommandLineExtra.erase_all();

   //   //auto pcreate = __create_new < ::create >();

   //   string strExtra = straExtra.implode(" ");

   //   if(straAccumul.is_empty())
   //   {

   //      pcreate->_001ParseCommandFork("app.exe : open_default " + strExtra);

   //   }
   //   else
   //   {

   //      string strParam = straAccumul.surround_and_implode(" ", "\"", "\"");

   //      pcreate->_001ParseCommandFork("app.exe " + strParam + " " + ::str::has_char(strExtra, " : "));

   //   }

   //   if(pcreate->m_pcommandline.is_null())
   //   {

   //      pcreate->m_pcommandline = line;

   //   }
   //   else if(line->m_ecommand == command_line::command_file_open)
   //   {

   //      pcreate->m_payloadFile.stra().case_insensitive_add_unique(line->m_payloadFile.stra());

   //      pcreate->m_ecommand = command_line::command_file_open;

   //   }
   //   else if(line->m_ecommand == command_line::command_application_start)
   //   {

   //      pcreate->m_payloadFile.stra().add(line->m_payloadFile.stra());

   //      pcreate->m_ecommand = command_line::command_application_start;

   //   }

   //   return true;

   //}


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


   void system::on_open_file(const ::string & pszFile)
   {

      //file_put_contents("/Users/camilo/debug/on_open_file.txt", pszFile);

      m_bPostedInitialRequest = true;

      ::pointer<::request>prequest(e_create_new, this);

      prequest->m_payloadFile = pszFile;

      auto papplication = application();

      if (!papplication)
      {

         papplication = application();

      }

      papplication->m_papexapplication->post_request(prequest);

      //      defer_accumulate_on_open_file({pszFile}, "");

            //return ::success;

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

   void system::on_os_text(enum_os_text etext, string strText)
   {


   }

   //#endif

   //#ifdef UNIVERSAL_WINDOWS
   //
   //
   //
   //   CLASS_DECL_APEX bool window_rectangle(::apex::system_window ^ pwindow, ::rectangle_f64 * prectangle)
   //
   //   {
   //
   //      ::winrt::Windows::Foundation::Rect rectangle = pwindow->window_rectangle();
   //
   //      prectangle->left() = rectangle.X;
   //
   //      prectangle->top() = rectangle.Y;
   //
   //      prectangle->right() = prectangle->left() + rectangle.Width;
   //
   //      prectangle->bottom() = prectangle->top() + rectangle.Height;
   //
   //
   //      return true;
   //   }
   //
   //
   //   CLASS_DECL_APEX bool window_rectangle(::apex::system_window ^ pwindow, ::rectangle_i32 * prectangle)
   //   {
   //
   //      ::rectangle_f64 rectangle;
   //
   //      if (!window_rectangle(pwindow, (::rectangle_f64*)rectangle_i32))
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
   //   throw ::exception(todo("aura"));
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

      return acmefile()->as_string(dir()->standalone() / (str + ".txt"));

   }


   void system::set_standalone_setting(string str, string strSetting)
   {

      acmefile()->put_contents(dir()->standalone() / (str + ".txt"), strSetting);

   }


   void system::on_extra(string str)
   {

//      auto purl = url();

      ::url::url url(str);

      string strProtocol = url.connect().protocol();

#ifdef WINDOWS_DESKTOP

      if (strProtocol == "ca2project")
      {

         string strBase = url.connect().host();

         string strAppId = url.request().as_string();

         strAppId.begins_eat("/");

         string strQuery = url.request().query();

         string strMessage;

         strMessage.formatf("protocol: ca2project\nbase: %s\nAppId: %s\nquery: %s\n", strBase, strAppId, strQuery);

         //message_box(strMessage, e_message_box_ok);

         string strParams;

         //strParams.formatf("\"ca2project\" \"%s\" \"%s\" \"%s\"\n", strBase, strAppId, strQuery);

         string strProj;

         strProj = strAppId;

         string_array stra;

         stra.explode("/", strAppId);

         strProj.case_insensitive_replace_with("_", "-");
         strProj.case_insensitive_replace_with("_", "/");

         //strProj = "..\\..\\..\\" + stra[0] + "\\" + stra[1] + "\\" + stra[1] + ".vcxproj";

         strParams.formatf("\"openvsproject://%s\"", strProj);


         //int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", e_display_none, 30, 1000, nullptr, 0);

      }
#elif defined MACOS
      if (strProtocol == "ca2project")
      {

         string strBase = ::url::get_host(str);

         string strScheme = ::url::get_request_path(str);

         strScheme.begins_eat("/");

         if (strBase == "scheme")
         {

            //         int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", e_display_none, 30, 1000, nullptr, 0);

            ::file::path pathScript = acmedirectory()->tool() / "papaya/script/xcode_set_active_scheme.scpt";

            ::system("osascript \"" + pathScript + "\" \"" + strScheme + "\"");

         }
         else if (strBase == "archive")
         {

            ::system("xcodebuild -scheme \"" + strScheme + "\" archive");

         }

      }
#endif

   }






   //void system::__tracea(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz)
   //{

   //   if (m_ptracelog.is_null())
   //   {

   //      __simple_tracea(trace_object(pparticle), elevel, pszFunction, pszFile, iLine, psz);

   //      return;

   //   }

   //   log().__tracea(trace_object(pparticle), elevel, pszFunction, pszFile, iLine, psz);

   //}



   string system::get_user_language()
   {

      return standalone_setting("current_language");

   }


   void system::set_user_language(::apex::application * papp, ::collection::index iSel)
   {

      auto psession = session();

      auto papexapplication = psession->application()->m_papexapplication;

      auto puserlanguagemap = papexapplication->m_puserlanguagemap;

      if (iSel < 0 || iSel >= puserlanguagemap->m_straLang.get_count())
      {

         return;

      }

      string strLang = puserlanguagemap->m_straLang[iSel];

      if (strLang == puserlanguagemap->m_strLang)
      {

         return;

      }

      set_user_language(papp, strLang);

      //if (!set_user_language(papp, strLang))
      //{

      //   return false;

      //}

      //return true;

   }


   void system::set_user_language(::apex::application * papp, string strLang)
   {

      auto psession = session();

      auto papexapplication = psession->application()->m_papexapplication;

      auto puserlanguagemap = papexapplication->m_puserlanguagemap;

      puserlanguagemap->set_language(papp, strLang);

      set_standalone_setting("current_language", strLang);

   }


   void system::process_machine_event_data(machine_event_data * pdata)
   {

      if (pdata->m_fixed.m_bRequestCloseApplication)
      {

         destroy();

      }

   }


   void system::browser(string strUrl, string strBrowser, string strProfile, string strTarget)
   {

      node()->open_url_link_at_system_browser(strUrl, strProfile);

      //return ::success;

#if 0

      if (strProfile.is_empty() && strTarget.is_empty() && strBrowser.is_empty())
      {

         //::message_box_synchronous(NULL, strUrl, strUrl, e_message_box_ok);

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

      if (strWeather.is_empty() || !strWeather.case_insensitive_begins("browser_"))
      {

         strWeather = file()->as_string(acmedirectory()->system() / "browser_weather.txt");

      }

      if (strWeather.is_empty() || !strWeather.case_insensitive_begins("browser_"))
      {

         strWeather = "browser_day";

      }

      ::earth::time timeNow = ::earth::time::now();

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

            //strUrl = "https://ca2.software/open_f___?url=" + ::url::encode(strUrl) + "&profile=" + ::url::encode(strProfile) + "&target=" + ::url::encode(strTarget);

         }
         else
         {

            //strUrl = "https://ca2.software/open_tab?url=" + ::url::encode(strUrl) + "&profile=" + ::url::encode(strProfile) + "&target=" + ::url::encode(strTarget);

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

#if defined(UNIVERSAL_WINDOWS)


         string * pstrNew = new string(strUrl);

         ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainImpact->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
            ref __new< ::winrt::Windows::UI::Core::DispatchedHandler([pstrNew] >()
               {

                  ::winrt::Windows::Foundation::Uri ^ uri = ref new ::winrt::Windows::Foundation::Uri (*pstrNew);

                  delete pstrNew;

                  LauncherOptions ^ options = ref new LauncherOptions();

                  options->TreatAsUntrusted = false;

                  Launcher::LaunchUriAsync(uri, options);

               }));

         //#elif defined(LINUX)
         //
         //      ::acme::system("xdg-open \"" + strUrl + "\"");
         //
         //      return true;
         //
         //#elif defined(__APPLE__)
         //    openURL(strLink);
         //  return true;
#elif defined(ANDROID)

         string strOpenUrl;

         if (::operating_system_driver::get()->m_pszOpenUrl != nullptr)
         {

            strOpenUrl = ::operating_system_driver::get()->m_pszOpenUrl;

            try
            {

               ::free((void *)::operating_system_driver::get()->m_pszOpenUrl);

            }
            catch (...)
            {


            }

            ::operating_system_driver::get()->m_pszOpenUrl = nullptr;

         }


         //strOpenUrl = strUrl + ::str::has_char(strOpenUrl, ";");

         //if (strOpenUrl.has_char())
         {

            // psystem->m_pandroidinitdata->m_pszOpenUrl = strdup(strLink);

            ::operating_system_driver::get()->m_pszOpenUrl = strdup(strUrl);

         }


#elif defined(MACOS)

         ::acme::system("open -a /Applications/Safari.app \"" + strUrl + "\"");

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

         //call_sync("C:\\Program Files\\Opera.exe", "--user-data-dir=\"" + path + "\" " + strUrl, "C:\\Users\\camilo\\AppData\\Local\\Vivaldi\\papp", SW_SHOWNORMAL, 0);

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

            ::acme::system("xdg-open " + strUrl);

         }



#endif

      }

#endif

   }



   void system::chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam)
   {

#ifdef UNIVERSAL_WINDOWS

      node()->native_full_web_browser(strUrl);

      return;

#endif

      ::file::path pathDir;

      pathDir = path.folder();

      ::file::path pathAppDataDir(acmedirectory()->ca2roaming());

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

               auto iFind = strParam.find_index("%1");

               if (::found(iFind))
               {

                  strParam = strParam(0, iFind) + strUrl + strParam.substr(iFind + 2) + " ";

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

            if (strParam.trimmed().case_insensitive_begins("--"))
            {

               strParam = "--user-data-dir=\"" + pathProfile + "\" " + strParam;

            }
            else
            {

               strParam += "--user-data-dir=\"" + pathProfile + "\"";

            }

            strParam += " " + acmefile()->as_string(acmedirectory()->localconfig() / "app-core/commander/chrome.txt");

            auto pnode = node();

            pnode->call_async(path, strParam, pathDir, e_display_default, false);

         }

#elif defined(MACOS)

         string_array sa;

         sa = get_c_args_for_c(strParam);

         sa.add("--user-data-dir=" + pathProfile + "");

         string strChrome = acmefile()->as_string(acmedirectory()->localconfig() / "app-core/commander/chrome.txt");

         string_array sa2 = get_c_args_for_c(strChrome);

         sa.append(sa2);

         auto argv = sa.c_ansi_get();

         argv.add(nullptr);

         auto purl = url();

         string strApp = ::url::decode(path);

         // 0x00010000 NSWorkspaceLaunchAsync
         // 0x00080000 NSWorkspaceLaunchNewInstance

         auto pnode = node();

         pnode->launch_app(strApp, argv.data(), 0x00010000 | 0x00080000);

#elif defined(LINUX)

         ::file::path shell;

         shell = "/bin/bash";

         strParam += "--user-data-dir=\"" + pathProfile + "\"";

         strParam += " " + acmefile()->as_string(acmedirectory()->localconfig() / "app-core/commander/chrome.txt");

         string strCmd = path + " " + strParam;

         strCmd.find_replace("\'", "\\\'");

         strParam = " -c '" + strCmd + "'";

         informationf(strParam);

         //auto psystem = system();

         auto pnode = node();

         pnode->call_async(shell, strParam, pathDir, e_display_default, false);

#endif

      }
      catch (...)
      {


      }

   }


   void system::defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile)
   {

#ifdef UNIVERSAL_WINDOWS


#else

      if (dir()->is(pathProfile))
      {

         return;

      }

      ::file::path pathDir;

      pathDir = pathFirefox.folder();

      ::file::path pathProfileDir;

      pathProfileDir = pathProfile.folder();

      dir()->create(pathProfileDir);

      string strParam = "-no-remote -CreateProfile \"" + strProfileName + " " + pathProfile + "\"";

      ::property_set set;

      auto pnode = node();

      ::i32 iExitCode = 0;

      pnode->call_sync(pathFirefox, strParam, pathDir, e_display_default, 3_minute, set, &iExitCode);

#endif

   }




   void system::firefox(string strUrl, string strBrowser, string strProfile, string strParam)
   {

#ifdef UNIVERSAL_WINDOWS

      node()->native_full_web_browser(strUrl);

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

      m_pacmenode->m_papexnode->get_firefox_installation_info(strBrowserPath, strBrowserDir);

      //if (::failed(estatus))
      //{

      //   return estatus;

      //}

      if (!file()->exists(strBrowserPath) || !dir()->is(strBrowserDir))
      {

         throw ::exception(error_not_found);

      }

      strBrowserHelperPath = ::file::path(strBrowserDir) / "uninstall/helper.exe";

      strBrowserHelperDir = ::file::path(strBrowserDir) / "uninstall";

      pathProfile = pathAppDataDir / "ca2/Firefox/Profile" / strProfile;

      defer_create_firefox_profile(strBrowserPath, strProfile, pathProfile);

      bool bFound = false;

      if (!bFound)
      {

         auto pnode = node();

         pnode->call_async(strBrowserPath, strParam, strBrowserDir, e_display_normal, false);

         pnode->call_async(strBrowserHelperPath, "/SetAsDefaultAppUser", strBrowserHelperDir, e_display_none, false);

      }

      if (strBrowser.has_char())
      {

         file()->put_text_utf8(acmedirectory()->system() / "browser.txt", strBrowser);

         file()->put_text_utf8(acmedirectory()->system() / "browser_path.txt", strBrowserPath);

         file()->put_text_utf8(acmedirectory()->system() / "browser_dir.txt", strBrowserDir);

      }

#endif

      //return ::success;

   }


   //string system::get_local_mutex_name(const ::string & pszAppName)
   //{

   //   string strMutex;

   //   strMutex.formatf("Local\\%s", pszAppName.c_str());

   //   return strMutex;

   //}

   //
   //string system::get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId)
   //{
   //   
   //   string strId(pszId);
   //   
   //   string strMutex;
   //   
   //   strMutex.formatf("Local\\%s, atom:%s", pszAppName.c_str(), strId.c_str());
   //   
   //   return strMutex;

   //}

   //
   //string system::get_global_mutex_name(const ::string & pszAppName)
   //{
   //   
   //   string strMutex;
   //   
   //   strMutex.formatf("Global\\%s", pszAppName.c_str());
   //   
   //   return strMutex;

   //}

   //
   //string system::get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId)
   //{
   //   
   //   string strId(pszId);
   //   
   //   string strMutex;

   //   strMutex.formatf("Global\\%s, atom:%s", pszAppName.c_str(), strId.c_str());

   //   return strMutex;

   //}


   //::task_group * system::task_group(::enum_priority epriority)
   //{

   //   if (m_bAvoidProcedureFork)
   //   {

   //      return nullptr;

   //   }

   //   synchronous_lock synchronouslock(this->synchronization());

   //   auto & threadgroupa = m_taskgroupmap[epriority];

   //   if (threadgroupa.is_empty())
   //   {

   //      auto pgroup = ::place(new ::task_group(this, epriority));

   //      threadgroupa.add(pgroup);

   //   }

   //   return threadgroupa.last();

   //}


   //::task_tool * system::task_tool(::enum_task_tool etool)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   auto& threadtoola = m_tasktoolmap[etool];

   //   if (threadtoola.is_empty())
   //   {

   //      auto ptool = ::place(new ::task_tool());

   //      ptool->m_atom = etool;

   //      threadtoola.add(ptool);

   //   }

   //   return threadtoola.last();

   //}


   //::pointer<::topic>system::new_subject(const MESSAGE& message)
   //{

   //   auto atom = (::iptr)message.wParam;

   //   auto ptopic = topic(atom);

   //   ptopic->m_pobjectTopic = (::object*) message.lParam.m_lparam;

   //   return ptopic;

   //}


   void system::open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      fork([this, strUrl, strProfile, strTarget]()
         {

            browser(strUrl, "", strProfile, strTarget);

         });

      //return ::success;

   }


   void system::verb() // ambigous inheritance from ::apex::system/::axis::application
   {

      return ::thread::verb();

   }


   string system::crypto_md5_text(const ::string & str)
   {

      auto pcrypto = crypto();

      return pcrypto->md5(str);

   }


   //string system::url::encode(const ::string & str)
   //{

   //   return m_purldepartment->::url::encode(str);

   //}


} // namespace apex








//#include "base/node/_node.h"


//#ifdef WINDOWS_DESKTOP
//#elif defined(UNIVERSAL_WINDOWS)
//#include "apex/operating_system/universal_windows/_universal_windows.h"
//#endif


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


#endif

//#ifdef LINUX
//#include <dlfcn.h>
//
////void* g_pbasecore = nullptr;
//
//
//typedef void BASECORE_INIT();
//#endif // LINUX
//

namespace apex
{


   CLASS_DECL_APEX void black_body(float * r, float * g, float * b, ::u32 dwTemp);


   void system::discard_to_factory(::pointer<object>pca)
   {

      __UNREFERENCED_PARAMETER(pca);

   }


   ::pointer<::data::node>system::load_xml(const ::string & pszXml)
   {

      throw ::interface_only();

      return nullptr;

   }


   void system::on_start_find_applications_from_cache()
   {

      throw ::exception(todo, "filehandler");
      // m_pfilehandler->m_ptree->erase_all();

   }


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

   void system::on_map_application_library(::acme::library & library)
   {

      throw ::exception(todo, "filehandler");
      // m_pfilehandler->defer_add_library(library.m_pca2library);

   }



#ifdef LINUX


   //   void system::deferx_initializex_x11()
   //   {
   //
   //      return ::acme::system::deferx_initializex_x11();
   //
   //   }


   //   bool system::sn_start_context()
   //   {
   //
   //      return false;
   //
   //   }


#endif


   ::apex::history & system::hist()
   {

      return *m_phistory;

   }


   void system::set_history(::apex::history * phistory)
   {

      //auto estatus = 
      __construct(m_phistory, phistory);

      /*   if (!estatus)
         {

            return estatus;

         }

         return estatus;*/

   }


   //::acme::library * system::on_get_library(const ::string & pszLibrary)
   //{

   //   ::pointer<::acme::library>plibrary;

   //   bool bLibraryOk = false;

   //   auto plibraryfactory = ::system_setup::get_first(::system_setup::flag_library, pszLibrary);

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

   networking::networking* system::networking()
   {

      if(!m_pnetworking)
      {

         initialize_networking();

      }

      return m_pnetworking;

   }


   void system::on_allocation_error(const ::string & str, ::object * pparticle)
   {

      string strMessage;

      strMessage.formatf("system::on_allocation_error Implement \"%s\" allocation\n", str.c_str());

      dev_log(strMessage);

   }


   //void system::on_request(::create* pcreate)
   //{

   //   //get_platform(pcreate->m_iEdge,pcreate->m_pappbias);

   //   ::apex::system::on_request(pcreate);

   //}


   //bool system::sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser, ::http::cookies* pcookies)
   bool system::sync_load_url(string & str, const ::string & pszUrl, ::http::cookies * pcookies)

   {

      string filename = file()->time_square();

      property_set set;

      //set["user"] = puser;

      set["cookies"] = pcookies;

      if (!::acme::context::http()->download(pszUrl, filename, set))

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

         file()->erase(filename);

         return ::acme::context::http()->download(str, strLocation, set);

      }

      str = file()->as_string(filename);

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


   //void system::add_impact_library(::acme::library* plibrary)
   //{

   //   m_libraryspa.add(plibrary);

   //   ::array < ::atom > ida;

   //   plibrary->get_create_impact_id_list(ida);

   //   for (i32 i = 0; i < ida.get_count(); i++)
   //   {

   //      m_idmapCreateImpactLibrary.set_at(ida[i], plibrary);

   //   }

   //   return true;

   //}


   //   void system::post_fork_uri(const ::string & pszUri,application_bias * pappbias)
   //   {
   //
   //      add_fork_uri(pszUri,pappbias);
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


#ifdef UNIVERSAL_WINDOWS


   bool system::window_rectangle(::rectangle_i32 * prectangle)
   {

      if (::is_null(session()))
      {

         return false;

      }

      return true;

   }


#endif


   //   void system::assert_ok() const
   //   {
   //
   //      ::thread::assert_ok();
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


   void system::main()
   {

      //process_init();

      //if (application()->is_console())
      //{

      //   application()->main();

      //}
      //else
      //{

         //auto estatus = 
      ::thread::main();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   //}

      //if (m_iExitCode == 0 && m_estatus.failed())
      //{

      //   m_iExitCode = m_estatus.exit_code();

      //}

   }


   //pointer_array < ::apex::session > & system::planesessionptra()
   //{

   //   return m_planesessionptra;

   //}


   void system::hist_hist(const ::string & psz)
   {

      hist().hist(psz);

   }


   void system::system_id_update(::i64 iUpdate, ::i64 iPayload)
   {

      call((::enum_id)iUpdate, iPayload);

   }


   //   void system::add_handler(::matter* pmatter, bool bPriority)
   //   {
   //
   //      ::apex::context::add_handler(pmatter, bPriority);
   //
   //   }

   void system::add_signal_handler(const ::signal_handler & signalhandler, const ::atom & atomSignal)
   {

      ::manager::add_signal_handler(signalhandler, atomSignal);

   }

   //   void system::add_signal_handler(const ::signal_handler& signalhandler, const ::atom& atomSignal)
   //   {
   //
   //      auto psignal = get_signal(atomSignal);
   //
   //      if (::is_null(psignal))
   //      {
   //
   //         throw ::exception(error_resource);
   //
   //      }
   //
   //      psignal->add_signal_handler(signalhandler);
   //
   //   }


   //   void system::add_signal_handler(const ::signal_handler& signalhandler, const ::atom& atomSignal)
   //   {
   //
   //      manager::add_signal_handler(signalhandler, atomSignal);
   //      
   //   }


   void system::erase_signal_handler(::signal_handler::base * pbase)
   {

      manager::erase_signal_handler(pbase);

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


   void system::handle(::topic * ptopic, ::context * pcontext)
   {

      acme::system::handle(ptopic, pcontext);
      //      auto psignal = get_signal((::enum_id) iUpdate);
      //
      //      psignal->m_payload = iPayload;
      //
      //      psignal->notify();



   }


   bool system::_handle_uri(const ::string & strUri)
   {

      if (application() && application()->_handle_uri(strUri))
      {

         return true;

      }

      if (!application() || application() != application())
      {

         if (application() && application()->_handle_uri(strUri))
         {

            return true;

         }

      }

      return false;

   }


   void system::destroy()
   {

      //::main::destroy();

      ::apex::context::destroy();

      m_sessionmap.clear();

      //m_mapLibrary4.clear();

      //return ::success;

      ::acme::system::destroy();

   }


   void system::process_exit_status(::object * pparticle, const ::e_status & estatus)
   {

      if (estatus == error_exit_session)
      {

         pparticle->session()->destroy();

      }
      else if (estatus == error_exit_application)
      {

         pparticle->session()->destroy();

      }
      else
      {

         ::acme::system::process_exit_status(pparticle, estatus);

      }

   }


   int system::console_end(::e_status estatus)
   {

      int iExitCode = estatus.exit_code();

      if (iExitCode == 0)
      {

         if (is_true("show_application_information"))
         {

            informationf("return code is %" PRIi64 "x", estatus.m_eenum);

         }

      }

      return iExitCode;

   }


   void system::system_construct(::acme::application * papplication)
   {

      ::acme::system::system_construct(papplication);

      //main::system_construct(papplication);

   }


   void system::defer_innate_ui()
   {
      
      if (!m_pinnateui)
      {

//#ifdef WINDOWS
//
//         auto pfactory = factory("innate_ui", "win32");
//
//         pfactory->merge_to_global_factory();
//
//#elif defined(LINUX)

         node()->m_papexnode->defer_innate_ui();

//#elif defined(MACOS)
//
//         node()->m_papexnode->defer_innate_ui();
//         
//#endif

         __construct(m_pinnateui);

      }

   }


#ifdef __APPLE__

   string get_bundle_app_library_name();

#endif




   //pointer <  >::apex::session* platform_create_session()
   //{
   //
   //   auto pstaticsetup = ::system_setup::get_first(::system_setup::flag_system, "");
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



   void system::application_main(int argc, char * argv[], const ::string & pszCommandLine)
   {

      //apex_application_main(argc, argv, pszCommandLine);

   }


   //pointer< ::extended::future < ::conversation > > system::_message_box(::particle * pparticle, const ::string & pszText, const ::string & pszTitle, const ::e_message_box & emessagebox)
   //{

   //   return ::system::_message_box(pparticle, pszText, pszTitle, emessagebox);

   //}

   // https://github.com/umpirsky/tld-list/blob/master/data/en/tld.txt


   ::string system::fetch_public_internet_domain_extension_list_text()
   {

      //auto estatus = 
      ///::acme::system::get_public_internet_domain_extension_list(stra);

      //return estatus;

      return {};

   }


   //void system::get_public_internet_domain_extension_list(string_array& stra)
   //{

   ////   //auto estatus = 
   ////   ::acme::system::get_public_internet_domain_extension_list(stra);

   //   ///return estatus;

   //}


   void system::system_main()
   {

      ::acme::system::system_main();

   }

   //
   //   void system::windowing_post_quit()
   //   {
   //      
   //      
   //   }

   void system::initialize_networking()
   {

      try
      {

         ::e_status estatus = ::success_none;

         auto & pfactoryNetworking = factory("networking", "bsd");

         //if (!pfactoryCrypto)
         //{

         //   WARNING("Could not open crypto openssl plugin.");

         //   //return pfactoryCrypto;

         //}

         pfactoryNetworking->merge_to_global_factory();

         //estatus =
         pfactoryNetworking->__construct(this, m_pnetworking);


         if (!m_pnetworking)
         {

            //estatus = __construct_new(m_psockets);

            //__construct(m_pnetworking);

            //if (!estatus)
            //{

            //   return estatus;

            //}

         }

         //return estatus;

      }
      catch (...)
      {

         application()->m_bNetworking = false;

      }

   }



   void system::on_application_dark_mode_change()
   {
   
      this->signal(id_application_dark_mode_change);

      ::acme::system::on_application_dark_mode_change();

   }


} // namespace apex



