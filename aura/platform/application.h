#pragma once


#include "context.h"
#include "aqua/platform/application.h"
#include "aura/filesystem/filemanager/callback.h"
#include "aura/user/user/form_handler.h"


class track_popup_menu;


namespace aura
{


   class CLASS_DECL_AURA application :
      virtual public ::aqua::application,
      virtual public ::aura::context,
      virtual public ::filemanager::callback,
      virtual public ::user::form_handler
   {
   public:

//
//       //__creatable_from_base(application, ::apex::application);
//
//
//       void* m_pnativeapp;
//
//
//       ::aura::application *                           m_pappParent;
//       //string                                          m_strAppName;
//       //string                                          m_strAppTitle;
//       //string                                          m_XstrAppId;
//       //string                                          m_strBaseSupportId;
//       //string                                          m_strRoot;
//       //string                                          m_strDomain;
//       //string                                          m_strLibraryName;
//       //string                                          m_strRelativeFolder;
//       //string                                          m_strBuild;
//       //string                                          m_strInstallToken;
//       //string                                          m_strInstallTraceLabel;
//       //string                                          m_strInstallBuild;
//       //string                                          m_strHttpUserAgentToken;
//       //string                                          m_strHttpUserAgentVersion;
//       //string_array_base                                    m_straAppCategory;
//       //bool                                            m_bLicense;
//       //bool                                            m_bRequiresInstallation;
//
//       //bool                                            m_bReadStringTable;
//
//       //::pointer<::application_menu>            m_pappmenu;
//
//       //::pointer<::game::game>                      m_pgame;
//       ::pointer<::user::interaction>               m_pacmeuserinteractionMain;
//
//       ::pointer<shell_open>                        m_pshellopen;
//
//       ::string_array_base                               m_straOptionsFormMakerLibrary;
//       ::user::interaction_base *                             m_puiCurrent;
//       //bool                                            m_bContextTheme;
//
// // #if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
// //       bool                                            m_bSnLauncheeSetup;
// // #endif
//       //semaphore                                       m_semCompiler;
//       // former ::aura::application_interface // moved on 2015-05-23 Sammstag while listening to RocketBeansTV (a German channel?) at TwitchTV
//
//       unsigned int                                           m_dwInstallGoodToCheckAgain;
//
//       //bool                                            m_bAppHasInstallerProtected;
//       //bool                                            m_bAppHasInstallerChangedProtected;
//       //::install::installer *                          m_pinstaller;
//
//       particle_address_array                         m_particleaddressaEventHook;
//
//       ::pointer < ::mutex >                                           m_pmutexFrame;
//       ::pointer<::user::interaction_array>           m_puserinteractiona;
//       ::pointer<::user::interaction_array>           m_puserinteractionaFrame;
//
//       //e_thread                                        m_ethreadClose;
//
//       //enum_exclusive_instance                              m_eexclusiveinstance;
//
//       //string_map_base < ::pointer<::acme::exclusive >>    m_mapExclusive;
//
//       //bool                                            m_bService;
//
//       //bool                                            m_bUpdateMatterOnInstall;
//
//       ::user::interaction *                              m_puiMainContainer;
//
//       ::pointer < ::mutex >                                           m_pmutexMatterLocator;
//
//       //::pointer < ::mutex >                                         m_pmutexStr;
//       //string_table_base                                    m_stringtable;
//       //string_table_base                                    m_stringtableStd;
//       //map_base < atom, atom, string, string >                  m_stringmap;
//
//       //atom_map_base < ::pointer<::channel >>                m_mapNotify;
//
//       //::pointer<image_context>                       m_pimagecontext;
//
//       //bool                                            m_bInitializeDataCentral;
//
//       //string                                          m_strLicense;
//
//       //int                                             m_iWaitCursorCount;         // for wait cursor (>0 => waiting)
//
//       //::pointer<::simpledb::server>                  m_psimpledb;
//
//       //::userex::pane_tab_impact *                       m_pmainpane;
//
//
// //      string                                          m_strHelpFilePath;
// //
// //#ifdef WINDOWS
// //
// //      HGLOBAL                                         m_hDevMode;             // printer Dev Mode
// //      HGLOBAL                                         m_hDevNames;            // printer Device Names
// //
// //#endif
// //
// //      unsigned int                                             m_dwPromptContext;        // help action_context override for message box
// //      // LKG
// //      unsigned int                                             m_dwPolicies;            // block for storing boolean system policies
// //
// //      // Support for Shift+F1 help mode.
// //      // true if we're in SHIFT+F1 mode.
// //      bool                                            m_bHelpMode;
// //
// //      //::userex::pane_tab_impact *                       m_ppaneimpactMain;
// //
// //      string                                          m_strProfileName;
// //
// //      ATOM                                            m_atomApp;
// //      ATOM                                            m_atomSystemTopic;   // for DDE open
// //      unsigned int                                            m_nNumThumbnailPages; // number of default printed pages
// //
// //      string                                          m_strId;
//
// //      int                                             m_iResourceId;
//
//       //::pointer<::experience::department>          m_pexperience;
//       ::pointer<::aura::theme>                       m_ptheme;
//
//
//       //string_array_base                                    m_straAppInterest;
//       //string_map_base < oswindow, oswindow >               m_mapAppInterest;
//
//       //int                                             m_iGcomBackgroundUpdateMillis;
//
//

      ::pointer<::gpu::approach>                         m_pgpu;
      ::string                                           m_strGraphics3DImplementation;
      ::string                                           m_strDraw2dImplementation;

      ::string                                           m_strTypefaceImplementation;

      ::string                                           m_strImagingImplementation;


      application();
      ~application() override;
      

      virtual void initialize(::particle * pparticle) override;


      //virtual string application_file_setting(const ::scoped_string& scopedstrFileName);


      void on_set_platform() override;


         ::user::user * user() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void enumerate_composite(matter_array& a) override;

      ::aura::game* game() override;


      virtual void _001CloseApplication() override;



      void on_application_message(::platform::message * papplicationmessage) override;


      //virtual ::user::style* get_user_style() const;
      //virtual bool app_data_get(const ::atom & atom, stream & os) override;
      //virtual bool app_data_set(const ::atom & atom, stream & is) override;

      //virtual bool app_data_set(const ::atom & atom, object & obj) override;
      //virtual bool app_data_get(const ::atom & atom, object & obj) override;

//      virtual void     interactive_credentials(::account::credentials * pcredentials) override;

      //virtual ::database::key calc_data_key() override;


      //virtual string load_podata(const ::scoped_string & scopedstrLang, bool bOnlyHeader);

      //virtual string load_string(const ::atom & atom) override;
      //virtual bool load_string(string & str, const ::atom & atom) override;
      //virtual void load_string_table() override;
      //virtual bool load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable) override;
      //virtual bool load_cached_string_by_id(string & str, const ::atom & atom, bool bLoadStringTable) override;
      //virtual void load_string_table(const ::scoped_string & scopedstrApp, const ::scoped_string & scopedstrId) override;



      //virtual bool is_system() const override;
      //virtual bool is_session() const override;
      //virtual bool is_serviceable() const override;
      virtual string get_window_class_name(::user::enum_control_type econtroltype) override;

      //virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver() override;
      //inline ::image_context& image() { return *m_pimagecontext; }


      //virtual void verb() override;


      //::aura::session* get_session();
      //::aura::system* system();



      virtual bool Ex2OnAppInstall() override;
      virtual bool Ex2OnAppUninstall() override;

      //virtual void init_application() override;

      virtual void init1() override;
      virtual void init2() override;
      virtual void init3() override;


      virtual void init() override;


      virtual void init_instance() override;


      //virtual void     run() override;
      //virtual void     main() override;
      //virtual void     on_run();

      //virtual void application_pre_run();
      //virtual bool initial_check_directrix() override;
      //virtual void os_native_bergedge_start();





      virtual void term() override;


      virtual void term_application() override;




      //virtual bool InitApplication();


      virtual void do_install() override;
      virtual void do_uninstall() override;


      virtual void on_install() override;
      virtual void on_uninstall() override;


      virtual void update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pathRoot, const ::scoped_string & scopedstrRelative) override;
      virtual void update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pathRoot, const ::scoped_string & scopedstrRelative, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrStyle) override;

      //virtual void SetCurrentHandles() override;


      //virtual void process_exception(const ::exception & e) override;


      //virtual ::pointer<::aura::application>assert_running(const ::scoped_string & scopedstrAppId) override;

      //bool is_task_set() const override;



      //virtual void on_request(::request * prequest) override;



      virtual bool assert_user_logged_in() override;

      virtual string matter_as_string(const ::scoped_string & scopedstrMatter, const ::scoped_string & scopedstrMatter2 = nullptr) override;














      //virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);
      //virtual bool do_prompt_file_name(::payload& payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);
      //user virtual bool do_prompt_file_name(::payload& payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);


      virtual void process_message_filter(int code, ::message::message * pmessage) override;



      virtual void DoWaitCursor(int nCode) override; // 0 => restore, 1=> begin, -1=> end

      // virtual void _001TryCloseApplication() override;


      virtual string get_license_id() override;




      virtual void process_init() override;




