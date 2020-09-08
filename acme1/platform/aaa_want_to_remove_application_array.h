#pragma once


class CLASS_DECL_ACME application_array:
   virtual public __pointer_array(::acme::application)
{
public:


   //application_array(::generic * pobject);
   application_array();
   application_array(const application_array & a);
   application_array(application_array && a);
   virtual ~application_array();
      
      
   application_array & operator = (const application_array & a);
   application_array & operator = (application_array && a);

   ::acme::application * find_by_app_name(string strAppName);

   ::acme::application * find_running_defer_try_quit_damaged(string strAppName);

   bool lookup(string strAppName, __pointer(::acme::application) & papp);


};

