#include "framework.h"


namespace sphere
{


   library::library(::particle * pparticle) :
      ::object(pparticle),
      ::acme::library(pparticle, 0, "app"),
      ::apex::single_application_library < application > (pparticle, "app"),
      ::filehandler::library(pparticle),
      ::filehandler::menu_library(pparticle)
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

   void library::get_extension_app(string_array & straApp, const ::string & pszExtension)
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


   /*   ::pointer<::aura::application>library::get_new_app(const ::string & pszAppId)
      {

         if(case_insensitive_equals(pszAppId, "calculator"))
         {
            return ___new ::calculator::application ();
         }
         else if(case_insensitive_equals(pszAppId, "command"))
         {
            return ___new ::command::application ();
         }
         else if(case_insensitive_equals(pszAppId, "userstack"))
         {
            return ___new ::userstack::application ();
         }
         else if(case_insensitive_equals(pszAppId, "default_file_handler"))
         {
            return ___new ::filehandler::application ();
         }

         return ::apex::single_application_library < application >::get_new_app(pszAppId);

      }*/


} // namespace sphere


#ifndef _WIN32
extern "C"
#endif
::acme::library * get_new_library(::particle * pparticle)
{

   return ___new ::sphere::library (pparticle);

}
