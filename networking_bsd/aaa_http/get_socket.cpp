#include "framework.h" 
#include "apex/id.h"
//#include "apex/networking/sockets/_sockets.h"


namespace http
{


   get_socket::get_socket(const string & url) :
      ::sockets::http_client_socket(url),
      ::sockets::http_get_socket(url)
   {

      m_pcookies = nullptr;

   }

      
   get_socket::get_socket(const string & host, port_t port, const string & url) :
      ::sockets::http_client_socket(url),
      ::sockets::http_get_socket(host, port, url)
   {

      m_pcookies = nullptr;

   }


   get_socket::~get_socket()
   {


   }

   void get_socket::OnDataArrived(const char *, memsize len)
   {
      __UNREFERENCED_PARAMETER(len);
   }

   void get_socket::OnHeader(atom key, const string & value)
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



