#include "framework.h"
#include "simpledb_socket.h"
#include "simpledb_socket_thread.h"





namespace simpledb
{


   socket::socket() :
      object(h.get_app()),
      base_socket(h),
      ::sockets::socket(h),
      stream_socket(h),
      tcp_socket(h),
#ifdef BSD_STYLE_SOCKETS
      http_base_socket(h),
      http_socket(h),
#endif
      httpd_socket(h)
   {
      /*m_strHead += "HTTP/1.1 200 OK\n";
      m_strHead += "Server: netnode/1.0 (Windows)\n";
      m_strHead += "Accept-Ranges: bytes\n";
      m_strHead += "Date: Mon, 23 May 2005 22:38:34 GMT\n";
      m_strHead += "Server: netnode/1.0 (Windows)\n";
      m_strHead += "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n";
      //m_memfileSend += "Etag: "3f80f-1b6-3e1cb03b"";
      m_strHead += "Accept-Ranges: bytes\n";
      // m_memfileSend += "Content-Length: 438";
      //m_strHead += "Connection: close\n";*/

      /*   m_memfileBody << "<html>\n";
         m_memfileBody << "<head>\n";
         m_memfileBody << "</head>\n";
         m_memfileBody << "<body>\n";
         m_memfileBody << "</body>\n";
         m_memfileBody.Truncate(0);*/
   }

   socket::~socket()
   {
   }


