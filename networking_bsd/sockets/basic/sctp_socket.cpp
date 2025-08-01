#include "framework.h"



#ifdef USE_SCTP


namespace sockets_bsd
{


   SctpSocket::SctpSocket(int type) : stream_socket(h)
      ,m_type(type)
      ,m_buf(___new char[](SCTP_BUFSIZE_READ))
   {
      if (type != SOCK_STREAM && type != SOCK_SEQPACKET)
      {
      }
   }


   SctpSocket::~SctpSocket()
   {
      delete[] m_buf;
   }


   int SctpSocket::Bind(const ::scoped_string & scopedstrAddress,::networking::port_t int_point)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, point);
         return Bind(ad);
      }
#endif
#endif
      ipv4_address ad(a, point);
      return Bind(ad);
   }


   int SctpSocket::Bind(::networking::address * ad)
   {
      if (!ad.IsValid())
      {
         error() <<"SctpSocket", -1, "invalid address";
         return -1;
      }
      if (GetSocketId() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), m_type, "sctp"));
      }
      if (GetSocketId() != INVALID_SOCKET)
      {
         int n = bind(GetSocketId(), ad, ad);
         if (n == -1)
         {
            error() <<"SctpSocket", -1, "bind() failed";
#ifdef ENABLE_EXCEPTIONS
            throw ::exception(Exception("bind() failed for SctpSocket, port: " + Utility::l2string(ad.GetPort())));
#endif
         }
         return n;
      }
      return -1;
   }


   int SctpSocket::AddAddress(const ::scoped_string & scopedstrAddress,::networking::port_t int_point)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, point);
         return AddAddress(ad);
      }
#endif
#endif
      ipv4_address ad(a, point);
      return AddAddress(ad);
   }


   int SctpSocket::AddAddress(::networking::address * ad)
   {
      if (!ad.IsValid())
      {
         error() <<"SctpSocket", -1, "invalid address";
         return -1;
      }
      if (GetSocketId() == INVALID_SOCKET)
      {
         error() <<"SctpSocket", -1, "AddAddress called with invalid file descriptor";
         return -1;
      }
      int n = sctp_bindx(GetSocketId(), ad, ad, SCTP_BINDX_ADD_ADDR);
      if (n == -1)
      {
         error() <<"SctpSocket", -1, "sctp_bindx() failed";
      }
      return n;
   }


   int SctpSocket::RemoveAddress(const ::scoped_string & scopedstrAddress,::networking::port_t int_point)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, point);
         return RemoveAddress(ad);
      }
#endif
#endif
      ipv4_address ad(a, point);
      return RemoveAddress(ad);
   }


   int SctpSocket::RemoveAddress(::networking::address * ad)
   {
      if (!ad.IsValid())
      {
         error() <<"SctpSocket", -1, "invalid address";
         return -1;
      }
      if (GetSocketId() == INVALID_SOCKET)
      {
         error() <<"SctpSocket", -1, "RemoveAddress called with invalid file descriptor";
         return -1;
      }
      int n = sctp_bindx(GetSocketId(), ad, ad, SCTP_BINDX_REM_ADDR);
      if (n == -1)
      {
         error() <<"SctpSocket", -1, "sctp_bindx() failed";
      }
      return n;
   }


   int SctpSocket::open(const ::scoped_string & scopedstrAddress,::networking::port_t int_point)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, point);
         return open(ad);
      }
