#include "framework.h" 
#include "aura/net/sockets/_.h"



namespace sockets
{



   link_out_socket::link_out_socket(base_socket_handler & h) : 
      ::object(&h),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h, 32000, 32000),
      m_in(nullptr),
      m_out(nullptr)
   {
   }


   link_out_socket::~link_out_socket()
   {
   }

   void link_out_socket::OnRead( char *buf, memsize n )
   {

      m_in->link_write(buf, n);

   }

   void link_out_socket::link_write(void * p, memsize size)
   {
      m_out->write((const char *) p, size);
   }


   void link_out_socket::server_to_link_out(httpd_socket * psocket)
   {
      
      socket_handler & h = dynamic_cast < socket_handler & > (psocket->Handler());
      
      auto p = h.m_sockets.begin();

      SOCKET key;

      for (; p; p++)
      {

         if(p->m_psocket == psocket)
         {

            h.m_sockets.set_at(key, this);

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


} // namespace sockets