#pragma once

//namespace gen
//{
//   class command_line;
//}
//
//namespace ios
//{
//
//   class CLASS_DECL_CORE main_init_data :
//      public ::create
//   {
//   public:
//      HINSTANCE   m_hInstance;
//     HINSTANCE   m_hPrevInstance;
//      string      m_strCommandLine;
//      int         m_nCmdShow;
//   };
//
//   class CLASS_DECL_CORE application :
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
//      application(::particle * pparticle);
//      ~application() override;
//      
//      virtual HINSTANCE GetHinstance();
//      bool _001OnDDECommand(const ::string & pcsz);
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
////      ::pointer<::user::interaction>window_from_os_data(void * pdata);
////      ::pointer<::user::interaction>window_from_os_data_permanent(void * pdata);
//      
//      virtual ::thread * GetThread();
//      virtual void set_thread(::thread * pthread);
//      
////      virtual ::user::interaction * FindWindow(const ::string & lpszClassName, const ::string & lpszWindowName);
////      virtual ::user::interaction * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const ::string & lpszClass, const ::string & lpszWindow);
//      
//      virtual void get_time(struct timeval *p);
//      virtual void set_env_var(const string & payload,const string & value);
//      virtual itask_t get_thread_id();
//      
//      
////      virtual ::pointer<::user::printer>get_printer(const ::string & pszDeviceName);
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
