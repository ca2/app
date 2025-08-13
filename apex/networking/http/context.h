#pragma once


#include "acme/platform/http.h"
#include "acme/prototype/collection/string_map.h"
////#include "acme/prototype/prototype/object.h"


namespace http
{



   class CLASS_DECL_APEX context :
      virtual public ::platform::http
   {
   public:


      ::pointer < ::mutex >                  m_pmutexPac;
      string_map_base < ::pointer<pac >>          m_mapPac;
      ::pointer < ::mutex >                  m_pmutexProxy;
      string_map_base < ::pointer<proxy >>        m_mapProxy;

      // ::property_set                         m_setHttp;
      //
      //
      // //::sockets::socket_handler *          m_phandler;
      //
      //
      //
      // //context(::particle * pparticle);
      context();
      ~context() override;


      void on_initialize_particle() override;


      void destroy() override;


      virtual void http_system_destruct() override;

      //DECLARE_MESSAGE_HANDLER(get);

      virtual bool http_get(::pointer<::sockets::http_client_socket>& m_psocket, const ::url::url & url, ::property_set & set) override;
      virtual bool get(::http::session & session, const ::url::url & url, string & str, ::property_set & set) override;
      virtual string get(::http::session & session, const ::url::url & url, ::property_set & set) override;


      //virtual void set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * pfile);
      //virtual void clean_proxy_auth(::account::user * puser);


      virtual bool open(::pointer<::sockets::http_session>& psession, const ::url::connect_range & connectrange, ::property_set & set, const ::scoped_string & scopedstrVersion) override;


      virtual bool request(::pointer<::sockets::http_session>& spsession, const ::url::request_range & requestrange, ::property_set & set) override;

      virtual ::payload get(const ::url::url & url, ::property_set & set);

      virtual bool request(const ::scoped_string & scopedstrMethod, const ::url::url & url, ::property_set & set) override;

      virtual bool download(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrRequest, ::payload payloadFile, ::property_set & set) override;
      virtual bool download(const ::url::url & url, ::payload payloadFile, ::property_set & set) override;

      virtual bool put(const ::url::url & url, memory_base & memory, ::property_set & set) override;
      virtual bool put(const ::url::url & url, file_pointer  pfile, ::property_set & set) override;
      virtual bool put(const ::url::url & url, memory_base * pmemory, ::property_set & set) override;
      //virtual bool put(const ::url::url & url, file_pointer  pfile, ::property_set & set);


      virtual ::url::url get_effective_url(const ::url::url & url) override;

      virtual void defer_auto_initialize_proxy_configuration() override;
      virtual void auto_config_proxy(int i) override;
      virtual int auto_config_proxy_count() override;
      virtual void config_proxy(const ::url::url & url, ::sockets::http_tunnel * psocket) override;
      virtual void config_proxy(const ::url::url & url, proxy * pproxy) override;
      virtual bool try_pac_script(const ::scoped_string & scopedstrScriptUrl, const ::url::url & url, proxy * pproxy) override;

      virtual string gmdate(posix_time t) override;

      virtual pac * get_pac(const ::url::url & url) override;
      virtual proxy * get_proxy(const ::url::url & url) override;

      //virtual void on_auth(::property_set & set, ::apex::application * papp, string & strUrl, string & strSessId, ::pointer<::account::user>& puser);

      void http_application_destruct();

      ::property_set & process_set(::property_set & set, const ::url::url & url);

      void get(::http::message * pmessage) override;

      virtual bool get(::pointer<::sockets::http_client_socket>& psocket, const ::url::url & url, ::property_set & set) override;

      //virtual string api_get(const ::url::url & url, ::property_set & set);
      //virtual string api_get(const ::url::url & url);

      //virtual bool exists(const ::url::url & url, ::property_set & set);
      virtual bool exists(const ::url::url & url, ::property_set & set) override;
      virtual ::file::enum_type get_type(const ::url::url & url, ::property_set & set) override;
      virtual ::file::enum_type get_type(const ::url::url & url, ::payload * pvarQuery, ::property_set & set) override;

      virtual ::payload length(const ::url::url & url, ::property_set & set) override;

      //virtual ::payload length(const ::url::url & url, ::property_set & set);
      virtual ::payload length(const ::url::url & url, ::payload * pvarQuery, ::property_set & set) override;

      //virtual string get(const ::url::url & url, ::property_set & set);
      virtual void _get(const ::url::url & url, ::property_set & set) override;

      virtual void get(string & str, const ::url::url & url , ::property_set & set) override;
      virtual void get(memory_base * pmemory, const ::url::url & url, ::property_set & set) override;
      
      virtual void perform(::nano::http::get * pget) override;

      //virtual bool request(const ::scoped_string & scopedstrRequest, const ::url::url & url, ::property_set & set);

      //virtual bool download(::pointer<::sockets::http_session>& psession, const ::url::url & url, ::payload payloadFile, ::property_set & set);
      //virtual bool download(const ::url::url & url, ::payload payloadFile, ::property_set & set);

      virtual string locale_schema_url(const ::url::url & url, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;

      virtual string get_locale_schema(const ::url::url & url, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;

   };


} // namespace http



