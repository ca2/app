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
//      virtual public ::platform::acme_application_layer_t,
//      virtual public ::platform::apex_application_layer_t,
//      virtual public ::platform::aqua_application_layer_t,
//      virtual public ::platform::aura_application_layer_t,
//      virtual public ::platform::axis_application_layer_t,
//      virtual public ::platform::base_application_layer_t,
//      virtual public ::platform::bred_application_layer_t,
//      virtual public ::platform::core_application_layer_t,
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

         
         
         // mutable ::apex::application* m_papexapplication;
         // mutable ::aqua::application* m_paquaapplication;
         // mutable ::aura::application* m_pauraapplication;
         // mutable ::axis::application* m_paxisapplication;
         // mutable ::base::application* m_pbaseapplication;
         // mutable ::bred::application* m_pbredapplication;
         // mutable ::core::application* m_pcoreapplication;

         class user_message :
         virtual public ::particle
         {

            public:

            ::e_status m_estatus;
            ::particle_pointer m_pparticle;
            long long m_hi;
            void * m_p;

         };

         //bool                                            m_bTransferToContainer;
         //bool                                            m_bTransferredToContainer;
   #if REFERENCING_DEBUGGING
         ::reference_referer* m_prefererCreation = nullptr;
   #endif
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

         bool m_bUseDraw2dProtoWindow;
         string                              m_strProgName;
         string                           m_strStandalone;
         //int                              m_iExitCode = 0;
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
         //struct apex_application_layer_t
         //{
            //__creatable(application);

            void* m_pnativeapp;

            ::string m_strNetworkingApplicationHostname;
            //class application_impl *                     m_pappimpl;

            // 2020-01-25: removing from ::apex::system, placing here (at ::handler_context)
            // 2020-07-23: now at ::application
            ::pointer<::user::language_map> m_puserlanguagemap;

            //::pointer<::apex::application>             m_pappParent;
            string m_strBaseSupportId;
            string m_strDatabaseAppId;
            string m_strRelativeFolder;
            string m_strInstallTraceLabel;
            string m_strInstallBuild;
            string m_strHttpUserAgentToken;
            string m_strHttpUserAgentVersion;
            bool m_bRequiresInstallation;

            bool m_bReadStringTable;

            ::pointer<class ::application_menu> m_papplicationmenu;
            //::pointer<::apex::menu>                 m_pmainmenu;

            //::pointer<::game::game>                    m_pgame;

            ::pointer<::user::interaction_base> m_puiCurrent;
            bool m_bContextTheme;

            // #if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
            //       bool                                         m_bSnLauncheeSetup;
            // #endif
            //semaphore                                    m_semCompiler;
            // former ::application_interface // moved on 2015-05-23 Sammstag while listening to RocketBeansTV (a German channel?) at TwitchTV
            string_array m_straActivationMessage;

            unsigned int m_dwInstallGoodToCheckAgain;

            bool m_bAppHasInstallerProtected;
            bool m_bAppHasInstallerChangedProtected;
            ::pointer<::install::installer> m_pinstaller;

            particle_address_array m_particleaddressaEventHook;

            bool m_bAttendedFirstRequest;

            //bool                                       m_bAgreeExit;
            //bool                                       m_bAgreeExitOk;
            //bool                                       m_bFranceExit;

            bool m_bEnableAutoStartOption;
            bool m_bInterprocessCommunication;
            ::pointer<::interprocess::communication> m_pinterprocesscommunication;
            ::pointer<::interprocess::handler> m_pinterprocesshandler;
            //::pointer<service>                         m_pservice;

            //::string_array                               m_straInterprocessCommunicationPendingHandleUri;


            // apex commented
            //::pointer < ::mutex >                                         m_pmutexFrame;
            //::pointer<::user::interaction_pointer_array> m_puiptraFrame;

            enum_thread_context m_ethreadcontextClose;

            enum_exclusive_instance m_eexclusiveinstance;

            bool m_bService;

            bool m_bUpdateMatterOnInstall;

            //::user::interaction *                      m_puiMainContainer;

            string_table m_stringtable;
            string_table m_stringtableStd;
            atom_map<string> m_stringmap;

            atom_map<::pointer<::channel>> m_mapNotify;

            string m_strLicense;

            int m_iWaitCursorCount; // for wait cursor (>0 => waiting)

            bool m_bEnableFsRawFolderProtocols = true;

            //::pointer<::simpledb::server>              m_psimpledb;

            //::userex::pane_tab_impact *                m_pmainpane;


            string m_strHelpFilePath;

            //#ifdef WINDOWS
            //
            //      HGLOBAL                                         m_hDevMode;             // printer Dev Mode
            //      HGLOBAL                                         m_hDevNames;            // printer Device Names
            //
            //#endif

            unsigned int m_dwPromptContext; // help action_context override for message box
            // LKG
            unsigned int m_dwPolicies; // block for storing boolean system policies

            // Support for Shift+F1 help mode.
            // true if we're in SHIFT+F1 mode.
            bool m_bHelpMode;

            //::userex::pane_tab_impact *                m_ppaneimpactMain;

            string m_strProfileName;

            //#ifdef WINDOWS
            //      ATOM                                 m_atomApp;
            //      ATOM                                 m_atomSystemTopic;   // for DDE open
            //#endif

            unsigned int m_nNumThumbnailPages; // number of default printed pages

            string m_strId;

            int m_iResourceId;

            //::pointer<::experience::department>        m_pexperience;
            //::pointer<::apex::theme>                   m_ptheme;


            string_array m_straAppInterest;

            ::pointer<::service_handler> m_pservicehandler;

            ::pointer<::networking::application> m_pnetworkingapplication;

            ::string_map<::pointer<::fs::folder_sync>> m_fsfoldersyncmap;


         //}; // end apex_application_t

         //struct CLASS_DECL_ACME aqua_application_layer_t
         //{


            ::pointer<::aqua::game>                      m_paquagame;
            //::pointer<::networking::application>         m_p_networkingapplication;


         //}; // end aqua_application_layer_t

         //struct CLASS_DECL_ACME aura_application_layer_t
         //{


            //__creatable_from_base(application, ::apex::application);


            //void* m_pnativeapp;


            ::aura::application *                           m_pappParent;
            //string                                          m_strAppName;
            //string                                          m_strAppTitle;
            //string                                          m_XstrAppId;
            //string                                          m_strBaseSupportId;
            //string                                          m_strRoot;
            //string                                          m_strDomain;
            //string                                          m_strLibraryName;
            //string                                          m_strRelativeFolder;
            //string                                          m_strBuild;
            //string                                          m_strInstallToken;
            //string                                          m_strInstallTraceLabel;
            //string                                          m_strInstallBuild;
            //string                                          m_strHttpUserAgentToken;
            //string                                          m_strHttpUserAgentVersion;
            //string_array                                    m_straAppCategory;
            //bool                                            m_bLicense;
            //bool                                            m_bRequiresInstallation;

            //bool                                            m_bReadStringTable;

            //::pointer<::application_menu>            m_pappmenu;

            //::pointer<::game::game>                      m_pgame;
            //::pointer<::user::interaction>               m_pacmeuserinteractionMain;

            ::pointer<shell_open>                        m_pshellopen;

            ::string_array                               m_straOptionsFormMakerLibrary;
            //::user::interaction_base *                             m_puiCurrent;
            //bool                                            m_bContextTheme;

      // #if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
      //       bool                                            m_bSnLauncheeSetup;
      // #endif
            //semaphore                                       m_semCompiler;
            // former ::aura::application_interface // moved on 2015-05-23 Sammstag while listening to RocketBeansTV (a German channel?) at TwitchTV

            //unsigned int                                           m_dwInstallGoodToCheckAgain;

            //bool                                            m_bAppHasInstallerProtected;
            //bool                                            m_bAppHasInstallerChangedProtected;
            //::install::installer *                          m_pinstaller;

            //particle_address_array                         m_particleaddressaEventHook;

            ::pointer < ::mutex >                                           m_pmutexFrame;
            ::pointer<::user::interaction_array>           m_puserinteractiona;
            ::pointer<::user::interaction_array>           m_puserinteractionaFrame;

            //e_thread                                        m_ethreadClose;

            //enum_exclusive_instance                              m_eexclusiveinstance;

            //string_map < ::pointer<::acme::exclusive >>    m_mapExclusive;

            //bool                                            m_bService;

            //bool                                            m_bUpdateMatterOnInstall;

            ::user::interaction *                              m_puiMainContainer;

            //::pointer < ::mutex >                                           m_pmutexMatterLocator;

            //::pointer < ::mutex >                                         m_pmutexStr;
            //string_table                                    m_stringtable;
            //string_table                                    m_stringtableStd;
            //map < atom, atom, string, string >                  m_stringmap;

            //atom_map < ::pointer<::channel >>                m_mapNotify;

            //::pointer<image_context>                       m_pimagecontext;

            //bool                                            m_bInitializeDataCentral;

            //string                                          m_strLicense;

            //int                                             m_iWaitCursorCount;         // for wait cursor (>0 => waiting)

            //::pointer<::simpledb::server>                  m_psimpledb;

            //::userex::pane_tab_impact *                       m_pmainpane;


      //      string                                          m_strHelpFilePath;
      //
      //#ifdef WINDOWS
      //
      //      HGLOBAL                                         m_hDevMode;             // printer Dev Mode
      //      HGLOBAL                                         m_hDevNames;            // printer Device Names
      //
      //#endif
      //
      //      unsigned int                                             m_dwPromptContext;        // help action_context override for message box
      //      // LKG
      //      unsigned int                                             m_dwPolicies;            // block for storing boolean system policies
      //
      //      // Support for Shift+F1 help mode.
      //      // true if we're in SHIFT+F1 mode.
      //      bool                                            m_bHelpMode;
      //
      //      //::userex::pane_tab_impact *                       m_ppaneimpactMain;
      //
      //      string                                          m_strProfileName;
      //
      //      ATOM                                            m_atomApp;
      //      ATOM                                            m_atomSystemTopic;   // for DDE open
      //      unsigned int                                            m_nNumThumbnailPages; // number of default printed pages
      //
      //      string                                          m_strId;

      //      int                                             m_iResourceId;

            //::pointer<::experience::department>          m_pexperience;
            ::pointer<::aura::theme>                       m_ptheme;


            //string_array                                    m_straAppInterest;
            //string_map < oswindow, oswindow >               m_mapAppInterest;

            //int                                             m_iGcomBackgroundUpdateMillis;




         //}; // end aura_application_layer_t

         //struct CLASS_DECL_ACME axis_application_layer_t
         //{


            ::pointer<::simpledb::server>                        m_psimpledb;


        // }; // end axis_application_layer_t

         //struct CLASS_DECL_ACME base_application_layer_t
         //{


            //::pointer<::aura::application_menu>      m_pappmenu;

            ::pointer < ::user::tab_impact >                m_ptabimpactBase;
            ::pointer < ::user::options_impact_handler >    m_poptionsimpacthandler;


         //}; // end base_application_layer_t

