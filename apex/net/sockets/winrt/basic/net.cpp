#include "framework.h"
#include "apex/net/net_sockets.h"

#if defined(LINUX) || defined(MACOS)
#if defined(MACOS)
#define	NI_MAXHOST	1025
#define	NI_MAXSERV	32
#endif
#define __USE_MISC
//#include <ctype.h>
//#include <sys/socket.h>
//#include <netdb.h>
#endif


namespace sockets
{


   net::net(::layered * pobjectContext) :
      ::object(pobject),
      m_mutexCache(pobject)
   {

   }

   net::~net()
   {

   }


   bool net::initialize()
   {

      return true;

   }


   bool net::gudo_set()
   {

      return true;

   }


   bool net::gudo_get()
   {

      return true;

   }


   bool net::finalize()
   {

      return true;

   }


   /*
   * Encode string per RFC1738 URL encoding rules
   * tnx rstaveley
   */
   string net::rfc1738_encode(const string & src)
   {
      static   char hex[] = "0123456789ABCDEF";
      string dst;
      for (int i = 0; i < src.get_length(); i++)
      {
         if (isalnum((unsigned char) src[i]))
         {
            dst += src[i];
         }
         else
            if (src[i] == ' ')
            {
               dst += '+';
            }
            else
            {
               unsigned char c = static_cast<unsigned char>(src[i]);
               dst += '%';
               dst += hex[c / 16];
               dst += hex[c % 16];
            }
      }
      return dst;
   } // rfc1738_encode


   /*
   * Decode string per RFC1738 URL encoding rules
   * tnx rstaveley
   */
   string net::rfc1738_decode(const string & src)
   {
      string dst;
      for (int i = 0; i < src.get_length(); i++)
      {
         if (src[i] == '%' && isxdigit((unsigned char) (src[i + 1])) && isxdigit((unsigned char) (src[i + 2])))
         {
            char c1 = src[++i];
            char c2 = src[++i];
            c1 = c1 - 48 - ((c1 >= 'A') ? 7 : 0) - ((c1 >= 'a') ? 32 : 0);
            c2 = c2 - 48 - ((c2 >= 'A') ? 7 : 0) - ((c2 >= 'a') ? 32 : 0);
            dst += (char)(c1 * 16 + c2);
         }
         else
            if (src[i] == '+')
            {
               dst += ' ';
            }
            else
            {
               dst += src[i];
            }
      }
      return dst;
   } // rfc1738_decode


   bool net::isipv4(const string & str)
   {
      int dots = 0;
      // %! ignore :port?
      for (int i = 0; i < str.get_length(); i++)
      {
         if (str[i] == '.')
            dots++;
         else
            if (!isdigit((unsigned char) str[i]))
               return false;
      }
      if (dots != 3)
         return false;
      return true;
   }


   bool net::isipv6(const string & str)
   {
      index qc = 0;
      index qd = 0;
      for (int i = 0; i < str.get_length(); i++)
      {
         qc += (str[i] == ':') ? 1 : 0;
         qd += (str[i] == '.') ? 1 : 0;
      }
      if (qc > 7)
      {
         return false;
      }
      if (qd && qd != 3)
      {
         return false;
      }
      ::str::parse pa(str,":.");
      string tmp = pa.getword();
      while (tmp.get_length())
      {
         if (tmp.get_length() > 4)
         {
            return false;
         }
         for (int i = 0; i < tmp.get_length(); i++)
         {
            if (tmp[i] < '0' || (tmp[i] > '9' && tmp[i] < 'A') ||
               (tmp[i] > 'F' && tmp[i] < 'a') || tmp[i] > 'f')
            {
               return false;
            }
         }
         //
         tmp = pa.getword();
      }
      return true;
   }



