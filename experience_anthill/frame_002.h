#pragma once



namespace experience
{


   namespace anthill
   {


            class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame_002 :
               public frame
            {
            public:


               frame_002();
               virtual ~frame_002();

               
               virtual string get_default_user_style() const;
               virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside);
               void GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               virtual e_hittest _001HitTest(const ::point_i32 & point);

               virtual status < ::color::color > get_border_main_body_color() override;


            };




   } // namespace anthill


} // namespace experience




