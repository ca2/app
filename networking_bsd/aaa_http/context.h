#pragma once


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


         string         m_strUrl;
         string         m_strAutoConfigScript;
         tinyjs *       m_pjs;
         ::duration           m_durationLastChecked;


         //pac(::particle * pparticle);
         pac();
         virtual ~pac();


      };


      class CLASS_DECL_APEX proxy :
         virtual public ::object
      {
      public:


         string         m_strUrl;
         bool           m_bDirect;
         string         m_strProxy;
         i32        m_iPort;
         ::duration m_durationLastChecked;


         //proxy(::particle * pparticle);
         proxy();


      };

      ::property_set                         m_setHttp;

      ::pointer< ::mutex >                              m_pmutexPac;
      string_map < ::pointer<pac >>       m_mapPac;
      ::pointer< ::mutex >                              m_pmutexProxy;
      string_map < ::pointer<proxy >>     m_mapProxy;

      ::pointer< ::mutex >                              m_pmutexDownload;
      string_array                           m_straDownloading;
      string_array                           m_straExists;
      //::sockets::socket_handler *          m_phandler;



      //context(::particle * pparticle);
      context();
      ~context();


      void on_initialize_particle() override;


      void http_system_destruct();


      DECLARE_MESSAGE_HANDLER(get);

      virtual bool http_get(::pointer<::sockets::http_client_socket>& m_psocket, const ::scoped_string & scopedstrUrl, property_set & set);
      virtual bool get(::http::session & session, const ::scoped_string & scopedstrUrl, string & str, property_set & set);
      virtual string get(::http::session & session, const ::scoped_string & scopedstrUrl, property_set & set);


      //virtual void set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * pfile);
      //virtual void clean_proxy_auth(::account::user * puser);


      virtual bool open(::pointer<::sockets::http_session>& psession, const ::string & strHost, const ::string & strProtocol, property_set & set, const ::string & strVersion);


      virtual bool request(::pointer<::sockets::http_session>& spsession, const ::scoped_string & scopedstrUrl, property_set & set);

      virtual ::payload get(const ::scoped_string & scopedstrUrl, property_set & set);

      virtual bool request(const ::scoped_string & scopedstrMethod, const ::scoped_string & scopedstrUrl, property_set & set);

      virtual bool download(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrRequest, ::payload payloadFile, property_set & set);
      virtual bool download(const ::scoped_string & scopedstrUrl, ::payload payloadFile, property_set & set);

      virtual bool put(const ::scoped_string & scopedstrUrl, memory_base & memory, property_set & set);
      virtual bool put(const ::scoped_string & scopedstrUrl, file_pointer  pfile, property_set & set);

      virtual void defer_auto_initialize_proxy_configuration();
      virtual void auto_config_proxy(i32 i);
      virtual i32 auto_config_proxy_count();
      virtual void config_proxy(const ::scoped_string & scopedstrUrl, ::sockets::http_tunnel * psocket);
      virtual void config_proxy(const ::scoped_string & scopedstrUrl, proxy * pproxy);
      virtual bool try_pac_script(const ::scoped_string & scopedstrScriptUrl, const ::scoped_string & scopedstrUrl, proxy * pproxy);

      virtual string gmdate(time_t t);

      virtual pac * get_pac(const ::scoped_string & scopedstrUrl);
      virtual proxy * get_proxy(const ::scoped_string & scopedstrUrl);

      //virtual void on_auth(property_set & set, ::apex::application * papp, string & strUrl, string & strSessId, ::pointer<::account::user>& puser);

      //application();
      //~application() override;

      void http_application_destruct();

      property_set & process_set(property_set & set, const ::scoped_string & scopedstrUrl);

      //DECLARE_MESSAGE_HANDLER(get);

      virtual bool get(::pointer<::sockets::http_client_socket>& psocket, const ::scoped_string & scopedstrUrl, property_set & set);

      virtual string api_get(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual string api_get(const ::scoped_string & scopedstrUrl);

      //virtual bool exists(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual bool exists(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual ::file::enum_type get_type(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual ::file::enum_type get_type(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set);

      virtual ::payload length(const ::scoped_string & scopedstrUrl, property_set & set);

      //virtual ::payload length(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual ::payload length(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set);

      //virtual string get(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual void _get(const ::scoped_string & scopedstrUrl, property_set & set);

      virtual void get(string & str, const ::scoped_string & scopedstrUrl, property_set & set);
      virtual void get(memory_base * pmemory, const ::scoped_string & scopedstrUrl, property_set & set);

      //virtual bool request(const ::scoped_string & scopedstrRequest, const ::scoped_string & scopedstrUrl, property_set & set);

      //virtual bool download(::pointer<::sockets::http_session>& psession, const ::scoped_string & scopedstrUrl, ::payload payloadFile, property_set & set);
      //virtual bool download(const ::scoped_string & scopedstrUrl, ::payload payloadFile, property_set & set);


      virtual bool put(const ::scoped_string & scopedstrUrl, memory_base * pmemory, property_set & set);
      //virtual bool put(const ::scoped_string & scopedstrUrl, file_pointer  pfile, property_set & set);

      virtual string locale_schema_url(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

      virtual string get_locale_schema(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

   };


} // namespace htttp



