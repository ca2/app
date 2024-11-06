#include "framework.h"
#include "udp_socket.h"



namespace sockets
{


   udp_socket::udp_socket(int ibufsz, bool ipv6, int retries) :
      //::object(&h)
      //,
      //base_socket(h)
      //,socket(h)
      m_ibuf(__raw_new char[ibufsz])
      , m_ibufsz(ibufsz)
      , m_bind_ok(false)
      , m_port(0)
      , m_last_size_written(-1)
      , m_iConnectionRetryCount(retries)
      , m_b_read_ts(false)
   {
      m_iWriteFlags = 0;
      SetIpv6(ipv6);
   }



   udp_socket::~udp_socket()
   {
      close();
      delete[] m_ibuf;
   }


   //int udp_socket::Bind(::networking::port_t &port, int range)
   //{
   //   if (IsIpv6())
   //   {
   //      ::networking::address ad(AF_INET6, port);
   //      return Bind((in6_addr) ad.u.m_addr6.sin6_addr, ad.u.m_addr6.sin6_port, range);
   //   }
   //   ::networking::address ad(AF_INET, port);
   //   return Bind((in_addr)  ad.u.m_addr.sin_addr, ad.u.m_addr.sin_port, range);
   //}


   //int udp_socket::Bind(const string & intf, ::networking::port_t &port, int range)
   //{

   //   ::networking::address ad(intf, port);

   //   if (ad.is_valid())
   //   {
   //      if(ad.is_ipv6())
   //      {
   //         return Bind((in6_addr) ad.u.m_addr6.sin6_addr, ad.u.m_addr6.sin6_port, range);
   //      }
   //      else if(ad.is_ipv4())
   //      {
   //         return Bind((in_addr)  ad.u.m_addr.sin_addr, ad.u.m_addr.sin_port, range);
   //      }

   //   }

   //   SetCloseAndDelete();

   //   return -1;

   //}


   //int udp_socket::Bind(in_addr a, ::networking::port_t &port, int range)
   //{
   //   ::networking::address ad(a, port);
   //   return Bind(ad, range);
   //}


   //int udp_socket::Bind(in6_addr a, ::networking::port_t &port, int range)
   //{
   //   ::networking::address ad(a, port);
   //   return Bind(ad, range);
   //}


   int udp_socket::Bind(::networking::address & ad, int range)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   attach(CreateSocket(ad.get_family(), SOCK_DGRAM, "udp"));
      //}
      //if (get_socket_id() != INVALID_SOCKET)
      //{
      //   SetNonblocking(true);
      //   int n = bind(get_socket_id(), ad.sa(), ad.sa_len());
      //   int tries = range;
      //   while (n == -1 && tries--)
      //   {
      //      ad.set_service_number(ad.get_service_number() + 1);
      //      n = bind(get_socket_id(), ad.sa(), ad.sa_len());
      //   }
      //   if (n == -1)
      //   {

      //      fatal() <<"bind" << Errno << ", " << bsd_socket_error(Errno);

