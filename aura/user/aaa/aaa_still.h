#pragma once


namespace user
{


   class CLASS_DECL_AURA still :
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
      //::rectangle                              m_rectMargin;
      //::rectangle                              m_rectBorder;
      //::rectangle                              m_rectPadding;
      ::e_align                             m_ealignText;
      e_style                             m_estyle;
      ::rectangle                              m_rectText;
      index                               m_iClick;
      e_stock_icon                        m_estockicon;

      ::rectangle                              m_rectCheckBox;
      string                              m_strLink;
      ::write_text::font_pointer              m_pfont;
      

      still();
      virtual ~still();


      virtual bool create_control(class control_descriptor * pdescriptor) override;

      virtual ::write_text::font_pointer get_font(style * pstyle, enum_element eelement = e_element_none, estate estate = e_state_none) const override;

      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDrawImage(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001SetCheck(::enum_check check, const ::action_context & action_context) override;
      //virtual ::enum_check _001GetCheck() override;

      //virtual bool is_pressed();


      //virtual void on_hit_test(::user::item & item) override;

      DECLARE_MESSAGE_HANDLER(_001OnKeyDown);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_middle_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_create);


      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable() override;

      // virtual bool has_action_hover() override;

      bool LoadBitmaps(::payload payload, ::payload varSel = ::e_type_null, ::payload varFocus = ::e_type_null, ::payload varDisabled = ::e_type_null, ::payload varHover = ::e_type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
      virtual void BaseToolTipGetRect(RECT32 * prect);

      virtual i32 BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void set_stock_icon(e_stock_icon eicon) override;
      virtual e_stock_icon get_stock_icon() override;

   };


} // namespace user



