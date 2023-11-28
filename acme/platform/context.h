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

      ::pointer<::context_image>                      m_pcontextimage;
      ::pointer<::dir_context>                        m_pdir;
      ::pointer<::file_context>                       m_pfile;

      ::pointer < ::os_context >                      m_poscontext;


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


      inline ::context_image* context_image() { return m_pcontextimage; }

      virtual bool is_system() const;
      virtual bool is_session() const;

      virtual void translate_text_data(::text::data * ptextdata);
      virtual ::text::text __text(const ::atom& atom) override;


      ::acme_file * acmefile();
      ::acme_path * acmepath();
      ::acme_directory * acmedirectory();
      ::acme::node * acmenode();
      inline ::acme::system * system() { return m_pacmesystem; }


      inline ::os_context* os_context() { return m_poscontext; }


      virtual ::dir_context* dir();
      virtual ::file_context* file();
      ::dir_system * dirsystem();
      ::file_system * filesystem();


      virtual ::payload file_payload(const ::payload & payloadFile);


      //::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen) override;


      virtual ::file::path defer_process_path(::file::path path);

      virtual void fork_count(::count iCount, const ::function < void(index, index, index, index) > & function, const ::procedure & procedureCompletion, index iStart = 0);



      virtual string get_locale();
      virtual string get_schema();


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema);
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


      virtual bool http_exists(const ::scoped_string & scopedstrUrl, ::property_set & set);
      virtual ::file::enum_type http_get_type(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual ::file::enum_type http_get_type(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set);


      virtual ::string http_text(const ::scoped_string & scopedstrUrl);
      virtual ::string http_text(const ::scoped_string & scopedstrUrl, ::property_set & set);

      
      virtual ::memory http_memory(const ::scoped_string & scopedstrUrl);
      virtual ::memory http_memory(const ::scoped_string & scopedstrUrl, ::property_set & set);

      
      virtual void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl);
      virtual void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set);


   };

   
} // namespace acme



