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
//#include "apex/networking/sockets/_sockets.h"
#include <time.h>

#ifdef __APPLE__
#include <netdb.h>
#endif


namespace sockets
{

   resolv_socket::resolv_socket() :
      m_bServer(false)
      ,m_parent(nullptr)
      ,m_resolve_ipv6(false)
      ,m_cached(false)
   {

      SetLineProtocol();

   }


   resolv_socket::resolv_socket(base_socket *parent, const string & host, port_t port, bool ipv6) :
      m_bServer(false)
      ,m_parent(parent)
      ,m_resolv_host(host)
      ,m_resolv_port(port)
      ,m_resolve_ipv6(ipv6)
      ,m_cached(false)
   {

      SetLineProtocol();

   }




   resolv_socket::resolv_socket(base_socket *parent, in_addr a) :
      m_bServer(false)
      ,m_parent(parent)
      ,m_resolv_port(0)
      ,m_resolv_address(a)
      ,m_resolve_ipv6(false)
      ,m_cached(false)
   {
      SetLineProtocol();
   }


   resolv_socket::resolv_socket(base_socket *parent, in6_addr& a) :
      m_bServer(false)
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


   void resolv_socket::initialize(::particle * pparticle)
   {

      //auto estatus = tcp_socket::initialize(pparticle);

      tcp_socket::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      system() = system();

      if (!system())
      {

         throw ::exception(error_resource);

      }

      m_paddressdepartment = ::networking::address_department();

      if (!m_paddressdepartment)
      {

         throw ::exception(error_failed);

      }

      //return estatus;

   }


   void resolv_socket::destroy()
   {

      system().release();

      m_paddressdepartment.release();

      //return ::success;

   }



