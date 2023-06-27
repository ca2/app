#include "framework.h"
#include "library.h"
#include "node.h"
#include "acme.h"
#include "system_setup.h"
#include "system.h"
#include "sequencer.h"
#include "application.h"
#include "session.h"
#include "simple_log.h"
#include "hyperlink.h"
#include "acme/compress/compress.h"
#include "acme/compress/uncompress.h"
#include "acme/constant/id.h"
#include "acme/constant/idpool.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/file/transfer.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/translator.h"
#include "acme/handler/topic.h"
#include "acme/handler/extended_topic.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/debug.h"
#include "acme/handler/request.h"
#include "acme/regular_expression/context.h"
#include "acme/primitive/datetime/datetime.h"
//#include "acme/primitive/primitive/payload.h"
//#include "acme/primitive/string/hex.h"
#include "acme/user/nano/nano.h"
//#include "acme/user/user/conversation.h"


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);
CLASS_DECL_ACME void trace_category_static_init(::acme::system * psystem);
CLASS_DECL_ACME void trace_category_static_term();


//static ::acme::system * g_psystem = nullptr;


//extern const char * g_pszTopLevelDomainList[];


enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::enum_message_box & emessagebox);



#include "acme/_operating_system.h"


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

      //__defer_construct_new(m_pprintingformat);

      m_plogger = __create_new < ::simple_log >();

#ifndef WINDOWS

      ::unsetenv("LD_LIBRARY_PATH");

