#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM frame_005 :
               public frame
            {
            public:


               ::draw2d::brush_pointer                m_brushGrip;
               ::draw2d::brush_pointer                m_brushTextCaption;


               frame_005();
               virtual ~frame_005();


               virtual string get_default_user_style() const override;
               virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

               virtual void on_initialize_experience_frame() override;


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
               void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);

               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside);

               void GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * prectangle, enum_border eside);

               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);

               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_grip egrip);

               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               e_hittest _001HitTest(const ::point_i32 & point) override;


            };


         } // namespace tranquillum


   } // namespace experience



