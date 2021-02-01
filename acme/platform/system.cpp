#include "framework.h"
#include "acme/id.h"


::acme::system * g_psystem = nullptr;


namespace acme
{


   system::system()
   {

#ifdef LINUX

      m_elinuxdistribution = e_linux_distribution_unknown;

#endif

      m_edesktop = ::user::e_desktop_none;

      os_construct();

      if (g_psystem == nullptr)
      {

         g_psystem = this;

      }

      m_papexsystem = nullptr;
      m_paquasystem = nullptr;
      m_paurasystem = nullptr;
      m_paxissystem = nullptr;
      m_pbasesystem = nullptr;
      m_pcoresystem = nullptr;

   }


   system::~system()
   {

      if (g_psystem == this)
      {

         g_psystem = nullptr;

      }

   }


   ::acme::node * system::node()
   {

      return m_pnode;

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

      return estatus;

   }


   ::e_status system::run_system()
   {

      auto estatus = create_os_node();

      if (!estatus)
      {

         //return estatus;

         estatus = ::success_none;

      }

      estatus = os_application_system_run();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }






   string system::os_get_user_theme()
   {

      return m_strOsUserTheme;

   }


   void system::defer_calc_os_dark_mode()
   {

      ::user::os_calc_dark_mode();

   }


//   void system::defer_calc_os_user_theme()
//   {
//
//      ::user::os_calc_user_theme();
//
//   }


   void system::on_subject(::promise::subject *psubject)
   {

      if (psubject->m_esubject == e_subject_prepare)
      {

         if (psubject->id() == id_os_dark_mode)
         {

            defer_calc_os_dark_mode();

         }
         else if (psubject->id() == id_os_user_theme)
         {

            string strTheme = ::user::_os_get_user_theme();

            if (strTheme != m_strOsUserTheme)
            {

               m_strOsUserTheme = strTheme;

               psubject->m_esubject = e_subject_process;

            }
            else
            {

               psubject->m_esubject = e_subject_not_modified;

            }
         }

      }

      if (psubject->m_esubject == e_subject_process)
      {

         if (psubject->id() == id_os_user_theme)
         {

            ::user::_os_process_user_theme(m_strOsUserTheme);

         }

         psubject->m_esubject = e_subject_deliver;

      }

      ::promise::handler::on_subject(psubject);

   }


   void system::open_profile_link(string strUrl, string strProfile, string strTarget)
   {


   }


   void system::open_link(string strUrl, string strProfile, string strTarget)
   {



   }


   void system::open_url(string strUrl, string strProfile, string strTarget)
   {


   }



   ::e_status system::main_user_async(const ::promise::routine & routine, ::e_priority epriority)
   {

      return ::error_interface_only;

   }


   ::e_status system::main_user_sync(const ::promise::routine & routine, const ::duration & duration, e_priority epriority)
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


   ::task * system::get_task(ithread_t ithread)
   {

      sync_lock sl(&m_mutexTask);

      return m_taskmap[ithread];

   }


   ithread_t system::get_task_id(::task * ptask)
   {

      sync_lock sl(&m_mutexTask);

      ithread_t ithread = NULL_ITHREAD;

      if (!m_taskidmap.lookup(ptask, ithread))
      {

         return 0;

      }

      return ithread;

   }


   void system::set_task(ithread_t ithread, ::task * ptask)
   {

      sync_lock sl(&m_mutexTask);

      m_taskmap[ithread].reset(ptask OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      m_taskidmap[ptask] = ithread;

   }


   void system::unset_task(ithread_t ithread, ::task * ptask)
   {

      sync_lock sl(&m_mutexTask);

#if OBJ_REF_DBG

      m_taskmap[ithread].release(OBJ_REF_DBG_THIS_FUNCTION_LINE);

#endif

      m_taskmap.remove_key(ithread);

      m_taskidmap.remove_key(ptask);

   }


   string system::__get_text(const string & str)
   {

      return str;

   }


   ::e_status system::message_box(const char* pszText, const char* pszTitle, const ::e_message_box & emessagebox , const ::promise::process & process)
   {

      printf("\n%s\n%s", pszTitle, pszText);

      getchar();

      getchar();

      return ::success;

   }


   ::user::enum_desktop system::get_edesktop()
   {

      if (m_edesktop == ::user::e_desktop_none)
      {

         m_edesktop = calc_edesktop();

      }

      return m_edesktop;

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



