// Created by camilo on 2021-11-07 11:36 BRT <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_AXIS networking_application :
   virtual public ::networking_application_handler
{
protected:

   
   string_map < __pointer(::networking_application_handler) >   m_maphandler;


public:


   __composite(::netserver::socket_thread_base)                 m_psocketthread;


   networking_application();
   ~networking_application() override;


   ::e_status initialize(::object* pobject) override;


   ::e_status create_networking_application();

   
   virtual i32 get_current_port();


   virtual i32 wait_get_current_port(const ::duration & duration);


   virtual ::e_status add_handler(const ::string& strPrefix, networking_application_handler* phandler);


   ::e_status on_html_response(::string & strHtml, const ::string& strUrl, const ::property_set& setPost) override;


};




