//*****************************************************************************
//
//      Class:          service_base
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides a apex class for a service that will exist as
//                      part of a service application. service_base must be
//                      derived when creating a ___new service class.
//
//*****************************************************************************
// Recreated on 2021-03-17 by camilo 11:44 BRT <3ThomasBS_!!
#pragma once


////#include "acme/prototype/prototype/object.h"


class CLASS_DECL_APEX service :
   virtual public ::object
{
public:


   //unsigned int                      m_dwStopTimeout;
   string                     m_strServiceName;
   //manual_reset_event         m_stopped;
   ////bool                       m_bStopping;
   //int                        m_iPid;
   //enum_service_status        m_estatus;
   //unsigned int                        m_uControlStart;
   //unsigned int                        m_uControlStop;
   
   service();
   virtual ~service();


   //virtual void control_start(unsigned int control);

   //virtual void control_stop(unsigned int control);

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



