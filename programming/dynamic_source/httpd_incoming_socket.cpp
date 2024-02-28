#include "framework.h"
#include "httpd_incoming_socket.h"


namespace dynamic_source
{


   httpd_incoming_socket::httpd_incoming_socket()
   {

      //m_posdataNetnodeSocket = nullptr;

      m_iCa2FetchMode = 0;

   }



   httpd_incoming_socket::~httpd_incoming_socket()
   {

   }


   void httpd_incoming_socket::Reset()
   {

      ::httpd::incoming_socket::Reset();

      m_iCa2FetchMode = 0;

   }


   void httpd_incoming_socket::finalize()
   {

      //m_pscript.release();

   }


} // namespace dynamic_source



