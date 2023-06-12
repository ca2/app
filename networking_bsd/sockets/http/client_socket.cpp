#include "framework.h"
#include "apex/id.h"
//#include "apex/networking/sockets/_sockets.h"


#define HEAVY_HTTP_LOG 0


namespace hex
{


inline CLASS_DECL_APEX void upper_pad_from(char* sz, const void* p, memsize s)
{
   const u8* pb = (const u8*)p;
   sz += s * 2;
   while (s)
   {
      sz -= 2;
      upper_from(sz, *pb);
      s--;
      pb++;
   }
}

}


string dump_hex(::file::file* pfile)
{

   string strBuffer;

   char* psz = strBuffer.get_buffer((strsize)(pfile->get_size() / 16 + 1) * 80);

   ::u8 buf[16];

   memsize iPos = 0;

   //string str;

   while(true)
   {

      auto iRead = pfile->read(buf, 16);

      if (iRead <= 0)
      {

         break;

      }

      ::hex::upper_pad_from(psz, &iPos, 4);

      psz += 8;
      *psz = ' ';
      psz++;

      for (int i = 0; i < 16; i++)
      {

         if (i < iRead)
         {

            ::hex::upper_pad_from(psz, buf + i, 1);
            psz += 2;

         }
         else
         {

            *psz = ' ';
            psz++;
            *psz = ' ';
            psz++;

         }

         *psz = ' ';
         psz++;

      }

      for (int i = 0; i < iRead; i++)
      {

         if (buf[i] < 32)
         {

            *psz = '.';
            psz++;

         }
         else
         {

            *psz = (char) buf[i];
            psz++;

         }

      }

      *psz = '\n';
      psz++;

      iPos += iRead;

   }
   *psz = '\0';

   strBuffer.release_buffer();

   return strBuffer;

}


#ifdef LINUX

#include <sys/time.h>

#endif

#define HEAVY_HTTP_LOG 0

string op_sys()
{

#if defined(WINDOWS_DESKTOP)
   return "Windows";
#elif defined(LINUX)
   return "Linux";
#elif defined(MACOS)
   return "OS X";
#elif defined(APPLE_IOS)
   return "iOS";
#elif defined(ANDROID)
   return "Android";
#elif defined(UNIVERSAL_WINDOWS)
   return "Windows Store";
#else
   return "";
#endif

}



namespace sockets
{


   http_client_socket::http_client_socket() :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      m_content_length((memsize)-1),
      m_content_ptr(0),
      m_b_complete(false),
      m_b_close_when_complete(false)
   {

      m_progressinteger.m_scalar.m_psource = this;
      m_progressinteger.m_scalar.m_escalar = scalar_download_size;

      m_pfile           = nullptr;
      m_iFinalSize      = -1;

      memory_counter_increment(this);

   }


   http_client_socket::http_client_socket(const ::string & strUrlParam) //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //m_content_length((memsize)-1),
      //m_content_ptr(0),
      //m_b_complete(false),
      //m_b_close_when_complete(false)
   {

      string strRequestUri;

      url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      m_strHost                                 = m_host;
      m_request.header("host")              = m_host;
      m_request.attr("http_protocol")       = m_protocol;
      m_request.attr("request_uri")         = strRequestUri;
      m_response.attr("request_uri")        = strRequestUri;
      m_strUrl                                  = strUrlParam;

#ifdef BSD_STYLE_SOCKETS
      if (m_host.is_empty())
      {

         auto psystem = acmesystem();

         auto purl = psystem->url();

         m_strInitSSLClientContext = purl->get_server(strRequestUri);

      }
      else
      {

         m_strInitSSLClientContext = m_host;

      }
#endif

      m_strConnectHost                          = m_host;
      m_iConnectPort                            = m_port;

      m_pfile                                   = nullptr;
      m_iFinalSize                              = -1;

      memory_counter_increment(this);

   }


   http_client_socket::~http_client_socket()
   {

      memory_counter_decrement(this);

   }


   void http_client_socket::OnConnect()
   {

      m_request.attr("http_method") = http_method_string(m_emethod);

      http_tunnel::OnConnect();

   }


   void http_client_socket::OnFirst()
   {
      if (!IsResponse())
      {

         fatal() <<"OnFirst: Response expected but not received - aborting";

         SetCloseAndDelete();

      }

      m_content = m_response.attr("http_version") + " " +
                  m_response.attr("http_status_code") + " " +
                  m_response.attr("http_status") + "\r\n";
   }


