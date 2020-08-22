/**
 **   \file SctpSocket.cpp
 **   \date  2006-09-04
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2007  Anders Hedstrom

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "framework.h"

#ifdef USE_SCTP

namespace sockets
{


   SctpSocket::SctpSocket(base_socket_handler& h,int type) : stream_socket(h)
      ,m_type(type)
      ,m_buf(new char[SCTP_BUFSIZE_READ])
   {
      if (type != SOCK_STREAM && type != SOCK_SEQPACKET)
      {
      }
   }


   SctpSocket::~SctpSocket()
   {
      delete[] m_buf;
   }


   int SctpSocket::Bind(const string & a,port_t p)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return Bind(ad);
      }
#endif
#endif
      ipv4_address ad(a, p);
      return Bind(ad);
   }


   int SctpSocket::Bind(::net::address& ad)
   {
      if (!ad.IsValid())
      {
         __error("SctpSocket", -1, "invalid address");
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), m_type, "sctp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         int n = bind(GetSocket(), ad, ad);
         if (n == -1)
         {
            __error("SctpSocket", -1, "bind() failed");
#ifdef ENABLE_EXCEPTIONS
            __throw(Exception("bind() failed for SctpSocket, port: " + Utility::l2string(ad.GetPort())));
#endif
         }
         return n;
      }
      return -1;
   }


   int SctpSocket::AddAddress(const string & a,port_t p)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return AddAddress(ad);
      }
#endif
#endif
      ipv4_address ad(a, p);
      return AddAddress(ad);
   }


   int SctpSocket::AddAddress(::net::address& ad)
   {
      if (!ad.IsValid())
      {
         __error("SctpSocket", -1, "invalid address");
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         __error("SctpSocket", -1, "AddAddress called with invalid file descriptor");
         return -1;
      }
      int n = sctp_bindx(GetSocket(), ad, ad, SCTP_BINDX_ADD_ADDR);
      if (n == -1)
      {
         __error("SctpSocket", -1, "sctp_bindx() failed");
      }
      return n;
   }


   int SctpSocket::RemoveAddress(const string & a,port_t p)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return RemoveAddress(ad);
      }
#endif
#endif
      ipv4_address ad(a, p);
      return RemoveAddress(ad);
   }


   int SctpSocket::RemoveAddress(::net::address& ad)
   {
      if (!ad.IsValid())
      {
         __error("SctpSocket", -1, "invalid address");
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         __error("SctpSocket", -1, "RemoveAddress called with invalid file descriptor");
         return -1;
      }
      int n = sctp_bindx(GetSocket(), ad, ad, SCTP_BINDX_REM_ADDR);
      if (n == -1)
      {
         __error("SctpSocket", -1, "sctp_bindx() failed");
      }
      return n;
   }


   int SctpSocket::open(const string & a,port_t p)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return open(ad);
      }
#endif
#endif
      ipv4_address ad(a, p);
      return open(ad);
   }


   int SctpSocket::open(::net::address& ad)
   {
      if (!ad.IsValid())
      {
         __error("SctpSocket", -1, "invalid address");
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), m_type, "sctp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         if (!SetNonblocking(true))
         {
            return -1;
         }
         int n = connect(GetSocket(), ad, ad);
         if (n == -1)
         {
            // check error code that means a connect is in progress
#ifdef _WIN32
            if (Errno == WSAEWOULDBLOCK)
#else
            if (Errno == EINPROGRESS)
#endif
            {
               INFO(log_this, "connect: connection pending", Errno, bsd_socket_error(Errno));
               SetConnecting( true ); // this flag will control fd_set's
            }
            else
            {
               __error("SctpSocket", -1, "connect() failed");
            }
         }
         return n;
      }
      return -1;
   }


#ifndef SOLARIS
   int SctpSocket::AddConnection(const string & a,port_t p)
   {
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return AddConnection(ad);
      }
#endif
#endif
      ipv4_address ad(a, p);
      return AddConnection(ad);
   }


   int SctpSocket::AddConnection(::net::address& ad)
   {
      if (!ad.IsValid())
      {
         __error("SctpSocket", -1, "invalid address");
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         __error("SctpSocket", -1, "AddConnection called with invalid file descriptor");
         return -1;
      }
      int n = sctp_connectx(GetSocket(), ad, ad);
      if (n == -1)
      {
         __error("SctpSocket", -1, "sctp_connectx() failed");
      }
      else
      {
         SetConnecting();
      }
      return n;
   }
#endif


   int SctpSocket::getpaddrs(sctp_assoc_t id,list<string>& vec)
   {
      struct sockaddr *p = nullptr;
      int n = sctp_getpaddrs(GetSocket(), id, &p);
      if (!n || n == -1)
      {
         WARN("SctpSocket", -1, "sctp_getpaddrs failed");
         return n;
      }
      for (int i = 0; i < n; i++)
      {
         vec.push_back(Utility::Sa2String(&p[i]));
      }
      sctp_freepaddrs(p);
      return n;
   }


   int SctpSocket::getladdrs(sctp_assoc_t id,list<string>& vec)
   {
      struct sockaddr *p = nullptr;
      int n = sctp_getladdrs(GetSocket(), id, &p);
      if (!n || n == -1)
      {
         WARN("SctpSocket", -1, "sctp_getladdrs failed");
         return n;
      }
      for (int i = 0; i < n; i++)
      {
         vec.push_back(Utility::Sa2String(&p[i]));
      }
      sctp_freeladdrs(p);
      return n;
   }


   int SctpSocket::PeelOff(sctp_assoc_t id)
   {
      int n = sctp_peeloff(GetSocket(), id);
      if (n == -1)
      {
         WARN("SctpSocket", -1, "PeelOff failed");
         return -1;
      }
      socket *p = create();
      p -> attach(n);
      p -> SetDeleteByHandler();
      Handler().add(p);
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
         initialized  to  the  size  of the buffer associated with from , and modified on return to indicate the actual size of the
         address stored.

         sinfo is a pointer to a sctp_sndrcvinfo structure to be filled upon receipt of the message.  msg_flags is a pointer  to  a
         integer that is filled with any message flags like MSG_NOTIFICATION or MSG_EOR.

      */
      struct sockaddr sa;
      socklen_t sa_len = 0;
      struct sctp_sndrcvinfo sinfo;
      int flags = 0;
      int n = sctp_recvmsg(GetSocket(), m_buf, SCTP_BUFSIZE_READ, &sa, &sa_len, &sinfo, &flags);
      if (n == -1)
      {
         FATAL(log_this, "SctpSocket", Errno, bsd_socket_error(Errno));
         SetCloseAndDelete();
      }
      else
      {
         OnReceiveMessage(m_buf, n, &sa, sa_len, &sinfo, flags);
      }
   }


   void SctpSocket::OnReceiveMessage(const char *buf,memsize sz,struct sockaddr *sa,socklen_t sa_len,struct sctp_sndrcvinfo *sinfo,int msg_flags)
   {
   }


   void SctpSocket::OnWrite()
   {
      if (Connecting())
      {
         int err = SoError();

         // don't reset connecting flag on error here, we want the OnConnectFailed timeout later on
         /// \todo add to read fd_set here
         if (!err) // ok
         {
            Set(!IsDisableRead(), false);
            SetConnecting(false);
            SetCallOnConnect();
            return;
         }
         FATAL(log_this, "sctp: connect failed", err, bsd_socket_error(err));
         Set(false, false); // no more monitoring because connection failed

         // failed
#ifdef ENABLE_SOCKS4
         if (Socks4())
         {
            OnSocks4ConnectFailed();
            return;
         }
#endif
         if (GetConnectionRetry() == -1 ||
               (GetConnectionRetry() && GetConnectionRetries() < GetConnectionRetry()) )
         {
            // even though the connection failed at once, only retry after
            // the connection timeout.
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
            return;
         }
         SetConnecting(false);
         SetCloseAndDelete( true );
         /// \todo state reason why connect failed
         OnConnectFailed();
         return;
      }
   }


   void SctpSocket::OnConnectTimeout()
   {
      FATAL(log_this, "connect", -1, "connect timeout");
#ifdef ENABLE_SOCKS4
      if (Socks4())
      {
         OnSocks4ConnectFailed();
         // retry direct connection
      }
      else
#endif
         if (GetConnectionRetry() == -1 ||
               (GetConnectionRetry() && GetConnectionRetries() < GetConnectionRetry()) )
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
      SetConnecting(false);
   }


#ifdef _WIN32
   void SctpSocket::OnException()
   {
      if (Connecting())
      {
#ifdef ENABLE_SOCKS4
         if (Socks4())
            OnSocks4ConnectFailed();
         else
#endif
            if (GetConnectionRetry() == -1 ||
                  (GetConnectionRetry() &&
                   GetConnectionRetries() < GetConnectionRetry() ))
            {
               // even though the connection failed at once, only retry after
               // the connection timeout
               // should we even try to connect again, when CheckConnect returns
               // false it's because of a connection error - not a timeout...
            }
            else
            {
               SetConnecting(false); // tnx snibbe
               SetCloseAndDelete();
               OnConnectFailed();
            }
         return;
      }
      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int err = SoError();
      FATAL(log_this, "exception on select", err, bsd_socket_error(err));
      SetCloseAndDelete();
   }
#endif // _WIN32


   int SctpSocket::Protocol()
   {
      return IPPROTO_SCTP;
   }


} // namespace sockets


#endif