//         struct CLASS_DECL_ACME bred_application_layer_t
//         {
//
//
//         }; // bred_application_layer_t
         
         
//         struct CLASS_DECL_ACME core_application_layer_t
//         {


            ::pointer<::userex::pane_tab_impact>     m_ppaneimpactCore;
            ::pointer < ::filemanager::filemanager> m_pfilemanager;


         //}; // end core_application_layer_t
         
      application();
      ~application() override;
      
#ifdef _DEBUG

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


      //virtual void application_main(::platform::system * psystem);

      virtual int application_main() override;


      void on_set_platform() override;


      void on_initialize_particle() override;

         ::user::user * user() override;

      //void initialize(::particle * pparticle) override;


      //virtual void start_application(::request* prequest) override;
         
         virtual void start_application() override;

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
      virtual ::property_set get_ini(const ::scoped_string& scopedstrIniName = {}) override;


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


#include "acme/prototype/prototype/factory.h"

#define IMPLEMENT_APPLICATION_FACTORY(APPLICATION_NAMESPACE) \
namespace APPLICATION_NAMESPACE \
{ \
CLASS_DECL_EXPORT void application_factory(::factory::factory * pfactory) \
{ \
   \
   pfactory->add_factory_item<::APPLICATION_NAMESPACE::application, ::platform::application>(); \
   \
} \
}




