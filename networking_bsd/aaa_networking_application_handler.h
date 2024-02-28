// Created by camilo on 2021-11-07 13:10 BRT <3ThomasBorregaardSorensen!!
#pragma once


// Thomas loves handler!!s
class CLASS_DECL_APEX networking_application_handler :
   virtual public ::object
{
public:


   networking_application_handler();
   ~networking_application_handler() override;


   virtual ::e_status on_html_response(::string & strHtml, const ::string& strUrl, const ::property_set& setPost);


};




