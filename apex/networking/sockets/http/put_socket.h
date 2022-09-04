/** \file http_put_socket.h
**   \date  2004-10-30
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


#include "client_socket.h"


namespace sockets
{

   class base_socket_handler;

   /** Put http page.
   \ingroup http */
   class CLASS_DECL_APEX http_put_socket :
      virtual public http_client_socket
   {
   public:


      string            m_filename;
      //string            m_content_type;
      //long              m_content_length;
      file_pointer     m_file;


      http_put_socket();
      /** client constructor,
      \lparam url_in = 'http://host:port/resource' */
      http_put_socket(const string & url_in);
      ~http_put_socket();

      // these must be specified before connecting / adding to handler
      /** Set filename to send. */
      void SetFile(const string & );
      /** Set mimetype of file to send. */
      void SetContentType(const string & );

      /** http put client implemented in OnConnect */
      virtual bool step() override;

   };


} // namespace sockets


