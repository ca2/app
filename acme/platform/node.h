//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//

// Created by camilo on 2021-03-21 18:11 <3ThomasBS_!!
#pragma once


namespace acme
{


   class CLASS_DECL_ACME node :
      virtual public object
      //, virtual public layered < node >
   {
   public:


      ::apex::node *          m_papexnode;
      ::aura::node *          m_pauranode;

      void *                  m_pAcmePosix;
      void *                  m_pApexPosix;
      void *                  m_pAuraPosix;

      void *                  m_pAcmePlatform;
      void *                  m_pApexPlatform;
      void *                  m_pAuraPlatform;

      void *                  m_pNodeX11;
      void *                  m_pNodeXcb;
      void *                  m_pNodeGnome;
      void *                  m_pNodeKDE;
      void *                  m_pNodeDesktopEnvironmentGnome;
      void *                  m_pNodeDesktopEnvironmentKDE;

      ::user::enum_desktop    m_edesktop;

      ::logic::bit            m_bLastDarkModeApp;

      ::logic::bit            m_bLastDarkModeSystem;

      ::color::color          m_colorSystemAppBackground;
      double                  m_dSystemLuminance;
      int                     m_iWeatherDarkness;
      ::file::path            m_pathModule;


      node();
      virtual ~node();


//#ifdef LINUX
//
//      virtual enum_linux_distribution get_linux_distribution() const;
//
//#endif



      virtual string audio_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();


      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status on_initialize_object() override;

      virtual void initialize_memory_counter();

      virtual ::e_status system_main();

      virtual ::e_status on_start_system();


      virtual void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension);


#ifdef WINDOWS_DESKTOP

      virtual ::e_status register_dll(const ::file::path& pathDll);

#endif


      virtual ::file::path module_path_source();
      //virtual ::file::path module_path_seed();
      //virtual ::file::path module_path_origin();
      //::file::path update_module_path();


      virtual ::e_status register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


      virtual ::file::path _module_path();


      //virtual bool memory_counter_on();

      //virtual ::file::path memory_counter_base_path();

      virtual ::e_status datetime_to_filetime(::filetime_t* pfiletime, const ::datetime::time& time);



      virtual int node_init_check(int * pi, char *** ppz);

      virtual ::e_status start_node();

      virtual ::e_status install_sigchld_handler();

      virtual ::color::color get_system_color(enum_system_color esystemcolor);

      virtual ::e_status set_system_dark_mode1(bool bSet = true);

      virtual ::e_status set_app_dark_mode1(bool bSet = true);

      virtual ::e_status set_internal_system_dark_mode(bool bSet = true);

      virtual ::e_status set_internal_app_dark_mode(bool bSet = true);

      virtual bool is_system_dark_mode();

      virtual bool is_app_dark_mode();

      virtual ::color::color get_system_app_background_color();

      virtual void set_system_app_background_color(::color::color color);

      virtual double get_system_app_luminance();

      virtual void set_system_app_luminance(double dLuminance);

      virtual int get_simple_ui_darkness();

      virtual void set_simple_ui_darkness(int iWeatherDarkness);

      virtual bool _os_calc_app_dark_mode();

      virtual bool _os_calc_system_dark_mode();

      virtual void os_calc_user_dark_mode();

      virtual void on_os_dark_mode_change();

      virtual void defer_initialize_dark_mode();

      virtual string os_get_user_theme();

      virtual bool os_set_user_theme(const ::string & strUserTheme);

      virtual void os_process_user_theme(string strTheme);

      virtual bool set_wallpaper(index iScreen, string strLocalImagePath);

      virtual string get_wallpaper(index iScreen);

      virtual string get_file_icon_path(const char * pszPath, int iSize);

      virtual string get_file_content_type(const char * pszPath);

      virtual int os_launch_uri(const char * pszUri, char * pszError = NULL, int iBufferSize = 0);

      virtual void enable_wallpaper_change_notification();

      template < typename PRED >
      void node_fork(PRED pred)
      {

         node_branch(__routine(pred));

      }

      virtual ::e_status node_branch(const ::routine & routine);

      template < typename PRED >
      ::e_status node_sync(const ::duration & durationTimeout, PRED pred)
      {

         auto estatus = node_sync(durationTimeout, __routine(pred));

         if(!estatus)
         {

            return estatus;

         }

         return estatus;

      }

      virtual ::e_status node_sync(const ::duration & durationTimeout, const ::routine & routine);

//      template < typename PRED >
//      void user_fork(PRED pred)
//      {
//
//         user_fork(__routine(pred));
//
//      }

      //virtual void user_fork(const ::routine & routine);

//      template < typename PRED >
//      void user_sync(const ::duration & durationTimeout, PRED pred)
//      {
//
//         user_sync(durationTimeout, __routine(pred));
//
//      }

      //virtual void user_sync(const ::duration & durationTimeout, const ::routine & routine);


      virtual void node_post_quit();

      //virtual void enum_display_monitors(::aura::session * psession);

      virtual void os_post_quit();

      virtual bool should_launch_on_node(::subject::subject * psubject);

      virtual bool defer_launch_on_node(::subject::subject * psubject);

      virtual bool launch_on_node(::subject::subject * psubject);


      virtual string get_user_name();

      virtual ::color::color get_simple_ui_color(::user::enum_element eelement, ::user::enum_state estate = ::user::e_state_none);

      virtual ::color::color get_default_color(::u64 u);

      virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha);

      virtual ::e_status open_folder(::file::path & pathFolder);



      virtual double get_time_zone();




      virtual string font_name(enum_font efont);
      //virtual string font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont);


      virtual string file_memory_map_path_from_name(const string& strName);


   };


} // namespace linux



