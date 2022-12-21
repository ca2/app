/** \file httpd_socket.h
*/
/*
Copyright (C) 2001-2007  Anders Hedstrom (grymse@alhem.net)

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


#include "apex/networking/sockets/http/http_base_socket.h"


namespace http
{
   
   class form;

}


namespace sockets
{

   /** \defgroup webserver Webserver framework */
   /** Web server socket framework.
      \ingroup webserver */
   class CLASS_DECL_APEX httpd_socket :
      virtual public http_base_socket
   {
   public:


      memsize m_received;
      string m_http_date;



      httpd_socket();
      virtual ~httpd_socket();



      //virtual bool read_file(const ::file::path & path,pointer_array < int_array > * prangea = nullptr,const ::scoped_string & scopedstrContentType = nullptr);



   //protected:
      //httpd_socket(const httpd_socket& s);
      /** Decode and send a base64-encoded string.
         \lparam str64 Base64-encoded string
         \lparam type Mime type of content (content-type header) */
      void Send64(const ::string & str64, const string & type);
      string datetime2httpdate(const string & dt);
      string GetDate();
      void Reset();

      virtual void InitSSLServer();



      


   };


} // namespace sockets



