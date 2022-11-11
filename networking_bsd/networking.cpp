// Created by camilo on 2021-03-10 06:22 BRT ThomasBS_!!
#include "framework.h"
#include "networking.h"
#include "sockets/ssl/initializer.h"
#include "acme/array.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/duration/_binary_stream.h"
#include "acme/primitive/string/parse.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"
#define ERROR(...) TRACE_LOG_ERROR(__VA_ARGS__)

//#include <stdio.h>


bool defer_initialize_operating_system_networking();
bool defer_finalize_operating_system_networking();


#ifdef RASPBIAN
#include <sys/types.h>
#include <unistd.h>
#endif


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
#undef USE_MISC

#if defined(__APPLE__) || defined(FREEBSD)
#define  NI_MAXHOST  1025
#define  NI_MAXSERV  32
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif
//#define __USE_MISC
//#include <ctype.h>
#endif

#if defined(FREEBSD)
#include <unistd.h>
#endif


namespace networking_bsd
{

   class networking* g_paddressdepartment = nullptr;


   networking::networking()
   {

      m_p2 = this;

      defer_create_synchronization();

      
      defer_initialize_operating_system_networking();
      //::net::g_paddressdepartment = nullptr;

      m_psslinit = nullptr;

      //m_pajpaxissocketinit    = nullptr;


      m_bInitialized = false;
      //m_mapCache.m_bAutoGudoSet = false;
      //m_mapReverseCache.m_bAutoGudoSet = false;

      //m_mapCache.erase_all();
      //m_mapReverseCache.erase_all();

      m_iListenSocket = 1;

   }


   networking::~networking()
   {

      defer_finalize_operating_system_networking();

   }


   //networking::net()
   //{

   //   defer_create_synchronization();

   //   m_bInitialized = false;
   //   //m_mapCache.m_bAutoGudoSet = false;
   //   //m_mapReverseCache.m_bAutoGudoSet = false;

   //   //m_mapCache.erase_all();
   //   //m_mapReverseCache.erase_all();

   //}


   //networking::~net()
   //{

   //}



   void     networking::initialize(::particle * pparticle)
   {

      if (m_bInitialized)
      {

         return;

      }

      //auto estatus = ::object::initialize(pparticle);

      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_bInitialized = true;

      //if(psystem->m_bGudoNetCache)
      {

         //get_app()->gudo_get("networking_bsd::networking::m_mapCache",m_mapCache);

         //get_app()->gudo_get("networking_bsd::networking::m_mapReverseCache",m_mapReverseCache);

      }


      //return estatus;

      //auto paddressdepartment = pparticle->__create_new<class ::networking::address_department>();

      //paddressdepartment->increment_reference_count();

      //::net::g_paddressdepartment = paddressdepartment;

      generate_random_bytes(m_baTicketKey, sizeof(m_baTicketKey));

      m_psslinit = __create_new<::sockets_bsd::SSLInitializer>();

      //estatus = __construct_new(m_pnet);

      //__construct_new(m_pnet);

      //if (!m_pnet)
      //{

      //   m_iErrorCode = -1;

      //   //return error_failed;

      //   return;

      //}

      ////if (!m_pnet->initialize(this))
      //m_pnet->initialize(this);
      /*{

         return error_failed;

      }*/

      //if (!::acme::department::initialize())
      //{

      //   return error_failed;

      //}

   //      try
   //      {
   //
   //#ifdef WINDOWS
   //         __construct(m_pportforward);
   //#endif
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }


         //m_pajpaxissocketinit = memory_new AjpBaseSocket::Initializer;

      m_countHttpPostBoundary = 0;

