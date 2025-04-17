//
// Created by camilo on 2024-10-28 23:55 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   struct CLASS_DECL_ACME apex_http_layer_t
   {

      //::property_set    m_setHttp;

   };


   class CLASS_DECL_ACME apex_http_layer
   {
   public:

      virtual void http_system_destruct();


      virtual void get(::http::message * phttpmessage);


      virtual bool http_get(::pointer<::sockets::http_client_socket>& m_psocket, const ::url::url & url, ::property_set & set);
      virtual bool get(::http::session & session, const ::url::url & url, string & str, ::property_set & set);
      virtual string get(::http::session & session, const ::url::url & url, ::property_set & set);


      //virtual void set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * pfile);
      //virtual void clean_proxy_auth(::account::user * puser);


      virtual bool open(::pointer<::sockets::http_session>& psession, const ::url::connect & connect, ::property_set & set, const ::string & strVersion);


      virtual bool request(::pointer<::sockets::http_session>& spsession, const ::url::request & request, ::property_set & set);

      //virtual ::payload get(const ::url::url & url, ::property_set & set);

      virtual bool request(const ::scoped_string & scopedstrMethod, const ::url::url & url, ::property_set & set);

      virtual bool download(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrRequest, ::payload payloadFile, ::property_set & set);
      virtual bool download(const ::url::url & url, ::payload payloadFile, ::property_set & set);

      virtual bool put(const ::url::url & url, memory_base & memory, ::property_set & set);
      virtual bool put(const ::url::url & url, file_pointer  pfile, ::property_set & set);
      virtual bool put(const ::url::url & url, memory_base * pmemory, ::property_set & set);
      //virtual bool put(const ::url::url & url, file_pointer  pfile, ::property_set & set);


      virtual ::url::url get_effective_url(const ::url::url & url);

      virtual void defer_auto_initialize_proxy_configuration();
      virtual void auto_config_proxy(int i);
      virtual int auto_config_proxy_count();
      virtual void config_proxy(const ::url::url & url, ::sockets::http_tunnel * psocket);
      virtual void config_proxy(const ::url::url & url, ::http::proxy * pproxy);
      virtual bool try_pac_script(const ::scoped_string & scopedstrScriptUrl, const ::url::url & url, ::http::proxy * pproxy);

      virtual string gmdate(posix_time t);

      virtual ::http::pac * get_pac(const ::url::url & url);
      virtual ::http::proxy * get_proxy(const ::url::url & url);

      //virtual void on_auth(::property_set & set, ::apex::application * papp, string & strUrl, string & strSessId, ::pointer<::account::user>& puser);

      void http_application_destruct();

      property_set & process_set(::property_set & set, const ::url::url & url);

      //DECLARE_MESSAGE_HANDLER(get);

      virtual bool get(::pointer<::sockets::http_client_socket>& psocket, const ::url::url & url, ::property_set & set);

      //virtual string api_get(const ::url::url & url, ::property_set & set);
      //virtual string api_get(const ::url::url & url);

      //virtual bool exists(const ::url::url & url, ::property_set & set);
      virtual bool exists(const ::url::url & url, ::property_set & set);
      virtual ::file::enum_type get_type(const ::url::url & url, ::property_set & set);
      virtual ::file::enum_type get_type(const ::url::url & url, ::payload * pvarQuery, ::property_set & set);

      virtual ::payload length(const ::url::url & url, ::property_set & set);

      //virtual ::payload length(const ::url::url & url, ::property_set & set);
      virtual ::payload length(const ::url::url & url, ::payload * pvarQuery, ::property_set & set);

      //virtual string get(const ::url::url & url, ::property_set & set);
      virtual void _get(const ::url::url & url, ::property_set & set);

      virtual void get(string & str, const ::url::url & url , ::property_set & set);
      virtual void get(memory_base * pmemory, const ::url::url & url, ::property_set & set);

      virtual void perform(::nano::http::get * pget);

      //virtual bool request(const ::scoped_string & scopedstrRequest, const ::url::url & url, ::property_set & set);

      //virtual bool download(::pointer<::sockets::http_session>& psession, const ::url::url & url, ::payload payloadFile, ::property_set & set);
      //virtual bool download(const ::url::url & url, ::payload payloadFile, ::property_set & set);

      virtual string locale_schema_url(const ::url::url & url, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

      virtual string get_locale_schema(const ::url::url & url, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);


   };


} // namespace platform



