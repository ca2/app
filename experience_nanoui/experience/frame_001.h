#pragma once


#include "frame.h"


namespace experience_nanoui
{


   class CLASS_DECL_APP_EXPERIENCE_CORE frame_001 :
      public frame
   {
   public:

         
      frame_001();
      ~frame_001() override;
         

      string get_default_user_style() const override;
      virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

      void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
      void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX);
      void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_border eside);
      //void GetBorderRectangle(const ::int_rectangle & rectangleX, ::int_rectangle * lprect, enum_border eside);
      void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX);
      void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_grip egrip);
      void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);

      ::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


   };


} // namespace experience_nanoui



