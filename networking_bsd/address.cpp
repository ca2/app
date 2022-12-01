#include "framework.h" 
#include "address.h"
#include "networking.h"


namespace networking_bsd
{


   address::address()
   {

      m_p2 = this;

#ifdef BSD_STYLE_SOCKETS
      ::zero(&u, sizeof(u));
      m_iLen = -1;
#endif

//#ifdef _UWP
//
//      m_posdata = memory_new os_data();
//
//#endif
      
   }


   void address::set_family(i32 family, ::networking::port_t port)
   {

#ifdef BSD_STYLE_SOCKETS

      ::zero(&u.m_sa, sizeof(u.m_sa));

      m_iLen = -1;

      u.s.set_family(family);

      u.s.m_port = htons(port);

#endif

//#ifdef _UWP
//
//      m_posdata = memory_new os_data();
//
//#endif
      sync_os_service();

   }


#ifdef BSD_STYLE_SOCKETS


   void address::set_address(const sockaddr & sa, int iLen)
   {

//#ifdef _UWP
//
//      m_posdata = memory_new os_data();
//
//#endif

      ::zero(&u.m_sa, sizeof(u.m_sa));

      if (sa.sa_family == AF_INET6)
      {
         m_iLen = iLen <= 0 ? sizeof(sockaddr_in6) : iLen;
         ::memcpy_dup(&u.m_addr6, &sa, m_iLen);
         sync_os_address();
         sync_os_service();
      }
      else if (sa.sa_family == AF_INET)
      {
         m_iLen = iLen <= 0 ? sizeof(sockaddr_in) : iLen;
         u.m_sa = sa;
         sync_os_address();
         sync_os_service();
      }
      else
      {
         m_iLen = -1;

         u.s.set_family(AF_UNSPEC);

      }

   }


   void address::set_address(const in6_addr& a, ::networking::port_t port)
   {

      ::zero(this, sizeof(u.m_sa));

      m_iLen = -1;
      
      u.s.set_family(AF_INET6);

      u.s.m_port = htons(port);

      u.m_addr6.sin6_addr = a;

      sync_os_address();

      sync_os_service();

   }


   void address::set_address(const sockaddr_in6& sa, int iLen)
   {

      ::zero(this, sizeof(u.m_sa));

      if (sa.sin6_family != AF_INET6)
      {

         u.s.set_family(AF_UNSPEC);

      }
      else
      {

         m_iLen = iLen <= 0 ? sizeof(sockaddr_in6) : iLen;

         ::memcpy_dup(&u.m_addr6, &sa, m_iLen);

         sync_os_address();

         sync_os_service();

      }

   }


   void address::set_address(const in_addr& a, ::networking::port_t port)
   {

      ::zero(this, sizeof(u.m_sa));

      m_iLen = -1;

      u.s.set_family(AF_INET);

      u.s.m_port = htons(port);

      u.m_addr.sin_addr = a;

      sync_os_address();

      sync_os_service();

   }


   void address::set_address(const sockaddr_in& sa)
   {

      ::zero(this, sizeof(u.m_sa));

      u.m_addr = sa;

      m_iLen = -1;

      if (u.s.get_family() != AF_INET)
      {

         u.s.set_family(AF_UNSPEC);

      }
      else
      {

         sync_os_address();

         sync_os_service();

      }

   }


#endif


//   void address::set_address(const string & host, ::networking::port_t port)
//   {
//
//      ::zero(this, sizeof(address));
//
//#ifdef BSD_STYLE_SOCKETS
//
//      m_iLen = -1;
//
//#endif
//
//      parse_string(host);
//
//#if defined(WINRT_SOCKETS)
//
//      m_port = port;
//
//#endif
//
//#ifdef BSD_STYLE_SOCKETS
//
//      u.s.m_port = htons(port);
//
//#endif
//
//      sync_os_service();
//
//   }


//   void address::set_address(::particle * pparticle, const string & host, const ::string & strService)
//   {
//
//      auto psystem = pparticle->acmesystem();
//
//      auto pnetworking = (::networking_bsd::networking *)psystem->m_papexsystem->networking()->m_p2;
//
//
//#ifdef BSD_STYLE_SOCKETS
//
//      ::zero(this, sizeof(u.m_sa));
//
//      m_iLen = -1;
//
//#endif
//
//      parse_string(host);
//
//#ifdef BSD_STYLE_SOCKETS
//
//      u.s.m_port = pnetworking->service_port(strService);
//
//#endif
//
//      sync_os_service();
//
//   }


