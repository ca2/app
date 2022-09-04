/**
 **   \file SctpSocket.h
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
#pragma once

#ifdef USE_SCTP

#include <netinet/sctp.h>


namespace sockets
{

   #define SCTP_BUFSIZE_READ 16400


   class SctpSocket : public stream_socket
   {
   public:
      /** SctpSocket constructor.
         \lparam h Owner
         \lparam type SCTP_STREAM or SCTP_SEQPACKET */
      SctpSocket(i32 type);
      ~SctpSocket();

      /** bind() */
      i32 Bind(const string &,::networking::port_t);
      i32 Bind(::networking::address * address);
      /** sctp_bindx() */
      i32 AddAddress(const string &,::networking::port_t);
      i32 AddAddress(::networking::address * address);
      /** sctp_bindx() */
      i32 RemoveAddress(const string &,::networking::port_t);
      i32 RemoveAddress(::networking::address * address);

      /** connect() */
      i32 open(const string &,::networking::port_t);
      i32 open(::networking::address * address);

      /** Connect timeout callback. */
      void on_connection_timeout();
   #ifdef _WIN32
      /** Connection failed reported as exception on win32 */
      void OnException();
   #endif

   #ifndef SOLARIS
      /** sctp_connectx() */
      i32 AddConnection(const string &,::networking::port_t);
      i32 AddConnection(::networking::address * address);
   #endif

      /** get peer addresses of an association. */
      i32 getpaddrs(sctp_assoc_t atom,list<string>&);
      /** get all bound addresses of an association. */
      i32 getladdrs(sctp_assoc_t atom,list<string>&);

      /** sctp_peeloff */
      i32 PeelOff(sctp_assoc_t atom);

      /** recvmsg callback */
      virtual void OnReceiveMessage(const char *buf,memsize sz,struct sockaddr *sa,socklen_t sa_len,struct sctp_sndrcvinfo *sinfo,i32 msg_flags) = 0;

      void OnOptions(i32,i32,i32,SOCKET) {}

      virtual i32 Protocol();

      SctpSocket(const SctpSocket& s) : stream_socket(s) {}
      void OnRead();
      void OnWrite();

      i32 m_type; ///< SCTP_STREAM or SCTP_SEQPACKET
      char *m_buf; ///< Temporary receive buffer
   };

} // namespace sockets

 

#endif // USE_SCTP

