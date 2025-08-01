//
// Created by camilo on 2024-10-24 04:05 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{

//
//   struct CLASS_DECL_ACME apex_context_layer_t
//   {
//
//
//
//      string                                    m_strStoreServerBaseUrl;
//
//      string_to_string                          m_mapCachedLatestBuild;
//      //::pointer<::os_context>                 m_poscontext;
//
//
//
//   };


   class CLASS_DECL_ACME apex_context_layer
   {
   public:


//      void initialize(::particle * pparticle) override;
//
//
//      void request(::request * prequest) override;
//
//      void post_request(::request * prequest) override;
//
//      bool on_idle() override;

      virtual string get_store_server_base_url();

      //bool contains(::request * prequest) const;

      //string command_line_text() const;

      //virtual void destroy() override;

      //virtual ::task_pool* taskpool() override;


//      void initialize_context() override;
//
//
//      void initialize_context_1() override;
//
//
//      void finalize_context() override;


      virtual void clear_cache();


//      bool is_system() const override;
//      bool is_session() const override;
      virtual bool is_local_data() const;


      //inline ::http::context& http() { return *m_phttp; }
      //inline ::os_context * os_context() { return m_poscontext; };


      //::directory_context * dir() override;
      //::directory_system * directory_system() override;
      //::file_context * file() override;
      //::file_system * file_system() override;


      //virtual ::handle::ini ini_from_path(::file::path& path);

      //virtual ::handle::ini local_ini();



      //virtual bool http_download(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile);
      //virtual string http_get(const ::scoped_string & scopedstrUrl, ::property_set & set);
      //virtual string http_get(const ::scoped_string & scopedstrUrl);

      virtual string get_latest_build_number(const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrAppId);

      virtual ::file::path defer_make_file_system_url(const ::scoped_string & scopedstr);
      virtual string defer_get_file_title(const ::scoped_string & scopedstr);


//      bool defer_process_media_library_path(::file::path& path) override;
//
//
//      ::file::path defer_process_path(::file::path path) override;
//      ::file::path _defer_process_path(::file::path path) override;
//      ::file::path __defer_process_path(::file::path path) override;

      virtual bool _001IsProtocol(::file::path & path, const ::scoped_string & scopedstrProtocol);

      //bool defer_process_known_folder_path(::file::path & path) override;
      virtual ::file::path full_process_path(::file::path path);

      //virtual bool defer_process_protocol_path(::file::path & path) override;

      //sclass ::hyperlink hyperlink() { return this; }


      // get a file and if there are exceptions, should show end user friendly messages
      virtual file_pointer friendly_get_file(::payload payloadFile, ::file::e_open eopen);


      //::pointer < ::file::link > os_resolve_alias(const ::file::path& path, bool bNoUI = false, bool bNoMount = false) override;

      //bool _os_has_alias_in_path(const ::file::path & path, bool bNoUI = false, bool bNoMount = false) override;

      //::pointer < ::file::link > _os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount) override;

      //virtual bool os_is_alias(const ::file::path & path) override;

      virtual ::file::path sys_path(const ::scoped_string & scopedstrPath);
      virtual void sys_set(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrValue);
      virtual string sys_get(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrDefault = "");


      virtual string load_string(const ::scoped_string & scopedstr);

      //bool _enumerates(::file::listing & listing) override;
      //bool enumerate(::file::listing& listing) override;
      //virtual bool perform_file_relative_name_listing(::file::listing& listing) override;


      //virtual ::image::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
      //virtual ::image::image_pointer matter_image(const ::scoped_string & scopedstrMatter, bool bCache = true, bool bSync = true);

      //virtual ::image::image_pointer load_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false) override;
      //virtual ::image::image_pointer load_matter_image(const ::scoped_string & scopedstrMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual ::image::image_pointer load_matter_icon(string_array & straMatter, const ::scoped_string & scopedstrIcon) override;
      //virtual ::image::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h) override;
      //virtual ::image::image_pointer load_thumbnail(const ::scoped_string & scopedstrPath);
      //virtual ::image::image_pointer load_dib(const ::file::path & pathDib) override;
      //virtual ::icon_pointer load_icon(const ::payload & payloadFile);


      //virtual void _get_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true);
      //virtual void _matter_image(::image::image *pimage, const ::scoped_string & scopedstrMatter, bool bSync = true);


      //virtual void _load_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual void _load_matter_image(::image::image *pimage, const ::scoped_string & scopedstrMatter, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual void _load_matter_icon(::image::image *pimage, string_array & straMatter, const ::scoped_string & scopedstrIcon);
      //virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile, int w, int h);
      //virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile);
      //virtual void _load_dib(::image::image *pimage, const ::file::path & pathDib);


      //virtual void save_image(const ::payload & payloadFile, const ::image::image *pimage, ::save_image * psaveimage = nullptr);
      //virtual void save_dib(const ::file::path & path, const ::image::image *pimage);


      //virtual ::image::image_pointer _load_image_from_file(const ::payload & payloadFile, const ::payload & varOptions);
      //virtual void _save_to_file(const ::payload & payloadFile, const ::image::image *pimage, const ::payload & varOptions);


      /*virtual string matter_locator(const ::scoped_string & scopedstrApp);
      virtual string matter_locator(::apex::application* papp);


      virtual void add_matter_locator(const ::scoped_string & scopedstrApp);
      virtual void add_matter_locator(::apex::application* papp);*/


      virtual void _load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload& varOptions);
      virtual void _save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::particle * pparticle);


      virtual void load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload* pvarOptions);
      virtual void load_from_file(::particle * pparticle, const ::payload& payloadFile);
      virtual void save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::particle * pparticle);
      virtual void save_to_file(const ::payload& payloadFile, const ::particle * pparticle);


      virtual bool defer_process_fs_raw_folder_protocol_path(::file::path & path);

      virtual bool is_fs_raw_folder_protocol_installed(const ::scoped_string & scopedstrProtocol);



      //virtual void destroy() override;

      //file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr) override;


//      using acme::handler_context::http_text;
//      ::string http_text(const ::scoped_string & scopedstrUrl, ::property_set & set) override;
//
//      using acme::handler_context::http_download;
//      void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set) override;

//      using acme::handler_context::http_get;
      //::pointer < ::nano::http::response > http_get(const ::scoped_string& scopedstrUrl, const ::property_set & set) override;

      //virtual void perform(::nano::http::get * pget);


   };


} // namespace platform







