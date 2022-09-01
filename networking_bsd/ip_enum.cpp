#include "framework.h"
#include "apex/networking/networking_bsd/_sockets.h"


namespace net
{


   ip_enum::ip_enum()
   {

   }


   ip_enum::~ip_enum()
   {

   }


   ::count ip_enum::enumerate(array < ::networking::address > & ipa)
   {

      __UNREFERENCED_PARAMETER(ipa);

      throw ::interface_only();

      return 0;

   }


} // namespace net



