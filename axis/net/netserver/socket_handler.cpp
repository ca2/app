#include "framework.h"
#include "_.h"


namespace netserver
{


   socket_handler::socket_handler(::layered * pobjectContext, ::apex::log * plogger) :
      ::object(pobjectContext),
      sockets::socket_handler(pobjectContext, plogger)
   {

   }


   socket_handler::~socket_handler()
   {

   }


} // namespace netserver




