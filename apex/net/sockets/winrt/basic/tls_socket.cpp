#include "framework.h"
#include "apex/net/sockets/_sockets.h"


namespace sockets
{


   tls_socket::tls_socket(::sockets::) :
      ::object(h.get_application()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h)
   {
   }


   tls_socket::~tls_socket()
   {
   }

   void tls_socket::InitSSLClient()
   {
#ifdef HAVE_OPENSSL
      InitializeContext(m_strCat, TLSv1_client_method());
#endif
   }


} // namespace sockets



