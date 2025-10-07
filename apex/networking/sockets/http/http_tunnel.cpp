#include "framework.h" 
#include "http_tunnel.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/platform/http.h"
#include "apex/constant/idpool.h"
#include "apex/networking/http/context.h"
#include "apex/platform/context.h"


namespace sockets
{


   http_tunnel::http_tunnel() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h)
   {

      ///m_memoryBuf.set_size(1024 * 16);
      //m_iProxyPort = -1;

   }

   http_tunnel::~http_tunnel()
   {


   }


   void http_tunnel::initialize(::particle * pparticle)
   {


      http_socket::initialize(pparticle);

      SetLineProtocol();
      m_bOk = false;
      m_bDirect = false;
      m_estate = e_state_initial;

   }


   void http_tunnel::OnConnect()
   {

      if (m_bDirect)
      {

         http_request_step();

      }
      else if (m_bOk)
      {

         http_request_step();

      }
      else if (GetUrlPort() == 80 || GetUrlPort() == 8080)
      {

         // It is absolutely no good idea to maintain a connection opened in the server
         // in a general place as this class, because no one will know when it will be closed.
         // And to keep alive in http - http_tunnel - it is better to create a session class,
         // that receives http requests and finally close connection...
         // session though is not currently implemented in ca2...
         //m_request.m_propertysetHeader["Proxy-Connection"] = "Keep-Alive";

         m_bOk = true;

         http_request_step();

      }
      else
      {

         if (m_estate == e_state_initial)
         {

            string str;

            str.formatf("CONNECT %s:%d HTTP/1.0\r\n", GetUrlHost().c_str(), (int)GetUrlPort());

            print(str);

            str.formatf("host: %s:%d\r\n", GetUrlHost().c_str(), (int)GetUrlPort());

            print(str);

            str = "\r\n";

            print(str);

            m_estate = state_connect_sent;

         }

      }

   }


   void http_tunnel::OnLine(const ::scoped_string & scopedstrParam)
   {

      if (m_bOk || m_bDirect)
      {

         http_socket::OnLine(scopedstrParam);

      }
      else
      {

         string str(scopedstrParam);

         m_straProxy.add(str);

         if (m_straProxy.get_count() == 1)
         {

            character_count iPos = str.find_index(" ");

            string strStatus;

            if (iPos >= 0)
            {

               strStatus = str.substr(iPos + 1);

            }

            //if (string_begins(strStatus, astr.s200Space))
            //{

            //   m_estate = state_proxy_ok;

            //}

         }

         str.trim();

         if (str.is_empty())
         {

            if (m_estate != state_proxy_ok)
            {

               return;

            }

            m_bOk = true;

            if (m_bSslTunnel)
            {

               EnableSSL();

               OnSSLConnect();

               m_estate = state_init_ssl;

            }
            else
            {

               http_request_step();

            }

         }

      }

   }


   bool http_tunnel::http_request_step()
   {

      string str;

      m_request.attr("http_method") = "GET";
      m_request.attr("request_uri") = m_strRequest;
      m_request.attr("http_version") = "HTTP/1.1";
      //   outheader("accept") = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
      //outheader("Accept-Language") = "en-us,en;q=0.5";
      //outheader("Accept-Encoding") = "gzip,deflate";
      //outheader("Accept-Charset") = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
      //outheader("user_agent") = MyUseragent();

      //if (GetUrlPort() != 80 && GetUrlPort() != 443)
      //   outheader("Host") = GetUrlHost() + ":" + Utility::l2string(GetUrlPort());
      //else
      //   outheader("Host") = GetUrlHost();
      outheader("host") = m_urlparts.connect().host();

      SendRequest();

      return true;

   }


   void http_tunnel::OnFirst()
   {

   }


   void http_tunnel::OnHeader(const ::atom & atom, const ::scoped_string & scopedstr)
   {

      inheader(atom) = scopedstr;

   }


   void http_tunnel::OnHeaderComplete()
   {

      http_socket::OnHeaderComplete();

      m_bHeaders = true;

      ødefer_construct_new(m_pfileBody);

      m_pfileBody->set_size(0);

      m_pfileBody->seek_to_begin();

   }


   void http_tunnel::OnData(const_char_pointer psz, memsize size)
   {

      m_pfileBody->write({ psz, size });

   }


   bool http_tunnel::proxy_open(const ::scoped_string & scopedstrHost, ::networking::port_t port)
   {

//      m_strProxy = host;
//
//      m_iProxyPort = port;
//
//#ifdef BSD_STYLE_SOCKETS
//      m_strInitSSLClientContext += "/" + m_strProxy + ":" + as_string(port);
//#endif
//
//      m_bSslTunnel = IsSSL();
//      
//      EnableSSL(false);
//      
//      if (!tcp_socket::open(host, port))
//      {
//
//         if (!is_connecting())
//         {
//
//            fatal() <<"http_get_socket: connect() failed miserably";
//            
//            SetCloseAndDelete();
//
//         }
//
//         return false;
//
//      }
//
      return true;

   }


   bool http_tunnel::open(bool bConfigProxy)
   {

      if (m_strProxy.has_character() && m_iProxyPort > 0 && !m_bDirect)
      {
      }
      else if (bConfigProxy)
      {

         ::pointer < ::http::context > phttp = http();

         phttp->config_proxy(get_url(), this);

      }
      else
      {

         m_bDirect = true;

      }

      if (m_bDirect)
      {

         if (!tcp_socket::open(get_connect_host(), get_connect_port()))
         {

            if (!is_connecting())
            {

               fatal() <<"http_get_socket: connect() failed miserably (1)";

               SetCloseAndDelete();

            }

            return false;

         }

      }
      else
      {

         return proxy_open(m_strProxy, (::networking::port_t)m_iProxyPort);

      }

      return true;

   }


   ::string http_tunnel::GetUrlHost()
   {
      
      return m_urlparts.connect().host();

   }


   ::networking::port_t http_tunnel::GetUrlPort()
   {

      return m_urlparts.connect().port();

   }


} // namespace sockets
