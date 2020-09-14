#pragma once


namespace user
{


   class CLASS_DECL_AXIS button :
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
      e_align                             m_ealignText;
      e_style                             m_estyle;
      //::enum_check                    m_echeck;
      ::rect                              m_rectText;
      index                               m_iClick;
      e_stock_icon                        m_estockicon;
      ::rect                              m_rectCheckBox;
      bitmap *                            m_pbitmap;
      list *                              m_plist;


      button();
      virtual ~button();


      void user_button_construct();

      virtual bool create_control(class control_descriptor* pdescriptor) override;


      virtual ::draw2d::font_pointer get_font(style* pstyle, e_element eelement = element_none, estate estate = e_state_none) const override;
      virtual e_translucency get_translucency(style * pstyle) const override;



      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawBitmap(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, RECT * prectText);

      virtual void _001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics);

      virtual COLORREF _001GetButtonBackgroundColor();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool is_custom_draw() override;

      using ::user::check::_001SetCheck;
      virtual void _001SetCheck(::enum_check check, const ::action_context & action_context) override;
      //virtual ::enum_check _001GetCheck() override;

      //virtual bool is_pressed();


      //virtual void on_hit_test(::user::item & item) override;

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnCreate);


      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable() override;

      //virtual bool has_action_hover() override;

      bool LoadBitmaps(::var var,::var varSel = ::type_null,::var varFocus = ::type_null,::var varDisabled = ::type_null,::var varHover = ::type_null);


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

      virtual COLORREF get_button_text_color();


      virtual void update(::update * pupdate) override;


   };


} // namespace user



