// http://www.alhem.net/
/** from C++ Sockets Library
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



// 1.8.6: define FD_SETSIZE to something bigger than 64 if there are a lot of
// simultaneous connections (must be done before including winsock.h)
//#define FD_SETSIZE 1024

// windows 2000 with ipv6 preview installed:
//    http://msdn.microsoft.com/downloads/sdks/platform/tpipv6.asp
// see the FAQ on how to install
/*#define WIN32_LEAN_AND_MEAN
#include <ws2tcpip.h>
#if _MSC_VER < 1200
#ifndef __CYGWIN__
#ifdef ENABLE_IPV6
#include <tpipv6.h>  // For IPv6 Tech Preview.
#endif
#endif
#endif // _MSC_VER < 1200
*/




namespace sockets
{
   // http://www.alhem.net/
   /** from C++ Sockets Library \file Utility.h
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

   class CLASS_DECL_APEX net :
      public ::object
   {
   private:


      string            m_host; ///< local hostname
      in_addr           m_ip; ///< local ip address
      string            m_addr; ///< local ip address in string format
      string            m_local_addr6; ///< local ip address in string format
      struct in6_addr   m_local_ip6; ///< local ipv6 address
      bool              m_local_resolved; ///< ResolveLocal has been called if true


   public:


      class CLASS_DECL_APEX dns_cache_item
      {
      public:


         in_addr        m_ipaddr;
         millis           m_millisLastChecked;
         bool           m_bOk;


      };


      ::mutex                                            m_mutexCache;
      ::string_map < dns_cache_item >                    m_mapCache;


      net();
      virtual ~net();


      virtual ::e_status initialize(::object * pobject) override;

      virtual bool gudo_set();

      virtual bool gudo_get();

      ::e_status destroy() override;

      /*
      * Encode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_encode(const string & src);

      /*
      * Decode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_decode(const string & src);

      static bool isipv4(const ::string & str);

      static bool isipv6(const ::string & str);

#ifdef BSD_STYLE_SOCKETS

      static bool convert(in_addr & addr, const string & psz, int ai_flags = 0);

      static bool convert(in6_addr & addr, const string & psz, int ai_flags = 0);

      static bool convert(string & str, const in_addr & addr, int ai_flags = 0);

      static bool convert(string & str, const in6_addr & addr, int ai_flags = 0);

#endif

      // use __memcmp;
      //int in6_addr_compare(struct ::in6_addr a, struct ::in6_addr b);

      void ResolveLocal();

      const string & GetLocalHostname();

      in_addr GetLocalIP();

      const string & GetLocalAddress();

      const struct in6_addr& GetLocalIP6();

      const string & GetLocalAddress6();

      //string Sa2String(sockaddr * psa);

      //::net::address CreateAddress(sockaddr * psa, socklen_t sa_len);

      bool reverse(string & number, const string & hostname, int flags = 0);

      bool reverse(string & hostname, const ::net::address & address, int flags = 0);

      static int service_port(const ::string & strName, int ai_flags = 0);

      string service_name(int iPort, int ai_flags = 0);

      string canonical_name(const ::net::address & address);

   };

} // namespace sockets


