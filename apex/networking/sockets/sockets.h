#pragma once


//#include "apex/networking/sockets/sockets_base.h"
//#include "apex/networking/sockets/bsd/ssl/client_context_map.h"
//#include "acme/primitive/primitive/object.h"


namespace sockets
{

   
   class SSLInitializer;


   class CLASS_DECL_APEX sockets :
      virtual public ::object
   {
   public:


      i32                                          m_iErrorCode;

      sockets();
      ~sockets() override;

      virtual void initialize(::particle * pparticle) override;

      virtual void destroy() override;

//      interlocked_i32                  m_lListenSocket;
//
//      ::pointer<SSLInitializer>       m_psslinit;
//
//      //byte                             m_baTicketKey[SSL_SESSION_TICKET_KEY_SIZE];
//
////#if defined(BSD_STYLE_SOCKETS)
////      ::pointer<ssl_client_context_map>          m_pclientcontextmap;
////#endif
//
//      ::count                          m_countHttpPostBoundary;
//      ::pointer < ::mutex >                          m_pmutexHttpPostBoundary;
//
//      //resolv_cache_t                   m_resolvcache;
//      //resolv_timeout_t                 m_resolvtimeout;
//      ::pointer < ::mutex >                          m_pmutexResolvCache;
        ::pointer<::networking::networking>       m_pnetworking;
//#ifdef WINDOWS
//      ::net::port_forward_pointer      m_pportforward;
//#endif
//
//      ::pointer < ::mutex >                          m_pmutexPool;
//      socket_map                       m_pool; ///< Active sockets map
//

      //sockets();
      //~sockets() override;

      class ::networking::networking * networking();

      //virtual void initialize(::particle * pparticle) override;

      //virtual void destroy() override;

      //virtual string get_http_post_boundary();

      virtual ::pointer<::networking::address>create_address(const ::string & strHostname);


   };


} // namespace sockets



