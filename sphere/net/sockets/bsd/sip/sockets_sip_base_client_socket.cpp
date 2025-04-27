#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


#if defined(LINUX) || defined(APPLEOS)

#include <sys/time.h>

#endif


namespace sockets
{


   sip_base_client_socket::sip_base_client_socket() :
      object(h.get_app()),
      base_socket(h),
      socket(h),
      m_request(h.get_app()),
      m_response(h.get_app()),
      m_bFirst(true)
      ,m_bHeader(true)
      ,m_bRequest(false)
      ,m_bResponse(false)
      ,m_body_size_left(0)
      ,m_b_http_1_1(false)
      ,m_b_keepalive(false)
      ,m_b_chunked(false)
      ,m_chunk_size(0)
      ,m_chunk_state(0)
   {

      m_request.attr("http_version") = "SIP/2.0";
      m_eerrorLast = error_none;
      SetLineProtocol();

   }


   sip_base_client_socket::sip_base_client_socket(const sip_base_client_socket& s) :
      object(s.get_app()),
      base_socket(s),
      socket(s),
      m_request(s.get_app()),
      m_response(s.get_app())
   {
   }


   sip_base_client_socket::~sip_base_client_socket()
   {
   }


   void sip_base_client_socket::OnRawData(char *buf,size_t len)
   {
      if (!m_bHeader)
      {
         if (m_b_chunked)
         {
            size_t ptr = 0;
            while (ptr < len)
            {
               switch (m_chunk_state)
               {
               case 4:
                  while (ptr < len && (m_chunk_line.get_length() < 2 || m_chunk_line.substr(m_chunk_line.get_length() - 2) != "\r\n"))
                     m_chunk_line += buf[ptr++];
                  if (m_chunk_line.get_length() > 1 && m_chunk_line.substr(m_chunk_line.get_length() - 2) == "\r\n")
                  {
                     OnDataComplete();
                     // prepare for next request(or response)
                     m_b_chunked = false;
                     SetLineProtocol( true );
                     m_bFirst = true;
                     m_bHeader = true;
                     m_body_size_left = 0;
                     if (len - ptr > 0)
                     {
                        memory mem;
                        mem.set_size(TCP_BUFSIZE_READ);
                        char * tmp = (char*) mem.get_data();
                        ::memory_copy(tmp, buf + ptr, len - ptr);
                        tmp[len - ptr] = 0;
                        on_read( tmp, len - ptr );
                        ptr = len;
                     }
                  }
                  break;
               case 0:
                  while (ptr < len && (m_chunk_line.get_length() < 2 || m_chunk_line.substr(m_chunk_line.get_length() - 2) != "\r\n"))
                     m_chunk_line += buf[ptr++];
                  if (m_chunk_line.get_length() > 1 && m_chunk_line.substr(m_chunk_line.get_length() - 2) == "\r\n")
                  {
                     m_chunk_line = m_chunk_line.left(m_chunk_line.get_length() - 2);
                     ::parse pa(m_chunk_line, ";");
                     string size_str = pa.getword();
                     m_chunk_size = ::hex::to_unsigned_int(size_str);
                     if (!m_chunk_size)
                     {
                        m_chunk_state = 4;
                        m_chunk_line = "";
                     }
                     else
                     {
                        m_chunk_state = 1;
                        m_chunk_line = "";
                     }
                  }
                  break;
               case 1:
               {
                  size_t left = len - ptr;
                  size_t sz = m_chunk_size < left ? m_chunk_size : left;
                  OnData(buf + ptr, sz);
                  m_chunk_size -= sz;
                  ptr += sz;
                  if (!m_chunk_size)
                  {
                     m_chunk_state = 2;
                  }
               }
               break;
               case 2: // skip CR
                  ptr++;
                  m_chunk_state = 3;
                  break;
               case 3: // skip LF
                  ptr++;
                  m_chunk_state = 0;
                  break;
               }
            }
         }
         else if (!m_b_keepalive)
         {
            OnData(buf, len);
            /*
               request is HTTP/1.0 _or_ HTTP/1.1 and not keep-alive

               This means we destroy the connection after the response has been delivered,
               hence no need to reset all internal state variables for a ___new incoming
               request.
            */
            m_body_size_left -= len;
            if (!m_body_size_left)
            {
               OnDataComplete();
            }
         }
         else
         {
            size_t sz = m_body_size_left < len ? m_body_size_left : len;
            OnData(buf, sz);
            m_body_size_left -= sz;
            if (!m_body_size_left)
            {
               OnDataComplete();
               // prepare for next request(or response)
               SetLineProtocol( true );
               m_bFirst = true;
               m_bHeader = true;
               m_body_size_left = 0;
               if (len - sz > 0)
               {
                  memory mem;
                  mem.set_size(TCP_BUFSIZE_READ);
                  char * tmp = (char*)mem.get_data();
                  ::memory_copy(tmp,buf + sz,len - sz);
                  tmp[len - sz] = 0;
                  on_read( tmp, len - sz );
               }
            }
         }
      }
   }


