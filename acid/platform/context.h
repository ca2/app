#pragma once


#include "acid/parallelization/task.h"


namespace acid
{


   class CLASS_DECL_ACID context :
      virtual public ::task
   {
   public:


      ::platform::platform *                          m_pplatform;


      ::apex::context *                               m_papexcontext;
      ::aura::context *                               m_pauracontext;


      ::acid::application*                            m_paceapplication;
      ::acid::session *                               m_pacesession;
      ::acid::system *                                m_pacesystem;
      ::acid::node *                                  m_pacenode;

      ::pointer<::text::translator>                   m_ptexttranslator;

      ::pointer<::context_image>                      m_pcontextimage;
      ::pointer<::dir_context>                        m_pdir;
      ::pointer<::file_context>                       m_pfile;

      //::pointer < ::os_context >                      m_poscontext;


      string                              m_strLocale;
      string                              m_strSchema;


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


      inline ::context_image* context_image() { return m_pcontextimage; }

      virtual bool is_system() const;
      virtual bool is_session() const;

      virtual void translate_text_data(::text::data * ptextdata);
      virtual ::text::text __text(const ::atom& atom) override;


      inline ::acid::system * system() { return m_pacesystem; }
      ::acid::node * node();


      //inline ::os_context * os_context() { return m_poscontext; }


      virtual bool os_is_alias(const ::file::path & path);

      ::ace_file * acefile();
      ::ace_path * acepath();
      ::ace_directory * acedirectory();




      virtual ::dir_context* dir();
      virtual ::file_context* file();
      ::dir_system * dirsystem();
      ::file_system * filesystem();


      virtual ::payload file_payload(const ::payload & payloadFile);


      //::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen) override;


      virtual ::file::path defer_process_path(::file::path path);

      virtual void fork_count(::collection::count iCount, const ::function < void(::collection::index, ::collection::index, ::collection::index, ::collection::index) > & function, const ::procedure & procedureCompletion, ::collection::index iStart = 0);



      virtual string get_locale();
      virtual string get_schema();


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema);
      virtual string get_locale_schema_dir();



      virtual string matter_locator(string strApp);
      virtual string matter_locator(::acid::application * papp);


      virtual void add_matter_locator(string strApp);
      virtual void add_matter_locator(::acid::application * papp);


      virtual ::file::path defer_process_matter_path(::file::path path);

      //virtual ::file::path defer_process_relative_path(const ::file::path & path);

      virtual ::file::path get_matter_path(string strMatter);
      virtual ::file::path get_matter_cache_path(::file::path path);
      virtual ::file::path side_get_matter_path(string strMatter);


      virtual bool http_exists(const ::scoped_string & scopedstrUrl, ::property_set & set);
      virtual ::file::enum_type http_get_type(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual ::file::enum_type http_get_type(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set);


      virtual ::string http_text(const ::scoped_string & scopedstrUrl, const class ::time & timeTimeout = 5_min);
      virtual ::string http_text(const ::scoped_string & scopedstrUrl, ::property_set & set, const class ::time & timeTimeout = 5_min);

      
      virtual void sync(::nano::http::get * pget);
      virtual void async(::nano::http::get * pget, const ::function < void(::nano::http::get *) > & callback);
      
      
      virtual void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, const class ::time & timeTimeout = 5_h);
      virtual void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set, const class ::time & timeTimeout = 5_h);


   };

   
} // namespace acid



