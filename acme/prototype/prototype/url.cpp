// From url_department.h by camilo on 2022-11-19 04:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "url.h"
//#include "as_string.h"
#include "acme/constant/id.h"
//#include "acme/constant/idpool.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/nano/nano.h"
#include "acme/nano/idn/idn.h"
#include "acme/prototype/string/str.h"
#include "acme/platform/system.h"


#if defined(__APPLE__) || defined(__BSD__)
#include <string.h>
#endif


//::string idn_to_punycode(const ::scoped_string & scopedstr);
//::string idn_from_punycode(const ::scoped_string & scopedstr);


namespace url
{


   connect_range::connect_range()
   {


   }


   connect_range::connect_range(const connect_range& connectrange)
   {

      operator = (connectrange);

   }


   connect_range::~connect_range()
   {


   }



   bool connect_range::is_secure() const
   {

      if (m_rangeProtocol.case_insensitive_equals("https")
         || m_rangeProtocol.case_insensitive_equals("wss"))
      {

         return true;

      }
      else if (m_rangeProtocol.case_insensitive_equals("http"))
      {

         return false;

      }
      else
      {

         return m_bSecure.is_set_true();

      }

   }
   
   
   const ::property_set& request_range::arguments() const
   {

      return ((request*)this)->arguments();

   }


   ::property_set& request_range::arguments()
   {

      __defer_raw_construct_new(m_psetArguments);

      return *m_psetArguments;

   }


   ::payload request_range::get(const ::atom& atom) const
   {

      return arguments()[atom];

   }


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


   connect::connect()
   {


   }
  

   connect::connect(const ::scoped_string& scopedstr)
   {

      parse(scopedstr);

   }


   void connect::parse(const ::scoped_string& scopedstr)
   {

      m_str = scopedstr;

      connect_range::parse(m_str);

   }


   //connect& connect::operator = (const::url::url& url)
   //{

   //   m_iPort = -1;

   //   m_bSecure = false;

   //   m_strProtocol = url.connect().protocol();

   //   m_strHost = url.connect().host();

   //   ::string strPort = url.connect().port();

   //   if (m_strProtocol.case_insensitive_equals("https")
   //      || m_strProtocol.case_insensitive_equals("wss"))
   //   {

   //      m_bSecure = true;

   //   }

   //   if (strPort.is_empty())
   //   {

   //      if (m_bSecure)
   //      {

   //         m_iPort = 443;

   //      }
   //      else
   //      {

   //         m_iPort = 80;

   //      }

   //   }
   //   else
   //   {

   //      m_iPort = ::as_int(strPort);

   //   }

   //   return *this;

   //}


   ::string connect_string(const ::scoped_string& scopedstrProtocol, const ::scoped_string& scopedstrHost, int iPort)
   {

      ::string strConnect;

      strConnect = scopedstrProtocol;

      strConnect += "://";

      strConnect += scopedstrHost;

      if (iPort < 0)
      {

         //if (scopedstrProtocol.case_insensitive_equals("https")
         //   || scopedstrProtocol.case_insensitive_equals("wss")
         //   || booleanSecure.is_true(false))
         //{

         //   m_iPort = 443;

         //}
         //else
         //{

         //   m_iPort = 80;

         //}

      }
      else
      {

         if (((scopedstrProtocol.case_insensitive_equals("https")
            || scopedstrProtocol.case_insensitive_equals("wss"))
            && iPort != 443)
            ||
            ((scopedstrProtocol.case_insensitive_equals("http"))
               && iPort != 80)
            ||
            ((scopedstrProtocol.case_insensitive_equals("ftp"))
               && iPort != 21))
         {
            //{

            //   m_iPort = 443;

            //}
            //else
            //{

            //   m_iPort = 80;

            //}

            strConnect += ":" + scopedstrHost;

         }

      }

      return strConnect;

   }


   void connect::set(const ::scoped_string& scopedstrProtocol, const ::scoped_string& scopedstrHost, int iPort, ::logic::boolean booleanSecure)
   {

      ::string strConnect = connect_string(scopedstrProtocol, scopedstrHost, iPort);

      parse(strConnect);

      m_bSecure = booleanSecure;

   }


