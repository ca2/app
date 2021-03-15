#include "framework.h" 
#include "apex/net/sockets/_sockets.h"


namespace sockets
{



   link_in_socket::link_in_socket() :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h, 32000, 32000),
      //m_in(nullptr),
      //m_out(nullptr)
      tcp_socket(32000, 32000),
      m_in(nullptr),
      m_out(nullptr)
   {
   }


   link_in_socket::~link_in_socket()
   {
   }


   void link_in_socket::OnRead( char *buf, memsize n )
   {

      m_out->link_write(buf, n);

   }


   void link_in_socket::link_write(void * p, memsize n)
   {

      m_in->write((const char *) p, n);

   }


   void link_in_socket::server_to_link_in(httpd_socket * psocket)
   {
      
      __pointer(::sockets::socket_handler) phandler = psocket->socket_handler();

      auto p = phandler->m_sockets.begin();

      for (; p; p++)
      {

         if(p->m_psocket == psocket)
         {

            phandler->m_sockets.set_at(p->m_socket, this);

         }

      }

      m_socket             = psocket->m_socket;

      m_bConnecting        = psocket->m_bConnecting; ///< Flag indicating connection in progress
      m_connect_timeout    = psocket->m_connect_timeout; ///< Connection timeout (seconds)
      m_flush_before_close = psocket->m_flush_before_close; ///< Send all data before closing (default true)
      m_connection_retry   = psocket->m_connection_retry; ///< Maximum connection retries (tcp)
      m_retries            = psocket->m_retries; ///< Actual number of connection retries (tcp)
      m_call_on_connect    = psocket->m_call_on_connect; ///< OnConnect will be called next base_socket_handler cycle if true
      m_b_retry_connect    = psocket->m_b_retry_connect; ///< Try another connection attempt next base_socket_handler cycle
      m_shutdown           = psocket->m_shutdown; ///< Shutdown status

      m_bSsl               = psocket->m_bSsl;
      m_bReconnect         = psocket->m_bReconnect;
      m_bSsl               = psocket->m_bSsl;
      m_bSslServer         = psocket->m_bSslServer;
      m_bEnableSsl         = psocket->m_bEnableSsl;

   }

   
   link_in_socket * link_in_socket::from_server(httpd_socket * psocket)
   {

      __pointer(link_in_socket) pinsocket = __new(link_in_socket);

      pinsocket->m_phandler = psocket->socket_handler();

      pinsocket->m_in = psocket;

      ASSERT(pinsocket->m_pmemfileInput != nullptr);

      pinsocket->m_pmemfileInput->from(psocket->m_pmemfileInput);

      pinsocket->server_to_link_in(psocket);

      psocket->m_bEnd = true;

      return pinsocket;

   }


} // namespace sockets




