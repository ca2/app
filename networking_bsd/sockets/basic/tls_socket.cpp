#include "framework.h"
#include "tls_socket.h"


namespace sockets_bsd
{


   tls_socket::tls_socket() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h)
   {

   }


   tls_socket::~tls_socket()
   {

   }

   void tls_socket::InitSSLClient()
   {

      InitializeContext(m_strCat, TLS_client_method());

   }


} // namespace sockets_bsd



