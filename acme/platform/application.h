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
#include "application_menu_callback.h"
#include "context.h"
#include "release_time_for_project.h"
#include "acme/primitive/text/text.h"


namespace acme
{


   class CLASS_DECL_ACME application :
//      virtual public application_base,
      virtual public APPLICATION_FLAGS,
      virtual public ::acme::context,
      virtual public ::application_exit,
      virtual public ::application_menu_callback
   {
   public:


      mutable ::apex::application* m_papexapplication;
      mutable ::aqua::application* m_paquaapplication;
      mutable ::aura::application* m_pauraapplication;
      mutable ::axis::application* m_paxisapplication;
      mutable ::base::application* m_pbaseapplication;
      mutable ::bred::application* m_pbredapplication;
      mutable ::core::application* m_pcoreapplication;
      
      class user_message :
      virtual public ::particle
      {
         
         public:
         
         ::e_status m_estatus;
         ::pointer < ::particle > m_pparticle;
         long long m_ll;
         void * m_p;
         
      };

      bool                                            m_bTransferToContainer;
      bool                                            m_bTransferredToContainer;

      //mutable ::platform::platform *               m_pplatform;

      //::APPLICATION_FLAGS                      m_applicationflags;
      ::pointer<main_hold_base>                       m_pmainholdbase;
      // FROM ::main (Now main2)
      ::pointer < ::filesystem::file_system_options > m_pfilesystemoptions;
      ::pointer_array < user_message >                m_usermessagea;
      bool                                            m_bGUIReady = false;
      bool                                            m_bModulePath = false;
      ::file::path                                    m_pathModule;

      bool                                            m_bModuleFolder = false;
      ::file::path                                    m_pathModuleFolder;


      string                              m_strProgName;
      string                           m_strStandalone;
      int                              m_iExitCode = 0;
      bool                             m_bApplicationFirstRequest;
      //::pointer < ::request >                         m_prequest;


      // END FROM ::main (Now main2 : merge)

      //::pointer < ::platform::platform >              m_pplatform;
      string                                          m_strAppId;
      string                                          m_strAppName;
      string                                          m_strRoot;
      string                                          m_strDomain;
      string                                          m_strLibraryName;
      string                                          m_strBuild;
      string                                          m_strInstallToken;
      string_array                                    m_straAppCategory;
      bool                                            m_bLicense;

      enum_application_capability_array               m_eapplicationcapabilitya;
      ::text::text                                    m_textAppTitle;
      ::text::text                                    m_textAppName;

      ::pointer < ::mutex >                                      m_pmutexMatterLocator;

      ::pointer < ::mutex >                                      m_pmutexStr;


      application();
      ~application() override;
      
     
      virtual ::release_time_for_project release_time();


      virtual void initialize_application(::platform::platform * pplatform);


      
      
      virtual void application_on_status(::e_status estatus, ::particle * pparticle = nullptr, long long ll = 0, void * p = nullptr);
      
      
      virtual void on_error_icloud_not_available(::particle * pparticle = nullptr, long long ll = 0, void * p = nullptr);


      virtual ::i32 application_main(::platform::platform * pplatform);

      
      void on_set_platform() override;


      void on_initialize_particle() override;


      //void initialize(::particle * pparticle) override;

      
      virtual void start_application(::request* prequest);
      
      //virtual void on_initialize_application();
      
      virtual class ::application_menu * application_menu();

//      using ::acme::context::factory;

//      virtual ::factory::factory_pointer& factory() const override;

      //virtual void implement_application();

      virtual void initialize_application_flags();

      virtual bool is_application() const;

      bool is_system() const override;
      bool is_session() const override;

      virtual bool is_service() const;
      virtual bool is_user_service() const;

      virtual bool can_exit_application() override;

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
      virtual void os_native_bergedge_start();

      virtual void init1();
      virtual void init2();
      virtual void init3();


      virtual void init();
      virtual void term();

      virtual void term3();
      virtual void term2();
      virtual void term1();


      virtual void do_install();
      virtual void do_uninstall();


      virtual void on_install();
      virtual void on_uninstall();


      virtual void init_instance();
      virtual void term_instance();

      void init_task() override;
      void term_task() override;


      virtual bool has_capability(enum_application_capability eapplicationcapability) const;
      virtual void add_capability(enum_application_capability ecapability);


      bool handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;
      virtual bool handle_application_call(::payload & payload, const ::string & strMember, ::property_set & propertyset);


      virtual ::file::path get_app_localconfig_folder();
      virtual ::pointer<::handle::ini>get_ini();


      virtual ::string get_visual_studio_build();


      virtual ::string get_application_name();


      void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

      virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale);
      string get_locale_schema_dir() override;

      virtual void set_locale(const ::scoped_string & scopedstrLocale, const ::action_context & action_context);

      virtual void set_schema(const ::scoped_string& scopedstrSchema, const ::action_context & action_context);

      virtual void on_set_locale(const ::scoped_string& scopedstrLocale, const ::action_context & action_context);

      virtual void on_set_schema(const ::scoped_string& scopedstrSchema, const ::action_context & action_context);



      virtual void fill_locale_schema(::text::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::text::international::locale_schema & localeschema, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);


      virtual void process_init();
      virtual void process_term();

      virtual void pre_run();
      virtual void application_pre_run();

      virtual void pos_run();
      virtual void application_pos_run();

      virtual void init_application();

      virtual void term_application();

      virtual ::string_array get_about_box_lines();

      virtual void show_about_box();

      bool on_application_menu_action(const ::atom & atom) override;

      
      

      virtual void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem);
      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom);


      virtual get_file_extension_mime_type * get_get_file_extension_mime_type();

      virtual void pick_browse(const ::function < void(const ::file::path & path) > & callback);
      virtual void pick_media(const char * pszMediaType);
      virtual void did_pick_document_at_url(const char * pszUrl);
      virtual void did_pick_document_at_urls(const ::string_array & stra);
      virtual void on_prompt_write_file(::user::controller * pusercontroller);
      virtual void file_manager_save_as(::user::controller * pusercontroller);

   };


} // namespace acme



