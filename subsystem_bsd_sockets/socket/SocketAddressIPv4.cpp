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
#include "framework.h"
#include "sockdefs.h"
#include "SocketAddressIPv4.h"
#include "subsystem_bsd_sockets/platform/subsystem.h"
#include "subsystem/socket/SocketException.h"
//#include "subsystem/platform/::string.h"

//#include "subsystem/thread/critical_section.h"

namespace subsystem_bsd_sockets
{

   //critical_section SocketAddressIPv4::s_resolveMutex;


   SocketAddressIPv4::SocketAddressIPv4()
   //: m_wsaStartup(1, 2)
   {
      m_addr.s_addr = INADDR_ANY;
      m_port = 0;
   }

   SocketAddressIPv4::~SocketAddressIPv4()
   {

   }



   void SocketAddressIPv4::initialize_socket_address_ipv4()
   {
      m_addr.s_addr = INADDR_ANY;
      m_port = 0;
   }

   void SocketAddressIPv4::_initialize_socket_address_ipv4(struct sockaddr_in addr)
   //: m_wsaStartup(1, 2)
   {
      m_addr.s_addr = INADDR_ANY;
      m_port = 0;

      if (addr.sin_family != AF_INET) {
         throw ::subsystem::SocketException("The specified m_addr is not AF_INET family m_addr!");
      }

      m_addr.s_addr = ntohl(addr.sin_addr.s_addr);
      m_port = ntohs(addr.sin_port);
   }

   void SocketAddressIPv4::initialize_socket_address_ipv4(const ::scoped_string & scopedstrHost, unsigned short port)
   {

      auto psocketaddress = bsd_sockets_subsystem()->resolve_ip4_address(scopedstrHost, port);

      auto  psocketaddressBsd = psocketaddress->impl<::subsystem_bsd_sockets::SocketAddressIPv4>();
      this->m_addr = psocketaddressBsd->m_addr;
      this->m_port = psocketaddressBsd->m_port;
   };

   void SocketAddressIPv4::initialize_socket_address_ipv4(::subsystem::SocketAddressIPv4Interface * psocketAddressIPv4)
   {
      auto  psocketaddressBsd = psocketAddressIPv4->impl<::subsystem_bsd_sockets::SocketAddressIPv4>();
      m_addr = psocketaddressBsd->m_addr;
      m_port = psocketaddressBsd->m_port;
   }

   void SocketAddressIPv4::assign(::subsystem::SocketAddressIPv4Interface * psocketAddressIPv4)
   {
      auto  psocketaddressBsd = psocketAddressIPv4->impl<::subsystem_bsd_sockets::SocketAddressIPv4>();
      if (this != psocketaddressBsd)
      {
         m_addr = psocketaddressBsd->m_addr;
         m_port = psocketaddressBsd->m_port;
      }

   }

   socklen_t SocketAddressIPv4::_getAddrLen() const
   {
      return sizeof(struct sockaddr_in);
   };

   struct sockaddr_in SocketAddressIPv4::_getSockAddr() const
   {
      struct sockaddr_in saddr;

      saddr.sin_family = AF_INET;
      saddr.sin_addr.s_addr = htonl(m_addr.s_addr);
      saddr.sin_port = htons(m_port);

#ifndef _WIN32
      saddr.sin_len = sizeof(struct sockaddr_in);
#endif

      return saddr;
   }

   ::string  SocketAddressIPv4::toString() const
   {
      u_char b1 = m_addr.S_un.S_un_b.s_b4;
      u_char b2 = m_addr.S_un.S_un_b.s_b3;
      u_char b3 = m_addr.S_un.S_un_b.s_b2;
      u_char b4 = m_addr.S_un.S_un_b.s_b1;

      return ::format("{}.{}.{}.{}", b1, b2, b3, b4);
   }

   unsigned short SocketAddressIPv4::getPort() const
   {
      return m_port;
   }


   bool SocketAddressIPv4::isLoopbackAddress() const
   {

      bool isLoopback = (unsigned long)m_addr.S_un.S_addr == 16777343;

      return isLoopback;

   }


   ::pointer < ::subsystem::SocketAddressIPv4Interface > subsystem::resolve_ip4_address(const ::scoped_string & scopedstrHost, unsigned short port)
   {
      auto presolvedAddress = createø<::subsystem::SocketAddressIPv4Interface>();

      auto paddressResolved = presolvedAddress->impl<::subsystem_bsd_sockets::SocketAddressIPv4>();

      ::string hostStorage(scopedstrHost);

      {
         critical_section_lock l(&s_criticalsectionResolveIp4);

         ::string hostAnsi(hostStorage);

         hostent *hent = gethostbyname(hostAnsi);
         if (hent == 0) {
            throw ::subsystem::SocketException();
         }

         paddressResolved->m_addr.S_un.S_addr = ntohl(*(u_long *)hent->h_addr_list[0]);
      }

      paddressResolved->m_port = port;

      return presolvedAddress;

   }


} // namespace subsystem_bsd_sockets



