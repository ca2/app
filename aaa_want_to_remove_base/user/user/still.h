#pragma once


namespace user
{


   class CLASS_DECL_BASE still :
      virtual public control
   {
   public:

      enum e_style
      {
         style_none,
         style_text,
         style_image
      };

      ::image_pointer                    m_pimage;          // not pressed default bitmap
      e_rect                            m_erectMargin;
      e_rect                            m_erectBorder;
      e_rect                            m_erectPadding;
      e_int                               m_eintTextAlign;
      e_style                             m_estyle;
      //::enum_check                    m_echeck;
      ::rect                              m_rectText;
      index                               m_iClick;
      //      ::user::front_end_schema::button *  m_pschema;
      //      ::user::front_end_schema::button *  m_pschemaDraw;
      e_stock_icon                        m_estockicon;

      ::rect                  m_rectCheckBox;
      string m_strLink;

      still();
      virtual ~still();


      virtual bool should_hover();

      virtual bool has_link();

      virtual bool create_control(class control_descriptor * pdescriptor) override;

      virtual void resize_to_fit() override;

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



