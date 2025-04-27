// From url_department.h by camilo on 2022-11-19 04:24 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/platform/department.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/string/scoped_string_base.h"

//template < primitive_character CHARACTER >
//const CHARACTER * const_string_range_begin(const ::range < const CHARACTER* >& range)
//{
//
//   return range.begin();
//
//}
//
//template < primitive_character CHARACTER >
//const CHARACTER* const_string_range_begin(const CHARACTER* p)
//{
//
//   return p;
//
//}
//
//template < primitive_character CHARACTER >
//character_count const_string_range_size(const ::range < const CHARACTER* >& range)
//{
//
//   return range.size();
//
//}
//
//template < primitive_character CHARACTER >
//character_count const_string_range_size(const CHARACTER* p)
//{
//
//   return string_safe_length(p);
//
//}


namespace url
{


   CLASS_DECL_ACME ::string connect_string(const ::scoped_string& scopedstrProtocol, const ::scoped_string& scopedstrHost, int iPort);
   CLASS_DECL_ACME::string request_string(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery = {}, const ::scoped_string& scopedstrFragment = {});
   CLASS_DECL_ACME::string request_string(const ::scoped_string& scopedstrPath, const ::property_set& setArguments, const ::scoped_string& scopedstrFragment = {});


   class parts;


   CLASS_DECL_ACME::string decode(const ::block& block);
   CLASS_DECL_ACME::string encode(const ::block& block);
   CLASS_DECL_ACME::string encode_path(const ::block& block);


   class CLASS_DECL_ACME connect_range
   {
   protected:


      friend class url;
      friend class connect;
      friend class request_range;
      
      
      //::url::url* m_purl;
      bool                    m_bIsUrl;
      ::ansi_range            m_range{ nullptr };
      //::string                m_str;
      ::logic::boolean        m_bSecure;
      //bool                    m_bScoped = false;
      ::ansi_range            m_rangeProtocol{ nullptr };
      ::ansi_range            m_rangeHost{ nullptr };
      ::ansi_range            m_rangePort{ nullptr };
      ::ansi_range            m_rangeRequest{ nullptr };
      int                     m_iPort = -1;


      connect_range();
      connect_range(const connect_range& connectrange);
      ~connect_range();


      connect_range& operator = (const connect_range& connectrange);

      void parse(const ::const_ansi_range& ansirange);

      ::const_ansi_range request_range() const { return m_rangeRequest; }


   public:



      /// parse connect range and returns range for the request
      
      


      ::string as_string() const;
      auto protocol() const { return m_rangeProtocol; }
      auto host() const { return m_rangeHost; }
      auto port_range() const { return m_rangePort; }
      int port() const;
      ::string port_part() const;
      bool is_url() const { return m_bIsUrl; }
      bool is_secure() const;
      //bool is_scoped() const { return m_bScoped; }


   };


   class CLASS_DECL_ACME request_range
   {
   protected:


      friend class url;
      friend class request;


      ::ansi_range                  m_range{ nullptr };
      //::string                      m_str;
      //bool                          m_bScoped = false;
      ::ansi_range                  m_rangePath{ nullptr };
      ::ansi_range                  m_rangeName{ nullptr };
      ::ansi_range                  m_rangeQuery{ nullptr };
      ::ansi_range                  m_rangeFragment{ nullptr };
      ::pointer < ::property_set >  m_psetArguments;

      request_range();
      request_range(const request_range& requestrange);
      ~request_range();


      request_range& operator = (const request_range& request);


      void parse(const ::const_ansi_range& ansirange);


   public:



      //   // Example: /script%20folder/strict%20object?param1=1&param2=2
      auto as_string() const { return m_range; } // /script%20folder/strict%20object?param1=1&param2=2
      auto raw_path() const { return m_rangePath; } // /script%20folder/strict%20object
      auto path() const { return decode(this->raw_path()); } // /script folder/strict object
      auto raw_name() const { return m_rangeName; } // strict%20object
      auto name() const { return decode(this->raw_name()); } // strict object
      auto query() const { return m_rangeQuery; }// param1=1&param2=2
      auto raw_fragment() const { return m_rangeFragment; }// param1=1&param2=2
      auto fragment() const { return decode(m_rangeFragment); }// param1=1&param2=2
      //bool is_scoped() const { return m_bScoped; }

