#include "framework.h"
#include "apex/net/sockets/_.h"
#include "apex/net/_net_impl.h"
#include <stdio.h>

#ifdef RASPBIAN
#include <sys/types.h>
#include <unistd.h>
#endif


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
#undef USE_MISC

#if defined(__APPLE__)
#define  NI_MAXHOST  1025
#define  NI_MAXSERV  32
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif
//#define __USE_MISC
//#include <ctype.h>
#endif


namespace sockets
{


   net::net()
   {

      defer_create_mutex();

      m_bInitialized = false;
      //m_mapCache.m_bAutoGudoSet = false;
      //m_mapReverseCache.m_bAutoGudoSet = false;

      //m_mapCache.remove_all();
      //m_mapReverseCache.remove_all();

   }


   net::~net()
   {

   }


   ::estatus     net::initialize(::layered * pobjectContext)
   {

      if(m_bInitialized)
         return true;

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_bInitialized = true;

      //if(System.m_bGudoNetCache)
      {

         //Application.gudo_get("sockets::net::m_mapCache",m_mapCache);

         //Application.gudo_get("sockets::net::m_mapReverseCache",m_mapReverseCache);

      }


      return estatus;

   }


   bool net::gudo_set()
   {

      if(!m_bInitialized)
         return false;

//      m_mapCache.gudo_set();

      //    m_mapReverseCache.gudo_set();

      return true;

   }


   void net::finalize()
   {

      ::object::finalize();

      if (!m_bInitialized)
      {

         return;

      }

      m_bInitialized = false;

   }


