/** \file resolv_socket.cpp
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
#include "framework.h"
#include "aura/net/net_sockets.h"
#ifdef _WIN32
#else
//#include <netdb.h>
#endif

namespace sockets
{


   resolv_socket::resolv_socket(base_socket_handler& h) :
      ::object(h.get_context_application()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h)
      ,m_bServer(false)
      ,m_parent(nullptr)
      ,m_resolve_ipv6(false)
      ,m_cached(false)
   {
      SetLineProtocol();
   }


   resolv_socket::resolv_socket(base_socket_handler& h, base_socket *parent, const string & host, port_t port, bool ipv6) :
      ::object(h.get_context_application()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h)
   ,m_bServer(false)
   ,m_parent(parent)
   ,m_resolv_host(host)
   ,m_resolv_port(port)
   ,m_resolve_ipv6(ipv6)
   ,m_cached(false)
   {
      SetLineProtocol();
   }


   resolv_socket::resolv_socket(base_socket_handler& h, base_socket *parent, in_addr a) :
      ::object(h.get_context_application()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h)
   ,m_bServer(false)
   ,m_parent(parent)
   ,m_resolv_port(0)
   ,m_resolv_address(a)
   ,m_resolve_ipv6(false)
   ,m_cached(false)
   {
      SetLineProtocol();
   }


   resolv_socket::resolv_socket(base_socket_handler& h, base_socket *parent, in6_addr& a) :
      ::object(h.get_context_application()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h)
   ,m_bServer(false)
   ,m_parent(parent)
   ,m_resolv_port(0)
   ,m_resolve_ipv6(true)
   ,m_resolv_address6(a)
   ,m_cached(false)
   {
      SetLineProtocol();
   }


   resolv_socket::~resolv_socket()
   {
   }


   void resolv_socket::OnLine(const string & line)
   {
      ::str::parse pa(line, ":");
      if (m_bServer)
      {
         m_query = pa.getword();
         m_data = pa.getrest();
   TRACE(" *** resolv_socket server; query=%s, data=%s\n", m_query, m_data);
         // %! check cache
         {
            single_lock lock(&Session.sockets().m_mutexResolvCache, true);
            string result;
            if(Session.sockets().m_resolvcache[m_query].lookup(m_data, result))
            {
               if (time(nullptr) - Session.sockets().m_resolvtimeout[m_query][m_data] < 3600) // ttl
               {
   TRACE(" *** Returning cache for [%s][%s] = '%s'\n", m_query, m_data, result);
                  write("Cached\n");
                  if (result.is_empty()) /* failed */
                  {
                     write("Failed\n\n");
                     SetCloseAndDelete();
                     return;
                  }
                  else if (m_query == "gethostbyname")
                  {
                     write("A: " + result + "\n\n");
                     SetCloseAndDelete();
                     return;
                  }
                  else if (m_query == "gethostbyname2")
                  {
                     write("AAAA: " + result + "\n\n");
                     SetCloseAndDelete();
                     return;
                  }
                  else if (m_query == "gethostbyaddr")
                  {
                     write("Name: " + result + "\n\n");
                     SetCloseAndDelete();
                     return;
                  }
               }
            }
         }
         if (!detach()) // detach failed?
         {
            SetCloseAndDelete();
         }
         return;
      }
      string key = pa.getword();
      string value = pa.getrest();
   TRACE(" *** resolv_socket response;  %s: %s\n", key, value);

      if (key == "Cached")
      {
         m_cached = true;
      }
      else
      if (key == "Failed" && m_parent)
      {
   TRACE(" ************ Resolve failed\n");
         if (Handler().Resolving(m_parent) || Handler().Valid(m_parent))
         {
            m_parent -> OnResolveFailed(m_resolv_id);
         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&Session.sockets().m_mutexResolvCache, true);
   TRACE(" *** Update cache for [%s][%s] = '%s'\n", m_query, m_data, value);
            Session.sockets().m_resolvcache[m_query][m_data] = value;
            Session.sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
      else
      if (key == "Name" && !m_resolv_host.get_length() && m_parent)
      {
         if (Handler().Resolving(m_parent) || Handler().Valid(m_parent))
         {
            m_parent -> OnReverseResolved(m_resolv_id, value);
         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&Session.sockets().m_mutexResolvCache, true);
   TRACE(" *** Update cache for [%s][%s] = '%s'\n", m_query, m_data, value);
            Session.sockets().m_resolvcache[m_query][m_data] = value;
            Session.sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
      else
      if (key == "A" && m_parent)
      {
         if (Handler().Resolving(m_parent) || Handler().Valid(m_parent))
         {
            //in_addr l;
            //Session.sockets().net().convert(l, value); // ip2ipaddr_t

            m_parent -> OnResolved(m_resolv_id, ::net::address(value, m_resolv_port));
         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&Session.sockets().m_mutexResolvCache, true);
   TRACE(" *** Update cache for [%s][%s] = '%s'\n", m_query, m_data, value);
            Session.sockets().m_resolvcache[m_query][m_data] = value;
            Session.sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr; // always use first ip in case there are several
      }
      else if (key == "AAAA" && m_parent)
      {
         if (Handler().Resolving(m_parent) || Handler().Valid(m_parent))
         {
            //in6_addr a;
            //Session.sockets().net().convert(a, value);
            m_parent -> OnResolved(m_resolv_id, ::net::address(value, m_resolv_port));
         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&Session.sockets().m_mutexResolvCache, true);
   TRACE(" *** Update cache for [%s][%s] = '%s'\n", m_query, m_data, value);
            Session.sockets().m_resolvcache[m_query][m_data] = value;
            Session.sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
   }


   void resolv_socket::OnDetached()
   {
      TRACE(" *** resolv_socket::OnDetached(); query=%s, data=%s\n", m_query, m_data);
      if(m_query == "gethostbyname")
      {
         in_addr sa;
         if(Session.sockets().net().convert(sa, m_data))
         {
            string ip;
            Session.sockets().net().convert(ip, sa);
            write("A: " + ip + "\n");
         }
         else
         {
            write("Failed\n");
         }
         write("\n");
      }
      else if(m_query == "gethostbyname2")
      {
         in6_addr sa;
         if(Session.sockets().net().convert(sa, m_data))
         {
            string ip;
            Session.sockets().net().convert(ip, sa);
            write("AAAA: " + ip + "\n");
         }
         else
         {
            write("Failed\n");
         }
         write("\n");
      }
      else
      if (m_query == "gethostbyaddr")
      {

         ::net::address addr(m_data);

         if(Session.sockets().net().isipv4(m_data) || Session.sockets().net().isipv6(m_data))
         {

            string strCanonicalName = Session.sockets().net().canonical_name(addr);

            if(Session.sockets().net().isipv4(strCanonicalName) || Session.sockets().net().isipv6(strCanonicalName))
            {
               write("Failed: convert to sockaddr_in failed\n");
            }
            else
            {
               write("Name: " + strCanonicalName+ "\n");
            }

         }
         else
         {
            write("Failed: malformed address\n");
         }
         write("\n");
      }
      else
      {
         string msg = "Unknown query type: " + m_query;
         log("OnDetached", 0, msg);
         write("Unknown\n\n");
      }
      SetCloseAndDelete();
   }


   void resolv_socket::OnConnect()
   {
      if (m_resolv_host.get_length())
      {
         string msg = (m_resolve_ipv6 ? "gethostbyname2 " : "gethostbyname ") + m_resolv_host + "\n";
         m_query = m_resolve_ipv6 ? "gethostbyname2" : "gethostbyname";
         m_data = m_resolv_host;
         write( msg );
         return;
      }
      if (m_resolve_ipv6)
      {
         string tmp;
         Session.sockets().net().convert(tmp, m_resolv_address6);
         m_query = "gethostbyaddr";
         m_data = tmp;
         string msg = "gethostbyaddr " + tmp + "\n";
         write( msg );
      }
      string tmp;
      Session.sockets().net().convert(tmp, m_resolv_address);
      m_query = "gethostbyaddr";
      m_data = tmp;
      string msg = "gethostbyaddr " + tmp + "\n";
      write( msg );
   }


   void resolv_socket::OnDelete()
   {
      if (m_parent)
      {
         if (Handler().Resolving(m_parent) || Handler().Valid(m_parent))
         {
            m_parent -> OnResolveFailed(m_resolv_id);
         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&Session.sockets().m_mutexResolvCache, true);
            string value;
   TRACE(" *** Update cache for [%s][%s] = '%s'\n", m_query, m_data, value);
            Session.sockets().m_resolvcache[m_query][m_data] = value;
            Session.sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
   }

} // namespace sockets

