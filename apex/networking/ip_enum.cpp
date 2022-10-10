#include "framework.h"
#include "ip_enum.h"


namespace networking
{


   ip_enum::ip_enum()
   {

   }


   ip_enum::~ip_enum()
   {

   }


   ::count ip_enum::enumerate(pointer_array < ::networking::address > & ipa)
   {

      __UNREFERENCED_PARAMETER(ipa);

      throw ::interface_only();

      return 0;

   }


} // namespace networking