   //::string connect::as_string() const
   //{

   //   if (m_rangeProtocol.is_empty() || m_rangeHost.is_empty())
   //   {

   //      return {};

   //   }

   //   return connect_string(m_rangeProtocol, m_rangeHost, m_iPort);

   //   //::string strConnectUrl;

   //   //if (m_iPort < 0
   //   //   || (m_iPort == 443 && m_strProtocol.case_insensitive_equals("https"))
   //   //   || (m_iPort == 80 && m_strProtocol.case_insensitive_equals("http")))
   //   //{

   //   //   strConnectUrl.formatf("%s://%s", m_strProtocol.c_str(), m_strHost.c_str());

   //   //}
   //   //else
   //   //{

   //   //   strConnectUrl.formatf("%s://%s:%d", m_strProtocol.c_str(), m_strHost.c_str(), m_iPort);

   //   //}

   //   //return strConnectUrl;

   //}


   request::request()
   {


   }


   request::request(const ::scoped_string& scopedstr)
   {

      parse(scopedstr);

   }


   void request::parse(const ::scoped_string& scopedstr)
   {

      m_str = scopedstr;

      request_range::parse(m_str);

   }


   //request& request::operator = (const::url::url& url)
   //{

   //   m_strPath = url.request().path();

   //   m_psetArguments = create_network_arguments_property_set(url.request().query());

   //   m_strFragment = url.request().fragment();

   //   return *this;

   //}


   void request::set(const ::scoped_string& scopedstrPath)
   {

      auto strRequest = request_string(scopedstrPath);

      parse(strRequest);
      //m_strPath = scopedstrPath;

      //m_psetArguments.release();

      //m_strFragment.empty();

   }


   void request::__set_href(const ::scoped_string& scopedstrHref)
   {

      ::string strRequest = ::url::request_set_href(m_range, scopedstrHref);

      parse(strRequest);

   }


   void request::set(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery)
   {

      auto strRequest = request_string(scopedstrPath, scopedstrQuery);

      parse(strRequest);

      //m_strPath = scopedstrPath;

      //m_psetArguments = create_network_arguments_property_set(scopedstrQuery);

      //m_strFragment.empty();

   }


   void request::set(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrFragment)
   {

      auto strRequest = request_string(scopedstrPath, scopedstrQuery, scopedstrFragment);

      parse(strRequest);


      //m_strPath = scopedstrPath;

      //m_psetArguments = create_network_arguments_property_set(scopedstrQuery);

      //m_strFragment = scopedstrFragment;

   }


   void request::set_query(const ::scoped_string& scopedstrQuery)
   {

      auto strRequest = request_string(
         m_rangePath, 
         scopedstrQuery, 
         m_rangeFragment);

      parse(strRequest);

   }


   void request::set_query(const ::property_set & set)
   {

      auto strRequest = request_string(
         m_rangePath,
         set,
         m_rangeFragment);

      parse(strRequest);

   }





   CLASS_DECL_ACME::string request_string(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrFragment)
   {

      ::string strRequest;

      if (scopedstrPath.has_character())
      {

         strRequest = scopedstrPath;

         if (!strRequest.begins("/"))
         {

            strRequest = "/" + strRequest;

         }

      }
      else
      {

         strRequest = "/";

      }

      if (scopedstrQuery.has_character())
      {

         strRequest += "?";

         strRequest += scopedstrQuery;

      }

      if (scopedstrFragment.has_character())
      {

         strRequest += "#";
            
         strRequest += scopedstrFragment;

      }

      return strRequest;

   }


   CLASS_DECL_ACME::string request_string(const ::scoped_string & scopedstrPath, const ::property_set& setArguments, const ::scoped_string & scopedstrFragment)
   {

      ::string strQuery = setArguments.get_network_arguments();

      auto strRequest = request_string(scopedstrPath, strQuery, scopedstrFragment);

      return strRequest;

   }


   ::string request::calculate_string() const
   {

      auto strRequest = request_string(m_rangePath, arguments(), m_rangeFragment);

      return strRequest;

   }


