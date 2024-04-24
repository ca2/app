// Created by camilo on 2021-11-07 11:36 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "application_handler.h"
#include "acme/primitive/collection/string_map.h"
#include "apex/networking/netserver/incoming_socket_thread.h"


namespace networking
{


   class CLASS_DECL_APEX application :
      virtual public ::networking::application_handler
   {
   protected:


      string_map < ::pointer<::networking::application_handler >>  m_maphandler;


   public:

      ::string                                                 m_strHostname;


      ::pointer < ::netserver::incoming_socket_thread >        m_psocketthread;


      application();
      ~application() override;
      

      void initialize(::particle * pparticle) override;


      void create_networking_application();


      virtual i32 get_current_port();


      virtual i32 wait_get_current_port(const class time & time);


      virtual void add_handler(const ::string& strPrefix, ::networking::application_handler* phandler);


      ::e_status on_html_response(::networking::application_socket * psocket, ::string & strHtml, const ::string& strUrl, const ::property_set& setPost) override;


   };


} // namespace networking



