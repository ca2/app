#pragma once


namespace sockets
{


   class CLASS_DECL_APEX sockets :
      virtual public ::acme::department
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
      ::pointer < ::mutex >                                   m_pmutexHttpPostBoundary;

      resolv_socket::cache_t                    m_resolvcache;
      resolv_socket::timeout_t                  m_resolvtimeout;
      ::pointer < ::mutex >                                   m_pmutexResolvCache;

      ::pointer<::sockets::net>                m_spnet;


      sockets();
      virtual ~sockets();


      class ::sockets::net& net();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;

//      virtual void http_config_proxy(const ::scoped_string & scopedstrUrl, http_tunnel * psocket);

   };


} // namespace sockets



