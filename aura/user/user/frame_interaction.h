#pragma once


#include "acme/user/user/_style.h"
#include "acme/user/user/frame_interaction.h"
#include "aura/user/user/box.h"


namespace user
{


   class CLASS_DECL_AURA frame_interaction :
      virtual public ::user::box,
      virtual public ::acme::user::frame_interaction
   {
   public:


      //::oswindow                                   m_oswindow;

      bool                                         m_bSnapToBars : 1;
      bool                                         m_bAddToTitle : 1;
      bool                                         m_bPrefixTitle : 1;
      bool                                         m_bDefaultNotifyIcon2 : 1;


      ::user::frame_window *                       m_puserframewindow;

      ::pointer<::image::icon>           m_pdrawicon;

      enum_style                                   m_estyle;
      string                                       m_strStyle;
      enum_display                                 m_edisplayRestore;
      string                                       m_strFrameTitle;
      ::int_size                                   m_sizeMinimum;
      bool                                         m_bCloseApplicationIfLastVisibleFrame;
      ::pointer<::user::style>                     m_puserstyleFrameInteraction;
      bool                                         m_bShowControlBox;
      
      
      ::pointer<::windowing::menu>m_pmenu;
      string_array                                 m_straMenuParent;
      string_array                                 m_straMenuName;
      string_array                                 m_straMenuId;
      ::pointer<::task_pool>                      m_ptaskpool;

  
      frame_interaction();
      ~frame_interaction() override;



      virtual void create_window() override;


      virtual void install_message_routing(::channel* pchannel) override;

      virtual ::task_pool  * taskpool() override;

void on_before_create_window(acme::windowing::window* pacmewindowingwindow) override;
      void destroy() override;


      //void start_destroying_window() override;

      void destroy_window() override;

      //virtual bool is_os_host() const override;

      using box::get_style;
      virtual style * get_style() const;

      virtual void set_frame_title(const string& strFrameTitle);
      virtual string get_frame_title();

     
      //::windowing::icon* get_windowing_icon() override;
      ::image::icon* get_draw_icon() override;

      
      //void this->rectangle(::int_rectangle * prectangle) override;
      ::user::interaction_base * set_parent(::user::interaction_base * puserinteractionParent) override;
      
      
      void user_interaction_on_destroy() override;


      //::user::thread * user_thread() override;

      
      virtual bool is_translucid_user_style(enum_style estyle);
      virtual ::user::enum_style translate_user_style(const ::string & pszStyle);
      virtual ::color::color get_moveable_border_color();

      virtual void set_user_style(enum_style estyle);
      virtual void set_user_style(const ::string & strStyle);
      virtual void on_user_style_change();


      enum_window_type get_window_type() override;


      void handle(::topic * ptopic, ::handler_context * pcontext) override;


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


      //virtual ::pointer<toolbar>create_toolbar(const ::atom & idToolbar, const ::string & strToolbar = nullptr, unsigned int dwCtrlStyle = TBSTYLE_FLAT, unsigned int uStyle = CBRS_ALIGN_TOP, const ::type_atom & typeatom = "user::toolbar");


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

      ::int_size get_window_minimum_size() override;

      DECLARE_MESSAGE_HANDLER(on_message_application_exit);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);

#ifdef WINDOWS_DESKTOP
      DECLARE_MESSAGE_HANDLER(_001OnSysCommand);
#endif

      //virtual bool _001Restore() override;


   };


} // namespace aura



