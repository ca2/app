// Created by camilo on 2023-03-31 14:19 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"


namespace application_build_helper
{
   

   void application::initial_ambient_setup()
   {
      
      auto str = acmenode()->get_user_permanent_environment_variable("PATH");
      
      bool bChanged = false;
      
      if (!str.case_insensitive_contains("C:\\operating_system\\bin"))
      {

         str += ";C:\\operating_system\\bin";
         
         bChanged  =true;
         
      }
      
      if (!str.case_insensitive_contains("C:\\operating_system\\tool-windows\\bin"))
      {

         str += ";C:\\operating_system\\tool-windows\\bin";
         
         bChanged = true;

      }

      if (bChanged)
      {

         acmenode()->set_user_permanent_environment_variable("PATH", str);

      }

   }


   void application::root_initial_ambient_setup()
   {

#ifdef WINDOWS_DESKTOP
      
      acmenode()->_beta_use_unicode_utf8();
      
#endif

   }
      
   
} // namespace application_build_helper
