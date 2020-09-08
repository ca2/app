#pragma once


#if defined(LINUX)
#include <netdb.h>
#define in_addr6 in6_addr
#elif defined(ANDROID)
#include <netdb.h>
#include <netinet/in.h>
#define in_addr6 in6_addr
#endif


namespace net
{


   struct CLASS_DECL_AQUA address
   {
   public:


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


      address();
      address(i32 family, port_t port = 0);
      address(const string & strAddress, port_t port = 0);
      address(::object * pobject, const string & strAddress, const string & strServiceName);
      address(const in_addr & a, port_t port = 0);
      address(const in6_addr & a, port_t port = 0);
      address(const sockaddr_in & a);
      address(const sockaddr_in6 & a, int iLen = -1);
      address(const sockaddr & sa, int iLen = -1);
      address(const address & address);
      ~address();


      address & operator = (const address & address);
      bool operator == (const address & address) const;


      inline void copy(const address & address);

      string get_display_number() const;

      port_t get_service_number() const;
      void set_service_number(port_t iPort);


      bool is_in_same_net(const address & addr,const address & addrMask) const;
      bool is_equal(const address & addr) const;


      inline bool is_ipv4() const;
      inline bool is_ipv6() const;


      inline bool is_valid() const;


      inline i32 get_family() const;


      inline sockaddr * sa();
      inline const sockaddr * sa() const;
      i32 sa_len() const;

      void * addr_data();


      void from_string(const string & strAddress);
      string to_string() const;


      inline void SetFlowinfo(u32 x);
      inline u32 GetFlowinfo();


#ifndef WINDOWS
      inline void SetScopeId(u32 x);
      inline u32 GetScopeId();
#endif

      void sync_os_address();
      void sync_os_service();

   };


   inline i32 address::get_family() const
   {

      return u.s.m_family;

   }



   inline bool address::is_ipv4() const
   {

      return u.s.m_family == AF_INET;

   }


   inline bool address::is_ipv6() const
   {

      return u.s.m_family == AF_INET6;

   }


   inline bool address::is_valid() const
   {

      return is_ipv6() || is_ipv4()
//#if defined _UWP && defined(__cplusplus_winrt)
//         || (m_posdata != nullptr && m_posdata->m_hostname != nullptr)
//#endif
         ;

   }


   inline sockaddr * address::sa()
   {

      return &u.m_sa;

   }


   inline const sockaddr * address::sa() const
   {

      return &u.m_sa;

   }


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


   CLASS_DECL_AQUA address ipv4(u32 ui, port_t port = 0);

   CLASS_DECL_AQUA address ipv6(void * p128bits, port_t port = 0);

} // namespace sockets





inline void __exchange(::stream& s, ::net::address& address);


