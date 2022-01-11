#include "framework.h"
#include "apex/id.h"
#include "apex/networking/sockets/_sockets.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"


namespace sockets
{


   http_base_socket::http_base_socket() 
      //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h)
   {


   }


   http_base_socket::http_base_socket(const http_base_socket& s) //:
      //::object(&s),
      //base_socket(s),
      //socket(s),
      //stream_socket(s),
      //tcp_socket(s),
      //http_socket(s)
   {


   }


   http_base_socket::~http_base_socket()
   {


   }


   void http_base_socket::OnFirst()
   {
      
      m_iContentLength = 0;

   }


   void http_base_socket::OnHeader(id key, const string & value)
   {

      http_socket::OnHeader(key, value);

      if(key == __id(content_length))
      {
         m_iContentLength = atoi(value);
      }

   }


   void http_base_socket::OnHeaderComplete()
   {

      string strProtocol = m_request.attr("http_protocol").string().c_str();

      string strHost;
      
      strHost = m_request.header("host");

      if (::str::ends_eat_ci(strHost, ".test.ca2.software"))
      {

         m_request.header("host") = strHost + ".ca2.software";

      }
      else if (strHost == "test.ca2.software")
      {

         m_request.header("host") = "ca2.software";

      }

      string strRequestUri = m_request.attr("request_uri").string();

      http_socket::OnHeaderComplete();

      INFORMATION(strProtocol << "://" << strHost << strRequestUri);

      string strTest(strHost);

      if (::str::ends_eat_ci(strTest, ".ca2.software"))
      {

         if (strTest.find('.') > 0)
         {

            output_debug_string("!!!!!!!!!! -> " + strTest + "\n");

         }

      }

      if(m_request.attr("request_uri").string().find("/passthrough/") >= 0)
      {
         
         INFORMATION("Passthrough");

      }

      if(m_request.headers().has_property(__id(user_agent)))
      {

         INFORMATION("user-agent: " << m_request.header(__id(user_agent)).get_string());

      }
      else
      {

         INFORMATION("user-agent: ():[" << m_addressRemote.get_string() << "]");

      }

      if(m_request.headers().has_property(__id(from)))
      {

         INFORMATION("from: " + m_request.header(__id(from)).get_string());

      }

      if(m_request.headers().has_property(__id(accept_language)))
      {

         FORMATTED_INFORMATION("accept-language: %s", m_request.header(__id(accept_language)).string().c_str());

      }

      m_request.InitBody(m_body_size_left);

   }


   void http_base_socket::OnData(const char *buf,memsize sz)
   {

      m_request.write( buf, sz );

   }

