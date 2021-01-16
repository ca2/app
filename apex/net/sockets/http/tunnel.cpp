#include "framework.h" 
#include "apex/astr.h"
#include "apex/id.h"
#include "apex/net/sockets/_sockets.h"


namespace sockets
{


   http_tunnel::http_tunnel(base_socket_handler & h) :
      ::object(&h),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h)
   {

      SetLineProtocol();
      m_bOk = false;
      m_bDirect = false;
      m_estate = e_state_initial;
      ///m_memoryBuf.set_size(1024 * 16);
      m_iProxyPort = -1;

   }


   void http_tunnel::OnConnect()
   {

      if (m_bDirect)
      {

         step();

      }
      else if (m_bOk)
      {

         step();

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

         step();

      }
      else
      {
         if (m_estate == e_state_initial)
         {
            string str;
            str.Format("CONNECT %s:%d HTTP/1.0\r\n", GetUrlHost().c_str(), (int)GetUrlPort());
            print(str);
            str.Format("host: %s:%d\r\n", GetUrlHost().c_str(), (int)GetUrlPort());
            print(str);
            str = "\r\n";
            print(str);
            m_estate = state_connect_sent;
         }
      }
   }

   void http_tunnel::OnLine(const string & strParam)
   {
      if (m_bOk || m_bDirect)
      {
         http_socket::OnLine(strParam);
      }
      else
      {
         string str(strParam);
         m_straProxy.add(str);
         if (m_straProxy.get_count() == 1)
         {
            strsize iPos = str.find(" ");
            string strStatus;
            if (iPos >= 0)
            {
               strStatus = str.Mid(iPos + 1);
            }
            if (::str::begins(strStatus, astr.s200Space))
            {
               m_estate = state_proxy_ok;
            }
         }
         str.trim();
         if (str.is_empty())
         {
            if (m_estate != state_proxy_ok)
               return;
            m_bOk = true;
            if (m_bSslTunnel)
            {
               EnableSSL();
               OnSSLConnect();
               m_estate = state_init_ssl;
            }
            else
            {
               step();
            }
         }
      }
   }

   void http_tunnel::step()
   {
      string str;
      m_request.attr(__id(http_method)) = "GET";
      m_request.attr(__id(request_uri)) = m_strRequest;
      m_request.attr(__id(http_version)) = "HTTP/1.1";
      //   outheader(__id(accept)) = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
      //outheader("Accept-Language") = "en-us,en;q=0.5";
      //outheader("Accept-Encoding") = "gzip,deflate";
      //outheader("Accept-Charset") = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
      //outheader(__id(user_agent)) = MyUseragent();

      //if (GetUrlPort() != 80 && GetUrlPort() != 443)
      //   outheader("Host") = GetUrlHost() + ":" + Utility::l2string(GetUrlPort());
      //else
      //   outheader("Host") = GetUrlHost();
      outheader(__id(host)) = m_host;
      SendRequest();
   }

   void http_tunnel::OnFirst()
   {
   }
   void http_tunnel::OnHeader(id key, const string & strValue)
   {
      inheader(key) = strValue;
   }
   void http_tunnel::OnHeaderComplete()
   {
      http_socket::OnHeaderComplete();

      m_bHeaders = true;
      m_fileBody.set_size(0);
      m_fileBody.seek_to_begin();
   }


   void http_tunnel::OnData(const char * psz, memsize size)
   {

      m_fileBody.write(psz, size);

   }


   bool http_tunnel::proxy_open(const string &host, port_t port)
   {

      m_strProxy = host;

      m_iProxyPort = port;

#ifdef BSD_STYLE_SOCKETS
      m_strInitSSLClientContext += "/" + m_strProxy + ":" + __str(port);
#endif

      m_bSslTunnel = IsSSL();
      
      EnableSSL(false);
      
      if (!tcp_socket::open(host, port))
      {

         if (!Connecting())
         {

            FATAL(log_this, "http_get_socket", -1, "connect() failed miserably");
            
            SetCloseAndDelete();

         }

         return false;

      }

      return true;

   }


   bool http_tunnel::open(bool bConfigProxy)
   {

      if (m_strProxy.has_char() && m_iProxyPort > 0 && !m_bDirect)
      {
      }
      else if (bConfigProxy)
      {

         Context.http().config_proxy(get_url(), this);

      }
      else
      {

         m_bDirect = true;

      }

      if (m_bDirect)
      {

         if (!tcp_socket::open(get_connect_host(), get_connect_port()))
         {

            if (!Connecting())
            {

               FATAL(log_this, "http_get_socket", -1, "connect() failed miserably");

               SetCloseAndDelete();

            }

            return false;

         }

      }
      else
      {

         return proxy_open(m_strProxy, (port_t)m_iProxyPort);

      }

      return true;

   }


   const string & http_tunnel::GetUrlHost()
   {
      return m_host;
   }


   port_t http_tunnel::GetUrlPort()
   {
      return m_port;
   }


} // namespace sockets
