#pragma once


namespace sockets
{


   class CLASS_DECL_APEX sockets :
      virtual public ::apex::department
   {
   public:

      i32                                       m_iErrorCode;
#ifdef HAVE_OPENSSL
      ssl_client_context_map                    m_clientcontextmap;
#endif

#ifdef _UWP
      long                                      m_lHttpGetSerial;
#endif

#ifdef AJP_SOCKET
      AjpBaseSocket::Initializer *              m_pajpbasesocketinit;
#endif

      count                                     m_countHttpPostBoundary;
      ::mutex                                   m_mutexHttpPostBoundary;

      resolv_socket::cache_t                    m_resolvcache;
      resolv_socket::timeout_t                  m_resolvtimeout;
      ::mutex                                   m_mutexResolvCache;

      __pointer(::sockets::net)                 m_spnet;


      sockets();
      virtual ~sockets();


      class ::sockets::net& net();


      virtual ::e_status initialize(::context_object * pcontextobject) override;
      virtual void finalize() override;

//      virtual void http_config_proxy(const char * pszUrl, http_tunnel * psocket);

   };


} // namespace sockets