   void http_client_socket::OnHeader(atom key, const string & value)
   {

#if HEAVY_HTTP_LOG
      FORMATTED_TRACE("OnHeader %s: %s", (const char*)key, (const char*)value);
#endif

      m_content += as_string(key) + ": " + value + "\r\n";
      m_response.m_propertysetHeader[key] = value;
      if (key == "content-length")
      {
         m_content_length = atoi(value);
      }
      else if (key == "content-type")
      {
         m_content_type = value;
      }
      else if (key == "set-cookie")
      {
         m_response.m_cookies.add(value);
      }
   }


   void http_client_socket::OnHeaderComplete()
   {

      http_tunnel::OnHeaderComplete();

      m_memoryfile.set_size(0);

      if(m_content_length != ((memsize) (-1)))
      {
         m_memoryfile.allocate_internal(m_content_length);

         if(outheader("content-encoding").case_insensitive_order("gzip") != 0
               && (m_response.attr("http_status_code") < 300 || m_response.attr("http_status_code") >= 400))
         {

            m_iFinalSize = m_content_length;

         }

      }

      m_memoryfile.seek_to_begin();

#if !defined(BSD_STYLE_SOCKETS)

      if(m_content_length > 0)
      {

         m_event.ResetEvent();

         m_bExpectResponse = true;

      }
      else
      {

         m_bExpectResponse = false;

      }

#endif

   }


   void http_client_socket::OnDataComplete()
   {

      information() << "OnDataComplete";

      m_b_complete = true;

      string strContentEncoding;
      
      strContentEncoding = outheader("content-encoding");

      if (strContentEncoding.case_insensitive_order("gzip") == 0)
      {

         memory_file memoryfile;

         m_memoryfile.seek_to_begin();

         acmesystem()->uncompress(&memoryfile, &m_memoryfile, "zlib");

         m_memoryfile = memoryfile;

      }

      if(m_pfile != nullptr && (m_response.attr("http_status_code") < 300 || m_response.attr("http_status_code") >= 400))
      {

         m_pfile->write(m_memoryfile.get_data(), (memsize) m_memoryfile.get_size());


#if HEAVY_HTTP_LOG
         
         m_pfile->seek_to_begin();

         string str = dump_hex(m_pfile);
         FORMATTED_TRACE("%s", m_strUrl.c_str());
         
         for (int i = 0; i < str.length(); i+=32 * 100)
         {

            ::OutputDebugStringA(str.substr(i, 32*100));

         }

#endif

      }

      OnContent();

      if(!m_bNoClose || m_b_close_when_complete)
      {

         SetCloseAndDelete();

      }

#if !defined(BSD_STYLE_SOCKETS)

      m_bExpectRequest = false;

      m_bExpectResponse = false;

#endif

   }


   void http_client_socket::OnData(const char *buf,memsize len)
   {

      if(m_response.attr("http_status_code").i32() >= 300 && m_response.attr("http_status_code").i32() <= 399)
      {

         return;

      }

      if(m_pfile != nullptr)
      {

         if(outheader("content-encoding").case_insensitive_order("gzip") != 0)
         {

            m_pfile->write(buf,len);

         }
         else
         {

            m_memoryfile.write(buf,len);

         }

      }
      else
      {

         m_memoryfile.write(buf,len);

      }

      OnDataArrived(buf, len);

      increment_scalar(scalar_download_size, len);

#if !defined(BSD_STYLE_SOCKETS)

      m_event.ResetEvent();

      m_bExpectResponse = true;

#endif

   }


   void http_client_socket::OnDataArrived(const char * buf, memsize len)
   {

      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(len);
   }


   void http_client_socket::OnDelete()
   {

      if (!m_b_complete)
      {

         information() << "OnDelete";

         m_b_complete = true;

         OnContent();

      }

   }


   const string & http_client_socket::GetContent()
   {

      return m_content;

   }


   memsize http_client_socket::GetContentLength()
   {

      if(m_content_length == ((memsize)-1))
      {

         return (memsize)m_memoryfile.get_size();

      }
      else
      {

         return (memsize)m_memoryfile.get_size();

      }

   }


   memsize http_client_socket::GetContentPtr()
   {
      return m_content_ptr;
   }

   memsize http_client_socket::GetPos()
   {
      return m_content_ptr;
   }


   bool http_client_socket::Complete()
   {

      return m_b_complete;

   }


   const unsigned char *http_client_socket::GetDataPtr() const
   {

      return m_memoryfile.get_data();

   }


   memsize http_client_socket::GetDataLength() const
   {

      return (memsize)m_memoryfile.get_size();

   }


   void http_client_socket::OnContent()
   {
   }


   void http_client_socket::SetCloseOnComplete(bool x)
   {

      m_b_close_when_complete = x;

   }


   const string & http_client_socket::GetUrlProtocol()
   {

      return m_protocol;

   }


   const string & http_client_socket::GetUrlFilename()
   {
      return m_url_filename;
   }

   const string & http_client_socket::GetContentType()
   {
      return m_content_type;
   }


