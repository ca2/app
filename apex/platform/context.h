#pragma once


#include "apex/parallelization/thread.h"
#include "acme/platform/context.h"
#include "acme/filesystem/filesystem/enumerator.h"
#include "acme/primitive/collection/string_map.h"


namespace apex
{


   class context_thread;


   class CLASS_DECL_APEX context :
      virtual public ::thread,
      virtual public ::acme::context,
      virtual public ::file::enumerator
   {
   public:


      string                              m_strStoreServerBaseUrl;

      string_to_string                    m_mapCachedLatestBuild;
      ::pointer<::http::context>          m_phttp;
      //::pointer<::os_context>             m_poscontext;




      string_array                        m_straMatterLocatorPriority;
      string_array                        m_straMatterLocator;

      ::payload                           m_payloadFile;
      ::pointer_array < ::request >       m_requestaPending;
      ::pointer_array < ::request >       m_requestaHistory;


      context();
      ~context() override;


      void initialize(::particle * pparticle) override;


      void request(::request * prequest) override;

      void post_request(::request * prequest) override;

      bool on_idle() override;

      bool post_next_pending_request();

      string get_store_server_base_url();

      bool contains(::request * prequest) const;

      string command_line_text() const;

      virtual void destroy() override;

      //virtual ::task_pool* taskpool() override;


      void initialize_context() override;


      void initialize_context_1() override;


      void clear_cache();


      bool is_system() const override;
      bool is_session() const override;
      virtual bool is_local_data() const;


      inline ::http::context& http() { return *m_phttp; }
      //inline ::os_context * os_context() { return m_poscontext; };


      //::dir_context * dir() override;
      //::dir_system * dirsystem() override;
      //::file_context * file() override;
      //::file_system * filesystem() override;


      ::handle::ini ini_from_path(::file::path& path);

      ::handle::ini local_ini();

      virtual string get_locale();
      virtual string get_schema();


      virtual void locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const string& strLocale, const string& strSchema);
      virtual string get_locale_schema_dir();



      virtual bool http_download(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile);
      virtual string http_get(const string& strUrl, ::property_set& set);
      virtual string http_get(const ::scoped_string & scopedstrUrl);

      string get_latest_build_number(const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrAppId);

      virtual ::file::path defer_make_file_system_url(string str);
      virtual string defer_get_file_title(string str);


      virtual bool defer_process_media_library_path(::file::path& path);


      ::file::path defer_process_path(::file::path path) override;
      virtual ::file::path _defer_process_path(::file::path path);
      virtual ::file::path __defer_process_path(::file::path path);

      virtual bool defer_process_known_folder_path(::file::path & path);
      virtual ::file::path full_process_path(::file::path path);

      virtual ::file::path defer_process_matter_path(::file::path path);

      //virtual ::file::path defer_process_relative_path(const ::file::path & path);

      virtual ::file::path get_matter_path(string strMatter);
      virtual ::file::path get_matter_cache_path(::file::path path);
      virtual ::file::path side_get_matter_path(string strMatter);


      //sclass ::hyperlink hyperlink() { return this; }


      // get a file and if there are exceptions, should show end user friendly messages
      virtual file_pointer friendly_get_file(::payload payloadFile, ::file::e_open eopen);


      virtual ::pointer < ::file::link > os_resolve_alias(const ::file::path& path, bool bNoUI = false, bool bNoMount = false);

      virtual bool _os_has_alias_in_path(const ::file::path & path, bool bNoUI = false, bool bNoMount = false);

      virtual ::pointer < ::file::link > _os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount);

      virtual bool os_is_alias(const ::file::path & path);

      virtual ::file::path sys_path(const ::scoped_string & scopedstrPath);
      virtual void sys_set(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrValue);
      virtual string sys_get(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrDefault = "");


      virtual string load_string(const ::scoped_string & scopedstr);

      //bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing& listing) override;
      //virtual bool perform_file_relative_name_listing(::file::listing& listing) override;


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
      virtual string matter_locator(::apex::application* papp);


      virtual void add_matter_locator(string strApp);
      virtual void add_matter_locator(::apex::application* papp);


      virtual void _load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload& varOptions);
      virtual void _save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::particle * pparticle);


      inline void load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload* pvarOptions);
      inline void load_from_file(::particle * pparticle, const ::payload& payloadFile);
      inline void save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::particle * pparticle);
      inline void save_to_file(const ::payload& payloadFile, const ::particle * pparticle);


      //virtual void destroy() override;

      file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr) override;


   };


} // namespace apex


