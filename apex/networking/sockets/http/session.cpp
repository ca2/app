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


   http_session::http_session(const string & protocol,const string & host) //:
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

      //m_bEnablePool = false;
      m_strProtocol                 = protocol;
      m_host                        = host;

      inattr("http_protocol")   = protocol;

      m_request.m_propertysetHeader["host"] = host;

      set_url(protocol + "://" + host);

      if(protocol == "http")
         m_port = 80;
      else
         m_port = 443;

      set_connect_host(m_host);
      set_connect_port(m_port);

      m_bRequestComplete            = false;

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

      m_emethod                     = emethod;
      inattr("request_uri")     = strRequest;
      inattr("http_protocol")   = m_strProtocol;
      set_url(m_strProtocol + "://" + GetUrlHost() + inattr("request_uri"));
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





