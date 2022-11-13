#include "framework.h" 
#include "put_socket.h"
#include "apex/constant/idpool.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


namespace sockets
{


   http_put_socket::http_put_socket() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h)
   {

      m_content_length = -1;

   }


   //http_put_socket::inithttp_put_socket(const string & url_in) :
   //   //::object(&h),
   //   //base_socket(h),
   //   //socket(h),
   //   //stream_socket(h),
   //   //tcp_socket(h),
   //   //http_socket(h),
   //   //http_tunnel(h),
   //   //http_client_socket(h, url_in)
   //   http_client_socket(url_in)
   //{

   //   m_content_length = -1;

   //}


   http_put_socket::~http_put_socket()
   {

   }


   void http_put_socket::initialize_http_put_socket(const string & strUrl)
   {

      initialize_http_client_socket(strUrl);

   }


   void http_put_socket::SetFile(const string & file)
   {

      if(::particle::file()->exists(file))
      {

         m_filename = file;

         m_content_length = ::particle::file()->length(file);

      }
      else
      {

//#ifdef BSD_STYLE_SOCKETS
//         FATAL("SetFile " << Errno << bsd_socket_error(Errno));
//#endif

         SetCloseAndDelete();

      }

   }


   void http_put_socket::SetContentType(const string & type)
   {

      m_content_type = type;

   }


   bool http_put_socket::step()
   {

      if(m_file.is_set())
      {

         m_content_length = (long) m_file->get_size();

      }

      m_request.attr("http_method")    = "PUT";

      m_request.attr("http_version")   = "HTTP/1.1";

      //inheader("host")                = GetUrlHost();

      if(m_content_type.has_char())
      {
         outheader("content-type")     = m_content_type;
      }
      inheader("content-length")      = (i64) m_content_length;
      inheader("user_agent")          = MyUseragent();
      inheader("connection")          = "close";
      SendRequest();

      if(m_file.is_set())
      {
         memsize n;
         char buf[32768];
         m_file->seek_to_begin();
         while ((n = m_file->read(buf, 32768)) > 0)
         {
            write(buf, n);
         }
      }
      else
      {
         FILE *fil = fopen(m_filename, "rb");
         if (fil)
         {
            memsize n;
            char buf[32768];
            while ((n = fread(buf, 1, 32768, fil)) > 0)
            {
               write(buf, n);
            }
            fclose(fil);
         }
      }


      return true;

   }

}


