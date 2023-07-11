#pragma once


//#include "aura/windowing/menu_item.h"
//#include "aura/windowing/menu.h"
#include "aura/user/user/box.h"


namespace user
{


   class CLASS_DECL_AURA frame:
      virtual public ::user::box
   {
   public:


      bool                                         m_bSnapToBars : 1;
      bool                                         m_bAddToTitle : 1;
      bool                                         m_bPrefixTitle : 1;


      ::user::frame_window *                       m_puserframewindow;

      ::pointer<::draw2d::icon>           m_pdrawicon;

      enum_style                                   m_estyle;
      string                                       m_strStyle;
      enum_display                                 m_edisplayRestore;
      bool                                         m_bDefaultNotifyIcon;
      string                                       m_strFrameTitle;
      ::size_i32                                   m_sizeMinimum;
      bool                                         m_bCloseApplicationIfLastVisibleFrame;
      ::pointer<::user::style>                  m_puserstyle;
      bool                                         m_bShowControlBox;
      
      
      ::pointer<::windowing::menu>m_pmenu;
      string_array                                 m_straMenuParent;
      string_array                                 m_straMenuName;
      string_array                                 m_straMenuId;
      ::pointer<::task_pool>                      m_ptaskpool;

  
      frame();
      ~frame() override;


      virtual void install_message_routing(::channel* pchannel) override;

      virtual ::task_pool  * taskpool() override;

      //virtual bool is_os_host() const override;

      using box::get_style;
      virtual style * get_style() const;

      virtual void set_frame_title(const string& strFrameTitle);
      virtual string get_frame_title();

     
      //::windowing::icon* get_windowing_icon() override;
      ::draw2d::icon* get_draw_icon() override;

      
      //void client_rectangle(::rectangle_i32 * prectangle) override;

      
      virtual bool is_translucid_user_style(enum_style estyle);
      virtual ::user::enum_style translate_user_style(const ::string & pszStyle);
      virtual ::color::color get_moveable_border_color();

      virtual void set_user_style(enum_style estyle);
      virtual void set_user_style(const ::string & strStyle);
      virtual void on_user_style_change();


      enum_window_type get_window_type() override;


      void handle(::topic * ptopic, ::context * pcontext) override;


      void display_previous_restore() override;
      void display_system_minimize() override;


      virtual ::color::color get_border_main_body_color();

      void add_menu_item(const ::string & strPath, const ::string & strText, const ::string & strId);


      virtual ::user::tool_window * tool_window(enum_tool etool, bool bCreate = false);


      //virtual ::user::toolbar * get_toolbar(const ::atom & idToolBar);

      virtual void add_control_bar(::user::control_bar * pcontrolbar);
      virtual void erase_control_bar(::user::control_bar * pcontrolbar);


      void show_control_bar(::user::control_bar * pcontrolbar) override;
      void hide_control_bar(::user::control_bar * pcontrolbar) override;


      //virtual ::pointer<toolbar>create_toolbar(const ::atom & idToolbar, const ::string & strToolbar = nullptr, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = CBRS_ALIGN_TOP, const ::type & type = "user::toolbar");


      virtual void on_create_bars();

      
      bool should_perform_layout(::draw2d::graphics_pointer & pgraphics) override;



      virtual ::user::interaction * get_active_impact();
      virtual void set_active_impact(::user::impact * pImpactNew, bool bNotify = true);

      virtual void ActivateFrame(::e_display edisplay = e_display_undefined);

      bool is_frame_window() override;

      //using ::user::box::_001FancyInitialFramePlacement;

      //bool _001FancyInitialFramePlacement(bool bForceRestore = false) override;

      virtual void initial_frame_placement();
      virtual void initial_frame_display();

      ::size_i32 get_window_minimum_size() override;

      DECLARE_MESSAGE_HANDLER(on_message_application_exit);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);

#ifdef WINDOWS_DESKTOP
      DECLARE_MESSAGE_HANDLER(_001OnSysCommand);
#endif

      //virtual bool _001Restore() override;


   };


} // namespace aura



