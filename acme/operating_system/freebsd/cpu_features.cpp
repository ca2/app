//
// Created by camilo on 2026-01-02 17:47 <3ThomasBorregaardSørensen!!
//
//
// Changed by camilo on 2026-02-02 09:44 <3ThomasBorregaardSørensen!!
//

#include "framework.h"
#include "acme/operating_system/cpu_features.h"
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <cstdint>


namespace operating_system
{


   ::string machine_architecture()
   {
      struct utsname u;
      if (uname(&u) != 0)
      {
         return "(Unknown architecture)";
      }

      // ARM64
      if (!strcmp(u.machine, "aarch64") ||
          !strcmp(u.machine, "arm64"))
      {
         return "aarch64";
      }
      // x86_64 / amd64
      else if (!strcmp(u.machine, "x86_64") ||
               !strcmp(u.machine, "amd64"))
      {
         return "x86_64";
      }

      return u.machine; // fallback: return raw uname value
   }


} // namespace operating_system