   void net::ResolveLocal()
   {

#ifdef _UWP

      //Retrieve the ConnectionProfile
      ::Windows::Networking::Connectivity::ConnectionProfile^ InternetConnectionProfile = Windows::Networking::Connectivity::NetworkInformation::GetInternetConnectionProfile();

      if(InternetConnectionProfile == nullptr)
         return;

      if(InternetConnectionProfile->NetworkAdapter == nullptr)
         return;

      //Pass the returned object to a function that accesses the connection data
      //::String^ strConnectionProfileInfo = GetConnectionProfileInfo(InternetConnectionProfile);

      //Windows::Networking::Connectivity::NetworkAdapter ^ adp = InternetConnectionProfile->NetworkAdapter();

      ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::HostName ^ > ^ names = ::Windows::Networking::Connectivity::NetworkInformation::GetHostNames();

      //strProfileInfo += connectionProfile->NetworkAdapter->NetworkAdapterId;
      //strProfileInfo += "\n";


      for(unsigned int ui = 0; ui < names->Size; ui++)
      {
         ::Windows::Networking::HostName ^ name = names->GetAt(ui);
         if(name == nullptr)
            continue;
         if(name->IPInformation == nullptr)
            continue;
         if(name->IPInformation->NetworkAdapter == nullptr)
            continue;
         if(name->IPInformation->NetworkAdapter->NetworkAdapterId == InternetConnectionProfile->NetworkAdapter->NetworkAdapterId)
         {
            // there may be more than one local address though
            m_host = begin(name->CanonicalName);
            m_local_resolved = true;
            break;
         }
      }




#else
      char h[256];

      // get local hostname and translate into ip-address
      *h = 0;
      gethostname(h,255);
      {
         if (net::u2ip(h, m_ip))
         {
            net::l2ip(m_ip, m_addr);
         }
      }
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      __memset(&m_local_ip6, 0, sizeof(m_local_ip6));
      {
         if (net::u2ip(h, m_local_ip6))
         {
            net::l2ip(m_local_ip6, m_local_addr6);
         }
      }
#endif
#endif
      m_host = h;
      m_local_resolved = true;

#endif

   }


   const string & net::GetLocalHostname()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_host;
   }


   ipaddr_t net::GetLocalIP()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_ip;
   }


   const string & net::GetLocalAddress()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_addr;
   }


   const struct in6_addr& net::GetLocalIP6()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_local_ip6;
   }


   const string & net::GetLocalAddress6()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_local_addr6;
   }

   /*
   string net::Sa2String(struct sockaddr *sa)
   {
      if (sa -> sa_family == AF_INET6)
      {
         struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)sa;
         string tmp;
         net::l2ip(sa6 -> sin6_addr, tmp);
         return tmp + ":" + __str(ntohs(sa6 -> sin6_port));
      }
      if (sa -> sa_family == AF_INET)
      {
         struct sockaddr_in *sa4 = (struct sockaddr_in *)sa;
         ipaddr_t a;
         ::memcpy_dup(&a, &sa4 -> sin_addr, 4);
         string tmp;
         net::l2ip(a, tmp);
         return tmp + ":" + __str(ntohs(sa4 -> sin_port));
      }
      return "";
   }



   ::sockets::address_pointer net::CreateAddress(struct sockaddr *sa,socklen_t sa_len)
   {
      switch (sa -> sa_family)
      {
      case AF_INET:
         if (sa_len == sizeof(struct sockaddr_in))
         {
            struct sockaddr_in *p = (struct sockaddr_in *)sa;
            ::sockets::address_pointer addr;
            addr(new ::sockets::ipv4_address(get_context_application(), *p));
            return addr;
         }
         break;
      case AF_INET6:
         if (sa_len == sizeof(struct sockaddr_in6))
         {
            struct sockaddr_in6 *p = (struct sockaddr_in6 *)sa;
            ::sockets::address_pointer addr;
            addr(new ::sockets::ipv6_address(get_context_application(), *p));
            return addr;
         }
         break;
      }
      return ::sockets::address_pointer();
   }
   */

   bool net::convert(in_addr & addr, const string & host,int ai_flags)
   {

      ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::EndpointPair ^ > ^ data = ::wait(::Windows::Networking::Sockets::DatagramSocket::GetEndpointPairsAsync(ref new ::Windows::Networking::HostName(host), "0"));

      if(data->Size <= 0)
         return false;

      string str = begin(data->GetAt(0)->RemoteHostName->DisplayName);

      if(!net::isipv4(str))
         return false;

      addr.S_un.S_addr = c_inet_addr(str);

      return true;

   }


   bool net::convert(in6_addr & sa, const string & host, int ai_flags)
   {

      ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::EndpointPair ^ > ^ data = ::wait(::Windows::Networking::Sockets::DatagramSocket::GetEndpointPairsAsync(ref new ::Windows::Networking::HostName(host), "0"));

      if(data->Size <= 0)
         return false;

      string str = begin(data->GetAt(0)->RemoteHostName->DisplayName);

      if(!net::isipv6(str))
         return false;

      from_string(sa, str);

      return true;

   }


   bool net::convert(string & str, const in_addr & addr, int ai_flags)
   {

      ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::EndpointPair ^ > ^ data = ::wait(::Windows::Networking::Sockets::DatagramSocket::GetEndpointPairsAsync(ref new ::Windows::Networking::HostName(to_string((in_addr &)addr)),"0"));

      if(data->Size <= 0)
         return false;

      str = begin(data->GetAt(0)->RemoteHostName->CanonicalName);

      return true;

   }


   bool net::convert(string & str, const in6_addr & addr, int ai_flags)
   {

      ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::EndpointPair ^ > ^ data = ::wait(::Windows::Networking::Sockets::DatagramSocket::GetEndpointPairsAsync(ref new ::Windows::Networking::HostName(to_string((in6_addr &) addr) ),"0"));

      if(data->Size <= 0)
         return false;

      str = begin(data->GetAt(0)->RemoteHostName->CanonicalName);

      return true;

   }


   bool net::reverse(string & number, const string & hostname, int flags)
   {

      ::net::address address(hostname);

      number = address.get_display_number();

      return true;

   }

