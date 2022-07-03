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
      ::rectangle_i32                                       m_rectanglePending;
      bool                                         m_bEnableFrameExperience;

      bool                                         m_bFullScreenReturn;
      bool                                         m_bFullScreenAlt;
      bool                                         m_bFullScreenCtrl;


      ::boolean                                 m_bitMinimizeToTray;
      bool                                         m_bFullScreenOnMaximize;
      
      ::u32                                        m_uiSWPFlags;

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

      comparable_array < enum_button >             m_ebuttonaHide;
      i32                                          m_iIndex;
      bool                                         m_bFullScreenOnZoom;
      bool                                         m_bInitialFramePosition;
         


      frame_window();
      ~frame_window() override;


      virtual __pointer(::experience::experience) create_experience(const ::string & strExperience);
      virtual __pointer(::experience::experience) experience(const ::string & strExperience);
      virtual __pointer(::experience::frame) frame_experience(const ::string & strExperience, const ::string & strFrame, const ::string & strStyle = nullptr);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      void defer_save_window_placement() override;

      virtual void window_enable_full_screen(bool bEnable = true);
      bool is_full_screen_enabled() const override;


      bool sketch_on_display() override;


      void display_previous_restore() override;

      void display_system_minimize() override;

      virtual void initialize_frame_window_experience();

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      void frame_experience_restore() override;

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience) override;


      virtual void _001OnExitFullScreen() override;

      virtual bool _001CallOnBeforeAppearance();
      virtual bool _001OnBeforeAppearance() override;



      virtual void _001OnAfterAppearance() override;




      virtual bool updown_get_up_enable() = 0;
      virtual bool updown_get_down_enable() = 0;

      virtual void frame_Attach();
      virtual void frame_Detach();


      virtual void _001OnTimer(::timer * ptimer) override;




      void OnNcCalcSize(RECTANGLE_I32 * prectangle);

      class dock_manager * dock_manager();
      class move_manager * move_manager();
      class size_manager * size_manager();


      virtual void set_frame(::experience::frame * pframe);
      void install_message_routing(::channel * pchannel) override;

      
      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      void on_command(::message::command * pcommand) override;
      

      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(_001OnNcLButtonDown);
      DECLARE_MESSAGE_HANDLER(_001OnNcMouseMove);
      DECLARE_MESSAGE_HANDLER(_001OnNcLButtonUp);
      DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnSysCommand);
      DECLARE_MESSAGE_HANDLER(on_message_size);

      virtual bool _001CanEnterScreenSaver() override;

      bool window_is_notify_icon_enabled() override;


      virtual index get_best_zoneing(edisplay & edisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleRequest = ::rectangle_i32(), bool bPreserveSize = false) override;



      bool IsHoverModeOn();
      bool IsHoverActive();
      void set_dock_mask(e_dock emask);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      void on_reposition() override;
      void ChildWnd(::user::interaction * pframewindow, ::user::interaction * puserinteractionParent);
      void FrameWnd(::user::interaction * pframewindow);
      bool Start();

      void Setframe_Style(i32 nStyle);
      void SetActiveFlag(bool fActive);
      void SetSWPFlags(::u32 uFlags);

      void GetRegionClientRect(RECTANGLE_I32 * prectangle);

      void get_draw_client_rect(RECTANGLE_I32 * prectangle);


      void relay_event(::message::message * pmessage);
      virtual void message_handler(::message::message * pusermessage) override;
      virtual void pre_translate_message(::message::message * pmessage) override;


      void enable_frame_experience(bool bEnable = true) override;
      void enable_dock(bool bEnable = true);
      void enable_move(bool bEnable = true);
      void enable_size(bool bEnable = true);
      void enable_menu(bool bEnable = true);

      bool is_frame_experience_enabled();
      bool is_docking_enabled();
      bool is_moving_enabled();
      bool is_sizing_enabled();
      bool is_sysmenu_enabled();


      ::experience::enum_frame experience_frame_hit_test(const ::point_i32& point);

      
      virtual button * get_box_button(enum_button ebutton);


      virtual void on_defer_display() override;


      virtual void on_visual_applied() override;


   };


} // namespace experience



