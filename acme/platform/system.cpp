#include "framework.h"
#include "library.h"
#include "node.h"
#include "acme.h"
#include "system_setup.h"
#include "system.h"
#include "system_factory.h"
//#include "sequencer.h"
#include "application.h"
#include "acme/nano/nano.h"
#include "acme/nano/http/http.h"
#include "session.h"
#include "simple_log.h"
#include "hyperlink.h"
#include "acme/compress/compress.h"
#include "acme/compress/uncompress.h"
#include "acme/constant/id.h"
//#include "acme/constant/idpool.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/dir_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/file/transfer.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/translator.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/request.h"
#include "acme/handler/topic.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/debug.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/prototype/prototype/prototype.h"
#include "acme/prototype/prototype/url.h"
#include "acme/regular_expression/context.h"
//#include "acme/prototype/prototype/payload.h"
//#include "acme/prototype/string/hex.h"
#include "acme/user/micro/user.h"
#include "acme/nano/http/http.h"
#include "acme/nano/speech/speech.h"
#include "acme/windowing/windowing.h"
//#include "acme/user/user/conversation.h"


//extern "C" void nano_dynamic_library_factory(::factory::factory * pfactory);


//#elif defined(UNIVERSAL_WINDOWS)
//
//extern "C" void nano_user_universal_windows_factory(::factory::factory * pfactory);
//
//#endif
//
//#elif defined(MACOS)
//
//extern "C" void nano_user_macos_factory(::factory::factory* pfactory);
//
//#endif


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);
CLASS_DECL_ACME void trace_category_static_init(::acme::system * psystem);
CLASS_DECL_ACME void trace_category_static_term();


::file::path _system_config_folder_path()
{

   ::file::path pathSystemConfigFolder;

#ifdef WINDOWS

   pathSystemConfigFolder = getenv("AppData");

#else // WINDOWS

   pathSystemConfigFolder = getenv("HOME");

#ifdef MACOS

   pathSystemConfigFolder /= "Application Support";

#else // MACOS

   pathSystemConfigFolder /= ".config";

#endif // !MACOS

#endif // !WINDOWS

   return pathSystemConfigFolder;

}

::file::path _ca2_config_system_folder_path()
{

   auto pathSystemConfigFolder = _system_config_folder_path();

   auto pathCa2ConfigSystemFolder = pathSystemConfigFolder / "ca2/config/system";

   return pathCa2ConfigSystemFolder;

}


//static ::acme::system * g_psystem = nullptr;


//extern const char * g_pszTopLevelDomainList[];


enum_dialog_result message_box_for_console(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrTitle, const ::enum_message_box& emessagebox);



#include "acme/_operating_system.h"


void initialize_nano_http(::factory::factory* pfactory);


namespace acme
{


   system::system()
   {

      m_pacmesystem = this;
      m_papexsystem = nullptr;
      m_paquasystem = nullptr;
      m_paurasystem = nullptr;
      m_paxissystem = nullptr;
      m_pbasesystem = nullptr;
      m_pbredsystem = nullptr;
      m_pcoresystem = nullptr;

#ifndef WINDOWS

      ::unsetenv("LD_LIBRARY_PATH");

#endif

      m_etracelevelMinimum = e_trace_level_undefined;

#ifdef DEBUG
      ::atom atom;
      int iAtom1 = sizeof(atom);
      int iAtomType = sizeof(atom.m_etype);
      int iDomainId = sizeof(atom.m_domainid);
      ::payload payload;
      auto pType = &payload.m_etype;
      auto pAll = &payload.m_payloadall;
      int iType = sizeof(payload.m_etype);
      int iAll = sizeof(payload.m_payloadall);
      int iThis = sizeof(payload);
      int iAddUp = 0;
#if REFERENCING_DEBUGGING
      iAddUp += sizeof(payload.m_preferer);
#endif
      int iComputed = (int) (((::u8*)pAll - (::u8*)pType) + iAll + iAddUp);
      int iColor = sizeof(payload.m_color);
      int iStr = sizeof(payload.m_str);
      int iHls = sizeof(payload.m_hls);
      int iTime = sizeof(payload.m_time);
      int iAtom = sizeof(payload.m_atom);
      int iFileTime = sizeof(payload.m_filetime);
      int iEarthTime = sizeof(payload.m_earthtime);
      if (iThis != iComputed)
      {

         throw 0;

      }
#endif


      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;
      m_bGraphicsAndWindowingSystemInitialized = false;

   }


   system::~system()
   {

      print_line("acme::system::~system() (start)");

      trace_category_static_term();

      m_pacmesystem = nullptr;
      m_papexsystem = nullptr;
      m_paquasystem = nullptr;
      m_paurasystem = nullptr;
      m_paxissystem = nullptr;
      m_pbasesystem = nullptr;
      m_pbredsystem = nullptr;
      m_pcoresystem = nullptr;

      print_line("acme::system::~system() (end)");

      //::acme::get()->m_pmanualreseteventReadyToExit->SetEvent();

   }


   void system::on_set_platform()
   {

      ::acme::context::on_set_platform();

   }


   enum_trace_level system::get_trace_level()
   {

      if(m_etracelevelMinimum != e_trace_level_undefined)
      {

         return m_etracelevelMinimum;

      }

      enum_trace_level etracelevel = e_trace_level_none;

      // if(is_debugger_attached())
      // {

      //    etracelevel = e_trace_level_information;

      // }
      // else
      // {

      //    etracelevel = e_trace_level_warning;

      // }

#ifdef _DEBUG

      etracelevel = e_trace_level_information;

#else

      auto pathCa2ConfigSystemFolder = _ca2_config_system_folder_path();

      auto pathTraceLevelInformation = pathCa2ConfigSystemFolder / "trace_level_information.txt";

      if (platform()->has_argument("--log"))
      {

         informationf("selecting informational trace\n");

         etracelevel = e_trace_level_information;

      }
      else if (file_exists(pathTraceLevelInformation))
      {

         etracelevel = e_trace_level_information;

      }
      else
      {

         etracelevel = e_trace_level_warning;

      }

#endif

      //if (etracelevel > e_trace_level_debug)
      //{

      auto strTraceLevel = m_pplatform->get_argument_begins_eat("--trace-level=");

      if (strTraceLevel == "debug")
      {

         etracelevel = e_trace_level_debug;

      }
      else if (strTraceLevel == "information")
      {

         etracelevel = e_trace_level_information;

      }
      else if (strTraceLevel == "warning")
      {

         etracelevel = e_trace_level_warning;

      }

      //         for (int i = 0; i < m_pplatform->get_argument_count1(); i++)
      //         {
      //
      //            string strArg = m_pplatform->get_argument1(i);
      //
      //            if (strArg == "verbose")
      //            {
      //
      //               etracelevel = e_trace_level_information;
      //
      //               break;
      //
      //            }
      //
      //         }

      //      }

      m_etracelevelMinimum = etracelevel;

      return m_etracelevelMinimum;

   }


