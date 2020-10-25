#include "framework.h"
#include "apex/net/sockets/_.h"


namespace sockets
{


   resolv_server::resolv_server()
   {


   }

      
   ::estatus     resolv_server::initialize_resolv_server(::object * pobjectParent, port_t port)
   {

      auto estatus = initialize(pobjectParent);

      if (!estatus)
      {

         return estatus;

      }

      m_port = port;

      fork();

      return estatus;

   }


   resolv_server::~resolv_server()
   {

   }


   void resolv_server::go()
   {

      //   trace_log log;
      socket_handler h(get_context_object());

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








