/** \file socket.cpp
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
#include "socket.h"
#include "socket_thread.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/earth_gregorian_time.h"
#include "acme/primitive/primitive/url.h"
#include "acme/primitive/primitive/url_domain.h"
#include "acme/primitive/string/base64.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif

#if defined(FREEBSD) || defined(OPENBSD) || defined(__APPLE__)
#include <stdio.h>
#endif

#include <time.h>
//#include <openssl/ssl.h>

//extern ::pointer< ::mutex > get_globals_mutex();

namespace httpd
{

#undef TMPSIZE
#define TMPSIZE 10000


   socket::socket() :
      m_received(0)
   {

      m_http_date = datetime2httpdate(GetDate());

   }


   //socket::socket(const socket& s) :
   //   ::object(&s),
   //   base_socket(s),
   //   socket(s),
   //   stream_socket(s),
   //   tcp_socket(s),
   //   http_base_socket(s),
   //   http_socket(s)
   //{

   //}


   socket::~socket()
   {

   }



   ::pointer < ::sockets::socket_thread > socket::create_socket_thread()
   {

      if (m_typeSocketThread.is_empty())
      {

         return __create < ::sockets::socket_thread >(m_pfactorySocketThread);

      }
      else
      {

         return __id_create(m_typeSocketThread, m_pfactorySocketThread);

      }

   }



   void socket::Send64(const ::string& str64, const string& type)
   {
      //   Base64 bb;

      /*   if (request().headers()["if-modified-since"].get_string().case_insensitive_order(m_start) == 0)
         {
            m_response.attr("http_status_code") = 304;
            m_response.attr("http_status") = "Not Modified";
            SendResponse();
         }
         else*/
      {

         auto psystem = system();

         auto pbase64 = psystem->base64();

         memory mem;

         pbase64->decode(mem, str64);

         m_response.attr("http_status_code") = 200;
         m_response.attr("http_status") = "OK";

         m_response.header("Content-length") = (i64)mem.size();
         m_response.header("content-type") = type;
         //      m_response.header("Last-modified") = m_start;
         SendResponse();

         write(mem);

      }

   }


   string socket::datetime2httpdate(const string& dt)
   {
      struct tm tp;
      posix_time t;
      const char* days[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
      const char* months[] = { "Jan","Feb","Mar","Apr","May","Jun",
                               "Jul","Aug","Sep","Oct","Nov","Dec"
      };
      i32 i;
      char s[40];

      /* 1997-12-16 09:50:40 */

      if (dt.length() == 19)
      {
         tp.tm_year = atoi(dt.substr(0, 4)) - 1900;
         i = atoi(dt.substr(5, 2)) - 1;
         tp.tm_mon = i >= 0 ? i : 0;
         tp.tm_mday = atoi(dt.substr(8, 2));
         tp.tm_hour = atoi(dt.substr(11, 2));
         tp.tm_min = atoi(dt.substr(14, 2));
         tp.tm_sec = atoi(dt.substr(17, 2));
         tp.tm_wday = 0;
         tp.tm_yday = 0;
         tp.tm_isdst = 0;
         t.m_iSecond = mktime(&tp);
         if (t.m_iSecond == -1)
         {

            information() << "datetime2httpdate: mktime() failed";

         }

         sprintf(s, "%s, %02d %s %d %02d:%02d:%02d GMT",
            days[tp.tm_wday],
            tp.tm_mday,
            months[tp.tm_mon],
            tp.tm_year + 1900,
            tp.tm_hour, tp.tm_min, tp.tm_sec);
      }
      else
      {
         *s = 0;
      }
      return s;
   }


   string socket::GetDate()
   {

      ::earth::gregorian_time gregoriantime;

      auto timeNow = ::earth::time::now();

      gregoriantime.set(timeNow, ::time::local());

      char slask[40]; // yyyy-mm-dd hh:mm:ss

      sprintf(slask, "%d-%02d-%02d %02d:%02d:%02d",
         gregoriantime.m_iYear,
         gregoriantime.m_iMonth + 1,
         gregoriantime.m_iDay,
         gregoriantime.m_iHour,
         gregoriantime.m_iMinute,
         gregoriantime.m_iSecond);

      return slask;

   }


   void socket::Reset()
   {
      http_socket::Reset();
      m_received = 0;
   }


   //map < int, DH * > * g_pmapdh = nullptr;

   //map < int, DH * > * dh_map()
   //{

   //   critical_section_lock synchronouslock(::globals_critical_section());

   //   if (g_pmapdh == nullptr)
   //   {

   //      g_pmapdh = __new< map < int, DH * > >();

   //   }

   //   return g_pmapdh;

   //}


   //DH * get_dh(int keylength)
   //{

   //   critical_section_lock synchronouslock(::globals_critical_section());

   //   return dh_map()->operator[](keylength);

   //}


   //void set_dh(int keylength, DH * pdh)
   //{

   //   critical_section_lock synchronouslock(::globals_critical_section());

   //   dh_map()->operator[](keylength) = pdh;

   //}


   //DH * tmp_dh_callback(SSL *ssl, int is_export, int keylength)
   //{

   //   switch(keylength)
   //   {
   //   case 512:
   //   case 1024:
   //   case 2048:
   //   case 4096:
   //      return get_dh(keylength);
   //   }

   //   return nullptr;

   //}


   void socket::InitSSLServer()
   {

      base_socket_composite()->_001InitSSLServer();

   }


   void socket::send_response()
   {

      on_send_response();

      i32 iStatusCode;

      string strStatus;

      //auto code123 = ::__spin_namespace::idpool::g_pthis->http_status_code;

      if (outattr("http_status_code").is_new() || outattr("http_status").is_new())
      {

         if (outheaders().has_property("location"))
         {

            iStatusCode = 303; // 303 (See Other Location)

            strStatus = "See Other";

         }
         else
         {

            iStatusCode = 200;

            strStatus = "OK";

         }

         outattr("http_status_code") = iStatusCode;

         outattr("http_status") = strStatus;

      }

      outattr("http_version") = "HTTP/1.1";

      if (outheader("content-type").begins("image/"))
      {

         m_bSetCookie = false;

      }
      else if (outheader("content-type") == "application/javascript")
      {

         m_bSetCookie = false;

      }
      else if (outheader("content-type") == "text/css")
      {

         m_bSetCookie = false;

      }

      Respond();

   }


   void socket::OnExecute()
   {

      string strUrl = m_request.attr("http_protocol") + "://" + m_request.header("host") + m_request.attr("request_uri");

      //informationf("socket::OnExecute: %s", strUrl.c_str());

      string str;

      for (auto& pproperty : m_request.headers().propertyptra())
      {

         ::string strNewHeader;

         strNewHeader.formatf("{%s=%s}", pproperty->m_atom.as_string().c_str(), pproperty->as_string().c_str());

         if (str.length() + strNewHeader.length() > 80)
         {

            informationf("Headers %s", str.c_str());

            str = strNewHeader;

         }
         else
         {

            str += strNewHeader;

         }

      }

      if (str.length() > 0)
      {

         informationf("Headers %s", str.c_str());

      }

      auto tickExecuteBeg = ::time::now();

      send_response();

      auto tickExecuteEnd = ::time::now();

      debug() << "====> " << (tickExecuteEnd - tickExecuteBeg).floating_second() << "s";

   }


   void socket::OnResponseComplete()
   {

   }


   void socket::on_send_response()
   {


   }


   bool socket::http_filter_response_header(atom key, string_array& straValue)
   {

      if (key == "location" && straValue.get_count() >= 1)
      {

         auto psystem = system();

         auto purl = psystem->url();

         for (int i = 0; i < straValue.get_size(); i++)
         {

            url_domain domain;

            domain.create(purl->get_server(straValue[i]));

            if (domain.m_strName == "ca2.software")
            {

               //straValue[i] = "https://" + papp->m_strFontopusServer + purl->get_object(straValue[i]);

            }

         }

      }
      else if (!m_bSetCookie && key == "set-cookie")
      {

         return false;

      }

      return true;

   }






   //void socket::simple_image_server(const ::string & pszPath, int iMaxWidth, int iMaxHeight)
   //{

   //   if (iMaxWidth <= 0 && iMaxHeight <= 0)
   //   {
   //      simple_file_server(pszPath);
   //   }
   //   else
   //   {
   //
   //      ::image_pointer pimage;

   //      pimage->load_image(pszPath);

   //      double dRateW = 1.0;

   //      if (iMaxWidth > 0)
   //      {
   //         if (pimage->width() > iMaxWidth)
   //         {
   //            dRateW = (double)iMaxWidth / (double)pimage->width();
   //         }
   //      }

   //      double dRateH = 1.0;

   //      if (iMaxHeight > 0)
   //      {
   //         if (pimage->height() > iMaxHeight)
   //         {
   //            dRateH = (double)iMaxHeight / (double)pimage->width();
   //         }
   //      }

   //      double dRate = minimum(dRateW, dRateH);

   //      ::image_pointer pimage;

   //      pimage = create_image({(i32)(pimage->width() * dRate),  (i32)(pimage->height() * dRate)});

   //      pimage->stretch_image(pimage);

   //      ::save_image saveimage;

   //      savepimage->m_eformat = pimage::e_format_jpeg;
   //      savepimage->m_iQuality = 50;

   //      outheader("content-type") = "image/jpeg";


   //      pimage->save_to_file(&response().file(), &saveimage);

   //   }


   //}



   void socket::simple_file_server(const ::string& pszPath, bool bMatter)
   {

      pointer_array < ::i32_array > rangea;

      if (inheader("range").has_char())
      {

         string_array straItem;

         straItem.explode("=", inheader("range"));

         if (straItem.get_count() == 2)
         {

            string strUnit = straItem[0];

            string_array stra;

            stra.explode(",", straItem[1]);

            for (i32 i = 0; i < stra.get_count(); i++)
            {

               string_array straRange;

               straRange.explode("-", stra[i]);

               if (straRange.get_count() == 2)
               {

                  rangea.add(__new< ::i32_array >());

                  rangea.last_ptr()->add(atoi(straRange[0]));

                  straRange[1].trim();

                  if (ansi_len(straRange[1]) == 0)
                     rangea.last_ptr()->add(-1);
                  else
                     rangea.last_ptr()->add(atoi(straRange[1]));

               }

            }

         }

      }

      read_file(pszPath, &rangea);

   }



} // namespace sockets



