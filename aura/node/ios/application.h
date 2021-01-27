#pragma once

//namespace gen
//{
//   class command_line;
//}
//
//namespace ios
//{
//
//   class CLASS_DECL_AURA main_init_data :
//      public ::create
//   {
//   public:
//      HINSTANCE   m_hInstance;
//     HINSTANCE   m_hPrevInstance;
//      string      m_strCommandLine;
//      int         m_nCmdShow;
//   };
//
//   class CLASS_DECL_AURA application :
//   virtual public ::aura::application
//   {
//   public:
//
//      USHORT               m_atomApp;
//      USHORT               m_atomSystemTopic;
//      
//      main_init_data *     m_pmaindata;
//      
//      
//      application(::layered * pobjectContext);
//      virtual ~application();
//      
//      virtual HINSTANCE GetHinstance();
//      bool _001OnDDECommand(const char * pcsz);
//      virtual void _001EnableShellOpen();
//      virtual ::user::document * _001OpenDocumentFile(::payload varFile);
//      virtual void _001OnFileNew();
//      
//      
//      virtual void ShowWaitCursor(bool bShow);
//      
//      
//      
//      virtual string get_version();
//      virtual void TermThread(HINSTANCE hInstTerm);
//      
//      virtual void SetCurrentHandles();
//      
//      virtual bool request(::create * pdata);
//      
//      virtual bool process_init();
//      virtual bool init1();
//      virtual bool init2();
//      virtual bool init3();
//      virtual i32  term_instance() override;
//      
//      
//      
//      
//      virtual bool win_init(main_init_data * pdata);
//      
////      virtual bool update_module_paths();
//      
//      
//      
//      
//      
////      __pointer(::user::interaction) window_from_os_data(void * pdata);
////      __pointer(::user::interaction) window_from_os_data_permanent(void * pdata);
//      
//      virtual ::thread * GetThread();
//      virtual void set_thread(::thread * pthread);
//      
////      virtual ::user::interaction * FindWindow(const char * lpszClassName, const char * lpszWindowName);
////      virtual ::user::interaction * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);
//      
//      virtual void get_time(struct timeval *p);
//      virtual void set_env_var(const string & payload,const string & value);
//      virtual ithread_t get_thread_id();
//      
//      
////      virtual __pointer(::user::printer) get_printer(const char * pszDeviceName);
//
//       string draw2d_get_default_library_name();
//      string multimedia_audio_mixer_get_default_library_name();
//      string multimedia_audio_get_default_library_name();
//      string veriwell_multimedia_music_midi_get_default_library_name();
//
////      virtual void ShowWaitCursor(bool bShow);
//   
//      
//   };
//
//   
//} // namespace ios
//
//
//
//
//
//
