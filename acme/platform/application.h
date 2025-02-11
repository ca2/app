//
// Created by camilo on 22/02/2022. 01:19 <3ThomasBorregaardSorensen!!
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:51 <3ThomasBorregaardSorensen!!
#pragma once


class main_hold_base;
//namespace apex{
//class menu;
//} // namespace apex
class application_menu;

class get_file_extension_mime_type;

namespace acme { class acme;  }

#include "application_base.h"
#include "application_exit.h"
#include "application_flags.h"
#include "acme/handler/command_handler.h"
#include "context.h"
#include "release_time_for_project.h"
#include "acme/prototype/data/client.h"
#include "acme/prototype/text/text.h"
#include "application_acme.h"
#include "application_apex.h"
#include "application_aqua.h"
#include "application_aura.h"
#include "application_axis.h"
#include "application_base.h"
#include "application_bred.h"
#include "application_core.h"


namespace platform
{


   class CLASS_DECL_ACME application :
//      virtual public application_base,
      virtual public APPLICATION_FLAGS,
      virtual public ::platform::context,
      virtual public ::data::client,
      virtual public ::application_exit,
      virtual public ::command_handler,
      virtual public ::platform::acme_application_layer_t,
      virtual public ::platform::apex_application_layer_t,
      virtual public ::platform::aqua_application_layer_t,
      virtual public ::platform::aura_application_layer_t,
      virtual public ::platform::axis_application_layer_t,
      virtual public ::platform::base_application_layer_t,
      virtual public ::platform::bred_application_layer_t,
      virtual public ::platform::core_application_layer_t,
      virtual public ::platform::acme_application_layer,
      virtual public ::platform::apex_application_layer,
      virtual public ::platform::aqua_application_layer,
      virtual public ::platform::aura_application_layer,
      virtual public ::platform::axis_application_layer,
      virtual public ::platform::base_application_layer,
      virtual public ::platform::bred_application_layer,
      virtual public ::platform::core_application_layer
      {
   public:

//
//       // mutable ::apex::application* m_papexapplication;
//       // mutable ::aqua::application* m_paquaapplication;
//       // mutable ::aura::application* m_pauraapplication;
//       // mutable ::axis::application* m_paxisapplication;
//       // mutable ::base::application* m_pbaseapplication;
//       // mutable ::bred::application* m_pbredapplication;
//       // mutable ::core::application* m_pcoreapplication;
//
//       class user_message :
//       virtual public ::particle
//       {
//
//          public:
//
//          ::e_status m_estatus;
//          ::particle_pointer m_pparticle;
//          long long m_hi;
//          void * m_p;
//
//       };
//
//       bool                                            m_bTransferToContainer;
//       bool                                            m_bTransferredToContainer;
// #if REFERENCING_DEBUGGING
//       ::reference_referer* m_prefererCreation = nullptr;
// #endif
//       //mutable ::platform::platform *               m_pplatform;
//
//       //::APPLICATION_FLAGS                      m_applicationflags;
//       ::pointer<main_hold_base>                       m_pmainholdbase;
//       // FROM ::main (Now main2)
//       ::pointer < ::filesystem::file_system_options > m_pfilesystemoptions;
//       ::pointer_array < user_message >                m_usermessagea;
//       bool                                            m_bGUIReady = false;
//       bool                                            m_bModulePath = false;
//       ::file::path                                    m_pathModule;
//
//       bool                                            m_bModuleFolder = false;
//       ::file::path                                    m_pathModuleFolder;
//
//
//       string                              m_strProgName;
//       string                           m_strStandalone;
//       int                              m_iExitCode = 0;
//       bool                             m_bApplicationFirstRequest;
//       //::pointer < ::request >                         m_prequest;
//
//
//       // END FROM ::main (Now main2 : merge)
//
//       //::pointer < ::platform::platform >              m_pplatform;
//       string                                          m_strAppId;
//       string                                          m_strAppName;
//       string                                          m_strRoot;
//       string                                          m_strDomain;
//       string                                          m_strLibraryName;
//       string                                          m_strBuild;
//       string                                          m_strInstallToken;
//       string_array                                    m_straAppCategory;
//       bool                                            m_bLicense;
//
//       enum_application_capability_array               m_eapplicationcapabilitya;
//       ::text::text                                    m_textAppTitle;
//       ::text::text                                    m_textAppName;
//
//       ::pointer < ::mutex >                                      m_pmutexMatterLocator;
//
//       ::pointer < ::mutex >                                      m_pmutexStr;


      application();
      ~application() override;
      
#ifdef DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif

      virtual ::release_time_for_project release_time() override;


      //virtual void initialize_application(::platform::platform * pplatform);

      virtual void initialize_application() override;

#if REFERENCING_DEBUGGING

      void on_after_construct(::reference_referer* preferer) override;

#endif

      virtual void _001TryCloseApplication() override;

      virtual void application_on_status(::e_status estatus, ::particle * pparticle = nullptr, long long hi = 0, void * p = nullptr) override;


      virtual void on_error_icloud_not_available(::particle * pparticle = nullptr, long long hi = 0, void * p = nullptr) override;


      //virtual void application_main();

      virtual int application_main() override;


      void on_set_platform() override;


      void on_initialize_particle() override;

         ::user::user * user() override;

      //void initialize(::particle * pparticle) override;


      virtual void start_application(::request* prequest) override;

      //virtual void on_initialize_application();

      virtual class ::application_menu * application_menu() override;

//      using ::platform::context::factory;

//      virtual ::factory::factory_pointer& factory() const override;

      //virtual void implement_application();

      virtual void initialize_application_flags() override;

      //virtual bool is_application() const;

      //bool is_system() const override;
      //bool is_session() const override;

      virtual bool is_service() const;
      virtual bool is_user_service() const;

      virtual bool can_exit_application() override;

      virtual ::file::path get_module_path() override;
      virtual ::file::path get_module_folder() override;


      virtual ::string app_name() override;

      //virtual ::string app_name();

      virtual ::string app_root() override;

      virtual ::string application_title() override;


      virtual ::string application_name() override;
//
//#ifdef WINDOWS
//
//      void get_arguments_from_command_line();
//
//#else
//
//      void set_args(int argc, char * argv[], char * envpb[]);
//
//#endif

      //virtual int __implement();

      //virtual int main_loop();

      void main() override;

      virtual ::enum_id key_command(::user::enum_key ekey, ::user::key_state * pkeystate) override;

      virtual void on_before_launching() override;
      //virtual void os_native_bergedge_start() override;

      virtual void init1();
      virtual void init2();
      virtual void init3();


      virtual void init();
      virtual void term();

      virtual void term3();
      virtual void term2();
      virtual void term1();


      virtual void do_install() override;
      virtual void do_uninstall() override;


      virtual void on_install() override;
      virtual void on_uninstall() override;


      virtual void init_instance() override;
      virtual void term_instance() override;

      void init_task() override;
      void term_task() override;

      
      virtual void user_confirm_close_application();


      virtual bool has_capability(enum_application_capability eapplicationcapability) const override;
      virtual void add_capability(enum_application_capability ecapability) override;


      bool handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;
      virtual bool handle_application_call(::payload & payload, const ::string & strMember, ::property_set & propertyset) override;


      virtual ::file::path get_app_localconfig_folder() override;
      virtual ::pointer<::handle::ini>get_ini() override;


      virtual ::string get_visual_studio_build() override;


      virtual ::string get_application_name() override;


      void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;

      virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale) override;
      string get_locale_schema_dir() override;

