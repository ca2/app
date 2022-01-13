#pragma once


#if defined()


i32 installer_start(const ::string & pszVersion, const ::string & pszId);


namespace install
{

   enum enum_check
   {
      
      check_before_auth,
      check_before_start

   };


   class CLASS_DECL_BASE plugin :
      virtual public ::hotplugin::plugin,
      virtual public ::account::login_callback
   {
   public:


      class CLASS_DECL_BASE thread_start_ca2 :
         public thread
      {
      public:


         plugin * m_pplugin;

         thread_start_ca2(::object * pobject);

         //virtual bool on_run_step();

         virtual void     run() override;


      } ;

      thread_start_ca2     m_startca2;
      canvas               m_canvas;
      ::duration m_durationLastInstallingCheck;
      ::duration m_durationLastRestart;
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
      ::duration m_durationLastOk;

      bool                 m_bPluginShiftKey;

      string               m_strLoginRequestingServer;

      ::rectangle_i32             m_rectangleSent;
      string_array              m_straLinesNativeLaunch;

      //bool                 m_bHasCred;
      //bool                 m_bHasCredEval;


      plugin(::object * pobject);
      virtual ~plugin();


      void install_message_routing(::channel * pchannel) override;



      virtual bool hist(const ::string & pszUrl);
      virtual void run_start_install(const ::string & pszType, const ::string & pszRun, const ::string & pszLocale, const ::string & pszSchema);


      virtual void start_ca2();

      virtual bool thread_start_ca2_on_idle();

      virtual bool plugin_initialize();

      virtual void on_paint(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lprect);

      virtual void on_prepare_memory();

      virtual void on_login_result(const ::e_status & estatus, const ::string & pszResponse);

      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      
      virtual void message_handler(::user::message * pusermessage) override;

      virtual void on_paint_progress(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lprect);

      virtual double extract_spa_progress_rate();

      virtual void deferred_prodevian_redraw();

#ifndef _UWP

      virtual void on_post(::aura::ipc::rx * prx, i64 a, i64 b);

      using ::hotplugin::plugin::on_receive;

      virtual void on_receive(::aura::ipc::rx * prx, i32 message, void * pdata, i32 len);

#endif

      virtual bool native_launch();

      virtual bool is_installing();

      virtual void restart_aura_ipc();

      using ::hotplugin::plugin::set_window_position;
      virtual bool set_window_position(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags = SWP_SHOWWINDOW);

      virtual void on_ready();

      virtual string defer_get_plugin();

      using ::hotplugin::plugin::viewport_screen_to_client;
      virtual void viewport_screen_to_client(POINT_I32 * ppt);
      
      using ::hotplugin::plugin::viewport_client_to_screen;
      virtual void viewport_client_to_screen(POINT_I32 * ppt);

      virtual bool set_host(::hotplugin::host * phost);

      //__pointer(::user::interaction) GetFocus();

      //__pointer(::user::interaction) SetFocus();

      virtual void on_host_timer();

   };


} // namespace install



#endif



