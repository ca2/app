// Created by camilo on 2021-11-07 11:36 BRT <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_AXIS networking_application :
   virtual public ::networking_application_handler
{
public:


   __composite(::netserver::socket_thread_base)                         m_psocketthread;
   int                                                                  m_iPort;
   string_map < __pointer_array(::networking_application_handler) >     m_mapnetworkingapplicationhandlera;


   networking_application();
   ~networking_application() override;


   ::e_status initialize(::object* pobject) override;


   ::e_status create_networking_application();


   ::e_status on_html_response(::string & strHtml, const ::string& strUrl, const ::property_set& setPost) override;


};




