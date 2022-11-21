//*****************************************************************************
//
//      Class:          service_base
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides a apex class for a service that will exist as
//                      part of a service application. service_base must be
//                      derived when creating a memory_new service class.
//
//*****************************************************************************
// Recreated on 2021-03-17 by camilo 11:44 BRT <3ThomasBS_!!
#pragma once


////#include "acme/primitive/primitive/object.h"


class CLASS_DECL_APEX service :
   virtual public ::object
{
public:


   //::u32                      m_dwStopTimeout;
   string                     m_strServiceName;
   //manual_reset_event         m_stopped;
   ////bool                       m_bStopping;
   //i32                        m_iPid;
   //enum_service_status        m_estatus;
   //u32                        m_uControlStart;
   //u32                        m_uControlStop;
   
   service();
   virtual ~service();


   //virtual void control_start(u32 control);

   //virtual void control_stop(u32 control);

   //virtual string get_service_name() const;

   //virtual bool get_run_service();

   //virtual void run();

   //virtual void service_main();

   void set_arguments(int argc, char** argv);

   void set_arguments(int argc, wchar_t** argv);

   virtual void start_service();

   virtual void stop_service();

   virtual ::enum_service_status get_service_status();


};



