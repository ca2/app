/** \file resolv_socket.h
**   \date  2005-03-24
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

      /** Async DNS resolver socket. 
      \ingroup async */
      class resolv_socket : public tcp_socket
      {
      public:


         /* type, host, result */
         typedef ::string_map < ::string_to_string > cache_t;

         /* type, host, time */
         typedef ::string_map < ::string_map < time_t > > timeout_t; 


         string m_query;
         string m_data;
         bool m_bServer;
         base_socket *m_parent;
         int m_resolv_id;
         string m_resolv_host;
         port_t m_resolv_port;
         in_addr m_resolv_address;
         bool m_resolve_ipv6;
         in6_addr m_resolv_address6;
         bool m_cached;


         resolv_socket();
         resolv_socket(base_socket * parent, const string & host, port_t port, bool ipv6 = false);
         resolv_socket(base_socket * parent, in_addr);
         resolv_socket(base_socket * parent, in6_addr&);
         ~resolv_socket();

         void OnAccept() { m_bServer = true; }
         void OnLine(const string & line);
         void OnDetached();
         void OnDelete();

         void SetId(int x) { m_resolv_id = x; }
         int GetId() { return m_resolv_id; }

         void OnConnect();

         void SetResolveIpv6(bool x = true) { m_resolve_ipv6 = x; }

      };


   } // namespace sockets
