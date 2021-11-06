#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   resolv_server::resolv_server()
   {


   }


   ::e_status     resolv_server::initialize_resolv_server(::object * pobjectParent, port_t port)
   {

      auto estatus = initialize(pobjectParent);

      if (!estatus)
      {

         return estatus;

      }

      m_port = port;

      branch();

      return estatus;

   }


   resolv_server::~resolv_server()
   {

   }


   void resolv_server::go()
   {

      //   trace_log log;
      auto phandler = __create_new < socket_handler > ();

      auto plistensocket = __create_new < listen_socket<resolv_socket> >();

      if (plistensocket->Bind("127.0.0.1", m_port))
      {

         return;

      }

      phandler->add2(plistensocket);

      m_ready = true;

      while (!m_quit && task_get_run())
      {

         phandler->select(0, 500000);

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








