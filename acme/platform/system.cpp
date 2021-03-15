#include "framework.h"
#include "acme/id.h"


::acme::system * g_psystem = nullptr;


enum_dialog_result message_box_for_console(const char * psz, const char * pszTitle, const ::e_message_box & emessagebox);


namespace acme
{


   system::system()
   {

      m_psystem = this;

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

         return estatus;

      }

      estatus = m_pnode->initialize_matter(this);

      if(!estatus)
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

      synchronization_lock synchronizationlock(&m_mutexTask);

      return m_taskmap[itask];

   }


   itask_t system::get_task_id(const ::task * ptask)
   {

      synchronization_lock synchronizationlock(&m_mutexTask);

      itask_t itask = null_ithread;

      if (!m_taskidmap.lookup((::task *const ) ptask, itask))
      {

         return 0;

      }

      return itask;

   }


   void system::set_task(itask_t itask, ::task * ptask)
   {

      synchronization_lock synchronizationlock(&m_mutexTask);

      m_taskmap[itask].reset(ptask OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      m_taskidmap[ptask] = itask;

   }


   void system::unset_task(itask_t itask, ::task * ptask)
   {

      synchronization_lock synchronizationlock(&m_mutexTask);

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


   __pointer(::extended::future < ::conversation >) system::_message_box(::context_object* pcontextobject, const char* pszText, const char* pszTitle, const ::e_message_box & emessagebox)
   {

      auto presult = __new(::future < ::conversation >);

      presult->set_status(error_interface_only);

      //return presult;

      //auto pprocess = __new(status < enum_dialog_result >);

      //pprocess->set_result(message_box_for_console(pszText, pszTitle, emessagebox));

      return presult;

   }


} // namespace acme


string __get_text(const string & str)
{

   return ::g_psystem->__get_text(str);

}


CLASS_DECL_ACME ::acme::system * get_context_system()
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


namespace acme
{


   CLASS_DECL_ACME system * get_system()
   {

      return ::g_psystem;

   }



   bool system::is_task_on(itask_t id)
   {

      synchronization_lock synchronizationlock(&m_mutexTaskOn);

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

      synchronization_lock synchronizationlock(&m_mutexTaskOn);

      m_mapTaskOn.set_at(id, id);

   }


   void system::set_task_off(itask_t id)
   {

      synchronization_lock synchronizationlock(&m_mutexTaskOn);

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


} // namespace acme



