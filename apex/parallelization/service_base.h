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


   ::u32                      m_dwStopTimeout;
   string                     m_serviceName;
   manual_reset_event         m_stopped;
   bool                       m_bStopping;
   i32                        m_iPid;

   
   service_base();
   virtual ~service_base();


   virtual void Start(u32 control) = 0;

   virtual void Stop(u32 control) = 0;

   virtual string get_service_name() const;

   virtual bool get_run_service();

   virtual ::e_status run();

   virtual ::e_status service_main();



};



