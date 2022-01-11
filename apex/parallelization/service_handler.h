// Created on 2021-03-17 by camilo 11:40 BRT <3ThomasBS_!!
#pragma once


class CLASS_DECL_APEX service_handler :
   virtual public ::acme::department
{
public:


   __pointer(::service)       m_pservice;


   service_handler();
   virtual ~service_handler();
   //virtual void start_service();

   //virtual void stop_service();

   service* get_service();
   //virtual void install_service();

   virtual void defer_service();

   //virtual void enable_service();
   //virtual void disable_service();

   virtual void start_service();
   virtual void stop_service();


};






