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
#include "aura/id.h"
#include "aura/net/sockets/_.h"
#include "aura/platform/static_start.h"
#include <openssl/ssl.h>

//extern ::mutex * g_pmutexGlobals;

namespace sockets
{

#undef TMPSIZE
#define TMPSIZE 10000


   httpd_socket::httpd_socket(base_socket_handler& h) :
      ::object(&h),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_base_socket(h),
      http_socket(h),
      m_received(0)
   {

      m_http_date = datetime2httpdate(GetDate());

   }


   httpd_socket::httpd_socket(const httpd_socket& s) :
      ::object(s.get_context_object()),
      base_socket(s),
      socket(s),
      stream_socket(s),
      tcp_socket(s),
      http_base_socket(s),
      http_socket(s)
   {

   }


   httpd_socket::~httpd_socket()
   {

   }


   void httpd_socket::Send64(const string & str64, const string & type)
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
         memory mem;
         System.base64().decode(mem, str64);
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

            INFO(log_this, "datetime2httpdate", 0, "mktime() failed");
            
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


   map < int, int, DH *, DH * > * g_pmapdh = nullptr;

   map < int, int, DH *, DH * > * dh_map()
   {

      sync_lock sl(::aura::g_pmutexGlobals);

      if (g_pmapdh == nullptr)
      {

         g_pmapdh = new map < int, int, DH *, DH * >();

      }

      return g_pmapdh;

   }


   DH * get_dh(int keylength)
   {

      sync_lock sl(::aura::g_pmutexGlobals);

      return dh_map()->operator[](keylength);

   }


