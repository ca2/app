#include "framework.h"


namespace sockets
{


   sip_base_client_socket::sip_base_client_socket() :
      ::object(h.get_app()),
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



   sip_base_client_socket::~sip_base_client_socket()
   {
   }


   void sip_base_client_socket::OnRawData(char *buf,memsize len)
   {
      if (!m_bHeader)
      {
         if (m_b_chunked)
         {
            memsize ptr = 0;
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
                        char tmp[TCP_BUFSIZE_READ];
                        ::memcpy_dup(tmp, buf + ptr, len - ptr);
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
                     m_chunk_size = ::hex::to_u32(size_str);
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
                  memsize left = len - ptr;
                  memsize sz = m_chunk_size < left ? m_chunk_size : left;
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
               hence no need to reset all internal state variables for a memory_new incoming
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
            memsize sz = m_body_size_left < len ? m_body_size_left : len;
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
                  char tmp[TCP_BUFSIZE_READ];
                  ::memcpy_dup(tmp, buf + sz, len - sz);
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
         {

#ifdef WINDOWS

            i64 count;
            i64 freq;
            if(QueryPerformanceCounter((LARGE_INTEGER *) &count)
                  && QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
            {
               m_iFirstTime = count * 1000 * 1000 / freq;
            }
            else
            {
               m_iFirstTime= ::time::now();
            }
#else

            timeval t;
            gettimeofday(&t, nullptr);
            m_iFirstTime = t.tv_sec * 1000 * 1000 + t.tv_usec;

#endif


         }
         ::parse pa(line);
         string str = pa.getword();
         if (str.length() > 4 &&  string_begins_ci(str, "http/")) // response
         {
            m_request.attr("http_version") = str;
            m_request.attr("http_status_code") = pa.getword();
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
      string key = pa.getword();
      string value = pa.getrest();
      string lowvalue = value;
      lowvalue.make_lower();
      OnHeader(key, value, lowvalue);
      if(equals_ci(key, "content-length"))
      {
         m_body_size_left = atol(value);
      }
      if(equals_ci(key, "connection"))
      {
         if (m_b_http_1_1)
         {
            if(equals_ci(value, "close"))
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
            if(equals_ci(value, "keep-alive"))
            {
               m_b_keepalive = true;
            }
            else
            {
               m_b_keepalive = false;
            }
         }
      }
      if (equals_ci(key, "transfer-encoding") && string_ends_ci(value, "chunked"))
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
      TRACE("\n");
      TRACE("SendResponse\n");
      string msg;
      string strLine;
      string strTrace;
      strLine = m_response.attr("http_version").as_string() + " " + m_response.attr("http_status_code") + " " + m_response.attr("http_status");
      msg = strLine + "\r\n";
      strTrace = strLine;
      strTrace.replace("%", "%%");
      TRACE(strTrace + "\n");

      for(auto & prop : m_response.m_propertysetHeader)
      {
         string strLine = prop.name() + ": " + prop.get_string();
         msg += strLine + "\r\n";
         strTrace = strLine;
         strTrace.replace("%", "%%");
         TRACE(strTrace + "\n");
      }
      msg += "\r\n";
      write( msg );
   }

   void sip_base_client_socket::SendResponseBody()
   {
      //SendBuf((const char *) response().file()->get_data(), response().file()->get_size());
   }


   void sip_base_client_socket::SendRequest()
   {
      string msg;
      msg = m_request.attr("http_method").as_string() + " " + m_request.attr("request_uri").as_string() + " " + m_request.attr("http_version").as_string() + "\r\n";
      for(auto & prop: m_response.m_propertysetHeader)
      {
         msg += prop.name() + ": " + prop.get_string() + "\r\n";
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
      if (!ansi_compare_ci(protocol, "https:"))
      {

#ifdef HAVE_OPENSSL

         EnableSSL();

#else

#ifndef _UWP


         WARNING("url_this", -1, "SSL not available");

#endif

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

   property & sip_base_client_socket::inattr(const ::scoped_string & scopedstrName)
   {
      return m_request.attr(pszName);
   }

   property_set & sip_base_client_socket::inattrs()
   {
      return m_request.attrs();
   }

   property & sip_base_client_socket::outattr(const ::scoped_string & scopedstrName)
   {
      return m_response.attr(pszName);
   }

   property_set & sip_base_client_socket::outattrs()
   {
      return m_response.attrs();
   }

   property & sip_base_client_socket::inheader(const ::scoped_string & scopedstrName)
   {
      return m_request.header(pszName);
   }

   property_set & sip_base_client_socket::inheaders()
   {
      return m_request.headers();
   }

   property & sip_base_client_socket::outheader(const ::scoped_string & scopedstrName)
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

   void sip_base_client_socket::OnHeader(const string & key,const string & value, const string & lowvalue)
   {
      //sip_base_client_socket::OnHeader(key, value);
      FORMATTED_TRACE("  (request)OnHeader %s: %s\n", (const char *) key, (const char *) value);
      if(key == "cookie")
      {
         m_request.cookies().parse_header(value);
         m_response.cookies().parse_header(value);
      }
      else
         m_request.header(key) = value;
   }

   //void sip_base_client_socket::OnHeaderComplete()
   //{

   //}
   //
   void sip_base_client_socket::OnData(const char *,memsize)
   {

   }

   void sip_base_client_socket::OnHeaderComplete()
   {
      int iStatusCode = m_response.attr("http_status_code");
      string strMethod = m_response.attr("http_method");
      if(m_estate == state_free)
      {
         if(strMethod == "INVITE")
         {
            //m_estate = state_ringing;
            //         sip_event event;
            //event.m_eevent = sip_event::event_invite;
            //m_pcallback->on_event(&event);
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


} // namespace sockets