      //      SetCloseAndDelete();
      //      throw ::exception(error_socket, "bind() failed for udp_socket, port:range: " + as_string(ad.get_service_number()) + ":" + as_string(range));
      //      return -1;
      //   }
      //   m_bind_ok = true;
      //   m_port = ad.get_service_number();
      //   return 0;
      //}
      return -1;
   }


   ///** if you wish to use Send, first open a connection */
   //bool udp_socket::open(in_addr l, ::networking::port_t port)
   //{
   //   ::networking::address ad(l, port);
   //   return open(ad);
   //}


   //bool udp_socket::open(const string & host, ::networking::port_t port)
   //{
   //   ::networking::address ad(host, port);
   //   if(!ad.is_valid())
   //      return false;
   //   return open(ad);
   //}


   //bool udp_socket::open(struct in6_addr& a, ::networking::port_t port)
   //{
   //   ::networking::address ad(a, port);
   //   return open(ad);
   //}


   bool udp_socket::open(::networking::address * ad)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   attach(CreateSocket(ad.get_family(), SOCK_DGRAM, "udp"));
      //}
      //if (get_socket_id() != INVALID_SOCKET)
      //{
      //   SetNonblocking(true);
      //   if (connect(get_socket_id(), ad.sa(), ad.sa_len()) == -1)
      //   {

      //      fatal() <<"connect" << Errno << ", " << bsd_socket_error(Errno);

      //      SetCloseAndDelete();
      //      return false;
      //   }
      //   SetConnected();
      //   return true;
      //}
      return false;
   }


   void udp_socket::CreateConnection()
   {
      if (IsIpv6())
      {
         //if (get_socket_id() == INVALID_SOCKET)
         //{
         //   socket_id s = CreateSocket(AF_INET6, SOCK_DGRAM, "udp");
         //   if (s == INVALID_SOCKET)
         //   {
         //      return;
         //   }
         //   SetNonblocking(true, s);
         //   attach(s);
         //}
         return;
      }
      //if (get_socket_id() == INVALID_SOCKET)
      {
         //socket_id s = CreateSocket(AF_INET, SOCK_DGRAM, "udp");
         //if (s == INVALID_SOCKET)
         //{
         //   return;
         //}
         //SetNonblocking(true, s);
         //attach(s);
      }
   }


   ///** send to specified address */
   //void udp_socket::SendToBuf(const string & h, ::networking::port_t p, const char *data, int len, int flags)
   //{
   //   SendToBuf(::networking::address(h, p), data, len, flags);
   //}


   ///** send to specified address */
   //void udp_socket::SendToBuf(const in_addr & a, ::networking::port_t p, const char *data, int len, int flags)
   //{
   //   SendToBuf(::networking::address(a, p), data, len, flags);
   //}


   //void udp_socket::SendToBuf(const in6_addr & a, ::networking::port_t p, const char *data, int len, int flags)
   //{
   //   SendToBuf(::networking::address(a, p), data, len, flags);
   //}


   void udp_socket::SendToBuf(::networking::address * ad, const char *data, int len, int flags)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   attach(CreateSocket(ad.get_family(), SOCK_DGRAM, "udp"));
      //}
      //if (get_socket_id() != INVALID_SOCKET)
      //{
      //   SetNonblocking(true);
      //   if ((m_last_size_written = sendto(get_socket_id(), data, len, flags, ad.sa(), (int) ad.sa_len())) == -1)
      //   {



      //      error() <<"sendto" << Errno << ", " << bsd_socket_error(Errno);



      //   }

      //}

   }


   //void udp_socket::SendTo(const string & a, ::networking::port_t port, const ::string & str, int flags)
   //{
   //   
   //   SendToBuf(a, port, str, (int)str.length(), flags);

   //}


   //void udp_socket::SendTo(in_addr a, ::networking::port_t port, const ::string & str, int flags)
   //{

   //   SendToBuf(a, port, str, (int)str.length(), flags);

   //}


   //void udp_socket::SendTo(in6_addr a, ::networking::port_t port, const ::string & str, int flags)
   //{
   //   
   //   SendToBuf(a, port, str, (int)str.length(), flags);

   //}


   void udp_socket::SendTo(::networking::address * ad, const ::string & str, int flags)
   {

      SendToBuf(ad, str, (int)str.length(), flags);

   }


   /** send to connected address */
   void udp_socket::write(const void *data, memsize len)
   {

      if (!IsConnected())
      {



         error() <<"write 0 not connected";



         return;

      }

      //if ((m_last_size_written = ::send(get_socket_id(), (const char *) data, (int)len, m_iWriteFlags)) == -1)
      //{



      //   error() <<"write" << Errno << ", " << bsd_socket_error(Errno);



      //}

   }