   ::string parts::as_string() const
   {

      return m_connect.as_string() + m_request.as_string();

   }


   ::url::url parts::as_url() const
   {

      return { m_connect, m_request };

   }



   connect_range& connect_range::operator = (const connect_range& connectrange)
   {

      //m_purl->m_str = connect.m_purl->m_str;
      //m_url = connect.m_url;
      //url.m_str = connect.url.m_str;
      m_bIsUrl = connectrange.m_bIsUrl;
      m_range = connectrange.m_range;
      m_bSecure = connectrange.m_bSecure;
      m_rangeProtocol = connectrange.m_rangeProtocol;
      m_rangeHost = connectrange.m_rangeHost;
      m_rangePort = connectrange.m_rangePort;
      m_rangeRequest = connectrange.m_rangeRequest;
      m_iPort = connectrange.m_iPort;
      //m_bScoped = connect.m_bScoped;

      return *this;

   }


   //const_ansi_range connect::__from(const ::scoped_string& scopedstr)
   //{

   //   m_bIsUrl = false;

   //   url.m_str = scopedstr;

   //   //m_rangeRequest.clear();

   //   m_iPort = -1;

   //   auto pszStart = url.m_str.c_str();

   //   auto psz = pszStart;

   //   while (character_isalnum(*psz) || *psz == '-' || *psz == '_' || *psz == '.')
   //   {

   //      psz++;

   //   }

   //   if (*psz != ':')
   //   {

   //      url.m_str.empty();

   //      return {};

   //   }

   //   auto pszProtocolColon = psz;

   //   auto pszSlash = pszProtocolColon + 1;

   //   if (*pszSlash != '/')
   //   {

   //      url.m_str.empty();

   //      return {};

   //   }

   //   m_rangeProtocol.m_begin = pszStart;

   //   m_rangeProtocol.m_end = pszProtocolColon;

   //   auto pszSecondSlash = pszSlash + 1;

   //   const_char_pointer  pszHost;

   //   if (*pszSecondSlash != '/')
   //   {

   //      pszHost = pszSecondSlash;

   //      if (m_rangeProtocol.size() <= 2)
   //      {

   //         // if it is like C:/example.com,
   //         // or if it is like ca:/example.com,
   //         // heuristically determine as non url

   //         url.m_str.empty();

   //         m_rangeProtocol.clear();

   //         m_rangeHost.clear();

   //         return {};

   //      }

   //   }
   //   else
   //   {

   //      pszHost = pszSecondSlash + 1;

   //   }

   //   m_bIsUrl = true;

   //   m_rangeHost.m_begin = pszHost;

   //   auto pszRequest = strchr(scopedstrHost, '/');

   //   if (!pszRequest)
   //   {

   //      m_rangeHost.m_end = url.m_str.m_end;

   //      auto pszPortColon = strchr(scopedstrHost, ':');

   //      if (pszPortColon)
   //      {

   //         m_rangeHost.m_end = pszPortColon;

   //         m_rangePort.m_begin = pszPortColon + 1;

   //         m_iPort = ::as_int(m_rangePort);

   //         m_rangePort.m_end = url.m_str.m_end;

   //      }
   //      else
   //      {

   //         m_rangeHost.m_end = url.m_str.m_end;

   //      }

   //      return {};

   //   }

   //   m_bIsUrl = true;

   //   auto pszPortColon = strchr(scopedstrHost, ':');

   //   if (pszPortColon)
   //   {

   //      if (pszPortColon > pszRequest)
   //      {

   //         pszPortColon = nullptr;

   //      }

   //   }

   //   if (pszPortColon)
   //   {

   //      m_rangePort.m_begin = pszPortColon + 1;

   //      m_rangePort.m_end = pszRequest;

   //      m_rangeHost.m_end = pszPortColon;

   //   }
   //   else
   //   {

   //      m_rangeHost.m_end = pszRequest;

   //   }

   //   //m_rangeRequest.m_begin = pszRequest;
   //   //m_rangeRequest.m_end = url.m_str.m_end;

   //   return { pszRequest, url.m_str.m_end };

   //}


