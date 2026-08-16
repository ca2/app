//
// Created by camilo on 2024-06-03 01:17 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "acme/operating_system/dynamic_library.h"


#if defined(LINUX) || defined(__BSD__)


namespace operating_system
{


   CLASS_DECL_ACME ::operating_system::dynamic_library* new_dynamic_library()
   {

      return øraw_new ::operating_system::dynamic_library();

   }


} // namespace operating_system

#endif
