/** \file http_debug_socket.h
**   \date  2004-09-27
**/
/*
Copyright (C) 2004-2007  Anders Hedstrm (grymse@alhem.net)

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


#include "socket.h"


namespace sockets
{


   class base_socket_handler;


   /** HTTP request "echo" class. This class echoes a http request/body
   with a html formatted page.
   \ingroup http */
   class CLASS_DECL_APEX http_debug_socket :
      public http_socket
   {
   public:


      memsize         m_content_length;
      memsize     m_read_ptr;


      http_debug_socket();
      ~http_debug_socket();

      void Init();

      void OnFirst();
      void OnHeader(atom key, const string & value);
      void OnHeaderComplete();
      void OnData(const char *,memsize);
      void OnDataComplete();

   };


} // namespace sockets


