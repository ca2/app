#pragma once


namespace acme
{


   class CLASS_DECL_ACME application:
      virtual public ::acme::application,
      virtual public ::user::form_callback,
      virtual public ::user::impact_creator,
      virtual public ::filemanager::callback,
      virtual public ::document_manager_container
   {
   public:


      ::userex::pane_tab_view *              m_pmainpane;

      //__pointer(::matter)                           m_spobjectUserFs;

      __composite(::userfs::userfs)                   m_puserfs;

      string                                 m_strHelpFilePath;

#ifdef WINDOWS


      HGLOBAL                                m_hDevMode;             // printer Dev Mode
      HGLOBAL                                m_hDevNames;            // printer Device Names


#endif

      u32                               m_dwPromptContext;        // help action_context override for message box
      // LKG
      u32                               m_dwPolicies;            // block for storing boolean system policies



      // Support for Shift+F1 help mode.
      // TRUE if we're in SHIFT+F1 mode.
      bool                                   m_bHelpMode;

      ::userex::pane_tab_view *              m_ppaneviewMain;

      string                                 m_strProfileName;

      ATOM                                   m_atomApp;
      ATOM                                   m_atomSystemTopic;   // for DDE open
      ::u32                                   m_nNumPreviewPages; // number of default printed pages

      string                                 m_strId;

      i32                                    m_iResourceId;

      __pointer(::experience::department)    m_pexperience;
      __composite(::acme::theme)             m_ptheme;


      string_array                                m_straAppInterest;
      string_map < oswindow,oswindow >       m_mapAppInterest;

      i32                                    m_iGcomBackgroundUpdateMillis;


      application();
      virtual ~application();

      virtual ::estatus initialize(::matter * pobjectContext) override;

      virtual ::estatus process_init() override;

      virtual ::estatus init1() override; // first initialization
      virtual ::estatus init2() override; // second initialization
      virtual ::estatus init3() override; // third initialization and so on...

      virtual ::estatus init() override; // last initialization

      virtual ::estatus bergedge_start();
      virtual ::estatus os_native_bergedge_start() override;

      virtual void term_application() override;

      virtual void term() override;

      virtual ::estatus     main() override;

      //virtual ::acme::application * get_context_application() const override;

      virtual bool is_system() const override;
      virtual bool is_session() const override;

      virtual u32 guess_code_page(const string& str);

      virtual i32 _sync_message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::u32 fuStyle) override;

      virtual bool is_serviceable() const override;


      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void EnableShellOpen();




      virtual void _001CloseApplication() override;



      virtual void on_create_split_view(::user::split_view * pview);


      virtual ::type control_type_from_id(const ::id & id, ::user::e_control_type & econtroltype) override;


      virtual bool base_support();

      //virtual string sync_message_box(const string & pszMatter,property_set & propertyset) override;


      virtual __pointer(::user::interaction) uie_from_point(const ::point & point);

      virtual bool on_application_menu_action(const char * pszCommand) override;

      virtual bool on_install() override;
      virtual bool on_uninstall() override;
      virtual bool on_run_install();
      virtual bool on_run_uninstall();

      DECL_GEN_SIGNAL(on_application_signal);
      DECL_GEN_SIGNAL(_001OnSwitchContextTheme);


      // open named file, trying to match a regsitered
      // document template to it.
      virtual void on_request(::create * pcreate) override;

      // overrides for implementation
      virtual bool on_idle(::i32 lCount); // return TRUE if more idle processing
      virtual void process_window_procedure_exception(::exception::exception * pexception, ::message::message * pmessage) override;

      void EnableModelessEx(bool bEnable);
#ifdef WINDOWS
      HENHMETAFILE LoadEnhMetaFile(::u32 uResource);
#endif
      bool GetResourceData(::u32 nID,const char * lcszType,memory & storage);

#ifdef WINDOWS
      virtual bool OnMessageWindowMessage(LPMESSAGE pmsg);

#elif defined(LINUX)
      virtual bool OnX11WindowMessage(void * pev);
#endif

      bool CreateFileFromRawResource(::u32 nID,const char * lcszType,const char * pcszFilePath);

      virtual LRESULT GetPaintMsgProc(i32 nCode,WPARAM wParam,LPARAM lParam);


      void OnUpdateRecentFileMenu(::user::command * pcommand);

