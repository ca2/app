#pragma once


//#include "acme/prototype/prototype/payload.h"
#include "acme/prototype/collection/string_map.h"
////#include "acme/prototype/prototype/object.h"


namespace http
{


   class CLASS_DECL_APEX context :
      virtual public ::object
   {
   public:



      class CLASS_DECL_APEX pac :
         virtual public ::object
      {
      public:


         ::url::url           m_url;
         string               m_strAutoConfigScript;
         tinyjs *             m_pjs;
         class ::time         m_timeLastChecked;


         //pac(::particle * pparticle);
         pac();
         virtual ~pac();


      };


      class CLASS_DECL_APEX proxy :
         virtual public ::object
      {
      public:


         ::url::url        m_url;
         bool              m_bDirect;
         string            m_strProxy;
         i32               m_iPort;
         class ::time      m_timeLastChecked;


         //proxy(::particle * pparticle);
         proxy();


      };

      ::property_set                         m_setHttp;

      ::pointer < ::mutex >                  m_pmutexPac;
      string_map < ::pointer<pac >>          m_mapPac;
      ::pointer < ::mutex >                  m_pmutexProxy;
      string_map < ::pointer<proxy >>        m_mapProxy;

      //::sockets::socket_handler *          m_phandler;



      //context(::particle * pparticle);
      context();
      ~context();


      void on_initialize_particle() override;


      void http_system_destruct();

      void finalize() override;


      DECLARE_MESSAGE_HANDLER(get);

      virtual bool http_get(::pointer<::sockets::http_client_socket>& m_psocket, const ::url::url & url, property_set & set);
      virtual bool get(::http::session & session, const ::url::url & url, string & str, property_set & set);
      virtual string get(::http::session & session, const ::url::url & url, property_set & set);


      //virtual void set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * pfile);
      //virtual void clean_proxy_auth(::account::user * puser);


      virtual bool open(::pointer<::sockets::http_session>& psession, const ::url::connect & connect, property_set & set, const ::string & strVersion);


      virtual bool request(::pointer<::sockets::http_session>& spsession, const ::url::request & request, property_set & set);

      virtual ::payload get(const ::url::url & url, property_set & set);

      virtual bool request(const ::scoped_string & scopedstrMethod, const ::url::url & url, property_set & set);

      virtual bool download(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrRequest, ::payload payloadFile, property_set & set);
      virtual bool download(const ::url::url & url, ::payload payloadFile, property_set & set);

      virtual bool put(const ::url::url & url, memory_base & memory, property_set & set);
      virtual bool put(const ::url::url & url, file_pointer  pfile, property_set & set);

      virtual ::url::url get_effective_url(const ::url::url & url);

      virtual void defer_auto_initialize_proxy_configuration();
      virtual void auto_config_proxy(i32 i);
      virtual i32 auto_config_proxy_count();
      virtual void config_proxy(const ::url::url & url, ::sockets::http_tunnel * psocket);
      virtual void config_proxy(const ::url::url & url, proxy * pproxy);
      virtual bool try_pac_script(const ::scoped_string & scopedstrScriptUrl, const ::url::url & url, proxy * pproxy);

      virtual string gmdate(posix_time t);

      virtual pac * get_pac(const ::url::url & url);
      virtual proxy * get_proxy(const ::url::url & url);

      //virtual void on_auth(property_set & set, ::apex::application * papp, string & strUrl, string & strSessId, ::pointer<::account::user>& puser);

      void http_application_destruct();

      property_set & process_set(property_set & set, const ::url::url & url);

      //DECLARE_MESSAGE_HANDLER(get);

      virtual bool get(::pointer<::sockets::http_client_socket>& psocket, const ::url::url & url, property_set & set);

      //virtual string api_get(const ::url::url & url, property_set & set);
      //virtual string api_get(const ::url::url & url);

      //virtual bool exists(const ::url::url & url, property_set & set);
      virtual bool exists(const ::url::url & url, property_set & set);
      virtual ::file::enum_type get_type(const ::url::url & url, property_set & set);
      virtual ::file::enum_type get_type(const ::url::url & url, ::payload * pvarQuery, property_set & set);

      virtual ::payload length(const ::url::url & url, property_set & set);

      //virtual ::payload length(const ::url::url & url, property_set & set);
      virtual ::payload length(const ::url::url & url, ::payload * pvarQuery, property_set & set);

      //virtual string get(const ::url::url & url, property_set & set);
      virtual void _get(const ::url::url & url, property_set & set);

      virtual void get(string & str, const ::url::url & url , property_set & set);
      virtual void get(memory_base * pmemory, const ::url::url & url, property_set & set);
      
      virtual void perform(::nano::http::get * pget);

      //virtual bool request(const ::scoped_string & scopedstrRequest, const ::url::url & url, property_set & set);

      //virtual bool download(::pointer<::sockets::http_session>& psession, const ::url::url & url, ::payload payloadFile, property_set & set);
      //virtual bool download(const ::url::url & url, ::payload payloadFile, property_set & set);


      virtual bool put(const ::url::url & url, memory_base * pmemory, property_set & set);
      //virtual bool put(const ::url::url & url, file_pointer  pfile, property_set & set);

      virtual string locale_schema_url(const ::url::url & url, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

      virtual string get_locale_schema(const ::url::url & url, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

   };


} // namespace htttp