   void sip_base_client_socket::OnLine(const string & line)
   {
      if (m_bFirst)
      {
         m_request.attr("remote_addr") = GetRemoteAddress().get_display_number();

         m_iFirstTime = get_nanos() / 1000;

         ::parse pa(line);
         string str = pa.getword();
         if (str.length() > 4 &&  case_insensitive_string_begins(str, "http/")) // response
         {
            m_request.attr("http_version") = str;
            m_request.attr("http_status_code") = atoi(pa.getword());
            m_request.attr("http_status") = pa.getrest();
            m_bResponse = true;
         }
         else // request
         {
            m_request.attr("http_method") = str;
            m_request.attr("https") = IsSSL();
            if(IsSSL())
            {
               m_request.attr("http_protocol") = "https";
            }
            else
            {
               m_request.attr("http_protocol") = "http";
            }
            m_request.attr("http_method") = str;
            m_request.attr("request_uri") = pa.getword();
            m_request.attr("http_version") = pa.getword();
            m_b_http_1_1 = string_ends(m_request.attr("http_version"), "/1.1");
            m_b_keepalive = m_b_http_1_1;
            m_bRequest = true;
         }
         m_bFirst = false;
         OnFirst();
         return;
      }
      if (!line.get_length())
      {
         if (m_body_size_left || !m_b_keepalive || m_b_chunked)
         {
            SetLineProtocol(false);
            m_bHeader = false;
         }
         OnHeaderComplete();
         if (!m_body_size_left && !m_b_chunked)
         {
            OnDataComplete();
         }
         return;
      }
      ::parse pa(line,":");
      string strKey = pa.getword();
      atom key(strKey.make_lower());
      string value = pa.getrest();
      OnHeader(key, value);
      if(key == "content-length")
      {
         m_body_size_left = atol(value);
      }
      if(key == "connection")
      {
         if (m_b_http_1_1)
         {
            if(case_insensitive_equals(value, "close"))
            {
               m_b_keepalive = false;
            }
            else
            {
               m_b_keepalive = true;
            }
         }
         else
         {
            if(case_insensitive_equals(value, "keep-alive"))
            {
               m_b_keepalive = true;
            }
            else
            {
               m_b_keepalive = false;
            }
         }
      }
      if (case_insensitive_equals(key, "transfer-encoding") && case_insensitive_string_ends(value, "chunked"))
      {
         m_b_chunked = true;
      }
      /* If remote end tells us to keep connection alive, and we're operating
      in http/1.1 mode (not http/1.0 mode), then we mark the socket to be
      retained. */
      if(m_b_keepalive)
      {
         SetRetain();
      }

   }


   void sip_base_client_socket::SendResponse()
   {
      informationf("");
      informationf("SendResponse");
      string msg;
      string strLine;
      string strTrace;
      strLine = m_response.attr("http_version").as_string() + " " + m_response.attr("http_status_code") + " " + m_response.attr("http_status");
      msg = strLine + "\r\n";
      strTrace = strLine;
      strTrace.replace("%", "%%");
      information(strTrace + "\n");
      for(auto assoc : m_response.m_propertysetHeader)
      {
         strLine = string(assoc.name()) +
                   ": " +
                   assoc.get_string();
         msg += strLine + "\r\n";
         strTrace = strLine;
         strTrace.replace("%", "%%");
         information(strTrace + "\n");
      }
      msg += "\r\n";
      write( msg );
   }

   void sip_base_client_socket::SendResponseBody()
   {
      //SendBuf((const ::string &) response().file()->get_data(), response().file()->get_size());
   }


   void sip_base_client_socket::SendRequest()
   {
      string msg;
      msg = m_request.attr("http_method").as_string() + " " + m_request.attr("request_uri").as_string() + " " + m_request.attr("http_version").as_string() + "\r\n";
      for(auto assoc : m_response.m_propertysetHeader)
      {
         msg += assoc.name() + ": " + assoc.get_string() + "\r\n";
      }
      msg += "\r\n";
      write( msg );
   }


