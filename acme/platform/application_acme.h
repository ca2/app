//
// Created by camilo on 2024-10-24 22:47 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/prototype/text/text.h"


namespace platform
{


//   struct CLASS_DECL_ACME acme_application_layer_t
//   {
//
//      // mutable ::apex::application* m_papexapplication;
//      // mutable ::aqua::application* m_paquaapplication;
//      // mutable ::aura::application* m_pauraapplication;
//      // mutable ::axis::application* m_paxisapplication;
//      // mutable ::base::application* m_pbaseapplication;
//      // mutable ::bred::application* m_pbredapplication;
//      // mutable ::core::application* m_pcoreapplication;
//
//      class user_message :
//      virtual public ::particle
//      {
//
//         public:
//
//         ::e_status m_estatus;
//         ::particle_pointer m_pparticle;
//         long long m_hi;
//         void * m_p;
//
//      };
//
//      //bool                                            m_bTransferToContainer;
//      //bool                                            m_bTransferredToContainer;
//#if REFERENCING_DEBUGGING
//      ::reference_referer* m_prefererCreation = nullptr;
//#endif
//      //mutable ::platform::platform *               m_pplatform;
//
//      //::APPLICATION_FLAGS                      m_applicationflags;
//      ::pointer<main_hold_base>                       m_pmainholdbase;
//      // FROM ::main (Now main2)
//      ::pointer < ::filesystem::file_system_options > m_pfilesystemoptions;
//      ::pointer_array < user_message >                m_usermessagea;
//      bool                                            m_bGUIReady = false;
//      bool                                            m_bModulePath = false;
//      ::file::path                                    m_pathModule;
//
//      bool                                            m_bModuleFolder = false;
//      ::file::path                                    m_pathModuleFolder;
//
//
//      string                              m_strProgName;
//      string                           m_strStandalone;
//      //int                              m_iExitCode = 0;
//      bool                             m_bApplicationFirstRequest;
//      //::pointer < ::request >                         m_prequest;
//
//
//      // END FROM ::main (Now main2 : merge)
//
//      //::pointer < ::platform::platform >              m_pplatform;
//      string                                          m_strAppId;
//      string                                          m_strAppName;
//      string                                          m_strRoot;
//      string                                          m_strDomain;
//      string                                          m_strLibraryName;
//      string                                          m_strBuild;
//      string                                          m_strInstallToken;
//      string_array                                    m_straAppCategory;
//      bool                                            m_bLicense;
//
//      enum_application_capability_array               m_eapplicationcapabilitya;
//      ::text::text                                    m_textAppTitle;
//      ::text::text                                    m_textAppName;
//
//      ::pointer < ::mutex >                                      m_pmutexMatterLocator;
//
//      ::pointer < ::mutex >                                      m_pmutexStr;
//
//
//   };


   class CLASS_DECL_ACME acme_application_layer
   {
   public:


      virtual ::release_time_for_project release_time();


      //virtual void initialize_application(::platform::platform * pplatform);

      virtual void initialize_application();

// #if REFERENCING_DEBUGGING
//
//       void on_after_construct(::reference_referer* preferer) override;
//
// #endif

      virtual void _001TryCloseApplication();

      virtual void application_on_status(::e_status estatus, ::particle * pparticle = nullptr, long long hi = 0, void * p = nullptr);


      virtual void on_error_icloud_not_available(::particle * pparticle = nullptr, long long hi = 0, void * p = nullptr);


      //virtual void application_main(::platform::system * psystem);

      virtual int application_main();


      //void on_set_platform() override;


      //void on_initialize_particle() override;


      //void initialize(::particle * pparticle) override;


      //virtual void start_application(::request* prequest);
      
      virtual void start_application();

      //virtual void on_initialize_application();

      virtual class ::application_menu * application_menu();

//      using ::platform::context::factory;

//      virtual ::factory::factory_pointer& factory() const override;

      //virtual void implement_application();

      virtual void initialize_application_flags();

      virtual bool is_application() const;

      // bool is_system() const override;
      // bool is_session() const override;
      //
      // virtual bool is_service() const;
      // virtual bool is_user_service() const;
      //
      // virtual bool can_exit_application() override;

      virtual ::file::path get_module_path();
      virtual ::file::path get_module_folder();


      virtual ::string app_name();

      //virtual ::string app_name();

      virtual ::string app_root();

      virtual ::string application_title();


      virtual ::string application_name();
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

      virtual int __implement();

      virtual int main_loop();

      virtual ::enum_id key_command(::user::enum_key ekey, ::user::key_state * pkeystate);

      virtual void on_before_launching();
      //virtual void os_native_bergedge_start();

      // virtual void init1();
      // virtual void init2();
      // virtual void init3();
      //
      //
      // virtual void init();
      // virtual void term();
      //
      // virtual void term3();
      // virtual void term2();
      // virtual void term1();
      //

      virtual void do_install();
      virtual void do_uninstall();


      virtual void on_install();
      virtual void on_uninstall();


      virtual void init_instance();
      virtual void term_instance();

      // void init_task() override;
      // void term_task() override;


      virtual bool has_capability(enum_application_capability eapplicationcapability) const;
      virtual void add_capability(enum_application_capability ecapability);


      //bool handle_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset) override;
      virtual bool handle_application_call(::payload & payload, const ::scoped_string & scopedstrMember, ::property_set & propertyset);


      virtual ::file::path get_app_localconfig_folder();
      virtual ::property_set get_ini(const ::scoped_string& scopedstrIniName = {});


      virtual ::string get_visual_studio_build();


      virtual ::string get_application_name();


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

      virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale);
      virtual string get_locale_schema_dir();

      virtual void set_locale(const ::scoped_string & scopedstrLocale, const ::action_context & action_context);

      virtual void set_schema(const ::scoped_string& scopedstrSchema, const ::action_context & action_context);

      virtual void on_set_locale(const ::scoped_string& scopedstrLocale, const ::action_context & action_context);

      virtual void on_set_schema(const ::scoped_string& scopedstrSchema, const ::action_context & action_context);



      virtual void fill_locale_schema(::text::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::text::international::locale_schema & localeschema, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);


      virtual void process_init();
      virtual void process_term();

      //virtual void pre_run();
      //virtual void application_pre_run();

      //virtual void pos_run();
      //virtual void application_pos_run();

      virtual void init_application();

      virtual void term_application();

      virtual ::string_array get_about_box_lines();

      virtual void show_about_box(::user::activation_token * puseractivationtoken);

      //bool on_command_final(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;




      virtual void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem);
      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom);


      virtual get_file_extension_mime_type * get_get_file_extension_mime_type();

      virtual void pick_browse(const ::function < void(const ::file::path & path) > & callback);
      virtual void pick_media(const char * pszMediaType);
      virtual void did_pick_document_at_url(const char * pszUrl);
      virtual void did_pick_document_at_urls(const ::string_array & stra);
      virtual void on_prompt_write_file(::user::controller * pusercontroller);
      virtual void file_manager_save_as(::user::controller * pusercontroller);


      virtual bool fill_system_menu(::operating_system::a_system_menu * psystemmenu);

   };


} // namespace platform



