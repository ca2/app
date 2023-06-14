#include "framework.h"
//#include "axis/compress/compress.h"


namespace sockets
{


   http_base_socket::http_base_socket() :
      ::object(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h)
   {

   }



   http_base_socket::~http_base_socket()
   {
   }


   void http_base_socket::OnFirst()
   {
      m_iContentLength = 0;
   }


   void http_base_socket::OnHeader(atom key,const string & value)
   {

      http_socket::OnHeader(key, value);

      if(key == __id(content-length))
      {
         m_iContentLength = atoi(value);
      }

   }


   void http_base_socket::OnHeaderComplete()
   {
      http_socket::OnHeaderComplete();
      //TRACE0("\n");
      //TRACE0(m_request.attr("http_protocol").as_string() + "://" + m_request.header("host").as_string() + m_request.attr("request_uri").as_string() + "\n");
      if(m_request.attr("request_uri").as_string().find("/passthrough/") >= 0)
      {
         //TRACE0( "Passthrought");
      }
      if(m_request.headers().has_property("user-agent"))
      {
         //TRACE0("user-agent: " + m_request.header("user-agent") + "\n");
      }
      if(m_request.headers().has_property("from"))
      {
         //TRACE0("from: " + m_request.header("from") + "\n");
      }
      if(m_request.headers().has_property("accept-language"))
      {
         //TRACE0("accept-language: " + m_request.header("accept-language") + "\n");
      }

      if (m_body_size_left > 0)
      {

         m_request.InitBody( m_body_size_left );

      }
      else
      {
         
         Execute();

      }
      
   }


   void http_base_socket::OnData(const char *buf,memsize sz)
   {
      
      m_request.write( buf, sz );
      
      m_body_size_left -= sz;

      m_body_size_downloaded += sz;

      if (!m_body_size_left)
      {

         m_request.CloseBody();

         Execute();

      }

   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Execute()
   {
      // parse form data / query_string and cookie header if available
      m_request.ParseBody();

      //information("http version: %s\n", m_request.attr("http_version").as_string());
      //information("connection: %s\n", m_request.header("connection").as_string());
      //information("keepalive: %s\n", m_b_keepalive ? "true" : "false");
   /*   if(string_ends(m_request.attr("http_version").as_string(), "/1.1")
         && m_request.header("connection").as_string().case_insensitive_order("close") != 0)
      {
         m_b_keepalive = true;
      information(" ***    keepalive: true\n");
      }
      else
      {
         m_b_keepalive = false;
         information(" *** keepalive: false\n");
      }*/

      // prepare page
      OnExecute();

      Reset();
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Respond()
   {

      //TRACE0("http_base_socket::Respond");

      if(outheader(__id(content-type)).get_string().find("text") >= 0)
      {
      
         on_compress();

      }

      m_response.m_propertysetHeader.set_at(__id(content-length), (i64) m_response.file()->get_size());

      for(int i = 0; i < m_response.cookies().get_size(); i++)
      {
      
         m_response.m_propertysetHeader.set_at(__id(set-cookie), m_response.cookies().element_at(i)->get_cookie_string());

      }

/* 

      if(m_response.m_propertysetHeader.low_has_property(as_string(location)))
      {

         string strLocation = m_response.m_propertysetHeader.lowprop(as_string(Location));

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


   // --------------------------------------------------------------------------------------
   void http_base_socket::OnWriteComplete()
   {
      //Debug deb("http_base_socket::OnTransferLimit");
      //information("\n");
      //information("http_base_socket::OnTransferLimit\n");
   //   char msg[32768];
      OnResponseComplete();
      if (!m_b_keepalive)
      {
         //information("SetCloseAndDelete\n");
         SetCloseAndDelete();
      }
      else
      {
         //information("keep-alive\n");
      }
   }


   // --------------------------------------------------------------------------------------
   void http_base_socket::Reset()
   {

      http_socket::Reset();

      m_body_size_left = 0;

      m_body_size_downloaded = 0;

   }


   void http_base_socket::OnResponseComplete()
   {

   }


   string http_base_socket::set-cookie(
         const char * name,
         ::payload payload,
         int iExpire,
         const ::file::path & path,
         const char * domain,
         bool bSecure)
   {

      m_request.cookies().set-cookie(
         name,
         ::payload,
         iExpire,
         path,
         domain,
         bSecure);

      return m_response.cookies().cookie(name);

   }


   void http_base_socket::on_compress()
   {
       
      if(inheader(__id(accept-encoding)).get_string().find("gzip") >= 0)
      {

         if(outheader(__id(content-type)).get_string().case_insensitive_find("text") >= 0)
         {
       
            m_response.m_propertysetHeader.set_at(__id(content-encoding), "gzip");

            auto pfile = create_memory_file();

            compress_context compress(this);

            if (response().m_strFile.has_char())
            {

               compress.gz(pfile, pcontext->m_papexcontext->file()->get_reader(response().m_strFile));

               response().m_strFile.empty();

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
