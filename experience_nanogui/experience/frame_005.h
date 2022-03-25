#pragma once



namespace experience_nanogui
{



      class CLASS_DECL_APP_EXPERIENCE_CORE frame_005 :
         public frame
      {
      public:


         ::draw2d::brush_pointer                m_pbrushGrip;
         ::draw2d::brush_pointer                m_pbrushTextCaption;


         frame_005();
         virtual ~frame_005();


         void on_initialize_experience_frame() override;


         string get_default_user_style() const override;
         void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;


         void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
         void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight) override;
         void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
         void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside);
         void GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside);
         void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
         void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_grip egrip);
         void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

         ::experience::enum_frame experience_frame_hit_test(const ::point_i32 & point) override;


      };



} // namespace experience_nanogui


