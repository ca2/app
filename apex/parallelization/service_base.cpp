#include "framework.h"


service_base::service_base()
{

}


service_base::~service_base()
{

}




//*****************************************************************************
//
//      Name:           ServiceName
//      Description:    Gets the service name of the service (as apposed to the
//                      display name). This is the name reported by the service
//                      control manager.
//
//*****************************************************************************
string service_base::get_service_name() const
{

   return m_serviceName;

}






bool service_base::get_run_service()
{

   return !m_bStopping;

}


::e_status service_base::run()
{

   m_bStopping = false;

   ::e_status estatus = ::error_failed;

   estatus = osthread_init();

   estatus = __thread_init();

   auto estatusMain = service_main();

   while (get_run_service())
   {

      sleep(100_ms);

   }

   Application.finalize();

   estatus = __thread_term();

   estatus = osthread_term();

   m_stopped.SetEvent();

   return estatusMain;

}


::e_status service_base::service_main()
{

   return ::success;

}

