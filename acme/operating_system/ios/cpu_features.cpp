//
// From linux/cpu_features.cpp by camilo on 2026-02-04 19:07 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include <sys/utsname.h>
#include <string.h>

namespace operating_system
{

   ::string machine_architecture()
   {
      struct utsname u{};
      uname(&u);

      // Apple Silicon
      if (!strcmp(u.machine, "arm64"))
      {
         return "arm64";
      }
      // Linux / BSD ARM64 naming
      else if (!strcmp(u.machine, "aarch64"))
      {
         return "arm64";
      }
      // Intel
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
