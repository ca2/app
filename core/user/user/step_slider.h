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

      
      bool create_window(::user::interaction * pwndParent, id id);


      virtual void install_message_routing(::channel * pchannel);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      void GetStepHoverRect(RECT32 * prect, i64 iVal, i64 iMin, i64 iMax, const ::rect & rectClient);

      void GetStepRect(RECT32 * prect, i64 iVal, i64 iMin, i64 iMax, const ::rect & lpcrectClient);


      void on_hit_test(::user::item & item);

      void update_hover();


      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
   };

} // namespace user
