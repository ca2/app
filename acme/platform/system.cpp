#include "framework.h"
#include "acme/id.h"


namespace acme
{

   system::system()
   {

      m_papexsystem = nullptr;
      m_paquasystem = nullptr;
      m_paurasystem = nullptr;
      m_paxissystem = nullptr;
      m_pbasesystem = nullptr;
      m_pcoresystem = nullptr;

   }


   system::~system()
   {


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

   }


   ITHREAD system::get_task_id(::task * ptask)
   {

   }


   void system::set_task(ITHREAD ithread, ::task * ptask)
   {

   }


   void system::unset_task(ITHREAD ithread, ::task * ptask)
   {

   }


} // namespace acme


::acme::system * g_psystem = nullptr;


::acme::system * get_context_system()
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
