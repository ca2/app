#include "framework.h"
#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
#include <arpa/inet.h>
#endif

namespace str
{


   CLASS_DECL_AURA string from(const struct sockaddr & sockaddr)
   {

      string str;

      char sz[INET6_ADDRSTRLEN + INET_ADDRSTRLEN];

      switch (sockaddr.sa_family)
      {
      case AF_INET:
         inet_ntop(AF_INET, &(((struct sockaddr_in &)sockaddr).sin_addr), sz, sizeof(sz));
         break;

      case AF_INET6:
         inet_ntop(AF_INET6, &(((struct sockaddr_in6 &)sockaddr).sin6_addr), sz, sizeof(sz));
         break;

      default:
         strncpy(sz, "(Unknown Address Family)", sizeof(sz));
         break;
      };

      str = sz;

      return str;

   }


} // namespace str