/*
   bool net::reverse(struct sockaddr *sa, socklen_t sa_len, string & hostname, string & service, int flags)
   {

#ifdef _UWP

      switch(sa->sa_family)
      {
      case AF_INET:
         {

            union
            {
               struct
               {
                  unsigned char b1;
                  unsigned char b2;
                  unsigned char b3;
                  unsigned char b4;
               } a;
               ipaddr_t l;
            } u;

            struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;

            ::memcpy_dup(&u.l, &sa_in -> sin_addr, sizeof(u.l));

            hostname.Format("%u.%u.%u.%u", u.a.b1, u.a.b2, u.a.b3, u.a.b4);

            if (flags & NI_NUMERICHOST)
            {
               return true;
            }

            ::Windows::Networking::HostName ^ name = ref new ::Windows::Networking::HostName(rtstr(hostname));

            if(name != nullptr)
            {

               hostname = begin(name->CanonicalName);

               return true;

            }

         }
         break;

      case AF_INET6:
         {
            char slask[100]; // l2ip temporary
            *slask = 0;
            unsigned int prev = 0;
            bool skipped = false;
            bool ok_to_skip = true;
            {
               unsigned short addr16[8];
               struct sockaddr_in6 *sa_in6 = (struct sockaddr_in6 *)sa;
               ::memcpy_dup(addr16, &sa_in6 -> sin6_addr, sizeof(addr16));
               for (index i = 0; i < 8; i++)
               {
                  unsigned short x = ntohs(addr16[i]);
                  if (*slask && (x || !ok_to_skip || prev))
                     ansi_concatenate(slask,":");
                  if (x || !ok_to_skip)
                  {
                     sprintf(slask + strlen(slask),"%x", x);
                     if (x && skipped)
                        ok_to_skip = false;
                  }
                  else
                  {
                     skipped = true;
                  }
                  prev = x;
               }
            }
            if (!*slask)
               strcpy(slask, "::");
            hostname = slask;
            if (flags & NI_NUMERICHOST)
            {
               return true;
            }
            // %! TODO: ipv6 reverse lookup

            ::Windows::Networking::HostName ^ name = ref new ::Windows::Networking::HostName(rtstr(hostname));

            if(name != nullptr)
            {

               hostname = begin(name->CanonicalName);

               return true;

            }
         }
         break;
      }
      return false;
#else
      hostname = "";
      service = "";
#ifdef NO_GETADDRINFO
      switch (sa -> sa_family)
      {
      case AF_INET:
         if (flags & NI_NUMERICHOST)
         {
            union {
               struct {
                  unsigned char b1;
                  unsigned char b2;
                  unsigned char b3;
                  unsigned char b4;
               } a;
               ipaddr_t l;
            } u;
            struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;
            ::memcpy_dup(&u.l, &sa_in -> sin_addr, sizeof(u.l));
            char tmp[100];
            sprintf(tmp, "%u.%u.%u.%u", u.a.b1, u.a.b2, u.a.b3, u.a.b4);
            hostname = tmp;
            return true;
         }
         else
         {
            struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;
            struct hostent *h = gethostbyaddr( (const string &)&sa_in -> sin_addr, sizeof(sa_in -> sin_addr), AF_INET);
            if (h)
            {
               hostname = h -> h_name;
               return true;
            }
         }
         break;
#ifdef ENABLE_IPV6
      case AF_INET6:
         if (flags & NI_NUMERICHOST)
         {
            char slask[100]; // l2ip temporary
            *slask = 0;
            unsigned int prev = 0;
            bool skipped = false;
            bool ok_to_skip = true;
            {
               unsigned short addr16[8];
               struct sockaddr_in6 *sa_in6 = (struct sockaddr_in6 *)sa;
               ::memcpy_dup(addr16, &sa_in6 -> sin6_addr, sizeof(addr16));
               for (index i = 0; i < 8; i++)
               {
                  unsigned short x = ntohs(addr16[i]);
                  if (*slask && (x || !ok_to_skip || prev))
                     ansi_concatenate(slask,":");
                  if (x || !ok_to_skip)
                  {
                     sprintf(slask + strlen(slask),"%x", x);
                     if (x && skipped)
                        ok_to_skip = false;
                  }
                  else
                  {
                     skipped = true;
                  }
                  prev = x;
               }
            }
            if (!*slask)
               strcpy(slask, "::");
            hostname = slask;
            return true;
         }
         else
         {
            // %! TODO: ipv6 reverse lookup
            struct sockaddr_in6 *sa_in = (struct sockaddr_in6 *)sa;
            struct hostent *h = gethostbyaddr( (const string &)&sa_in -> sin6_addr, sizeof(sa_in -> sin6_addr), AF_INET6);
            if (h)
            {
               hostname = h -> h_name;
               return true;
            }
         }
         break;
#endif
      }
      return false;
#else
      char host[NI_MAXHOST];
      char serv[NI_MAXSERV];
      // NI_NOFQDN
      // NI_NUMERICHOST
      // NI_NAMEREQD
      // NI_NUMERICSERV
      // NI_DGRAM
      int n = getnameinfo(sa, sa_len, host, sizeof(host), serv, sizeof(serv), flags);
      if (n)
      {
         // EAI_AGAIN
         // EAI_BADFLAGS
         // EAI_FAIL
         // EAI_FAMILY
         // EAI_MEMORY
         // EAI_NONAME
         // EAI_OVERFLOW
         // EAI_SYSTEM
         return false;
      }
      hostname = host;
      service = serv;
      return true;
#endif // NO_GETADDRINFO
#endif
   }
   */

      /*

   bool net::u2service(const string & name, int& service, int ai_flags)
   {

#ifdef BSD_STYLE_SOCKETS

#ifdef NO_GETADDRINFO
      // %!
      return false;
#else
      struct addrinfo hints;
      service = 0;
      __memset(&hints, 0, sizeof(hints));
      // AI_NUMERICHOST
      // AI_CANONNAME
      // AI_PASSIVE - server
      // AI_ADDRCONFIG
      // AI_V4MAPPED
      // AI_ALL
      // AI_NUMERICSERV
      hints.ai_flags = ai_flags;
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = 0;
      hints.ai_protocol = 0;
      struct addrinfo *res;
      int n = getaddrinfo(nullptr, name, &hints, &res);
      if (!n)
      {
         service = res -> ai_protocol;
         freeaddrinfo(res);
         return true;
      }
      return false;
#endif // NO_GETADDRINFO

#else

      return false;

#endif

   }
   */


   int net::service_port(const string & psz, int flags)
   {

      if(::str::is_simple_natural(psz))
         return ::str::to_i32(psz);

      string str(psz);

      if(str.compare_ci("http"))
      {
         return 80;
      }
      else if(str.compare_ci("https"))
      {
         return 443;
      }
      else
      {
         return 0;
      }

   }


   string  net::service_name(int iPort, int flags)
   {

      switch(iPort)
      {
      case 80:
         return "http";
      case 443:
         return "https";
      default:
         return "";
      }

   }



   string net::canonical_name(const ::net::address & address)
   {

      return address.m_posdata->m_hostname->CanonicalName;

   }




} // namespace sockets


