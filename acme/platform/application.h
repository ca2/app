//
// Created by camilo on 22/02/2022. 01:19 <3ThomasBorregaardSorensen!!
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:51 <3ThomasBorregaardSorensen!!
#pragma once


class main_hold_base;


#include "application_base.h"
#include "application_exit.h"
#include "application_flags.h"
#include "context.h"
#include "acme/primitive/text/text.h"


namespace acme
{


   class CLASS_DECL_ACME application :
      virtual public application_base,
      virtual public APPLICATION_FLAGS,
      virtual public ::acme::context,
      virtual public ::application_exit
   {
   public:


      ::apex::application* m_papexapplication;
      ::aqua::application* m_paquaapplication;
      ::aura::application* m_pauraapplication;
      ::axis::application* m_paxisapplication;
      ::base::application* m_pbaseapplication;
      ::bred::application* m_pbredapplication;
      ::core::application* m_pcoreapplication;


      //::APPLICATION_FLAGS                      m_applicationflags;
      ::pointer<main_hold_base>                      m_pmainholdbase;
      // FROM ::main (Now main2)
      string                                          m_strCommandLine;


      bool                                            m_bModulePath = false;
      ::file::path                                    m_pathModule;

      bool                                            m_bModuleFolder = false;
      ::file::path                                    m_pathModuleFolder;


      string                              m_strProgName;
      string                           m_strStandalone;
      int                              m_iExitCode = 0;

      //::pointer < ::request >                         m_prequest;


      // END FROM ::main (Now main2 : merge)


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


      void initialize(::particle * pparticle) override;

      
      virtual void start_application(::request* prequest);
      
      //virtual void on_initialize_application();

      using ::acme::context::factory;

      virtual ::factory::factory_pointer& factory() override;

      virtual void implement_application();

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

      
      virtual void on_before_launching();
      virtual void os_native_bergedge_start();

      virtual void init1();
      virtual void init2();
      virtual void init3();


      virtual void init();


      virtual void do_install();
      virtual void do_uninstall();


      virtual void on_install();
      virtual void on_uninstall();


      virtual void init_instance();


      virtual bool has_capability(enum_application_capability eapplicationcapability) const;
      virtual void add_capability(enum_application_capability ecapability);


      bool handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;
      virtual bool handle_application_call(::payload & payload, const ::string & strMember, ::property_set & propertyset);


      virtual ::file::path get_app_localconfig_folder();
      virtual ::pointer<::handle::ini>get_ini();


      virtual ::string get_visual_studio_build();


      virtual ::string get_application_name();


      void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema);

      virtual string get_locale_schema_dir(const ::string & strLocale, const ::string & strSchema);
      virtual string get_locale_schema_dir(const ::string & strLocale);
      string get_locale_schema_dir() override;

      virtual void set_locale(const string & pcsz, const ::action_context & action_context);

      virtual void set_schema(const string & pcsz, const ::action_context & action_context);

      virtual void on_set_locale(const string & pcsz, const ::action_context & action_context);

      virtual void on_set_schema(const string & pcsz, const ::action_context & action_context);



      virtual void fill_locale_schema(::text::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::text::international::locale_schema & localeschema, const string & strLocale, const string & strSchema);


      virtual void process_init();

      virtual void pre_run();
      virtual void application_pre_run();

      virtual void init_application();

   };


} // namespace acme



