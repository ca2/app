#include "framework.h"
#include "library.h"
#include "node.h"
#include "acme.h"
#include "system_setup.h"
#include "system.h"
#include "sequencer.h"
#include "application.h"
#include "log.h"
#include "acme/compress/compress.h"
#include "acme/compress/uncompress.h"
#include "acme/constant/id.h"
#include "acme/constant/idpool.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/file/transfer.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/translator.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/regular_expression/context.h"
#include "acme/primitive/datetime/datetime.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/string/hex.h"
#include "acme/user/nano/nano.h"
#include "acme/user/user/conversation.h"


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);
CLASS_DECL_ACME void trace_category_static_init(::acme::system * psystem);
CLASS_DECL_ACME void trace_category_static_term();


static ::acme::system * g_psystem = nullptr;


extern const char * g_pszTopLevelDomainList[];


enum_dialog_result message_box_for_console(const char * psz, const char * pszTitle, const ::enum_message_box & emessagebox);





namespace acme
{


   system::system()
   {

      m_psubsystem = ::acme::acme::g_p->m_psubsystem;

      m_psubsystem->m_pcontext = this;

#ifdef PARALLELIZATION_PTHREAD
#if defined(__APPLE__)
      m_bJoinable = true;
#endif
#endif

      m_pcontext = this;

      m_pacmesystem = this;

      m_ewindowing = e_windowing_none;

      m_etracelevel = e_trace_level_information;

      trace_category_static_init(this);


      __defer_construct_new(m_pmemorycounter);

      //____creatable_from_base(simple_log, logger);

      //____creatable(task);

      m_bPostedInitialRequest = false;

      //m_bOnInitializeWindowObject = false;

      //m_pcleanuptask = __new(::parallelization::cleanup_task);

      //m_pcleanuptask->begin();
      //::factory::add_factory_item<::acme::idpool>();

      //m_pacme = nullptr;
      //m_pacmedirectory = nullptr;
      //m_pacmepath = nullptr;

      ::factory::get_factory()->initialize(this);

      //#ifdef LINUX
      //
      //      m_elinuxdistribution = e_linux_distribution_unknown;
      //
      //#endif

         //m_edesktop = ::user::e_desktop_none;

      os_construct();

      //acmesystem() = this;

      if (g_psystem == nullptr)
      {

         g_psystem = this;

      }


      __construct_new(m_pnano);

      //m_psystemimpl = memory_new system_impl;

      //set_os_data(LAYERED_ACME, this);

      

   }


   system::~system()
   {

      if (g_psystem == this)
      {

         g_psystem = nullptr;

      }

      trace_category_static_term();

      //m_mapLibrary4.clear();

      //::acme::del(m_psystemimpl);

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

         //FATAL("node_factory has failed (status=" << (const void &) pfactory << ")");

         throw ::exception(error_resource);

      }


#if !defined(WINDOWS)
      

      __construct(m_pexceptiontranslator);
      

      m_pexceptiontranslator->attach();

      
#endif


      //auto estatus = __construct(m_pnode);
      __construct(m_pnode);

      //if(!estatus)
      //{

      //   FATAL("Failed to construct node " << estatus);

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


   ::pointer<::factory::factory>& system::node_factory()
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

      //   ::acme::acme::g_p->factory_close();

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


   //void system::__tracea(enum_trace_level elevel, const char* pszFunction, const char* pszFile, int iLine, const char* psz) const
   //{

   //   if (!m_ptracelog)
   //   {

   //      ::output_debug_string(psz);

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
   //   void system::main_user_sync(const ::procedure & procedure, const ::duration & duration, enum_priority epriority)
   //   {
   //
   //      auto proutine = ___sync_routine(routine);
   //
   //      main_user_async(proutine, epriority);
   //
   //      auto waitresult = proutine->wait(duration);
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

      m_taskmap.erase_key(itask);

      m_taskidmap.erase_key(ptask);

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


   //CLASS_DECL_ACME class system * get_system()
   //{
   //
   //   return ::g_psystem;
   //
   //}
   //


