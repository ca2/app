#include "framework.h"
#include "apex/net/sockets/_sockets.h"


namespace sockets
{


   udp_socket::udp_socket(int ibufsz, bool ipv6, int retries) :
      ::object(h.get_application()),
      base_socket(h),
      socket(h)
      , m_ibuf(new char[ibufsz])
      , m_ibufsz(ibufsz)
      , m_bind_ok(false)
      , m_port(0)
      , m_last_size_written(-1)
      , m_retries(retries)
      , m_b_read_ts(false)
   {
      //m_posdata = new os_data();
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

      m_datagramsocket = ref new ::Windows::Networking::Sockets::DatagramSocket;
      //::sockets::socket::os_data data;
      //data.o = m_datagramsocket;
      //attach(data);
      create_socket();

      m_datagramsocket->MessageReceived +=
      ref new ::Windows::Foundation::TypedEventHandler < ::Windows::Networking::Sockets::DatagramSocket ^, ::Windows::Networking::Sockets::DatagramSocketMessageReceivedEventArgs ^ >
      ([this](Windows::Networking::Sockets::DatagramSocket ^ socket, ::Windows::Networking::Sockets::DatagramSocketMessageReceivedEventArgs ^ args)
      {

         Array < unsigned char, 1U > ^ ucha = ref new Array < unsigned char, 1U >(args->GetDataReader()->UnconsumedBufferLength);

         args->GetDataReader()->ReadBytes(ucha);

         OnRawData((char *) ucha->Data, ucha->Length);

      });

      m_datagramsocket->BindServiceNameAsync(__str(port))->Completed =
      ref new ::Windows::Foundation::AsyncActionCompletedHandler
      ([this] (::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
      {

         if(status == ::Windows::Foundation::AsyncStatus::Completed)
         {
            m_bind_ok = true;
            OnAccept();

         }

      });

      return 0;

   }


   int udp_socket::Bind(const char * pszHost, port_t port, int range)
   {

      return Bind(::net::address(pszHost, port), range);

   }


   int udp_socket::Bind(const ::net::address & ad, int range)
   {

      //         attach(CreateSocket(ad.GetFamily(), SOCK_DGRAM, "udp"));

      m_datagramsocket = ref new ::Windows::Networking::Sockets::DatagramSocket();

      //::sockets::socket::os_data data;
      //data.o = m_datagramsocket;
      //attach(data);

      create_socket();

      SetNonblocking(true);

      m_datagramsocket->BindEndpointAsync(ad.m_hostname, __str(ad.get_service_number()))->Completed =
      ref new ::Windows::Foundation::AsyncActionCompletedHandler
      ([this](::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
      {

         if(status == ::Windows::Foundation::AsyncStatus::Completed)
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
   ipv4_address ad(get_application(), l, port);
   return open(ad);
   }
   */

   bool udp_socket::open(const char * host, port_t port)
   {

      return open(::net::address(host, port));

   }


   /*bool udp_socket::open(struct in6_addr& a, port_t port)
   {
   ipv6_address ad(get_application(), a, port);
   return open(ad);
   }
   */

   bool udp_socket::open(::net::address & ad)
   {

      m_datagramsocket = ref new ::Windows::Networking::Sockets::DatagramSocket();

      //::sockets::socket::os_data data;
      //data.o = m_datagramsocket;
      //attach(data);

      create_socket();

      SetNonblocking(true);

      m_datagramsocket->ConnectAsync(ad.m_hostname, __str(ad.get_service_number()))->Completed =
      ref new ::Windows::Foundation::AsyncActionCompletedHandler
      ([this](::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
      {

         if(status == ::Windows::Foundation::AsyncStatus::Completed)
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

   ::net::address ad(get_application(), h, p);

   SendToBuf(ad, data, len, flags);

   }
   */

   /** send to specified address */
   /*   void udp_socket::SendToBuf(ipaddr_t a, port_t p, const char *data, int len, int flags)
   {
   ipv4_address ad(get_application(), a, p);
   SendToBuf(ad, data, len, flags);
   }


   void udp_socket::SendToBuf(in6_addr a, port_t p, const char *data, int len, int flags)
   {
   ipv6_address ad(get_application(), a, p);
   SendToBuf(ad, data, len, flags);
   }
   */

   /*
   void udp_socket::SendToBuf(::net::address& ad, const char *data, int len, int flags)
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

   /*   void udp_socket::SendTo(const string & a, port_t p, const string & str, int flags)
   {
   SendToBuf(a, p, str, (int)str.get_length(), flags);
   }


   void udp_socket::SendTo(ipaddr_t a, port_t p, const string & str, int flags)
   {
   SendToBuf(a, p, str, (int)str.get_length(), flags);
   }


   void udp_socket::SendTo(in6_addr a, port_t p, const string & str, int flags)
   {
   SendToBuf(a, p, str, (int)str.get_length(), flags);
   }


   void udp_socket::SendTo(::net::address& ad, const string & str, int flags)
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

      ::Windows::Storage::Streams::DataWriter ^ writer = ref new ::Windows::Storage::Streams::DataWriter(m_datagramsocket->OutputStream);

      writer->WriteBytes(ref new Array < unsigned char, 1U >((unsigned char *) data, len));

      /*writer->FlushAsync()->Completed = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < bool >([this](::Windows::Foundation::IAsyncOperation<bool> asyncInfo, ::Windows::Foundation::AsyncStatus asyncStatus)
      {



      });*/

      /*      if ((m_last_size_written = send(GetSocket(), data, (int)len, flags)) == -1)
      {
      __error("send", Errno, bsd_socket_error(Errno));
      }*/

   }


   void udp_socket::Send(const string & str, int flags)
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

      __memset(&msg, 0, sizeof(msg));
      __memset(from, 0, fromlen);
      __memset(ioBuf, 0, inBufSize);
      __memset(&cmsg_un, 0, sizeof(cmsg_un));

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
      ::apex::get_system()->get_time(&ts);
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
      int q = m_retries; // receive maximum 10 at one cycle
      while (n > 0)
      {
      if (sa_len != sizeof(sa))
      {
      WARN("recvfrom", 0, "unexpected address struct size_i32");
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
      ::apex::get_system()->get_time(&ts);
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
      int q = m_retries;
      while (n > 0)
      {
      if (sa_len != sizeof(sa))
      {
      WARN("recvfrom", 0, "unexpected address struct size_i32");
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
      /*::Windows::Storage::Streams::DataReader ^ reader = ref new ::Windows::Storage::Streams::DataReader(m_datagramsocket->OutputStream);
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
      __throw(error_not_implemented);
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
      WARN("SetBroadcast", Errno, bsd_socket_error(Errno));
      }
      }
      else
      {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *) &zero, sizeof(zero)) == -1)
      {
      WARN("SetBroadcast", Errno, bsd_socket_error(Errno));
      }
      }*/
   }


   bool udp_socket::IsBroadcast()
   {
      __throw(error_not_implemented);
      /*int is_broadcast = 0;
      socklen_t size;

      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *)&is_broadcast, &size) == -1)
      {
      WARN("IsBroadcast", Errno, bsd_socket_error(Errno));
      }
      return is_broadcast != 0;*/
   }


   void udp_socket::SetMulticastTTL(int ttl)
   {
      __throw(error_not_implemented);
      /*if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (setsockopt(GetSocket(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(int)) == -1)
      {
      WARN("SetMulticastTTL", Errno, bsd_socket_error(Errno));
      }*/
   }


   int udp_socket::GetMulticastTTL()
   {
      __throw(error_not_implemented);
      /*int ttl = 0;
      socklen_t size = sizeof(int);

      if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (getsockopt(GetSocket(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, &size) == -1)
      {
      WARN("GetMulticastTTL", Errno, bsd_socket_error(Errno));
      }
      return ttl;*/
   }


   void udp_socket::SetMulticastLoop(bool x)
   {
      __throw(error_not_implemented);
      /*if (GetSocket() == INVALID_SOCKET)
      {
      CreateConnection();
      }
      if (IsIpv6())
      {
      int val = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (char *)&val, sizeof(int)) == -1)
      {
      WARN("SetMulticastLoop", Errno, bsd_socket_error(Errno));
      }
      return;
      }
      int val = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&val, sizeof(int)) == -1)
      {
      WARN("SetMulticastLoop", Errno, bsd_socket_error(Errno));
      }*/
   }


   bool udp_socket::IsMulticastLoop()
   {
      __throw(error_not_implemented);
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
      WARN("IsMulticastLoop", Errno, bsd_socket_error(Errno));
      }
      return is_loop ? true : false;
      }
      int is_loop = 0;
      socklen_t size = sizeof(int);
      if (getsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
      {
      WARN("IsMulticastLoop", Errno, bsd_socket_error(Errno));
      }
      return is_loop ? true : false;*/
   }


   void udp_socket::AddMulticastMembership(const string & group, const string & local_if, int if_index)
   {
      __throw(error_not_implemented);
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
      WARN("AddMulticastMembership", Errno, bsd_socket_error(Errno));
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
      WARN("AddMulticastMembership", Errno, bsd_socket_error(Errno));
      }
      }*/
   }


   void udp_socket::DropMulticastMembership(const string & group, const string & local_if, int if_index)
   {
      __throw(error_not_implemented);
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
      WARN("DropMulticastMembership", Errno, bsd_socket_error(Errno));
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
      WARN("DropMulticastMembership", Errno, bsd_socket_error(Errno));
      }
      }*/
   }


   void udp_socket::SetMulticastHops(int hops)
   {
      __throw(error_not_implemented);
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
      WARN("SetMulticastHops", Errno, bsd_socket_error(Errno));
      }*/
   }


   int udp_socket::GetMulticastHops()
   {
      __throw(error_not_implemented);
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
      WARN("GetMulticastHops", Errno, bsd_socket_error(Errno));
      }
      return hops;*/
   }


   bool udp_socket::IsBound()
   {
      return m_bind_ok;
   }


   void udp_socket::OnRawData(char * buf, memsize len, struct sockaddr * sa, socklen_t sa_len)
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(len);
      UNREFERENCED_PARAMETER(sa);
      UNREFERENCED_PARAMETER(sa_len);
   }


   void udp_socket::OnRawData(char * buf, memsize len, struct sockaddr * sa, socklen_t sa_len, struct timeval * ts)
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(len);
      UNREFERENCED_PARAMETER(sa);
      UNREFERENCED_PARAMETER(sa_len);
      UNREFERENCED_PARAMETER(ts);
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

      return ::apex::get_system()->sockets().net().service_port(m_datagramsocket->Information->RemotePort);

   }


   ::net::address udp_socket::GetRemoteAddress()
   {

      return ::net::address(get_application(), m_datagramsocket->Information->RemoteAddress->CanonicalName, m_datagramsocket->Information->RemotePort);

   }


   port_t udp_socket::GetLocalPort()
   {

      return ::apex::get_system()->sockets().net().service_port(m_datagramsocket->Information->LocalPort);

   }


   ::net::address udp_socket::GetLocalAddress()
   {

      return ::net::address(get_application(), m_datagramsocket->Information->LocalAddress->CanonicalName, m_datagramsocket->Information->LocalPort);

   }


} // namespace sockets



