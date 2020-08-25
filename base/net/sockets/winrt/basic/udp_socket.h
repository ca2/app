/** \file udp_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/
/*
Copyright (C) 2004-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

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
#pragma once


namespace sockets
{


   /** socket implementation for UDP.
   \ingroup basic */
   class CLASS_DECL_BASE udp_socket : 
      virtual public socket
   {
   private:

#if defined(__cplusplus_winrt)

      class os_data
      {
      public:

         ::Windows::Networking::Sockets::DatagramSocket ^      m_datagramsocket;

      };
#else

      class os_data;

#endif

      os_data * m_posdata;
      char *m_ibuf; ///< Input buffer
      int m_ibufsz; ///< size of input buffer
      bool m_bind_ok; ///< Bind completed successfully
      port_t m_port; ///< Bind port number
      int m_last_size_written;
      int m_retries;
      bool m_b_read_ts;


   public:

      int m_iWriteFlags;


      /** Constructor.
      \param h base_socket_handler context_object
      \param ibufsz Maximum size of receive message (extra bytes will be truncated)
      \param ipv6 'true' if this is an ipv6 socket */
      udp_socket(base_socket_handler& h,int ibufsz = 16384,bool ipv6 = false, int retries = 0);
      ~udp_socket();

      /** Called when incoming data has been received.
      \param buf Pointer to data
      \param len Length of data
      \param sa Pointer to sockaddr struct of sender
      \param sa_len Length of sockaddr struct */
      using socket::OnRawData;
      virtual void OnRawData(char *buf,memsize len,struct sockaddr *sa,socklen_t sa_len);

      /** Called when incoming data has been received and read timestamp is enabled.
      \param buf Pointer to data
      \param len Length of data
      \param sa Pointer to sockaddr struct of sender
      \param sa_len Length of sockaddr struct
      \param ts Timestamp from message */
      virtual void OnRawData(char *buf,memsize len,struct sockaddr *sa,socklen_t sa_len,struct timeval *ts);

      /** To receive incoming data, call Bind to setup an incoming port.
      \param port Incoming port number
      \param range Port range to try if ports already in use
      \return 0 if bind succeeded */
      int Bind(port_t port,int range = 1);
      /** To receive data on a specific interface:port, use this.
      \param intf Interface ip/hostname
      \param port Port number
      \param range Port range
      \return 0 if bind succeeded */
      int Bind(const char * pszInterface, port_t port, int range = 1);
      /** To receive data on a specific interface:port, use this.
      \param a Ip ::net::address
      \param port Port number
      \param range Port range
      \return 0 if bind succeeded */
      //int Bind(ipaddr_t a,port_t& port,int range = 1);
      /** To receive data on a specific interface:port, use this.
      \param a Ipv6 ::net::address
      \param port Port number
      \param range Port range
      \return 0 if bind succeeded */
      //int Bind(in6_addr a,port_t& port,int range = 1);
      /** To receive data on a specific interface:port, use this.
      \param ad socket ::net::address
      \param range Port range
      \return 0 if bind succeeded */
      int Bind(const ::net::address & ad, int range = 1);

      /** Define remote host.
      \param l Address of remote host
      \param port Port of remote host
      \return true if successful */
      //bool open(ipaddr_t l,port_t port);
      /** Define remote host.
      \param host Hostname
      \param port Port number
      \return true if successful */
      bool open(const char * host, port_t port);
      /** Define remote host.
      \param a Address of remote host, ipv6
      \param port Port of remote host
      \return true if successful */
      //bool open(struct in6_addr& a,port_t port);
      /** Define remote host.
      \param ad socket ::net::address
      \return true if successful */
      bool open(::net::address & ad);

      /** Send to specified host */
      //void SendToBuf(const string & ,port_t,const char *data,int len,int flags = 0);
      /** Send to specified ::net::address */
//      void SendToBuf(ipaddr_t,port_t,const char *data,int len,int flags = 0);
      /** Send to specified ipv6 ::net::address */
  //    void SendToBuf(in6_addr,port_t,const char *data,int len,int flags = 0);
      /** Send to specified socket ::net::address */
      //void SendToBuf(::net::address& ad,const char *data,int len,int flags = 0);

      /** Send string to specified host */
      //void SendTo(const string &,port_t,const string &,int flags = 0);
      /** Send string to specified ::net::address */
//      void SendTo(ipaddr_t,port_t,const string &,int flags = 0);
      /** Send string to specified ipv6 ::net::address */
  //    void SendTo(in6_addr,port_t,const string &,int flags = 0);
      /** Send string to specified socket ::net::address */
      //void SendTo(::net::address& ad,const string &,int flags = 0);

      /** Send to connected ::net::address */
      void SendBuf(const char *data,memsize,int flags = 0);
      /** Send string to connected ::net::address. */
      void Send(const string & ,int flags = 0);

      /** Set broadcast */
      void SetBroadcast(bool b = true);
      /** Check broadcast flag.
      \return true broadcast is enabled. */
      bool IsBroadcast();

      /** multicast */
      void SetMulticastTTL(int ttl = 1);
      int GetMulticastTTL();
      void SetMulticastLoop(bool = true);
      bool IsMulticastLoop();
      void AddMulticastMembership(const string & group,const string & intf = "0.0.0.0",int if_index = 0);
      void DropMulticastMembership(const string & group,const string & intf = "0.0.0.0",int if_index = 0);
      /** multicast, ipv6 only */
      void SetMulticastHops(int = -1);
      /** multicast, ipv6 only */
      int GetMulticastHops();
      /** Returns true if Bind succeeded. */
      bool IsBound();
      /** Return Bind port number */
      port_t GetPort();
      void OnOptions(int,int,int,SOCKET) {}
      int GetLastSizeWritten();

      /** Also read timestamp information from incoming message */
      void SetTimestamp(bool = true);

      virtual port_t GetRemotePort();
      virtual ::net::address GetRemoteAddress();
      virtual port_t GetLocalPort();
      virtual ::net::address GetLocalAddress();

   protected:
      udp_socket(const udp_socket& s) : base_socket(s), socket(s) {}
      void OnRead();
#if defined(LINUX) || defined(MACOSX)
      /** This method emulates socket recvfrom, but uses messages so we can get the timestamp */
      int ReadTS(char *ioBuf, int inBufSize, struct sockaddr *from, socklen_t fromlen, struct timeval *ts);
#endif

      /** create before using sendto methods */
      //void CreateConnection();


   };


} // namespace sockets