      // return ::success;


   }


   bool networking::gudo_set()
   {

      if (!m_bInitialized)
         return false;

      //      m_mapCache.gudo_set();

            //    m_mapReverseCache.gudo_set();

      return true;

   }


   void networking::destroy()
   {

      ::object::destroy();

      if (m_bInitialized)
      {

         m_bInitialized = false;

      }


      //void networking_bsd::destroy()
      //{

      //   sockets_base::destroy();

         //bool bOk = true;

         //if (m_pnet)
         //{

         //   //try
         //   //{

         //   //   //if (!m_pnet->gudo_set())

         //   //   //m_pnet->gudo_set()
         //   //   //{

         //   //   //   m_iErrorCode = -87;

         //   //   //}

         //   //}
         //   //catch (...)
         //   //{

         //   //   m_iErrorCode = -87;

         //   //}

         //}

#ifdef WINDOWS

         try
         {

            if (m_pportforward.is_set())
            {

               m_pportforward.release();

            }

         }
         catch (...)
         {

            //bOk = false;

         }

         try
         {

            m_pportforward.release();

         }
         catch (...)
         {

         }

#endif

         //if (m_pnet)
         //{

         //   try
         //   {

         //      m_pnet->destroy();

         //   }
         //   catch (...)
         //   {

         //      m_iErrorCode = -87;

         //   }

         //   try
         //   {

         //      m_pnet.release();

         //   }
         //   catch (...)
         //   {

         //      m_iErrorCode = -86;

         //   }

         //}

         ///::acme::del(m_pajpaxissocketinit);

         //return ::success;

   //   }

      //return ::success;

   }


   /*
   * Encode string per RFC1738 URL encoding rules
   * tnx rstaveley
   */
   string networking::rfc1738_encode(const string& src)
   {
      static   char hex[] = "0123456789ABCDEF";
      string dst;
      for (i32 i = 0; i < src.get_length(); i++)
      {
         if (ansi_char_is_alnum((uchar)src[i]))
         {
            dst += src[i];
         }
         else if (src[i] == ' ')
         {
            dst += '+';
         }
         else
         {
            uchar ca = static_cast<uchar>(src[i]);
            dst += '%';
            dst += hex[ca / 16];
            dst += hex[ca % 16];
         }
      }
      return dst;
   } // rfc1738_encode


   /*
   * Decode string per RFC1738 URL encoding rules
   * tnx rstaveley
   */
   string networking::rfc1738_decode(const string& src)
   {
      string dst;
      for (i32 i = 0; i < src.get_length(); i++)
      {
         if (src[i] == '%' && isxdigit((uchar)(src[i + 1])) && isxdigit((uchar)(src[i + 2])))
         {
            char c1 = src[++i];
            char c2 = src[++i];
            c1 = c1 - 48 - ((c1 >= 'A') ? 7 : 0) - ((c1 >= 'a') ? 32 : 0);
            c2 = c2 - 48 - ((c2 >= 'A') ? 7 : 0) - ((c2 >= 'a') ? 32 : 0);
            dst += (char)(c1 * 16 + c2);
         }
         else if (src[i] == '+')
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


   bool networking::is_ip4(const string& str)
   {
      i32 dots = 0;
      // %! ignore :port?
      for (i32 i = 0; i < str.get_length(); i++)
      {
         if (str[i] == '.')
            dots++;
         else if (!isdigit((uchar)str[i]))
            return false;
      }
      if (dots != 3)
         return false;
      return true;
   }


   bool networking::is_ip6(const string& str)
   {
      if (str.is_empty())
         return false;
      index qc = 0;
      index qd = 0;
      for (i32 i = 0; i < str.get_length(); i++)
      {
         qc += (str[i] == ':') ? 1 : 0;
         qd += (str[i] == '.') ? 1 : 0;
      }
      if (qc < 2)
         return false;
      if (qc > 7)
      {
         return false;
      }
      if (qd && qd != 3)
      {
         return false;
      }
      
      ::parse pa(str, ":.");

      string tmp = pa.getword();
      while (tmp.get_length())
      {
         if (tmp.get_length() > 4)
         {
            return false;
         }
         for (i32 i = 0; i < tmp.get_length(); i++)
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

   bool networking::convert(in_addr& l, const string& str, i32 ai_flags)
   {

      if (str.is_empty())
         return false;

      single_lock synchronouslock(m_pmutexCache, true);
      dns_cache_item item;
      if (m_mapCache.lookup(str, item) && (item.m_bOk && (!item.m_bTimeout || ((item.m_durationLastChecked.elapsed()) < (5_minute)))))
      {
         if (item.m_bOk)
         {
            l = item.m_ipaddr;
         }
         //         ::duration tick2= ::duration::now();
         /*FORMATTED_TRACE("Got from cache networking::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
         (u32)((byte*)&pitem->m_ipaddr)[0],
         (u32)((byte*)&pitem->m_ipaddr)[1],
         (u32)((byte*)&pitem->m_ipaddr)[2],
         (u32)((byte*)&pitem->m_ipaddr)[3],
         (tick2 - tick1));*/
         return item.m_bOk;
      }
      struct sockaddr_in sa;
      __memset(&sa, 0, sizeof(sa));
      sa.sin_family = AF_INET;
#ifdef NO_GETADDRINFO
      if ((ai_flags & AI_NUMERICHOST) != 0 || isipv4(host))
      {
         ::parse pa((const char*)host, ".");
         union
         {
            struct
            {
               uchar b1;
               uchar b2;
               uchar b3;
               uchar b4;
            } a;
            ipaddr_t l;
         } u;
         u.a.b1 = static_cast<uchar>(pa.getvalue());
         u.a.b2 = static_cast<uchar>(pa.getvalue());
         u.a.b3 = static_cast<uchar>(pa.getvalue());
         u.a.b4 = static_cast<uchar>(pa.getvalue());
         ::memcpy_dup(&sa.sin_addr, &u.l, sizeof(sa.sin_addr));
         return true;
      }
#ifndef LINUX
      struct hostent* he = gethostbyname(host);
      if (!he)
      {
         return false;
      }
      ::memcpy_dup(&sa.sin_addr, he->h_addr, sizeof(sa.sin_addr));
#else
      struct hostent he;
      struct hostent* result = nullptr;
      i32 myerrno = 0;
      char buf[2000];
      i32 n = gethostbyname_r(host, &he, buf, sizeof(buf), &result, &myerrno);
      if (n || !result)
      {
         return false;
      }
      if (he.h_addr_list && he.h_addr_list[0])
         ::memcpy_dup(&sa.sin_addr, he.h_addr, 4);
      else
         return false;
#endif
      return true;
#else
      struct addrinfo hints;
      __memset(&hints, 0, sizeof(hints));
      // AI_NUMERICHOST
      // AI_CANONNAME
      // AI_PASSIVE - server
      // AI_ADDRCONFIG
      // AI_V4MAPPED
      // AI_ALL
      // AI_NUMERICSERV
      hints.ai_flags = ai_flags;
      hints.ai_family = AF_INET;
      hints.ai_socktype = 0;
      hints.ai_protocol = 0;
      struct addrinfo* res;
      if (is_ip4(str))
         hints.ai_flags |= AI_NUMERICHOST;

      i32 n = getaddrinfo(str, nullptr, &hints, &res);
      if (n)
      {
         string error = "getaddrinfo Error: ";
#ifndef __CYGWIN__
         error += gai_strerror(n);
#endif
         ERROR(error + " for " + str);
         item.m_bOk = false;
         item.m_bTimeout = true;
         item.m_durationLastChecked.Now();
         m_mapCache.set_at(str, item);

         return false;
#endif // NO_GETADDRINFO
      }
      item.m_bOk = true;
      address_array < addrinfo* > vec;
      addrinfo* ai = res;
      while (ai)
      {
         if (ai->ai_addrlen == sizeof(sa))
            vec.add(ai);
         ai = ai->ai_next;
      }
      if (!vec.get_count())
         return false;
      ai = vec[rand() % vec.get_count()];
      {
         ::memcpy_dup(&sa, ai->ai_addr, ai->ai_addrlen);
      }
      freeaddrinfo(res);
      item.m_ipaddr = sa.sin_addr;
      item.m_durationLastChecked.Now();
      m_mapCache.set_at(str, item);

      //if(psystem->m_bGudoNetCache)
      {

         //get_app()->gudo_set("networking_bsd::networking::m_mapCache",m_mapCache);

      }

      //      ::duration tick2= ::duration::now();
      //      FORMATTED_TRACE("DNS lookup networking::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
         //       (u32)((byte*)&pitem->m_ipaddr)[0],
         //     (u32)((byte*)&pitem->m_ipaddr)[1],
         //   (u32)((byte*)&pitem->m_ipaddr)[2],
         // (u32)((byte*)&pitem->m_ipaddr)[3],
         //(tick2 - tick1));
      l = item.m_ipaddr;

      return item.m_bOk;

   }


   //bool networking::convert(struct in6_addr& l, const ::string & str, i32 ai_flags)
   //{


   //   return from_string(l, str) != false;


   //}


   bool networking::convert(string& str, const in_addr& inaddr)
   {

      try
      {

         str = __string(inaddr);

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   bool networking::convert(string& str, const struct in6_addr& inaddr6)
   {

      try
      {

         str = __string(inaddr6);

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   i32 networking::in6_addr_compare(in6_addr a, in6_addr b)
   {
      for (index i = 0; i < 16; i++)
      {
         if (a.s6_addr[i] < b.s6_addr[i])
            return -1;
         if (a.s6_addr[i] > b.s6_addr[i])
            return 1;
      }
      return 0;
   }

   void networking::ResolveLocal()
   {

      char h[256];

      // get local hostname and translate into ip-address
      *h = 0;
      gethostname(h, 255);
      {
         if (convert(m_ip, h))
         {
            convert(m_addr, m_ip);
         }
      }
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      __memset(&m_local_ip6, 0, sizeof(m_local_ip6));
      {
         if (convert(m_local_ip6, h))
         {
            convert(m_local_addr6, m_local_ip6);
         }
      }
#endif
#endif
      m_host = h;
      m_local_resolved = true;

   }


   const string& networking::GetLocalHostname()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_host;
   }


   in_addr networking::GetLocalIP()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_ip;
   }


   const string& networking::GetLocalAddress()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_addr;
   }


   const struct in6_addr& networking::GetLocalIP6()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_local_ip6;
   }


   const string& networking::GetLocalAddress6()
   {
      if (!m_local_resolved)
      {
         ResolveLocal();
      }
      return m_local_addr6;
   }

   string networking::Sa2String(struct sockaddr* sa)
   {
      if (sa->sa_family == AF_INET6)
      {
         struct sockaddr_in6* sa6 = (struct sockaddr_in6*)sa;
         string tmp;
         convert(tmp, sa6->sin6_addr);
         return tmp + ":" + __string(ntohs(sa6->sin6_port));
      }
      if (sa->sa_family == AF_INET)
      {
         struct sockaddr_in* sa4 = (struct sockaddr_in*)sa;
         string tmp;
         convert(tmp, sa4->sin_addr);
         return tmp + ":" + __string(ntohs(sa4->sin_port));
      }
      return "";
   }


   /*
   ::networking::address networking::CreateAddress(struct sockaddr *sa,socklen_t sa_len)
   {
      retur
      switch (sa -> sa_family)
      {
      case AF_INET:
         if (sa_len == sizeof(struct sockaddr_in))
         {
            struct sockaddr_in *point = (struct sockaddr_in *)sa;
            ::networking_bsd::address_pointer addr;
            addr(memory_new ::networking_bsd::ipv4_address(get_app(), *point_i32));
            return addr;
         }
         break;
      case AF_INET6:
         if (sa_len == sizeof(struct sockaddr_in6))
         {
            struct sockaddr_in6 *point = (struct sockaddr_in6 *)sa;
            ::networking_bsd::address_pointer addr;
            addr(memory_new ::networking_bsd::ipv6_address(get_app(), *point_i32));
            return addr;
         }
         break;
      }
      return ::networking_bsd::address_pointer();
   }
   */

   /*   bool networking::convert(in_addr & sa, const string & host, i32 ai_flags)
      {

         __memset(&sa, 0, sizeof(sa));
         sa.sin_family = AF_INET;
   #ifdef NO_GETADDRINFO
         if ((ai_flags & AI_NUMERICHOST) != 0 || isipv4(host))
         {
            ::parse pa((const char *)host, ".");
            union {
               struct {
                  uchar b1;
                  uchar b2;
                  uchar b3;
                  uchar b4;
               } a;
               ipaddr_t l;
            } u;
            u.a.b1 = static_cast<uchar>(pa.getvalue());
            u.a.b2 = static_cast<uchar>(pa.getvalue());
            u.a.b3 = static_cast<uchar>(pa.getvalue());
            u.a.b4 = static_cast<uchar>(pa.getvalue());
            ::memcpy_dup(&sa.sin_addr, &u.l, sizeof(sa.sin_addr));
            return true;
         }
   #ifndef LINUX
         struct hostent *he = gethostbyname( host );
         if (!he)
         {
            return false;
         }
         ::memcpy_dup(&sa.sin_addr, he -> h_addr, sizeof(sa.sin_addr));
   #else
         struct hostent he;
         struct hostent *result = nullptr;
         i32 myerrno = 0;
         char buf[2000];
         i32 n = gethostbyname_r(host, &he, buf, sizeof(buf), &result, &myerrno);
         if (n || !result)
         {
            return false;
         }
         if (he.h_addr_list && he.h_addr_list[0])
            ::memcpy_dup(&sa.sin_addr, he.h_addr, 4);
         else
            return false;
   #endif
         return true;
   #else
         struct addrinfo hints;
         __memset(&hints, 0, sizeof(hints));
         // AI_NUMERICHOST
         // AI_CANONNAME
         // AI_PASSIVE - server
         // AI_ADDRCONFIG
         // AI_V4MAPPED
         // AI_ALL
         // AI_NUMERICSERV
         hints.ai_flags = ai_flags;
         hints.ai_family = AF_INET;
         hints.ai_socktype = 0;
         hints.ai_protocol = 0;
         struct addrinfo *res;
         if (networking::isipv4(host))
            hints.ai_flags |= AI_NUMERICHOST;
         i32 n = getaddrinfo(host, nullptr, &hints, &res);
         if (!n)
         {
            ref_array <  addrinfo > vec;
            addrinfo *ai = res;
            while (ai)
            {
               if (ai -> ai_addrlen == sizeof(sa))
                  vec.add( ai );
               ai = ai -> ai_next;
            }
            if (!vec.get_count())
               return false;
            ai = vec[pmathematics->rnd() % vec.get_count()];
            {
               ::memcpy_dup(&sa, ai -> ai_addr, ai -> ai_addrlen);
            }
            freeaddrinfo(res);
            return true;
         }
         string error = "Error: ";
   #ifndef __CYGWIN__
         error += gai_strerror(n);
   #endif
         return false;
   #endif // NO_GETADDRINFO
      }*/


   bool networking::convert(struct in6_addr& sa, const string& host, i32 ai_flags)
   {

      try
      {

         ::from_string(sa, host);

      }
      catch (const ::exception& e)
      {

         output_debug_string(e.m_strMessage);

         return false;

         //if (e.is < parsing_exception >())
         {

            // return false;

         }
         //else
         {

            // __rethrow(e);

         }

      }

      __memset(&sa, 0, sizeof(sa));
#ifdef WINDOWS
#else
      //sa.sin6_family = AF_INET6;
#endif
#ifdef NO_GETADDRINFO
      if ((ai_flags & AI_NUMERICHOST) != 0 || isipv6(host))
      {
         //         list<string> vec;
         index x = 0;
         for (index i = 0; i <= host.get_length(); i++)
         {
            if (i == host.get_length() || host[i] == ':')
            {
               string s = host.Mid(x, i - x);
               //
               if (strstr(s, ".")) // x.x.x.x
               {
                  Parse pa(s, ".");
                  char slask[100]; // u2ip temporary hgenstring conversion
                  unsigned long b0 = static_cast<unsigned long>(pa.getvalue());
                  unsigned long b1 = static_cast<unsigned long>(pa.getvalue());
                  unsigned long b2 = static_cast<unsigned long>(pa.getvalue());
                  unsigned long b3 = static_cast<unsigned long>(pa.getvalue());
                  sprintf(slask, "%lx", b0 * 256 + b1);
                  vec.push_back(slask);
                  sprintf(slask, "%lx", b2 * 256 + b3);
                  vec.push_back(slask);
               }
               else
               {
                  vec.push_back(s);
               }
               //
               x = i + 1;
            }
         }
         index sz = vec.get_length(); // number of byte pairs
         index i = 0; // index in in6_addr.in6_u.u6_addr16[] ( 0 .. 7 )
         u16 addr16[8];
         for (list<string>::iterator it = vec.begin(); it != vec.end(); it++)
         {
            string bytepair = *it;
            if (bytepair.get_length())
            {
               addr16[i++] = htons(networking::hgenunsigned(bytepair));
            }
            else
            {
               addr16[i++] = 0;
               while (sz++ < 8)
               {
                  addr16[i++] = 0;
               }
            }
         }
         ::memcpy_dup(&sa.sin6_addr, addr16, sizeof(addr16));
         return true;
      }
#ifdef SOLARIS
      i32 errnum = 0;
      struct hostent* he = getipnodebyname(host, AF_INET6, 0, &errnum);
#else
      struct hostent* he = gethostbyname2(host, AF_INET6);
#endif
      if (!he)
      {
         return false;
      }
      ::memcpy_dup(&sa.sin6_addr, he->h_addr_list[0], he->h_length);
#ifdef SOLARIS
      free(he);
#endif
      return true;
#else
      struct addrinfo hints;
      __memset(&hints, 0, sizeof(hints));
      hints.ai_flags = ai_flags;
      hints.ai_family = AF_INET6;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_protocol = IPPROTO_TCP;
      struct addrinfo* res;
      if (is_ip6(host))
         hints.ai_flags |= AI_NUMERICHOST;
      i32 n = getaddrinfo(host, nullptr, &hints, &res);
      if (!n)
      {

         array <  sockaddr_in6* > addra;
         struct addrinfo* ai = res;
         int iSaSize = sizeof(sockaddr_in6);
         //char ipstringbuffer[46];
         //::u32 ipbufferlength = 46;
         while (ai)
         {
            // The buffer length is changed by each call to WSAAddresstoString
            // So we need to set it for each iteration through the loop for safety
            if (ai->ai_addrlen == iSaSize)
               addra.add((sockaddr_in6*)ai->ai_addr);
            ai = ai->ai_next;
         }
         if (addra.is_empty())
            return false;
         ::memcpy_dup(&sa, &::acme::array::pick_random(addra)->sin6_addr, sizeof(sa));
         freeaddrinfo(res);
         return true;
      }
      string error = "Error: ";
#ifndef __CYGWIN__
      error += gai_strerror(n);
#endif
      return false;
#endif // NO_GETADDRINFO

   }


   bool networking::reverse(string& number, const string& hostname)
   {

      auto paddress = create_address(hostname);

      number = paddress->get_display_number();

      return true;

   }


   bool networking::reverse_schedule(reverse_cache_item* pitem)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_reversecacheaRequest.add(pitem);

      }

      if (!m_pthreadReverse)
      {

         auto psystem = get_system()->m_papexsystem;

         m_pthreadReverse = psystem->fork([this]()
            {

               ::task_set_name("reverse___dns");

               single_lock synchronouslock(this->synchronization());

               while (task_get_run())
               {

                  synchronouslock.lock();

                  if (m_reversecacheaRequest.has_elements())
                  {

                     auto pitem = m_reversecacheaRequest[0];

                     m_reversecacheaRequest.erase_at(0);

                     synchronouslock.unlock();

                     reverse_sync(pitem);

                  }
                  else
                  {

                     synchronouslock.unlock();

                     preempt(100_ms);

                  }

               }

               m_pthreadReverse.release();

            });

      }

      return true;

   }


   bool networking::reverse(string& hostname, ::networking::address * paddress)
   {

      single_lock synchronouslock(m_pmutexReverseCache, true);

      auto& pitem = m_mapReverseCache[paddress->get_display_number()];

      if (pitem && !pitem->m_bProcessing && !pitem->m_bTimeout && pitem->m_durationLastChecked.elapsed() < 6_hour)
      {

         hostname = pitem->m_strReverse;

         return pitem->m_bOk;

      }

      pitem = __new(reverse_cache_item);

      pitem->m_paddress = paddress;

      pitem->m_bTimeout = false;

      pitem->m_bProcessing = true;

      pitem->m_bOk = false;

      reverse_schedule(pitem);

      return true;

   }


   bool networking::reverse_sync(reverse_cache_item* pitem)
   {

      int flags = NI_NUMERICHOST;

#ifdef NO_GETADDRINFO
      switch (sa->sa_family)
      {
      case AF_INET:
         if (flags & NI_NUMERICHOST)
         {
            union
            {
               struct
               {
                  uchar b1;
                  uchar b2;
                  uchar b3;
                  uchar b4;
               } a;
               ipaddr_t l;
            } u;
            struct sockaddr_in* sa_in = (struct sockaddr_in*)sa;
            ::memcpy_dup(&u.l, &sa_in->sin_addr, sizeof(u.l));
            char tmp[100];
            sprintf(tmp, "%u.%u.%u.%u", u.a.b1, u.a.b2, u.a.b3, u.a.b4);
            hostname = tmp;
            return true;
         }
         else
         {
            struct sockaddr_in* sa_in = (struct sockaddr_in*)sa;
            struct hostent* h = gethostbyaddr((const char*)&sa_in->sin_addr, sizeof(sa_in->sin_addr), AF_INET);
            if (h)
            {
               hostname = h->h_name;
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
            u32 prev = 0;
            bool skipped = false;
            bool ok_to_skip = true;
            {
               u16 addr16[8];
               struct sockaddr_in6* sa_in6 = (struct sockaddr_in6*)sa;
               ::memcpy_dup(addr16, &sa_in6->sin6_addr, sizeof(addr16));
               for (index i = 0; i < 8; i++)
               {
                  u16 x = ntohs(addr16[i]);
                  if (*slask && (x || !ok_to_skip || prev))
                     ansi_concatenate(slask, ":");
                  if (x || !ok_to_skip)
                  {
                     sprintf(slask + strlen(slask), "%x", x);
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
            struct sockaddr_in6* sa_in = (struct sockaddr_in6*)sa;
            struct hostent* h = gethostbyaddr((const char*)&sa_in->sin6_addr, sizeof(sa_in->sin6_addr), AF_INET6);
            if (h)
            {
               hostname = h->h_name;
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

      auto psa = &pitem->m_paddress->u.m_sa;

      auto len = pitem->m_paddress->m_iLen;

      i32 n = getnameinfo(psa, len, host, sizeof(host), serv, sizeof(serv), flags);
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


      //   reverse_cache_item item;

      single_lock synchronouslock(m_pmutexReverseCache, true);

      pitem->m_strReverse = host;
      //item.m_strService = serv;
      pitem->m_durationLastChecked.Now();

      //single_lock synchronouslock(m_pmutexCache, true);

      //m_mapReverseCache.set_at(strIpString, item);

      return true;
#endif // NO_GETADDRINFO

   }



   //string networking::reverse_name(::networking::address * address, bool bSynch, const ::duration& duration)
   //{
   //
   //   string strHostname;
   //
   //   reverse((sockaddr *) &address.u.m_sa,sizeof(address.u.m_sa), strHostname, 0, bSynch, duration);
   //
   //   return strHostname;
   //
   //}


   string networking::reverse_name(::networking::address * address)
   {

      string hostname;

      reverse(hostname, address);

      return hostname;

   }



   bool networking::u2service(const string& name, i32& service, i32 ai_flags)
   {

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
      struct addrinfo* res;
      i32 n = getaddrinfo(nullptr, name, &hints, &res);
      if (!n)
      {
         service = res->ai_protocol;
         freeaddrinfo(res);
         return true;
      }
      return false;
#endif // NO_GETADDRINFO

   }


   i32 networking::service_port(const string& str, i32 flags)
   {

      if (::str().is_simple_natural(str))
         return ::str().to_i32(str);

      if (str.compare_ci("http"))
      {
         return 80;
      }
      else if (str.compare_ci("https"))
      {
         return 443;
      }
      else
      {

         i32 service = 0;

         if (!u2service(str, service, 0))
            return 0;

         return service;

      }

   }


   string  networking::service_name(i32 iPort, i32 flags)
   {

      switch (iPort)
      {
      case 80:
         return "http";
      case 443:
         return "https";
      default:
         return "";
      }

   }

   string networking::canonical_name(::networking::address * paddress)
   {

      string str;

      auto paddress2 = (::networking_bsd::address *) paddress->m_p2;

      if (paddress2->u.m_sa.sa_family == AF_INET)
      {
         
         convert(str, paddress2->u.m_addr.sin_addr);

      }
      else if (paddress2->u.m_sa.sa_family == AF_INET6)
      {

         convert(str, paddress2->u.m_addr6.sin6_addr);

      }

      return str;

   }


   string networking::service_name(::networking::address * paddress)
   {

      return service_name(paddress->get_service_number());

   }


   networking::dns_cache_item::dns_cache_item()
   {

      __zero(m_ipaddr);
      m_bOk = false;
      m_bTimeout = true;

   }


   networking::dns_cache_item::dns_cache_item(const dns_cache_item& item)
   {

      this->operator = (item);

   }



   networking::dns_cache_item& networking::dns_cache_item::operator = (const dns_cache_item& item)
   {

      if (this == &item)
         return *this;

      ::memcpy_dup(&m_ipaddr, &item.m_ipaddr, sizeof(m_ipaddr));
      m_durationLastChecked = item.m_durationLastChecked;
      m_bOk = item.m_bOk;
      m_bTimeout = item.m_bTimeout;

      return *this;

   }


   networking::reverse_cache_item::reverse_cache_item()
   {

      //__zero(m_ipaddr);
      //m_durationLastChecked = 0;
      m_bOk = false;
      m_bTimeout = true;

   }


   networking::reverse_cache_item::reverse_cache_item(const reverse_cache_item& item)
   {

      this->operator = (item);

   }



   networking::reverse_cache_item& networking::reverse_cache_item::operator = (const reverse_cache_item& item)
   {

      if (this != &item)
      {

         auto paddress = __new(address);

         *paddress = *item.m_paddress;

         m_paddress = paddress;
         m_strIpAddress = item.m_strIpAddress;
         m_durationLastChecked = item.m_durationLastChecked;
         m_strReverse = item.m_strReverse;
         m_bOk = item.m_bOk;
         m_bTimeout = item.m_bTimeout;
         m_bProcessing = item.m_bProcessing;

      }

      return *this;

   }



//   void networking::ResolveLocal()
//   {
//
//      char h[256];
//
//      // get local hostname and translate into ip-address
//      *h = 0;
//      gethostname(h, 255);
//      {
//         if (convert(m_ip, h))
//         {
//            convert(m_addr, m_ip);
//         }
//      }
//#ifdef ENABLE_IPV6
//#ifdef IPPROTO_IPV6
//      __memset(&m_local_ip6, 0, sizeof(m_local_ip6));
//      {
//         if (convert(m_local_ip6, h))
//         {
//            convert(m_local_addr6, m_local_ip6);
//         }
//      }
//#endif
//#endif
//      m_host = h;
//      m_local_resolved = true;
//
//   }
//
//
//   const string& networking::GetLocalHostname()
//   {
//      if (!m_local_resolved)
//      {
//         ResolveLocal();
//      }
//      return m_host;
//   }
//
//
//   in_addr networking::GetLocalIP()
//   {
//      if (!m_local_resolved)
//      {
//         ResolveLocal();
//      }
//      return m_ip;
//   }
//
//
//   const string& networking::GetLocalAddress()
//   {
//      if (!m_local_resolved)
//      {
//         ResolveLocal();
//      }
//      return m_addr;
//   }
//
//
//   const struct in6_addr& networking::GetLocalIP6()
//   {
//      if (!m_local_resolved)
//      {
//         ResolveLocal();
//      }
//      return m_local_ip6;
//   }
//
//
//   const string& networking::GetLocalAddress6()
//   {
//      if (!m_local_resolved)
//      {
//         ResolveLocal();
//      }
//      return m_local_addr6;
//   }


   CLASS_DECL_NETWORKING_BSD class networking* networking()
   {

      return g_paddressdepartment;

   }





   i32 family_len(i32 family)
   {

      if (family == AF_INET)
      {

         return sizeof(sockaddr_in);

      }
      else if (family == AF_INET6)
      {

         return sizeof(sockaddr_in6);

      }
      else if (family == AF_UNSPEC)
      {

         return 0;

      }
      else
      {

         throw ::not_implemented();

      }

   }



   //void networking::initialize(::particle * pparticle)
   //{

   //   if (m_bInitialized)
   //   {

   //      return;

   //   }

   //   //auto estatus = ::object::initialize(pparticle);

   //   ::object::initialize(pparticle);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   m_bInitialized = true;

   //   //if(psystem->m_bGudoNetCache)
   //   {

   //      //get_app()->gudo_get("networking_bsd::networking::m_mapCache",m_mapCache);

   //      //get_app()->gudo_get("networking_bsd::networking::m_mapReverseCache",m_mapReverseCache);

   //   }


   //   //return estatus;

   //}


   //   bool networking::gudo_set()
   //   {
   //
   //      if(!m_bInitialized)
   //         return false;
   //
   ////      m_mapCache.gudo_set();
   //
   //      //    m_mapReverseCache.gudo_set();
   //
   //      return true;
   //
   //   }


   //void networking::destroy()
   //{

   //   ::object::destroy();

   //   if (m_bInitialized)
   //   {

   //      m_bInitialized = false;

   //   }

   //   //return ::success;

   //}


   ///*
   //* Encode string per RFC1738 URL encoding rules
   //* tnx rstaveley
   //*/
   //string networking::rfc1738_encode(const string & src)
   //{

   //   static char hex[] = "0123456789ABCDEF";

   //   string dst;

   //   for (i32 i = 0; i < src.get_length(); i++)
   //   {

   //      if (ansi_char_is_alnum((uchar)src[i]))
   //      {

   //         dst += src[i];

   //      }
   //      else if (src[i] == ' ')
   //      {

   //         dst += '+';

   //      }
   //      else
   //      {

   //         uchar ca = static_cast<uchar>(src[i]);

   //         dst += '%';

   //         dst += hex[ca / 16];

   //         dst += hex[ca % 16];

   //      }

   //   }

   //   return dst;

   //} // rfc1738_encode


   ///*
   //* Decode string per RFC1738 URL encoding rules
   //* tnx rstaveley
   //*/
   //string networking::rfc1738_decode(const string & src)
   //{
   //   string dst;
   //   for (i32 i = 0; i < src.get_length(); i++)
   //   {
   //      if (src[i] == '%' && isxdigit((uchar)(src[i + 1])) && isxdigit((uchar)(src[i + 2])))
   //      {
   //         char c1 = src[++i];
   //         char c2 = src[++i];
   //         c1 = c1 - 48 - ((c1 >= 'A') ? 7 : 0) - ((c1 >= 'a') ? 32 : 0);
   //         c2 = c2 - 48 - ((c2 >= 'A') ? 7 : 0) - ((c2 >= 'a') ? 32 : 0);
   //         dst += (char)(c1 * 16 + c2);
   //      }
   //      else if (src[i] == '+')
   //      {
   //         dst += ' ';
   //      }
   //      else
   //      {
   //         dst += src[i];
   //      }
   //   }
   //   return dst;
   //} // rfc1738_decode


   //bool networking::is_ip4(const ::string & str)
   //{
   //   i32 dots = 0;
   //   // %! ignore :port?
   //   for (i32 i = 0; i < str.get_length(); i++)
   //   {
   //      if (str[i] == '.')
   //         dots++;
   //      else if (!isdigit((uchar)str[i]))
   //         return false;
   //   }
   //   if (dots != 3)
   //      return false;
   //   return true;
   //}


   //bool networking::is_ip6(const ::string & str)
   //{
   //   if (str.is_empty())
   //      return false;
   //   index qc = 0;
   //   index qd = 0;
   //   for (i32 i = 0; i < str.get_length(); i++)
   //   {
   //      qc += (str[i] == ':') ? 1 : 0;
   //      qd += (str[i] == '.') ? 1 : 0;
   //   }
   //   if (qc < 2)
   //      return false;
   //   if (qc > 7)
   //   {
   //      return false;
   //   }
   //   if (qd && qd != 3)
   //   {
   //      return false;
   //   }

   //   ::parse pa(str, ":.");

   //   string tmp = pa.getword();

   //   while (tmp.get_length())
   //   {
   //      if (tmp.get_length() > 4)
   //      {
   //         return false;
   //      }
   //      for (i32 i = 0; i < tmp.get_length(); i++)
   //      {
   //         if (tmp[i] < '0' || (tmp[i] > '9' && tmp[i] < 'A') ||
   //            (tmp[i] > 'F' && tmp[i] < 'a') || tmp[i] > 'f')
   //         {
   //            return false;
   //         }
   //      }
   //      //
   //      tmp = pa.getword();
   //   }
   //   return true;
   //}

   //   bool networking::convert(in_addr & l, const ::string & str, i32 ai_flags)
   //   {
   //
   //      if(str.is_empty())
   //         return false;
   //
   //      single_lock synchronouslock(m_pmutexCache, true);
   //      dns_cache_item item;
   //      if(m_mapCache.lookup(str, item) && (item.m_bOk && (!item.m_bTimeout || ((item.m_durationLastChecked.elapsed()) < (5 * 60 * 1000)))))
   //      {
   //         if (item.m_bOk)
   //         {
   //            l = item.m_ipaddr;
   //         }
   //         //         ::duration tick2= ::duration::now();
   //         /*FORMATTED_TRACE("Got from cache networking::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
   //         (u32)((byte*)&pitem->m_ipaddr)[0],
   //         (u32)((byte*)&pitem->m_ipaddr)[1],
   //         (u32)((byte*)&pitem->m_ipaddr)[2],
   //         (u32)((byte*)&pitem->m_ipaddr)[3],
   //         (tick2 - tick1));*/
   //         return item.m_bOk;
   //      }
   //      struct sockaddr_in sa;
   //      __memset(&sa, 0, sizeof(sa));
   //      sa.sin_family = AF_INET;
   //#ifdef NO_GETADDRINFO
   //      if ((ai_flags & AI_NUMERICHOST) != 0 || isipv4(host))
   //      {
   //         ::parse pa((const char *)host, ".");
   //         union
   //         {
   //            struct
   //            {
   //               uchar b1;
   //               uchar b2;
   //               uchar b3;
   //               uchar b4;
   //            } a;
   //            ipaddr_t l;
   //         } u;
   //         u.a.b1 = static_cast<uchar>(pa.getvalue());
   //         u.a.b2 = static_cast<uchar>(pa.getvalue());
   //         u.a.b3 = static_cast<uchar>(pa.getvalue());
   //         u.a.b4 = static_cast<uchar>(pa.getvalue());
   //         ::memcpy_dup(&sa.sin_addr, &u.l, sizeof(sa.sin_addr));
   //         return true;
   //      }
   //#ifndef LINUX
   //      struct hostent *he = gethostbyname( host );
   //      if (!he)
   //      {
   //         return false;
   //      }
   //      ::memcpy_dup(&sa.sin_addr, he -> h_addr, sizeof(sa.sin_addr));
   //#else
   //      struct hostent he;
   //      struct hostent *result = nullptr;
   //      i32 myerrno = 0;
   //      char buf[2000];
   //      i32 n = gethostbyname_r(host, &he, buf, sizeof(buf), &result, &myerrno);
   //      if (n || !result)
   //      {
   //         return false;
   //      }
   //      if (he.h_addr_list && he.h_addr_list[0])
   //         ::memcpy_dup(&sa.sin_addr, he.h_addr, 4);
   //      else
   //         return false;
   //#endif
   //      return true;
   //#else
   //      struct addrinfo hints;
   //      __memset(&hints, 0, sizeof(hints));
   //      // AI_NUMERICHOST
   //      // AI_CANONNAME
   //      // AI_PASSIVE - server
   //      // AI_ADDRCONFIG
   //      // AI_V4MAPPED
   //      // AI_ALL
   //      // AI_NUMERICSERV
   //      hints.ai_flags = ai_flags;
   //      hints.ai_family = AF_INET;
   //      hints.ai_socktype = 0;
   //      hints.ai_protocol = 0;
   //      struct addrinfo *res;
   //      if (networking::isipv4(str))
   //         hints.ai_flags |= AI_NUMERICHOST;
   //
   //      i32 n = getaddrinfo(str, nullptr, &hints, &res);
   //      if (n)
   //      {
   //         string error = "getaddrinfo Error: ";
   //#ifndef __CYGWIN__
   //         error += gai_strerror(n);
   //#endif
   //         ERR(error + " for " + str);
   //         item.m_bOk = false;
   //         item.m_bTimeout = true;
   //         item.m_durationLastChecked.Now();
   //         m_mapCache.set_at(str, item);
   //
   //         return false;
   //#endif // NO_GETADDRINFO
   //   }
   //   item.m_bOk = true;
   //   address_array < addrinfo * > vec;
   //   addrinfo * ai = res;
   //   while (ai)
   //   {
   //      if (ai -> ai_addrlen == sizeof(sa))
   //         vec.add( ai );
   //      ai = ai -> ai_next;
   //   }
   //   if (!vec.get_count())
   //      return false;
   //   ai = vec[rand() % vec.get_count()];
   //   {
   //      ::memcpy_dup(&sa, ai -> ai_addr, ai -> ai_addrlen);
   //   }
   //   freeaddrinfo(res);
   //   item.m_ipaddr = sa.sin_addr;
   //   item.m_durationLastChecked.Now();
   //   m_mapCache.set_at(str, item);
   //
   //   //if(psystem->m_bGudoNetCache)
   //   {
   //
   //      //get_app()->gudo_set("networking_bsd::networking::m_mapCache",m_mapCache);
   //
   //   }
   //
   ////      ::duration tick2= ::duration::now();
   ////      FORMATTED_TRACE("DNS lookup networking::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
   //   //       (u32)((byte*)&pitem->m_ipaddr)[0],
   //   //     (u32)((byte*)&pitem->m_ipaddr)[1],
   //   //   (u32)((byte*)&pitem->m_ipaddr)[2],
   //   // (u32)((byte*)&pitem->m_ipaddr)[3],
   //   //(tick2 - tick1));
   //   l = item.m_ipaddr;
   //
   //   return item.m_bOk;
   //
   //}
   //

   //bool networking::convert(struct in6_addr& l, const ::string & str, i32 ai_flags)
   //{


   //   return from_string(l, str) != false;


   //}

   //
   //bool networking::convert(string & str, const in_addr & ip)
   //{
   //
   //   struct sockaddr_in sa;
   //
   //   __memset(&sa, 0, sizeof(sa));
   //
   //   sa.sin_family  = AF_INET;
   //
   //   sa.sin_addr    = ip;
   //
   //   try
   //   {
   //
   //      __string(str, sa);
   //
   //      return true;
   //
   //   }
   //   catch (...)
   //   {
   //
   //   }
   //
   //   return false;
   //
   //}
   //
   //
   //bool networking::convert(string & str, const struct in6_addr& ip, bool mixed)
   //{
   //
   //
   //   char slask[100]; // l2ip temporary
   //   *slask = 0;
   //   u32 prev = 0;
   //   bool skipped = false;
   //   bool ok_to_skip = true;
   //   if (mixed)
   //   {
   //      u16 x;
   //      u16 addr16[8];
   //      ::memcpy_dup(addr16, &ip, sizeof(addr16));
   //      for (index i = 0; i < 6; i++)
   //      {
   //         x = ntohs(addr16[i]);
   //         if (*slask && (x || !ok_to_skip || prev))
   //            ansi_concatenate(slask,":");
   //         if (x || !ok_to_skip)
   //         {
   //            sprintf(slask + strlen(slask),"%x", x);
   //            if (x && skipped)
   //               ok_to_skip = false;
   //         }
   //         else
   //         {
   //            skipped = true;
   //         }
   //         prev = x;
   //      }
   //      x = ntohs(addr16[6]);
   //      sprintf(slask + strlen(slask),":%u.%u",x / 256,x & 255);
   //      x = ntohs(addr16[7]);
   //      sprintf(slask + strlen(slask),".%u.%u",x / 256,x & 255);
   //   }
   //   else
   //   {
   //
   //      struct sockaddr_in6 sa;
   //
   //      __memset(&sa, 0, sizeof(sa));
   //
   //      sa.sin6_family = AF_INET6;
   //
   //      sa.sin6_addr = ip;
   //
   //      try
   //      {
   //
   //         __string(str, sa);
   //
   //         return true;
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }
   //
   //      return false;
   //
   //   }
   //   str = slask;
   //   return true;
   //}


   //i32 networking::in6_addr_compare(in6_addr a, in6_addr b)
   //{
   //   for (index i = 0; i < 16; i++)
   //   {
   //      if (a.s6_addr[i] < b.s6_addr[i])
   //         return -1;
   //      if (a.s6_addr[i] > b.s6_addr[i])
   //         return 1;
   //   }
   //   return 0;
   //}

   //string networking::Sa2String(struct sockaddr *sa)
   //{
   //   if (sa -> sa_family == AF_INET6)
   //   {
   //      struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)sa;
   //      string tmp;
   //      convert(tmp, sa6 -> sin6_addr);
   //      return tmp + ":" + __string(ntohs(sa6 -> sin6_port));
   //   }
   //   if (sa -> sa_family == AF_INET)
   //   {
   //      struct sockaddr_in *sa4 = (struct sockaddr_in *)sa;
   //      string tmp;
   //      convert(tmp, sa4 -> sin_addr);
   //      return tmp + ":" + __string(ntohs(sa4 -> sin_port));
   //   }
   //   return "";
   //}
   //

   /*
   ::networking::address networking::CreateAddress(struct sockaddr *sa,socklen_t sa_len)
   {
      retur
      switch (sa -> sa_family)
      {
      case AF_INET:
         if (sa_len == sizeof(struct sockaddr_in))
         {
            struct sockaddr_in *point = (struct sockaddr_in *)sa;
            ::networking_bsd::address_pointer addr;
            addr(memory_new ::networking_bsd::ipv4_address(get_app(), *point_i32));
            return addr;
         }
         break;
      case AF_INET6:
         if (sa_len == sizeof(struct sockaddr_in6))
         {
            struct sockaddr_in6 *point = (struct sockaddr_in6 *)sa;
            ::networking_bsd::address_pointer addr;
            addr(memory_new ::networking_bsd::ipv6_address(get_app(), *point_i32));
            return addr;
         }
         break;
      }
      return ::networking_bsd::address_pointer();
   }
   */

   /*   bool networking::convert(in_addr & sa, const string & host, i32 ai_flags)
      {

         __memset(&sa, 0, sizeof(sa));
         sa.sin_family = AF_INET;
   #ifdef NO_GETADDRINFO
         if ((ai_flags & AI_NUMERICHOST) != 0 || isipv4(host))
         {
            ::parse pa((const char *)host, ".");
            union {
               struct {
                  uchar b1;
                  uchar b2;
                  uchar b3;
                  uchar b4;
               } a;
               ipaddr_t l;
            } u;
            u.a.b1 = static_cast<uchar>(pa.getvalue());
            u.a.b2 = static_cast<uchar>(pa.getvalue());
            u.a.b3 = static_cast<uchar>(pa.getvalue());
            u.a.b4 = static_cast<uchar>(pa.getvalue());
            ::memcpy_dup(&sa.sin_addr, &u.l, sizeof(sa.sin_addr));
            return true;
         }
   #ifndef LINUX
         struct hostent *he = gethostbyname( host );
         if (!he)
         {
            return false;
         }
         ::memcpy_dup(&sa.sin_addr, he -> h_addr, sizeof(sa.sin_addr));
   #else
         struct hostent he;
         struct hostent *result = nullptr;
         i32 myerrno = 0;
         char buf[2000];
         i32 n = gethostbyname_r(host, &he, buf, sizeof(buf), &result, &myerrno);
         if (n || !result)
         {
            return false;
         }
         if (he.h_addr_list && he.h_addr_list[0])
            ::memcpy_dup(&sa.sin_addr, he.h_addr, 4);
         else
            return false;
   #endif
         return true;
   #else
         struct addrinfo hints;
         __memset(&hints, 0, sizeof(hints));
         // AI_NUMERICHOST
         // AI_CANONNAME
         // AI_PASSIVE - server
         // AI_ADDRCONFIG
         // AI_V4MAPPED
         // AI_ALL
         // AI_NUMERICSERV
         hints.ai_flags = ai_flags;
         hints.ai_family = AF_INET;
         hints.ai_socktype = 0;
         hints.ai_protocol = 0;
         struct addrinfo *res;
         if (networking::isipv4(host))
            hints.ai_flags |= AI_NUMERICHOST;
         i32 n = getaddrinfo(host, nullptr, &hints, &res);
         if (!n)
         {
            ref_array <  addrinfo > vec;
            addrinfo *ai = res;
            while (ai)
            {
               if (ai -> ai_addrlen == sizeof(sa))
                  vec.add( ai );
               ai = ai -> ai_next;
            }
            if (!vec.get_count())
               return false;
            ai = vec[pmathematics->rnd() % vec.get_count()];
            {
               ::memcpy_dup(&sa, ai -> ai_addr, ai -> ai_addrlen);
            }
            freeaddrinfo(res);
            return true;
         }
         string error = "Error: ";
   #ifndef __CYGWIN__
         error += gai_strerror(n);
   #endif
         return false;
   #endif // NO_GETADDRINFO
      }*/


      //bool networking::convert(struct in6_addr & sa, const string & host, i32 ai_flags)
      //{
      //
      //   try
      //   {
      //
      //      ::from_string(sa, host);
      //
      //   }
      //   catch (const ::exception & e)
      //   {
      //
      //      output_debug_string(e.m_strMessage);
      //
      //      return false;
      //
      //      //if (e.is < parsing_exception >())
      //      {
      //
      //        // return false;
      //
      //      }
      //      //else
      //      {
      //
      //        // __rethrow(e);
      //
      //      }
      //
      //   }
      //
      //   __memset(&sa, 0, sizeof(sa));
      //#ifdef WINDOWS
      //#else
      //   //sa.sin6_family = AF_INET6;
      //#endif
      //#ifdef NO_GETADDRINFO
      //   if ((ai_flags & AI_NUMERICHOST) != 0 || isipv6(host))
      //   {
      //      //         list<string> vec;
      //      index x = 0;
      //      for (index i = 0; i <= host.get_length(); i++)
      //      {
      //         if (i == host.get_length() || host[i] == ':')
      //         {
      //            string s = host.Mid(x, i - x);
      //            //
      //            if (strstr(s,".")) // x.x.x.x
      //            {
      //               Parse pa(s,".");
      //               char slask[100]; // u2ip temporary hgenstring conversion
      //               unsigned long b0 = static_cast<unsigned long>(pa.getvalue());
      //               unsigned long b1 = static_cast<unsigned long>(pa.getvalue());
      //               unsigned long b2 = static_cast<unsigned long>(pa.getvalue());
      //               unsigned long b3 = static_cast<unsigned long>(pa.getvalue());
      //               sprintf(slask,"%lx",b0 * 256 + b1);
      //               vec.push_back(slask);
      //               sprintf(slask,"%lx",b2 * 256 + b3);
      //               vec.push_back(slask);
      //            }
      //            else
      //            {
      //               vec.push_back(s);
      //            }
      //            //
      //            x = i + 1;
      //         }
      //      }
      //      index sz = vec.get_length(); // number of byte pairs
      //      index i = 0; // index in in6_addr.in6_u.u6_addr16[] ( 0 .. 7 )
      //      u16 addr16[8];
      //      for (list<string>::iterator it = vec.begin(); it != vec.end(); it++)
      //      {
      //         string bytepair = *it;
      //         if (bytepair.get_length())
      //         {
      //            addr16[i++] = htons(networking::hgenunsigned(bytepair));
      //         }
      //         else
      //         {
      //            addr16[i++] = 0;
      //            while (sz++ < 8)
      //            {
      //               addr16[i++] = 0;
      //            }
      //         }
      //      }
      //      ::memcpy_dup(&sa.sin6_addr, addr16, sizeof(addr16));
      //      return true;
      //   }
      //#ifdef SOLARIS
      //   i32 errnum = 0;
      //   struct hostent *he = getipnodebyname( host, AF_INET6, 0, &errnum );
      //#else
      //   struct hostent *he = gethostbyname2( host, AF_INET6 );
      //#endif
      //   if (!he)
      //   {
      //      return false;
      //   }
      //   ::memcpy_dup(&sa.sin6_addr,he -> h_addr_list[0],he -> h_length);
      //#ifdef SOLARIS
      //   free(he);
      //#endif
      //   return true;
      //#else
      //   struct addrinfo hints;
      //   __memset(&hints, 0, sizeof(hints));
      //   hints.ai_flags = ai_flags;
      //   hints.ai_family = AF_INET6;
      //   hints.ai_socktype = SOCK_STREAM;
      //   hints.ai_protocol = IPPROTO_TCP;
      //   struct addrinfo *res;
      //   if (networking::isipv6(host))
      //      hints.ai_flags |= AI_NUMERICHOST;
      //   i32 n = getaddrinfo(host, nullptr, &hints, &res);
      //   if (!n)
      //   {
      //
      //      array <  sockaddr_in6 * > addra;
      //      struct addrinfo *ai = res;
      //      int iSaSize = sizeof(sockaddr_in6);
      //      //char ipstringbuffer[46];
      //      ::u32 ipbufferlength = 46;
      //      while (ai)
      //      {
      //         // The buffer length is changed by each call to WSAAddresstoString
      //         // So we need to set it for each iteration through the loop for safety
      //         if (ai -> ai_addrlen == iSaSize)
      //            addra.add((sockaddr_in6 *)ai->ai_addr);
      //         ai = ai -> ai_next;
      //      }
      //      if(addra.is_empty())
      //         return false;
      //      ::memcpy_dup(&sa, &::papaya::array::pick_random(addra)->sin6_addr, sizeof(sa));
      //      freeaddrinfo(res);
      //      return true;
      //   }
      //   string error = "Error: ";
      //#ifndef __CYGWIN__
      //   error += gai_strerror(n);
      //#endif
      //   return false;
      //#endif // NO_GETADDRINFO
      //
      //}
      //
      //
      //bool networking::reverse(string & number, const string & hostname)
      //{
      //
      //   ::networking::address address(hostname);
      //
      //   number = address.get_display_number();
      //
      //   return true;
      //
      //}
      //
      //
      //bool networking::reverse_schedule(reverse_cache_item * pitem)
      //{
      //
      //   synchronous_lock synchronouslock(this->synchronization());
      //
      //   m_reversecacheaRequest.add(pitem);
      //
      //   if (!m_pthreadReverse)
      //   {
      //
      //      auto psystem = get_system()->m_papexsystem;
      //
      //      m_pthreadReverse = psystem->fork([this]()
      //         {
      //
      //            ::task_set_name("reverse_dns");
      //
      //            single_lock synchronouslock(this->synchronization());
      //
      //            while (task_get_run())
      //            {
      //
      //               synchronouslock.lock();
      //
      //               if (m_reversecacheaRequest.has_elements())
      //               {
      //
      //                  auto pitem = m_reversecacheaRequest[0];
      //
      //                  m_reversecacheaRequest.erase_at(0);
      //
      //                  synchronouslock.unlock();
      //
      //                  reverse_sync(pitem);
      //
      //               }
      //               else
      //               {
      //
      //                  synchronouslock.unlock();
      //
      //                  if (!task_sleep(100_ms))
      //                  {
      //
      //                     break;
      //
      //                  }
      //
      //               }
      //
      //            }
      //
      //            m_pthreadReverse.release();
      //
      //         });
      //
      //   }
      //
      //   return true;
      //
      //}
      //
      //
      //bool networking::reverse(string & hostname, ::networking::address * address)
      //{
      //
      //   single_lock synchronouslock(m_pmutexReverseCache, true);
      //
      //   auto & pitem = m_mapReverseCache[address.get_display_number()];
      //
      //   if (pitem && !pitem->m_bProcessing && !pitem->m_bTimeout && pitem->m_durationLastChecked.elapsed() < 3600_min)
      //   {
      //
      //      hostname = pitem->m_strReverse;
      //
      //      return pitem->m_bOk;
      //
      //   }
      //
      //   pitem = __new(reverse_cache_item);
      //
      //   pitem->m_address = address;
      //
      //   pitem->m_bTimeout = false;
      //
      //   pitem->m_bProcessing = true;
      //
      //   pitem->m_bOk = false;
      //
      //   reverse_schedule(pitem);
      //
      //   return true;
      //
      //}
      //
      //
      //bool networking::reverse_sync(reverse_cache_item * pitem)
      //{
      //
      //   int flags = NI_NUMERICHOST;
      //
      //#ifdef NO_GETADDRINFO
      //   switch (sa->sa_family)
      //   {
      //   case AF_INET:
      //      if (flags & NI_NUMERICHOST)
      //      {
      //         union
      //         {
      //            struct
      //            {
      //               uchar b1;
      //               uchar b2;
      //               uchar b3;
      //               uchar b4;
      //            } a;
      //            ipaddr_t l;
      //         } u;
      //         struct sockaddr_in* sa_in = (struct sockaddr_in*)sa;
      //         ::memcpy_dup(&u.l, &sa_in->sin_addr, sizeof(u.l));
      //         char tmp[100];
      //         sprintf(tmp, "%u.%u.%u.%u", u.a.b1, u.a.b2, u.a.b3, u.a.b4);
      //         hostname = tmp;
      //         return true;
      //      }
      //      else
      //      {
      //         struct sockaddr_in* sa_in = (struct sockaddr_in*)sa;
      //         struct hostent* h = gethostbyaddr((const char*)&sa_in->sin_addr, sizeof(sa_in->sin_addr), AF_INET);
      //         if (h)
      //         {
      //            hostname = h->h_name;
      //            return true;
      //         }
      //      }
      //      break;
      //#ifdef ENABLE_IPV6
      //   case AF_INET6:
      //      if (flags & NI_NUMERICHOST)
      //      {
      //         char slask[100]; // l2ip temporary
      //         *slask = 0;
      //         u32 prev = 0;
      //         bool skipped = false;
      //         bool ok_to_skip = true;
      //         {
      //            u16 addr16[8];
      //            struct sockaddr_in6* sa_in6 = (struct sockaddr_in6*)sa;
      //            ::memcpy_dup(addr16, &sa_in6->sin6_addr, sizeof(addr16));
      //            for (index i = 0; i < 8; i++)
      //            {
      //               u16 x = ntohs(addr16[i]);
      //               if (*slask && (x || !ok_to_skip || prev))
      //                  ansi_concatenate(slask, ":");
      //               if (x || !ok_to_skip)
      //               {
      //                  sprintf(slask + strlen(slask), "%x", x);
      //                  if (x && skipped)
      //                     ok_to_skip = false;
      //               }
      //               else
      //               {
      //                  skipped = true;
      //               }
      //               prev = x;
      //            }
      //         }
      //         if (!*slask)
      //            strcpy(slask, "::");
      //         hostname = slask;
      //         return true;
      //      }
      //      else
      //      {
      //         // %! TODO: ipv6 reverse lookup
      //         struct sockaddr_in6* sa_in = (struct sockaddr_in6*)sa;
      //         struct hostent* h = gethostbyaddr((const char*)&sa_in->sin6_addr, sizeof(sa_in->sin6_addr), AF_INET6);
      //         if (h)
      //         {
      //            hostname = h->h_name;
      //            return true;
      //         }
      //      }
      //      break;
      //#endif
      //   }
      //   return false;
      //#else
      //   char host[NI_MAXHOST];
      //   char serv[NI_MAXSERV];
      //   // NI_NOFQDN
      //   // NI_NUMERICHOST
      //   // NI_NAMEREQD
      //   // NI_NUMERICSERV
      //   // NI_DGRAM
      //
      //   auto psa = &pitem->m_address.u.m_sa;
      //
      //   auto len = pitem->m_address.m_iLen;
      //
      //   i32 n = getnameinfo(psa, len, host, sizeof(host), serv, sizeof(serv), flags);
      //   if (n)
      //   {
      //      // EAI_AGAIN
      //      // EAI_BADFLAGS
      //      // EAI_FAIL
      //      // EAI_FAMILY
      //      // EAI_MEMORY
      //      // EAI_NONAME
      //      // EAI_OVERFLOW
      //      // EAI_SYSTEM
      //      return false;
      //   }
      //
      //
      ////   reverse_cache_item item;
      //
      //   single_lock synchronouslock(m_pmutexReverseCache, true);
      //
      //   pitem->m_strReverse = host;
      //   //item.m_strService = serv;
      //   pitem->m_durationLastChecked.Now();
      //
      //   //single_lock synchronouslock(m_pmutexCache, true);
      //
      //   //m_mapReverseCache.set_at(strIpString, item);
      //
      //   return true;
      //#endif // NO_GETADDRINFO
      //
      //}
      //


      //string networking::reverse_name(::networking::address * address, bool bSynch, const ::duration& duration)
      //{
      //
      //   string strHostname;
      //
      //   reverse((sockaddr *) &address.u.m_sa,sizeof(address.u.m_sa), strHostname, 0, bSynch, duration);
      //
      //   return strHostname;
      //
      //}

      //
      //string networking::reverse_name(::networking::address * address)
      //{
      //
      //   string hostname;
      //
      //   reverse(hostname, address);
      //
      //   return hostname;
      //
      //}
      //


//   bool networking::u2service(const string & name, i32 & service, i32 ai_flags)
//   {
//
//#ifdef NO_GETADDRINFO
//      // %!
//      return false;
//#else
//      struct addrinfo hints;
//      service = 0;
//      __memset(&hints, 0, sizeof(hints));
//      // AI_NUMERICHOST
//      // AI_CANONNAME
//      // AI_PASSIVE - server
//      // AI_ADDRCONFIG
//      // AI_V4MAPPED
//      // AI_ALL
//      // AI_NUMERICSERV
//      hints.ai_flags = ai_flags;
//      hints.ai_family = AF_UNSPEC;
//      hints.ai_socktype = 0;
//      hints.ai_protocol = 0;
//      struct addrinfo * res;
//      i32 n = getaddrinfo(nullptr, name, &hints, &res);
//      if (!n)
//      {
//         service = res->ai_protocol;
//         freeaddrinfo(res);
//         return true;
//      }
//      return false;
//#endif // NO_GETADDRINFO
//
//   }
//
//
//   i32 networking::service_port(const ::string & str, i32 flags)
//   {
//
//      if (::str().is_simple_natural(str))
//         return ::str().to_i32(str);
//
//      if (str.compare_ci("http"))
//      {
//         return 80;
//      }
//      else if (str.compare_ci("https"))
//      {
//         return 443;
//      }
//      else
//      {
//
//         i32 service = 0;
//
//         if (!u2service(str, service, 0))
//            return 0;
//
//         return service;
//
//      }
//
//   }


   //string  networking::service_name(i32 iPort, i32 flags)
   //{
   //
   //   switch(iPort)
   //   {
   //   case 80:
   //      return "http";
   //   case 443:
   //      return "https";
   //   default:
   //      return "";
   //   }
   //
   //}

   //string networking::canonical_name(::networking::address * address)
   //{
   //
   //   string str;
   //
   //   if(address.is_ipv4())
   //   {
   //      ::networking_bsd::networking::convert(str, address.u.m_addr.sin_addr);
   //   }
   //   else if(address.is_ipv6())
   //   {
   //      ::networking_bsd::networking::convert(str, address.u.m_addr6.sin6_addr);
   //   }
   //
   //   return str;
   //
   //}
   //
   //
   //string networking::service_name(::networking::address * address)
   //{
   //
   //   return service_name(address.get_service_number());
   //
   //}
   //
   //
   //networking::dns_cache_item::dns_cache_item()
   //{
   //
   //   __zero(m_ipaddr);
   //   m_bOk = false;
   //   m_bTimeout = true;
   //
   //}
   //
   //
   //networking::dns_cache_item::dns_cache_item(const dns_cache_item & item)
   //{
   //
   //   this->operator = (item);
   //
   //}
   //
   //
   //stream & networking::dns_cache_item::write(stream & stream) const
   //{
   //
   //   string strAddress;
   //
   //   __string(strAddress, m_ipaddr);
   //
   //   stream << strAddress;
   //   stream << m_durationLastChecked;
   //   stream << m_bOk;
   //   stream << m_bTimeout;
   //
   //   return stream;
   //
   //}
   //
   //
   //stream & networking::dns_cache_item::read(stream & stream)
   //{
   //
   //   string strAddress;
   //
   //   stream >> strAddress;
   //
   //   ::from_string(m_ipaddr, strAddress);
   //
   //   stream >> m_durationLastChecked;
   //   stream >> m_bOk;
   //   stream >> m_bTimeout;
   //
   //   return stream;
   //
   //}
   //
   //
   //networking::dns_cache_item & networking::dns_cache_item::operator = (const dns_cache_item & item)
   //{
   //
   //   if(this==&item)
   //      return *this;
   //
   //   ::memcpy_dup(&m_ipaddr,&item.m_ipaddr,sizeof(m_ipaddr));
   //   m_durationLastChecked = item.m_durationLastChecked;
   //   m_bOk = item.m_bOk;
   //   m_bTimeout = item.m_bTimeout;
   //
   //   return *this;
   //
   //}
   //
   //
   //networking::reverse_cache_item::reverse_cache_item()
   //{
   //
   //   //__zero(m_ipaddr);
   //   //m_durationLastChecked = 0;
   //   m_bOk = false;
   //   m_bTimeout = true;
   //
   //}
   //
   //
   //networking::reverse_cache_item::reverse_cache_item(const reverse_cache_item & item)
   //{
   //
   //   this->operator = (item);
   //
   //}
   //
   //
   //stream & networking::reverse_cache_item::write(stream & stream) const
   //{
   //
   //   stream << m_address;
   //   stream << m_strReverse;
   //   stream << m_durationLastChecked;
   //   stream << m_bOk;
   //   stream << m_bTimeout;
   //   stream << m_bProcessing;
   //
   //   return stream;
   //
   //}
   //
   //
   //stream & networking::reverse_cache_item::read(stream & stream)
   //{
   //
   //   stream >> m_address;
   //   stream >> m_strReverse;
   //   stream >> m_durationLastChecked;
   //   stream >> m_bOk;
   //   stream >> m_bTimeout;
   //   stream >> m_bProcessing;
   //
   //   return stream;
   //
   //}
   //
   //
   //networking::reverse_cache_item & networking::reverse_cache_item::operator = (const reverse_cache_item & item)
   //{
   //
   //   if(this==&item)
   //      return *this;
   //
   //   m_address = item.m_address;
   //   m_durationLastChecked = item.m_durationLastChecked;
   //   m_strReverse = item.m_strReverse;
   //   m_bOk = item.m_bOk;
   //   m_bTimeout = item.m_bTimeout;
   //   m_bProcessing = item.m_bProcessing;
   //
   //   return *this;
   //
   //}
   //


//i32 networking::_select(::sockets::socket_handler * psockethandler, const class ::wait & wait)
//{
//
//   struct timeval tsel;
//
//   tsel.tv_sec = ::duration(wait).integral_second();
//   tsel.tv_nsec = ::duration(wait).integral_nanosecond() % 1'000'000'000;
//
//   {
//
//      try
//      {
//
//         m_socketmap.values().each([](auto & psocket)
//            {
//
//               psocket->on_select_idle();
//
//            });
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//   ::duration tick1, tick2;
//
//start_processing_adding:
//
//   auto passociationAdd = m_socketmapAdd.get_start();
//
//   if (passociationAdd)
//   {
//
//      if (m_socketmap.get_size() >= FD_SETSIZE)
//      {
//
//         WARNING("Select " << (i32)m_socketmap.get_size() << " FD_SETSIZE reached");
//
//         goto end_processing_adding;
//
//      }
//
//      SOCKET SOCKET = passociationAdd->m_socket_id;
//
//      auto & psocket = passociationAdd->m_psocket_id;
//
//      if (m_socketmap.has(SOCKET))
//      {
//
//         _WARNING(psocket, "add" << (i32)psocket->GetSocketId() << "Attempt to add SOCKET already in controlled queue");
//
//         m_socketmapAdd.erase(passociationAdd);
//
//         goto start_processing_adding;
//
//      }
//
//      if (psocket->IsCloseAndDelete())
//      {
//
//         _WARNING(psocket, "add " << (i32)psocket->GetSocketId() << " Trying to add SOCKET with SetCloseAndDelete() true");
//
//         m_socketidlist.add_tail(SOCKET);
//
//         m_socketmap.move(passociationAdd, &m_socketmapAdd);
//
//         socket_id_list_add(SOCKET, e_list_close);
//
//         goto start_processing_adding;
//
//      }
//
//      auto pstreamsocket_id = dynamic_cast <stream_socket_id *> (psocket.m_p);
//
//      if (::is_set(pstreamsocket_id) && pstreamsocket_id->is_connecting()) // 'open' called before adding SOCKET
//      {
//
//         set(SOCKET, true, true);
//
//      }
//      else
//      {
//
//         auto ptcpsocket = dynamic_cast <tcp_socket *> (psocket.m_p);
//
//         bool bWrite = ::is_set(ptcpsocket) ? ptcpsocket->GetOutputLength() != 0 || ptcpsocket->CallOnConnect() : false;
//
//         bool bRead = ::is_set(ptcpsocket) ? !ptcpsocket->IsDisableRead() : true;
//
//         set(SOCKET, bRead, bWrite);
//
//      }
//
//      m_maxsock = (SOCKET + 1 > m_maxsock) ? SOCKET + 1 : m_maxsock;
//
//      // only add to m_socketidlist (process fd_set events) if
//      //  slave handler and detached/detaching SOCKET
//      //  master handler and non-detached SOCKET
//      //if (!(m_slave ^ psocket->IsDetach()))
//      //if (!(m_slave ^ psocket->IsDetach()))
//      //{
//
//        // m_socketidlist.add_tail(SOCKET);
//
//      //}
//
//      m_socketidlist.add_tail(SOCKET);
//
//      m_socketmap.move(passociationAdd, &m_socketmapAdd);
//
//      if (passociationAdd->m_psocket_id->IsDetach())
//      {
//
//         passociationAdd->m_psocket_id->OnDetached();
//
//      }
//
//      goto start_processing_adding;
//
//   }
//
//end_processing_adding:
//
//   fd_set rfds;
//   fd_set wfds;
//   fd_set efds;
//
//   FD_COPY(&m_rfds, &rfds);
//   FD_COPY(&m_wfds, &wfds);
//   FD_COPY(&m_efds, &efds);
//
//   fd_set * psetR = m_countR > 0 ? &rfds : nullptr;
//   fd_set * psetW = m_countW > 0 ? &wfds : nullptr;
//   fd_set * psetE = m_countE > 0 ? &efds : nullptr;
//
//   i32 n = 0;
//
//   tick1 = ::duration::now();
//
//   ::duration tickRWENull;
//
//   if (psetR == nullptr && psetW == nullptr && psetE == nullptr)
//   {
//
//      tickRWENull.Now();
//
//      //INFORMATION("rfds, wfds and efds are null!!"));
//
//   }
//   else
//   {
//
//      //debug_print(" m_socketmap : %d\n", m_socketmap.size());
//      //debug_print(" m_socketmapAdd     : %d\n", m_socketmapAdd.size());
//      //debug_print(" m_delete  : %d\n", m_delete.size());
//
//      if (m_b_use_mutex)
//      {
//
//         mutex()->unlock();
//
//         n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);
//
//         m_iSelectErrno = networking_last_error();
//
//         mutex()->lock();
//
//      }
//      else
//      {
//
//         n = ::select((int)m_maxsock, psetR, psetW, psetE, tsel);
//
//         m_iSelectErrno = networking_last_error();
//
//      }
//
//   }
//
//
//}





//networking_bsd::networking_bsd()
//{
//
//
//}


//networking_bsd::~networking_bsd()
//{
//
//   ::acme::del(::net::g_paddressdepartment);
//   //::acme::del(m_psslinit);
//
//   //::acme::del(m_pajpaxissocketinit);
//
//}
//
//
//void networking_bsd::initialize(::particle * pparticle)
//{
//
//   //auto estatus = sockets_base::initialize(pparticle);
//
//   sockets_base::initialize(pparticle);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   auto paddressdepartment = pparticle->__create_new<class ::networking::address_department>();
//
//   paddressdepartment->increment_reference_count();
//
//   ::net::g_paddressdepartment = paddressdepartment;
//
//   generate_random_bytes(m_baTicketKey, sizeof(m_baTicketKey));
//
//   m_psslinit = __create_new<::networking_bsd::SSLInitializer>();
//
//   //estatus = __construct_new(m_pnet);
//
//   __construct_new(m_pnet);
//
//   if (!m_pnet)
//   {
//
//      m_iErrorCode = -1;
//
//      //return error_failed;
//
//      return;
//
//   }
//
//   //if (!m_pnet->initialize(this))
//   m_pnet->initialize(this);
//   /*{
//
//      return error_failed;
//
//   }*/
//
//   //if (!::acme::department::initialize())
//   //{
//
//   //   return error_failed;
//
//   //}
//
////      try
////      {
////
////#ifdef WINDOWS
////         __construct(m_pportforward);
////#endif
////
////      }
////      catch (...)
////      {
////
////      }
//
//
//      //m_pajpaxissocketinit = memory_new AjpBaseSocket::Initializer;
//
//   m_countHttpPostBoundary = 0;
//
//   // return ::success;
//
//}




//::networking_bsd::net & networking_bsd::net()
//{
//
//   return *m_pnet;
//
//}


   string networking::get_http_post_boundary()
   {

      //auto psystem = get_system()->m_papexsystem;

      single_lock lock(m_pmutexHttpPostBoundary, true);

      string strBoundary = "----";

      for (int i = 0; i < 12; i++)
      {

         char c = m_countHttpPostBoundary++ % 128;

         while (!ansi_char_is_alnum((unsigned char)c))
         {

            c = m_countHttpPostBoundary++ % 128;

         }

         strBoundary += c;

      }

      strBoundary += "__" + __string(m_countHttpPostBoundary++);

      return strBoundary;

   }


   ::pointer<address>networking::create_ip4_address(u32 u, ::networking::port_t port)
   {

      auto paddress2 = __new(address);

   #if defined(BSD_STYLE_SOCKETS)

      auto a = *paddress2;

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


      return paddress2;

   }

   ::pointer<address>networking::create_ip6_address(void * p128bits, ::networking::port_t port)
   {

      auto paddress2 = __new(address);
   #if defined(BSD_STYLE_SOCKETS)

      auto a = *paddress2;
      ::zero(&a, sizeof(a));

      a.m_iLen = sizeof(sockaddr_in6);
      a.u.m_addr6.sin6_family = AF_INET6;
      a.u.m_addr6.sin6_port = port;
      ::memcpy_dup(&a.u.m_addr6.sin6_addr, p128bits, sizeof(a.u.m_addr6.sin6_addr));

      a.sync_os_address();
      a.sync_os_service();

   #endif

      return paddress2;

   }


   ::pointer<::networking::address>networking::create_ip4_address(const ::string & strAddress, ::networking::port_t port)
   {

      auto paddress2 = __new(address);

      if(convert(paddress2->u.m_addr.sin_addr, strAddress))
      {

         paddress2->u.s.set_family(AF_INET);

         paddress2->set_service_number(port);

      }

      return paddress2;

   }

   ::pointer<::networking::address>networking::create_ip6_address(const ::string & strAddress, ::networking::port_t port)
   {

      auto paddress2 = __new(address);

      if (convert(paddress2->u.m_addr6.sin6_addr, strAddress))
      {

         paddress2->u.s.set_family(AF_INET6);

         paddress2->set_service_number(port);

      }

      return paddress2;

   }


   //address_pointer networking::create_address(const ::string & strAddress, port_t port)
   //{

   //   if (is_ip6(strAddress))
   //   {

   //      return create_ip6_address(strAddress))

   //   }
   //   else if (paddressdepartment->isipv4(strAddress))
   //   {

   //      if (paddressdepartment->convert(u.m_addr.sin_addr, strAddress))
   //      {

   //         u.s.set_family(AF_INET);

   //      }

   //   }
   //   else
   //   {

   //      throw ::exception(error_parsing, "Unrecognized networking IP address");

   //   }


   //}


} // namespace networking_bsd


