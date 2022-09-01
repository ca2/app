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

      byte                                         m_baTicketKey[SSL_SESSION_TICKET_KEY_SIZE];

#if defined(BSD_STYLE_SOCKETS)
      ssl_client_context_map                       m_clientcontextmap;
#endif
      AjpBaseSocket::Initializer *                 m_pajpaxissocketinit;

      ::count m_countHttpPostBoundary;
      ::mutex                                        m_mutexHttpPostBoundary;

      resolv_socket::cache_t                       m_resolvcache;
      resolv_socket::timeout_t                     m_resolvtimeout;
      ::mutex                                        m_mutexResolvCache;
      __pointer(::sockets::net)                           m_spnet;
      ::net::port_forward_sp                       m_spportforward;

      ::mutex                                        m_mutexPool;
      socket_map                                   m_pool; ///< Active sockets map


      sockets(::object * pobject);
      virtual ~sockets();

      class ::sockets::net                         & net();

      bool init1();

      void     destroy() override;


   };


} // namespace sockets