   void system::initialize_matter()
   {

      if (application()->m_bResource)
      {

         bool bMatterFromHttpCache = false;

         bool bMatterFromResource = false;

         auto pfile = file()->create_resource_file("app/_matter/main/_std/_std/Thomas Borregaard Sørensen.dedicatory");

         if (pfile)
         {

            information() << "found Thomas Borregaard Sørensen.dedicatory";

            bMatterFromResource = true;

         }
         else
         {

            warning() << "Thomas Borregaard Sørensen.dedicatory not found";

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

               ::file::path pathSide = m_pcontext->side_get_matter_path("app/_matter/main");

               ::file::path pathLocal = local_get_matter_path("app/_matter/main");

               bool bFileSystemMatter = m_pacmedirectory->is(pathSide) || m_pacmedirectory->is(pathLocal);

               bMatterFromHttpCache = !bFileSystemMatter;

            }
            else
            {

               bMatterFromHttpCache = m_iMatterFromHttpCache != 0;

            }

            m_pdirsystem->m_bMatterFromHttpCache = bMatterFromHttpCache;

            m_pdirsystem->m_bMatterFromResource = false;

         }

      }

   }



   void system::on_initialize_particle()
   {

      ::acme::context::on_initialize_particle();

      //::output_debug_string("Going to create simple log\n");

      //m_plogger = __create_new < ::simple_log >();

      __construct(m_plogger);

      //::output_debug_string("output_debug_string : simple log created\n");

      //information() << "information() << output_debug_string : simple log created";

#ifdef PARALLELIZATION_PTHREAD

#if defined(__APPLE__)

      m_bJoinable = true;

#endif

#endif

      //#ifdef WINDOWS_DESKTOP
      //
      //      //{
      //
      //      //   auto papp = ::app_factory::new_app();
      //
      //      //papplication->m_argc = __argc;
      //
      //      //papplication->m_argv = __argv;
      //
      //      //papplication->m_wargv = __wargv;
      //
      //      //papplication->m_envp = *__p__environ();
      //
      //      //papplication->m_wenvp = *__p__wenviron();
      //
      //      //papplication->m_hinstanceThis = hinstanceThis;
      //
      //      //papplication->m_hinstancePrev = hinstancePrev;
      //
      //      //papplication->m_nCmdShow = nCmdShow;
      //
      //      //papplication->is_console() = false;
      //
      //      //int iExitCode = papplication->main_loop();
      //
      //      //return iExitCode;
      //
      //#elif !defined(UNIVERSAL_WINDOWS)
      //
      //      //papplication->set_args(g_argc, g_argv, g_envp);
      //
      //#endif
      //
      //m_ewindowing = e_windowing_none;

      //m_plogger->m_etracelevelMinimum = e_trace_level_warning;

      //m_strAppId = papplication->m_strAppId;



      //information() << "initialize_system trace_category_static_init";

      trace_category_static_init(this);


      //____creatable_from_base(simple_log, logger);

      //____creatable(task);

      m_bPostedInitialRequest = false;

      //m_bOnInitializeWindowObject = false;

      //m_pcleanuptask = __allocate ::parallelization::cleanup_task();

      //m_pcleanuptask->begin();
      //factory()->add_factory_item<::acme::idpool>();

      //m_pacme = nullptr;
      //m_pacmedirectory = nullptr;
      //m_pacmepath = nullptr;

      __defer_construct_new(m_pmathematics);

      __defer_construct_new(m_pprototype);

      //::plane_system::on_initialize_particle();

   }


   void system::initialize_system()
   {

      //information() << "initialize_system factory()->initialize";

      factory()->initialize(this);

      //      //#ifdef LINUX
      //      //
      //      //      m_elinuxdistribution = e_linux_distribution_unknown;
      //      //
      //      //#endif
      //
      //      //m_edesktop = ::user::e_desktop_none;
      //
      //      information() << "initialize_system os_construct";
      //
      //      os_construct();
      //
      //      //system() = this;
      //
      //      //      if (g_psystem == nullptr)
      //      //      {
      //      //
      //      //         g_psystem = this;
      //      //
      //      //      }


      //information() << "initialize_system create nano";

      //__construct(m_pnano);

      //m_psystemimpl = ___new system_impl();

      //set_os_data(LAYERED_ACME, this);

      //information() << "acme initialize_system end";

   }


   void system::on_pre_run_task()
   {

      /*auto estatus =*/ on_start_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::on_branch_system_from_main_thread_startup()
   {

      m_itask = 0;

      m_htask = nullptr;

      branch_synchronously();

      // To pair freebsd.h/main platform_create_system ___new system
      // This should be safe here in this node_gtk::node
      // because just above system() has begin_synch()
      // so the running thread is holding references to the system() thread.
      release();

   }


   void system::main()
   {

      /*auto estatus = */

      //if (!estatus)
      //{

      //   return estatus;

      //}

      /*estatus =*/
      if (platform()->is_console())
      {

         process_init();

         run_posted_procedures();

         application()->main();

      }
      else
      {

         task_osinit();

         __task_init();

//         m_peventInitialization->SetEvent();

         while(task_get_run())
         {

            run_posted_procedures();

            preempt(100_ms);

         }

         //acme_windowing()->windowing_system_application_main_loop();


      }



      //run();




      //if (!estatus)
      //{

      //   return estatus;

      //}

      end();

      //return estatus;

   }


   //   ::acme::node * system::node()
   //   {
   //
   //      return m_pnode;
   //
   //   }


   class ::mathematics::mathematics* system::mathematics()
   {

      return m_pmathematics;

   }


   class ::image::imaging* system::imaging()
   {

      throw ::interface_only("imaging requires aura layer or upper layer");

      return nullptr;

   }



   ::acme::system_factory* system::system_factory()
   {

      if (!m_psystemfactory)
      {

         __construct_new(m_psystemfactory);

      }

      return m_psystemfactory;

   }


   ::xml::xml* system::_xml()
   {

      return nullptr;

   }


   void system::create_os_node()
   {

      if (m_pnode)
      {

         return;

      }

      //information() <<"::acme::system create_os_node";

      auto& pfactory = node_factory();

      if (!pfactory)
      {

         fatal() << "node_factory has failed";

         throw ::exception(error_resource);

      }

#if !defined(WINDOWS)

      __construct(m_pexceptiontranslator);

      m_pexceptiontranslator->attach();

#endif

      //information() << "create_os_node going to create node";

      __construct(m_pnode);

      m_pacmenode = m_pnode;

      if (m_pacmesession)
      {

         m_pacmesession->m_pacmenode = m_pnode;

      }

      if (m_pacmeapplication)
      {

         m_pacmeapplication->m_pacmenode = m_pnode;

      }

      m_pmutexHttpDownload = node()->create_mutex();


      //if(!estatus)
      //{

      //   fatal() <<"Failed to construct node " << estatus;

      //   return estatus;

      //}

      //estatus = m_pnode->initialize_matter(this);
      //m_pnode->initialize_matter(this);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //::acme::g_pengine;

      //return estatus;

   }


   void system::speak(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrLang, enum_gender egender)
   {

      nano()->speech()->speak(scopedstr, scopedstrLang, egender);

   }


   ::pointer<::factory::factory>& system::node_factory()
   {

      auto& pfactory = factory("acme", OPERATING_SYSTEM_NAME);

      if (!pfactory)
      {

         return pfactory;

      }

      pfactory->merge_to_global_factory();

      return pfactory;

   }


   void system::process_init()
   {

      application()->initialize_application_flags();

      factory()->add_factory_item<::request>();



#if REFERENCING_DEBUGGING

      ::refdbg_top_track toptrack(this);

#endif

      __construct_new(m_purlcontext);

      //::acme::idpool::init(this);

//      /// Create/Replace logger

      __construct_new(m_pdatetime);



      m_pnode->m_htaskSystem = m_htask;

      //auto estatus = __defer_construct_new(m_pfactorysquare);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      // auto estatus = ([a-z0-9_]+)_factory("acme", OPERATING_SYSTEM_NAME);

      // if (!estatus)
      // {

      //    return estatus;

      // }

      //estatus = __construct(m_pacmenode);

      //if (!m_pacmenode)
      //{

      //   return error_no_memory;

      //}

      //auto estatus = __raw_construct(m_pacmedirectory);

      __raw_construct(m_pacmedirectory);

      /*if (!estatus)
       {

       return estatus;

       }*/

       //      m_pacmedirectory = pacmedirectory;

       //    m_pacmedirectory->increment_reference_count();

       //estatus = __raw_construct(m_pacmefile);

      __raw_construct(m_pacmefile);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = __raw_construct(m_pacmepath);

      __raw_construct(m_pacmepath);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pacmedirectory->m_pacmefile = m_pacmefile;
      m_pacmedirectory->m_pacmepath = m_pacmepath;
      m_pacmefile->m_pacmedirectory = m_pacmedirectory;
      m_pacmefile->m_pacmepath = m_pacmepath;
      m_pacmepath->m_pacmedirectory = m_pacmedirectory;
      m_pacmepath->m_pacmefile = m_pacmefile;

      //estatus = m_pacmefile->initialize(this);

      m_pacmefile->initialize(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = m_pacmepath->initialize(this);

      m_pacmepath->initialize(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = m_pacmedirectory->initialize(this);

      m_pacmedirectory->initialize(this);


      //throw ::exception(error_failed);



      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

      m_timeStart.Now();

      m_timeAfterApplicationFirstRequest = m_timeStart;

      //if (acmefile()->exists(::file::path(APP_CORE_BASE_DIR) / "wait_on_beg.txt"))
      //{

      //   sleep(10_s);

      //}

      //if (acmefile()->exists(::file::path(APP_CORE_BASE_DIR) / "beg_debug_box.txt"))
      //{

      //   //debug_box("zzzAPPzzz app", "zzzAPPzzz app", e_message_box_icon_information);

      //}
      //estatus =

      __construct(m_pfilesystem);

      //if(!estatus)
      //{

      //   ERROR("failed to initialize file-system");

      //   return estatus;

      //}

      //estatus =

      //::allocator::add_referer(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);

      __construct(m_pdirsystem);

      //if (!estatus)
      //{

      //   ERROR("failed to initialize dir-system");

      //   return false;

      //}

      ///INFORMATION("apex::session::process_init .3");

      //estatus =
      m_pfilesystem->init_system();

      //if (!estatus)
      //{

      //   m_estatus = estatus;

      //   return estatus;

      //}

      //estatus =
      m_pdirsystem->init_system();

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

#if !defined(APPLE_IOS)

      auto pid = node()->current_process_identifier();

      string strPid = ::as_string(pid);

      //auto psystem = system();

      auto pdatetime = datetime();

      string strLogTime = pdatetime->date_time_text_for_file_with_no_spaces();

      strLogTime.replace_with("/", "-");

      strLogTime.replace_with("/", "_");

      {

         string strExecutable = platform()->get_executable();

         string_array straArguments;

         for (int i = 0; i < platform()->get_argument_count1(); i++)
         {

            string strArgument = platform()->get_argument1(i);

            straArguments.add(strArgument);

         }

         string strCmd = strExecutable + " " + straArguments.implode("\n");

         string strAppId = application()->m_strAppId;

         string strCmdLineDumpFileName = strAppId / (strLogTime + "-pid" + strPid + "-command_line.txt");

         ::file::path pathCmdLineDumpFile = acmedirectory()->home() / "application" / strCmdLineDumpFileName;

         acmefile()->put_contents(pathCmdLineDumpFile, strCmd);

      }

      {

         string_array straEnv;
#ifdef WINDOWS_DESKTOP
         if (platform()->m_wenvp)
         {

            int iIndex = 0;

            for (auto wenv = platform()->m_wenvp; *wenv != 0; wenv++, iIndex++)
            {

               auto thisEnv = *wenv;

               int iLen = (int) wcslen(thisEnv);

               /*if (iLen >= 42)
               {
                  output_debug_string("aaa");
               }
               else*/ if (!wcsncmp(thisEnv, L"Path=", 5))
               {

                  output_debug_string("aaa");

               }
               else if (!wcsncmp(thisEnv, L"VsPer", 5))
               {

                  output_debug_string("aaa");

               }

               straEnv.add(thisEnv);

            }

         }
         else
#endif
            if (platform()->m_envp)
            {

               for (auto env = platform()->m_envp; *env != 0; env++)
               {

                  auto thisEnv = *env;

                  straEnv.add(thisEnv);

               }

            }

         string strEnv = straEnv.implode("\n");

         string strAppId = application()->m_strAppId;

         string strEnvDumpFileName = strAppId / strLogTime + "-pid" + strPid + "-environment_variables.txt";

         ::file::path pathEnvDumpFile = acmedirectory()->home() / "application" / strEnvDumpFileName;

         acmefile()->put_contents(pathEnvDumpFile, strEnv);

      }

#endif

#if !defined(APPLE_IOS)

      report_system_instance();

#endif





   }


   //   void system::start()
   //   {
   //
   ////      auto estatus = create_os_node();
   ////
   ////      if (!estatus)
   ////      {
   ////
   ////         //return estatus;
   ////
   ////         estatus = ::success_none;
   ////
   ////      }
   //
   //      estatus = os_application_system_run();
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


   void system::TermSystem()
   {

      auto pacmewindowing = m_pacmewindowing;

      if (pacmewindowing)
      {

         ::acme::get()->m_pmanualreseteventReadyToExit = __raw_new manual_reset_event();
         ::acme::get()->m_pmanualreseteventMainLoopEnd = __raw_new manual_reset_event();

         if (!m_procedureTaskEnded)
         {

            m_procedureTaskEnded = [pacmewindowing]()
               {

                  ::acme::get()->m_pmanualreseteventReadyToExit->set_event();

               };

            m_pacmewindowing->set_finish();

            ::acme::get()->m_pmanualreseteventMainLoopEnd->wait(2.5_min);

            delete ::acme::get()->m_pmanualreseteventMainLoopEnd;

            ::acme::get()->m_pmanualreseteventMainLoopEnd = nullptr;

         }

      }

      m_pacmewindowing.release();

      m_pmapRegularExpressionContext.release();

      m_pfactoryFolder.release();

      m_pdirsystem.release();
      m_pfilesystem.release();
      m_pacmefile.release();
      m_pacmedirectory.release();
      m_pacmepath.release();

      m_purlcontext.release();

      m_pdatetime.release();

      //::acme::idpool::term();

      //m_pnode->user_post_quit();

      m_pnode.release();

      //try
      //{

      //   ::acme::acme::g_pacme->factory_close();

      //}
      //catch (...)
      //{

      //}

      //m_mapFactory.clear();

      //m_mapComponentFactory.clear();




      destroy();




      //m_mapLibrary4.clear();

   }


   void system::erase_from_any_hook(::matter* pmatter)
   {


   }


   string system::os_get_user_theme()
   {

      return m_strOsUserTheme;

   }


   ::u32 system::crc32(::u32 uCrc, const ::block& block)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!m_pcompressZlibCrc32)
      {

         m_pcompressZlibCrc32 = new_zlib_compress();

      }

      auto pcompress = m_pcompressZlibCrc32;

      if (!pcompress)
      {

         throw "Couldn't create compress_zlib::compress instance.";

      }

      return pcompress->crc32(uCrc, block);

   }


   void system::open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      throw ::interface_only();

   }


   void system::open_link(string strUrl, string strProfile, string strTarget)
   {

      open_profile_link(strUrl, strProfile, strTarget);

   }


   void system::open_url(string strUrl, string strProfile, string strTarget)
   {

      throw ::exception(::error_interface_only);

   }


   //void system::__tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) const
   //{

   //   if (!m_ptracelog)
   //   {

   //      ::information(psz);

   //      return;

   //   }

   //   m_ptracelog->__tracea(elevel, pszFunction, pszFile, iLine, psz);

   //}


   //   void system::main_user_async(const ::procedure & procedure, ::enum_priority epriority)
   //   {
   //
   //      throw ::interface_only();
   //
   //   }
   //
   //
   //   void system::main_user_sync(const ::procedure & procedure, const class time & time, enum_priority epriority)
   //   {
   //
   //      auto proutine = ___sync_routine(routine);
   //
   //      main_user_async(proutine, epriority);
   //
   //      auto waitresult = proutine->wait(time);
   //
   //      if (!waitresult.succeeded())
   //      {
   //
   //         return ::error_timeout;
   //
   //      }
   //
   //      return proutine->m_estatus;
   //
   //   }




   void system::init_task()
   {

      task::init_task();

      call_init_system();

   }


   void system::term_task()
   {

      //term_system();

      task::term_task();

   }

   string system::__get_text(const ::string& str)
   {

      return str;

   }


   //pointer< ::extended::sequence < ::conversation > > system::message_box(::user::interaction * puserinteraction, const ::string & pszText, const ::string & pszTitle, const ::e_message_box & emessagebox)
   //{

   //   auto psequence = __allocate ::sequence < ::conversation > ();

   //   psequence->set_status(error_interface_only);

   //   //return presult;

   //   //auto pprocess = __allocate status < enum_dialog_result > ();

   //   //pprocess->set_result(message_box_for_console(pszText, pszTitle, emessagebox));

   //   return psequence;

   //}


   //void system::on_initialize_window_object()
   //{

   //   if (m_bOnInitializeWindowObject)
   //   {

   //      return ::success_none;

   //   }

   //   m_bOnInitializeWindowObject = true;

   //   auto estatus = _on_initialize_window_object();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   //CLASS_DECL_ACME class system * system()
   //{
   //
   //   return ::g_psystem;
   //
   //}
   //


   task_group* system::task_group(enum enum_priority)
   {

      return nullptr;

   }


   task_tool* system::task_tool(::enum_task_tool etool)
   {

      return nullptr;

   }


   void system::inline_init()
   {

      init_system();

   }


   void system::call_init_system()
   {

      try
      {

         init_system();

      }
      catch (::exception& exception)
      {

         //auto pmessagebox = __initialize_new ::message_box(exception.m_strMessage, m_strAppId, e_message_box_ok, exception.m_strDetails);

//pmessagebox->sync();

         string strMoreDetails;

         strMoreDetails = "caught at system::call_init_system";

         m_pnode->report_exception_to_user(this, exception, strMoreDetails);

         m_estatus = exception.m_estatus;

      }

   }


   void system::init_system()
   {

      set_current_handles();

      //::acme::application * pappStartup = ::acme::application::g_p;

      //if (::is_null(pappStartup))
      //{

      //   pappStartup = new_app(m_strAppId);

      //}

      //if (!pappStartup)
      //{

      //   return -1;

      //}

      //application() = pappStartup;

      m_pacmeapplication->initialize(this);

      m_pacmeapplication->get_property_set().merge(get_property_set());

      //*((::APPLICATION_FLAGS *)this) = *application();

      process_init();

      init1();

      init2();

      //   auto & pfactory = node_factory();
      //
      //   if (!pfactory)
      //   {
      //
      //      //fatal() <<"node_factory has failed (status=" << (const void &) pfactory << ")";
      //
      //      throw ::exception(error_resource);
      //
      //   }
      //
      //   //auto estatus = create_os_node();
      //   create_os_node();

      //if (!estatus)
      //{

      //   fatal() <<"create_os_node has failed " << estatus;

      //   return estatus;

      //}

      //estatus = process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return success;

   }


   ::nano::nano* system::nano()
   {

      if (!m_pnano)
      {

         //initialize_nano_window(factory());

         __construct_new(m_pnano);

      }

      return m_pnano;

   }


   void system::defer_innate_ui()
   {


   }


   ::innate_ui::innate_ui * system::innate_ui()
   {

      defer_innate_ui();

      return m_pinnateui;

   }


   void system::defer_audio()
   {

      throw ::interface_only();

   }
   //::nano::nano * system::nano()
   //{
   //
   //   if (!m_pnanohttp)
   //   {
   //
   //      initialize_nano_http(factory());
   //
   //      __construct(m_pnanohttp);
   //
   //   }
   //
   //   return m_pnanohttp;
   //
   //}


   //   ::nano::http * system::nano_http()
   //   {
   //
   //      if (!m_pnanohttp)
   //      {
   //
   //         initialize_nano_http(factory());
   //
   //         __construct(m_pnanohttp);
   //
   //      }
   //
   //      return m_pnanohttp;
   //
   //   }
   //
   //
   bool system::has_audio()
   {

      return false;

   }


   void system::init1()
   {

      initialize_context_1();

   }


   void system::init2()
   {


      initialize_matter();

      if (application()->m_bSession)
      {

         //return ::success;
         create_session();

      }

      //::string strRoot = "ca2.network";

      //::file::path pathGooglePayload = "C:\\sensitive\\sensitive\\api\\google\\account\\" + strRoot + ".network_payload";

      //auto payloadGoogle = file()->as_network_payload(pathGooglePayload);

      //::string strClientId = payloadGoogle["web"]["client_id"];

      //auto straRedirectUri = payloadGoogle["web"]["redirect_uris"].as_string_array();

      //auto iFind = straRedirectUri.find_first_begins("https://" + strRoot + "/");

      //if (iFind < 0)
      //{

      //   throw ::exception(error_failed);

      //}

      if (application()->m_bSession)
      {

         session()->branch_synchronously();

      }


   }


   void system::set_current_handles()
   {


   }



   //::pointer<::acme::library> system::library(const ::string& strComponent, const ::string& strImplementationParam)
   //{

   //   string strImplementation(strImplementationParam);

   //   strImplementation.case_insensitive_begins_eat(strComponent + "_");

   //   string strLibrary;

   //   strLibrary = strComponent + "_" + strImplementation;

   //   auto& plibrary = library(strLibrary);

   //   if (!plibrary)
   //   {

   //      return plibrary;

   //   }

   //   return plibrary;

   //}






   //::pointer<::acme::library>& system::library(const ::string & strComponent, const ::string & strImplementation)
   //{

   //   // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"

   //   if (strComponent.is_empty() || strImplementation.is_empty())
   //   {

   //      throw error_bad_argument;

   //   }

   //   auto psystem = system();

   //   _synchronous_lock synchronouslock(&psystem->m_pmutexLibrary2);

   //   auto & plibrary = psystem->m_mapLibrarySquare[strComponent][strImplementation];

   //   if (plibrary.is_initialized())
   //   {

   //      return plibrary;

   //   }

   //   string strLibrary;

   //   strLibrary = strComponent + "_" + strImplementation;

   //   _load_library(plibrary, strLibrary);

   //   return plibrary;

   //}


   //::pointer<::acme::library>system::open_containerized_component_library(const ::string & pszComponent, const ::string & pszImplementation)
   //{

   //   // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"

   //   string strComponent(pszComponent);

   //   string strImplementation(pszImplementation);

   //   strComponent.trim();

   //   strImplementation.trim();

   //   string strLibrary;

   //   if (strImplementation.is_empty())
   //   {

   //      return nullptr;

   //   }

   //   strImplementation.case_insensitive_begins_eat(strComponent + "_");

   //   strImplementation.case_insensitive_begins_eat(strComponent);

   //   auto psystem = system();

   //   _synchronous_lock synchronouslock(&psystem->m_pmutexContainerizedLibrary);

   //   ::pointer<::acme::library>plibrary = psystem->m_mapContainerizedLibrary[strComponent][strImplementation];

   //   if (plibrary && plibrary->is_opened())
   //   {

   //      return plibrary;

   //   }

   //   strLibrary = strComponent + "_" + strImplementation;

   //#ifdef CUBE

   //   auto plibraryfactory = ::system_setup::get_first(::system_setup::flag_library, strLibrary);

   //   if (!plibraryfactory)
   //   {

   //      return nullptr;

   //   }

   //   plibrary = plibraryfactory->create_library();

   //#else

   //   if (!plibrary)
   //   {

   //      plibrary = __allocate ::acme::library();

   //      plibrary->initialize_matter(this);

   //   }

   //   if (!plibrary->open(strLibrary))
   //   {

   //      return nullptr;

   //   }

   //   if (!plibrary->is_opened())
   //   {

   //      return nullptr;

   //   }

   //#endif

   //   return plibrary;

   //}


   class ::time system::get_update_poll_time(const ::atom& atom)
   {

      return 0_s;

   }


   ::acme::library* system::on_get_library(const ::string& pszLibrary)
   {

      return nullptr;

   }


   //   ::extended::transport < ::factory::factory > system::([a-z0-9_]+)_factory(const ::string & pszComponent, const ::string & pszImplementation)
   //   {
   //
   //      auto& pfactory = m_mapFactoryMap[strComponent][strImplementation];
   //
   //      string strComponent(pszComponent);
   //
   //      string strImplementation(pszImplementation);
   //
   //      strImplementation.case_insensitive_begins_eat(strComponent + "_");
   //
   //      strImplementation.case_insensitive_begins_eat(strComponent);
   //
   //   //#ifdef CUBE
   //
   //      //auto pfnFactoryExchange = m_mapFactoryExchange[strComponent][strImplementation];
   //
   //      //if (::is_null(pfnFactoryExchange))
   //      //{
   //
   //      //   return ::error_failed;
   //
   //      //}
   //
   //#ifdef CUBE
   //
   //      _synchronous_lock synchronouslock(m_pmutexContainerizedLibrary);
   //
   //      auto & plibrary = m_mapContainerizedLibrary[strComponent][strImplementation];
   //
   //      if (plibrary && plibrary->is_opened())
   //      {
   //
   //         return plibrary;
   //
   //      }
   //
   //      string strLibrary = strComponent + "_" + strImplementation;
   //
   //      auto pfnFactoryExchange = ::system_setup::get_factory_item_exchange(strLibrary);
   //
   //      //if (::is_null(pfnFactoryExchange))
   //      if (::is_null(pfnFactoryExchange))
   //      {
   //
   //         return ::error_failed;
   //
   //      }
   //
   //      plibrary = __allocate ::acme::library();
   //
   //      plibrary->initialize_matter(this);
   //
   //      __construct_new(plibrary->m_pfactory);
   //
   //      plibrary->m_pfactory->initialize_matter(this);
   //
   //      pfnFactoryExchange(plibrary->m_pfactory);
   //
   //      return plibrary;
   //
   //   #else
   //
   //      auto plibrary = open_containerized_component_library(pszComponent, pszImplementation);
   //
   //      if (!plibrary)
   //      {
   //
   //         return ::error_failed;
   //
   //      }
   //
   //      string strFunctionName = strComponent + "_" + strImplementation + "_factory";
   //
   //      PFN_factory ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >(strFunctionName);
   //
   //      if (([a-z0-9_]+)_factory == nullptr)
   //      {
   //
   //         ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >(strComponent + "_factory");
   //
   //         if (([a-z0-9_]+)_factory == nullptr)
   //         {
   //
   //            ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >("factory_exchange");
   //
   //            if (([a-z0-9_]+)_factory == nullptr)
   //            {
   //
   //               return ::error_failed;
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      __construct_new(pfactory);
   //
   //      plibrary->m_pfactory->initialize_matter(this);
   //
   //      ([a-z0-9_]+)_factory(plibrary->m_pfactory);
   //
   //      return plibrary;
   //
   //#endif
   //
   //   }


   void system::check_exit()
   {


   }


   ::regular_expression_pointer system::create_regular_expression(const ::string& pszStyle, const string& str)
   {

      auto pcontext = get_regular_expression_context(pszStyle);

      if (!pcontext)
      {

         return nullptr;

      }

      auto pregularexpression = pcontext->compile(str);

      if (!pregularexpression)
      {

         return nullptr;

      }

      return pregularexpression;

   }


   ::pointer<::regular_expression::context>system::get_regular_expression_context(const ::string& pszStyle)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      __defer_construct_new(m_pmapRegularExpressionContext);

      auto& pcontext = (*m_pmapRegularExpressionContext)[pszStyle];

      if (!pcontext)
      {

         auto& pfactory = factory("regular_expression", pszStyle);

         if (!pfactory)
         {

            throw ::exception(error_resource);

         }

         pfactory->__construct(this, pcontext);

      }

      return pcontext;

   }


   ::regular_expression_pointer system::compile_pcre(const string& str)
   {

      return create_regular_expression("pcre2", str);

   }


   ::pointer<::regular_expression::context>system::get_pcre_context()
   {

      return get_regular_expression_context("pcre2");

   }


   //   int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)
   //   {
   //
   //      throw_todo();
   //
   //      return -1;
   //
   //   }


   ::string system::fetch_public_internet_domain_extension_list_text()
   {

      throw interface_only();

      return {};

   }


   void system::get_public_internet_domain_extension_list(string_array& stra)
   {

      //::file::path pathPublicDomainExtensionList = "https://ca2.network/public_internet_domain_extension_list.txt";

      //file()->load_lines(stra, pathPublicDomainExtensionList);

      string str = fetch_public_internet_domain_extension_list_text();

      auto psz = str.c_str();

      while (*psz != '\0')
      {

         string str(*psz);

         auto pStart = str.find('(');

         if (::is_null(pStart))
         {

            stra.add(str);

            continue;

         }

         auto pEnd = str(pStart + 1).find(')');

         if (::is_null(pEnd))
         {

            string strItem = str(0, pStart);

            stra.add(strItem);

            continue;

         }

         stra.add({ pStart, pEnd - pStart - 1 });

      }

      stra.trim();

      stra.erase_empty();

      information() << "acme::system::get_public_internet_domain_extension_list";

      for (auto& str : stra)
      {

         informationf("%s", str.c_str());

      }

      //return ::success;

   }


   void system::create_session(::collection::index iEdge)
   {

      if (session(iEdge))
      {

         //return ::success;
         return;

      }

      auto psession = on_create_session(iEdge);

      //if (!psession)
      //{

      //   return false;

      //}

      add_session(iEdge, psession);

      //return ::success;

   }



   ::pointer<::acme::session>system::on_create_session(::collection::index iEdge)
   {

      ::pointer<::acme::session>psession;

      //auto estatus =
      __raw_construct(psession);

      psession->set_platform();

      psession->initialize(this);

      psession->m_pacmeapplication = m_pacmeapplication;
      psession->m_pacmesystem = this;
      psession->m_pacmenode = m_pacmenode;

      if (m_pacmeapplication)
      {

         m_pacmeapplication->m_pacmesession = psession->m_pacmesession;

      }

      //if (!estatus)
      //{

      //   return estatus;

      //}

      psession->m_iEdge = iEdge;

      return psession;

   }


   ::acme::session* system::session(::collection::index iEdge)
   {

      auto iterator = m_sessionmap.plookup(iEdge);

      if (iterator.is_null())
      {

         return nullptr;

      }

      return iterator->element2();

   }


   void system::add_session(::collection::index iEdge, ::acme::session* psession)
   {

      if (!::is_set(psession))
      {

         return;

      }

      bool bWasEmpty = m_sessionmap.is_empty();

      m_sessionmap[iEdge] = psession;

      on_add_session(psession);

      if (bWasEmpty)
      {

         m_bFinalizeIfNoSession = m_bFinalizeIfNoSessionSetting;

      }

   }


   void system::on_add_session(::acme::session* pacmesession)
   {

      if (pacmesession->m_iEdge == 0)
      {

         if (!m_pacmesession)
         {

            m_pacmesession = pacmesession;

         }

      }

      pacmesession->m_pacmesystem = this;

   }


   void system::erase_session(::collection::index iEdge)
   {

      auto psession = m_sessionmap[iEdge];

      m_sessionmap.erase_item(iEdge);

      if (m_sessionmap.is_empty() && m_bFinalizeIfNoSession)
      {

         set_finish();

      }

      //   if (psession)
      //   {
      //
      //      class time time;
      //
      //      time.Now();
      //
      //      while (true)
      //      {
      //
      //         if (psession->m_countReference <= 1)
      //         {
      //
      //            break;
      //
      //         }
      //
      //         preempt(100_ms);
      //
      //         if (time.elapsed() > 10_s)
      //         {
      //
      //            break;
      //
      //         }
      //
      //      }
      //
      //   }
      //
   }


   void system::on_request(::request* prequest)
   {

      auto psession = session();

      if (psession == nullptr)
      {

         return;

      }

      information() << "::apex::system::on_request session = " << ::type(psession).name() << "(" << ((iptr)psession) << ")";

      psession->post_request(prequest);

   }



   void system::process_exit_status(::particle* pparticle, const ::e_status& estatus)
   {

      if (estatus == error_exit_system)
      {

         pparticle->system()->set_finish();

      }

   }


   void system::on_start_system()
   {

      ////*auto estatus =*/ m_pnode->on_start_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::defer_post_initial_request()
   {

      if (!m_bPostedInitialRequest)
      {

         m_bPostedInitialRequest = true;

         auto prequest = __create_new< ::request>();

         auto strCommandLine = platform()->m_strCommandLine;

         strCommandLine.trim();

         prequest->m_strAppId = application()->m_strAppId;

         ::string strApp;

         if (strCommandLine.has_char())
         {

            information() << "system::defer_post_initial_request ***strCommandLine*** : ***" << strCommandLine << "***";

            prequest->m_strCommandLine = strCommandLine;

            prequest->get_property_set()._008ParseCommandFork(
               strCommandLine,
               prequest->m_payloadFile,
               strApp);

         }
         else
         {

            strApp = m_pplatform->m_args[0];

            ::string_array straFiles;

            for (int iArgument = 1; iArgument < m_pplatform->m_argc; )
            {

               auto iArgumentBefore = iArgument;

               if (node()->defer_consume_main_arguments(
                  m_pplatform->m_argc,
                  m_pplatform->m_args,
                  iArgument)
                  && iArgument > iArgumentBefore)
               {

                  continue;

               }

               if (application()->defer_consume_main_arguments(
                  m_pplatform->m_argc,
                  m_pplatform->m_args,
                  iArgument)
                  && iArgument > iArgumentBefore)
               {

                  continue;

               }

               ::string strArgument = m_pplatform->m_args[iArgument];

               if (strArgument.begins("-"))
               {

                  prequest->get_property_set()._008AddArgument(strArgument);

               }
               else
               {

                  straFiles.add(strArgument);

               }

               iArgument++;

            }

            if (straFiles.has_elements())
            {

               if (straFiles.size() == 1)
               {

                  prequest->m_payloadFile = straFiles[0];

               }
               else
               {

                  prequest->m_payloadFile.string_array_reference() = straFiles;

               }

            }

         }

         payload("command_line_arg0") = strApp;

         application()->get_property_set().merge(prequest->get_property_set());

         post_request(prequest);

      }

   }


   void system::canonical_system_main()
   {

      process_init();

      if (platform()->is_console())
      {

         application()->main();

      }
      else
      {

         // on canonical system on_start_system is called before main loop
         on_start_system();

         //auto estatus = 
         main();

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }

      if (m_iExitCode == 0 && m_estatus.failed())
      {

         m_iExitCode = m_estatus.exit_code();

      }


   }


   void system::system_main()
   {

      init_system();

      m_pnode->system_main();

   }



   //::application* system::get_main_application()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void system::system_construct(int argc, char** argv, char** envp)
   //{

   //   throw ::interface_only();

   //}


   //void system::system_construct(int argc, wchar_t** argv, wchar_t** envp)
   //{

   //   throw ::interface_only();

   //}

   //
   //   void system::inline_init()
   //   {
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
   //      return ::success;
   //
   //   }
   //
   //
   void system::inline_term()
   {

      //return ::success;

   }


   //   void system::on_start_system()
   //   {
   //
   //      return ::success;
   //
   //   }
   //
   //
   void system::on_end()
   {

      TermSystem();

      //return ::success;

   }

   void system::end()
   {

      /*auto estatus = */ on_end();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      /*estatus = */ inline_term();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;
      //
#ifdef __MCRTDBG

      _CrtDumpMemoryLeaks();

#endif

   }


   void system::report_system_instance()
   {

      string strAppId = application()->m_strAppId;

      if (strAppId.has_char())
      {

         string strModifier;

         string strDate;

         strDate = datetime()->date_time_text_for_file_with_no_spaces();

         string strPid;

         strPid = ::as_string(node()->current_process_identifier());

         strModifier = strDate + "_" + strPid;

         ::file::path pathFolder;

#ifdef ANDROID

         pathFolder = system()->m_pathCacheDirectory;

#else

         pathFolder = acmedirectory()->roaming();

#endif

         pathFolder /= strAppId;

         pathFolder /= "instance";

         ::file::path path = pathFolder / (strModifier + "_command_line.txt");

         acmefile()->put_contents(path, platform()->m_strCommandLine);

         ::file::path pathExecutable = acmefile()->module();

         string strAppTitle = node()->executable_title_from_appid(strAppId);

         path = pathFolder / (strModifier + "_executable.txt");

         acmefile()->put_contents(path, pathExecutable);

      }

   }




   ::acme::application* system::get_main_app()
   {


      throw ::interface_only();


      return nullptr;

   }


   ::pointer<::factory::factory>& system::folder_factory()
   {

      if (m_pfactoryFolder)
      {

         return m_pfactoryFolder;

      }

      m_pfactoryFolder = factory("folder", "zip");

      m_pfactoryFolder->merge_to_global_factory();

      return m_pfactoryFolder;

   }


   void system::system_construct(::acme::application* papplication)
   {

      m_pacmeapplication = papplication;


      ///*auto estatus = */ ::main::system_construct(papplication);

      /*  if (!estatus)
       {

       return estatus;

       }

       return estatus;*/

      if (m_pacmeapplication)
      {

         m_pacmeapplication->m_pacmesystem = this;

      }


   }


   //void system::system_construct(int argc, wchar_t** argv, wchar_t** envp)
   //{

   //   acme_main_data::system_construct(argc, argv, envp);

   //}



//   void system::os_construct()
//   {
//
//
//   }


#ifdef _DEBUG


   i64 system::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   i64 system::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif


   void system::system_id_update(::i64 iId, ::i64 iPayload)
   {

      call((::enum_id)iId, iPayload);

   }

   void system::handle(::topic* ptopic, ::context* pcontext)
   {

      if (ptopic->m_atom == id_get_operating_system_dark_mode_reply)
      {

         if (ptopic->payload("wparam").is_true())
         {

            background_color(::color::black);

         }
         else
         {

            background_color(::color::white);

         }

         if (m_pnano)
         {

            m_pnano->handle(ptopic, pcontext);

         }

      }
      else if (ptopic->m_atom == id_operating_system_user_theme_change)
      {

         // auto pnode = node();
         //
         // string strTheme = pnode->os_get_user_theme();
         //
         // if (strTheme != m_strOsUserTheme)
         // {
         //
         //    m_strOsUserTheme = strTheme;
         //
         // }

      }
      else if (ptopic->m_atom == id_open_hyperlink)
      {

         auto plink = ptopic->_extended_topic()->m_payload.cast < ::hyperlink >();

         if (plink)
         {

            //if (plink->m_bProfile)
            {

               open_profile_link(plink->m_strLink, plink->m_strBrowserAccount, plink->m_strTarget);

            }
            //else
            {

               // open_link(plink->m_strLink, plink->m_strProfile, plink->m_strTarget);

            }

         }

      }
      else if (ptopic->m_atom == id_app_activated)
      {

         node()->on_app_activated();
         
         if (::is_set(application()))
         {

            application()->handle(ptopic, pcontext);

         }

      }
      else if (ptopic->m_atom == id_did_pick_document_at_url)
      {

         if (::is_set(application()))
         {
            
            auto pszUrl = (const char *) ptopic->payload("wparam").as_iptr();

            application()->did_pick_document_at_url(pszUrl);

         }

      }

   }


   //   void system::add_handler(::matter * pmatter, bool bPriority)
   //   {
   //
   //
   //   }


   void system::add_signal_handler(const ::signal_handler& signalhandler, const ::atom& atomSignal)
   {


   }


   void system::erase_signal_handler(::signal_handler::base* pbase)
   {

   }


   //   void system::erase_signal_handlers(::particle * pparticle)
   //   {
   //      
   //   }


   void system::node_will_finish_launching()
   {

      //   auto pnode = node();
      //
      //   pnode->_will_finish_launching();

      //   auto pnode = session()->m_paurasession;
      //
      //   auto puser = psession->user();
      //
      //   auto pwindowing = puser->windowing();
      //
      //   pwindowing->_will_finish_launching();

      auto pnode = node();

      pnode->_will_finish_launching();

      //return ::success;

   }


   void system::on_open_untitled_file()
   {

      if (!m_bPostedInitialRequest)
      {

         defer_post_initial_request();

      }

      //      throw ::interface_only();

      //throw ::interface_only();

   }


   void system::on_open_file(const ::string& pszFile)
   {

      throw ::interface_only();

   }


   ::pointer < ::compress > system::_new_compress(const ::scoped_string& scopedstrImplementation)
   {

      auto pcompress = create < ::compress >("compress", scopedstrImplementation);

      if (!pcompress)
      {

         throw ::exception(error_resource);

      }

      return pcompress;

   }


   ::pointer < ::uncompress > system::_new_uncompress(const ::scoped_string& scopedstrImplementation)
   {

      auto puncompress = create < ::uncompress >("compress", scopedstrImplementation);

      if (!puncompress)
      {

         throw ::exception(error_resource);

      }

      /// *ppuncompress = puncompress;

      //puncompress->increment_reference_count();

      return puncompress;

   }


   ::pointer < ::compress > system::new_zlib_compress()
   {

      if (!m_pfactoryitemCompressZlib)
      {

         auto& pfactory = this->factory("compress", "zlib");

         m_pfactoryitemCompressZlib = pfactory->get_factory_item< ::compress>();

      }

#if REFERENCING_DEBUGGING
      ::allocator::add_referer({refdbg_this(), __FUNCTION_FILE_LINE__});
#endif

      auto pcompress = m_pfactoryitemCompressZlib->__call__create_particle();

      pcompress->initialize(this);

      return pcompress;

   }



   ::pointer < ::uncompress > system::new_zlib_uncompress()
   {

      if (!m_pfactoryitemUncompressZlib)
      {

         auto& pfactory = this->factory("compress", "zlib");

         m_pfactoryitemUncompressZlib = pfactory->get_factory_item< ::uncompress>();

      }

      auto puncompress = m_pfactoryitemUncompressZlib->__call__create_particle();

      puncompress->initialize(this);

      return puncompress;

   }


   void system::_compress(const ::payload& payloadTarget, const ::payload& payloadSource, const ::scoped_string& scopedstrImplementation)
   {

      ::pointer<::compress>pcompress = _new_compress(scopedstrImplementation);

      ///*auto estatus =*/ new_compress(&pcompress.m_p, scopedstrImplementation);

      /*  if (!estatus)
       {

       return estatus;

       }*/

      auto pfileTarget = acmefile()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);

      auto pfileSource = acmefile()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);

      /*estatus = */ pcompress->transfer(pfileTarget, pfileSource);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::_uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, const ::scoped_string& scopedstrImplementation, transfer_progress_function transferprogressfunction)
   {

      ::pointer<::uncompress>puncompress = _new_uncompress(scopedstrImplementation);

      ///*auto estatus = */ new_uncompress(&puncompress.m_p, scopedstrImplementation);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pfileTarget = acmefile()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);

      auto pfileSource = acmefile()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);

      /*estatus = */ puncompress->transfer(pfileTarget, pfileSource, transferprogressfunction);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::zlib_compress(const ::payload& payloadTarget, const ::payload& payloadSource)
   {

      ::pointer<::compress>pcompress = new_zlib_compress();

      ///*auto estatus =*/ new_compress(&pcompress.m_p, scopedstrImplementation);

      /*  if (!estatus)
       {

       return estatus;

       }*/

      auto pfileTarget = acmefile()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);

      auto pfileSource = acmefile()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);

      /*estatus = */ pcompress->transfer(pfileTarget, pfileSource);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::zlib_uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, transfer_progress_function transferprogressfunction)
   {

      ::pointer<::uncompress>puncompress = new_zlib_uncompress();

      ///*auto estatus = */ new_uncompress(&puncompress.m_p, scopedstrImplementation);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pfileTarget = acmefile()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);

      auto pfileSource = acmefile()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);

      /*estatus = */ puncompress->transfer(pfileTarget, pfileSource, transferprogressfunction);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   bool system::fast_is_decompressable_folder(const ::file::path& path)
   {

      auto bZip = path.case_insensitive_ends(".zip");

      if (bZip)
      {

         return true;

      }

      return false;

   }




   //::pointer < ::subparticle > system::message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
   //{
   //
   //   auto psequencer = nano()->message_box(strMessage, strTitle, emessagebox, strDetails);
   //
   //   pmessagebox->sync();
   //
   //   return psequencer;
   //
   //}

   ::pointer<::acme::application>system::new_app(const ::scoped_string& scopedstrAppId)
   {

      ::pointer<::acme::application>papp;

      string strAppId = scopedstrAppId;

      auto psetup = system_setup::get_first(::system_setup::flag_application, strAppId);

      if (psetup)
      {

         auto pelementApp = psetup->create_application_as_particle();

         papp = pelementApp;

         //papp.reset(papp.m_p REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);

         if (papp)
         {

            strAppId = papp->m_strAppId;

         }

      }

      //#ifndef CUBE

      if (!papp)
      {

         if (strAppId.is_empty() || platform()->is_console())
         {

            papp = __create < ::acme::application >();

            papp->increment_reference_count();

         }
         else
         {

            string strLibrary = strAppId;

            strLibrary.replace_with("_", "/");

            strLibrary.replace_with("_", "-");

            if (application()->m_bVerbose)
            {

               informationf("\n\n::apex::session::get_new_application assembled library path " + strLibrary + "\n\n");

            }

            //auto psystem = system()->m_papexsystem;

            auto& plibrary = m_pplatform->library(strLibrary);

            if (!plibrary)
            {

#ifndef UNIVERSAL_WINDOWS

               //            output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", e_message_box_icon_error);

               //output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. ", "ca2", e_message_box_icon_error);

               informationf("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + "ca2");

#endif

               return nullptr;

            }

            if (application()->m_bVerbose)
            {

               informationf("\n\n::apex::session::get_new_application Found library : " + strLibrary + "\n\n");

            }

            // error anticipation is not perfect prediction and may affect results
            // so anticipation may be counter-self-healing
            // specially if what it would avoid on error is exactly we want if successful
            // who doesn't try it, won't taste it neither possibly enjoy it
            //          if (!plibrary->is_opened())
            //          {
            //
            //             informationf("\n\n::apex::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
            //
            //             return nullptr;
            //
            //          }

            if (application()->m_bVerbose)
            {

               informationf("\n\n::apex::session::get_new_application Opened library : " + strLibrary + "\n\n");

            }

            ::factory::factory_pointer pfactory;

            plibrary->create_factory(pfactory);

            if (pfactory)
            {

               papp = __create < ::acme::application >(pfactory);

               if (!papp)
               {

                  informationf("\n\n::apex::session::get_new_application\n...but this ___new found library:\n\n   -->  " + strLibrary + "  <--\n\ncannot instantiate application with following AppId:\n\n   -->  " + strAppId + "  <--\n\nIs it missing application factory_item?\n\n\n");

               }

               ::e_status estatus;

               //         if(papp)
               //         {
               //
               //            estatus = papp->initialize(pparticle);
               //
               //         }

               informationf("\n\n\n|(4)----");
               informationf("| app : " + strAppId + "(papp=0x" + ::hex::upper_case_from((uptr)papp.m_p) + ")\n");
               informationf("|\n");
               informationf("|\n");
               informationf("|----");

            }

         }

      }

      //#endif

      if (!papp)
      {

         return nullptr;

      }

      //#ifdef WINDOWS_DESKTOP
      //
      //      WCHAR wsz[1024];
      //
      //      DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);
      //
      //      GetUserNameW(wsz, &dwSize);
      //
      //      string strUserName = wsz;
      //
      //#endif // WINDOWS_DESKTOP

      //   if (is_verbose())
      //   {
      //
      //      informationf("\n\n\n|(3)----");
      //      informationf("| app : " + strAppId + "\n");
      //      informationf("|\n");
      //      informationf("|\n");
      //      informationf("|----");
      //
      //   }
      //
      //   if (is_verbose())
      //   {
      //
      //      informationf("\n\n\n|(2)----");
      //      informationf("| app : " + strAppId + "\n");
      //      informationf("|\n");
      //      informationf("|\n");
      //      informationf("|----");
      //
      //   }
      //
      //
      //   if (is_verbose())
      //   {
      //
      //      informationf("\n\n\n|(1)----");
      //      informationf("| app : " + strAppId + "\n");
      //      informationf("|\n");
      //      informationf("|\n");
      //      informationf("|----");
      //
      //   }

      papp->m_strAppId = strAppId;

      //if (m_strAppId.is_empty())
      //{

      //   m_strAppId = strAppId;

      //}

      return papp;

   }


   bool system::_handle_call(::payload& payload, const ::string& strObject, const ::string& strMember, ::property_set& propertyset)
   {

      try
      {

         bool bOk = false;

         if (m_pacmeapplication)
         {

            if (m_pacmeapplication->_handle_call(payload, strObject, strMember, propertyset))
            {

               return true;

            }

         }

      }
      catch (...)
      {

      }

      return false;

   }


   string system::get_latest_deployment_number(const ::string& strBranch)
   {

      return "(lastest deployed build)";

   }


   //   void system::windowing_send(const ::procedure & procedure)
   //   {
   //
   //      auto pmanualresetevent = __allocate manual_reset_event();
   //
   //      windowing_post([pmanualresetevent, procedure]()
   //                     {
   //
   //                        procedure();
   //
   //                        pmanualresetevent->set_event();
   //
   //      }
   //
   //      );
   //
   //      pmanualresetevent->wait(procedure.m_timeTimeout);
   //
   //   }


   void system::destroy()
   {

#if !defined(WINDOWS)

      if (::is_set(m_pexceptiontranslator))
      {

         m_pexceptiontranslator->detach();

         m_pexceptiontranslator->destroy();

         m_pexceptiontranslator.release();

      }

#endif

      ::acme::context::destroy();

      ::task::destroy();

      auto ptask = ::get_task();

      if (ptask == this)
      {

         ::task_release();

      }

      ::platform::get()->m_psystem.release();

   }


   ::string system::implementation_name(const ::scoped_string& scopedstrComponent, const ::scoped_string& scopedstrImplementation)
   {

      return scopedstrImplementation;

   }


   ::string system::library_name(const ::scoped_string& scopedstrComponent, const ::scoped_string& scopedstrImplementation)
   {

      return scopedstrComponent + "_" + scopedstrImplementation;

   }


   ::file::path system::local_get_matter_path()
   {

      return acmedirectory()->ca2roaming() / "appmatter";

   }


   ::file::path system::local_get_matter_path(string strMatter)
   {

#ifdef UNIVERSAL_WINDOWS

      return "";

#else

      return local_get_matter_path() / strMatter;

#endif

   }


   ::file::path system::local_get_matter_cache_path()
   {

      return acmedirectory()->ca2roaming() / "cache/appmatter";

   }


   ::file::path system::local_get_matter_cache_path(string strMatter)
   {

      return local_get_matter_cache_path() / strMatter;

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


   void system::install_progress_add_up(int iAddUp)
   {


   }


   class ::manager_room * system::manager_room()
   {

      return nullptr;

   }



   ::string system::get_application_server_name()
   {

      string strApplicationServerName = application()->m_strAppId;

      strApplicationServerName.replace_with(".", "/");

      strApplicationServerName.replace_with("-", "_");

      return strApplicationServerName;

   }


   ::draw2d::draw2d* system::draw2d() const
   {

      return nullptr;

   }


   ::write_text::write_text* system::write_text() const
   {

      return nullptr;

   }


   ::color::color system::background_color() const
   {

      return m_colorBackground;

   }


   double system::luminance() const
   {

      return m_dLuminance;

   }


   void system::background_color(const ::color::color & color)
   {

      if (m_colorBackground == color)
      {

         return;

      }

      m_colorBackground = color;

      m_dLuminance = m_colorBackground.get_luminance();

      set_dark_mode(m_dLuminance < 0.5);

   }


   ::color::color system::get_simple_ui_color(::enum_element eelement, ::user::enum_state estate)
   {

      ::color::color color;

      if (eelement == ::e_element_background)
      {

         if (dark_mode())
         {

            color = argb(255, 0x50, 0x50, 0x58);

         }
         else
         {

            color = argb(255, 0xcd, 0xcd, 0xc8);

         }

      }
      else
      {

         if (dark_mode())
         {

            color = argb(255, 255, 255, 255);

         }
         else
         {

            color = argb(255, 49, 50, 42);

         }

      }

      return color;

   }


   ::color::color system::get_default_color(::color::color color)
   {

      return argb(255, 0, 0, 0);

   }


   void system::set_dark_mode(bool bDark)
   {

      m_bDarkMode = bDark;

      if (m_bDarkMode)
      {

         informationf("background_color :: Dark\n");

      }
      else
      {

         informationf("background_color :: Lite\n");

      }

      on_application_dark_mode_change();

   }


   bool system::dark_mode() const
   {

      return m_bDarkMode;

   }


   void system::on_application_dark_mode_change()
   {

      auto ptopic = __allocate ::topic(id_application_dark_mode_change);

      application()->handle(ptopic, nullptr);

   }


   bool system::defer_component_factory(const ::scoped_string & scopedstrComponent)
   {

      auto pnode = node();

      if (::is_set(pnode))
      {

         if (pnode->defer_component_factory(scopedstrComponent))
         {

            return true;

         }

         ::string strComponentDefaultImplementation = pnode->default_component_implementation(scopedstrComponent);

         if (strComponentDefaultImplementation.has_char())
         {

            auto pfactory = this->factory(scopedstrComponent, strComponentDefaultImplementation);

            if (pfactory)
            {

               pfactory->merge_to_global_factory();

               return true;

            }

         }


      }

      if(_defer_component_factory(scopedstrComponent))
      {

         return true;

      }

      return false;


   }


   bool system::_defer_component_factory(const ::scoped_string & scopedstrComponent)
   {

      //if (scopedstrComponent == "nano_dynamic_library")
      //{

      //   auto pfactory = this->factory();

      //   nano_dynamic_library_factory(pfactory);

      //   return true;

      //}

//      else if (scopedstrComponent == "nano_user")
//      {
//
//
//#if defined(WINDOWS_DESKTOP)
//
//
//         auto pfactory = this->factory();
//
//         nano_user_win32_factory(pfactory);
//
//         return;
//         
//#elif defined(UNIVERSAL_WINDOWS)
//
//
//         auto pfactory = this->factory();
//
//
//         nano_user_universal_windows_factory(pfactory);
//
//
//         return;
//
//#elif defined(MACOS)
//         
//         auto pfactory = this->factory();
//
//         nano_user_macos_factory(pfactory);
//
//         return;
//         
//#elif defined(APPLE_IOS)
//
//         return;
//
//#endif
//
//      }
//      else if (scopedstrComponent == "nano_user")
//      {
//
//
//#if defined(WINDOWS_DESKTOP)
//
//
//         auto pfactory = this->factory();
//
//         nano_user_win32_factory(pfactory);
//
//         return;
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//
//         auto pfactory = this->factory();
//
//
//         nano_user_universal_windows_factory(pfactory);
//
//
//         return;
//
//#elif defined(MACOS)
//
//         auto pfactory = this->factory();
//
//         nano_user_macos_factory(pfactory);
//
//         return;
//
//#elif defined(APPLE_IOS)
//
//         return;
//
//#endif
//
//      }

      return false;

   }


   ::micro::user * system::micro_user()
   {

      if (!m_pmicrouser)
      {

         __construct_new(m_pmicrouser);

      }

      return m_pmicrouser;

   }


   ::acme::windowing::windowing * system::acme_windowing()
   {

      if (!m_pacmewindowing)
      {

         do_graphics_and_windowing_system_factory();

         __construct(m_pacmewindowing);

      }

      return m_pacmewindowing;

   }


   ::windowing::windowing * system::windowing()
   {

      return acme_windowing()->windowing_windowing();

   }


   void system::do_graphics_and_windowing_system_factory()
   {

      if(!m_bGraphicsAndWindowingSystemInitialized)
      {

         m_bGraphicsAndWindowingSystemInitialized = true;

         nano()->graphics();

         ::string strToolkit = ::windowing::get_user_toolkit_id();

         m_pfactoryAcmeWindowing = this->factory("acme_windowing", strToolkit);

         m_pfactoryAcmeWindowing->merge_to_global_factory();

      }

   }


   //::pointer < ::message_box > & system::realize(::pointer < ::message_box > & pmessagebox)
   //{

   //   return micro_user()->realize(pmessagebox);

   //}

   
//   ::pointer < ::message_box > system::message_box(const ::string & strMessage, const ::string & strTitle,
//                                                       const ::e_message_box & emessagebox,
//                                                       const ::string & strDetails, ::nano::graphics::icon * picon)
//   {
//      
//      
//      return micro_user()->message_box(
//strMessage,
//strTitle,
//emessagebox,
//strDetails,
//picon);
//   }


   //::pointer < ::message_box > system::exception_message_box(
   //    const ::exception & exception, const ::string & strMessage, 
   //   const ::string & strTitle,
   //    const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
   //{
   //   return micro_user()->exception_message_box(
   //exception,
   //strMessage,
   //strTitle,
   //emessagebox,
   //strDetails,
   //picon);

   //}


   //::pointer < ::message_box > system::message_console(const ::string & strMessage, const ::string & strTitle,
   //                                                           const ::e_message_box & emessagebox,
   //                                                           const ::string & strDetails, ::nano::graphics::icon * picon)
   //{
   //   
   //   return micro_user()->message_console(
   //      strMessage,
   //      strTitle,
   //      emessagebox,
   //      strDetails,
   //      picon);

   //}


   //::pointer < ::message_box > system::exception_message_console(
   //    const ::exception & exception, const ::string & strMessage,
   //   const ::string & strTitle,
   //    const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
   //{

   //   return micro_user()->exception_message_console(
   //      exception,
   //      strMessage,
   //      strTitle,
   //      emessagebox,
   //      strDetails,
   //      picon);

   //}


   //::windowing::windowing_base * system::windowing_base()
   //{

   //   if(!m_pwindowingbase)
   //   {

   //      do_graphics_and_windowing_system_factory();

   //      __construct(m_pwindowingbase);

   //   }

   //   return m_pwindowingbase;

   //}


} // namespace acme


//CLASS_DECL_ACME::acme::system * system()
//{

  // return g_psystem;

//}


//CLASS_DECL_ACME class ::plane_system * get_plane_system()
//{
//
//   return system();
//
////}
//
//
//CLASS_DECL_ACME string get_latest_deployment_number(const ::string & strBranch)
//{
//
//   return system()->get_latest_deployment_number(strBranch);
//
//}




//
//CLASS_DECL_ACME string __get_text(const string & str)
//{
//
//   return ::g_psystem->__get_text(str);
//
//}

//
//CLASS_DECL_ACME::acme::system * get_context_system()
//{
//
//   return g_psystem;
//
//}

//
//CLASS_DECL_ACME::acme::system * acme_system_init()
//{
//
//   g_psystem = ___new ::acme::system ();
//
//   return g_psystem;
//
//}


//CLASS_DECL_ACME void acme_system_term()
//{
//
//   ::acme::del(g_psystem);
//
//}


void system_id_update(void* pSystem, ::i64 iUpdate, ::i64 iParam)
{

   auto psystem = (::acme::system*)pSystem;

   psystem->system_id_update(iUpdate, iParam);

}


void node_will_finish_launching(void* pSystem);
void system_on_open_untitled_file(void* pSystem);
void system_on_open_file(void* pSystem, const char* pszFile);


void node_will_finish_launching(void* pSystem)
{

   auto psystem = (::acme::system*)pSystem;

   psystem->node_will_finish_launching();

}


void system_on_open_untitled_file(void* pSystem)
{

   auto psystem = (::acme::system*)pSystem;

   psystem->on_open_untitled_file();

}


void system_on_open_file(void* pSystem, const char* pszFile)
{

   auto psystem = (::acme::system*)pSystem;

   psystem->on_open_file(pszFile);


}


//::pointer<::acme::system>platform_create_system(const ::scoped_string & scopedstrAppId)
//{
//
//   string strAppId(pszAppId);
//
//#if !defined(CUBE)
//
//   if (strAppId.has_char())
//   {
//
//      string strMessage;
//
//      string strLibrary = strAppId;
//
//      strLibrary.replace_with("_", "/");
//
//      strLibrary.replace_with("_", "-");
//
//      strLibrary.replace_with("_", ".");
//
//      auto plibrary = psystem->operating_system_library_open(strLibrary, strMessage);
//
//      if (!plibrary)
//      {
//
//         //{
//
//         //   //auto pfuture = __sync_future();
//
//         //   //message_box(strMessage, "Could not open required library. Want to give an yes/no answer insted of pression cancel?", e_message_box_icon_exclamation | e_message_box_yes_no_cancel, pfuture);
//
//         //   //pfuture->wait(10_s);
//
//         //   int iDialogResult = pfuture->m_var;
//
//         //   informationf("result " + as_string(iDialogResult));
//
//         //}
//
//         //throw ::exception(error_failed, strMessage + "\n\nCould not open required library.");
//
//         informationf("The application library for appid \"" + strAppId + "\" wasn't loaded.");
//
//      }
//
//   }
//
//#endif
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
//   auto pelement = pstaticsetup->create_particle();
//
//   if (!pelement)
//   {
//
//      return nullptr;
//
//   }
//
//   ::pointer<::acme::system>psystem = pelement;
//
//   if (!psystem)
//   {
//
//      return nullptr;
//
//   }
//
//   //psystem->m_strAppId = strAppId;
//
//   return ::transfer(psystem);
//
//}
//

CLASS_DECL_ACME task_pointer fork(::particle* pparticle, const ::procedure& procedure)
{

   return pparticle->system()->fork(procedure);

}

