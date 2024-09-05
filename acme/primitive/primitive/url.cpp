// From url_department.h by camilo on 2022-11-19 04:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "url.h"
//#include "as_string.h"
#include "acme/constant/id.h"
//#include "acme/constant/idpool.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/nano/nano.h"
#include "acme/nano/idn/idn.h"
#include "acme/primitive/string/str.h"
#include "acme/platform/system.h"


#if defined(__APPLE__)
#include <string.h>
#endif


//::string idn_to_punycode(const ::string & str);
//::string idn_from_punycode(const ::string & str);


namespace url
{


   //url::url()
   //{

   //   m_bIsUrl = false;

   //}


   //url::url(const ::scoped_string& scopedstr)
   //{

   //   from(scopedstr);

   //}


   //url::~url()
   //{


   //}


   connect_part::connect_part()
   {


   }


   connect_part::connect_part(const ::url::connect& connect)
   {

      operator = (connect);

   }


   connect_part& connect_part::operator = (const::url::connect& connect)
   {

      m_iPort = -1;

      m_bSecure = false;

      m_strProtocol = connect.protocol();

      m_strHost = connect.host();

      ::string strPort = connect.port();

      if (m_strProtocol.case_insensitive_equals("https")
         || m_strProtocol.case_insensitive_equals("wss"))
      {

         m_bSecure = true;

      }

      if (strPort.is_empty())
      {

         if (m_bSecure)
         {

            m_iPort = 443;

         }
         else
         {

            m_iPort = 80;

         }

      }
      else
      {

         m_iPort = ::as_i32(strPort);

      }

      return *this;

   }


   void connect_part::set(const ::scoped_string& scopedstrProtocol, const ::scoped_string& scopedstrHost, ::i32 iPort, ::logic::boolean booleanSecure)
   {

      m_strProtocol = scopedstrProtocol;

      m_strHost = scopedstrProtocol;

      if (iPort < 0)
      {

         if (m_strProtocol.case_insensitive_equals("https")
            || m_strProtocol.case_insensitive_equals("wss")
            || booleanSecure.is_true(false))
         {

            m_iPort = 443;

         }
         else
         {

            m_iPort = 80;

         }

      }

      m_bSecure = booleanSecure;

   }


   ::string connect_part::as_string() const
   {

      ::string strConnectUrl;

      if (m_iPort < 0
         || (m_iPort == 443 && m_strProtocol.case_insensitive_equals("https"))
         || (m_iPort == 80 && m_strProtocol.case_insensitive_equals("http")))
      {

         strConnectUrl.formatf("%s://%s", m_strProtocol.c_str(), m_strHost.c_str());

      }
      else
      {

         strConnectUrl.formatf("%s://%s:%d", m_strProtocol.c_str(), m_strHost.c_str(), m_iPort);

      }

      return strConnectUrl;

   }


   request_part::request_part()
   {


   }


   request_part::request_part(const::url::request& request)
   {

      operator = (request);

   }


   request_part& request_part::operator = (const::url::request& request)
   {

      m_strPath = request.path();

      m_psetArguments = create_network_arguments_property_set(request.query());

      m_strFragment = request.fragment();

      return *this;

   }


   void request_part::set(const ::scoped_string& scopedstrPath)
   {

      m_strPath = scopedstrPath;

      m_psetArguments.release();

      m_strFragment.empty();

   }


   void request_part::__set_href(const ::scoped_string& scopedstrHref)
   {

      ::url::path_set_href(m_strPath, scopedstrHref);

   }


   void request_part::set(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery)
   {

      m_strPath = scopedstrPath;

      m_psetArguments = create_network_arguments_property_set(scopedstrQuery);

      m_strFragment.empty();

   }


   void request_part::set(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrFragment)
   {

      m_strPath = scopedstrPath;

      m_psetArguments = create_network_arguments_property_set(scopedstrQuery);

      m_strFragment = scopedstrFragment;

   }


   ::string request_part::as_string() const
   {

      ::string strRequest;

      if (m_strPath.has_char())
      {

         strRequest = m_strPath;

      }

      if ((m_psetArguments && m_psetArguments->has_element())
         || m_strFragment.has_char())
      {

         if (!strRequest.begins("/"))
         {

            strRequest = "/" + strRequest;

         }

         if (m_psetArguments && m_psetArguments->has_element())
         {

            strRequest += "?" + m_psetArguments->get_network_arguments();

         }

         if (m_strFragment.has_char())
         {

            strRequest += "#" + m_strFragment;

         }

      }

      return strRequest;

   }


