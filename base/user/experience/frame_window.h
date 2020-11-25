#pragma once


namespace experience
{


   class CLASS_DECL_BASE frame_window :
      virtual public ::user::frame_window
   {
   public:


      bool                                         m_bHoverModeOn;
      bool                                         m_bHoverActive;
      bool                                         m_bEnableMouse;
      __composite(::experience::frame)             m_pframe;
      ::rect                                       m_rectPending;
      bool                                         m_bEnableFrameExperience;

      bool                                         m_bFullScreenReturn;
      bool                                         m_bFullScreenAlt;
      bool                                         m_bFullScreenCtrl;


      ::logic::bit                                 m_bitMinimizeToTray;
      bool                                         m_bFullScreenOnMaximize;


      ::u32                                         m_uiSWPFlags;

      __composite(class move_manager)              m_pmovemanager;
      __composite(class size_manager)              m_psizemanager;
      __composite(class dock_manager)              m_pdockmanager;
      __composite(class menu_manager)              m_pmenumanager;

      bool                                         m_bDockEnable;
      bool                                         m_bMoveEnable;
      bool                                         m_bSizeEnable;
      bool                                         m_bMenuEnable;
      bool                                         m_bFullScreenEnable;

      bool                                         m_fActive;
      bool                                         m_bUseNc;

      __composite(::draw2d::icon)                  m_picon;

      comparable_array < ::experience::e_button >  m_ebuttonaHide;
      i32                                          m_iIndex;
      bool                                         m_bFullScreenOnZoom;
      bool                                         m_bInitialFramePosition;
         


      frame_window();
      virtual ~frame_window();


      virtual ::experience::experience* get_new_experience(const char* pszExperienceLibrary);
      virtual ::experience::experience* get_experience(const char* pszExperienceLibrary);
      virtual ::experience::frame* get_frame_experience(const char* pszExperienceLibrary, const char* pszFrame, const char* pszStyle = nullptr);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void defer_save_window_placement() override;

      virtual void window_enable_full_screen(bool bEnable = true);
      virtual bool is_full_screen_enabled() const override;


      virtual bool sketch_on_display() override;


      virtual void display_previous_restore() override;

      virtual void display_system_minimize() override;

      virtual void toggle_restore();

      virtual bool initialize_frame_window_experience();

      virtual void on_command_message(::user::command* pcommand) override;
      virtual void route_command_message(::user::command* pcommand) override;


      //virtual void wfi_dock_on_button_down(::user::control_event * pevent);

      virtual void experience_on_start_dock(::message::mouse * pmouse);

      //virtual bool WfiOnBeginSizing(::u32 nType, const ::point & point);
      //virtual bool WfiOnBeginMoving(const ::point & point);

      virtual void frame_experience_restore();

      virtual void on_start_layout_experience(e_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(e_layout_experience elayoutexperience) override;


      virtual void _001OnExitFullScreen() override;

      virtual bool _001CallOnBeforeAppearance();
      virtual bool _001OnBeforeAppearance() override;



      virtual void _001OnAfterAppearance() override;




      virtual bool updown_get_up_enable() = 0;
      virtual bool updown_get_down_enable() = 0;

      virtual void frame_Attach();
      virtual void frame_Detach();


      virtual void _001OnTimer(::timer * ptimer) override;




      void OnNcCalcSize(RECT32 * prect);

      class dock_manager * dock_manager();
      class move_manager * move_manager();
      class size_manager * size_manager();


      virtual void set_frame(::experience::frame * pframe);
      virtual void install_message_routing(::channel * pchannel) override;

      
      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;
      

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnNcLButtonDown);
      DECL_GEN_SIGNAL(_001OnNcMouseMove);
      DECL_GEN_SIGNAL(_001OnNcLButtonUp);
      DECL_GEN_SIGNAL(_001OnNcHitTest);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnCommand);
      DECL_GEN_SIGNAL(_001OnSysCommand);
      DECL_GEN_SIGNAL(_001OnSize);

      virtual bool _001CanEnterScreenSaver();

      bool window_is_notify_icon_enabled() override;


      virtual index get_best_zoneing(edisplay & edisplay, ::rect * prect, const ::rect & rectRequest = ::rect(), bool bPreserveSize = false) override;



      bool IsHoverModeOn();
      bool IsHoverActive();
      void set_dock_mask(edock emask);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      void on_reposition() override;
      void ChildWnd(::user::interaction * pframewindow, ::user::interaction * pwndParent);
      void FrameWnd(::user::interaction * pframewindow);
      bool Start();

      void Setframe_Style(i32 nStyle);
      void SetActiveFlag(bool fActive);
      void SetSWPFlags(::u32 uFlags);

      void GetRegionClientRect(RECT32 * prect);

      void get_draw_client_rect(RECT32 * prect);


      void relay_event(::message::message * pmessage);
      virtual void message_handler(::message::base * pbase) override;
      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void on_control_event(::user::control_event * pevent) override;


      void enable_frame_experience(bool bEnable = true);
      void enable_dock(bool bEnable = true);
      void enable_move(bool bEnable = true);
      void enable_size(bool bEnable = true);
      void enable_menu(bool bEnable = true);

      bool is_frame_experience_enabled();
      bool is_docking_enabled();
      bool is_moving_enabled();
      bool is_sizing_enabled();
      bool is_sysmenu_enabled();

      //virtual void on_command_message(::user::command * pcommand) override;

      e_hittest _001HitTest(const ::point& point);

      virtual ::experience::button * get_box_button(e_button ebutton);

      virtual void on_defer_display() override;


      virtual void on_visual_applied() override;

   };



} // namespace experience


