#include "framework.h" 
#include "apex/networking/sockets/_sockets.h"

#if defined(FREEBSD)

#include <sys/socket.h>
#include <netinet/in.h>

#endif

#if defined(__arm__)

#if !defined(RASPBIAN)

#include <sys/endian.h>

#endif

#include <arpa/inet.h>

#endif


namespace net
{


   address::address()
   {

#ifdef BSD_STYLE_SOCKETS
      ::zero(this, sizeof(u.m_sa));
      m_iLen = -1;
#endif

//#ifdef _UWP
//
//      m_posdata = new os_data();
//
//#endif
      
   }


   address::address(i32 family, port_t port)
   {

#ifdef BSD_STYLE_SOCKETS

      ::zero(this, sizeof(u.m_sa));

      m_iLen = -1;

      ADDR_STRUCT_SET_FAMILY(u.s, family);

      u.s.m_port = htons(port);

#endif

//#ifdef _UWP
//
//      m_posdata = new os_data();
//
//#endif
      sync_os_service();

   }


#ifdef BSD_STYLE_SOCKETS


   address::address(const sockaddr & sa, int iLen)
   {

//#ifdef _UWP
//
//      m_posdata = new os_data();
//
//#endif

      ::zero(this, sizeof(u.m_sa));

      if (sa.sa_family == AF_INET6)
      {
         m_iLen = iLen <= 0 ? sizeof(sockaddr_in6) : iLen;
         ::memcpy_dup(&u.m_sa, &sa, m_iLen);
         sync_os_address();
         sync_os_service();
      }
      else if (sa.sa_family == AF_INET)
      {
         m_iLen = -1;
         ::memcpy_dup(&u.m_sa, &sa, sizeof(sockaddr_in));
         sync_os_address();
         sync_os_service();
      }
      else
      {
         m_iLen = -1;

         ADDR_STRUCT_SET_FAMILY(u.s, AF_UNSPEC);

      }

   }


   address::address(const in6_addr& a, port_t port)
   {

      ::zero(this, sizeof(u.m_sa));

      m_iLen = -1;
      
      ADDR_STRUCT_SET_FAMILY(u.s, AF_INET6);

      u.s.m_port = htons(port);

      u.m_addr6.sin6_addr = a;

      sync_os_address();

      sync_os_service();

   }


   address::address(const sockaddr_in6& sa, int iLen)
   {

      ::zero(this, sizeof(u.m_sa));

      if (sa.sin6_family != AF_INET6)
      {

         ADDR_STRUCT_SET_FAMILY(u.s, AF_UNSPEC);

      }
      else
      {

         m_iLen = iLen <= 0 ? sizeof(sockaddr_in6) : iLen;

         ::memcpy_dup(&u.m_addr6, &sa, m_iLen);

         sync_os_address();

         sync_os_service();

      }

   }


   address::address(const in_addr& a, port_t port)
   {

      ::zero(this, sizeof(u.m_sa));

      m_iLen = -1;

      ADDR_STRUCT_SET_FAMILY(u.s, AF_INET);

      u.s.m_port = htons(port);

      u.m_addr.sin_addr = a;

      sync_os_address();

      sync_os_service();

   }


   address::address(const sockaddr_in& sa)
   {

      ::zero(this, sizeof(u.m_sa));

      u.m_addr = sa;

      m_iLen = -1;

      if (u.s.ADDR_STRUCT_FAMILY != AF_INET)
      {

         ADDR_STRUCT_SET_FAMILY(u.s, AF_UNSPEC);

      }
      else
      {

         sync_os_address();

         sync_os_service();

      }

   }


#endif


   address::address(const string & host, port_t port)
   {

      ::zero(this, sizeof(address));

#ifdef BSD_STYLE_SOCKETS

      m_iLen = -1;

#endif

      parse_string(host);

#if defined(WINRT_SOCKETS)

      m_port = port;

#endif

#ifdef BSD_STYLE_SOCKETS

      u.s.m_port = htons(port);

#endif

      sync_os_service();

   }


   address::address(::object * pobject, const string & host, const ::string & strService)
   {

#ifdef BSD_STYLE_SOCKETS

      ::zero(this, sizeof(u.m_sa));

      m_iLen = -1;

#endif

      parse_string(host);

#ifdef BSD_STYLE_SOCKETS

      auto psystem = pobject->get_system();

      u.s.m_port = psystem->m_papexsystem->sockets().net().service_port(strService);

#endif

      sync_os_service();

   }


