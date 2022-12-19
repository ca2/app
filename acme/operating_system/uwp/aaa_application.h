//#pragma once
//
//
//namespace gen
//{
//
//
//   class command_line;
//
//
//} // namespace gen
//
//
//namespace universal_windows
//{
//
//
//   class CLASS_DECL_ACME main_init_data :
//      public ::create
//   {
//   public:
//
//
//      HINSTANCE   m_hInstance;
//      HINSTANCE   m_hPrevInstance;
//      int         m_nCmdShow;
//
//
//   };
//
//}

//
//   class CLASS_DECL_ACME application :
//      virtual public ::acme::application
//   {
//   public:
//
//
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
//      bool _001OnDDECommand(const char * pcsz);
//      virtual void _001EnableShellOpen();
////      virtual ::user::document * _001OpenDocumentFile(::payload payloadFile);
//      virtual void _001OnFileNew();
//
//      // Loads a cursor resource.
//      HCURSOR LoadCursor(const char * lpszResourceName) const;
//      HCURSOR LoadCursor(::u32 nIDResource) const;
//
//      // Loads a stock cursor resource; for for IDC_* values.
//      HCURSOR LoadStandardCursor(const char * lpszCursorName) const;
//
//      // Loads an OEM cursor; for all OCR_* values.
//      HCURSOR LoadOEMCursor(::u32 nIDCursor) const;
//
//      // Loads an icon resource.
//      HICON LoadIcon(const char * lpszResourceName) const;
//      HICON LoadIcon(::u32 nIDResource) const;
//
//      // Loads an icon resource; for stock IDI_ values.
//      HICON LoadStandardIcon(const char * lpszIconName) const;
//
//      // Loads an OEM icon resource; for all OIC_* values.
//      HICON LoadOEMIcon(::u32 nIDIcon) const;
//
//      virtual string get_version();
//
//      virtual bool Ex2OnAppInstall();
//      virtual bool Ex2OnAppUninstall();
//
//
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
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//      /*virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);
//
//      virtual bool begin(int nPriority = THREAD_PRIORITY_NORMAL, ::u32 nStackSize = 0,
//         ::u32 dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = nullptr);
//
//      bool CreateThread(::u32 dwCreateFlags = 0, ::u32 nStackSize = 0,
//         LPSECURITY_ATTRIBUTES lpSecurityAttrs = nullptr);
//
//      virtual iptr get_os_data();
//      virtual iptr get_os_int();
//
//
//      int GetThreadPriority();
//      bool SetThreadPriority(int nPriority);
//
//   // Operations
//      ::u32 SuspendThread();
//      ::u32 ResumeThread();
//      bool post_message(::user::interaction * pguie, const ::atom & atom, WPARAM wParam, LPARAM lParam);
//
//      virtual bool PreInitInstance();
//
//      // called when occurs an standard_exception exception in run
//      // return true to call run again
//      virtual bool on_run_exception(const ::exception & e);
//
//   // Overridables
//      // thread initialization
//      virtual bool init_application();
//
//      virtual ::message::e_prototype GetMessagePrototype(const ::atom & atom, ::u32 uCode);
//
//      // running and idle processing
//      virtual int run();
//      virtual void pre_translate_message(::message::message * pmessage);
//      virtual bool pump_message();     // low level message pump
//      virtual bool on_idle(::i32 lCount); // return true if more idle processing
//      virtual bool is_idle_message(MSG* pMsg);  // checks for special messages
//
//      // thread termination
//      virtual int term_instance() override; // default will 'delete this'
//
//      // Advanced: exception handling
//      virtual LRESULT ProcessWndProcException(::exception::acme* e, const MSG* pMsg);
//
//      // Advanced: handling messages sent to message filter hook
//      virtual bool ProcessMessageFilter(int code, LPMSG lpMsg);
//
//      // Advanced: virtual access to GetMainWnd()
//      virtual ::user::interaction* GetMainWnd();
//
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
//      virtual void CommonConstruct();
//      virtual void Delete();
//         // 'delete this' only if m_bAutoDelete == true
//
//
//
//      bool DispatchThreadMessageEx(MSG* msg);  // helper*/
//
//      //::draw2d::graphics * graphics_from_os_data(void * pdata);
//
//
//      //::pointer<::user::interaction>window_from_os_data(void * pdata);
//      //::pointer<::user::interaction>window_from_os_data_permanent(void * pdata);
//
//
//      //virtual ::pointer<::user::interaction>FindWindow(const char * lpszClassName, const char * lpszWindowName);
//      //virtual ::pointer<::user::interaction>FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);
//
//      virtual void get_time(struct timeval *p);
//      virtual void set_env_var(const string & payload,const string & value);
//      virtual u32 get_thread_id();
//
//      //::pointer<::user::printer>get_printer(const scoped_string & strDeviceName);
//
//
//      void show_wait_cursor(bool bShow);
//
//      virtual string draw2d_get_default_library_name();
//
//      string veriwell_multimedia_music_midi_get_default_library_name();
//
//
//         string multimedia_audio_mixer_get_default_library_name();
//
//         string multimedia_audio_get_default_library_name();
//
//   };
//
//
//} // namespace universal_windows
//
