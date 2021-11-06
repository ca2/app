// Created on 2021-03-17 by camilo 11:40 BRT <3ThomasBS_!!
#pragma once


class CLASS_DECL_APEX service_handler :
   virtual public ::acme::department
{
public:


   __pointer(::service)       m_pservice;


   service_handler();
   virtual ~service_handler();
   //virtual ::e_status start_service();

   //virtual ::e_status stop_service();

   service* get_service();
   //virtual ::e_status install_service();

   virtual ::e_status defer_service();

   //virtual ::e_status enable_service();
   //virtual ::e_status disable_service();

   virtual ::e_status start_service();
   virtual ::e_status stop_service();


};






