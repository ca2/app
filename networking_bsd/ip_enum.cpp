#include "framework.h"
#include "ip_enum.h"
#include "acme/exception/interface_only.h"


namespace networking_bsd
{


   ip_enum::ip_enum()
   {

   }


   ip_enum::~ip_enum()
   {

   }


   ::raw::count ip_enum::enumerate(pointer_array < ::networking::address > & ipa)
   {

      __UNREFERENCED_PARAMETER(ipa);

      throw ::interface_only();

      return 0;

   }


} // namespace net



