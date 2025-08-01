#include "framework.h"
#include "session.h"
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
#include "acme/filesystem/watcher/watcher.h"
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
#include "acme/platform/http.h"
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
#include "apex/networking/http/message.h"
#include "apex/networking/internet.h"
#include "apex/networking/networking.h"
#include "apex/operating_system/department.h"
#include "apex/parallelization/threading.h"
#include "apex/user/user/language_map.h"
#ifdef LINUX
#include <unistd.h>
#endif
#include "component.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/prototype/text/context.h"
#include "apex/message/command.h"
#include "acme/prototype/geometry2d/geometry.h"
#include "acme/platform/hyperlink.h"
//#include "acme/platform/system_impl.h"
#include "acme/prototype/string/base64.h"


int file_put_contents(const ::file::path & path, const_char_pointer contents);;
CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::scoped_string & scopedstrMoreDetails);


CLASS_DECL_ACME ::string get_operating_system_name();


//extern ::apex::system* g_papexsystem;

//CLASS_DECL_APEX void apex_generate_random_bytes(void* p, memsize s);

//RECTANGLE__I32 get_main_screen_rectangle();


///const ::string & g_pszMultimediaLibraryName = nullptr;

void apex_system_update(const ::atom & atom, const ::payload & payload);

void apex_system_set_modified(const ::atom & atom);


// CLASS_DECL_APEX void multimedia_set_library_name(const ::scoped_string & scopedstr)
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

CLASS_DECL_APEX void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


//void os_post_quit();


#ifdef UNIT_TEST
void unit_test_primitive_var_apex_block();
#endif


void dappy(const ::scoped_string & scopedstr);


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

      //m_papexsystem = this;

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

      factory()->add_factory_item < ::apex::session, ::apex::session >();
      factory()->add_factory_item < ::http::context, ::platform::http >();
      factory()->add_factory_item < ::http::message, ::nano::http::get>();
      factory()->add_factory_item < ::apex::component, ::component >();

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

      //m_bSimpleMessageLoop = false;


      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

      //      factory()->add_factory_item < ::apex::application >();
            //factory()->add_factory_item < ::apex::idpool, ::acme::idpool >();


   }


#ifdef _DEBUG


   long long system::increment_reference_count()
   {

      return ::platform::system::increment_reference_count();

   }


   long long system::decrement_reference_count()
   {

      return ::platform::system::decrement_reference_count();

   }


#endif


   // void system::on_set_platform()
   // {
   //
   //    apex::handler_context::on_set_platform();
   //
   //    platform::system::on_set_platform();
   //
   //
   // }


   void system::on_initialize_particle()
   {

      //::platform::context::on_initialize_particle();

      ::platform::system::on_initialize_particle();

   }


   void system::install_message_routing(::channel * pchannel)
   {

      //::platform::context::install_message_routing(pchannel);

      //MESSAGE_LINK(e_message_erase_session, pchannel, this, &system::on_message_erase_session);

   }


   // void system::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
   // {
   //
   //
   // }
   //
   //
   // string system::get_locale_schema_dir()
   // {
   //
   //    return "_std/_std";
   //
   // }






   bool system::on_get_task_name(string & strTaskName)
   {

      if (this->is_console())
      {

         return false;

      }

      return ::thread::on_get_task_name(strTaskName);

   }


   ::factory::factory * system::node_factory()
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

         if (is_command_line_parameter_true(strShowApplicationInformation, this->m_strCommandLine, "show_application_information"))
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

      //initialize(this);

      //set_object(psystem);


      // what could influence time before Main?
      // cold start (never previously called program and its Dlls...)?
      m_timeMainStart = m_timeStart;

      //xxdebug_box("box1", "box1", e_message_box_icon_information);
   //
     // ::file::path pathOutputDebugString = directory_system()->system() / strAppId / "information.txt" ;

      //::file::path pathGlobalOutputDebugString = directory_system()->config() / "information.txt" ;

      //::apex::g_bOutputDebugString = file_system()->exists(pathOutputDebugString)||  file_system()->exists(pathGlobalOutputDebugString);

      //return true;


      factory()->add_factory_item<http::context>();

      //auto estatus =
      ::platform::system::process_init();

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

#if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)

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

#ifdef _DEBUG

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

      m_nSafetyPoolSize = 512;        // default int_size

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

      //    ::file::path pathNoExceptionStackTrace = directory_system()->config() / "system/no_exception_stack_trace.txt";

      //    if (file_system()->exists(pathNoExceptionStackTrace))
      //    {

      //       bGlobalEnableStackTrace = false;

      //    }

      //    ::exception::enable_call_stack_back_trace(bGlobalEnableStackTrace);

      // }

      //add_factory_item < ::stdio_file, ::file::text_file >();
      //add_factory_item < ::stdio_file, ::file::file >();
      factory()->add_factory_item < ::long_long_array >();
      factory()->add_factory_item < ::double_array >();
      factory()->add_factory_item < ::acme::library >();

      factory()->add_factory_item < ::file::path_object >();

      factory()->add_factory_item < string_array >();
      factory()->add_factory_item < memory >();
      factory()->add_factory_item < memory_file >();
      factory()->add_factory_item < ::int_array >();

      //factory()->add_factory_item < ::file::path_object >();
      //factory()->add_factory_item < ::long_long_array >();
      //factory()->add_factory_item < ::double_array >();
      //factory()->add_factory_item < ::acme::library >();

      //factory()->add_factory_item < ::file::path_object >();

      //factory()->add_factory_item < string_array >();
      //factory()->add_factory_item < memory >();
      //factory()->add_factory_item < memory_file >();
      //factory()->add_factory_item < ::int_array >();

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


