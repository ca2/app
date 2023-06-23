#pragma once


namespace sockets
{

   class SSLInitializer;

   class CLASS_DECL_APEX sockets :
      virtual public ::acme::department
   {
   public:


      i32                                      m_iErrorCode;

      SSLInitializer *                             m_psslinit;

      ::u8                                         m_baTicketKey[SSL_SESSION_TICKET_KEY_SIZE];

#if defined(BSD_STYLE_SOCKETS)
      ssl_client_context_map                       m_clientcontextmap;
#endif
      AjpBaseSocket::Initializer *                 m_pajpaxissocketinit;

      ::count m_countHttpPostBoundary;
      ::pointer < ::mutex >                                        m_pmutexHttpPostBoundary;

      resolv_socket::cache_t                       m_resolvcache;
      resolv_socket::timeout_t                     m_resolvtimeout;
      ::pointer < ::mutex >                                        m_pmutexResolvCache;
      ::pointer<::sockets::net>                          m_spnet;
      ::net::port_forward_sp                       m_spportforward;

      ::pointer < ::mutex >                                        m_pmutexPool;
      socket_map                                   m_pool; ///< Active sockets map


      sockets(::particle * pparticle);
      virtual ~sockets();

      class ::sockets::net                         & net();

      bool init1();

      void     destroy() override;


   };


} // namespace sockets