   bool system::is_task_on(itask_t atom)
   {

      synchronous_lock synchronouslock(m_pmutexTaskOn);

      return m_mapTaskOn.plookup(atom) != nullptr;

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

      m_mapTaskOn.erase_key(atom);

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

         g_psystem->m_pnode->report_exception_to_user(this, exception, strMoreDetails);

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

      //m_pacmeapplicationStartup = pappStartup;

      m_pacmeapplicationStartup->initialize(this);

      m_pacmeapplicationStartup->get_property_set().merge(get_property_set());

      copy_main(*m_pacmeapplicationStartup);

      process_init();

      init1();

      init2();

      //   auto & pfactory = node_factory();
      //
      //   if (!pfactory)
      //   {
      //
      //      //FATAL("node_factory has failed (status=" << (const void &) pfactory << ")");
      //
      //      throw ::exception(error_resource);
      //
      //   }
      //
      //   //auto estatus = create_os_node();
      //   create_os_node();

         //if (!estatus)
         //{

         //   FATAL("create_os_node has failed " << estatus);

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

      //return ::success;

   }


   void system::set_current_handles()
   {


   }


   ::pointer<::acme::library>system::create_library(const ::string & strLibrary)
   {

#ifdef CUBE

      auto plibraryfactory = ::system_setup::get_first(::system_setup::flag_library, strLibrary);

      if (!plibraryfactory)
      {

         return nullptr;

      }

      auto plibrary = plibraryfactory->create_library();

#else

      auto plibrary = __create_new < ::acme::library >();

      //plibrary->initialize_matter(this);

      //auto estatus = plibrary->open(strLibrary);

      INFORMATION("system::create_library Going to open library \"" << strLibrary << "\".");

      plibrary->open(strLibrary);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      if (!plibrary->is_opened())
      {

         string strMessage = plibrary->m_strMessage;

         INFORMATION("Library wasn't opened (\"" << strLibrary << "\") : " << strMessage);

         throw ::exception(error_failed, "Library wasn't opened (\"" + strLibrary + "\")", strMessage);

      }

#endif

      return plibrary;

   }


