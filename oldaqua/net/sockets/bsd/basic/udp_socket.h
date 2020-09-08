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
      class CLASS_DECL_AQUA udp_socket : 
         virtual public socket
      {
      public:


         char *m_ibuf; ///< Input buffer
         i32 m_ibufsz; ///< size of input buffer
         bool m_bind_ok; ///< Bind completed successfully
         port_t m_port; ///< Bind port number
         memsize m_last_size_written;
         i32 m_retries;
         bool m_b_read_ts;


         int m_iWriteFlags;

         /** Constructor.
         \lparam h base_socket_handler context_object
         \lparam ibufsz Maximum size of receive message (extra bytes will be truncated)
         \lparam ipv6 'true' if this is an ipv6 socket */
         udp_socket(base_socket_handler& h,i32 ibufsz = 16384,bool ipv6 = false, i32 retries = 0);
         ~udp_socket();

         /** Called when incoming data has been received.
         \lparam buf Pointer to data
         \lparam len Length of data
         \lparam sa Pointer to sockaddr struct of sender
         \lparam sa_len Length of sockaddr struct */
         using socket::OnRawData;
         virtual void OnRawData(char *buf,memsize len,struct sockaddr *sa,socklen_t sa_len);

         /** Called when incoming data has been received and read timestamp is enabled.
         \lparam buf Pointer to data
         \lparam len Length of data
         \lparam sa Pointer to sockaddr struct of sender
         \lparam sa_len Length of sockaddr struct
         \lparam ts Timestamp from message */
         virtual void OnRawData(char *buf,memsize len,struct sockaddr *sa,socklen_t sa_len,struct timeval *ts);

         /** To receive incoming data, call Bind to setup an incoming port.
         \lparam port Incoming port number
         \lparam range Port range to try if ports already in use
         \return 0 if bind succeeded */
         i32 Bind(port_t  & port, i32 range = 1);
         /** To receive data on a specific interface:port, use this.
         \lparam intf Interface ip/hostname
         \lparam port Port number
         \lparam range Port range
         \return 0 if bind succeeded */
         i32 Bind(const string & strHost, port_t & port, i32 range = 1);
         /** To receive data on a specific interface:port, use this.
         \lparam a Ip address
         \lparam port Port number
         \lparam range Port range
         \return 0 if bind succeeded */
         i32 Bind(in_addr a,port_t& port,i32 range = 1);
         /** To receive data on a specific interface:port, use this.
         \lparam a Ipv6 address
         \lparam port Port number
         \lparam range Port range
         \return 0 if bind succeeded */
         i32 Bind(in6_addr a,port_t& port,i32 range = 1);
         /** To receive data on a specific interface:port, use this.
         \lparam ad socket address
         \lparam range Port range
         \return 0 if bind succeeded */
         i32 Bind(::net::address & address, i32 range = 1);

         /** Define remote host.
         \lparam l Address of remote host
         \lparam port Port of remote host
         \return true if successful */
         //using ::sockets::socket::open;
         bool open(in_addr l,port_t port);
         /** Define remote host.
         \lparam host Hostname
         \lparam port Port number
         \return true if successful */
         bool open(const string & host,port_t port);
         /** Define remote host.
         \lparam a Address of remote host, ipv6
         \lparam port Port of remote host
         \return true if successful */
         bool open(struct in6_addr& a,port_t port);
         /** Define remote host.
         \lparam ad socket address
         \return true if successful */
         bool open(const ::net::address & address);

         /** Send to specified host */
         void SendToBuf(const string & ,port_t,const char *data,i32 len,i32 flags = 0);
         /** Send to specified address */
         void SendToBuf(const in_addr & a, port_t,const char *data,i32 len,i32 flags = 0);
         /** Send to specified ipv6 address */
         void SendToBuf(const in6_addr & a,port_t,const char *data,i32 len,i32 flags = 0);
         /** Send to specified socket address */
         void SendToBuf(const ::net::address & address, const char *data,i32 len,i32 flags = 0);

         /** Send string to specified host */
         void SendTo(const string &,port_t,const string &,i32 flags = 0);
         /** Send string to specified address */
         void SendTo(in_addr,port_t,const string &,i32 flags = 0);
         /** Send string to specified ipv6 address */
         void SendTo(in6_addr,port_t,const string &,i32 flags = 0);
         /** Send string to specified socket address */
         void SendTo(const ::net::address & address, const string &,i32 flags = 0);

         /** Send to connected address */
         //using ::file::file::write;
         //using ::object::write;
         void write(const void *data, memsize c);
         /** Send string to connected address. */
         //void Send(const string &);

         /** set broadcast */
         void SetBroadcast(bool b = true);
         /** Check broadcast flag.
         \return true broadcast is enabled. */
         bool IsBroadcast();

         /** multicast */
         void SetMulticastTTL(i32 ttl = 1);
         i32 GetMulticastTTL();
         void SetMulticastLoop(bool = true);
         bool IsMulticastLoop();
         void AddMulticastMembership(const string & group,const string & intf = "0.0.0.0",i32 if_index = 0);
         void DropMulticastMembership(const string & group,const string & intf = "0.0.0.0",i32 if_index = 0);
         /** multicast, ipv6 only */
         void SetMulticastHops(i32 = -1);
         /** multicast, ipv6 only */
         i32 GetMulticastHops();
         /** Returns true if Bind succeeded. */
         bool IsBound();
         /** Return Bind port number */
         port_t GetPort();
         void OnOptions(i32,i32,i32,SOCKET) {}
         memsize GetLastSizeWritten();

         /** Also read timestamp information from incoming message */
         void SetTimestamp(bool = true);

      protected:
         udp_socket(const udp_socket& s) : base_socket(s), socket(s) {}
         void OnRead();
#if defined(LINUX) || defined(MACOSX)
         /** This method emulates socket recvfrom, but uses messages so we can get the timestamp */
         i32 ReadTS(char *ioBuf, i32 inBufSize, struct sockaddr *from, socklen_t fromlen, struct timeval *ts);
#endif

         /** create before using sendto methods */
         void CreateConnection();


      };


   } // namespace sockets






