#pragma once


#include "frame.h"


namespace experience_anthill
{


   class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame_005 :
      public frame
   {
   public:


      ::draw2d::brush_pointer                m_pbrushGrip;
      ::draw2d::brush_pointer                m_pbrushTextCaption;


      frame_005();
      ~frame_005() override;


      void on_initialize_experience_frame() override;

      string get_default_user_style() const override;
      void _on_style_change(::draw2d::graphics_pointer & pgraphics)override;


      void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
      void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight) override;
      void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
      void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside);
      void GetBorderRectangle(const ::rectangle_i32 & rectangleClient, ::rectangle_i32 * lprect, enum_border eside);
      void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
      void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_grip egrip);
      void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

      //::experience::enum_frame experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;


   };


} // namespace experience_anthill




