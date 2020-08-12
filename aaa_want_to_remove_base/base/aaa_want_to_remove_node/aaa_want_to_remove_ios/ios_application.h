#pragma once

namespace gen
{
   class command_line;
}

namespace ios
{

   class CLASS_DECL_AURA main_init_data :
      public ::aura::main_init_data
   {
   public:
      HINSTANCE   m_hInstance;
     HINSTANCE   m_hPrevInstance;
      string      m_strCommandLine;
      int         m_nCmdShow;
   };

   class CLASS_DECL_AURA application :
   virtual public ::aura::application
   {
   public:

      USHORT               m_atomApp;
      USHORT               m_atomSystemTopic;
      
      main_init_data *     m_pmaindata;
      
      
      application(::object * pobject);
      virtual ~application();
      
      virtual HINSTANCE GetHinstance();
      bool _001OnDDECommand(const char * pcsz);
      virtual void _001EnableShellOpen();
      virtual __pointer(::user::object) _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew();
      
      
      virtual void ShowWaitCursor(bool bShow);
      
      
      
      virtual string get_version();
      virtual void TermThread(HINSTANCE hInstTerm);
      
      virtual void SetCurrentHandles();
      
      virtual bool request(::aura::main_init_data * pdata);
      
      virtual bool process_init();
      virtual bool init1();
      virtual bool init2();
      virtual bool init3();
      virtual i32  exit_application() override;
      
      
      
      
      virtual bool win_init(main_init_data * pdata);
      
      virtual bool update_module_paths();
      
      
      
      
      
      __pointer(::user::interaction) window_from_os_data(void * pdata);
      __pointer(::user::interaction) window_from_os_data_permanent(void * pdata);
      
      virtual ::thread * GetThread();
      virtual void set_thread(::thread * pthread);
      
      virtual __pointer(::window) FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual __pointer(::window) FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);
      
      virtual void get_time(struct timeval *p);
      virtual void set_env_var(const string & var,const string & value);
      virtual u32 get_thread_id();
      
      
      virtual __pointer(::user::printer) get_printer(const char * pszDeviceName);

       string draw2d_get_default_library_name();
      string multimedia_audio_mixer_get_default_library_name();
      string multimedia_audio_get_default_library_name();
      string veriwell_multimedia_music_midi_get_default_library_name();

      virtual void ShowWaitCursor(bool bShow);
   
      
   };

   
} // namespace ios