   //void connect::__from(const ::url::connect_part& connect)
   //{

   //   //m_bScoped = true;

   //   auto str = connect.as_string();

   //   __from(str);

   //   //m_rangeProtocol = connect.m_strProtocol;
   //   //m_rangeHost = connect.m_strHost;
   //   //m_rangePort.clear();
   //   ////m_rangeRequest.clear();
   //   //m_iPort = connect.m_iPort;
   //   //m_bSecure = connect.m_bSecure;

   //}


   ::string connect_range::as_string() const
   {
      return m_range;

   }

   //   //if (url.m_str.has_character())
   //   {

   //      return url.m_str;

   //   }
   //   //else if (m_bScoped)
   //   //{

   //   //   return m_rangeProtocol + "://" + m_rangeHost + this->port_part();

   //   //}
   //   //else
   //   //{

   //   //   return {};

   //   //}
   //
   //}


   int connect_range::port() const
   {

      if (m_iPort > 0)
      {

         return m_iPort;

      }

      if (m_rangeProtocol == "https"
         || m_rangeProtocol == "wss")
      {

         return 443;

      }
      else if (m_rangeProtocol == "http")
      {

         return 80;

      }

      return -1;



   }


   ::string connect_range::port_part() const
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


   request_range::request_range()
   {


   }


   request_range::request_range(const request_range& requestrange)
   {

      operator = (requestrange);

   }


   request_range::~request_range()
   {


   }


   request_range& request_range::operator = (const request_range& requestrange)
   {

      //m_purl->m_str = requestrange.m_purl->m_str;
      m_range = requestrange.m_range;
      m_rangePath = requestrange.m_rangePath;
      m_rangeName = requestrange.m_rangeName;
      m_rangeQuery = requestrange.m_rangeQuery;
      m_rangeFragment = requestrange.m_rangeFragment;
      m_psetArguments = requestrange.m_psetArguments;
      //m_bScoped = request.m_bScoped;

      return *this;

   }


   ////void request::__from(const ::scoped_string& scopedstr)
   ////{

   ////   //m_bScoped = false;

   ////   url.m_str = scopedstr;

   ////   if (scopedstr.is_empty())
   ////   {

   ////      m_rangePath.clear();

   ////      m_rangeName.clear();

   ////      m_rangeQuery.clear();

   ////      m_psetArguments.release();

   ////      m_rangeFragment.clear();

   ////      return;

   ////   }

   ////   auto pszScript = url.m_str.c_str();

   ////   auto pszLastSlashOnScript = strrchr(scopedstrScript, '/');

   ////   const_char_pointer  pszQuestion = strchr(scopedstrScript, '?');

   ////   const_char_pointer  pszFragment;

   ////   if (scopedstrQuestion)
   ////   {

   ////      pszFragment = strchr(scopedstrQuestion, '#');

   ////   }
   ////   else
   ////   {

   ////      pszFragment = strchr(scopedstrScript, '#');

   ////   }

   ////   m_rangePath.m_begin = pszScript;

   ////   auto pszPathEnd = minimum_non_null(url.m_str.m_end, minimum_non_null(scopedstrQuestion, pszFragment));

   ////   m_rangePath.m_end = pszPathEnd;

   ////   m_rangeName.m_end = pszPathEnd;

   ////   if (scopedstrLastSlashOnScript < pszPathEnd)
   ////   {

   ////      m_rangeName.m_begin = pszLastSlashOnScript + 1;

   ////   }
   ////   else if (::is_empty(scopedstrScript))
   ////   {

   ////      m_rangeName.m_begin = m_rangeName.m_end;

   ////   }
   ////   else
   ////   {

   ////      m_rangeName.m_begin = pszScript + 1;

   ////   }

   ////   if (scopedstrQuestion)
   ////   {

   ////      m_rangeQuery.m_begin = pszQuestion + 1;

   ////      if (scopedstrFragment)
   ////      {

   ////         m_rangeQuery.m_end = pszFragment;

   ////      }
   ////      else
   ////      {

   ////         m_rangeQuery.m_end = url.m_str.m_end;

   ////      }

   ////   }

