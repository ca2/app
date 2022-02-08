#pragma once


namespace url
{


   class CLASS_DECL_ACME department :
      virtual public ::acme::department
   {
   public:


      string_array                 m_straPublicDomainExtension;
      critical_section        m_csPublicDomainExtension;


      department();
      virtual ~department();


      // Example: http://veriwell.com.br:443/page?id=1
      string get_protocol(const ::string & strUrl); // http
      string get_root(const ::string & strUrl); // veriwell.com.br:443
      string get_server(const ::string & strUrl); // veriwell.com.br
      i32 get_port(const ::string & strUrl, i32 iDefault = -1); // 443
      string get_object(const ::string & strUrl); // page?id=1
      string get_script(const ::string & strUrl); // page
      string get_query(const ::string & strUrl); // id=1
      string set_key(const ::string & strUrl, const ::string & strKey, ::payload payload);
      void set_key(string & strUrl, const ::string & str, const ::string & strKey, ::payload payload);
      void set_param(string & strUrl, const ::string & str, const ::string & strKey, const ::string & strParam);
      void set_param(string & strUrl, const ::string & strKey, const ::string & strParam);
      string string_set(string & strUrl, const ::string & strKey, ::payload payload);
      string string_set_if_not_empty(string& strUrl, const ::string & strKey, ::payload payload);
      ::payload & var_set(::payload & varUrl, const ::string & strKey, ::payload payload);
      property & property_set(property & propUrl, const ::string & strKey, ::payload payload);
      string set_script(const ::string & strUrl, const ::string & strScript);
      string override_if_empty(const ::string & strDest, const ::string & strSrc, bool bOverrideQuery = false);
      string override_if_set_at_source(const ::string & strDest, const ::string & strSrc);
      string erase_key(const ::string & strUrl, const ::string & strKey);
      string string_erase(string & strUrl, const ::string & strKey);
      ::payload & var_erase(::payload & varUrl, const ::string & strKey);
      property & property_erase(property & propUrl, const ::string & strKey);
      // Example: page?id=1
      string object_get_script(const ::string & str); // page
      string object_get_query(const ::string & str); // id=1

      bool is_url(const ::string & strCandidate);
      
      string object(const ::string & strScript, const ::string & strQuery);
      string object_set(const ::string & strObject, const ::string & strKey, ::payload payload);

      string path(const ::string & str1, const ::string & str2);
      string path(const ::string & str1, const ::string & str2, const ::string & str3);
      string name(const ::string & str);
      string url_encode(const ::string & str);
      string url_decode(const ::string & str);
      string url_decode(const ::string & str, strsize iLen);

      string query_append(const ::string & strUrl, const ::string & strQuery);
      string query_erase(const ::string & strQuery, string_array & straKey);
      string query_erase(const ::string & strQuery, const ::string & strKey);
      string query_set(const ::string & strQuery, const ::string & strKey, ::payload payload);
      string query_set_param(const ::string & strQuery, const ::string & strKey, const ::string & strParam);
      bool query_get_param(string & strValue, const ::string & strUrl, const ::string & strKey);
      bool query_has_param(const ::string & strUrl, const ::string & strKey);
      bool query_param_has_char(const ::string & strUrl, const ::string & strKey);

      ::payload get_var(const ::string & strQuery, const ::string & strKey);
      ::payload query_get_var(const ::string & strQuery, const ::string & strKey);
      string get_param(const ::string & strQuery, const ::string & strKey);
      string query_get_param(const ::string & strQuery, const ::string & strKey);
      bool query_has_param_replace(string & strQuery, const ::string & strKey, const ::string & strValue);
      string __query_erase(const ::string & strQuery, const ::string & strAndKeyEqual);
      bool get_param(string & strValue, const ::string & strUrl, const ::string & strKey);
      bool has_param(const ::string & strUrl, const ::string & strKey);
      bool param_has_char(const ::string & strUrl, const ::string & strKey);
      bool has_param_replace(string & strUrl, const ::string & strKey, const ::string & strValue);

      virtual bool locale_is_eu(atom pszLocale);
      virtual bool locale_is_asia(atom pszLocale);
      virtual bool locale_is_africa(atom pszLocale);
      virtual bool locale_is_america(atom pszLocale);
      virtual bool locale_is_caribe(atom pszLocale);
      virtual bool locale_is_middle_east(atom pszLocale);
      virtual bool locale_is_south_america(atom pszLocale);
      virtual bool locale_is_latin_america(atom pszLocale);
      virtual bool locale_is_north_america(atom pszLocale);
      virtual bool locale_is_central_america(atom pszLocale);
      virtual bool locale_is_oceania(atom pszLocale);
      
      
      virtual bool server_ends(string strUrl, string strRoot);


      static string to_punycode(const ::string & str);
      static string from_punycode(const ::string & str);
      
      string os_fspath(string strUrl);
      
      string os_fsname(string strUrl);
      
      string os_fs(string strUrl, bool bPath);
      
      virtual bool is_valid_public_domain(const string& strDomain);

   };


} // namespace url



