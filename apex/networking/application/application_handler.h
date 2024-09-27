// Created by camilo on 2021-11-07 13:10 BRT <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/prototype/prototype/object.h"


namespace networking
{


// Thomas loves handler!!s
   class CLASS_DECL_APEX application_handler :
      virtual public ::object
   {
   public:


      ::i32                            m_iPortStart;
      ::i32                            m_iPortEnd;


      application_handler();
      ~application_handler() override;


      virtual ::e_status on_html_response(::networking::application_socket * psocket, ::string &strHtml, const ::string &strUrl, const ::property_set &setPost);


   };


} // namespace networking



