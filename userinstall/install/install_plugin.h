#pragma once


#if defined()


int installer_start(const ::scoped_string & scopedstrVersion, const ::scoped_string & scopedstrId);


namespace install
{

   enum enum_check
   {
      
      check_before_auth,
      check_before_start

   };


   class CLASS_DECL_BERG plugin :
      virtual public ::hotplugin::plugin,
      virtual public ::account::login_callback
   {
   public:


      class CLASS_DECL_BERG thread_start_ca2 :
         public thread
      {
      public:


         plugin * m_pplugin;

         thread_start_ca2(::particle * pparticle);

         //virtual bool on_run_step();

         virtual void     run() override;


      } ;

      thread_start_ca2     m_startca2;
      canvas               m_canvas;
      class ::time m_timeLastInstallingCheck;
      class ::time m_timeLastRestart;
      // logged in ? alarm comments
      bool                 m_bLogged;
      // in login process, login screen should be shown
      bool                 m_bLogin;
      bool                 m_bCa2Login;
      bool                 m_bCa2Logout;
      bool                 m_bNativeLaunch;
      bool                 m_bPluginTypeTested;
      bool                 m_bPluginDownloaded;
      bool                 m_bNativeLaunchFail;
      bool                 m_bRestartCa2;
      bool                 m_bPendingRestartCa2;
      bool                 m_bPendingStream;
      class ::time m_timeLastOk;

      bool                 m_bPluginShiftKey;

      string               m_strLoginRequestingServer;

      ::int_rectangle             m_rectangleSent;
      string_array_base              m_straLinesNativeLaunch;

      //bool                 m_bHasCred;
      //bool                 m_bHasCredEval;


      plugin(::particle * pparticle);
      virtual ~plugin();


      void install_message_routing(::channel * pchannel) override;



      virtual bool hist(const ::scoped_string & scopedstrUrl);
      virtual void run_start_install(const ::scoped_string & scopedstrType, const ::scoped_string & scopedstrRun, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);


      virtual void start_ca2();

      virtual bool thread_start_ca2_on_idle();

      virtual bool plugin_initialize();

      virtual void on_paint(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lprect);

      virtual void on_prepare_memory();

      virtual void on_login_result(const ::e_status & estatus, const ::scoped_string & scopedstrResponse);

      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      
      virtual void message_handler(::user::message * pusermessage) override;

      virtual void on_paint_progress(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lprect);

      virtual double extract_spa_progress_rate();

      virtual void deferred_prodevian_redraw();

#ifndef UNIVERSAL_WINDOWS

      virtual void on_post(::aura::ipc::rx * prx, long long a, long long b);

      using ::hotplugin::plugin::on_receive;

      virtual void on_receive(::aura::ipc::rx * prx, int message, void * pdata, int len);

#endif

      virtual bool native_launch();

      virtual bool is_installing();

      virtual void restart_aura_ipc();

      using ::hotplugin::plugin::set_window_position;
      virtual bool set_window_position(iptr z,int x,int y,int cx,int cy,unsigned int nFlags = SWP_SHOWWINDOW);

      virtual void on_ready();

      virtual string defer_get_plugin();

      using ::hotplugin::plugin::viewport_screen_to_client;
      virtual void viewport_screen_to_client(::int_point * ppt);
      
      using ::hotplugin::plugin::viewport_client_to_screen;
      virtual void viewport_client_to_screen(::int_point * ppt);

      virtual bool set_host(::hotplugin::host * phost);

      //::pointer<::user::interaction>GetFocus();

      //::pointer<::user::interaction>set_keyboard_focus();

      virtual void on_host_timer();

   };


} // namespace install



#endif



