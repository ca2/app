#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM frame_002 :
               public frame
            {
            public:


               frame_002();
               virtual ~frame_002();

               virtual void on_style_change();

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient);

               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, enum_border eside);

               void GetBorderRect(const ::rectangle_i32 & rectClient, RECTANGLE_I32 * prectangle, enum_border eside);

               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient);

               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, enum_grip egrip);

               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               virtual e_hittest _001HitTest(const ::point_i32 & point);

               color32_t get_border_main_body_color();


            };


         } // namespace tranquillum


   } // namespace experience