   void http_client_socket::Url(const string & url_in, string & host, port_t & port)
   {

      string url;

      url_this(url_in, m_protocol, m_host, m_port, url, m_url_filename);

      m_request.attr("url") = url;

      auto psystem = acmesystem();

      auto purl = psystem->url();

      host = purl->get_server(url);

      port = (port_t) purl->get_port(url);

   }


   void http_client_socket::request_url(string strUrlParam)
   {
      string strRequestUri;

      url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      m_request.attr("http_protocol")     = m_protocol;
      m_request.header("host")                   = m_host;
      m_request.attr("request_uri")       = strRequestUri;
      m_response.attr("request_uri")      = strRequestUri;

      m_strUrl = strUrlParam;

      m_pfile = nullptr;

   }


   void http_client_socket::on_set_scalar(enum_scalar escalar,i64 iValue,int iFlags)
   {

      if (escalar == scalar_download_size)
      {

         m_content_ptr = (memsize) iValue;

      }
      else
      {

         return ::int_scalar_source::on_set_scalar(escalar, iValue, iFlags);

      }

   }


   void http_client_socket::get_scalar_minimum(enum_scalar escalar, i64 & i)
   {

      if (escalar == scalar_download_size)
      {

         i = 0;

      }
      else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }

   void http_client_socket::get_scalar(enum_scalar escalar, i64 & i)
   {

      if (escalar == scalar_download_size)
      {

         i = m_content_ptr;

      }
      else
      {

         ::int_scalar_source::get_scalar(escalar, i);

      }

   }

   void http_client_socket::get_scalar_maximum(enum_scalar escalar, i64 & i)
   {

      if (escalar == scalar_download_size)
      {

         i = m_content_length;

      }
      else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }

   CLASS_DECL_APEX string http_method_string(e_http_method emethod)
   {

      switch (emethod)
      {
      case http_method_get:

         return "GET";

      case http_method_post:

         return "POST";

      case http_method_put:

         return "PUT";

      default:

         return "GET";

      }

   }


   CLASS_DECL_APEX e_http_method string_http_method(const ::string & str)
   {

      string strMethod(str);

      strMethod.make_lower();

      if (strMethod == "get")
      {

         return http_method_get;

      }
      else if (strMethod == "post")
      {

         return http_method_post;

      }
      else if (strMethod == "put")
      {

         return http_method_put;

      }
      else
      {

         return http_method_get;

      }

   }


   string http_client_socket::MyUseragent()
   {

      string strAddUp;

      if (get_app()->m_papexapplication->m_strHttpUserAgentToken.has_char() && get_app()->m_papexapplication->m_strHttpUserAgentVersion.has_char())
      {

         strAddUp = get_app()->m_papexapplication->m_strHttpUserAgentToken + "/" + get_app()->m_papexapplication->m_strHttpUserAgentVersion;

      }
      else
      {

         strAddUp = "ca2/1.0";

      }

#ifdef WINDOWS
      return "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (ca2, like Gecko) " + strAddUp;
#elif defined(MACOS)
      return "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12) AppleWebKit/537.36 (ca2, like Gecko) " + strAddUp;
#elif defined(LINUX)
      return "Mozilla/5.0 (Linux; x86_64) AppleWebKit/537.36 (ca2, like Gecko) " + strAddUp;
#elif defined(FREEBSD)
      return "Mozilla/5.0 (Linux; x86_64) AppleWebKit/537.36 (ca2, like Gecko) " + strAddUp;
#elif defined(APPLE_IOS)
      return "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12) AppleWebKit/537.36 (ca2, like Gecko) " + strAddUp;
#elif defined(ANDROID)
      return "Mozilla/5.0 (Android; x86) AppleWebKit/537.36 (ca2, like Gecko) " + strAddUp;
#else
      throw ::exception(todo);
#endif
//      string str;
//
//      string strSockets = "ca2-sockets/0.1";
//
//      string strOpSys = op_sys();
//
//      if (get_app()->m_strAppName.has_char())
//      {
//
//         str += get_app()->m_strAppName;
//
//         str += " (";
//
//         if (strOpSys.has_char())
//         {
//
//            str += strOpSys;
//
//            str += ";";
//
//         }
//
//         str += strSockets;
//
//         str += ";)";
//
//      }
//      else
//      {
//
//         str += strSockets;
//
//         str += " (";
//
//         if (strOpSys.has_char())
//         {
//
//            str += strOpSys;
//
//            str += ";";
//
//         }
//
//         str += ")";
//
//      }
//
//      return str;

   }

} // namespace sockets


namespace http
{

   session::session()
      //::particle * pparticle) :
      //m_handler(pparticle)
   {

      //m_handler.EnablePool();

   }


   session::~session()
   {


   }

}
