#include "framework.h"
#include "acme/id.h"


::acme::system * g_psystem = nullptr;

namespace acme
{

   system::system()
   {


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


   void system::defer_calc_os_dark_mode()
   {

#ifdef LINUX

      ::user::os_calc_dark_mode();

#elif defined(WINDOWS_DESKTOP)

      ::user::os_calc_dark_mode();

      //::user::set_system_dark_mode(::user::calc_system_dark_mode());

      //::user::set_app_dark_mode(::user::calc_app_dark_mode());

#endif

   }


   void system::on_apply(::action * paction)
   {

      if(paction->id() == id_dark_mode)
      {

         defer_calc_os_dark_mode();

      }

   }


   ::task * system::get_task(ITHREAD ithread)
   {

      sync_lock sl(&m_mutexTask);

      return m_taskmap[ithread];

   }


   ITHREAD system::get_task_id(::task * ptask)
   {

      sync_lock sl(&m_mutexTask);

      ITHREAD ithread = NULL_ITHREAD;

      if (!m_taskidmap.lookup(ptask, ithread))
      {

         return 0;

      }

      return ithread;

   }


   void system::set_task(ITHREAD ithread, ::task * ptask)
   {

      sync_lock sl(&m_mutexTask);

      m_taskmap[ithread].reset(ptask OBJ_REF_DBG_COMMA_P_NOTE(this, "thread::thread_set"));

      m_taskidmap[ptask] = ithread;

   }


   void system::unset_task(ITHREAD ithread, ::task * ptask)
   {

      sync_lock sl(&m_mutexTask);

#if OBJ_REF_DBG

      m_taskmap[ithread].release(this);

#endif

      m_taskmap.remove_key(ithread);

      m_taskidmap.remove_key(ptask);

   }


} // namespace acme





CLASS_DECL_ACME ::acme::system * get_context_system()
{

   return g_psystem;

}




void acme_system_init()
{

   g_psystem = new acme::system();

}



void acme_system_term()
{

   ::acme::del(g_psystem);

}



