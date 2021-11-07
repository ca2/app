// Created by camilo on 2021-11-07 11:36 BRT <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_AXIS networking_application :
   virtual public ::object
{
public:


   __composite(::netserver::socket_thread_base)       m_psocketthread;
   int                                                m_iPort;


   networking_application();
   ~networking_application() override;


   ::e_status initialize(::object* pobject) override;


   ::e_status create_networking_application();


   string on_html_response(const ::string& strUrl, const ::property_set& setPost);


};




