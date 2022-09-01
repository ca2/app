#pragma once


#include "apex/networking/sockets/sockets_base.h"
//#include "apex/networking/sockets/bsd/ssl/client_context_map.h"


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
      __pointer(ssl_client_context_map)           m_pclientcontextmap;
#endif

      ::count                          m_countHttpPostBoundary;
      ::mutex                          m_mutexHttpPostBoundary;

      resolv_cache_t                   m_resolvcache;
      resolv_timeout_t                 m_resolvtimeout;
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

      virtual void initialize(::object * pobject) override;

      virtual void destroy() override;

      virtual string get_http_post_boundary();


   };


} // namespace sockets



