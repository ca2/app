#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
////#include "acme/prototype/prototype/object.h"
#include "acme/constant/element.h"
#include "acme/exception/status.h"


namespace experience
{


   class CLASS_DECL_BERG frame :
      virtual public ::object
   {
   public:


      //enum enum_element
      //{

      //   ::e_element_none,
      //   e_element_top_left_icon,
      //   e_element_move_grip_minimal,
      //   ElementEnd,

      //};


      status < ::color::color >       m_colorMoveableBorderHilight;
      status < ::color::color >       m_colorMoveableBorderDkShadow;
      status < ::color::color >       m_colorCaptionTextBk;
      status < ::color::color >       m_colorActiveCaptionTextBk;
      status < ::color::color >       m_colorCaptionText;

      bool                                   m_bHollow;
      string                                 m_strExperience;
      string                                 m_strFrameSchema;
      ::int_rectangle                        m_rectangleCaption;
      ::int_rectangle                        m_rectangleWindowText;
      int                                    m_iControlBoxPosition;
      //::int_rectangle                      m_rectangleControlBoxFullScreen;
      //::int_rectangle                      m_rectangleControlBoxZoomed;
      //::int_rectangle                      m_rectangleControlBoxNormal;
      int_point                              m_pointWindowIcon;
      ///int_point                           m_pointMoveGripMinimal;

      status < ::color::color >              m_colorMoveableBorder;
      status < ::color::color >              m_colorMoveableBorderShadow;


      ::pointer < ::experience::experience >    m_pexperience;
      ::pointer < ::experience::frame_window >  m_pframewindow;

      ::pointer<control_box>              m_pcontrolbox;

      int                                    m_iCaptionHeight;
      int                                    m_iTitleBottom;

      ::int_rectangle                        m_rectangleMarginFullScreen;
      ::int_rectangle                        m_rectangleMarginZoomed;
      ::int_rectangle                        m_rectangleMarginNormal;
      ::int_rectangle                        m_rectangleMarginDock;

      ::int_rectangle                        m_rectangleCaptionTextPadding;


      //::int_rectangle                        m_rectangleX;
      ::int_rectangle                        m_rectangleWindow;

      bool                                   m_bFirstLayoutDone;
      bool                                   m_bControlBoxAlignRight;
      bool                                   m_bInitialControlBoxPosition;
      bool                                   m_bPendingStyleChange;
      //int                                    m_iCaptionHeight;



      frame();
      ~frame() override;



#ifdef _DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif

      void destroy() override;


      // ::berg::application * get_app();
      // ::berg::session * get_session();
      // ::berg::system * get_system();
      // ::base::user * user();


      virtual int adjust_client_height(int iHeight);
      virtual int adjust_client_width(int iWidth);

      //virtual void set_style(const ::scoped_string & scopedstrStyle);
      virtual void on_initialize_experience_frame();
      virtual void on_initialize_appearance();

      virtual void on_defer_display();

      //virtual void update_dock_grip_border_and_display();
      virtual void sync_dock_grip_border();

      virtual void set_need_redraw_frame(::user::enum_layout elayout);

      //virtual void update_drawing_objects();
      virtual void update_window_client_rect();
      //virtual void update_window_region(const ::int_rectangle & rectangleWindow);

      //virtual void update_window();
      //virtual void update_window_style();

      virtual void __defer_frame_placement_snapping();


      virtual string get_default_user_style() const;


      virtual void set_moveable_border_color(const ::color::color & color);


      virtual ::int_rectangle outer_frame();
      
      //virtual bool calculate_hosting_rectangle(::int_rectangle * prectangle, ::user::enum_layout elayout = ::user::e_layout_design);

      virtual bool calculate_hosting_rectangle(::int_rectangle * prectangle, ::draw2d::graphics_pointer & pgraphics);

      virtual ::int_rectangle hosting_rectangle();

      //virtual ::int_rectangle rectangle(::user::enum_layout elayout = ::user::e_layout_design);

      //virtual bool get_draw_client_rectangle(::int_rectangle * prectangle, ::user::enum_layout elayout = ::user::e_layout_design);


      //virtual void calc_window_client_rect(::int_rectangle * prectangle, const int_rectangle & lprectWindow);


      virtual bool get_element_rectangle(::int_rectangle & rectangle, ::enum_element eelement);


      virtual void get_parent_rectangle(::int_rectangle & rectangle);

      virtual int_rectangle get_margin_rectangle();
      virtual int_rectangle get_caption_text_padding();
      virtual int get_caption_height();
      virtual void calculate_caption_height(::draw2d::graphics_pointer & pgraphics);

      virtual void title_bar_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();

      virtual ::pointer<control_box>get_control_box();


      virtual void OnMove(::pointer<::user::interaction>pframewindow);


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void on_style_change();

      virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual int_size GetMinSize();

      virtual void OnActivate();
      virtual void OnNcCalcSize(::int_rectangle * prectangle);

      //virtual void _001OnBeforeSize(const ::int_rectangle & rectangleWindow);

      virtual ::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder);

      //virtual ::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder);


      virtual status < ::color::color > get_border_main_body_color();


      virtual bool on_message_parent_left_button_down(::message::mouse * pmouse);
      virtual bool on_message_left_button_down(::message::mouse * pmouse);
      virtual bool on_message_left_button_up(::message::mouse * pmouse);
      virtual bool on_message_left_button_double_click(::message::mouse* pmouse);
      virtual bool on_message_parent_mouse_move(::message::mouse * pmouse);
      virtual bool on_message_mouse_move(::message::mouse * pmouse);
      //virtual bool on_message_set_cursor(::message::set_cursor * psetcursor);
      virtual bool _001OnNcLButtonDown(::message::mouse * pmouse);
      virtual bool _001OnNcLButtonUp(::message::mouse * pmouse);
      virtual bool _001OnNcMouseMove(::message::mouse * pmouse);
      virtual bool _001OnNcHitTest(const ::int_point & point, enum_hit_test & ehittest);
      virtual bool on_timer(unsigned int uEvent);
      //virtual bool on_message_size(unsigned int nType, int cx, int cy);
      //virtual bool on_message_move(int x, int y);
      //virtual bool _001OnCommand(wparam wparam, lparam lparam, lresult & lresult);



      virtual void frame_on_attach();
      virtual void frame_on_detach();

      virtual bool is_control_box_moveable();

      virtual void GetFrameRect(int_rectangle & rectangle);



      //virtual void nextstyle(::user::style_context * pcontext) override;
      virtual void place_set_need_redraw(const ::int_rectangle & rectangleAfter, const ::int_rectangle & rectangleBefore, ::draw2d::graphics * pgraphics);

   };



} // namespace experience