//#ifdef WINDOWS_DESKTOP
//      virtual void TermThread(HINSTANCE hInstTerm) override;
//#endif

      //virtual void set_env_var(const string & payload, const string & value) override;


      virtual ::draw2d::printer * get_printer(const ::scoped_string & scopedstrDeviceName) override;


      virtual ::image::icon * set_icon(::object * pobject, ::image::icon * picon, bool bBigIcon) override;

      virtual ::image::icon * get_icon(::object * pobject, bool bBigIcon) const override;

      //virtual void on_service_request(::request * prequest) override;

      virtual string get_mutex_name_gen() override;

      //virtual ::user::interaction * user_interaction_from_oswindow(::windowing::window * pwindow);


      //virtual int hotplugin_host_starter_start_sync(const ::scoped_string & scopedstrCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);
      //virtual int hotplugin_host_host_starter_start_sync(const ::scoped_string & scopedstrCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);

      //virtual void on_update_impact(::user::impact * pimpact, ::user::impact * pviewSender, lparam lHint, object * pHint);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      //virtual void on_notify_control_event(::user::control_event* phappening);
      //virtual void route(::topic * ptopic, ::handler_context * phandlercontext);



      //user virtual bool on_open_document(::user::document * pdocument, ::payload payloadFile);
      //user virtual bool on_save_document(::user::document * pdocument, ::payload payloadFile);



      //inline ::html::html * html() { return puser->m_phtml; }

      //virtual ::html::html * create_html();

      //virtual string http_get(const ::scoped_string & scopedstrUrl, ::property_set & set) override;

      //virtual bool compress_ungz(const ::stream & os, const ::stream & is) override;

      ///virtual bool compress_ungz(memory_base & mem) override;
      //virtual bool compress_gz(const ::stream& os, const ::stream& is, int iLevel = 6) override;

      //virtual bool compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6) override;


      //virtual bool is_local_data() override;


      //application();
      //~ application() override;
      
      //virtual void locale_schema_matter(string_array_base & stra, const string_array_base & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      //virtual string get_locale_schema_dir();


      //virtual void initialize(::particle * pparticle) override;


      //::application_menu & applicationmenu();


      //virtual ::file::path appconfig_folder() override;


      //// void assert_ok() const override;
      //// void dump(dump_context & dumpcontext) const override;


      //virtual ::file::path get_app_localconfig_folder() override;
      //virtual ::handle::ini get_ini() override;


      //virtual bool app_data_set(const ::atom & atom, stream & os) override;
      //virtual bool app_data_get(const ::atom & atom, stream & is) override;

      //virtual bool app_data_set(const ::atom & atom, ::object & obj) override;
      //virtual bool app_data_get(const ::atom & atom, ::object & obj) override;

      void install_message_routing(::channel * pchannel) override;

      virtual string dialog_box(const ::scoped_string & scopedstrMatter, ::property_set & propertyset) override;

      //virtual void application_menu_update() override;


      //virtual string calc_data_key();



      //virtual void notify_changed(const ::atom & atom, const ::action_context & action_context);


      //virtual ::file::path local_application_path() override;

      //virtual ::file::path local_application_home_path() override;


      virtual void destroy() override;


      //virtual void release_parents() override;
      ::property_object * parent_property_set_holder() const override;


      //virtual bool is_set_finish() const override;


      virtual void on_change_theme() override;
      virtual string get_theme() override;


      //virtual ::pointer<::acme::exclusive>get_exclusive(const ::scoped_string & scopedstr, LPSECURITY_ATTRIBUTES psa) override;
      //virtual bool exclusive_fails(const ::scoped_string & scopedstr, LPSECURITY_ATTRIBUTES psa) override;


      //virtual bool start_application(bool bSynch, ::request * prequest) override;



      //virtual void release_children() override;
      //virtual void merge_command_line(::create * pcommand);

