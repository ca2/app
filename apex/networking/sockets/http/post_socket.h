/** \file http_post_socket.h
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

//#include "sockets_http_client_socket.h"

namespace sockets
{

   class CLASS_DECL_APEX multipart :
      virtual public object
   {
   public:

      class CLASS_DECL_APEX item
      {
      public:

         file_pointer      m_spfile;
         u64             m_uiContentLength;
         string               m_strContentType;

      };

      string                  m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends;
      string_map < item >     m_map;

      //multipart(::object * pobject): ::object(pobject) {}
      multipart(::object* pobject) { initialize(pobject); }
      virtual ~multipart() {}

   };

   class base_socket_handler;

   /** Generate a http post request, get response.
   \ingroup http */
   class CLASS_DECL_APEX http_post_socket :
      virtual public http_client_socket
   {
   public:


      string                                 m_boundary;
      __pointer(multipart)                   m_pmultipart;


      http_post_socket();
      /* client constructor,
      \lparam url_in = 'http://host:port/resource' */
      http_post_socket(const string & url_in);
      virtual ~http_post_socket();

      // these must be specified before connecting / adding to handler
      /** add field to post. */
      void AddField(const string & name,const string & value);
      /** add multiline field to post. */
      void AddMultilineField(const string & name, string_array & values);
      /** add file to post. */
      void AddFile(const string & name,const string & filename,const string & type);

      /** use this to post with content-type multipart/form-data.
      // when adding a file to the post, this is the default and only content-type */
      //void SetMultipart();

      /** http put client implemented in OnConnect */
      virtual void step() override;

      property_set m_fields;
      void DoMultipartPost();


   };


} // namespace sockets

