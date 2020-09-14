#include "framework.h"
#include "apex/id.h"
#include "apex/net/sockets/_.h"



namespace sockets
{


   http_base_socket::http_base_socket(base_socket_handler& h) :
      ::object(&h),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h)
   {

   }


   http_base_socket::http_base_socket(const http_base_socket& s) :
      ::object(s.get_context_object()),
      base_socket(s),
      socket(s),
      stream_socket(s),
      tcp_socket(s),
      http_socket(s)
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

      string strProtocol = m_request.attr("http_protocol").get_string().c_str();

      string strHost = m_request.header("host");

      if (::str::ends_eat_ci(strHost, ".test.ca2.cc"))
      {

         m_request.header("host") = strHost + ".ca2.cc";

      }
      else if (strHost == "test.ca2.cc")
      {

         m_request.header("host") = "ca2.cc";

      }

      string strRequestUri = m_request.attr("request_uri").get_string();

      http_socket::OnHeaderComplete();

      TRACE("%s://%s%s", strProtocol.c_str(), strHost.c_str(), strRequestUri.c_str());

      string strTest(strHost);

      if (::str::ends_eat_ci(strTest, ".ca2.cc"))
      {

         if (strTest.find('.') > 0)
         {

            output_debug_string("!!!!!!!!!! -> " + strTest + "\n");

         }

      }

      if(m_request.attr("request_uri").get_string().find("/passthrough/") >= 0)
      {
         
         TRACE("Passthrough");

      }

      if(m_request.headers().has_property(__id(user_agent)))
      {

         TRACE("user-agent: " + m_request.header(__id(user_agent)));

      }
      else
      {

         TRACE("user-agent: ():[%s]", m_addressRemote.to_string().c_str());

      }

      if(m_request.headers().has_property(__id(from)))
      {

         TRACE("from: " + m_request.header(__id(from)));

      }

      if(m_request.headers().has_property(__id(accept_language)))
      {

         TRACE("accept-language: %s", m_request.header(__id(accept_language)).get_string().c_str());

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

      //TRACE("http version: %s\n", m_request.attr("http_version").get_string());
      //TRACE("connection: %s\n", m_request.header("connection").get_string());
      //TRACE("keepalive: %s\n", m_b_keepalive ? "true" : "false");
      /*   if(::str::ends(m_request.attr("http_version").get_string(), "/1.1")
            && m_request.header("connection").get_string().compare_ci("close") != 0)
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

      if(outheader(__id(content_type)).get_string().find("text") >= 0
            || outheader(__id(content_type)).get_string().find("javascript") >= 0)
      {

         on_compress();

      }

      if (response().m_strFile.has_char())
      {

         response().m_propertysetHeader[__id(content_length)] = file_length_dup(response().m_strFile);

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

               m_response.m_propertysetHeader.remove_by_name("Location");

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
   //var var,
   //i32 iExpire,
   //const char * path,
   //const char * domain,
   //bool bSecure)
   //{
   //   m_request.cookies().set_cookie(
   //   name,
   //   var,
   //   iExpire,
   //   path,
   //   domain,
   //   bSecure);
   //   return m_response.cookies().set_cookie(
   //          name,
   //          var,
   //          iExpire,
   //          path,
   //          domain,
   //          bSecure);
   //}

   void http_base_socket::on_compress()
   {

      if(inheader("accept-encoding").get_string().find("gzip") >= 0)
      {

         string str = outheader(__id(content_type)).get_string();

         if (str.find_ci("text") >= 0 || str.find_ci("javascript") >= 0)
         {

            m_response.m_propertysetHeader.set_at(__id(content_encoding), "gzip");

            auto pfile = create_memory_file();

            compress_context compress(this);

            if (response().m_strFile.has_char())
            {

               compress.gz(pfile, Context.file().get_reader(response().m_strFile));

               response().m_strFile.Empty();

            }
            else
            {

               response().file()->seek_to_begin();

               compress.gz(pfile, response().file());

            }

            response().file()->from_begin(pfile);

         }

      }

   }


} // namespace sockets