   void address::set_address(::networking::address * paddress)
   {

//#ifdef _UWP
//
//      m_posdata = memory_new os_data();
//
//#endif

      auto paddress2 = (::networking_bsd::address *)paddress->m_p2;

      operator =(*paddress2);

   }


   address::~address()
   {

//#ifdef _UWP
//
//      delete m_posdata;
//
//#endif

   }


   //address & address::operator = (const address & address)
   //{

   //   if (&address == this)
   //      return *this;

   //   copy(address);

   //   return *this;

   //}


   //bool address::operator == (const address & address) const
   //{

   //   if (&address == this)
   //      return true;

   //   return is_equal(address);

   //}


   string address::get_display_number() const
   {

//#ifdef _UWP
//
//      if (!_is_ip4() && !_is_ip6() && m_posdata != nullptr && m_posdata->m_hostname != nullptr)
//      {
//
//         ((address *) this)->sync_os_address();
//
//      }
//
//#endif

      string str;

#ifdef BSD_STYLE_SOCKETS

      if (_is_ip4())
      {

         str = as_string(u.m_addr.sin_addr);

      }
      else if (_is_ip6())
      {

         str = as_string(u.m_addr6.sin6_addr);

      }

#endif

      return str;

   }


   bool address::is_in_same_net(::networking::address * paddress, ::networking::address * paddressMask) const
   {

      auto paddress2 = __Address(paddress);

      auto paddressMask2 = __Address(paddressMask);

      if (_is_ip4() && paddress2->_is_ip4() && paddressMask2->_is_ip4())
      {

#ifdef BSD_STYLE_SOCKETS

         auto a1 = u.m_addr.sin_addr;

         auto a2 = paddress2->u.m_addr.sin_addr;

         auto aM = paddressMask2->u.m_addr.sin_addr;

         __memand(&a1, &a1, &aM, sizeof(a1));

         __memand(&a2, &a2, &aM, sizeof(a2));

         return __memcmp(&a1, &a2, sizeof(aM)) == 0;

#endif

         return false;


      }
      else if (_is_ip6() && paddress2->_is_ip6() && paddressMask2->_is_ip6())
      {

#ifdef BSD_STYLE_SOCKETS

         auto a1 = u.m_addr6.sin6_addr;

         auto a2 = paddress2->u.m_addr6.sin6_addr;

         auto aM = paddressMask2->u.m_addr6.sin6_addr;

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

   bool address::is_equal(::networking::address * paddress) const
   {


#ifdef BSD_STYLE_SOCKETS

      auto paddress2 = (::networking_bsd::address *)paddress->m_p2;

      if (u.s.m_port != paddress2->u.s.m_port)
         return false;

      if (_is_ip6() && paddress2->_is_ip6())
      {

         return __memcmp(&u.m_addr6.sin6_addr, &paddress2->u.m_addr6.sin6_addr, sizeof(in6_addr)) == 0;

      }
      else if (_is_ip4() && paddress2->_is_ip4())
      {

         return __memcmp(&u.m_addr.sin_addr, &paddress2->u.m_addr.sin_addr, sizeof(in_addr)) == 0;

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
//         m_posdata->m_hostname = ref memory_new ::winrt::Windows::Networking::HostName(get_display_number());
//      }
//      else if (m_posdata->m_hostname != nullptr)
//      {
//
//         string strDisplayNumber = m_posdata->m_hostname->RawName;
//
//         if (::networking_bsd::net::isipv4(strDisplayNumber))
//         {
//            ::networking_bsd::net::convert(u.m_addr.sin_addr, strDisplayNumber);
//            u.s.m_family = AF_INET;
//         }
//         else if (::networking_bsd::net::isipv6(strDisplayNumber))
//         {
//            ::networking_bsd::net::convert(u.m_addr6.sin6_addr, strDisplayNumber);
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


//   void address::parse_string(const ::string & strAddress)
//   {
//
//#if defined(BSD_STYLE_SOCKETS)
//
//      auto paddressdepartment = ::networking::address_department();
//
//      if (paddressdepartment->isipv6(strAddress))
//      {
//       
//         if (paddressdepartment->convert(u.m_addr6.sin6_addr, strAddress))
//         {
//
//            u.s.set_family(AF_INET6);
//
//         }
//
//      }
//      else if (paddressdepartment->isipv4(strAddress))
//      {
//
//         if (paddressdepartment->convert(u.m_addr.sin_addr, strAddress))
//         {
//
//            u.s.set_family(AF_INET);
//
//         }
//
//      }
//      else
//      {
//
//         throw ::exception(error_parsing, "Unrecognized networking IP address");
//
//      }
//
//#elif defined(WINRT_SOCKETS)
//
//      m_hostname = ref memory_new ::winrt::Windows::Networking::HostName(strAddress);
//
//
//#endif
//
//   }


//   string address::get_string() const
//   {
//
//      string str;
//
//#if defined(BSD_STYLE_SOCKETS)
//
//      if (_is_ip4())
//      {
//
//         ::to_string(str, u.m_addr);
//
//      }
//      else if (_is_ip6())
//      {
//
//         ::to_string(str, u.m_addr6);
//
//      }
//         
//#endif
//
//      return str;
//
//   }


#if defined(BSD_STYLE_SOCKETS)

   i32 address::sa_len() const
   {

      int iFamilyLen = u.s.get_family_len();

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


   address & address::operator = (const address & address)
   {

      if (this != &address)
      {

         ::memcpy_dup(&u, &address.u, sizeof(u));

         m_iLen = address.m_iLen;

      }

      return *this;

   }


//   address ipv4(u32 u, ::networking::port_t port)
//   {
//
//      address a;
//
//#if defined(BSD_STYLE_SOCKETS)
//
//      ::zero(&a, sizeof(a));
//
//      a.m_iLen = -1;
//      a.u.m_addr.sin_family = AF_INET;
//      a.u.m_addr.sin_port = port;
//      ::memcpy_dup(&a.u.m_addr.sin_addr, &u, sizeof(a.u.m_addr.sin_addr));
//#ifdef WINDOWS
//      ::__swap(a.u.m_addr.sin_addr.S_un.S_un_b.s_b1, a.u.m_addr.sin_addr.S_un.S_un_b.s_b4);
//      ::__swap(a.u.m_addr.sin_addr.S_un.S_un_b.s_b2, a.u.m_addr.sin_addr.S_un.S_un_b.s_b3);
//#else
////      ::__swap(&a.u.m_addr.sin_addr.s_addr.S_un_b.s_b1, &a.u.m_addr.sin_addr.s_addr.S_un_b.s_b4);
////      ::__swap(&a.u.m_addr.sin_addr.s_addr.S_un_b.s_b2, &a.u.m_addr.sin_addr.s_addr.S_un_b.s_b3);
//#endif
//
//      a.sync_os_address();
//      a.sync_os_service();
//
//#endif
//
//      return a;
//
//   }
//
//   address ipv6(void * p128bits, ::networking::port_t port)
//   {
//
//      address a;
//
//#if defined(BSD_STYLE_SOCKETS)
//
//      ::zero(&a, sizeof(a));
//
//      a.m_iLen = sizeof(sockaddr_in6);
//      a.u.m_addr6.sin6_family = AF_INET6;
//      a.u.m_addr6.sin6_port = port;
//      ::memcpy_dup(&a.u.m_addr6.sin6_addr, p128bits, sizeof(a.u.m_addr6.sin6_addr));
//
//      a.sync_os_address();
//      a.sync_os_service();
//
//#endif
//
//      return a;
//
//   }
//

   ::networking::port_t address::use_address_service_number_as_offset_for_base_port(::networking::port_t portBase) const
   {

      return portBase + get_service_number();

   }


   ::networking::port_t address::get_service_number() const
   {

#if defined(BSD_STYLE_SOCKETS)

      return ntohs(u.s.m_port);

#elif defined(WINRT_SOCKETS)

      return m_port;

#else

      return 0;

#endif

   }


   void address::set_service_number(::networking::port_t port)
   {

#if defined(BSD_STYLE_SOCKETS)

      u.s.m_port = htons(port);

#endif

   }

   bool address::is_ip4() const
   {


#if defined(BSD_STYLE_SOCKETS)

      return get_family() == AF_INET;

#elif defined(WINRT_SOCKETS)

      return false;

#else

#error "what socket?"

#endif


   }


   bool address::is_ip6() const
   {


#if defined(BSD_STYLE_SOCKETS)

      return get_family() == AF_INET6;

#elif defined(WINRT_SOCKETS)

      return false;

#else

#error "what socket?"

#endif

   }




   bool address::is_valid() const
   {

      return is_ip6() || is_ip4()
         //#if defined _UWP && defined(__cplusplus_winrt)
         //         || (m_posdata != nullptr && m_posdata->m_hostname != nullptr)
         //#endif
         ;

   }



} // namespace net