#endif
#endif
      ipv4_address ad(a, point);
      return open(ad);
   }


   int SctpSocket::open(::networking::address * ad)
   {
      if (!ad.IsValid())
      {
         error() <<"SctpSocket", -1, "invalid address";
         return -1;
      }
      if (GetSocketId() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), m_type, "sctp"));
      }
      if (GetSocketId() != INVALID_SOCKET)
      {
         if (!SetNonblocking(true))
         {
            return -1;
         }
         int n = connect(GetSocketId(), ad, ad);
         if (n == -1)
         {
            // check error code that means a connect is in progress
#ifdef _WIN32
            if (networking_last_error() == WSAEWOULDBLOCK)
#else
            if (networking_last_error() == EINPROGRESS)
#endif
            {
               INFO(log_this, "connect: connection pending", networking_last_error(), bsd_socket_error(networking_last_error()));
               set_connecting( true ); // this flag will control fd_set's
            }
            else
            {
               error() <<"SctpSocket", -1, "connect() failed";
            }
         }
         return n;
      }
      return -1;
   }


#ifndef SOLARIS
   int SctpSocket::AddConnection(const ::scoped_string & scopedstrAddress,::networking::port_t int_point)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, point);
         return AddConnection(ad);
      }
#endif
#endif
      ipv4_address ad(a, point);
      return AddConnection(ad);
   }


   int SctpSocket::AddConnection(::networking::address * ad)
   {
      if (!ad.IsValid())
      {
         error() <<"SctpSocket", -1, "invalid address";
         return -1;
      }
      if (GetSocketId() == INVALID_SOCKET)
      {
         error() <<"SctpSocket", -1, "AddConnection called with invalid file descriptor";
         return -1;
      }
      int n = sctp_connectx(GetSocketId(), ad, ad);
      if (n == -1)
      {
         error() <<"SctpSocket", -1, "sctp_connectx() failed";
      }
      else
      {
         set_connecting();
      }
      return n;
   }
