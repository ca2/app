//
// Created by camilo on 22/02/2022. 01:19 <3ThomasBorregaardSørensen!!
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:51 <3ThomasBorregaardSørensen!!
#pragma once


class main_hold_base;


#include "application_base.h"
#include "application_exit.h"
#include "application_flags.h"
#include "context.h"


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

      virtual bool is_system() const;
      virtual bool is_session() const;

      virtual bool is_service() const;
      virtual bool is_user_service() const;

      virtual bool can_exit_application() override;

      virtual ::file::path get_module_path();
      virtual ::file::path get_module_folder();

//
//#ifdef WINDOWS
//
//      void get_arguments_from_command_line();
//
//#else
//
//      void set_args(int argc, char * argv[], char * envp[]);
//
//#endif

      virtual int __implement();

      virtual int main_loop();



      virtual void init1();


      virtual void init_instance();


      virtual bool has_capability(enum_application_capability eapplicationcapability) const;
      virtual void add_capability(enum_application_capability ecapability);


      bool handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;
      virtual bool handle_application_call(::payload & payload, const ::string & strMember, ::property_set & propertyset);


      virtual ::file::path get_app_localconfig_folder();
      virtual ::pointer<::handle::ini>get_ini();


   };


} // namespace acme



