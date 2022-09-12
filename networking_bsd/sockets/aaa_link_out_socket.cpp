#include "framework.h" 




namespace networking_bsd
{



   link_out_socket::link_out_socket() : 
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
      
      //socket_handler * h = dynamic_cast < socket_handler * > (psocket->socket_handler());

      __pointer(::networking_bsd::socket_handler) phandler = psocket->socket_handler();
      
      auto p = phandler->m_socketmap.begin();

      SOCKET key = psocket->m_socket;

      for (; p; p++)
      {

         if(p->m_psocket == psocket)
         {

            phandler->m_socketmap.set_at(key, this);

         }

      }

      m_socket             = psocket->m_socket;

      m_bConnecting        = psocket->m_bConnecting; ///< Flag indicating connection in progress
      //m_secsConnectionTimeout    = psocket->m_secsConnectionTimeout; ///< Connection timeout (seconds)
      m_bFlushBeforeClose = psocket->m_bFlushBeforeClose; ///< Send all data before closing (default true)
      m_iMaximumConnectionRetryCount   = psocket->m_iMaximumConnectionRetryCount; ///< Maximum connection retries (tcp)
      m_iConnectionRetryCount            = psocket->m_iConnectionRetryCount; ///< Actual number of connection retries (tcp)
      m_bCallOnConnect    = psocket->m_bCallOnConnect; ///< OnConnect will be called next base_socket_handler cycle if true
      m_bRetryClientConnect    = psocket->m_bRetryClientConnect; ///< Try another connection attempt next base_socket_handler cycle
      m_iShutdownStatus           = psocket->m_iShutdownStatus; ///< Shutdown status

      m_bSsl               = psocket->m_bSsl;
      m_bReconnect         = psocket->m_bReconnect;
      m_bSsl               = psocket->m_bSsl;
      m_bSslServer         = psocket->m_bSslServer;
      m_bEnableSsl         = psocket->m_bEnableSsl;

   }


} // namespace networking_bsd
