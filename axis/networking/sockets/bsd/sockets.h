#pragma once


namespace sockets
{

   
   class SSLInitializer;


   class CLASS_DECL_AXIS sockets :
      virtual public sockets_base
   {
   public:

      interlocked_long                             m_lListenSocket;

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
      ::net::port_forward_pointer                       m_spportforward;

      ::mutex                                        m_mutexPool;
      socket_map                                   m_pool; ///< Active sockets map


      sockets();
      virtual ~sockets();

      class ::sockets::net                         & net();

      virtual void initialize(::object * pobject) override;

      virtual void destroy() override;


   };


} // namespace sockets



