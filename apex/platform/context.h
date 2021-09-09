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


      string_to_string                    m_mapCachedLatestBuild;
      __composite(::http::context)        m_phttp;
      __composite(::dir_context)          m_pdir;
      __composite(::file_context)         m_pfile;
      __composite(::os_context)           m_pos;


      string                              m_strLocale;
      string                              m_strSchema;


      string_array                        m_straMatterLocatorPriority;
      string_array                        m_straMatterLocator;

      ::payload                                    m_varFile;
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

      bool contains(::create* pcreate) const;

      string command_line_text() const;

      virtual ::e_status destroy() override;

      //virtual ::task_pool* taskpool() override;


      virtual ::e_status initialize_context() override;


      void clear_cache();


      bool is_system() const override;
      bool is_session() const override;
      virtual bool is_local_data() const;


      inline ::http::context& http() { return *m_phttp; }
      inline ::dir_context& dir() { return *m_pdir; }
      inline ::file_context& file() { return *m_pfile; }
      inline ::os_context& os() { return *m_pos; };

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

      virtual ::file::path defer_process_path(::file::path path);
      virtual ::file::path _defer_process_path(::file::path path);
      virtual ::file::path __defer_process_path(::file::path path);

      virtual ::file::path full_process_path(::file::path path);

      virtual ::file::path defer_process_matter_path(::file::path path);

      virtual ::file::path get_matter_path(string strMatter);
      virtual ::file::path get_matter_cache_path(::file::path path);
      virtual ::file::path side_get_matter_path(string strMatter);


      //sclass ::hyperlink hyperlink() { return this; }


      // get a file and if there are exceptions, should show end user friendly messages
      virtual file_pointer friendly_get_file(::payload varFile, const ::file::e_open& eopen);


      virtual bool os_resolve_alias(::file::path& path, const char* psz, bool bNoUI = false, bool bNoMount = false);

      //CLASS_DECL_APEX bool os_is_folder_alias(::object * pobject, const char * psz, bool bNoUI = false, bool bNoMount = false);

      virtual bool _os_resolve_alias(::file::path& path, const char* psz, bool bNoUI, bool bNoMount);

      virtual bool os_is_alias(const char* psz);

      virtual bool sys_set(string strPath, string strValue);
      virtual string sys_get(string strPath, string strDefault = "");


      virtual string load_string(const char* psz);

      virtual ::file::listing& perform_file_listing(::file::listing& listing) override;
      virtual ::file::listing& perform_file_relative_name_listing(::file::listing& listing) override;


      //virtual ::image_transport get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
      //virtual ::image_transport matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

      //virtual ::image_transport load_image(const ::payload & varFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false) override;
      //virtual ::image_transport load_matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual ::image_transport load_matter_icon(string_array & straMatter, string strIcon) override;
      //virtual ::image_transport load_thumbnail(const ::payload & varFile, int w, int h) override;
      //virtual ::image_transport load_thumbnail(const ::string & strPath);
      //virtual ::image_transport load_dib(const ::file::path & pathDib) override;
      //virtual ::icon_transport load_icon(const ::payload & varFile);


      //virtual ::e_status _get_image(image * pimage, const ::payload & varFile, bool bSync = true);
      //virtual ::e_status _matter_image(image * pimage, const ::string & strMatter, bool bSync = true);


      //virtual ::e_status _load_image(image * pimage, const ::payload & varFile, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual ::e_status _load_matter_image(image * pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual ::e_status _load_matter_icon(image * pimage, string_array & straMatter, string strIcon);
      //virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile, int w, int h);
      //virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile);
      //virtual ::e_status _load_dib(image * pimage, const ::file::path & pathDib);


      //virtual ::e_status save_image(const ::payload & varFile, const image * pimage, ::save_image * psaveimage = nullptr);
      //virtual ::e_status save_dib(const ::file::path & path, const image * pimage);


      //virtual ::image_transport _load_image_from_file(const ::payload & varFile, const ::payload & varOptions);
      //virtual ::e_status _save_to_file(const ::payload & varFile, const image * pimage, const ::payload & varOptions);


      virtual string matter_locator(string strApp);
      virtual string matter_locator(::application* papp);

      virtual void on_update_matter_locator();

      virtual void add_matter_locator(string strApp);
      virtual void add_matter_locator(::application* papp);


      virtual ::e_status _load_from_file(::matter* pobject, const ::payload& varFile, const ::payload& varOptions);
      virtual ::e_status _save_to_file(const ::payload& varFile, const ::payload& varOptions, const ::matter* pobject);


      inline ::e_status load_from_file(::matter* pobject, const ::payload& varFile, const ::payload* pvarOptions);
      inline ::e_status load_from_file(::matter* pobject, const ::payload& varFile);
      inline ::e_status save_to_file(const ::payload& varFile, const ::payload* pvarOptions, const ::matter* pobject);
      inline ::e_status save_to_file(const ::payload& varFile, const ::matter* pobject);


      //virtual ::e_status destroy() override;

      file_transport get_file(const ::payload& varFile, const ::file::e_open& eopen) override;


   };


} // namespace apex


