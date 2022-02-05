#pragma once


namespace user
{


   class CLASS_DECL_AURA button :
      virtual public ::user::interaction,
      virtual public check
   {
   public:


      enum e_style
      {
         style_none,
         style_normal,
         style_simple,
         style_image,
         style_image_and_text,
         style_push,
         style_list,
         style_stock_icon,
      };

      class bitmap
      {
      public:

         ::image_pointer                    m_pimage;          // not pressed default bitmap
         ::image_pointer                    m_pimageSel;       // pressed bitmap
         ::image_pointer                    m_pimageFocus;     // focus bitmap
         ::image_pointer                    m_pimageDisabled;  // disabled bitmap
         ::image_pointer                    m_pimageHover;     // hover bitmap

      };


      class list
      {
      public:

         __pointer(::image_list)          m_pimagelistNormal;
         __pointer(::image_list)          m_pimagelistItemHover;
         __pointer(::image_list)          m_pimagelistSubItemHover;
         i32                              m_iImageNormal;
         i32                              m_iImageItemHover;
         i32                              m_iImageSubItemHover;

      };

      //normal

      //e_rect                            m_erectMargin;
      //e_rect                            m_erectBorder;
      //e_rect                            m_erectPadding;
      ::e_align                           m_ealignText;
      ::e_draw_text                       m_edrawtext;
      e_style                             m_estyle;
      ::rectangle_i32                     m_rectangleText;
      index                               m_iClick;
      enum_stock_icon                     m_estockicon;
      ::rectangle_i32                     m_rectangleCheckBox;
      bitmap *                            m_pbitmap;
      list *                              m_plist;


      button();
      button(const ::string & pszName, const ::atom & atom);
      ~button() override;


      void user_button_construct();


      ::element * clone() const override;

      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;


      virtual ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) const override;
      virtual enum_translucency get_translucency(style * pstyle) const override;



      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawBitmap(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, RECTANGLE_I32 * prectText);

      virtual void _001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics);

      virtual ::color::color _001GetButtonBackgroundColor();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool is_custom_draw() override;

      using ::user::check::_001SetCheck;
      virtual void _001SetCheck(::enum_check check, const ::action_context & action_context) override;
      //virtual ::enum_check _001GetCheck() override;

      //virtual bool is_pressed();


      //virtual void on_hit_test(::item & item) override;

      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_create);


      virtual ::size_f64 _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool keyboard_focus_is_focusable() const override;

      //virtual bool has_action_hover() override;

      bool LoadBitmaps(::payload payload,::payload varSel = ::e_type_null,::payload varFocus = ::e_type_null,::payload varDisabled = ::e_type_null,::payload varHover = ::e_type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
      virtual void BaseToolTipGetRect(RECTANGLE_I32 * prectangle);

      virtual i32 BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pmessage) override;


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      void set_stock_icon(enum_stock_icon eicon) override;
      enum_stock_icon get_stock_icon() override;

      //virtual ::color::color get_button_text_color();


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace user



