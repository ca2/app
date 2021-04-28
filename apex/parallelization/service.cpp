#include "framework.h"
#include "service.h"


service::service()
{

}


service::~service()
{

}


void service::set_arguments(int argc, char** argv)
{



}


void service::set_arguments(int argc, wchar_t** argv)
{



}


::e_status service::start_service()
{

   return error_failed;

}


::e_status service::stop_service()
{

   return ::success;

}

::enum_service_status service::get_service_status()
{

   return e_service_status_stopped;

}


//
//void service::start_service(u32 control)
//{
//
//   m_estatus = e_status_starting;
//
//   m_uControlStart = control;
//
//}
//
//
//void service::stop_service(u32 control)
//{
//
//   m_estatus = e_status_stopping;
//
//   m_uControlStop = control;
//
//
//}
//
//
//
////*****************************************************************************
////
////      Name:           ServiceName
////      Description:    Gets the service name of the service (as apposed to the
////                      display name). This is the name reported by the service
////                      control manager.
////
////*****************************************************************************
//string service::get_service_name() const
//{
//
//   return m_serviceName;
//
//}
//
//
//
//
//
//
//bool service::get_run_service()
//{
//
//   return !m_bStopping;
//
//}
//
//
//::e_status service::run()
//{
//
//   m_bStopping = false;
//
//   ::e_status estatus = ::error_failed;
//
//   estatus = osthread_init();
//
//   estatus = __thread_init();
//
//   auto estatusMain = service_main();
//
//   while (get_run_service())
//   {
//
//      sleep(100_ms);
//
//   }
//
//   get_application()->finalize();
//
//   estatus = __thread_term();
//
//   estatus = osthread_term();
//
//   m_stopped.SetEvent();
//
//   return estatusMain;
//
//}
//
//
//::e_status service::service_main()
//{
//
//   return ::success;
//
//}
//
