#pragma once


#if defined(LINUX) || defined(FREEBSD)
#include <netdb.h>
#define in_addr6 in6_addr
#elif defined(ANDROID)
#include <netdb.h>
#include <netinet/in.h>
#define in_addr6 in6_addr
#endif


namespace net
{


   class CLASS_DECL_APEX address
   {
   public:


#ifdef BSD_STYLE_SOCKETS

      union address_union
      {


         struct address_struct
         {


            u16 m_family;
            u16 m_port;

         } s;


         struct sockaddr_in      m_addr;
         struct sockaddr_in6     m_addr6;
         struct sockaddr         m_sa;


      } u;

      int   m_iLen;


#elif defined(WINRT_SOCKETS)

      //::winrt::Windows::Networking::HostName^ m_hostname;
      //port_t      m_port;


#else

#error "what sockets?"


#endif


      address();
      address(const address& address);
      address(i32 family, port_t port = 0);
      address(const ::string & strAddress, port_t port = 0);
      address(::object * pobject, const ::string & strAddress, const ::string & strServiceName);
#if defined(BSD_STYLE_SOCKETS)
      address(const in_addr & a, port_t port = 0);
      address(const in6_addr & a, port_t port = 0);
      address(const sockaddr_in & a);
      address(const sockaddr_in6 & a, int iLen = -1);
      address(const sockaddr & sa, int iLen = -1);
#endif
      ~address();


      address & operator = (const address & address);
      bool operator == (const address & address) const;


      inline void copy(const address & address);

      string get_display_number() const;

      port_t get_service_number() const;
      port_t use_address_service_number_as_offset_for_base_port(port_t portBase) const;
      void set_service_number(port_t port);


      bool is_in_same_net(const address & addr,const address & addrMask) const;
      bool is_equal(const address & addr) const;


      inline bool is_ipv4() const;
      inline bool is_ipv6() const;


      inline bool is_valid() const;


      inline i32 get_family() const;


#if defined(BSD_STYLE_SOCKETS)

      inline sockaddr * sa();
      inline const sockaddr * sa() const;
      i32 sa_len() const;

      void * addr_data();

#endif

      void parse_string(const ::string & strAddress);
      string get_string() const;

#ifdef BSD_STYLE_SOCKETS
      inline void SetFlowinfo(u32 x);
      inline u32 GetFlowinfo();
#endif

#ifndef WINDOWS
      inline void SetScopeId(u32 x);
      inline u32 GetScopeId();
#endif

      void sync_os_address();
      void sync_os_service();

   };


   inline i32 address::get_family() const
   {

#if defined(BSD_STYLE_SOCKETS)

      return u.s.m_family;

#elif defined(WINRT_SOCKETS)

      if (is_ipv4())
      {

         return AF_INET;

      }
      else if (is_ipv6())
      {

         return AF_INET6;

      }
      else
      {

         return -1;

      }

#else

#error "what socket?"

#endif


   }



   inline bool address::is_ipv4() const
   {


#if defined(BSD_STYLE_SOCKETS)

      return u.s.m_family == AF_INET;

#elif defined(WINRT_SOCKETS)

      return false;

#else

#error "what socket?"

#endif


   }


   inline bool address::is_ipv6() const
   {


#if defined(BSD_STYLE_SOCKETS)

      return u.s.m_family == AF_INET6;

#elif defined(WINRT_SOCKETS)

      return false;

#else

#error "what socket?"

#endif

   }


   inline bool address::is_valid() const
   {

      return is_ipv6() || is_ipv4()
//#if defined _UWP && defined(__cplusplus_winrt)
//         || (m_posdata != nullptr && m_posdata->m_hostname != nullptr)
//#endif
         ;

   }



#ifdef BSD_STYLE_SOCKETS


   inline sockaddr * address::sa()
   {

      return &u.m_sa;

   }


   inline const sockaddr * address::sa() const
   {

      return &u.m_sa;

   }


#endif


#ifdef BSD_STYLE_SOCKETS


   inline void address::SetFlowinfo(u32 x)
   {
      ASSERT(is_ipv6());
      u.m_addr6.sin6_flowinfo = x;
   }


   inline u32 address::GetFlowinfo()
   {
      ASSERT(is_ipv6());
      return u.m_addr6.sin6_flowinfo;
   }


#endif


#ifndef WINDOWS

   inline void address::SetScopeId(u32 x)
   {
      ASSERT(is_ipv6());
      u.m_addr6.sin6_scope_id = x;
   }


   inline u32 address::GetScopeId()
   {
      ASSERT(is_ipv6());
      return u.m_addr6.sin6_scope_id;
   }

#endif


   CLASS_DECL_APEX address ipv4(u32 u, port_t port = 0);

   CLASS_DECL_APEX address ipv6(void * p128bits, port_t port = 0);

} // namespace sockets





inline void __exchange(::stream& s, ::net::address& address);