//   virtual void merge(::handler * phandler);

      //virtual void record(::create * pcommand);

      //virtual void on_event(unsigned long long u, ::particle * pparticle) override;
      //virtual ::pointer<::thread_toolset>create_thread_toolset(::enum_task_tool etool);


      //// ca2verses
      //// os_* functions generally
      //// reserves a lot of surprises from each
      //// operating system specific behavior
      //virtual void auto pmessagebox = __initialize_new ::message_box(::user::interaction_base * puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback());

//pmessagebox->sync();


      //virtual void ui_message_box(::user::interaction_base * puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback());
      //virtual void ui_message_box_timeout(::user::interaction_base * puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class ::time& timeTimeOut = time::infinite(), const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback());


      //using ::aura::context_thread::message_box;
      //virtual void message_box(::user::interaction_base * puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback());
      //virtual void message_box_timeout(::user::interaction_base * puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class ::time& timeTimeOut = time::infinite(), const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback());


      //virtual void on_file_new() override;


      //virtual string get_title() override;
      //virtual string_array_base get_categories() override;

      virtual void defer_create_keyboard() override;
      //virtual bool set_keyboard_layout(const ::scoped_string & scopedstrPath, const ::action_context & action_context);


      //virtual bool enable_application_events(::particle * pparticle, bool bEnable) override;

      //virtual bool is_equal_file_path(const ::file::path & path1, const ::file::path & path2) override;


      //virtual bool process_exception(const ::exception & e) override;


      //virtual bool is_system() const override;
      //virtual bool is_session() const override;
      //virtual bool is_serviceable() const;
      //virtual bool is_user_service() const override;

      //void set_has_installer(bool bSet);



      //virtual ::file::path defer_process_path(::file::path path);
      //virtual ::file::path full_process_path(::file::path path);

      //virtual void DoWaitCursor(int nCode); // 0 => restore, 1=> begin, -1=> end
      //virtual void show_wait_cursor(bool bShow = true) override;



      //virtual void process_message_filter(int code,::message::message * pmessage) override;

      virtual void on_thread_on_idle(::thread * pthread,int lCount) override;


      //virtual bool app_set(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrValue) override;
      //virtual string app_get(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrDefault = "") override;


      //virtual bool Ex2OnAppInstall();
      //virtual bool Ex2OnAppUninstall();

      using ::aqua::application::on_command;
      bool on_command_final(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;
      //virtual void _001CloseApplication();

      //virtual string get_license_id();

      //virtual string get_version() override;

//      virtual ::pointer<::interprocess::communication>create_interprocess_communication() override;

      //virtual void process_init();
      //virtual void process_term() override;

      //virtual void impl_process_init();
      //virtual void impl_init1();
      //virtual void impl_init2();
      //virtual void impl_init3();

      //virtual void impl_process_term();
      //virtual void impl_term1();
      //virtual void impl_term2();
      //virtual void impl_term3();

      //virtual void init1();
      //virtual void init2();
      //virtual void init3();

      virtual void term1() override;
      virtual void term2() override;
      virtual void term3() override;

      //virtual void init_thread() override;
      //virtual void init_application();
      //virtual void term_application();
      //virtual void term_thread() override;

      //virtual void init_instance() override;
      virtual void term_instance() override;

      //virtual void init();
      //virtual void term();

      //virtual void notify_process_init();
      //virtual void notify_init1();
      //virtual void notify_init2();
      //virtual void notify_init3();

      //virtual void notify_term3();
      //virtual void notify_term2();
      //virtual void notify_term1();
      //virtual void notify_process_term();

      // virtual bool is_installing();
      // virtual bool is_unstalling();

      //virtual string get_version();
      //virtual void     run() override;
      //virtual void     main() override;
      //virtual void     on_run();

      virtual void on_before_launching() override;
      //virtual void os_native_bergedge_start();

      //virtual void pre_run() override;
      //virtual void application_pre_run();

      ////virtual void on_pos_run_thread() override;
      //virtual void pos_run() override;
      //virtual void application_pos_run() override;

      ////virtual bool InitApplication();
      ////virtual void TermApplication() override;

      //virtual bool on_install();
      //virtual bool on_uninstall();

      //virtual bool system_add_app_install(const ::scoped_string & scopedstrId, const ::scoped_string & scopedstrBuild) override;

      //virtual void TermThread(HINSTANCE hInstTerm);

      //virtual void SetCurrentHandles();

      //virtual void set_env_var(const string & payload,const string & value);
      //virtual itask get_thread_id();


      //virtual bool _001OnDDECommand(const ::scoped_string & scopedstr) override;

      virtual void _001InitializeShellOpen() override;
      virtual void _001OnFileNew(::message::message * pmessage) override;


      //virtual string multimedia_audio_get_default_implementation_name() override;
      //virtual string multimedia_audio_mixer_get_default_implementation_name() override;
      //virtual string veriwell_multimedia_music_midi_get_default_implementation_name() override;

      //virtual bool get_temp_file_name_template(string & str, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrTemplate) override;

      //virtual bool get_temp_file_name(string & str, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension) override;

      //service_base * get_service();
      //virtual service_base * allocate_new_service() override;
      //virtual bool init_service() override;

      //virtual bool os_create_service() override;
      //virtual bool os_erase_service() override;

      //virtual bool os_start_service() override;
      //virtual bool os_stop_service() override;

      //virtual void on_service_request(::request * prequest);

      //virtual bool is_running();

      //virtual string get_mutex_name_gen();

      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this ___new additional instance creation
      //virtual void on_exclusive_instance_conflict(bool & bHandled, enum_exclusive_instance eexclusive, const ::scoped_string & scopedstrId) override;

      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this ___new additional instance creation
//      virtual bool on_exclusive_instance_local_conflict(bool & bHandled) override;

            /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this ___new additional instance creation
      //virtual bool on_exclusive_instance_local_conflict_id(bool & bHandled, const ::scoped_string & scopedstrId) override;

      /// return true if the external additional instance might continue execution
      /// bHandled true if some action was done in response to the external aaa_memory_new additional instance creation
      //virtual void on_additional_local_instance(bool & bHandled, const ::scoped_string & scopedstrModule, int iPid, const ::scoped_string & scopedstrCommandLine) override;

      //virtual void on_new_instance(const ::scoped_string & scopedstrModule, const ::atom & idPid) override;

      //virtual string get_local_mutex_id() override;
      //virtual string get_global_mutex_id() override;

      //virtual ::pointer< ::mutex > get_local_mutex();
      //virtual ::pointer< ::mutex > get_global_mutex();

      //virtual string get_local_mutex_name() override;
      //virtual string get_local_id_mutex_name() override;
      //virtual string get_global_mutex_name() override;
      //virtual string get_global_id_mutex_name() override;

      //virtual bool check_exclusive(bool & bHandled) override;
      //virtual bool release_exclusive() override;

      //virtual void on_set_scalar(e_scalar escalar,long long iValue,int iFlags) override;
      //virtual void get_scalar_minimum(e_scalar escalar,long long & i) override;
      //virtual void get_scalar(e_scalar escalar,long long & i) override;
      //virtual void get_scalar_maximum(e_scalar escalar,long long & i) override;



      //bool safe_is_running();


      //virtual void on_request(::request * prequest) override;

      //// name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
      //// get/set serializables to user directory
      //template < typename TYPE >
      //bool gudo_get(const ::scoped_string & scopedstrKey, TYPE & t);

      //template < typename TYPE >
      //bool gudo_set(const ::scoped_string & scopedstrKey, const TYPE & t);


      //virtual bool assert_user_logged_in();

      //virtual void     do_request(::request * prequest) override;
      //virtual void call_request(::request * prequest) override;


      //virtual void process_message(::user::message * base) override;

      //virtual void message_handler(::user::message * pusermessage) override;



      //virtual string http_get_locale_schema(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;

      //virtual void on_update_matter_locator() override;

      //virtual void locale_schema_matter(string_array_base & stra, const string_array_base & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      //virtual void matter_locator_locale_schema_matter(string_array_base & stra, const string_array_base & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;

      //virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      //virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale) override;
      //virtual string get_locale_schema_dir() override;

      //virtual void set_locale(const string & pcsz, const ::action_context & action_context) override;

      //virtual void set_schema(const string & pcsz, const ::action_context & action_context) override;

      //virtual void on_set_locale(const string & pcsz, const ::action_context & action_context) override;

      //virtual void on_set_schema(const string & pcsz, const ::action_context & action_context) override;



      //virtual void fill_locale_schema(::text::international::locale_schema & localeschema) override;
      //virtual void fill_locale_schema(::text::international::locale_schema & localeschema,const ::scoped_string & scopedstrLocale,const ::scoped_string & scopedstrSchema) override;

      //virtual bool platform_open_by_file_extension(::collection::index iEdge, const ::scoped_string & scopedstrPathName, ::request * prequest = nullptr) override;
      //virtual bool platform_open_by_file_extension(::collection::index iEdge,::create * pcc) override;


      //virtual bool on_start_application() override;

      //virtual bool os_on_start_application() override;

      //virtual bool is_application() const override;


      //DECLARE_MESSAGE_HANDLER(on_message_app_exit);
      //virtual bool _001OnAgreeExit() override;
      //virtual void france_exit() override;
      //virtual void _001FranceExit() override;


      //virtual string lstr(const ::atom & atom, const ::scoped_string & scopedstrDefault = "") override;



      //virtual bool do_install();
      //virtual bool do_uninstall();



      //void request(::create * pcommand) override;
      //void on_create(::request * prequest) override;

//      virtual void dispatch_user_message(::user::message * pusermessage);

      //virtual void throw_not_installed();

      //virtual void play_audio(::payload payloadFile, bool bSynch = false);

      //virtual void post_critical_error_message(const ::scoped_string & scopedstrMessage, bool bShowLog = true) override;

      //virtual void show_critical_error_log() override;

      //virtual string get_app_user_friendly_task_bar_name() override;

      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //virtual bool compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed);

      //virtual bool compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6);

      //virtual void interactive_credentials(::account::credentials * pcredentials) override;

      //virtual ::file::path get_executable_path() override;
      //virtual string get_executable_extension() override;
      //virtual string get_executable_title() override;
      //virtual string get_executable_appid() override;



      //virtual bool on_open_document_file(::payload payloadFile) override;

      //virtual string get_app_id(string wstr) override;


      //virtual void install_trace(const ::scoped_string & scopedstr) override;
      //virtual void install_trace(double dRate) override;
      //virtual bool register_spa_file_type() override;

      //virtual bool low_is_app_app_admin_running(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;
      //virtual void defer_start_program_files_app_app_admin(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;
      //virtual void start_program_files_app_app_admin(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration) override;



      virtual bool keyboard_focus_is_focusable(const ::user::interaction_base * pue) override;
      virtual bool keyboard_focus_OnSetFocus(::user::interaction_base * pue) override;

      virtual ::user::interaction * main_window() override;


      virtual bool is_sandboxed() override;



      ///virtual ::pointer<::user::message>get_user_message(MESSAGE * pmsg);

      virtual bool get_frame(::pointer<::user::interaction>& pinteraction) override;
      virtual void add_user_interaction(::user::interaction * puserinteraction) override;
      virtual void erase_user_interaction(::user::interaction * puserinteraction) override;

      void send_message_to_windows(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam) override; // with tbs in <3

      void route_message_to_windows(::message::message * pmessage) override; // with tbs in <3


      //virtual void send_language_change_message() override;



      virtual string preferred_experience() override;


      // user virtual ::user::document * place_hold(::user::interaction * pinteraction);


      virtual void post_message(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {}) override;


      //virtual ::image::icon * set_icon(object * pparticle, ::image::icon * picon, bool bBigIcon);

      //virtual ::image::icon * get_icon(object * pparticle, bool bBigIcon) const;

      //virtual void handle(::topic * ptopic, ::handler_context * phandlercontext);
void initialize_context() override;
         void initialize_context_1() override;


//      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//
////      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr);
//
//      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr);

      virtual void on_initial_frame_position(::user::frame_interaction * pframe) override;

      virtual void on_graphics_ready() override;

      //virtual ::type_atom user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);
      virtual ::type_atom control_type_from_id(const ::atom & atom, ::user::enum_control_type & econtroltype) override;


      //virtual ::atom translate_property_id(const ::atom & atom) override;
      //virtual property fetch_property(const ::atom & atom) override;

      //virtual void get_time(struct timeval *int_point) override;

      void close(::enum_exit eexit) override;


      void close_application() override;


      //user virtual ::pointer<::user::document>defer_create_impact(const ::scoped_string & scopedstrImpact, ::user::interaction * puiParent, e_window_flag ewindowflag, const ::atom & atom = nullptr);


      void HideApplication() override;


      //virtual void initialize(::particle * pparticle) override;

      //virtual void process_init() override;

      //virtual void init1() override; // first initialization
      //virtual void init2() override; // second initialization
      //virtual void init3() override; // third initialization and so on...

      //virtual void init() override; // last initialization

      //virtual void bergedge_start();
      //virtual void os_native_bergedge_start() override;

      //virtual void term_application() override;

      //virtual void term() override;

      //virtual void     main() override;

      //virtual ::aura::application * get_app() const override;

      //virtual bool is_system() const override;
      //virtual bool is_session() const override;

      //virtual unsigned int guess_code_page(const ::scoped_string & scopedstr) override;

      //virtual int _sync_message_box(::user::interaction_base* puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, unsigned int fuStyle) override;

      //virtual bool is_serviceable() const override;


      virtual void pre_translate_message(::message::message* pmessage) override;


      //virtual void EnableShellOpen() override;



      //virtual bool base_support() override;

      virtual bool on_run_install() override;
      virtual bool on_run_uninstall() override;

      DECLARE_MESSAGE_HANDLER(on_application_signal);
      DECLARE_MESSAGE_HANDLER(_001OnSwitchContextTheme);


      virtual bool on_idle(int lCount) override; // return true if more idle processing
      virtual void process_window_procedure_exception(const ::exception & e, ::message::message* pmessage) override;

//      void EnableModelessEx(bool bEnable);
//      bool GetResourceData(unsigned int nID, const ::scoped_string & scopedstrType, memory& storage);

//#ifdef WINDOWS
//      virtual bool OnMessageWindowMessage(MESSAGE * pmsg);
//
//#elif defined(LINUX)
//      virtual bool OnX11WindowMessage(void* pev);
//#endif

      bool CreateFileFromRawResource(unsigned int nID, const ::scoped_string & scopedstrType, const ::scoped_string & scopedstrFilePath);

      void OnUpdateRecentFileMenu(::message::command* pcommand);

      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      //virtual void EnableHtmlHelp();

      // set regsitry key name to be used by application's
      // profile member functions; prevents writing to an INI spfile->
      virtual void SetRegistryKey(const ::scoped_string & scopedstrRegistryKey) override;

      virtual void SetRegistryKey(unsigned int nIDRegistryKey) override;


      virtual void RegisterShellFileTypes(bool bCompat = false) override;

      // call after all doc templates are registered
      void UnregisterShellFileTypes();

      // run this cast as an embedded object.
      // virtual bool RunEmbedded();

      // run this cast as an OLE automation server.
      //virtual bool RunAutomated();

      // exiting
      bool save_all_modified() override; // save before exit
    
      virtual void _001OnFileNew() override;
       virtual void on_file_open() override;

      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      //virtual ::collection::count get_open_document_count();

      //static const char gen_FileSection[];
      //static const char gen_FileEntry[];
      //static const char gen_ThumbnailSection[];
      //static const char gen_ThumbnailEntry[];




      virtual bool does_launch_window_on_startup() override;
      virtual bool activate_app() override;





      virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::user::system* pusersystem) override;




       virtual ::aura::theme* theme()  override;
      

      virtual void initialize_contextualized_theme() override;



      virtual int track_popup_menu(::menu::track_popup* ptrackpopup) override;

      virtual bool get_fs_size(string& strSize, const ::scoped_string & scopedstrPath, bool& bPending) override;
      virtual bool get_fs_size(long long& i64Size, const ::scoped_string & scopedstrPath, bool& bPending) override;

      virtual void set_title(const ::scoped_string & scopedstrTitle) override;


      virtual bool _001CloseApplicationByUser(::pointer<::user::interaction>puserinteractionExcept) override;

      void update_app_interest();
      void ensure_app_interest();

      virtual bool is_system() const override;
      virtual bool is_session() const override;


