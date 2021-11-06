#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace net
{


   ip_enum::ip_enum()
   {

   }


   ip_enum::~ip_enum()
   {

   }


   ::count ip_enum::enumerate(array < ::net::address > & ipa)
   {

      __UNREFERENCED_PARAMETER(ipa);

      throw ::interface_only_exception();

      return 0;

   }


} // namespace net