   address::address(const address & address)
   {

//#ifdef _UWP
//
//      m_posdata = new os_data();
//
//#endif

      copy(address);

   }


   address::~address()
   {

//#ifdef _UWP
//
//      delete m_posdata;
//
//#endif

   }


   address & address::operator = (const address & address)
   {

      if (&address == this)
         return *this;

      copy(address);

      return *this;

   }


   bool address::operator == (const address & address) const
   {

      if (&address == this)
         return true;

      return is_equal(address);

   }


   string address::get_display_number() const
   {

//#ifdef _UWP
//
//      if (!is_ipv4() && !is_ipv6() && m_posdata != nullptr && m_posdata->m_hostname != nullptr)
//      {
//
//         ((address *) this)->sync_os_address();
//
//      }
//
//#endif

      string str;

#ifdef BSD_STYLE_SOCKETS

      if (is_ipv4())
      {

         ::to_string(str, (in_addr &)u.m_addr.sin_addr);

      }
      else if (is_ipv6())
      {

         ::to_string(str, (in_addr6 &) u.m_addr6.sin6_addr);

      }

#endif

      return str;

   }


   bool address::is_in_same_net(const ::net::address & addr, const ::net::address & addrMask) const
   {

      if (is_ipv4() && addr.is_ipv4() && addrMask.is_ipv4())
      {

#ifdef BSD_STYLE_SOCKETS

         in_addr a1 = u.m_addr.sin_addr;

         in_addr a2 = addr.u.m_addr.sin_addr;

         in_addr aM = addrMask.u.m_addr.sin_addr;

         __memand(&a1, &a1, &aM, sizeof(a1));

         __memand(&a2, &a2, &aM, sizeof(a2));

         return __memcmp(&a1, &a2, sizeof(aM)) == 0;

#endif

         return false;


      }
      else if (is_ipv6() && addr.is_ipv6() && addrMask.is_ipv6())
      {

#ifdef BSD_STYLE_SOCKETS

         in6_addr a1 = u.m_addr6.sin6_addr;

         in6_addr a2 = addr.u.m_addr6.sin6_addr;

         in6_addr aM = addrMask.u.m_addr6.sin6_addr;

         __memand(&a1, &a1, &aM, sizeof(a1));

         __memand(&a2, &a2, &aM, sizeof(a2));

         return __memcmp(&a1, &a2, sizeof(aM)) == 0;

#endif

         return false;

      }
      else
      {
         return false;
      }

   }

   bool address::is_equal(const address & addr) const
   {


#ifdef BSD_STYLE_SOCKETS

      if (u.s.m_port != addr.u.s.m_port)
         return false;

      if (is_ipv6() && addr.is_ipv6())
      {

         return __memcmp(&u.m_addr6.sin6_addr, &addr.u.m_addr6.sin6_addr, sizeof(in6_addr)) == 0;

      }
      else if (is_ipv4() && addr.is_ipv4())
      {

         return __memcmp(&u.m_addr.sin_addr, &addr.u.m_addr.sin_addr, sizeof(in_addr)) == 0;

      }

      return false;
#else

      return false;

#endif

   }


   void address::sync_os_address()
   {
//#ifdef _UWP
//
//      if (u.s.m_family == AF_INET || u.s.m_family == AF_INET6)
//      {
//         m_posdata->m_hostname = ref new ::winrt::Windows::Networking::HostName(get_display_number());
//      }
//      else if (m_posdata->m_hostname != nullptr)
//      {
//
//         string strDisplayNumber = m_posdata->m_hostname->RawName;
//
//         if (::sockets::net::isipv4(strDisplayNumber))
//         {
//            ::sockets::net::convert(u.m_addr.sin_addr, strDisplayNumber);
//            u.s.m_family = AF_INET;
//         }
//         else if (::sockets::net::isipv6(strDisplayNumber))
//         {
//            ::sockets::net::convert(u.m_addr6.sin6_addr, strDisplayNumber);
//            u.s.m_family = AF_INET;
//         }
//         else
//         {
//            u.s.m_family = AF_UNSPEC;
//         }
//
//      }
//#endif
   }

   void address::sync_os_service()
   {
//#ifdef _UWP
//#endif
   }


#if defined(BSD_STYLE_SOCKETS)

