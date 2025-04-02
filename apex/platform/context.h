#pragma once


#include "apex/parallelization/thread.h"
#include "acme/platform/application.h"
#include "acme/filesystem/filesystem/enumerator.h"
#include "acme/prototype/collection/string_map.h"


namespace apex
{


   class context_thread;


   class CLASS_DECL_APEX context :
      virtual public ::thread,
      virtual public ::platform::context,
      virtual public ::file::enumerator
   {
   public:
      //
      //
      // string                              m_strStoreServerBaseUrl;
      //
      // string_to_string                    m_mapCachedLatestBuild;
      // //::pointer<::http::context>          m_phttpcontext;
      // //::pointer<::os_context>             m_poscontext;
      //

      bool                                                        m_bModifiedFsRawFolderProtocols;
      ::string_map < ::pointer < ::fs::raw_folder_protocol > >    m_mapFsRawFolderProtocol;



      context();
      ~context() override;


      void initialize(::particle * pparticle) override;


      void request(::request * prequest) override;

      void post_request(::request * prequest) override;

      bool on_idle() override;

      string get_store_server_base_url() override;

      bool contains(::request * prequest) const override;

      string command_line_text() const override;

      virtual void destroy() override;

      //virtual ::task_pool* taskpool() override;


      void initialize_context() override;


      void initialize_context_1() override;


      void initialize_http() override;


      void finalize_context() override;


      void clear_cache() override;


      bool is_system() const override;
      bool is_session() const override;
      virtual bool is_local_data() const override;


      //inline ::http::context& http() { return *m_phttp; }
      //inline ::os_context * os_context() { return m_poscontext; };


      //::directory_context * dir() override;
      //::directory_system * directory_system() override;
      //::file_context * file() override;
      //::file_system * file_system() override;


      ::handle::ini ini_from_path(::file::path& path) override;

      ::handle::ini local_ini() override;



      //virtual bool http_download(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile);
      //virtual string http_get(const string& strUrl, ::property_set& set);
      //virtual string http_get(const ::scoped_string & scopedstrUrl);

      string get_latest_build_number(const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrAppId) override;

      virtual ::file::path defer_make_file_system_url(string str) override;
      virtual string defer_get_file_title(string str) override;


      bool defer_process_media_library_path(::file::path& path) override;


      ::file::path defer_process_path(::file::path path) override;
      ::file::path _defer_process_path(::file::path path) override;
      ::file::path __defer_process_path(::file::path path) override;

      virtual bool _001IsProtocol(::file::path & path, const ::string & strProtocol) override;


      virtual void defer_calculate_fs_raw_folder_protocols();

      bool defer_process_fs_raw_folder_protocol_path(::file::path & path) override;

      bool is_fs_raw_folder_protocol_installed(const ::scoped_string & scopedstrProtocol) override;

      bool defer_process_known_folder_path(::file::path & path) override;
      virtual ::file::path full_process_path(::file::path path) override;

      bool defer_process_protocol_path(::file::path & path) override;

      //sclass ::hyperlink hyperlink() { return this; }


      // get a file and if there are exceptions, should show end user friendly messages
      virtual file_pointer friendly_get_file(::payload payloadFile, ::file::e_open eopen) override;


      ::pointer < ::file::link > os_resolve_alias(const ::file::path& path, bool bNoUI = false, bool bNoMount = false) override;

      bool _os_has_alias_in_path(const ::file::path & path, bool bNoUI = false, bool bNoMount = false) override;

      ::pointer < ::file::link > _os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount) override;

      virtual bool os_is_alias(const ::file::path & path) override;

      virtual ::file::path sys_path(const ::scoped_string & scopedstrPath) override;
      virtual void sys_set(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrValue) override;
      virtual string sys_get(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrDefault = "") override;


      virtual string load_string(const ::scoped_string & scopedstr) override;

      //bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing& listing) override;
      //virtual bool perform_file_relative_name_listing(::file::listing& listing) override;


      //virtual ::image::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
      //virtual ::image::image_pointer matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

      //virtual ::image::image_pointer load_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false) override;
      //virtual ::image::image_pointer load_matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual ::image::image_pointer load_matter_icon(string_array & straMatter, string strIcon) override;
      //virtual ::image::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h) override;
      //virtual ::image::image_pointer load_thumbnail(const ::string & strPath);
      //virtual ::image::image_pointer load_dib(const ::file::path & pathDib) override;
      //virtual ::icon_pointer load_icon(const ::payload & payloadFile);


      //virtual void _get_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true);
      //virtual void _matter_image(::image::image *pimage, const ::string & strMatter, bool bSync = true);


      //virtual void _load_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual void _load_matter_image(::image::image *pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
      //virtual void _load_matter_icon(::image::image *pimage, string_array & straMatter, string strIcon);
      //virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile, int w, int h);
      //virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile);
      //virtual void _load_dib(::image::image *pimage, const ::file::path & pathDib);


      //virtual void save_image(const ::payload & payloadFile, const ::image::image *pimage, ::save_image * psaveimage = nullptr);
      //virtual void save_dib(const ::file::path & path, const ::image::image *pimage);


      //virtual ::image::image_pointer _load_image_from_file(const ::payload & payloadFile, const ::payload & varOptions);
      //virtual void _save_to_file(const ::payload & payloadFile, const ::image::image *pimage, const ::payload & varOptions);


      /*virtual string matter_locator(string strApp);
      virtual string matter_locator(::apex::application* papp);


      virtual void add_matter_locator(string strApp);
      virtual void add_matter_locator(::apex::application* papp);*/


      virtual void _load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload& varOptions) override;
      virtual void _save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::particle * pparticle) override;


      void load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload* pvarOptions) override;
      void load_from_file(::particle * pparticle, const ::payload& payloadFile) override;
      void save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::particle * pparticle) override;
      void save_to_file(const ::payload& payloadFile, const ::particle * pparticle) override;


      //virtual void destroy() override;

      file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr) override;


//      using acme::handler_context::http_text;
//      ::string http_text(const ::scoped_string & scopedstrUrl, ::property_set & set) override;
//
//      using acme::handler_context::http_download;
//      void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set) override;

//      using acme::handler_context::http_get;
      //::pointer < ::nano::http::response > http_get(const ::scoped_string& scopedstrUrl, const ::property_set& set) override;

      //virtual void perform(::nano::http::get * pget);




   };


} // namespace apex


