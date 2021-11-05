#pragma once


namespace user
{


   class CLASS_DECL_CORE step_slider :
      public ::user::interaction
   {
   public:


      int_scalar           m_scalar;


      step_slider();
      virtual ~step_slider();

      
      //bool create_window(::user::interaction * puserinteractionParent, id id);


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void GetStepHoverRect(RECTANGLE_I32 * prectangle, i64 iVal, i64 iMin, i64 iMax, const ::rectangle_i32 & rectangleClient);

      void GetStepRect(RECTANGLE_I32 * prectangle, i64 iVal, i64 iMin, i64 iMax, const ::rectangle_i32 & lpcrectClient);


      void on_hit_test(::item & item) override;

      void update_hover();


      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   };

} // namespace user
