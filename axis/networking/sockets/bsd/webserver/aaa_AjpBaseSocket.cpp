/**
 **   \file AjpBaseSocket.cpp
 **   \date  2007-10-05
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2007  Anders Hedstrom

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
//#include "apex/networking/sockets/_.h"
#include "axis/net/sockets/bsd/webserver/ajp13.h"
#include "axis/net/sockets/bsd/webserver/ajp_base_socket.h"


namespace sockets
{



   AjpBaseSocket::Initializer::Initializer()
   {

      header[HTTP_REQUEST_ACCEPT] = "accept";
      header[HTTP_REQUEST_ACCEPT_CHARSET] = "accept-charset";
      header[HTTP_REQUEST_ACCEPT_ENCODING] = "accept-encoding";
      header[HTTP_REQUEST_ACCEPT_LANGUAGE] = "accept-language";
      header[HTTP_REQUEST_AUTHORIZATION] = "authorization";
      header[HTTP_REQUEST_CONNECTION] = "connection";
      header[HTTP_REQUEST_CONTENT_TYPE] = "content-type";
      header[HTTP_REQUEST_CONTENT_LENGTH] = "content-length";
      header[HTTP_REQUEST_COOKIE] = "cookie";
      header[HTTP_REQUEST_COOKIE2] = "cookie2";
      header[HTTP_REQUEST_HOST] = "host";
      header[HTTP_REQUEST_PRAGMA] = "pragma";
      header[HTTP_REQUEST_REFERER] = "referer";
      header[HTTP_REQUEST_USER_AGENT] = "::account::user-agent";

      Method[HTTP_METHOD_OPTIONS] = "OPTIONS";
      Method[HTTP_METHOD_GET] = "GET";
      Method[HTTP_METHOD_HEAD] = "HEAD";
      Method[HTTP_METHOD_POST] = "POST";
      Method[HTTP_METHOD_PUT] = "PUT";
      Method[HTTP_METHOD_DELETE] = "DELETE";
      Method[HTTP_METHOD_TRACE] = "information";
      Method[HTTP_METHOD_PROPFIND] = "PROPFIND";
      Method[HTTP_METHOD_PROPPATCH] = "PROPPATCH";
      Method[HTTP_METHOD_MKCOL] = "MKCOL";
      Method[HTTP_METHOD_COPY] = "COPY";
      Method[HTTP_METHOD_MOVE] = "MOVE";
      Method[HTTP_METHOD_LOCK] = "LOCK";
      Method[HTTP_METHOD_UNLOCK] = "UNLOCK";
      Method[HTTP_METHOD_ACL] = "ACL";
      Method[HTTP_METHOD_REPORT] = "REPORT";
      Method[HTTP_METHOD_VERSION_CONTROL] = "VERSION_CONTROL"; // with a dash "VERSION-CONTROL"
      Method[HTTP_METHOD_CHECKIN] = "CHECKIN";
      Method[HTTP_METHOD_CHECKOUT] = "CHECKOUT";
      Method[HTTP_METHOD_UNCHECKOUT] = "UNCHECKOUT";
      Method[HTTP_METHOD_SEARCH] = "SEARCH";
      Method[HTTP_METHOD_MKWORKSPACE] = "MKWORKSPACE";
      Method[HTTP_METHOD_UPDATE] = "UPDATE";
      Method[HTTP_METHOD_LABEL] = "LABEL";
      Method[HTTP_METHOD_MERGE] = "MERGE";
      Method[HTTP_METHOD_AXISLINE_CONTROL] = "AXISLINE_CONTROL";
      Method[HTTP_METHOD_MKACTIVITY] = "MKACTIVITY";

      Attribute[ATTR_CONTEXT] = "context";
      Attribute[ATTR_SERVLET_PATH] = "servlet_path";
      Attribute[ATTR_REMOTE_USER] = "remote_user";
      Attribute[ATTR_AUTH_TYPE] = "auth_type";
      Attribute[ATTR_QUERY_STRING] = "query_string";
      Attribute[ATTR_ROUTE] = "route";
      Attribute[ATTR_SSL_CERT] = "ssl_cert";
      Attribute[ATTR_SSL_CIPHER] = "ssl_cipher";
      Attribute[ATTR_SSL_SESSION] = "ssl_session";
      Attribute[ATTR_SSL_KEY_SIZE] = "ssl_key_size";
      Attribute[ATTR_SECRET] = "secret";
      Attribute[ATTR_STORED_METHOD] = "stored_method";

      ResponseHeader["content-type"] = 0xa001;
      ResponseHeader["content-language"] = 0xa002;
      ResponseHeader["content-length"] = 0xa003;
      ResponseHeader["date"] = 0xa004;
      ResponseHeader["last-modified"] = 0xa005;
      ResponseHeader["locationd"] = 0xa006;
      ResponseHeader["set-cookie"] = 0xa007;
      ResponseHeader["set-cookie2"] = 0xa008;
      ResponseHeader["servlet-engine"] = 0xa009;
      ResponseHeader["status"] = 0xa00a;
      ResponseHeader["www-authenticate"] = 0xa00b;

   }


   AjpBaseSocket::AjpBaseSocket() : 
      ::object(&h),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      m_iState(0),
      m_length(4),
      m_ptr(0)
   {

   }


   void AjpBaseSocket::OnRawData(char *buf, memsize sz)
   {

      informationf("OnRawData: %d bytes\n", sz);
      memsize ptr = 0;
      while (true)
      {
         memsize left = sz - ptr;
         informationf(" left: %d bytes\n", left);
         informationf(" state: %d\n", m_iState);
         switch (m_iState)
         {
         case 0:
            {
               memsize missing = m_length - m_ptr;
               short len = (short)(missing < left ? missing : left);
               ::memory_copy(m_message + m_ptr, buf + ptr, len);
               m_ptr += len;
               ptr += len;
               if (m_ptr < m_length)
               {
                  return; // read more
               }
               int point = 0;
               short atom = get_integer(m_message, point);
               short length = get_integer(m_message, point);
               OnHeader(atom, length);
               m_iState = 1;
               m_length = length;
               m_ptr = 0; // bytes in m_message
            }
            break;
         case 1:
            {
               memsize missing = m_length - m_ptr;
               short len = (short)(missing < left ? missing : left);
               ::memory_copy(m_message + m_ptr, buf + ptr, len);
               m_ptr += len;
               ptr += len;
               if (m_ptr < m_length)
               {
                  return; // read more
               }
               OnPacket(m_message, m_ptr);
               m_iState = 0;
               m_length = 4;
               m_ptr = 0;
            }
            break;
         }
      }
   }


   // ---------------------------------------------------------------------------
   uchar AjpBaseSocket::get_byte(const ::string &buf, int& ptr)
   {
      return (uchar)buf[ptr++];
   }


   // ---------------------------------------------------------------------------
   bool AjpBaseSocket::get_boolean(const ::string &buf, int& ptr)
   {
      return ( (uchar)buf[ptr++] & 1) == 1 ? true : false;
   }


   // ---------------------------------------------------------------------------
   short AjpBaseSocket::get_integer(const ::string &buf, int& ptr)
   {
      short n;
      ::memory_copy(&n, buf + ptr, 2);
      ptr += 2;
      return ntohs(n);
   }


   // ---------------------------------------------------------------------------
   string AjpBaseSocket::get_string(const ::string &buf, int& ptr)
   {
      short len = get_integer(buf, ptr);
      if (len != -1)
      {
         string tmp = buf + ptr;
         ptr += len;
         ptr++; // skip trailing 0x0
         tmp = tmp.left(len);
         return tmp;
      }
      return "";
   }


   // ---------------------------------------------------------------------------
   void AjpBaseSocket::put_byte(char *buf, int& ptr, uchar zz)
   {
      buf[ptr++] = zz;
   }


   // ---------------------------------------------------------------------------
   void AjpBaseSocket::put_boolean(char *buf, int& ptr, bool zz)
   {
      buf[ptr++] = zz ? 1 : 0;
   }


   // ---------------------------------------------------------------------------
   void AjpBaseSocket::put_integer(char *buf, int& ptr, short zz)
   {
      short tmp = htons(zz);
      ::memory_copy(buf + ptr, &tmp, 2);
      ptr += 2;
   }


   // ---------------------------------------------------------------------------
   void AjpBaseSocket::put_string(char *buf, int& ptr, const ::scoped_string & scopedstr)
   {
      string str(scopedstr);
      put_integer(buf, ptr, (short)str.length() );
      ::memory_copy(buf + ptr, (const ::string &) str);
      ptr += (int)str.length();
      put_byte(buf, ptr, 0);
   }


} // namespace sockets


