#pragma once


class CLASS_DECL_APEX application_array:
   virtual public __pointer_array(::application)
{
public:


   //application_array(::object * pobject);
   application_array();
   application_array(const application_array & a);
   application_array(application_array && a);
   virtual ~application_array();
      
      
   application_array & operator = (const application_array & a);
   application_array & operator = (application_array && a);

   ::application * find_by_app_name(string strAppName);

   ::application * find_running_defer_try_quit_damaged(string strAppName);

   bool lookup(string strAppName, __pointer(::application) & papp);


};