#if defined(LINUX) || defined(MACOSX)
   int udp_socket::ReadTS(char *ioBuf, int inBufSize, struct sockaddr *from, int fromlen, struct timeval *ts)
   {
//      struct msghdr msg;
//      struct iovec vec[1];
//      union
//      {
//         struct cmsghdr cm;
//#ifdef MACOSX
//#ifdef __DARWIN_UNIX03
//#define ALIGNBYTES __DARWIN_ALIGNBYTES
//#endif
//#define myALIGN(p) (((unsigned int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
//#define myCMSG_SPACE(l) (myALIGN(sizeof(struct cmsghdr)) + myALIGN(l))
//         char data[ myCMSG_SPACE(sizeof(struct timeval)) ];
//#else
//         char data[ CMSG_SPACE(sizeof(struct timeval)) ];
//#endif
//      } cmsg_un;
//      struct cmsghdr *cmsg;
//      struct timeval *tv;
//
//      vec[0].iov_base = ioBuf;
//      vec[0].iov_len = inBufSize;
//
//      memory_set(&msg, 0, sizeof(msg));
//      memory_set(from, 0, fromlen);
//      memory_set(ioBuf, 0, inBufSize);
//      memory_set(&cmsg_un, 0, sizeof(cmsg_un));
//
//#ifdef WINDOWS
//      msg.msg_name = (caddr_t)from;
//#else
//      msg.msg_name = from;
//#endif
//      msg.msg_namelen = fromlen;
//      msg.msg_iov = vec;
//      msg.msg_iovlen = 1;
//      msg.msg_control = cmsg_un.data;
//      msg.msg_controllen = sizeof(cmsg_un.data);
//      msg.msg_flags = 0;
//
//      // Original version - for object only
//      //int n = recvfrom(get_socket_id(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
//
//      int n = recvmsg(get_socket_id(), &msg, MSG_DONTWAIT);
//
//      // now ioBuf will contain the data, as if we used recvfrom
//
//      // Now get the time
//      if(n != -1 && msg.msg_controllen >= sizeof(struct cmsghdr) && !(msg.msg_flags & MSG_CTRUNC))
//      {
//         tv = 0;
//         for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != nullptr; cmsg = CMSG_NXTHDR(&msg, cmsg))
//         {
//            if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_TIMESTAMP)
//            {
//               tv = (struct timeval *)CMSG_DATA(cmsg);
//            }
//         }
//         if (tv)
//         {
//            ::memory_copy(ts, tv, sizeof(struct timeval));
//         }
//      }
//      // The address is in network order, but that's OK right now
//      return n;
return -1;
   }
