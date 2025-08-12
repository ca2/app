#pragma once


//#include "apex/networking/sockets/sockets_base.h"
//#include "apex/networking/sockets/bsd/ssl/client_context_map.h"
////#include "acme/prototype/prototype/object.h"


namespace sockets
{

   
   class SSLInitializer;


   class CLASS_DECL_APEX sockets :
      virtual public ::object
   {
   public:


      int                                          m_iErrorCode;

      sockets();
      ~sockets() override;

      virtual void initialize(::particle * pparticle) override;

      virtual void destroy() override;

//      interlocked_int                  m_lListenSocket;
//
//      ::pointer<SSLInitializer>       m_psslinit;
//
//      //unsigned char                             m_baTicketKey[SSL_SESSION_TICKET_KEY_SIZE];
//
////#if defined(BSD_STYLE_SOCKETS)
////      ::pointer<ssl_client_context_map>          m_pclientcontextmap;
////#endif
//
//      ::collection::count                          m_countHttpPostBoundary;
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
//      socket_map                       m_pool; ///< Active sockets map_base
//

      //sockets();
      //~sockets() override;

      class ::networking::networking * networking();

      //virtual void initialize(::particle * pparticle) override;

      //virtual void destroy() override;

      //virtual string get_http_post_boundary();

      virtual ::pointer<::networking::address>create_address(const ::scoped_string & scopedstrHostname);


   };


} // namespace sockets



