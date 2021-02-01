#include "framework.h"
#include "apex/net/sockets/_sockets.h"


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

      UNREFERENCED_PARAMETER(ipa);

      ::exception::throw_interface_only();

      return 0;

   }


} // namespace net