#endif


   void udp_socket::OnRead()
   {
      if (IsIpv6())
      {
//         struct sockaddr_in6 sa;
//         socklen_t sa_len = sizeof(sa);
//         if (m_b_read_ts)
//         {
//            
//            ::time time;
//
//            time.Now();
//
//            struct timeval timeval;
//
//            timeval.tv_sec = (long) time.m_iSecond;
//
//            timeval.tv_usec = (int) (time.m_iNanosecond / 1'000);
//
//#if !defined(LINUX) && !defined(MACOSX)
//            memsize n = recvfrom(get_socket_id(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
//#else
//            int n = ReadTS(m_ibuf, m_ibufsz, (struct sockaddr *)&sa, sa_len, &timeval);
//#endif
//            if (n > 0)
//            {
//               
//               this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len, &timeval);
//
//            }
//            else if (n == -1)
//            {
//#ifdef _WIN32
//               if (Errno != WSAEWOULDBLOCK)
//               {
//#else
//               if (Errno != EWOULDBLOCK)
//               {
//
//#endif
//
//
//
//                  error() <<"recvfrom" << Errno << ", " << bsd_socket_error(Errno);
//
//
//               }
//
//            }
//
//            return;
//
//         }
//
//         memsize n = recvfrom(get_socket_id(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
//         int q = m_iConnectionRetryCount; // receive maximum 10 at one cycle
//         while (n > 0)
//         {
//            if (sa_len != sizeof(sa))
//            {
//
//               warning() <<"recvfrom 0 unexpected address struct int_size";
//
//            }
//            this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len);
//            if (!q--)
//               break;
//            //
//            n = recvfrom(get_socket_id(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
//         }
//         if (n == -1)
//         {
//#ifdef _WIN32
//            if (Errno != WSAEWOULDBLOCK)
//            {
//#else
//            if (Errno != EWOULDBLOCK)
//            {
//#endif
//
//               error() <<"recvfrom " << Errno << ", " << bsd_socket_error(Errno);
//
//            }
//         }
         return;
      }
//      struct sockaddr_in sa;
//      socklen_t sa_len = sizeof(sa);
//      if (m_b_read_ts)
//      {
//         
//         ::time time;
//
//         time.Now();
//
//         timeval timeval;
//
//         timeval.tv_sec = (long) time.m_iSecond;
//
//         timeval.tv_usec = (int) (time.m_iNanosecond / 1'000);
//
//#if !defined(LINUX) && !defined(MACOSX)
//
//         memsize n = recvfrom(get_socket_id(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
//
//#else
//
//         int n = ReadTS(m_ibuf, m_ibufsz, (struct sockaddr *)&sa, sa_len, &timeval);
//
//#endif
//
//         if (n > 0)
//         {
//            
//            this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len, &timeval);
//
//         }
//         else if (n == -1)
//         {
//#ifdef _WIN32
//            if (Errno != WSAEWOULDBLOCK)
//            {
//#else
//            if (Errno != EWOULDBLOCK)
//            {
//#endif
//
//
//               error() <<"recvfrom" << Errno << ", " << bsd_socket_error(Errno);
//
//            }
//         }
//         return;
//      }
//      memsize n = recvfrom(get_socket_id(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
//      int q = m_iConnectionRetryCount;
//      while (n > 0)
//      {
//         if (sa_len != sizeof(sa))
//         {
//
//            warning() <<"recvfrom 0 unexpected address struct int_size";
//
//         }
//         this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len);
//         if (!q--)
//            break;
//         //
//         n = recvfrom(get_socket_id(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
//      }
//      if (n == -1)
//      {
//#ifdef _WIN32
//         if (Errno != WSAEWOULDBLOCK)
//         {
//#else
//         if (Errno != EWOULDBLOCK)
//         {
//#endif
//
//            error() <<"recvfrom" << Errno << ", " << bsd_socket_error(Errno);
//
//         }
//      }
   }


   void udp_socket::SetMulticastTTL(int ttl)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (setsockopt(get_socket_id(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(int)) == -1)
      //{

      //   warning() <<"SetMulticastTTL" << Errno << ", " << bsd_socket_error(Errno);

      //}
   }


   int udp_socket::GetMulticastTTL()
   {
      int ttl = 0;
      //socklen_t size = sizeof(int);

      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (getsockopt(get_socket_id(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, &size) == -1)
      //{

      //   warning() <<"GetMulticastTTL" << Errno << ", " << bsd_socket_error(Errno);

      //}
      return ttl;
   }


   bool udp_socket::SetMulticastLoop(bool x)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (IsIpv6())
      //{
      //   int val = x ? 1 : 0;
      //   if (setsockopt(get_socket_id(), IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (char *)&val, sizeof(int)) == -1)
      //   {

      //      warning() <<"SetMulticastLoop" << Errno << ", " << bsd_socket_error(Errno);

      //   }
      //   return;
      //}
      //int val = x ? 1 : 0;
      //if (setsockopt(get_socket_id(), SOL_IP, IP_MULTICAST_LOOP, (char *)&val, sizeof(int)) == -1)
      //{

      //   warning() <<"SetMulticastLoop" << Errno << ", " << bsd_socket_error(Errno);

      //}
      return false;
   }


   bool udp_socket::IsMulticastLoop()
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (IsIpv6())
      //{
      //   int is_loop = 0;
      //   socklen_t size = sizeof(int);
      //   if (getsockopt(get_socket_id(), IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
      //   {

      //      warning() <<"IsMulticastLoop" << Errno << ", " << bsd_socket_error(Errno);

      //   }
      //   return is_loop ? true : false;
      //}
      int is_loop = 0;
      //socklen_t size = sizeof(int);
      //if (getsockopt(get_socket_id(), SOL_IP, IP_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
      //{

      //   warning() <<"IsMulticastLoop" << Errno << ", " << bsd_socket_error(Errno);

      //}
      return is_loop ? true : false;
   }


   void udp_socket::AddMulticastMembership(const string & group, const string & local_if, int if_index)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (IsIpv6())
      //{
      //   struct ipv6_mreq x;
      //   struct in6_addr addr;

      //   auto paddressdepartment = ::networking::address_department();

      //   if (paddressdepartment->convert( addr, group ))
      //   {
      //      x.ipv6mr_multiaddr = addr;
      //      x.ipv6mr_interface = if_index;
      //      if (setsockopt(get_socket_id(), IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, (char *)&x, sizeof(struct ipv6_mreq)) == -1)
      //      {

      //         warning() <<"AddMulticastMembership" << Errno << ", " << bsd_socket_error(Errno);

      //      }
      //   }
      //   return;
      //}
      //struct ip_mreq x; // ip_mreqn
      //in_addr addr;

      //auto paddressdepartment = ::networking::address_department();

      //if (paddressdepartment->convert(addr,  group ))
      //{
      //   ::memory_copy(&x.imr_multiaddr.s_addr, &addr, sizeof(addr));

      //   auto psystem = system();

      //   paddressdepartment->convert(addr,  local_if);

      //   ::memory_copy(&x.imr_interface.s_addr, &addr, sizeof(addr));
      //   //      x.imr_ifindex = if_index;
      //   if (setsockopt(get_socket_id(), SOL_IP, IP_ADD_MEMBERSHIP, (char *)&x, sizeof(struct ip_mreq)) == -1)
      //   {

      //      warning() <<"AddMulticastMembership " << Errno << " , " << bsd_socket_error(Errno);

      //   }
      //}
   }


   void udp_socket::DropMulticastMembership(const string & group, const string & local_if, int if_index)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (IsIpv6())
      //{
      //   struct ipv6_mreq x;
      //   struct in6_addr addr;

      //   auto paddressdepartment = ::networking::address_department();

      //   if (paddressdepartment->convert(addr, group))
      //   {
      //      x.ipv6mr_multiaddr = addr;
      //      x.ipv6mr_interface = if_index;
      //      if (setsockopt(get_socket_id(), IPPROTO_IPV6, IPV6_DROP_MEMBERSHIP, (char *)&x, sizeof(struct ipv6_mreq)) == -1)
      //      {

      //         warning() <<"DropMulticastMembership " << Errno << " , " << bsd_socket_error(Errno);

      //      }
      //   }
      //   return;
      //}
      //struct ip_mreq x; // ip_mreqn
      //in_addr addr;

      //auto paddressdepartment = ::networking::address_department();

      //if (paddressdepartment->convert(addr, group))
      //{
      //   ::memory_copy(&x.imr_multiaddr.s_addr, &addr, sizeof(addr));

      //   paddressdepartment->convert(addr, local_if);
      //   ::memory_copy(&x.imr_interface.s_addr, &addr, sizeof(addr));
      //   //      x.imr_ifindex = if_index;
      //   if (setsockopt(get_socket_id(), SOL_IP, IP_DROP_MEMBERSHIP, (char *)&x, sizeof(struct ip_mreq)) == -1)
      //   {

      //      warning() <<"DropMulticastMembership " << Errno << ", " << bsd_socket_error(Errno);

      //   }
      //}
   }


   void udp_socket::SetMulticastHops(int hops)
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (!IsIpv6())
      //{

      //   error() <<"SetMulticastHops 0 Ipv6 only";

      //   return;
      //}
      //if (setsockopt(get_socket_id(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, sizeof(int)) == -1)
      //{

      //   warning() <<"SetMulticastHops" << Errno << ", " << bsd_socket_error(Errno);

      //}
   }


   int udp_socket::GetMulticastHops()
   {
      //if (get_socket_id() == INVALID_SOCKET)
      //{
      //   CreateConnection();
      //}
      //if (!IsIpv6())
      //{

      //   error() <<"SetMulticastHops 0 Ipv6 only";

      //   return -1;
      //}
      int hops = 0;
      //socklen_t size = sizeof(int);
      //if (getsockopt(get_socket_id(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, &size) == -1)
      //{

      //   warning() <<"GetMulticastHops" << Errno << ", " << bsd_socket_error(Errno);

      //}
      return hops;
   }


   bool udp_socket::IsBound()
   {
      return m_bind_ok;
   }


   //void udp_socket::OnRawData(char * buf, memsize len, struct sockaddr * sa, socklen_t sa_len)
   //{
   //   __UNREFERENCED_PARAMETER(buf);
   //   __UNREFERENCED_PARAMETER(len);
   //   __UNREFERENCED_PARAMETER(sa);
   //   __UNREFERENCED_PARAMETER(sa_len);
   //}


   //void udp_socket::OnRawData(char * buf, memsize len, struct sockaddr * sa, socklen_t sa_len, struct timeval * ts)
   //{
   //   __UNREFERENCED_PARAMETER(buf);
   //   __UNREFERENCED_PARAMETER(len);
   //   __UNREFERENCED_PARAMETER(sa);
   //   __UNREFERENCED_PARAMETER(sa_len);
   //   __UNREFERENCED_PARAMETER(ts);
   //}


   //::networking::port_t udp_socket::GetPort()
   //{
   //   return m_port;
   //}


   memsize udp_socket::GetLastSizeWritten()
   {
      return m_last_size_written;
   }


   void udp_socket::SetTimestamp(bool x)
   {
      m_b_read_ts = x;
   }


}




