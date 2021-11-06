#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   httpd_socket::httpd_socket()
   {

      m_posdataNetnodeSocket = nullptr;

      m_iCa2FetchMode = 0;

   }



   httpd_socket::~httpd_socket()
   {

   }


   void httpd_socket::Reset()
   {

      ::sockets::httpd_socket::Reset();

      m_iCa2FetchMode = 0;

   }


} // namespace dynamic_source



