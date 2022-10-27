#pragma once


#include "apex/networking/sockets/basic/tcp_socket.h"


namespace sockets
{


   /** Async DNS resolver socket. 
   \ingroup async */
   class CLASS_DECL_APEX resolv_socket : public tcp_socket
   {
   public:



      string                                          m_query;
      string                                          m_data;
      bool                                            m_bServer;
      base_socket *                                   m_parent;
      i32                                             m_resolv_id;
      string                                          m_resolv_host;
      ::networking::port_t                                          m_resolv_port;
      //in_addr                                         m_resolv_address;
      bool                                            m_resolve_ipv6;
      //in6_addr                                        m_resolv_address6;
      bool                                            m_cached;


      ::pointer<::apex::system>                      acmesystem();
      ::pointer<::networking::networking>     m_pnetworking;


      resolv_socket();
      resolv_socket(base_socket *parent, const string & host, ::networking::port_t port, bool ipv6 = false);
      //resolv_socket(base_socket *parent, in_addr);
      ///resolv_socket(base_socket *parent, in6_addr&);
      ~resolv_socket();

      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;

      void OnAccept() override { m_bServer = true; }
      void OnLine(const string & line) override;
      void OnDetached() override;
      void OnDelete() override;

      void SetId(i32 x) { m_resolv_id = x; }
      i32 GetId() { return m_resolv_id; }

      void OnConnect() override;

      void SetResolveIpv6(bool x = true) { m_resolve_ipv6 = x; }

      

   };


} // namespace sockets





