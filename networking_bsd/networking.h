// Created by camilo on 2021-03-10 06:22 BRT ThomasBS_!!
#pragma once


#include "apex/networking/networking.h"
#include "address.h"
#include "networking_bsd/sockets/ssl/client_context_map.h"
#include "sockets/_collection.h"
#include "acme/primitive/collection/string_map.h"


namespace sockets_bsd
{


   /* type, host, result */
   typedef string_map < ::string_to_string >       resolv_cache_t;

   /* type, host, time */
   typedef string_map < string_map < time_t > >    resolv_timeout_t;


} // namespace sockets_bsd


namespace networking_bsd
{




   class CLASS_DECL_NETWORKING_BSD networking :
      public ::networking::networking
   {
   public:


      string         m_host; ///< local hostname
      in_addr        m_ip; ///< local ip address
      string         m_addr; ///< local ip address in string format
      string         m_local_addr6; ///< local ip address in string format
      in6_addr       m_local_ip6; ///< local ipv6 address
      bool           m_local_resolved; ///< ResolveLocal has been called if true
      bool           m_bInitialized;


      class CLASS_DECL_NETWORKING_BSD dns_cache_item :
         virtual public ::object
      {
      public:


         in_addr           m_ipaddr;
         class ::time m_timeLastChecked;
         bool              m_bOk;
         bool              m_bTimeout;


         dns_cache_item();
         dns_cache_item(const dns_cache_item& item);


         //void write(::binary_stream < FILE > & stream) const override;
         //void read(::binary_stream < FILE >& stream) override;

         dns_cache_item& operator = (const dns_cache_item& item);


      };


      class CLASS_DECL_NETWORKING_BSD reverse_cache_item :
         virtual public ::matter
      {
      public:

         
         ::pointer<::networking_bsd::address>   m_paddress;
         string                                 m_strIpAddress;
         string                                 m_strReverse;
         class ::time                             m_timeLastChecked;
         bool                                   m_bOk;
         bool                                   m_bTimeout;
         bool                                   m_bProcessing;


         reverse_cache_item();
         reverse_cache_item(const reverse_cache_item& item);

         //void write(::binary_stream < FILE > & stream) const override;
         //void read(::binary_stream < FILE >& stream);

         reverse_cache_item& operator = (const reverse_cache_item& item);

      };

      ::pointer < ::mutex >                              m_pmutexCache;
      ::pointer < ::mutex >                              m_pmutexReverseCache;
      string_map < dns_cache_item >                      m_mapCache;
      string_map < ::pointer<reverse_cache_item >>       m_mapReverseCache;
      array < ::pointer<reverse_cache_item >>            m_reversecacheaRequest;
      ::task_pointer                                     m_pthreadReverse;
      ::i64                                              m_iListenSocket;
      /*::pointer < ::mutex > m_pmutexPool;*/

      interlocked_i32                                    m_lListenSocket;

      ::pointer<::sockets_bsd::SSLInitializer>           m_psslinit;

      byte                                               m_baTicketKey[SSL_SESSION_TICKET_KEY_SIZE];

#if defined(BSD_STYLE_SOCKETS)
      ::sockets_bsd::ssl_client_context_map              m_clientcontextmap;
#endif

      ::count                                            m_countHttpPostBoundary;
      ::pointer < ::mutex >                              m_pmutexHttpPostBoundary;

      ::sockets_bsd::resolv_cache_t                      m_resolvcache;
      ::sockets_bsd::resolv_timeout_t                    m_resolvtimeout;
      ::pointer < ::mutex >                              m_pmutexResolvCache;
      //::pointer<::sockets::net>                        m_pnet;
#ifdef WINDOWS
      ::net::port_forward_pointer                        m_pportforward;
#endif

      ::pointer < ::mutex >                              m_pmutexPool;
      ::sockets_bsd::socket_map                          m_pool; ///< Active sockets map


      networking();
      ~networking() override;


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;

      virtual bool gudo_set() override;


      /*
      * Encode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_encode(const string& src) override;

      /*
      * Decode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_decode(const string& src) override;

      bool is_ip4(const string& str) override;

      bool is_ip6(const string& str) override;

      virtual bool convert(struct ::in_addr& l, const string& str, i32 ai_flags = 0);
      virtual bool convert(struct ::in6_addr& l, const string& str, i32 ai_flags = 0);
      virtual bool convert(string& str, const struct ::in_addr& inaddr);
      virtual bool convert(string& str, const struct ::in6_addr& inaddr6);

      virtual i32 in6_addr_compare(struct ::in6_addr a, struct ::in6_addr b);

      virtual void ResolveLocal();

      virtual const string& GetLocalHostname();

      virtual in_addr GetLocalIP();

      virtual const string& GetLocalAddress();

      virtual const struct in6_addr& GetLocalIP6();

      virtual const string& GetLocalAddress6();

      virtual string Sa2String(sockaddr* psa);

      bool reverse(string& hostname, ::networking::address * address) override;

      virtual bool reverse_schedule(reverse_cache_item* pitem);

      virtual bool reverse_sync(reverse_cache_item* pitem);

      bool reverse(string& hostname, const string& number) override;


      bool u2service(const string& name, i32& service, i32 ai_flags) override;

      i32 service_port(const string& str, i32 flags = 0) override;

      string  service_name(i32 iPort, i32 flags = 0) override;


      string canonical_name(::networking::address * address) override;

      string service_name(::networking::address * address) override;

      string reverse_name(::networking::address * address) override;
      
      //i32 _select(::sockets::socket_handler * psockethandler, const class time & timeWait) override;

      ::pointer<::networking::address>create_ip4_address(const ::string & strIp4, ::networking::port_t port = 0) override;

      ::pointer<::networking::address>create_ip6_address(const ::string & strIp6, ::networking::port_t port = 0) override;

      ::pointer<address>create_ip4_address(u32 u, ::networking::port_t port = 0);

      ::pointer<address>create_ip6_address(void * p128bits, ::networking::port_t port = 0);

    

      //sockets();
      //virtual ~sockets();

      //class ::sockets::net & net();

      //virtual void initialize(::particle * pparticle) override;

      //virtual void destroy() override;

      virtual string get_http_post_boundary();


      ::pointer_array < ::networking::address > list_computers() override;


      ::pointer_array < ::networking::address > list_network_interfaces() override;


   };

   //CLASS_DECL_NETWORKING_BSD class address_department * address_department();

} // namespace net