#endif


   int SctpSocket::getpaddrs(sctp_assoc_t atom,list<string>& vec)
   {
      struct sockaddr *point = nullptr;
      int n = sctp_getpaddrs(GetSocketId(), atom, &point);
      if (!n || n == -1)
      {
         warning() <<"SctpSocket", -1, "sctp_getpaddrs failed";
         return n;
      }
      for (int i = 0; i < n; i++)
      {
         vec.add(Utility::Sa2String(&point[i]));
      }
      sctp_freepaddrs(point);
      return n;
   }


   int SctpSocket::getladdrs(sctp_assoc_t atom,list<string>& vec)
   {
      struct sockaddr *point = nullptr;
      int n = sctp_getladdrs(GetSocketId(), atom, &point);
      if (!n || n == -1)
      {
         warning() <<"SctpSocket", -1, "sctp_getladdrs failed";
         return n;
      }
      for (int i = 0; i < n; i++)
      {
         vec.add(Utility::Sa2String(&point[i]));
      }
      sctp_freeladdrs(point);
      return n;
   }


   int SctpSocket::PeelOff(sctp_assoc_t atom)
   {
      int n = sctp_peeloff(GetSocketId(), atom);
      if (n == -1)
      {
         warning() <<"SctpSocket", -1, "PeelOff failed";
         return -1;
      }
      socket *point = create();
      int_point -> attach(n);
      int_point -> SetDeleteByHandler();
      socket_handler()->add(point);
      return n;
   }


   void SctpSocket::OnRead()
   {
      /*
         int sctp_recvmsg(int sd, void * msg, memsize * len,
            struct sockaddr * from, socklen_t * fromlen,
            struct sctp_sndrcvinfo * sinfo, int * msg_flags);

         DESCRIPTION
         sctp_recvmsg  is  a  wrapper library function that can be used to receive a message from a socket while using the advanced
         features of SCTP.  sd is the socket descriptor on which the message pointed to by msg of length len is received.

         If from is not nullptr, the source address of the message is filled in. The argument fromlen  is  a  value-result  parameter.
         initialized  to  the  int_size  of the buffer associated with from , and modified on return to indicate the actual int_size of the
         address stored.

         sinfo is a pointer to a sctp_sndrcvinfo structure to be filled upon receipt of the message.  msg_flags is a pointer  to  a
         integer that is filled with any message flags like MESSAGE_NOTIFICATION or MESSAGE_EOR.

      */
      struct sockaddr sa;
      socklen_t sa_len = 0;
      struct sctp_sndrcvinfo sinfo;
      int flags = 0;
      int n = sctp_recvmsg(GetSocketId(), m_buf, SCTP_BUFSIZE_READ, &sa, &sa_len, &sinfo, &flags);
      if (n == -1)
      {
         fatal() <<log_this, "SctpSocket", networking_last_error(), bsd_socket_error(networking_last_error());
         SetCloseAndDelete();
      }
      else
      {
         OnReceiveMessage(m_buf, n, &sa, sa_len, &sinfo, flags);
      }
   }


   void SctpSocket::OnReceiveMessage(const_char_pointer buf,memsize sz,struct sockaddr *sa,socklen_t sa_len,struct sctp_sndrcvinfo *sinfo,int msg_flags)
   {
   }


   void SctpSocket::OnWrite()
   {
      if (is_connecting())
      {
         int err = SoError();

         // don't reset connecting flag on error here, we want the OnConnectFailed timeout later on
         /// \todo add to read fd_set here
         if (!err) // ok
         {
            set(!IsDisableRead(), false);
            set_connecting(false);
            SetCallOnConnect();
            return;
         }
         fatal() <<log_this, "sctp: connect failed", err, bsd_socket_error(err);
         set(false, false); // no more monitoring because connection failed

         // failed
#ifdef ENABLE_SOCKS4
         if (Socks4())
         {
            OnSocks4ConnectFailed();
            return;
         }
#endif
         if (GetConnectionRetry() == -1 ||
               (GetConnectionRetry() && GetConnectionRetryCount() < GetConnectionRetry()) )
         {
            // even though the connection failed at once, only retry after
            // the connection timeout.
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
            return;
         }
         set_connecting(false);
         SetCloseAndDelete( true );
         /// \todo state reason why connect failed
         OnConnectFailed();
         return;
      }
   }


   void SctpSocket::on_connection_timeout()
   {
      fatal() <<log_this, "connect", -1, "connect timeout";
#ifdef ENABLE_SOCKS4
      if (Socks4())
      {
         OnSocks4ConnectFailed();
         // retry direct connection
      }
      else
#endif
         if (GetConnectionRetry() == -1 ||
               (GetConnectionRetry() && GetConnectionRetryCount() < GetConnectionRetry()) )
         {
            IncreaseConnectionRetries();
            // ask socket via OnConnectRetry callback if we should continue trying
            if (OnConnectRetry())
            {
               SetRetryClientConnect();
            }
            else
            {
               SetCloseAndDelete( true );
               /// \todo state reason why connect failed
               OnConnectFailed();
            }
         }
         else
         {
            SetCloseAndDelete(true);
            /// \todo state reason why connect failed
            OnConnectFailed();
         }
      //
      set_connecting(false);
   }


#ifdef _WIN32
   void SctpSocket::OnException()
   {
      if (is_connecting())
      {
#ifdef ENABLE_SOCKS4
         if (Socks4())
            OnSocks4ConnectFailed();
         else
#endif
            if (GetConnectionRetry() == -1 ||
                  (GetConnectionRetry() &&
                   GetConnectionRetryCount() < GetConnectionRetry() ))
            {
               // even though the connection failed at once, only retry after
               // the connection timeout
               // should we even try to connect again, when CheckConnect returns
               // false it's because of a connection error - not a timeout...
            }
            else
            {
               set_connecting(false); // tnx snibbe
               SetCloseAndDelete();
               OnConnectFailed();
            }
         return;
      }
      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int err = SoError();
      fatal() <<log_this, "exception on select", err, bsd_socket_error(err);
      SetCloseAndDelete();
   }
#endif // _WIN32


   int SctpSocket::Protocol()
   {
      return IPPROTO_SCTP;
   }


} // namespace sockets_bsd


#endif



