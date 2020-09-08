#include "framework.h"

namespace sockets
{

   sip_server::sip_server(::axis::application * papp) :
      ::object(pobject),
      thread(pobject)
   {
   }

   int sip_server::run()
   {
      return 0;
   }

} // namespace sockets