   ::pointer<::acme::library>& system::library(const ::string & str)
   {

      // Ex. "audio" (library)

      if (str.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      critical_section_lock synchronouslock(&m_psubsystem->m_criticalsection);

      string strLibrary = library_filter(str);

      auto & plibrary = m_psubsystem->m_mapLibrary[strLibrary];

      if (plibrary)
      {

         return plibrary;

      }

      plibrary = create_library(strLibrary);

      return plibrary;

   }


   //::pointer<::acme::library> system::library(const ::string& strComponent, const ::string& strImplementationParam)
   //{

   //   string strImplementation(strImplementationParam);

   //   strImplementation.begins_eat_ci(strComponent + "_");

   //   string strLibrary;

   //   strLibrary = strComponent + "_" + strImplementation;

   //   auto& plibrary = library(strLibrary);

   //   if (!plibrary)
   //   {

   //      return plibrary;

   //   }

   //   return plibrary;

   //}


   ::pointer<::factory::factory>& system::factory(const ::string & strComponent, const ::string & strImplementation)
   {
      
      critical_section_lock synchronouslock(&m_psubsystem->m_criticalsection);
      
      auto & pfactory = (*m_psubsystem->m_pmapComponentFactory)[strComponent][implementation_name(strComponent, strImplementation)];
      
      if (pfactory)
      {
         
         return pfactory;
         
      }
      
      string strLibrary;
      
      strLibrary = library_name(strComponent, strImplementation);
      
      auto & plibrary = library(strLibrary);
      
      if (!plibrary)
      {
         
#ifdef CUBE
         
         auto pfnFactory = ::system_setup::get_factory_function(strLibrary);
         
         if (pfnFactory)
         {
            
            pfactory = acmesystem()->__create_new < ::factory::factory >();
            
            pfnFactory(pfactory);
            
            return pfactory;
            
         }
         
#endif
         
         //pfactory = (const ::extended::status&)plibrary;
         throw ::exception(error_resource, strComponent + "_" + strImplementation + "_factory not found!!");
         
      }
      
      pfactory = plibrary->create_factory();
      
      return pfactory;
         
   }


   ::pointer<::factory::factory>& system::impact_factory(const ::string & strComponent, const ::string & strImplementation)
   {
      
      critical_section_lock synchronouslock(&m_psubsystem->m_criticalsection);
      
      auto & pfactory = (*m_psubsystem->m_pmapComponentFactory)[strComponent][implementation_name(strComponent, strImplementation)];
      
      try
      {
         
         return factory(strComponent, strImplementation);
         
      }
      catch(const ::exception & exception)
      {
         
         string strMessage = "Library couldn't be opened : " + exception.m_strMessage;
         
         string strDetails = exception.get_consolidated_details();
         
         auto psequencer = nano()->message_box_sequencer(strMessage, "Library Loading Failure", e_message_box_ok | e_message_box_icon_warning,
                                                        strDetails);
         
         psequencer->do_asynchronously();
         
         throw exception;
         
      }
      
      return pfactory;
      
   }


   ::pointer<::factory::factory>& system::factory(const ::string & strLibraryRequest)
   {

      critical_section_lock synchronouslock(&m_psubsystem->m_criticalsection);

      string strLibrary;

      strLibrary = library_filter(strLibraryRequest);

      auto & pfactory = (*m_psubsystem->m_pmapFactory)[strLibrary];

      if (pfactory)
      {

         return pfactory;

      }

      INFORMATION("system::factory Going to get library \"" << strLibrary << "\".");

      auto & plibrary = library(strLibrary);

      if (!plibrary)
      {

#ifdef CUBE

         auto pfnFactory = ::system_setup::get_factory_function(strLibrary);

         if (!pfnFactory)
         {

            throw ::exception(error_resource);


         }

         plibrary = acmesystem()->__create_new < ::acme::library >();

         plibrary->m_strName = strLibrary;

         plibrary->m_pfnFactory = pfnFactory;

#endif

      }

      INFORMATION("system::factory Going to create factory from library \"" << strLibrary << "\".");

      pfactory = plibrary->create_factory();

      if (!pfactory)
      {

         return pfactory;

      }

      return pfactory;

   }


   //::pointer<::acme::library>& system::library(const ::string & strComponent, const ::string & strImplementation)
   //{

   //   // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"

   //   if (strComponent.is_empty() || strImplementation.is_empty())
   //   {

   //      throw error_bad_argument;

   //   }

   //   auto psystem = get_system();

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

   //   strImplementation.begins_eat_ci(strComponent + "_");

   //   strImplementation.begins_eat_ci(strComponent);

   //   auto psystem = get_system();

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


   ::duration system::get_update_poll_time(const ::atom & atom)
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
   //      strImplementation.begins_eat_ci(strComponent + "_");
   //
   //      strImplementation.begins_eat_ci(strComponent);
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


   void system::get_public_internet_domain_extension_list(string_array & stra)
   {

      //         ::file::path pathPublicDomainExtensionList = "https://server.ca2.software/public_internet_domain_extension_list.txt";

      //    file()->load_lines(stra, pathPublicDomainExtensionList);

      auto psz = g_pszTopLevelDomainList;

      while (*psz != nullptr)
      {

         string str(*psz);

         auto iStart = str.find('(');

         if (iStart < 0)
         {

            stra.add(str);

            continue;

         }

         auto iEnd = str.find(')', iStart + 1);

         if (iEnd < 0)
         {

            string strItem = str.Left(iStart);

            stra.add(strItem);

            continue;

         }

         string strItem = str.Mid(iStart, iEnd - iStart - 1);

         stra.add(strItem);

      }

      stra.trim();

      stra.erase_empty();

      INFORMATION("acme::system::get_public_internet_domain_extension_list");

      for (auto & str : stra)
      {

         FORMATTED_INFORMATION("%s", str.c_str());

      }

      //return ::success;

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


   void system::post_initial_request()
   {

      //return ::success;

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

   }


   void system::report_system_instance()
   {

      string strAppId = m_strAppId;

      if (strAppId.has_char())
      {

         string strModifier;

         string strDate;

         strDate = datetime()->international().get_date_time_for_file_with_no_spaces();

         string strPid;

         strPid = ::as_string(acmenode()->get_current_process_id());

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

         acmefile()->put_contents(path, m_strCommandLine);

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


   void system::system_construct(::acme::application * papplication)
   {

      m_pacmeapplicationStartup = papplication;

      m_strAppId = papplication->m_strAppId;

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

      m_etracelevel = etracelevel;

      /*auto estatus = */ ::main::system_construct(papplication);

      /*  if (!estatus)
      {

         return estatus;

      }

      return estatus;*/

      if (m_pacmeapplicationStartup)
      {

         m_pacmeapplicationStartup->m_pacmesystem = this;

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


   }


   void system::add_handler(::matter * pmatter, bool bPriority)
   {


   }


   void system::add_signal_handler(const ::signal_handler& signalhandler, const ::atom & atomSignal)
   {


   }


   void system::node_will_finish_launching()
   {

      //   auto pnode = node();
      //      
      //   pnode->_will_finish_launching();

      //   auto pnode = get_session()->m_paurasession;
      //
      //   auto puser = psession->user();
      //
      //   auto pwindowing = puser->windowing1();
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

         post_initial_request();

      }

      //      throw ::interface_only();

         //throw ::interface_only();

   }


   void system::on_open_file(const ::string & pszFile)
   {

      throw ::interface_only();

   }


   void system::new_compress(::compress ** ppcompress, const char * pszImplementation)
   {

      auto pcompress = create < ::compress >("compress", pszImplementation);

      if (!pcompress)
      {

         throw ::exception(error_resource);

      }

      *ppcompress = pcompress;

      pcompress->increment_reference_count();

      //return ::success;

   }


   void system::new_uncompress(::uncompress ** ppuncompress, const char * pszImplementation)
   {

      auto puncompress = create < ::uncompress >("compress", pszImplementation);

      if (!puncompress)
      {

         throw ::exception(error_resource);

      }

      *ppuncompress = puncompress;

      puncompress->increment_reference_count();

      //return puncompress;

   }

   void system::compress(::file::file * pfileOut, ::file::file * pfileIn, const char * pszImplementation)
   {

      ::pointer<::compress>pcompress;

      /*auto estatus =*/ new_compress(&pcompress.m_p, pszImplementation);

      /*  if (!estatus)
      {

         return estatus;

      }*/

      /*estatus = */ pcompress->transfer(pfileOut, pfileIn);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::uncompress(::file::file * pfileOut, ::file::file * pfileIn, const char * pszImplementation)
   {

      ::pointer<::uncompress>puncompress;

      /*auto estatus = */ new_uncompress(&puncompress.m_p, pszImplementation);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      /*estatus =*/ puncompress->transfer(pfileOut, pfileIn);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   bool system::fast_is_decompressable_folder(const ::file::path & path)
   {

      auto bZip = path.ends_ci(".zip");

      if (bZip)
      {

         return true;

      }

      return false;

   }




   //pointer< ::sequencer < ::conversation > > system::message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
   //{
   //
   //   auto psequencer = nano()->message_box_sequencer(strMessage, strTitle, emessagebox, strDetails);
   //
   //   psequencer->do_synchronously();
   //
   //   return psequencer;
   //
   //}

   ::pointer<::acme::application>system::new_app(const char * pszAppId)
   {

      ::pointer<::acme::application>papp;

      string strAppId = pszAppId;

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

         if (strAppId.is_empty() || m_bConsole)
         {

            papp = __create < ::acme::application >();

            papp->increment_reference_count();

         }
         else
         {

            string strLibrary = strAppId;

            strLibrary.replace_with("_", "/");

            strLibrary.replace_with("_", "-");

            if (is_verbose())
            {

               ::output_debug_string("\n\n::apex::session::get_new_application assembled library path " + strLibrary + "\n\n");

            }

            //auto psystem = get_system()->m_papexsystem;

            auto psystem = get_system();

            auto & plibrary = psystem->library(strLibrary);

            if (!plibrary)
            {

#ifndef _UWP

               //            output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", e_message_box_icon_error);

                           //output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. ", "ca2", e_message_box_icon_error);

               output_debug_string("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + "ca2");

#endif

               return nullptr;

            }

            if (is_verbose())
            {

               ::output_debug_string("\n\n::apex::session::get_new_application Found library : " + strLibrary + "\n\n");

            }

            // error anticipation is not perfect prediction and may affect results
            // so anticipation may be counter-self-healing
            // specially if what it would avoid on error is exactly we want if successful
            // who doesn't try it, won't taste it neither possibly enjoy it
            //          if (!plibrary->is_opened())
            //          {
            //
            //             ::output_debug_string("\n\n::apex::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
            //
            //             return nullptr;
            //
            //          }

            if (is_verbose())
            {

               ::output_debug_string("\n\n::apex::session::get_new_application Opened library : " + strLibrary + "\n\n");

            }

            auto pfactory = plibrary->create_factory();

            if (pfactory)
            {

               papp = pfactory->create < ::acme::application >();

               if (!papp)
               {

                  ::output_debug_string("\n\n::apex::session::get_new_application\n...but this memory_new found library:\n\n   -->  " + strLibrary + "  <--\n\ncannot instantiate application with following AppId:\n\n   -->  " + strAppId + "  <--\n\nIs it missing application factory_item?\n\n\n");

               }

               ::e_status estatus;

               //         if(papp)
               //         {
               //
               //            estatus = papp->initialize(pparticle);
               //
               //         }

               ::output_debug_string("\n\n\n|(4)----");
               ::output_debug_string("| app : " + strAppId + "(papp=0x" + ::hex::upper_from((uptr)papp.m_p) + ")\n");
               ::output_debug_string("|\n");
               ::output_debug_string("|\n");
               ::output_debug_string("|----");

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
      //      ::output_debug_string("\n\n\n|(3)----");
      //      ::output_debug_string("| app : " + strAppId + "\n");
      //      ::output_debug_string("|\n");
      //      ::output_debug_string("|\n");
      //      ::output_debug_string("|----");
      //
      //   }
      //
      //   if (is_verbose())
      //   {
      //
      //      ::output_debug_string("\n\n\n|(2)----");
      //      ::output_debug_string("| app : " + strAppId + "\n");
      //      ::output_debug_string("|\n");
      //      ::output_debug_string("|\n");
      //      ::output_debug_string("|----");
      //
      //   }
      //
      //
      //   if (is_verbose())
      //   {
      //
      //      ::output_debug_string("\n\n\n|(1)----");
      //      ::output_debug_string("| app : " + strAppId + "\n");
      //      ::output_debug_string("|\n");
      //      ::output_debug_string("|\n");
      //      ::output_debug_string("|----");
      //
      //   }

      papp->m_strAppId = strAppId;

      if (m_strAppId.is_empty())
      {

         m_strAppId = strAppId;

      }

      return papp;

   }


   bool system::_handle_call(::payload & payload, const ::block & blockObject, const ::block & blockMember, ::property_set & propertyset)
   {
      
      try
      {

         bool bOk = false;

         if (m_pacmeapplicationMain)
         {

            if (m_pacmeapplicationMain->_handle_call(payload, blockObject, blockMember, propertyset))
            {

               return true;

            }

         }
         else if (m_pacmeapplicationStartup)
         {

            if (m_pacmeapplicationStartup->_handle_call(payload, blockObject, blockMember, propertyset))
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

      pmanualresetevent->wait(procedure.m_waitTimeout);

   }


   void system::destroy()
   {

#if !defined(WINDOWS)

      m_pexceptiontranslator->detach();

      m_pexceptiontranslator->destroy();

      m_pexceptiontranslator.release();

#endif

      ::acme::context::destroy();

      ::task::destroy();

   }


} // namespace acme


CLASS_DECL_ACME::acme::system * get_system()
{

   return g_psystem;

}


CLASS_DECL_ACME class ::plane_system * get_plane_system()
{

   return get_system();

}


CLASS_DECL_ACME string get_latest_deployment_number(const ::string & strBranch)
{

   return get_system()->get_latest_deployment_number(strBranch);

}





CLASS_DECL_ACME string __get_text(const string & str)
{

   return ::g_psystem->__get_text(str);

}


CLASS_DECL_ACME::acme::system * get_context_system()
{

   return g_psystem;

}


CLASS_DECL_ACME::acme::system * acme_system_init()
{

   g_psystem = memory_new ::acme::system();

   return g_psystem;

}


CLASS_DECL_ACME void acme_system_term()
{

   ::acme::del(g_psystem);

}


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


::pointer<::acme::system>platform_create_system(const char * pszAppId)
{

   string strAppId(pszAppId);

#if !defined(CUBE)

   if (strAppId.has_char())
   {

      string strMessage;

      string strLibrary = strAppId;

      strLibrary.replace_with("_", "/");

      strLibrary.replace_with("_", "-");

      strLibrary.replace_with("_", ".");

      auto plibrary = __node_library_open(strLibrary, strMessage);

      if (!plibrary)
      {

         //{

         //   //auto pfuture = __sync_future();

         //   //message_box(strMessage, "Could not open required library. Want to give an yes/no answer insted of pression cancel?", e_message_box_icon_exclamation | e_message_box_yes_no_cancel, pfuture);

         //   //pfuture->wait(10_s);

         //   int iDialogResult = pfuture->m_var;

         //   ::output_debug_string("result " + as_string(iDialogResult));

         //}

         //throw ::exception(error_failed, strMessage + "\n\nCould not open required library.");

         ::output_debug_string("The application library for appid \"" + strAppId + "\" wasn't loaded.");

      }

   }

#endif

   auto pstaticsetup = ::system_setup::get_first(::system_setup::flag_system, "");

   if (!pstaticsetup)
   {

      return nullptr;

   }

   auto pelement = pstaticsetup->create_particle();

   if (!pelement)
   {

      return nullptr;

   }

   ::pointer<::acme::system>psystem = pelement;

   if (!psystem)
   {

      return nullptr;

   }

   //psystem->m_strAppId = strAppId;

   return ::move(psystem);

}


CLASS_DECL_ACME task_pointer fork(::particle * pparticle, const ::procedure & procedure)
{

   return pparticle->acmesystem()->fork(procedure);

}



