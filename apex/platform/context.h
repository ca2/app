#pragma once


namespace apex
{

   class context_thread;


   class CLASS_DECL_APEX context :
      virtual public ::thread,
      virtual public ::acme::context,
      virtual public ::file::listing_provider
   {
   public:


      string                              m_strStoreServerBaseUrl;

      string_to_string                    m_mapCachedLatestBuild;
      __composite(::http::context)        m_phttp;
      __composite(::dir_context)          m_pdir;
      __composite(::file_context)         m_pfile;
      __composite(::os_context)           m_poscontext;


      string                              m_strLocale;
      string                              m_strSchema;


      string_array                        m_straMatterLocatorPriority;
      string_array                        m_straMatterLocator;

      ::payload                                    m_payloadFile;
      __reference_array(::create)            m_createaPending;
      __reference_array(::create)            m_createaHistory;
      __reference(::create)                  m_pcreate;
      //__pointer(::task_pool)                 m_ptaskpool;


      // context_thread();
      // virtual ~context_thread();


      context();
      ~context() override;


      virtual void on_command_create(::create* pcreate);

      void add_create(::create* pcreate);

      create * get_create();


      string get_store_server_base_url();

      bool contains(::create* pcreate) const;

      string command_line_text() const;

      virtual void destroy() override;

      //virtual ::task_pool* taskpool() override;


      virtual void initialize_context() override;


      void clear_cache();


      bool is_system() const override;
      bool is_session() const override;
      virtual bool is_local_data() const;


      inline ::http::context& http() { return *m_phttp; }
      inline ::dir_context& dir() { return *m_pdir; }
      inline ::file_context& file() { return *m_pfile; }
      inline ::os_context * os_context() { return m_poscontext; };

      ::handle::ini ini_from_path(::file::path& path);

      ::handle::ini local_ini();

      virtual string get_locale();
      virtual string get_schema();


      virtual void locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const string& strLocale, const string& strSchema);
      virtual string get_locale_schema_dir();



      virtual bool http_download(const char* pszUrl, const char* pszFile);
      virtual string http_get(const string& strUrl, ::property_set& set);
      virtual string http_get(const char* pszUrl);

      string get_latest_build_number(const char* pszConfiguration, const char* pszAppId);

      virtual ::file::path defer_make_file_system_url(string str);
      virtual string defer_get_file_title(string str);

      ::file::path defer_process_path(::file::path path) override;
      virtual ::file::path _defer_process_path(::file::path path);
      virtual ::file::path __defer_process_path(::file::path path);

      virtual ::file::path full_process_path(::file::path path);

      virtual ::file::path defer_process_matter_path(::file::path path);

      //virtual ::file::path defer_process_relative_path(const ::file::path & path);

      virtual ::file::path get_matter_path(string strMatter);
      virtual ::file::path get_matter_cache_path(::file::path path);
      virtual ::file::path side_get_matter_path(string strMatter);


      //sclass ::hyperlink hyperlink() { return this; }


      // get a file and if there are exceptions, should show end user friendly messages
      virtual file_pointer friendly_get_file(::payload payloadFile, const ::file::e_open& eopen);


      virtual bool os_resolve_alias(::file::path& path, const char* psz, bool bNoUI = false, bool bNoMount = false);

      virtual bool _os_has_alias_in_path(const char * psz, bool bNoUI = false, bool bNoMount = false);

      virtual bool _os_resolve_alias(::file::path& path, const char* psz, bool bNoUI, bool bNoMount);

      virtual bool os_is_alias(const char* psz);

      virtual void sys_set(string strPath, string strValue);
      virtual string sys_get(string strPath, string strDefault = "");


      virtual string load_string(const char* psz);

      virtual bool perform_file_listing(::file::listing& listing) override;
      virtual bool perform_file_relative_name_listing(::file::listing& listing) override;


      //virtual ::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
      //virtual ::image_pointer matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

      //virtual ::image_pointer load_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false) override;
      //virtual ::image_pointer load_matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual ::image_pointer load_matter_icon(string_array & straMatter, string strIcon) override;
      //virtual ::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h) override;
      //virtual ::image_pointer load_thumbnail(const ::string & strPath);
      //virtual ::image_pointer load_dib(const ::file::path & pathDib) override;
      //virtual ::icon_pointer load_icon(const ::payload & payloadFile);


      //virtual void _get_image(image * pimage, const ::payload & payloadFile, bool bSync = true);
      //virtual void _matter_image(image * pimage, const ::string & strMatter, bool bSync = true);


      //virtual void _load_image(image * pimage, const ::payload & payloadFile, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual void _load_matter_image(image * pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual void _load_matter_icon(image * pimage, string_array & straMatter, string strIcon);
      //virtual void _load_thumbnail(image * pimage, const ::payload & payloadFile, int w, int h);
      //virtual void _load_thumbnail(image * pimage, const ::payload & payloadFile);
      //virtual void _load_dib(image * pimage, const ::file::path & pathDib);


      //virtual void save_image(const ::payload & payloadFile, const image * pimage, ::save_image * psaveimage = nullptr);
      //virtual void save_dib(const ::file::path & path, const image * pimage);


      //virtual ::image_pointer _load_image_from_file(const ::payload & payloadFile, const ::payload & varOptions);
      //virtual void _save_to_file(const ::payload & payloadFile, const image * pimage, const ::payload & varOptions);


      virtual string matter_locator(string strApp);
      virtual string matter_locator(::application* papp);

      virtual void on_update_matter_locator();

      virtual void add_matter_locator(string strApp);
      virtual void add_matter_locator(::application* papp);


      virtual void _load_from_file(::matter* pobject, const ::payload& payloadFile, const ::payload& varOptions);
      virtual void _save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::matter* pobject);


      inline void load_from_file(::matter* pobject, const ::payload& payloadFile, const ::payload* pvarOptions);
      inline void load_from_file(::matter* pobject, const ::payload& payloadFile);
      inline void save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::matter* pobject);
      inline void save_to_file(const ::payload& payloadFile, const ::matter* pobject);


      //virtual void destroy() override;

      file_pointer get_file(const ::payload& payloadFile, const ::file::e_open& eopen) override;


   };


} // namespace apex


