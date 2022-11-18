#include "framework.h" 
#include "get_socket.h" 
//#include "apex/id.h"
//#include "apex/networking/sockets/_sockets.h"


namespace http
{


   get_socket::get_socket()
   {

      m_pcookies = nullptr;

   }

      
   get_socket::~get_socket()
   {


   }


   void get_socket::initialize_get_socket(const ::string & strUrl)
   {

      initialize_http_get_socket(strUrl);

   }


   void get_socket::initialize_get_socket(const string & host, ::networking::port_t port, const string & strUrl)
   {

      initialize_http_get_socket(host, port, strUrl);

   }


   void get_socket::OnDataArrived(const char *, memsize len)
   {
      __UNREFERENCED_PARAMETER(len);
   }

   void get_socket::OnHeader(atom key, const string & value)
   {

      ::sockets::http_get_socket::OnHeader(key, value);

      if(key == "location")
      {

         m_strHeaderLocation = value;

      }
      else if(key == "set-cookie")
      {

         if(m_pcookies != nullptr)
         {

            m_pcookies->add(value);

         }

      }

   }



} // namespace apex



