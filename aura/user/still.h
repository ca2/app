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


      ::write_text::font_pointer          m_pfont;
      ::image_pointer                     m_pimage;          // not pressed default bitmap
      //::rectangle_i32                   m_rectangleMargin;
      //::rectangle_i32                   m_rectangleBorder;
      //::rectangle_i32                   m_rectanglePadding;
      ::e_align                           m_ealignText;
      e_style                             m_estyle;
      ::rectangle_i32                     m_rectangleText;
      index                               m_iClick;
      enum_stock_icon                     m_estockicon;

      ::write_text::text_out_array        m_textouta;

      ::rectangle_i32                     m_rectangleCheckBox;
      string                              m_strLink;
      

      still();
      virtual ~still();


      //virtual bool should_hover();

      virtual bool has_link() const override;

      //virtual bool create_interaction(::user::interaction * pinteractionParent) override;

      virtual ::write_text::font_pointer get_font(style * pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) const override;

      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDrawImage(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001SetCheck(::enum_check check, const ::action_context & action_context) override;
      //virtual ::enum_check _001GetCheck() override;

      //virtual bool is_pressed();

      //virtual ::write_text::font_pointer get_font(style * pstyle, enum_element eelement, estate estate = e_state_none) const;



      //virtual void on_hit_test(::item & item) override;

      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_middle_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_create);


      virtual ::size_f64 _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool keyboard_focus_is_focusable() const override;

      // virtual bool has_action_hover() override;

      bool LoadBitmaps(::payload payload, ::payload varSel = ::e_type_null, ::payload varFocus = ::e_type_null, ::payload varDisabled = ::e_type_null, ::payload varHover = ::e_type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
      virtual void BaseToolTipGetRect(RECTANGLE_I32 * prectangle);

      virtual i32 BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pmessage) override;


      void on_hit_test(::item& item) override;


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      void set_stock_icon(enum_stock_icon eicon) override;
      enum_stock_icon get_stock_icon() override;


   };


} // namespace user



