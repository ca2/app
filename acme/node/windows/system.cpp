//
// Created by camilo on 05/12/2020. <3tbs!!
//
#include "framework.h"
#include "acme/operating_system.h"


namespace acme
{


   ::e_status system::os_application_system_run()
   {

      auto estatus = do_task();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }




   void system::os_construct()
   {


   }


   ::user::enum_desktop system::calc_edesktop()
   {

      return ::user::e_desktop_windows;

   }


} // namespace acme



