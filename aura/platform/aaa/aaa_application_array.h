#pragma once


class CLASS_DECL_AURA application_array:
   virtual public pointer_array < ::aura::application >
{
public:


   //application_array(::particle * pparticle);
   application_array();
   application_array(const application_array & a);
   application_array(application_array && a);
   virtual ~application_array();
      
      
   application_array & operator = (const application_array & a);
   application_array & operator = (application_array && a);

   ::aura::application * find_by_app_name(string strAppName);

   ::aura::application * find_running_defer_try_quit_damaged(string strAppName);

   bool lookup(string strAppName, ::pointer<::aura::application>& papp);


};

