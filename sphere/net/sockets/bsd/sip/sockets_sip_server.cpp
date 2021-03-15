#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{

   sip_server::sip_server(::context_object * pcontextobject) :
      ::object(pobject),
      thread(pobject)
   {
   }

   i32 sip_server::run()
   {
      return 0;
   }

} // namespace sockets