#include "framework.h" 
#include "apex/id.h"
#include "apex/net/sockets/_sockets.h"


namespace http
{


   get_socket::get_socket(::sockets::socket_handler & handler, const string & url) :
      ::object(&handler),
      ::sockets::base_socket(handler),
      ::sockets::socket(handler),
      ::sockets::stream_socket(handler),
      ::sockets::tcp_socket(handler),
      ::sockets::http_socket(handler),
      ::sockets::http_tunnel(handler),
      ::sockets::http_client_socket(handler, url),
      ::sockets::http_get_socket(handler, url)
   {

      m_pcookies = nullptr;

   }

      
   get_socket::get_socket(::sockets::socket_handler & handler, const string & host, port_t port, const string & url) :
      ::sockets::base_socket(handler),
      ::sockets::socket(handler),
      ::sockets::stream_socket(handler),
      ::sockets::tcp_socket(handler),
      ::sockets::http_socket(handler),
      ::sockets::http_tunnel(handler),
      ::sockets::http_client_socket(handler, url),
      ::sockets::http_get_socket(handler, host, port, url)
   {

      m_pcookies = nullptr;

   }


   get_socket::~get_socket()
   {


   }

   void get_socket::OnDataArrived(const char *, memsize len)
   {
      UNREFERENCED_PARAMETER(len);
   }

   void get_socket::OnHeader(id key, const string & value)
   {

      ::sockets::http_get_socket::OnHeader(key, value);

      if(key == __id(location))
      {

         m_strHeaderLocation = value;

      }
      else if(key == __id(set_cookie))
      {

         if(m_pcookies != nullptr)
         {

            m_pcookies->add(value);

         }

      }

   }



} // namespace apex



