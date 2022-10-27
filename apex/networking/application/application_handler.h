// Created by camilo on 2021-11-07 13:10 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/primitive/primitive/object.h"


namespace networking
{


// Thomas loves handler!!s
   class CLASS_DECL_APEX application_handler :
      virtual public ::object
   {
   public:


      application_handler();

      ~application_handler() override;


      virtual ::e_status on_html_response(::string &strHtml, const ::string &strUrl, const ::property_set &setPost);


   };


} // namespace networking



