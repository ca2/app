// Created by camilo on 2024-12-01 00:34 <3ThomasBorregaardSorensen!!
// 🌌🌍 [ Ubuntu 24.10 ] [ day 92 ] [ C++ ] ca2 Store
#include "framework.h"


CLASS_DECL_ACME ::string get_operating_system_name()
{

#if defined(LINUX)
   return "linux";
#elif defined(WINDOWS_DESKTOP)
   return "windows";
#elif defined(MACOS))
   return "macos";
#elif defined(APPLE_IOS))
   return "ios";
#elif defined(FREEBSD))
   return "freebsd";
#elif defined(NETBSD))
   return "netbsd";
#elif defined(OPENBSD))
   return "openbsd";
#endif


}



