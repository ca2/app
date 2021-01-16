//*****************************************************************************
//
//      Class:          service_base
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides a apex class for a service that will exist as
//                      part of a service application. service_base must be
//                      derived when creating a new service class.
//
//*****************************************************************************
#include "framework.h"

#ifdef WINDOWS
u32 Win32FromHResult(HRESULT value);
#endif

//
// The single, static service instance pointer.
//
service_base* service_base::s_pservice = 0;

//*****************************************************************************
//
//      Name:           service_base
//      Description:    The constructor - initializes a new instance of the
//                      service_base class.
//
//*****************************************************************************
service_base::service_base(u32 controlsAccepted) :
   m_bStopping(false)
#ifdef WINDOWS_DESKTOP
   , m_handle(0)
#else
//   , m_waitableptra(0)
#endif
{

   m_dwStopTimeout = 30 * 1000; // 30 seconds

#ifdef WINDOWS_DESKTOP
   m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
   m_status.dwCurrentState = SERVICE_START_PENDING;
   m_status.dwControlsAccepted = controlsAccepted;
#endif

}

//*****************************************************************************
//
//      Name:           service_base
//      Description:    The virtual destructor.
//
//*****************************************************************************
service_base::~service_base()
{
   // Do nothing
}

//*****************************************************************************
//
//      Name:           run
//      Description:    Provides the Main entry point for an executable that
//                      contains a single service. Loads the service into
//                      memory so it can be started. This method blocks until
//                      the service has stopped.
//
//*****************************************************************************
void service_base::serve(service_base & service)
{

   ASSERT(0 == s_pservice);

   s_pservice = &service;

   s_pservice->_server();

}


void service_base::_server()
{
#ifdef WINDOWS_DESKTOP

   SERVICE_TABLE_ENTRYW serviceTable[] =
   {

      // Even though the service name is ignored for own process services,
      // it must be a valid string and cannot be 0.
      { L"", ServiceMain },

      // Designates the end of table.
      { 0, 0 }

   };

   //::MessageBox(nullptr,"attach","attach",e_message_box_ok);

   if (!::StartServiceCtrlDispatcherW(serviceTable))
   {

      __throw(last_error_exception());

   }

#endif

}

#ifdef WINDOWS
u32 Win32FromHResult(HRESULT value)
{

   ASSERT(FACILITY_WIN32 == HRESULT_FACILITY(value));

   return value & ~0x80070000;

}
#endif

//*****************************************************************************
//
//      Name:           UpdateState
//      Description:    Updates the current state and exit code of the service
//                      and notifies the service control manager of the machine.
//
//*****************************************************************************
#ifdef WINDOWS
void service_base::UpdateState(u32 state, HRESULT errorCode)
{


#ifdef WINDOWS_DESKTOP


   m_status.dwCurrentState = state;

   ASSERT(0 == m_status.dwWin32ExitCode);
   ASSERT(0 == m_status.dwServiceSpecificExitCode);

   if (FAILED(errorCode))
   {
      if (FACILITY_WIN32 == HRESULT_FACILITY(errorCode))
      {
         m_status.dwWin32ExitCode = Win32FromHResult(errorCode);
      }
      else
      {
         m_status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
         m_status.dwServiceSpecificExitCode = errorCode;
      }
   }

   SetServiceStatus();


#endif


}
#endif
//*****************************************************************************
//
//      Name:           SetServiceStatus
//      Description:    Wrapper for the SetServiceStatus SCM function.
//
//*****************************************************************************
void service_base::SetServiceStatus()
{

   // If m_service is zero it means we're not running as a service but
   // rather from the console. This is possible in debug mode.

   if(::is_null(s_pservice))
   {

      return;

   }

#ifdef WINDOWS_DESKTOP

   if (!::SetServiceStatus(m_handle, &m_status))
   {

      __throw(last_error_exception());

   }

#endif

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


#ifdef WINDOWS_DESKTOP

//*****************************************************************************
//
//      Name:           ServiceMain
//      Description:    The starting point for the service.
//
//*****************************************************************************
void WINAPI service_base::ServiceMain(DWORD argumentCount, PWSTR * arguments)
{

   // Since there's no way to inform the SCM of failure before a successful
   // call to RegisterServiceCtrlHandler, if an error occurs before we have
   // a service status handle we don't catch any exceptions and let the
   // process terminate. The SCM will diligently log this event.
   //

   ASSERT(s_pservice != nullptr);

   s_pservice->_main_server(argumentCount, arguments);

}


void service_base::_main_server(::u32 argumentCount, PWSTR * arguments)
{

   if (1 != argumentCount || 0 == arguments || 0 == arguments[0])
   {

      __throw(invalid_argument_exception());

   }
   sleep(10_s);


   s_pservice->m_serviceName = arguments[0];

   s_pservice->m_handle = ::RegisterServiceCtrlHandlerW(L"", ServiceHandler);

   if(s_pservice->m_handle == nullptr)
   {
      __throw(last_error_exception());
   }

   s_pservice->SetServiceStatus();

   try
   {

      s_pservice->Start(0);

      s_pservice->UpdateState(SERVICE_RUNNING);

   }
   catch (const hresult_exception& e)
   {
      //
      // If the service can't start it should __throw( an exception from the
      // Start method. If this happens, we catch it here and notify the
      // SCM so that it can log the error code.
      //

      s_pservice->UpdateState(SERVICE_STOPPED, e);
   }


}

//*****************************************************************************
//
//      Name:           Handler
//      Description:    The handler function called by the control dispatcher
//                      when an event occurs.
//
//*****************************************************************************
void WINAPI service_base::ServiceHandler(DWORD control)
{


   try
   {
      switch (control)
      {
      case SERVICE_CONTROL_CONTINUE :
      {
         s_pservice->UpdateState(SERVICE_CONTINUE_PENDING);
         s_pservice->Start(control);
         s_pservice->UpdateState(SERVICE_RUNNING);
         break;
      }
      case SERVICE_CONTROL_PAUSE :
      {
         s_pservice->UpdateState(SERVICE_PAUSE_PENDING);
         s_pservice->Stop(control);
         s_pservice->UpdateState(SERVICE_PAUSED);
         break;
      }
      case SERVICE_CONTROL_SHUTDOWN :
      case SERVICE_CONTROL_STOP :
      {
         s_pservice->UpdateState(SERVICE_STOP_PENDING);
         s_pservice->Stop(control);
         s_pservice->UpdateState(SERVICE_STOPPED);

         Sys(s_pservice).finalize();
         break;
      }
      }
   }
   catch (const hresult_exception& e)
   {
      s_pservice->UpdateState(SERVICE_STOPPED, e);
   }


}

#endif


bool service_base::get_run_service()
{

   return !m_bStopping;

}



void service_base::call_server()
{

   m_bStopping = false;

   ::e_status estatus = ::error_failed;

   estatus = osthread_init();

   estatus = __thread_init();

   serve();

   while (get_run_service())
   {

      sleep(100_ms);

   }

   Application.finalize();

   estatus = __thread_term();

   estatus = osthread_term();

   m_stopped.SetEvent();

}
