#include "framework.h" 
#include "apex/id.h"
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   http_get_socket::http_get_socket() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h)
   {

#if !defined(BSD_STYLE_SOCKETS)

      m_bExpectRequest = true;

#endif

   }


   http_get_socket::http_get_socket(const string & url_in) :
      //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      http_client_socket(url_in)
   {

#if !defined(BSD_STYLE_SOCKETS)

      m_bExpectRequest = true;

#endif

      m_emethod = http_method_get;

   }


   http_get_socket::http_get_socket(const string & host,port_t port,const string & url_in) :
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

#if !defined(BSD_STYLE_SOCKETS)

      m_bExpectRequest = true;

#endif

      m_emethod = http_method_get;

      __UNREFERENCED_PARAMETER(host);

      __UNREFERENCED_PARAMETER(port);

   }


   http_get_socket::~http_get_socket()
   {
   }


   void http_get_socket::step()
   {

      if (inattr("minimal_headers").is_false())
      {
         //inheader("Accept") = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
         //inheader("Accept-Language") = "en-us,en;q=0.5";
         if (m_pfile == nullptr) // by the time, inline gzip decompression not yet implemented
         {
            if (inheader(__id(accept_encoding)).is_new())
            {
               inheader(__id(accept_encoding)) = "gzip,deflate";
            }
         }
         //inheader("Accept-Charset") = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
         inheader(__id(user_agent)) = MyUseragent();
      }
      //inheader("Content-Length") = 0;
      //inheader("Cache-Controlngth") = 0;

      /*      if (GetUrlPort() != 80 && GetUrlPort() != 443)
               inheader(__id(host)) = GetUrlHost() + ":" + __string(GetUrlPort());
            else
               inheader(__id(host)) = GetUrlHost();*/

#if defined(WINRT_SOCKETS)

      m_bWaitingResponse = true;

      m_bExpectResponse = false;

      m_bExpectRequest = false;

#endif

      SendRequest();

      return ::success;

   }


} // namespace sockets