      const property_set& arguments() const;
      property_set& arguments();

      ::payload get(const ::atom& atom) const;

   };



   //class connect;
   //class request;

   //struct CLASS_DECL_ACME part
   //{

   //   enum enum_type
   //   {
   //      
   //      e_type_mixed,
   //      e_type_strict_object_with_query,
   //      e_type_strict_object_no_query,
   //      e_type_query,

   //   };

   //   enum_type      m_type;
   //   const char *   m_pszLastQuestionMarkAfterLastSlash;
   //   const char *   m_pszLastSlash;

   //   part(const char* psz);

   //};



   class CLASS_DECL_ACME connect :
      public connect_range
   {
   protected:


      ::string                      m_str;


   public:


      //::string                   m_strProtocol;
      //::string                   m_strHost;
      //int                        m_iPort;
      //::logic::boolean           m_bSecure;


      connect();
      connect(const ::scoped_string& scopedstr);
      //connect(const ::url::url & url);


      void parse(const ::scoped_string& scopedstr);


      //connect& operator = (const ::url::url & url);


      void set(const ::scoped_string& scopedstrProtocol, const ::scoped_string& scopedstrHost, int iPort = -1, ::logic::boolean booleanSecure = {});


      ::string as_string() const;


   };


   class CLASS_DECL_ACME request :
      public request_range
   {
   protected:

      ::string          m_str;
      
      void __set_href(const ::scoped_string& scopedstrHref);

      friend class ::url::parts;

   public:


      //::string                      m_strPath;
      //::pointer < property_set >    m_psetArguments;
      //::string                      m_strFragment;

      request();
      request(const ::scoped_string& scopedstr);
      //request(const::url::url& url);


      void parse(const ::scoped_string& scopedstr);
      
      //request& operator = (const::url::url& url);


      void set(const ::scoped_string& scopedstrPath);
      void set(const ::scoped_string& scopedstrPath, const ::scoped_string & scopedstrQuery);
      void set(const ::scoped_string& scopedstrPath, const ::scoped_string & scopedstrQuery, const ::scoped_string & scopedstrFragment);

      void set_query(const ::scoped_string& scopedstrKey);
      void set_query(const property_set & set);




      ::string as_string() const;


   };


   class CLASS_DECL_ACME parts
   {
   public:


      connect      m_connect;
      request      m_request;


      parts();
      parts(const ::url::url& url);
      //parts(const ::scoped_string & scopedstrConnect);
      //parts(const ::scoped_string & scopedstrConnect, const ::scoped_string& scopedstrRequest);
      ~parts();

      
      void from(const ::url::url& url);
      void set(const ::url::connect_range & connectrange);
      void set(const ::url::request_range & requestrange);
      
      void set_href(const ::scoped_string& scopedstrHref);


      auto& connect() { return m_connect; }
      auto& request() { return m_request; }
      auto& connect() const { return m_connect; }
      auto& request() const { return m_request; }
      auto& arguments() { return request().arguments(); }

      ::url::url as_url() const;
      ::string as_string() const;

   };


   //class CLASS_DECL_ACME connect
   //{
   //protected:


   //   bool                    m_bIsUrl;
   //   ::string                m_str;
   //   ::logic::boolean        m_bSecure;
   //   //bool                    m_bScoped = false;
   //   ::const_ansi_range      m_rangeProtocol{ nullptr };
   //   ::const_ansi_range      m_rangeHost{ nullptr };
   //   ::const_ansi_range      m_rangePort{ nullptr };
   //   int                     m_iPort = -1;
   //   

   //   friend ::url::url;
   //   friend ::url::request;

   //   // returns range of the request

   //   const_ansi_range __from(const ::scoped_string & scopedstr);
   //   void __from(const ::url::connect_part& connect);

   //public:



   //   connect();
   //   template < const_string_castable STRING >
   //   connect(const STRING& string)
   //   {

   //      __from(string);

   //   }
   //   connect(const ::url::connect& connect);
   //   ~connect();