   /*
   * Encode string per RFC1738 URL encoding rules
   * tnx rstaveley
   */
   string net::rfc1738_encode(const string & src)
   {
      static   char hex[] = "0123456789ABCDEF";
      string dst;
      for (i32 i = 0; i < src.get_length(); i++)
      {
         if (ansi_char_is_alphanumeric((uchar) src[i]))
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
   string net::rfc1738_decode(const string & src)
   {
      string dst;
      for (i32 i = 0; i < src.get_length(); i++)
      {
         if (src[i] == '%' && isxdigit((uchar) (src[i + 1])) && isxdigit((uchar) (src[i + 2])))
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


   bool net::isipv4(const string & str)
   {
      i32 dots = 0;
      // %! ignore :port?
      for (i32 i = 0; i < str.get_length(); i++)
      {
         if (str[i] == '.')
            dots++;
         else if (!isdigit((uchar) str[i]))
            return false;
      }
      if (dots != 3)
         return false;
      return true;
   }


   bool net::isipv6(const string & str)
   {
      if(str.is_empty())
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
      ::str::parse pa(str,":.");
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

   bool net::convert(in_addr & l, const string & str, i32 ai_flags)
   {

      if(str.is_empty())
         return false;

      single_lock sl(&m_mutexCache, true);
      dns_cache_item item;
      if(m_mapCache.lookup(str, item) && (item.m_bOk && (!item.m_bTimeout || ((item.m_tickLastChecked.elapsed()) < (5 * 60 * 1000)))))
      {
         if (item.m_bOk)
         {
            l = item.m_ipaddr;
         }
         //         tick tick2 = ::get_tick();
         /*TRACE("Got from cache net::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
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
         ::str::parse pa((const char *)host, ".");
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
      if (net::isipv4(str))
         hints.ai_flags |= AI_NUMERICHOST;

      i32 n = getaddrinfo(str, nullptr, &hints, &res);
      if (n)
      {
         string error = "getaddrinfo Error: ";
#ifndef __CYGWIN__
         error += gai_strerror(n);
#endif
         ERR(error + " for " + str);
         item.m_bOk = false;
         item.m_bTimeout = true;
         item.m_tickLastChecked.Now();
         m_mapCache.set_at(str, item);

         return false;
#endif // NO_GETADDRINFO
   }
   item.m_bOk = true;
   address_array < addrinfo * > vec;
   addrinfo * ai = res;
   while (ai)
   {
      if (ai -> ai_addrlen == sizeof(sa))
         vec.add( ai );
      ai = ai -> ai_next;
   }
   if (!vec.get_count())
      return false;
   ai = vec[rand() % vec.get_count()];
   {
      ::memcpy_dup(&sa, ai -> ai_addr, ai -> ai_addrlen);
   }
   freeaddrinfo(res);
   item.m_ipaddr = sa.sin_addr;
   item.m_tickLastChecked.Now();
   m_mapCache.set_at(str, item);

   //if(System.m_bGudoNetCache)
   {

      //Application.gudo_set("sockets::net::m_mapCache",m_mapCache);

   }

//      tick tick2 = ::get_tick();
//      TRACE("DNS lookup net::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
   //       (u32)((byte*)&pitem->m_ipaddr)[0],
   //     (u32)((byte*)&pitem->m_ipaddr)[1],
   //   (u32)((byte*)&pitem->m_ipaddr)[2],
   // (u32)((byte*)&pitem->m_ipaddr)[3],
   //(tick2 - tick1));
   l = item.m_ipaddr;

   return item.m_bOk;

}


//bool net::convert(struct in6_addr& l, const string & str, i32 ai_flags)
//{


//   return from_string(l, str) != FALSE;


//}


bool net::convert(string & str, const in_addr & ip)
{

   struct sockaddr_in sa;

   __memset(&sa, 0, sizeof(sa));

   sa.sin_family  = AF_INET;

   sa.sin_addr    = ip;

   try
   {

      ::str::from(str, sa);

      return true;

   }
   catch (...)
   {

   }

   return false;

}


bool net::convert(string & str, const struct in6_addr& ip, bool mixed)
{


   char slask[100]; // l2ip temporary
   *slask = 0;
   u32 prev = 0;
   bool skipped = false;
   bool ok_to_skip = true;
   if (mixed)
   {
      u16 x;
      u16 addr16[8];
      ::memcpy_dup(addr16, &ip, sizeof(addr16));
      for (index i = 0; i < 6; i++)
      {
         x = ntohs(addr16[i]);
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
      x = ntohs(addr16[6]);
      sprintf(slask + strlen(slask),":%u.%u",x / 256,x & 255);
      x = ntohs(addr16[7]);
      sprintf(slask + strlen(slask),".%u.%u",x / 256,x & 255);
   }
   else
   {

      struct sockaddr_in6 sa;

      __memset(&sa, 0, sizeof(sa));

      sa.sin6_family = AF_INET6;

      sa.sin6_addr = ip;

      try
      {

         ::str::from(str, sa);

         return true;

      }
      catch (...)
      {

      }

      return false;

   }
   str = slask;
   return true;
}


i32 net::in6_addr_compare(in6_addr a,in6_addr b)
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

void net::ResolveLocal()
{

   char h[256];

   // get local hostname and translate into ip-address
   *h = 0;
   gethostname(h,255);
   {
      if(convert(m_ip, h))
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


const string & net::GetLocalHostname()
{
   if (!m_local_resolved)
   {
      ResolveLocal();
   }
   return m_host;
}


in_addr net::GetLocalIP()
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

string net::Sa2String(struct sockaddr *sa)
{
   if (sa -> sa_family == AF_INET6)
   {
      struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)sa;
      string tmp;
      convert(tmp, sa6 -> sin6_addr);
      return tmp + ":" + __str(ntohs(sa6 -> sin6_port));
   }
   if (sa -> sa_family == AF_INET)
   {
      struct sockaddr_in *sa4 = (struct sockaddr_in *)sa;
      string tmp;
      convert(tmp, sa4 -> sin_addr);
      return tmp + ":" + __str(ntohs(sa4 -> sin_port));
   }
   return "";
}


/*
::net::address net::CreateAddress(struct sockaddr *sa,socklen_t sa_len)
{
   retur
   switch (sa -> sa_family)
   {
   case AF_INET:
      if (sa_len == sizeof(struct sockaddr_in))
      {
         struct sockaddr_in *point = (struct sockaddr_in *)sa;
         ::sockets::address_pointer addr;
         addr(new ::sockets::ipv4_address(get_context_application(), *point));
         return addr;
      }
      break;
   case AF_INET6:
      if (sa_len == sizeof(struct sockaddr_in6))
      {
         struct sockaddr_in6 *point = (struct sockaddr_in6 *)sa;
         ::sockets::address_pointer addr;
         addr(new ::sockets::ipv6_address(get_context_application(), *point));
         return addr;
      }
      break;
   }
   return ::sockets::address_pointer();
}
*/

/*   bool net::convert(in_addr & sa, const string & host, i32 ai_flags)
   {

      __memset(&sa, 0, sizeof(sa));
      sa.sin_family = AF_INET;
#ifdef NO_GETADDRINFO
      if ((ai_flags & AI_NUMERICHOST) != 0 || isipv4(host))
      {
         ::str::parse pa((const char *)host, ".");
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
      if (net::isipv4(host))
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
         ai = vec[System.math().rnd() % vec.get_count()];
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


bool net::convert(struct in6_addr & sa, const string & host, i32 ai_flags)
{

   try
   {

      ::str::to(sa, host);

   }
   catch (const parsing_exception & e)
   {

      output_debug_string(e.m_pszMessage);

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
            if (strstr(s,".")) // x.x.x.x
            {
               Parse pa(s,".");
               char slask[100]; // u2ip temporary hgenstring conversion
               unsigned long b0 = static_cast<unsigned long>(pa.getvalue());
               unsigned long b1 = static_cast<unsigned long>(pa.getvalue());
               unsigned long b2 = static_cast<unsigned long>(pa.getvalue());
               unsigned long b3 = static_cast<unsigned long>(pa.getvalue());
               sprintf(slask,"%lx",b0 * 256 + b1);
               vec.push_back(slask);
               sprintf(slask,"%lx",b2 * 256 + b3);
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
            addr16[i++] = htons(net::hgenunsigned(bytepair));
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
   struct hostent *he = getipnodebyname( host, AF_INET6, 0, &errnum );
#else
   struct hostent *he = gethostbyname2( host, AF_INET6 );
#endif
   if (!he)
   {
      return false;
   }
   ::memcpy_dup(&sa.sin6_addr,he -> h_addr_list[0],he -> h_length);
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
   struct addrinfo *res;
   if (net::isipv6(host))
      hints.ai_flags |= AI_NUMERICHOST;
   i32 n = getaddrinfo(host, nullptr, &hints, &res);
   if (!n)
   {

      array <  sockaddr_in6 * > addra;
      struct addrinfo *ai = res;
      int iSaSize = sizeof(sockaddr_in6);
      //char ipstringbuffer[46];
      ::u32 ipbufferlength = 46;
      while (ai)
      {
         // The buffer length is changed by each call to WSAAddresstoString
         // So we need to set it for each iteration through the loop for safety
         if (ai -> ai_addrlen == iSaSize)
            addra.add((sockaddr_in6 *)ai->ai_addr);
         ai = ai -> ai_next;
      }
      if(addra.is_empty())
         return false;
      ::memcpy_dup(&sa, &::papaya::array::pick_random(addra)->sin6_addr, sizeof(sa));
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


bool net::reverse(string & number, const string & hostname)
{

   ::net::address address(hostname);

   number = address.get_display_number();

   return true;

}


bool net::reverse_schedule(reverse_cache_item * pitem)
{

   sync_lock sl(mutex());

   m_reversecacheaRequest.add(pitem);

   if (!m_pthreadReverse)
   {

      m_pthreadReverse = System.fork([this]()
         {

            ::set_thread_name("reverse_dns");

            single_lock sl(mutex());

            while (thread_get_run())
            {

               sl.lock();

               if (m_reversecacheaRequest.has_elements())
               {

                  auto pitem = m_reversecacheaRequest[0];

                  m_reversecacheaRequest.remove_at(0);

                  sl.unlock();

                  reverse_sync(pitem);

               }
               else
               {

                  sl.unlock();

                  if (!task_sleep(100_ms))
                  {

                     break;

                  }

               }

            }

            m_pthreadReverse.release();

         });

   }

   return true;

}


bool net::reverse(string & hostname, const ::net::address & address)
{

   single_lock sl(&m_mutexReverseCache, true);

   auto & pitem = m_mapReverseCache[address.get_display_number()];

   if (pitem && !pitem->m_bProcessing && !pitem->m_bTimeout && pitem->m_tickLastChecked.elapsed() < 3600_min)
   {

      hostname = pitem->m_strReverse;

      return pitem->m_bOk;

   }

   pitem = __new(reverse_cache_item);

   pitem->m_address = address;

   pitem->m_bTimeout = false;

   pitem->m_bProcessing = true;

   pitem->m_bOk = false;

   reverse_schedule(pitem);

   return true;

}


bool net::reverse_sync(reverse_cache_item * pitem)
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

   auto psa = &pitem->m_address.u.m_sa;

   auto len = pitem->m_address.m_iLen;

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

   single_lock sl(&m_mutexReverseCache, true);

   pitem->m_strReverse = host;
   //item.m_strService = serv;
   pitem->m_tickLastChecked.Now();

   //single_lock sl(&m_mutexCache, true);

   //m_mapReverseCache.set_at(strIpString, item);

   return true;
#endif // NO_GETADDRINFO

}



//string net::reverse_name(const ::net::address & address, bool bSynch, const ::duration& duration)
//{
//
//   string strHostname;
//
//   reverse((sockaddr *) &address.u.m_sa,sizeof(address.u.m_sa), strHostname, 0, bSynch, duration);
//
//   return strHostname;
//
//}


string net::reverse_name(const ::net::address & address)
{

   string hostname;

   reverse(hostname, address);

   return hostname;

}



bool net::u2service(const string & name, i32& service, i32 ai_flags)
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
   struct addrinfo *res;
   i32 n = getaddrinfo(nullptr, name, &hints, &res);
   if (!n)
   {
      service = res -> ai_protocol;
      freeaddrinfo(res);
      return true;
   }
   return false;
#endif // NO_GETADDRINFO

}


i32 net::service_port(const string & str, i32 flags)
{

   if(::str::is_simple_natural(str))
      return ::str::to_i32(str);

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

      i32 service = 0;

      if(!u2service(str, service, 0))
         return 0;

      return service;

   }

}


string  net::service_name(i32 iPort, i32 flags)
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

   string str;

   if(address.is_ipv4())
   {
      ::sockets::net::convert(str, address.u.m_addr.sin_addr);
   }
   else if(address.is_ipv6())
   {
      ::sockets::net::convert(str, address.u.m_addr6.sin6_addr);
   }

   return str;

}


string net::service_name(const ::net::address & address)
{

   return service_name(address.get_service_number());

}


net::dns_cache_item::dns_cache_item()
{

   xxf_zero(m_ipaddr);
   m_tickLastChecked = 0;
   m_bOk = false;
   m_bTimeout = true;
}


net::dns_cache_item::dns_cache_item(const dns_cache_item & item)
{

   this->operator = (item);

}


stream & net::dns_cache_item::write(stream & stream) const
{

   stream << m_ipaddr;
   stream << m_tickLastChecked;
   stream << m_bOk;
   stream << m_bTimeout;

   return stream;

}


stream & net::dns_cache_item::read(stream & stream)
{

   stream >> m_ipaddr;
   stream >> m_tickLastChecked;
   stream >> m_bOk;
   stream >> m_bTimeout;

   return stream;

}


net::dns_cache_item & net::dns_cache_item::operator = (const dns_cache_item & item)
{

   if(this==&item)
      return *this;

   ::memcpy_dup(&m_ipaddr,&item.m_ipaddr,sizeof(m_ipaddr));
   m_tickLastChecked = item.m_tickLastChecked;
   m_bOk = item.m_bOk;
   m_bTimeout = item.m_bTimeout;

   return *this;

}


net::reverse_cache_item::reverse_cache_item()
{

   //xxf_zero(m_ipaddr);
   m_tickLastChecked = 0;
   m_bOk = false;
   m_bTimeout = true;

}


net::reverse_cache_item::reverse_cache_item(const reverse_cache_item & item)
{

   this->operator = (item);

}


stream & net::reverse_cache_item::write(stream & stream) const
{

   stream << m_address;
   stream << m_strReverse;
   stream << m_tickLastChecked;
   stream << m_bOk;
   stream << m_bTimeout;
   stream << m_bProcessing;

   return stream;

}


stream & net::reverse_cache_item::read(stream & stream)
{

   stream >> m_address;
   stream >> m_strReverse;
   stream >> m_tickLastChecked;
   stream >> m_bOk;
   stream >> m_bTimeout;
   stream >> m_bProcessing;

   return stream;

}


net::reverse_cache_item & net::reverse_cache_item::operator = (const reverse_cache_item & item)
{

   if(this==&item)
      return *this;

   m_address = item.m_address;
   m_tickLastChecked = item.m_tickLastChecked;
   m_strReverse = item.m_strReverse;
   m_bOk = item.m_bOk;
   m_bTimeout = item.m_bTimeout;
   m_bProcessing = item.m_bProcessing;

   return *this;

}


} // namespace sockets





//namespace net
//{
//
//
//   i32 family_len(i32 family)
//   {
//
//      if(family == AF_INET)
//         return sizeof(sockaddr_in);
//      else if(family == AF_INET6)
//         return sizeof(sockaddr_in6);
//      else
//         return 0;
//
//   }
//
//
//} // namespace net
//
//
//
//
//
//
//
//
//