//      virtual ::pointer<::apex::application>create_platform(::apex::session* psession) override;

      void data_on_after_change(::database::client* pclient, const ::scoped_string & scopedstr, ::topic * ptopic) override;


      virtual int GetVisibleTopLevelFrameCountExcept(::pointer<::user::interaction>puserinteractionExcept) override;
      virtual int GetVisibleFrameCount() override;

      virtual void prepare_form(atom atom, ::form_document* pformdocument) override;


      void report_error(const ::exception & exception, int iMessageFlags, const ::scoped_string & scopedstrTopic) override;


      bool can_close_application() override;


      virtual bool on_close_frame_window(::user::frame_interaction* pframe) override;


      void create_impact_system() override;

      virtual ::user::interaction* create_menu_interaction() override;

      void on_song_added(const ::scoped_string & scopedstr) override;


      virtual string get_visual_studio_build() override;


      string sound_path(const ::scoped_string & scopedstr) override;
      string get_default_playlist_path() override;

      
//#if defined(FREEBSD) || defined(OPENBSD)
//
//      bool os_on_start_application() override;
//
//#endif

      string draw2d_get_default_implementation_name() override;

      string typeface_get_default_implementation_name() override;

      string imaging_get_default_implementation_name() override;


      void on_additional_local_instance(bool & bHandled, const ::scoped_string & scopedstrModule, int iPid, const ::scoped_string & scopedstrCommandLine) override;


      // ::user::user * aurauser() override;
      // ::axis::user * axisuser() override;
      // ::berg::user * baseuser() override;
      // ::bred::user * breduser() override;
      // ::core::user * coreuser() override;

      void pick_browse(const ::function < void(const ::file::path & path) > & callback) override;
      
      void pick_media(const ::scoped_string & scopedstrMediaType) override;

      void on_prompt_write_file(::user::controller * pusercontroller) override;
      
      //::pointer < ::innate_ui::icon > innate_ui_icon(const ::int_size & size) override;
