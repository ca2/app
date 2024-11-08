#include "framework.h"
#include "incoming_socket.h"
#include "socket.h"
#include "socket_thread.h"
#include "apex/networking/sockets/basic/socket_handler.h"


namespace httpd
{


   socket_thread::socket_thread()
   {


   }


   socket_thread::~socket_thread()
   {


   }

      
   void socket_thread::initialize_socket_thread(::sockets::base_socket* psocket)
   {

      m_psocket = psocket;

      ::sockets::socket_thread::initialize_socket_thread(psocket);

   }


   void socket_thread::run()
   {
      
      ::sockets::socket_thread::run();

   }


   void socket_thread::destroy()
   {

      m_psocket.defer_destroy();

      ::sockets::socket_thread::destroy();

   }


} // namespace httpd



