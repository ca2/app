#include "framework.h"
#include "base_socket.h"
#include "apex/constant/idpool.h"
//#include "apex/networking/sockets/_sockets.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/system.h"
#include "acme/primitive/string/base64.h"
#include "acme/filesystem/file/memory_file.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


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


   void http_base_socket::OnHeader(atom key, const string & value)
   {

      http_socket::OnHeader(key, value);

      if(key == "content-length")
      {
         m_iContentLength = atoi(value);
      }

   }


   void http_base_socket::OnHeaderComplete()
   {

      string strProtocol = m_request.attr("http_protocol");

      string strHost;
      
      strHost = m_request.header("host");

      if (strHost.case_insensitive_ends_eat(".test.ca2.software"))
      {

         m_request.header("host") = strHost + ".ca2.software";

      }
      else if (strHost == "test.ca2.software")
      {

         m_request.header("host") = "ca2.software";

      }

      string strRequestUri = m_request.attr("request_uri");

      http_socket::OnHeaderComplete();

      information() << strProtocol << "://" << strHost << strRequestUri;

      string strTest(strHost);

      if (strTest.case_insensitive_ends_eat(".ca2.software"))
      {

         if (strTest.find_index('.') > 0)
         {

            infomration("!!!!!!!!!! -> " + strTest + "\n");

         }

      }

      if(m_request.attr("request_uri").as_string().find_index("/passthrough/") >= 0)
      {
         
         information() << "Passthrough";

      }

      if(m_request.headers().has_property("user_agent"))
      {

         information() << "user-agent: " << m_request.header("user_agent").as_string();

      }
      else
      {

         //information() << "user-agent: ():[" << m_addressRemote.get_string() << "]";

      }

      if(m_request.headers().has_property("from"))
      {

         information() << "from: " + m_request.header("from");

      }

      if(m_request.headers().has_property("accept-language"))
      {

         information("accept-language: %s", m_request.header("accept-language").as_string().c_str());

      }

      //m_request.InitBody(m_body_size_left);

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
      m_request.ParseBody(m_pcontext->m_papexcontext);

      //information("http version: %s\n", m_request.attr("http_version").string());
      //information("connection: %s\n", m_request.header("connection").string());
      //information("keepalive: %s\n", m_b_keepalive ? "true" : "false");
      /*   if(string_ends(m_request.attr("http_version").string(), "/1.1")
            && m_request.header("connection").string().case_insensitive_order("close") != 0)
         {
            m_b_keepalive = true;
         information(" ***    keepalive: true");
         }
         else
         {
            m_b_keepalive = false;
            information(" *** keepalive: false");
         }*/

      // prepare page
      OnExecute();

      Reset();
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Respond()
   {

      //TRACE0("http_base_socket::Respond");

      if(outheader("content-type").as_string().contains("text")
            || outheader("content-type").as_string().contains("javascript"))
      {

         on_compress();

      }

      if (response().m_strFile.has_char())
      {

         response().m_propertysetHeader["content-length"] = acmefile()->get_size(response().m_strFile);

      }
      else
      {

         m_response.m_propertysetHeader.set_at("content-length", (i64)m_response.file()->size());

      }

      for(i32 i = 0; i < m_response.cookies().size(); i++)
      {

         m_response.m_propertysetHeader.set_at("set-cookie", m_response.cookies().element_at(i)->get_cookie_string());

      }

      /*

            if(m_response.m_propertysetHeader.has_property("locationd"))
            {

               string strLocation = m_response.m_propertysetHeader.lowprop("Location");

               m_response.m_propertysetHeader.erase_by_name("Location");

               m_response.m_propertysetHeader["Location"] = strLocation;

            }

      */

      SendResponse();

      if(top_output_buffer() == nullptr)
      {

         OnWriteComplete();

      }

      response().file()->set_size(0);
   }


   void http_base_socket::OnWriteComplete()
   {
      //Debug deb("http_base_socket::OnTransferLimit");
      //information("");
      //information("http_base_socket::OnTransferLimit");
      //   char msg[32768];
      OnResponseComplete();
      //if (!m_b_keepalive)
      //{
      //   //information("SetCloseAndDelete");
      //   SetCloseAndDelete();
      //}
      //else
      //{
      //   //information("keep-alive");
      //}
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Reset()
   {

      http_socket::Reset();

      //m_body_size_left = 0;

      //m_body_size_downloaded = 0;

   }


   void http_base_socket::OnExecute()
   {

   }


   void http_base_socket::OnResponseComplete()
   {

   }



   //string http_base_socket::set-cookie(
   //const char * name,
   //::payload payload,
   //i32 iExpire,
   //const ::file::path & path,
   //const char * domain,
   //bool bSecure)
   //{
   //   m_request.cookies().set-cookie(
   //   name,
   //   ::payload,
   //   iExpire,
   //   path,
   //   domain,
   //   bSecure);
   //   return m_response.cookies().set-cookie(
   //          name,
   //          ::payload,
   //          iExpire,
   //          path,
   //          domain,
   //          bSecure);
   //}

   void http_base_socket::on_compress()
   {

      if(inheader("accept-encoding").as_string().contains("gzip"))
      {

         string str = outheader("content-type");

         if (str.case_insensitive_contains("text") || str.case_insensitive_contains("javascript"))
         {

            auto pfile = create_memory_file();

            auto & strFile = response().m_strFile;

            ::filesize iInputFileSize = 0;

            if (strFile.has_char())
            {

               auto pfileIn = file()->get_reader(strFile);

               iInputFileSize = pfileIn->size();

               acmesystem()->compress(pfile, pfileIn, "zlib");

               response().m_strFile.empty();

            }
            else
            {

               response().file()->seek_to_begin();

               iInputFileSize = response().file()->size();

               acmesystem()->compress(pfile, response().file(), "zlib");

            }

            //if (pfile->full_data_size() < iInputFileSize * 9 / 10)
            //{

               m_response.m_propertysetHeader.set_at("content-encoding", "gzip");

               response().file()->clear();

               response().file()->write_from_beginning(pfile);

            //}

         }

      }

   }


   bool http_base_socket::read_file(const ::file::path& pcszParam, pointer_array < int_array >* prangea, const ::scoped_string & scopedstrContentType)
   {

      ::file::path pcsz(pcszParam);

      bool bMd5Request = pcsz.case_insensitive_ends_eat(".md5");

      string strExtension = pcsz.final_extension();

      string str = strExtension;
      str.make_lower();
      string strContentType(scopedstrContentType);

      string strName(pcsz);



//      if (string_ends_ci(strName, "03 Coisa De Acender - Se..... - Djavan.mp3"))
  //    {
    //     debug_print("%s", strName.c_str());
      //}

      if (bMd5Request)
      {
         outheader("content-type") = "text/plain";
      }
      else if (outheader("content-type").as_string().has_char())
      {
      }
      else if (strContentType.has_char() && strContentType.case_insensitive_order("unknown") != 0)
      {
         outheader("content-type") = strContentType;
      }
      else
      {

         outheader("content-type") = get_file_extension_mime_type(strExtension);

      }

      string strReferer;
      
      strReferer = inheader("referer");

      string strServer = acmesystem()->url()->get_server(strReferer);

      string_array straAllowedOrigin;

      straAllowedOrigin.add("ca2.software");
      straAllowedOrigin.add("camilothomas.com");

      bool bAllowedOrigin = false;

      for (auto& strAllowedOrigin : straAllowedOrigin)
      {

         if (strServer.case_insensitive_ends("." + strAllowedOrigin) || strServer.case_insensitive_order(strAllowedOrigin) == 0)
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

      if (!acmefile()->exists(pcsz))
      {

         if (acmedirectory()->is(pcsz))
         {
            
            outattr("http_status_code") = 200;
            
            outattr("http_status") = "OK";
            
            outheader("x-fstype") = "directory";

         }
         else
         {
            
            outattr("http_status_code") = 404;
            
            outattr("http_status") = "Not Found";

         }

         return false;

      }

      outheader("x-fstype") = "file";

      if (prangea == nullptr || prangea->get_count() == 0)
      {

         if (strContentType.case_insensitive_begins("audio/"))
         {

            auto preader = file()->get_reader(pcsz);

            //if (!acmesystem()->uncompress(response().file(), preader, "zlib"))

            acmesystem()->uncompress(response().file(), preader, "zlib");
            //{

               response().file()->write_from_beginning(preader);

            //}

         }
         else
         {

            if (bMd5Request)
            {

               response().file()->print(file()->md5(pcsz));

               return true;

            }

            if (response().file()->get_position() == 0)
            {

               response().m_strFile = pcsz;

               outattr("http_status_code") = 200;

               outattr("http_status") = "OK";

            }
            else
            {

               auto preader = file()->shared_reader(pcsz);

               if (!preader)
               {

                  return false;

               }

               response().file()->write(preader);

            }

         }

      }
      else
      {

         auto preader = file()->shared_reader(pcsz);

         if (!preader)
         {

            return false;

         }

         auto iLen = preader->size();

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
               
               response().file()->println("--THIS_STRING_SEPARATES\r\n");
               
               response().file()->println("Content-range: bytes " + ::as_string(iStart) + "-" + ::as_string(iEnd) + "/" +::as_string(iLen));
               
               response().file()->println("Content-Transfer-Encoding: base64");

               while (true)
               {

                  if (iEnd >= iStart)
                  {
                     uRead = minimum(mem.size(), (memsize)(iEnd - iPos + 1));
                  }
                  else
                  {
                     uRead = mem.size();
                  }
                  uRead = preader->read(mem(0,uRead));
                  uTotal += uRead;
                  if (uRead == 0)
                     break;
                  pfile->write(mem(0, uRead));
                  iPos += uRead;
                  if (iPos >= preader->size())
                     break;
               }

               auto psystem = acmesystem();

               auto pbase64 = psystem->base64();
               
               response().file()->println(pbase64->encode(*pfile->get_memory()));

            }
            
            response().file()->println("--THIS_STRING_SEPARATES--\r\n");
            
            outheader("content-type") = "multipart/x-byteranges; boundary=THIS_STRING_SEPARATES";

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

                     uRead = minimum(mem.size(), (memsize)(iEnd - iPos + 1));

                  }
                  else
                  {
                     
                     uRead = mem.size();

                  }
                  
                  uRead = preader->read(mem(0, uRead));
                  
                  uTotal += uRead;

                  if (uRead == 0)
                  {

                     break;

                  }
                  
                  response().file()->write(mem(0, uRead));
                  
                  iPos += uRead;

                  if (iPos >= preader->size())
                  {

                     break;

                  }

               }

            }

            outattr("http_status_code") = 206;

            outattr("http_status") = "Partial Content";

            if (iEnd == -1)
            {
               
               outheader("Content-range") = "bytes " + ::as_string(iStart) + "-" + ::as_string(iEnd) + "/*";

            }
            else
            {

               outheader("Content-range") = "bytes " + ::as_string(iStart) + "-" + ::as_string(iEnd) + "/" + ::as_string(iLen);

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

      file()->get_lines(stra, payloadFile);

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



