#pragma once


namespace experience
{

   class  CLASS_DECL_BASE control_box :
      virtual public ::user::box
   {
   public:


      ::experience::frame_window * m_pframewindow;
      millis m_tickShow;
      bool                          m_bShowAttempt;
      bool                          m_bDrag;
      point                         m_pointDrag;
      i32                           m_iDefaultButtonMargin;
      ::size                        m_sizeButtonDefault;
      ::draw2d::font_pointer             m_fontMarlett;

      ::draw2d::brush_pointer            m_brushButtonBack;
      ::draw2d::brush_pointer            m_brushButtonBackSel;
      ::draw2d::brush_pointer            m_brushButtonBackFocus;
      ::draw2d::brush_pointer            m_brushButtonBackDisabled;

      ::draw2d::pen_pointer              m_penButtonBack;
      ::draw2d::pen_pointer              m_penButtonBackSel;
      ::draw2d::pen_pointer              m_penButtonBackFocus;
      ::draw2d::pen_pointer              m_penButtonBackDisabled;

      color32_t                      m_crButtonFore;
      color32_t                      m_crButtonForeSel;
      color32_t                      m_crButtonForeFocus;
      color32_t                      m_crButtonForeDisabled;

      map < e_button, e_button, id >           m_mapButtonId;
      id_map < e_button >           m_mapIdButton;
      map < e_button, e_button, bool, bool >       m_buttonmapPresent;
            

      color32_t                      m_crBackground;


      map < e_button, e_button, __pointer(button), __pointer(button) >      m_buttonmap;


      control_box();
      virtual ~control_box();


      virtual void set_button_color_system_default_001();


      virtual void install_message_routing(::channel *pframewindow);

      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics);

      void drag(const ::point & point);


      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      virtual ::size get_button_size(e_button ebutton);

      virtual ::rect get_button_margin(e_button ebutton);

      virtual i32 calc_button_size(::draw2d::graphics_pointer & pgraphics);

      virtual i32 calc_control_box_height();

      virtual i32 calc_control_box_normal_width();

      virtual i32 calc_control_box_zoomed_width();

      virtual i32 calc_control_box_full_screen_width();

      virtual void reset_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void _layout_button(e_button ebutton, ::rect & rect);
      virtual bool should_show_button(e_button ebutton);

      virtual bool has_button(e_button ebutton);
      virtual void hide_button(e_button ebutton, bool bHide = true);
      virtual bool create_buttons();
      virtual void update_control_box_button(e_button ebutton);
      virtual void update_control_box_buttons();
      virtual bool create_button(e_button ebutton);
      virtual bool get_control_box_button_caption(e_button ebutton, string & str);
      virtual e_stock_icon get_control_box_button_stock_icon(e_button ebutton);
      virtual void set_control_box_button_id(e_button ebutton, id id);
      virtual id get_control_box_button_id(e_button ebutton);
      virtual string get_control_box_button_tag(e_button ebutton);
      virtual e_button get_control_box_button_type(id id);
      __pointer(button) get_button(e_button ebutton);
      virtual __pointer(button) get_box_button(e_button ebutton);

      virtual bool get_font(::draw2d::font_pointer & font);

   };



} // namespace experience



