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

#pragma once

class CLASS_DECL_APEX service_base :
   virtual public ::thread
{
public:

   DWORD                   m_dwStopTimeout;
   static service_base *   s_pservice;

   service_status          m_status;
   string                  m_serviceName;

   manual_reset_event      m_stopped;
   bool                    m_bStopping;

#ifdef WINDOWS_DESKTOP

   SERVICE_STATUS_HANDLE   m_handle;

#else

   i32                 m_iPid;

#endif



#ifdef WINDOWS_DESKTOP

   service_base(u32 controlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);

#else

   service_base(u32 controlsAccepted = 0);

#endif

   virtual ~service_base();

   virtual void Start(u32 control) = 0;

   virtual void Stop(u32 control) = 0;

   virtual void UpdateState(u32 state, HRESULT errorCode = S_OK);

   virtual string get_service_name() const;

   virtual void SetServiceStatus();

   virtual bool get_run_service();

   virtual void call_server();

   virtual void serve() = 0;

   static void serve(service_base& service);

   virtual void _server();

#ifdef WINDOWS_DESKTOP

   virtual void _main_server(DWORD argumentCount, PWSTR * arguments);


   static void WINAPI ServiceMain(DWORD argumentCount, PWSTR* arguments);

   static void WINAPI ServiceHandler(DWORD control);

#endif

};


