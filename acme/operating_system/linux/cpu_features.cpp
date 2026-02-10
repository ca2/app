//
// Created by camilo on 2026-02-02 04:05 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include <sys/utsname.h>
#include <string.h>


namespace operating_system
{


   ::string machine_architecture()
   {

      struct utsname u;

      uname(&u);

      if (!strcmp(u.machine, "aarch64"))
      {

         return "aarch64";

      }
      else if (!strcmp(u.machine, "x86_64"))
      {

         return "x86_64";

      }
      else
      {

         return "(Unknown architecture)";

      }

   }


} // namespace operating_system