   void http_base_socket::OnDataComplete()
   {

      m_request.CloseBody();

      Execute();

   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Execute()
   {
      // parse form data / query_string and cookie header if available
      m_request.ParseBody();

      //FORMATTED_TRACE("http version: %s\n", m_request.attr("http_version").string());
      //FORMATTED_TRACE("connection: %s\n", m_request.header("connection").string());
      //FORMATTED_TRACE("keepalive: %s\n", m_b_keepalive ? "true" : "false");
      /*   if(::str::ends(m_request.attr("http_version").string(), "/1.1")
            && m_request.header("connection").string().compare_ci("close") != 0)
         {
            m_b_keepalive = true;
         TRACE(" ***    keepalive: true\n");
         }
         else
         {
            m_b_keepalive = false;
            TRACE(" *** keepalive: false\n");
         }*/

      // prepare page
      OnExecute();

      Reset();
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Respond()
   {

      //TRACE0("http_base_socket::Respond");

      if(outheader(__id(content_type)).string().find("text") >= 0
            || outheader(__id(content_type)).string().find("javascript") >= 0)
      {

         on_compress();

      }

      if (response().m_strFile.has_char())
      {

         response().m_propertysetHeader[__id(content_length)] = m_psystem->m_pacmefile->get_size(response().m_strFile);

      }
      else
      {

         m_response.m_propertysetHeader.set_at(__id(content_length), (i64)m_response.file()->get_size());

      }

      //for(i32 i = 0; i < m_response.cookies().get_size(); i++)
      //{

      //   m_response.m_propertysetHeader.set_at(__id(set_cookie), m_response.cookies().element_at(i)->get_cookie_string());

      //}

      /*

            if(m_response.m_propertysetHeader.has_property(__id(locationd)))
            {

               string strLocation = m_response.m_propertysetHeader.lowprop(__id(Location));

               m_response.m_propertysetHeader.erase_by_name("Location");

               m_response.m_propertysetHeader["Location"] = strLocation;

            }

      */

      SendResponse();

      if(m_obuf_top == nullptr)
      {
         OnWriteComplete();
      }

      response().file()->set_size(0);
   }


   void http_base_socket::OnWriteComplete()
   {
      //Debug deb("http_base_socket::OnTransferLimit");
      //TRACE("\n");
      //TRACE("http_base_socket::OnTransferLimit\n");
      //   char msg[32768];
      OnResponseComplete();
      if (!m_b_keepalive)
      {
         //TRACE("SetCloseAndDelete\n");
         SetCloseAndDelete();
      }
      else
      {
         //TRACE("keep_alive\n");
      }
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Reset()
   {

      http_socket::Reset();

      m_body_size_left = 0;

      m_body_size_downloaded = 0;

   }


   void http_base_socket::OnExecute()
   {

   }


   void http_base_socket::OnResponseComplete()
   {

   }



   //string http_base_socket::set_cookie(
   //const char * name,
   //::payload payload,
   //i32 iExpire,
   //const char * path,
   //const char * domain,
   //bool bSecure)
   //{
   //   m_request.cookies().set_cookie(
   //   name,
   //   ::payload,
   //   iExpire,
   //   path,
   //   domain,
   //   bSecure);
   //   return m_response.cookies().set_cookie(
   //          name,
   //          ::payload,
   //          iExpire,
   //          path,
   //          domain,
   //          bSecure);
   //}

   void http_base_socket::on_compress()
   {

      if(inheader("accept-encoding").string().find("gzip") >= 0)
      {

         string str = outheader(__id(content_type)).string();

         if (str.find_ci("text") >= 0 || str.find_ci("javascript") >= 0)
         {

            m_response.m_propertysetHeader.set_at(__id(content_encoding), "gzip");

            auto pfile = create_memory_file();

            if (response().m_strFile.has_char())
            {

               m_psystem->compress(pfile, m_pcontext->m_papexcontext->file().get_reader(response().m_strFile), "zlib");

               response().m_strFile.Empty();

            }
            else
            {

               response().file()->seek_to_begin();

               m_psystem->compress(pfile, response().file(), "zlib");

            }

            response().file()->from_begin(pfile);

         }

      }

   }


   bool http_base_socket::read_file(const ::file::path& pcszParam, pointer_array < int_array >* prangea, const char* pszContentType)
   {

      ::file::path pcsz(pcszParam);

      bool bMd5Request = str::ends_eat_ci(pcsz, ".md5");

      string strExtension = pcsz.final_extension();

      string str = strExtension;
      str.make_lower();
      string strContentType(pszContentType);

      string strName(pcsz);



      if (str::ends_ci(strName, "03 Coisa De Acender - Se..... - Djavan.mp3"))
      {
         debug_print("%s", strName.c_str());
      }

      if (bMd5Request)
      {
         outheader(__id(content_type)) = "text/plain";
      }
      else if (outheader(__id(content_type)).string().has_char())
      {
      }
      else if (strContentType.has_char() && strContentType.compare_ci("unknown") != 0)
      {
         outheader(__id(content_type)) = strContentType;
      }
      else
      {

         outheader(__id(content_type)) = get_file_extension_mime_type(strExtension);

      }

      string strReferer;
      
      strReferer = inheader("referer");

      string strServer = m_psystem->url()->get_server(strReferer);

      string_array straAllowedOrigin;

      straAllowedOrigin.add("ca2.software");
      straAllowedOrigin.add("camilothomas.com");

      bool bAllowedOrigin = false;

      for (auto& strAllowedOrigin : straAllowedOrigin)
      {

         if (strServer.ends_ci("." + strAllowedOrigin) || strServer.compare_ci(strAllowedOrigin) == 0)
         {

            bAllowedOrigin = true;
            break;

         }

      }

      if (bAllowedOrigin)
      {

         string strOrigin = strServer;

         if (strExtension == "ttf")
         {
            
            outheader("access-control-allow-origin") = strOrigin;
            
            outheader("vary") = "origin";

         }
         else if (strExtension == "otf")
         {
            
            outheader("access-control-allow-origin") = strOrigin;
            
            outheader("vary") = "origin";

         }
         else if (strExtension == "woff")
         {
            
            outheader("access-control-allow-origin") = strOrigin;
            
            outheader("vary") = "origin";

         }
         else if (strExtension == "woff2")
         {
            
            outheader("access-control-allow-origin") = strOrigin;
            
            outheader("vary") = "origin";

         }

      }

      if (!m_psystem->m_pacmefile->exists(pcsz))
      {

         if (m_psystem->m_pacmedir->is(pcsz))
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

      if (prangea == nullptr || prangea->get_count() == 0)
      {

         if (::str::begins_ci(strContentType, "audio/"))
         {

            auto preader = m_pcontext->m_papexcontext->file().get_reader(pcsz);

            if (!m_psystem->uncompress(response().file(), preader, "zlib"))
            {

               response().file()->from_begin(preader);

            }

         }
         else
         {

            if (bMd5Request)
            {

               response().print(m_pcontext->m_papexcontext->file().md5(pcsz));

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

               auto preader = m_pcontext->m_papexcontext->file().shared_reader(pcsz);

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

         auto preader = m_pcontext->m_papexcontext->file().shared_reader(pcsz);

         if (!preader)
         {

            return false;

         }

         auto iLen = preader->get_size();

         if (prangea->get_count() > 1)
         {
            
            memsize uTotal = 0;
            
            memory mem;
            
            mem.set_size(128 * 1024 * 1024);

            for (i32 i = 0; i < prangea->get_count(); i++)
            {
               
               memsize iStart = prangea->element_at(i)->element_at(0);
               
               memsize iEnd = prangea->element_at(i)->element_at(1);

               if (iStart >= iLen)
               {

                  continue;

               }
               
               // iEnd > iLen is not verified because file may be growing
               preader->set_position(iStart);

               memsize uRead;

               auto pfile = create_memory_file();

               memsize iPos = iStart;

               if (iEnd >= iStart)
               {

               }
               else if (iStart > 0)
               {
                  
                  iEnd = (::memsize) (iLen - 1);

               }
               else
               {
                  
                  continue;

               }
               
               response().println("--THIS_STRING_SEPARATES\r\n");
               
               response().println("Content-range: bytes " + __string(iStart) + "-" + __string(iEnd) + "/" + __string(iLen));
               
               response().println("Content-Transfer-Encoding: base64");

               while (true)
               {

                  if (iEnd >= iStart)
                  {
                     uRead = minimum(mem.get_size(), (memsize)(iEnd - iPos + 1));
                  }
                  else
                  {
                     uRead = mem.get_size();
                  }
                  uRead = preader->read(mem.get_data(), uRead);
                  uTotal += uRead;
                  if (uRead == 0)
                     break;
                  pfile->write(mem.get_data(), uRead);
                  iPos += uRead;
                  if (iPos >= preader->get_size())
                     break;
               }

               auto psystem = m_psystem;

               auto pbase64 = psystem->base64();
               
               response().println(pbase64->encode(*pfile->get_memory()));

            }
            
            response().println("--THIS_STRING_SEPARATES--\r\n");
            
            outheader(__id(content_type)) = "multipart/x-byteranges; boundary=THIS_STRING_SEPARATES";

         }
         else
         {
            
            memsize uTotal = 0;
            
            memory mem;
            
            mem.set_size(128 * 1024 * 1024);
            
            memsize iStart = prangea->element_at(0)->element_at(0);
            
            memsize iEnd = prangea->element_at(0)->element_at(1);

            if (iStart < iLen)
            {
               
               // iEnd > iLen is not verified because file may be growing
               preader->set_position(iStart);
               
               memsize uRead;

               ::memory_file memfile;
               
               memsize iPos = iStart;
               
               if (iEnd >= iStart)
               {

               }
               else if (iStart > 0)
               {
                  
                  iEnd = (::memsize) (iLen - 1);

               }

               while (true)
               {

                  if (iEnd != -1 && iEnd >= iStart)
                  {

                     uRead = minimum(mem.get_size(), (memsize)(iEnd - iPos + 1));

                  }
                  else
                  {
                     
                     uRead = mem.get_size();

                  }
                  
                  uRead = preader->read(mem.get_data(), uRead);
                  
                  uTotal += uRead;

                  if (uRead == 0)
                  {

                     break;

                  }
                  
                  response().file()->write(mem.get_data(), uRead);
                  
                  iPos += uRead;

                  if (iPos >= preader->get_size())
                  {

                     break;

                  }

               }

            }

            outattr("http_status_code") = 206;

            outattr("http_status") = "Partial Content";

            if (iEnd == -1)
            {
               
               outheader("Content-range") = "bytes " + __string(iStart) + "-" + __string(iEnd) + "/*";

            }
            else
            {

               outheader("Content-range") = "bytes " + __string(iStart) + "-" + __string(iEnd) + "/" + __string(iLen);

            }

         }
         
      }

      return true;

   }


   bool http_base_socket::read_text_file_for_linux(const ::payload& payloadFile)
   {

      ::memory memory;

      string str;

      string_array stra;

      m_pcontext->m_papexcontext->file().get_lines(stra, payloadFile);

      str = stra.implode("\n");

      memory.assign(str.c_str(), str.length());

      dump_memory(memory);

      return true;

   }


   bool http_base_socket::dump_memory(const ::block& block)
   {

      response().file()->write(block);

      return true;

   }


} // namespace sockets