   ::string parts::as_string() const
   {

      return m_connectpart.as_string() + m_requestpart.as_string();

   }


   ::url::url parts::as_url() const
   {

      return { m_connectpart, m_requestpart };

   }


   connect::connect()
   {


   }



   connect::connect(const ::url::connect& connect)
   {

      operator = (connect);

   }


   connect::~connect()
   {


   }





   connect& connect::operator = (const ::url::connect& connect)
   {

      m_bIsUrl = connect.m_bIsUrl;
      m_str = connect.m_str;
      m_rangeProtocol = connect.m_rangeProtocol;
      m_rangeHost = connect.m_rangeHost;
      m_rangePort = connect.m_rangePort;
      m_iPort = connect.m_iPort;
      m_bSecure = connect.m_bSecure;
      m_bScoped = connect.m_bScoped;
      m_pszRequestStart = connect.m_pszRequestStart;

      return *this;

   }


   const_ansi_range connect::__from(const ::scoped_string& scopedstr)
   {

      m_bIsUrl = false;

      m_str = scopedstr;

      m_iPort = -1;

      auto pszStart = m_str.c_str();

      auto psz = pszStart;

      while (character_isalnum(*psz) || *psz == '-' || *psz == '_' || *psz == '.')
      {

         psz++;

      }

      if (*psz != ':')
      {

         m_str.empty();

         return scopedstr;

      }

      auto pszProtocolColon = psz;

      auto pszSlash = pszProtocolColon + 1;

      if (*pszSlash != '/')
      {

         m_str.empty();

         return scopedstr;

      }

      m_bIsUrl = true;

      m_rangeProtocol.m_begin = pszStart;

      m_rangeProtocol.m_end = pszProtocolColon;

      auto pszSecondSlash = pszSlash + 1;

      const char* pszHost;

      if (*pszSecondSlash != '/')
      {

         pszHost = pszSecondSlash;

      }
      else
      {

         pszHost = pszSecondSlash + 1;

      }

      m_rangeHost.m_begin = pszHost;

      auto pszRequest = strchr(pszHost, '/');

      if (!pszRequest)
      {

         m_rangeHost.m_end = m_str.m_end;

         auto pszPortColon = strchr(pszHost, ':');

         if (pszPortColon)
         {

            m_rangeHost.m_end = pszPortColon;

            m_rangePort.m_begin = pszPortColon + 1;

            m_iPort = ::as_i32(m_rangePort);

            m_rangePort.m_end = m_str.m_end;

         }
         else
         {

            m_rangeHost.m_end = m_str.m_end;

         }

         return {};

      }

      auto pszPortColon = strchr(pszHost, ':');

      if (pszPortColon)
      {

         if (pszPortColon > pszRequest)
         {

            pszPortColon = nullptr;

         }

      }

      if (pszPortColon)
      {

         m_rangePort.m_begin = pszPortColon + 1;

         m_rangePort.m_end = pszRequest;

         m_rangeHost.m_end = pszPortColon;

      }
      else
      {

         m_rangeHost.m_end = pszRequest;

      }

      m_pszRequestStart = pszRequest;

      return { pszRequest, m_str.m_end };

   }


   void connect::__from(const ::url::connect_part& connect)
   {

      m_bScoped = true;

      m_rangeProtocol = connect.m_strProtocol;
      m_rangeHost = connect.m_strHost;
      m_rangePort.clear();
      m_iPort = connect.m_iPort;
      m_bSecure = connect.m_bSecure;
      m_pszRequestStart = nullptr;

   }


   ::string connect::as_string() const
   {

      if (m_pszRequestStart && m_pszRequestStart <= m_str.m_end)
      {

         return { m_rangeProtocol.m_begin, m_pszRequestStart };

      }
      else if (m_bScoped)
      {

         return m_rangeProtocol + "://" + m_rangeHost + this->port_part();

      }
      else
      {

         return {};

      }
   
   }


