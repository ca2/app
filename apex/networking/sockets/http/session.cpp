#include "framework.h" 
#include "session.h"
#include "apex/constant/idpool.h"


//#ifdef LINUX
//
//#include <sys/time.h>
//
//#endif

namespace sockets
{


   http_session::http_session(const ::url::connect_part & connectpart) //:
     /* ::object(&handler),
      base_socket(handler),
      socket(handler),
      stream_socket(handler),
      tcp_socket(handler),
      http_socket(handler),
      http_tunnel(handler),
      http_client_socket(handler),
      http_get_socket(handler),
      http_post_socket(handler),
      http_put_socket(handler)*/
   {

      //::url::url url(connect);

      m_urlparts.m_connectpart = connectpart;

      //m_urlparts.m_strHost      = host;

      inattr("http_protocol") = connectpart.m_strProtocol;

      m_request.m_propertysetHeader["host"] = connectpart.m_strHost;

      //set_url(protocol + "://" + host);

      set_url(connectpart);

      set_connect_host(connectpart.m_strHost);

      set_connect_port(connectpart.m_iPort);

      m_bRequestComplete = false;

   }


   http_session::~http_session()
   {

   }


   void http_session::request(const ::string & strMethod, const ::string & strRequest)
   {

      request(string_http_method(strMethod), strRequest);

   }


   void http_session::request(e_http_method emethod, const ::string & strRequest)
   {

      m_emethod                  = emethod;
      inattr("request_uri")      = strRequest;
      inattr("http_protocol")    = m_urlparts.connect().m_strProtocol;
      m_urlparts.request() = strRequest;
      set_url(m_urlparts.as_url());
      inattr("http_version")    = "HTTP/1.1";
      //m_b_keepalive                 = true;
      m_content_ptr                 = 0;

      if(m_bRequestComplete)
      {
         http_request_step();
      }

      m_bRequestComplete      = false;

   }


   bool http_session::http_request_step()
   {

      inheader("connection") = "Keep-Alive";

      inattr("http_method") = http_method_string(m_emethod);

      switch (m_emethod)
      {
      case http_method_get:

         http_get_socket::http_request_step();

         break;

      case http_method_post:

         http_post_socket::http_request_step();

         break;

      case http_method_put:

         http_put_socket::http_request_step();

         break;

      default:

         http_get_socket::http_request_step();

         break;

      }

      return ::success;

   }


   void http_session::OnDataComplete()
   {

      http_client_socket::OnDataComplete();
      
      m_bRequestComplete = true;

   }


   void http_session::OnHeaderComplete()
   {

      http_client_socket::OnHeaderComplete();

   }


} // namespace sockets





