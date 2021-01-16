#pragma once


namespace http
{


   class CLASS_DECL_APEX context :
      virtual public ::object
   {
   public:


      ::property_set       m_setHttp;


      class CLASS_DECL_APEX pac :
         virtual public ::object
      {
      public:


         string         m_strUrl;
         string         m_strAutoConfigScript;
         tinyjs *       m_pjs;
         millis           m_millisLastChecked;


         pac(::layered * pobjectContext);
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
         millis m_millisLastChecked;


         proxy(::layered * pobjectContext);


      };

      ::mutex * m_pmutexPac;
      string_map < __pointer(pac)  >         m_mapPac;
      ::mutex * m_pmutexProxy;
      string_map < __pointer(proxy)  >       m_mapProxy;

      ::mutex * m_pmutexDownload;
      string_array                                m_straDownloading;
      string_array                                m_straExists;
      //::sockets::socket_handler *          m_phandler;



      //context(::layered * pobjectContext);
      context();
      virtual ~context();


      void http_system_destruct();


      DECL_GEN_SIGNAL(get);

      virtual bool http_get(::sockets::socket_handler & handler, __pointer(::sockets::http_client_socket) & m_psocket, const char * pszUrl, property_set & set);
      virtual bool get(::http::session & session, const char * pszUrl, string & str, property_set & set);
      virtual string get(::http::session & session, const char * pszUrl, property_set & set);


      //virtual void set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * pfile);
      //virtual void clean_proxy_auth(::account::user * puser);


      virtual bool open(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const char * pszHost, const char * pszProtocol, property_set & set, const char * pszVersion);


      virtual bool request(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & spsession, const char * pszUrl, property_set & set);

      virtual bool exists(const char * pszUrl, property_set & set);
      virtual bool is_file_or_dir(const char * pszUrl, property_set & set, ::file::enum_type * petype = nullptr);

      virtual payload length(const char * pszUrl, property_set & set);

      virtual payload get(const char * pszUrl, property_set & set);

      virtual bool request(const char * pszMethod, const char * pszUrl, property_set & set);

      virtual bool download(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const char * pszRequest, payload varFile, property_set & set);
      virtual bool download(const char * pszUrl, payload varFile, property_set & set);

      virtual bool put(const char * pszUrl, memory_base & memory, property_set & set);
      virtual bool put(const char * pszUrl, file_pointer  pfile, property_set & set);

      virtual void defer_auto_initialize_proxy_configuration();
      virtual void auto_config_proxy(i32 i);
      virtual i32 auto_config_proxy_count();
      virtual void config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket);
      virtual void config_proxy(const char * pszUrl, proxy * pproxy);
      virtual bool try_pac_script(const char * pszScriptUrl, const char * pszUrl, proxy * pproxy);

      virtual string gmdate(time_t t);

      virtual pac * get_pac(const char * pszUrl);
      virtual proxy * get_proxy(const char * pszUrl);

      //virtual void on_auth(property_set & set, ::apex::application * papp, string & strUrl, string & strSessId, __pointer(::account::user) & puser);

      //application();
      //virtual ~application();

      void http_application_destruct();

      property_set & process_set(property_set & set, const char * pszUrl);

      //DECL_GEN_SIGNAL(get);

      virtual bool get(::sockets::socket_handler & handler, __pointer(::sockets::http_client_socket) & psocket, const char * pszUrl, property_set & set);

      virtual string api_get(const char * pszUrl, property_set & set);
      virtual string api_get(const char * pszUrl);

      //virtual bool exists(const char * pszUrl, property_set & set);
      virtual bool is_file_or_dir(const char * pszUrl, payload * pvarQuery, ::file::enum_type * petype, property_set & set);

      //virtual payload length(const char * pszUrl, property_set & set);
      virtual payload length(const char * pszUrl, payload * pvarQuery, property_set & set);

      //virtual string get(const char * pszUrl, property_set & set);
      virtual ::e_status _get(const char * pszUrl, property_set & set);

      virtual ::e_status get(string & str, const char * pszUrl, property_set & set);
      virtual ::e_status get(memory_base * pmemory, const char * pszUrl, property_set & set);

      //virtual bool request(const char * pszRequest, const char * pszUrl, property_set & set);

      //virtual bool download(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const char * pszUrl, payload varFile, property_set & set);
      //virtual bool download(const char * pszUrl, payload varFile, property_set & set);


      virtual bool put(const char * pszUrl, memory_base * pmemory, property_set & set);
      //virtual bool put(const char * pszUrl, file_pointer  pfile, property_set & set);

      virtual string locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema);

      virtual string get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema);

   };


} // namespace htttp



