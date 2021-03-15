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

   class ::net::address;


   class SctpSocket : public stream_socket
   {
   public:
      /** SctpSocket constructor.
         \param h Owner
         \param type SCTP_STREAM or SCTP_SEQPACKET */
      SctpSocket(int type);
      ~SctpSocket();

      /** bind() */
      int Bind(const string &,port_t);
      int Bind(::net::address&);
      /** sctp_bindx() */
      int AddAddress(const string &,port_t);
      int AddAddress(::net::address&);
      /** sctp_bindx() */
      int RemoveAddress(const string &,port_t);
      int RemoveAddress(::net::address&);

      /** connect() */
      int open(const string &,port_t);
      int open(::net::address&);

      /** Connect timeout callback. */
      void OnConnectTimeout();
   #ifdef _WIN32
      /** Connection failed reported as exception on win32 */
      void OnException();
   #endif

   #ifndef SOLARIS
      /** sctp_connectx() */
      int AddConnection(const string &,port_t);
      int AddConnection(::net::address&);
   #endif

      /** get peer addresses of an association. */
      int getpaddrs(sctp_assoc_t id,list<string>&);
      /** get all bound addresses of an association. */
      int getladdrs(sctp_assoc_t id,list<string>&);

      /** sctp_peeloff */
      int PeelOff(sctp_assoc_t id);

      /** recvmsg callback */
      virtual void OnReceiveMessage(const char *buf,memsize sz,struct sockaddr *sa,socklen_t sa_len,struct sctp_sndrcvinfo *sinfo,int msg_flags) = 0;

      void OnOptions(int,int,int,SOCKET) {}

      virtual int Protocol();

      SctpSocket(const SctpSocket& s) : stream_socket(s) {}
      void OnRead();
      void OnWrite();

      int m_type; ///< SCTP_STREAM or SCTP_SEQPACKET
      char *m_buf; ///< Temporary receive buffer
   };

} // namespace sockets

 

#endif // USE_SCTP

