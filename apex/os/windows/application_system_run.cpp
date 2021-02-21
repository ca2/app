#include "framework.h"
#include "apex/operating_system.h"


namespace apex
{


   ::e_status system::start()
   {

      auto estatus = ::acme::system::start();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;


   }


} // namespace apex



