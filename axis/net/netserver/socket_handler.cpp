#include "framework.h"
#include "_.h"


namespace netserver
{


   socket_handler::socket_handler(::object * pobject, ::aura::log * plogger) :
      ::object(pobject),
      sockets::socket_handler(pobject, plogger)
   {

   }


   socket_handler::~socket_handler()
   {

   }


} // namespace netserver




