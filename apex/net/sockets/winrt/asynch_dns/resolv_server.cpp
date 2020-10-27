#include "framework.h"
#include "apex/net/sockets/_.h"


namespace sockets
{


   resolv_server::resolv_server(::layered * pobjectContext, port_t port) :
      ::object(pobjectContext),
      m_quit(false),
      m_port(port),
      m_ready(false)
   {

      fork();

   }


   resolv_server::~resolv_server()
   {

   }


   void resolv_server::go()
   {

      socket_handler h(this);

      listen_socket<resolv_socket> l(h);

      if (l.Bind("127.0.0.1", m_port))
      {
         return;
      }
      h.add(&l);

      m_ready = true;
      while (!m_quit && thread_get_run())
      {
         h.select(0, 500000);
      }
   }


   void resolv_server::Quit()
   {
      m_quit = true;
   }


   bool resolv_server::Ready()
   {
      return m_ready;
   }


} // namespace sockets