#if !defined(__ANDROID__) && !defined(APPLE_IOS)

      if (!application()->is_service() || application()->is_user_service())
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

      //estatus = __øconstruct(m_papexnode);

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

         information("Process PID: " + ::as_string(iPid));

      }


#endif


      //#ifdef LINUX
      //
      //      {
      //
      //         string str;
      //
      //         str = directory_system()->home() / ".profile";
      //
      //         if(!file_system()->exists(str))
      //         {
      //
      //            str = directory_system()->home() / ".bashrc";
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
      //            character_count i = strLine.find('=');
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
      //               ::zero(scopedstrEnvLine, iSize);
      //
      //               strcpy(scopedstrEnvLine, strLine);
      //
      //               ::putenv(scopedstrEnvLine);
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
      //add_factory_item < happening >();

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

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create("/ca2core");

                  file_system()->put_contents("/ca2core/teste.txt", str, str.length());
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

      if (!m_pmachinehappeningcentral)
      {

#ifndef APPLE_IOS

         //auto estatus =
         __construct_new(m_pmachinehappeningcentral);

         //if (!estatus)
         //{

         //   return false;

         //}

         //if(!m_pmachinehappeningcentral->initialize())
         //{

         //   return false;

         //}

         if (m_pmachinehappeningcentral->is_close_application())
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
      //         informationf("\nCurrent Working Directory : " + strCurrentWorkingDirectory);
      //
      //      }

            //estatus = m_ptracelog->process_init();

            //if(!estatus)
            //{

               //WARNING("failed to process_init ::apex::log trace");

            //}

            //estatus =

      //initialize_context();


   }


   void system::init1()
   {

      //auto estatus =
      ::platform::system::init1();

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

//      if (application()->m_bCrypto)
//      {
//
//         auto & pfactoryCrypto = factory("crypto", "openssl");
//
//         //if (!pfactoryCrypto)
//         //{
//
//         //   WARNING("Could not open crypto openssl plugin.");
//
//         //   //return pfactoryCrypto;
//
//         //}
//
//         pfactoryCrypto->merge_to_global_factory();
//
//         //estatus =
//         pfactoryCrypto->__øconstruct(this, m_pcrypto);
//
//      }

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
      //       m_pdirectorysystem->m_bMatterFromHttpCache = false;
      //
      //       m_pdirectorysystem->m_bMatterFromResource = true;
      //
      //    }
      //    else
      //    {
      //
      //       if (m_iMatterFromHttpCache == -1)
      //       {
      //
      //          ::file::path pathSide = m_papplication->side_get_matter_path("app/_matter/main");
      //
      //          ::file::path pathLocal = local_get_matter_path("app/_matter/main");
      //
      //          bool bFileSystemMatter = m_pdirectorysystem->is(pathSide) || m_pdirectorysystem->is(pathLocal);
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
      //       m_pdirectorysystem->m_bMatterFromHttpCache = bMatterFromHttpCache;
      //
      //       m_pdirectorysystem->m_bMatterFromResource = false;
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

//#if !defined(CUBE) && !defined(__ANDROID__)
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

      ::platform::system::init2();

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

      auto strMain = directory()->install() / "app/_appmatter/main";

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


   // void system::initialize_context()
   // {
   //
   //    //auto estatus =
   //    ::platform::context::initialize_context();
   //
   //    //if(!estatus)
   //    //{
   //
   //    //   return estatus;
   //
   //    //}
   //
   //    //return estatus;
   //
   // }


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
      ::platform::system::on_start_system();

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
   //      unsigned long long tt;
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

//
//   void system::init_task()
//   {
//
//      ::thread::init_task();
//
//      call_init_system();
//
//      //auto estatus = ([a-z0-9_]+)_factory();
//
//      //if(!estatus)
//      //{
//
//        // return estatus;
//
//      //}
//
//      //auto estatus =
////      process_init();
////
////      //if(!estatus)
////      //{
////
////      //   return estatus;
////
////      //}
////
////      if (m_psystemParent)
////      {
////
////         m_psystemParent->add_reference(this);
////
////      }
////
////
////      //if (!estatus)
////      //{
////
////      //   return estatus;
////
////      //}
////
////      //estatus =
////      init1();
////
////      //if(!estatus)
////      //{
////
////      //   return estatus;
////
////      //}
////
////      //estatus =
////      init2();
////
////      //if (!estatus)
////      //{
////
////      //   return estatus;
////
////      //}
////
////
//////      estatus = process_init();
//////
//////      if (!estatus)
//////      {
//////
//////         return estatus;
//////
//////      }
////
////
////      //estatus = process_creation_requests();
////
////      //if (!estatus)
////      //{
////
////      //   return estatus;
////
////      //}
////
////      //return true;
//
//   }


   void system::init()
   {

      //return true;

   }


   //void system::post_pending_requests()
   //{

   //   while (handle_next_pending_request())
   //   {

   //   }

   //}


   //void system::defer_post_initial_request()
   //{

   //   ::platform::system::defer_post_initial_request();

   //   //if (!m_bPostedInitialRequest)
   //   //{

   //   //   m_bPostedInitialRequest = true;

   //   //   auto prequest = __create_new< ::request>();

   //   //   string strAppId = application()->m_strAppId;

   //   //   if (strAppId.is_empty())
   //   //   {

   //   //      if (application())
   //   //      {

   //   //         strAppId = application()->m_strAppId;

   //   //      }

   //   //   }

   //   //   prequest->m_strAppId = strAppId;

   //   //   //pcreate->m_pcommandline = __create_new < command_line >();
   //   //   post_request(prequest);

   //   //}

   //}


   //void system::post_request(::request* prequest)
   //{

   //   auto straArguments = ::system()->get_arguments();

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

      ::platform::system::inline_init();

      //::platform::context::inline_init();

   }


   void system::inline_term()
   {

      //::platform::context::inline_term();

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


   //void system::__task_init()
   //{

   //   try
   //   {

   //      ::thread::__task_init();

   //   }
   //   catch (exception & exception)
   //   {

   //      string strMoreDetails;

   //      strMoreDetails = "command line: " + string(this->m_strCommandLine) + "\n\n";

   //      auto pmessagebox = __initialize_new ::message_box(exception, strMoreDetails);

   //      throw exception;

   //   }

   //}


   ::platform::application * system::get_main_app()
   {

      return application();

   }

//
//   void system::init_system()
//   {
//
//      //auto estatus =
//      ::platform::system::init_system();
//
//      //if(!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
////      ::platform::application * pappStartup = ::platform::application::g_p;
////
////      if(::is_null(pappStartup))
////      {
////
////         pappStartup = new_app(m_strAppId);
////
////      }
////
////      //if (!pappStartup)
////      //{
////
////      //   return -1;
////
////      //}
////
////      __refer(application(), pappStartup);
////
////      application()->initialize(this);
////
////      application()->get_property_set().merge(get_property_set());
////
////      set_main_struct(*application());
//
//      //return estatus;
//
//   }


   void system::term()
   {


   }


   //void system::on_message_erase_session(::message::message * pmessage)
   //{

   //   auto iEdge = pmessage->m_wparam;

   //   erase_session(iEdge);

   //}


   string system::get_application_server_name()
   {

      return ::platform::system::get_application_server_name();

   }


   bool system::task_get_run() const
   {

      return ::thread::task_get_run();

   }

   [[nodiscard]] class ::handler::signal * system::signal(const ::atom& atom)
   {

      return ::manager::signal(atom);

   }


   void system::term1()
   {

   }


   void system::term2()
   {

      m_psignalmap.release();

      m_phistory.release();

      try
      {

         if (m_pmachinehappeningcentral)
         {

            m_pmachinehappeningcentral->destroy();

         }

      }
      catch (...)
      {

      }

   }


   //void system::thread_loop()
   //{

   //   return thread::thread_loop();

   //}


   //void system::term_task()
   //{

   //   try
   //   {

   //      term_system();

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      ::thread::term_task();

   //   }
   //   catch (...)
   //   {

   //   }

   //}


   //void system::post_to_all_threads(::enum_message emessage, ::wparam wparam, ::lparam lparam)
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

      ::platform::system::TermSystem();

   }


   //void system::create_os_node()
   //{

   //   ::platform::system::create_os_node();

   //}


   // ::apex::node * system::node()
   // {
   //
   //    return m_pnode ? m_pnode : nullptr;
   //
   // }


   ::file::watcher * system::file_watcher() const
   {

      if (!m_pfilewatcher)
      {

         ((system*)this)->__øconstruct(((system *)this)->m_pfilewatcher);

      }

      return m_pfilewatcher;

   }


   ::input::input * system::input()
   {

      if (!m_pinput)
      {

         auto pinput = node()->create_input();

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


   unsigned int system::os_post_to_all_threads(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      post_to_all_threads(emessage, wparam, lparam);

      return 0;

   }


   // bool system::is_system() const
   // {
   //
   //    return true;
   //
   // }


   int system::_001OnDebugReport(int i1, const ::scoped_string & scopedstr1, int i2, const ::scoped_string & scopedstr2, const ::scoped_string & scopedstr3, va_list args)
   {

      return _debug_logging_report(i1, scopedstr1, i2, scopedstr2, scopedstr3, args);

   }


   int system::_debug_logging_report(int iReportType, const ::scoped_string & scopedstrFileName, int iLineNumber, const ::scoped_string & scopedstrModuleName, const_char_pointer pszFormat, va_list list)
   {

      //if(!m_ptracelog || !m_ptracelog->m_bExtendedLog)
      //{

      //   return ::apex::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);

      //}

      string str;

      if (scopedstrFileName.has_character() || scopedstrModuleName.has_character())
      {

         string_array stra;

         if (scopedstrFileName.has_character())
         {

            stra.add(scopedstrFileName);

         }

         if (scopedstrModuleName.has_character())
         {

            stra.add(scopedstrModuleName);

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


   bool system::assert_failed_line(const ::scoped_string & scopedstrFileName, int iLine)
   {

      __UNREFERENCED_PARAMETER(scopedstrFileName);

      __UNREFERENCED_PARAMETER(iLine);

      return false;

   }


   bool system::on_assert_failed_line(const ::scoped_string & scopedstrFileName, int iLine)
   {

      __UNREFERENCED_PARAMETER(scopedstrFileName);

      __UNREFERENCED_PARAMETER(iLine);

      return true;

   }


   //void system::__set_thread_on()
   //{

   //   ::thread::__set_thread_on();

   //}


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
   //         m_spmutexOpenweatherCity = __allocate ::pointer < ::mutex > ();
   //
   //#else
   //
   //         m_spmutexOpenweatherCity = __allocate ::pointer < ::mutex > (e_create_new, false, "Global\\ca2_weather_city");
   //
   //#endif
   //
   //      }
   //
   //      return m_spmutexOpenweatherCity;
   //
   //   }


      //void system::on_allocation_error(const ::scoped_string & scopedstr, ::particle * pparticle)
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



   machine_event_central * system::machine_event_central()
   {
      
      return m_pmachinehappeningcentral;
      
   }







   //::apex::os & system::os()
   //{

   //   return *m_spos;

   //}


//pointer_array < ::apex::session > & system::basesessionptra()
//{

//   return m_basesessionptra;

//}


   ::operating_system::department * system::operating_system()
   {

      return m_poperatingsystem;

   }


   void system::initialize_log(const ::scoped_string & scopedstrId)
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

//      for(int i = 0; i < appptra().get_size(); i++)
      //    {
      //     ::application * papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }


   void system::appa_set_locale(const ::scoped_string & scopedstrLocale, const ::action_context & context)
   {

      //retry_single_lock rsl(mutex(),::time(100),::time(100));
      single_lock rsl(synchronization());

      rsl.wait(10_s);

      //      for(int i = 0; i < appptra().get_size(); i++)
      //     {
            //       ::application * papp = appptra()(i);
            //       papp->set_locale(scopedstrLocale,context);
            //    }

   }


   void system::appa_set_schema(const ::scoped_string & scopedstrStyle, const ::action_context & context)
   {

      //retry_single_lock rsl(mutex(),::time(100),::time(100));
      single_lock rsl(synchronization());

      rsl.wait(10_s);

      //      for(int i = 0; i < appptra().get_size(); i++)
            //    {
            //       ::application * papp = appptra()(i);
            //       papp->set_schema(scopedstrStyle,context);
            //    }

   }



   bool system::assert_running_global(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrId)
   {

      if (string(scopedstrId).has_character())
      {

         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_id_mutex_name(scopedstrAppName, pszId));
         auto pmutex = node()->open_global_named_mutex(this, m_pnode->get_global_id_mutex_name(scopedstrAppName, scopedstrId));

         if (pmutex == nullptr)
         {

            string strApp = scopedstrAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(scopedstrId) + "\"";

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__APPLE__)

            auto plauncher = __øcreate < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, directory()->module() / strApp, strParameters, nullptr, e_display_normal);

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
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_global_mutex_name(scopedstrAppName));
         auto pmutex = node()->open_global_named_mutex(this, m_pnode->get_global_mutex_name(scopedstrAppName));
         if (pmutex == nullptr)
         {
            string strApp = scopedstrAppName;
            strApp += "app.exe";

#if defined(UNIVERSAL_WINDOWS)

            throw ::exception(todo);

#else

            auto plauncher = __øcreate < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, directory()->module() / strApp, nullptr, nullptr, e_display_normal);

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


   bool system::assert_running_local(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrId)
   {
      string strAppName(scopedstrAppName);
      string strId(scopedstrId);
      if (strId.has_character())
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_id_mutex_name(scopedstrAppName, strId));
         auto pmutex = node()->open_local_named_mutex(this, m_pnode->get_local_id_mutex_name(scopedstrAppName, strId));
         if (pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef UNIVERSAL_WINDOWS

            throw ::exception(todo);

#else

            auto plauncher = __øcreate < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, directory()->module() / strApp, strParameters, nullptr, e_display_normal);

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
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, false, get_local_mutex_name(scopedstrAppName));
         auto pmutex = node()->open_local_named_mutex(this, m_pnode->get_local_mutex_name(scopedstrAppName));
         if (pmutex == nullptr)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef UNIVERSAL_WINDOWS

            throw ::exception(todo);

#else

            auto plauncher = __øcreate < ::apex::shell_launcher >();

            plauncher->setup(nullptr, nullptr, directory()->module() / strApp, strParameters, nullptr, e_display_normal);

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


   //string system::crypto_md5_text(const ::scoped_string & scopedstr)
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

      ::platform::system::on_request(prequest);

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
   ////      file_pointer pfile = file()->get_file(directory()->appdata() / "applibcache.bin",::file::e_open_binary | ::file::e_open_read);
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
   //#if defined(CUBE) || defined(__ANDROID__)
   //      return true;
   //#endif
   //
   //      /*      m_spfilehandler(___new ::apex::filehandler::handler (this));*/
   //
   ////      m_mapAppLibrary.erase_all();
   ////
   ////      string strLibraryId;
   ////
   ////      ::file::listing straTitle(this);
   ////
   ////      ::file::path pathCa2Module = directory()->ca2module();
   ////
   ////      informationf("\n\n::apex::system::find_applications_to_cache\n\n");
   ////
   ////      informationf("ca2 module folder : " + pathCa2Module);
   ////
   ////      informationf("\n\n\n");
   ////
   ////      straTitle.ls_pattern(pathCa2Module, { "*.*" });
   ////
   ////      for(int i = 0; i < straTitle.get_count(); i++)
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
   ////            informationf("library("+as_string(i)+") : " + strLibraryId+"\n\n");
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
   ////         file = psession->file()->get_file(directory()->appdata() / "applibcache.bin",::file::e_open_defer_create_directory | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_write);
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


   //   bool system::map_application_library(const ::scoped_string & scopedstrLibrary)
   //   {
   //
   //      ::acme::library library;
   //
   //      library.initialize_library(this, 0);
   //
   //      if(!strcmp(scopedstrLibrary,"app_core_rdpclient"))
   //      {
   //         INFORMATION("reach");
   //      }
   //
   //      if(!case_insensitive_ansi_compare(scopedstrLibrary, "app_core_hello_multiverse"))
   //      {
   //         INFORMATION("reach app_core_hello_multiverse");
   //      }
   //
   //      if(!case_insensitive_ansi_compare(scopedstrLibrary, "experience_lite"))
   //      {
   //         INFORMATION("reach experience_lite");
   //      }
   //
   //      if(!case_insensitive_ansi_compare(scopedstrLibrary, "app_core_hello_multiverse"))
   //      {
   //         INFORMATION("reach app_core_hello_multiverse");
   //      }
   //
   //      if(!library.open(scopedstrLibrary, true))
   //      {
   //         INFORMATION("::system::map_application_library Failed to open library :" << pszLibrary);
   //         return false;
   //      }
   //
   //      //if(!library.open_library())
   //      //{
   //
   //      //   informationf("::system::map_application_library open_ca2_library(2) Failed :" + string(scopedstrLibrary) + "\n\n");
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
   //      string strLibrary = ::file::path(scopedstrLibrary).title();
   //
   //#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)
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
   //      for(int i = 0; i < stra.get_count(); i++)
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




   //string system::url::encode(const ::scoped_string & scopedstr)
   //{

   //   //throw ::interface_only();

   //   return ::url::encode(str);

   //}

//#ifdef __ANDROID__
//
//   bool system::android_set_user_wallpaper(const ::scoped_string & scopedstrUrl)
//   {
//
//      //operating_system_driver::get().m_strSetUserWallpaper = strUrl;
//
//      return true;
//
//   }
//
//   bool system::android_get_user_wallpaper(string & strUrl)
//   {
//
//      //operating_system_driver::get().m_bGetUserWallpaper = true;
//
//      //for(int i = 0; i < 10; i++)
//      //{
//
//      //   if (!operating_system_driver::get().m_bGetUserWallpaper)
//      //   {
//
//
//      //   }
//
//      //   sleep(50_ms);
//
//      //}
//
//      //strUrl = operating_system_driver::get().m_strGetUserWallpaper;
//
//      return true;
//
//   }
//
//
//#endif

   //::crypto::crypto* system::crypto()
   //{

   //   return m_pcrypto;

   //}


   //::pointer<::account::user_set>system::userset()
   //{

   //   return m_puserset;

   //}


   bool system::defer_accumulate_on_open_file(string_array stra, const ::scoped_string & scopedstrExtra)
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

      ::platform::application * papplication = nullptr;

      auto psession = session();

      if (psession == nullptr)
      {

         papplication = application();

      }
      else
      {

         auto appptra = psession->get_applicationa();

         // appptra.predicate_erase([](auto & papp)
         //    {
         //
         //       return papp->is_system() || papp->is_session();
         //
         //    });
         //
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

   //      pcreate->_001ParseCommandFork("app.exe " + strParam + " " + ::str::has_character(strExtra, " : "));

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


   bool system::on_open_file(::payload payloadFile, const ::scoped_string & scopedstrExtra)
   {

      //

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

      //      papp->request({"app.exe \"" + payloadFile.get_file_path() + "\" " + ::str::has_character(strExtra, " : ")});

      //   }

      //   return true;

      //}

      return false;

   }


   void system::on_open_file(const ::scoped_string & scopedstrFile)
   {

      //file_put_contents("/Users/camilo/debug/on_open_file.txt", pszFile);

      //m_bPostedInitialRequest = true;

      ::pointer<::request>prequest(e_create_new, this);

      prequest->m_payloadFile = scopedstrFile;
      
      prequest->m_ecommand = e_command_file_open;
      
      prequest->m_strAppId = m_papplication->m_strAppId;
      
      prequest->m_bPreferSync = true;
      
      auto psession = session();
      
      psession->request(prequest);

//      auto papplication = application();
//
//      if (!papplication)
//      {
//
//         papplication = application();
//
//      }
//
//      papplication->post_request(prequest);

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
//    void * system::initialize_native_window2(const ::int_rectangle & rectangle)

//    {

//       return nullptr;

//    }
// #endif

//#ifndef __ANDROID__

   void system::on_os_text(enum_os_text etext, const ::scoped_string & scopedstrText)
   {


   }

   //#endif

   //#ifdef UNIVERSAL_WINDOWS
   //
   //
   //
   //   CLASS_DECL_APEX bool window_rectangle(::apex::system_window ^ pwindow, ::double_rectangle * prectangle)
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
   //   CLASS_DECL_APEX bool window_rectangle(::apex::system_window ^ pwindow, ::int_rectangle * prectangle)
   //   {
   //
   //      ::double_rectangle rectangle;
   //
   //      if (!window_rectangle(pwindow, (::double_rectangle*)int_rectangle))
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


   string system::standalone_setting(const ::scoped_string & scopedstr)
   {

      return file_system()->as_string(directory()->standalone() / (scopedstr + ".txt"));

   }


   void system::set_standalone_setting(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSetting)
   {

      file_system()->put_contents(directory()->standalone() / (scopedstr + ".txt"), scopedstrSetting);

   }


   void system::on_extra(const ::scoped_string & scopedstr)
   {

//      auto purl = url();

      ::url::url url(scopedstr);

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

            ::file::path pathScript = directory_system()->tool() / "papaya/script/xcode_set_active_scheme.scpt";

            ::system("osascript \"" + pathScript + "\" \"" + strScheme + "\"");

         }
         else if (strBase == "archive")
         {

            ::system("xcodebuild -scheme \"" + strScheme + "\" archive");

         }

      }
#endif

   }






   //void system::__tracea(::particle * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr)
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

      auto papexapplication = psession->application();

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


   void system::set_user_language(::apex::application * papp, const ::scoped_string & scopedstrLang)
   {

      auto psession = session();

      auto papexapplication = psession->application();

      auto puserlanguagemap = papexapplication->m_puserlanguagemap;

      puserlanguagemap->set_language(papp, scopedstrLang);

      set_standalone_setting("current_language", scopedstrLang);

   }


   void system::process_machine_event_data(machine_event_data * pdata)
   {

      if (pdata->m_fixed.m_bRequestCloseApplication)
      {

         destroy();

      }

   }


void system::open_internet_link_in_browser(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrBrowser, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   {

   
   
   ::string strUrl(scopedstrUrl);
   
   ::string strBrowser(scopedstrBrowser);
   
   ::string strProfile(scopedstrProfile);
   
   ::string strTarget(scopedstrProfile);

   fork([this, strUrl, strBrowser, strProfile, strTarget]()
         {
      
      node()->open_internet_link_in_browser(strUrl, strBrowser, strProfile, strTarget);

         });

      //retu
      //return ::success;

#if 0

      if (strProfile.is_empty() && strTarget.is_empty() && strBrowser.is_empty())
      {

         //::auto pmessagebox = __initialize_new ::message_box(NULL, strUrl, strUrl, e_message_box_ok);

         pmessagebox->sync();

         m_papplication->os().link_open(strUrl);

         return;

      }

      string strBrowserPath;
      string strBrowserDir;
      string strBrowserHelperPath;
      string strBrowserHelperDir;

      string strId;

      ::file::path path;

      string strParam;

      m_papplication->os().get_default_browser(strId, path, strParam);

      if (strProfile.is_empty() || strProfile == "native")
      {

         strProfile = "default";

      }

      string strUser = strProfile;

      string strWeather = strBrowser;

      if (strWeather.is_empty() || !strWeather.case_insensitive_begins("browser_"))
      {

         strWeather = file()->as_string(directory_system()->system() / "browser_weather.txt");

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

      if (strUrl.has_character())
      {

         if (strBrowser == "firefox")
         {

            //strUrl = "https://ca2.network/open_f___?url=" + ::url::encode(strUrl) + "&profile=" + ::url::encode(strProfile) + "&target=" + ::url::encode(strTarget);

         }
         else
         {

            //strUrl = "https://ca2.network/open_tab?url=" + ::url::encode(strUrl) + "&profile=" + ::url::encode(strProfile) + "&target=" + ::url::encode(strTarget);

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

            chromium(strUrl, strBrowser, strId, m_papplication->os().get_app_path("chrome"), strProfile, strParam);

         }
         //else
         {

            //commander(strUrl, strWeather, strUser, path, strParam);

         }

      }
      else
      {

#if defined(UNIVERSAL_WINDOWS)


         string * pstrNew = ___new string(strUrl);

         ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainImpact->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
            ref __allocate< ::winrt::Windows::UI::Core::DispatchedHandler([pstrNew] >()
               {

                  ::winrt::Windows::Foundation::Uri ^ uri = ref ___new ::winrt::Windows::Foundation::Uri (*pstrNew);

                  delete pstrNew;

                  LauncherOptions ^ options = ref ___new LauncherOptions();

                  options->TreatAsUntrusted = false;

                  Launcher::LaunchUriAsync(uri, options);

               }));

         //#elif defined(LINUX)
         //
         //      ::platform::system("xdg-open \"" + strUrl + "\"");
         //
         //      return true;
         //
         //#elif defined(__APPLE__)
         //    openURL(strLink);
         //  return true;
#elif defined(__ANDROID__)

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


         //strOpenUrl = strUrl + ::str::has_character(strOpenUrl, ";");

         //if (strOpenUrl.has_character())
         {

            // psystem->m_pandroidinitdata->m_pszOpenUrl = strdup(strLink);

            ::operating_system_driver::get()->m_pszOpenUrl = strdup(strUrl);

         }


#elif defined(MACOS)

         ::platform::system("open -a /Applications/Safari.app \"" + strUrl + "\"");

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

         if (strUrl.has_character())
         {

            strParam = "\"" + strUrl + "\"";

         }

         ::file::path pathFolder;

         pathFolder = path.folder();

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

            ::platform::system("xdg-open " + strUrl);

         }



#endif

      }

#endif

   }



   void system::chromium(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrBrowser, const ::scoped_string & scopedstrId, ::file::path path, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrParam)
   {

#ifdef UNIVERSAL_WINDOWS

      node()->native_full_web_browser(strUrl);

      return;

#endif

      ::file::path pathFolder;

      pathFolder = path.folder();

      ::file::path pathAppDataDir(directory_system()->ca2roaming());

      ::file::path pathProfile;

      string strBrowserProfile;

      if (scopedstrId == "chrome" || scopedstrId == "commander")
      {

         strBrowserProfile = "Chrome";


      }
      else if (scopedstrId == "vivaldi")
      {

         strBrowserProfile = "Vivaldi";

      }
      else
      {

         strBrowserProfile = "Chromium";

      }

      ::string strParam;

      try
      {

         bool bFound = false;

         pathProfile = pathAppDataDir / strBrowserProfile / "Profile" / scopedstrProfile;

         if (!bFound)
         {

            if (scopedstrUrl.has_character())
            {

               auto iFind = scopedstrParam.find_index("%1");

               if (::found(iFind))
               {

                  strParam = scopedstrParam(0, iFind) + scopedstrUrl + scopedstrParam.substr(iFind + 2) + " ";

               }
               else
               {

                  strParam = "\"" + scopedstrUrl + "\" ";

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

            strParam += " " + file_system()->as_string(directory_system()->localconfig() / "app-core/commander/chrome.txt");

            auto pnode = node();

            pnode->call_async(path, strParam, pathFolder, e_display_default, false);

         }

#elif defined(MACOS)

         string_array sa;

         sa = get_c_args_for_c(strParam);

         sa.add("--user-data-dir=" + pathProfile + "");

         string strChrome = file_system()->as_string(directory_system()->localconfig() / "app-core/commander/chrome.txt");

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

         strParam += " " + file_system()->as_string(directory_system()->localconfig() / "app-core/commander/chrome.txt");

         string strCmd = path + " " + strParam;

         strCmd.find_replace("\'", "\\\'");

         strParam = " -c '" + strCmd + "'";

         informationf(strParam);

         //auto psystem = system();

         auto pnode = node();

         pnode->call_async(shell, strParam, pathFolder, e_display_default, false);

#endif

      }
      catch (...)
      {


      }

   }


   void system::defer_create_firefox_profile(::file::path pathFirefox, const ::scoped_string & scopedstrProfileName, ::file::path pathProfile)
   {

#ifdef UNIVERSAL_WINDOWS


#else

      if (directory()->is(pathProfile))
      {

         return;

      }

      ::file::path pathFolder;

      pathFolder = pathFirefox.folder();

      ::file::path pathProfileDir;

      pathProfileDir = pathProfile.folder();

      directory()->create(pathProfileDir);

      string strParam = "-no-remote -CreateProfile \"" + scopedstrProfileName + " " + pathProfile + "\"";

      ::property_set set;

      auto pnode = node();

      int iExitCode = 0;

      pnode->call_sync(pathFirefox, strParam, pathFolder, e_display_default, 3_minute, set, &iExitCode);

#endif

   }




   void system::firefox(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrBrowser, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrParam)
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

      ::string strParam(scopedstrParam);

      strParam = "-P \"" + scopedstrProfile + "\"";

      if (scopedstrUrl.has_character())
      {

         strParam += " -___new-tab \"" + scopedstrUrl + "\"";

      }

      m_pnode->get_firefox_installation_info(strBrowserPath, strBrowserDir);

      //if (::failed(estatus))
      //{

      //   return estatus;

      //}

      if (!file()->exists(strBrowserPath) || !directory()->is(strBrowserDir))
      {

         throw ::exception(error_not_found);

      }

      strBrowserHelperPath = ::file::path(strBrowserDir) / "uninstall/helper.exe";

      strBrowserHelperDir = ::file::path(strBrowserDir) / "uninstall";

      pathProfile = pathAppDataDir / "ca2/Firefox/Profile" / scopedstrProfile;

      defer_create_firefox_profile(strBrowserPath, scopedstrProfile, pathProfile);

      bool bFound = false;

      if (!bFound)
      {

         auto pnode = node();

         pnode->call_async(strBrowserPath, strParam, strBrowserDir, e_display_normal, false);

         pnode->call_async(strBrowserHelperPath, "/SetAsDefaultAppUser", strBrowserHelperDir, e_display_none, false);

      }

      if (scopedstrBrowser.has_character())
      {

         file()->put_text_utf8(directory_system()->userconfig() / "browser.txt", scopedstrBrowser);

         file()->put_text_utf8(directory_system()->userconfig() / "browser_path.txt", strBrowserPath);

         file()->put_text_utf8(directory_system()->userconfig() / "browser_dir.txt", strBrowserDir);

      }

#endif

      //return ::success;

   }


   //string system::get_local_mutex_name(const ::scoped_string & scopedstrAppName)
   //{

   //   string strMutex;

   //   strMutex.formatf("Local\\%s", pszAppName.c_str());

   //   return strMutex;

   //}

   //
   //string system::get_local_id_mutex_name(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrId)
   //{
   //
   //   string strId(scopedstrId);
   //
   //   string strMutex;
   //
   //   strMutex.formatf("Local\\%s, atom:%s", pszAppName.c_str(), strId.c_str());
   //
   //   return strMutex;

   //}

   //
   //string system::get_global_mutex_name(const ::scoped_string & scopedstrAppName)
   //{
   //
   //   string strMutex;
   //
   //   strMutex.formatf("Global\\%s", pszAppName.c_str());
   //
   //   return strMutex;

   //}

   //
   //string system::get_global_id_mutex_name(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrId)
   //{
   //
   //   string strId(scopedstrId);
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

   //      auto pgroup = __allocate ::task_group(this, epriority);

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

   //      auto ptool = __allocate ::task_tool();

   //      ptool->id() = etool;

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


void system::open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   {
   
   ::string strUrl(scopedstrUrl);
   
   ::string strProfile(scopedstrProfile);
   
   ::string strTarget(scopedstrProfile);

   fork([this, strUrl, strProfile, strTarget]()
         {

         node()->open_internet_link(strUrl, strProfile, strTarget);

         });

      //return ::success;

   }


   // void system::verb() // ambigous inheritance from ::apex::system/::axis::application
   // {
   //
   //    return ::thread::verb();
   //
   // }


   void system::initialize_crypto()
   {

      m_pfactoryCrypto = factory("crypto", "openssl");

      __øconstruct(m_pcrypto, m_pfactoryCrypto);
      
   }


   string system::crypto_md5_text(const ::scoped_string & scopedstr)
   {

      auto pcrypto = crypto();

      return pcrypto->md5(scopedstr);

   }


   //string system::url::encode(const ::scoped_string & scopedstr)
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


   CLASS_DECL_APEX void black_body(float * r, float * g, float * b, unsigned int dwTemp);


   void system::discard_to_factory(::pointer<object>pca)
   {

      __UNREFERENCED_PARAMETER(pca);

   }


   ::pointer<::data::node>system::load_xml(const ::scoped_string & scopedstrXml)
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
   //      return ::platform::system::deferx_initializex_x11();
   //
   //   }


   //   bool system::sn_start_context()
   //   {
   //
   //      return false;
   //
   //   }


#endif


   ::apex::history * system::hist()
   {

      return m_phistory;

   }


   void system::set_history(::apex::history * phistory)
   {

      //auto estatus =
      //__øconstruct(m_phistory, phistory);

      m_phistory = phistory;

      /*   if (!estatus)
         {

            return estatus;

         }

         return estatus;*/

   }


   //::acme::library * system::on_get_library(const ::scoped_string & scopedstrLibrary)
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

::parallelization::threading           *  system::threading()  { return m_pthreading; }


   networking::networking* system::networking()
   {

      if(!m_pnetworking)
      {

         initialize_networking();

      }

      return m_pnetworking;

   }


   void system::on_allocation_error(const ::scoped_string & scopedstr, ::object * pparticle)
   {

      string strMessage;

      ::string str(scopedstr);

      strMessage.formatf("system::on_allocation_error Implement \"%s\" allocation\n", str.c_str());

      dev_log(strMessage);

   }


   //void system::on_request(::create* pcreate)
   //{

   //   //get_platform(pcreate->m_iEdge,pcreate->m_pappbias);

   //   ::apex::system::on_request(pcreate);

   //}


   //bool system::sync_load_url(string& str, const ::scoped_string & scopedstrUrl, ::account::user* puser, ::http::cookies* pcookies)
   bool system::sync_load_url(string & str, const ::scoped_string & scopedstrUrl, ::http::cookies * pcookies)

   {

      string filename = file()->time_square();

      ::property_set set;

      //set["user"] = puser;

      set["cookies"] = pcookies;

      try
      {
         http()->download(scopedstrUrl, filename, set);
      }
      catch(...)
      {

         return false;

      }

      string strLocation;

      strLocation = set["get_headers"]["Location"];

      if (strLocation.has_character())
      {

         ::property_set set;

         //set["user"] = puser;

         set["cookies"] = pcookies;

         file()->erase(filename);

         try
         {
            http()->download(str, strLocation, set);
         }
         catch(...)
         {

            return false;

         }

         return true;

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

   //   for (int i = 0; i < ida.get_count(); i++)
   //   {

   //      m_idmapCreateImpactLibrary.set_at(ida[i], plibrary);

   //   }

   //   return true;

   //}


   //   void system::post_fork_uri(const ::scoped_string & scopedstrUri,application_bias * pappbias)
   //   {
   //
   //      add_fork_uri(scopedstrUri,pappbias);
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


   bool system::window_rectangle(::int_rectangle * prectangle)
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


   void system::hist_hist(const ::scoped_string & scopedstr)
   {

      hist()->hist(scopedstr);

   }


//   void system::system_id_update(long long iUpdate, long long iPayload)
//   {
//
//      call((::enum_id)iUpdate, iPayload);
//
//   }


   //   void system::add_handler(::matter* pmatter, bool bPriority)
   //   {
   //
   //      ::platform::context::add_handler(pmatter, bPriority);
   //
   //   }

   // void system::add_signal_handler(const ::signal_handler & signalhandler, const ::atom & atomSignal)
   // {
   //
   //    ::manager::add_signal_handler(signalhandler, atomSignal);
   //
   // }

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


   // void system::erase_signal_handler(::signal_handler::base * pbase)
   // {
   //
   //    manager::erase_signal_handler(pbase);
   //
   // }


   void system::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      command_handler(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      //if (m_papexnode)
      //{

      //   route_command(pcommand, false);

      //}

   }


   void system::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::thread::handle(ptopic, phandlercontext);
      //      auto psignal = get_signal((::enum_id) iUpdate);
      //
      //      psignal->m_payload = iPayload;
      //
      //      psignal->notify();



   }


   bool system::_handle_uri(const ::scoped_string & scopedstrUri)
   {

      if (application() && application()->_handle_uri(scopedstrUri))
      {

         return true;

      }

      if (!application() || application() != application())
      {

         if (application() && application()->_handle_uri(scopedstrUri))
         {

            return true;

         }

      }

      return false;

   }


   void system::destroy()
   {

      //::main::destroy();

      //::platform::context::destroy();

      m_sessionmap.clear();

      m_pfilewatcher.defer_destroy();

      //m_mapLibrary4.clear();

      //return ::success;

      ::platform::system::destroy();

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

         ::platform::system::process_exit_status(pparticle, estatus);

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


   void system::system_construct(::platform::application * papplication)
   {

      ::platform::system::system_construct(papplication);

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

         node()->defer_innate_ui();

//#elif defined(MACOS)
//
//         node()->defer_innate_ui();
//
//#endif

         __øconstruct(m_pinnateui);

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
   //void apex_application_main(int argc, char* argv[], const ::scoped_string & scopedstrCommandLine);



   void system::application_main(int argc, char * argv[], const ::scoped_string & scopedstrCommandLine)
   {

      //apex_application_main(argc, argv, pszCommandLine);

   }


   //pointer< ::extended::future < ::conversation > > system::_message_box(::particle * pparticle, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox)
   //{

   //   return ::system::_message_box(pparticle, pszText, pszTitle, emessagebox);

   //}

   // https://github.com/umpirsky/tld-list/blob/master/data/en/tld.txt


   ::string system::fetch_public_internet_domain_extension_list_text()
   {

      //auto estatus =
      ///::platform::system::get_public_internet_domain_extension_list(stra);

      //return estatus;

      return {};

   }


   //void system::get_public_internet_domain_extension_list(string_array& stra)
   //{

   ////   //auto estatus =
   ////   ::platform::system::get_public_internet_domain_extension_list(stra);

   //   ///return estatus;

   //}


   void system::system_main()
   {

      ::platform::system::system_main();

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
         pfactoryNetworking->__øconstruct(this, m_pnetworking);


         if (!m_pnetworking)
         {

            //estatus = __construct_new(m_psockets);

            //__øconstruct(m_pnetworking);

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

      send_signal(id_application_dark_mode_change);

      ::platform::system::on_application_dark_mode_change();

   }


   void system::dump_command_line_and_environment_variables_to_file()
   {
   }


   void system::do_operating_ambient_factory()
   {


//#ifdef WINDOWS_DESKTOP
//
//      auto & pfactory = factory("apex", "windows");
//
//      pfactory->merge_to_global_factory();
//
//#endif

      auto strOperatingSystem = ::get_operating_system_name();

      auto & pfactory = factory("apex", strOperatingSystem);

      pfactory->merge_to_global_factory();


   }


   ::string system::component_path(const ::scoped_string & scopedstrComponent)
   {

      ::string strComponent = scopedstrComponent;

      strComponent.make_lower();

      if (strComponent == "fs_raw_folder_protocol")
      {

         return "apex/filesystem/fs/raw_folder";

      }

      return ::platform::system::component_path(scopedstrComponent);

   }



} // namespace apex



