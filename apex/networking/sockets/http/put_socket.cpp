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

         m_content_length = ::particle::file()->length(file).as_i64();

      }
      else
      {

//#ifdef BSD_STYLE_SOCKETS
//         fatal() <<"SetFile " << Errno << bsd_socket_error(Errno);
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

         m_content_length = (long) m_file->size();

      }

      m_request.attr("http_method")    = "PUT";

      m_request.attr("http_version")   = "HTTP/1.1";

      auto strHost = GetUrlHost();
      inheader("host")                = strHost;

      if(m_content_type.has_char())
      {
         outheader("content-type")     = m_content_type;
      }
      inheader("content-length")      = (i64) m_content_length;
      
      auto strUserAgent=MyUseragent();
      inheader("user-agent")          = strUserAgent;
      //inheader("connection")          = "close";
      SendRequest();
      if(m_file.is_set())
      {
         ::information("Sending " + ::as_string(m_content_length)+ " bytes");
         memsize n;
         if(m_transferprogressfunction)
         {
            m_transferprogressfunction(0.0, 0, m_content_length);
         }
         ::memory memory;
         memory.set_size(32KiB);
         m_file->seek_to_begin();
         memsize total = 0;
         while ((n = m_file->read(memory.data(), memory.size())) > 0)
         {
            write(memory.data(), n);
            total+=n;
            double dRate=(double)total/(double)m_content_length;
            ::format_output_debug_string("%0.2f%% %d of %d bytes\n",100.0*dRate, total, m_content_length);
            
            if(m_transferprogressfunction)
            {

               m_transferprogressfunction(dRate, total, m_content_length);
               
            }
            
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
               write({ buf, n });
            }
            fclose(fil);
         }
      }


      return true;

   }

}


