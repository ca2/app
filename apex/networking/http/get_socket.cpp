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


   void get_socket::initialize_get_socket(const ::url::url & url)
   {

      initialize_http_get_socket(url);

   }


   void get_socket::initialize_get_socket(const ::scoped_string & scopedstrProtocol, const ::scoped_string & scopedstrHost, ::networking::port_t port, const ::url::request & request)
   {

      initialize_http_get_socket(scopedstrProtocol, scopedstrHost, port, request);

   }


   void get_socket::OnDataArrived(const char *, memsize len)
   {
      __UNREFERENCED_PARAMETER(len);
   }

   void get_socket::OnHeader(const ::atom & atom, const ::scoped_string & scopedstr)
   {

      ::sockets::http_get_socket::OnHeader(atom, scopedstr);

      if(atom == "location")
      {

         m_strHeaderLocation = scopedstr;

      }
      else if(atom == "set-cookie")
      {

         if(m_pcookies != nullptr)
         {

            m_pcookies->add(scopedstr);

         }

      }

   }



} // namespace apex



