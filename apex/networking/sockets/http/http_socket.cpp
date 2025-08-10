#include "framework.h"
#include "http_socket.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/system.h"
//#include "acme/prototype/string/hex.h"
#include "acme/prototype/string/parse.h"
#include "acme/prototype/string/str.h"
#include "apex/constant/idpool.h"

#define HEAVY_HTTP_LOG 0

template < typename T >
T* non_const_of(const T* p)
{

   return (T*)p;

}

namespace sockets
{


   ::interlocked_count g_interlockedcountHttpSocketRequestSerial;


   http_socket::http_socket() :
   //:
   //::object(&h),
   //base_socket(h),
   //socket(h),
   //stream_socket(h),
   //tcp_socket(h),
           m_bFirst(true),
           m_bHeader(true),
           m_bRequest(false),
           m_bResponse(false),
           m_body_size_left(0),
           m_body_size_downloaded(0),
           m_b_http_1_1(false),
           m_b_keepalive(false),
           m_chunk_size(0),
           m_chunk_state(0),
      m_bChunked(false),
      m_iRequestIndex(-1)
   {

      //m_bOnlyHeaders = false;
      //m_bNoClose = false;

   }


   http_socket::~http_socket()
   {

   }


   void http_socket::initialize(::particle *pparticle)
   {

      tcp_socket::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_request.attr("http_version") = "HTTP/1.1";
      m_response.attr("http_version") = "HTTP/1.1";
      SetLineProtocol();
      DisableInputBuffer();

      m_request.initialize(this);

      m_response.initialize(this);

      //return estatus;

   }


