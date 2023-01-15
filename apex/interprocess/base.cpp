// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:19 <3ThomasBorregaardSørensen!!
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




   string app_install(string strPlatform)
   {

      return "::ca2::account::ca2_installer_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

   }




} // namespace interprocess



