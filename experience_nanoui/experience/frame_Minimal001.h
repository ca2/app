#pragma once


#include "frame.h"


namespace experience_nanoui
{


   class CLASS_DECL_APP_EXPERIENCE_CORE frame_Minimal001 :
      public frame
   {
   public:


      frame_Minimal001();
      virtual ~frame_Minimal001();


      string get_default_user_style() const override;
      void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

      void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
      void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::i32_rectangle & rectangleX);
      void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::i32_rectangle & rectangleX, enum_border eside);
      //void GetBorderRectangle(const ::i32_rectangle & rectangleX, ::i32_rectangle * lprect, enum_border eside);
      void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::i32_rectangle & rectangleX);
      void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::i32_rectangle & rectangleX, enum_grip egrip);
      void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::i32_rectangle & rectangle);

      ::experience::enum_frame experience_frame_hit_test(const ::i32_point & point, ::user::e_zorder ezorder) override;


   };


} // namespace experience_nanoui



