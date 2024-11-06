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
         style_bitmap,
         style_image_and_text,
         style_push,
         style_list
      };

      class bitmap
      {
      public:

         ::image::image_pointer                    m_pimage;          // not pressed default bitmap
         ::image::image_pointer                    m_pimageSel;       // pressed bitmap
         ::image::image_pointer                    m_pimageFocus;     // focus bitmap
         ::image::image_pointer                    m_pimageDisabled;  // disabled bitmap
         ::image::image_pointer                    m_pimageHover;     // hover bitmap

      };


      class list
      {
      public:

         ::image::image_list_pointer            m_pimagelistNormal;
         ::image::image_list_pointer            m_pimagelistItemHover;
         ::image::image_list_pointer            m_pimagelistSubItemHover;
         int                              m_iImageNormal;
         int                              m_iImageItemHover;
         int                              m_iImageSubItemHover;

      };

      //normal

      //e_rect                            m_erectMargin;
      //e_rect                            m_erectBorder;
      //e_rect                            m_erectPadding;
      ealign                              m_ealignText;
      e_style                             m_estyle;
      //::enum_check                    m_echeck;
      ::rectangle_f64                              m_rectangleText;
      ::collection::index                               m_iClick;
      e_stock_icon                        m_estockicon;
      ::rectangle_f64                              m_rectangleCheckBox;
      bitmap *                            m_pbitmap;
      list *                              m_plist;


      button();
      virtual ~button();


      void user_button_construct();

      virtual bool create_control(class control_descriptor* pdescriptor) override;


      virtual ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, estate estate = e_state_none) const override;
      virtual enum_translucency get_translucency(style * pstyle) const override;



      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawBitmap(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, RECT32 * prectText);

      virtual void _001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics);

      virtual color32_t _001GetButtonBackgroundColor();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool is_custom_draw() override;

      using ::user::check::set_check;
      virtual void set_check(::enum_check check, const ::action_context & action_context) override;
      //virtual ::enum_check get_check() override;

      //virtual bool is_pressed();


      //virtual ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_create);


      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable() override;

      //virtual bool has_action_hover() override;

      bool LoadBitmaps(::payload payload,::payload varSel = ::e_type_null,::payload varFocus = ::e_type_null,::payload varDisabled = ::e_type_null,::payload varHover = ::e_type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
      virtual void BaseToolTipGetRect(RECT32 * prect);

      virtual int BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void set_stock_icon(e_stock_icon eicon) override;
      virtual e_stock_icon get_stock_icon() override;

      virtual color32_t get_button_text_color();


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace user



