#pragma once


namespace user
{


   class CLASS_DECL_AXIS still :
      virtual public ::user::interaction
   {
   public:

      enum e_style
      {
         style_none,
         style_text,
         style_image
      };

      ::image_pointer                     m_pimage;          // not pressed default bitmap
      //::rect                              m_rectMargin;
      //::rect                              m_rectBorder;
      //::rect                              m_rectPadding;
      ::e_align                             m_ealignText;
      e_style                             m_estyle;
      ::rect                              m_rectText;
      index                               m_iClick;
      e_stock_icon                        m_estockicon;

      ::rect                              m_rectCheckBox;
      string                              m_strLink;
      ::draw2d::font_pointer              m_pfont;
      

      still();
      virtual ~still();


      virtual bool should_hover();

      virtual bool has_link();

      virtual bool create_control(class control_descriptor * pdescriptor) override;

      virtual ::draw2d::font_pointer get_font(style * pstyle, e_element eelement = element_none, estate estate = e_state_none) const override;

      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDrawImage(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001SetCheck(::enum_check check, const ::action_context & action_context) override;
      //virtual ::enum_check _001GetCheck() override;

      //virtual bool is_pressed();


      //virtual void on_hit_test(::user::item & item) override;

      DECL_GEN_SIGNAL(_001OnKeyDown);
      //DECL_GEN_SIGNAL(_001OnLButtonDown);
      //DECL_GEN_SIGNAL(_001OnLButtonUp);
      //DECL_GEN_SIGNAL(_001OnMButtonDown);
      //DECL_GEN_SIGNAL(_001OnMButtonUp);
      //DECL_GEN_SIGNAL(_001OnMouseMove);
      //DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnCreate);


      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable() override;

      // virtual bool has_action_hover() override;

      bool LoadBitmaps(::var var, ::var varSel = ::type_null, ::var varFocus = ::type_null, ::var varDisabled = ::type_null, ::var varHover = ::type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
      virtual void BaseToolTipGetRect(RECT * prect);

      virtual i32 BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void set_stock_icon(e_stock_icon eicon) override;
      virtual e_stock_icon get_stock_icon() override;

   };


} // namespace user