   ////   if (scopedstrFragment)
   ////   {

   ////      m_rangeFragment.m_begin = pszFragment + 1;

   ////      m_rangeQuery.m_end = url.m_str.m_end;

   ////   }

   ////}


   //void request::__from(const ::url::request_part& request)
   //{

   //   m_bScoped = true;

   //   m_rangePath = request.m_strPath;
   //   m_rangeName = ::file_path_name(m_rangePath);
   //   m_rangeQuery.clear();
   //   m_psetArguments = request.m_psetArguments;
   //   m_rangeFragment = request.m_strFragment;

   //}


   url::url()
   {


   }


   //url::url(const ::scoped_string& scopedstr) /*:
   //   m_connect(scopedstr),
   //   m_request(m_connect.is_url() ?
   //      ::range < const_char_pointer >(
   //         scopedstr.begin() + m_connect.url.m_str.size(),
   //         scopedstr.size() - m_connect.url.m_str.size()) :
   //      ::range<const_char_pointer >{}) */
   //{

   //}


   url::url(const ::url::connect_range& connectrange)
   {

      parse(connectrange.as_string());

   }


   url::url(const ::url::connect_range& connectrange, const ::url::request_range& requestrange)
   {

      auto strUrl = connectrange.as_string() + requestrange.as_string();

      parse(strUrl);

   }


   url::url(const ::url::url& url)
   {

      operator =(url);

   }


   url::~url()
   {


   }


   void url::parse(const ::scoped_string& scopedstr)
   {

      m_str = scopedstr;

      m_connectrange.parse(m_str);

      m_requestrange.parse(m_connectrange.request_range());

      ///construct_connect();

      //construct_request();

   }


   void connect_range::parse(const ::const_ansi_range& ansirange)
   {

      auto range = ansirange();

      m_bIsUrl = false;

      //url.m_str = scopedstr;

      m_rangeRequest.clear();

      //purl->m_pszRequest = nullptr;

      m_iPort = -1;

      auto pszStart = range.begin();

      auto psz = pszStart;

      while (character_isalnum(*psz) || *psz == '-' || *psz == '_' || *psz == '.')
      {

         psz++;

      }

      if (*psz != ':')
      {

         m_range.clear();

         m_rangeRequest = range;

         //return {};
         return
            ;

      }

      auto pszProtocolColon = psz;

      auto pszSlash = pszProtocolColon + 1;

      if (*pszSlash != '/')
      {

         m_range.clear();

         m_rangeRequest = range;

         //return {};
         //return {};
         return;

      }

      m_range.m_begin = pszStart;

      m_rangeProtocol.m_begin = pszStart;

      m_rangeProtocol.m_end = pszProtocolColon;

      auto pszSecondSlash = pszSlash + 1;

      const_char_pointer  pszHost;

      if (*pszSecondSlash != '/')
      {

         pszHost = pszSecondSlash;

         if (m_rangeProtocol.size() <= 2)
         {

            // if it is like C:/example.com,
            // or if it is like ca:/example.com,
            // heuristically determine as non url

            m_range.clear();

            m_rangeProtocol.clear();

            m_rangeHost.clear();

            m_rangeRequest = range;

            //return {};
            return;

         }

      }
      else
      {

         pszHost = pszSecondSlash + 1;

      }

      m_bIsUrl = true;

      m_rangeHost.m_begin = pszHost;

      auto pszRequest = strchr(pszHost, '/');

      if (!pszRequest)
      {

         m_rangeHost.m_end = range.m_end;

         auto pszPortColon = strchr(pszHost, ':');

         if (pszPortColon)
         {

            m_rangeHost.m_end = pszPortColon;

            m_rangePort.m_begin = pszPortColon + 1;

            m_iPort = ::as_int(m_rangePort);

            m_rangePort.m_end = range.m_end;

            m_range.m_end = m_rangePort.m_end;

         }
         else
         {

            m_rangeHost.m_end = range.m_end;

            m_range.m_end = m_rangeHost.m_end;

         }

         //return {};
         return;

      }

      m_bIsUrl = true;

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

      m_range.m_end = pszRequest;

      m_rangeRequest.m_begin = pszRequest;

      m_rangeRequest.m_end = range.m_end;

   }