   ::string connect::port_part() const 
   { 

      if (m_rangeProtocol == "https" && m_iPort == 443)
      {

         return {};

      }
      else if (m_rangeProtocol == "http" && m_iPort == 80)
      {

         return {};

      }

      return ":" + m_rangePort;
   
   }


   request::request()
   {


   }


   request::request(const request& request)
   {

      operator = (request);

   }


   request::~request()
   {


   }


   request& request::operator = (const ::url::request& request)
   {

      m_str = request.m_str;
      m_rangeName = request.m_rangeName;
      m_rangePath = request.m_rangePath;
      m_rangeQuery = request.m_rangeQuery;
      m_rangeFragment = request.m_rangeFragment;
      m_psetArguments = request.m_psetArguments;
      m_bScoped = request.m_bScoped;

      return *this;

   }


   void request::__from(const ::scoped_string& scopedstr)
   {

      m_bScoped = false;

      m_str = scopedstr;

      if (scopedstr.is_empty())
      {

         m_rangePath.clear();

         m_rangePath.clear();


      }

      auto pszScript = m_str.c_str();

      auto pszLastSlashOnScript = strrchr(pszScript, '/');

      const char * pszQuestion = strchr(pszScript, '?');

      const char* pszFragment;

      if (pszQuestion)
      {

         pszFragment = strchr(pszQuestion, '#');

      }
      else
      {

         pszFragment = strchr(pszScript, '#');

      }

      m_rangePath.m_begin = pszScript;

      auto pszPathEnd = minimum_non_null(m_str.m_end, minimum_non_null(pszQuestion, pszFragment));

      m_rangePath.m_end = pszPathEnd;

      m_rangeName.m_end = pszPathEnd;

      if (pszLastSlashOnScript < pszPathEnd)
      {

         m_rangeName.m_begin = pszLastSlashOnScript + 1;

      }
      else if (::is_empty(pszScript))
      {

         m_rangeName.m_begin = m_rangeName.m_end;

      }
      else
      {

         m_rangeName.m_begin = pszScript + 1;

      }

      if (pszQuestion)
      {

         m_rangeQuery.m_begin = pszQuestion + 1;

         if (pszFragment)
         {

            m_rangeQuery.m_end = pszFragment;

         }
         else
         {

            m_rangeQuery.m_end = m_str.m_end;

         }

      }

      if (pszFragment)
      {

         m_rangeFragment.m_begin = pszFragment + 1;

         m_rangeQuery.m_end = m_str.m_end;

      }

   }


   void request::__from(const ::url::request_part& request)
   {

      m_bScoped = true;

      m_rangePath = request.m_strPath;
      m_rangeName = ::file_path_name(m_rangePath);
      m_rangeQuery.clear();
      m_psetArguments = request.m_psetArguments;
      m_rangeFragment = request.m_strFragment;

   }


   url::url()
   {


   }


   url::url(const ::url::connect_part& connectpart)
   {

      __from(connectpart.as_string());

   }


   url::url(const ::url::connect_part& connectpart, const ::url::request_part& requestpart)
   {

      ::string strUrl = connectpart.as_string() + requestpart.as_string();

      __from(strUrl);

   }



   url::url(const ::url::url& url)
   {

      operator =(url);

   }


   url::~url()
   {


   }


   url& url::operator = (const ::url::url& url)
   {

      m_connect = url.m_connect;
      m_request = url.m_request;

      return *this;

   }


   ::string url::as_string() const
   {

      return m_connect.as_string() + m_request.as_string();

   }


   void url::__from(const ::scoped_string& scopedstr)
   {

      m_request.__from(m_connect.__from(scopedstr));

   }


   void url::__from(const ::url::parts& parts)
   {

      m_connect.__from(parts.m_connectpart);

      m_request.__from(parts.m_requestpart);

   }


   char* string_append_character(char* psz, ::ansi_character ch)
   {

      *psz = ch;

      psz++;

      *psz = '\0';

      return psz;

   }