#endif


   }


   system::~system()
   {

      trace_category_static_term();

   }


   void system::initialize_system()
   {

      m_psubsystem = ::acme::acme::g_pacme->m_psubsystem;

      m_psubsystem->initialize(this);

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
      //      //pacmeapplication->m_argc = __argc;
      //
      //      //pacmeapplication->m_argv = __argv;
      //
      //      //pacmeapplication->m_wargv = __wargv;
      //
      //      //pacmeapplication->m_envp = *__p__environ();
      //
      //      //pacmeapplication->m_wenvp = *__p__wenviron();
      //
      //      //pacmeapplication->m_hinstanceThis = hinstanceThis;
      //
      //      //pacmeapplication->m_hinstancePrev = hinstancePrev;
      //
      //      //pacmeapplication->m_nCmdShow = nCmdShow;
      //
      //      //pacmeapplication->m_bConsole = false;
      //
      //      //int iExitCode = pacmeapplication->main_loop();
      //
      //      //return iExitCode;
      //
      //#elif !defined(UNIVERSAL_WINDOWS)
      //
      //      //pacmeapplication->set_args(g_argc, g_argv, g_envp);
      //
      //#endif
      //
      m_ewindowing = e_windowing_none;

      m_plogger->m_etracelevelMinimum = e_trace_level_information;

      trace_category_static_init(this);


      //____creatable_from_base(simple_log, logger);

      //____creatable(task);

      m_bPostedInitialRequest = false;

      //m_bOnInitializeWindowObject = false;

      //m_pcleanuptask = __new(::parallelization::cleanup_task);

      //m_pcleanuptask->begin();
      //factory()->add_factory_item<::acme::idpool>();

      //m_pacme = nullptr;
      //m_pacmedirectory = nullptr;
      //m_pacmepath = nullptr;

      factory()->initialize(this);

      //#ifdef LINUX
      //
      //      m_elinuxdistribution = e_linux_distribution_unknown;
      //
      //#endif

      //m_edesktop = ::user::e_desktop_none;

      os_construct();

      //acmesystem() = this;

      //      if (g_psystem == nullptr)
      //      {
      //
      //         g_psystem = this;
      //
      //      }


      __construct_new(m_pnano);

      //m_psystemimpl = memory_new system_impl;

      //set_os_data(LAYERED_ACME, this);




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


   void system::main()
   {

      /*auto estatus = */ process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      /*estatus =*/
      run();


      if (acmeapplication()->m_bConsole)
      {

         acmeapplication()->main();

      }

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


   ::xml::xml * system::_xml()
   {

      return nullptr;

   }


   void system::create_os_node()
   {

      if (m_pnode)
      {

         //return ::success;

         return;

      }

      auto & pfactory = node_factory();

      if (!pfactory)
      {

         //fatal() <<"node_factory has failed (status=" << (const void &) pfactory << ")";

         throw ::exception(error_resource);

      }


#if !defined(WINDOWS)


      __construct(m_pexceptiontranslator);


      m_pexceptiontranslator->attach();


#endif


      //auto estatus = __construct(m_pnode);
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


   ::pointer<::factory::factory> & system::node_factory()
   {

      auto & pfactory = factory("acme", OPERATING_SYSTEM_NAME);

      if (!pfactory)
      {

         return pfactory;

      }

      pfactory->merge_to_global_factory();

      return pfactory;

   }


   void system::process_init()
   {

      //::acme::idpool::init(this);

      /// Create/Replace logger
      __construct(m_plogger);

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


      report_system_instance();




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

      m_pmapRegularExpressionContext.release();

      m_pfactoryFolder.release();

      //::acme::idpool::term();

      m_pnode->node_quit();

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


   void system::erase_from_any_hook(::matter * pmatter)
   {


   }


   string system::os_get_user_theme()
   {

      return m_strOsUserTheme;

   }


   ::u32 system::crc32(::u32 uCrc, const ::block & block)
   {

      auto pcompress = create < ::compress >("compress", "zlib");

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


   ::task * system::get_task(itask_t itask)
   {

      synchronous_lock synchronouslock(m_pmutexTask);

      return m_taskmap[itask];

   }


   itask_t system::get_task_id(const ::task * ptask)
   {

      synchronous_lock synchronouslock(m_pmutexTask);

      itask_t itask = null_itask;

      if (!m_taskidmap.lookup((::task * const)ptask, itask))
      {

         return 0;

      }

      return itask;

   }


   void system::set_task(itask_t itask, ::task * ptask)
   {

      synchronous_lock synchronouslock(m_pmutexTask);

      m_taskmap[itask].reset(ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      m_taskidmap[ptask] = itask;

   }


   void system::unset_task(itask_t itask, ::task * ptask)
   {

      synchronous_lock synchronouslock(m_pmutexTask);

#if OBJECT_REFERENCE_COUNT_DEBUG

      m_taskmap[itask].release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);

#endif

      m_taskmap.erase_item(itask);

      m_taskidmap.erase_item(ptask);

   }


   void system::init_task()
   {

      task::init_task();

      init_system();

   }


   void system::term_task()
   {

      //term_system();

      task::term_task();

   }

   string system::__get_text(const ::string & str)
   {

      return str;

   }


   //pointer< ::extended::sequence < ::conversation > > system::message_box(::user::interaction * puserinteraction, const ::string & pszText, const ::string & pszTitle, const ::e_message_box & emessagebox)
   //{

   //   auto psequence = __new(::sequence < ::conversation >);

   //   psequence->set_status(error_interface_only);

   //   //return presult;

   //   //auto pprocess = __new(status < enum_dialog_result >);

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


   //CLASS_DECL_ACME class system * acmesystem()
   //{
   //
   //   return ::g_psystem;
   //
   //}
   //


   bool system::is_task_on(itask_t atom)
   {

      synchronous_lock synchronouslock(m_pmutexTaskOn);

      return m_mapTaskOn.plookup(atom);

   }


   bool system::is_active(::task * ptask)
   {

      if (::is_null(ptask))
      {

         return false;

      }

      return is_task_on(m_itask);

   }


   void system::set_task_on(itask_t atom)
   {

      synchronous_lock synchronouslock(m_pmutexTaskOn);

      m_mapTaskOn.set_at(atom, atom);

   }


   void system::set_task_off(itask_t atom)
   {

      synchronous_lock synchronouslock(m_pmutexTaskOn);

      m_mapTaskOn.erase_item(atom);

   }


   task_group * system::task_group(enum enum_priority)
   {

      return nullptr;

   }


   task_tool * system::task_tool(::enum_task_tool etool)
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
      catch (::exception & exception)
      {

         //message_box_synchronous(this, exception.m_strMessage, m_strAppId, e_message_box_ok, exception.m_strDetails);

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

      //acmeapplication() = pappStartup;

      m_pacmeapplication->initialize(this);

      m_pacmeapplication->get_property_set().merge(get_property_set());

      //*((::APPLICATION_FLAGS *)this) = *acmeapplication();

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


   void system::defer_audio()
   {

      throw ::interface_only();

   }


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

      if (acmeapplication()->m_bSession)
      {
       
         //return ::success;
         create_session();

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

   //   auto psystem = acmesystem();

   //   synchronous_lock synchronouslock(&psystem->m_pmutexLibrary2);

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

   //   auto psystem = acmesystem();

   //   synchronous_lock synchronouslock(&psystem->m_pmutexContainerizedLibrary);

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

   //      plibrary = __new(::acme::library);

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


   class ::time system::get_update_poll_time(const ::atom & atom)
   {

      return 0_s;

   }


   ::acme::library * system::on_get_library(const ::string & pszLibrary)
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
   //      synchronous_lock synchronouslock(m_pmutexContainerizedLibrary);
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
   //      plibrary = __new(::acme::library);
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


   ::regular_expression_pointer system::create_regular_expression(const ::string & pszStyle, const string & str)
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


   ::pointer<::regular_expression::context>system::get_regular_expression_context(const ::string & pszStyle)
   {

      __defer_construct_new(m_pmapRegularExpressionContext);

      auto & pcontext = (*m_pmapRegularExpressionContext)[pszStyle];

      if (!pcontext)
      {

         auto & pfactory = factory("regular_expression", pszStyle);

         if (!pfactory)
         {

            throw ::exception(error_resource);

         }

         pfactory->__construct(this, pcontext);

      }

      return pcontext;

   }


   ::regular_expression_pointer system::compile_pcre(const string & str)
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


   void system::get_public_internet_domain_extension_list(string_array & stra)
   {

      //::file::path pathPublicDomainExtensionList = "https://server.ca2.software/public_internet_domain_extension_list.txt";

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

      for (auto & str : stra)
      {

         information("%s", str.c_str());

      }

      //return ::success;

   }


   void system::create_session(index iEdge)
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



   ::pointer<::acme::session>system::on_create_session(index iEdge)
   {

      ::pointer<::acme::session>psession;

      //auto estatus =
      __construct(psession);

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


   ::acme::session * system::session(index iEdge)
   {

      auto iterator = m_sessionmap.plookup(iEdge);

      if (iterator.is_null())
      {

         return nullptr;

      }

      return iterator->element2();

   }


   void system::add_session(index iEdge, ::acme::session * psession)
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


   void system::on_add_session(::acme::session * pacmesession)
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


   void system::erase_session(index iEdge)
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


   void system::on_request(::request * prequest)
   {

      auto psession = acmesession();

      if (psession == nullptr)
      {

         return;

      }

      information() << "::apex::system::on_request session = " << __type_name(psession) << "(" << ((iptr)psession) << ")";

      psession->post_request(prequest);

   }



   void system::process_exit_status(::particle * pparticle, const ::e_status & estatus)
   {

      if (estatus == error_exit_system)
      {

         pparticle->acmesystem()->set_finish();

      }

   }


   void system::on_start_system()
   {

      /*auto estatus =*/ m_pnode->on_start_system();

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

         auto strCommandLine = acmeapplication()->m_strCommandLine;

         prequest->m_strAppId = acmeapplication()->m_strAppId;

         ::string strApp;

         prequest->get_property_set()._008ParseCommandFork(
                                                           strCommandLine,
                                                           prequest->m_payloadFile,
                                                           strApp);

#if !defined(WINDOWS)

         for (::index iArgument = 1; iArgument < m_psubsystem->m_argc; iArgument++)
         {

            ::string strArgument = m_psubsystem->m_argv[iArgument];

            prequest->get_property_set()._008AddArgument(strArgument);

         }

#endif

         payload("command_line_arg0") = strApp;

         acmeapplication()->get_property_set().merge(prequest->get_property_set());

         post_request(prequest);

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

      string strAppId = acmeapplication()->m_strAppId;

      if (strAppId.has_char())
      {

         string strModifier;

         string strDate;

         strDate = datetime()->international().get_date_time_for_file_with_no_spaces();

         string strPid;

         strPid = ::as_string(acmenode()->current_process_identifier());

         strModifier = strDate + "_" + strPid;

         ::file::path pathFolder;

#ifdef ANDROID

         pathFolder = acmesystem()->m_pathCacheDirectory;

#else

         pathFolder = acmedirectory()->roaming();

#endif

         pathFolder /= strAppId;

         pathFolder /= "instance";

         ::file::path path = pathFolder / (strModifier + "_command_line.txt");

         acmefile()->put_contents(path, acmeapplication()->m_strCommandLine);

         ::file::path pathExecutable = acmefile()->module();

         string strAppTitle = acmenode()->executable_title_from_appid(strAppId);

         path = pathFolder / (strModifier + "_executable.txt");

         acmefile()->put_contents(path, pathExecutable);

      }

   }




   ::acme::application * system::get_main_app()
   {


      throw ::interface_only();


      return nullptr;

   }


   ::pointer<::factory::factory> & system::folder_factory()
   {

      if (m_pfactoryFolder)
      {

         return m_pfactoryFolder;

      }

      m_pfactoryFolder = factory("folder", "zip");

      m_pfactoryFolder->merge_to_global_factory();

      return m_pfactoryFolder;

   }


   void system::system_construct(::acme::application * papplication)
   {

      m_pacmeapplication = papplication;

      //m_strAppId = papplication->m_strAppId;

      enum_trace_level etracelevel;

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

      etracelevel = e_trace_level_warning;

#endif

      if (etracelevel > e_trace_level_information)
      {

         for (int i = 0; i < m_psubsystem->get_argument_count1(); i++)
         {

            string strArg = m_psubsystem->get_argument1(i);

            if (strArg == "verbose")
            {

               etracelevel = e_trace_level_information;

               break;

            }

         }

      }

      m_plogger->m_etracelevelMinimum = etracelevel;

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



   void system::os_construct()
   {


   }


#ifdef _DEBUG


   i64 system::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 system::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void system::system_id_update(::i64 iId, ::i64 iPayload)
   {

      call((::enum_id)iId, iPayload);

   }
   void system::handle(::topic * ptopic, ::context * pcontext)
   {


      if (ptopic->m_atom == id_set_dark_mode)
      {

         if (ptopic->payload("wparam").is_true())
         {

            m_pnode->background_color(::color::black);

         }
         else
         {

            m_pnode->background_color(::color::white);

         }

         m_pnano->handle(ptopic, pcontext);

      }
      else if (ptopic->m_atom == id_operating_system_user_theme_change)
      {

         auto pnode = node();

         string strTheme = pnode->os_get_user_theme();

         if (strTheme != m_strOsUserTheme)
         {

            m_strOsUserTheme = strTheme;

         }

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

         if (::is_set(acmeapplication()))
         {

            acmeapplication()->handle(ptopic, pcontext);

         }

      }



   }


   void system::add_handler(::matter * pmatter, bool bPriority)
   {


   }


   void system::add_signal_handler(const ::signal_handler & signalhandler, const ::atom & atomSignal)
   {


   }


   void system::node_will_finish_launching()
   {

      //   auto pnode = node();
      //
      //   pnode->_will_finish_launching();

      //   auto pnode = acmesession()->m_paurasession;
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


   void system::on_open_file(const ::string & pszFile)
   {

      throw ::interface_only();

   }


   void system::new_compress(::compress ** ppcompress, const ::scoped_string & scopedstrImplementation)
   {

      auto pcompress = create < ::compress >("compress", scopedstrImplementation);

      if (!pcompress)
      {

         throw ::exception(error_resource);

      }

      *ppcompress = pcompress;

      pcompress->increment_reference_count();

      //return ::success;

   }


   void system::new_uncompress(::uncompress ** ppuncompress, const ::scoped_string & scopedstrImplementation)
   {

      auto puncompress = create < ::uncompress >("compress", scopedstrImplementation);

      if (!puncompress)
      {

         throw ::exception(error_resource);

      }

      *ppuncompress = puncompress;

      puncompress->increment_reference_count();

      //return puncompress;

   }

   void system::compress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation)
   {

      ::pointer<::compress>pcompress;

      /*auto estatus =*/ new_compress(&pcompress.m_p, scopedstrImplementation);

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


   void system::uncompress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation)
   {

      ::pointer<::uncompress>puncompress;

      /*auto estatus = */ new_uncompress(&puncompress.m_p, scopedstrImplementation);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pfileTarget = acmefile()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);

      auto pfileSource = acmefile()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);

      /*estatus = */ puncompress->transfer(pfileTarget, pfileSource);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   bool system::fast_is_decompressable_folder(const ::file::path & path)
   {

      auto bZip = path.case_insensitive_ends(".zip");

      if (bZip)
      {

         return true;

      }

      return false;

   }




   //pointer< ::sequencer < ::conversation > > system::message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
   //{
   //
   //   auto psequencer = nano()->message_box(strMessage, strTitle, emessagebox, strDetails);
   //
   //   psequencer->do_synchronously();
   //
   //   return psequencer;
   //
   //}

   ::pointer<::acme::application>system::new_app(const ::scoped_string & scopedstrAppId)
   {

      ::pointer<::acme::application>papp;

      string strAppId = scopedstrAppId;

      auto psetup = system_setup::get_first(::system_setup::flag_application, strAppId);

      if (psetup)
      {

         auto pelementApp = psetup->create_application_as_particle();

         papp = pelementApp;

         papp.reset(papp.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

         if (papp)
         {

            strAppId = papp->m_strAppId;

         }

      }

      //#ifndef CUBE

      if (!papp)
      {

         if (strAppId.is_empty() || acmeapplication()->m_bConsole)
         {

            papp = __create < ::acme::application >();

            papp->increment_reference_count();

         }
         else
         {

            string strLibrary = strAppId;

            strLibrary.replace_with("_", "/");

            strLibrary.replace_with("_", "-");

            if (acmeapplication()->m_bVerbose)
            {

               ::information("\n\n::apex::session::get_new_application assembled library path " + strLibrary + "\n\n");

            }

            //auto psystem = acmesystem()->m_papexsystem;

            auto & plibrary = m_psubsystem->library(strLibrary);

            if (!plibrary)
            {

#ifndef UNIVERSAL_WINDOWS

               //            output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", e_message_box_icon_error);

               //output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. ", "ca2", e_message_box_icon_error);

               information("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + "ca2");

#endif

               return nullptr;

            }

            if (acmeapplication()->m_bVerbose)
            {

               ::information("\n\n::apex::session::get_new_application Found library : " + strLibrary + "\n\n");

            }

            // error anticipation is not perfect prediction and may affect results
            // so anticipation may be counter-self-healing
            // specially if what it would avoid on error is exactly we want if successful
            // who doesn't try it, won't taste it neither possibly enjoy it
            //          if (!plibrary->is_opened())
            //          {
            //
            //             ::information("\n\n::apex::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
            //
            //             return nullptr;
            //
            //          }

            if (acmeapplication()->m_bVerbose)
            {

               ::information("\n\n::apex::session::get_new_application Opened library : " + strLibrary + "\n\n");

            }

            ::factory::factory_pointer pfactory;

            plibrary->create_factory(pfactory);

            if (pfactory)
            {

               papp = pfactory->create < ::acme::application >();

               if (!papp)
               {

                  ::information("\n\n::apex::session::get_new_application\n...but this memory_new found library:\n\n   -->  " + strLibrary + "  <--\n\ncannot instantiate application with following AppId:\n\n   -->  " + strAppId + "  <--\n\nIs it missing application factory_item?\n\n\n");

               }

               ::e_status estatus;

               //         if(papp)
               //         {
               //
               //            estatus = papp->initialize(pparticle);
               //
               //         }

               ::information("\n\n\n|(4)----");
               ::information("| app : " + strAppId + "(papp=0x" + ::hex::upper_case_from((uptr)papp.m_p) + ")\n");
               ::information("|\n");
               ::information("|\n");
               ::information("|----");

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
      //      ::information("\n\n\n|(3)----");
      //      ::information("| app : " + strAppId + "\n");
      //      ::information("|\n");
      //      ::information("|\n");
      //      ::information("|----");
      //
      //   }
      //
      //   if (is_verbose())
      //   {
      //
      //      ::information("\n\n\n|(2)----");
      //      ::information("| app : " + strAppId + "\n");
      //      ::information("|\n");
      //      ::information("|\n");
      //      ::information("|----");
      //
      //   }
      //
      //
      //   if (is_verbose())
      //   {
      //
      //      ::information("\n\n\n|(1)----");
      //      ::information("| app : " + strAppId + "\n");
      //      ::information("|\n");
      //      ::information("|\n");
      //      ::information("|----");
      //
      //   }

      papp->m_strAppId = strAppId;

      //if (m_strAppId.is_empty())
      //{

      //   m_strAppId = strAppId;

      //}

      return papp;

   }


   bool system::_handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset)
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


   string system::get_latest_deployment_number(const ::string & strBranch)
   {

      return "(lastest deployed build)";

   }


   void system::windowing_send(const ::procedure & procedure)
   {

      auto pmanualresetevent = __new(manual_reset_event);

      windowing_post([pmanualresetevent, procedure]()
                     {

                        procedure();

                        pmanualresetevent->set_event();

      }

      );

      pmanualresetevent->wait(procedure.m_timeTimeout);

   }


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

   }


   ::string system::implementation_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
   {

      return scopedstrImplementation;

   }


   ::string system::library_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
   {

      return scopedstrComponent + "_" + scopedstrImplementation;

   }


} // namespace acme


//CLASS_DECL_ACME::acme::system * acmesystem()
//{

  // return g_psystem;

//}


//CLASS_DECL_ACME class ::plane_system * get_plane_system()
//{
//
//   return acmesystem();
//
////}
//
//
//CLASS_DECL_ACME string get_latest_deployment_number(const ::string & strBranch)
//{
//
//   return acmesystem()->get_latest_deployment_number(strBranch);
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
//   g_psystem = memory_new ::acme::system();
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


void system_id_update(void * pSystem, ::i64 iUpdate, ::i64 iParam)
{

   auto psystem = (::acme::system *)pSystem;

   psystem->system_id_update(iUpdate, iParam);

}


void node_will_finish_launching(void * pSystem);
void system_on_open_untitled_file(void * pSystem);
void system_on_open_file(void * pSystem, const char * pszFile);


void node_will_finish_launching(void * pSystem)
{

   auto psystem = (::acme::system *)pSystem;

   psystem->node_will_finish_launching();

}


void system_on_open_untitled_file(void * pSystem)
{

   auto psystem = (::acme::system *)pSystem;

   psystem->on_open_untitled_file();

}


void system_on_open_file(void * pSystem, const char * pszFile)
{

   auto psystem = (::acme::system *)pSystem;

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
//         //   ::information("result " + as_string(iDialogResult));
//
//         //}
//
//         //throw ::exception(error_failed, strMessage + "\n\nCould not open required library.");
//
//         ::information("The application library for appid \"" + strAppId + "\" wasn't loaded.");
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

CLASS_DECL_ACME task_pointer fork(::particle * pparticle, const ::procedure & procedure)
{

   return pparticle->acmesystem()->fork(procedure);

}



