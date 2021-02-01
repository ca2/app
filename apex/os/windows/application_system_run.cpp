#include "framework.h"
#include "apex/operating_system.h"


namespace apex
{


   ::e_status system::os_application_system_run()
   {

      auto estatus = ::acme::system::os_application_system_run();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;


   }


} // namespace apex



