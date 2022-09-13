/** \file httpd_socket.cpp
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
#include "framework.h"
#include "apex/id.h"
#include "httpd_socket.h"

#include "acme/primitive/string/base64.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#include <openssl/ssl.h>

//extern ::mutex * get_globals_mutex();

namespace sockets
{

#undef TMPSIZE
#define TMPSIZE 10000


   httpd_socket::httpd_socket() :
      m_received(0)
   {

      m_http_date = datetime2httpdate(GetDate());

   }


   //httpd_socket::httpd_socket(const httpd_socket& s) :
   //   ::object(&s),
   //   base_socket(s),
   //   socket(s),
   //   stream_socket(s),
   //   tcp_socket(s),
   //   http_base_socket(s),
   //   http_socket(s)
   //{

   //}


   httpd_socket::~httpd_socket()
   {

   }


   void httpd_socket::Send64(const ::string & str64, const string & type)
   {
      //   Base64 bb;

      /*   if (request().headers()["if-modified-since"].get_string().compare_ci(m_start) == 0)
         {
            m_response.attr("http_status_code") = 304;
            m_response.attr("http_status") = "Not Modified";
            SendResponse();
         }
         else*/
      {

         auto psystem = m_psystem;

         auto pbase64 = psystem->base64();

         memory mem;

         pbase64->decode(mem, str64);

         m_response.attr("http_status_code") = 200;
         m_response.attr("http_status") = "OK";

         m_response.header("Content-length") = (i64) mem.get_size();
         m_response.header(__id(content_type)) = type;
         //      m_response.header("Last-modified") = m_start;
         SendResponse();

         write((char *)mem.get_data(), (i32) mem.get_size());
      }
   }


   string httpd_socket::datetime2httpdate(const string & dt)
   {
      struct tm tp;
      time_t t;
      const char *days[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
      const char *months[] = { "Jan","Feb","Mar","Apr","May","Jun",
                               "Jul","Aug","Sep","Oct","Nov","Dec"
                             };
      i32 i;
      char s[40];

      /* 1997-12-16 09:50:40 */

      if (dt.get_length() == 19)
      {
         tp.tm_year = atoi(dt.Mid(0,4)) - 1900;
         i = atoi(dt.Mid(5,2)) - 1;
         tp.tm_mon = i >= 0 ? i : 0;
         tp.tm_mday = atoi(dt.Mid(8,2));
         tp.tm_hour = atoi(dt.Mid(11,2));
         tp.tm_min = atoi(dt.Mid(14,2));
         tp.tm_sec = atoi(dt.Mid(17,2));
         tp.tm_wday = 0;
         tp.tm_yday = 0;
         tp.tm_isdst = 0;
         t = mktime(&tp);
         if (t == -1)
         {

            INFORMATION("datetime2httpdate: mktime() failed");
            
         }

         sprintf(s,"%s, %02d %s %d %02d:%02d:%02d GMT",
                 days[tp.tm_wday],
                 tp.tm_mday,
                 months[tp.tm_mon],
                 tp.tm_year + 1900,
                 tp.tm_hour,tp.tm_min,tp.tm_sec);
      }
      else
      {
         *s = 0;
      }
      return s;
   }


   string httpd_socket::GetDate()
   {
      time_t t = time(nullptr);
      struct tm tp;
#ifdef _WIN32
      ::memcpy_dup(&tp, localtime(&t), sizeof(tp));
#else
      localtime_r(&t, &tp);
#endif
      char slask[40]; // yyyy-mm-dd hh:mm:ss
      sprintf(slask,"%d-%02d-%02d %02d:%02d:%02d",
              tp.tm_year + 1900,
              tp.tm_mon + 1,
              tp.tm_mday,
              tp.tm_hour,tp.tm_min,tp.tm_sec);
      return slask;
   }


   void httpd_socket::Reset()
   {
      http_socket::Reset();
      m_received = 0;
   }


   map < int, DH * > * g_pmapdh = nullptr;

   map < int, DH * > * dh_map()
   {

      synchronous_lock synchronouslock(::get_globals_mutex());

      if (g_pmapdh == nullptr)
      {

         g_pmapdh = new map < int, DH * >();

      }

      return g_pmapdh;

   }


   DH * get_dh(int keylength)
   {

      synchronous_lock synchronouslock(::get_globals_mutex());

      return dh_map()->operator[](keylength);

   }


   void set_dh(int keylength, DH * pdh)
   {

      synchronous_lock synchronouslock(::get_globals_mutex());

      dh_map()->operator[](keylength) = pdh;

   }


   DH * tmp_dh_callback(SSL *ssl, int is_export, int keylength)
   {

      switch(keylength)
      {
      case 512:
      case 1024:
      case 2048:
      case 4096:
         return get_dh(keylength);
      }

      return nullptr;

   }


   void httpd_socket::InitSSLServer()
   {

      base_socket_composite()->_001InitSSLServer();

   }




} // namespace sockets