//      ::gpu::approach* get_gpu_approach() override;
//      ::gpu::approach* gpu() override;
//      void create_gpu() override;

      //virtual ::graphics3d::camera get_default_camera();


      virtual ::file::path assets_folder();

      virtual ::file::path shaders_folder();


      //virtual void initialize_cube(::user::graphics3d* pimpact);

      //virtual void run_application();

      //virtual void on_layout_cube(int cx, int cy);

      //::string draw2d_get_default_implementation_name() override;

      virtual ::string graphics3d_get_implementation_name();


   };


} // namespace aura







//CLASS_DECL_AURA unsigned int c_cdecl application_thread_procedure(LPVOID pvoid);

//typedef ::pointer<::aura::application>(*LPFN_instantiate_application)(::pointer<::aura::application>appParent, const ::scoped_string & scopedstrId);

//extern CLASS_DECL_AURA LPFN_instantiate_application g_lpfn_instantiate_application;

//#ifdef WINDOWS_DESKTOP
//
//CLASS_DECL_AURA BOOL LaunchAppIntoDifferentSession(const ::scoped_string & scopedstrProcess, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi, int iSession = -1);
//
//CLASS_DECL_AURA BOOL LaunchAppIntoSystemAcc(const ::scoped_string & scopedstrProcess, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi);
//
//#endif // WINDOWS_DESKTOP





