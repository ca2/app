#include "framework.h"
#include "apex/operating_system.h"


#ifdef WINDOWS
u32 Win32FromHResult(HRESULT value);
#endif


namespace windows
{


   service * service::s_pservice = nullptr;


   service::service(u32 controlsAccepted) :
      m_handle(0)
   {

      m_dwStopTimeout = 30 * 1000; // 30 seconds

   #ifdef WINDOWS_DESKTOP
      m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
      m_status.dwCurrentState = SERVICE_START_PENDING;
      m_status.dwControlsAccepted = controlsAccepted;
   #endif

   }


   service::~service()
   {

   }


   void service::Start(u32)
   {

      queue_user_work_item();

   }


   void service::_server()
   {


#ifdef WINDOWS_DESKTOP


      SERVICE_TABLE_ENTRYW serviceTable[] =
      {

         // Even though the service name is ignored for own process services,
         // it must be a valid string and cannot be 0.
         { (WCHAR *)L"", ServiceMain },

         // Designates the end of table.
         { 0, 0 }

      };

      if (!::StartServiceCtrlDispatcherW(serviceTable))
      {

         __throw(exception::exception());

      }

#endif

   }




   //*****************************************************************************
   //
   //      Name:           SetServiceStatus
   //      Description:    Wrapper for the SetServiceStatus SCM function.
   //
   //*****************************************************************************
   void service::SetServiceStatus()
   {

      // If m_service is zero it means we're not running as a service but
      // rather from the console. This is possible in debug mode.

      if (::is_null(s_pservice))
      {

         return;

      }

#ifdef WINDOWS_DESKTOP

      if (!::SetServiceStatus(m_handle, &m_status))
      {

         DWORD dwLastError = ::GetLastError();

         __throw(exception::exception());

      }

#endif

   }


   ::e_status service::queue_user_work_item(WINULONG flags)
   {

      if (::QueueUserWorkItem(thread_proc, this, flags))
      {

         return error_failed;

      }

      fork([this]()
         {

            run();

         });

      return ::success;

   }


   void service::serve(service * pservice)
   {

      ASSERT(0 == s_pservice);

      s_pservice = pservice;

      s_pservice->_server();

   }


   void service::Stop(u32 u)
   {

      m_bStopping = true;

      m_stopped.wait(millis((u32)m_dwStopTimeout));

   }


   DWORD WINAPI service::thread_proc(void * pcontext)
   {

      service * pservice = (service *)pcontext;
      
      auto estatus = pservice->run();

      return (DWORD) estatus.m_estatus;

   }


   //*****************************************************************************
   //
   //      Name:           ServiceMain
   //      Description:    The starting point for the service.
   //
   //*****************************************************************************
   void WINAPI service::ServiceMain(DWORD argumentCount, PWSTR * arguments)
   {

      // Since there's no way to inform the SCM of failure before a successful
      // call to RegisterServiceCtrlHandler, if an error occurs before we have
      // a service status handle we don't catch any exceptions and let the
      // process terminate. The SCM will diligently log this event.
      //

      ASSERT(s_pservice != nullptr);

      s_pservice->_main_server(argumentCount, arguments);

   }


   //*****************************************************************************
   //
   //      Name:           Handler
   //      Description:    The handler function called by the control dispatcher
   //                      when an event occurs.
   //
   //*****************************************************************************
   void WINAPI service::ServiceHandler(DWORD control)
   {

      try
      {

         switch (control)
         {
         case SERVICE_CONTROL_CONTINUE:
         {

            s_pservice->UpdateState(SERVICE_CONTINUE_PENDING);
            s_pservice->Start(control);
            s_pservice->UpdateState(SERVICE_RUNNING);

            break;

         }
         case SERVICE_CONTROL_PAUSE:
         {

            s_pservice->UpdateState(SERVICE_PAUSE_PENDING);
            s_pservice->Stop(control);
            s_pservice->UpdateState(SERVICE_PAUSED);

            break;

         }
         case SERVICE_CONTROL_SHUTDOWN:
         case SERVICE_CONTROL_STOP:
         {

            s_pservice->UpdateState(SERVICE_STOP_PENDING);
            s_pservice->Stop(control);
            s_pservice->UpdateState(SERVICE_STOPPED);

            Sys(s_pservice).finalize();

            break;

         }
         default:
            break;
         }

      }
      catch (const hresult_exception & e)
      {

         s_pservice->UpdateState(SERVICE_STOPPED, e);

      }

   }


   void service::_main_server(::u32 argumentCount, PWSTR * arguments)
   {

      if (1 != argumentCount || 0 == arguments || 0 == arguments[0])
      {

         __throw(invalid_argument_exception());

      }

      s_pservice->m_serviceName = arguments[0];

      s_pservice->m_handle = ::RegisterServiceCtrlHandlerW(L"", ServiceHandler);

      if (s_pservice->m_handle == nullptr)
      {

         DWORD dwLastError = ::GetLastError();
         
         __throw(exception::exception());

      }

      s_pservice->SetServiceStatus();

      try
      {

         s_pservice->Start(0);

         s_pservice->UpdateState(SERVICE_RUNNING);

      }
      catch (const hresult_exception & e)
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
   //      Name:           UpdateState
   //      Description:    Updates the current state and exit code of the service
   //                      and notifies the service control manager of the machine.
   //
   //*****************************************************************************
   void service::UpdateState(u32 state, HRESULT errorCode)
   {


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

   }


} // namespace windows





#ifdef WINDOWS


u32 Win32FromHResult(HRESULT value)
{

   ASSERT(FACILITY_WIN32 == HRESULT_FACILITY(value));

   return value & ~0x80070000;

}
#endif



