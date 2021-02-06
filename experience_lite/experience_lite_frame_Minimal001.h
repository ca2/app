#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame_Minimal001 :
               public frame
            {
            public:


               frame_Minimal001(::layered * pobjectContext);
               virtual ~frame_Minimal001();

               virtual void on_style_change();

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient, enum_border eside);
               void GetBorderRect(const RECTANGLE_I32 & lpcrectClient, RECTANGLE_I32 * lprect, enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 & lpcrectClient, enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               virtual e_hittest _001HitTest(const ::point_i32 & point);


            };


         } // namespace lite



      


   } // namespace experience