   void * address::addr_data()
   {
      if (u.m_sa.sa_family == AF_INET)
      {
         return &u.m_addr.sin_addr;
      }
      else if (u.m_sa.sa_family == AF_INET6)
      {

         return &u.m_addr6.sin6_addr;

      }
      else
      {

         return nullptr;

      }

   }


#endif


   void address::parse_string(const ::string & strAddress)
   {

#if defined(BSD_STYLE_SOCKETS)

      auto paddressdepartment = ::net::address_department();

      if (paddressdepartment->isipv6(strAddress))
      {
       
         if (paddressdepartment->convert(u.m_addr6.sin6_addr, strAddress))
         {

            u.s.ADDR_STRUCT_FAMILY = AF_INET6;

         }

      }
      else if (paddressdepartment->isipv4(strAddress))
      {

         if (paddressdepartment->convert(u.m_addr.sin_addr, strAddress))
         {

            u.s.ADDR_STRUCT_FAMILY = AF_INET;

         }

      }
      else
      {

         __throw(error_parsing, "Unrecognized networking IP address");

      }

#elif defined(WINRT_SOCKETS)

      m_hostname = ref new ::winrt::Windows::Networking::HostName(strAddress);


#endif

   }


   string address::get_string() const
   {

      string str;

#if defined(BSD_STYLE_SOCKETS)

      if (is_ipv4())
      {

         ::to_string(str, u.m_addr);

      }
      else if (is_ipv6())
      {

         ::to_string(str, u.m_addr6);

      }
         
#endif

      return str;

   }


#if defined(BSD_STYLE_SOCKETS)

   i32 address::sa_len() const
   {

      int iFamilyLen = family_len(u.s.m_family);

      if (m_iLen <= 0)
      {

         return iFamilyLen;

      }
      else
      {

         return m_iLen;

      }

   }


#endif


   void address::copy(const address & address)
   {

      ::memcpy_dup(this, &address, sizeof(address));

      sync_os_address();
      sync_os_service();

   }


   address ipv4(u32 u, port_t port)
   {

      address a;

#if defined(BSD_STYLE_SOCKETS)

      ::zero(&a, sizeof(a));

      a.m_iLen = -1;
      a.u.m_addr.sin_family = AF_INET;
      a.u.m_addr.sin_port = port;
      ::memcpy_dup(&a.u.m_addr.sin_addr, &u, sizeof(a.u.m_addr.sin_addr));
#ifdef WINDOWS
      ::__swap(a.u.m_addr.sin_addr.S_un.S_un_b.s_b1, a.u.m_addr.sin_addr.S_un.S_un_b.s_b4);
      ::__swap(a.u.m_addr.sin_addr.S_un.S_un_b.s_b2, a.u.m_addr.sin_addr.S_un.S_un_b.s_b3);
#else
//      ::__swap(&a.u.m_addr.sin_addr.s_addr.S_un_b.s_b1, &a.u.m_addr.sin_addr.s_addr.S_un_b.s_b4);
//      ::__swap(&a.u.m_addr.sin_addr.s_addr.S_un_b.s_b2, &a.u.m_addr.sin_addr.s_addr.S_un_b.s_b3);
#endif

      a.sync_os_address();
      a.sync_os_service();

#endif

      return a;

   }

   address ipv6(void * p128bits, port_t port)
   {

      address a;

#if defined(BSD_STYLE_SOCKETS)

      ::zero(&a, sizeof(a));

      a.m_iLen = sizeof(sockaddr_in6);
      a.u.m_addr6.sin6_family = AF_INET6;
      a.u.m_addr6.sin6_port = port;
      ::memcpy_dup(&a.u.m_addr6.sin6_addr, p128bits, sizeof(a.u.m_addr6.sin6_addr));

      a.sync_os_address();
      a.sync_os_service();

#endif

      return a;

   }


   port_t address::use_address_service_number_as_offset_for_base_port(port_t portBase) const
   {

      return portBase + get_service_number();

   }


   port_t address::get_service_number() const
   {

#if defined(BSD_STYLE_SOCKETS)

      return ntohs(u.s.m_port);

#elif defined(WINRT_SOCKETS)

      return m_port;

#else

      return 0;

#endif

   }


   void address::set_service_number(port_t port)
   {

#if defined(BSD_STYLE_SOCKETS)

      u.s.m_port = htons(port);

#endif

   }


} // namespace net



