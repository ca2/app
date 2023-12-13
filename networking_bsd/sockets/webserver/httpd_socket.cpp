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
//#include "apex/networking/sockets/_sockets.h"
//#include "apex/platform/static_start.h"
#include "acme/primitive/string/base64.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#include <openssl/ssl.h>

//extern ::pointer< ::mutex > get_globals_mutex();

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

         m_response.header("Content-length") = (i64) mem.get_size();
         m_response.header("content-type") = type;
         //      m_response.header("Last-modified") = m_start;
         SendResponse();

         write((char *)mem.get_data(), (i32) mem.get_size());
      }
   }


   string httpd_socket::datetime2httpdate(const string & dt)
   {
      struct tm tp;
      posix_time t;
      const char *days[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
      const char *months[] = { "Jan","Feb","Mar","Apr","May","Jun",
                               "Jul","Aug","Sep","Oct","Nov","Dec"
                             };
      i32 i;
      char s[40];

      /* 1997-12-16 09:50:40 */

      if (dt.get_length() == 19)
      {
         tp.tm_year = atoi(dt.substr(0,4)) - 1900;
         i = atoi(dt.substr(5,2)) - 1;
         tp.tm_mon = i >= 0 ? i : 0;
         tp.tm_mday = atoi(dt.substr(8,2));
         tp.tm_hour = atoi(dt.substr(11,2));
         tp.tm_min = atoi(dt.substr(14,2));
         tp.tm_sec = atoi(dt.substr(17,2));
         tp.tm_wday = 0;
         tp.tm_yday = 0;
         tp.tm_isdst = 0;
         t = mktime(&tp);
         if (t == -1)
         {

            information() << "datetime2httpdate: mktime() failed";
            
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
      posix_time t = time(nullptr);
      struct tm tp;
#ifdef _WIN32
      ::memory_copy(&tp, localtime(&t), sizeof(tp));
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

      synchronous_lock synchronouslock(::globals_critical_section());

      if (g_pmapdh == nullptr)
      {

         g_pmapdh = __new< map < int, DH * > >();

      }

      return g_pmapdh;

   }


   DH * get_dh(int keylength)
   {

      synchronous_lock synchronouslock(::globals_critical_section());

      return dh_map()->operator[](keylength);

   }


   void set_dh(int keylength, DH * pdh)
   {

      synchronous_lock synchronouslock(::globals_critical_section());

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
      // here's the server.pem file we just created above
      // %! remember to machine the password to the one you used for your server key
      //InitializeContext(m_strCat, m_strCat, "", SSLv23_server_method());

      string strId = m_strCat;

      auto psystem = system()->m_papexsystem;

      if (strId.case_insensitive_begins("cat://"))
      {

         auto pcrypto = psystem->crypto();

         strId = "cat://" + psystem->crypto()->md5(strId);

      }
      InitializeContext(strId, m_strCat, "", TLS_server_method());

      string strCipherList = m_strCipherList;

      if (strCipherList.is_empty())
      {

         strCipherList = "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH";

      }

      //if (strCipherList.find("DH") >= 0)
      //{

      //   ::i32_array ia;

      //   ia.add(512);
      //   ia.add(1024);
      //   ia.add(2048);
      //   ia.add(4096);

      //   for (index i = 0; i < ia.get_count(); i++)
      //   {

      //      int keylength = ia[i];

      //      if (get_dh(keylength) == nullptr)
      //      {

      //         string strTitle = ::file::path(m_strCat).name();

      //         if (strTitle.case_insensitive_find(".") >= 0)
      //         {

      //            strTitle = strTitle.left(strTitle.rear_find("."));

      //         }

      //         string strFile = ::file::path(m_strCat).sibling(strTitle) + ".dh" + as_string(keylength) + ".pem";

      //         FILE * paramfile = fopen(strFile, "r");

      //         if (paramfile)
      //         {

      //            DH * pdh = PEM_read_DHparams(paramfile, nullptr, nullptr, nullptr);

      //            set_dh(keylength, pdh);

      //            fclose(paramfile);

      //         }

      //      }

      //   }

      //   SSL_CTX_set_tmp_dh_callback(m_psslcontext->m_pclientcontext->m_psslcontext, &tmp_dh_callback);

      //}


      //int nid = OBJ_sn2nid(ECDHE_CURVE);

      if (strCipherList.find("ECDH") >= 0)
      {

         //EVP_PKEY_CTX_new_from_name(nullptr, )

         //EC_KEY *ecdh = EC_KEY_new_by_curve_name(NID_secp384r1);

         //SSL_CTX_set_tmp_ecdh(m_psslcontext->m_pclientcontext->m_psslcontext, ecdh);

         i32_array iaCurves;
         //int* curves_new;
         char* cs = NULL;
         //char* p, * q;
         int rv = -1;
         //int nid;


#define TLS_ECDHE_CURVES	"X25519,P-256,P-384"
         //const char* curves = NID_secp384r1;

         //free(config->ecdhecurves);
         //config->ecdhecurves = NULL;
         //config->ecdhecurves_len = 0;

         //if (curves == NULL || strcasecmp(curves, "default") == 0)
         //   curves = TLS_ECDHE_CURVES;

         iaCurves.add(NID_X25519);
         iaCurves.add(NID_secp256k1);
         iaCurves.add(NID_secp384r1);
         // iaCurves.add(NID_secp521r1);

         if (!SSL_CTX_set1_groups(m_psslcontext->m_pclientcontext->m_psslcontext, iaCurves.get_data(), (long) iaCurves.get_size()))
         {
         
            warning() <<"failed to set ecdhe curves";

         }

      }

      //if (strCipherList.find("DH") >= 0)
      //{

      //   SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext) | SSL_OP_SINGLE_DH_USE | SSL_OP_CIPHER_SERVER_PREFERENCE);

      //}
      //else
      {

         SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext) | SSL_OP_CIPHER_SERVER_PREFERENCE);

      }

      if (!SSL_CTX_set_cipher_list(m_psslcontext->m_pclientcontext->m_psslcontext, strCipherList))
      {

         warning() <<"failed to set cipher_list";

      }

   }




} // namespace sockets


