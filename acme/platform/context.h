#pragma once


#include "acme/handler/handler.h"
#include "acme/parallelization/task.h"
#include "acme/platform/message_box.h"
#include "context_acme.h"
#include "context_apex.h"
#include "context_aqua.h"
#include "context_aura.h"



namespace platform
{


   class CLASS_DECL_ACME context :
      virtual public ::task,
      //virtual public ::handler::handler,
      virtual public ::reificator < ::message_box >,
   virtual public ::platform::acme_context_layer_t,
   virtual public ::platform::apex_context_layer_t,
   virtual public ::platform::aqua_context_layer_t,
   virtual public ::platform::aura_context_layer_t,
   virtual public ::platform::acme_context_layer,
   virtual public ::platform::apex_context_layer,
   virtual public ::platform::aqua_context_layer,
   virtual public ::platform::aura_context_layer
   {
   public:
      //
      //
      // //::platform::platform *                          m_pplatform;
      //
      //
      // //::platform::context *                               m_papexcontext;
      // //::aura::context *                               m_pauracontext;
      //
      //
      // ::platform::application*                        m_papplication;
      // ::platform::session *                           m_psession;
      // ::platform::system *                            m_psystem;
      // ::platform::node *                              m_pnode;
      //
      // ::pointer<::text::translator>                   m_ptexttranslator;
      //
      // ::pointer<::image::image_context>               m_pimagecontext;
      // ::pointer<::directory_context>                  m_pdirectorycontext;
      // ::pointer<::file_context>                       m_pfilecontext;
      // ::pointer<::http::context>                      m_phttpcontext;
      //
      // //::pointer < ::os_context >                      m_poscontext;
      //
      //
      // ::string                                        m_strLocale;
      // ::string                                        m_strSchema;
      //
      //
      // string_array                                    m_straMatterLocatorPriority;
      // string_array                                    m_straMatterLocator;
      //

      context();
      ~context() override;


      void destroy() override;


      virtual void on_set_platform();

      virtual void set_platform() override;


      void initialize(::particle * pparticle) override;

      virtual void initialize_context() override;

      virtual void initialize_context_1() override;

      virtual void finalize_context() override;

      ::pointer < ::reified < ::message_box > > realize(::realizable < ::message_box > * p) override;

      virtual ::image::image_context * image() override;

      //virtual bool is_system() const;
      //virtual bool is_session() const;

      virtual void translate_text_data(::text::data * ptextdata) override;
      virtual ::text::text __text(const ::atom& atom) override;


      //inline ::platform::system * system();
      ::platform::node * node();


      //inline ::os_context * os_context() { return m_poscontext; }



      //::file_system * file_system();
      //::directory_system * directory_system();




      virtual ::directory_context* directory() override;
      virtual ::file_context* file() override;
      virtual ::directory_system * directory_system() override;
      virtual ::file_system * file_system() override;
      virtual ::path_system * path_system() override;


      //virtual ::file::watcher * file_watcher() override;


      virtual ::payload file_payload(const ::payload & payloadFile) override;

      ::platform::http * http() override;

      void initialize_http() override;

      //::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen) override;

      virtual ::file::path defer_process_path(::file::path path) override;
      virtual ::file::path _defer_process_path(::file::path path) override;
      virtual ::file::path __defer_process_path(::file::path path) override;


      virtual void fork_count(::collection::count iCount, const ::function < void(::collection::index, ::collection::index, ::collection::index, ::collection::index) > & function, const ::procedure & procedureCompletion, ::collection::index iStart = 0) override;



      virtual ::string get_locale() override;
      virtual ::string get_schema() override;


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      virtual string get_locale_schema_dir() override;



      virtual string matter_locator(string strApp) override;
      virtual string matter_locator(::platform::application * papp) override;


      virtual void add_matter_locator(string strApp) override;
      virtual void add_matter_locator(::platform::application * papp) override;


      virtual ::file::path defer_process_matter_path(::file::path path) override;

      //virtual ::file::path defer_process_relative_path(const ::file::path & path);

      virtual ::file::path get_matter_path(string strMatter) override;
      virtual ::file::path get_matter_cache_path(::file::path path) override;
      virtual ::file::path side_get_matter_path(string strMatter) override;


      virtual bool os_is_alias(const ::file::path & path) override;
      virtual ::pointer < ::file::link > os_resolve_alias(const ::file::path& path, bool bNoUI = false, bool bNoMount = false) override;
      virtual bool _os_has_alias_in_path(const ::file::path & path, bool bNoUI = false, bool bNoMount = false) override;
      virtual ::pointer < ::file::link > _os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount) override;
      //virtual bool os_is_alias(const ::file::path & path) override;

      virtual bool defer_process_media_library_path(::file::path & path) override;
      virtual bool defer_process_known_folder_path(::file::path & path) override;
      virtual bool defer_process_protocol_path(::file::path & path)  override;


   };

   
} // namespace platform



