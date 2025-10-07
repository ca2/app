// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:19 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "base.h"


namespace interprocess
{


   base::base()
   {

      //set_hwnd(nullptr);

   }


   base::~base()
   {


   }




   string app_install(const ::scoped_string & scopedstrPlatform)
   {

      return "::ca2::account::ca2_installer_install_" + scopedstrPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

   }




} // namespace interprocess



