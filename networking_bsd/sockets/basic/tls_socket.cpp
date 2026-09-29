#include "platform.h"
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
       
                          //const SSL_METHOD *meth = meth_in;
                          
                          const SSL_METHOD *meth;
                   
                   //if(::is_null(meth))
                   {


#if OPENSSL_VERSION_NUMBER >= 0x10100000L

meth = TLS_client_method();

#else

meth = SSLv23_client_method();

#endif


}


      InitializeContext(m_strCat, meth);

   }


} // namespace sockets_bsd