   void socket::send_response()
   {

      if(::str::begins(inattr("request_uri"),astr.PassthroughUri))
      {
      }
      else
      {

         http::response res(this);

         string strUri(inattr("request_uri"));
         string strHost(inheader("host"));
         string strScript = purl->object_get_script(strUri);
         if(strUri.find("thesecret") >= 0)
         {
            //      debug_break();
         }
         if(strHost == "aura.am")
         {
            TRACE("simpledb::socket::send_response aura.am");
//            u32 dw= ::duration::now();
            //  debug_break();
         }
         if(strScript == "songs")
         {
            TRACE("simpledb::socket::send_response songs");
            //u32 dw= ::duration::now();
         }
         manager().handle(this);
      }
      if(!outheaders().has_property("content-type") && response().file().get_length() > 0)
      {
         outheader(__id(content_type)) = "text/html; charset=UTF-8";
      }
      i32 iStatusCode;
      string strStatus;
      if(outattr("http_status_code").is_new()
            || outattr("http_status").is_new())
      {
         if(outheader("location").is_set())
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
      Respond();
   }



   class manager & socket::manager()
   {
      return *dynamic_cast < ::simpledb::socket_thread & > (socket_handler()).m_pservice->m_pmanager;
   }


   void socket::OnExecute()
   {
      send_response();
   }

   void socket::OnResponseComplete()
   {
   }

   /*
   bool socket::http_filter_response_header(atom key, string & strValue)
   {
      if(strKey.compare_ci("Location") == 0)
      {
         url_domain domain;
         domain.create(purl->get_server(strValue));
         if(domain.m_strRadix == "ca2open")
         {
            strValue = "https://" + papp->m_strFontopusServer + purl->get_object(strValue);
         }
         else if(domain.m_strName == "account.ca2.software" && purl->get_protocol(strValue) == "https")
         {
            strValue = "https://" + papp->m_strFontopusServer + purl->get_object(strValue);
         }
      }
      strValue.trim();
      if(strValue.is_empty())
         return false;
      return true;
   }
   */

   void socket::OnSSLAccept()
   {
      m_strCat = psystem->m_psimpledb->db().data_load(nullptr, "netnodec." + GetLocalAddress().get_display_number());
      ::sockets::httpd_socket::OnSSLAccept();
   }

   void socket::simple_file_server(const ::file::path & psz, const ::string & pszRelative)
   {
      pointer_array < int_array > rangea;
      if(strlen(inheader("range")) > 0)
      {
         string_array straItem;
         straItem.explode("=", inheader("range"));
         if(straItem.get_count() == 2)
         {
            string strUnit = straItem[0];
            string_array stra;
            stra.explode(",", straItem[1]);
            for(i32 i = 0; i < stra.get_count(); i++)
            {
               string_array straRange;
               straRange.explode("-", stra[i]);
               if(straRange.get_count() == 2)
               {
                  rangea.add(new int_array());
                  rangea.last_pointer()->add(atoi(straRange[0]));
                  straRange[1].trim();
                  if(strlen(straRange[1]) == 0)
                     rangea.last_pointer()->add(-1);
                  else
                     rangea.last_pointer()->add(atoi(straRange[1]));
               }
            }
         }
      }
      string strRelative;
      if(pszRelative != nullptr)
      {
         strRelative = string(pszRelative);
      }
      else
      {
         strRelative = purl->url_decode(purl->get_script(inattr("request_uri")));
      }
      string strPath;
      strPath = psz / strRelative;
      read_file(strPath, &rangea);
   }


   bool socket::read_file(const ::file::path & lpcsz,pointer_array < int_array > * prangea, const ::string & pszContentType)
   {
      string strExtension = lpcsz.extension();
      string str = strExtension;
      str.make_lower();
      string strContentType(pszContentType);
      if(strContentType.has_char() && strContentType.compare_ci("unknown") != 0)
      {
         outheader(__id(content_type)) = strContentType;
      }
      else if(str == "mp3")
      {
         outheader(__id(content_type)) = "audio/mpeg";
      }
      else if(str == "exe")
      {
         outheader(__id(content_type)) = "application/x-msdownload";
      }
      else if(str == "spa")
      {
         outheader(__id(content_type)) = "application/x-spa";
      }
      else if(str == "mid")
      {
         outheader(__id(content_type)) = "audio/midi";
      }
      else if(str == "js")
      {
         outheader(__id(content_type)) = "text/javascript";
      }
      else if(str == "xpi")
      {
         outheader(__id(content_type)) = "application/x-xpinstall";
      }
      else if(str == "ttf")
      {
         outheader(__id(content_type)) = "font/ttf";
      }
      else if(str == "ogv")
      {
         outheader(__id(content_type)) = "video/ogg";
      }
      else if(str == "zip")
      {
         outheader(__id(content_type)) = "application/x-zip-compressed";
      }
      else if(str == "jar")
      {
         outheader(__id(content_type)) = "application/x-jar";
      }
      file_pointer spfile(e_create);
      if(spfile->open(lpcsz, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none).failed())
      {
         return false;
      }
      if(prangea == nullptr || prangea->get_count() == 0)
      {
         stream is(spfile);
         stream os(&response().file());
         os.transfer_from(is);
      }
      else
      {
         i32 iLen = pcontext->m_papexcontext->file().length(lpcsz);
         if(prangea->get_count() > 1)
         {
            memsize uTotal = 0;
            memory mem;
            mem.set_size(128 * 1024 * 1024);
            for(i32 i = 0; i < prangea->get_count(); i++)
            {
               memsize  iStart = prangea->element_at(i)->element_at(0);
               memsize  iEnd = prangea->element_at(i)->element_at(1);
               if(iStart >= natural(iLen))
                  continue;
               // iEnd > iLen is not verified because file may be growing
               spfile->seek(iStart, ::e_seek_set);
               memsize uRead;
               ::memory_file memfile(this);
               memsize iPos = iStart;
               if(iEnd >= iStart)
               {
               }
               else if(iStart > 0)
               {
                  iEnd = iLen - 1;
               }
               else
               {
                  continue;
               }
               response().ostream() << "--THIS_STRING_SEPARATES\r\n\r\n";
               response().ostream() << "Content-range: bytes " + __string(iStart) + "-" + __string(iEnd) + "/" + __string(iLen) + "\r\n";
               response().ostream() << "Content-Transfer-Encoding: base64";
               response().ostream() << "\r\n";
               while(true)
               {
                  if(iEnd >= iStart)
                  {
                     uRead = minimum(mem.get_size(), (memsize) (iEnd - iPos + 1));
                  }
                  else
                  {
                     uRead = mem.get_size();
                  }
                  uRead = spfile->read(mem.get_data(), uRead);
                  uTotal += uRead;
                  if(uRead == 0)
                     break;
                  memfile.write(mem.get_data(), uRead);
                  iPos += uRead;
                  if(iPos >= spfile->get_length())
                     break;
               }
               response().ostream() << pbase64->encode(*memfile.get_memory());
            }
            response().ostream() << "--THIS_STRING_SEPARATES--\r\n\r\n";
            outheader(__id(content_type)) = "multipart/x-byteranges; boundary=THIS_STRING_SEPARATES";
         }
         else
         {
            memsize uTotal = 0;
            memory mem;
            mem.set_size(128 * 1024 * 1024);
            memsize iStart = prangea->element_at(0)->element_at(0);
            memsize iEnd = prangea->element_at(0)->element_at(1);
            if(iStart < natural(iLen))
            {
               // iEnd > iLen is not verified because file may be growing
               spfile->seek(iStart, ::e_seek_set);
               memsize uRead;
               ::memory_file memfile(this);
               memsize iPos = iStart;
               if(iEnd >= iStart)
               {
               }
               else if(iStart > 0)
               {
                  iEnd = iLen - 1;
               }
               while(true)
               {
                  if(iEnd != -1 && iEnd >= iStart)
                  {
                     uRead = minimum(mem.get_size(), (iEnd - iPos + 1));
                  }
                  else
                  {
                     uRead = mem.get_size();
                  }
                  uRead = spfile->read(mem.get_data(), uRead);
                  uTotal += uRead;
                  if(uRead == 0)
                     break;
                  response().file().write(mem.get_data(), uRead);
                  iPos += uRead;
                  if(iPos >= spfile->get_length())
                     break;
               }
            }
            outattr("http_status_code") = 206;
            outattr("http_status") = "Partial Content";
            if(iEnd == -1)
            {
               outheader("Content-range") = "bytes " + __string(iStart) + "-" + __string(iEnd) + "/*";
            }
            else
            {
               outheader("Content-range") = "bytes " + __string(iStart) + "-" + __string(iEnd) + "/" + __string(iLen);
            }

         }
//         brk1:;
      }
      return true;
   }


} // namespace simpledb