   void http_socket::OnRawData(char *buf, memsize len)
   {

      if (!m_bHeader)
      {

         if (m_bChunked)
         {

            memsize ptr = 0;

            while (ptr < len)
            {

               switch (m_chunk_state)
               {
                  case 4:
                     while (ptr < len &&
                            (m_chunk_line.length() < 2 || m_chunk_line.substr(m_chunk_line.length() - 2) != "\r\n"))
                        m_chunk_line += buf[ptr++];
                     if (m_chunk_line.length() > 1 && m_chunk_line.substr(m_chunk_line.length() - 2) == "\r\n")
                     {
                        OnDataComplete();
                        // prepare for next request(or response)
                        m_bChunked = false;
                        SetLineProtocol(true);
                        m_bFirst = true;
                        m_bHeader = true;
                        m_body_size_left = 0;
                        m_body_size_downloaded = 0;
                        if (len - ptr > 0)
                        {
                           memory mem;
                           mem.set_size(TCP_BUFSIZE_READ);
                           char *tmp = (char *) mem.data();
                           ::memory_copy(tmp, buf + ptr, len - ptr);
                           tmp[len - ptr] = 0;
                           on_read(tmp, (int) (len - ptr));
                           ptr = len;
                        }
                     }
                     break;
                  case 0:
                     while (ptr < len &&
                            (m_chunk_line.length() < 2 || m_chunk_line.substr(m_chunk_line.length() - 2) != "\r\n"))
                        m_chunk_line += buf[ptr++];
                     if (m_chunk_line.length() > 1 && m_chunk_line.substr(m_chunk_line.length() - 2) == "\r\n")
                     {

                        m_chunk_line = m_chunk_line.left(m_chunk_line.length() - 2);

                        ::parse pa(m_chunk_line, ";"_ansi);

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
                     memsize left = len - ptr;
                     memsize sz = m_chunk_size < left ? m_chunk_size : left;
                     OnData(buf + ptr, sz);
                     m_chunk_size -= sz;
                     ptr += sz;
                     if (!m_chunk_size)
                     {
                        OnEndChunk();
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
         else
         {

            memsize sizeData = m_body_size_left < len ? m_body_size_left : len;

            m_body_size_left -= sizeData;

            m_body_size_downloaded += sizeData;

            OnData(buf, sizeData);

            if (!m_body_size_left)
            {

               OnDataComplete();

               if (!m_b_keepalive)
               {

                  /*
                  request is HTTP/1.0 _or_ HTTP/1.1 and not keep-alive

                  This means we destroy the connection after the response has been delivered,
                  hence no need to reset all internal state variables for a ___new incoming
                  request.
                  */

               }
               else
               {

                  // prepare for next request(or response)

                  SetLineProtocol(true);

                  m_bFirst = true;

                  m_bHeader = true;

                  m_body_size_left = 0;

                  if (len - sizeData > 0)
                  {

                     on_read(buf + sizeData, (int) (len - sizeData));

                  }

               }

            }

         }

      }

   }


   void http_socket::OnLine(const ::scoped_string & scopedstrLine)
   {

      if (m_bFirst)
      {

#if 0

         INFO(line);

#endif

         m_timeFirstTime.Now();

         ::parse pa(scopedstrLine);

         string str = pa.getword();

         if (str.length() > 4 && str.case_insensitive_begins("http/")) // response
         {

            //m_response.attr("remote_addr") = GetRemoteAddress().get_display_number();
            m_response.attr("http_version") = str;
            string strHttpStatusCode = pa.getword();

            int iStatusCode = atoi(strHttpStatusCode);
            m_response.attr("http_status_code") = iStatusCode;

            ::string strStatus = pa.getrest();
            m_response.attr("http_status") = strStatus;

            m_bResponse = true;
            m_bRequest = false;

         }
         else // request
         {

            m_iRequestIndex++;

            m_iHttpSocketRequestSerial = g_interlockedcountHttpSocketRequestSerial++;

            str.make_lower();
            //m_request.attr("remote_addr") = GetRemoteAddress().get_display_number();
            m_request.m_atomHttpMethod = str;
            m_request.attr("http_method") = str;
            m_request.attr("https") = IsSSL();
            if (IsSSL())
            {
               m_request.attr("http_protocol") = "https";
            }
            else
            {
               m_request.attr("http_protocol") = "http";
            }

            string strRequestUri = pa.getword();

            ::url::request request(strRequestUri);

            string strPath = request.path();

            string strQuery = request.query();

            //m_request.m_strRequestUri = ::url::decode(strScript) + ::str::has_character(strQuery, "?");
            
            m_request.m_strRequestUri = strRequestUri;
            
            m_request.attr("request_uri") = strRequestUri;

            ::string strHttpVersion = pa.getword();

            m_request.attr("http_version") = strHttpVersion;

            m_b_http_1_1 = strHttpVersion.ends("/1.1");

            m_b_keepalive = m_b_http_1_1;

            m_bRequest = true;

            m_bResponse = false;

         }

         m_bFirst = false;
         OnFirst();

         return;

      }

      if (!scopedstrLine.size())
      {

         if (m_body_size_left || !m_b_keepalive || m_bChunked)
         {

            SetLineProtocol(false);

            m_bHeader = false;

         }

         OnHeaderComplete();

         if (!m_body_size_left && !m_bChunked)
         {

            OnDataComplete();

         }

         return;

      }

      atom key;
      string strKey;
      string value;
      auto iFind = scopedstrLine.find_index(':');
      if (::not_found(iFind))
      {
         strKey = scopedstrLine;
      }
      else
      {
         strKey = scopedstrLine(0, iFind);
         strKey.trim();
         iFind++;
         while (character_isspace(scopedstrLine[iFind]) && iFind < scopedstrLine.size())
         {
            iFind++;
         }
         character_count iLen = scopedstrLine.size();
         while (iLen >= iFind && character_isspace(scopedstrLine[iLen - 1]))
         {
            iLen--;
         }
         value = scopedstrLine.substr(iFind, iLen - iFind);
      }

      strKey.make_lower();

      key = strKey;

      OnHeader(key, value);

      printf_line("Header Key: %s Value: %s", key.as_string().c_str(), value.c_str());

      if(key.case_insensitive_order("x-forwarded-proto") == 0)
      {

         ::string strProtocol = value;

         if (strProtocol.has_character())
         {

            if (strProtocol.case_insensitive_equals("https"))
            {

               m_request.attr("http_protocol") = "https";
               m_request.attr("https") = true;

            }
            else
            {

               m_request.attr("http_protocol") = "http";
               m_request.attr("https") = false;

            }

         }

      }
      if (key == "host")
      {

         m_request.m_strHttpHost = value;

         m_request.attr("http_host") = value;

      }
      else if (key == "content-length")
      {

         m_body_size_left = atol(value);

         m_body_size_downloaded = 0;

      }
      else if (key == "connection")
      {

         if (m_b_http_1_1)
         {

            if (case_insensitive_equals(value, "close"))
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

            if (case_insensitive_equals(value, "keep-alive"))
            {

               m_b_keepalive = true;

            }
            else
            {

               m_b_keepalive = false;

            }

         }

      }

      if (key.case_insensitive_order("transfer-encoding") == 0 && case_insensitive_string_ends(value, "chunked"))
      {
         m_bChunked = true;
      }
      /* If remote end tells us to keep connection alive, and we're operating
      in http/1.1 mode (not http/1.0 mode), then we mark the socket to be
      retained. */
      if (m_b_keepalive)
      {

         SetRetain();

      }

   }


   bool http_socket::http_filter_response_header(::property & property)
   {
      __UNREFERENCED_PARAMETER(property);
//      __UNREFERENCED_PARAMETER(straValue);
      return true;
   }


   void http_socket::SendResponse()
   {

      string msg;

      string strLine;

      ::string strHttpStatusCode = m_response.attr("http_status_code");

      if (strHttpStatusCode.case_insensitive_equals("ok"_ansi))
      {

         ::string strHttpStatus = m_response.attr("http_status");

         debug("what?!?!?!");

      }

      strLine =   m_response.attr("http_version") + " " + 
                  strHttpStatusCode + " " +
                  m_response.attr("http_status");

      msg = strLine + "\r\n";

      string strHost;

      strHost = m_response.header("host");

      if (strHost.has_character())
      {

         msg += "Host: " + strHost + "\r\n";

         information() << "Host: " << strHost;

      }

      bool bContentLength = m_response.attr("http_status_code") != 304;

      if (bContentLength)
      {

         if (!m_response.m_propertysetHeader.has_property("content-length"))
         {

            m_response.m_propertysetHeader["content-length"] = response().file()->size();

         }

      }
      else
      {

         m_response.m_propertysetHeader.erase_by_name("content-length");

      }

      for (auto & pproperty: m_response.m_propertysetHeader)
      {

         string strKey = pproperty->name();

         ::string_array_base straValue;

         if (pproperty->array_get_count() > 1)
         {

            straValue = pproperty->as_string_array();

         }
         else
         {

            straValue.add(pproperty->as_string());

         }

         if (!http_filter_response_header(*pproperty))
         {

            continue;

         }

         if (strKey.case_insensitive_order("host") == 0)
         {

            continue;

         }
         if (strKey.case_insensitive_order("set-cookie") == 0)
         {

            continue;

         }


         for (int j = 0; j < straValue.get_count(); j++)
         {

            string strValue = straValue[j];
            //         strLine = ;
            msg += strKey + ": " + strValue + "\r\n";
            //informationf("%s: %s", strKey, strValue);
         }
         //information(strTrace + "\n");
      }

      for (auto &pcookie: m_response.cookies())
      {

         msg += "Set-Cookie: " + pcookie->get_cookie_string() + "\r\n";

      }

      msg += "\r\n";

      ::string strMessage;

      ::string strTitle1;

      strTitle1.formatf("Response for request %lld ------------------------------------", get_request_serial());

      ::string strMessage2;

      strMessage2 = "\n\n" + strTitle1 + "\n";
      
      strMessage2 += m_request.m_url.as_string() + "\n";

      ::string strMsg(msg);

      strMsg.ends_eat("\r\n");
      
      strMessage2 += strMsg;

      //strMessage2 += string('-', maximum(10, strTitle1.length() - 20));

      m_strResponseLogMessage = strMessage2;

      //strMessage2 += "\n";

      //output_debug_string(strMessage2 + "\n");

      if (m_request.m_url.as_string() == "https://xn--thomasborregaardsrensen-1mc.com/")
      {

         print_line("Testing Response for https://xn--thomasborregaardsrensen-1mc.com/");

      }

      print(msg);

      if (bContentLength)
      {

         SendResponseBody();

      }

   }


   void http_socket::SendResponseBody()
   {

      if (response().m_strFile.has_character())
      {

         string strFile = response().m_strFile;

         response().m_strFile.empty();

         file_pointer spfile(e_create, this);

         //try
         //{

         if (strFile.case_insensitive_ends("Bamboo Weathered Standard.jpg"))
         {

            spfile->open(strFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);

         }
         else
         {

            spfile->open(strFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);

         }

         //   if (spfile->open(strFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none).failed())
         //   {

         //      throw ::exception(::error_io, "http_socket::SendResponseBody(1) file=" + strFile + "\n");

         //   }

         //}
         //catch (...)
         //{

         //   throw ::exception(::error_io, "http_socket::SendResponseBody(2) file=" + strFile + "\n");

         //}

         __transfer_to_writable(this, spfile, 1_MiB);

      }
      else if (response().file()->size() > 0)
      {

         response().file()->seek_to_begin();

         __transfer_to_writable(this, response().file());

      }

   }


   void http_socket::SendRequest()
   {

      string msg;

      string strLine;

      msg = m_request.attr("http_method") + " " + m_request.attr("request_uri") + " " + m_request.attr("http_version") +
            "\r\n";

      if (m_request.m_propertysetHeader["host"].has_character())
      {

         strLine = "Host: " + m_request.m_propertysetHeader["host"];

         if (m_iProxyPort > 0 ||
             (get_connect_port() != 80 && !IsSSL()) || (get_connect_port() != 443 && IsSSL()))
         {

            strLine += ":";

            strLine += ::as_string(get_connect_port());

         }

         msg += strLine + "\r\n";

      }

      for (auto & pproperty: m_request.m_propertysetHeader)
      {

         string strKey = pproperty->name();

         string strValue = pproperty->as_string();

         if (pproperty->name() == "content-type")
         {

            msg += "Content-Type: " + strValue + "\r\n";

         }
         else
         {

            if (strKey.case_insensitive_order("host") == 0)
            {

               continue;

            }

            strValue.trim();

            if (strValue.is_empty())
            {

               continue;

            }

            msg += strKey + ": " + strValue + "\r\n";

         }

      }

      msg += "\r\n";

      print(msg);

   }


   string http_socket::MyUseragent()
   {
      string version = "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:10.0) Gecko/20100101 veriview/10.0";

      //string version = "Mozilla/5.0 (Windows; U; Windows NT 6.0; int_point-BR; rv:1.9.2.13) Gecko/20101203 Firefox/3.6.13";
      //string version = "C++Sockets/";
#ifdef _VERSION
      version += _VERSION;
#endif
      return version;
   }


   void http_socket::Reset()
   {
      m_bFirst = true;
      m_bHeader = true;
      m_bRequest = false;
      m_bResponse = false;
      SetLineProtocol(true);
      m_request.clear();
      m_response.clear();
   }


   void http_socket::set_url(const ::url::url & url)
   {

      m_urlparts.from(url);

      if (m_urlparts.connect().is_secure())
      {

         ////#ifdef HAVE_OPENSSL

         EnableSSL();

         ////#else
         ////
         ////#ifndef UNIVERSAL_WINDOWS
         ////
         ////
         ////         warning() <<"url_this",-1,"SSL not available";
         ////
         ////#endif
         ////
         ////#endif
         //if(m_urlparts.connect().m_strPort.is_empty())
         //{
         //
         //   m_urlparts.m_iPort = 443;

         //}

      }
      //else
      //{

      //   if (m_urlparts.m_strPort.is_empty())
      //   {

      //      m_urlparts.m_iPort = 80;

      //   }

      //}

      //if (!strUrl.eat_before(strProtocol, "://"))
      //{

      //   return;

      //}

//      if (strProtocol.case_insensitive_equals("https") || strProtocol.case_insensitive_equals("wss"))
//      {
//
////#ifdef HAVE_OPENSSL
//
//         EnableSSL();
//
////#else
////
////#ifndef UNIVERSAL_WINDOWS
////
////
////         warning() <<"url_this",-1,"SSL not available";
////
////#endif
////
////#endif
//         port = 443;
//
//      }
//      else
//      {
//
//         port = 80;
//
//      }

      //string strPort;

      //strUrl.eat_before_let_separator(strPort, "/", true);

      //if (strPort.eat_before(strHost, ":", true))
      //{

      //   port = atoi(strPort);

      //}

      //strRequestUri = strUrl;

      //strUrl.eat_before(strFile, "?", true);

   }


   void http_socket::OnFirst()
   {
   }

   void http_socket::OnHeader(const ::atom & atom, const ::scoped_string & scopedstr)
   {



      //http_socket::OnHeader(key, value);
      /*if(key.case_insensitive_order("user-agent") == 0)
      {
         informationf("  (request)OnHeader %s: %s\n", (const_char_pointer )key, (const_char_pointer )value);
      }*/
      m_request.header(atom) = scopedstr;
      if (atom.as_string().case_insensitive_equals("cookie"))
      {
         m_request.cookies().parse_header(scopedstr);
         //m_response.cookies().parse_header(value);
      }

   }


   void http_socket::OnHeaderComplete()
   {

      string strUrl = m_request.attr("http_protocol") + "://" + m_request.header("host") + m_request.attr("request_uri");

      if (strUrl == "https://camilothomas.com/dk/calendar"_ansi)
      {

         print_line("hand_root https://camilothomas.com/dk/calendar"_ansi);

      }

      m_request.m_url = strUrl;

      //if(IsRequest())
      //{

      //   m_request.header("content-length").as(m_body_size_left);

      //   m_body_size_downloaded = 0;

      //}

      //if(IsResponse())
      //{

      //   m_response.header("content-length").as(m_body_size_left);

      //   m_body_size_downloaded = 0;

      //}

      /*if(m_bOnlyHeaders)
      {

         SetCloseAndDelete();

      }*/

   }


   void http_socket::OnData(const_char_pointer ,memsize)
   {

   }


   void http_socket::OnDataComplete()
   {
   }

   void http_socket::client_to_server(http_socket *psocket)
   {

      //m_ssl             = psocket->m_ssl;
      //m_socket          = psocket->m_socket;
      //m_bSsl            = psocket->m_bSsl;
      //m_bSslServer      = psocket->m_bSslServer;
      //m_bEnableSsl      = psocket->m_bEnableSsl;
      //m_bConnected      = psocket->m_bConnected;

      SetRemoteHostname(psocket->GetRemoteHostname());

   }


   long long http_socket::get_request_serial()
   {

      return m_iHttpSocketRequestSerial;

   }


   ::string http_socket::get_request_url_string()
   {

      return m_request.m_url.as_string();

   }


   ::string http_socket::get_short_debug_text(int i) const
   {

      ::string str;

      str = tcp_socket::get_short_debug_text(i);

      auto p = non_const_of(this);

      str += "url: "+p->get_request_url_string() + "\n";

      return str;

   }


   void http_socket::OnEndChunk()
   {


   }


   void http_socket::destroy()
   {

      m_request.clear();

      m_response.clear();

      m_plistener.release();

      tcp_socket::destroy();

   }


} // namespace sockets