   void set_dh(int keylength, DH * pdh)
   {

      sync_lock sl(::aura::g_pmutexGlobals);

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
      // %! remember to change the password to the one you used for your server key
      //InitializeContext(m_strCat, m_strCat, "", SSLv23_server_method());

      string strId = m_strCat;

      if (strId.begins_ci("cat://"))
      {

         strId = "cat://" + System.crypto().md5(strId);

      }
      InitializeContext(strId, m_strCat, "", TLS_server_method());

      string strCipherList = m_strCipherList;

      if (strCipherList.is_empty())
      {

         strCipherList = "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH";

      }

      if (strCipherList.find("DH") >= 0)
      {

         int_array ia;

         ia.add(512);
         ia.add(1024);
         ia.add(2048);
         ia.add(4096);

         for (index i = 0; i < ia.get_count(); i++)
         {

            int keylength = ia[i];

            if (get_dh(keylength) == nullptr)
            {

               string strTitle = ::file::path(m_strCat).name();

               if (strTitle.find_ci(".") >= 0)
               {

                  strTitle = strTitle.Left(strTitle.reverse_find("."));

               }

               string strFile = ::file::path(m_strCat).sibling(strTitle) + ".dh" + __str(keylength) + ".pem";

               FILE * paramfile = fopen(strFile, "r");

               if (paramfile)
               {

                  DH * pdh = PEM_read_DHparams(paramfile, nullptr, nullptr, nullptr);

                  set_dh(keylength, pdh);

                  fclose(paramfile);

               }

            }

         }

         SSL_CTX_set_tmp_dh_callback(m_psslcontext->m_pclientcontext->m_psslcontext, &tmp_dh_callback);

      }


      //int nid = OBJ_sn2nid(ECDHE_CURVE);

      if (strCipherList.find("ECDH") >= 0)
      {

         EC_KEY *ecdh = EC_KEY_new_by_curve_name(NID_secp384r1);

         SSL_CTX_set_tmp_ecdh(m_psslcontext->m_pclientcontext->m_psslcontext, ecdh);

      }

      if (strCipherList.find("DH") >= 0)
      {

         SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext) | SSL_OP_SINGLE_DH_USE | SSL_OP_CIPHER_SERVER_PREFERENCE);

      }
      else
      {

         SSL_CTX_set_options(m_psslcontext->m_pclientcontext->m_psslcontext, SSL_CTX_get_options(m_psslcontext->m_pclientcontext->m_psslcontext) | SSL_OP_CIPHER_SERVER_PREFERENCE);

      }

      SSL_CTX_set_cipher_list(m_psslcontext->m_pclientcontext->m_psslcontext, strCipherList);

   }



   bool httpd_socket::read_file(const ::file::path& pcszParam, pointer_array < int_array >* prangea, const char* pszContentType)

   {

       ::file::path pcsz(pcszParam);

       bool bMd5Request = str::ends_eat_ci(pcsz, ".md5");

      string strExtension = pcsz.extension();

      string str = strExtension;
      str.make_lower();
      string strContentType(pszContentType);

      string strName(pcsz);



      if(str::ends_ci(strName,"03 Coisa De Acender - Se..... - Djavan.mp3"))
      {
         debug_print("%s", strName.c_str());
      }

      if (bMd5Request)
      {
         outheader(__id(content_type)) = "text/plain";
      }
      else if(outheader(__id(content_type)).get_string().has_char())
      {
      }
      else if(strContentType.has_char() && strContentType.compare_ci("unknown") != 0)
      {
         outheader(__id(content_type)) = strContentType;
      }
      else
      {

         outheader(__id(content_type)) = get_file_extension_mime_type(strExtension);

      }

      //string strOrigin = inheader("origin");

      //if (!strOrigin.ends_ci("/ca2.cc") && !strOrigin.ends_ci(".ca2.cc"))
      //{

      //   strOrigin = "https://server.ca2.cc";
      //   //strOrigin = "*";

      //}

      //if(strExtension == "ttf")
      //{
      //   outheader("access-control-allow-origin") = strOrigin;
      //   //outheader("vary") = "origin";
      //}
      //else if(strExtension == "otf")
      //{
      //   outheader("access-control-allow-origin") = strOrigin;
      //   //outheader("vary") = "origin";
      //}
      //else if(strExtension == "woff")
      //{
      //   outheader("access-control-allow-origin") = strOrigin;
      //   //outheader("vary") = "origin";
      //}
      //else if (strExtension == "woff2")
      //{
      //   outheader("access-control-allow-origin") = strOrigin;
      //   //outheader("vary") = "origin";
      //}

      if(!file_exists(pcsz))

      {
         if (::dir::is(pcsz))

         {
            outattr(__id(http_status_code)) = 200;
            outattr(__id(http_status)) = "OK";
            outheader("x-fstype") = "directory";
         }
         else
         {
            outattr(__id(http_status_code)) = 404;
            outattr(__id(http_status)) = "Not Found";
         }
         return false;
      }

      outheader("x-fstype") = "file";

      if(prangea == nullptr || prangea->get_count() == 0)
      {

         if(::str::begins_ci(strContentType,"audio/"))
         {

            auto preader = Context.file().get_reader(pcsz);

            compress_context compress(this);
            
            if(!compress.ungz(response().file(), preader))
            {

               response().file()->from_begin(preader);

            }

         }
         else
         {

            if (bMd5Request)
            {

               response().print(Context.file().md5(pcsz));

               return true;

            }

            if (response().file()->get_position() == 0)
            {

               response().m_strFile = pcsz;

               outattr(__id(http_status_code)) = 200;

               outattr(__id(http_status)) = "OK";

            }
            else
            {

               auto preader = Context.file().shared_reader(pcsz);

               if (!preader)
               {

                  return false;

               }

               response().file()->from(preader);

            }

         }

      }
      else
      {

         auto preader = Context.file().shared_reader(pcsz);

         if (!preader)
         {

            return false;

         }

         auto iLen = preader->get_size();

         if(prangea->get_count() > 1)
         {
            memsize uiTotal = 0;
            memory mem;
            mem.set_size(128 * 1024 * 1024);
            for(i32 i = 0; i < prangea->get_count(); i++)
            {
               memsize iStart = prangea->element_at(i)->element_at(0);
               memsize iEnd = prangea->element_at(i)->element_at(1);
               if(iStart >= iLen)
                  continue;
               // iEnd > iLen is not verified because file may be growing
               preader->seek(iStart,::file::seek_begin);
               memsize uiRead;

               auto pfile = create_memory_file();

               memsize iPos = iStart;

               if(iEnd >= iStart)
               {
               }
               else if(iStart > 0)
               {
                  iEnd = (::memsize) (iLen - 1);
               }
               else
               {
                  continue;
               }
               response().println("--THIS_STRING_SEPARATES\r\n");
               response().println("Content-range: bytes " + __str(iStart) + "-" + __str(iEnd) + "/" + __str(iLen));
               response().println("Content-Transfer-Encoding: base64");
               while(true)
               {
                  if(iEnd >= iStart)
                  {
                     uiRead = MIN(mem.get_size(),(memsize) (iEnd - iPos + 1));
                  }
                  else
                  {
                     uiRead = mem.get_size();
                  }
                  uiRead = preader->read(mem.get_data(),uiRead);
                  uiTotal += uiRead;
                  if(uiRead == 0)
                     break;
                  pfile->write(mem.get_data(),uiRead);
                  iPos += uiRead;
                  if(iPos >= preader->get_size())
                     break;
               }
               response().println(System.base64().encode(*pfile->get_memory()));
            }
            response().println("--THIS_STRING_SEPARATES--\r\n");
            outheader(__id(content_type)) = "multipart/x-byteranges; boundary=THIS_STRING_SEPARATES";
         }
         else
         {
            memsize uiTotal = 0;
            memory mem;
            mem.set_size(128 * 1024 * 1024);
            memsize iStart = prangea->element_at(0)->element_at(0);
            memsize iEnd = prangea->element_at(0)->element_at(1);
            if(iStart < iLen)
            {
               // iEnd > iLen is not verified because file may be growing
               preader->seek(iStart,::file::seek_begin);
               memsize uiRead;
               ::memory_file memfile;
               memsize iPos = iStart;
               if(iEnd >= iStart)
               {
               }
               else if(iStart > 0)
               {
                  iEnd = (::memsize) (iLen - 1);
               }
               while(true)
               {
                  if(iEnd != -1 && iEnd >= iStart)
                  {
                     uiRead = MIN(mem.get_size(),(memsize) (iEnd - iPos + 1));
                  }
                  else
                  {
                     uiRead = mem.get_size();
                  }
                  uiRead = preader->read(mem.get_data(),uiRead);
                  uiTotal += uiRead;
                  if(uiRead == 0)
                     break;
                  response().file()->write(mem.get_data(),uiRead);
                  iPos += uiRead;
                  if(iPos >= preader->get_size())
                     break;
               }
            }
            outattr("http_status_code") = 206;
            outattr("http_status") = "Partial Content";
            if(iEnd == -1)
            {
               outheader("Content-range") = "bytes " + __str(iStart) + "-" + __str(iEnd) + "/*";
            }
            else
            {
               outheader("Content-range") = "bytes " + __str(iStart) + "-" + __str(iEnd) + "/" + __str(iLen);
            }

         }
         //      brk1:;
      }
      return true;
   }


} // namespace sockets


