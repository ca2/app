#pragma once

//
//namespace user
//{
//
//
//   class CLASS_DECL_AURA button :
//      virtual public control
//   {
//   public:
//
//      enum e_style
//      {
//         style_none,
//         style_normal,
//         style_simple,
//         style_bitmap,
//         style_push,
//         style_list
//      };
//
//      class bitmap
//      {
//      public:
//
//         ::image_pointer                    m_pimage;          // not pressed default bitmap
//         ::image_pointer                    m_pimageSel;       // pressed bitmap
//         ::image_pointer                    m_pimageFocus;     // focus bitmap
//         ::image_pointer                    m_pimageDisabled;  // disabled bitmap
//         ::image_pointer                    m_pimageHover;     // hover bitmap
//
//      };
//
//
//      class list
//      {
//      public:
//
//         __pointer(image_list)                      m_pimagelistNormal;
//         __pointer(image_list)                      m_pimagelistItemHover;
//         __pointer(image_list)                      m_pimagelistSubItemHover;
//         i32                             m_iImageNormal;
//         i32                             m_iImageItemHover;
//         i32                             m_iImageSubItemHover;
//
//      };
//
//      //normal
//
//      e_style                             m_estyle;
//      enum_check                      m_echeck;
//      ::rect                              m_rectText;
//      index                               m_iClick;
//      ::user::front_end_schema::button *  m_pschema;
//      ::user::front_end_schema::button *  m_pschemaDraw;
//      e_stock_icon                        m_estockicon;
//
//
//      // bitmap
//
//      bitmap *                            m_pbitmap;
//
//      list *                              m_plist;
//      //bool                                m_bActionHover;
//
//
//
//      button();
//      button(::object * pobject);
//      virtual ~button();
//
//      virtual bool create_control(class control_descriptor * pdescriptor, index iItem = 0);
//
//      virtual void resize_to_fit();
//
//      virtual void install_message_routing(::channel * pchannel);
//
//      virtual void _001OnDrawPush(::draw2d::graphics_pointer & pgraphics);
//      virtual void _001OnDrawList(::draw2d::graphics_pointer & pgraphics);
//      virtual void _001OnDrawBitmap(::draw2d::graphics_pointer & pgraphics);
//
//      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
//      virtual void _002OnDraw(::draw2d::graphics_pointer & pgraphics);
//
//      virtual bool is_custom_draw();
//
//      virtual void _001SetCheck(enum_check check, const ::action_context & action_context);
//      virtual enum_check _001GetCheck();
//
//      virtual bool is_pressed();
//
//
//      virtual void on_hit_test(::user::item & item);
//
//      DECL_GEN_SIGNAL(_001OnKeyDown);
//      DECL_GEN_SIGNAL(_001OnLButtonDown);
//      DECL_GEN_SIGNAL(_001OnLButtonUp);
//      DECL_GEN_SIGNAL(_001OnMButtonDown);
//      DECL_GEN_SIGNAL(_001OnMButtonUp);
//      DECL_GEN_SIGNAL(_001OnMouseMove);
//      DECL_GEN_SIGNAL(_001OnMouseLeave);
//      DECL_GEN_SIGNAL(_001OnCreate);
//
//
//      ::size calc_text_size();
//
//      virtual bool keyboard_focus_is_focusable();
//
//      virtual bool has_action_hover();
//
//      bool LoadBitmaps(::var var,::var varSel = ::type_null,::var varFocus = ::type_null,::var varDisabled = ::type_null,::var varHover = ::type_null);
//
//
//      virtual void set_button_style(e_style estyle);
//      virtual void on_enter_button_style(e_style estyle);
//      virtual void on_exit_button_style(e_style estyle);
//
//      virtual void BaseToolTipRelayEvent(::message::message * pmessage);
//      virtual void BaseToolTipGetRect(LPRECT lprect);
//      virtual i32 BaseToolTipGetIndex();
//
//      virtual void pre_translate_message(::message::message * pmessage);
//
//
//      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
//
//
//      virtual void set_stock_icon(e_stock_icon eicon);
//      virtual e_stock_icon get_stock_icon();
//
//   };
//
//
//} // namespace user
//
//
//
