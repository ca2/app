#pragma once


#include "base/user/user/frame_window.h"


namespace experience
{


   class CLASS_DECL_BASE frame_window :
      virtual public ::user::frame_window
   {
   public:


      bool                                         m_bHoverModeOn;
      bool                                         m_bHoverActive;
      bool                                         m_bEnableMouse;
      ::pointer<::experience::frame>               m_pframe;
      bool                                         m_bEnableFrameExperience;

      bool                                         m_bFullScreenReturn;
      bool                                         m_bFullScreenAlt;
      bool                                         m_bFullScreenCtrl;


      ::logic::boolean                                   m_bitMinimizeToTray;
      bool                                         m_bFullScreenOnMaximize;
      
      unsigned int                                        m_uiSWPFlags;

      ::pointer<class move_manager>                m_pmovemanager;
      ::pointer<class size_manager>                m_psizemanager;
      ::pointer<class dock_manager>                m_pdockmanager;
      ::pointer<class menu_manager>                m_pmenumanager;

      bool                                         m_bDockEnable;
      bool                                         m_bMoveEnable;
      bool                                         m_bSizeEnable;
      bool                                         m_bMenuEnable;
      bool                                         m_bFullScreenEnable;

      bool                                         m_fActive;
      bool                                         m_bUseNc;

      comparable_array < enum_button >             m_ebuttonaHide;
      int                                          m_iIndex;
      bool                                         m_bFullScreenOnZoom;
      bool                                         m_bInitialFramePosition;
         


      frame_window();
      ~frame_window() override;



#ifdef _DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif


      virtual ::pointer<::experience::experience>create_experience(const ::scoped_string & scopedstrExperience);
      virtual ::pointer<::experience::experience>experience(const ::scoped_string & scopedstrExperience);
      virtual ::pointer<::experience::frame>frame_experience(const ::scoped_string & scopedstrExperience, const ::scoped_string & scopedstrFrame, const ::scoped_string & scopedstrStyle = nullptr);



      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      void defer_save_window_placement() override;

      virtual void window_enable_full_screen(bool bEnable = true);
      bool is_full_screen_enabled() override;


      ::int_rectangle outer_frame() override;


      ::item_pointer hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;


      void destroy() override;

      bool is_window_resizing() override;
      bool is_window_repositioning() override;
      bool is_window_docking() override;


      bool sketch_on_display() override;


      void display_docked(::e_display edisplay, const ::user::activation & useractivation) override;

      void display_previous_restore() override;

      void display_system_minimize() override;

      virtual void initialize_frame_window_experience();

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      void frame_experience_restore(const ::user::activation & useractivation = {}) override;

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience) override;


      //bool _001CallOnEnterAppearance();
      bool _001OnBeforeEnterAppearance() override;


      //bool _001OnBeforeExitFullScreen() override;


      //void _001OnAfterExitAppearance() override;


      virtual bool updown_get_up_enable() = 0;
      virtual bool updown_get_down_enable() = 0;


      virtual void frame_Attach();
      virtual void frame_Detach();


      virtual void on_timer(::timer * ptimer) override;




      void OnNcCalcSize(::int_rectangle * prectangle);

      class dock_manager * dock_manager();
      class move_manager * move_manager();
      class size_manager * size_manager();


      virtual void set_frame(::experience::frame * pframe);
      void install_message_routing(::channel * pchannel) override;

      
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      void on_command(::message::command * pcommand) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_parent_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_parent_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_parent_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      DECLARE_MESSAGE_HANDLER(_001OnNcLButtonDown);
      DECLARE_MESSAGE_HANDLER(_001OnNcMouseMove);
      DECLARE_MESSAGE_HANDLER(_001OnNcLButtonUp);
      DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnSysCommand);
      DECLARE_MESSAGE_HANDLER(on_message_size);

      virtual bool _001CanEnterScreenSaver() override;

      bool window_is_notify_icon_enabled() override;


      virtual ::collection::index get_best_zoneing(::e_display & edisplay, ::int_rectangle * prectangle, const ::int_rectangle & rectangleRequest = ::int_rectangle(), bool bPreserveSize = false) override;

      
      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


      bool IsHoverModeOn();
      bool IsHoverActive();
      void set_dock_mask(e_dock emask);

      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;
      void on_reposition() override;
      void ChildWnd(::user::interaction * pframewindow, ::user::interaction * puserinteractionParent);
      void FrameWnd(::user::interaction * pframewindow);
      bool Start();

      void Setframe_Style(int nStyle);
      void SetActiveFlag(bool fActive);
      void SetSWPFlags(unsigned int uFlags);

      //void GetRegionClientRectangle(::int_rectangle * prectangle);

      
      //::int_rectangle client_rectangle2(::user::enum_layout elayout = ::user::e_layout_design) override;


      void relay_event(::message::message * pmessage);
      virtual void message_handler(::message::message * pusermessage) override;
      virtual void pre_translate_message(::message::message * pmessage) override;


      void enable_frame_experience(bool bEnable = true) override;
      void enable_dock();
      void disable_dock();
      void enable_move(bool bEnable = true);
      void enable_size(bool bEnable = true);
      void enable_menu(bool bEnable = true);

      bool is_frame_experience_enabled();
      bool is_docking_enabled();
      bool is_moving_enabled();
      bool is_sizing_enabled();
      bool is_sysmenu_enabled();


      ::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder);

      //::item_pointer experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder);

      
      virtual button * get_box_button(enum_button ebutton);


      virtual void on_defer_display() override;


      //virtual void on_visual_applied() override;

      void place_set_need_redraw(const ::int_rectangle & rectangleAfter, const ::int_rectangle & rectangleBefore, ::draw2d::graphics * pgraphics) override;


      void _001OnAfterEnterZoomed() override;
      void _001OnAfterExitZoomed() override;


   };


} // namespace experience



