#pragma once


namespace aura { class context_thread; }


class CLASS_DECL_AURA context :
   virtual public ::object,
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


   context(){}
   virtual ~context(){}


   virtual ::e_status initialize_context();


   void clear_cache();


   virtual bool is_system() const;


   inline ::http::context & http() { return *m_phttp; }
   inline ::dir_context & dir() { return *m_pdir; }
   inline ::file_context & file() { return *m_pfile; }
   inline ::os_context & os() { return *m_pos; };

   ::handle::ini ini_from_path(::file::path & path);

   ::handle::ini local_ini();

   virtual string get_locale();
   virtual string get_schema();


   virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema);
   virtual string get_locale_schema_dir();



   virtual bool http_download(const ::string & pszUrl, const ::string & pszFile);
   virtual string http_get(const ::string & strUrl, ::property_set & set);
   virtual string http_get(const ::string & pszUrl);

   string get_latest_build_number(const ::string & pszConfiguration, const ::string & pszAppId);

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


   class ::hyperlink hyperlink() { return this; }


   // get a file and if there are exceptions, should show end user friendly messages
   virtual file_pointer friendly_get_file(::payload varFile, ::u32 nOpenFlags);


   virtual bool os_resolve_alias(::file::path & path, const ::string & psz, ::user::primitive * pinteraction, bool bNoUI = false, bool bNoMount = false);

   //CLASS_DECL_AURA bool os_is_folder_alias(::object * pobject, const ::string & psz, bool bNoUI = false, bool bNoMount = false);

   virtual bool _os_resolve_alias(::file::path & path, const ::string & psz, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount);

   virtual bool os_is_alias(const ::string & psz);

   virtual bool sys_set(string strPath, string strValue);
   virtual string sys_get(string strPath, string strDefault = "");


   virtual string load_string(const ::string & psz);

   virtual ::file::listing & perform_file_listing(::file::listing & listing) override;
   virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) override;


   virtual ::image_result get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
   virtual ::image_result matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   virtual ::image_result load_image(const ::payload & varFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false) override;
   virtual ::image_result load_matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image_result load_matter_icon(string_array & straMatter, string strIcon) override;
   virtual ::image_result load_thumbnail(const ::payload & varFile, int w, int h) override;
   virtual ::image_result load_thumbnail(const ::string & strPath);
   virtual ::image_result load_dib(const ::file::path & pathDib) override;
   virtual ::icon_result load_icon(const ::payload & varFile);


   virtual ::e_status _get_image(image * pimage, const ::payload & varFile, bool bSync = true);
   virtual ::e_status _matter_image(image * pimage, const ::string & strMatter, bool bSync = true);


   virtual ::e_status _load_image(image * pimage, const ::payload & varFile, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::e_status _load_matter_image(image * pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::e_status _load_matter_icon(image * pimage, string_array & straMatter, string strIcon);
   virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile, int w, int h);
   virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile);
   virtual ::e_status _load_dib(image * pimage, const ::file::path & pathDib);


   virtual ::e_status save_image(const ::payload & varFile, const image * pimage, ::save_image * psaveimage = nullptr);
   virtual ::e_status save_dib(const ::file::path & path, const image * pimage);


   virtual ::image_result _load_image_from_file(const ::payload & varFile, const ::payload & varOptions);
   virtual ::e_status _save_to_file(const ::payload & varFile, const image * pimage, const ::payload & varOptions);


   virtual string matter_locator(string strApp);
   virtual string matter_locator(::aura::application * papp);

   virtual void on_update_matter_locator();

   virtual void add_matter_locator(string strApp);
   virtual void add_matter_locator(::aura::application * papp);


   virtual ::e_status _load_from_file(::matter * pobject, const ::payload& varFile, const ::payload& varOptions);
   virtual ::e_status _save_to_file(const ::payload& varFile, const ::payload& varOptions, const ::matter* pobject);


   inline ::e_status load_from_file(::matter* pobject, const ::payload& varFile, const ::payload* pvarOptions);
   inline ::e_status load_from_file(::matter* pobject, const ::payload& varFile);
   inline ::e_status save_to_file(const ::payload& varFile, const ::payload* pvarOptions, const ::matter* pobject);
   inline ::e_status save_to_file(const ::payload& varFile, const ::matter* pobject);


   virtual ::e_status destroy() override;


};



