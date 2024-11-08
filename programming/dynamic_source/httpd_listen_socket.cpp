#include "framework.h"
#include "httpd_socket.h"


namespace dynamic_source
{


   httpd_socket::httpd_socket()
   {

      //m_posdataNetnodeSocket = nullptr;

      m_iCa2FetchMode = 0;

   }



   httpd_socket::~httpd_socket()
   {

   }


   void httpd_socket::Reset()
   {

      ::httpd::socket::Reset();

      m_iCa2FetchMode = 0;

   }


   void httpd_socket::destroy()
   {

      m_pscript.release();

      ::httpd::socket::destroy();

   }


} // namespace dynamic_source



