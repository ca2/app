#include "framework.h"
#include "acme/id.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_path.h"


::acme::system * g_psystem = nullptr;


enum_dialog_result message_box_for_console(const char * psz, const char * pszTitle, const ::e_message_box & emessagebox);


namespace acme
{


   system::system()
   {

      m_pcleanuptask = __new(::parallelization::cleanup_task);

      m_pcleanuptask->begin();

      m_psystem = this;

      //m_pacme = nullptr;
      //m_pacmedir = nullptr;
      //m_pacmepath = nullptr;

      m_pacmesystem = this;
      ::object::m_pcontext = this;


#ifdef LINUX

      m_elinuxdistribution = e_linux_distribution_unknown;

#endif

      m_edesktop = ::user::e_desktop_none;

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

   }


   ::e_status system::main()
   {

      auto estatus = run();

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

      auto estatus = __compose(m_pnode);

      if(!estatus)
      {

         return estatus;

      }

      estatus = m_pnode->initialize_matter(this);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::process_init()
   {

      m_pfactorymapsquare = new string_map < __pointer(::factory_map) >();

      if (!m_pfactorymapsquare)
      {

         return ::success;

      }

      auto estatus = do_factory_exchange("acme", "windows");

      if (!estatus)
      {

         return estatus;

      }

      //estatus = __compose(m_pacmenode);

      //if (!m_pacmenode)
      //{

      //   return error_no_memory;

      //}

      estatus = __compose(m_pacmedir);

      if (!estatus)
      {

         return estatus;

      }

//      m_pacmedir = pacmedir;

  //    m_pacmedir->add_ref();

      estatus = __compose(m_pacmepath);

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


   string system::os_get_user_theme()
   {

      return m_strOsUserTheme;

   }


   ::user::enum_desktop system::get_edesktop()
   {

      if (m_edesktop == ::user::e_desktop_none)
      {

         m_edesktop = calc_edesktop();

      }

      return m_edesktop;

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


   ::e_status system::main_user_async(const ::routine & routine, ::e_priority epriority)
   {

      return ::error_interface_only;

   }


   ::e_status system::main_user_sync(const ::routine & routine, const ::duration & duration, e_priority epriority)
   {

      auto proutine = ___sync_routine(routine);

      main_user_async(proutine, epriority);

      auto waitresult = proutine->wait(duration);

      if (!waitresult.succeeded())
      {

         return ::error_timeout;

      }

      return proutine->m_estatus;

   }


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

      m_taskmap[itask].reset(ptask OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      m_taskidmap[ptask] = itask;

   }


   void system::unset_task(itask_t itask, ::task * ptask)
   {

      synchronous_lock synchronouslock(&m_mutexTask);

#if OBJ_REF_DBG

      m_taskmap[itask].release(OBJ_REF_DBG_THIS_FUNCTION_LINE);

#endif

      m_taskmap.remove_key(itask);

      m_taskidmap.remove_key(ptask);

   }


   string system::__get_text(const string & str)
   {

      return str;

   }


   __pointer(::extended::future < ::conversation >) system::_message_box(::object* pobject, const char* pszText, const char* pszTitle, const ::e_message_box & emessagebox)
   {

      auto presult = __new(::future < ::conversation >);

      presult->set_status(error_interface_only);

      //return presult;

      //auto pprocess = __new(status < enum_dialog_result >);

      //pprocess->set_result(message_box_for_console(pszText, pszTitle, emessagebox));

      return presult;

   }


   CLASS_DECL_ACME system * get_system()
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

      m_mapTaskOn.remove_key(id);

   }


   task_group * system::task_group(enum e_priority)
   {

      return nullptr;

   }


   task_tool * system::task_tool(::enum_task_tool etool)
   {

      return nullptr;

   }


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


   ::e_status system::init_system()
   {

      auto estatus = create_os_node();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::e_status system::init1()
   {

      return ::success;

   }


   __pointer(::acme::library) system::open_component_library(const char* pszComponent, const char* pszImplementation)
   {

      // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"

      __pointer(::acme::system) psystem = get_system();

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


   __pointer(::acme::library) system::open_containerized_component_library(const char* pszComponent, const char* pszImplementation)
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

      __pointer(::acme::system) psystem = get_system();

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

   
   ::acme::library * system::on_get_library(const char * pszLibrary)
   {

      return nullptr;

   }


   ::extended::transport < ::acme::library > system::do_containerized_factory_exchange(const char* pszComponent, const char* pszImplementation)
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

      ::__construct_new(plibrary->m_pfactorymap);

      plibrary->m_pfactorymap->initialize_matter(this);

      pfn_factory_exchange(plibrary->m_pfactorymap);

#endif

      return plibrary;

   }


   void system::check_exit()
   {


   }


} // namespace acme






string __get_text(const string& str)
{

   return ::g_psystem->__get_text(str);

}


CLASS_DECL_ACME::acme::system* get_context_system()
{

   return g_psystem;

}


CLASS_DECL_ACME void acme_system_init()
{

   g_psystem = new acme::system();

}


CLASS_DECL_ACME void acme_system_term()
{

   ::acme::del(g_psystem);

}


