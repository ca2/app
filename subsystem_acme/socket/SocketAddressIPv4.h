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

#include "subsystem_acme/_common_header.h"
//#include "subsystem_acme/thread/critical_section.h"
#include "SocketException.h"
#include "sockdefs.h"
//#include "remoting/remoting_common/win_system/WsaStartup.h"


namespace subsystem
{
   // FIXME: Deprecated method, only for testing of old code.
   void getLocalIPAddrString(char *buffer, int buflen);

   class CLASS_DECL_ACME SocketAddressIPv4Interface :
   virtual public ::subsystem::particle_interface<SocketAddressIPv4Interface>
   {
   public:

      //virtual ~SocketAddressIPv4Interface() = 0;


      virtual void initialize_socket_address_ipv4() = 0;
      //virtual void initialize_socket_address_ipv4(struct sockaddr_in) = 0;
      virtual void initialize_socket_address_ipv4(const ::scoped_string & scopedstrHost, unsigned short port) = 0;
      virtual void initialize_socket_address_ipv4(const SocketAddressIPv4 &socketAddressIPv4) = 0;


      virtual void assign(const SocketAddressIPv4 &socketAddressIPv4) = 0;


      ///socklen_t getAddrLen() const = 0;
      //struct sockaddr_in getSockAddr() const = 0;

      // Converts socket address to it's string value (ip address as string).
      ::string toString() const;

      // Returns socket port number
      unsigned short getPort() const;


   // //protected:
   //    //WsaStartup m_wsaStartup;
   //    unsigned short m_port;
   //    struct in_addr m_addr;


   };
} // namespace subsystem