      virtual void set_locale(const ::scoped_string & scopedstrLocale, const ::action_context & action_context) override;

      virtual void set_schema(const ::scoped_string& scopedstrSchema, const ::action_context & action_context) override;

      virtual void on_set_locale(const ::scoped_string& scopedstrLocale, const ::action_context & action_context) override;

      virtual void on_set_schema(const ::scoped_string& scopedstrSchema, const ::action_context & action_context) override;



      virtual void fill_locale_schema(::text::international::locale_schema & localeschema) override;
      virtual void fill_locale_schema(::text::international::locale_schema & localeschema, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;


      virtual void process_init() override;
      virtual void process_term() override;

      //virtual void pre_run() override;
      //virtual void application_pre_run() override;

      //virtual void pos_run() override;
      //virtual void application_pos_run() override;

      virtual void init_application() override;

      virtual void term_application() override;

      virtual ::string_array get_about_box_lines() override;

      void show_about_box(::user::activation_token * puseractivationtoken) override;

      bool handle_command(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;

      bool on_command_final(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;


      virtual void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem) override;
      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom) override;


      virtual get_file_extension_mime_type * get_get_file_extension_mime_type() override;

      virtual void pick_browse(const ::function < void(const ::file::path & path) > & callback) override;
      virtual void pick_media(const char * pszMediaType) override;
      virtual void did_pick_document_at_url(const char * pszUrl) override;
      virtual void did_pick_document_at_urls(const ::string_array & stra) override;
      virtual void on_prompt_write_file(::user::controller * pusercontroller) override;
          virtual void file_manager_save_as(::user::controller * pusercontroller) override;


      virtual bool fill_system_menu(::operating_system::a_system_menu * psystemmenu) override;
         
         
      void application_menu_update() override;

      virtual void on_system_main();

   };


} // namespace platform



