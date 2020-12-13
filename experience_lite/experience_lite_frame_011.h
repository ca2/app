#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame_011:
               public frame
            {
            public:


               frame_011(::layered * pobjectContext);
               virtual ~frame_011();


               virtual void on_style_change();


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics,const RECT32 & lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics,const RECT32 & lpcrectClient,enum_border eside);
               void GetBorderRect(const RECT32 & lpcrectClient,LPRECT32 lprect,enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics,const RECT32 & lpcrectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics,const RECT32 & lpcrectClient,enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const RECT32 & rect);

               virtual e_hittest _001HitTest(const ::point & point);


            };


         } // namespace lite



      


   } // namespace experience









