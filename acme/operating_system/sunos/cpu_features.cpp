//
// Created by camilo on 2026-02-02 04:05 <3ThomasBorregaardSørensen!!
//

#include "platform.h"
#include <sys/utsname.h>
#include <string.h>


namespace operating_system
{


   ::string machine_architecture()
   {

      struct utsname u{};

      if(::uname(&u) != 0)
      {

         return "(Unknown architecture)";

      }


      //
      // illumos / Solaris on x86 normally reports "i86pc"
      // as the machine platform, including on 64-bit systems.
      //

      if(!::strcmp(u.machine, "i86pc"))
      {

#if defined(__x86_64__) || defined(__amd64__)

         return "x86_64";

#elif defined(__i386__)

         return "x86";

#else

         return "i86pc";

#endif

      }


      if(!::strcmp(u.machine, "aarch64"))
      {

         return "aarch64";

      }


      if(!::strcmp(u.machine, "amd64"))
      {

         return "x86_64";

      }


      if(!::strcmp(u.machine, "x86_64"))
      {

         return "x86_64";

      }


      if(!::strcmp(u.machine, "sparc"))
      {

#if defined(__sparcv9)

         return "sparcv9";

#else

         return "sparc";

#endif

      }


      return "(Unknown architecture)";

   }


} // namespace operating_system
