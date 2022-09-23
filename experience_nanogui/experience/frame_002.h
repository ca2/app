#pragma once


#include "frame.h"


namespace experience_nanogui
{



   class CLASS_DECL_APP_EXPERIENCE_CORE frame_002 :
      public frame
   {
   public:


      frame_002();
      virtual ~frame_002();

      string get_default_user_style() const override;
      virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

      void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
      void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
      void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside);
      void GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside);
      void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
      void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_grip egrip);
      void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

      ::experience::enum_frame experience_frame_hit_test(const ::point_i32 & point) override;

      status < ::color::color > get_border_main_body_color() override;


   };


} // namespace experience_nanogui