   void resolv_socket::OnLine(const string & line)
   {

      ::parse pa(line, ":");

      if (m_bServer)
      {

         m_query = pa.getword();

         m_data = pa.getrest();

         information() << " *** resolv_socket server; query="<< m_query <<", data="<< m_data ;

         // %! check cache

         {

            single_lock lock(&system()->sockets().m_pmutexResolvCache, true);

            string result;

            if(system()->sockets().m_resolvcache[m_query].lookup(m_data, result))
            {

               if (time(nullptr) - system()->sockets().m_resolvtimeout[m_query][m_data] < 3600) // ttl
               {

                  information() << " *** Returning cache for ["<< m_query <<"]["<< m_data <<"] = '"<< result <<"'";

                  information() << "Cached";
                  if (result.is_empty()) /* failed */
                  {
                     warning() <<"Failed";
                     SetCloseAndDelete();
                     return;
                  }
                  else if (m_query == "gethostbyname")
                  {
                     information() << "A: " << result;
                     SetCloseAndDelete();
                     return;
                  }
                  else if (m_query == "gethostbyname2")
                  {
                     information() << "AAAA: " << result;
                     SetCloseAndDelete();
                     return;
                  }
                  else if (m_query == "gethostbyaddr")
                  {
                     information() << "Name: " << result;
                     SetCloseAndDelete();
                     return;
                  }
               }
            }
         }
         if (!prepare_for_detach()) // detach failed?
         {
            SetCloseAndDelete();
         }
         return;
      }
      string key = pa.getword();
      string value = pa.getrest();
      information() << " *** resolv_socket response;  "<< key <<": "<< value;

      if (key == "Cached")
      {
         m_cached = true;
      }
      else if (key == "Failed" && m_parent)
      {
         information() << " ************ Resolve failed";
//         if (socket_handler()->Resolving(m_parent) || socket_handler()->Valid(m_parent))
//         {
//            m_parent -> OnResolveFailed(m_resolv_id);
//         }
         // update cache
         if (!m_cached)
         {

            single_lock lock(&system()->sockets().m_pmutexResolvCache, true);
            information() << " *** Update cache for ["<< m_query <<"]["<< m_data <<"] = '"<< value <<"'";
            system()->sockets().m_resolvcache[m_query][m_data] = value;
            system()->sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
      else if (key == "Name" && !m_resolv_host.get_length() && m_parent)
      {
//         if (socket_handler()->Resolving(m_parent) || socket_handler()->Valid(m_parent))
//         {
//            m_parent -> OnReverseResolved(m_resolv_id, value);
//         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&system()->sockets().m_pmutexResolvCache, true);
            information() << " *** Update cache for [" << m_query << "][" << m_data << "] = '" << value << "'";
            system()->sockets().m_resolvcache[m_query][m_data] = value;
            system()->sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
      else if (key == "A" && m_parent)
      {
//         if (socket_handler()->Resolving(m_parent) || socket_handler()->Valid(m_parent))
//         {
//            in_addr l;
//            m_paddressdepartment->convert(l, value); // ip2ipaddr_t
//            m_parent -> OnResolved(m_resolv_id, ::networking::address(l, m_resolv_port));
//         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&system()->sockets().m_pmutexResolvCache, true);
            information() << " *** Update cache for [" << m_query << "][" << m_data << "] = '" << value << "'";
            system()->sockets().m_resolvcache[m_query][m_data] = value;
            system()->sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr; // always use first ip in case there are several
      }
      else if (key == "AAAA" && m_parent)
      {
//         if (socket_handler()->Resolving(m_parent) || socket_handler()->Valid(m_parent))
//         {
//            in6_addr a;
//            m_paddressdepartment->convert(value, a);
//            m_parent -> OnResolved(m_resolv_id, ::networking::address(a, m_resolv_port));
//         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&system()->sockets().m_pmutexResolvCache, true);
            information() << " *** Update cache for [" << m_query << "][" << m_data << "] = '" << value << "'";
            system()->sockets().m_resolvcache[m_query][m_data] = value;
            system()->sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
   }


   void resolv_socket::OnDetached()
   {
      information() << " *** resolv_socket::OnDetached(); query="<<m_query<<", data="<<m_data;
      if (m_query == "gethostbyname")
      {
         struct in_addr sa;
         if (m_paddressdepartment->convert(sa, m_data))
         {
            
            string ip;
            
            m_paddressdepartment->convert(ip, sa);
            
            information() << "A: " << ip;

         }
         else
         {

            information() << "Failed";

         }
         
      }
      else if (m_query == "gethostbyname2")
      {
         
         struct in6_addr sa;

         if (m_paddressdepartment->convert(sa, m_data))
         {
            
            string ip;
            
            m_paddressdepartment->convert(ip, sa);
            
            information() << "AAAA: " + ip;

         }
         else
         {

            information() << "Failed";

         }
         
      }
      else if (m_query == "gethostbyaddr")
      {
         
         ::networking::address address(m_data);

         string name;

         if (!m_paddressdepartment->reverse(name, address))
         {

            information() << "Failed: convert to sockaddr_in failed";
         
         }
         else
         {

            information() << "Name: " << name;

         }

      }
      else
      {

         string msg = "Unknown query type: " + m_query;

         information() << "OnDetached " << msg;

         print("Unknown\n\n");

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

         print( msg );

         return;

      }

      if (m_resolve_ipv6)
      {

         string tmp;

         m_paddressdepartment->convert(tmp, m_resolv_address6);

         m_query = "gethostbyaddr";

         m_data = tmp;

         string msg = "gethostbyaddr " + tmp + "\n";

         print( msg );

      }
      
      string tmp;

      m_paddressdepartment->convert(tmp, m_resolv_address);

      m_query = "gethostbyaddr";

      m_data = tmp;

      string msg = "gethostbyaddr " + tmp + "\n";

      print( msg );

   }


   void resolv_socket::OnDelete()
   {
      if (m_parent)
      {
//         if (socket_handler()->Resolving(m_parent) || socket_handler()->Valid(m_parent))
//         {
//            m_parent -> OnResolveFailed(m_resolv_id);
//         }
         // update cache
         if (!m_cached)
         {
            single_lock lock(&system()->sockets().m_pmutexResolvCache, true);
            string value;
            information() << " *** Update cache for ["<< m_query <<"][" << m_data << "] = '"<<value<<"'";
            system()->sockets().m_resolvcache[m_query][m_data] = value;
            system()->sockets().m_resolvtimeout[m_query][m_data] = time(nullptr);
         }
         m_parent = nullptr;
      }
   }

} // namespace sockets

