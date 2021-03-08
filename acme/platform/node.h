//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace acme
{


   class CLASS_DECL_ACME node :
      virtual public ::layered
   {
   public:


      ::apex::node *          m_papexnode;
      ::aura::node *          m_pauranode;
      ::user::enum_desktop    m_edesktop;

      ::logic::bit            m_bLastDarkModeApp;

      ::logic::bit            m_bLastDarkModeSystem;

      ::color::color          m_colorSystemAppBackground;
      double                  m_dSystemLuminance;
      int                     m_iWeatherDarkness;


      node();
      virtual ~node();


//#ifdef LINUX
//
//      virtual enum_linux_distribution get_linux_distribution() const;
//
//#endif

      virtual int node_init_check(int * pi, char *** ppz);

      virtual ::e_status start();

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

         node_fork(__routine(pred));

      }

      virtual void node_fork(const ::routine & routine);

      template < typename PRED >
      void node_sync(const ::duration & durationTimeout, PRED pred)
      {

         node_sync(durationTimeout, __routine(pred));

      }

      virtual void node_sync(const ::duration & durationTimeout, const ::routine & routine);

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

      virtual ::e_status get_system_time(system_time_t * psystemtime);

      virtual ::e_status file_time_to_time(time_t * ptime, const filetime_t * pfiletime, i32 nDST = -1);

      virtual ::e_status system_time_to_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST = -1);

      virtual ::e_status system_time_to_file_time(filetime_t * pfiletime, const system_time_t * psystemtime);

      virtual ::e_status time_to_system_time(system_time_t * psystem_time, const time_t * ptime);

      virtual ::e_status time_to_file_time(filetime_t * pfiletime, const time_t * ptime);

      virtual ::e_status get_system_time_as_file_time(filetime_t * pfiletime);

      virtual ::e_status file_time_to_system_time(system_time_t * psystemtime, const filetime_t * pfiletime);

      virtual ::e_status file_time_to_local_file_time(filetime_t * pfiletimeLocal, const filetime_t * pfiletime);

      virtual ::e_status is_valid_filetime(const filetime_t * pfiletime);

      virtual filetime get_filetime_now();


   };


} // namespace linux



