#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sockets :
      virtual public ::aura::department
   {
   public:

      i32                                      m_iErrorCode;
#ifdef HAVE_OPENSSL
      ssl_client_context_map                       m_clientcontextmap;
#endif

      AjpBaseSocket::Initializer *                 m_pajpbasesocketinit;

      count                                        m_countHttpPostBoundary;
      ::mutex                                        m_mutexHttpPostBoundary;

      resolv_socket::cache_t                       m_resolvcache;
      resolv_socket::timeout_t                     m_resolvtimeout;
      ::mutex                                        m_mutexResolvCache;

      __pointer(::sockets::net)                           m_spnet;


      sockets(::object * pobject);


      bool init1();
      bool finalize();


      virtual void http_config_proxy(const char * pszUrl, http_tunnel * psocket);


      class ::sockets::net & net();

   };


} // namespace sockets