      //virtual void send_app_language_changed();
      virtual void route_command_message(::user::command * pcommand) override;




      void EnableHtmlHelp();


      //virtual i32 sync_message_box_timeout(::user::primitive * puiOwner,var var, const char * pszTitle, ::duration durationTimeout,::u32 fuStyle = e_message_box_ok) override;
      //virtual i32 sync_message_box(::user::primitive * puiOwner,const char * pszMessage, const char * pszTitle, ::u32 fuStyle = e_message_box_ok) override;
      

      //bool on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId) override;

      virtual bool process_exception(exception_pointer e) override;

      //virtual bool on_uninstall() override;

      //virtual bool is_serviceable() const override;

      //virtual bool on_install() override;


      ::user::document * place_hold(::user::interaction * pinteraction) override;



      //virtual bool on_install() override;
      //virtual bool on_application_menu_action(const char * pszCommand) override;


      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, ::user::menu_item * pitem) override;

      // set regsitry key name to be used by application's
      // profile member functions; prevents writing to an INI spfile->
      void SetRegistryKey(const char * pszRegistryKey);

      void SetRegistryKey(::u32 nIDRegistryKey);


      void RegisterShellFileTypes(bool bCompat = FALSE);

      // call after all doc templates are registered
      void UnregisterShellFileTypes();



      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
      void SelectPrinter(HANDLE hDevNames,HANDLE hDevMode,bool bFreeOld = TRUE);

      // create a DC for the system default printer.
      ::draw2d::graphics * CreatePrinterDC();

      
      //   bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

      // run this cast as an embedded matter.
      bool RunEmbedded();

      // run this cast as an OLE automation server.
      bool RunAutomated();

      // Parse the command line for stock options and commands.
      //   void ParseCommandLine(CCommandLineInfo& rCmdInfo);

      // React to a shell-issued command line directive.
      //   bool ProcessShellCommand(CCommandLineInfo& rCmdInfo);

      // Overridables


      // exiting
      virtual bool save_all_modified(); // save before exit
      virtual void HideApplication() override;
      virtual void close(::acme::e_end eend) override; // close documents before exiting

      // Advanced: to override message boxes and other hooks
      //virtual i32 DoMessageBox(const char * pszPrompt,::u32 nType,::u32 nIDPrompt);


      // Advanced: process async DDE request
      //virtual bool OnDDECommand(LPWSTR pszCommand);


//#ifdef WINDOWS_DESKTOP
//      // Advanced: Help support
//      virtual void WinHelp(uptr dwData,::u32 nCmd = HELP_CONTEXT);
//      virtual void HtmlHelp(uptr dwData,::u32 nCmd = 0x000F);
//      virtual void WinHelpInternal(uptr dwData,::u32 nCmd = HELP_CONTEXT);
//#endif

      // Command Handlers
      // map to the following for file new/open
      void _001OnFileNew();
      void on_file_open();

      // map to the following to enable print setup
      void OnFilePrintSetup();

      // map to the following to enable help
      void OnContextHelp();   // shift-F1
      void OnHelp();          // F1 (uses current action_context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING

      // Implementation

      void UpdatePrinterSelection(bool bForceDefaults);
      void SaveStdProfileSettings();  // save options to .INI file



      void DevModeChange(char * pDeviceName);


      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      i32 get_open_document_count();

      virtual bool do_prompt_file_name(var & varFile,string strTitle,u32 lFlags,bool bOpenFileDialog, ::user::impact_system * ptemplate,::user::document * pdocument) override;

      void EnableModeless(bool bEnable); // to disable OLE in-place dialogs


      // Helper for message boxes; can work when no application can be found
      //static i32 ShowAppMessageBox(__pointer(application)pApp,const char * pszPrompt,::u32 nType,::u32 nIDPrompt);

      static void DoEnableModeless(bool bEnable); // to disable OLE in-place dialogs

#ifdef WINDOWS_DESKTOP
      // helpers for registration
      HKEY GetSectionKey(const char * pszSection);

      HKEY GetAppRegistryKey();