   string sip_base_client_socket::MyUseragent()
   {
      string version = "C++Sockets/";
#ifdef _VERSION
      version += _VERSION;
#endif
      return version;
   }


   void sip_base_client_socket::Reset()
   {
      m_bFirst = true;
      m_bHeader = true;
      m_bRequest = false;
      m_bResponse = false;
      SetLineProtocol(true);
      m_request.clear();
      m_response.clear();
   }




   bool sip_base_client_socket::IsRequest()
   {
      return m_bRequest;
   }


   bool sip_base_client_socket::IsResponse()
   {
      return m_bResponse;
   }





   void sip_base_client_socket::url_this(const string & url_in,string & protocol,string & host,port_t& port,string & url,string & file)
   {
      ::parse pa(url_in,"/");
      protocol = pa.getword(); // http
      if (!case_insensitive_ansi_compare(protocol, "https:"))
      {
#ifdef HAVE_OPENSSL
         EnableSSL();
#else
         log("url_this", -1, "SSL not available", e_trace_level_warning);
#endif
         port = 443;
      }
      else
      {
         port = 80;
      }
      host = pa.getword();
      if (strstr(host,":"))
      {
         ::parse pa(host,":");
         pa.getword(host);
         port = static_cast<port_t>(pa.getvalue());
      }
      url = "/" + pa.getrest();
      {
         ::parse pa(url,"/");
         string tmp = pa.getword();
         while (tmp.get_length())
         {
            file = tmp;
            tmp = pa.getword();
         }
      }
   } // url_this


   sip::request & sip_base_client_socket::request()
   {
      return m_request;
   }

   sip::response & sip_base_client_socket::response()
   {
      return m_response;
   }

   property & sip_base_client_socket::inattr(const ::string & pszName)
   {
      return m_request.attr(pszName);
   }

   property_set & sip_base_client_socket::inattrs()
   {
      return m_request.attrs();
   }

   property & sip_base_client_socket::outattr(const ::string & pszName)
   {
      return m_response.attr(pszName);
   }

   property_set & sip_base_client_socket::outattrs()
   {
      return m_response.attrs();
   }

   property & sip_base_client_socket::inheader(const ::string & pszName)
   {
      return m_request.header(pszName);
   }

   property_set & sip_base_client_socket::inheaders()
   {
      return m_request.headers();
   }

   property & sip_base_client_socket::outheader(const ::string & pszName)
   {
      return m_response.header(pszName);
   }

   property_set & sip_base_client_socket::outheaders()
   {
      return m_response.headers();
   }

   void sip_base_client_socket::OnFirst()
   {

   }

   void sip_base_client_socket::OnHeader(atom key, const string & value)
   {
      //sip_base_client_socket::OnHeader(key, value);
      informationf("  (request)OnHeader %s: %s\n", (const ::string &) string(key), (const ::string &) value);
      if(key == "cookie")
      {
         m_request.cookies().parse_header(value);
         m_response.cookies().parse_header(value);
      }
      else
         m_request.header(key) = value;
   }


   void sip_base_client_socket::OnHeaderComplete()
   {
      int iStatusCode = m_response.attr("http_status_code").int32();
      string strMethod = m_response.attr("http_method");
      if(m_estate == state_free)
      {
         if(strMethod == "INVITE")
         {
            //m_estate = state_ringing;
            //         sip_event happening;
            //happening.m_ehappening = sip_event::event_invite;
            //m_pcallback->on_event(&happening);
         }
      }
      if(m_estate == state_waiting_call_trying)
      {
         if(iStatusCode >= 100 && iStatusCode < 200)
         {
            if(iStatusCode == 100)
            {
               //            m_estate = state_waiting_call_ringing;
            }
            else if(iStatusCode == 180)
            {
               //          m_estate = state_waiting_call_ok;
            }
            else
            {
               //        m_estate = state_waiting_call_ok;
            }
         }
      }
      if(m_estate == state_waiting_call_trying)
      {
         if(m_response.attr("http_status_code") == 200)
         {
            //   m_estate = state_waiting_call_ringing;
         }
      }
      /*   m_body_size_left = atol(m_request.header("content-length"));
         if (m_body_size_left > 0)
         {
            m_request.InitBody( m_body_size_left );
         }
         else
         {
            // execute
            Execute();
         }*/
   }

   void sip_base_client_socket::OnData(const ::string &, size_t)
   {
   }


   void sip_base_client_socket::OnDataComplete()
   {
   }

} // namespace sockets
