

namespace sockets
{


   tls_socket::tls_socket(::sockets::base_socket_handler& h) :
      ::object(h.get_context_application()),
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


