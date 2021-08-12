#include "framework.h" 
#include "apex/id.h"
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   http_debug_socket::http_debug_socket() :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      m_content_length(-1),
      m_read_ptr(0)
   {

   }


   http_debug_socket::~http_debug_socket()
   {

   }


   void http_debug_socket::Init()
   {

      if (get_parent() -> GetPort() == 443)
      {

#ifdef HAVE_OPENSSL

         EnableSSL();

#else

#ifndef _UWP

         WARN("url_this", -1, "SSL not available");

#endif

#endif

      }

   }


   void http_debug_socket::OnFirst()
   {
      print(
      "HTTP/1.1 200 OK\n"
      "Content-type: text/html\n"
      "Connection: close\n"
      "Server: http_debug_socket/1.0\n"
      "\n");
      print(
      "<html><head><title>Echo Request</title></head>"
      "<body><h3>Request header</h3>");
      print(   "<form method='post' action='/test_post'>"
               "<input type='text' name='text' value='test text'><br>"
               "<input type='submit' name='submit' value=' OK '></form>");
      print(   "<pre style='background: #e0e0e0'>");
      print(m_request.attr(__id(http_method)).string() + " " + m_request.attr(__id(request_uri)) + " " + m_request.attr(__id(http_version)) + "\n");
   }


   void http_debug_socket::OnHeader(id key, const string & value)
   {
      if(key == __id(content_length))
         m_content_length = atoi(value);

      print(__str(key) + ": " + value + "\n");
   }


   void http_debug_socket::OnHeaderComplete()
   {
      if (m_content_length || m_content_length != ((memsize)(-1)) || IsChunked())
      {
         print("</pre><h3>Request Body</h3><pre style='background: #e0e0e0'>");
      }
      else
      {
         print("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


   void http_debug_socket::OnData(const char *point,memsize l)
   {
      write(point,l);
      m_read_ptr += (int)l;
      if (m_read_ptr >= m_content_length && m_content_length && m_content_length != ((memsize)(-1)))
      {
         print("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


   void http_debug_socket::OnDataComplete()
   {
      if (!IsCloseAndDelete())
      {
         print("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


} // namespace sockets


