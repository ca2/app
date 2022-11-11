#include "framework.h"

namespace sockets
{

   sip_server::sip_server(::axis::application * papp) :
      ::object(pparticle),
      thread(pparticle)
   {
   }

   int sip_server::run()
   {
      return 0;
   }

} // namespace sockets
