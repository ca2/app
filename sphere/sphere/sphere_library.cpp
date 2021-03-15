#include "framework.h"


namespace sphere
{


   library::library(::context_object * pcontextobject) :
      ::object(pobject),
      ::apex::library(pobject, 0, "app"),
      ::apex::single_application_library < application > (pobject, "app"),
      ::filehandler::library(pobject),
      ::filehandler::menu_library(pobject)
   {

   }


   void library::get_app_list(string_array & stra)
   {

      stra.add("calculator");
      stra.add("command");
      stra.add("default_file_handler");
      stra.add("userstack");

   }


   void library::get_extension_list(string_array & stra)
   {

      stra.add("*");

   }

   void library::get_extension_app(string_array & straApp, const char * pszExtension)
   {

      string strExtension(pszExtension);

      strExtension.make_lower();

      if(strExtension == "*")
      {
         straApp.add_unique("default_file_handler");
      }
      if(strExtension == "mid" || strExtension == "karaoke" || strExtension == "st3")
      {
         straApp.add_unique("mplite");
         straApp.add_unique("vmsp");
      }

   }


   /*   __pointer(::aura::application) library::get_new_app(const char * pszAppId)
      {

         if(::str::equals_ci(pszAppId, "calculator"))
         {
            return new ::calculator::application();
         }
         else if(::str::equals_ci(pszAppId, "command"))
         {
            return new ::command::application();
         }
         else if(::str::equals_ci(pszAppId, "userstack"))
         {
            return new ::userstack::application();
         }
         else if(::str::equals_ci(pszAppId, "default_file_handler"))
         {
            return new ::filehandler::application();
         }

         return ::apex::single_application_library < application >::get_new_app(pszAppId);

      }*/


} // namespace sphere


#ifndef _WIN32
extern "C"
#endif
::apex::library * get_new_library(::context_object * pcontextobject)
{

   return new ::sphere::library(pobject);

}
