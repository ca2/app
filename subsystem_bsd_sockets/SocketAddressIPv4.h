// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

//#ifndef SOCKET_ADDRESS_IPV4_H
#pragma once
//#define SOCKET_ADDRESS_IPV4_H

#include "subsystem/socket/SocketAddressIPv4.h"
#include "subsystem/_common_header.h"
//#include "subsystem/thread/critical_section.h"
#include "sockdefs.h"
//#include "remoting/remoting_common/win_system/WsaStartup.h"


namespace subsystem_bsd_sockets
{


   // FIXME: Deprecated method, only for testing of old code.
   void getLocalIPAddrString(char *buffer, int buflen);


   class CLASS_DECL_SUBSYSTEM_BSD_SOCKETS SocketAddressIPv4 :
   virtual public ::subsystem::implementation<::subsystem::SocketAddressIPv4Interface>
   {
   public:


      // SocketAddressIPv4();
      // SocketAddressIPv4(struct sockaddr_in);
      // SocketAddressIPv4(const ::scoped_string & scopedstrHost, unsigned short port);
      //
      // SocketAddressIPv4(const SocketAddressIPv4 &socketAddressIPv4);
      // SocketAddressIPv4 &operator=(const SocketAddressIPv4 &socketAddressIPv4);

      SocketAddressIPv4();
      ~SocketAddressIPv4() override;

      void initialize_socket_address_ipv4() override;
      void _initialize_socket_address_ipv4(struct sockaddr_in);
      void initialize_socket_address_ipv4(const ::scoped_string & scopedstrHost, unsigned short port) override;
      void initialize_socket_address_ipv4(const SocketAddressIPv4Interface &socketAddressIPv4) override;


      virtual void assign(const SocketAddressIPv4Interface &socketAddressIPv4) override;

      virtual socklen_t _getAddrLen() const;
      virtual struct sockaddr_in _getSockAddr() const;

      // Converts socket address to it's string value (ip address as string).
      ::string toString() const override;

      // Returns socket port number
      unsigned short getPort() const override;

      /// SocketAddressIPv4 resolve(const ::scoped_string & scopedstrHost, unsigned short port);

   //protected:
     // WsaStartup m_wsaStartup;
      unsigned short m_port;
      struct in_addr m_addr;

      //static critical_section s_resolveMutex;

   };


} // namespace  subsystem_bsd_sockets