#endif

      void OnAppExit();
      // System Policy Settings
      virtual bool LoadSysPolicies(); // Override to load policies other than the system policies that acme API loads.
      bool GetSysPolicyValue(u32 dwPolicyID,bool *pbValue); // returns the policy's setting in the out parameter
      bool _LoadSysPolicies() noexcept; // Implementation helper
      static const char gen_FileSection[];
      static const char gen_FileEntry[];
      static const char gen_PreviewSection[];
      static const char gen_PreviewEntry[];








      virtual bool does_launch_window_on_startup();
      virtual bool activate_app();

      // Hooks for your initialization code
      virtual bool InitApplication() override;



      virtual ::estatus init_application() override;

      //virtual ::estatus init_instance() override;


//      virtual bool process_exception(::exception_pointer e) override;





      virtual ::user::interaction * get_request_parent_ui(::user::interaction * pinteraction, ::create * pcreate);




      //      virtual ::acme::file_system & file_system();
      virtual bool _001OnDDECommand(const char * pcsz) override;

      virtual ::user::document * _001OpenDocumentFile(var varFile);
      //virtual bool on_open_document_file(var varFile) override;
      DECL_GEN_SIGNAL(_001OnFileNew) override;


      //virtual string get_version();


      virtual ::user::interaction_impl * get_desktop_window();

      virtual ::estatus     run() override;

      //::acme::application * get_context_system();

      virtual bool set_keyboard_layout(const char * pszPath, const ::action_context & action_context) override;


      ::experience::department * experience();
      

      virtual void on_change_theme() override;


      inline ::acme::theme * theme() { return m_ptheme.get(); }
      virtual string get_theme() override;
      
      
      virtual ::estatus initialize_contextualized_theme();




      virtual string dialog_box(const char * pszMatter,property_set & propertyset) override;

      virtual i32 track_popup_menu(const char * pszMatter,const ::point & point,__pointer(::user::interaction) puie);

      virtual bool get_fs_size(string & strSize,const char * pszPath,bool & bPending);
      virtual bool get_fs_size(i64 & i64Size,const char * pszPath,bool & bPending);

      virtual void set_title(const char * pszTitle);


      virtual bool _001CloseApplicationByUser(__pointer(::user::interaction) pwndExcept);


#ifdef WINDOWS_DESKTOP

      static BOOL CALLBACK GetAppsEnumWindowsProc(oswindow oswindow,LPARAM lParam);

#endif

      void update_app_interest();
      void ensure_app_interest();


      virtual oswindow get_ca2_app_wnd(const char * psz);


      //virtual void request_create(::create * pcreate);

      //      virtual void on_exclusive_instance_local_conflict();

      virtual i32 send_simple_command(const char * psz,void * osdataSender);
      virtual i32 send_simple_command(void * osdata,const char * psz,void * osdataSender);

      virtual ::acme::printer * get_printer(const char * pszDeviceName) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;










      virtual __pointer(::acme::application) create_platform(::acme::session * psession) override;





      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/System
      //
      //::user::document * place_hold(::user::interaction * pinteraction)  override;

      /*
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index i, RECT32 * prect);

      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, RECT32 * prect);

      */


      //////////////////////////////////////////////////////////////////////////////////////////////////
      // Session/Session
      //
      //         virtual __pointer(::bergedge::view) get_view();
      //       virtual __pointer(::bergedge::document) get_document();


      //virtual ::estatus add_library(::acme::library * plibrary);

      virtual ::estatus initialize_userex();
      virtual ::estatus userfs_init1();
      virtual ::estatus initialize1_experience();
      virtual ::estatus userfs_process_init();

      //virtual __pointer(::userex::userex) create_userex();
      //virtual __pointer(::userfs::userfs) create_userfs();




      //virtual void assert_valid() const;
      //virtual void dump(dump_context & action_context) const;


      //virtual void construct();
      //virtual void construct(const char * pszId);


      //virtual void _001OnFileNew();


      //virtual void on_request(::create * pcreate);

      //__pointer(::acme::application) get_context_system();

      //virtual __pointer(::acme::application) assert_running(const char * pszAppdId);









      // pointer < ::cubebase::application >::oattrib
      // or any function needing it
      application & operator = (const application & app)
      {

         UNREFERENCED_PARAMETER(app);

         // do nothing

         return *this;

      }

      // get a file and if there are exceptions, should show end user friendly messages
      virtual file_pointer friendly_get_file(var varFile,::u32 nOpenFlags);


      virtual void data_on_after_change(::message::message * pmessage);

      virtual ::user::document * open_document_file(::matter * pobject, const char * pszFileName);



      virtual i32 GetVisibleTopLevelFrameCountExcept(__pointer(::user::interaction) pwndExcept);
      virtual i32 GetVisibleFrameCount();

      virtual void on_create_keyboard() override;

      virtual ::type user_default_controltype_to_typeinfo(::user::e_control_type econtroltype) override;

      //virtual void set_form_impact_system(::user::impact_system * pdoctemplate,::user::impact_system * pdoctemplateChild,::user::impact_system * pdoctemplatePlaceHolder);

      ::user::document * hold(__pointer(::user::interaction) pinteraction);

      //virtual bool platform_open_by_file_extension(int iEdge,const char * pszPathName,application_bias * papplicationbias = nullptr);
      //virtual bool platform_open_by_file_extension(int iEdge,::create * pcc);


      virtual void on_change_cur_sel(::user::tab * ptab);


