#pragma once

//namespace gen
//{
//   class command_line;
//}
//
//namespace ios
//{
//
//   class CLASS_DECL_ACME main_init_data :
//      public ::create
//   {
//   public:
//      HINSTANCE   m_hInstance;
//     HINSTANCE   m_hPrevInstance;
//      string      m_strCommandLine;
//      int         m_nCmdShow;
//   };
//
//   class CLASS_DECL_ACME application :
//   virtual public ::platform::application
//   {
//   public:
//
//      USHORT               m_atomApp;
//      USHORT               m_atomSystemTopic;
//      
//      main_init_data *     m_pmaindata;
//      
//      
//      application(::particle * pparticle);
//      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();

//      
//      virtual HINSTANCE GetHinstance();
//      bool _001OnDDECommand(const ::scoped_string & scopedstr);
//      virtual void _001EnableShellOpen();
//      virtual ::user::document * _001OpenDocumentFile(::payload payloadFile);
//      virtual void _001OnFileNew();
//      
//      
//      virtual void show_wait_cursor(bool bShow);
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
//      virtual int  term_instance() override;
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
////      ::pointer<::user::interaction>window_from_os_data(void * pdata);
////      ::pointer<::user::interaction>window_from_os_data_permanent(void * pdata);
//      
//      virtual ::thread * GetThread();
//      virtual void set_thread(::thread * pthread);
//      
////      virtual ::user::interaction * FindWindow(const char * lpszClassName, const char * lpszWindowName);
////      virtual ::user::interaction * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);
//      
//      virtual void get_time(struct timeval *p);
//      virtual void set_env_var(const string & payload,const string & value);
//      virtual itask get_thread_id();
//      
//      
////      virtual ::pointer<::user::printer>get_printer(const ::scoped_string & scopedstrDeviceName);
//
//       string draw2d_get_default_implementation_name();
//      string multimedia_audio_mixer_get_default_implementation_name();
//      string multimedia_audio_get_default_implementation_name();
//      string veriwell_multimedia_music_midi_get_default_implementation_name();
//
////      virtual void show_wait_cursor(bool bShow);
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
