#pragma once


namespace experience
{


   class CLASS_DECL_BASE frame :
      virtual public ::object
   {
   public:


      enum enum_element
      {

         ElementNone,
         ElementTopLeftIcon,
         ElementMoveGripMinimal,
         ElementEnd,

      };


      status < ::color::color >       m_colorMoveableBorderHilight;
      status < ::color::color >       m_colorMoveableBorderDkShadow;
      status < ::color::color >       m_colorCaptionTextBk;
      status < ::color::color >       m_colorActiveCaptionTextBk;
      status < ::color::color >       m_colorCaptionText;

      bool                                   m_bHollow;
      string                                 m_strExperience;
      string                                 m_strFrameSchema;
      ::rectangle_i32                        m_rectangleCaption;
      ::rectangle_i32                        m_rectangleWindowText;
      int                                    m_iControlBoxPosition;
      //::rectangle_i32                      m_rectangleControlBoxFullScreen;
      //::rectangle_i32                      m_rectangleControlBoxZoomed;
      //::rectangle_i32                      m_rectangleControlBoxNormal;
      point_i32                              m_pointWindowIcon;
      ///point_i32                           m_pointMoveGripMinimal;

      status < ::color::color >       m_colorMoveableBorder;
      status < ::color::color >       m_colorMoveableBorderShadow;


      ::experience::experience *             m_pexperience;
      ::experience::frame_window *           m_pframewindow;

      __composite(control_box)               m_pcontrolbox;

      i32                                    m_iCaptionHeight;
      i32                                    m_iTitleBottom;

      ::rectangle_i32                        m_rectangleMarginFullScreen;
      ::rectangle_i32                        m_rectangleMarginZoomed;
      ::rectangle_i32                        m_rectangleMarginNormal;
      ::rectangle_i32                        m_rectangleMarginDock;

      ::rectangle_i32                        m_rectangleCaptionTextPadding;


      ::rectangle_i32                        m_rectangleClient;
      ::rectangle_i32                        m_rectangleWindow;

      bool                                   m_bFirstLayoutDone;
      bool                                   m_bControlBoxAlignRight;
      bool                                   m_bInitialControlBoxPosition;
      bool                                   m_bPendingStyleChange;



      frame();
      ~frame() override;


      inline ::base::application* get_app() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      virtual int adjust_client_height(int iHeight);
      virtual int adjust_client_width(int iWidth);

      //virtual void set_style(const ::string & pszStyle);
      virtual void on_initialize_experience_frame();
      virtual void on_initialize_appearance();

      virtual void on_defer_display();

      //virtual void update_dock_grip_border_and_display();
      virtual void sync_dock_grip_border();

      //virtual void update_drawing_objects();
      virtual void update_window_client_rect();
      //virtual void update_window_region(const ::rectangle_i32 & rectangleWindow);

      //virtual void update_window();
      //virtual void update_window_style();

      virtual void defer_frame_placement_snapping();


      virtual string get_default_user_style() const;


      virtual void set_moveable_border_color(const ::color::color & color);




      virtual bool get_window_client_rect(RECTANGLE_I32 * prectangle);

      virtual bool get_draw_client_rect(RECTANGLE_I32 * prectangle);


      //virtual void calc_window_client_rect(RECTANGLE_I32 * prectangle, const rectangle_i32 & lprectWindow);


      virtual bool get_element_rect(RECTANGLE_I32 * prectangle, enum_element eelement);


      virtual void get_parent_rect(RECTANGLE_I32 * prectangle);

      virtual rectangle_i32 get_margin_rect();
      virtual rectangle_i32 get_caption_text_padding();
      virtual i32 get_caption_height();
      virtual i32 calc_caption_height(::draw2d::graphics_pointer & pgraphics);

      virtual void title_bar_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();

      virtual __pointer(control_box) get_control_box();


      virtual void OnMove(__pointer(::user::interaction) pframewindow);


      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void on_style_change();

      virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual size_i32 GetMinSize();

      virtual void OnActivate();
      virtual void OnNcCalcSize(RECTANGLE_I32 * prectangle);

      //virtual void _001OnBeforeSize(const ::rectangle_i32 & rectangleWindow);

      virtual e_hittest _001HitTest(const ::point_i32 & point);


      virtual status < ::color::color > get_border_main_body_color();


      virtual bool on_message_left_button_down(::message::mouse * pmouse);
      virtual bool on_message_left_button_up(::message::mouse * pmouse);
      virtual bool on_message_mouse_move(::message::mouse * pmouse);
      //virtual bool on_message_set_cursor(::message::set_cursor * psetcursor);
      virtual bool _001OnNcLButtonDown(::message::mouse * pmouse);
      virtual bool _001OnNcLButtonUp(::message::mouse * pmouse);
      virtual bool _001OnNcMouseMove(::message::mouse * pmouse);
      virtual bool _001OnNcHitTest(const ::point_i32 & point, enum_hit_test & ehittest);
      virtual bool _001OnTimer(::u32 uEvent);
      //virtual bool on_message_size(::u32 nType, i32 cx, i32 cy);
      //virtual bool on_message_move(i32 x, i32 y);
      //virtual bool _001OnCommand(wparam wparam, lparam lparam, lresult & lresult);



      virtual void frame_on_attach();
      virtual void frame_on_detach();

      virtual bool is_control_box_moveable();

      virtual void GetFrameRect(rectangle_i32 * prectangle);



      //virtual void nextstyle(::user::style_context * pcontext) override;


   };



} // namespace experience



