#include "framework.h"
#include "acme/id.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/platform/static_start_internal.h"
#include "acme/platform/static_setup.h"
#include "simple_log.h"

//__namespace_object_factory(class ::system, ::static_setup::flag_system)


CLASS_DECL_ACME void trace_category_static_init(class ::system* psystem);
CLASS_DECL_ACME void trace_category_static_term();

class ::system * g_psystem = nullptr;

extern const char8_t  * g_pszTopLevelDomainList[];

enum_dialog_result message_box_for_console(const char * psz, const char * pszTitle, const ::enum_message_box & emessagebox);


//namespace acme
//{


   system::system()
   {

      m_psystem = this;

      trace_category_static_init(this);

      create_factory < simple_log, logger >();
      
      m_bPostedInitialRequest = false;

      //m_bOnInitializeWindowObject = false;

      //m_pcleanuptask = __new(::parallelization::cleanup_task);

      //m_pcleanuptask->begin();
      create_factory<acme::idpool>();

      //m_pacme = nullptr;
      //m_pacmedir = nullptr;
      //m_pacmepath = nullptr;

      m_pacmesystem = this;
      ::object::m_pcontext = this;

      ::factory::get_factory_map()->initialize(this);
   //#ifdef LINUX
   //
   //      m_elinuxdistribution = e_linux_distribution_unknown;
   //
   //#endif

      //m_edesktop = ::user::e_desktop_none;

      os_construct();

      m_psystem = this;

      if (g_psystem == nullptr)
      {

         g_psystem = this;

      }

      //set_os_data(LAYERED_ACME, this);

   }


   system::~system()
   {

      if (g_psystem == this)
      {

         g_psystem = nullptr;

      }

      trace_category_static_term();

      m_pnode->node_quit();

   }


   ::e_status system::on_pre_run_task()
   {

      auto estatus = on_start_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }



   ::e_status system::main()
   {

      auto estatus = process_init();

      if (!estatus)
      {

         return estatus;

      }

      estatus = run();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   //   ::acme::node * system::node()
   //   {
   //
   //      return m_pnode;
   //
   //   }


   ::xml::xml* system::_xml()
   {

      return nullptr;

   }

   
   ::e_status system::create_os_node()
   {

      if(m_pnode)
      {

         return ::success;

      }

      auto estatus = __construct(m_pnode);

      if(!estatus)
      {

         FATAL("Failed to construct node " << estatus);

         return estatus;

      }

      estatus = m_pnode->initialize_matter(this);

      if(!estatus)
      {

         return estatus;

      }

      //::acme::g_pengine;

      return estatus;

   }


   ::e_status system::node_factory_exchange()
   {

      auto estatus = do_factory_exchange("acme", PLATFORM_NAME);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::process_init()
   {

      ::acme::idpool::init(this);

      auto estatus = __defer_construct_new(m_pfactorymapsquare);

      if (!estatus)
      {

         return estatus;

      }

      // auto estatus = do_factory_exchange("acme", PLATFORM_NAME);

      // if (!estatus)
      // {

      //    return estatus;

      // }

      //estatus = __compose(m_pacmenode);

      //if (!m_pacmenode)
      //{

      //   return error_no_memory;

      //}

      estatus = __raw_compose(m_pacmedir);

      if (!estatus)
      {

         return estatus;

      }

   //      m_pacmedir = pacmedir;

   //    m_pacmedir->increment_reference_count();

      estatus = __raw_compose(m_pacmefile);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __raw_compose(m_pacmepath);

      if (!estatus)
      {

         return estatus;

      }

      m_pacmedir->m_pacmefile = m_pacmefile;
      m_pacmedir->m_pacmepath = m_pacmepath;
      m_pacmefile->m_pacmedir = m_pacmedir;
      m_pacmefile->m_pacmepath = m_pacmepath;
      m_pacmepath->m_pacmedir = m_pacmedir;
      m_pacmepath->m_pacmefile = m_pacmefile;

      estatus = m_pacmefile->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pacmepath->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pacmedir->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   //   ::e_status system::start()
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

      ::acme::idpool::term();
      
      //m_pnode->os_post_quit();

   }


   void system::erase_from_any_hook(::matter * pmatter)
   {


   }


   string system::os_get_user_theme()
   {

      return m_strOsUserTheme;

   }




   ::e_status system::open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      return error_interface_only;

   }


   ::e_status system::open_link(string strUrl, string strProfile, string strTarget)
   {

      return error_interface_only;

   }


   ::e_status system::open_url(string strUrl, string strProfile, string strTarget)
   {

      return ::error_interface_only;

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


   //   ::e_status system::main_user_async(const ::routine & routine, ::enum_priority epriority)
   //   {
   //
   //      return ::error_interface_only;
   //
   //   }
   //
   //
   //   ::e_status system::main_user_sync(const ::routine & routine, const ::duration & duration, enum_priority epriority)
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

      synchronous_lock synchronouslock(&m_mutexTask);

      return m_taskmap[itask];

   }


   itask_t system::get_task_id(const ::task * ptask)
   {

      synchronous_lock synchronouslock(&m_mutexTask);

      itask_t itask = null_ithread;

      if (!m_taskidmap.lookup((::task *const ) ptask, itask))
      {

         return 0;

      }

      return itask;

   }


   void system::set_task(itask_t itask, ::task * ptask)
   {

      synchronous_lock synchronouslock(&m_mutexTask);

      m_taskmap[itask].reset(ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      m_taskidmap[ptask] = itask;

   }


   void system::unset_task(itask_t itask, ::task * ptask)
   {

      synchronous_lock synchronouslock(&m_mutexTask);

   #if OBJECT_REFERENCE_COUNT_DEBUG

      m_taskmap[itask].release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);

   #endif

      m_taskmap.erase_key(itask);

      m_taskidmap.erase_key(ptask);

   }


   string system::__get_text(const ::string & str)
   {

      return str;

   }


   //__pointer(::extended::sequence < ::conversation >) system::message_box(::user::interaction * puserinteraction, const ::string & pszText, const ::string & pszTitle, const ::e_message_box & emessagebox)
   //{

   //   auto psequence = __new(::sequence < ::conversation >);

   //   psequence->set_status(error_interface_only);

   //   //return presult;

   //   //auto pprocess = __new(status < enum_dialog_result >);

   //   //pprocess->set_result(message_box_for_console(pszText, pszTitle, emessagebox));

   //   return psequence;

   //}


   //::e_status system::on_initialize_window_object()
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


   //::e_status system::_on_initialize_window_object()
   //{

   //   ::e_status estatus = ::success;
   // 
   //   m_pnode->_os_calc_user_dark_mode();

   //   return estatus;

   //}


   CLASS_DECL_ACME class system * get_system()
   {

      return ::g_psystem;

   }



   bool system::is_task_on(itask_t id)
   {

      synchronous_lock synchronouslock(&m_mutexTaskOn);

      return m_mapTaskOn.plookup(id) != nullptr;

   }


   bool system::is_active(::task * ptask)
   {

      if (::is_null(ptask))
      {

         return false;

      }

      return is_task_on(m_itask);

   }


   void system::set_task_on(itask_t id)
   {

      synchronous_lock synchronouslock(&m_mutexTaskOn);

      m_mapTaskOn.set_at(id, id);

   }


   void system::set_task_off(itask_t id)
   {

      synchronous_lock synchronouslock(&m_mutexTaskOn);

      m_mapTaskOn.erase_key(id);

   }


   task_group * system::task_group(enum enum_priority)
   {

      return nullptr;

   }


   task_tool * system::task_tool(::enum_task_tool etool)
   {

      return nullptr;

   }


   ::e_status system::do_factory_exchange(const ::string & pszComponent, const ::string & pszImplementation)
   {

      string strComponent(pszComponent);

      string strImplementation(pszImplementation);

      ::str::begins_eat_ci(strImplementation, strComponent + "_");

      ::str::begins_eat_ci(strImplementation, strComponent);

      string strLibrary = strComponent + "_" + strImplementation;

   #ifdef CUBE

      auto pfnFactoryExchange = ::static_setup::get_factory_exchange(strLibrary);

      //if (::is_null(pfnFactoryExchange))
      if (::is_null(pfnFactoryExchange))
      {

         return ::error_failed;

      }

//      auto pfnFactoryExchange = m_mapFactoryExchange[strComponent][strImplementation];

      ::factory_map * pfactorymap = ::factory::get_factory_map();

      pfnFactoryExchange(pfactorymap);

      return ::success;

   #else

      auto plibrary = open_containerized_component_library(pszComponent, pszImplementation);

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

      ::factory_map* pfactorymap = ::factory::get_factory_map();

      pfn_factory_exchange(pfactorymap);

      return ::success;

   #endif

   }


   ::e_status system::inline_init()
   {

      auto estatus = init_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::call_init_system()
   {

      auto estatus = init_system();

      if(!estatus)
      {

         FATAL("system init_system has failed " << estatus);

         return estatus;

      }

      return estatus;

   }


   ::e_status system::init_system()
   {

      auto estatus = node_factory_exchange();

      if (!estatus)
      {

         FATAL("node_factory_exchange has failed (status=" << estatus << ")");

         return estatus;

      }

      estatus = create_os_node();

      if (!estatus)
      {

         FATAL("create_os_node has failed " << estatus);

         return estatus;

      }

      //estatus = process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return success;

   }


   ::e_status system::defer_audio()
   {

      return error_interface_only;

   }


   ::e_status system::init1()
   {

      return ::success;

   }


   void system::set_current_handles()
   {


   }


   __pointer(::acme::library) system::open_component_library(const ::string & pszComponent, const ::string & pszImplementation)
   {

      // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      __pointer(::acme::library) plibrary = psystem->m_mapLibrary[pszComponent];

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

         plibrary = __new(::acme::library);

         plibrary->initialize_matter(this);

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


   __pointer(::acme::library) system::open_containerized_component_library(const ::string & pszComponent, const ::string & pszImplementation)
   {

      // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"

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

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexContainerizedLibrary);

      __pointer(::acme::library) plibrary = psystem->m_mapContainerizedLibrary[strComponent][strImplementation];

      if (plibrary && plibrary->is_opened())
      {

         return plibrary;

      }

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

         plibrary = __new(::acme::library);

         plibrary->initialize_matter(this);

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


   ::duration system::get_update_poll_time(const ::id & id)
   {
      
      return 0_s;
      
   }

   
   ::acme::library * system::on_get_library(const ::string & pszLibrary)
   {

      return nullptr;

   }


   ::extended::transport < ::acme::library > system::do_containerized_factory_exchange(const ::string & pszComponent, const ::string & pszImplementation)
   {

      string strComponent(pszComponent);

      string strImplementation(pszImplementation);

      ::str::begins_eat_ci(strImplementation, strComponent + "_");

      ::str::begins_eat_ci(strImplementation, strComponent);

   //#ifdef CUBE

      //auto pfnFactoryExchange = m_mapFactoryExchange[strComponent][strImplementation];

      //if (::is_null(pfnFactoryExchange))
      //{

      //   return ::error_failed;

      //}

#ifdef CUBE

      synchronous_lock synchronouslock(&m_mutexContainerizedLibrary);

      auto & plibrary = m_mapContainerizedLibrary[strComponent][strImplementation];

      if (plibrary && plibrary->is_opened())
      {

         return plibrary;

      }

      string strLibrary = strComponent + "_" + strImplementation;

      auto pfnFactoryExchange = ::static_setup::get_factory_exchange(strLibrary);

      //if (::is_null(pfnFactoryExchange))
      if (::is_null(pfnFactoryExchange))
      {

         return ::error_failed;

      }

      plibrary = __new(::acme::library);

      plibrary->initialize_matter(this);

      __construct_new(plibrary->m_pfactorymap);

      plibrary->m_pfactorymap->initialize_matter(this);

      pfnFactoryExchange(plibrary->m_pfactorymap);

      return plibrary;

   #else

      auto plibrary = open_containerized_component_library(pszComponent, pszImplementation);

      if (!plibrary)
      {

         return ::error_failed;

      }

      string strFunctionName = strComponent + "_" + strImplementation + "_factory_exchange";

      PFN_factory_exchange pfn_factory_exchange = plibrary->get < PFN_factory_exchange >(strFunctionName);

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

      __construct_new(plibrary->m_pfactorymap);

      plibrary->m_pfactorymap->initialize_matter(this);

      pfn_factory_exchange(plibrary->m_pfactorymap);

      return plibrary;

#endif

   }


   void system::check_exit()
   {


   }


   ::regular_expression_pointer system::create_regular_expression(const ::string & pszStyle, const string& str)
   {

      auto pcontext = get_regular_expression_context(pszStyle);

      if(!pcontext)
      {

         return nullptr;

      }

      auto pregularexpression = pcontext->compile(str);

      if(!pregularexpression)
      {

         return nullptr;

      }

      return pregularexpression;

   }


   __pointer(::regular_expression::context) system::get_regular_expression_context(const ::string & pszStyle)
   {

      __defer_construct_new(m_pmapRegularExpressionContext);

      auto & pcontext = (*m_pmapRegularExpressionContext)[pszStyle];

      if(!pcontext)
      {

         auto ptransport = do_containerized_factory_exchange("regular_expression", pszStyle);

         if(!ptransport)
         {

            return nullptr;

         }

         ptransport->__construct(pcontext);

      }

      return pcontext;

   }


   ::regular_expression_pointer system::create_pcre(const string& str)
   {

      return create_regular_expression("pcre2", str);

   }


   __pointer(::regular_expression::context) system::get_pcre_context()
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

   
   ::e_status system::get_public_internet_domain_extension_list(string_array& stra)
   {

   //         ::file::path pathPublicDomainExtensionList = "https://server.ca2.software/public_internet_domain_extension_list.txt";

   //    m_pcontext->m_papexcontext->file().load_lines(stra, pathPublicDomainExtensionList);

      auto psz = g_pszTopLevelDomainList;

      while (*psz != nullptr)
      {

         string str(psz);

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

      for (auto& str : stra)
      {

         FORMATTED_INFORMATION("%s", str);

      }

      return ::success;

   }


   void system::process_exit_status(::object* pobject, const ::e_status& estatus)
   {

      if (estatus == error_exit_system)
      {

         pobject->m_psystem->destroy();

      }

   }


   ::e_status system::on_start_system()
   {

      auto estatus = m_pnode->on_start_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::post_initial_request()
   {

      return ::success;

   }


   ::e_status system::system_main()
   {

      auto estatus = init_system();

      if(!estatus)
      {

         return estatus;

      }

      estatus = m_pnode->system_main();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }



   //::application* system::get_main_application()
   //{

   //   throw ::interface_only_exception();

   //   return nullptr;

   //}


   //void system::system_construct(int argc, char** argv, char** envp)
   //{

   //   throw ::interface_only_exception();

   //}


   //void system::system_construct(int argc, wchar_t** argv, wchar_t** envp)
   //{

   //   throw ::interface_only_exception();

   //}

   //
   //   ::e_status system::inline_init()
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
   ::e_status system::inline_term()
   {

      return ::success;

   }


   //   ::e_status system::on_start_system()
   //   {
   //
   //      return ::success;
   //
   //   }
   //
   //
   ::e_status system::on_end()
   {

      return ::success;

   }

   ::e_status system::end()
   {

      auto estatus = on_end();

      if (!estatus)
      {

         return estatus;

      }

      estatus = inline_term();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::application* system::get_main_application()
   {


      throw ::interface_only_exception();


      return nullptr;

   }


   void system::system_construct(main_arguments & mainarguments)
   {

      acme_main_data::system_construct(mainarguments);

      set_current_handles();

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


   ::e_status system::node_will_finish_launching()
   {

      auto pnode = node();
      
      pnode->_will_finish_launching();
      
      return ::success;
      
   }


   ::e_status system::on_open_untitled_file()
   {
      
      if(!m_bPostedInitialRequest)
      {
         
         post_initial_request();
         
      }
      
//      throw ::interface_only_exception();
   
      return error_interface_only;
   
   }


   ::e_status system::on_open_file(const ::string & pszFile)
   {
      
      throw ::interface_only_exception();
   
      return error_interface_only;
      
   }


//} // namespace acme


string __get_text(const string& str)
{

   return ::g_psystem->__get_text(str);

}


CLASS_DECL_ACME class ::system* get_context_system()
{

   return g_psystem;

}


CLASS_DECL_ACME class ::system * acme_system_init()
{

   g_psystem = new class ::system();

   return g_psystem;

}


CLASS_DECL_ACME void acme_system_term()
{

   ::acme::del(g_psystem);

}


void system_id_update(void * pSystem, ::i64 iUpdate, ::i64 iParam)
{
   
   auto psystem = (class ::system *) pSystem;
   
   psystem->system_id_update(iUpdate, iParam);
   
}


void node_will_finish_launching(void * pSystem);
void system_on_open_untitled_file(void * pSystem);
void system_on_open_file(void * pSystem, const char * pszFile);


void node_will_finish_launching(void * pSystem)
{

   auto psystem = (class ::system *) pSystem;
   
   psystem->node_will_finish_launching();

}


void system_on_open_untitled_file(void * pSystem)
{

   auto psystem = (class ::system *) pSystem;
   
   psystem->on_open_untitled_file();

}


void system_on_open_file(void * pSystem, const char * pszFile)
{

   auto psystem = (class ::system *) pSystem;
   
   psystem->on_open_file(pszFile);


}


__pointer(class ::system) platform_create_system(const char* pszAppId)
{

   string strAppId(pszAppId);

#if !defined(CUBE)

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

         //{

         //   //auto pfuture = __sync_future();

         //   //message_box(strMessage, "Could not open required library. Want to give an yes/no answer insted of pression cancel?", e_message_box_icon_exclamation | e_message_box_yes_no_cancel, pfuture);

         //   //pfuture->wait(10_s);

         //   int iDialogResult = pfuture->m_var;

         //   ::output_debug_string("result " + __string(iDialogResult));

         //}

         //__throw(error_failed, strMessage + "\n\nCould not open required library.");

         ::output_debug_string("The application library for appid \"" + strAppId + "\" wasn't loaded.");

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

   auto psystem = dynamic_cast<class ::system*>(pobject);

   if (!psystem)
   {

      delete pobject;

      return nullptr;

   }

   psystem->m_strAppId = strAppId;

   return ::move_transfer(psystem);

}