   //   connect& operator = (const ::url::connect& connect);

   //   ::string as_string() const;
   //   auto protocol() const { return m_rangeProtocol; }
   //   auto host() const { return m_rangeHost; }
   //   auto port() const { return m_rangePort; }
   //   ::string port_part() const;
   //   bool is_url() const { return m_bIsUrl; }
   //   bool is_secure() const { return m_bSecure; }
   //   //bool is_scoped() const { return m_bScoped; }


   //};


   //class CLASS_DECL_ACME request
   //{
   //protected:


   //   ::string                      m_str;
   //   //bool                          m_bScoped = false;
   //   ::const_ansi_range            m_rangePath{ nullptr };
   //   ::const_ansi_range            m_rangeName{ nullptr };
   //   ::const_ansi_range            m_rangeQuery{ nullptr };
   //   ::pointer < ::property_set >  m_psetArguments;
   //   ::const_ansi_range            m_rangeFragment{ nullptr };

   //   // returns the request
   //   void __from(const ::scoped_string & scopedstr);
   //   void __from(const ::url::request_part& request);


   //   friend ::url::url;


   //public:


   //   request();
   //   template < const_string_castable STRING >
   //   request(const STRING& string) requires
   //      !::std::is_same_v < STRING, ::url::connect >
   //   {
   //      
   //      __from(string);

   //   }
   //   request(const ::url::request& request);
   //   ~request();
   //   

   //   request& operator = (const ::url::request& request);


   //   // Example: /script%20folder/strict%20object?param1=1&param2=2
   //   auto as_string() const { return m_str; } // /script%20folder/strict%20object?param1=1&param2=2
   //   auto raw_path() const { return m_rangePath; } // /script%20folder/strict%20object
   //   auto path() const { return decode(this->raw_path()); } // /script folder/strict object
   //   auto raw_name() const { return m_rangeName; } // strict%20object
   //   auto name() const { return decode(this->raw_name()); } // strict object
   //   auto query() const { return m_rangeQuery; }// param1=1&param2=2
   //   auto raw_fragment() const { return m_rangeFragment; }// param1=1&param2=2
   //   auto fragment() const { return decode(m_rangeFragment); }// param1=1&param2=2
   //   //bool is_scoped() const { return m_bScoped; }

   //   auto& arguments() { return *m_psetArguments; }


   //   ::string query(const ::scoped_string& scopedstrKey) const;


   //   
   //};




   class CLASS_DECL_ACME url
   {
   public:

      ::string                m_str;


      //const char*             m_pszRequest;

      
      //bool                    m_bScoped = false;
      ::url::connect_range    m_connectrange;
      ::url::request_range    m_requestrange;



   //public:


      url();


      template < const_string_castable STRING >
      url(const STRING & str)
      { 

         ::string strSink(str);
      
         parse(strSink);

      }


      url(const ::url::connect_range & connectrange);
      url(const ::url::connect_range & connectrange, const ::url::request_range & requestrange);
      url(const ::url::url& url);
      ~url();
      
      
      //void __from(const ::scoped_string& scopedstr);
      //void __from(const ::url::parts& parts);

      
      void parse(const ::scoped_string & scopedstr);


      //void parse(const ::url::parts & parts);


      //void construct_connect();
      //void construct_request();

      
      url& operator = (const ::url::url& url);
    

      // Example: http://website.com:80/script%20folder/strict%20object?param1=1&param2=2
      ::string as_string() const;
      auto & connect() const { return m_connectrange; }
      auto & request() const { return m_requestrange; }
      //auto request_uri() const { return m_rangeRequestUri; } // /script%20folder/strict%20object?param1=1&param2=2
      //auto raw_script() const { return m_rangeScript; } // /script%20folder/strict%20object
      //auto script() const { return decode(this->raw_script()); } // /script folder/strict object
      //auto raw_name() const { return m_rangeName; } // strict%20object
      //auto name() const { return decode(this->raw_name()); } // strict object
      //auto query() const { return m_rangeQuery; }// param1=1&param2=2


      bool is() const { return m_connectrange.is_url(); }





