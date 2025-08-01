//
// Created by camilo on 2024-10-24 04:01 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


//   struct CLASS_DECL_ACME acme_context_layer_t
//   {
//
//
//
//
//      //::platform::platform *                          m_pplatform;
//
//
//      //::platform::context *                               m_papexcontext;
//      //::aura::context *                               m_pauracontext;
//
//
//      //::platform::application*                        m_papplication;
//      ::platform::session *                           m_psession;
//      ::platform::system *                            m_psystem;
//      //::platform::node *                              m_pnode;
//
//      ::pointer<::text::translator>                   m_ptexttranslator;
//
//      ::pointer<::image::image_context>               m_pimagecontext;
//      ::pointer<::directory_context>                  m_pdirectorycontext;
//      ::pointer<::file_context>                       m_pfilecontext;
//      //::pointer<::http::context>                      m_phttpcontext;
//
//      //::pointer < ::os_context >                      m_poscontext;
//
//
//      ::string                                        m_strLocale;
//      ::string                                        m_strSchema;
//
//
//      string_array                                    m_straMatterLocatorPriority;
//      string_array                                    m_straMatterLocator;
//
//      ::pointer<::platform::http>                     m_phttp;
//
//
//   };
//

   class CLASS_DECL_ACME acme_context_layer
   {
   public:

      //void destroy() override;


      //virtual void on_set_platform();

      virtual void set_platform();


      //void initialize(::particle * pparticle) override;

      virtual void initialize_context();

      virtual void initialize_context_1();

      virtual void finalize_context();

      virtual void initialize_http();

      //::pointer < ::reified < ::message_box > > realize(::realizable < ::message_box > * p) override;

      virtual ::image::image_context* image();

      // virtual bool is_system() const;
      // virtual bool is_session() const;

      virtual void translate_text_data(::text::data * ptextdata);
      //virtual ::text::text __text(const ::atom& atom) override;


      //inline ::platform::system * system();
      //::platform::node * node();


      //inline ::os_context * os_context() { return m_poscontext; }



      //::file_system * file_system();
      //::directory_system * directory_system();




      virtual ::directory_context* directory();
      virtual ::file_context* file();
      virtual ::directory_system * directory_system();
      virtual ::file_system * file_system();
      virtual ::path_system * path_system();


      //virtual ::file::watcher * file_watcher();


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



      virtual string matter_locator(const ::scoped_string & scopedstrApp);
      virtual string matter_locator(::platform::application * papp);


      virtual void add_matter_locator(const ::scoped_string & scopedstrApp);
      virtual void add_matter_locator(::platform::application * papp);


      virtual ::file::path defer_process_matter_path(::file::path path);

      //virtual ::file::path defer_process_relative_path(const ::file::path & path);

      virtual ::file::path get_matter_path(const ::scoped_string & scopedstrMatter);
      virtual ::file::path get_matter_cache_path(::file::path path);
      virtual ::file::path side_get_matter_path(const ::scoped_string & scopedstrMatter);


      virtual bool os_is_alias(const ::file::path & path);
      virtual ::pointer < ::file::link > os_resolve_alias(const ::file::path& path, bool bNoUI = false, bool bNoMount = false);
      virtual bool _os_has_alias_in_path(const ::file::path & path, bool bNoUI = false, bool bNoMount = false);
      virtual ::pointer < ::file::link > _os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount);
      //virtual bool os_is_alias(const ::file::path & path) override;

      virtual bool defer_process_media_library_path(::file::path & path);
      virtual bool defer_process_known_folder_path(::file::path & path);
      virtual bool defer_process_protocol_path(::file::path & path) ;


      virtual ::platform::http * http();


   };


} // namespace platform