   string decode(const ::block& block)
   {

      auto sizeLen = block.size();

      if (sizeLen <= 0)
      {

         return {};

      }

      string strDecode;

      char* pszStart = strDecode.get_buffer(sizeLen * 4);

      auto pszDecode = pszStart;

      strsize i = 0;

      const ::ansi_character* pszEncoded = (const char*)block.begin();

      while (*pszEncoded != '\0' && i < sizeLen)
      {

         if (*pszEncoded == '+')
         {

            i++;

            *pszDecode = ' ';

            pszDecode++;

            pszEncoded++;

         }
         else if (*pszEncoded == '%')
         {

            sizeLen--;

            pszEncoded++;

            if (*pszEncoded == '%')
            {

               i++;

               *pszDecode = '%';

               pszDecode++;

               pszEncoded++;

            }
            else
            {

               i++;

               sizeLen--;

               auto nibble1 = hex::to_nibble(*pszEncoded++);

               if (nibble1 < 0)
               {

                  throw_parsing_exception("url decode: % first nibble non hex");

               }

               auto nibble2 = hex::to_nibble(*pszEncoded++);

               if (nibble2 < 0)
               {

                  throw_parsing_exception("url decode: % second nibble non hex");

               }

               *pszDecode = (char)(uchar)(((nibble1 << 4) & 0xf0) | (nibble2 & 0xf));

               pszDecode++;

            }

         }
         else
         {

            i++;

            *pszDecode = *pszEncoded;

            pszDecode++;

            pszEncoded++;

         }

      }

      strDecode.release_buffer(sizeLen);

      return ::transfer(strDecode);

   }



   string _encode(const ::block& block, bool bPath)
   {

      string strEncoded;

      auto pszEncodedStart = strEncoded.get_buffer(block.size() * 5);

      auto pszEncoded = pszEncodedStart;

      auto pszInput = (const char*)block.begin();

      memory_set(pszEncoded, 0, block.size() * 5);

      while (*pszInput != '\0')
      {

         char ch = *pszInput;

         if (ansi_char_isalnum(ch)
            || ch == '.'
            || ch == '-'
            || ch == '_'
            || (bPath && ch =='/'))
         {

            pszEncoded = string_append_character(pszEncoded, ch);

         }
         else if (ch == ' ')
         {

            if (bPath)
            {

               pszEncoded = string_append_character(pszEncoded, '%');
               pszEncoded = string_append_character(pszEncoded, '2');
               pszEncoded = string_append_character(pszEncoded, '0');

            }
            else
            {

               pszEncoded = string_append_character(pszEncoded, '+');

            }

         }
         else
         {

            pszEncoded = string_append_character(pszEncoded, '%');

            pszEncoded = string_append_character(pszEncoded, ::hex::nibble_upper_case_from((ch >> 4) & 0xf));

            pszEncoded = string_append_character(pszEncoded, ::hex::nibble_upper_case_from(ch & 0xf));

         }

         pszInput++;

      }

      strEncoded.release_buffer(pszEncoded - pszEncodedStart);

      return ::transfer(strEncoded);

   }

   
   string encode(const ::block & block)
   {

      return _encode(block, false);

   }


   string encode_path(const ::block & block)
   {

      return _encode(block, true);

   }


   parts::parts()
   {

      //m_iPort = -1;
      //m_bSecure = false;

   }


   parts::parts(const ::url::url& url)
   {

      from(url);

   }


   parts::~parts()
   {


   }


   void parts::from(const ::url::url& url)
   {

      m_connectpart = url.connect();

      m_requestpart = url.request();

   }


   void parts::set_href(const ::scoped_string& scopedstrHref)
   {

      ::url::url url(scopedstrHref);

      if (url.is())
      {

         operator=(url);

         return;

      }

      request().__set_href(url.request().as_string());

   }





   //string url::protocol() const // http
   //{

   //   return m_rangeProtocol;

   //}


   //string url::root()const // website.com:80
   //{

   //   return m_rangeRoot;

   //}


   //string url::server()const // website.com
   //{

   //   return m_rangeServer;

   //}


   //string url::port() const// 80
   //{

   //   return m_rangePort;

   //}


   //string url::name() const// strict%20object
   //{

   //   return m_rangeName;

   //}


   //string url::script()const // script folder/strict object
   //{

   //   return m_rangeScript;

   //}


   //string url::query()const // param1=1&param2=2
   //{

   //   return m_rangeQuery;

   //}


   ::string request::query(const ::scoped_string& scopedstrKey) const
   {

      return ::url::get_parameter(this->query(), scopedstrKey);

   }


} // namespace url




