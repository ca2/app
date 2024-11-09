#include "framework.h"
#include "client_socket.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/memory/counter.h"
#include "acme/prototype/prototype/url.h"
//#include "acme/prototype/string/hex.h"
#include "apex/constant/idpool.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


#define HEAVY_HTTP_LOG 0


namespace hex
{


   inline CLASS_DECL_APEX void upper_case_pad_from(char* sz, const void* p, memsize s)
   {
      const unsigned char* pb = (const unsigned char*)p;
      sz += s * 2;
      while (s)
      {
         sz -= 2;
         upper_case_from(sz, *pb);
         s--;
         pb++;
      }
   }


} // namespace hex


string dump_hex(::file::file* pfile)
{

   string strBuffer;

   char* psz = strBuffer.get_buffer((character_count)(pfile->size() / 16 + 1) * 80);

   unsigned char buf[16];

   memsize iPos = 0;

   //string str;

   while(true)
   {

      auto iRead = pfile->read({ buf, 16 });

      if (iRead <= 0)
      {

         break;

      }

      ::hex::upper_case_pad_from(psz, &iPos, 4);

      psz += 8;
      *psz = ' ';
      psz++;

      for (int i = 0; i < 16; i++)
      {

         if (i < iRead)
         {

            ::hex::upper_case_pad_from(psz, buf + i, 1);

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

      //m_progressinteger.m_scalar.m_psource = this;
      //m_progressinteger.m_scalar.m_escalar = scalar_download_size;

      m_pfile           = nullptr;
      m_iFinalSize      = -1;

      //memory_counter_increment(this);

   }


   http_client_socket::~http_client_socket()
   {

      //memory_counter_decrement(this);

   }


   void http_client_socket::initialize_http_client_socket(const ::url::url & url) //:
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

      //string strRequestUri;

      //url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      set_url(url);

      set_host(m_urlparts.connect().m_strHost);

      m_request.header("host") = get_host();

      m_request.attr("http_protocol") = m_urlparts.connect().m_strProtocol;

      ::string strRequest = m_urlparts.request().as_string();

      m_request.attr("request_uri") = strRequest;

      m_response.attr("request_uri") = strRequest;

       //set_url(strUrlParam);

//#ifdef BSD_STYLE_SOCKETS
//      
//      if (m_host.is_empty())
//      {
//
//         auto psystem = system();
//
//         auto purl = psystem->url();
//
//         set_init_ssl_client_context(purl->get_server(strRequestUri));
//
//      }
//      else
//      {
//
//         set_init_ssl_client_context(m_host);
//
//      }
//      
//#endif

      set_connect_host(get_host());

      set_connect_port(m_urlparts.connect().m_iPort);

      m_pfile = nullptr;

      m_iFinalSize = -1;

      //memory_counter_increment(this);

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
      informationf("OnHeader %s: %s", (const char*)key, (const char*)value);
#endif

      m_content += key + ": " + value + "\r\n";
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

      __defer_construct_new(m_pmemoryfile);

      m_pmemoryfile->set_size(0);

      if(m_content_length != ((memsize) (-1)))
      {
         m_pmemoryfile->allocate_internal(m_content_length);

         if(outheader("content-encoding").case_insensitive_order("gzip") != 0
               && (m_response.attr("http_status_code") < 300 || m_response.attr("http_status_code") >= 400))
         {

            m_iFinalSize = m_content_length;

         }

      }

      m_pmemoryfile->seek_to_begin();

#ifdef WINRT_SOCKETS

      if(m_content_length > 0)
      {

         m_happening.reset_happening();

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

         auto pmemoryfile = create_memory_file();

         m_pmemoryfile->seek_to_begin();

         system()->zlib_uncompress(pmemoryfile, m_pmemoryfile);

         m_pmemoryfile = pmemoryfile;

      }

      int iStatusCode = m_response.attr("http_status_code").as_int();

//      if(m_pfile != nullptr && (iStatusCode < 300 || iStatusCode >= 400))
//      {
//
//         m_pfile->write(m_pmemoryfile->data(), (memsize) m_pmemoryfile->size());
//
//#if HEAVY_HTTP_LOG
//         
//         m_pfile->seek_to_begin();
//
//         string str = dump_hex(m_pfile);
//         informationf("%s", m_strUrl.c_str());
//         
//         for (int i = 0; i < str.length(); i+=32 * 100)
//         {
//
//            ::OutputDebugStringA(str.substr(i, 32*100));
//
//         }
//
//#endif
//
//      }

      OnContent();

      //if(!m_bNoClose || m_b_close_when_complete)
      //{

      //   SetCloseAndDelete();

      //}

#ifdef WINRT_SOCKETS

      m_bExpectRequest = false;

      m_bExpectResponse = false;

#endif

   }


   void http_client_socket::OnData(const char *buf,memsize len)
   {

      if(m_response.attr("http_status_code").as_int() >= 300 && m_response.attr("http_status_code").as_int() <= 399)
      {

         return;

      }

      if(m_pfile != nullptr)
      {

         if(outheader("content-encoding").case_insensitive_equals("gzip"))
         {

            m_pmemoryfile->write({ buf,len });

         }
         else
         {

            m_pfile->write({ buf,len });

         }

      }
      else
      {

         m_pmemoryfile->write({ buf,len });

      }

      OnDataArrived(buf, len);

      //increment_scalar(scalar_download_size, len);

#ifdef WINRT_SOCKETS

      m_happening.reset_happening();

      m_bExpectResponse = true;

#endif

   }


   void http_client_socket::OnDataArrived(const char * buf, memsize len)
   {

      __UNREFERENCED_PARAMETER(buf);
      __UNREFERENCED_PARAMETER(len);
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

      if (!m_pmemoryfile)
      {

         return 0;

      }

      if(m_content_length == ((memsize)-1))
      {

         return (memsize)m_pmemoryfile->size();

      }
      else
      {

         return (memsize)m_pmemoryfile->size();

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

      return m_pmemoryfile ? m_pmemoryfile->full_data_begin() : nullptr;

   }


   memsize http_client_socket::GetDataLength() const
   {

      return (memsize)m_pmemoryfile->full_data_size();

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

      return m_urlparts.connect().m_strProtocol;

   }


   const string & http_client_socket::GetUrlFilename()
   {
      
      return m_urlparts.request().m_strPath;

   }


   const string & http_client_socket::GetContentType()
   {

      return m_content_type;

   }


   void http_client_socket::set_url(const ::url::url & url)
   {

      http_tunnel::set_url(url);

      //m_request.attr("url") = url;

      //host = purl->get_server(url);

      //port = (::networking::port_t) purl->get_port(url);

   }


   void http_client_socket::request_url(const ::url::url& url)
   {

      //string strRequestUri;

      //url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      set_url(url);

      m_request.attr("http_protocol")     = m_urlparts.connect().m_strProtocol;
      m_request.header("host")            = m_urlparts.connect().m_strHost;
      
      ::string strRequest = m_urlparts.request().as_string();

      m_request.attr("request_uri")       = strRequest;
      m_response.attr("request_uri")      = strRequest;

      //set_url(strUrlParam);

      m_pfile = nullptr;

   }


   bool http_client_socket::on_set_scalar(enum_scalar escalar,::number number,int iFlags)
   {

      if (escalar == e_scalar_download_size)
      {

         m_content_ptr = (memsize) number.get_huge_integer();

         return true;

      }
      else
      {

         return ::scalar_source::on_set_scalar(escalar, number, iFlags);

      }

   }


   ::number http_client_socket::get_scalar_minimum(enum_scalar escalar)
   {

      if (escalar == e_scalar_download_size)
      {

         return (huge_integer)0;

      }
      else
      {

         return ::scalar_source::get_scalar_minimum(escalar);

      }

   }


   ::number http_client_socket::get_scalar(enum_scalar escalar)
   {

      if (escalar == e_scalar_download_size)
      {

         return (huge_integer)m_content_ptr;

      }
      else
      {

         return ::scalar_source::get_scalar(escalar);

      }

   }


   ::number http_client_socket::get_scalar_maximum(enum_scalar escalar)
   {

      if (escalar == e_scalar_download_size)
      {

         return (huge_integer) m_content_length;

      }
      else
      {

         return ::scalar_source::get_scalar_maximum(escalar);

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


   bool http_client_socket::http_request_step()
   {

      return true;

   }


   string http_client_socket::MyUseragent()
   {

      string strAddUp;

      auto papp = get_app();

      if (get_app()->m_strHttpUserAgentToken.has_character() && get_app()->m_strHttpUserAgentVersion.has_character())
      {

         strAddUp = get_app()->m_strHttpUserAgentToken + "/" + get_app()->m_strHttpUserAgentVersion;

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
#elif defined(FREEBSD) || defined(OPENBSD)
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
//      if (get_app()->m_strAppName.has_character())
//      {
//
//         str += get_app()->m_strAppName;
//
//         str += " (";
//
//         if (strOpSys.has_character())
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
//         if (strOpSys.has_character())
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