   void request_range::parse(const ::const_ansi_range & ansirange)
   {

      auto range = ansirange();

      //m_bScoped = false;

      //purl->m_str = scopedstr;

      if (range.is_empty())
      {

         m_range.clear();

         m_rangePath.clear();

         m_rangeName.clear();

         m_rangeQuery.clear();

         m_psetArguments.release();

         m_rangeFragment.clear();

         return;

      }

      m_range = range;

      auto pszScript = range.begin();

      auto pszLastSlashOnScript = strrchr(pszScript, '/');

      const_char_pointer  pszQuestion = strchr(pszScript, '?');

      const_char_pointer  pszFragment;

      if (pszQuestion)
      {

         pszFragment = strchr(pszQuestion, '#');

      }
      else
      {

         pszFragment = strchr(pszScript, '#');

      }

      m_rangePath.m_begin = pszScript;

      auto pszPathEnd = minimum_non_null(range.m_end, minimum_non_null(pszQuestion, pszFragment));

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

            m_rangeQuery.m_end = range.m_end;

         }

      }

      if (pszFragment)
      {

         m_rangeFragment.m_begin = pszFragment + 1;

         m_rangeQuery.m_end = range.m_end;

      }

   }



   url& url::operator = (const ::url::url& url)
   {

      m_str = url.m_str;
      m_connectrange = url.m_connectrange;
      m_requestrange = url.m_requestrange;

      return *this;

   }


   ::string url::as_string() const
   {

      return m_str;
      //m_connectrange.as_string() + m_requestrange.as_string();

   }


   //void url::__from(const ::scoped_string& scopedstr)
   //{

   //   m_str = scopedstr;

   //   m_connectrange.construct(this);

   //   m_request.construct(this);

   //   //m_request.__from(m_connect.__from(scopedstr));

   //}


   ////void url::parse(const ::url::parts& parts)
   //{

   //   //throw "todo1111";

   //   m_connectrange.parse(parts.connect().as_string());

   //   m_requestrange.parse(parts.request().as_string());

   //}


   char* string_append_character(char* psz, ::ansi_character ch)
   {

      *psz = ch;

      psz++;

      *psz = '\0';

      return psz;

   }


   string decode_block(const ::block& block)
   {

      auto sizeLen = block.size();

      if (sizeLen <= 0)
      {

         return {};

      }

      string strDecode;

      char* pszStart = strDecode.get_buffer(sizeLen * 4);

      auto pszDecode = pszStart;

      character_count i = 0;

      const ::ansi_character* pszEncoded = (const_char_pointer )block.begin();

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


   string _encode_block(const ::block& block, bool bPath)
   {

      string strEncoded;

      auto pszEncodedStart = strEncoded.get_buffer(block.size() * 5);

      auto pszEncoded = pszEncodedStart;

      auto pszInput = (const_char_pointer )block.begin();

      memory_set(pszEncoded, 0, block.size() * 5);

      while (*pszInput != '\0')
      {

         char ch = *pszInput;

         if (ansi_char_isalnum(ch)
            || ch == '.'
            || ch == '-'
            || ch == '_'
            || (bPath && ch == '/'))
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


   string encode_block(const ::block& block)
   {

      return _encode_block(block, false);

   }


   string encode_path_block(const ::block& block)
   {

      return _encode_block(block, true);

   }


   string decode(const ::scoped_string & scopedstr)
   {

      return decode_block(::as_block(scopedstr));

   }


   string encode(const ::scoped_string & scopedstr)
   {

      return encode_block(::as_block(scopedstr));

   }


   string encode_path(const ::scoped_string & scopedstr)
   {

      return encode_path_block(::as_block(scopedstr));

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

      m_connect.parse(url.connect().as_string());

      m_request.parse(url.request().as_string());

   }


   void parts::set(const ::url::connect_range& connectrange)
   {

      m_connect.parse(connectrange.as_string());

   }


   void parts::set(const ::url::request_range& requestrange)
   {

      m_request.parse(requestrange.as_string());

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




} // namespace url




