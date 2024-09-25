#pragma once


#include "acme/parallelization/task.h"


namespace acme
{


   class CLASS_DECL_ACME context :
      virtual public ::task
   {
   public:


      ::platform::platform *                          m_pplatform;


      ::apex::context *                               m_papexcontext;
      ::aura::context *                               m_pauracontext;


      ::acme::application*                            m_pacmeapplication;
      ::acme::session *                               m_pacmesession;
      ::acme::system *                                m_pacmesystem;
      ::acme::node *                                  m_pacmenode;

      ::pointer<::text::translator>                   m_ptexttranslator;

      ::pointer<::image::image_context>               m_pimagecontext;
      ::pointer<::dir_context>                        m_pdir;
      ::pointer<::file_context>                       m_pfile;
      ::pointer<::http::context>                      m_phttpcontext;

      //::pointer < ::os_context >                      m_poscontext;


      ::string                               m_strLocale;
      ::string                               m_strSchema;


      string_array                        m_straMatterLocatorPriority;
      string_array                        m_straMatterLocator;


      context();
      ~context() override;


      virtual void on_set_platform();

      virtual void set_platform(::platform::platform * pplatform);


      void initialize(::particle * pparticle) override;

      virtual void initialize_context();

      virtual void initialize_context_1();

      virtual void finalize_context();


      inline ::image::image_context* image() { return m_pimagecontext; }

      virtual bool is_system() const;
      virtual bool is_session() const;

      virtual void translate_text_data(::text::data * ptextdata);
      virtual ::text::text __text(const ::atom& atom) override;


      inline ::acme::system * system() { return m_pacmesystem; }
      ::acme::node * node();


      //inline ::os_context * os_context() { return m_poscontext; }



      ::acme_file * acmefile();
      ::acme_path * acmepath();
      ::acme_directory * acmedirectory();




      virtual ::dir_context* dir();
      virtual ::file_context* file();
      ::dir_system * dirsystem();
      ::file_system * filesystem();


      ::http::context * http();


      virtual ::payload file_payload(const ::payload & payloadFile);


      //::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen) override;


      virtual ::file::path defer_process_path(::file::path path);
      virtual ::file::path _defer_process_path(::file::path path);
      virtual ::file::path __defer_process_path(::file::path path);


      virtual void fork_count(::collection::count iCount, const ::function < void(::collection::index, ::collection::index, ::collection::index, ::collection::index) > & function, const ::procedure & procedureCompletion, ::collection::index iStart = 0);



      virtual ::string get_locale();
      virtual ::string get_schema();


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      virtual string get_locale_schema_dir();



      virtual string matter_locator(string strApp);
      virtual string matter_locator(::acme::application * papp);


      virtual void add_matter_locator(string strApp);
      virtual void add_matter_locator(::acme::application * papp);


      virtual ::file::path defer_process_matter_path(::file::path path);

      //virtual ::file::path defer_process_relative_path(const ::file::path & path);

      virtual ::file::path get_matter_path(string strMatter);
      virtual ::file::path get_matter_cache_path(::file::path path);
      virtual ::file::path side_get_matter_path(string strMatter);


      virtual bool os_is_alias(const ::file::path & path);
      virtual ::pointer < ::file::link > os_resolve_alias(const ::file::path& path, bool bNoUI = false, bool bNoMount = false);
      virtual bool _os_has_alias_in_path(const ::file::path & path, bool bNoUI = false, bool bNoMount = false);
      virtual ::pointer < ::file::link > _os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount);
      //virtual bool os_is_alias(const ::file::path & path) override;

      virtual bool defer_process_media_library_path(::file::path & path);
      virtual bool defer_process_known_folder_path(::file::path & path);
      virtual bool defer_process_protocol_path(::file::path & path) ;

      virtual bool http_exists(const ::url::url & url, ::property_set & set);
      virtual ::file::enum_type http_get_type(const ::url::url & url, property_set & set);
      virtual ::file::enum_type http_get_type(const ::url::url & url, ::payload * pvarQuery, property_set & set);


      virtual ::string http_text(const ::url::url & url, const class ::time & timeTimeout = 5_min);
      virtual ::string http_text(const ::url::url & url, ::property_set & set, const class ::time & timeTimeout = 5_min);

      virtual ::url::url http_get_effective_url(const ::url::url & url);
      
      virtual void sync(::nano::http::get * pget);
      virtual void async(::nano::http::get * pget, const ::function < void(::nano::http::get *) > & callback);
      
      
      virtual void http_download(const ::payload & payloadFile, const ::url::url & url, const class ::time & timeTimeout = 5_h);
      virtual void http_download(const ::payload & payloadFile, const ::url::url & url, ::property_set & set, const class ::time & timeTimeout = 5_h);


   };

   
} // namespace acme



