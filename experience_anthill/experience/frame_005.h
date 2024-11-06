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
      void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight) override;
      void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX);
      void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_border eside);
      //void GetBorderRectangle(const ::int_rectangle & rectangleX, ::int_rectangle * lprect, enum_border eside);
      void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX);
      void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, enum_grip egrip);
      void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);

      //::experience::enum_frame experience_frame_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


   };


} // namespace experience_anthill




