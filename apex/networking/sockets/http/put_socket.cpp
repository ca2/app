#include "framework.h" 
#include "apex/id.h"
#include "apex/networking/sockets/_sockets.h"
#include <stdio.h>


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


   http_put_socket::http_put_socket(const string & url_in) :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h, url_in)
      http_client_socket(url_in)
   {

      m_content_length = -1;

   }


   http_put_socket::~http_put_socket()
   {

   }


   void http_put_socket::SetFile(const string & file)
   {

      if(m_pcontext->m_papexcontext->file().exists(file))
      {

         m_filename = file;

         m_pcontext->m_papexcontext->file().length(file).as(m_content_length);

      }
      else
      {

#ifdef BSD_STYLE_SOCKETS
         FATAL("SetFile " << Errno << bsd_socket_error(Errno));
#endif

         SetCloseAndDelete();

      }

   }


   void http_put_socket::SetContentType(const string & type)
   {

      m_content_type = type;

   }


   void http_put_socket::step()
   {

      if(m_file.is_set())
      {

         m_content_length = (long) m_file->get_size();

      }

      m_request.attr(__id(http_method))    = "PUT";

      m_request.attr(__id(http_version))   = "HTTP/1.1";

      //inheader(__id(host))                = GetUrlHost();

      if(m_content_type.has_char())
      {
         outheader(__id(content_type))     = m_content_type;
      }
      inheader(__id(content_length))      = (i64) m_content_length;
      inheader(__id(user_agent))          = MyUseragent();
      inheader(__id(connection))          = "close";
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