      //string set_parameter(const ::scoped_string & scopedstrKey, const scoped_string & scopedstr);
      //string erase_parameter(const ::string& strKey);

      //void set_parameter(string & strUrl, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstr);
      //void set_param(string & strUrl, const ::string & str, const ::string & strKey, const ::string & strParam);
      //void set_param(string & strUrl, const ::string & strKey, const ::string & strParam);
      //string string_set(string & strUrl, const ::string & strKey, ::payload payload);
      //string string_set_if_not_empty(string& strUrl, const ::string & strKey, ::payload payload);
      //::payload & var_set(::payload & varUrl, const ::string & strKey, ::payload payload);
      //property & property_set(property & propUrl, const ::string & strKey, ::payload payload);

      //string set_script(const ::string & strUrl, const ::string & strScript);
      
      //string parameters_set_if_empty_at_target(const ::string & strDest, const ::string & strSrc, bool bOverrideQuery = false);
      //string replaced_parameters_if_set_at_source(const ::string & strDest, const ::string & strSrc);
      
      //string & erase_key(string & strUrl, const ::string & strKey);
      //::payload & erase_key(::payload & varUrl, const ::string & strKey);
      //property & erase_key(property & propUrl, const ::string & strKey);

      //string object(const ::string & strScript, const ::string & strQuery);
      //string object_set(const ::string & strObject, const ::string & strKey, ::payload payload);

      //string path(const ::string & str1, const ::string & str2);
      //string path(const ::string & str1, const ::string & str2, const ::string & str3);
      //string name(const ::string & str);
      //string ::url::encode(const ::string & str);
      //string ::url::decode(const ::string & str);
      //string ::url::decode(const ::string & str, character_count iLen);

      //string query_append(const ::string & strUrl, const ::string & strQuery);
      //string query_erase(const ::string & strQuery, string_array & straKey);
      //string query_erase(const ::string & strQuery, const ::string & strKey);
      ////string query_set(const ::string & strQuery, const ::string & strKey, ::payload payload);
      //bool query_get_param(string & strValue, const ::string & strUrl, const ::string & strKey);
      //bool query_has_param(const ::string & strUrl, const ::string & strKey);
      //bool query_param_has_char(const ::string & strUrl, const ::string & strKey);

      // can return false (not_found) or string
      //::payload get_parameter(const ::string & strQuery, const ::string & strKey);
      // can return false (not_found) or string
      //::payload query_get_parameter(const ::string & strQuery, const ::string & strKey);
      //string get_param(const ::string & strQuery, const ::string & strKey);
      //string query_get_param(const ::string & strQuery, const ::string & strKey);
      //bool query_has_parameter_replace(string & strQuery, const ::string & strKey, const ::string & strValue);
      //string __query_erase(const ::string & strQuery, const ::string & strAndKeyEqual);
      //bool get_parameter(string & strValue, const ::string & strUrl, const ::string & strKey);
      //bool has_parameter(const ::string & strUrl, const ::string & strKey);
      //bool parameter_has_char(const ::string & strUrl, const ::string & strKey);
      //bool has_parameter_replace(string & strUrl, const ::string & strKey, const ::string & strValue);

      
      
      //virtual bool server_ends(string strUrl, string strRoot);


      //virtual string to_punycode(const ::string & str);
      //virtual string from_punycode(const ::string & str);
      
      //string os_fspath(string strUrl);
      
      //string os_fsname(string strUrl);
      
      //string os_fs(string strUrl, bool bPath);
      


      //virtual void defer_raw_http(::property_set & set, const ::payload & payloadUrl);
      //virtual void defer_raw_http(::property_set & set);


      //bool case_insensitive_is_protocol(const ::string & strProtocol) const;
      //bool is_http() const;
      //bool is_https(const ::string & strUrl) const;
      //bool is_http_or_https() const;
      //bool is_ftp(const ::string & strUrl) const;
      //bool is_ftps(const ::string & strUrl) const;
      //bool is_ftp_or_ftps(const ::string & strUrl) const;

      //string __query_set(const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr);

      //string __object_set(const ::scoped_string& scopedstrObject, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr);


   };


} // namespace url


