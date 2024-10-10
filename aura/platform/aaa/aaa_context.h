#pragma once


namespace aura { class context_thread; }


class CLASS_DECL_AURA context :
   virtual public ::object,
   virtual public ::file::listing_provider
{
public:


   string_to_string                    m_mapCachedLatestBuild;
   ::pointer<::http::context>       m_phttp;
   ::pointer<::dir_context>         m_pdir;
   ::pointer<::file_context>        m_pfile;
   ::pointer<::os_context>          m_pos;


   string                              m_strLocale;
   string                              m_strSchema;


   string_array                        m_straMatterLocatorPriority;
   string_array                        m_straMatterLocator;


   context(){}
   virtual ~context(){}


   virtual void initialize_context();


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
   virtual file_pointer friendly_get_file(::payload payloadFile, ::u32 nOpenFlags);


   virtual bool os_resolve_alias(::file::path & path, const ::string & psz, ::user::interaction_base * pinteraction, bool bNoUI = false, bool bNoMount = false);

   //CLASS_DECL_AURA bool os_is_folder_alias(::particle * pparticle, const ::string & psz, bool bNoUI = false, bool bNoMount = false);

   virtual bool _os_resolve_alias(::file::path & path, const ::string & psz, ::user::interaction_base * pinteraction, bool bNoUI, bool bNoMount);

   virtual bool os_is_alias(const ::string & psz);

   virtual bool sys_set(string strPath, string strValue);
   virtual string sys_get(string strPath, string strDefault = "");


   virtual string load_string(const ::string & psz);

   virtual ::file::listing & perform_file_listing(::file::listing & listing) override;
   virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) override;


   virtual ::image::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
   virtual ::image::image_pointer matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   virtual ::image::image_pointer load_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false) override;
   virtual ::image::image_pointer load_matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image::image_pointer load_matter_icon(string_array & straMatter, string strIcon) override;
   virtual ::image::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h) override;
   virtual ::image::image_pointer load_thumbnail(const ::string & strPath);
   virtual ::image::image_pointer load_dib(const ::file::path & pathDib) override;
   virtual ::icon_pointer load_icon(const ::payload & payloadFile);


   virtual void _get_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true);
   virtual void _matter_image(::image::image *pimage, const ::string & strMatter, bool bSync = true);


   virtual void _load_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true, bool bCreateHelperMaps = false);
   virtual void _load_matter_image(::image::image *pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
   virtual void _load_matter_icon(::image::image *pimage, string_array & straMatter, string strIcon);
   virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile, int w, int h);
   virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile);
   virtual void _load_dib(::image::image *pimage, const ::file::path & pathDib);


   virtual void save_image(const ::payload & payloadFile, const ::image::image *pimage, ::save_image * psaveimage = nullptr);
   virtual void save_dib(const ::file::path & path, const ::image::image *pimage);


   virtual ::image::image_pointer _load_image_from_file(const ::payload & payloadFile, const ::payload & varOptions);
   virtual void _save_to_file(const ::payload & payloadFile, const ::image::image *pimage, const ::payload & varOptions);


   virtual string matter_locator(string strApp);
   virtual string matter_locator(::aura::application * papp);

   virtual void on_update_matter_locator();

   virtual void add_matter_locator(string strApp);
   virtual void add_matter_locator(::aura::application * papp);


   virtual void _load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload& varOptions);
   virtual void _save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::particle * pparticle);


   inline void load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload* pvarOptions);
   inline void load_from_file(::particle * pparticle, const ::payload& payloadFile);
   inline void save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::particle * pparticle);
   inline void save_to_file(const ::payload& payloadFile, const ::particle * pparticle);


   virtual void destroy() override;


};



