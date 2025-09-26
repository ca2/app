#include "framework.h"
#include "socket_thread.h"
#include "apex/networking/sockets/basic/socket_handler.h"


namespace netserver
{


   socket_thread::socket_thread()
   {




   }


   socket_thread::~socket_thread()
   {

   }



   ::pointer <::sockets::socket_handler > socket_thread::create_socket_handler()
   {

      return øcreate< ::sockets::socket_handler >();

   }



   void socket_thread::run()
   {

      ::sockets::socket_thread::run();

   }


} // namespace netserver



