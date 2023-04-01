#pragma once


#include "acme/primitive/primitive/particle.h"


namespace networking
{


   class CLASS_DECL_APEX address :
      virtual public ::particle
   {
   public:

      void * m_p2;


      address();
      //address(const address& address);
      ////address(i32 family, ::networking::port_t port = 0);
      //address(const ::string & strAddress, ::networking::port_t port = 0);
      //address(::particle * pparticle, const ::string & strAddress, const ::string & strServiceName);
//#if defined(BSD_STYLE_SOCKETS)
//      address(const in_addr & a, ::networking::port_t port = 0);
//      address(const in6_addr & a, ::networking::port_t port = 0);
//      address(const sockaddr_in & a);
//      address(const sockaddr_in6 & a, int iLen = -1);
//      address(const sockaddr & sa, int iLen = -1);
//#endif
      ~address();


      //virtual address & operator = (const address & address);
      //virtual bool operator == (const address & address) const;


      //virtual  void copy(address * paddress);

      virtual string get_display_number() const;

      virtual ::networking::port_t get_service_number() const;
      virtual ::networking::port_t use_address_service_number_as_offset_for_base_port(::networking::port_t portBase) const;
      virtual void set_service_number(::networking::port_t port);


      virtual bool is_in_same_net(address * paddress,address * paddressMask) const;
      virtual bool is_equal(address * paddress) const;


      virtual  bool is_ip4() const;
      virtual  bool is_ip6() const;


      virtual  bool is_valid() const;


      //virtual  i32 get_family() const;


//#if defined(BSD_STYLE_SOCKETS)
//
//      inline sockaddr * sa();
//      inline const sockaddr * sa() const;
//      i32 sa_len() const;
//
//      void * addr_data();
//
//#endif

      //virtual void parse_string(const ::string & strAddress);
      //virtual string get_string() const;

//#ifdef BSD_STYLE_SOCKETS
//      virtual  void SetFlowinfo(u32 x);
//      virtual  u32 GetFlowinfo();
//#endif
//
//#ifndef WINDOWS
//      virtual  void SetScopeId(u32 x);
//      virtual  u32 GetScopeId();
//#endif

      virtual void sync_os_address();
      virtual void sync_os_service();



   };


//   inline i32 address::get_family() const
//   {
//
//#if defined(BSD_STYLE_SOCKETS)
//
//      return u.s.get_family();
//
//#elif defined(WINRT_SOCKETS)
//
//      if (is_ipv4())
//      {
//
//         return AF_INET;
//
//      }
//      else if (is_ipv6())
//      {
//
//         return AF_INET6;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//#else
//
//#error "what socket?"
//
//#endif
//
//
//   }
//
//
//
//   inline bool address::is_ipv4() const
//   {
//
//
//#if defined(BSD_STYLE_SOCKETS)
//
//      return get_family() == AF_INET;
//
//#elif defined(WINRT_SOCKETS)
//
//      return false;
//
//#else
//
//#error "what socket?"
//
//#endif
//
//
//   }
//
//
//   inline bool address::is_ipv6() const
//   {
//
//
//#if defined(BSD_STYLE_SOCKETS)
//
//      return get_family() == AF_INET6;
//
//#elif defined(WINRT_SOCKETS)
//
//      return false;
//
//#else
//
//#error "what socket?"
//
//#endif
//
//   }
//
//
//   inline bool address::is_valid() const
//   {
//
//      return is_ipv6() || is_ipv4()
////#if defined UNIVERSAL_WINDOWS && defined(__cplusplus_winrt)
////         || (m_posdata != nullptr && m_posdata->m_hostname != nullptr)
////#endif
//         ;
//
//   }
//
//
//
//#ifdef BSD_STYLE_SOCKETS
//
//
//   inline sockaddr * address::sa()
//   {
//
//      return &u.m_sa;
//
//   }
//
//
//   inline const sockaddr * address::sa() const
//   {
//
//      return &u.m_sa;
//
//   }
//
//
//#endif
//
//
//#ifdef BSD_STYLE_SOCKETS
//
//
//   inline void address::SetFlowinfo(u32 x)
//   {
//      ASSERT(is_ipv6());
//      u.m_addr6.sin6_flowinfo = x;
//   }
//
//
//   inline u32 address::GetFlowinfo()
//   {
//      ASSERT(is_ipv6());
//      return u.m_addr6.sin6_flowinfo;
//   }
//
//
//#endif
//
//
//#ifndef WINDOWS
//
//   inline void address::SetScopeId(u32 x)
//   {
//      ASSERT(is_ipv6());
//      u.m_addr6.sin6_scope_id = x;
//   }
//
//
//   inline u32 address::GetScopeId()
//   {
//      ASSERT(is_ipv6());
//      return u.m_addr6.sin6_scope_id;
//   }
//
//#endif
////
//
//   CLASS_DECL_APEX address ipv4(u32 u, ::networking::port_t port = 0);
//
//   CLASS_DECL_APEX address ipv6(void * p128bits, ::networking::port_t port = 0);

} // namespace networking



//
//
//inline void __exchange(::stream& s, ::networking::address& address);
//

