#include "framework.h"
#include "apex/net/sockets/_sockets.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/os/ansios/_pthread.h"


#endif


#include <openssl/ssl.h>


namespace sockets
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


} // namespace sockets





