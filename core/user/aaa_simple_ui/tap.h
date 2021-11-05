#pragma once


namespace simple_ui
{


   class CLASS_DECL_CORE tap :
      virtual public ::user::interaction
   {
   public:

      bool                 m_bAutoStockIconPenWidth;
      double               m_dStockIconPenWidth;
      e_stock_icon         m_estockicon;
      bool                 m_bDown;
      bool                 m_bMouseMove;


      tap();
      virtual ~tap();

      void install_message_routing(::channel * pchannel) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void simple_ui_draw_simple(::draw2d::graphics_pointer & pgraphics);
      virtual void simple_ui_draw_volume(::draw2d::graphics_pointer & pgraphics);

      virtual void simple_ui_draw_text(::draw2d::graphics_pointer & pgraphics);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);


      virtual bool keyboard_focus_is_focusable() const override;
      virtual bool is_hover();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;

   };




} // namespace simple_ui




