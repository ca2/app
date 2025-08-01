// Created by camilo on 2021-11-07 11:36 BRT <3ThomasBorregaardSorensen!!
#pragma once



class CLASS_DECL_APEX networking_application :
   virtual public ::networking_application_handler
{
protected:

   
   string_map < ::pointer<::networking_application_handler >>  m_maphandler;


public:


   ::pointer<::netserver::socket_thread_base>                m_psocketthread;


   networking_application();
   ~networking_application() override;


   void initialize(::particle * pparticle) override;


   void create_networking_application();

   
   virtual int get_current_port();


   virtual int wait_get_current_port(const ::duration & duration);


   virtual void add_handler(const ::scoped_string & scopedstrPrefix, networking_application_handler* phandler);


   ::e_status on_html_response(::string & strHtml, const ::scoped_string & scopedstrUrl, const ::property_set& setPost) override;


};




