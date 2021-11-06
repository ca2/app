#pragma once


namespace sockets
{

   
   class SSLInitializer;


   class CLASS_DECL_APEX sockets :
      virtual public sockets_base
   {
   public:


      interlocked_i32                  m_lListenSocket;

      __pointer(SSLInitializer)        m_psslinit;

      byte                             m_baTicketKey[SSL_SESSION_TICKET_KEY_SIZE];

#if defined(BSD_STYLE_SOCKETS)
      ssl_client_context_map           m_clientcontextmap;
#endif

      ::count                          m_countHttpPostBoundary;
      ::mutex                          m_mutexHttpPostBoundary;

      resolv_socket::cache_t           m_resolvcache;
      resolv_socket::timeout_t         m_resolvtimeout;
      ::mutex                          m_mutexResolvCache;
      __pointer(::sockets::net)        m_pnet;
#ifdef WINDOWS
      ::net::port_forward_pointer      m_pportforward;
#endif

      ::mutex                          m_mutexPool;
      socket_map                       m_pool; ///< Active sockets map


      sockets();
      virtual ~sockets();

      class ::sockets::net                         & net();

      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status destroy() override;

      virtual string get_http_post_boundary();


   };


} // namespace sockets



