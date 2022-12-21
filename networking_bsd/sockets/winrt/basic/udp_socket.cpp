#include "framework.h"
//#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   udp_socket::udp_socket(int ibufsz, bool ipv6, int retries) :
      ::object(h.get_app()),
      base_socket(h),
      socket(h)
      , m_ibuf(memory_new char[ibufsz])
      , m_ibufsz(ibufsz)
      , m_bind_ok(false)
      , m_port(0)
      , m_last_size_written(-1)
      , m_iConnectionRetryCount(retries)
      , m_b_read_ts(false)
   {
      //m_posdata = memory_new os_data();
      SetIpv6(ipv6);
   }


   udp_socket::~udp_socket()
   {
      close();
      //delete m_posdata;
      //delete[] m_ibuf;
   }


   int udp_socket::Bind(port_t port, int range)
   {

      m_datagramsocket = ref memory_new ::winrt::Windows::Networking::Sockets::DatagramSocket;
      //::sockets::socket::os_data data;
      //data.o = m_datagramsocket;
      //attach(data);
      create_socket();

      m_datagramsocket->MessageReceived +=
      ref memory_new ::winrt::Windows::Foundation::TypedEventHandler < ::winrt::Windows::Networking::Sockets::DatagramSocket ^, ::winrt::Windows::Networking::Sockets::DatagramSocketMessageReceivedEventArgs ^ >
      ([this](::winrt::Windows::Networking::Sockets::DatagramSocket ^ socket, ::winrt::Windows::Networking::Sockets::DatagramSocketMessageReceivedEventArgs ^ args)
      {

         Array < unsigned char, 1U > ^ ucha = ref memory_new Array < unsigned char, 1U >(args->GetDataReader()->UnconsumedBufferLength);

         args->GetDataReader()->ReadBytes(ucha);

         OnRawData((char *) ucha->Data, ucha->Length);

      });

      m_datagramsocket->BindServiceNameAsync(as_string(port))->Completed =
      ref memory_new ::winrt::Windows::Foundation::AsyncActionCompletedHandler
      ([this] (::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status)
      {

         if(status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
         {
            m_bind_ok = true;
            OnAccept();

         }

      });

      return 0;

   }


   int udp_socket::Bind(const ::scoped_string & scopedstrHost, port_t port, int range)
   {

      return Bind(::networking::address(pszHost, port), range);

   }


   int udp_socket::Bind(::networking::address * ad, int range)
   {

      //         attach(CreateSocket(ad.GetFamily(), SOCK_DGRAM, "udp"));

      m_datagramsocket = ref memory_new ::winrt::Windows::Networking::Sockets::DatagramSocket();

      //::sockets::socket::os_data data;
      //data.o = m_datagramsocket;
      //attach(data);

      create_socket();

      SetNonblocking(true);

      m_datagramsocket->BindEndpointAsync(ad.m_hostname, as_string(ad.get_service_number()))->Completed =
      ref memory_new ::winrt::Windows::Foundation::AsyncActionCompletedHandler
      ([this](::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status)
      {

         if(status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
         {
            m_bind_ok = true;
            OnAccept();

         }

      });

      return 0;

   }


   /** if you wish to use Send, first open a connection */
   /*   bool udp_socket::open(ipaddr_t l, port_t port)
   {
   ipv4_address ad(get_app(), l, port);
   return open(ad);
   }
   */

   bool udp_socket::open(const char * host, port_t port)
   {

      return open(::networking::address(host, port));

   }


   /*bool udp_socket::open(struct in6_addr& a, port_t port)
   {
   ipv6_address ad(get_app(), a, port);
   return open(ad);
   }
   */

   bool udp_socket::open(::networking::address & ad)
   {

      m_datagramsocket = ref memory_new ::winrt::Windows::Networking::Sockets::DatagramSocket();

      //::sockets::socket::os_data data;
      //data.o = m_datagramsocket;
      //attach(data);

      create_socket();

      SetNonblocking(true);

      m_datagramsocket->ConnectAsync(ad.m_hostname, as_string(ad.get_service_number()))->Completed =
      ref memory_new ::winrt::Windows::Foundation::AsyncActionCompletedHandler
      ([this](::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status)
      {

         if(status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
         {

            OnConnect();

         }

      });

      return true;

   }

   /*
   void udp_socket::CreateConnection()
   {
   if (IsIpv6())
   {
   if (GetSocket() == INVALID_SOCKET)
   {
   SOCKET s = CreateSocket(AF_INET6, SOCK_DGRAM, "udp");
   if (s == INVALID_SOCKET)
   {
   return;
   }
   SetNonblocking(true, s);
   attach(s);
   }
   return;
   }
   if (GetSocket() == INVALID_SOCKET)
   {
   SOCKET s = CreateSocket(AF_INET, SOCK_DGRAM, "udp");
   if (s == INVALID_SOCKET)
   {
   return;
   }
   SetNonblocking(true, s);
   attach(s);
   }
   }
   */

   /** send to specified address */
   /*   void udp_socket::SendToBuf(const string & h, port_t p, const char *data, int len, int flags)
   {

   ::networking::address ad(get_app(), h, p);

   SendToBuf(ad, data, len, flags);

   }
   */

   /** send to specified address */
   /*   void udp_socket::SendToBuf(ipaddr_t a, port_t p, const char *data, int len, int flags)
   {
   ipv4_address ad(get_app(), a, p);
   SendToBuf(ad, data, len, flags);
   }


   void udp_socket::SendToBuf(in6_addr a, port_t p, const char *data, int len, int flags)
   {
   ipv6_address ad(get_app(), a, p);
   SendToBuf(ad, data, len, flags);
   }
   */

   /*
   void udp_socket::SendToBuf(::networking::address& ad, const char *data, int len, int flags)
   {
   if (GetSocket() == INVALID_SOCKET)
   {
   attach(CreateSocket(ad.GetFamily(), SOCK_DGRAM, "udp"));
   }
   if (GetSocket() != INVALID_SOCKET)
   {
   SetNonblocking(true);
   if ((m_last_size_written = sendto(GetSocket(), data, len, flags, ad, ad)) == -1)
   {
   __error("sendto", Errno, bsd_socket_error(Errno));
   }
   }
   }
   */

   /*   void udp_socket::SendTo(const string & a, port_t p, const ::string & str, int flags)
   {
   SendToBuf(a, p, str, (int)str.get_length(), flags);
   }


   void udp_socket::SendTo(ipaddr_t a, port_t p, const ::string & str, int flags)
   {
   SendToBuf(a, p, str, (int)str.get_length(), flags);
   }


   void udp_socket::SendTo(in6_addr a, port_t p, const ::string & str, int flags)
   {
   SendToBuf(a, p, str, (int)str.get_length(), flags);
   }


   void udp_socket::SendTo(::networking::address& ad, const ::string & str, int flags)
   {
   SendToBuf(ad, str, (int)str.get_length(), flags);
   }
   */

   /** send to connected address */
   void udp_socket::SendBuf(const char *data, memsize len, int flags)
   {
      
      if (!IsConnected())
      {
         
         //__error("SendBuf", 0, "not connected");

         return;

      }

      ::winrt::Windows::Storage::Streams::DataWriter ^ writer = ref memory_new ::winrt::Windows::Storage::Streams::DataWriter(m_datagramsocket->OutputStream);

      writer->WriteBytes(ref memory_new Array < unsigned char, 1U >((unsigned char *) data, len));

      /*writer->FlushAsync()->Completed = ref memory_new ::winrt::Windows::Foundation::AsyncOperationCompletedHandler < bool >([this](::winrt::Windows::Foundation::IAsyncOperation<bool> asyncInfo, ::winrt::Windows::Foundation::AsyncStatus asyncStatus)
      {



      });*/

      /*      if ((m_last_size_written = send(GetSocket(), data, (int)len, flags)) == -1)
      {
      __error("send", Errno, bsd_socket_error(Errno));
      }*/

   }


   void udp_socket::Send(const ::string & str, int flags)
   {
      SendBuf(str, (int)str.get_length(), flags);
   }


#if defined(LINUX) || defined(MACOSX)
   int udp_socket::ReadTS(char *ioBuf, int inBufSize, struct sockaddr *from, socklen_t fromlen, struct timeval *ts)
   {
      struct msghdr msg;
      struct iovec vec[1];
      union
      {
         struct cmsghdr cm;
#ifdef MACOSX
#ifdef __DARWIN_UNIX03
#define ALIGNBYTES __DARWIN_ALIGNBYTES
#endif
#define myALIGN(p) (((unsigned int)(p) + ALIGNBYTES) &~ ALIGNBYTES)
#define myCMSG_SPACE(l) (myALIGN(sizeof(struct cmsghdr)) + myALIGN(l))
         char data[ myCMSG_SPACE(sizeof(struct timeval)) ];
#else
         char data[ CMSG_SPACE(sizeof(struct timeval)) ];
#endif
      } cmsg_un;
      struct cmsghdr *cmsg;
      struct timeval *tv;

      vec[0].iov_base = ioBuf;
      vec[0].iov_len = inBufSize;

      memory_set(&msg, 0, sizeof(msg));
      memory_set(from, 0, fromlen);
      memory_set(ioBuf, 0, inBufSize);
      memory_set(&cmsg_un, 0, sizeof(cmsg_un));

#ifdef WINDOWS
      msg.msg_name = (caddr_t)from;
#else
      msg.msg_name = from;
#endif
      msg.msg_namelen = fromlen;
      msg.msg_iov = vec;
      msg.msg_iovlen = 1;
      msg.msg_control = cmsg_un.data;
      msg.msg_controllen = sizeof(cmsg_un.data);
      msg.msg_flags = 0;

      // Original version - for object only
      //int n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);

      int n = recvmsg(GetSocket(), &msg, MSG_DONTWAIT);

      // now ioBuf will contain the data, as if we used recvfrom

      // Now get the time
      if(n != -1 && msg.msg_controllen >= sizeof(struct cmsghdr) && !(msg.msg_flags & MSG_CTRUNC))
      {
         tv = 0;
         for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != nullptr; cmsg = CMSG_NXTHDR(&msg, cmsg))
         {
            if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_TIMESTAMP)
            {
               tv = (struct timeval *)CMSG_DATA(cmsg);
            }
         }
         if (tv)
         {
            ::memcpy_dup(ts, tv, sizeof(struct timeval));
         }
      }
      // The address is in network order, but that's OK right now
      return n;
   }
#endif


   void udp_socket::OnRead()
   {
      /*if (IsIpv6())
      {
      struct sockaddr_in6 sa;
      socklen_t sa_len = sizeof(sa);
      if (m_b_read_ts)
      {
      struct timeval ts;
      ::apexacmesystem()->get_time(&ts);
      #if !defined(LINUX) && !defined(MACOSX)
      int n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      #else
      int n = ReadTS(m_ibuf, m_ibufsz, (struct sockaddr *)&sa, sa_len, &ts);
      #endif
      if (n > 0)
      {
      this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len, &ts);
      }
      else
      if (n == -1)
      {
      #ifdef _WIN32
      if (Errno != WSAEWOULDBLOCK)
      #else
      if (Errno != EWOULDBLOCK)
      #endif
      __error("recvfrom", Errno, bsd_socket_error(Errno));
      }
      return;
      }
      int n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      int q = m_iConnectionRetryCount; // receive maximum 10 at one cycle
      while (n > 0)
      {
      if (sa_len != sizeof(sa))
      {
      WARNING("recvfrom", 0, "unexpected address struct size_i32");
      }
      this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len);
      if (!q--)
      break;
      //
      n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      }
      if (n == -1)
      {
      #ifdef _WIN32
      if (Errno != WSAEWOULDBLOCK)
      #else
      if (Errno != EWOULDBLOCK)
      #endif
      __error("recvfrom", Errno, bsd_socket_error(Errno));
      }
      return;
      }
      struct sockaddr_in sa;
      socklen_t sa_len = sizeof(sa);
      if (m_b_read_ts)
      {
      struct timeval ts;
      ::apexacmesystem()->get_time(&ts);
      #if !defined(LINUX) && !defined(MACOSX)
      int n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      #else
      int n = ReadTS(m_ibuf, m_ibufsz, (struct sockaddr *)&sa, sa_len, &ts);
      #endif
      if (n > 0)
      {
      this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len, &ts);
      }
      else
      if (n == -1)
      {
      #ifdef _WIN32
      if (Errno != WSAEWOULDBLOCK)
      #else
      if (Errno != EWOULDBLOCK)
      #endif
      __error("recvfrom", Errno, bsd_socket_error(Errno));
      }
      return;
      }
      int n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      int q = m_iConnectionRetryCount;
      while (n > 0)
      {
      if (sa_len != sizeof(sa))
      {
      WARNING("recvfrom", 0, "unexpected address struct size_i32");
      }
      this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len);
      if (!q--)
      break;
      //
      n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      }
      if (n == -1)
      {
      #ifdef _WIN32
      if (Errno != WSAEWOULDBLOCK)
      #else
      if (Errno != EWOULDBLOCK)
      #endif
      __error("recvfrom", Errno, bsd_socket_error(Errno));
      }
      */
      /*::winrt::Windows::Storage::Streams::DataReader ^ reader = ref memory_new ::winrt::Windows::Storage::Streams::DataReader(m_datagramsocket->OutputStream);
      //int n = reader->UnconsumedBufferLength;
      Array < unsigned char, 1U > ^ ucha = nullptr;
      reader->ReadBytes(ucha);
      if(ucha != nullptr)
      {
      OnRawData(ucha->Data, ucha->Length);
      }*/

   }


   void udp_socket::SetBroadcast(bool b)
   {
      throw ::not_implemented();
      /*
      int one = 1;
      int zero = 0;

      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (b)
      {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *) &one, sizeof(one)) == -1)
      {
      WARNING("SetBroadcast", Errno, bsd_socket_error(Errno));
      }
      }
      else
      {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *) &zero, sizeof(zero)) == -1)
      {
      WARNING("SetBroadcast", Errno, bsd_socket_error(Errno));
      }
      }*/
   }


   bool udp_socket::IsBroadcast()
   {
      throw ::not_implemented();
      /*int is_broadcast = 0;
      socklen_t size;

      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *)&is_broadcast, &size) == -1)
      {
      WARNING("IsBroadcast", Errno, bsd_socket_error(Errno));
      }
      return is_broadcast != 0;*/
   }


   void udp_socket::SetMulticastTTL(int ttl)
   {
      throw ::not_implemented();
      /*if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (setsockopt(GetSocket(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(int)) == -1)
      {
      WARNING("SetMulticastTTL", Errno, bsd_socket_error(Errno));
      }*/
   }


   int udp_socket::GetMulticastTTL()
   {
      throw ::not_implemented();
      /*int ttl = 0;
      socklen_t size = sizeof(int);

      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (getsockopt(GetSocket(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, &size) == -1)
      {
      WARNING("GetMulticastTTL", Errno, bsd_socket_error(Errno));
      }
      return ttl;*/
   }


   void udp_socket::SetMulticastLoop(bool x)
   {
      throw ::not_implemented();
      /*if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (IsIpv6())
      {
      int val = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (char *)&val, sizeof(int)) == -1)
      {
      WARNING("SetMulticastLoop", Errno, bsd_socket_error(Errno));
      }
      return;
      }
      int val = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&val, sizeof(int)) == -1)
      {
      WARNING("SetMulticastLoop", Errno, bsd_socket_error(Errno));
      }*/
   }


   bool udp_socket::IsMulticastLoop()
   {
      throw ::not_implemented();
      /*if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (IsIpv6())
      {
      int is_loop = 0;
      socklen_t size = sizeof(int);
      if (getsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
      {
      WARNING("IsMulticastLoop", Errno, bsd_socket_error(Errno));
      }
      return is_loop ? true : false;
      }
      int is_loop = 0;
      socklen_t size = sizeof(int);
      if (getsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
      {
      WARNING("IsMulticastLoop", Errno, bsd_socket_error(Errno));
      }
      return is_loop ? true : false;*/
   }


   void udp_socket::AddMulticastMembership(const string & group, const string & local_if, int if_index)
   {
      throw ::not_implemented();
      /*
      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (IsIpv6())
      {
      struct ipv6_mreq x;
      struct in6_addr addr;
      if (psession->sockets().net().u2ip( group, addr ))
      {
      x.ipv6mr_multiaddr = addr;
      x.ipv6mr_interface = if_index;
      if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, (char *)&x, sizeof(struct ipv6_mreq)) == -1)
      {
      WARNING("AddMulticastMembership", Errno, bsd_socket_error(Errno));
      }
      }
      return;
      }
      struct ip_mreq x; // ip_mreqn
      ipaddr_t addr;
      if (psession->sockets().net().u2ip( group, addr ))
      {
      ::memcpy_dup(&x.imr_multiaddr.s_addr, &addr, sizeof(addr));
      psession->sockets().net().u2ip( local_if, addr);
      ::memcpy_dup(&x.imr_interface.s_addr, &addr, sizeof(addr));
      //      x.imr_ifindex = if_index;
      if (setsockopt(GetSocket(), SOL_IP, IP_ADD_MEMBERSHIP, (char *)&x, sizeof(struct ip_mreq)) == -1)
      {
      WARNING("AddMulticastMembership", Errno, bsd_socket_error(Errno));
      }
      }*/
   }


   void udp_socket::DropMulticastMembership(const string & group, const string & local_if, int if_index)
   {
      throw ::not_implemented();
      /*
      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (IsIpv6())
      {
      struct ipv6_mreq x;
      struct in6_addr addr;
      if (psession->sockets().net().u2ip( group, addr ))
      {
      x.ipv6mr_multiaddr = addr;
      x.ipv6mr_interface = if_index;
      if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_DROP_MEMBERSHIP, (char *)&x, sizeof(struct ipv6_mreq)) == -1)
      {
      WARNING("DropMulticastMembership", Errno, bsd_socket_error(Errno));
      }
      }
      return;
      }
      struct ip_mreq x; // ip_mreqn
      ipaddr_t addr;
      if (psession->sockets().net().u2ip( group, addr ))
      {
      ::memcpy_dup(&x.imr_multiaddr.s_addr, &addr, sizeof(addr));
      psession->sockets().net().u2ip( local_if, addr);
      ::memcpy_dup(&x.imr_interface.s_addr, &addr, sizeof(addr));
      //      x.imr_ifindex = if_index;
      if (setsockopt(GetSocket(), SOL_IP, IP_DROP_MEMBERSHIP, (char *)&x, sizeof(struct ip_mreq)) == -1)
      {
      WARNING("DropMulticastMembership", Errno, bsd_socket_error(Errno));
      }
      }*/
   }


   void udp_socket::SetMulticastHops(int hops)
   {
      throw ::not_implemented();
      /*if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (!IsIpv6())
      {
      __error("SetMulticastHops", 0, "Ipv6 only");
      return;
      }
      if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, sizeof(int)) == -1)
      {
      WARNING("SetMulticastHops", Errno, bsd_socket_error(Errno));
      }*/
   }


   int udp_socket::GetMulticastHops()
   {
      throw ::not_implemented();
      /*
      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (!IsIpv6())
      {
      __error("SetMulticastHops", 0, "Ipv6 only");
      return -1;
      }
      int hops = 0;
      socklen_t size = sizeof(int);
      if (getsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, &size) == -1)
      {
      WARNING("GetMulticastHops", Errno, bsd_socket_error(Errno));
      }
      return hops;*/
   }


   bool udp_socket::IsBound()
   {
      return m_bind_ok;
   }


   void udp_socket::OnRawData(char * buf, memsize len, struct sockaddr * sa, socklen_t sa_len)
   {
      __UNREFERENCED_PARAMETER(buf);
      __UNREFERENCED_PARAMETER(len);
      __UNREFERENCED_PARAMETER(sa);
      __UNREFERENCED_PARAMETER(sa_len);
   }


   void udp_socket::OnRawData(char * buf, memsize len, struct sockaddr * sa, socklen_t sa_len, struct timeval * ts)
   {
      __UNREFERENCED_PARAMETER(buf);
      __UNREFERENCED_PARAMETER(len);
      __UNREFERENCED_PARAMETER(sa);
      __UNREFERENCED_PARAMETER(sa_len);
      __UNREFERENCED_PARAMETER(ts);
   }


   port_t udp_socket::GetPort()
   {
      return m_port;
   }


   int udp_socket::GetLastSizeWritten()
   {
      return m_last_size_written;
   }


   void udp_socket::SetTimestamp(bool x)
   {
      m_b_read_ts = x;
   }


   port_t udp_socket::GetRemotePort()
   {

      return ::apexacmesystem()->sockets().net().service_port(m_datagramsocket->Information->RemotePort);

   }


   ::networking::address udp_socket::GetRemoteAddress()
   {

      return ::networking::address(get_app(), m_datagramsocket->Information->RemoteAddress->CanonicalName, m_datagramsocket->Information->RemotePort);

   }


   port_t udp_socket::GetLocalPort()
   {

      return ::apexacmesystem()->sockets().net().service_port(m_datagramsocket->Information->LocalPort);

   }


   ::networking::address udp_socket::GetLocalAddress()
   {

      return ::networking::address(get_app(), m_datagramsocket->Information->LocalAddress->CanonicalName, m_datagramsocket->Information->LocalPort);

   }


} // namespace sockets



