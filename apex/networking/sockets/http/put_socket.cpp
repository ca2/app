#include "framework.h" 
#include "put_socket.h"
#include "apex/constant/idpool.h"
#include "acme/filesystem/filesystem/file_context.h"
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


   void http_put_socket::initialize_http_put_socket(const ::url::url & url)
   {

      initialize_http_client_socket(url);

   }


   void http_put_socket::SetFile(const ::scoped_string & scopedstrFile)
   {

      if(::particle::file()->exists(scopedstrFile))
      {

         m_filename = scopedstrFile;

         m_content_length = ::particle::file()->length(scopedstrFile).as_long_long();

      }
      else
      {

//#ifdef BSD_STYLE_SOCKETS
//         fatal() <<"SetFile " << Errno << bsd_socket_error(Errno);
//#endif

         SetCloseAndDelete();

      }

   }


   void http_put_socket::SetContentType(const ::scoped_string & scopedstrType)
   {

      m_content_type = scopedstrType;

   }


   bool http_put_socket::http_request_step()
   {

      if(m_file.is_set())
      {

         m_content_length = (long) m_file->size();

      }

      m_request.attr("http_method")    = "PUT";

      m_request.attr("http_version")   = "HTTP/1.1";

      auto strHost = GetUrlHost();
      inheader("host")                = strHost;

      if(m_content_type.has_character())
      {
         outheader("content-type")     = m_content_type;
      }
      inheader("content-length")      = (long long) m_content_length;
      
      auto strUserAgent=MyUseragent();
      inheader("user-agent")          = strUserAgent;
      //inheader("connection")          = "close";
      SendRequest();
      if(m_file.is_set())
      {
         information("Sending " + ::as_string(m_content_length)+ " bytes");
         memsize n;
         if(m_transferprogressfunction)
         {
            m_transferprogressfunction(0.0, 0, m_content_length);
         }
         ::memory memory;
         memory.set_size(32_KiB);
         m_file->seek_to_begin();
         memsize total = 0;
         while ((n = m_file->read(memory.data(), memory.size())) > 0)
         {
            write(memory.data(), n);
            total+=n;
            double dRate=(double)total/(double)m_content_length;
            ::output_debug_string_formatf("%0.2f%% %d of %d bytes\n",100.0*dRate, total, m_content_length);
            
            if(m_transferprogressfunction)
            {

               m_transferprogressfunction(dRate, total, m_content_length);
               
            }
            
         }

      }
      else
      {

         auto preader = file()->get_reader(m_filename);

         if (preader.ok())
         {

            memory buffer;

            buffer.set_size(32_KiB);

            memsize n;

            while ((n = preader->read(buffer)) > 0)
            {

               write({ buffer.data(), n });

            }

         }

      }

      return true;

   }

}