//      virtual void interactive_credentials(::account::credentials * pcredentials) override;
//      virtual string get_cred(string & strUsername, string & strPassword, string strToken);
//      virtual void set_cred(string strToken, const char * pszUsername, const char * pszPassword) override;
//      virtual void set_cred_ok(string strToken, bool bOk) override;

      virtual void remove_document_template(::user::impact_system * pimpactsystem);

      virtual bool _001OnAgreeExit() override;
      virtual void _001OnFranceExit() override;

      virtual void prepare_form(id id, ::form_document * pdocument);


      virtual void report_error(::exception::exception * pexception, int iMessageFlags, const char * pszTopic);



      virtual bool on_close_frame_window(::user::frame * pframe);




      //application();
      //virtual ~application();


      //virtual ::estatus     initialize(::matter* pobjectContext) override;


      //virtual void install_message_routing(::channel * pchannel) override;

      //virtual void on_apply(::action * paction) override;

      //virtual ::estatus process_init() override;

      virtual ::estatus init_instance() override;

      virtual ::estatus     create_impact_system();

      //virtual ::type user_default_controltype_to_typeinfo(::user::e_control_type econtroltype) override;
      //virtual ::type control_type_from_id(const ::id& id, ::user::e_control_type& econtroltype) override;


      virtual void on_create_impact(::user::impact_data* pimpactdata) override;
      void process_message_filter(i32 code, ::message::message* pmessage) override;



      //virtual __pointer(::user::user) create_user();

      virtual bool on_thread_on_idle(::thread* pthread, ::i32 lCount) override;



      virtual bool process_message() override;

      //i32 hotplugin_host_host_starter_start_sync(const char* pszCommandLine, ::acme::application* papp, ::hotplugin::host* phost, ::hotplugin::plugin* pplugin) override;


      //virtual ::form_property_set * get_form_property_set() override;



      using ::acme::application::on_control_event;
      using ::user::form_callback::on_control_event;


      //virtual void remove_document_template(::user::impact_system* pimpactsystem);

      //virtual void term_application() override;

      //virtual void SetCurrentHandles() override;

      virtual ::draw2d::icon* set_icon(matter* pobject, ::draw2d::icon* picon, bool bBigIcon) override;

      virtual ::draw2d::icon* get_icon(matter* pobject, bool bBigIcon) const override;

      virtual void on_control_event(::user::control_event* pevent) override;

      virtual ::user::interaction* create_menu_interaction();

      virtual __pointer(::user::document) defer_create_view(string strView, ::user::interaction* puiParent, ewindowflag ewindowflag = window_flag_none, const ::id& id = nullptr) override;

      // multimedia

      virtual void on_song_added(const string& str);

   };


} // namespace acme


CLASS_DECL_ACME ::u32 c_cdecl application_thread_procedure(LPVOID pvoid);

typedef __pointer(::acme::application) (*LPFN_instantiate_application)(__pointer(::acme::application) pappParent, const char * pszId);

extern CLASS_DECL_ACME LPFN_instantiate_application g_lpfn_instantiate_application;

#ifdef WINDOWS_DESKTOP

CLASS_DECL_ACME BOOL LaunchAppIntoDifferentSession(const char * pszProcess, const char * pszCommand, const char * pszDir, STARTUPINFO * psi, PROCESS_INFORMATION * ppi, int iSession = -1);

CLASS_DECL_ACME BOOL LaunchAppIntoSystemAcc(const char * pszProcess,const char * pszCommand,const char * pszDir,STARTUPINFO * psi,PROCESS_INFORMATION * ppi);

#endif // WINDOWS_DESKTOP





